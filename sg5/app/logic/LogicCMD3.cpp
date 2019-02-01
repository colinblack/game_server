/*
 * LogicCMD3.cpp
 *
 *  Created on: 2016-11-15
 *      Author: Ralf
 */



#include "LogicCMD.h"
#include "LogicUnitWrap.h"
#include "LogicCmdUnits.h"
#include <math.h>
#include <algorithm>
using std::min;

int CLogicCMD::ChangeName(unsigned uid, string& name, string& openid, string& figure, Json::Value &result, unsigned lasttime, unsigned seqid)
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

	CLogicUserBasic logicUserBasic;
	DataUserBasic dataUserBasic;
	CDataUserBasic dbUserBasic;
	CDataName dbName;
	string eopenid;

	String::Trim(name);
	if(name.empty() || !StringFilter::Check(name))
	{
		result["result"] = "change_name_fobbid";
		goto END_CHANGE_NAME;
	}
	unsigned euid;
	ret = dbName.GetName(name, eopenid, euid);
	if(ret == 0)
	{
		result["result"] = "change_name_exist";
		goto END_CHANGE_NAME;
	}
	else if(ret != R_ERR_NO_DATA)
		return ret;

	result["result"] = "ok";
	ret = logicUserBasic.GetUserBasicLimitWithoutPlatform(uid,dataUserBasic);
	if(ret)
		return ret;

	if(!dataUserBasic.name.empty())
	{
		ret = dbName.DelName(dataUserBasic.name);
		if(ret != 0 && ret != R_ERR_NO_DATA)
			return ret;
	}

	dataUserBasic.name = name;
	dataUserBasic.figure_url = figure;
	ret = dbUserBasic.SetUserBasicLimit(uid,PT_TEST,dataUserBasic);
	if(ret)
		return ret;

	ret = dbName.AddName(name, openid, uid);
	if(ret)
		return ret;

END_CHANGE_NAME:
	ret = logicUser.SetUserLimit(uid, dataUser);
	if(ret)
		return ret;

	return R_SUCCESS;
}

int CLogicCMD::ChangeNameAfterFirst(unsigned uid, string& name, unsigned equd, string& openid, string& figure,  Json::Value &result, unsigned lasttime, unsigned seqid)
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

	CLogicUserBasic logicUserBasic;
	DataUserBasic dataUserBasic;
	CDataUserBasic dbUserBasic;
	CDataName dbName;
	string eopenid;
	String::Trim(name);
	if(name.empty() || !StringFilter::Check(name))
	{
		result["result"] = "change_name_fobbid";
		goto END_CHANGE_NAME_AFTER_FIRST;
	}
	unsigned euid;
	ret = dbName.GetName(name, eopenid, euid);
	if(ret == 0)
	{
		result["result"] = "change_name_exist";
		goto END_CHANGE_NAME_AFTER_FIRST;
	}
	else if(ret != R_ERR_NO_DATA)
		return ret;
	result["result"] = "ok";

	ret = logicUserBasic.GetUserBasicLimitWithoutPlatform(uid,dataUserBasic);
	if(ret)
		return ret;
	if(!dataUserBasic.name.empty())
	{
		ret = dbName.DelName(dataUserBasic.name);
		if(ret != 0 && ret != R_ERR_NO_DATA)
			return ret;
	}

	//core process
	CLogicEquipment equipment;
	ret = equipment.UseEquipment(uid, CHANGE_NAME_CARD_ID, equd, 1, "ChangeNameAfterFirst");
	if(ret)
		return ret;
	dataUserBasic.name = name;
	dataUserBasic.figure_url = figure;
	ret = dbUserBasic.SetUserBasicLimit(uid,PT_TEST,dataUserBasic);
	if(ret)
		return ret;

	ret = dbName.AddName(name, openid, uid);
	if(ret)
		return ret;

END_CHANGE_NAME_AFTER_FIRST:
	ret = logicUser.SetUserLimit(uid, dataUser);
	if(ret)
		return ret;

	return R_SUCCESS;
}

int CLogicCMD::SJ4399(unsigned uid, string& code, string& openid, Json::Value &result, unsigned lasttime, unsigned seqid)
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

	CLogicPromotionMapping logicPromotionMapping;
	DataPromotionMapping dataPromotionMapping;
	CLogicEquipment logicEquipment;

	string ecode = OpenPlatform::GetPlatform()->GetConfig(CONFIG_4399_OTHER_KEY)
			+ OpenPlatform::GetPlatform()->GetConfig(CONFIG_4399_GAME_NAME)
			+ "S" + CTrans::ITOS(Config::GetZoneByUID(uid)) + openid + "sj";
	string mcode = Crypt::Md5Encode(ecode);
	if(mcode != code)
	{
		result["result"] = "4399_code_error";
		goto END_SJ4399;
	}
	dataPromotionMapping.uid = uid;
	dataPromotionMapping.useflag = 0;
	ret = logicPromotionMapping.GetPromotionMapping(dataPromotionMapping);
	if(ret != R_SUCCESS && ret != R_ERR_NO_DATA)
		return ret;
	if(ret == R_SUCCESS)
	{
		if(dataPromotionMapping.useflag & SJ_4399_EXCHANGE)
		{
			result["result"] = "4399_code_exist";
			goto END_SJ4399;
		}
		dataPromotionMapping.useflag |= SJ_4399_EXCHANGE;
		dataPromotionMapping.usetime = Time::GetGlobalTime();
		ret = logicPromotionMapping.SetPromotionMapping(dataPromotionMapping);
		if(ret)
			return ret;
	}
	else
	{
		dataPromotionMapping.useflag |= SJ_4399_EXCHANGE;
		dataPromotionMapping.usetime = Time::GetGlobalTime();
		dataPromotionMapping.pid = 0;
		ret = logicPromotionMapping.AddPromotionMapping(dataPromotionMapping);
		if(ret)
			return ret;
	}

	ret = logicEquipment.AddOneItem(uid, 803, 1, "4399sj", result["equip"]);
	if(ret)
		return ret;

END_SJ4399:
	ret = logicUser.SetUserLimit(uid, dataUser);
	if(ret)
		return ret;

	return R_SUCCESS;
}

int CLogicCMD::XSK4399(unsigned uid, string& code, string& openid, Json::Value &result, unsigned lasttime, unsigned seqid)
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

	CLogicPromotionMapping logicPromotionMapping;
	DataPromotionMapping dataPromotionMapping;
	CLogicEquipment logicEquipment;

	string ecode = OpenPlatform::GetPlatform()->GetConfig(CONFIG_4399_OTHER_KEY)
			+ OpenPlatform::GetPlatform()->GetConfig(CONFIG_4399_GAME_NAME)
			+ "S" + CTrans::ITOS(Config::GetZoneByUID(uid)) + openid + "xsk";
	string mcode = Crypt::Md5Encode(ecode);
	if(mcode != code)
	{
		result["result"] = "4399_code_error";
		goto END_XSK4399;
	}

	dataPromotionMapping.uid = uid;
	dataPromotionMapping.useflag = 0;
	ret = logicPromotionMapping.GetPromotionMapping(dataPromotionMapping);
	if(ret != R_SUCCESS && ret != R_ERR_NO_DATA)
		return ret;
	if(ret == R_SUCCESS)
	{
		if(dataPromotionMapping.useflag & XSK_4399_EXCHANGE)
		{
			result["result"] = "4399_code_exist";
			goto END_XSK4399;
		}
		dataPromotionMapping.useflag |= XSK_4399_EXCHANGE;
		dataPromotionMapping.usetime = Time::GetGlobalTime();
		ret = logicPromotionMapping.SetPromotionMapping(dataPromotionMapping);
		if(ret)
			return ret;
	}
	else
	{
		dataPromotionMapping.useflag |= XSK_4399_EXCHANGE;
		dataPromotionMapping.usetime = Time::GetGlobalTime();
		dataPromotionMapping.pid = 0;
		ret = logicPromotionMapping.AddPromotionMapping(dataPromotionMapping);
		if(ret)
			return ret;
	}

	ret = logicEquipment.AddOneItem(uid, 802, 1, "4399xsk", result["equip"]);
	if(ret)
		return ret;

END_XSK4399:
	ret = logicUser.SetUserLimit(uid, dataUser);
	if(ret)
		return ret;

	return R_SUCCESS;
}


int CLogicCMD::XSKBaidu(unsigned uid, string &code, string &openid, Json::Value &result, unsigned lasttime, unsigned seqid)
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

	CLogicPromotionMapping logicPromotionMapping;
	DataPromotionMapping dataPromotionMapping;
	CLogicEquipment logicEquipment;

	string ecode = OpenPlatform::GetPlatform()->GetAppId()
			+ OpenPlatform::GetPlatform()->GetConfig(CONFIG_BAIDU_GAME_NAME)
			+ CTrans::ITOS(Config::GetZoneByUID(uid)) + openid
			+ "baidu";

	string mcode = Crypt::Md5Encode(ecode);

	if (mcode != code)
	{
		result["result"] = "baidu_code_error";
		goto END_XSKBaidu;
	}

	dataPromotionMapping.uid = uid;
	dataPromotionMapping.useflag = 0;
	ret = logicPromotionMapping.GetPromotionMapping(dataPromotionMapping);
	if (R_SUCCESS != ret && R_ERR_NO_DATA != ret)
	{
		return ret;
	}

	if(ret == R_SUCCESS)
	{
		if(dataPromotionMapping.useflag & XSK_BAIDU_EXCHANGE)
		{
			result["result"] = "baidu_code_exist";
			goto END_XSKBaidu;
		}
		dataPromotionMapping.useflag |= XSK_BAIDU_EXCHANGE;
		dataPromotionMapping.usetime = Time::GetGlobalTime();
		ret = logicPromotionMapping.SetPromotionMapping(dataPromotionMapping);
		if(ret)
		{
			return ret;
		}
	}
	else
	{
		dataPromotionMapping.useflag |= XSK_BAIDU_EXCHANGE;
		dataPromotionMapping.usetime = Time::GetGlobalTime();
		dataPromotionMapping.pid = 0;
		ret = logicPromotionMapping.AddPromotionMapping(dataPromotionMapping);
		if(ret)
		{
			return ret;
		}
	}

	ret = logicEquipment.AddOneItem(uid, 802, 1, "baiduxsk", result["equip"]);
	if(ret)
	{
		return ret;
	}

END_XSKBaidu:

	ret = logicUser.SetUserLimit(uid, dataUser);
	if (ret)
	{
		return ret;
	}

	return R_SUCCESS;
}


int CLogicCMD::CreditShop(unsigned uid, unsigned eqid, unsigned b4399, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	int ret = logicUser.GetUser(uid, dataUser);
	if (ret)
	{
		error_log("[get_user_info_failed] [uid = %u, ret = %d]", uid, ret);
		return ret;
	}

	ret = checkLastSaveUID(dataUser);
	if (ret)
	{
		return ret;
	}

	ret = checkLastSaveTime(dataUser, lasttime, seqid);
	if (ret)
	{
		return ret;
	}

	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	Json::Reader reader;
	Json::Value user_flag;
	Json::FastWriter writer;

	reader.parse(dataUser.user_flag, user_flag);

	int cost = (OpenPlatform::GetType() == PT_4399 && b4399) ? -COST_CREDIT_NUM_4399 : -COST_CREDIT_NUM;
	CLogicPay logicPay;
	ret = logicPay.ChangePayHeroCoins(uid, cost, "CreditShop", user_flag);
	if (ret)
	{
		error_log("ChangePayHeroCoins failed, uid = %u, ret = %d", uid, ret);
		return ret;
	}

	dataUser.user_flag = writer.write(user_flag);
	result["coins3"] = user_flag["heroCoins"][1u];

	CLogicEquipment logicEquip;
	ret = logicEquip.AddOneItem(uid, eqid, GET_BALANCE_NUM, "CreditShop", result["equipment"], true);
	if (ret)
	{
		error_log("AddOneItem failed, uid = %u, eqid = %u, ret = %d", uid, eqid, ret);
		return ret;
	}

	ret = logicUser.SetUser(uid, dataUser);
	if (ret)
	{
		return ret;
	}

	return R_SUCCESS;
}

int CLogicCMD::getDragonlist(Json::Value &draglist, const unsigned id)
{
	static unsigned longlingNum[TOMB_NUM] = {160, 350, 600, 1000, 2000};
	static unsigned foNum[TOMB_NUM] = {24, 52, 90, 150, 300};
	unsigned dragScale = 0;
	unsigned fo = 0;
	unsigned i;

	for (i = 0; i < DRAG_LIST_NUM; ++i)
	{
		fo = Math::GetRandomInt(foNum[id]);
		dragScale = Math::GetRandomInt(2) ? (longlingNum[id] + fo) : (longlingNum[id] - fo);
		draglist[i] = dragScale;
	}

	return 0;
}


int CLogicCMD::getUselist(Json::Value &uselist, const Json::Value &draglist, unsigned &dragScale)
{
	static unsigned randNum[DRAG_LIST_NUM];
	unsigned i;
	unsigned len = DRAG_LIST_NUM;
	unsigned randindex = 0;
	unsigned listindex = 0;

	for (i = 0; i < DRAG_LIST_NUM; ++i)
	{
		randNum[i] = i;
	}

	uselist.clear();
	for (i = 0; i < GET_DRAG_NUM; ++i)
	{
		randindex = Math::GetRandomInt(len);
		listindex = randNum[randindex];
		randNum[randindex] = randNum[len - 1];
		--len;

		uselist[i] = listindex;

		// 所获得的龙鳞
		dragScale += draglist[listindex].asUInt();

	}

	return 0;
}


int CLogicCMD::resetTouch(Json::Value &draglist, Json::Value &uselist, const unsigned id)
{
	uselist.clear();
	getDragonlist(draglist, id);

	return 0;
}


int CLogicCMD::TouchGold(unsigned uid, unsigned type, unsigned id, unsigned listindex, unsigned ud, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	unsigned now = Time::GetGlobalTime();

	if ((now < Config::GetIntValue(CONFIG_TOMB_TREASURE_BEGIN_TS))
	|| (now > Config::GetIntValue(CONFIG_TOMB_TREASURE_END_TS )))
	{
		PARAM_ERROR_RETURN_MSG("time is error");
	}

	if (type < TouchReset || type > TouchSkip)
	{
		PARAM_ERROR_RETURN_MSG("type is error");
	}

	if (id < TOUCH_TOMB_DEFAULT_ID || id > TOUCH_TOMB_MAX_ID)
	{
		PARAM_ERROR_RETURN_MSG("id is error");
	}

	if (listindex < 0 || listindex > DRAG_LIST_NUM)
	{
		PARAM_ERROR_RETURN_MSG("listindex is error");
	}

	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	int ret = logicUser.GetUser(uid, dataUser);
	if (ret)
	{
		error_log("[get_user_info_failed] [uid = %u, ret = %d]", uid, ret);
		return ret;
	}

	ret = checkLastSaveUID(dataUser);
	if (ret)
	{
		return ret;
	}

	ret = checkLastSaveTime(dataUser, lasttime, seqid);
	if (ret)
	{
		return ret;
	}

	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	Json::Reader reader;
	Json::Value user_flag;
	Json::FastWriter writer;

	reader.parse(dataUser.user_flag, user_flag);


	CLogicSecinc logicSecinc;
	Json::Value newAct1;
	Json::Value newAct2;
	unsigned i = 0;
	int ret1 = 0;
	int ret2 = 0;

	ret1 = logicSecinc.GetSecinc(uid, NAT_TOUCH1, newAct1);
	ret2 = logicSecinc.GetSecinc(uid, NAT_TOUCH2, newAct2);
	if (R_ERR_NO_DATA == ret1 || R_ERR_NO_DATA == ret2)
	{
		newAct1.clear();
		newAct2.clear();

		newAct1["id"] = NAT_TOUCH1;
		newAct1["a"] = 0;					// total
		newAct1["c"] = 0;					// lastResetTS
		newAct1["v"] = Config::GetIntValue(CONFIG_TOMB_TREASURE_VER);


		newAct2["id"] = NAT_TOUCH2;
		newAct2["d"][0u] = TOMB_UNLOCK;		// tombStat

		for (i = 1; i < TOMB_NUM; ++i)
		{
			newAct2["d"][i] = TOMB_LOCK;
		}
		newAct2["d"][i] = 0;					// tombCount
		newAct2["f"] = Json::arrayValue;
	}
	else if (ret1 || ret2)
	{
		return ret1 ? ret1 : ret2;
	}

	if (Config::GetIntValue(CONFIG_TOMB_TREASURE_VER) != newAct1["v"].asInt())
	{
		newAct1.clear();
		newAct2.clear();

		newAct1["id"] = NAT_TOUCH1;
		newAct1["a"] = 0;					// total
		newAct1["c"] = 0;					// lastResetTS
		newAct1["v"] = Config::GetIntValue(CONFIG_TOMB_TREASURE_VER);


		newAct2["id"] = NAT_TOUCH2;
		newAct2["d"][0u] = TOMB_UNLOCK;		// tombStat

		for (i = 1; i < TOMB_NUM; ++i)
		{
			newAct2["d"][i] = TOMB_LOCK;
		}
		newAct2["d"][i] = 0;					// tombCount
		newAct2["f"] = Json::arrayValue;
	}


	unsigned total = newAct1["a"].asUInt();
	unsigned tombCount= newAct2["d"][(unsigned)TOMB_NUM].asUInt();
	unsigned lastResetTS = newAct1["c"].asUInt();
	Json::Value &tombStat = newAct2["d"];
	Json::Value &draglist = newAct2["e"];
	Json::Value &uselist = newAct2["f"];

	if ((total > TOTAL_TOMB_ACT_COUNT)
		|| ((TouchAKeyTurn == type) && (total + GET_DRAG_NUM > TOTAL_TOMB_ACT_COUNT)))
	{
		LOGIC_ERROR_RETURN_MSG("total too large");
	}

	if (tombCount > GET_DRAG_NUM)
	{
		LOGIC_ERROR_RETURN_MSG("tombCount too large");
	}

	if (lastResetTS > now)
	{
		LOGIC_ERROR_RETURN_MSG("lastResetTS error");
	}

	static const unsigned nextTombChance[TOMB_NUM] = {5, 6, 7, 8, 20};
	static const unsigned payCash[GET_DRAG_NUM] = {2, 5, 10, 20, 50};
	static const string reason[TouchTypeNum] = {
			"TouchReset",
			"TouchTurn",
			"TouchAKeyTurn",
			"TouchSkip",
	};

	unsigned rate = 0;
	unsigned dragScale = 0;
	int cash = 0;

	// 重置
	// 检查当前时间相是否越过0点
	if (!Time::IsToday(lastResetTS))
	{
		resetTouch(draglist, uselist, TOUCH_TOMB_DEFAULT_ID);
		total = 0;
		tombCount = 0;
		newAct1["c"] = now;

		tombStat[0u] = TOMB_UNLOCK;
		for (i = 1; i < TOMB_NUM; ++i)
		{
			tombStat[i] = TOMB_LOCK;
		}
	}

	if (TouchReset == type)
	{
		if (TOMB_LOCK == tombStat[id].asUInt())
		{
			LOGIC_ERROR_RETURN_MSG("the tomb is lock");
		}
		// 重新生成
		resetTouch(draglist, uselist, id);
		tombCount = 0;
	}
	else if (TouchTurn == type)
	{
		if (tombCount >= GET_DRAG_NUM)
		{
			LOGIC_ERROR_RETURN_MSG("tombCount must less than 5");
		}

		uselist[tombCount] = listindex;

		// 一定几率解锁下一个 tomb
		rate = Math::GetRandomInt(100);
		if ((id < TOUCH_TOMB_MAX_ID) && (TOMB_LOCK == tombStat[id + 1].asUInt()))
		{
			tombStat[id + 1] = rate < nextTombChance[id] ? TOMB_UNLOCK : TOMB_LOCK;
		}

		tombCount += 1;
		total += 1;
		cash = -payCash[id];
		dragScale += draglist[listindex].asUInt();
	}
	else if (TouchAKeyTurn == type)
	{
		if (0 != tombCount)
		{
			LOGIC_ERROR_RETURN_MSG("tombCount muse be 0");
		}

		getUselist(uselist, draglist, dragScale);

		// unlock tomb
		if ((id < TOUCH_TOMB_MAX_ID) && (TOMB_LOCK == tombStat[id + 1].asUInt()))
		{
			for (i = 0; i < GET_DRAG_NUM; ++i)
			{
				rate = Math::GetRandomInt(100);
				if (rate < nextTombChance[id])
				{
					tombStat[id + 1] = TOMB_UNLOCK;
					break;
				}
			}
		}

		tombCount = GET_DRAG_NUM;
		total += GET_DRAG_NUM;
		cash = -(GET_DRAG_NUM * payCash[id]);
	}
	else if (TouchSkip == type)
	{
		if (TOUCH_TOMB_SKIP_ID != id || (TOMB_UNLOCK == tombStat[id].asUInt()))
		{
			LOGIC_ERROR_RETURN_MSG("id must be 3 or already unlock");
		}
		// id must be TOUCH_TOMB_SKIP_ID
		tombStat[TOUCH_TOMB_SKIP_ID] = TOMB_UNLOCK;
		cash = -SKIP_STEP_COST;

		resetTouch(draglist, uselist, TOUCH_TOMB_SKIP_ID);
		tombCount = 0;
	}

	CLogicPay logicPay;
	DataPay dataPay;
	bool bsave = false;
	if (cash)
	{
#ifdef SG_USE_CASH
		ret = logicPay.ProcessOrderForBackend(uid, cash, 0, dataPay, reason[type], user_flag, bsave);
		if (ret)
		{
			error_log("ProcessOrderForBackend failed. uid = %u, cash = %d, ret = %d", uid, cash, ret);
			return ret;
		}
		result["cash"] = dataPay.cash;
#else
		if (type == TouchTurn || type == TouchAKeyTurn)
		{
			int ret = CLogicEquipment().UseEquipment(uid, 2025, ud, -cash, reason[type]);
			if (ret)
			{
				error_log("use_equip error. uid:%u, ud: %d, number: %d", uid, ud, -cash);
				return ret;
			}
			result["equip_cost"] = -cash;
		}
		else
		{
			ret = logicPay.ProcessOrderForBackend(uid, cash, 0, dataPay, reason[type], user_flag, bsave);
			if (ret)
			{
				error_log("ProcessOrderForBackend failed. uid = %u, cash = %d, ret = %d", uid, cash, ret);
				return ret;
			}
			result["cash"] = dataPay.cash;
		}
#endif

		if (bsave)
		{
			result["pointpay"] = user_flag["user_pay"];
			dataUser.user_flag = writer.write(user_flag);
		}
	}

	if (dragScale)
	{
		unsigned yinliang = 0;
		Json::Value tech;
		reader.parse(dataUser.user_tech,tech);
		Json::GetUInt(tech, "yinliang", yinliang);

		yinliang += dragScale;

		result["yinliang"] = yinliang;
		tech["yinliang"] = yinliang;
		dataUser.user_tech = writer.write(tech);

		RESOURCE_LOG("[TouchGold][uid=%u,chgcash=%d,cash=%d,chgyinliang=%u,yinliang=%u]", uid,
				cash, dataPay.cash, dragScale, yinliang);
	}


	newAct1["a"] = total;
	newAct2["d"][(unsigned)TOMB_NUM] = tombCount;
	result["newAct1"] = newAct1;
	result["newAct2"] = newAct2;

	ret = logicSecinc.SetOneSecinc(uid, newAct1);
	if (ret)
	{
		error_log("SetOneSecinc failed. uid = %u, ret = %d", uid, ret);
		return ret;
	}

	ret = logicSecinc.SetOneSecinc(uid, newAct2);
	if (ret)
	{
		error_log("SetOneSecinc failed. uid = %u, ret = %d", uid, ret);
		return ret;
	}

	ret = logicUser.SetUser(uid, dataUser);
	if (ret)
	{
		return ret;
	}

	return R_SUCCESS;
}


int CLogicCMD::ProtectToken(unsigned uid, unsigned equd, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	int ret = logicUser.GetUser(uid, dataUser);
	if (ret)
	{
		error_log("[get_user_info_failed] [uid = %u, ret = %d]", uid, ret);
		return ret;
	}

	ret = checkLastSaveUID(dataUser);
	if (ret)
	{
		return ret;
	}

	ret = checkLastSaveTime(dataUser, lasttime, seqid);
	if (ret)
	{
		return ret;
	}

	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	unsigned now = Time::GetGlobalTime();

	if (dataUser.protected_time > now)
	{
		LOGIC_ERROR_RETURN_MSG("already protect time");
	}

	Json::Value worldres;
	Json::Reader reader;
	Json::FastWriter writer;

	reader.parse(dataUser.worldres, worldres);
	unsigned lpt = 0;
	unsigned pt = 0;
	unsigned tokencount = 1;

	Json::GetUInt(worldres, "lpt", lpt);
	Json::GetUInt(worldres, "pt", pt);

	// 本次消耗令牌数量
	Json::GetUInt(worldres, "tokencount", tokencount);

	// 判断是否重置
	if (CTime::GetDayInterval(lpt, now))
	{
		pt = 0;
		tokencount = 1;
	}

	// 消耗道具
	CLogicEquipment logicEquip;
	ret = logicEquip.UseEquipment(uid, PROTECT_TOKEN_ID, equd, tokencount, "ProtectToken");
	if (ret)
	{
		error_log("UseEquipment failed. uid = %d, eqid = %d, equd = %u", uid, PROTECT_TOKEN_ID, equd);
		return ret;
	}

	lpt = now;
	pt += PROTECT_TOKEN_TS;
	dataUser.protected_time = now + PROTECT_TOKEN_TS;
	tokencount *= 2;

	worldres["lpt"] = lpt;
	worldres["pt"] = pt;
	worldres["tokencount"] = tokencount;
	dataUser.worldres = writer.write(worldres);

	result["tokencount"] = tokencount;
	result["protected_time"] = dataUser.protected_time;

	ret = logicUser.SetUser(uid, dataUser);
	if (ret)
	{
		return ret;
	}

	return R_SUCCESS;
}


// 天书 遁甲 活动
// type: 1 heaven, 0 daoist
// equd[0, 0, 0, 0] 四种 equipment ud, 0:没有该equipment
// r1: 粮食, r4: 铁矿
// 1. tech 获得 heaven or daoist
// 2. 判断 lv resource equipment
// 3. 根据 equd 获得 eqid
// 4. 扣除 resource, equipment
// 5. 判断是否升级
int CLogicCMD::HeavenDaoist(unsigned uid, unsigned type, unsigned count, const Json::Value &equd, bool is_cash, Json::Value &result, unsigned lasttime, unsigned seqid, unsigned oneclick)
{
	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	int ret = logicUser.GetUser(uid, dataUser);
	if (ret)
	{
		error_log("[get_user_info_failed] [uid = %u, ret = %d]", uid, ret);
		return ret;
	}

	ret = checkLastSaveUID(dataUser);
	if (ret)
	{
		return ret;
	}

	ret = checkLastSaveTime(dataUser, lasttime, seqid);
	if (ret)
	{
		return ret;
	}

	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	Json::Value tech;
	Json::Reader reader;
	Json::FastWriter writer;
	unsigned exp = 0;
	unsigned lv = 0;

	reader.parse(dataUser.user_tech, tech);

	Json::Value &heavenDaoist = type ? tech["heaven"] : tech["daoist"];
	unsigned &resource = type ? dataUser.r1 : dataUser.r4;
	unsigned typePrefix = type ? HEAVEN_PREFIX : DAOIST_PREFIX;
	unsigned maxlv      = type ? HEAVEN_MAXLV : DAOIST_MAXLV;

	Json::GetUInt(heavenDaoist, "exp", exp);

	unsigned max_exp = type ? MAXEXP_1 : MAXEXP_8;
	if (exp >= max_exp)
	{
		LOGIC_ERROR_RETURN_MSG("already highest exp");
	}

	CDataXML *dataXML = CDataXML::GetCDataXML();
	XMLHeavenDaoist xmlHeavenDaoist;

	if (exp)
	{
		// 档中 lv 不可靠因此
		// 根据exp获得lv
		ret = dataXML->GetHeavenDaoistLv(typePrefix + maxlv, exp, lv);
		if (ret)
		{
			error_log("GetHeavenItem failed. uid = %u, ret = %d", uid, ret);
			return ret;
		}
		lv = type ? lv : (lv - HEAVEN_NUM);
	}

	unsigned jie_index = 0;
	if (lv == 0)
	{
		jie_index = 0;
	} else if (lv >= 1 && lv <= 10)
	{
		jie_index = 1;
	}else if (lv >= 11 && lv <= 20)
	{
		jie_index = 2;
	}else if (lv >= 21 && lv <= 30)
	{
		jie_index = 3;
	}else if (lv >= 31 && lv <= 40)
	{
		jie_index = 4;
	}else if (lv >= 41 && lv <= 50)
	{
		jie_index = 5;
	}else if (lv >= 51 && lv <= 60)
	{
		jie_index = 6;
	}else if (lv >= 61 && lv <= 70)
	{
		jie_index = 7;
	}else if (lv >= 71 && lv <= 80)
	{
		jie_index = 8;
	}else if (lv >= 81 && lv <= 90)
	{
		jie_index = 9;
	}else if (lv >= 91 && lv <= 100)
	{
		jie_index = 10;
	}else if (lv >= 101 && lv <= 110)
	{
		jie_index = 11;
	}else if (lv >= 111 && lv <= 120)
	{
		jie_index = 12;
	}else if(lv >= 121 && lv <= 130 && type == 1)
	{
		jie_index = 13;
	}else if(lv >= 131 && lv <= 140 && type == 1)
	{
		jie_index = 14;
	}else if(lv >= 141 && lv <= 150 && type == 1)
	{
		jie_index = 15;
	}

	if (jie_index >= 13 )
	{
		if(type == 0){
			LOGIC_ERROR_RETURN_MSG("jie shu is too high");
		}else if(type == 1) {
			if(jie_index >= 16) {
				LOGIC_ERROR_RETURN_MSG("jie shu is too high");
			}
		}
	}
	unsigned need_cash = 0;
	ret = dataXML->GetCostHeavenDaoist((bool)type, jie_index, need_cash);
	if (ret)
	{
		error_log("GetHeavenItem cost failed. uid = %u, ret = %d", uid, ret);
		return ret;
	}

	ret = dataXML->GetHeavenDaoistItem(typePrefix + lv, xmlHeavenDaoist);
	if (ret)
	{
		error_log("GetHeavenItem failed. uid = %u, ret = %d", uid, ret);
		return ret;
	}

	unsigned curexp = exp;
	unsigned curper = xmlHeavenDaoist.per;
	unsigned curres = xmlHeavenDaoist.res;
	unsigned curneedeq = xmlHeavenDaoist.needeq;
	unsigned curcnt = 0;
	unsigned nextexp = 0;

	unsigned sumres = 0;
	unsigned sumneedeq = 0;

	CLogicEquipment logicEquip;
	Json::Value equip_data;
	unsigned ecnt = 0;
	unsigned i = 0;
	unsigned ud = 0;
	unsigned id = 0;
	unsigned len = equd.size();
	unsigned sumecnt = 0;
	Json::Value eqid(Json::arrayValue);
	Json::Value eqcount(Json::arrayValue);

	eqid.resize(len);
	eqcount.resize(len);
	for (i = 0; i < len; ++i)
	{
		ud = equd[i].asUInt();
		ecnt = 0;
		id = 0;
		if (ud)
		{
			ret = logicEquip.Get(uid, ud, equip_data);
			if (ret)
			{
				debug_log("Get failed. uid = %u, equd = %u", uid, ud);
			}

			if (!Json::GetUInt(equip_data, "id", id) || (0 == id)
					|| !Json::GetUInt(equip_data, "count", ecnt) || (0 == ecnt))
			{
				debug_log("id or count is empty");
				return R_ERR_DB;
			}
		}

		sumecnt += ecnt;
		eqid[i] = id;
		eqcount[i] = ecnt;
	}
	while (count > 0)
	{
		++lv;
		ret = dataXML->GetHeavenDaoistItem(typePrefix + lv, xmlHeavenDaoist);
		if (ret)
		{
			error_log("GetHeavenItem failed. uid = %u, ret = %d", uid, ret);
			return ret;
		}

		nextexp = xmlHeavenDaoist.exp;

		// 当前需要次数
		curcnt = (unsigned)ceil((nextexp - curexp)/(float)curper);
		unsigned next_lv_cnt = curcnt;
		if(1 == oneclick)
		{
			unsigned c3 = sumecnt / curneedeq;
			unsigned min_cnt = curcnt;
			if(is_cash)
			{
				CLogicPay logic_pay;
				DataPay pay;
				int ret = logic_pay.GetPay(uid, pay);
				if (ret != 0)
					return ret;
				unsigned c2 = pay.cash /need_cash;
				min_cnt = min(c2, c3);
			//	error_log("HeavenDaoist: curcnt: %u, c2 %u, c3 %u resource %u sumecnt %u", curcnt, c2, c3, resource, sumecnt);
			}
			else
			{
				unsigned c1 = resource /curres;
				min_cnt = min(c1, c3);
			//	error_log("HeavenDaoist: curcnt: %u, c1 %u, c3 %u resource %u sumecnt %u", curcnt,c1, c3, resource, sumecnt);
			}

			curcnt = min_cnt > curcnt ? curcnt: min_cnt;
			if(curcnt >0)
			{
				need_cash *= curcnt;
			}
			if(curcnt < next_lv_cnt)
			{
				--lv;
			}
			count = curcnt;
		}
		else
		{
			// 次数不够
			if (curcnt > count)
			{
				--lv;
				curcnt = count;
			}
		}

		count -= curcnt;
		curexp += curper * curcnt;
		// 总共消耗的资源
		sumres += curres * curcnt;
		// 总共消耗道具
		sumneedeq += curneedeq * curcnt;
		exp = curexp;
		if (exp >= max_exp)
		{
			break;
		}

		curper = xmlHeavenDaoist.per;
		curneedeq = xmlHeavenDaoist.needeq;
		curres = xmlHeavenDaoist.res;
	}

	if ((!is_cash) && sumres > resource)
	{
		LOGIC_ERROR_RETURN_MSG("resource is not enough");
	}
	if (!is_cash)
	{
		resource -= sumres;
	}

	if (sumneedeq > sumecnt)
	{
		LOGIC_ERROR_RETURN_MSG("equipment count is not enough");
	}

	unsigned usecount = 0;
	for (i = 0; (i < len) && sumneedeq; ++i)
	{
		ud = equd[i].asUInt();
		if (ud)
		{
			ecnt = eqcount[i].asUInt();
			id = eqid[i].asUInt();
			if (sumneedeq > ecnt)
			{
				usecount = ecnt;
				sumneedeq -= ecnt;
			}
			else
			{
				usecount = sumneedeq;
				sumneedeq = 0;
			}

			ret = logicEquip.UseEquipment(uid, id, ud, usecount, "Heaven_" + CTrans::UTOS(i));
			if (ret)
			{
				error_log("UseEquipment failed. uid = %u, eqid = %u, equd = %u", uid, id, ud);
				return ret;
			}
		}
		// 每个道具使用数量
		result["usecount"][i] = usecount;
	}

	// 已使用完剩余使用0
	while (i < len)
	{
		result["usecount"][i++] = 0;
	}

	if (is_cash)
	{
		Json::Value user_flag;
		bool bsave = false;
		reader.parse(dataUser.user_flag, user_flag);
		CLogicPay logicPay;
		DataPay payData;
		const string reason = type ? "HEAVEN_CASH" : "DAOIST_CASH";
		ret = logicPay.ProcessOrderForBackend(uid, -need_cash, 0, payData, reason, user_flag, bsave);
		if(ret)
			return ret;
		result["pointpay"].resize(0);
		if(bsave)
		{
			result["pointpay"] = user_flag["user_pay"];
			dataUser.user_flag = writer.write(user_flag);
		}
		result["coins"] = payData.coins;
		result["coins2"] = payData.cash;
	}


	heavenDaoist["exp"] = exp;
	heavenDaoist["lv"] = lv;

	result["heaven"] = tech["heaven"];
	result["daoist"] = tech["daoist"];
	result["r1"] = dataUser.r1;
	result["r4"] = dataUser.r4;

	dataUser.user_tech = writer.write(tech);
    string res = writer.write(result);
    EQUIPMENT_LOG("HeavenDaoist: res %s", res.c_str());

	ret = logicUser.SetUser(uid, dataUser);
	if (ret)
	{
		return ret;
	}

	return R_SUCCESS;
}


int CLogicCMD::Catapult(unsigned uid, unsigned count, const Json::Value &equd, int is_cash, Json::Value &result, unsigned lasttime, unsigned seqid, unsigned oneclick)
{
	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	int ret = logicUser.GetUser(uid, dataUser);
	if (ret)
	{
		error_log("[get_user_info_failed] [uid = %u, ret = %d]", uid, ret);
		return ret;
	}

	ret = checkLastSaveUID(dataUser);
	if (ret)
	{
		return ret;
	}

	ret = checkLastSaveTime(dataUser, lasttime, seqid);
	if (ret)
	{
		return ret;
	}

	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	Json::Value tech;
	Json::Reader reader;
	Json::FastWriter writer;
	unsigned exp = 0;
	unsigned lv = 0;

	reader.parse(dataUser.user_tech, tech);

	Json::Value &catapult = tech["catapult"];
	unsigned &resource = dataUser.r4;
	EQUIPMENT_LOG("Catapult:resource %u", resource);

	Json::GetUInt(catapult, "exp", exp);

	if (exp >= MAXEXP_CATAPULT)
	{
		LOGIC_ERROR_RETURN_MSG("already highest exp");
	}

	CDataXML *dataXML = CDataXML::GetCDataXML();
	XMLCatapult xmlcatapult;

	if (exp)
	{
		// 档中 lv 不可靠因此
		// 根据exp获得lv
		ret = dataXML->GetCatapultLv(MAXLV, exp, lv);
		if (ret)
		{
			error_log("GetCatapultLv failed. uid = %u, ret = %d", uid, ret);
			return ret;
		}
	}

	unsigned jie_index = (lv % 10 == 0 ? lv/10 : lv/10+1);

	if (jie_index >= 13)
	{
		LOGIC_ERROR_RETURN_MSG("jie shu is too high");
	}


	unsigned need_cash = 0;
	ret = dataXML->GetCostCatapult(jie_index, need_cash);
	if (ret)
	{
		error_log("GetcostCatapult failed. uid = %u, ret = %d, jie_index=%u", uid, ret, jie_index);
		return ret;
	}

	ret = dataXML->GetCatapultItem(lv, xmlcatapult);

	if (ret)
	{
		error_log("GetHeavenItem failed. uid = %u, ret = %d", uid, ret);
		return ret;
	}

	unsigned curexp = exp;
	unsigned curper = xmlcatapult.per;
	unsigned curres = xmlcatapult.res;
	unsigned curneedeq = xmlcatapult.needeq;
	unsigned curcnt = 0;
	unsigned nextexp = 0;

	unsigned sumres = 0;
	unsigned sumneedeq = 0;

	CLogicEquipment logicEquip;
	Json::Value equip_data;
	unsigned ecnt = 0;
	unsigned i = 0;
	unsigned ud = 0;
	unsigned id = 0;
	unsigned len = equd.size();
	unsigned sumecnt = 0;
	Json::Value eqid(Json::arrayValue);
	Json::Value eqcount(Json::arrayValue);

	eqid.resize(len);
	eqcount.resize(len);
	unsigned equd_array[1] ={4094};

	for (i = 0; i < len &&  i < sizeof(equd_array)/sizeof(equd_array[0]); ++i)
	{
		ud = equd[i].asUInt();
		ecnt = 0;
		id = 0;
		if (ud)
		{
			ret = logicEquip.Get(uid, ud, equip_data);
			if (ret)
			{
				debug_log("Get failed. uid = %u, equd = %u", uid, ud);
			}

			if (!Json::GetUInt(equip_data, "id", id) || (0 == id)
					|| !Json::GetUInt(equip_data, "count", ecnt) || (0 == ecnt))
			{
				debug_log("id or count is empty");
				return R_ERR_DB;
			}
			if(id != equd_array[i])
			{
				debug_log("id is worng uid=%u", uid);
				return R_ERR_PARAM;
			}
		}

		sumecnt += ecnt;
		eqid[i] = id;
		eqcount[i] = ecnt;
	}
	while (count > 0)
	{
		++lv;
		ret = dataXML->GetCatapultItem(lv, xmlcatapult);
		if (ret)
		{
			error_log("GetCatapultItem failed. uid = %u, ret = %d", uid, ret);
			return ret;
		}

		nextexp = xmlcatapult.exp;

		// 当前需要次数
		curcnt = (unsigned)ceil((nextexp - curexp)/(float)curper);
		unsigned next_lv_cnt = curcnt;
		if(1 == oneclick)
		{
			unsigned c3 = sumecnt / curneedeq;
			unsigned min_cnt = curcnt;
			if(1 == is_cash)
			{
				CLogicPay logic_pay;
				DataPay pay;
				int ret = logic_pay.GetPay(uid, pay);
				if (ret != 0)
					return ret;
				unsigned c2 = pay.cash /need_cash;
				min_cnt = min(c2, c3);
			}
			else
			{
				unsigned c1 = resource /curres;
				min_cnt = min(c1, c3);
			}

			curcnt = min_cnt > curcnt ? curcnt: min_cnt;
			if(curcnt >0)
			{
				need_cash *= curcnt;
			}
			if(curcnt < next_lv_cnt)
			{
				--lv;
			}
			count = curcnt;
		}
		else
		{
			// 次数不够
			if (curcnt > count)
			{
				--lv;
				curcnt = count;
			}
		}

		count -= curcnt;
		curexp += curper * curcnt;
		// 总共消耗的资源
		sumres += curres * curcnt;
		// 总共消耗道具
		sumneedeq += curneedeq * curcnt;
		exp = curexp;
		if (exp >= MAXEXP_CATAPULT)
		{
			break;
		}

		curper = xmlcatapult.per;
		curneedeq = xmlcatapult.needeq;
		curres = xmlcatapult.res;
	}

	if ((0 == is_cash) && sumres > resource)
	{
		LOGIC_ERROR_RETURN_MSG("resource is not enough");
	}
	if (0 == is_cash)
	{
		resource -= sumres;
	}

	if (sumneedeq > sumecnt)
	{
		LOGIC_ERROR_RETURN_MSG("equipment count is not enough");
	}

	unsigned usecount = 0;
	for (i = 0; (i < len) && sumneedeq; ++i)
	{
		ud = equd[i].asUInt();
		if (ud)
		{
			ecnt = eqcount[i].asUInt();
			id = eqid[i].asUInt();
			if (sumneedeq > ecnt)
			{
				usecount = ecnt;
				sumneedeq -= ecnt;
			}
			else
			{
				usecount = sumneedeq;
				sumneedeq = 0;
			}

			ret = logicEquip.UseEquipment(uid, id, ud, usecount, "Catapult_" + CTrans::UTOS(i));
			if (ret)
			{
				error_log("UseEquipment failed. uid = %u, eqid = %u, equd = %u", uid, id, ud);
				return ret;
			}
		}
		// 每个道具使用数量
		result["usecount"][i] = usecount;
	}

	// 已使用完剩余使用0
	while (i < len)
	{
		result["usecount"][i++] = 0;
	}

	if (1 == is_cash)
	{
		Json::Value user_flag;
		bool bsave = false;
		reader.parse(dataUser.user_flag, user_flag);
		CLogicPay logicPay;
		DataPay payData;
		ret = logicPay.ProcessOrderForBackend(uid, -need_cash, 0, payData, "CATAPULT_CASH", user_flag, bsave); if(ret) return ret; result["pointpay"].resize(0); if(bsave)
		{
			result["pointpay"] = user_flag["user_pay"];
			dataUser.user_flag = writer.write(user_flag);
		}
		result["coins"] = payData.coins;
		result["coins2"] = payData.cash;
	}


	catapult["exp"] = exp;
	catapult["lv"] = lv;

	result["catapult"] = tech["catapult"];
	result["r4"] = dataUser.r4;

	dataUser.user_tech = writer.write(tech);
	string res = writer.write(result);
	EQUIPMENT_LOG("uid:%u, Catapult: res %s", uid, res.c_str());

	ret = logicUser.SetUser(uid, dataUser);
	if (ret)
	{
		return ret;
	}

	return R_SUCCESS;
}

int CLogicCMD::MergeEquipment(unsigned uid, const vector< vector<unsigned> > &uds, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	if (!IsValidUid(uid))
		return R_ERR_PARAM;

	int ret = 0;
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

	unsigned now = Time::GetGlobalTime();
	CLogicEquipment logicEquip;
	Json::Value equip;
	Json::FastWriter writer;
	result["equipment"] = Json::Value(Json::arrayValue);
	for (unsigned i = 0; i < uds.size(); ++i)
	{
		bool first = true;
		unsigned sum = 0;
		unsigned id = 0;
		unsigned ud = 0;
		bool tmp = false;
		unsigned ats = 0;
		vector<unsigned> del;
		Json::Value keepEquip;
		bool retry = false;

		for (unsigned j = 0; j < uds[i].size(); ++j)
		{
			ret = logicEquip.Get(uid, uds[i][j], equip);
			if (ret)
				return ret;

			unsigned tmpAts = 0;
			Json::GetUInt(equip, "ats", tmpAts);
			if (tmpAts)
			{
				tmp = true;
				if (tmpAts < now)
				{
					del.push_back(uds[i][j]);
					continue;
				}

				if (tmpAts > ats)
					ats = tmpAts;
			}
			if ((tmp && !tmpAts) || (!tmp && tmpAts))
			{
				//需要重新遍历
				retry = true;
				break;
			}

			unsigned count = 0;
			Json::GetUInt(equip, "count", count);
			sum += count;
			if (first)
			{
				first = false;
				ud = uds[i][j];
				id = equip["id"].asUInt();
				if (IS_UN_OVERLAY_ID(id))
				{
					error_log("[can't overlay][uid=%u&ud=%u&eqid=%u]",uid,ud,id);
					DATA_ERROR_RETURN_MSG("can't overlay");
				}
				keepEquip = equip;
			}
			else
			{
				if (id != equip["id"].asUInt())
				{
					error_log("[eqid is not same][uid=%u&ud=%u&eqid=%u&eqid2=%u]",uid, uds[i][j], id, equip["id"].asUInt());
					DATA_ERROR_RETURN_MSG("eqid is not same");
				}
				del.push_back(uds[i][j]);
			}
		}

		if (retry)  //临时物品中有 没有ats字段 的记录，需要重新遍历
		{
			first = true;
			sum = 0;
			id = 0;
			ud = 0;
			tmp = true; //必定是临时物品
			ats = 0;
			del.clear();
			keepEquip.clear();
			for (unsigned j = 0; j < uds[i].size(); ++j)
			{
				ret = logicEquip.Get(uid, uds[i][j], equip);
				if (ret)
					return ret;

				unsigned tmpAts = 0;
				Json::GetUInt(equip, "ats", tmpAts);
				if (!tmpAts || tmpAts < now)
				{
					del.push_back(uds[i][j]);
					continue;
				}
				if (tmpAts > ats)
					ats = tmpAts;

				unsigned count = 0;
				Json::GetUInt(equip, "count", count);
				sum += count;
				if (first)
				{
					first = false;
					ud = uds[i][j];
					id = equip["id"].asUInt();
					if (IS_UN_OVERLAY_ID(id))
					{
						error_log("[can't overlay][uid=%u&ud=%u&eqid=%u]",uid,ud,id);
						DATA_ERROR_RETURN_MSG("can't overlay");
					}
					keepEquip = equip;
				}
				else
				{
					if (id != equip["id"].asUInt())
					{
						error_log("[eqid is not same][uid=%u&ud=%u&eqid=%u&eqid2=%u]",uid, uds[i][j], id, equip["id"].asUInt());
						DATA_ERROR_RETURN_MSG("eqid is not same");
					}
					del.push_back(uds[i][j]);
				}
			}
		}

		if ((tmp && ats) || !tmp)
		{
			if (ats)
				keepEquip["ats"] = ats;

			keepEquip["count"] = sum;
			ret = logicEquip.Chg(uid, ud, keepEquip);
			if (ret)
				return ret;
			EQUIPMENT_LOG("uid=%u,id=%u,eqid=%d,act=MergeChg,chg=%d,count=%d,code=%s,data=%s",
					uid,ud,id,0,sum,"MergeEquipment",writer.write(keepEquip).c_str());
			result["equipment"].append(keepEquip);
		}

		for (unsigned j = 0; j < del.size(); ++j)
		{
			ret = logicEquip.Del(uid, del[j]);
			if (ret)
				return ret;
			EQUIPMENT_LOG("uid=%u,id=%u,eqid=%d,act=MergeDel,chg=%d,count=%d,code=%s,data=0",
					uid,del[j],id,0,0,"MergeEquipment");
		}
	}

	ret = logicUser.SetUserLimit(uid, dataUser);
	if(ret)
		return ret;

	return R_SUCCESS;
}

int CLogicCMD::R5(unsigned uid, unsigned count, Json::Value &result, unsigned lasttime, unsigned seqid)
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

	CLogicSecinc Secinc;
	Json::Value r5;
	ret = Secinc.GetSecinc(uid, NAT_R5, r5);
	if(ret)
		return ret;

	unsigned e3 = 0;
	Json::GetUInt(r5, "e3", e3);
	if(e3 < count)
		return R_ERR_LOGIC;

	vector<unsigned> rewards;
	for (unsigned i = 0; i < 5; ++i)
		rewards.push_back(0);
	int random = 0;
	for (int i = 0; i < count; ++i)
	{
		random = Math::GetRandomInt(100);
		for (unsigned j = 0; j < 5; ++j)
		{
			if (random < ALLAINCE_SNATCH_RATE[j])
			{
				++rewards[j];
				break;
			}
		}
	}

	vector<ItemAdd> items;
	const unsigned reward_eqid[4] = {4066,4065,42015,6050}; //单挑令，集结令，招募令，洗髓令
	for(unsigned i = 0; i < 4; ++i)
	{
		if (rewards[i] > 0)
		{
			ItemAdd item;
			item.eqid = reward_eqid[i];
			item.count = rewards[i];
			item.reason = "lianmengduobao";

			items.push_back(item);
		}
	}
	CLogicEquipment logicEquipment;
	if(items.size())
	{
		ret = logicEquipment.AddItems(uid,items,result["equip"],true);
		if(ret)
			return ret;
	}
	else
		result["equip"].resize(0);

	//威望
	if (rewards[4] > 0)
	{
		dataUser.prosper += 150 * rewards[4];
		result["prosper"] = 150 * rewards[4];
	}

	e3 -= count;
	r5["e3"] = e3;

	result["e3"] = e3;

	ret = Secinc.SetOneSecinc(uid, r5);
	if(ret)
		return ret;

	ret = logicUser.SetUserLimit(uid, dataUser);
	if(ret)
		return ret;

	Json::FastWriter write;
	string equip = write.write(result["equip"]);
	RESOURCE_LOG("[R5][uid=%u,equip=%s,prosper=%u]",uid,equip.c_str(),150*rewards[4]);

	return R_SUCCESS;
}

int CLogicCMD::MultipleWheel(unsigned uid, unsigned type, unsigned lasttime, unsigned seqid, Json::Value &result)
{
	if (type >= MultipleWheelType_Max)
	{
		PARAM_ERROR_RETURN_MSG("type error!");
	}

	unsigned now = Time::GetGlobalTime();
	if (now < Config::GetIntValue(CONFIG_MULTIPLE_WHEEL_BEGIN_TS)
	|| now > Config::GetIntValue(CONFIG_MULTIPLE_WHEEL_END_TS ))
	{
		PARAM_ERROR_RETURN_MSG("time is error");
	}

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

	CLogicSecinc Secinc;
	Json::Value newAct;
	unsigned sid = NAT_MULTIPLEWHEEL;
	ret = Secinc.GetSecinc(uid, sid, newAct);
	if(ret == R_ERR_NO_DATA)
	{
		newAct["id"] = sid;
		newAct["v"] = Config::GetIntValue(CONFIG_MULTIPLE_WHEEL_VER); //version
		newAct["cost"] = 0;
	}
	else if (ret)
	{
		return ret;
	}

	if (newAct["v"].asInt() != Config::GetIntValue(CONFIG_MULTIPLE_WHEEL_VER))
	{
		newAct["v"] = Config::GetIntValue(CONFIG_MULTIPLE_WHEEL_VER);
		newAct["cost"] = 0;
	}

	Json::Reader reader;
	Json::FastWriter write;
	Json::Value user_flag;
	reader.parse(dataUser.user_flag, user_flag);

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
		if(ts >= Config::GetIntValue(CONFIG_MULTIPLE_WHEEL_BEGIN_TS)
		&& ts <= Config::GetIntValue(CONFIG_MULTIPLE_WHEEL_END_TS))
		{
			chargeTotal += user_flag["chgs"][i][1u].asUInt();
		}
	}

	unsigned creditTotal = chargeTotal / 100;	//100钻1积分
	unsigned creditCost = newAct["cost"].asUInt();

	if (creditTotal <= creditCost
			|| (type == MultipleWheelType_One && creditTotal - creditCost < 10)
			|| (type == MultipleWheelType_Ten && creditTotal - creditCost < 100))
	{
		LOGIC_ERROR_RETURN_MSG("have no credit");
	}

	CLogicEquipment logicEquip;
	result["reward"] = Json::Value(Json::arrayValue);
	if (type == MultipleWheelType_One)
	{
		unsigned random = Math::GetRandomInt(100);
		unsigned eqid = 0;
		unsigned count = 0;
		for (unsigned i = 0; i < MULTIPLE_WHEEL_REWARD_NUM; ++i)
		{
			if (random < MULTIPLE_WHEEL_REWARD_RATE[i])
			{
				eqid = MULTIPLE_WHEEL_REWARD_ID[i];
				count = MULTIPLE_WHEEL_REWARD_COUNT[i];

				result["reward"][0u]["eq"] = i;
				result["reward"][0u]["id"] = eqid;
				break;
			}
		}

		random = Math::GetRandomInt(1000);
		for (unsigned i = 0; i < MULTIPLE_WHEEL_MULTIPLE_NUM; ++i)
		{
			if (random < MULTIPLE_WHEEL_MULTIPLE_RATE[i])
			{
				count *= MULTIPLE_WHEEL_MULTIPLE[i];

				result["reward"][0u]["mu"] = i;
				result["reward"][0u]["cnt"] = count;
				break;
			}
		}

		ret = logicEquip.AddOneItem(uid, eqid, count, "MultipleWheel_Reward", result["equipment"], true);
		if (ret)
			return ret;

		newAct["cost"] = creditCost + 10;
	}
	else if (type == MultipleWheelType_Ten)
	{
		vector<ItemAdd> items;
		for (unsigned k = 0; k < 10; ++k)
		{
			unsigned eqid = 0;
			unsigned count = 0;
			unsigned random = Math::GetRandomInt(100);
			for (unsigned i = 0; i < MULTIPLE_WHEEL_REWARD_NUM; ++i)
			{
				if (random < MULTIPLE_WHEEL_REWARD_RATE[i])
				{
					eqid = MULTIPLE_WHEEL_REWARD_ID[i];
					count = MULTIPLE_WHEEL_REWARD_COUNT[i];

					result["reward"][k]["eq"] = i;
					result["reward"][k]["id"] = eqid;
					break;
				}
			}

			random = Math::GetRandomInt(1000);
			for (unsigned i = 0; i < MULTIPLE_WHEEL_MULTIPLE_NUM; ++i)
			{
				if (random < MULTIPLE_WHEEL_MULTIPLE_RATE[i])
				{
					count *= MULTIPLE_WHEEL_MULTIPLE[i];

					result["reward"][k]["mu"] = i;
					result["reward"][k]["cnt"] = count;
					break;
				}
			}

			ItemAdd item;
			item.eqid = eqid;
			item.count = count;
			item.reason = "MultipleWheel_Reward";
			items.push_back(item);
		}

		ret = logicEquip.AddItems(uid, items, result["equipment"], true);
		if (ret)
			return ret;

		newAct["cost"] = creditCost + 100;
	}

	result["newAct"] = Json::Value(Json::arrayValue);
	result["newAct"].append(newAct);

	ret = Secinc.SetOneSecinc(uid, newAct);
	if(ret)
		return ret;

	ret = logicUser.SetUser(uid, dataUser);
	if(ret)
		return ret;

	return R_SUCCESS;
}

int CLogicCMD::UpgradeGem(unsigned uid, unsigned equd, Json::Value &result, unsigned lasttime, unsigned seqid)
{
#ifdef SG_16_VER
	const int UP_GEM_COST[10] = {0,20,60,180,540,1620,4860,14580,43740,131220};
#else
	const int UP_GEM_COST[10] = {0,6,24,90,360,1440,5760,23040,92160,368640};
#endif
	int ret = 0;
	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	ret = logicUser.GetUser(uid,dataUser);
	if(ret)
	{
		error_log(" get user info failed,uid = %u",uid);
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

	Json::Value gem;
	CLogicEquipment logicEquipment;
	ret = logicEquipment.Get(uid, equd, gem);
	if(ret)
		return ret;
	int id = 0, l = 0, cost = 0;
	Json::GetInt(gem, "id", id);
	l = id % 10;
	if(!IS_GEM_EQID(id) || l == 0)
		return R_ERR_LOGIC;

	cost = -UP_GEM_COST[l];
	++id;
	gem["id"] = id;

	CLogicPay logicPay;
	DataPay payData;
	ret = logicPay.ProcessOrderForBackend(uid, cost, 0, payData, "UPGRADE_GEM",user_flag,bsave);
	if(ret)
		return ret;
	result["pointpay"].resize(0);
	if(bsave)
	{
		result["pointpay"] = user_flag["user_pay"];
		dataUser.user_flag = writer.write(user_flag);
	}

	result["coins"] = payData.coins;
	result["coins2"] = payData.cash;

	ret = logicEquipment.Chg(uid, equd, gem);
	if(ret)
		return ret;

	result["gem"] = gem;
	string equipstr = writer.write(gem);
	EQUIPMENT_LOG("uid=%u,id=%u,eqid=%d,act=%s,chg=%d,count=%d,code=%s,data=%s",uid,equd,id,
			"UpgradeGem",0,0,"UpgradeGem",equipstr.c_str());

	ret = logicUser.SetUser(uid, dataUser);
	if(ret)
		return ret;

	return R_SUCCESS;
}

int CLogicCMD::UpgradeTenWeapon(unsigned uid, unsigned id, unsigned equd, unsigned times, unsigned count, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	if (id >= 10)
	{
		PARAM_ERROR_RETURN_MSG("id error!");
	}

	int ret = 0;
	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	ret = logicUser.GetUser(uid,dataUser);
	if(ret)
	{
		error_log(" get user info failed,uid = %u",uid);
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

	Json::Value tech;
	Json::Reader reader;
	Json::FastWriter writer;
	reader.parse(dataUser.user_tech, tech);

	if (!tech.isMember("tw") || !tech["tw"].isArray() || 10 != tech["tw"].size())
	{
		tech["tw"] = Json::Value(Json::arrayValue);
		for (unsigned i = 0; i < 10; ++i)
		{
			tech["tw"][i][0u] = 0; //经验
			tech["tw"][i][1u] = 0; //英雄ud
		}
	}

	if (times) // 每消耗100器魂，可以获得铸魂一次
	{
		unsigned now = Time::GetGlobalTime();
		const unsigned maxTimes = 10; //每天最多10次

		if (!tech.isMember("twts"))
		{
			tech["twts"] = Json::Value(Json::arrayValue);
			tech["twts"][0u] = 0;  // 消耗魂器所得铸魂次数
			tech["twts"][1u] = now; // 时间戳
		}

		unsigned ts = tech["twts"][1u].asUInt();
		if (CTime::IsDiffDay(ts, now))
		{
			tech["twts"][0u] = 0;  // 每天重置
			tech["twts"][1u] = now;
		}

		unsigned t = tech["twts"][0u].asUInt();
		if (t+times > maxTimes)
		{
			error_log("[to mamy times][uid=%u&times=%u]",uid,t+times);
			LOGIC_ERROR_RETURN_MSG("to many times");
		}

		if (!tech.isMember("godE") || !tech["godE"].isMember("qlE"))
		{
			error_log("[tech don't have godE][uid=%u]",uid);
			DATA_ERROR_RETURN_MSG("tech don't have godE");
		}
		unsigned qlE = tech["godE"]["qlE"][0u].asUInt();

		if (qlE < 100*times)
		{
			error_log("[don't have enought qlE][uid=%u&qlECost=%u&qlE=%u]",uid,100*times,qlE);
			LOGIC_ERROR_RETURN_MSG("don't have enought qlE");
		}

		tech["godE"]["qlE"][0u] = qlE - 100*times;
		tech["twts"][0u] = t + times;
	}

	if (count)
	{
		const unsigned eqid = 1909; //铸魂符id
		const unsigned limit_eqid = 2023;  //限级铸魂符

		unsigned cost_eqid = 0;

		CLogicEquipment logicEquip;
		Json::Value equip_data;
		logicEquip.Get(uid, equd, equip_data);

		//判断是否是限级铸魂符
		if (equip_data["id"].asUInt() == limit_eqid)
		{
			//根据经验，判断铸魂所在的阶层。注意，限级铸魂符用于三阶到五阶
			//todo 铸魂经验对应的阶层
			int zhuhun_class = GetZhuhunClass(tech["tw"][id][0u].asUInt());

			if (zhuhun_class < 3 || zhuhun_class > 5)
			{
				error_log("[zhu hun class condition not match. only 3-5], uid=%u,class=%d",uid, zhuhun_class);
				LOGIC_ERROR_RETURN_MSG("zhu_hun_class_mismatch");
			}

			cost_eqid = limit_eqid;
		}
		else
		{
			cost_eqid = eqid;
		}

		ret = logicEquip.UseEquipment(uid, cost_eqid, equd, count, "tenWeaponCost");
		if (ret)
			return ret;
		EQUIPMENT_LOG("uid=%u,id=%u,times=%u,count=%u,exp=%u,eqid=%d,equd=%u,act=%s,count=%d,code=%s",
				uid,id,times,count,exp,cost_eqid,equd,"UpgradeTenWeapon",count,"UpgradeTenWeapon");
	}

	unsigned exp = tech["tw"][id][0u].asUInt();
	exp += 100*(times+count);
	tech["tw"][id][0u] = exp;

	result["tw"] = tech["tw"];
	result["twts"] = tech["twts"];
	result["qlE"] = tech["godE"]["qlE"][0u].asUInt();

	dataUser.user_tech = writer.write(tech);
	ret = logicUser.SetUser(uid, dataUser);
	if (ret)
		return ret;

	return R_SUCCESS;
}

int CLogicCMD::GetZhuhunClass(unsigned exp)
{
	if (exp < zhu_hun_lvl_exp[0])
	{
		return 0;
	}

	int len = sizeof(zhu_hun_lvl_exp)/sizeof(int);
	int level = 0;

	for(int i = len - 1; i >= 0; --i)
	{
		if (exp >= zhu_hun_lvl_exp[i])
		{
			level = i+1;
			break;
		}
	}

	//返回阶层
	return ceil(level / static_cast<double>(10));
}

int CLogicCMD::initDouble11NewAct(Json::Value &newAct)
{
	for (unsigned i = 0; i < XMLDOUBLE_TYPE_NUM * XMLDOUBLE_PROP_NUM; ++i)
	{
		newAct["a"][i] = 0;
	}

	newAct["b"] = Time::GetGlobalTime();
	newAct["id"] = NAT_DOUBLE11;
	newAct["v"] = Config::GetIntValue(CONFIG_DOUBLE11_ALLSERVER_VER);

	return R_SUCCESS;
}


int CLogicCMD::deterDouble11TS(unsigned type)
{
	unsigned now = Time::GetGlobalTime();
	unsigned bts = CTime::GetDayBeginTime(now);

	static const unsigned startts[XMLDOUBLE_TYPE_NUM + 1] = {
			9 * 3600 + 1800 - 60,			// 9:30
			11 * 3600 + 1800 - 60,			// 11:30
			14 * 3600 + 1800 - 60,			// 14:30
			16 * 3600 + 1800 - 60,			// 16:30
			18 * 3600 + 1800 - 60,			// 18:30
			20 * 3600 + 1800 - 60,			// 20:30
			22 * 3600 + 1800 - 60,			// 22:30	endts
	};

	if (now < Config::GetIntValue(CONFIG_DOUBLE11_ALLSERVER_BEGIN_TS)
	|| now > Config::GetIntValue(CONFIG_DOUBLE11_ALLSERVER_END_TS)
	|| (now < (bts + startts[type]))
	|| (now > (bts + startts[XMLDOUBLE_TYPE_NUM])))
	{
		LOGIC_ERROR_RETURN_MSG("time_is_error");
	}

	return R_SUCCESS;
}


int CLogicCMD::Double11(unsigned uid, unsigned type, unsigned id, Json::Value &result, unsigned lasttime, unsigned seqid)
{

	if (type >= XMLDOUBLE_TYPE_NUM || id >= XMLDOUBLE_PROP_NUM)
	{
		error_log("type or id error. uid = %u, type = %u, id = %u", uid, type, id);
		LOGIC_ERROR_RETURN_MSG("type or id error");
	}

	int ret = deterDouble11TS(type);
	if (ret)
	{
		return ret;
	}

	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	ret = logicUser.GetUser(uid, dataUser);
	if (ret)
	{
		error_log("[get_user_info_failed] [uid = %u, ret = %d]", uid, ret);
		return ret;
	}

	ret = checkLastSaveUID(dataUser);
	if (ret)
	{
		return ret;
	}

	ret = checkLastSaveTime(dataUser, lasttime, seqid);
	if (ret)
	{
		return ret;
	}

	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	CLogicSecinc logicSec;
	Json::Value newAct;

	ret = logicSec.GetSecinc(uid, NAT_DOUBLE11, newAct);
	if (R_ERR_NO_DATA == ret)
	{
		initDouble11NewAct(newAct);
	}
	else if (ret)
	{
		return ret;
	}

	if (newAct["v"].asInt() != Config::GetIntValue(CONFIG_DOUBLE11_ALLSERVER_VER)
	|| CTime::IsDiffDay(newAct["b"].asUInt(), Time::GetGlobalTime()))
	{
		newAct.clear();
		initDouble11NewAct(newAct);
	}

	CLogicDouble11 logicDouble;
	XMLDouble11Prop prop;
	bool nocnt;

	ret = logicDouble.BuyOneProp(type, id, prop, nocnt);
	if (ret)
	{
		return ret;
	}

	Json::Value rcnt(Json::arrayValue);
	ret = logicDouble.GetRemainCount(rcnt);
	if (ret)
	{
		return ret;
	}

	if (false == nocnt)
	{
		unsigned index = type * XMLDOUBLE_TYPE_NUM + id;
		unsigned count = newAct["a"][index].asUInt();
		// 每人每个物品只能购买一次
		static const unsigned limit = 1;

		if (count >= limit)
		{
			LOGIC_ERROR_RETURN_MSG("over limit");
		}

		++count;
		newAct["a"][index] = count;

		CLogicEquipment logicEquip;

		ret = logicEquip.AddOneItem(uid, prop.eqid, prop.eqcnt, "Double11", result["equip"], true);
		if (ret)
		{
			return ret;
		}

		Json::Value user_flag;
		Json::Reader reader;
		Json::FastWriter writer;

		reader.parse(dataUser.user_flag, user_flag);

		CLogicPay logicPay;
		DataPay dataPay;
		bool bsave;

		ret = logicPay.ProcessOrderForBackend(uid, -prop.price, 0, dataPay, "Double11", user_flag, bsave);
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
	}

	result["newAct"] = newAct;
	result["rcnt"] = rcnt;
	result["nocnt"] = nocnt;

	ret = logicSec.SetOneSecinc(uid, newAct);
	if (ret)
	{
		return ret;
	}

	ret = logicUser.SetUser(uid, dataUser);
	if (ret)
	{
		return ret;
	}

	return R_SUCCESS;
}


int CLogicCMD::GetDouble11Rcnt(unsigned uid, Json::Value &result, unsigned lasttime, unsigned seqid)
{

	unsigned now = Time::GetGlobalTime();
	if (now < Config::GetIntValue(CONFIG_DOUBLE11_ALLSERVER_BEGIN_TS)
	|| now > Config::GetIntValue(CONFIG_DOUBLE11_ALLSERVER_END_TS))
	{
		LOGIC_ERROR_RETURN_MSG("time_is_error");
	}

	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	int ret = logicUser.GetUserLimit(uid, dataUser);
	if (ret)
	{
		error_log("[get_user_info_failed] [uid = %u, ret = %d]", uid, ret);
		return ret;
	}

	ret = checkLastSaveUID(dataUser);
	if (ret)
	{
		return ret;
	}

	ret = checkLastSaveTime(dataUser, lasttime, seqid);
	if (ret)
	{
		return ret;
	}

	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	Json::Value rcnt(Json::arrayValue);
	CLogicDouble11 logicDouble;

	ret = logicDouble.GetRemainCount(rcnt);
	if (ret)
	{
		return ret;
	}

	result["rcnt"] = rcnt;

	ret = logicUser.SetUserLimit(uid, dataUser);
	if (ret)
	{
		return ret;
	}

	return R_SUCCESS;
}

int CLogicCMD::Sell(unsigned uid, const Json::Value &data, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	unsigned isbs = 1;
	Json::GetUInt(data, "bs", isbs);
	if(!data.isMember("sell") || !data["sell"].isArray())
		return R_ERR_PARAM;
	vector<pair<unsigned, unsigned> > objs;
	for(unsigned i=0;i<data["sell"].size();++i)
		objs.push_back(pair<unsigned, unsigned>(data["sell"][i][0u].asUInt(), data["sell"][i][1u].asUInt()));

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

	CLogicEquipment logicEquipment;
	Json::FastWriter writer;
	unsigned bs = 0;
	for(unsigned i=0;i<objs.size();++i)
	{
		Json::Value eq;
		ret = logicEquipment.Get(uid, objs[i].first, eq);
		if(ret)
			return ret;

		string logtype;
		unsigned id = eq["id"].asUInt();
		unsigned count = eq["count"].asUInt();
		if(IS_UN_OVERLAY_ID(id))
		{
			ret = logicEquipment.Del(uid, objs[i].first);
			if(ret)
				return ret;
			logtype = "del";
			++bs;
		}
		else
		{
			if(count < objs[i].second)
				return R_ERR_LOGIC;
			else if(count == objs[i].second)
			{
				ret = logicEquipment.Del(uid, objs[i].first);
				if(ret)
					return ret;
				logtype = "del";
			}
			else
			{
				count -= objs[i].second;
				eq["count"] = count;
				ret = logicEquipment.Chg(uid, objs[i].first, eq);
				if(ret)
					return ret;
				logtype = "use";
			}
			bs += objs[i].second;
		}

		string equipData = writer.write(data);
		EQUIPMENT_LOG("uid=%u,id=%u,eqid=%d,act=%s,chg=%d,count=%d,code=sell,data=%s",uid,objs[i].first,id,
						logtype.c_str(),-objs[i].second,count,equipData.c_str());
	}

	bs *= 10;
	if(isbs)
	{
		dataUser.battle_spirits += bs;
		RESOURCE_LOG("[Sell][uid=%u,chgbs=%u,bs=%u]", uid, bs, dataUser.battle_spirits);
	}

	ret = logicUser.SetUserLimit(uid, dataUser);
	if(ret)
		return ret;

	return R_SUCCESS;
}


int CLogicCMD::getHitEggNewAct(unsigned uid, Json::Value &newAct, bool &isfirst)
{
	CLogicSecinc logicSec;

	int ret = logicSec.GetSecinc(uid, NAT_EGG, newAct);
	if (R_ERR_NO_DATA == ret)
	{
		ret = initHitEggNewAct(newAct, 1);
		if (ret)
		{
			return ret;
		}

		isfirst = true;
	}
	else if (ret)
	{
		return ret;
	}

	if (Config::GetIntValue(CONFIG_HITEGG_VER) != newAct["v"].asUInt())
	{
		ret = initHitEggNewAct(newAct, 1);
		if (ret)
		{
			return ret;
		}

		isfirst = true;
	}

	return R_SUCCESS;
}


int CLogicCMD::getHitEggEquip(Json::Value &newAct, unsigned lock)
{
	CDataXML *dataxml = CDataXML::GetCDataXML();
	if (NULL == dataxml)
	{
		return R_ERR_DB;
	}

	vector<EggRewardItem> items;
	int ret = dataxml->GetEggItems(lock, newAct, items);
	if (ret)
	{
		return ret;
	}

	if (2 == lock)
	{
		for (unsigned i = 0; i < items.size() && i < lock; ++i)
		{
			newAct["eq"][i] = items[i].eqid;
			newAct["c"][i] = items[i].count;
			newAct["h"][i] = items[i].warn;
		}
	}
	else if (lock < 2)
	{
		if (!items.empty())
		{
			newAct["eq"][lock] = items[0].eqid;
			newAct["c"][lock] = items[0].count;
			newAct["h"][lock] = items[0].warn;
		}
	}

	return R_SUCCESS;
}


int CLogicCMD::refreshHitEggNewAct(Json::Value &newAct, unsigned lock)
{
	int ret = 0;
	ret = initHitEggNewAct(newAct);
	if (ret)
	{
		return ret;
	}

	ret = getHitEggEquip(newAct, lock);
	if (ret)
	{
		return ret;
	}

	return ret;
}


int CLogicCMD::initHitEggNewAct(Json::Value &newAct, unsigned reset)
{
	int ret = 0;
	if (reset)
	{
		newAct.clear();
		newAct["id"] = NAT_EGG;
		newAct["v"] = Config::GetIntValue(CONFIG_HITEGG_VER);

		for (unsigned i = 0; i < HITEGG_EQNUM; ++i)
		{
			newAct["eq"][i] = "";
			newAct["d"][i] = 0;
			newAct["c"][i] = 0;
			newAct["h"][i] = 0;
		}
		ret = getHitEggEquip(newAct);
		if (ret)
		{
			return ret;
		}
	}

	vector<unsigned> ieq;

	for (unsigned i = 0; i < HITEGG_NUM; ++i)
	{
		newAct["l"][i] = HITEGG_OPEN;
		ieq.push_back(i);
	}

	random_shuffle(ieq.begin(), ieq.end());

	for (unsigned i = 0; i < HITEGG_EQNUM; ++i)
	{
		newAct["f"][i] = ieq[i];
	}

	// eq 已砸的次数
	newAct["g"] = 0;

	return R_SUCCESS;
}


int CLogicCMD::HitEgg(unsigned uid, unsigned type, unsigned index, unsigned equd, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	if(Time::GetGlobalTime() < Config::GetIntValue(CONFIG_HITEGG_BEGIN_TS)
	|| Time::GetGlobalTime() > Config::GetIntValue(CONFIG_HITEGG_END_TS))
	{
		LOGIC_ERROR_RETURN_MSG("activity time is error");
	}

	if ((type > HitEgg_RandomType) || (index >= HITEGG_NUM))
	{
		DATA_ERROR_RETURN_MSG("type greater 2 or index greater 8");
	}

	int ret = 0;
	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	ret = logicUser.GetUser(uid,dataUser);
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

	Json::Value user_flag;
	Json::Reader reader;
	Json::FastWriter writer;

	reader.parse(dataUser.user_flag, user_flag);

	Json::Value newAct;

	bool isfirst = false;
	ret = getHitEggNewAct(uid, newAct, isfirst);
	if (ret)
	{
		return ret;
	}

	vector<unsigned>ihit;

	if (HitEgg_OneType == type)
	{
		ihit.push_back(index);
		if (HITEGG_CLOSE == newAct["l"][index].asUInt())
		{
			LOGIC_ERROR_RETURN_MSG("index already close");
		}
	}
	else
	{
		for (unsigned i = 0; i < HITEGG_NUM; ++i)
		{
			if (HITEGG_OPEN == newAct["l"][i].asUInt())
			{
				ihit.push_back(i);
			}
		}

		// 随机
		if (HitEgg_RandomType == type)
		{
			random_shuffle(ihit.begin(), ihit.end());
		}
	}

	unsigned hcount = newAct["g"].asUInt();
	bool stop = false;
	int cost = 0;
	vector<unsigned>::iterator it = ihit.begin();

	string eqid;
	unsigned eqcount = 1;

	for (; (it != ihit.end() && hcount < HITEGG_EQNUM); ++it)
	{
		newAct["l"][*it] = HITEGG_CLOSE;
		cost += HITEGG_COST_NUM;
		result["list"].append(*it);

		for (unsigned i = 0; i < newAct["f"].size(); ++i)
		{
			if (newAct["f"][i].asUInt() == *it)
			{
				newAct["l"][*it] = HITEGG_REWARD;

				result["warn"] = newAct["h"][i];

				Json::GetUInt(newAct["c"], i, eqcount);
				eqid = newAct["eq"][i].asString();
				newAct["eq"][i] = "";
				++hcount;
				stop = true;
				break;
			}
		}

		if (stop)
		{
			break;
		}
	}

	if (HITEGG_EQNUM == hcount)
	{
		hcount = 0;
		// refresh
		ret = refreshHitEggNewAct(newAct);
		if (ret)
		{
			return ret;
		}
	}

	if (!eqid.empty())
	{
		if ('H' == eqid[0])
		{
			CLogicHero logicHero;

			ret = logicHero.AddOneHero(uid, eqid, "HitEgg", result["hero"]);
			if (ret)
			{
				return ret;
			}
		}
		else
		{
			CLogicEquipment logicEquip;

			ret = logicEquip.AddOneItem(uid, CTrans::STOI(eqid), eqcount, "HitEgg", result["equip"], true);
			if (ret)
			{
				return ret;
			}
		}
	}

	CLogicPay logicPay;
	DataPay pay;

	string reason = "HitEgg_" + CTrans::ITOS(type);
	bool bsave = false;
#ifdef SG_USE_CASH
	ret = logicPay.ProcessOrderForBackend(uid, -cost, 0, pay, reason, user_flag, bsave);
	result["cash"] = pay.cash;
	result["coins"] = pay.coins;
#else
	CLogicEquipment equipment;
	const int purple_key_eqid = 2024;
	//花费钻石与花费道具数量的比例是100:20 即5:1
	int equip_cost = cost/5;
	ret = equipment.UseEquipment(uid, purple_key_eqid, equd, equip_cost, reason);

	result["equip_cost"] = equip_cost;
#endif

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

	newAct["g"] = hcount;
	result["newAct"] = newAct;
	result["newAct"].removeMember("f");

	CLogicSecinc logicSec;
	ret = logicSec.SetOneSecinc(uid, newAct);
	if (ret)
	{
		return ret;
	}

	ret = logicUser.SetUser(uid, dataUser);
	if (ret)
	{
		return ret;
	}

	return R_SUCCESS;
}


int CLogicCMD::RefreshHitEgg(unsigned uid, unsigned lock, unsigned equd, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	if(Time::GetGlobalTime() < Config::GetIntValue(CONFIG_HITEGG_BEGIN_TS)
	|| Time::GetGlobalTime() > Config::GetIntValue(CONFIG_HITEGG_END_TS))
	{
		LOGIC_ERROR_RETURN_MSG("activity time is error");
	}

	int ret = 0;
	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	ret = logicUser.GetUser(uid,dataUser);
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

	Json::Value user_flag;
	Json::Reader reader;
	Json::FastWriter writer;

	reader.parse(dataUser.user_flag, user_flag);

	Json::Value newAct;

	bool isfirst = false;
	ret = getHitEggNewAct(uid, newAct, isfirst);
	if (ret)
	{
		return ret;
	}

	ret = refreshHitEggNewAct(newAct, lock);
	if (ret)
	{
		return ret;
	}

	CLogicPay logicPay;
	DataPay pay;

	bool bsave = false;

	string reason = "RefreshHitEgg_" + CTrans::UTOS(lock);

	// 默认扣20
	int cash = -20;

	if (isfirst)
	{
		cash = 0;
	}

#ifdef SG_USE_CASH
	ret = logicPay.ProcessOrderForBackend(uid, cash, 0, pay, reason, user_flag, bsave);
	result["cash"] = pay.cash;
	result["coins"] = pay.coins;
#else
	CLogicEquipment equipment;
	const int purple_refresh_eqid = refresh_key;
	//花费紫色刷新符2枚
	int equip_cost = 2;

	if (isfirst)
	{
		equip_cost = 0;
	}

	ret = equipment.UseEquipment(uid, purple_refresh_eqid, equd, equip_cost, reason);
#endif

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

	result["newAct"] = newAct;
	result["newAct"].removeMember("f");

	CLogicSecinc logicSec;
	ret = logicSec.SetOneSecinc(uid, newAct);
	if (ret)
	{
		return ret;
	}

	ret = logicUser.SetUser(uid, dataUser);
	if (ret)
	{
		return ret;
	}

	return R_SUCCESS;
}


int CLogicCMD::initBetShopNewAct(Json::Value &newAct, bool reset)
{
	if (reset)
	{
		newAct.clear();
		newAct["v"] = BETSHOP_VERSION;
		newAct["id"] = NAT_CAIHUA;
	}

	for (unsigned i = 0; i < XMLBETSHOP_ITEMNUM; ++i)
	{
		newAct["a"][i] = 0;
	}
	newAct["b"] = Time::GetGlobalTime();

	return R_SUCCESS;
}


int CLogicCMD::getBetShopNewAct(unsigned uid, Json::Value &newAct)
{
	CLogicSecinc logicSec;

	int ret = logicSec.GetSecinc(uid, NAT_CAIHUA, newAct);
	if (R_ERR_NO_DATA == ret)
	{
		initBetShopNewAct(newAct);
	}
	else if (ret)
	{
		return ret;
	}

	if (newAct["v"].asUInt() != BETSHOP_VERSION)
	{
		initBetShopNewAct(newAct);
	}

	unsigned now = Time::GetGlobalTime();

	if (CTime::IsDiffDay(now, newAct["b"].asUInt()))
	{
		initBetShopNewAct(newAct, false);
	}

	return R_SUCCESS;
}


int CLogicCMD::BetShop(unsigned uid, unsigned index, unsigned eqid, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	if (index >= XMLBETSHOP_ITEMNUM)
	{
		DATA_ERROR_RETURN_MSG("index over limit");
	}

	int ret = 0;
	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	ret = logicUser.GetUser(uid,dataUser);
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

	Json::Value newAct;

	ret = getBetShopNewAct(uid, newAct);
	if (ret)
	{
		return ret;
	}

	XMLBetShopItem item;

	CDataXML *dataxml = CDataXML::GetCDataXML();
	if (NULL == dataxml)
	{
		return R_ERR_DB;
	}

	ret = dataxml->GetBetShopItem(eqid, item);
	if (ret)
	{
		return ret;
	}

	unsigned times = newAct["a"][index].asUInt();

	if (times >= item.times)
	{
		LOGIC_ERROR_RETURN_MSG("Over times limit");
	}

	++times;

	unsigned balance = 0;
	ret = logicUser.ChangeBetForBack(uid, -item.cost, dataUser.user_stat, balance);
	if (ret)
	{
		return ret;
	}

	if (eqid)
	{
		CLogicEquipment logicEquip;

		ret = logicEquip.AddOneItem(uid, eqid, item.c, "BetShop", result["equip"], true);
		if (ret)
		{
			return ret;
		}
	}
	else
	{
		Json::Value user_flag;
		Json::Reader reader;
		Json::FastWriter writer;

		reader.parse(dataUser.user_flag, user_flag);

		CLogicPay logicPay;
		DataPay pay;
		bool bsave = false;

		ret = logicPay.ProcessOrderForBackend(uid, 0, item.c, pay, "BetShop", user_flag, bsave);
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

		result["coins"] = pay.coins;
		result["coins2"] = pay.cash;
	}

	newAct["a"][index] = times;
	result["newAct"] = newAct;
	result["bet"] = balance;

	CLogicSecinc logicSec;

	ret = logicSec.SetOneSecinc(uid, newAct);
	if (ret)
	{
		return ret;
	}

	ret = logicUser.SetUser(uid, dataUser);
	if (ret)
	{
		return ret;
	}

	return R_SUCCESS;
}


int CLogicCMD::initGetMedalNewAct(unsigned type, Json::Value &newAct, bool reset)
{
	if (reset)
	{
		newAct.clear();
		newAct["id"] = type?NAT_GVG_4:NAT_MEDAL;
		newAct["v"] = GETMEDAL_VERSION;
	}

	for (unsigned i = 0; i < GETMEDAL_NUM; ++i)
	{
		newAct["a"][i] = 0;
	}
	newAct["b"] = Time::GetGlobalTime();

	return R_SUCCESS;
}

int CLogicCMD::initGetNewWorldKillNewAct(Json::Value &newAct, bool reset)
{
	if (reset)
	{
		newAct.clear();
		newAct["id"] = NAT_NEWWORLD_KILL_REWARDS;
		newAct["v"] = NEWWORLD_KILL_VERSION;
	}
	unsigned i = 0;
	for (; i < NEWWORLD_KILL_NUM; ++i)
	{
		newAct["a"][i] = 0;
	}

	newAct["b"] = Time::GetGlobalTime();

	return R_SUCCESS;
}

int CLogicCMD::GetMedal(unsigned uid, unsigned type, unsigned index, Json::Value &result, unsigned lasttime, unsigned seqid)
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

	// 1. newAct["a"] 保存已领取次数
	// 2. newAct["b"] 上次领取ts
	// 3. check newAct["a"][index] 是否已领取
	// 4. 获取勋章

	CLogicSecinc logicSec;
	Json::Value newAct;

	ret = logicSec.GetSecinc(uid, type?NAT_GVG_4:NAT_MEDAL, newAct);
	if (R_ERR_NO_DATA == ret)
	{
		initGetMedalNewAct(type, newAct);
	}
	else if (ret)
	{
		return ret;
	}

	if (GETMEDAL_VERSION != newAct["v"].asUInt())
	{
		initGetMedalNewAct(type, newAct);
	}

	unsigned now = Time::GetGlobalTime();
	unsigned lastts = newAct["b"].asUInt();

	if (lastts > now)
	{
		lastts = now;
		initGetMedalNewAct(type, newAct, false);
	}

	// 每天22:15 重置
	unsigned bts = CTime::GetDayBeginTime(lastts) + (22 * 60 * 60 + 15 * 60);
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
		initGetMedalNewAct(type, newAct, false);
	}

	// 每日领取一次
	static const unsigned limit = 1;
	unsigned acount = newAct["a"][index].asUInt();

	if (acount >= limit)
	{
		LOGIC_ERROR_RETURN_MSG("over getmedal limit");
	}

	// 必须先把前面的领完
	unsigned i;
	for (i = 0; i < index; ++i)
	{
		if (limit > newAct["a"][i].asUInt())
		{
			break;
		}
	}

	if (i < index)
	{
		LOGIC_ERROR_RETURN_MSG("must get front medal");
	}

	++acount;

	static const unsigned eqcnt[GETMEDAL_NUM] = {10, 10, 10, 10, 10};
	static const unsigned eqid = NEW_WORLD_KILL_REWARD_NEW;			// 国战勋章

	CLogicEquipment logicEquip;
#ifdef SG_16_VER
	vector<ItemAdd> items;
	string reason_add = type?"GetMedal_GVG":"GetMedal_World";
	ItemAdd temp_item1(eqid, eqcnt[index], reason_add);
	items.push_back(temp_item1);
	ItemAdd temp_item2(51001+Math::GetRandomInt(4), 2, reason_add);
	items.push_back(temp_item2);
	ret = logicEquip.AddItems(uid,items,result["equip"], true);
#else
	ret = logicEquip.AddOneItem(uid, eqid, eqcnt[index], type?"GetMedal_GVG":"GetMedal_World", result["equip"], true);
#endif
	if (ret)
	{
		return ret;
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

int CLogicCMD::BuyQiRi(unsigned uid, unsigned index, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	static const int diamond[3] = {-500, -2000, -5000};
	if (index == 0 || index > 3)
		return R_ERR_PARAM;

	int ret = 0;
	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	ret = logicUser.GetUser(uid,dataUser);
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

	CLogicUserData logicUserData;
	DataUserData data;
	ret = logicUserData.GetUserData(uid, data);
	if (ret)
		return ret;
	Json::Value gift;
	Json::FromString(gift, data.gift);
	Json::Value qiri;
	Json::GetObjectOrArray(gift, "qiri", qiri);

	unsigned buy = 0;
	Json::GetUInt(qiri, "buy", buy);
	if (buy)
	{
		error_log("[buy qiri before][uid=%u&index=%u]", uid, index);
		LOGIC_ERROR_RETURN_MSG("buy qiri before");
	}

	Json::Value user_flag;
	Json::FromString(user_flag, dataUser.user_flag);

	bool bsave = false;
	CLogicPay logicPay;
	DataPay payData;
	ret = logicPay.ProcessOrderForBackend(uid, diamond[index-1], 0, payData, "qiri_"+CTrans::UTOS(index), user_flag, bsave);
	if(ret)
		return ret;
	result["pointpay"].resize(0);
	if(bsave)
	{
		result["pointpay"] = user_flag["user_pay"];
		dataUser.user_flag = Json::ToString(user_flag);
	}
	result["coins"] = payData.coins;
	result["coins2"] = payData.cash;

	qiri["buy"] = index;
	qiri["buyTs"] = Time::GetGlobalTime();
	qiri["gets"] = Json::Value(Json::arrayValue);
	for (unsigned i = 0; i < 7; ++i)
		qiri["gets"][i] = 0;

	gift["qiri"] = qiri;
	result["qiri"] = qiri;
	ret = logicUserData.SetGift(uid, gift);
	if (ret)
		return ret;

	ret = logicUser.SetUser(uid, dataUser);
	if (ret)
		return ret;

	return R_SUCCESS;
}

int CLogicCMD::GetQiRi(unsigned uid, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	static const int cashAdd[3][7] =
	{
			{150,50,50,50,50,50,100},
			{600,200,200,200,200,200,400},
			{1500,500,500,500,500,500,1000}
	};
	static const int coinsAdd[3][7] =
	{
			{30,10,10,10,10,10,20},
			{180,60,60,60,60,60,120},
			{750,250,250,250,250,250,500}
	};
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

	CLogicUserData logicUserData;
	DataUserData data;
	ret = logicUserData.GetUserData(uid, data);
	if (ret)
		return ret;
	Json::Value gift;
	Json::FromString(gift, data.gift);
	Json::Value qiri;
	Json::GetObjectOrArray(gift, "qiri", qiri);

	unsigned buy = 0;
	unsigned buyTs = 0;
	Json::GetUInt(qiri, "buy", buy);
	Json::GetUInt(qiri, "buyTs", buyTs);
	if (!buy || !buyTs)
	{
		error_log("[no buy][uid=%u]", uid);
		LOGIC_ERROR_RETURN_MSG("no buy");
	}
	if (buy > 3)
	{
		error_log("[buy error][uid=%u&buy=%u]",uid, buy);
		DATA_ERROR_RETURN_MSG("buy error");
	}

	if (!qiri.isMember("gets") || !qiri["gets"].isArray() || qiri["gets"].size() != 7)
	{
		qiri["gets"] = Json::Value(Json::arrayValue);
		for (unsigned i = 0; i < 7; ++i)
			qiri["gets"][i] = 0;
	}
	int day = CTime::GetDayInterval(buyTs, Time::GetGlobalTime());
	if (day < 0)
		return R_ERR_DATA;
	day = (day <= 6)?day:6;
	if (qiri["gets"][day].asUInt())
	{
		error_log("[get qiri before][uid=%u&buy=%u&day=%u]",uid, buy, day);
		LOGIC_ERROR_RETURN_MSG("get qiri before");
	}

	int cash = 0;
	int coins = 0;
	for (unsigned i = 0; i < day+1; ++i)
	{
		if (!qiri["gets"][i].asUInt())
		{
			cash += cashAdd[buy-1][i];
			coins += coinsAdd[buy-1][i];
			qiri["gets"][i] = 1;
		}
	}
	CLogicPay logicPay;
	DataPay   dataPay;
	ret = logicPay.ChangePay(uid, cash, coins, "qiri", dataPay);
	if (ret)
		return ret;
	result["coins"] = dataPay.coins;
	result["coins2"] = dataPay.cash;

	result["qiri"] = qiri;
	gift["qiri"] = qiri;
	ret = logicUserData.SetGift(uid, gift);
	if (ret)
		return ret;

	ret = logicUser.SetUserLimit(uid, dataUser);
	if (ret)
		return ret;

	return R_SUCCESS;
}

int CLogicCMD::GetGiftBagLvl(unsigned uid, unsigned id, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	if (id == 0 || id > GIFT_BAG_LEVEL_COUNT)
		return R_ERR_PARAM;

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

	CDataXML *pData = CDataXML::GetCDataXML();
	if (NULL == pData)
	{
		error_log("GetInitXML fail");
		return R_ERR_DB;
	}
	XMLGifgBagLvl item;
	ret = pData->GetGiftBagLevel(id, item);
	if (ret)
		return ret;
	if (dataUser.level < item.level)
	{
		error_log("[level error][uid=%u&id=%u_%u&userLevel=%u&level=%u]",uid,id,item.id,dataUser.level,item.level);
		LOGIC_ERROR_RETURN_MSG("evel error");
	}

	CLogicUserData logicUserData;
	DataUserData data;
	ret = logicUserData.GetUserData(uid, data);
	if (ret)
		return ret;
	Json::Value gift;
	Json::FromString(gift, data.gift);
	Json::Value level;
	Json::GetObjectOrArray(gift, "level", level);
	if (!level.isArray() || level.size() != GIFT_BAG_LEVEL_COUNT)
	{
		level = Json::Value(Json::arrayValue);
		for(unsigned i = 0; i < GIFT_BAG_LEVEL_COUNT; ++i)
			level[i] = 0;
	}
	unsigned flag = 0;
	Json::GetUInt(level, id-1, flag);
	if (flag)
	{
		error_log("[get level reward before][uid=%u&id=%u]",uid,id);
		DATA_ERROR_RETURN_MSG("get level reward before");
	}
	level[id-1] = 1;

	Json::Value reward;
	XMLQuestReward questReward;
	Json::Value equipData;
	vector<string> hero;
	Json::FromString(reward, item.data);
	parseQuestReward(reward["reward"], questReward, equipData, hero, "giftBagLevel");
	if (questReward.gol || questReward.cas)
	{
		CLogicPay logicPay;
		DataPay dataPay;
		bool bSave = false;
		ret = logicPay.ChangePay(uid, questReward.cas, questReward.gol,"giftBagLevel", dataPay);
		if (ret)
			return ret;
		result["coins"] = dataPay.coins;
		result["coins2"] = dataPay.cash;
	}
	if (!equipData.empty())
	{
		CLogicEquipment logicEquip;
		ret = logicEquip.UpdateEquipment(uid, 0, equipData, result["equipment"]);
		if (ret)
			return ret;
	}

	result["level"] = level;
	gift["level"] = level;
	ret = logicUserData.SetGift(uid, gift);
	if (ret)
		return ret;

	ret = logicUser.SetUserLimit(uid, dataUser);
	if (ret)
		return ret;

	return R_SUCCESS;
}




int CLogicCMD::FirstRechargeReward(unsigned uid,  Json::Value &result, unsigned lasttime, unsigned seqid)
{
	int ret = 0;
	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	ret = logicUser.GetUserLimit(uid,dataUser);
	if(ret)
	{
		error_log("get_user_info_failed,uid = %u",uid);
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


	//因为配置基本上不会变了，所以直接写死在代码里了
	//1.是否充值过钱了
	if (dataUser.accCharge < 100)
	{
		error_log("accCharge is not enough,uid = %u",uid);
		return R_ERR_LOGIC;
	}

	//2.是否领取过了
	CLogicUserData logicUserData;
	DataUserData userData;
	ret = logicUserData.GetUserData(uid, userData);
	if (ret)
		return ret;
	Json::Value gift;
	Json::FromString(gift, userData.gift);
	if (gift["charge"]["reward"].asBool())
	{
		error_log("have get first recharge reward,uid = %u",uid);
		return R_ERR_LOGIC;
	}
	result["reward"] = 0;

	//3. 档里加装备, 加英雄，改领取标志
	//"equip1":{"id":100009,"c":1,"q":5,"ch":4},
	//"equip2":{"id":103009,"c":1,"q":5,"ch":4}
	//"equip3":{"id":103002,"c":1,"q":5,"ch":4},
	//"equip4":{"id":100002,"c":1,"q":5,"ch":4},
	//"equip5":{"id":4403,"c":1}
	//"hero":{"id":3008,"c":1,"q":0}
	CLogicEquipment logicEquipment;
	vector<ItemAdd> items;
	string reason_add = "FirstRechargeReward";
#ifdef SG_16_VER
	ItemAdd temp_item1(4022, 20, reason_add);
	items.push_back(temp_item1);
	ItemAdd temp_item2(4403, 1, reason_add);
	items.push_back(temp_item2);
	ItemAdd temp_item3(42015, 30, reason_add);
	items.push_back(temp_item3);
	ItemAdd temp_item4(110012, 1, reason_add, 4, 5);
	items.push_back(temp_item4);
	ItemAdd temp_item5(113012, 1, reason_add, 4, 5);
	items.push_back(temp_item5);
#else
	ItemAdd temp_item1(100009, 1, reason_add, 4, 5);
	items.push_back(temp_item1);
	ItemAdd temp_item2(103009, 1, reason_add, 4, 5);
	items.push_back(temp_item2);
	ItemAdd temp_item3(103002, 1, reason_add, 4, 5);
	items.push_back(temp_item3);
	ItemAdd temp_item4(100002, 1, reason_add, 4, 5);
	items.push_back(temp_item4);
	ItemAdd temp_item5(4403, 1, reason_add);
	items.push_back(temp_item5);
#endif
	ret = logicEquipment.AddItems(uid,items,result["equip"], true);
	if(ret)
	{
		error_log("Add equipments failed. uid = %u, ret = %d, reason = %s", uid, ret, reason_add.c_str());
		return ret;
	}

	CLogicHero  logicHero;
#ifdef SG_16_VER
	ret = logicHero.AddOneHero(uid, "H3211", reason_add, result["hero"]);
#else
	ret = logicHero.AddOneHero(uid, "H3008", reason_add, result["hero"]);
#endif
	if (ret)
	{
		error_log("AddOneHero failed. uid = %u, ret = %d, reason = %s", uid, ret, reason_add.c_str());
		return ret;
	}

	gift["charge"]["reward"] = 1;
	Json::FastWriter writer;
	userData.gift = writer.write(gift);
	ret = logicUserData.SetUserData(uid, userData);
	if (ret)
	{
		error_log("SetUserData failed. uid = %u, ret = %d, reason = %s", uid, ret, reason_add.c_str());
		return ret;
	}
	result["reward"] = 1;

	ret = logicUser.SetUserLimit(uid, dataUser);
	if (ret)
		return ret;

	return R_SUCCESS;
}


int CLogicCMD::GrowthFund(unsigned uid, bool is_buy, unsigned count, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	int ret = 0;
	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	ret = logicUser.GetUserLimit(uid,dataUser);
	if(ret)
	{
		error_log("get_user_info_failed,uid = %u",uid);
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

	//主城必须>=15
	int BdLvl = 0;
	Json::Value Bd;
	CLogicBuilding logicBd;
	ret = logicBd.Get(uid, 1, 0, true, Bd);
	if (ret == 0)
	{
		if (Bd.isMember("l") && Bd["l"].isIntegral())
		{
			BdLvl = Bd["l"].asInt();
		}
	}
	if (BdLvl < 15)
	{
		error_log("home town level is too small,uid = %u",uid);
		return R_ERR_LOGIC;
	}

	CLogicUserData logicUserData;
	DataUserData userData;
	ret = logicUserData.GetUserData(uid, userData);
	if (ret)
		return ret;
	Json::Value gift;
	Json::FromString(gift, userData.gift);

	// gift["fund"] 7个元素数组  [0,0,0,0,0,0,0]
	if (!gift.isMember("boughtfund"))
	{
		gift["boughtfund"] = 0;
	}
	int have_buy = gift["boughtfund"].asInt();
	if (!gift.isMember("fund"))
	{
		for (int ix = 0; ix != LEN_FUND; ++ix)
		{
			gift["fund"][(unsigned)ix] = 0;
		}
	}
	if (!gift["fund"].isArray() || gift["fund"].size() != LEN_FUND)
	{
		error_log("gift fund is error,uid = %u",uid);
		return R_ERR_DB;
	}

	//gift["fundlog"]不定长的数组   {"c":100,"c2":0,"count":2,"l":0,"ts":1458010162,"type":0}, type为0时候代表买
	int len_fund_log = 0;
	Json::Value gift_temp;
	//删除第一个元素，怕爆档
	if (gift.isMember("fundlog"))
	{
		len_fund_log = gift["fundlog"].size();
		if (len_fund_log > 10)
		{
			for (int ix = 1; ix != len_fund_log; ++ix)
			{
				gift_temp["fundlog"][unsigned(ix-1)] = gift["fundlog"][unsigned(ix)];
			}
			gift["fundlog"] = gift_temp["fundlog"];
		}
	}

	if (have_buy > TIMES_LIMIT_FUND_BUY)
	{
		error_log("can not buy fund more,uid = %u",uid);
		return R_ERR_LOGIC;
	}

	unsigned now = Time::GetGlobalTime();
	CLogicPay logicPay;
	DataPay payData;
	if (is_buy)
	{
		int can_buy_fund = TIMES_LIMIT_FUND_BUY - have_buy;
		if (count > can_buy_fund)
		{
			error_log("once buy more,uid = %u",uid);
			return R_ERR_LOGIC;
		}

		//增加fundlog
		int sum_cash_buy_fund = -(count * CASH_ONE_FUND);
		int sum_coins_buy_fund = -(count * COINS_ONE_FUND);
		int first_back_coins = -(sum_cash_buy_fund + sum_coins_buy_fund) * FIRST_BACK_COINS_RATE;
		have_buy += count;
		gift["fundlog"][unsigned(len_fund_log)]["c"] = first_back_coins;
		gift["fundlog"][unsigned(len_fund_log)]["c2"] = 0;
		gift["fundlog"][unsigned(len_fund_log)]["count"] = count;
		gift["fundlog"][unsigned(len_fund_log)]["l"] = 0;
		gift["fundlog"][unsigned(len_fund_log)]["ts"] = now;
		gift["fundlog"][unsigned(len_fund_log)]["type"] = 0;
		//扣钻石
		ret = logicPay.ChangePay(uid, sum_cash_buy_fund, sum_coins_buy_fund, "activity_jijin_buyfund1");
		if (ret != 0)
			return ret;
		//买的时候返还coins
		ret = logicPay.ChangePay(uid, 0, first_back_coins, "get_coin_buy_fund_first_return");
		if (ret != 0)
			return ret;
	}else //等级返还
	{
		bool level_matched = false;
		int find_pos = 0;
		for (int ix = 0; ix != LEN_FUND; ++ix)
		{
			if (LVL_FUND_BACK[ix] == dataUser.level)
			{
				if (gift["fund"][(unsigned)ix].asBool())
				{
					//已经领取过等级奖励
					error_log("can get back_fund_level once,uid = %u",uid);
					return R_ERR_LOGIC;
				}
				level_matched = true;
				find_pos = ix;
				break;
			}
		}
		if (!level_matched)
		{
			error_log("fund_back level is not match,uid = %u",uid);
			return R_ERR_LOGIC;
		}

		int coins_level_back = have_buy * CASH_ONE_FUND * COINS_FUND_BACK[find_pos]/100;
		int cash_level_back  = have_buy * CASH_ONE_FUND * CASH_FUND_BACK[find_pos]/100;
		//更改gift["fund"]
		gift["fund"][(unsigned)find_pos] = 1;
		//增加fundlog
		gift["fundlog"][unsigned(len_fund_log)]["c"] = coins_level_back;
		gift["fundlog"][unsigned(len_fund_log)]["c2"] = cash_level_back;
		gift["fundlog"][unsigned(len_fund_log)]["count"] = have_buy;
		gift["fundlog"][unsigned(len_fund_log)]["l"] = dataUser.level;
		gift["fundlog"][unsigned(len_fund_log)]["ts"] = now;
		gift["fundlog"][unsigned(len_fund_log)]["type"] = 1;
		//返还奖励
		ret = logicPay.ChangePay(uid, cash_level_back, coins_level_back, "get_coin_levelup_fund_reward");
		if (ret != 0)
			return ret;
	}
	result["fund"] = gift["fund"];
	result["fundlog"] = gift["fundlog"];
	ret = logicPay.GetPay(uid, payData);
	if (ret != 0)
		return ret;
	result["coins"] = payData.coins;
	result["coins2"] = payData.cash;
	result["boughtfund"] = have_buy;
	gift["boughtfund"] = have_buy;

	Json::FastWriter writer;
	userData.gift = writer.write(gift);
	ret = logicUserData.SetUserData(uid, userData);
	if (ret)
	{
		error_log("SetUserData failed. uid = %u, ret = %d, reason = %s", uid, ret, "GrowthFund");
		return ret;
	}

	ret = logicUser.SetUserLimit(uid, dataUser);
	if (ret)
		return ret;

	return R_SUCCESS;
}


int CLogicCMD::DeDaoZhenRenVisit(unsigned uid, Json::Value &result, unsigned seqid, unsigned lasttime)
{
	if(Time::GetGlobalTime() < Config::GetIntValue(CONFIG_DEDAOZHENREN_BEGIN_TS) ||
	   Time::GetGlobalTime() > Config::GetIntValue(CONFIG_DEDAOZHENREN_END_TS))
		return R_ERR_AUTH;

	AUTO_LOCK_USER(uid)
	int ret = 0;
	CLogicUser logicUser;
	DataUser dataUser;
	ret = logicUser.GetUser(uid,dataUser);
	if(ret)
	{
		error_log("get_user_info_failed,uid = %u",uid);
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

	//1.首先检查时间， ver, 对newAct进行重置， newAct里的存放格式是： {id:71, l:[1,0,0,0], t:100, ts:1462850687, ver:20160510}
	CLogicSecinc Secinc;
	Json::Value SecincData;
	ret = Secinc.GetSecinc(uid, NAT_DEDAO_ZHENREN, SecincData);
	if (R_ERR_NO_DATA == ret)
	{
		SecincData["id"] = NAT_DEDAO_ZHENREN;
		SecincData["l"][0u] = 1;
		SecincData["l"][1u] = 0;
		SecincData["l"][2u] = 0;
		SecincData["l"][3u] = 0;
		SecincData["t"] = 0;
		SecincData["ts"] = Time::GetGlobalTime();
		SecincData["ver"] = Config::GetIntValue(CONFIG_DEDAOZHENREN_VER);
	} else if (ret)
	{
		return ret;
	}
	if(!SecincData.isMember("id") ||
	   !SecincData.isMember("l")  || !SecincData["l"].isArray() || SecincData["l"].size() != DEDAOZHENREN_PERSON_NUM ||
	   !SecincData.isMember("t")  ||
	   !SecincData.isMember("ts") ||
	   !SecincData.isMember("ver"))
	{
		error_log("dedaozhenren data error, uid = %u",uid);
		return R_ERR_DATA;
	}

	if (!Time::IsToday(SecincData["ts"].asUInt()))
	{
		SecincData["l"][0u] = 1;
		SecincData["l"][1u] = 0;
		SecincData["l"][2u] = 0;
		SecincData["l"][3u] = 0;
		SecincData["t"] = 0;
	}
	if(SecincData["ver"].asInt() != Config::GetIntValue(CONFIG_DEDAOZHENREN_VER))
	{
		SecincData["ver"] = Config::GetIntValue(CONFIG_DEDAOZHENREN_VER);
	}

	//2.遍历l， l[0,1,0,0] 这种是错误的, 所以当有a[i]<a[i+1]时，报逻辑错误
	for (int ix = 0; ix != DEDAOZHENREN_PERSON_NUM-1; ++ix)
	{
		if (SecincData["l"][unsigned(ix)].asUInt() < SecincData["l"][unsigned(ix+1)].asUInt())
		{
			error_log("dedaozhenren data l is error, uid = %u",uid);
			return R_ERR_LOGIC;
		}
	}

	//3.检查1)newAct里面的l:[1,0,0,0] 第4个元素是否是 0，不然就是逻辑错误;  检查2) newAct里面的 t总次数到100时， 报逻辑错误
	if (SecincData["l"][3u].asUInt() || SecincData["t"].asUInt() >= DEDAOZHENREN_HUIFU_TIMES)
	{
		error_log("dedaozhenren can visit already or not buy more, uid = %u",uid);
		return R_ERR_LOGIC;
	}

	//4.检查钱是否够 600钻石
	Json::Reader reader;
	Json::FastWriter writer;
	Json::Value user_flag;
	reader.parse(dataUser.user_flag,user_flag);
	CLogicPay logicPay;
	DataPay payData;
	bool bsave = false;
	ret = logicPay.ProcessOrderForBackend(uid, -DEDAOZHENREN_VISIT_CASH, 0, payData, "activity_dedaozhenren_visit",user_flag,bsave);
	if(ret)
		return ret;
	result["pointpay"].resize(0);
	if(bsave)
	{
		result["pointpay"] = user_flag["user_pay"];
		dataUser.user_flag = writer.write(user_flag);
	}
	result["coins2"] = payData.cash;

	//5.处理过程： l:[1,0,0,0] ----> l:[1,1,1,1]
	SecincData["l"][1u] = 1;
	SecincData["l"][2u] = 1;
	SecincData["l"][3u] = 1;

	//6.最后扣钱， 改数据：  newAct里的 l, ts
	SecincData["ts"] = Time::GetGlobalTime();
	ret = Secinc.SetOneSecinc(uid, SecincData);
	if(ret)
		return ret;
	//7.前端返回数据, 返回newAct， 返回剩余的钻石数
	result["newAct"] = SecincData;

	ret = logicUser.SetUser(uid, dataUser);
	if (ret)
		return ret;
	return R_SUCCESS;
}


int CLogicCMD::DeDaoZhenRenDrawPicture(unsigned uid, unsigned person, unsigned equd, Json::Value &result, unsigned seqid, unsigned lasttime)
{
	if(Time::GetGlobalTime() < Config::GetIntValue(CONFIG_DEDAOZHENREN_BEGIN_TS) ||
	   Time::GetGlobalTime() > Config::GetIntValue(CONFIG_DEDAOZHENREN_END_TS))
		return R_ERR_AUTH;

	AUTO_LOCK_USER(uid)
	int ret = 0;
	CLogicUser logicUser;
	DataUser dataUser;
	ret = logicUser.GetUser(uid,dataUser);
	if(ret)
	{
		error_log("get_user_info_failed,uid = %u",uid);
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

	//1.  对newAct进行重置，newAct里的存放格式是： {id:71, l:[1,0,0,0], t:100, ts:1462850687, ver:20160510}
	CLogicSecinc Secinc;
	Json::Value SecincData;
	ret = Secinc.GetSecinc(uid, NAT_DEDAO_ZHENREN, SecincData);
	if (R_ERR_NO_DATA == ret)
	{
		SecincData["id"] = NAT_DEDAO_ZHENREN;
		SecincData["l"][0u] = 1;
		SecincData["l"][1u] = 0;
		SecincData["l"][2u] = 0;
		SecincData["l"][3u] = 0;
		SecincData["t"] = 0;
		SecincData["ts"] = Time::GetGlobalTime();
		SecincData["ver"] = Config::GetIntValue(CONFIG_DEDAOZHENREN_VER);
	} else if (ret)
	{
		return ret;
	}
	if(!SecincData.isMember("id") ||
	   !SecincData.isMember("l")  || !SecincData["l"].isArray() || SecincData["l"].size() != DEDAOZHENREN_PERSON_NUM ||
	   !SecincData.isMember("t")  ||
	   !SecincData.isMember("ts") ||
	   !SecincData.isMember("ver"))
	{
		error_log("dedaozhenren data error, uid = %u",uid);
		return R_ERR_DATA;
	}

	if (!Time::IsToday(SecincData["ts"].asUInt()))
	{
		SecincData["l"][0u] = 1;
		SecincData["l"][1u] = 0;
		SecincData["l"][2u] = 0;
		SecincData["l"][3u] = 0;
		SecincData["t"] = 0;
	}
	if(SecincData["ver"].asInt() != Config::GetIntValue(CONFIG_DEDAOZHENREN_VER))
	{
		SecincData["ver"] = Config::GetIntValue(CONFIG_DEDAOZHENREN_VER);
	}

	//2.  绘符的次数是否够了, 够了的话，逻辑错误
	if (SecincData["t"].asUInt() >= DEDAOZHENREN_HUIFU_TIMES)
	{
		error_log("dedaozhenren can not buy more, uid = %u",uid);
		return R_ERR_LOGIC;
	}

	//3.  l:[1,0,0,0]  遍历l， l[0,1,0,0] 这种是错误的, 所以当有a[i]<a[i+1]时，报逻辑错误
	for (int ix = 0; ix != DEDAOZHENREN_PERSON_NUM-1; ++ix)
	{
		if (SecincData["l"][unsigned(ix)].asUInt() < SecincData["l"][unsigned(ix+1)].asUInt())
		{
			error_log("dedaozhenren data l is error, uid = %u",uid);
			return R_ERR_LOGIC;
		}
	}

	//4.  l[person]  判断其是否为1， 如果不是，逻辑错误
	if (!SecincData["l"][person].asUInt())
	{
		error_log("dedaozhenren data l is error, uid=%u, person=%u", uid, person);
		return R_ERR_LOGIC;
	}

	//5.  判断钱是否够。
	Json::Reader reader;
	Json::FastWriter writer;
	Json::Value user_flag;
	reader.parse(dataUser.user_flag,user_flag);
	CLogicPay logicPay;
	DataPay payData;
	bool bsave = false;
	int need_cash = DEDAOZHENREN_HUIFU_CASH[person];
#ifdef SG_USE_CASH
	ret = logicPay.ProcessOrderForBackend(uid, -need_cash, 0, payData, "activity_dedaozhenren_huifu",user_flag,bsave);
	if(ret)
		return ret;
	result["pointpay"].resize(0);
	if(bsave)
	{
		result["pointpay"] = user_flag["user_pay"];
		dataUser.user_flag = writer.write(user_flag);
	}
	result["coins2"] = payData.cash;
#else
	ret = CLogicEquipment().UseEquipment(uid, purple_key, equd, need_cash/5, "DeDaoZhenRenDrawPicture");
	if(ret)
		return ret;
#endif

	//6.  读取配置， 计算应获得的铸魂符的 数目。  newAct里   l值的更改，t值的更改，ts的更改
	//7.  最后，扣钱，加装备， 写回newAct
	int rate_random = Math::GetRandomInt(100);
	int index_get = 0;
	for (; index_get != DEDAOZHENREN_PRODUCT_NUM_KINDS; ++index_get)
	{
		if (rate_random <= DEDAOZHENREN_HUIFU_RATE[person][index_get])
		{
			break;
		}
	}
	if (index_get >= DEDAOZHENREN_PRODUCT_NUM_KINDS)
	{
		error_log("dedaozhenren index_get is error, uid=%u, index_get=%d", uid, index_get);
		return R_ERR_DATA_LIMIT;
	}
	unsigned add_product_num = DEDAOZHENREN_HUIFU_PRODUCT_NUM[person][index_get];
	CLogicEquipment logicEquipment;
	ret = logicEquipment.AddOneItem(uid, ZHUHUNFU_ID, add_product_num,"dedaozhenren",result["equip"], true);
	if(ret)
		return ret;

	if (person < (DEDAOZHENREN_PERSON_NUM-1)  &&
	    !SecincData["l"][unsigned(person+1)].asUInt())  //实现解锁
	{
		int unlock_random = Math::GetRandomInt(100);
		if (unlock_random < DEDAOZHENREN_UNLOCK_RATE[person])
			SecincData["l"][unsigned(person+1)] = 1;
	}
	SecincData["t"] = SecincData["t"].asUInt() + 1;
	SecincData["ts"] = Time::GetGlobalTime();

	//8.  前端返回数据, 返回newAct， 返回剩余的钻石数, 铸魂符的数目也给前端
	ret = Secinc.SetOneSecinc(uid, SecincData);
	if(ret)
		return ret;
	result["newAct"] = SecincData;

	ret = logicUser.SetUser(uid, dataUser);
	if (ret)
		return ret;
	return R_SUCCESS;
}


int CLogicCMD::SignInReward(unsigned uid, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	int ret = 0;
	CLogicUser logicUser;
	DataUser dataUser;
	std::string userState;
	AUTO_LOCK_USER(uid)
	ret = logicUser.GetUserLimit(uid,dataUser);
	if(ret)
	{
		error_log(" get_user_info_failed,uid = %u",uid);
		return ret;
	}

	if ((ret = checkLastSaveUID(dataUser)) != R_SUCCESS)
	{
		return ret;
	}

	if ((ret = checkLastSaveTime(dataUser,lasttime,seqid)) != R_SUCCESS)
	{
		return ret;
	}

	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	Json::Reader reader;
	Json::Value jsonStats;
	if ((ret = logicUser.GetUserStat(uid, jsonStats)) != 0)
	{
		DB_ERROR_RETURN_MSG("get_user_stat failed");
	}

	Json::Value jsonDsNews;
	if (! Json::GetArray(jsonStats, "dsNew", jsonDsNews))
	{
		error_log("[SignInReward][parse_dsNew_fail.uid=%d]", uid);
		DB_ERROR_RETURN_MSG("parse_dsNew_fail");
	}

	//获取签到的第几天
	unsigned nowTime = Time::GetGlobalTime();
	unsigned monthBegin = CTime::GetMonthBeginTime(nowTime);
	int intervalDays = abs(CTime::GetDayInterval(monthBegin, nowTime));
	if (intervalDays >= (int)jsonDsNews.size())
	{
		error_log("[SignInReward][interval_day_over_config.uid=%d]", uid);
		DATA_ERROR_RETURN_MSG("interval_day_over_config");
	}

	if (jsonDsNews[intervalDays].asInt() != 0)
	{
		error_log("[SignInReward][already_sign_in.uid=%d]", uid);
		LOGIC_ERROR_RETURN_MSG("already_sign_in");
	}

	jsonDsNews[intervalDays] = 1;
	jsonStats["dsNew"] = jsonDsNews;
	logicUser.SetUserStat(uid, jsonStats);

	result["dsNew"] = jsonDsNews;
	//签到次数
	int cDays = 0;
	for (int i = 0; i < (int)jsonDsNews.size(); ++i)
	{
		if (jsonDsNews[i].asInt() == 1)
		{
			++cDays;
		}
	}

	const static int daysLevel[SIGNIN_REWARDS_NUM] = {2, 5, 10, 17, 26};
	int index = -1;
	for (int i = SIGNIN_REWARDS_NUM - 1; i >= 0; --i)
	{
		if (cDays >= daysLevel[i])
		{
			index = i;
			break;
		}
	}

	//校验是否领取
	Json::Value jsonDrNew;
	if (! Json::GetArray(jsonStats, "drNew", jsonDrNew))
	{
		error_log("[SignInReward][parse_drNew_fail.uid=%d]", uid);
		DB_ERROR_RETURN_MSG("parse_drNew_fail");
	}

//	if (jsonDrNew.size() != SIGNIN_REWARDS_NUM)
//	{
//		DB_ERROR_RETURN_MSG("drNew_size_error");
//	}

	if (index >= 0 && jsonDrNew[index].asInt() == 0)
	{
		//签到成功 有奖品
		//修改参数 已领取
		jsonDrNew[index] = 1;
		jsonStats["drNew"] = jsonDrNew;

		result["drNew"] = jsonDrNew;

		if (logicUser.SetUserStat(uid, jsonStats) != 0)
		{
			DB_ERROR_RETURN_MSG("change_user_stat_error");
		}

		//TODO 发放奖励
		if (this->ProvideSignInReward(uid, index, dataUser, result) != R_SUCCESS)
		{
			error_log("[SignInReward][provide_sign_In_reward_error.uid=%d]", uid);
			LOGIC_ERROR_RETURN_MSG("provide_sign_In_reward_error");
		}
	}

	if ((ret = logicUser.SetUserLimit(uid, dataUser)) != 0)
	{
		error_log("get_sign_in_reward save user limit failed. uid=%d,ret=%d", uid,ret);
		return ret;
	}

	return R_SUCCESS;
}

int CLogicCMD::ProvideSignInReward(unsigned uid
		, int dayLevel
		, DataUser& dataUser
		, Json::Value &result)
{
	int ret = R_ERROR;
	XMLSignInReward reward;

	CDataXML *dataxml = CDataXML::GetCDataXML();
	if (NULL == dataxml)
	{
		error_log("get_sign_in_reward get dataXML error uid=%d", uid);
		return R_ERR_DB;
	}

	if ((ret = dataxml->GetSignInReward(dayLevel, reward)) != R_SUCCESS)
	{
        error_log("get_sign_in_reward failed uid=%d,ret=%d", uid, ret);
		return ret;
	}

	//TODO 同步奖励
	//Add 威望
	dataUser.prosper += reward.prosper;
	result["prosper"] = dataUser.prosper;

	std::string szReason = "sign_in_reward_op";
	RESOURCE_LOG("[ProvideSignInReward][uid=%u,chgprosper=%u,prosper=%u,code=%s]"
									,uid, reward.prosper, dataUser.prosper, szReason.c_str());
	//修改金币
	CLogicPay logicPay;
	if ((ret = logicPay.ChangePay(uid, 0, reward.gold, szReason)) != 0)
	{
        error_log("get_sign_in_reward add coins failed. uid=%d, ret=%d", uid, ret);
		return ret;
	}
	result["coins"] = reward.gold;

	//装备
	vector<ItemAdd> items;
	for (int i = 0; i < reward.equipCnt; ++i)
	{
		ItemAdd item;
		item.eqid = reward.equips[i].id;
		item.count = reward.equips[i].cnt;
		item.q = reward.equips[i].quality;
		item.reason = szReason;
		items.push_back(item);
	}

	CLogicEquipment logicEquip;
	if ((ret = logicEquip.AddItems(uid, items, result["equipment"], true)) != 0)
	{
        error_log("get_sign_in_reward add items failed. uid=%d, ret=%d", uid, ret);
		return ret;
	}

	return R_SUCCESS;
}

int CLogicCMD::GetInviteReward(unsigned uid, unsigned rewardid, Json::Value &result, unsigned lasttime, unsigned seqid)
{
    int ret = 0;
	CLogicUser logicUser;
	DataUser dataUser;
	std::string userState;
	AUTO_LOCK_USER(uid)
	ret = logicUser.GetUserLimit(uid,dataUser);
	if(ret)
	{
		error_log(" get_user_info_failed,uid = %u",uid);
		return ret;
	}

	if ((ret = checkLastSaveUID(dataUser)) != R_SUCCESS)
	{
		return ret;
	}

	if ((ret = checkLastSaveTime(dataUser,lasttime,seqid)) != R_SUCCESS)
	{
		return ret;
	}

	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

    //TODO
	CDataUserData dataUserDBC;
	std::string szUserGift;
	if ((ret = dataUserDBC.GetGift(uid, szUserGift)) != 0)
	{
		error_log("[GetInviteReward][get_user_gift failed.uid=%u]", uid);
		DB_ERROR_RETURN_MSG("get_user_gift failed");
	}
	Json::Value jsonUserGift;
	Json::Reader().parse(szUserGift, jsonUserGift);

	//为0 则发放每日的好友邀请奖励
	if (0 == rewardid)
	{
		if (0 != jsonUserGift["dInvite"].asInt())
		{
			//REFUSE_RETURN_MSG("already_get_invite_reward_day");
			result["errMsg"] = "already_get_invite_reward_day";
		}
		else
		{
			jsonUserGift["dInvite"] = 1;
			dataUserDBC.SetGift(uid, Json::ToString(jsonUserGift));

			//发放奖励
			if ((ret = this->ProvideInviteDayReward(uid, result)) != R_SUCCESS)
			{
				error_log("[GetInviteReward][provide_invite_reward_day_error.uid=%u]", uid);
				LOGIC_ERROR_RETURN_MSG("provide_invite_reward_error");
			}
		}
	}
	else
	{
		Json::Value jsonLInvite;
		if (! Json::GetArray(jsonUserGift, "lInvite", jsonLInvite))
		{
			error_log("[GetInviteReward][parse_user_gift_lInvite_error.uid=%u]", uid);
			DB_ERROR_RETURN_MSG("parse_user_gift_lInvite failed");
		}

		int index = rewardid - 1;
		if (index < 0 || index >= (int)jsonLInvite.size())
		{
			error_log("[GetInviteReward][rewardid_params_error.uid=%u]", uid);
			PARAM_ERROR_RETURN_MSG("get_invite_reward rewardid params error.");
		}

		//是否已经领取
		if (0 != jsonLInvite[index].asInt())
		{
			error_log("[GetInviteReward][already_get_invite_reward_level.uid=%u]", uid);
			REFUSE_RETURN_MSG("already_day_invite_reward");
		}

		//-----------------------------------------------------------------------
		//是否满足领取的条件
		CDataXML *dataxml = CDataXML::GetCDataXML();
		if (NULL == dataxml)
		{
			error_log("[GetInviteReward]get_invite_reward get dataXML error uid=%d", uid);
			DB_ERROR_RETURN_MSG("get_invite_reward get dataXML error");
		}

		XMLInviteLevelGiftItem levelItem;
		if (( ret = dataxml->GetInviteLevelItem(rewardid, levelItem)) != 0)
		{
			error_log("[GetInviteReward][get dataXML error.uid=%d]", uid);
			DB_ERROR_RETURN_MSG("get_invite_reward config error.");
		}

		if ((ret = this->VerifyInviteRewardOfLevelCondition(uid, levelItem)) != R_SUCCESS)
		{
			error_log("[GetInviteReward][not_get_reward_condition.uid=%d]", uid);
			REFUSE_RETURN_MSG("not_get_reward_condition");
		}

		//设置领取标志位
		jsonLInvite[index] = 1;
		jsonUserGift["lInvite"] = jsonLInvite;
		dataUserDBC.SetGift(uid, Json::ToString(jsonUserGift));

		if ((ret = this->ProvideInviteLevelReward(uid, levelItem, result)) != R_SUCCESS)
		{
			error_log("[GetInviteReward][provide_invite_reward_failed.uid=%d]", uid);
			LOGIC_ERROR_RETURN_MSG("provide_invite_reward_error");
		}
	}

	if ((ret = logicUser.SetUserLimit(uid, dataUser)) != 0)
	{
		error_log("Get_Invite_Reward save user limit error. uid=%d,ret=%d", uid,ret);
		return ret;
	}

    return R_SUCCESS;
}

int CLogicCMD::VerifyInviteRewardOfLevelCondition(
		  unsigned uid
		, const XMLInviteLevelGiftItem& item )
{
	int ret = 0;
	CDataInviteMapping mappingdata;
	DataUser userInvited;
	CLogicUser logicuser;
	vector<unsigned> vUid;

	if ((ret = mappingdata.GetUid(uid, vUid)) != 0)
	{
		error_log("get_user_invite_list error. uid=%d,ret=%d", uid, ret);
		return ret;
	}

	int nlevelUserCnt = 0;
	for(int i = vUid.size() - 1; i >= 0; i--)
	{
		logicuser.GetUserLimit(vUid[i],userInvited);
		if( userInvited.level >= (int)item.level)
		{
			++ nlevelUserCnt;
		}
	}

	if (nlevelUserCnt < (int)item.number)
	{
		error_log("verify_user_invite. uid=%d,invites=%d,level=%d,real=%d"
				, uid, item.number, item.level, nlevelUserCnt);
		return R_ERROR;
	}

	return R_SUCCESS;
}

int CLogicCMD::ProvideInviteDayReward(unsigned uid, Json::Value &result)
{
	//每日的邀请奖励写死在代码，不去读配置文件
	int ret = 0;

	CLogicEquipment logicEquip;
	if ((ret = logicEquip.AddOneItem(uid, 4015, 1, "invite_reward_day", result["equipment"], true)) != 0)
	{
		error_log("get_sign_in_reward add items failed. uid=%d, ret=%d", uid, ret);
		return ret;
	}

	return R_SUCCESS;
}

int CLogicCMD::ProvideInviteLevelReward(
		  unsigned uid
		, const XMLInviteLevelGiftItem& inviteLevel
		, Json::Value &result)
{
	int ret = 0;
	//装备
	vector<ItemAdd> items;
	for (int i = 0; i < (int)inviteLevel.equipsCnt; ++i)
	{
		ItemAdd item;
		item.eqid = inviteLevel.equips[i].id;
		item.count = inviteLevel.equips[i].cnt;
		item.q = inviteLevel.equips[i].quality;
		item.reason = "invite_reward_level";
		items.push_back(item);
	}

	CLogicEquipment logicEquip;
	if ((ret = logicEquip.AddItems(uid, items, result["equipment"], true)) != 0)
	{
		error_log("get_sign_in_reward add items failed. uid=%d, ret=%d", uid, ret);
		return ret;
	}

	return R_SUCCESS;
}

int CLogicCMD::DailyQuestReward(unsigned uid
		, unsigned index
		, bool type
		, bool blue_torch_burning
        , Json::Value& result
        , unsigned lasttime
        , unsigned seqid)
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

	if ((ret = checkLastSaveUID(dataUser)) != R_SUCCESS)
	{
		return ret;
	}

	if ((ret = checkLastSaveTime(dataUser,lasttime,seqid)) != R_SUCCESS)
	{
		return ret;
	}

	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	CDataUserData userDataDBC;
    std::string szDailyQuest;
    if ((ret = userDataDBC.GetDailyQuest(uid, szDailyQuest)))
    {
    	error_log("[DailyQuestReward][get_daily_quest data error.uid=%u]", uid);
        DB_ERROR_RETURN_MSG("get_daily_quest data error.");
    }

    Json::Value jsonDailyQuest;
    if (! Json::FromString(jsonDailyQuest, szDailyQuest))
    {
    	error_log("[DailyQuestReward][parse_daily_quest data error.uid=%u]", uid);
        DATA_ERROR_RETURN_MSG("parse_daily_quest error");
    }

    //------------------------------------------------------------
    //判断是否已经领取
    Json::Value jsonGetStatus;
    if (! Json::GetArray(jsonDailyQuest, "r", jsonGetStatus))
    {
    	error_log("[DailyQuestReward][parse_daily_quest r node error.uid=%u]", uid);
    	DATA_ERROR_RETURN_MSG("parse_daily_quest r node error");
    }

    if (index >= 4)
    {
    	error_log("[DailyQuestReward][param_index_error error.uid=%u,index=%d]", uid, index);
    	PARAM_ERROR_RETURN_MSG("param_index_error");
    }

    //
    if (jsonGetStatus[index].asInt() > 0)
	{
    	error_log("[DailyQuestReward][already_get_reward.uid=%u,index=%d]", uid, index);
		REFUSE_RETURN_MSG("already_get_reward");
	}
    //End----------------------------------------------------------
    else
    {
    	 //-------------------------------------------------------------
		//判断是否能够领取
		//1. 一键领取
		if (type)
		{
			Json::Value user_flag;

			if ((ret = logicUser.GetUserFlag(uid, user_flag)) != 0)
			{
				error_log("[DailyQuestReward][get_user_flag_error.uid=%u,index=%d]", uid, index);
				DATA_ERROR_RETURN_MSG("get_user_flag_error");
			}

			static const int diamonds[4] = {20, 50, 70, 90};

			bool bsave = false;
			CLogicPay logicPay;
			DataPay payData;
			ret = logicPay.ProcessOrderForBackend(uid, -diamonds[index], 0, payData, "DaiyQuestReward_"+CTrans::UTOS(index), user_flag, bsave);
			if(ret != R_SUCCESS)
			{
				error_log("[DailyQuestReward][cost_diamod_error.uid=%u,index=%d,diamods=%d]", uid, index, diamonds[index]);
				DATA_ERROR_RETURN_MSG("cost_diamod_error");
			}

			result["pointpay"].resize(0);
			if(bsave)
			{
				result["pointpay"] = user_flag["user_pay"];
				logicUser.SetUserFlag(uid, user_flag);
			}

			result["coins"] = payData.coins;
			result["diamond"] = payData.cash;
		}
		//2. 根据任务完成度
		else
		{
			Json::Value jsonTasksStatus;
			if (! Json::GetArray(jsonDailyQuest, "s", jsonTasksStatus))
			{
				error_log("[DailyQuestReward][parse_daily_quest s node error.uid=%u]", uid);
				DATA_ERROR_RETURN_MSG("parse_daily_quest s node error");
			}

			unsigned finishTasks = 0;
			for (int i = 0; i < (int)jsonTasksStatus.size(); ++i)
			{
				if (jsonTasksStatus[i].asInt() > 0)
				{
					++ finishTasks;
				}
			}

			static const unsigned sLivenessLevel[4] = {20, 50, 70, 90};
			unsigned liveness = finishTasks * 5;
			if (liveness < sLivenessLevel[index])
			{
				//REFUSE_RETURN_MSG("get_reward_condition_not_enough");
				result["errMsg"] = "quest_daily_error";

				if ((ret = logicUser.SetUserLimit(uid, dataUser)) != 0)
				{
					error_log("get_daily_quest_reward add experience failed. uid=%d,ret=%d", uid,ret);
					return ret;
				}

				return 0;
			}
		}
		//End-------------------------------------------------------------

		//记录档案，发放奖励
		jsonGetStatus[index] = 1;
		jsonDailyQuest["r"] = jsonGetStatus;
		szDailyQuest = Json::ToString(jsonDailyQuest);

		if ((ret = userDataDBC.SetDailyQuest(uid, szDailyQuest)))
		{
			 error_log("[DailyQuestReward][set_user_daily_quest error.uid=%u]", uid);
			 DATA_ERROR_RETURN_MSG("set_user_daily_quest error");
		}

		if ((ret = this->ProvideDailyQuestReward(uid, index, blue_torch_burning, dataUser, jsonDailyQuest, result)) != R_SUCCESS)
		{
			error_log("[DailyQuestReward][provide_daily_quest_reward_failed.uid=%u]", uid);
			LOGIC_ERROR_RETURN_MSG("provide_daily_quest_reward_failed");
		}
    }

	if ((ret = logicUser.SetUserLimit(uid, dataUser)) != 0)
	{
		error_log("get_daily_quest_reward add experience failed. uid=%d,ret=%d", uid,ret);
		return ret;
	}

    return R_SUCCESS;
}


int CLogicCMD::ProvideDailyQuestReward(
		  unsigned uid
		, unsigned index
		, bool blue_torch_burning
		, DataUser& dataUser
		, const Json::Value& dailyQuest
		, Json::Value& result)
{
	Json::Value jsonG;
	if (! Json::GetArray(dailyQuest,"g", jsonG))
	{
		error_log("daily_quest_g_node_error");
		return R_ERR_DB;
	}


	std::string szReason = "daily_quest_reward_op";
	vector<ItemAdd> items;
	unsigned expLevel = 0;
	if (index  == 3)
	{
		expLevel = 10;
		int itemId = jsonG[1].asInt();
		if (0 == itemId)
		{
			error_log("daily_quest_g_node_index_3_error");
			return R_ERR_DB;
		}

		items.push_back(ItemAdd(itemId, 1, szReason));
#ifdef SG_16_VER
		items.push_back(ItemAdd(42015, 10, szReason));
#else
		items.push_back(ItemAdd(4065, 10, szReason));
#endif
	}
	else if (index == 2)
	{
		expLevel = 40;

		int itemId = jsonG[0u].asInt();
		if (0 == itemId)
		{
			error_log("daily_quest_g_node_index_2_error");
			return R_ERR_DB;
		}
		items.push_back(ItemAdd(itemId, 1, szReason));
#ifdef SG_16_VER
		items.push_back(ItemAdd(4015, 2, szReason));
#else
		items.push_back(ItemAdd(4066, 2, szReason));
#endif
	}
	else if (index == 1)
	{
		expLevel = 30;
		items.push_back(ItemAdd(4201, 5, szReason));
		items.push_back(ItemAdd(11112, 1, szReason));
	}
	else if (index == 0)
	{
		expLevel = 20;
		items.push_back(ItemAdd(4022, 3, szReason));
	}
	else
	{
		return R_ERR_REFUSE;
	}

	int ret = 0;
	CLogicEquipment logicEquip;
	if ((ret = logicEquip.AddItems(uid, items, result["equipment"], true)) != 0)
	{
		error_log("get_sign_in_reward add items failed. uid=%d, ret=%d", uid, ret);
		return ret;
	}

	unsigned temp_add_point = int((expLevel / 100.0) * (3.5 * pow((dataUser.level + 10), 2.2) - 600));
	if (blue_torch_burning)
		temp_add_point *= 1.1;
	dataUser.point += temp_add_point;

	RESOURCE_LOG("[DailyQuestReward][uid=%u,expchg=%u,exp=%u]",uid,temp_add_point,dataUser.point);

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

	return R_SUCCESS;
}

int CLogicCMD::VipGiftBag(unsigned uid, unsigned vipLevel, Json::Value& result, unsigned lasttime, unsigned seqid)
{
	int ret = 0;
	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	ret = logicUser.GetUser(uid,dataUser);
	if(ret)
	{
		error_log(" get_user_info_failed,uid = %u",uid);
		return ret;
	}

	if ((ret = checkLastSaveUID(dataUser)) != R_SUCCESS)
	{
		return ret;
	}

	if ((ret = checkLastSaveTime(dataUser,lasttime,seqid)) != R_SUCCESS)
	{
		return ret;
	}

	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	//
	if (vipLevel < 1 || vipLevel > 10)
	{
		error_log("[VipGiftBag][vip_level_param_error,uid=%u,level=%d]",uid, vipLevel);
		PARAM_ERROR_RETURN_MSG("vip_level_param_error");
	}

	//
	if (dataUser.viplevel < (int)vipLevel)
	{
		error_log("[VipGiftBag][vip_level_param_error,uid=%u,uLv=%d,level=%d]",uid,dataUser.viplevel,vipLevel);
		REFUSE_RETURN_MSG("vip_level_not_enough");
	}

	Json::Value jsonVipState;
	if (! Json::FromString(jsonVipState, dataUser.vipstat) || ! jsonVipState.isArray())
	{
		//DB_ERROR_RETURN_MSG("user_vip_stat_parse_error");
		for (int i = 0; i < 10; ++i)
		{
			jsonVipState[i] = 0;
		}
	}

	//判断是否已经领取
	if (jsonVipState[vipLevel - 1].asInt() > 0)
	{
		error_log("[VipGiftBag][already_get_gift_bag,uid=%u,level=%d]",uid,vipLevel);
		REFUSE_RETURN_MSG("already_get_gift_bag");
	}

	//设置标志位
	jsonVipState[vipLevel - 1] = 1;
	dataUser.vipstat = Json::ToString(jsonVipState);

	if ((ret = this->ProvideVipGiftBag(uid, vipLevel, dataUser, result)) != R_SUCCESS)
	{
		error_log("[VipGiftBag][provide_gift_bag_failed,uid=%u,level=%d]",uid,vipLevel);
		LOGIC_ERROR_RETURN_MSG("provide_gift_bag_failed");
	}

	if ((ret = logicUser.SetUser(uid, dataUser)) != 0)
	{
		error_log("get_daily_quest_reward add experience failed. uid=%d,ret=%d", uid,ret);
		return ret;
	}

	return R_SUCCESS;
}

int CLogicCMD::LoginGiftOfTencentPCManager(unsigned uid, Json::Value& result, unsigned lasttime, unsigned seqid)
{
	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	int ret = logicUser.GetUserLimit(uid,dataUser);
	if(ret)
	{
		error_log("get_user_info_failed,uid = %u",uid);
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

	//2. 检查相应礼包: 是否已经领取过了    数据格式 {"id":20, a:0,  b:0, c:22222222}
	//format newAct
	Json::Value newAct;
	CLogicSecinc logicSecinc;
	ret = logicSecinc.GetSecinc(uid, NAT_TENCENT_MANAGER, newAct);
	if (R_ERR_NO_DATA == ret)
	{
		newAct["id"] = NAT_TENCENT_MANAGER;
		newAct["a"] = 0;
		newAct["b"] = 0;
		newAct["c"] = Time::GetGlobalTime();
	} else if (R_SUCCESS != ret)
		return ret;

	if (!newAct.isMember("id"))
		newAct["id"] = NAT_TENCENT_MANAGER;
	if (!newAct.isMember("a"))
		newAct["a"] = 0;
	if (!newAct.isMember("b"))
		newAct["b"] = 0;
	if (!newAct.isMember("c"))
		newAct["c"] = Time::GetGlobalTime();

	//需要对  昨天领取过的 登录礼包做处理: 这个在登录礼包的领取时， 单独做处理
	if (newAct["b"].asUInt() && CTime::IsDiffDay(newAct["c"].asUInt(), Time::GetGlobalTime()))
	{
		newAct["b"] = 0;
		newAct["c"] = Time::GetGlobalTime();
	}
	// 今天已经领取过了
	if (newAct["b"].asUInt())
	{
		error_log("has got LoginGiftOfTencentPCManager, uid=%u", uid);
		return R_ERR_LOGIC;
	}
	//下面是 可以领取的情况
	//3. 发放礼包:  1) 先改NewAct  2)发放装备  3)前端返回数据： 装备和NewAct
	newAct["b"] = 1;
	newAct["c"] = Time::GetGlobalTime();
	ret = logicSecinc.SetOneSecinc(uid, newAct);
	if (ret)
	{
		error_log("LoginGiftOfTencentPCManager SetOneSecinc failed. uid=%u, ret=%d", uid, ret);
		return ret;
	}
	result["newAct"] = newAct;

 	std::string szReason = "login_gift_tencent_pc_manager";
	vector<ItemAdd> items;
	items.push_back(ItemAdd(42015, 1, szReason));
	items.push_back(ItemAdd(4022, 2, szReason));
	items.push_back(ItemAdd(4011, 6, szReason));
	CLogicEquipment logicEquip;
	if ((ret = logicEquip.AddItems(uid, items, result["equipment"], true)) != 0)
	{
		error_log("LoginGiftOfTencentPCManager AddItems failed. uid=%u, ret=%d", uid, ret);
		return ret;
	}

	ret = logicUser.SetUserLimit(uid, dataUser);
	if (ret)
		return ret;

	return R_SUCCESS;
}


int CLogicCMD::InstallGiftOfTencentPCManager(unsigned uid, Json::Value& result, unsigned lasttime, unsigned seqid)
{
	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	int ret = logicUser.GetUserLimit(uid,dataUser);
	if(ret)
	{
		error_log("get_user_info_failed,uid = %u",uid);
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

	//2. 检查相应礼包: 是否已经领取过了  数据格式 {"id":24, a:1,  b:1, c:22222222}
	//format newAct
	Json::Value newAct;
	CLogicSecinc logicSecinc;
	ret = logicSecinc.GetSecinc(uid, NAT_TENCENT_MANAGER, newAct);
	if (R_ERR_NO_DATA == ret)
	{
		newAct["id"] = NAT_TENCENT_MANAGER;
		newAct["a"] = 0;
		newAct["b"] = 0;
		newAct["c"] = Time::GetGlobalTime();
	} else if (R_SUCCESS != ret)
		return ret;

	if (!newAct.isMember("id"))
		newAct["id"] = NAT_TENCENT_MANAGER;
	if (!newAct.isMember("a"))
		newAct["a"] = 0;
	if (!newAct.isMember("b"))
		newAct["b"] = 0;
	if (!newAct.isMember("c"))
		newAct["c"] = Time::GetGlobalTime();

	//只能领取一次安装礼包
	if (newAct["a"].asUInt())
	{
		error_log("has got InstallGiftOfTencentPCManager, uid=%u", uid);
		return R_ERR_LOGIC;
	}
	//下面是 可以领取的情况
	//3. 发放礼包:  1) 先改NewAct  2)发放装备  3)前端返回数据： 装备和NewAct
	newAct["a"] = 1;
	ret = logicSecinc.SetOneSecinc(uid, newAct);
	if (ret)
	{
		error_log("InstallGiftOfTencentPCManager SetOneSecinc failed. uid=%u, ret=%d", uid, ret);
		return ret;
	}
	result["newAct"] = newAct;

 	std::string szReason = "install_gift_tencent_pc_manager";
	vector<ItemAdd> items;
	items.push_back(ItemAdd(42015, 15, szReason));
	items.push_back(ItemAdd(11112, 4, szReason));
	items.push_back(ItemAdd(4011, 20, szReason));
	items.push_back(ItemAdd(4452, 2, szReason));
	CLogicEquipment logicEquip;
	if ((ret = logicEquip.AddItems(uid, items, result["equipment"], true)) != 0)
	{
		error_log("InstallGiftOfTencentPCManager AddItems failed. uid=%u, ret=%d", uid, ret);
		return ret;
	}

	ret = logicUser.SetUserLimit(uid, dataUser);
	if (ret)
		return ret;

	return R_SUCCESS;
}


int CLogicCMD::ProvideVipGiftBag(unsigned uid, unsigned vipLevel, DataUser& dataUser, Json::Value& result)
{
	std::string szReason = "vip_gift_bag_op_vip_";

	vector<ItemAdd> items;
	//
	std::vector<std::string> vHeroIds;
	std::vector<std::string> vHeroCodes;

	switch (vipLevel)
	{
		case 1:
		{
			items.push_back(ItemAdd(4201, 2, szReason.append("1")));
			items.push_back(ItemAdd(4015, 1, szReason));
			items.push_back(ItemAdd(40122, 1, szReason));
			items.push_back(ItemAdd(4011, 30, szReason));

			break;
		}
		case 2:
		{
			items.push_back(ItemAdd(40122, 2, szReason.append("2")));
			items.push_back(ItemAdd(4015, 2, szReason));
			items.push_back(ItemAdd(4202, 7, szReason));
			items.push_back(ItemAdd(4011, 60, szReason));
			items.push_back(ItemAdd(11111, 2, szReason));
			items.push_back(ItemAdd(4402, 2, szReason));
			items.push_back(ItemAdd(4302, 2, szReason));
			break;
		}
		case 3:
		{
			items.push_back(ItemAdd(4203, 2, szReason.append("3")));
			items.push_back(ItemAdd(4015, 3, szReason));
			items.push_back(ItemAdd(40123, 2, szReason));
			items.push_back(ItemAdd(4011, 90, szReason));
			items.push_back(ItemAdd(42015, 2, szReason));
			break;
		}
		case 4:
		{
			items.push_back(ItemAdd(4324, 1, szReason.append("4")));
			items.push_back(ItemAdd(40132, 1, szReason));
			items.push_back(ItemAdd(4012, 30, szReason));
			items.push_back(ItemAdd(4204, 2, szReason));
			items.push_back(ItemAdd(42015, 3, szReason));
			break;
		}
		case 5:
		{
			items.push_back(ItemAdd(4305, 1, szReason.append("5")));
			items.push_back(ItemAdd(40132, 2, szReason));
			items.push_back(ItemAdd(4012, 60, szReason));
			items.push_back(ItemAdd(4205, 4, szReason));
			items.push_back(ItemAdd(11111, 10, szReason));
			break;
		}
		case 6:
		{
			items.push_back(ItemAdd(4335, 1, szReason.append("6")));
			items.push_back(ItemAdd(4012, 90, szReason));
			items.push_back(ItemAdd(40133, 2, szReason));
			items.push_back(ItemAdd(4206, 3, szReason));
			//hero
			vHeroIds.push_back(CDataXML::Hero2Str(3101));
			vHeroCodes.push_back(szReason);
			break;
		}
		case 7:
		{
			items.push_back(ItemAdd(4207, 2, szReason.append("7")));
			items.push_back(ItemAdd(40142, 1, szReason));
			items.push_back(ItemAdd(4013, 30, szReason));
			items.push_back(ItemAdd(4404, 1, szReason));
			items.push_back(ItemAdd(11112, 5, szReason));
			break;
		}
		case 8:
		{
			items.push_back(ItemAdd(11112, 30, szReason.append("8")));
			items.push_back(ItemAdd(40142, 2, szReason));
			items.push_back(ItemAdd(4013, 60, szReason));
			items.push_back(ItemAdd(4206, 3, szReason));
			items.push_back(ItemAdd(4208, 2, szReason));
			items.push_back(ItemAdd(4424, 1, szReason));

			//hero
			vHeroIds.push_back(CDataXML::Hero2Str(3201));
			vHeroCodes.push_back(szReason);
			break;
		}
		case 9:
		{
			items.push_back(ItemAdd(4327, 1, szReason.append("9")));
			items.push_back(ItemAdd(11112, 90, szReason));
			items.push_back(ItemAdd(4206, 5, szReason));
			items.push_back(ItemAdd(40143, 2, szReason));
			items.push_back(ItemAdd(4434, 1, szReason));
			items.push_back(ItemAdd(4013, 90, szReason));
			items.push_back(ItemAdd(4209, 2, szReason));

			//hero
			vHeroIds.push_back(CDataXML::Hero2Str(3001));
			vHeroCodes.push_back(szReason);
			break;
		}
		case 10:
		{
			items.push_back(ItemAdd(4210, 2, szReason.append("10")));
			items.push_back(ItemAdd(4015, 10, szReason));
			items.push_back(ItemAdd(40152, 2, szReason));
			items.push_back(ItemAdd(4014, 30, szReason));
			items.push_back(ItemAdd(4337, 1, szReason));
			items.push_back(ItemAdd(4327, 1, szReason));
			items.push_back(ItemAdd(4347, 1, szReason));
			items.push_back(ItemAdd(11112, 100, szReason));
			break;
		}
		default:
		{
			error_log("Get_vip_gift_bag param error. viplevel: {%d}", vipLevel);
			return R_ERROR;
		}
	}

	int ret = 0;
	CLogicEquipment logicEquip;
	if ((ret = logicEquip.AddItems(uid, items, result["equipment"], true)) != 0)
	{
		error_log("Get_vip_bag add items failed. uid=%u, ret=%d", uid, ret);
		return ret;
	}

	if(vHeroIds.size() > 0)
	{
		CLogicHero Hero;
		ret = Hero.AddHeros(uid,vHeroIds,vHeroCodes,result["hero"]);
		if(R_SUCCESS != ret)
		{
			error_log("Get_vip_bag_add_hero_error uid=%u | ret=%u", uid , ret);
			return R_ERR_DATA;
		}
	}

	return R_SUCCESS;
}

int CLogicCMD::RechargeGiftBag(
		  unsigned uid
		, unsigned id
		, Json::Value& result
		, unsigned lasttime
		, unsigned seqid)
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

	if ((ret = checkLastSaveUID(dataUser)) != R_SUCCESS)
	{
		return ret;
	}

	if ((ret = checkLastSaveTime(dataUser,lasttime,seqid)) != R_SUCCESS)
	{
		return ret;
	}

	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;
	//@end

	//参数校验
	if (id == 0 || id > 10)
	{
		error_log("[RechargeGiftBag][params_error. uid=%u, id=%d]", uid, id);
		PARAM_ERROR_RETURN_MSG("params_error");
	}
	//@end

	//1. 判断累计充值和VIP等级
	unsigned needRecharge = 0;
	unsigned level = 0;
	{
		struct VipPayCfg
		{
			unsigned id;
			unsigned coin;
			unsigned level;
		} static const aVipPays[] = {
				{1, 5, 0},
				{3, 2000, 3},
				{6, 20000, 6},
				{9, 200000, 9},
				{10, 500000, 10}
		};

		for (int i = 0; i < (int)(sizeof(aVipPays) / sizeof(VipPayCfg)); ++i)
		{
			if (aVipPays[i].id == id)
			{
				needRecharge = aVipPays[i].coin;
				level = aVipPays[i].level;
				break;
			}
		}
	}

	if (0 == needRecharge)
	{
		error_log("[RechargeGiftBag][not_cfg. uid=%u, id=%d]", uid, id);
		PARAM_ERROR_RETURN_MSG("not_cfg");
	}

	if (needRecharge > dataUser.accCharge)
	{
		error_log("[RechargeGiftBag][not_enough_acc_charge. uid=%u,uCharge=%d,need=%d]"
				, uid, dataUser.accCharge, needRecharge);
		REFUSE_RETURN_MSG("not_enough_acc_charge");
	}

	if ((int)level > dataUser.viplevel)
	{
		error_log("[RechargeGiftBag][not_enough_vip_level. uid=%u,ulv=%d,need=%d]"
						, uid, dataUser.viplevel, level);
		REFUSE_RETURN_MSG("not_enough_vip_level");
	}
	//@end

	//2. 判断是否领取过
	CLogicUserData logicUserDataHandle;
	Json::Value jsonGift;
	Json::Value jsonPay;
	if ((ret = logicUserDataHandle.GetGift(uid, jsonGift)) != R_SUCCESS)
	{
//		error_log("[RechargeGiftBag][get_gift_data_error. uid=%u]", uid);
//		DATA_ERROR_RETURN_MSG("get_gift_data_error");
		for (int i = 0; i < 10; ++i)
		{
			jsonPay[i]["id"] = i + 1;
			jsonPay[i]["reward"] = 0;
		}
		jsonGift["pay"] = jsonPay;
	}
	else
	{
		if (! Json::GetArray(jsonGift, "pay", jsonPay))
		{
	//		error_log("[RechargeGiftBag][get_gift_pay_node_error. uid=%u]", uid);
	//		DATA_ERROR_RETURN_MSG("get_gift_pay_node_error");
			for (int i = 0; i < 10; ++i)
			{
				jsonPay[i]["id"] = i + 1;
				jsonPay[i]["reward"] = 0;
			}
		}
	}

	int index = -1;
	for (int i = 0; i < (int)jsonPay.size(); ++i)
	{
		if (jsonPay[i]["id"].asInt() == (int)id)
		{
			if (jsonPay[i]["reward"].asInt() > 0)
			{
				error_log("[RechargeGiftBag][already_get_pay_gift_bag. uid=%u]", uid);
				REFUSE_RETURN_MSG("already_get_pay_gift_bag");
			}
			index = i;
			break;
		}
	}

	if (index < 0)
	{
		error_log("[RechargeGiftBag][can_not_find_the_record. uid=%u]", uid);
		DB_ERROR_RETURN_MSG("can_not_find_the_record");
	}
	//@end

	//记录到档案
	jsonPay[index]["reward"] = 1;
	jsonGift["pay"] = jsonPay;
	logicUserDataHandle.SetGift(uid, jsonGift);
	//@end

	if (( ret = ProvideRechargeGiftBag(uid, id, result)) != R_SUCCESS)
	{
		error_log("[RechargeGiftBag][ProvideRechargeGiftBag. uid=%u]", uid);
		LOGIC_ERROR_RETURN_MSG("provide_gift_bag_failed");
	}


	if ((ret = logicUser.SetUserLimit(uid, dataUser)) != 0)
	{
		error_log("get_daily_quest_reward add experience failed. uid=%d,ret=%d", uid,ret);
		return ret;
	}


	return R_SUCCESS;
}

int CLogicCMD::ProvideRechargeGiftBag(unsigned uid, unsigned id, Json::Value& result)
{
	std::string szReason = "recharge_gift_bag_op_id_";

	vector<ItemAdd> items;
	//
	std::vector<std::string> vHeroIds;
	std::vector<std::string> vHeroCodes;

	switch (id)
	{
		case 1:
		{
			items.push_back(ItemAdd(4015, 2, szReason.append("1")));
			items.push_back(ItemAdd(4402, 1, szReason));
			items.push_back(ItemAdd(4422, 1, szReason));
			items.push_back(ItemAdd(4462, 1, szReason));

			break;
		}
		case 3:
		{
			items.push_back(ItemAdd(4203, 5, szReason.append("3")));
			items.push_back(ItemAdd(11111, 5, szReason));
			items.push_back(ItemAdd(4303, 3, szReason));
			items.push_back(ItemAdd(4423, 3, szReason));
			break;
		}
		case 6:
		{
			items.push_back(ItemAdd(4205, 5, szReason.append("6")));
			items.push_back(ItemAdd(11112, 20, szReason));
			items.push_back(ItemAdd(4304, 5, szReason));
			items.push_back(ItemAdd(4404, 3, szReason));
			break;
		}
		case 9:
		{
			items.push_back(ItemAdd(4207, 5, szReason.append("9")));
			items.push_back(ItemAdd(11112, 50, szReason));
			items.push_back(ItemAdd(4428, 1, szReason));
			items.push_back(ItemAdd(4325, 5, szReason));
			break;
		}
		case 10:
		{
			items.push_back(ItemAdd(4440, 2, szReason.append("10")));
			items.push_back(ItemAdd(11112, 99, szReason));
			items.push_back(ItemAdd(4330, 2, szReason));
			//hero
#ifdef SG_16_VER
			vHeroIds.push_back(CDataXML::Hero2Str(3225));
#else
			vHeroIds.push_back(CDataXML::Hero2Str(3099));
#endif
			vHeroCodes.push_back(szReason);
			break;
		}
		default:
		{
			error_log("Get_recharge_gift_bag param error. id: {%d}", id);
			return R_ERROR;
		}
	}

	int ret = 0;
	CLogicEquipment logicEquip;
	if ((ret = logicEquip.AddItems(uid, items, result["equipment"], true)) != 0)
	{
		error_log("Get_recharge_gift_bag add items failed. uid=%u,ret=%d", uid, ret);
		return ret;
	}

	if(vHeroIds.size() > 0)
	{
		CLogicHero Hero;
		ret = Hero.AddHeros(uid,vHeroIds,vHeroCodes,result["hero"]);
		if(R_SUCCESS != ret)
		{
			error_log("Get_vip_bag_add_hero_error uid=%u,ret=%u", uid , ret);
			return R_ERR_DATA;
		}
	}

	return R_SUCCESS;
}

