/*
 * LogicCMD.cpp
 *
 *  Created on: 2014-5-6
 *      Author: Ralf
 */

#include "LogicCMD.h"
#include "LogicUnitWrap.h"
#include "LogicCmdUnits.h"
#include <math.h>


int CLogicCMD::ChangeEquipSub(unsigned uid, unsigned equip, unsigned lvl, unsigned stone, unsigned type, unsigned spirit, unsigned free, Json::Value &keep, Json::Value &result,unsigned lasttime,unsigned seqid)
{
	if(spirit == 0)
		return R_ERR_PARAM;
	if(free)
		stone = 0;
	bool isAct = true;
	if(Time::GetGlobalTime() < Config::GetIntValue(CONFIG_ZHIZUN_BEGIN_TS)
	|| Time::GetGlobalTime() >= Config::GetIntValue(CONFIG_ZHIZUN_END_TS))
		isAct = false;
	if(free && !isAct)
		return R_ERR_PARAM;

	int ret;
	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	ret = logicUser.GetUser(uid,dataUser);
	if(ret)
	{
		error_log(" get  user info failed,uid = %u",uid);
		return ret;
	}
	ret = checkLastSaveUID(dataUser);
	if(ret)
		return ret;

	ret = checkLastSaveTime(dataUser,lasttime,seqid);
	if(ret)
		return ret;
	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	Json::Reader reader;
	Json::FastWriter writer;
	Json::Value user_flag;
	bool bsave = false;
	reader.parse(dataUser.user_flag,user_flag);

	Json::Value newAct;
	CLogicSecinc logicSecinc;
	if(isAct)
	{
		ret = logicSecinc.GetSecinc(uid, NAT_ZHIZUN_XILIAN, newAct);
		if (ret == R_ERR_NO_DATA)
		{
			newAct["id"] = NAT_ZHIZUN_XILIAN;
			newAct["a"] = 0;
			newAct["b"] = 0;
			newAct["c"] = 0;
			newAct["d"] = 0;
			newAct["v"] = Config::GetIntValue(CONFIG_ZHIZUN_VER);
		}
		else if(ret)
			return ret;
		if(Config::GetIntValue(CONFIG_ZHIZUN_VER) != newAct["v"].asInt())
		{
			newAct["a"] = 0;
			newAct["b"] = 0;
			newAct["c"] = 0;
			newAct["d"] = 0;
			newAct["v"] = Config::GetIntValue(CONFIG_ZHIZUN_VER);
		}
	}

	unsigned i;
	Json::Value dataEquip,dataStone;
	CLogicEquipment loigcEquipment;
	ret = loigcEquipment.Get(uid, equip,dataEquip);
	if(ret)
		return ret;
	if(stone)
	{
		ret = loigcEquipment.Get(uid, stone,dataStone);
		if(ret)
			return ret;
	}
	unsigned ch, myStoneID;
	if(!dataEquip.isMember("sub") || !Json::GetUInt(dataEquip,"ch",ch))
		return R_ERR_DB;
	if(stone && !Json::GetUInt(dataStone,"id",myStoneID))
		return R_ERR_DB;

	unsigned subNum = getSubNumByCh(ch);
	subNum -= keep.size();
	vector<string> keepstr;
	for(i=0;i<keep.size();++i)
		keepstr.push_back(keep[i].asString());
	CDataXML *dataXML = CDataXML::GetCDataXML();
	if(!dataXML)
	{
		error_log("GetInitXML fail");
		return R_ERR_DB;
	}
	vector<EquipSub> sub;
	unsigned stoneID,gold;
	ret = dataXML->GetEquipSub(lvl,stoneID,gold,subNum,keepstr,sub);
	if(ret)
		return ret;

	if (spirit > dataUser.battle_spirits)
	{
		LOGIC_ERROR_RETURN_MSG("battle_spirits less than zero");
	}
	dataUser.battle_spirits -= spirit;

	if(stone && stoneID != myStoneID)
		return R_ERR_LOGIC;
	if(stone)
	{
		ret = loigcEquipment.UseEquipment(uid, myStoneID, stone, 1, "smithy_xi_tab");
		if(ret)
			return ret;
	}

	unsigned stonegold = 0;
	if(stone == 0 && free == 0)
	{
#ifdef SG_16_VER
		switch(stoneID)
		{
		case 4011:
			stonegold = 2;
			break;
		case 4012:
			stonegold = 6;
			break;
		case 4013:
			stonegold = 18;
			break;
		case 4014:
			stonegold = 54;
			break;
		default:
			return R_ERR_LOGIC;
			break;
		}
#else
		switch(stoneID)
		{
		case 4011:
			stonegold = 10;
			break;
		case 4012:
			stonegold = 40;
			break;
		case 4013:
			stonegold = 160;
			break;
		case 4014:
			stonegold = 640;
			break;
		default:
			return R_ERR_LOGIC;
			break;
		}
#endif

	}
	if(gold+stonegold)
	{
		CLogicPay logicPay;
		DataPay payData;
		ret = logicPay.ProcessOrderForBackend(uid, type?-(gold+stonegold):0, type?0:-(gold+stonegold), payData, "smithy_xi_tab",user_flag,bsave);
		if(ret)
			return ret;
	}
	result["pointpay"].resize(0);
	result["pointpay"] = user_flag["user_pay"];
	if(bsave)
	{
		dataUser.user_flag = writer.write(user_flag);
	}

	if(free)
	{
		int b = 3;
		if(lvl >= 110)
			b = 6;
		if(newAct["b"].asInt() < b)
			return R_ERR_LOGIC;
		newAct["b"] = newAct["b"].asInt() - b;
	}
	if(isAct)
	{
		if(free == 0)
		{
			int b = 0;
			if(lvl >= 110)
				b = 2;
			else if(lvl >= 90)
				b = 1;
			int a = 0;
			if(lvl >= 90)
				a = 1;
			for(i=0;i<sub.size();++i)
			{
				switch(sub[i].star)
				{
				case 7:
					b += 20;
					break;
				case 8:
					b += 40;
					break;
				case 9:
					b += 60;
					break;
				case 10:
					b += 120;
					break;
				default:
					break;
				}
			}
			newAct["a"] = newAct["a"].asInt() + a;
			newAct["b"] = newAct["b"].asInt() + b;
		}
		ret = logicSecinc.SetOneSecinc(uid, newAct);
		if(ret)
			return ret;
		result["newAct"] = newAct;
	}

	Json::Value newSub;
	for(i=0;i<keepstr.size();++i)
		newSub[keepstr[i]] = dataEquip["sub"][keepstr[i]];
	for(i=0;i<sub.size();++i)
		newSub[sub[i].id] = sub[i].value;
	dataEquip["sub"] = newSub;
	ret = loigcEquipment.Chg(uid, equip,dataEquip);
	if(ret)
		return ret;
	unsigned eqid;
	Json::GetUInt(dataEquip,"id",eqid);
	string equipstr = writer.write(dataEquip);
	EQUIPMENT_LOG("uid=%u,id=%u,eqid=%d,act=%s,chg=%d,count=%d,code=%s,data=%s",uid,equip,eqid,"sub",0,0,"sub",equipstr.c_str());

	result["equip"] = dataEquip;

	if(bsave)
		ret = logicUser.SetUser(uid, dataUser);
	else
		ret = logicUser.SetUserLimit(uid, dataUser);
	if(ret)
		return ret;

	return R_SUCCESS;
}
int CLogicCMD::EquipSubAct1(unsigned uid, unsigned equip, string& osub, string& nsub, unsigned lvl, Json::Value &result,unsigned lasttime,unsigned seqid)
{
	if(Time::GetGlobalTime() < Config::GetIntValue(CONFIG_ZHIZUN_BEGIN_TS)
	|| Time::GetGlobalTime() >= Config::GetIntValue(CONFIG_ZHIZUN_END_TS))
		return R_ERR_LOGIC;

	int ret;
	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	ret = logicUser.GetUserLimit(uid,dataUser);
	if(ret)
	{
		error_log(" get  user info failed,uid = %u",uid);
		return ret;
	}
	ret = checkLastSaveUID(dataUser);
	if(ret)
		return ret;

	ret = checkLastSaveTime(dataUser,lasttime,seqid);
	if(ret)
		return ret;
	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	Json::FastWriter writer;
	Json::Value newAct;
	CLogicSecinc logicSecinc;
	ret = logicSecinc.GetSecinc(uid, NAT_ZHIZUN_XILIAN, newAct);
	if (ret == R_ERR_NO_DATA)
	{
		newAct["id"] = NAT_ZHIZUN_XILIAN;
		newAct["a"] = 0;
		newAct["b"] = 0;
		newAct["c"] = 0;
		newAct["d"] = 0;
		newAct["v"] = Config::GetIntValue(CONFIG_ZHIZUN_VER);
	}
	else if(ret)
		return ret;
	if(Config::GetIntValue(CONFIG_ZHIZUN_VER) != newAct["v"].asInt())
	{
		newAct["a"] = 0;
		newAct["b"] = 0;
		newAct["c"] = 0;
		newAct["d"] = 0;
		newAct["v"] = Config::GetIntValue(CONFIG_ZHIZUN_VER);
	}
	unsigned a = 0, c = 0;
	Json::GetUInt(newAct, "a", a);
	Json::GetUInt(newAct, "c", c);
	++c;
	if(c > 15 || a < c*25)
		return R_ERR_LOGIC;
	newAct["c"] = c;

	Json::Value dataEquip;
	CLogicEquipment loigcEquipment;
	ret = loigcEquipment.Get(uid, equip,dataEquip);
	if(ret)
		return ret;
	if(!dataEquip.isMember("sub") || !dataEquip["sub"].isMember(osub) || dataEquip["sub"].isMember(nsub))
		return R_ERR_DB;

	CDataXML *dataXML = CDataXML::GetCDataXML();
	if(!dataXML)
	{
		error_log("GetInitXML fail");
		return R_ERR_DB;
	}
	unsigned star = 0, value = 0;
	Json::GetUInt(dataEquip["sub"], osub.c_str(), value);
	ret = dataXML->GetEquipSubStar(lvl,osub,value,star);
	if(ret)
		return ret;
	ret = dataXML->GetEquipSubValue(lvl,nsub,star,value);
	if(ret)
		return ret;
	dataEquip["sub"].removeMember(osub);
	dataEquip["sub"][nsub] = value;

	ret = logicSecinc.SetOneSecinc(uid, newAct);
	if(ret)
		return ret;
	result["newAct"] = newAct;

	ret = loigcEquipment.Chg(uid, equip,dataEquip);
	if(ret)
		return ret;
	unsigned eqid;
	Json::GetUInt(dataEquip,"id",eqid);
	string equipstr = writer.write(dataEquip);
	EQUIPMENT_LOG("uid=%u,id=%u,eqid=%d,act=%s,chg=%d,count=%d,code=%s,data=%s",uid,equip,eqid,"sub1",0,0,"sub1",equipstr.c_str());
	result["equip"] = dataEquip;

	ret = logicUser.SetUserLimit(uid, dataUser);
	if(ret)
		return ret;

	return R_SUCCESS;
}
int CLogicCMD::EquipSubAct2(unsigned uid, unsigned equip, unsigned all, unsigned lvl, Json::Value &result,unsigned lasttime,unsigned seqid)
{
	if(Time::GetGlobalTime() < Config::GetIntValue(CONFIG_ZHIZUN_BEGIN_TS)
	|| Time::GetGlobalTime() >= Config::GetIntValue(CONFIG_ZHIZUN_END_TS))
		return R_ERR_LOGIC;

	int ret;
	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	ret = logicUser.GetUser(uid,dataUser);
	if(ret)
	{
		error_log(" get  user info failed,uid = %u",uid);
		return ret;
	}
	ret = checkLastSaveUID(dataUser);
	if(ret)
		return ret;

	ret = checkLastSaveTime(dataUser,lasttime,seqid);
	if(ret)
		return ret;
	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	Json::Reader reader;
	Json::FastWriter writer;
	Json::Value user_flag;
	bool bsave = false;
	reader.parse(dataUser.user_flag,user_flag);

	Json::Value newAct;
	CLogicSecinc logicSecinc;
	ret = logicSecinc.GetSecinc(uid, NAT_ZHIZUN_XILIAN, newAct);
	if (ret == R_ERR_NO_DATA)
	{
		newAct["id"] = NAT_ZHIZUN_XILIAN;
		newAct["a"] = 0;
		newAct["b"] = 0;
		newAct["c"] = 0;
		newAct["d"] = 0;
		newAct["v"] = Config::GetIntValue(CONFIG_ZHIZUN_VER);
	}
	else if(ret)
		return ret;
	if(Config::GetIntValue(CONFIG_ZHIZUN_VER) != newAct["v"].asInt())
	{
		newAct["a"] = 0;
		newAct["b"] = 0;
		newAct["c"] = 0;
		newAct["d"] = 0;
		newAct["v"] = Config::GetIntValue(CONFIG_ZHIZUN_VER);
	}
	unsigned a = 0, d = 0;
	Json::GetUInt(newAct, "a", a);
	Json::GetUInt(newAct, "d", d);
	++d;
	if(d > 3 || a < d*40)
		return R_ERR_LOGIC;
	newAct["d"] = d;

	Json::Value dataEquip;
	CLogicEquipment loigcEquipment;
	ret = loigcEquipment.Get(uid, equip,dataEquip);
	if(ret)
		return ret;
	if(!dataEquip.isMember("sub"))
		return R_ERR_DB;

	CDataXML *dataXML = CDataXML::GetCDataXML();
	if(!dataXML)
	{
		error_log("GetInitXML fail");
		return R_ERR_DB;
	}

	if(all)
	{
		CLogicPay logicPay;
		DataPay payData;
		ret = logicPay.ProcessOrderForBackend(uid, -2000, 0, payData, "EquipSubAct2",user_flag,bsave);
		if(ret)
			return ret;
		result["coins"] = payData.coins;
		result["coins2"] = payData.cash;
	}
	result["pointpay"].resize(0);
	result["pointpay"] = user_flag["user_pay"];
	if(bsave)
	{
		dataUser.user_flag = writer.write(user_flag);
	}

	Json::Value::Members members(dataEquip["sub"].getMemberNames());
	for (Json::Value::Members::iterator it = members.begin(); it != members.end(); ++it)
	{
		unsigned star = 0, value = 0;
		Json::GetUInt(dataEquip["sub"], (*it).c_str(), value);
		ret = dataXML->GetEquipSubStar(lvl,*it,value,star);
		if(ret)
			return ret;
		star = all?10:(min(unsigned(10),star+1));
		ret = dataXML->GetEquipSubValue(lvl,*it,star,value);
		if(ret)
			return ret;
		dataEquip["sub"][*it] = value;
	}

	ret = logicSecinc.SetOneSecinc(uid, newAct);
	if(ret)
		return ret;
	result["newAct"] = newAct;

	ret = loigcEquipment.Chg(uid, equip,dataEquip);
	if(ret)
		return ret;
	unsigned eqid;
	Json::GetUInt(dataEquip,"id",eqid);
	string equipstr = writer.write(dataEquip);
	EQUIPMENT_LOG("uid=%u,id=%u,eqid=%d,act=%s,chg=%d,count=%d,code=%s,data=%s",uid,equip,eqid,"sub2",0,0,"sub2",equipstr.c_str());
	result["equip"] = dataEquip;

	if(bsave)
		ret = logicUser.SetUser(uid, dataUser);
	else
		ret = logicUser.SetUserLimit(uid, dataUser);
	if(ret)
		return ret;

	return R_SUCCESS;
}

int CLogicCMD::GetWorldReward(unsigned uid, unsigned index, unsigned eqid, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	if(index > 3/* || ((index == 2 || index == 3) && (eqid < 51001 || eqid > 51004))*/)
		return R_ERR_PARAM;

	int ret;
	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	ret = logicUser.GetUserLimit(uid,dataUser);
	if(ret)
	{
		error_log(" get  user info failed,uid = %u",uid);
		return ret;
	}
	ret = checkLastSaveUID(dataUser);
	if(ret)
		return ret;

	ret = checkLastSaveTime(dataUser,lasttime,seqid);
	if(ret)
		return ret;
	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	Json::Value newAct;
	CLogicSecinc logicSecinc;
	ret = logicSecinc.GetSecinc(uid, NAT_NEWWORLD_MISSION_1, newAct);
	if(ret)
		return ret;
	if(newAct["r"][index].asUInt())
		return R_ERR_LOGIC;
	newAct["r"][index] = 1;
	time_t ts = newAct["ver"].asUInt();
	struct tm *pTm = localtime(&ts);
	unsigned dt = pTm->tm_wday == 5 ? 2 : 1;

	ret = logicSecinc.SetOneSecinc(uid, newAct);
	if(ret)
		return ret;
	result["newAct"] = newAct;

	if(index == 2 || index == 3)
	{
		CLogicEquipment loigcEquipment;
		ret = loigcEquipment.AddOneItem(uid, /*eqid*/4055, 15 * dt * 15, "GetWorldReward", result["equip"], true);
		if(ret)
			return ret;
	}
	else
	{
		dataUser.point += dt * unsigned((double(3.5) * pow((dataUser.level + 10), 2.2) - 600)) / 100 * 3;

		//更新用户level数据
		int levelSize = (int)(sizeof(user_lvl_exp) / sizeof(user_lvl_exp[0]));
		if (dataUser.point >=  user_lvl_exp[levelSize - 1])
		{
			dataUser.level = levelSize;
		}
		else
		{
			for (int i = dataUser.level; i < levelSize; i++)
			{
				if (dataUser.point < (uint64_t)user_lvl_exp[i])
				{
					dataUser.level = i;
					break;
				}
			}
		}

		result["exp"] = Convert::Int64ToString(dataUser.point);
		result["level"] = dataUser.level;
	}

	ret = logicUser.SetUserLimit(uid, dataUser);
	if(ret)
		return ret;

	return R_SUCCESS;
}


int CLogicCMD::GetKillReward(unsigned uid, unsigned index, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	int ret = 0;
	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	ret = logicUser.GetUserLimit(uid,dataUser);
	if(ret)
	{
		error_log(" get_user_info_failed,uid = %u",uid);
		return ret;
	}

	ret = checkLastSaveUID(dataUser);
	if(ret)
		return ret;
	ret = checkLastSaveTime(dataUser,lasttime,seqid);
	if(ret)
		return ret;
	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	CLogicSecinc logicSec;
	Json::Value newAct;

	ret = logicSec.GetSecinc(uid, NAT_NEWWORLD_KILL_REWARDS, newAct);
	if (R_ERR_NO_DATA == ret)
	{
		initGetNewWorldKillNewAct(newAct);
	}
	else if (ret)
	{
		return ret;
	}

	if (NEWWORLD_KILL_VERSION != newAct["v"].asUInt())
	{
		initGetNewWorldKillNewAct(newAct);
	}

	unsigned now = Time::GetGlobalTime();
	unsigned lastts = newAct["b"].asUInt();

	if (lastts > now)
	{
		lastts = now;
		initGetNewWorldKillNewAct(newAct, false);
	}

	//每晚24:00重置
	unsigned bts = CTime::GetDayBeginTime(lastts) + (24 * 60 * 60);
	unsigned rts = 0;

	if (lastts < bts)
	{
		rts = bts;
	}
	else
	{
		rts = bts + CTime::SECONDS_OF_DAY;
	}

	if ((lastts < rts) && (now > rts))
	{
		initGetNewWorldKillNewAct(newAct, false);
	}

	// 每日领取一次
	static const unsigned limit = 1;
	unsigned acount = newAct["a"][index].asUInt();

	if (acount >= limit)
	{
		LOGIC_ERROR_RETURN_MSG("over get kill rewards limit");
	}

	++acount;

	CDataXML *pDataXML = CDataXML::GetCDataXML();
	if(!pDataXML)
	{
		error_log("GetInitXML fail");
		return R_ERR_DB;
	}
	Json::Value data;
	ret = pDataXML->GetWorldBattleKillRewards(data, index);
	if(ret)
	{
		return R_ERR_DATA;
	}
	CLogicEquipment logicEquip;
	Json::Value::Members members(data["reward"].getMemberNames());
	unsigned size = data["reward"].size();
	result["equip"].resize(size);
	int i =0;
	for (Json::Value::Members::iterator it = members.begin(); it != members.end(); ++it)
	{
		string type = *it;
		if(type.find("equip") != string::npos)
		{
			unsigned id = data["reward"][*it]["id"].asUInt();
			unsigned count = data["reward"][*it]["c"].asUInt();
			ret = logicEquip.AddOneItem(uid, id, count, "get_world_battle_Kill_rewards", result["equip"][i], true);
			if (ret)
			{
				return ret;
			}
		}
		++i;
	}
	newAct["a"][index] = acount;

	result["newAct"] = newAct;

	ret = logicSec.SetOneSecinc(uid, newAct);
	if (ret)
	{
		return ret;
	}

	ret = logicUser.SetUserLimit(uid, dataUser);
	if (ret)
	{
		return ret;
	}

	return R_SUCCESS;
}

int CLogicCMD::ProcessTribute(unsigned uid, unsigned id, unsigned fcm, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	int ret;
	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	ret = logicUser.GetUserLimit(uid,dataUser);
	if(ret)
	{
		error_log(" get  user info failed,uid = %u",uid);
		return ret;
	}
	ret = checkLastSaveUID(dataUser);
	if(ret)
		return ret;

	ret = checkLastSaveTime(dataUser,lasttime,seqid);
	if(ret)
		return ret;
	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	CDataTribute tributeDB;
	string stri;
	ret = tributeDB.GetTribute(uid, id, stri);
	if(ret)
		return ret;
	Json::Value jtri;
	Json::Reader reader;
	reader.parse(stri, jtri);
	unsigned coins = 0, c = 0, t = 0;
	Json::GetUInt(jtri, "coins", coins);
	Json::GetUInt(jtri, "c", c);
	Json::GetUInt(jtri, "t", t);
	ret = tributeDB.RemoveTribute(uid, id);
	if(ret)
		return ret;

	coins = (int)(coins * FCM_VALUE[fcm]);
	if(coins)
	{
		CLogicPay logicPay;
		ret = logicPay.ChangePay(uid, 0, coins, "ProcessTribute");
		if(ret)
			return ret;
	}
	c = (int)(c * FCM_VALUE[fcm]);
	if(c)
	{
		switch(t)
		{
		case 0:
			dataUser.r1 += c;
			if(dataUser.r1 > dataUser.r1_max)
				dataUser.r1 = dataUser.r1_max;
			break;
		case 1:
			dataUser.r2 += c;
			if(dataUser.r2 > dataUser.r2_max)
				dataUser.r2 = dataUser.r2_max;
			break;
		case 2:
			dataUser.r3 += c;
			if(dataUser.r3 > dataUser.r3_max)
				dataUser.r3 = dataUser.r3_max;
			break;
		case 3:
			dataUser.r4 += c;
			if(dataUser.r4 > dataUser.r4_max)
				dataUser.r4 = dataUser.r4_max;
			break;
		}
	}

	ret = logicUser.SetUserLimit(uid, dataUser);
	if(ret)
		return ret;

	return R_SUCCESS;
}
int CLogicCMD::MeltEquip(unsigned uid, unsigned ud1, unsigned ud2, unsigned ud3, unsigned lvl, unsigned spirit, Json::Value &result,unsigned lasttime,unsigned seqid)
{
	if(spirit == 0)
		return R_ERR_PARAM;

	int ret;
	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	ret = logicUser.GetUserLimit(uid,dataUser);
	if(ret)
	{
		error_log(" get  user info failed,uid = %u",uid);
		return ret;
	}
	ret = checkLastSaveUID(dataUser);
	if(ret)
		return ret;

	ret = checkLastSaveTime(dataUser,lasttime,seqid);
	if(ret)
		return ret;
	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	if (spirit > dataUser.battle_spirits)
	{
		LOGIC_ERROR_RETURN_MSG("battle_spirits less than zero");
	}
	dataUser.battle_spirits -= spirit;

	Json::Value dataEquip1, dataEquip2, dataEquip3;
	CLogicEquipment loigcEquipment;
	ret = loigcEquipment.Get(uid, ud1, dataEquip1);
	if(ret)
		return ret;
	ret = loigcEquipment.Get(uid, ud2, dataEquip2);
	if(ret)
		return ret;
	ret = loigcEquipment.Get(uid, ud3, dataEquip3);
	if(ret)
		return ret;

	unsigned eqid = dataEquip1["id"].asUInt();
	unsigned ch = dataEquip1["ch"].asUInt();
	if(!IS_GENERAL_EQ_EQID(eqid) || ch >= 4
	|| eqid != dataEquip2["id"].asUInt() || eqid != dataEquip3["id"].asUInt()
	|| ch != dataEquip2["ch"].asUInt() || ch != dataEquip3["ch"].asUInt())
		return R_ERR_LOGIC;
	++ch;

	unsigned subNum = getSubNumByCh(ch);
	vector<string> keepstr;
	CDataXML *dataXML = CDataXML::GetCDataXML();
	if(!dataXML)
	{
		error_log("GetInitXML fail");
		return R_ERR_DB;
	}
	vector<EquipSub> sub;
	unsigned stoneID,gold;
	ret = dataXML->GetEquipSub(lvl,stoneID,gold,subNum,keepstr,sub);
	if(ret)
		return ret;

	ret = loigcEquipment.Del(uid, ud1);
	if(ret)
		return ret;
	ret = loigcEquipment.Del(uid, ud2);
	if(ret)
		return ret;
	ret = loigcEquipment.Del(uid, ud3);
	if(ret)
		return ret;

	Json::Value newEqDatas = Json::Value(Json::arrayValue);
	ItemAdd item(eqid, 1, "MeltEquip", ch);
	loigcEquipment.genEquip(item,newEqDatas);
	for(unsigned i=0;i<sub.size();++i)
		newEqDatas[0u]["sub"][sub[i].id] = sub[i].value;
	ret = loigcEquipment.UpdateEquipment(uid, 0, newEqDatas, result["equip"], true);
	if(ret)
		return ret;

	ret = logicUser.SetUserLimit(uid, dataUser);
	if(ret)
		return ret;

	return R_SUCCESS;
}

int CLogicCMD::VickyAcc(unsigned uid, unsigned index, Json::Value & result, unsigned lasttime, unsigned seqid)
{
	const int vicky_all = 10;
	const int vicky_money[vicky_all] = {500,1000,2000,5000,10000,50000,100000,250000,500000,1000000};
	const int vicky_bag[vicky_all] = {8901,8902,8903,8904,8905,8906,8907,8908,8909,8910};

	if(index >= vicky_all)
		return R_ERR_PARAM;
	if(Time::GetGlobalTime() < Config::GetIntValue(CONFIG_VICKY_ACC_BEGIN_TS)
	|| Time::GetGlobalTime() >= Config::GetIntValue(CONFIG_VICKY_ACC_END_TS))
		return R_ERR_LOGIC;

	int ret;
	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	ret = logicUser.GetUser(uid,dataUser);
	if(ret)
	{
		error_log(" get  user info failed,uid = %u",uid);
		return ret;
	}
	ret = checkLastSaveUID(dataUser);
	if(ret)
		return ret;

	ret = checkLastSaveTime(dataUser,lasttime,seqid);
	if(ret)
		return ret;
	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	Json::Reader reader;
	Json::Value user_flag;
	reader.parse(dataUser.user_flag,user_flag);
	if (!user_flag.isMember("chgs") || !user_flag["chgs"].isArray())
	{
		error_log("chgs error");
		DATA_ERROR_RETURN_MSG("chgs error");
	}
	unsigned size = user_flag["chgs"].size();
	unsigned chargeTotal = 0;
	for (unsigned i = 0; i < size; ++i)
	{
		unsigned ts  = user_flag["chgs"][i][0u].asUInt();
		if(ts >= Config::GetIntValue(CONFIG_VICKY_ACC_BEGIN_TS)
		&& ts <= Config::GetIntValue(CONFIG_VICKY_ACC_END_TS))
			chargeTotal += user_flag["chgs"][i][1u].asUInt();
	}
	if(chargeTotal < vicky_money[index])
		return R_ERR_LOGIC;

	Json::Value newAct;
	CLogicSecinc logicSecinc;
	ret = logicSecinc.GetSecinc(uid, NAT_VICKY_ACC, newAct);
	if (ret == R_ERR_NO_DATA)
	{
		newAct["id"] = NAT_VICKY_ACC;
		newAct["a"].resize(0);
		for(unsigned i=0;i<vicky_all;++i)
			newAct["a"].append(0);
		newAct["v"] = Config::GetIntValue(CONFIG_VICKY_ACC_VER);
	}
	else if(ret)
		return ret;
	if(Config::GetIntValue(CONFIG_VICKY_ACC_VER) != newAct["v"].asInt())
	{
		newAct["a"].resize(0);
		for(unsigned i=0;i<vicky_all;++i)
			newAct["a"].append(0);
		newAct["v"] = Config::GetIntValue(CONFIG_VICKY_ACC_VER);
	}
	if(newAct["a"][index].asInt() != 0)
		return R_ERR_LOGIC;
	newAct["a"][index] = 1;

	ret = logicSecinc.SetOneSecinc(uid, newAct);
	if(ret)
		return ret;
	result["newAct"] = newAct;

	return _useGiftBag(dataUser, vicky_bag[index], 1, result);
}

int CLogicCMD::GetXinWuFB(unsigned uid, unsigned index, unsigned pay, Json::Value & result, unsigned lasttime, unsigned seqid)
{
	if(index >= XINWU_FB)
		return R_ERR_PARAM;

	CDataXML *dataXML = CDataXML::GetCDataXML();
	if(!dataXML)
	{
		error_log("GetInitXML fail");
		return R_ERR_DB;
	}

	int ret;
	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	/*if(pay)
		ret = logicUser.GetUser(uid,dataUser);
	else*/
		ret = logicUser.GetUserLimit(uid,dataUser);
	if(ret)
	{
		error_log(" get  user info failed,uid = %u",uid);
		return ret;
	}
	ret = checkLastSaveUID(dataUser);
	if(ret)
		return ret;

	ret = checkLastSaveTime(dataUser,lasttime,seqid);
	if(ret)
		return ret;
	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	Json::Value newAct;
	CLogicSecinc logicSecinc;
	ret = logicSecinc.GetSecinc(uid, NAT_XINWU_FB, newAct);
	if(ret)
		return ret;

	unsigned count = 0;
	if(pay)
	{
		if(!newAct.isMember("b") || newAct["b"].asUInt() >= 5 || !newAct.isMember("a") || newAct["a"][index][0u].asUInt() == 0)
			return R_ERR_LOGIC;
		if(newAct["a"][index][1u].asUInt() == 0)
			return R_ERR_LOGIC;
		count = dataXML->GetXinWuReward(index, false);
		newAct["a"][index][1u] = newAct["a"][index][1u].asUInt() + 1;
		newAct["b"] = newAct["b"].asUInt() + 1;

		/*Json::Reader reader;
		Json::FastWriter writer;
		Json::Value user_flag;
		bool bsave = false;
		reader.parse(dataUser.user_flag,user_flag);

		CLogicPay logicPay;
		DataPay payData;
		ret = logicPay.ProcessOrderForBackend(uid, -1, 0, payData, "GetXinWuFB",user_flag,bsave);
		if(ret)
			return ret;
		result["coins"] = payData.coins;
		result["coins2"] = payData.cash;
		result["pointpay"].resize(0);
		result["pointpay"] = user_flag["user_pay"];
		if(bsave)
			dataUser.user_flag = writer.write(user_flag);*/
	}
	else
	{
		if(!newAct.isMember("b") || newAct["b"].asUInt() > 5 || !newAct.isMember("a") || newAct["a"][index][0u].asUInt() == 0)
			return R_ERR_LOGIC;
		if(newAct["a"][index][1u].asUInt() == 0)
		{
			if(index + 1 < XINWU_FB)
				newAct["a"][index + 1][0u] = 1;
			count = dataXML->GetXinWuReward(index, true);
		}
		else
			count = dataXML->GetXinWuReward(index, false);
		newAct["a"][index][1u] = newAct["a"][index][1u].asUInt() + 1;
	}

	ret = logicSecinc.SetOneSecinc(uid, newAct);
	if(ret)
		return ret;
	result["newAct"] = newAct;

	CLogicEquipment loigcEquipment;
	ret = loigcEquipment.AddOneItem(uid, KeepsakeUnit::produce_need_equip, count, "GetXinWuFB", result["equip"], true);
	if(ret)
		return ret;

	/*if(pay)
		ret = logicUser.SetUser(uid, dataUser);
	else*/
		ret = logicUser.SetUserLimit(uid, dataUser);
	if(ret)
		return ret;

	return R_SUCCESS;
}

int CLogicCMD::TowerStepUp(unsigned uid, unsigned bdid, unsigned equd, Json::Value & result, unsigned lasttime, unsigned seqid)
{
	int ret;
	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	ret = logicUser.GetUserLimit(uid,dataUser);
	if(ret)
	{
		error_log(" get  user info failed,uid = %u",uid);
		return ret;
	}
	ret = checkLastSaveUID(dataUser);
	if(ret)
		return ret;

	ret = checkLastSaveTime(dataUser,lasttime,seqid);
	if(ret)
		return ret;
	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	Json::Value bd;
	CLogicBuilding logicBd;
	ret = logicBd.Get(uid, bdid, 0, true, bd);
	if(ret)
		return ret;
	int l = 0, t = 0;
	Json::GetInt(bd, "l", l);
	Json::GetInt(bd, "t", t);
	if(l < 100)
		return R_ERR_LOGIC;
	l -= 99;
	switch(t)
	{
	case 8:
		t = 58;
		break;
	case 13:
		t = 59;
		break;
	case 9:
		t = 60;
		break;
	case 12:
		t = 61;
		break;
	case 42:
		t = 63;
		break;
	default:
		return R_ERR_LOGIC;
	}
	bd["l"] = l;
	bd["t"] = t;

	CLogicEquipment loigcEquipment;
	ret = loigcEquipment.UseEquipment(uid, 2020, equd, 70, "TowerStepUp");
	if(ret)
		return ret;

	ret = logicBd.Chg(uid, bdid, 0, true, bd);
	if(ret)
		return ret;
	result["bd"] = bd;

	ret = logicUser.SetUserLimit(uid, dataUser);
	if(ret)
		return ret;

	return R_SUCCESS;
}
int CLogicCMD::TowerUnlock(unsigned uid, unsigned bdid, unsigned equd, Json::Value & result, unsigned lasttime, unsigned seqid)
{
	int ret;
	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	ret = logicUser.GetUserLimit(uid,dataUser);
	if(ret)
	{
		error_log(" get  user info failed,uid = %u",uid);
		return ret;
	}
	ret = checkLastSaveUID(dataUser);
	if(ret)
		return ret;

	ret = checkLastSaveTime(dataUser,lasttime,seqid);
	if(ret)
		return ret;
	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	Json::Value bd;
	CLogicBuilding logicBd;
	ret = logicBd.Get(uid, bdid, 0, true, bd);
	if(ret)
		return ret;
	int tu = 0, t = 0;
	Json::GetInt(bd, "tu", tu);
	Json::GetInt(bd, "t", t);
	if(t != 58 && t != 59 && t != 60 && t != 61 && t != 63)
		return R_ERR_LOGIC;
	if(tu)
		return R_ERR_LOGIC;
	bd["tu"] = 1;

	CLogicEquipment loigcEquipment;
	ret = loigcEquipment.UseEquipment(uid, 2021, equd, 100, "TowerUnlock");
	if(ret)
		return ret;

	ret = logicBd.Chg(uid, bdid, 0, true, bd);
	if(ret)
		return ret;
	result["bd"] = bd;

	ret = logicUser.SetUserLimit(uid, dataUser);
	if(ret)
		return ret;

	return R_SUCCESS;
}

int CLogicCMD::UpGradeBNW(unsigned uid, Json::Value & result, unsigned lasttime, unsigned seqid)
{
	int ret;
	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	ret = logicUser.GetUser(uid,dataUser);
	if(ret)
	{
		error_log(" get  user info failed,uid = %u",uid);
		return ret;
	}
	ret = checkLastSaveUID(dataUser);
	if(ret)
		return ret;

	ret = checkLastSaveTime(dataUser,lasttime,seqid);
	if(ret)
		return ret;
	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	Json::Reader reader;
	Json::FastWriter writer;
	Json::Value tech;
	reader.parse(dataUser.user_tech,tech);
	if(!tech.isMember("bnw"))
	{
		tech["bnw"]["lv"] = 1;
		tech["bnw"]["lts"] = 0;
	}
	unsigned lv = tech["bnw"]["lv"].asUInt();
	unsigned lts = tech["bnw"]["lts"].asUInt();
	if(lts > Time::GetGlobalTime() || lv == BRAVE_NEW_WORLD_LEVEL)
		return R_ERR_LOGIC;
	BraveNewWorldConfig::City city = ConfigManager::Instance()->GetBraveNewWorldConfigCity(lv);
	if(city.need() > dataUser.type)
		return R_ERR_LOGIC;
	dataUser.type -= city.need();
	tech["bnw"]["lts"] = Time::GetGlobalTime() + city.time();
	tech["bnw"]["lv"] = lv + 1;
	dataUser.user_tech = writer.write(tech);

	RESOURCE_LOG("[bnwm][uid=%u,chg=%d,bnwm=%u]",uid,-city.need(),dataUser.type);

	ret = logicUser.SetUser(uid, dataUser);
	if(ret)
		return ret;

	result["bnw"] = tech["bnw"];
	result["bnwm"] = dataUser.type;
	return R_SUCCESS;
}

int CLogicCMD::FastUpGradeBNW(unsigned uid, Json::Value & result, unsigned lasttime, unsigned seqid)
{
	int ret;
	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	ret = logicUser.GetUser(uid,dataUser);
	if(ret)
	{
		error_log(" get  user info failed,uid = %u",uid);
		return ret;
	}
	ret = checkLastSaveUID(dataUser);
	if(ret)
		return ret;

	ret = checkLastSaveTime(dataUser,lasttime,seqid);
	if(ret)
		return ret;
	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	Json::Reader reader;
	Json::FastWriter writer;
	Json::Value tech, user_flag;
	reader.parse(dataUser.user_tech,tech);
	reader.parse(dataUser.user_flag, user_flag);
	if(!tech.isMember("bnw"))
	{
		tech["bnw"]["lv"] = 1;
		tech["bnw"]["lts"] = 0;
	}
	unsigned lts = tech["bnw"]["lts"].asUInt();
	if(lts <= Time::GetGlobalTime())
		return R_ERR_LOGIC;
	int c = (lts - Time::GetGlobalTime()) / 600 + 1;

	CLogicPay logicPay;
	DataPay dataPay;
	bool bsave;
	ret = logicPay.ProcessOrderForBackend(uid, -c, 0, dataPay, "FastUpGradeBNW", user_flag, bsave);
	if (ret)
	{
		return ret;
	}
	result["pointpay"].resize(0);
	if(bsave)
	{
		result["pointpay"] = user_flag["user_pay"];
		dataUser.user_flag = writer.write(user_flag);
	}
	result["coins"] = dataPay.coins;
	result["coins2"] = dataPay.cash;


	tech["bnw"]["lts"] = 0;
	dataUser.user_tech = writer.write(tech);

	ret = logicUser.SetUser(uid, dataUser);
	if(ret)
		return ret;

	result["bnw"] = tech["bnw"];
	return R_SUCCESS;
}

int CLogicCMD::UpGradeBNWTech(unsigned uid, unsigned job, unsigned type, Json::Value & result, unsigned lasttime, unsigned seqid)
{
	if(job >= 3 || type >= 3)
		return R_ERR_PARAM;

	int ret;
	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	ret = logicUser.GetUser(uid,dataUser);
	if(ret)
	{
		error_log(" get  user info failed,uid = %u",uid);
		return ret;
	}
	ret = checkLastSaveUID(dataUser);
	if(ret)
		return ret;

	ret = checkLastSaveTime(dataUser,lasttime,seqid);
	if(ret)
		return ret;
	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	Json::Reader reader;
	Json::FastWriter writer;
	Json::Value tech;
	reader.parse(dataUser.user_tech,tech);
	if(!tech.isMember("bnwt") || !tech["bnwt"].isArray())
	{
		tech["bnwt"].resize(0);
		for(unsigned i=0;i<3;++i)
		{
			Json::Value t;
			t["t"].resize(0);
			for(unsigned j=0;j<3;++j)
				t["t"].append(0);
			t["tn"] = 0;
			t["ts"] = 0;
			tech["bnwt"].append(t);
		}
	}
	unsigned lv = tech["bnwt"][job]["t"][type].asUInt();
	unsigned lts = tech["bnwt"][job]["ts"].asUInt();
	if(lts > Time::GetGlobalTime() || lv == 100)
		return R_ERR_LOGIC;
	BraveNewWorldConfig::Tech te = ConfigManager::Instance()->GetBraveNewWorldConfigTech(job, type, lv);
	if(te.cost() > dataUser.type)
		return R_ERR_LOGIC;
	dataUser.type -= te.cost();
	tech["bnwt"][job]["ts"] = Time::GetGlobalTime() + te.cd()*60;
	tech["bnwt"][job]["t"][type] = lv + 1;
	tech["bnwt"][job]["tn"] = type;
	dataUser.user_tech = writer.write(tech);

	RESOURCE_LOG("[bnwm][uid=%u,chg=%d,bnwm=%u]",uid,-te.cost(),dataUser.type);

	ret = logicUser.SetUser(uid, dataUser);
	if(ret)
		return ret;

	result["bnwt"] = tech["bnwt"];
	result["bnwm"] = dataUser.type;
	return R_SUCCESS;
}

int CLogicCMD::FastUpGradeBNWTech(unsigned uid, unsigned job, Json::Value & result, unsigned lasttime, unsigned seqid)
{
	if(job >= 3)
		return R_ERR_PARAM;

	int ret;
	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	ret = logicUser.GetUser(uid,dataUser);
	if(ret)
	{
		error_log(" get  user info failed,uid = %u",uid);
		return ret;
	}
	ret = checkLastSaveUID(dataUser);
	if(ret)
		return ret;

	ret = checkLastSaveTime(dataUser,lasttime,seqid);
	if(ret)
		return ret;
	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	Json::Reader reader;
	Json::FastWriter writer;
	Json::Value tech, user_flag;
	reader.parse(dataUser.user_tech,tech);
	reader.parse(dataUser.user_flag, user_flag);

	if(!tech.isMember("bnwt") || !tech["bnwt"].isArray())
		return R_ERR_LOGIC;
	unsigned lts = tech["bnwt"][job]["ts"].asUInt();
	if(lts <= Time::GetGlobalTime())
		return R_ERR_LOGIC;

	int c = (lts - Time::GetGlobalTime()) / 60 + 1;
	CLogicPay logicPay;
	DataPay dataPay;
	bool bsave;
	ret = logicPay.ProcessOrderForBackend(uid, -c, 0, dataPay, "FastUpGradeBNWTech", user_flag, bsave);
	if (ret)
	{
		return ret;
	}
	result["pointpay"].resize(0);
	if(bsave)
	{
		result["pointpay"] = user_flag["user_pay"];
		dataUser.user_flag = writer.write(user_flag);
	}
	result["coins"] = dataPay.coins;
	result["coins2"] = dataPay.cash;

	tech["bnwt"][job]["ts"] = 0;
	dataUser.user_tech = writer.write(tech);

	ret = logicUser.SetUser(uid, dataUser);
	if(ret)
		return ret;

	result["bnwt"] = tech["bnwt"];
	return R_SUCCESS;
}

int CLogicCMD::GetHequChargeReward(unsigned uid, unsigned index, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	try
	{
		AUTO_LOCK_USER(uid);

		UserWrap userWrap(uid, false);

		int ret = userWrap.CheckSession(lasttime, seqid, result);

		if (ret != R_SUCCESS)
		{
			return ret;
		}

		//todo 充值
		HeQuActivityUnit hequactivity(uid);

		hequactivity.GetChargeReward(userWrap, index, result);

		userWrap.Save();
	}
	catch (const std::exception& e)
	{
		::SetError(R_ERROR, e.what());
		return R_ERROR;
	}

	return R_SUCCESS;
}

int CLogicCMD::GetHequVIPeward(unsigned uid, unsigned vindex, unsigned subindex, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	try
	{
		AUTO_LOCK_USER(uid);

		UserWrap userWrap(uid, false);

		int ret = userWrap.CheckSession(lasttime, seqid, result);

		if (ret != R_SUCCESS)
		{
			return ret;
		}

		//todo 合区vip同庆
		HeQuActivityUnit hequactivity(uid);

		hequactivity.GetVIPCelebrate(userWrap, vindex, subindex, result);

		userWrap.Save();
	}
	catch (const std::exception& e)
	{
		::SetError(R_ERROR, e.what());
		return R_ERROR;
	}

	return R_SUCCESS;
}

int CLogicCMD::GetHequRecompenseReward(unsigned uid, unsigned index, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	try
	{
		AUTO_LOCK_USER(uid);

		UserWrap userWrap(uid, false);

		int ret = userWrap.CheckSession(lasttime, seqid, result);

		if (ret != R_SUCCESS)
		{
			return ret;
		}

		//todo 合区补偿
		HeQuActivityUnit hequactivity(uid);

		hequactivity.GetCombineZoneRecompense(userWrap, index, result);

		userWrap.Save();
	}
	catch (const std::exception& e)
	{
		::SetError(R_ERROR, e.what());
		return R_ERROR;
	}

	return R_SUCCESS;
}

int CLogicCMD::Learjyt(unsigned uid, unsigned ud, Json::Value & result, unsigned lasttime, unsigned seqid)
{
	int ret;
	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	ret = logicUser.GetUser(uid,dataUser);
	if(ret)
	{
		error_log(" get  user info failed,uid = %u",uid);
		return ret;
	}
	ret = checkLastSaveUID(dataUser);
	if(ret)
		return ret;

	ret = checkLastSaveTime(dataUser,lasttime,seqid);
	if(ret)
		return ret;
	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	Json::Reader reader;
	Json::FastWriter writer;
	Json::Value tech;
	reader.parse(dataUser.user_tech,tech);
	unsigned jyt = 0;
	Json::GetUInt(tech, "jyt", jyt);
	if(jyt)
		return R_ERR_LOGIC;

	CLogicEquipment loigcEquipment;
	ret = loigcEquipment.UseEquipment(uid, 2022, ud, 100, "Learjyt");
	if(ret)
		return ret;

	tech["jyt"] = 1;
	dataUser.user_tech = writer.write(tech);

	ret = logicUser.SetUser(uid, dataUser);
	if(ret)
		return ret;

	return R_SUCCESS;
}

int CLogicCMD::LearnJM(unsigned uid, unsigned ud, unsigned id, Json::Value & result, unsigned lasttime, unsigned seqid)
{
	if(id == 0 || id >= e_JM_max)
		return R_ERR_PARAM;

	int ret;
	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	ret = logicUser.GetUser(uid,dataUser);
	if(ret)
	{
		error_log(" get  user info failed,uid = %u",uid);
		return ret;
	}
	ret = checkLastSaveUID(dataUser);
	if(ret)
		return ret;

	ret = checkLastSaveTime(dataUser,lasttime,seqid);
	if(ret)
		return ret;
	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	Json::Reader reader;
	Json::FastWriter writer;
	Json::Value tech;
	reader.parse(dataUser.user_tech,tech);
	if(!tech.isMember("jm") || !tech["jm"].isArray())
	{
		tech["jm"].resize(0);
		for(int i=1;i<e_JM_max;++i)
		{
			Json::Value t;
			t["id"] = i;
			t["lv"] = 0;
			t["ts"] = 0;
			tech["jm"].append(t);
		}
	}
	if(tech["jm"].size()+1 < e_JM_max)
	{
		for(unsigned i=tech["jm"].size()+1;i<e_JM_max;++i)
		{
			Json::Value t;
			t["id"] = i;
			t["lv"] = 0;
			t["ts"] = 0;
			tech["jm"].append(t);
		}
	}
	unsigned lv = tech["jm"][id-1]["lv"].asInt();
	++lv;
	unsigned count = 0;
	switch(lv)
	{
	case 1:
		count = 100;
		break;
	case 2:
		count = 200;
		break;
	case 3:
		count = 500;
		break;
	default:
		return R_ERR_LOGIC;
	}
	tech["jm"][id-1]["lv"] = lv;

	CLogicEquipment loigcEquipment;
	ret = loigcEquipment.UseEquipment(uid, 2060, ud, count, "LearnJM");
	if(ret)
		return ret;

	dataUser.user_tech = writer.write(tech);

	ret = logicUser.SetUser(uid, dataUser);
	if(ret)
		return ret;

	result["jm"] = tech["jm"];

	return R_SUCCESS;
}

int CLogicCMD::LoadScrollActivity(unsigned uid, Json::Value & result, unsigned lasttime, unsigned seqid)
{
	try
	{
		AUTO_LOCK_USER(uid);
		UserWrap userWrap(uid, true);

		int ret = userWrap.CheckSession(lasttime, seqid, result);

		if (ret != R_SUCCESS)
		{
			return ret;
		}

		//todo 古卷专项活动
		ScrollActivityUnit scrollactivity(uid);
		scrollactivity.LoadScrollActivity(result);

		userWrap.Save();
	}
	catch (const std::exception& e)
	{
		::SetError(R_ERROR, e.what());
		return R_ERROR;
	}

	return 0;
}

int CLogicCMD::CompleteAffair(unsigned uid, unsigned type, Json::Value & result, unsigned lasttime, unsigned seqid)
{
	try
	{
		AUTO_LOCK_USER(uid);
		UserWrap userWrap(uid, true);

		int ret = userWrap.CheckSession(lasttime, seqid, result);

		if (ret != R_SUCCESS)
		{
			return ret;
		}

		//todo 古卷专项活动
		ScrollActivityUnit scrollactivity(uid);
		scrollactivity.CompleteAffair(type, result);

		userWrap.Save();
	}
	catch (const std::exception& e)
	{
		::SetError(R_ERROR, e.what());
		return R_ERROR;
	}

	return 0;
}

int CLogicCMD::GetActiveReward(unsigned uid, unsigned index, Json::Value & result, unsigned lasttime, unsigned seqid)
{
	try
	{
		AUTO_LOCK_USER(uid);
		UserWrap userWrap(uid, true);

		int ret = userWrap.CheckSession(lasttime, seqid, result);

		if (ret != R_SUCCESS)
		{
			return ret;
		}

		//todo 古卷专项活动
		ScrollActivityUnit scrollactivity(uid);
		scrollactivity.GetActiveReward(index, result);

		userWrap.Save();
	}
	catch (const std::exception& e)
	{
		::SetError(R_ERROR, e.what());
		return R_ERROR;
	}

	return 0;
}

int CLogicCMD::OpenKingTreasure(unsigned uid, unsigned equd, Json::Value & result, unsigned lasttime, unsigned seqid)
{
	try
	{
		AUTO_LOCK_USER(uid);
		UserWrap userWrap(uid, true);

		int ret = userWrap.CheckSession(lasttime, seqid, result);

		if (ret != R_SUCCESS)
		{
			return ret;
		}

		//todo 开宝箱
		KingTreasureActivityUnit kingtreasure(uid);
		kingtreasure.OpenTreasureBox(equd, result);

		userWrap.Save();
	}
	catch (const std::exception& e)
	{
		::SetError(R_ERROR, e.what());
		return R_ERROR;
	}

	return 0;
}

int CLogicCMD::ReceiveKingTreasure(unsigned uid, Json::Value & result, unsigned lasttime, unsigned seqid)
{
	try
	{
		AUTO_LOCK_USER(uid);
		UserWrap userWrap(uid, true);

		int ret = userWrap.CheckSession(lasttime, seqid, result);

		if (ret != R_SUCCESS)
		{
			return ret;
		}

		//todo 领取奖励
		KingTreasureActivityUnit kingtreasure(uid);
		kingtreasure.ReceiveReward(result);

		userWrap.Save();
	}
	catch (const std::exception& e)
	{
		::SetError(R_ERROR, e.what());
		return R_ERROR;
	}

	return 0;
}

int CLogicCMD::RecycleKingTreasure(unsigned uid, Json::Value & result, unsigned lasttime, unsigned seqid)
{
	try
	{
		AUTO_LOCK_USER(uid);
		UserWrap userWrap(uid, true);

		int ret = userWrap.CheckSession(lasttime, seqid, result);

		if (ret != R_SUCCESS)
		{
			return ret;
		}

		//todo 宝箱回收
		KingTreasureActivityUnit kingtreasure(uid);
		kingtreasure.RecycleReward(result);

		userWrap.Save();
	}
	catch (const std::exception& e)
	{
		::SetError(R_ERROR, e.what());
		return R_ERROR;
	}

	return 0;
}

int CLogicCMD::ReceiveScrollFeedback(unsigned uid, unsigned index, Json::Value & result, unsigned lasttime, unsigned seqid)
{
	try
	{
		AUTO_LOCK_USER(uid);
		UserWrap userWrap(uid, false);

		int ret = userWrap.CheckSession(lasttime, seqid, result);

		if (ret != R_SUCCESS)
		{
			return ret;
		}

		//todo 古卷回馈活动
		ScrollFeedbackActivityUnit scrollfeedback(uid);
		scrollfeedback.ReceiveFeedback(index, userWrap, result);

		userWrap.Save();
	}
	catch (const std::exception& e)
	{
		::SetError(R_ERROR, e.what());
		return R_ERROR;
	}

	return 0;
}

int CLogicCMD::ReceiveSevenDayAwaken(unsigned uid, unsigned type, Json::Value & result, unsigned lasttime, unsigned seqid)
{
	try
	{
		AUTO_LOCK_USER(uid);
		UserWrap userWrap(uid, false);

		int ret = userWrap.CheckSession(lasttime, seqid, result);

		if (ret != R_SUCCESS)
		{
			return ret;
		}

		//todo 七日觉醒活动
		SevenDaysAwakenActivityUnit sevenawaken(uid);
		sevenawaken.ReceiveGift(type, userWrap, result);

		userWrap.Save();
	}
	catch (const std::exception& e)
	{
		::SetError(R_ERROR, e.what());
		return R_ERROR;
	}

	return 0;
}

int CLogicCMD::YingLingNormal(unsigned uid, Json::Value &data, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	unsigned type = 0;
	Json::GetUInt(data, "type", type);

	int ret = 0;
	AUTO_LOCK_USER(uid);
	UserWrap userWrap(uid, false);
	ret = userWrap.CheckSession(lasttime, seqid, result);
	if(ret)
		return ret;

	Json::Value tech;
	userWrap.GetUserTech(tech);
	if(!tech.isMember("ylna") || !tech["ylna"].isObject())
	{
		tech.removeMember("ylna");
		tech["ylna"]["nts"] = Time::GetGlobalTime();
		tech["ylna"]["nt"] = 0;
		tech["ylna"]["ats"] = 0;
	}
	if(CTime::IsDiffDay(tech["ylna"]["nts"].asUInt(), Time::GetGlobalTime()))
	{
		tech["ylna"]["nts"] = Time::GetGlobalTime();
		tech["ylna"]["nt"] = 0;
	}

	if(type == 0)
	{
		if(tech["ylna"]["nt"].asUInt() >= ConfigManager::Instance()->m_yingling.m_config.normaltime())
			return R_ERR_LOGIC;
		tech["ylna"]["nt"] = tech["ylna"]["nt"].asUInt() + 1;
	}
	else
	{
		if(Time::GetGlobalTime() < tech["ylna"]["ats"].asUInt() || Time::GetGlobalTime() - tech["ylna"]["ats"].asUInt() < ConfigManager::Instance()->m_yingling.m_config.advancetime())
			return R_ERR_LOGIC;
		tech["ylna"]["ats"] = Time::GetGlobalTime();
	}

	pair<unsigned, unsigned> r = ConfigManager::Instance()->GetYingLingRandom(type);
	ret = CLogicEquipment().AddOneItem(uid, r.first, r.second, "YingLingNormal", result["equip"]);
	if(ret)
		return ret;
	result["ylna"] = tech["ylna"];

	userWrap.SetUserTech(tech);
	userWrap.Save();

	return R_SUCCESS;
}
int CLogicCMD::YingLingAdvance(unsigned uid, Json::Value &data, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	unsigned ud = 0;
	Json::GetUInt(data, "ud", ud);
	unsigned count = 0;
	Json::GetUInt(data, "count", count);

	int ret = 0;
	AUTO_LOCK_USER(uid);
	UserWrap userWrap(uid, true);
	ret = userWrap.CheckSession(lasttime, seqid, result);
	if(ret)
		return ret;

	CLogicEquipment logicEquip;
	ret = logicEquip.UseEquipment(uid, ConfigManager::Instance()->m_yingling.m_config.advancecost(), ud, count, "YingLingAdvance");
	if(ret)
		return ret;

	vector<ItemAdd> equip_items;
	for(int i=0;i<count;i++)
	{
		pair<unsigned, unsigned> r = ConfigManager::Instance()->GetYingLingRandom(1);
		ItemAdd eqip;
		eqip.eqid = r.first;
		eqip.count = r.second;
		eqip.reason = "YingLingAdvance";
		equip_items.push_back(eqip);
	}
	ret = logicEquip.AddItems(uid, equip_items, result["equip"]);
	if(ret)
		return ret;

	userWrap.Save();
	return R_SUCCESS;
}
int CLogicCMD::YingLingExp(unsigned uid, Json::Value &data, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	unsigned ud = 0;
	Json::GetUInt(data, "ud", ud);
	unsigned id = 0;
	Json::GetUInt(data, "id", id);
	unsigned ylud = 0;
	Json::GetUInt(data, "ylud", ylud);

	int ret = 0;
	AUTO_LOCK_USER(uid);
	UserWrap userWrap(uid, true);
	ret = userWrap.CheckSession(lasttime, seqid, result);
	if(ret)
		return ret;

	CLogicEquipment logicEquip;
	Json::Value eq;
	ret = logicEquip.Get(uid, ylud, eq);
	if(ret)
		return ret;
	unsigned tts = 0, yexp = 0;
	Json::GetUInt(eq, "tts", tts);
	Json::GetUInt(eq, "yexp", yexp);
	if(tts > Time::GetGlobalTime())
		return R_ERR_LOGIC;

	const YingLing::YingLingExp& cfg = ConfigManager::Instance()->GetYingLingExp(id);
	userWrap.ChangeResource(-cfg.r1(), -cfg.r2(), -cfg.r3(), -cfg.r4(), "YingLingExp", result);
	ret = logicEquip.UseEquipment(uid, id, ud, 1, "YingLingExp");
	if(ret)
		return ret;

	eq["tts"] = Time::GetGlobalTime() + cfg.time();
	eq["yexp"] = yexp + cfg.exp();
	ret = logicEquip.Chg(uid, ylud, eq);
	if(ret)
		return ret;
	result["equip"] = eq;

	userWrap.Save();
	return R_SUCCESS;
}
int CLogicCMD::YingLingStar(unsigned uid, Json::Value &data, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	unsigned ud = 0;
	Json::GetUInt(data, "ud", ud);
	unsigned ylud = 0;
	Json::GetUInt(data, "ylud", ylud);

	int ret = 0;
	AUTO_LOCK_USER(uid);
	UserWrap userWrap(uid, true);
	ret = userWrap.CheckSession(lasttime, seqid, result);
	if(ret)
		return ret;

	CLogicEquipment logicEquip;
	Json::Value eq;
	ret = logicEquip.Get(uid, ylud, eq);
	if(ret)
		return ret;
	unsigned star = 0;
	Json::GetUInt(eq, "star", star);

	const YingLing::YingLingStar& cfg = ConfigManager::Instance()->GetYingLingStar(eq["id"].asUInt());
	ret = logicEquip.UseEquipment(uid, cfg.sid(), ud, cfg.cost(star), "YingLingStar");
	if(ret)
		return ret;

	eq["star"] = star + 1;
	ret = logicEquip.Chg(uid, ylud, eq);
	if(ret)
		return ret;
	result["equip"] = eq;

	userWrap.Save();
	return R_SUCCESS;
}

int CLogicCMD::UpgradeBuilding(unsigned uid, unsigned id, bool tv, string bq, unsigned fcm, Json::Value &result, unsigned lasttime,unsigned seqid)
{
	const int vdt[10] = {6,7,8,10,11,12,18,18,18,19};

	int ret = 0;
	CDataXML *dataXML = CDataXML::GetCDataXML();
	if(!dataXML)
	{
		error_log("GetInitXML fail");
		return R_ERR_DB;
	}

	AUTO_LOCK_USER(uid);
	UserWrap userWrap(uid, false);
	ret = userWrap.CheckSession(lasttime, seqid, result);
	if(ret)
		return ret;

	CLogicBuilding lb;
	Json::Value b;
	ret = lb.Get(uid, id, 0, true, b);
	if(ret)
		return ret;

	unsigned t = 0, cU = 0, upts = 0, l = 1;
	Json::GetUInt(b, "t", t);
	Json::GetUInt(b, "cU", cU);
	Json::GetUInt(b, "upts", upts);
	Json::GetUInt(b, "l", l);

	unsigned now = Time::GetGlobalTime();
	if(upts > now)
		upts = now;
	if(cU && now - upts >= cU)
	{
		cU = 0;
		b.removeMember("cU");
		++l;
		b["l"] = l;
	}

	if(t == 62 || !t || cU || l >= 150)
	{
		error_log("[uid=%u,t=%u, cU=%u, l=%u]", uid, t, cU, l);
		LOGIC_ERROR_RETURN_MSG("t_cU_l_error");
	}

	++l;
	XMLBuildingItem c;
	ret = dataXML->GetBuilding(t, l, c);
	if(ret)
		return ret;

	userWrap.ChangeResource(-c.cost[0], -c.cost[1], -c.cost[2], -c.cost[3], "UpgradeBuilding", result);
	int e = CLogicArchive().getResCostAddExp(userWrap.GetUserLevel(), c.cost[0], c.cost[1], c.cost[2], c.cost[3]);
	e = (int)(e * FCM_VALUE[fcm]);
	if(e)
		userWrap.AddExp(e, "UpgradeBuilding", result);

	int v = userWrap.VipLevel();
	if(tv)
		v = max(3, v);
	int vt = v ? vdt[v-1]*60 : 0;
	int time = c.time - vt;

	Json::Value buildq;
	userWrap.GetUserBuildQ(buildq);
	b["upts"] = now;
	if(time > 0)
	{
		b["cU"] = time;
		if(vt)
			b["vsp"] = 1;

		if(!bq.empty() && buildq.isMember(bq))
		{
			buildq[bq]["i"]["id"] = id;
			buildq[bq]["i"]["bt"] = t;
			buildq[bq]["i"]["ot"] = 1;
			userWrap.SetUserBuildQ(buildq);
		}
	}
	else
	{
		b["l"] = l;
		BUILDING_LEVEL_LOG("uid=%u,l=%u,id=%u",uid,l,t);
		if(t == 1 && l >= ALL_SERVER_MAP_MIN_LEVEL && OpenPlatform::IsLY_ALL_Platform())
		{
			CLogicAllServerMap logicAllServerMap;
			logicAllServerMap.Set(uid, l);
		}
	}
	b.removeMember("hl");
	b.removeMember("cB");

	ret = lb.Chg(uid, id, 0, true, b);
	if(ret)
		return ret;

	result["build"] = b;
	result["buildQ"] = buildq;

	userWrap.Save();
	return R_SUCCESS;
}
int CLogicCMD::FastUpgradeBuilding(unsigned uid, unsigned id, unsigned type, unsigned ud, unsigned count, string bq, unsigned help, Json::Value &result, unsigned lasttime,unsigned seqid)
{
	const unsigned eqid[3] = {4022, 4023, 4024};
	const int et[3] = {15, 60, 180};

	if(type < 1 || type > 4)
		return R_ERR_PARAM;

	int ret = 0;
	CDataXML *dataXML = CDataXML::GetCDataXML();
	if(!dataXML)
	{
		error_log("GetInitXML fail");
		return R_ERR_DB;
	}

	AUTO_LOCK_USER(uid);
	UserWrap userWrap(uid, false);
	ret = userWrap.CheckSession(lasttime, seqid, result);
	if(ret)
		return ret;

	CLogicBuilding lb;
	Json::Value b;
	ret = lb.Get(uid, id, 0, true, b);
	if(ret)
		return ret;

	unsigned cU = 0, upts = 0, l = 1, t = 0;
	Json::GetUInt(b, "cU", cU);
	Json::GetUInt(b, "upts", upts);
	Json::GetUInt(b, "l", l);
	Json::GetUInt(b, "t", t);

	if(cU == 0 || l >= 150)
	{
		error_log("[uid=%u,t=%u, cU=%u, l=%u]", uid, t, cU, l);
		LOGIC_ERROR_RETURN_MSG("t_cU_l_error");
	}

	unsigned now = Time::GetGlobalTime();
	if(upts > now)
		upts = now;
	if(now - upts < cU)
	{
		cU = cU - (now - upts);
		if(type == 4)
		{
			if(!b.isMember("hl"))
				b["hl"][0u] = help;
			else if(b["hl"].size() < 5)
				b["hl"].append(help);
			else
				return R_ERR_LOGIC;
			cU = unsigned(double(0.95)*double(cU));
		}
		else
		{
			ret = CLogicEquipment().UseEquipment(uid, eqid[type-1], ud, count, "FastUpgradeBuilding");
			if(ret)
				return ret;
			cU = max(0, int(cU)-et[type-1]*60*int(count));
		}
	}
	else
		cU = 0;

	Json::Value buildq;
	userWrap.GetUserBuildQ(buildq);
	b["upts"] = now;
	if(cU)
		b["cU"] = cU;
	else
	{
		++l;
		b["l"] = l;
		b.removeMember("cU");
		b.removeMember("hl");
		b.removeMember("cB");
		BUILDING_LEVEL_LOG("uid=%u,l=%u,id=%u",uid,l,t);
		if(t == 1 && l >= ALL_SERVER_MAP_MIN_LEVEL && OpenPlatform::IsLY_ALL_Platform())
		{
			CLogicAllServerMap logicAllServerMap;
			logicAllServerMap.Set(uid, l);
		}
		if(!bq.empty() && buildq.isMember(bq))
		{
			buildq[bq].removeMember("i");
			userWrap.SetUserBuildQ(buildq);
		}
	}

	ret = lb.Chg(uid, id, 0, true, b);
	if(ret)
		return ret;

	result["build"] = b;
	result["buildQ"] = buildq;

	userWrap.Save();
	return R_SUCCESS;
}
int CLogicCMD::GMUpgradeBuilding(unsigned uid, Json::Value& data, Json::Value &result, unsigned lasttime,unsigned seqid)
{
	if(!data.isMember("build") || !data["build"].isArray() || data["build"].size() == 0)
		return R_ERR_PARAM;

	int ret = 0;
	AUTO_LOCK_USER(uid);
	UserWrap userWrap(uid, false);
	ret = userWrap.CheckSession(lasttime, seqid, result);
	if(ret)
		return ret;

	string openid, openkey;
	ret = CLogicUserBasic().GetOpenKey(uid, openid, openkey);
	if(ret)
		return ret;
	unsigned gmFlag = gm_none;
	ret = CLogicAdmin().CheckGM(openid, gmFlag);
	if(ret)
		return ret;
	if(gmFlag != gm_th)
		return R_ERR_LOGIC;

	result["build"].resize(0);
	CLogicBuilding lb;
	for(unsigned i=0;i<data["build"].size();++i)
	{
		ret = lb.Chg(uid, data["build"][i]["id"].asUInt(), 0, true, data["build"][i]);
		if(ret)
			return ret;
		result["build"].append(data["build"][i]);
	}

	if(data.isMember("buildq") && data["buildq"].isObject())
		userWrap.SetUserBuildQ(data["buildq"]);

	userWrap.Save();
	return R_SUCCESS;
}

int CLogicCMD::GMAddExp(unsigned uid, Json::Value &result, unsigned lasttime,unsigned seqid)
{
	int ret = 0;
	AUTO_LOCK_USER(uid);
	UserWrap userWrap(uid, true);
	ret = userWrap.CheckSession(lasttime, seqid, result);
	if(ret)
		return ret;

	if(userWrap.GetUserLevel() >= 120)
		return R_ERR_PARAM;

	string openid, openkey;
	ret = CLogicUserBasic().GetOpenKey(uid, openid, openkey);
	if(ret)
		return ret;
	unsigned gmFlag = gm_none;
	ret = CLogicAdmin().CheckGM(openid, gmFlag);
	if(ret)
		return ret;
	if(gmFlag != gm_th)
		return R_ERR_LOGIC;

	userWrap.AddExp((CLogicArchive().getExp(userWrap.GetUserLevel()) - userWrap.GetUserExp())/5, "GM", result);

	userWrap.Save();
	return R_SUCCESS;
}
int CLogicCMD::ExpMaxAdd(unsigned uid, unsigned type, Json::Value &result, unsigned lasttime,unsigned seqid)
{
	const char* na[3] = {"bMaxLv", "sMaxLv", "hAddLv"};

	if(type > 3 || type < 1)
		return R_ERR_PARAM;

	int ret = 0;
	AUTO_LOCK_USER(uid);
	UserWrap userWrap(uid, false);
	ret = userWrap.CheckSession(lasttime, seqid, result);
	if(ret)
		return ret;

	Json::Value tech;
	userWrap.GetUserTech(tech);
	int k = 0, v = 0;
	const int *q;
	Json::GetInt(tech, na[type-1], k);
	switch(type)
	{
	case 1:
		if(k >= 150)
			return R_ERR_LOGIC;
		if(k < 120)
			k = 120;
		v = k - 120;
		q = bMaxLv_exp;
		break;
	case 2:
		if(k >= 150)
			return R_ERR_LOGIC;
		if(k < 120)
			k = 120;
		v = k - 120;
		q = sMaxLv_exp;
		break;
	case 3:
		if(k >= 30)
			return R_ERR_LOGIC;
		v = k;
		q = hAddLv_exp;
		break;
	default:
		return R_ERR_PARAM;
	}

	userWrap.AddExp(-q[v], "ExpMaxAdd", result);
	if(userWrap.GetUserLevel() < 120)
		return R_ERR_LOGIC;

	result[na[type-1]] = tech[na[type-1]] = k + 1;

	userWrap.SetUserTech(tech);
	userWrap.Save();
	return R_SUCCESS;
}

int CLogicCMD::MeltOldSoulStone(unsigned uid, Json::Value &data, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	if(!data.isMember("ud") || !data["ud"].isArray() || data["ud"].size() == 0)
		return R_ERR_PARAM;
	if(!data.isMember("id") || !data["id"].isArray() || data["id"].size() == 0)
		return R_ERR_PARAM;
	if(data["ud"].size() != data["id"].size())
		return R_ERR_PARAM;

	int ret = 0;
	AUTO_LOCK_USER(uid);
	UserWrap userWrap(uid, false);
	ret = userWrap.CheckSession(lasttime, seqid, result);
	if(ret)
		return ret;

	Json::Value tech;
	userWrap.GetUserTech(tech);
	if(!tech.isMember("nsa") || !tech["nsa"].isObject())
	{
		tech.removeMember("nsa");
		tech["nsa"]["ns"] = 0;
		tech["nsa"]["ts"] = Time::GetGlobalTime();
		tech["nsa"]["nt"] = 0;
	}

	unsigned ns = 0;
	CLogicEquipment logicEquip;
	for(unsigned i=0;i<data["ud"].size();++i)
	{
		unsigned id = data["id"][i].asUInt();
		unsigned ud = data["ud"][i].asUInt();
		ns += ConfigManager::Instance()->GetOldSoulStoneA(id);
		ret = logicEquip.UseEquipment(uid, id, ud, 1, "MeltOldSoulStone");
		if(ret)
			return ret;
	}
	tech["nsa"]["ns"] = tech["nsa"]["ns"].asUInt() + ns;
	result["nsa"] = tech["nsa"];

	userWrap.SetUserTech(tech);
	userWrap.Save();

	RESOURCE_LOG("[ns][uid=%u,chg=%d,ns=%u]",uid,ns,tech["nsa"]["ns"].asUInt());
	return R_SUCCESS;
}
int CLogicCMD::SynNewSoulStone(unsigned uid, Json::Value &data, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	unsigned type = 0;
	if(!Json::GetUInt(data, "type", type) || type >= NEW_STONE_NUM)
		return R_ERR_PARAM;

	int ret = 0;
	AUTO_LOCK_USER(uid);
	UserWrap userWrap(uid, false);
	ret = userWrap.CheckSession(lasttime, seqid, result);
	if(ret)
		return ret;

	Json::Value tech;
	userWrap.GetUserTech(tech);
	if(!tech.isMember("nsa") || !tech["nsa"].isObject())
	{
		tech.removeMember("nsa");
		tech["nsa"]["ns"] = 0;
		tech["nsa"]["ts"] = Time::GetGlobalTime();
		tech["nsa"]["nt"] = 0;
	}
	if(CTime::IsDiffDay(tech["nsa"]["ts"].asUInt(), Time::GetGlobalTime()))
	{
		tech["nsa"]["ts"] = Time::GetGlobalTime();
		tech["nsa"]["nt"] = 0;
	}
	if(tech["nsa"]["nt"].asUInt() >= NEW_STONE_NUM || tech["nsa"]["ns"].asUInt() < ConfigManager::Instance()->m_newsoulstone.m_config.newstone3(type).a())
		return R_ERR_LOGIC;

	tech["nsa"]["nt"] = tech["nsa"]["nt"].asUInt() + 1;
	tech["nsa"]["ns"] = tech["nsa"]["ns"].asUInt() - ConfigManager::Instance()->m_newsoulstone.m_config.newstone3(type).a();
	ret = CLogicEquipment().AddOneItem(uid, ConfigManager::Instance()->GetNewSoulStone(type), 1, "SynNewSoulStone", result["equip"], true);
	if(ret)
		return ret;
	result["nsa"] = tech["nsa"];

	userWrap.SetUserTech(tech);
	userWrap.Save();

	RESOURCE_LOG("[ns][uid=%u,chg=%d,ns=%u]",uid,-ConfigManager::Instance()->m_newsoulstone.m_config.newstone3(type).a(),tech["nsa"]["ns"].asUInt());
	return R_SUCCESS;
}
int CLogicCMD::SynNewSoulStoneUp(unsigned uid, Json::Value &data, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	if(!data.isMember("ud") || !data["ud"].isArray() || data["ud"].size() == 0)
		return R_ERR_PARAM;
	unsigned id = 0;
	Json::GetUInt(data, "id", id);
	if(!IS_NEW_SOULSTONE_EQID(id) || id % 10 == 0)
		return R_ERR_PARAM;
	unsigned s = data["ud"].size();
	if(s % 4 != 0)
		return R_ERR_PARAM;

	int ret = 0;
	AUTO_LOCK_USER(uid);
	UserWrap userWrap(uid, true);
	ret = userWrap.CheckSession(lasttime, seqid, result);
	if(ret)
		return ret;

	CLogicEquipment logicEquip;
	for(unsigned i=0;i<s;++i)
	{
		unsigned ud = data["ud"][i].asUInt();
		ret = logicEquip.UseEquipment(uid, id, ud, 1, "SynNewSoulStoneUp");
		if(ret)
			return ret;
	}
	ret = logicEquip.AddOneItem(uid, id+1, s/4, "SynNewSoulStoneUp", result["equip"], true);
	if(ret)
		return ret;

	userWrap.Save();
	return R_SUCCESS;
}

int CLogicCMD::HeroExtraStone(unsigned uid, unsigned heroud, unsigned equd, unsigned index, Json::Value &result, unsigned lasttime,unsigned seqid)
{
	if(index >= 10)
		return R_ERR_PARAM;

	int ret = 0;
	AUTO_LOCK_USER(uid);
	UserWrap userWrap(uid, true);
	ret = userWrap.CheckSession(lasttime, seqid, result);
	if(ret)
		return ret;

	Json::Value hero;
	CLogicHero logicHero;
	ret = logicHero.Get(uid, heroud, hero);
	if(ret)
		return ret;

	unsigned exs = 0;
	Json::GetUInt(hero, "exs", exs);
	if(exs & (0x0001 << index))
		return R_ERR_LOGIC;

	CLogicEquipment logicEquipment;
	ret = logicEquipment.UseEquipment(uid, 1991, equd, 1000, "HeroExtraStone");
	if(ret)
		return ret;

	exs |= (0x0001 << index);
	hero["exs"] = exs;
	ret = logicHero.Chg(uid, heroud, hero);
	if(ret)
		return ret;
	result["exs"] = exs;

	userWrap.Save();
	return R_SUCCESS;
}
