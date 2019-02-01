/*
 * LogicCMD5.cpp
 *
 *  Created on: 2016-11-15
 *      Author: Ralf
 */


#include "LogicCMD.h"
#include "LogicUnitWrap.h"
#include "LogicCmdUnits.h"
#include <math.h>


int CLogicCMD::RefreshHero(unsigned uid, unsigned refreshType, unsigned sourceType, Json::Value &result,unsigned zmlud,unsigned &lasttime,unsigned &seqid)
{
	int ret = 0;
	CDataXML *dataXML = CDataXML::GetCDataXML();
	if(!dataXML)
	{
		error_log("GetInitXML fail");
		return R_ERR_DB;
	}

	// 扣资源
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

	Json::Value stats;
	Json::Reader reader;
	reader.parse(dataUser.user_stat,stats);
	Json::FastWriter writer;
	Json::Value user_flag;
	bool bsave = false;
	reader.parse(dataUser.user_flag,user_flag);

	ret = deductSource(uid, dataUser.viplevel, refreshType, sourceType, result, stats, zmlud, user_flag, bsave);
	if(ret)
	{
		error_log("deductSource error");
		return R_ERR_PARAM;
	}
	result["pointpay"].resize(0);
	if(bsave)
	{
		result["pointpay"] = user_flag["user_pay"];
		dataUser.user_flag = writer.write(user_flag);
	}

	unsigned hero1, hero2, hero3,star1,star2,star3;

#ifdef SG_16_VER
	unsigned hct = 0;
	Json::GetUInt(stats, "hct", hct);
	if(refreshType == XML_HERO_RATE - 2)
		++hct;
	result["hct"] = stats["hct"] = hct;
	ret = dataXML->RefreshHero(refreshType, hero1, star1, hero2, star2, hero3, star3, hct%10 == 0);
#else
	ret = dataXML->RefreshHero(refreshType, hero1, star1, hero2, star2, hero3, star3);
#endif
	if(ret)
	{
		error_log("RefreshHero error");
		return ret;
	}

	result["chh"][0u] = CDataXML::Hero2Str(hero1).append(",0,").append(CTrans::UTOS(star1));
	result["chh"][1u] = CDataXML::Hero2Str(hero2).append(",0,").append(CTrans::UTOS(star2));
	result["chh"][2u] = CDataXML::Hero2Str(hero3).append(",0,").append(CTrans::UTOS(star3));

	stats["chh"][0u] = result["chh"][0u];
	stats["chh"][1u] = result["chh"][1u];
	stats["chh"][2u] = result["chh"][2u];

	dataUser.user_stat = writer.write(stats);
	ret = logicUser.SetUser(uid, dataUser);
	if(ret)
		return ret;

	return R_SUCCESS;
}


int CLogicCMD::deductSource(unsigned uid, int viplvl, unsigned refreshType, unsigned sourceType, Json::Value &result, Json::Value &stats, unsigned zmlud, Json::Value &user_flag, bool &bsave){
	int ret = -1;
	switch(sourceType)
	{
	case REFRESH_COST_TIME:
		ret = deductTime(uid, refreshType, stats, result);
		break;
	case REFRESH_COST_COIN:
		ret = deductCoin(uid, refreshType, result, user_flag, bsave);
		break;
	case REFRESH_COST_CASH:
		ret = deductCash(uid, refreshType, result, user_flag, bsave);
		break;
	case REFRESH_COST_ITEM:
		ret = deductItem(uid, refreshType, result, zmlud);
		break;
	case REFRESH_COST_VIP:
		ret = deductVip(uid, viplvl, refreshType, stats, result);
		break;
	default:
		error_log("error sourceType=%u, uid=%u", sourceType, uid);
	}
	return ret;
}

int CLogicCMD::deductTime(unsigned uid, unsigned refreshType, Json::Value &stats, Json::Value &result){
	uint32_t time_now = time(NULL);

	int BdLvl = 0;
	Json::Value Bd;
	CLogicBuilding logicBd;
	int ret = logicBd.Get(uid, 8,0,true, Bd);
	if (ret == 0)
	{
		if (Bd.isMember("l") && Bd["l"].isIntegral())
		{
			BdLvl = Bd["l"].asInt();
		}
	}
	float per = 1.0f - 0.002f * (float)BdLvl;

	switch (refreshType)
	{
	case REFRESH_GREEN:
		{
			unsigned hc = 0;
			Json::GetUInt(stats,"hc",hc);
			unsigned hcc = 0;
			Json::GetUInt(stats,"hcc",hcc);

			if(time_now < hc)
			{
				return REFRESH_COST_TIME;
			}
			// 新的计算，5次内1800s，6至10次3600s，11到15次5400s，15+ 10800s
			uint32_t stats_hcc = hcc;
			uint32_t cdTime;
			if(stats_hcc <= 5) {
				cdTime = 1800;
			} else if(6 <= stats_hcc && stats_hcc <= 10) {
				cdTime = 3600;
			} else if(11 <= stats_hcc && stats_hcc <= 15) {
				cdTime = 5400;
			} else {
				cdTime = 10800;
			}
			stats["hc"] = time_now + cdTime;
			stats["hcc"] = stats_hcc + 1;
			result["hc"] = stats["hc"];
			result["hcc"] = stats["hcc"];
		}
		break;
	case REFRESH_BLUE:
		{
			unsigned hc2 = 0;
			Json::GetUInt(stats,"hc2",hc2);
			if(time_now < hc2)
			{
				return REFRESH_COST_TIME;
			}
			// hc2：中级刷新，冷却时间（24 * 60 * 60）
			stats["hc2"] = time_now + 24.0f * 60.0f * 60.0f * per;
			result["hc2"] = stats["hc2"];
		}
		break;
	case REFRESH_PURPLE:
		{
			unsigned hc3 = 0;
			Json::GetUInt(stats,"hc3",hc3);
			if(time_now < hc3)
			{
				return REFRESH_COST_TIME;
			}
			// 紫色刷新，冷却时间（72 * 60 * 60）
			if(OpenPlatform::IsEN())
				stats["hc3"] = time_now + 12.0f * 60.0f * 60.0f * per;
			else
				stats["hc3"] = time_now + 72.0f * 60.0f * 60.0f * per;
			result["hc3"] = stats["hc3"];
		}
		break;
	default:
		error_log("error refreshType=%u, uid=%u", refreshType, uid);
		return 1;
	}
	return R_SUCCESS;
}

int CLogicCMD::deductCoin(unsigned uid, unsigned refreshType, Json::Value &result, Json::Value &user_flag, bool &bsave){
	int coinCost = getCoinOrCashCost(refreshType);
	if(coinCost > 0) {
		return REFRESH_COST_COIN;
	}
	CLogicPay logicPay;
	DataPay payData;
	int ret = logicPay.ProcessOrderForBackend(uid, 0, coinCost, payData, "accelerate_wujiang_HIREHERO_SPEEDUP", user_flag, bsave);
	if (ret != 0)
	{
		return REFRESH_COST_COIN;
	}
	result["coins"] = coinCost * -1;
	return R_SUCCESS;
}

int CLogicCMD::deductCash(unsigned uid, unsigned refreshType, Json::Value &result, Json::Value &user_flag, bool &bsave){
	int cashCost = getCoinOrCashCost(refreshType);
	if(cashCost > 0) {
		return REFRESH_COST_CASH;
	}
	CLogicPay logicPay;
	DataPay payData;
	int ret = logicPay.ProcessOrderForBackend(uid, cashCost, 0, payData, "accelerate_wujiang_HIREHERO_SPEEDUP", user_flag, bsave);
	if (ret != 0)
	{
		return REFRESH_COST_CASH;
	}
	result["cash"] = cashCost * -1;
	return R_SUCCESS;
}

// 4-招募令
int CLogicCMD::deductItem(unsigned uid, unsigned refreshType, Json::Value &result, unsigned zmlud){
	int num;
	if(OpenPlatform::IsEN())
		num = 2;
	else
		num = getZhaomulingNum(getCoinOrCashCost(refreshType) * -1);
	CLogicEquipment equipment;
	int ret = equipment.UseEquipment(uid, ZHAO_MU_LING,zmlud,num, "accelerate_wujiang_HIREHERO_SPEEDUP");
	if(ret != 0)
	{
		return REFRESH_COST_ITEM;
	}
	result["item"] = Convert::IntToString(ZHAO_MU_LING).append("_").append(Convert::IntToString(num));

	//充值送星级活动
	try
	{
		unsigned time_now = Time::GetGlobalTime();

		if (HeroUpgrideUnit::IsActiving(time_now))  //在活动时间范围内
		{
			HeroUpgrideUnit  herounit(uid);
			herounit.UpdateZMLUsed(num);
		}
	}
	catch(const std::exception& e)
	{
		error_log("[deductItem] %s, uid=%u", e.what(), uid);
	}

	return R_SUCCESS;
}

int CLogicCMD::deductVip(unsigned uid, int viplvl, unsigned refreshType,Json::Value &stats, Json::Value &result){
	if(refreshType != REFRESH_PURPLE) {
		error_log("error refreshType=%u, uid=%u",refreshType,uid);
		return REFRESH_COST_VIP;
	}


	CDataXML *pDataXML = CDataXML::GetCDataXML();
	if(!pDataXML)
	{
		cout << "GetCDataXML fail" << endl;
		return R_ERR_DATA;
	}
	XMLVIP vip;
	uint32_t index = 14;
	int ret = pDataXML->GetVIP(index, vip);
	if(ret)
	{
		error_log("GetVIP fail uid=%u", uid);
		return REFRESH_COST_VIP;
	}

	if(viplvl < 1)
	{
		return REFRESH_COST_VIP;
	}

	int count;
	// 超级VIP
	if(stats["byv"].asInt() > 0) {
		count = vip.privileS[viplvl-1];
	} else {
		count = vip.privile[viplvl-1];
	}

	if(stats["frht"].asInt() >= count) {
		return REFRESH_COST_VIP;
	}
	stats["frht"] = stats["frht"].asInt() + 1;
	result["frht"] = stats["frht"];
	return R_SUCCESS;
}

int CLogicCMD::getCoinOrCashCost(unsigned refreshType){
	int coinCost = 1;
	switch (refreshType)
	{
	case REFRESH_GREEN:
		coinCost = ACC_COST_GREEN;
		break;
	case REFRESH_BLUE:
		coinCost = ACC_COST_BLUE;
		break;
	case REFRESH_PURPLE:
		coinCost = ACC_COST_PURPLE;
		break;
	default:
		error_log("error refreshType=%u", refreshType);
	}
	return -coinCost;
}

int CLogicCMD::ChargeBackHappyCard(unsigned uid, Json::Value &result,unsigned &lasttime,unsigned &seqid)
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

	string gift;
	CDataUserData db;
	db.GetGift(uid, gift);

	Json::Value gt;
	Json::Reader reader;
	reader.parse(gift,gt);

	if(gt.isMember("happycard") && gt["happycard"].isMember("hcShowArr") && gt["happycard"].isMember("hcChoosArr")
	&& gt["happycard"]["hcShowArr"].isArray() && gt["happycard"]["hcChoosArr"].isArray()
	&& !gt["happycard"]["hcShowArr"].empty() && !gt["happycard"]["hcChoosArr"].empty())
	{
		gt["happycard"]["hcShowArr"].clear();
		gt["happycard"]["hcChoosArr"].clear();
		gt["happycard"]["hcmfsx"] = 0;
		Json::FastWriter writer;
		ret = db.SetGift(uid,writer.write(gt));
		if (ret != 0)
			return R_ERR_DATA;

		result["happycard"]["hcShowArr"] = gt["happycard"]["hcShowArr"];
		result["happycard"]["hcChoosArr"] = gt["happycard"]["hcChoosArr"];
		result["happycard"]["hcmfsx"] = gt["happycard"]["hcmfsx"];

		CLogicPay logicPay;
		DataPay payData;
		ret = logicPay.ChangePay(uid, 60, 0, "happyCard",payData);
		if (ret != 0)
			return ret;

		result["coins"] = payData.coins;	//金币
		result["coins2"] = payData.cash;	//钻石
	}
	else
		return R_ERR_DATA;

	ret = logicUser.SetUserLimit(uid, dataUser);
	if(ret)
		return ret;

	return R_SUCCESS;
}

int CLogicCMD::UpgradeHero(unsigned uid, int target, int source[XML_HERO_SOURCE], Json::Value &result,unsigned &lasttime,unsigned &seqid)
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

	unsigned i;
	CLogicHero logicHero;
	map<unsigned,Json::Value> data;
	ret = logicHero.GetHero(uid,data);
	if(ret)
		return ret;

	if(!data.count(target))
	{
		error_log("[target not exist]");
		return R_ERR_DATA;
	}
	for(i=0;i<XML_HERO_SOURCE;++i)
	{
		if(source[i] != XML_HERO_SELF && !data.count(source[i]))
		{
			error_log("[source not exist]");
			return R_ERR_DATA;
		}
	}
	string hidts,hids[XML_HERO_SOURCE];
	unsigned hidt,hid[XML_HERO_SOURCE],st,s[XML_HERO_SOURCE],t[XML_HERO_SOURCE];
	if(!Json::GetString(data[target],"id",hidts))
	{
		error_log("[target hid or star error]");
		return R_ERR_DATA;
	}
	hidts = hidts.substr(1);
	hidt = CTrans::STOI(hidts);
	if(!Json::GetUInt(data[target],"star",st))
		st = 1;
	for(i=0;i<XML_HERO_SOURCE;++i)
	{
		hid[i] = t[i] = s[i] = 0;
		if(source[i] != XML_HERO_SELF)
		{
			if(!Json::GetString(data[source[i]],"id",hids[i]))
			{
				error_log("[source hid or star error]");
				return R_ERR_DATA;
			}
			hids[i] = hids[i].substr(1);
			hid[i] = CTrans::STOI(hids[i]);
			if(!Json::GetUInt(data[source[i]],"star",s[i]))
				s[i] = 1;
		}
	}

	CDataXML *pDataXML = CDataXML::GetCDataXML();
	if(!pDataXML)
	{
		cout << "GetCDataXML fail" << endl;
		return R_ERR_DATA;
	}
	XMLHero hero;
	for(i=0;i<XML_HERO_SOURCE;++i)
	{
		if(hid[i])
		{
			ret = pDataXML->GetHero(hid[i], hero);
			if(ret)
			{
				error_log("GetHero fail uid=%u", uid);
				return R_ERR_DATA;
			}
			t[i] = hero.type;
		}
	}
	ret = pDataXML->GetHero(hidt, hero);
	if(ret)
	{
		error_log("GetHero fail uid=%u", uid);
		return R_ERR_DATA;
	}
	if(!hero.mix)
		return R_ERR_DATA;
	XMLSourceHero mixhero[XML_HERO_SOURCE];
	ret = pDataXML->GetMixHero(hero.mix, st + 1 ,mixhero);
	if(ret)
	{
		error_log("GetMixHero fail uid=%u", uid);
		return R_ERR_DATA;
	}

	for(i=0;i<XML_HERO_SOURCE;++i)
	{
		if(mixhero[i].star && mixhero[i].star > s[i])
		{
			error_log("mix star fail uid=%u,i=%u", uid,i);
			return R_ERR_LOGIC;
		}
		if(mixhero[i].type && mixhero[i].type > t[i])
		{
			error_log("mix type fail uid=%u,i=%u", uid,i);
			return R_ERR_LOGIC;
		}
		if(mixhero[i].heroId == XML_HERO_SELF)
			mixhero[i].heroId = hidt;
		if(mixhero[i].heroId && mixhero[i].heroId != hid[i])
		{
			error_log("mix id fail uid=%u,i=%u", uid,i);
			return R_ERR_LOGIC;
		}
	}

	Json::FastWriter writer;
	for(i=0;i<XML_HERO_SOURCE;++i)
	{
		if(source[i] != XML_HERO_SELF)
		{
			ret = logicHero.Del(uid,source[i]);
			if(ret)
			{
				error_log("DelHero fail uid=%u", uid);
				return R_ERR_DATA;
			}
			string heroData = writer.write(data[source[i]]);
			HERO_LOG("uid=%u,id=%u,heroid=%s,act=%s,code=%s,data=%s",uid,source[i],hids[i].c_str(),"del"
					,"up",heroData.c_str());
		}
	}
	data[target]["star"] = st + 1;
	ret = logicHero.Chg(uid,target,data[target]);
	if(ret)
	{
		error_log("ChgHero fail uid=%u", uid);
		return R_ERR_DATA;
	}
	string heroData = writer.write(data[target]);
	HERO_LOG("uid=%u,id=%u,heroid=%s,act=%s,code=%s,data=%s",uid,target,hidts.c_str(),"up"
			,"up",heroData.c_str());


	ret = logicUser.SetUserLimit(uid, dataUser);
	if(ret)
		return ret;

	return R_SUCCESS;
}

int CLogicCMD::GetUpgradeHeroForActivity(unsigned uid, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	if(Time::GetGlobalTime() < Config::GetIntValue(CONFIG_WUJIANGSHEGNXING_BEGIN_TS)
	|| Time::GetGlobalTime() >= Config::GetIntValue(CONFIG_WUJIANGSHEGNXING_END_TS))
		return R_ERR_LOGIC;

	CDataXML *pDataXML = CDataXML::GetCDataXML();
	if(!pDataXML)
	{
		cout << "GetCDataXML fail" << endl;
		return R_ERR_DATA;
	}
	XMLHero hero;

	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	int ret = logicUser.GetUserLimit(uid,dataUser);
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

	bool new2 = false;
	Json::Value newAct, newAct2;
	CLogicSecinc logicSecinc;
	ret = logicSecinc.GetSecinc(uid, NAT_FREE_MIX_HERO_1, newAct);
	if (ret == R_ERR_NO_DATA)
	{
		new2 = true;
		Json::Value array(Json::arrayValue);
		for(unsigned i = 0; i < CONFIG_WUJIANGSHEGNXING_ITEM; i++)
			array.append(0);
		newAct["id"] = NAT_FREE_MIX_HERO_1;
		newAct["lingqu"] = array;
		newAct["v"] = Config::GetIntValue(CONFIG_WUJIANGSHEGNXING_VER);
	}
	else if(ret)
		return ret;
	if(Config::GetIntValue(CONFIG_WUJIANGSHEGNXING_VER) != newAct["v"].asInt())
	{
		new2 = true;
		Json::Value array(Json::arrayValue);
		for(unsigned i = 0; i < CONFIG_WUJIANGSHEGNXING_ITEM; i++)
			array.append(0);
		newAct["lingqu"] = array;
		newAct["v"] = Config::GetIntValue(CONFIG_WUJIANGSHEGNXING_VER);
	}
	if(new2)
	{
		Json::Value array(Json::arrayValue);
		for(unsigned i = 0; i < CONFIG_WUJIANGSHEGNXING_ITEM; i++)
			array.append(0);
		newAct2["id"] = NAT_FREE_MIX_HERO_2;
		newAct2["usetimes"] = array;
	}
	else
	{
		ret = logicSecinc.GetSecinc(uid, NAT_FREE_MIX_HERO_2, newAct2);
		if(ret)
			return ret;
	}

	CLogicHero logicHero;
	map<unsigned,Json::Value> data;
	ret = logicHero.GetHero(uid,data);
	if(ret)
		return ret;

	unsigned l[CONFIG_WUJIANGSHEGNXING_ITEM] = {0};
	for(map<unsigned,Json::Value>::iterator it=data.begin();it!=data.end();++it)
	{
		Json::Value &t = it->second;
		unsigned star = 0;
		Json::GetUInt(t, "star", star);
		if(star < CONFIG_WUJIANGSHEGNXING_MIN || star > CONFIG_WUJIANGSHEGNXING_MAX)
			continue;
		string id;
		Json::GetString(t, "id", id);
		ret = pDataXML->GetHero(CDataXML::Str2Hero(id), hero);
		if(ret)
			return ret;
		unsigned type = min(unsigned(CONFIG_WUJIANGSHEGNXING_TYPE), hero.type);
		++l[(star-CONFIG_WUJIANGSHEGNXING_MIN)*CONFIG_WUJIANGSHEGNXING_TYPE+type-1];
	}
	for(unsigned i=0;i<CONFIG_WUJIANGSHEGNXING_ITEM;++i)
	{
		l[i] = min(unsigned(CONFIG_WUJIANGSHEGNXING_TIMES), l[i]);
		unsigned k = newAct["lingqu"][i].asUInt();
		if(k >= CONFIG_WUJIANGSHEGNXING_TIMES || l[i] <= k)
			continue;
		newAct2["usetimes"][i] = newAct2["usetimes"][i].asUInt() + (l[i] - k);
		newAct["lingqu"][i] = l[i];
	}

	ret = logicSecinc.SetOneSecinc(uid, newAct);
	if(ret)
		return ret;
	ret = logicSecinc.SetOneSecinc(uid, newAct2);
	if(ret)
		return ret;
	result["newAct"].resize(0);
	result["newAct"].append(newAct);
	result["newAct"].append(newAct2);

	ret = logicUser.SetUserLimit(uid, dataUser);
	if(ret)
		return ret;

	return R_SUCCESS;
}
int CLogicCMD::UpgradeHeroForActivity(unsigned uid, int target, int source[XML_HERO_SOURCE], Json::Value &result, unsigned lasttime, unsigned seqid)
{
	if(Time::GetGlobalTime() < Config::GetIntValue(CONFIG_WUJIANGSHEGNXING_BEGIN_TS)
	|| Time::GetGlobalTime() >= Config::GetIntValue(CONFIG_WUJIANGSHEGNXING_END_TS))
		return R_ERR_LOGIC;

	unsigned count_negative = 0;
	int      index_negative = -1;
	for (int ix = 0; ix < XML_HERO_SOURCE; ++ix)
	{
		if (source[ix] <= 0)
		{
			++count_negative;
			index_negative = ix;
		}
	}
	if (count_negative != 1 || index_negative==-1)
	{
		error_log("[In UpgradeHeroForActivity:: the parameter must only have one negative]");
		return R_ERR_LOGIC;
	}

	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	int ret = logicUser.GetUserLimit(uid,dataUser);
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


	CLogicHero logicHero;
	map<unsigned,Json::Value> data;
	ret = logicHero.GetHero(uid,data);
	if(ret)
		return ret;

	if(!data.count(target))
	{
		error_log("[target not exist]");
		return R_ERR_DATA;
	}
	for (int ix = 0; ix < XML_HERO_SOURCE; ++ix)
	{
		if (index_negative != ix)
		{
			if(!data.count(source[ix]))
			{
				error_log("[source of real  not exist]");
				return R_ERR_DATA;
			}
			if (target == source[ix])
			{
				error_log("UpgradeHeroForActivity: source is target uid=%u", uid);
				return R_ERR_LOGIC;
			}

		}
	}

	string  hidt_str, hid_source_str[XML_HERO_SOURCE];
	unsigned hidt, hid_source[XML_HERO_SOURCE];
	unsigned star_target, star_source[XML_HERO_SOURCE];
	unsigned type_source[XML_HERO_SOURCE];

	if(!Json::GetString(data[target],"id",hidt_str))
	{
		error_log("[target hid or star error]");
		return R_ERR_DATA;
	}
	hidt_str = hidt_str.substr(1);
	hidt = CTrans::STOI(hidt_str);
	if(!Json::GetUInt(data[target],"star",star_target))
		star_target = 1;

	Json::Value newAct;
	CLogicSecinc logicSecinc;
	ret = logicSecinc.GetSecinc(uid, NAT_FREE_MIX_HERO_1, newAct);
	if(ret)
		return ret;
	if(Config::GetIntValue(CONFIG_WUJIANGSHEGNXING_VER) != newAct["v"].asInt())
		return R_ERR_LOGIC;

	Json::Value   can_use_all_data;
	ret = logicSecinc.GetSecinc(uid, NAT_FREE_MIX_HERO_2, can_use_all_data);
	if (ret != 0)
		return ret;
	Json::Value   arr_can_use(Json::arrayValue);
	if(!Json::GetArray(can_use_all_data,"usetimes",arr_can_use))
	{
		error_log("[UpgradeHeroForActivity:GetArray  error]");
		return R_ERR_DATA;
	}
	unsigned can_use_correspond_times = 0;
	unsigned free_real_index = -source[index_negative];


	if(!Json::GetUInt(arr_can_use,free_real_index,can_use_correspond_times))
	{
		error_log("[UpgradeHeroForActivity:GetUInt  error]");
		return R_ERR_DATA;
	}
	if(can_use_correspond_times < 1)
	{
		error_log("[can_use_correspond_times is 0  error]");
		return R_ERR_LOGIC;
	}

	can_use_all_data["usetimes"][free_real_index] = can_use_correspond_times -1;
	type_source[index_negative] = WJ_SHENGXING_CH[free_real_index];
	star_source[index_negative] = WJ_SHENGXING_STAR[free_real_index];

	CDataXML *pDataXML = CDataXML::GetCDataXML();
	if(!pDataXML)
	{
		cout << "GetCDataXML fail" << endl;
		return R_ERR_DATA;
	}

	XMLHero hero;
	for(int ix = 0; ix < XML_HERO_SOURCE; ++ix)
	{
		if (index_negative != ix)
		{
			if(!Json::GetString(data[source[ix]],"id",hid_source_str[ix]))
			{
				error_log("[source hid or star error]");
				return R_ERR_DATA;
			}
			hid_source_str[ix] = hid_source_str[ix].substr(1);
			hid_source[ix] = CTrans::STOI(hid_source_str[ix]);
			ret = pDataXML->GetHero(hid_source[ix], hero);
			if(ret)
			{
				error_log("GetHero fail uid=%u", uid);
				return R_ERR_DATA;
			}
			type_source[ix] = hero.type;

			if(!Json::GetUInt(data[source[ix]],"star",star_source[ix]))
				star_source[ix] = 1;

		}
	}

	ret = pDataXML->GetHero(hidt, hero);
	if(ret)
	{
		error_log("GetHero target fail uid=%u", uid);
		return R_ERR_DATA;
	}
	if(!hero.mix)
		return R_ERR_DATA;
	XMLSourceHero mixhero[XML_HERO_SOURCE];
	ret = pDataXML->GetMixHero(hero.mix, star_target + 1 ,mixhero);
	if(ret)
	{
		error_log("GetMixHero fail uid=%u", uid);
		return R_ERR_DATA;
	}

	for (int ix = 0; ix < XML_HERO_SOURCE; ++ix)
	{
		if (index_negative != ix)
		{
			if(mixhero[ix].star && mixhero[ix].star > star_source[ix])
			{
				error_log("mix star hero fail uid=%u", uid);
				return R_ERR_LOGIC;
			}
			if(mixhero[ix].type && mixhero[ix].type > type_source[ix])
			{
				error_log("mix type hero fail uid=%u", uid);
				return R_ERR_LOGIC;
			}
			if(mixhero[ix].heroId == XML_HERO_SELF)
				mixhero[ix].heroId = hidt;
			if(mixhero[ix].heroId && mixhero[ix].heroId != hid_source[ix])
			{
				error_log("mix id hero fail uid=%u", uid);
				return R_ERR_LOGIC;
			}
		} else
		{
			if (mixhero[ix].heroId)
			{
				error_log("mix hero is no free uid=%u", uid);
				return R_ERR_LOGIC;
			} else
			{
				if(mixhero[ix].star && mixhero[ix].star > star_source[ix])
				{
					error_log("mix hero  star fail uid=%u", uid);
					return R_ERR_LOGIC;
				}
				if(mixhero[ix].type && mixhero[ix].type > type_source[ix])
				{
					error_log("mix hero  type fail uid=%u", uid);
					return R_ERR_LOGIC;
				}
			}
		}
	}

	ret = logicSecinc.SetOneSecinc(uid, can_use_all_data);
	if(ret != 0)
	{
		error_log("UpgradeHeroForActivity::SetOneSecinc fail uid=%u", uid);
		return ret;
	}
	result["newAct"] = can_use_all_data;

	string heroData;
	Json::FastWriter writer;
	for (int ix = 0; ix < XML_HERO_SOURCE; ++ix)
	{
		if (index_negative != ix)
		{
			ret = logicHero.Del(uid,source[ix]);
			if(ret)
			{
				error_log("DelHero source fail uid=%u", uid);
				return R_ERR_DATA;
			}
			heroData = writer.write(data[source[ix]]);
			HERO_LOG("uid=%u,id=%u,heroid=%s,act=%s,code=%s,data=%s",uid,source[ix],hid_source_str[ix].c_str(),"del"
					,"up",heroData.c_str());
		}
	}

	data[target]["star"] = star_target + 1;
	ret = logicHero.Chg(uid,target,data[target]);
	if(ret)
	{
		error_log("ChgHero  target fail uid=%u", uid);
		return R_ERR_DATA;
	}
	heroData = writer.write(data[target]);
	HERO_LOG("uid=%u,id=%u,heroid=%s,act=%s,code=%s,data=%s",uid,target,hidt_str.c_str(),"up"
			,"up",heroData.c_str());

	ret = logicUser.SetUserLimit(uid, dataUser);
	if(ret)
		return ret;

	return R_SUCCESS;
}

int CLogicCMD::TreasureHunt(unsigned uid, unsigned type, unsigned times, unsigned equd, Json::Value &result, unsigned &lasttime,unsigned &seqid)
{
	if(Time::GetGlobalTime() < Config::GetIntValue(CONFIG_TREASURE_BEGIN_TS) ||
	   Time::GetGlobalTime() > Config::GetIntValue(CONFIG_TREASURE_END_TS))
	{
		error_log("activity_TreasureHunt_time_error");
		return R_ERR_REFUSE;
	}
	if(type == 0 && times > 1)
		return R_ERR_PARAM;

	unsigned id = 0, point = 0, jade = 0, diamond = 0, gold = XML_TREASURE_COIN;
	int ret = 0;
	CDataXML *dataXML = CDataXML::GetCDataXML();
	if(!dataXML)
	{
		error_log("GetInitXML fail");
		return R_ERR_DB;
	}

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

	Json::Value stats;
	Json::Reader reader;
	reader.parse(dataUser.user_stat,stats);
	Json::FastWriter writer;
	Json::Value user_flag;
	bool bsave = false;
	reader.parse(dataUser.user_flag,user_flag);

	Json::GetUInt(stats,"trhs",id);
	Json::GetUInt(stats,"trpt",point);
	Json::GetUInt(stats,"trhj",jade);
	Json::GetUInt(stats,"trhg",gold);
	Json::GetUInt(stats,"trhd",diamond);

	if(!id)
		id = 1;
	vector<TreasureHuntItem> res;
	ret = dataXML->GetTreasureHunt(id,times,res);
	if(ret)
		return ret;

//zkw add
	CLogicSecinc Secinc;
	Json::Value SecincData;
	ret = Secinc.GetSecinc(uid, NAT_TREASURE_HUNT, SecincData);
	if(ret!=0 && ret!=R_ERR_NO_DATA)
	{
		return ret;
	}

	if(!SecincData.isMember("id"))
	{
		SecincData["id"] = NAT_TREASURE_HUNT;
	}
	if(!SecincData.isMember("ver") || SecincData["ver"].asInt() != Config::GetIntValue(CONFIG_TREASURE_VER))
	{
		SecincData["ver"] = Config::GetIntValue(CONFIG_TREASURE_VER);
	}
	if(!SecincData.isMember("fts") || !SecincData.isMember("fc") || !Time::IsToday(SecincData["fts"].asUInt()))
	{
		SecincData["fc"] = NAT_TREASURE_HUNT_FREE_NUM;
		SecincData["fts"] = Time::GetGlobalTime();
	}
	unsigned fc = SecincData["fc"].asUInt();
	if (fc > NAT_TREASURE_HUNT_FREE_NUM)
	{
		error_log("TREASURE_HUNT free times illegal");
		return R_ERR_LOGIC;
	}
//zkw add over

	if(type == 0)
	{
		if (fc == 0)  { ++gold; }
		result["trhg"] = stats["trhg"] = gold;
	}
	else
	{
		diamond += times;
		if(diamond > DESS_DIAMOND_MAX)
			return R_ERR_LOGIC;
		result["trhd"] = stats["trhd"] = diamond;
	}

	CLogicPay logicPay;
	DataPay payData;
	if (0 == type && fc)
	{
		//单次投掷才可以用
		--fc;
		SecincData["fc"] = fc;
		//ret = logicPay.ProcessOrderForBackend(uid, type?-(XML_TREASURE_CASH*times):0, 0, payData, type?"activity_treasurehunt_dice_diamond":"activity_treasurehunt_dice_gold",user_flag,bsave);
		ret = 0;
	}
	else
	{
		#ifdef SG_USE_CASH
			ret = logicPay.ProcessOrderForBackend(uid, type?-(XML_TREASURE_CASH*times):0, type?0:-(int)(gold-1+5), payData, type?"activity_treasurehunt_dice_diamond":"activity_treasurehunt_dice_gold",user_flag,bsave);
			result["coins"] = payData.coins;
			result["coins2"] = payData.cash;
		#else
			//金币抽奖原本所需要的金币道具换成同等数量的绿色密钥、钻石抽奖（紫色密钥*2)、自动投掷（紫色密钥*40）
			CLogicEquipment equipment;
			//花费钻石与花费道具数量的比例是100:20 即5:1
			int cost_eqid = 0;
			int count = 0;

			if (0 == type)
			{
				//金币
				cost_eqid = green_key;
				count = gold-1+5;
			}
			else
			{
				//钻石
				cost_eqid = purple_key;
				const int per_times_cost = 2; //一次次数对应的密钥消耗个数
				count = per_times_cost*times;
			}

			ret = equipment.UseEquipment(uid, cost_eqid, equd, count, type?"activity_treasurehunt_dice_purple":"activity_treasurehunt_dice_green");
		#endif
	}

	if(ret)
		return ret;
	result["pointpay"].resize(0);

	if(bsave)
	{
		result["pointpay"] = user_flag["user_pay"];
		dataUser.user_flag = writer.write(user_flag);
	}

	CLogicEquipment logicEquipment;
	vector<ItemAdd> items;

	for(int i=0;i<res.size();++i)
	{
		if(id > res[i].id)
			jade += 5;
		id = res[i].id;
		point += res[i].point;
		jade += res[i].jade;
		if(res[i].equip)
		{
			ItemAdd temp;
			temp.eqid = res[i].equip;
			temp.count = res[i].count;
			temp.reason = "TreasureHunt";
			items.push_back(temp);
		}
	}

	result["trpt"] = stats["trpt"] = point;
	result["trhj"] = stats["trhj"] = jade;
	result["trhs"] = stats["trhs"] = id;

	if(items.size())
		ret = logicEquipment.AddItems(uid,items,result["equip"], true);
	if(ret)
		return ret;

	ret = Secinc.SetOneSecinc(uid, SecincData);

	if(ret)
		return ret;

	result["newAct"] = SecincData;

	dataUser.user_stat = writer.write(stats);
	ret = logicUser.SetUser(uid, dataUser);
	if(ret)
		return ret;

	return R_SUCCESS;
}

int CLogicCMD::DigEquipSubStone(unsigned uid, unsigned type, unsigned equd, Json::Value &result,unsigned &lasttime,unsigned &seqid)
{
	if(Time::GetGlobalTime() < Config::GetIntValue(CONFIG_ACTIVITY_DIG_STONE_B_TS)
	|| Time::GetGlobalTime() > Config::GetIntValue(CONFIG_ACTIVITY_DIG_STONE_E_TS))
		return R_ERR_AUTH;

	if(type > 2)
		return R_ERR_PARAM;

	int ret = 0;
	CDataXML *dataXML = CDataXML::GetCDataXML();
	if(!dataXML)
	{
		error_log("GetInitXML fail");
		return R_ERR_DB;
	}

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

	Json::Value stats;
	Json::Reader reader;
	reader.parse(dataUser.user_stat,stats);
	Json::FastWriter writer;
	Json::Value user_flag;
	bool bsave = false;
	reader.parse(dataUser.user_flag,user_flag);

	if(!stats.isMember("DESS") || !stats["DESS"].isArray() || stats["DESS"].size() != 3)
	{
		stats.removeMember("DESS");
		stats["DESS"].resize(3);
		stats["DESS"][0u] = stats["DESS"][1u] = stats["DESS"][2u] = 0;
	}

	unsigned nowtimes = 0;
	Json::GetUInt(stats["DESS"], type, nowtimes);
	if(nowtimes > DESS_TIME[type])
		return R_ERR_LOGIC;

//zkw add
	CLogicSecinc Secinc;
	Json::Value SecincData;
	ret = Secinc.GetSecinc(uid, NAT_DIGEQUIP_SUBSTONE, SecincData);
	if(ret!=0 && ret!=R_ERR_NO_DATA)
	{
		return ret;
	}

	if(!SecincData.isMember("id"))
	{
		SecincData["id"] = NAT_DIGEQUIP_SUBSTONE;
	}
	if(!SecincData.isMember("ver") || SecincData["ver"].asInt() != Config::GetIntValue(CONFIG_ACTIVITY_DIG_STONE_VER))
	{
		SecincData["ver"] = Config::GetIntValue(CONFIG_ACTIVITY_DIG_STONE_VER);
	}
	if(!SecincData.isMember("fts") || !SecincData.isMember("fc") || !Time::IsToday(SecincData["fts"].asUInt()))
	{
		SecincData["fc"] = NAT_DIGEQUIP_SUBSTONE_FREE_NUM;
		SecincData["fts"] = Time::GetGlobalTime();
	}
	unsigned fc = SecincData["fc"].asUInt();
	if (fc > NAT_DIGEQUIP_SUBSTONE_FREE_NUM)
	{
		error_log("DIGEQUIP_SUBSTONE_FREE times illegal");
		return R_ERR_LOGIC;
	}

	if ((0 == type) && fc) {
		stats["DESS"][type] = nowtimes;
	} else {
		stats["DESS"][type] = nowtimes + 1;
	}
//zkw add over

	CLogicPay logicPay;
	DataPay payData;
	if ((0==type) && fc)
	{
		//只针对初级挖矿进行免费次数扣除
		--fc;
		SecincData["fc"] = fc;
		ret = 0;
	}
	else
	{
		#ifdef SG_USE_CASH
			ret = logicPay.ProcessOrderForBackend(uid, type?-DESS_COST[type]:0, type?0:-DESS_COST[type], payData, type?"activity_DESS_dice_diamond":"activity_DESS_dice_gold",user_flag,bsave);
			result["cash"] = payData.cash;
			result["coins"] = payData.coins;
		#else
			//金币抽奖原本所需要的金币道具换成同等数量的绿色密钥、钻石抽奖（紫色密钥*2)、自动投掷（紫色密钥*40）
			CLogicEquipment equipment;
			int cost_eqid = 0;
			int count = 0;

			if (0 == type)
			{
				//初始
				cost_eqid = green_key;
				count = DESS_COST[type]; //1金/个绿色密钥
			}
			else
			{
				//中级或高级
				cost_eqid = purple_key;
				count = DESS_COST[type]/5; //5钻/个紫色密钥
			}

			ret = equipment.UseEquipment(uid, cost_eqid, equd, count, type?"activity_DESS_dice_purple":"activity_DESS_dice_green");
		#endif
	}

	if(ret)
		return ret;
	result["pointpay"].resize(0);
	if(bsave)
	{
		result["pointpay"] = user_flag["user_pay"];
		dataUser.user_flag = writer.write(user_flag);
	}

	unsigned rate = Math::GetRandomInt(100);
	for(unsigned i=0;i<5;++i)
	{
		if(rate < DESS_RATE[type][i])
		{
			CLogicEquipment logicEquipment;
			ret = logicEquipment.AddOneItem(uid, DESS_STONE_ID[type], DESS_STONE[type][i],"DESS",result["equip"], true);
			if(ret)
				return ret;
			break;
		}
	}

	ret = Secinc.SetOneSecinc(uid, SecincData);
	if(ret)
		return ret;

	dataUser.user_stat = writer.write(stats);
	ret = logicUser.SetUser(uid, dataUser);
	if(ret)
		return ret;

	return R_SUCCESS;
}

int CLogicCMD::getSubNumByCh(unsigned ch)
{
	const unsigned subNum[XML_EQUIP_SUB_GOLD + 2] = {0, 1, 3, 5, 5, 5};
	if(ch > XML_EQUIP_SUB_GOLD + 2)
		ch = 0;
	else
		--ch;
	return subNum[ch];
}

int CLogicCMD::checkLastSaveUID(DataUser &user)
{
	if (IsBeingAttacked(user.last_breath_time))
	{
		//error_log("[being_attacked][uid=%u,last_breath_time=%u]",user.uid,user.last_breath_time);
		LOGIC_ERROR_RETURN_MSG("u_being_attacked");
	}
	if(user.last_save_uid != user.uid )
	{
		error_log("[last_save_uid_mismatch][operator=%u,user_last_save_uid=%u]",user.uid, user.last_save_uid);
		LOGIC_ERROR_RETURN_MSG("last_save_uid_mismatch");
	}
	return R_SUCCESS;
}
int CLogicCMD::checkLastSaveTime(DataUser &user,unsigned lasttime,unsigned seqid)
{
	if (lasttime != user.last_save_time || seqid != user.lastseq + 1)
	{
		error_log(
			"[lasttime_mismatch][operator=%u,lasttime=%u,last_save_time=%u,seqid=%u,lastseq=%u]",
			user.uid, lasttime, user.last_save_time, seqid, user.lastseq);
		LOGIC_ERROR_RETURN_MSG("lasttime_mismatch");
	}
	user.last_save_time = Time::GetGlobalTime();
	user.lastseq = seqid;
	return R_SUCCESS;
}

int CLogicCMD::useGiftBag(unsigned uid,unsigned ud,unsigned count,Json::Value &result,unsigned seqid,unsigned lasttime)
{
	int ret = 0;
	Json::FastWriter writer;
	Json::Reader reader;

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

	Json::Value Equip_data;
	Equip_data.clear();
	CLogicEquipment Equip;
	ret = Equip.Get(uid, ud, Equip_data);
	if(ret)
	{
		error_log("[giftbagId_ud_error][uid=%u,ud=%u]",uid,ud);
		return R_ERROR;
	}

	unsigned giftbagId = Equip_data["id"].asUInt();
	ret = Equip.UseEquipment(uid, giftbagId,ud,count, "use_giftbag");
	if(ret)
	{
		error_log("use_giftbag_fail uid=%u | giftbagId=%u", uid , giftbagId);
		return R_ERR_DATA;
	}

	return _useGiftBag(dataUser, giftbagId, count, result);
}
//调用者必须是使用CLogicUser::GetUser加载的dataUser
int CLogicCMD::_useGiftBag(DataUser& dataUser, unsigned giftbagId, unsigned count, Json::Value &result)
{
	unsigned uid = dataUser.uid;
	Json::FastWriter writer;
	Json::Reader reader;
	CLogicUser logicUser;

	CDataXML *pDataXML = CDataXML::GetCDataXML();
	if(!pDataXML)
	{
		error_log("GetInitXML fail");
		return R_ERR_DB;
	}

	Json::Value data;
	data.clear();
	int ret = pDataXML->GetGiftBag(uid,giftbagId,count,data);
	if(ret)
	{
		error_log("[get_giftdata_error] [uid=%u | giftbagId=%u]", uid , giftbagId);
		return R_ERR_DATA;
	}

	vector<ItemAdd> equip_items;
	vector<HeroAdd> hero;
	vector<pair<unsigned,unsigned> > juexue_id;

	unsigned coins = 0;
	unsigned prosper = 0;
	unsigned rs1 = 0;
	unsigned rs2 = 0;
	unsigned rs3 = 0;
	unsigned rs4 = 0;
	unsigned longlin = 0;
	unsigned qihun = 0;
	unsigned tongqian = 0;

	for(int i = 0;i < data.size();++i)
	{
		Json::Value::Members members(data[i].getMemberNames());
		for (Json::Value::Members::iterator it = members.begin(); it != members.end(); ++it)
		{
			string type = *it;
//			string e_data = writer.write(data[i]);
//			debug_log("test: %s",e_data.c_str());
			if(type.find("equip") != string::npos )
			{
				if(!data[i][type].isMember("ch"))
				{
					data[i][type]["ch"] = "0";
				}
				ItemAdd eqip;
				eqip.eqid = data[i][type]["id"].asUInt();
				eqip.count = data[i][type]["c"].asUInt();
				eqip.q = data[i][type]["q"].asUInt();
				eqip.ch = CTrans::STOI(data[i][type]["ch"].asString());
				if(data[i][type].isMember("ats"))
					eqip.ats = data[i][type]["ats"].asUInt() * 86400;
				if(data[i][type].isMember("xwexp"))
					eqip.xwexp = data[i][type]["xwexp"].asUInt();
				if(data[i][type].isMember("xwsub"))
					eqip.xwsub = data[i][type]["xwsub"];
				if(data[i][type].isMember("sexp"))
					eqip.sexp = data[i][type]["sexp"].asUInt();
				if(data[i][type].isMember("lexp"))
					eqip.lexp = data[i][type]["lexp"].asUInt();
				if(data[i][type].isMember("hexp"))
					eqip.hexp = data[i][type]["hexp"].asUInt();
				string reason = "from_useGiftbag_";
				eqip.reason = reason.append(CTrans::UTOS(giftbagId));
				equip_items.push_back(eqip);
			}
			else if(type.find("hero") != string::npos)
			{
				string code = "from_useGiftbag_";
				code.append(CTrans::UTOS(giftbagId));
				string id = CDataXML::Hero2Str(data[i][type]["id"].asUInt());
				unsigned star = 1, l = 1;
				Json::GetUInt(data[i][type], "star", star);
				Json::GetUInt(data[i][type], "l", l);
				hero.push_back(HeroAdd(id, code, star, l));
			}
			else if(type.find("prosper") != string::npos)		//威望
			{
				prosper += data[i][type].asUInt();
			}
			else if(type.find("rs1") != string::npos)			 //资源
			{
				rs1 += data[i][type].asUInt();
			}
			else if(type.find("rs2") != string::npos)			//资源
			{
				rs2 += data[i][type].asUInt();
			}
			else if(type.find("rs3") != string::npos)			//资源
			{
				rs3 += data[i][type].asUInt();
			}
			else if(type.find("rs4") != string::npos)			//资源
			{
				rs4 += data[i][type].asUInt();
			}
			else if(type.find("juexue") != string::npos)			//绝学
			{
				unsigned juexue = 0, exp;
				Json::GetUInt(data[i][type], "id", juexue);
				Json::GetUInt(data[i][type], "exp", exp);
				juexue_id.push_back(make_pair(juexue,exp));
			}
			else if(type.find("longlin") != string::npos)			//龙鳞
			{
				longlin += data[i][type].asUInt();
			}
			else if(type.find("gold") != string::npos)
			{
				if(type.find("newgold") != string::npos)			//随机金币礼包
				{
					unsigned minrate = data[i][type]["min"].asUInt();
					unsigned interval_rate = data[i][type]["max"].asUInt() - minrate + 1;
					unsigned add_coins = Math::GetRandomInt(interval_rate) + minrate;
					coins += add_coins;
				}
				else									//普通金币礼包
				{
					coins += data[i][type].asUInt();
				}
			}
			else if(type.find("qh") != string::npos)  //器魂
			{
				qihun += data[i][type].asUInt();
			}
			else if(type.find("tongqian") != string::npos)  //铜钱
			{
				tongqian += data[i][type].asUInt();
			}
		}
	}

	if(equip_items.size() > 0)
	{
		CLogicEquipment Equip;
		ret = Equip.AddItems(uid,equip_items,result["add_equip"], true);
		if(ret)
		{
			error_log("Add_Equip_error uid=%u | giftbagId=%u", uid , giftbagId);
			return R_ERR_DATA;
		}
	}

	if(hero.size() > 0)
	{
		CLogicHero Hero;
		ret = Hero.AddHeros(uid,hero,result["hero"]);
		if(ret)
		{
			error_log("Add_hero_error uid=%u | giftbagId=%u", uid , giftbagId);
			return R_ERR_DATA;
		}
	}

	if(coins > 0)
	{
		CLogicPay logicPay;
		ret = logicPay.ChangePay(uid, 0, coins, "use_giftbag_add_coins");
		if(ret)
		{
			error_log("[Add_coins_error] [uid=%u | giftbagId=%u]", uid , giftbagId);
			return R_ERROR;
		}
		result["coins"] = coins;
	}

	if(juexue_id.size() > 0)
	{
		Json::Value user_tech;
		user_tech.clear();
		reader.parse(dataUser.user_tech,user_tech);
		for(int i = 0; i < juexue_id.size(); ++i)
		{
			int flag = 0;
			for(int j=0;j<20;j++)
			{
				if(user_tech["baglist"][j][0u].asInt() ==0)
				{
					user_tech["baglist"][j][0u] = juexue_id[i].first;
					user_tech["baglist"][j][1u] = juexue_id[i].second;
					flag =1;
					break;
				}
			}
			if(flag == 0)
			{
				error_log("[juexue_baglist_is_full][uid=%u | juexue_id=%u]",uid,juexue_id[i].first);
			}
			HERO_LOG("uid=%u,id=%u,heroid=%s,act=juexue,juexue_id=%u,exp=%u",uid,0,"0",juexue_id[i].first,juexue_id[i].second);
		}
		dataUser.user_tech = writer.write(user_tech);
		result["juexue"] =user_tech["baglist"];

	}

	unsigned total_longlin = 0;
	if(longlin > 0)
	{
		Json::Value user_tech;
		user_tech.clear();
		reader.parse(dataUser.user_tech,user_tech);
		if(!user_tech.isMember("yinliang"))
		{
			user_tech["yinliang"] = longlin;
		}
		else
		{
			unsigned total_longlin = user_tech["yinliang"].asUInt() + longlin;
			user_tech["yinliang"] = total_longlin;
		}
		dataUser.user_tech = writer.write(user_tech);
		total_longlin = user_tech["yinliang"].asUInt();
		result["longlin"] = user_tech["yinliang"].asUInt();
	}

	if(prosper > 0 || rs1 > 0 || rs2 > 0 || rs3 > 0 || rs4 > 0 || tongqian > 0)
	{
		dataUser.prosper += prosper;
		dataUser.r1 += rs1;
		dataUser.r2 += rs2;
		dataUser.r3 += rs3;
		dataUser.r4 += rs4;
		if(dataUser.r1 > dataUser.r1_max)
			dataUser.r1 = dataUser.r1_max;
		if(dataUser.r2 > dataUser.r2_max)
			dataUser.r2 = dataUser.r2_max;
		if(dataUser.r3 > dataUser.r3_max)
			dataUser.r3 = dataUser.r3_max;
		if(dataUser.r4 > dataUser.r4_max)
			dataUser.r4 = dataUser.r4_max;
		dataUser.type += tongqian;
	}

	unsigned total_qihun = 0;
	if (qihun > 0 )
	{
		Json::Value tech;
		reader.parse(dataUser.user_tech, tech);

		if (!tech.isMember("godE") || !tech["godE"].isMember("qlE"))
		{
			tech["godE"]["qlE"] = Json::Value(Json::arrayValue);
		}
		tech["godE"]["qlE"][0u] = tech["godE"]["qlE"][0u].asUInt() + qihun;
		total_qihun = tech["godE"]["qlE"][0u].asUInt();

		dataUser.user_tech = writer.write(tech);
		result["qh"] = total_qihun;
	}

	ret = logicUser.SetUser(uid, dataUser);
	if(ret)
		return ret;

	if(prosper > 0 || longlin > 0 || rs1 > 0 || rs2 > 0 || rs3 > 0 || rs4 > 0 || qihun > 0 || tongqian > 0)
	{
		RESOURCE_LOG("[useGiftbag][uid=%u,chgprosper=%u,prosper=%u,chglonglin=%u,longlin=%u,chgqle=%u,qle=%u,chgr1=%u,r1=%u,chgr2=%u,r2=%u,chgr3=%u,r3=%u,chgr4=%u,r4=%u,chgtongqian=%u,tongqian=%u]"
				,uid,prosper,dataUser.prosper,longlin,total_longlin,qihun,total_qihun,rs1,dataUser.r1,rs2,dataUser.r2,rs3,dataUser.r3,rs4,dataUser.r4,tongqian,dataUser.type);
	}

	return R_SUCCESS;
}

int CLogicCMD::Payrank_activity(unsigned uid,unsigned lottery_number,unsigned point,Json::Value &result,unsigned lasttime,unsigned seqid)
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

	ret = checkLastSaveUID(dataUser);
	if(ret)
		return ret;

	ret = checkLastSaveTime(dataUser,lasttime,seqid);
	if(ret)
		return ret;
	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	CDataXML *pDataXML = CDataXML::GetCDataXML();
	if(!pDataXML)
	{
		error_log("GetInitXML fail");
		return R_ERR_DB;
	}


	vector<unsigned> id;
	vector<unsigned> count;
	vector<string> type;
	id.clear();
	count.clear();
	type.clear();

	Json::Value userGift;
	CDataUserData userData;
	string user_gift;
	ret = userData.GetGift(uid, user_gift);
	if(ret)
		return ret;
	Json::Reader reader;
	Json::FastWriter writer;
	reader.parse(user_gift, userGift);

	if(!userGift.isMember("pointreward"))
	{
		return R_ERR_NO_DATA;
	}

	unsigned lottery_point = lottery_number * point;
	int temp = userGift["pointreward"]["lp"].asInt() + lottery_number * point;

	userGift["pointreward"]["lp"] = temp;
	user_gift = writer.write(userGift);

	Json::Value user_Flag;
	reader.parse(dataUser.user_flag, user_Flag);
	int pointpay = 0;
	if(user_Flag.isMember("user_pay"))
	{
		unsigned size = user_Flag["user_pay"].size();
		for(int i = 0; i < size; ++i)
		{
			unsigned ts  = user_Flag["user_pay"][i][0u].asUInt();
			if(ts >= Config::GetIntValue(CONFIG_PAYRANK_BEGIN_TS)
			&& ts <= Config::GetIntValue(CONFIG_PAYRANK_END_TS))
			{
				unsigned temp = user_Flag["user_pay"][i][1u].asUInt() + user_Flag["user_pay"][i][2u].asUInt();
				pointpay += temp;
			}
		}
	}
	int all_pointpay = userGift["pointreward"]["tp"].asInt() + pointpay;
	if(all_pointpay < temp)
	{
		error_log("[Points_inadequate] [uid=%u]",uid);
		return R_ERR_DATA;
	}
	ret = pDataXML->GetPayrank(uid,lottery_number,point,id,count,type);
	if(ret)
		return ret;

	vector<ItemAdd> equip_items;
	vector<string> hero_id;
	vector<string> hero_code;
	equip_items.clear();
	hero_id.clear();
	hero_code.clear();

	for(int i=0; i< id.size(); ++i)
	{
		if(type[i] == "equip")
		{
			ItemAdd eqip;
			eqip.eqid = id[i];
			eqip.count = count[i];
			eqip.q = 0;
			eqip.ch = 0;
			string reason = "activity_new_payrank_";
			eqip.reason = reason.append(CTrans::UTOS(lottery_point));
			equip_items.push_back(eqip);

		}
		else if(type[i] == "hero")
		{
			string code = "activity_new_payrank_";
			hero_code.push_back(code.append(CTrans::UTOS(lottery_point)));
			hero_id.push_back(CDataXML::Hero2Str(id[i]));
		}
	}

	ret = userData.SetGift(uid,user_gift);
	if(ret)
		return ret;

	if(equip_items.size() > 0)
	{
		CLogicEquipment Equip;
		ret = Equip.AddItems(uid,equip_items,result["equip"], true);
		if(ret)
		{
			error_log("[activity_new_payrank_error] [uid=%u | lottery_point=%u]", uid , lottery_point);
			return R_ERR_DATA;
		}
	}

	if(hero_id.size() > 0)
	{
		CLogicHero Hero;
		ret = Hero.AddHeros(uid,hero_id,hero_code,result["hero"]);
		if(ret)
		{
			error_log("[activity_new_payrank_error] [uid=%u | lottery_point=%u]", uid , lottery_point);
			return R_ERR_DATA;
		}
	}

	ret = logicUser.SetUser(uid, dataUser);
	if(ret)
		return ret;

	return R_SUCCESS;
}

int CLogicCMD::BuyBet(unsigned uid,unsigned bet,Json::Value &result,unsigned lasttime,unsigned seqid)
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

	ret = checkLastSaveUID(dataUser);
	if(ret)
		return ret;

	ret = checkLastSaveTime(dataUser,lasttime,seqid);
	if(ret)
		return ret;
	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	CLogicPay logicPay;
	ret = logicPay.ChangePay(uid, 0, -bet, "buybet");
	if(ret)
		return ret;

	CLogicUser User;
	unsigned balance = 0;
	ret = User.ChangeBetForBack(uid, bet, dataUser.user_stat, balance);
	if(ret)
		return ret;

	result["bet"] = balance;
	ret = logicUser.SetUser(uid, dataUser);
	if(ret)
		return ret;

	return R_SUCCESS;
}

int CLogicCMD::Shop(unsigned uid, unsigned id, unsigned count, unsigned flag, unsigned type, unsigned vip, unsigned equd, Json::Value &result, unsigned &lasttime,unsigned &seqid)
{
	if(id == 0 || count == 0 || vip > SHOP_VIP_NUM)
		return R_ERR_PARAM;

	int ret = 0;
	XMLShop shop;
	CDataXML *dataXML = CDataXML::GetCDataXML();
	if(!dataXML)
	{
		error_log("GetInitXML fail");
		return R_ERR_DB;
	}
	ret = dataXML->GetShopItem(id,shop);
	if(ret || shop.id == 0 || vip ? shop.vip == 0 : shop.price == 0)
	{
		error_log("[GetShopItem_error][uid=%u&id=%u]", uid , id);
		return ret;
	}

	if(shop.type != 0 && shop.type != 2 && type == 0)
		return R_ERR_PARAM;
	int cost = (int)(vip?shop.vip:shop.price * count) * -1;
	/*
	if(flag)
		cost = (int)((float)cost * SHOP_FLAG);
	*/
	if(cost == 0)
		cost = -1;

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

	if(vip)
	{
		Json::Value newAct;
		CLogicSecinc logicSecinc;
		ret = logicSecinc.GetSecinc(uid, NAT_VIP_SHOP, newAct);

		if (ret == R_ERR_NO_DATA)
		{
			Json::Value array(Json::arrayValue);
			for(unsigned i = 0; i < SHOP_VIP_NUM; i++)
				array.append(0);
			newAct["id"] = NAT_VIP_SHOP;
			newAct["a"] = array;
			newAct["ts"] = Time::GetGlobalTime();
		}
		else if(ret)
			return ret;

		if(!Time::IsToday(newAct["ts"].asUInt()))
		{
			for(unsigned i = 0; i < SHOP_VIP_NUM; i++)
				newAct["a"][i] = 0;
			newAct["ts"] = Time::GetGlobalTime();
		}

		if(newAct["a"][vip - 1].asUInt() != 0)
		{
			LOGIC_ERROR_RETURN_MSG("vip_shop_limit");
		}

		newAct["a"][vip - 1] = 1;
		ret = logicSecinc.SetOneSecinc(uid, newAct);

		if(ret)
			return ret;

		result["newAct"] = newAct;
	}

	//钻石支付的情况下，如果前端代金券ud存在，则优先使用代金券
	if (type == 1 && equd > 0)
	{
		int costcount = -cost;

		//扣除代金券
		CLogicEquipment logicEquipment;
		Json::Value equipdata;

		logicEquipment.Get(uid, equd, equipdata);

		int realcount = min(equipdata["count"].asInt(), costcount);

		int ret = logicEquipment.UseEquipment(uid, SHOP_PAY_VOUCHER, equd, realcount, "shop_SHOP__"+ CTrans::UTOS(shop.id)+"_0:"+CTrans::UTOS(count));

		if (0 == ret)
		{
			result["djcount"] = realcount;
			cost += realcount;
		}
	}

	if (cost < 0)
	{
		CLogicPay logicPay;
		DataPay payData;
		ret = logicPay.ProcessOrderForBackend(uid, type?cost:0, type?0:cost, payData, "shop_SHOP__"+CTrans::UTOS(shop.id)+"_0:"+CTrans::UTOS(count),user_flag,bsave);

		if(ret)
			return ret;

		result["pointpay"].resize(0);

		result["coins"] = payData.coins;
		result["coins2"] = payData.cash;
	}

	if(bsave)
	{
		result["pointpay"] = user_flag["user_pay"];
		dataUser.user_flag = writer.write(user_flag);
	}

	if(shop.type == 2 || shop.type == 3)
		return _useGiftBag(dataUser, shop.id, count, result);

	CLogicEquipment logicEquipment;
	logicEquipment.AddOneItem(uid, shop.id, count, "backshp", result["equipment"], true, shop.ch);
	if(ret)
		return ret;

	if(bsave)
		ret = logicUser.SetUser(uid, dataUser);
	else
		ret = logicUser.SetUserLimit(uid, dataUser);
	if(ret)
		return ret;

	return R_SUCCESS;
}
int CLogicCMD::ProductShop(unsigned uid, unsigned type, unsigned costUd, unsigned id, Json::Value &result, unsigned &lasttime,unsigned &seqid)
{
	if(type < WorldBattleShop || type > HufuShop)
		return R_ERR_PARAM;

	int ret = 0;
	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	ret = logicUser.GetUserLimit(uid,dataUser);
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

	if (type == WorldBattleShop)
	{
		XMLWorldBattleShopItem shopItem;
		CDataXML *dataXML = CDataXML::GetCDataXML();
		if(!dataXML)
		{
			error_log("GetInitXML fail");
			return R_ERR_DB;
		}

		unsigned shopCount = 0;
		ret = dataXML->GetWorldBattleShopItem(id, shopItem, shopCount);
		if (ret)
		{
			error_log("[GetWorldBattleShopItem_error][uid=%u&id=%u]", uid , id);
			return ret;
		}
		unsigned costItem = shopItem.costItem;
		unsigned costCount = shopItem.costCount;
		unsigned getItem = shopItem.getItem;
		unsigned getCount = shopItem.getCount;
		unsigned limitTimes = shopItem.times;

		Json::Value newAct;
		CLogicSecinc logicSecinc;
		ret = logicSecinc.GetSecinc(uid, NAT_NEWWORLD_SOHP, newAct);
		if (ret == R_ERR_NO_DATA)
		{
			Json::Value array(Json::arrayValue);
			for (int i = 0; i < shopCount; i++)
				array.append(0);
			newAct["id"] = NAT_NEWWORLD_SOHP;
			newAct["b"] = array;
			newAct["a"] = Time::GetGlobalTime();
		}
		else if (ret != 0)
		{
			return ret;
		}

		if (CTime::GetDayInterval(newAct["a"].asUInt(), Time::GetGlobalTime()) != 0)
		{
			for(int i = 0; i < shopCount; i++)
				newAct["b"][i] = 0;
		}

		unsigned times = 0;
		if (newAct.isMember("b") && newAct["b"].isArray())
		{
			times = newAct["b"][id-1].asUInt();
		}
		else
		{
			Json::Value array(Json::arrayValue);
			for (int i = 0; i < shopCount; i++)
				array.append(0);
			newAct["b"] = array;
		}
		if (times >= limitTimes)
		{
			error_log("[Get too many times][uid=%u&type=%u&id=%u&times=%u&limitTimes=%u]", uid, type, id, times, limitTimes);
			LOGIC_ERROR_RETURN_MSG("Get too many times");
		}

		newAct["b"][id-1] = times + 1;
		newAct["a"] = Time::GetGlobalTime();
		ret = logicSecinc.SetOneSecinc(uid, newAct);
		if (ret)
			return ret;
		result["newAct"] = Json::Value(Json::arrayValue);
		result["newAct"].append(newAct);

		CLogicEquipment logicEquip;
		ret = logicEquip.UseEquipment(uid, costItem, costUd, costCount, "WorldBattleShop");
		if (ret)
			return ret;
		ret = logicEquip.AddOneItem(uid, getItem, getCount, "WorldBattleShop", result["equipment"], true);
		if (ret)
			return ret;
	}
	else if (type == RankBattleShop)
	{
		XMLRankBattleShopItem shopItem;
		CDataXML *dataXML = CDataXML::GetCDataXML();
		if(!dataXML)
		{
			error_log("GetInitXML fail");
			return R_ERR_DB;
		}

		unsigned shopCount = 0;
		ret = dataXML->GetRankBattleShopItem(id, shopItem, shopCount);
		if (ret)
		{
			error_log("[GetRankBattleShopItem_error][uid=%u&id=%u]", uid , id);
			return ret;
		}
		unsigned costItem = shopItem.costItem;
		unsigned costCount = shopItem.costCount;
		unsigned getItem = shopItem.getItem;
		unsigned getCount = shopItem.getCount;
		unsigned limitTimes = shopItem.times;

		Json::Value newAct;
		CLogicSecinc logicSecinc;
		ret = logicSecinc.GetSecinc(uid, NAT_RANK_BATTLE_2, newAct);
		if (ret == R_ERR_NO_DATA)
		{
			Json::Value array(Json::arrayValue);
			for (int i = 0; i < shopCount; i++)
				array.append(0);
			newAct["id"] = NAT_RANK_BATTLE_2;
			newAct["c"] = array;
			newAct["b"] = Time::GetGlobalTime();
		}
		else if (ret != 0)
		{
			return ret;
		}

		if (CTime::GetDayInterval(newAct["b"].asUInt(), Time::GetGlobalTime()) != 0)
		{
			for(int i = 0; i < shopCount; i++)
				newAct["c"][i] = 0;
		}

		unsigned times = 0;
		if (newAct.isMember("c") && newAct["c"].isArray())
		{
			times = newAct["c"][id-1].asUInt();
		}
		else
		{
			Json::Value array(Json::arrayValue);
			for (int i = 0; i < shopCount; i++)
				array.append(0);
			newAct["c"] = array;
		}
		if (times >= limitTimes)
		{
			error_log("[Get too many times][uid=%u&type=%u&id=%u&times=%u&limitTimes=%u]", uid, type, id, times, limitTimes);
			LOGIC_ERROR_RETURN_MSG("Get too many times");
		}

		newAct["c"][id-1] = times + 1;
		newAct["b"] = Time::GetGlobalTime();
		ret = logicSecinc.SetOneSecinc(uid, newAct);
		if (ret)
			return ret;
		result["newAct"] = Json::Value(Json::arrayValue);
		result["newAct"].append(newAct);

		CLogicEquipment logicEquip;
		ret = logicEquip.UseEquipment(uid, costItem, costUd, costCount, "RankBattleShop");
		if (ret)
			return ret;
		ret = logicEquip.AddOneItem(uid, getItem, getCount, "RankBattleShop", result["equipment"], true);
		if (ret)
			return ret;
	}
	else if (type == HufuShop)
	{
		XMLHufuShopItem shopItem;
		CDataXML *dataXML = CDataXML::GetCDataXML();
		if(!dataXML)
		{
			error_log("GetInitXML fail");
			return R_ERR_DB;
		}

		unsigned shopCount = 0;
		ret = dataXML->GetHufuShopItem(id, shopItem, shopCount);
		if (ret)
		{
			error_log("[GetWorldBattleShopItem_error][uid=%u&id=%u]", uid , id);
			return ret;
		}
		unsigned costItem = HUFU_ID;
		unsigned tab = shopItem.tab;
		unsigned costCount = shopItem.costCount;
		unsigned getItem = shopItem.getItem;
		unsigned getCount = shopItem.getCount;
		unsigned limitTimes = shopItem.times;

		Json::Value newAct;
		CLogicSecinc logicSecinc;
		ret = logicSecinc.GetSecinc(uid, NAT_HUFU, newAct);
		if (ret == R_ERR_NO_DATA)
		{
			Json::Value array(Json::arrayValue);
			for (int i = 0; i < 3 ; i++)
			{
				Json::Value subArray(Json::arrayValue);
				for (int j = 0; j < 15; j++)
					subArray.append(0);
				array.append(subArray);
			}
			newAct["id"] = NAT_HUFU;
			newAct["a"] = array;
		}
		else if (ret != 0)
		{
			return ret;
		}

		unsigned times = 0;
		unsigned idIndex = 0;
		if (tab == 1)
			idIndex = id;
		else if (tab == 2)
			idIndex = id - 20;
		else if (tab == 3)
			idIndex = id - 30;

		if (newAct.isMember("a") && newAct["a"].isArray())
		{
			times = newAct["a"][tab-1][idIndex-1].asUInt();
		}
		else
		{
			Json::Value array(Json::arrayValue);
			for (int i = 0; i < 3 ; i++)
			{
				Json::Value subArray(Json::arrayValue);
				for (int j = 0; j < 15; j++)
					subArray.append(0);
				array.append(subArray);
			}
			newAct["a"] = array;
		}

		if (times >= limitTimes)
		{
			error_log("[Get too many times][uid=%u&type=%u&id=%u&times=%u&limitTimes=%u]", uid, type, id, times, limitTimes);
			LOGIC_ERROR_RETURN_MSG("Get too many times");
		}

		newAct["a"][tab-1][idIndex-1] = times + 1;
		ret = logicSecinc.SetOneSecinc(uid, newAct);
		if (ret)
			return ret;
		result["newAct"] = Json::Value(Json::arrayValue);
		result["newAct"].append(newAct);

		CLogicEquipment logicEquip;
		ret = logicEquip.UseEquipment(uid, costItem, costUd, costCount, "HufuShop");
		if (ret)
			return ret;

		if (getItem == 0)
		{
			// gold
			CLogicPay logicPay;
			DataPay payData;
			ret = logicPay.ChangePay(uid, 0, getCount, "HufuShop", payData);
			if(ret)
				return ret;
			result["coins"] = payData.coins;
			result["coins2"] = payData.cash;
		}
		else
		{
			ret = logicEquip.AddOneItem(uid, getItem, getCount, "HufuShop", result["equipment"], true);
		}
		if (ret)
			return ret;
	}
	else
	{
		return R_ERR_PARAM;
	}

	ret = logicUser.SetUserLimit(uid, dataUser);
	if (ret)
		return ret;
	return R_SUCCESS;
}


int CLogicCMD::FashionShop(unsigned uid, unsigned id, unsigned count, bool is_cash, Json::Value &result, unsigned &lasttime,unsigned &seqid)
{
	//参数校验
	if(uid == 0 || id == 0 || count == 0)
	{
		error_log("param value wrong");
		return R_ERR_PARAM;
	}

	//配置校验
	CDataXML *dataXML = CDataXML::GetCDataXML();
	if(!dataXML)
	{
		error_log("GetInitXML fail");
		return R_ERR_DB;
	}
	XMLFashionShopItem shop;
	int ret = 0;
	ret = dataXML->GetFashionShopItem(id, shop);
	if (ret || (shop.id_ == 0))
	{
		error_log("[GetFashionShopItem_error][uid=%u&id=%u]", uid, id);
		return ret;
	}
	if (shop.is_cash_ && !is_cash)
	{
		PARAM_ERROR_RETURN_MSG("must be cash");
	}

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

	//vip level check
	if (dataUser.viplevel < shop.vip_)
	{
		error_log("[vip is not match][uid=%u&id=%u]", uid, shop.id_);
		return ret;
	}

	//扣钱
	Json::Reader reader;
	Json::FastWriter writer;
	Json::Value user_flag;
	reader.parse(dataUser.user_flag, user_flag);
	bool bsave = false;
	unsigned need_cash = count * (is_cash ? shop.cost_ : 0);
	unsigned need_coins = count * (is_cash ? 0 : shop.cost_);

	CLogicPay logicPay;
	DataPay payData;
	ret = logicPay.ProcessOrderForBackend(uid, -need_cash, -need_coins, payData, "fashion_Shop__"+CTrans::UTOS(shop.id_)+"_0:"+CTrans::UTOS(count), user_flag, bsave);
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

	//发时装
	string item_reason = "FashionShop";
	ItemAdd item(shop.id_, count, item_reason);
	unsigned ts_dead = 0;
	if (shop.die_)
	{
		ts_dead = Time::GetGlobalTime() + shop.days_*86400;
	}
	Json::Value newEqDatas = Json::Value(Json::arrayValue);
	CLogicEquipment logicEquip;
	ret = logicEquip.genFashion(item, shop.die_, ts_dead, newEqDatas);
	if (ret)
	{
		error_log("gen_fashion_error uid=%u | equip_id=%u", uid, shop.id_);
		return R_ERR_DATA;
	}
	ret = logicEquip.UpdateEquipment(uid, 0, newEqDatas, result["add_equip"]);
	if(ret)
	{
		error_log("upgrade_fashion_error uid=%u | equip_id=%u", uid, shop.id_);
		return R_ERR_DATA;
	}

	if(bsave)
		ret = logicUser.SetUser(uid, dataUser);
	else
		ret = logicUser.SetUserLimit(uid, dataUser);
	if(ret)
		return ret;

	return R_SUCCESS;
}


int CLogicCMD::GetEquipIntensifys(unsigned uid, const Json::Value data, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	int ret = 0;
	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	ret = logicUser.GetUserLimit(uid,dataUser);
	if(ret)
	{
		error_log("[get_user_info_failed] [uid=%u]",uid);
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

	unsigned equip_level = 0, equip_ud = 0;
	unsigned xingyunshi_num = 0, xingyunshi_ud = 0;
	unsigned q_ud = 0, q_level = 0, q_id = 0;
	unsigned costBs = 0;

	if(!Json::GetUInt(data, "equip_level", equip_level) || !Json::GetUInt(data, "equip_ud", equip_ud)
	|| !Json::GetUInt(data, "xingyunshi_num", xingyunshi_num) || !Json::GetUInt(data, "costBs", costBs)
	|| !Json::GetUInt(data, "q_ud", q_ud) || !Json::GetUInt(data, "q_level", q_level)
	|| !Json::GetUInt(data, "q_id", q_id)
	)
	{
		error_log("para_error");
		return R_ERR_PARAM;
	}

	unsigned snap_xingyunshi_n = 0, snap_xingyunshi_ud = 0, snap_xingyunshi_type = 0;

	if(data.isMember("snap_xingyunshi_n"))
	{
		Json::GetUInt(data, "snap_xingyunshi_n", snap_xingyunshi_n);
		Json::GetUInt(data, "snap_xingyunshi_ud", snap_xingyunshi_ud);
		Json::GetUInt(data, "snap_xingyunshi_type", snap_xingyunshi_type);
	}

	//增加限级强化幸运石
	unsigned qlimit_xingyunshi_n = 0, qlimit_xingyunshi_ud = 0;

	//仅针对100级以上的装备
	if(equip_level >= 100 && data.isMember("qlimit_xingyunshi_n"))
	{
		Json::GetUInt(data, "qlimit_xingyunshi_n", qlimit_xingyunshi_n);
		Json::GetUInt(data, "qlimit_xingyunshi_ud", qlimit_xingyunshi_ud);
	}

	unsigned x_all_num = qlimit_xingyunshi_n + snap_xingyunshi_n + xingyunshi_num;
	unsigned id = 11;
	if(equip_level > 51)
	{
		id = ceil(float(equip_level) / 10) - 1;
	}
	else if(equip_level > 36 && equip_level < 46)
	{
		id = 4;
	}
	else if(equip_level > 21 && equip_level < 31)
	{
		id = 3;
	}
	else if(equip_level > 6 && equip_level < 16)
	{
		id = 2;
	}
	else if(1 == equip_level)
	{
		id = 1;
	}

	CDataXML *pDataXML = CDataXML::GetCDataXML();
	if(!pDataXML)
	{
		error_log("GetInitXML fail");
		return R_ERR_DB;
	}

	if(snap_xingyunshi_n > 0)
	{
		unsigned sx_result = 0;
		ret = pDataXML->GetEquipIntensifysRate(id, q_level, xingyunshi_num, sx_result);
		if(ret)
		{
			error_log("[get_equipintensifysdatarate_error] [uid=%u|e_id=%u|q_level=%u]", uid, equip_ud, q_level);
			return ret;
		}

		if(0 == sx_result)
		{
			error_log("xinyunshi_para_error");
			return R_ERR_LOGIC;
		}
	}

	int temp = dataUser.battle_spirits - costBs;
	if (temp < 0)
	{
		LOGIC_ERROR_RETURN_MSG("battle_spirits less than zero");
	}
	dataUser.battle_spirits = temp;

	unsigned costIron = pow((equip_level + q_level), 2) * q_level + 100;
	temp = dataUser.r4 - costIron;
	if (temp < 0)
	{
		LOGIC_ERROR_RETURN_MSG("r4 less than zero");
	}
	dataUser.r4 = temp;

	CLogicEquipment Equip;

	//先扣除限级强化幸运石
	if (qlimit_xingyunshi_n > 0)
	{
		int qlimit_xingyunshi_id = 0;

		switch(q_level)
		{
			case 6: qlimit_xingyunshi_id = QLIMIT_LUCK_STONE_6_ID; break;
			case 7: qlimit_xingyunshi_id = QLIMIT_LUCK_STONE_7_ID; break;
			case 8: qlimit_xingyunshi_id = QLIMIT_LUCK_STONE_8_ID; break;
			case 9: qlimit_xingyunshi_id = QLIMIT_LUCK_STONE_9_ID; break;
			default: break;
		}

		ret = Equip.UseEquipment(uid, qlimit_xingyunshi_id, qlimit_xingyunshi_ud, qlimit_xingyunshi_n, "equip_intensifys_back");
		if(ret)
		{
			error_log("[equipintensifys_deduct_qlimit_xingyunshi_fail] [uid=%u|e_id=%u|count=%u]", uid, qlimit_xingyunshi_id, qlimit_xingyunshi_n);
			return ret;
		}
	}

	if(xingyunshi_num > 0)	//扣除强化所需幸运石
	{
		if(!Json::GetUInt(data, "xingyunshi_ud", xingyunshi_ud))
		{
			error_log("para_error");
			return R_ERR_PARAM;
		}
		ret = Equip.UseEquipment(uid, LUCKY_STONE_ID, xingyunshi_ud, xingyunshi_num, "equip_intensifys_back");
		if(ret)
		{
			error_log("[equipintensifys_deduct_xingyunshi_fail] [uid=%u|e_id=%u|count=%u]", uid, LUCKY_STONE_ID, xingyunshi_num);
			return ret;
		}
	}

	if(snap_xingyunshi_n > 0)	//扣除强化所需临时幸运石
	{
		int snap_xingyunshi_id = 0;
		if(1 == snap_xingyunshi_type)				//限制强化等级的临时幸运石
		{
			if(8 == q_level)
				snap_xingyunshi_id = LUCKY_STONE_8_ID;
			else if(9 == q_level)
				snap_xingyunshi_id = LUCKY_STONE_9_ID;
			else if(10 == q_level)
				snap_xingyunshi_id = LUCKY_STONE_10_ID;
		}
		else if(0 == snap_xingyunshi_type)			//可强化所有等级的临时幸运石
		{
			snap_xingyunshi_id = LUCKY_STONE_ALL_LEVEL_ID;
		}

		ret = Equip.UseEquipment(uid, snap_xingyunshi_id, snap_xingyunshi_ud, snap_xingyunshi_n, "equip_intensifys_back");
		if(ret)
		{
			error_log("[equipintensifys_deduct_snap_xingyunshi_fail] [uid=%u|e_id=%u|count=%u]", uid, snap_xingyunshi_id, snap_xingyunshi_n);
			return ret;
		}
	}

	//扣除强化石
	int qianghuashi_id = GET_EN_STONE_ID(q_level);
	if((q_id == EN_STONE_ID_5_T && 5 == q_level ) || (q_id == EN_STONE_ID_9_T && 9 == q_level)
	|| (q_id == EN_STONE_ID_3_T && 3 == q_level) || (q_id == EN_STONE_ID_6_T && 6 == q_level)
	|| (q_id == EN_STONE_ID_7_T && 7 == q_level) || (q_id == EN_STONE_ID_8_T && 8 == q_level)
	|| (q_id == EN_STONE_ID_1_T && 1 == q_level) || (q_id == EN_STONE_ID_10_T && 10 == q_level)
	)
	{
		qianghuashi_id = q_id;
	}

	ret = Equip.UseEquipment(uid, qianghuashi_id, q_ud, 1, "equip_intensifys_back");
	if(ret)
	{
		error_log("[equipintensifys_deduct_qianghuashi_fail] [uid=%u|e_id=%u|count=%u]", uid, qianghuashi_id, 1);
		return ret;
	}

	ret = pDataXML->GetEquipIntensifys(id, q_level, x_all_num, result["intensifys"]);
	if(ret)
	{
		error_log("[get_equipintensifysdata_error] [uid=%u|e_id=%u|q_level=%u]", uid, equip_ud, q_level);
		return ret;
	}


	if(result["intensifys"].asString() == "success")
	{
		Json::Value Equip_data;

		ret = Equip.Get(uid, equip_ud, Equip_data);
		if(ret)
		{
			error_log("[intensifys_ud_error][uid=%u,ud=%u]",uid,equip_ud);
			return ret;
		}

		Equip_data["q"] = Equip_data["q"].asInt() + 1;
		if(Equip_data["q"].asInt() > 10)  //强化等级最高为10级
		{
			Equip_data["q"] = 10;
		}
		ret = Equip.Chg(uid, equip_ud, Equip_data);
		result["equip"] = Equip_data;

		Json::FastWriter writer;
		string e_data = writer.write(Equip_data);
		EQUIPMENT_LOG("uid=%u,id=%u,eqid=%d,act=%s,chg=%d,count=%d,code=%s,data=%s",uid,equip_ud,Equip_data["id"].asInt(),
					"qup",0,0,"equip_intensifys_back",e_data.c_str());
	}

	ret = logicUser.SetUserLimit(uid, dataUser);
	if(ret)
		return ret;
	result["chgbs"] = costBs;
	result["bs"] = dataUser.battle_spirits;
	result["chgr4"] = costIron;
	result["r4"] = dataUser.r4;
	RESOURCE_LOG("[eqipintensifys][uid=%u,id=%d,q_level=%d,chgbs=%u,bs=%u,chgr4=%u,r4=%u]"
					,uid, id, q_level, costBs, dataUser.battle_spirits, costIron, dataUser.r4);

	return R_SUCCESS;
}

int CLogicCMD::QianghuaDismantlingEquip(unsigned uid, unsigned equip_level, unsigned equip_ud, unsigned q_level, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	int ret = 0;
	Json::FastWriter writer;
	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	ret = logicUser.GetUserLimit(uid,dataUser);
	if(ret)
	{
		error_log("[get_user_info_failed] [uid=%u]",uid);
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

	unsigned id = 1;
	if(equip_level > 51)
	{
		id = ceil(float(equip_level) / 10) - 1;
	}
	else if(equip_level > 36 && equip_level < 46)
	{
		id = 4;
	}
	else if(equip_level > 21 && equip_level < 31)
	{
		id = 3;
	}
	else if(equip_level > 6 && equip_level < 16)
	{
		id = 2;
	}
	else if(1 == equip_level)
	{
		id = 1;
	}

	CDataXML *pDataXML = CDataXML::GetCDataXML();
	if(!pDataXML)
	{
		error_log("GetInitXML fail");
		return R_ERROR;
	}

	Json::Value Equip_data;
	CLogicEquipment LogicEquip;
	ret = LogicEquip.Get(uid, equip_ud, Equip_data);
	if(ret)
		return ret;

	if(Equip_data["q"].asUInt() != q_level)
	{
		error_log("[QianghuaDismantlingEquip_para_error][uid=%u,q_level=%u,real_q_level=%u]",uid, q_level, Equip_data["q"].asUInt());
		return R_ERR_PARAM;
	}

	unsigned xingyunshi_count = 0;
	ret = pDataXML->GetEquipDismantling_xingyunshi(id, q_level, xingyunshi_count);
	if(ret)
	{
		error_log("[get_equipdismantling_xingyunshi_error] [uid=%u|e_id=%u|q_level=%u]", uid, equip_ud, q_level);
		return R_ERR_DATA;
	}

	unsigned q_id = 0;
	unsigned q_number = 0;
	ret = pDataXML->GetEquipDismantling_qianghuashi(q_level, q_id,  q_number);
	if(ret || q_id == 0 || q_number == 0)
	{
		error_log("[get_DataXMLolequipset_Dismantling_error] [uid=%u|e_id=%u|q_level=%u]", uid, equip_ud, q_level);
		return R_ERR_DATA;
	}

	Equip_data["q"] = 0;
	ret = LogicEquip.Chg(uid, equip_ud, Equip_data);
	if(ret)
		return ret;

	result["equipdismantling"] = Equip_data;
	EQUIPMENT_LOG("uid=%u,id=%u,eqid=%d,act=oth,chg=0,count=0,code=back_equipdismantling_chg,data=%s",uid, equip_ud, Equip_data["id"].asUInt(),writer.write(Equip_data).c_str());

	if(xingyunshi_count > 0)
	{
		ret = LogicEquip.AddOneItem(uid, LUCKY_STONE_ID, xingyunshi_count,"back_equipdismantling_add",result["add_xingyunshi"], true);
		if(ret)
			return ret;
	}

	ret = LogicEquip.AddOneItem(uid, q_id, q_number,"back_equipdismantling_add",result["add_qianghuashi"], true);
	if(ret)
		return ret;

	ret = logicUser.SetUserLimit(uid, dataUser);
	if(ret)
		return ret;
	return R_SUCCESS;
}

int CLogicCMD::TaozhuangDismantlingEquip(unsigned uid, unsigned equip_id, unsigned ud, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	int ret = 0;
	Json::FastWriter writer;
	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	ret = logicUser.GetUserLimit(uid,dataUser);
	if(ret)
	{
		error_log("[get_user_info_failed] [uid=%u]",uid);
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

	CDataXML *pDataXML = CDataXML::GetCDataXML();
	if(!pDataXML)
	{
		error_log("GetInitXML fail");
		return R_ERROR;
	}

	unsigned level = unsigned((equip_id - 150000) / 1000) * 10 + 50;
	unsigned part = equip_id % 10;
	unsigned cailiao_id = Math::GetRandomInt(4) + 51001;

	CLogicEquipment LogicEquip;
	Json::Value set_data;
	LogicEquip.Get(uid, ud, set_data);
	if(equip_id != set_data["id"].asUInt())
	{
		error_log("[taozhuang_chaijie_equpid_or_ud_error][uid=%u,equip_id=%u,ud=%u,ud_equipid=%u]", uid, equip_id, ud, set_data["id"].asUInt());
		return R_ERR_PARAM;
	}

	unsigned cailiao_num = 0;
	ret = pDataXML->GetEquipDismantling_taozhuang(level, part, cailiao_num);
	if(ret)
	{
		error_log("[get_DataXMLolequipset_error][uid=%u|ud=%u|equip_id=%u]", uid, ud, equip_id);
		return R_ERR_DATA;
	}

	if(set_data.isMember("gems"))
	{
		if(set_data["gems"].isMember("1"))
		{
			Json::Value gem_data;
			LogicEquip.Get(uid, set_data["gems"]["1"].asUInt(), gem_data);
			gem_data["status"] = 0;
			LogicEquip.Chg(uid, set_data["gems"]["1"].asUInt(), gem_data);
		}
		if(set_data["gems"].isMember("2"))
		{
			Json::Value gem_data;
			LogicEquip.Get(uid, set_data["gems"]["2"].asUInt(), gem_data);
			gem_data["status"] = 0;
			LogicEquip.Chg(uid, set_data["gems"]["2"].asUInt(), gem_data);
		}
		if(set_data["gems"].isMember("3"))
		{
			Json::Value gem_data;
			LogicEquip.Get(uid, set_data["gems"]["3"].asUInt(), gem_data);
			gem_data["status"] = 0;
			LogicEquip.Chg(uid, set_data["gems"]["3"].asUInt(), gem_data);
		}
		if(set_data["gems"].isMember("4"))
		{
			Json::Value gem_data;
			LogicEquip.Get(uid, set_data["gems"]["4"].asUInt(), gem_data);
			gem_data["status"] = 0;
			LogicEquip.Chg(uid, set_data ["gems"]["4"].asUInt(), gem_data);
		}
	}
	ret = LogicEquip.Del(uid, ud);
	if(ret == 0)
	{
		EQUIPMENT_LOG("uid=%u,id=%u,eqid=%d,act=del,chg=1,count=0,code=EquipSet_chaijie,data=%s",uid,ud,equip_id,writer.write(set_data).c_str());
	}

	ret = LogicEquip.AddOneItem(uid, cailiao_id, cailiao_num,"back_equipdismantling_add",result["add_cailiao"], true);
	if(ret)
		return ret;

	ret = logicUser.SetUserLimit(uid, dataUser);
	if(ret)
		return ret;
	return R_SUCCESS;
}

//天降神力
int CLogicCMD::DivinePower(unsigned uid, Json::Value &data, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	unsigned  gem_id = 0;
	if(!data.isMember("ud") || !data["ud"].isArray() || !Json::GetUInt(data, "gem_id", gem_id))
	{
		error_log("para_error");
		return R_ERR_PARAM;
	}
	Json::Value& ud_array = data["ud"];
	if(ud_array.size() % 4 != 0)
	{
		return R_ERR_PARAM;
	}
	if(!IS_TECH_GEM_EQID(gem_id) || gem_id == 6610)
	{
		return R_ERR_PARAM;
	}

	int ret = 0;
	Json::FastWriter writer;
	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	ret = logicUser.GetUserLimit(uid,dataUser);
	if(ret)
	{
		error_log("[get_user_info_failed] [uid=%u]",uid);
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

	CLogicEquipment logicEquip;
	for(unsigned i = 0; i < ud_array.size(); ++i)
	{
		ret = logicEquip.UseEquipment(uid, gem_id, ud_array[i].asUInt(), 1, "DivinePower");
		if(ret)
		{
			LOGIC_ERROR_RETURN_MSG("DivinePower_FourLowLevel_To_OneHighLevel_ud");
		}
	}
	ret = logicEquip.AddOneItem(uid, gem_id+1, ud_array.size()/4, "DivinePower",result["add_equip"], true);
	if(ret)
		return ret;

	ret = logicUser.SetUserLimit(uid, dataUser);
	if(ret)
		return ret;
	return R_SUCCESS;
}

int CLogicCMD::StarStone(unsigned uid,  Json::Value &data, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	const unsigned sexp[3] = {60, 240, 480};

	unsigned ud = 0;
	if(!data.isMember("uds") || !data["uds"].isArray() || !Json::GetUInt(data, "ud", ud))
	{
		error_log("para_error");
		return R_ERR_PARAM;
	}
	Json::Value& uds = data["uds"];

	int ret = 0;
	Json::FastWriter writer;
	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	ret = logicUser.GetUserLimit(uid,dataUser);
	if(ret)
	{
		error_log("[get_user_info_failed] [uid=%u]",uid);
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

	CLogicEquipment logicEquip;
	Json::Value o;
	ret = logicEquip.Get(uid, ud, o);
	if(ret)
		return ret;
	unsigned so = 0, eqid = 0;
	Json::GetUInt(o, "sexp", so);
	Json::GetUInt(o, "id", eqid);
	if(!IS_STAR_STONE_EQID(eqid))
		return R_ERR_PARAM;
	for(unsigned i = 0; i < uds.size(); ++i)
	{
		unsigned u = uds[i].asUInt();
		Json::Value t;
		ret = logicEquip.Get(uid, u, t);
		if(ret)
			continue;
		unsigned ch = 0, s = 0, id = 0;
		Json::GetUInt(t, "ch", ch);
		Json::GetUInt(t, "sexp", s);
		Json::GetUInt(t, "id", id);
		if(!IS_STAR_STONE_EQID(id))
			continue;
		if(ch > 3 || ch < 1)
			continue;
		so += s + sexp[ch-1];
		logicEquip.Del(uid, u);
		EQUIPMENT_LOG("uid=%u,id=%u,eqid=%d,act=del,chg=-1,count=0,code=StarStone,sexp=%u",uid,u,id,s);
	}
	o["sexp"] = so;
	ret = logicEquip.Chg(uid, ud, o);
	if(ret)
		return ret;
	EQUIPMENT_LOG("uid=%u,id=%u,eqid=%d,act=oth,chg=0,count=1,code=StarStone,sexp=%u",uid,ud,eqid,so);

	result["equip"] = o;

	ret = logicUser.SetUserLimit(uid, dataUser);
	if(ret)
		return ret;
	return R_SUCCESS;
}

//每日累充
int CLogicCMD::EveryDayRecharge(unsigned uid, Json::Value &data, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	//判断是否在活动开启时间之内
	unsigned now = Time::GetGlobalTime();
	ActInfoConfig actCfg = ActInfoConfig(CONFIG_TWOHOLIDAY_ENJOY);
	if(!actCfg.IsActive())
	{
		return R_ERR_LOGIC;
	}

	int ret = 0;
	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	ret = logicUser.GetUser(uid,dataUser);
	if(ret)
	{
		error_log("[get_user_info_failed] [uid=%u]",uid);
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

	unsigned index;  //识别是哪个操作 1:每日领取 2:七日领取 3:12日领取
	if(!Json::GetUInt(data, "index", index))
	{
		error_log("para_error");
		return R_ERR_PARAM;
	}

	if(index < 1 || index > 3)
	{
		return R_ERR_PARAM;
	}

	Json::Reader reader;
	Json::Value user_flag;
	reader.parse(dataUser.user_flag, user_flag);
	if (!user_flag.isMember("chgs") || !user_flag["chgs"].isArray())
	{
		error_log("chgs error");
		DATA_ERROR_RETURN_MSG("chgs error");
	}

	Json::Value newAct; //newAct初始化
	CLogicSecinc logicSecinc;
	ret = logicSecinc.GetSecinc(uid, NAT_EVERYDAYRECHARGE, newAct);
	if (ret == R_ERR_NO_DATA)
	{
		newAct["id"] = NAT_EVERYDAYRECHARGE;
		newAct["s1"] = 0;  //每日奖励领取状态（0：没领；1：领过）
		newAct["s7"]  = 0;  //七次奖励领取状态（0：没领；1：领过）
		newAct["s12"]  = 0; //十二次奖励领取状态（0：没领；1：领过）
		newAct["v"] = actCfg.Version();
	}
	else if(ret)
		return ret;

	if(!newAct.isMember("id"))
	{
		newAct["id"] = NAT_EVERYDAYRECHARGE;
	}

	if(actCfg.Version() != newAct["v"].asInt())
	{
		newAct["v"] = actCfg.Version();
		newAct["s7"]  = 0;
		newAct["s12"]  = 0;
		newAct["s1"] = 0;
	}

	if(!newAct.isMember("ts") || !Time::IsToday(newAct["ts"].asUInt()) || !newAct.isMember("s1"))
	{
		newAct["s1"]  = 0; //在线时长达标奖励领取状态（0：没领；1：领过）
	}

	unsigned size = user_flag["chgs"].size();
	unsigned day_count = 0;   //充值次数
	unsigned charge_limit = ConfigManager::Instance()->m_twoholidaycfg.m_config.everyday_recharge().charge();
	for (unsigned i = 0; i < size; ++i)
	{
		unsigned ts  = user_flag["chgs"][i][0u].asUInt();
		if(ts >= actCfg.StartTS() && ts <= actCfg.EndTS())
		{
			if(user_flag["chgs"][i][1u].asUInt() >= charge_limit)
			{
				day_count += 1;
			}

			if(index == 1 && !CTime::IsDiffDay(ts, now))
			{
				//如果今天充值够了并且没领过
				if(user_flag["chgs"][i][1u].asUInt() >= charge_limit && newAct["s1"].asUInt() == 0)
				{
					//发奖励
					unsigned reward_num = ConfigManager::Instance()->m_twoholidaycfg.m_config.everyday_recharge().reward_one_size();
					vector<ItemAdd> equip_items;
					equip_items.clear();

					for(unsigned j = 0; j < reward_num; ++j)
					{
						unsigned eqid = ConfigManager::Instance()->m_twoholidaycfg.m_config.everyday_recharge().reward_one(j).equips(0).eqid();
						unsigned count = ConfigManager::Instance()->m_twoholidaycfg.m_config.everyday_recharge().reward_one(j).equips(0).c();
						ItemAdd eqip;
						eqip.eqid = eqid;
						eqip.count = count;
						string reason = "everydayrecharge_one_1_";
						eqip.reason = reason.append(CTrans::UTOS(j));
						equip_items.push_back(eqip);
					}

					if(equip_items.size() > 0)
					{
						CLogicEquipment logicEquip;
						ret = logicEquip.AddItems(uid,equip_items,result["equipments"], true);
						if(ret)
						{
							error_log("Add_Equip_error_1 uid=%u ", uid);
							return R_ERR_DATA;
						}
					}
					newAct["s1"] = 1;
				}
				else
				{
					PARAM_ERROR_RETURN_MSG("have recv or not enough recharge");
				}
			}
		}
	}
	//7日奖励发放
	if(index == 2)
	{
		if(day_count >= 7 && newAct["s7"].asUInt() == 0)
		{
			//发奖励
			unsigned reward_num = ConfigManager::Instance()->m_twoholidaycfg.m_config.everyday_recharge().reward_seven_size();
			vector<ItemAdd> equip_items;
			equip_items.clear();
			CLogicEquipment logicEquip;
			for(unsigned j = 0; j < reward_num; ++j)
			{
				unsigned eqid = ConfigManager::Instance()->m_twoholidaycfg.m_config.everyday_recharge().reward_seven(j).equips(0).eqid();
				unsigned count = ConfigManager::Instance()->m_twoholidaycfg.m_config.everyday_recharge().reward_seven(j).equips(0).c();

				ItemAdd eqip;
				eqip.eqid = eqid;
				eqip.count = count;
				string reason = "everydayrecharge_one_7_";
				eqip.reason = reason.append(CTrans::UTOS(j));
				equip_items.push_back(eqip);
			}
			if(equip_items.size() > 0)
			{
				CLogicEquipment logicEquip;
				ret = logicEquip.AddItems(uid,equip_items,result["equipments"], true);
				if(ret)
				{
					error_log("Add_Equip_error_7 uid=%u ", uid);
					return R_ERR_DATA;
				}
			}
			newAct["s7"] = 1;
		}
		else
		{
			PARAM_ERROR_RETURN_MSG("have recv or not enough count");
		}
	}

	//领取了12次奖励
	if(index == 3)
	{
		if(day_count == 12 && newAct["s12"].asUInt() == 0)
		{
			//发奖励
			unsigned reward_num = ConfigManager::Instance()->m_twoholidaycfg.m_config.everyday_recharge().reward_twelve_size();
			vector<ItemAdd> equip_items;
			equip_items.clear();
			CLogicEquipment logicEquip;
			for(unsigned j = 0; j < reward_num; ++j)
			{
				unsigned eqid = ConfigManager::Instance()->m_twoholidaycfg.m_config.everyday_recharge().reward_twelve(j).equips(0).eqid();
				unsigned count = ConfigManager::Instance()->m_twoholidaycfg.m_config.everyday_recharge().reward_twelve(j).equips(0).c();
				ItemAdd eqip;
				eqip.eqid = eqid;
				eqip.count = count;
				string reason = "everydayrecharge_one_12_";
				eqip.reason = reason.append(CTrans::UTOS(j));
				equip_items.push_back(eqip);
			}
			if(equip_items.size() > 0)
			{
				CLogicEquipment logicEquip;
				ret = logicEquip.AddItems(uid,equip_items,result["equipments"], true);
				if(ret)
				{
					error_log("Add_Equip_error_12 uid=%u ", uid);
					return R_ERR_DATA;
				}
			}
			newAct["s12"] = 1;
		}
		else
		{
			PARAM_ERROR_RETURN_MSG("have recv or not enough count");
		}
	}

	newAct["ts"] = now;
	result["newAct"] = newAct;
	ret = logicSecinc.SetOneSecinc(uid, newAct);
	if(ret)
		return ret;

	ret = logicUser.SetUser(uid, dataUser);
	if(ret)
		return ret;
	return R_SUCCESS;
}

//每日在线
int CLogicCMD::EveryDayOnline(unsigned uid, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	//判断是否在活动开启时间之内
	unsigned now = Time::GetGlobalTime();
	ActInfoConfig actCfg = ActInfoConfig(CONFIG_TWOHOLIDAY_ENJOY);
	if(!actCfg.IsActive())
		return R_ERR_LOGIC;

	int ret = 0;
	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	ret = logicUser.GetUserLimit(uid,dataUser);
	if(ret)
	{
		error_log("[get_user_info_failed] [uid=%u]",uid);
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

	Json::Value newAct; //newAct初始化
	CLogicSecinc logicSecinc;
	ret = logicSecinc.GetSecinc(uid, NAT_EVERYDAYONLINE, newAct);
	if (ret == R_ERR_NO_DATA)
	{
		newAct["id"] = NAT_EVERYDAYONLINE;
		newAct["v"] = actCfg.Version();
	}
	else if(ret)
		return ret;
	if(!newAct.isMember("id"))
	{
		newAct["id"] = NAT_EVERYDAYONLINE;
	}

	if(actCfg.Version() != newAct["v"].asInt())
	{
		newAct["v"] = actCfg.Version();
		newAct["s"]  = 0; //在线时长达标奖励领取状态（0：没领；1：领过）
	}

	if(!newAct.isMember("ts") || !Time::IsToday(newAct["ts"].asUInt()) || !newAct.isMember("s"))
	{
		newAct["s"]  = 0; //在线时长达标奖励领取状态（0：没领；1：领过）
	}

	if (CTime::GetDayInterval(dataUser.last_active_time, Time::GetGlobalTime()) == 0)
	{
		result["onlinets"] = dataUser.ext;
		//如果在线时长达标并且未领取
		if(dataUser.ext >= ConfigManager::Instance()->m_twoholidaycfg.m_config.eveyday_online().ts_limit() && newAct["s"].asUInt() == 0)
		{
			//发奖励
			unsigned reward_num = ConfigManager::Instance()->m_twoholidaycfg.m_config.eveyday_online().reward_size();
			vector<ItemAdd> equip_items;
			equip_items.clear();
			CLogicEquipment logicEquip;
			for(unsigned j = 0; j < reward_num; ++j)
			{
				unsigned eqid = ConfigManager::Instance()->m_twoholidaycfg.m_config.eveyday_online().reward(j).equips(0).eqid();
				unsigned count = ConfigManager::Instance()->m_twoholidaycfg.m_config.eveyday_online().reward(j).equips(0).c();
				ItemAdd eqip;
				eqip.eqid = eqid;
				eqip.count = count;
				string reason = "everydayonline_";
				eqip.reason = reason.append(CTrans::UTOS(j));
				equip_items.push_back(eqip);
			}
			if(equip_items.size() > 0)
			{
				CLogicEquipment logicEquip;
				ret = logicEquip.AddItems(uid,equip_items,result["equipments"], true);
				if(ret)
				{
					error_log("Add_Equip_error_12 uid=%u ", uid);
					return R_ERR_DATA;
				}
			}
			newAct["s"] = 1;  //将状态置1
		}
		else
		{
			PARAM_ERROR_RETURN_MSG("have recv or not enough time");
		}
	}
	else
	{
		PARAM_ERROR_RETURN_MSG("today not active");
	}

	newAct["ts"] = Time::GetGlobalTime();
	result["newAct"] = newAct;
	ret = logicSecinc.SetOneSecinc(uid, newAct);
	if(ret)
		return ret;

	ret = logicUser.SetUserLimit(uid, dataUser);
	if(ret)
		return ret;
	return R_SUCCESS;
}

//畅享商店
int CLogicCMD::EnjoyStore(unsigned uid, Json::Value &data, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	//判断是否在活动开启时间之内
	unsigned now = Time::GetGlobalTime();
	ActInfoConfig actCfg = ActInfoConfig(CONFIG_TWOHOLIDAY_ENJOY);
	if(!actCfg.IsActive())
		return R_ERR_LOGIC;

	int ret = 0;
	Json::FastWriter writer;
	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	ret = logicUser.GetUser(uid,dataUser);
	if(ret)
	{
		error_log("[get_user_info_failed] [uid=%u]",uid);
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

	unsigned type_index, reward_index;  //识别是哪一个物品
	if(!Json::GetUInt(data, "type_index", type_index) || !Json::GetUInt(data, "reward_index", reward_index))
	{
		error_log("para_error");
		return R_ERR_PARAM;
	}
	if(type_index < 0 || type_index > 4 || reward_index < 0 || reward_index > 4)
	{
		return R_ERR_PARAM;
	}

	Json::Value newAct; //newAct初始化
	CLogicSecinc logicSecinc;
	ret = logicSecinc.GetSecinc(uid, NAT_ENJOYSTORE, newAct);
	if (ret == R_ERR_NO_DATA)
	{
		newAct["id"] = NAT_ENJOYSTORE;
		newAct["v"] = actCfg.Version();
	}
	else if(ret)
		return ret;
	if(!newAct.isMember("id"))
	{
		newAct["id"] = NAT_ENJOYSTORE;
	}

	if(actCfg.Version() != newAct["v"].asInt())
	{
		newAct["v"] = actCfg.Version();
		Json::Value array(Json::arrayValue);
		for (int i = 0; i < 5; i++)
			array.append("00000");
		newAct["a"] = array;   //记录了物品的购买状态（共有5栏，每栏5个）
	}

	//起到每日清零的作用
	if(!newAct.isMember("ts") || !Time::IsToday(newAct["ts"].asUInt()) || !newAct.isMember("a"))
	{
		Json::Value array(Json::arrayValue);
		for (int i = 0; i < 5; i++)
			array.append("00000");
		newAct["a"] = array;   //记录了物品的购买状态（共有5栏，每栏5个）
	}

	string buy_status = newAct["a"][type_index].asString();
	Json::Reader reader;
	Json::Value user_flag;
	reader.parse(dataUser.user_flag,user_flag);
	if (!user_flag.isMember("chgs") || !user_flag["chgs"].isArray())
	{
		error_log("chgs error");
		DATA_ERROR_RETURN_MSG("chgs error");
	}

	if(type_index == 0)
	{
		if(buy_status[reward_index] != '0')
		{
			PARAM_ERROR_RETURN_MSG("have buy ");
		}
		unsigned need_cash = ConfigManager::Instance()->m_twoholidaycfg.m_config.recharge_buy(type_index).cheap_buy(reward_index).price_discount();
		unsigned need_coins = 0;
		CLogicPay logicPay;
		DataPay payData;
		bool bsave = false;
		unsigned eqid = ConfigManager::Instance()->m_twoholidaycfg.m_config.recharge_buy(type_index).cheap_buy(reward_index).reward().equips(0).eqid();
		unsigned count = ConfigManager::Instance()->m_twoholidaycfg.m_config.recharge_buy(type_index).cheap_buy(reward_index).reward().equips(0).c();
		string log_reason = "activity_twoholiday_"+ CTrans::UTOS(eqid) + ":" + CTrans::UTOS(count);
		ret = logicPay.ProcessOrderForBackend(uid, -need_cash, -need_coins, payData, log_reason, user_flag, bsave);
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
		//发商品
		CLogicEquipment logicEquip;
		logicEquip.AddOneItem(uid, eqid, count, "enjoystore", result["equipments"], true);
	}
	else
	{
		unsigned size = user_flag["chgs"].size();
		unsigned recharge_today = 0; //今天充值的金额
		for (unsigned i = 0; i < size; ++i)
		{
			unsigned ts  = user_flag["chgs"][i][0u].asUInt();
			if(!CTime::IsDiffDay(ts, now))  //如果是当天
			{
				recharge_today = user_flag["chgs"][i][1u].asUInt();

				unsigned limit_num = ConfigManager::Instance()->m_twoholidaycfg.m_config.recharge_buy_size();
				unsigned record_index = 0; //记录当日充值达到第几档
				for(unsigned j = 0; j < limit_num; ++j)
				{
					//当天充值金额达到标准
					if(recharge_today >= ConfigManager::Instance()->m_twoholidaycfg.m_config.recharge_buy(j).recharge_limit())
					{
						record_index += 1;
					}
					else
					{
						break;
					}
				}
				//如果有资格购买该商品并且今日还未购买
				if(type_index + 1 <= record_index && buy_status[reward_index] == '0')
				{
					unsigned need_cash = ConfigManager::Instance()->m_twoholidaycfg.m_config.recharge_buy(type_index).cheap_buy(reward_index).price_discount();
					unsigned need_coins = 0;
					CLogicPay logicPay;
					DataPay payData;
					bool bsave = false;
					unsigned eqid = ConfigManager::Instance()->m_twoholidaycfg.m_config.recharge_buy(type_index).cheap_buy(reward_index).reward().equips(0).eqid();
					unsigned count = ConfigManager::Instance()->m_twoholidaycfg.m_config.recharge_buy(type_index).cheap_buy(reward_index).reward().equips(0).c();
					string log_reason = "activity_twoholiday_"+ CTrans::UTOS(eqid) + ":" + CTrans::UTOS(count);
					ret = logicPay.ProcessOrderForBackend(uid, -need_cash, -need_coins, payData, log_reason, user_flag, bsave);
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
					//发商品
					CLogicEquipment logicEquip;
					logicEquip.AddOneItem(uid, eqid, count, "enjoystore", result["equipments"], true);
				}
				else
				{
					PARAM_ERROR_RETURN_MSG("have buy or can not buy");
				}
				break;  //已经找到当日的购买记录，处理完直接退出循环
			}
		}
	}

	newAct["ts"] = Time::GetGlobalTime();
	buy_status[reward_index] = '1';
	newAct["a"][type_index] = buy_status.c_str();
	result["newAct"] = newAct;

	ret = logicSecinc.SetOneSecinc(uid, newAct);
	if(ret)
		return ret;
	ret = logicUser.SetUser(uid, dataUser);
	if(ret)
		return ret;
	return R_SUCCESS;
}
//vip奖励
int CLogicCMD::VipReward(unsigned uid, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	//判断是否在活动开启时间之内
	unsigned now = Time::GetGlobalTime();
	ActInfoConfig actCfg = ActInfoConfig(CONFIG_TWOHOLIDAY_ENJOY);
	if(!actCfg.IsActive())
		return R_ERR_LOGIC;

	int ret = 0;
	Json::FastWriter writer;
	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	ret = logicUser.GetUserLimit(uid,dataUser);
	if(ret)
	{
		error_log("[get_user_info_failed] [uid=%u]",uid);
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

	Json::Value newAct; //newAct初始化
	CLogicSecinc logicSecinc;
	ret = logicSecinc.GetSecinc(uid, NAT_VIPREWARD, newAct);
	if (ret == R_ERR_NO_DATA)
	{
		newAct["id"] = NAT_VIPREWARD;
		newAct["v"] = actCfg.Version();
	}
	else if(ret)
		return ret;
	if(!newAct.isMember("id"))
	{
		newAct["id"] = NAT_VIPREWARD;
	}

	if(actCfg.Version() != newAct["v"].asInt())
	{
		newAct["v"] = actCfg.Version();
		newAct["s"]  = 0;
	}

	if(!newAct.isMember("ts") || !Time::IsToday(newAct["ts"].asUInt()) || !newAct.isMember("s"))
	{
		newAct["s"]  = 0; //vip奖励领取状态（0：没领；1：领过）
	}
	unsigned vip_level = dataUser.viplevel;

	if(vip_level >= 1 && vip_level <= 3 && newAct["s"].asUInt() == 0)
	{
		//发奖励
		unsigned reward_num = ConfigManager::Instance()->m_twoholidaycfg.m_config.vip_reward().reward_one_size();
		vector<ItemAdd> equip_items;
		equip_items.clear();
		for(unsigned j = 0; j < reward_num; ++j)
		{
			unsigned eqid = ConfigManager::Instance()->m_twoholidaycfg.m_config.vip_reward().reward_one(j).equips(0).eqid();
			unsigned count = ConfigManager::Instance()->m_twoholidaycfg.m_config.vip_reward().reward_one(j).equips(0).c();
			ItemAdd eqip;
			eqip.eqid = eqid;
			eqip.count = count;
			string reason = "vipreward1T3_";
			eqip.reason = reason.append(CTrans::UTOS(j));
			equip_items.push_back(eqip);
		}
		if(equip_items.size() > 0)
		{
			CLogicEquipment logicEquip;
			ret = logicEquip.AddItems(uid,equip_items,result["equipments"], true);
			if(ret)
			{
				error_log("Add_Equip_error_vip1_3 uid=%u ", uid);
				return R_ERR_DATA;
			}
		}
	}
	else if(vip_level >= 4 && vip_level <= 6 && newAct["s"].asUInt() == 0)
	{
		//发奖励
		unsigned reward_num = ConfigManager::Instance()->m_twoholidaycfg.m_config.vip_reward().reward_two_size();
		vector<ItemAdd> equip_items;
		equip_items.clear();
		for(unsigned j = 0; j < reward_num; ++j)
		{
			unsigned eqid = ConfigManager::Instance()->m_twoholidaycfg.m_config.vip_reward().reward_two(j).equips(0).eqid();
			unsigned count = ConfigManager::Instance()->m_twoholidaycfg.m_config.vip_reward().reward_two(j).equips(0).c();
			ItemAdd eqip;
			eqip.eqid = eqid;
			eqip.count = count;
			string reason = "vipreward4T6_";
			eqip.reason = reason.append(CTrans::UTOS(j));
			equip_items.push_back(eqip);
		}
		if(equip_items.size() > 0)
		{
			CLogicEquipment logicEquip;
			ret = logicEquip.AddItems(uid,equip_items,result["equipments"], true);
			if(ret)
			{
				error_log("Add_Equip_error_vip1_3 uid=%u ", uid);
				return R_ERR_DATA;
			}
		}
	}
	else if(vip_level >= 7 && vip_level <= 10 && newAct["s"].asUInt() == 0)
	{
		//发奖励
		unsigned reward_num = ConfigManager::Instance()->m_twoholidaycfg.m_config.vip_reward().reward_three_size();
		vector<ItemAdd> equip_items;
		equip_items.clear();
		for(unsigned j = 0; j < reward_num; ++j)
		{
			unsigned eqid = ConfigManager::Instance()->m_twoholidaycfg.m_config.vip_reward().reward_three(j).equips(0).eqid();
			unsigned count = ConfigManager::Instance()->m_twoholidaycfg.m_config.vip_reward().reward_three(j).equips(0).c();
			ItemAdd eqip;
			eqip.eqid = eqid;
			eqip.count = count;
			string reason = "vipreward7T10_";
			eqip.reason = reason.append(CTrans::UTOS(j));
			equip_items.push_back(eqip);
		}
		if(equip_items.size() > 0)
		{
			CLogicEquipment logicEquip;
			ret = logicEquip.AddItems(uid,equip_items,result["equipments"], true);
			if(ret)
			{
				error_log("Add_Equip_error_vip7_10 uid=%u ", uid);
				return R_ERR_DATA;
			}
		}
	}
	else
	{
		PARAM_ERROR_RETURN_MSG("have recv or viplevel not enough");
	}

	newAct["ts"] = Time::GetGlobalTime();
	newAct["s"] = 1;
	result["newAct"] = newAct;
	ret = logicSecinc.SetOneSecinc(uid, newAct);
	if(ret)
		return ret;

	ret = logicUser.SetUserLimit(uid, dataUser);
	if(ret)
		return ret;
	return R_SUCCESS;
}

int CLogicCMD::SyntheticGem(unsigned uid, Json::Value &data, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	int ret = 0;
	Json::FastWriter writer;
	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	ret = logicUser.GetUserLimit(uid,dataUser);
	if(ret)
	{
		error_log("[get_user_info_failed] [uid=%u]",uid);
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

	unsigned count = 0, gem_id = 0;
	if(!Json::GetUInt(data, "count", count) || !Json::GetUInt(data, "gem_id", gem_id))
	{
		error_log("para_error");
		return R_ERR_PARAM;
	}

	if(4014 == gem_id || 0 == gem_id%10) //最高级等级石头
	{
		return R_ERR_PARAM;
	}

	unsigned  snap_gem_id = 0, snap_gem_count = 0;
	if(data.isMember("snap_gem_id"))
	{
		if(!IS_SOULSTONE_EQID(gem_id) && !IS_BUILDSTONE_EQID(gem_id))
			return R_ERR_LOGIC;

		Json::GetUInt(data, "snap_gem_id", snap_gem_id);
		Json::GetUInt(data, "snap_gem_count", snap_gem_count);

		if(IS_SOULSTONE_EQID(gem_id) && GET_SNAP_SOUL_EQID(gem_id%10) != snap_gem_id)			//魂石判断
		{
			error_log("[soulstone_para_error][uid=%u,gem_id=%u,snap_gem_id=%u]",uid, gem_id, snap_gem_id);
			return R_ERR_PARAM;
		}

		if(IS_BUILDSTONE_EQID(gem_id) && GET_SNAP_BUILDSTONE_EQID(gem_id%10) != snap_gem_id)			//宝石判断
		{
			error_log("[buildstone_para_error][uid=%u,gem_id=%u,snap_gem_id=%u]",uid, gem_id, snap_gem_id);
			return R_ERR_PARAM;
		}
	}

	unsigned synthetic_count = 0;
	unsigned synthetic_gem_id = gem_id + 1;
#ifdef SG_16_VER
	if(IS_INTENSIFY_EQID(gem_id))		//强化石
	{
		synthetic_count = (count + snap_gem_count) / 2;
	}
	else if(IS_SOULSTONE_EQID(gem_id))   //魂石
	{
		if(count < snap_gem_count * 2)
		{
			error_log("[syntheticgem_soulgem_count_gt][uid=%u,gem_count=%u,snap_gem_count=%u]", uid, count, snap_gem_count);
			return R_ERR_PARAM;
		}
		synthetic_count = (count + snap_gem_count) / 3;
	}
	else if(IS_BUILDSTONE_EQID(gem_id))   //宝石
	{
		if(count < snap_gem_count * 2)
		{
			error_log("[syntheticgem_buildgem_count_gt][uid=%u,gem_count=%u,snap_gem_count=%u]", uid, count, snap_gem_count);
			return R_ERR_PARAM;
		}
		synthetic_count = (count + snap_gem_count) / 3;
	}
	else if(IS_SUCCINCT_EQID(gem_id))		//洗练石
	{
		synthetic_count = (count + snap_gem_count) / 3;
	}
	else if(IS_CAN_SYN_SPECIALSTONE_EQID(gem_id))
	{
		synthetic_count = (count + snap_gem_count) / 3;
	}
	else
		return R_ERR_LOGIC;
#else
	if(IS_INTENSIFY_EQID(gem_id))		//强化石
	{
		synthetic_count = (count + snap_gem_count) / 2;
	}
	else if(IS_SOULSTONE_EQID(gem_id))   //魂石
	{
		if(count < snap_gem_count * 3)
		{
			error_log("[syntheticgem_soulgem_count_gt][uid=%u,gem_count=%u,snap_gem_count=%u]", uid, count, snap_gem_count);
			return R_ERR_PARAM;
		}
		synthetic_count = (count + snap_gem_count) / 4;
	}
	else if(IS_BUILDSTONE_EQID(gem_id) || IS_DOUBLE_GEM(gem_id))   //宝石和双属性宝石
	{
		if(count < snap_gem_count)
		{
			error_log("[syntheticgem_buildgem_count_gt][uid=%u,gem_count=%u,snap_gem_count=%u]", uid, count, snap_gem_count);
			return R_ERR_PARAM;
		}
		synthetic_count = (count + snap_gem_count) / 4;
	}
	else if(IS_SUCCINCT_EQID(gem_id))		//洗练石
	{
		synthetic_count = (count + snap_gem_count) / 4;
	}
	else if(IS_CAN_SYN_SPECIALSTONE_EQID(gem_id))
	{
		synthetic_count = (count + snap_gem_count) / 4;
	}
	else
		return R_ERR_LOGIC;
#endif

	CLogicEquipment logicEquip;
	Json::Value equip_data;
	ret = logicEquip.GetEquipment(uid, 0, equip_data);
	if(ret)
		return ret;

	if(IS_INTENSIFY_EQID(gem_id) || IS_SUCCINCT_EQID(gem_id)) //洗练石和强化石
	{
		for(int i=0; i<equip_data.size(); ++i)
		{
			if(equip_data[i]["id"].asUInt() == gem_id)
			{
				string reason = "back_synthetic_gem";
				equip_data[i]["count"] = equip_data[i]["count"].asUInt() - count;
				ret = logicEquip.UseEquipment(uid, equip_data[i]["id"].asUInt(), equip_data[i]["ud"].asUInt(), count, reason);
				if(ret)
					return ret;
				result["del_equip"] = equip_data[i];
				break;
			}
		}
	}
	else					//不叠加的宝石和魂石
	{
		unsigned back_count = 0, back_snap_count = 0, reselt_id = 0;
		vector <unsigned> del_gem_ids;
		vector <unsigned> del_gem_equids;
		vector <string> del_data_ids;

		for(int i=0; i<equip_data.size(); ++i)
		{
			if(equip_data[i]["id"].asInt() == gem_id  && equip_data[i].isMember("status") && equip_data[i]["status"].asUInt() == 0)
			{
				if(back_count == count)
				{
					continue;
				}
				++back_count;
				del_gem_ids.push_back(equip_data[i]["ud"].asUInt());
				del_gem_equids.push_back(equip_data[i]["id"].asUInt());
				del_data_ids.push_back(writer.write(equip_data[i]));
				result["del_equip"][reselt_id] = equip_data[i];
				++reselt_id;
			}

			if(equip_data[i]["id"].asInt() == snap_gem_id &&
			equip_data[i].isMember("ats") && equip_data[i]["ats"].asUInt() >= Time::GetGlobalTime())
			{
				if(back_snap_count == snap_gem_count )
				{
					continue;
				}
				++back_snap_count;
				del_gem_ids.push_back(equip_data[i]["ud"].asUInt());
				del_gem_equids.push_back(equip_data[i]["id"].asUInt());
				del_data_ids.push_back(writer.write(equip_data[i]));
				result["del_equip"][reselt_id] = equip_data[i];
				++reselt_id;
			}
		}

		if(back_snap_count + back_count != count + snap_gem_count)
		{
			error_log("[syntheticgem_gem_count_lacking][uid=%u,gem_id=%u,snap_gem_id=%u,gem_count=%u,snap_gem_count=%u,back_count=%u,back_snap_count=%u]",
					uid, gem_id, snap_gem_id, count, snap_gem_count, back_count, back_snap_count);
			return R_ERROR;
		}

		for(int i=0; i<del_gem_ids.size(); i++)
		{
			ret = logicEquip.Del(uid, del_gem_ids[i]);
			if(ret)
				return ret;
			EQUIPMENT_LOG("uid=%u,id=%u,eqid=%d,act=%s,chg=%d,count=%d,code=%s,data=%s",uid,del_gem_ids[i],del_gem_equids[i],
							"del",-1,0,"back_synthetic_gem_del",del_data_ids[i].c_str());
		}
	}

	ret = logicEquip.AddOneItem(uid, synthetic_gem_id, synthetic_count,"back_synthetic_gem_add",result["add_equip"], true);
	if(ret)
		return ret;

	ret = logicUser.SetUserLimit(uid, dataUser);
	if(ret)
		return ret;
	return R_SUCCESS;
}

int CLogicCMD::HammerHit(unsigned uid, unsigned equd, int hitCount, Json::Value &result, unsigned &lasttime,unsigned &seqid)
{
	int ret = 0;
	bool isOneHit;
	if (hitCount == 1)
		isOneHit = true;
	else if (hitCount == 100)
		isOneHit = false;
	else
	{
		error_log("[hammerhitdata hitCount error] [uid=%u, hitCount=%d]",uid, hitCount);
		return R_ERR_PARAM;
	}

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
	Json::Value user_stat;
	reader.parse(dataUser.user_stat,user_stat);

	unsigned curHammerId = 0;
	unsigned point = 0;
	Json::Value stage_flag;
	Json::GetUInt(user_stat,"hlv",curHammerId);
	Json::GetUInt(user_stat,"hsr",point);
	Json::GetArray(user_stat, "hrb", stage_flag);

	LogicHammer lgHammer;
	ret = lgHammer.hitJar(uid, curHammerId, equd, result, isOneHit);
	if(ret)
		return ret;

	point += result["hammerCost"].asUInt() * 10;
	if ((ret = lgHammer.StageReward(uid, point, stage_flag, result)) > 0)
	{
		return ret;
	}

	result["hsr"] = point;
	user_stat["hlv"] = result["hlv"];
	user_stat["hsr"] = point;
	user_stat["hrb"] = result["hrb"];

	dataUser.user_stat = writer.write(user_stat);
	ret = logicUser.SetUser(uid, dataUser);
	if(ret)
		return ret;

	return R_SUCCESS;
}

int CLogicCMD::HammerHitAllServer(unsigned uid, unsigned equd, int hitCount, Json::Value &result, unsigned &lasttime,unsigned &seqid)
{
	unsigned now = Time::GetGlobalTime();
	if(now < Config::GetIntValue(CONFIG_HAMMERHIT_ALLSERVER_BEGIN_TS)
	|| now > Config::GetIntValue(CONFIG_HAMMERHIT_ALLSERVER_END_TS))
	{
		error_log("hammerHit_allServer_time_error");
		return R_ERR_REFUSE;
	}

	int ret = 0;
	bool isOneHit;
	if (hitCount == 1)
		isOneHit = true;
	else if (hitCount == 100)
		isOneHit = false;
	else
	{
		error_log("[hammerhitdata hitCount error] [uid=%u, hitCount=%d]",uid, hitCount);
		return R_ERR_PARAM;
	}

	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	ret = logicUser.GetUserLimit(uid,dataUser);
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

	Json::Value newAct;
	CLogicSecinc logicSec;
	ret = logicSec.GetSecinc(uid, NAT_HAMMERHIT_ALLSERVER, newAct);
	if (ret == R_ERR_NO_DATA)
	{
		newAct["v"] = Config::GetIntValue(CONFIG_HAMMERHIT_ALLSERVER_VER);
		newAct["id"] = NAT_HAMMERHIT_ALLSERVER;
		newAct["lvl"] = 0; //罐子等级
		newAct["p"] = Json::Value(Json::arrayValue); //当天积分(数组，积分和时间戳)
		newAct["p"][0u] = now;
		newAct["p"][1u] = 0;
		newAct["n"] = 0; //还需多少积分能发送请求
		newAct["pa"] = 0; //总积分
	}
	else if (ret)
	{
		return ret;
	}

	if (newAct["v"].asUInt() != Config::GetIntValue(CONFIG_HAMMERHIT_ALLSERVER_VER))
	{
		newAct["v"] = Config::GetIntValue(CONFIG_HAMMERHIT_ALLSERVER_VER);
		newAct["id"] = NAT_HAMMERHIT_ALLSERVER;
		newAct["lvl"] = 0; //罐子等级
		newAct["p"] = Json::Value(Json::arrayValue); //当天积分(数组，积分和时间戳)
		newAct["p"][0u] = now;
		newAct["p"][1u] = 0;
		newAct["n"] = 0; //还需多少积分能发送请求
		newAct["pa"] = 0; //总积分
	}

	unsigned curHammerId = newAct["lvl"].asUInt();
	unsigned points = 0;
	unsigned pointsDay = 0;
	unsigned pointsAll = newAct["pa"].asUInt();
	unsigned need = 0;

	LogicHammer lgHammer;
	ret = lgHammer.hitJar(uid, curHammerId, equd, result, isOneHit, true);
	if(ret)
		return ret;

	newAct["lvl"] = result["hlv"].asUInt();
	points += result["hammerCost"].asUInt() * 10;

	time_t dd;
	time(&dd);
	struct tm *pTm = localtime(&dd);
	int tempSec = pTm->tm_sec;
	int tempMin = pTm->tm_min;
	int tempHour = pTm->tm_hour;
	unsigned tempNow = tempSec + tempMin * 60 + tempHour *3600;

	if (tempNow < 79200)
	{
		if (CTime::IsDiffDay(newAct["p"][0u].asUInt(), now))
		{
			need = 0;
			pointsDay = points;
			newAct["p"][0u] = now;
			newAct["p"][1u] = pointsDay;
			newAct["n"] = 0;
		}
		else
		{
			need = newAct["n"].asUInt();
			pointsDay = newAct["p"][1u].asUInt() + points;
			newAct["p"][1u] = pointsDay;
		}
	}
	else
	{
		if (CTime::IsDiffDay(newAct["p"][0u].asUInt(), now))
		{
			pointsDay = points;
			need = 0;
		}
		else
		{
			pointsDay = newAct["p"][1u].asUInt();
			need = newAct["n"].asUInt();
		}
	}

	pointsAll += points;
	newAct["pa"] = pointsAll;

	if (points >= need)
	{
		//向全服服务器发送请求
		CLogicUserBasic logicUserBasic;
		DataUserBasic dataUserBasic;
		logicUserBasic.GetUserBasicLimit(uid,OpenPlatform::GetType(),dataUserBasic);

		CLogicPointsRank logicPR;
		ret = logicPR.SetUser(uid, pointsDay, pointsAll, dataUserBasic.name, need);
		newAct["n"] = need;
	}
	else
	{
		need -= points;
		newAct["n"] = need;
	}

	result["newAct"] = Json::Value(Json::arrayValue);
	result["newAct"].append(newAct);

	ret = logicSec.SetOneSecinc(uid, newAct);
	if (ret)
		return ret;
	ret = logicUser.SetUserLimit(uid, dataUser);
	if(ret)
		return ret;

	return R_SUCCESS;
}

int CLogicCMD::UseShip(unsigned uid, unsigned torch, unsigned classType, Json::Value &result, unsigned &lasttime,unsigned &seqid)
{
	int ret = 0;
	CDataXML *dataXML = CDataXML::GetCDataXML();
	if(!dataXML)
	{
		error_log("GetInitXML fail");
		return R_ERR_DB;
	}

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

	Json::Value stats;
	Json::Reader reader;
	reader.parse(dataUser.user_stat,stats);
	Json::FastWriter writer;

	unsigned boat = 0, bt = 0;
	if(!stats.isMember("boat"))
	{
		stats["boat"][0u] = 0;
		stats["boat"][1u] = 0;
	}
	boat = stats["boat"][0u].asUInt();
	Json::GetUInt(stats,"bt",bt);
	++boat;
	if(boat > 3 || boat < 0 || bt < 1 || bt > 5)
		return R_ERR_LOGIC;

	unsigned newbt;
	ret = dataXML->GetBoatType(newbt);
	if(ret)
		return ret;
	XMLBoat newboat;
	ret = dataXML->GetBoat(bt, newboat);
	if(ret)
		return ret;
	unsigned posy = (Math::GetRandomInt(10) + 6) * 20;
	Json::Value param;
	param["posy"] = posy;
	param["attacktimes"] = 0;
	param["type"] = bt;
	param["startts"] = Time::GetGlobalTime();
	param["endts"] = Time::GetGlobalTime() + newboat.time*60;
	param["uid"] = uid;
	param["yellow_torch_burning"] = torch;
	if (classType<1 || classType > 3)
		return R_ERR_PARAM;
	param["classType"] = classType;
	CLogicRiver logicRiver;
	ret = logicRiver.SetShip(uid, param);
	if(ret)
		return ret;

	stats["boat"][0u] = boat;
	stats["bt"] = newbt;
	result["boat"] = stats["boat"];
	result["bt"] = stats["bt"];
	result["posy"] = posy;

	dataUser.user_stat = writer.write(stats);
	ret = logicUser.SetUser(uid, dataUser);
	if(ret)
		return ret;

	return R_SUCCESS;
}
int CLogicCMD::RefreshShip(unsigned uid, unsigned refreshType, unsigned equd, Json::Value &result, unsigned &lasttime,unsigned &seqid)
{
	int ret = 0;
	CDataXML *dataXML = CDataXML::GetCDataXML();
	if(!dataXML)
	{
		error_log("GetInitXML fail");
		return R_ERR_DB;
	}

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

	Json::Value stats;
	Json::Reader reader;
	reader.parse(dataUser.user_stat,stats);
	Json::FastWriter writer;
	Json::Value user_flag;
	bool bsave = false;
	reader.parse(dataUser.user_flag,user_flag);

	int cash, coin;
	if(refreshType == 0)
	{
		cash = 0;
		coin = -10;
	}
	else if(refreshType == 1)
	{
		cash = -10;
		coin = 0;
	}
	else
	{
		cash = -50;
		coin = 0;
	}
	if(refreshType == 0 || refreshType == 1)
	{
#ifdef SG_USE_CASH

		CLogicPay logicPay;
		DataPay payData;
		ret = logicPay.ProcessOrderForBackend(uid, cash, coin, payData, "play_boat_boatrefresh", user_flag, bsave);
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
#else
		CLogicEquipment equipment;
		ret = equipment.UseEquipment(uid, refresh_key_low, equd, 1, "play_boat_boatrefresh");
		if(ret)
			return ret;
#endif
	}
	else
	{
		CLogicPay logicPay;
		DataPay payData;
		ret = logicPay.ProcessOrderForBackend(uid, cash, coin, payData, "play_boat_boatrefresh", user_flag, bsave);
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


	unsigned newbt;
	if(refreshType >= 2)
		newbt = 5;
	else
	{
		ret = dataXML->GetBoatType(newbt);
		if(ret)
			return ret;
	}
	result["bt"] = stats["bt"] = newbt;

	dataUser.user_stat = writer.write(stats);
	ret = logicUser.SetUser(uid, dataUser);
	if(ret)
		return ret;

	return R_SUCCESS;
}

int CLogicCMD::HeroPowerUp(unsigned uid, unsigned heroud, unsigned equd, Json::Value &result, unsigned &lasttime,unsigned &seqid)
{
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

	Json::Value hero, equip;
	CLogicHero logicHero;
	ret = logicHero.Get(uid, heroud, hero);
	if(ret)
		return ret;

	XMLHero xmlhero;
	string hid = hero["id"].asString();
	ret = dataXML->GetHero(CDataXML::Str2Hero(hid), xmlhero);
	if(ret)
		return ret;

	CLogicEquipment logicEquipment;
	ret = logicEquipment.Get(uid, equd, equip);
	if(ret)
		return ret;

	int grade, level;
	unsigned eqid = equip["id"].asUInt();
	ret = CDataXML::GetGradeLevel(eqid, grade, level);
	if(ret)
		return ret;
	if(grade != hero["grade"].asInt())
		return R_ERR_LOGIC;
	float maxpt = CDataXML::GetMaxGradePoint(grade, (float)xmlhero.point);
	float pt = hero["pt"].asDouble();
	if(pt > maxpt)
		return R_ERR_LOGIC;

	ret = logicEquipment.UseEquipment(uid, eqid, equd, 1, "heropowerup");
	if(ret)
		return ret;
	pt += CDataXML::GetRandomGradePoint(xmlhero.type, grade, level);
	if(pt >= maxpt)
		pt = maxpt;

	//zkw add  在活动内，发放奖励
	if (Time::GetGlobalTime() >= Config::GetIntValue(CONFIG_PEIYANG_BEGIN_TS) &&
		Time::GetGlobalTime() <= Config::GetIntValue(CONFIG_PEIYANG_END_TS))
	{
		ret = HeroPowerUpSendReward(uid, heroud, pt, dataXML, hero, result);
		if (ret)
		{
			error_log("HeroPowerUpSendReward error, uid=%u, heroud=%u, pt=%f", uid, heroud, pt);
			return ret;
		}
	}
	//zkw add over

	hero["pt"] = pt;
	ret = logicHero.Chg(uid, heroud, hero);
	if(ret)
		return ret;
	result["pt"] = pt;

	ret = logicUser.SetUserLimit(uid, dataUser);
	if(ret)
		return ret;

	return R_SUCCESS;
}


int CLogicCMD::HeroPowerUpSendReward(unsigned uid, unsigned heroud, float pt, CDataXML * dataXML, Json::Value & hero, Json::Value &result)
{
	bool reset_secinc = false, reset_hero_port = false;
	CLogicSecinc Secinc;
	Json::Value SecincDataOne;
	int ret = 0;
	ret = Secinc.GetSecinc(uid, NAT_PEIYANG_1, SecincDataOne);
	if (ret == R_ERR_NO_DATA)
	{
		reset_secinc = true;
		reset_hero_port = true;
	} else if (!ret)
	{
		if ((!SecincDataOne.isMember("ver")) || SecincDataOne["ver"].asInt() != Config::GetIntValue(CONFIG_PEIYANG_VER))
		{
			reset_secinc = true;
			reset_hero_port = true;
		}
	} else
	{
		error_log("GetSecinc_error,uid = %u", uid);
		return ret;
	}

	Json::Value SecincDataTwo;
	ret = Secinc.GetSecinc(uid, NAT_PEIYANG_2, SecincDataTwo);
	if (ret == R_ERR_NO_DATA)
	{
		reset_secinc = true;
		reset_hero_port = true;
	} else if (ret)
	{
		error_log("GetSecinc_error,uid = %u", uid);
		return ret;
	}

	if (reset_secinc)
	{
		SecincDataOne["id"] = NAT_PEIYANG_1;
		SecincDataOne["ver"] = Config::GetIntValue(CONFIG_PEIYANG_VER);
		Json::Value array_rd(Json::arrayValue);
		for(unsigned i = 0; i < HEROGROWDEVELOP_BIG_CNT; i++)
			array_rd.append(0);
		SecincDataOne["rd"] = array_rd;
		Json::Value array(Json::arrayValue);
		for (int i = 0; i < HEROGROWDEVELOP_BIG_CNT; i++)
		{
			Json::Value subArray(Json::arrayValue);
			for (int j = 0; j < HEROGROWDEVELOP_SMALL_CNT; j++)
				subArray.append(0);
			array.append(subArray);
		}
		SecincDataOne["gd"] = array;

		SecincDataTwo["id"] = NAT_PEIYANG_2;
		SecincDataTwo["mh"] = array;
	}

	if ((!hero.isMember("pot")) || (!hero["pot"].isMember("g")) || (!hero["pot"].isMember("p")))
	{
		reset_hero_port = true;
	}

	if (reset_hero_port)
	{
		hero["pot"]["g"] = hero["grade"].asInt();
		hero["pot"]["p"] = hero["pt"].asDouble();
	}


	//2.是否已经发放过了，或者是否已经都发放了
	bool goto_end = false;
	unsigned hero_grade = hero["grade"].asInt();
	if (SecincDataOne["rd"][hero_grade].asInt() >= HEROGROWDEVELOP_SMALL_CNT)
	{
		goto_end = true;
	}

	if (!goto_end)
	{
		bool have_got = false;
		for(unsigned inx = 0; inx != HEROGROWDEVELOP_SMALL_CNT; ++inx)
		{
			if (SecincDataTwo["mh"][hero_grade][inx].asUInt() == heroud)
			{
				have_got = true;
				break;
			}
		}
		if (have_got)
		{
			goto_end = true;
		}
	}

	if (!goto_end)
	{
		//读取配置,根据hero的阶 读取相应的require
		unsigned require_add_pt = 0;
		ret = dataXML->GetGrowDevelopCond(hero_grade + 1, require_add_pt);
		if(ret)
			return ret;
		if (hero["pot"]["p"].asDouble() + require_add_pt > pt)
		{
			goto_end = true;   //不满足发放物品的条件
		}
	}

	//发放奖励
	if (!goto_end)   //满足了发送奖励的要求
	{
		unsigned index_ud = SecincDataOne["rd"][hero_grade].asInt();
		SecincDataTwo["mh"][hero_grade][index_ud] = heroud;
		SecincDataOne["rd"][hero_grade] = index_ud + 1;
	}

	//将两个newAct写回去
	if (reset_secinc || !goto_end)
	{
		ret = Secinc.SetOneSecinc(uid, SecincDataOne);
		if (ret)
		{
			error_log("HeroPowerUpSendReward SecincDataOne failed. uid=%u, ret=%d", uid, ret);
			return ret;
		}
		result["newAct"][0u] = SecincDataOne;
		ret = Secinc.SetOneSecinc(uid, SecincDataTwo);
		if (ret)
		{
			error_log("HeroPowerUpSendReward SecincDataTwo failed. uid=%u, ret=%d", uid, ret);
			return ret;
		}
		result["newAct"][1u] = SecincDataTwo;
	}

	if (reset_hero_port)
	{
		result["pot"] = hero["pot"];
	}

	return R_SUCCESS;
}


int CLogicCMD::HeroPower2Up(unsigned uid, unsigned heroud, unsigned equd, unsigned specialud, unsigned equd1, unsigned equd2, unsigned equd3, unsigned equd4, unsigned type, Json::Value &result, unsigned &lasttime,unsigned &seqid)
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

	Json::Value hero, equip;
	CLogicHero logicHero;
	ret = logicHero.Get(uid, heroud, hero);
	if(ret)
		return ret;

	if(!hero.isMember("hs"))
		hero["hs"][0u] = hero["hs"][1u] = hero["hs"][2u] = hero["hs"][3u] = 0;
	else if(!hero["hs"].isArray() || hero["hs"].size() != 4)
		return R_ERR_DATA;
	unsigned level = hero["hs"][0u].asUInt();
	unsigned exp = hero["hs"][1u].asUInt();
	if(hero["grade"].asInt() < 3 || level >= HERO_POWER_2_MAX)
		return R_ERR_LOGIC;

	int used = 0;
	//unsigned total = HERO_POWER_2_UP_COST[level][2] * (100 - Math::GetRandomInt(20));
	unsigned total = HERO_POWER_2_UP_COST[level][2];
	unsigned old_level = level;

	//type:0-单次进阶，1-自动进阶至下一层
	if(type == 0)
	{
		used = HERO_POWER_2_UP_COST[level][0];
		exp += HERO_POWER_2_UP_COST[level][1];

		if(exp>= total)
		{
			++level;
			exp = 0;
			if(level %10 == 1)
				hero["hs"][3u] = 0;
		}
	}
	else
	{
		do
		{
			used += HERO_POWER_2_UP_COST[level][0];
			exp += HERO_POWER_2_UP_COST[level][1];
		}while(exp < total);
		++level;
		exp = 0;
		if(level %10 == 1)
			hero["hs"][3u] = 0;
	}

	CLogicEquipment logicEquipment;

	//激活觉醒专用-洗髓真丹
	if (0 == old_level && specialud > 0)
	{
		//优先使用洗髓真丹
		if (0 == logicEquipment.UseEquipment(uid, HERO_POWER_2_UP_AWAKEN, specialud, 1, "heropower2up"))
		{
			used -= HERO_POWER_2_UP_COST[old_level][0];
		}
	}

	//限级洗髓丹5-7阶
	if (used > 0 && equd1 > 0 && (old_level >= 41 && old_level <= 70))
	{
		Json::Value dataEquip;
		int equips = 0;

		if (0 == logicEquipment.Get(uid, equd1, dataEquip))
		{
			equips = dataEquip["count"].asInt();
		}

		if (equips > 0)
		{
			int minVal = min(equips, used);

			if (0 == logicEquipment.UseEquipment(uid, HERO_POWER_2_UP_LIMIT, equd1, minVal, "heropower2up"))
			{
				result["used_limit_1"] = minVal;
				used -= minVal;
			}
		}
	}

	//洗髓丹5-9阶
	if (used > 0 && equd2 > 0 && (old_level >= 41 && old_level <= 90))
	{
		Json::Value dataEquip;
		int equips = 0;

		if (0 == logicEquipment.Get(uid, equd2, dataEquip))
		{
			equips = dataEquip["count"].asInt();
		}

		if (equips > 0)
		{
			int minVal = min(equips, used);

			if (0 == logicEquipment.UseEquipment(uid, HERO_POWER_2_UP_LIMIT_2, equd2, minVal, "heropower2up"))
			{
				result["used_limit_2"] = minVal;
				used -= minVal;
			}
		}
	}

	//洗髓丹6阶以上
	if (used > 0 && equd3 > 0 && old_level >= 51)
	{
		Json::Value dataEquip;
		int equips = 0;

		if (0 == logicEquipment.Get(uid, equd3, dataEquip))
		{
			equips = dataEquip["count"].asInt();
		}

		if (equips > 0)
		{
			int minVal = min(equips, used);

			if (0 == logicEquipment.UseEquipment(uid, HERO_POWER_2_UP_LIMIT_3, equd3, minVal, "heropower2up"))
			{
				result["used_limit_3"] = minVal;
				used -= minVal;
			}
		}
	}

	//洗髓丹4阶以上
	if (used > 0 && equd4 > 0 && old_level >= 31)
	{
		Json::Value dataEquip;
		int equips = 0;

		if (0 == logicEquipment.Get(uid, equd4, dataEquip))
		{
			equips = dataEquip["count"].asInt();
		}

		if (equips > 0)
		{
			int minVal = min(equips, used);

			if (0 == logicEquipment.UseEquipment(uid, HERO_POWER_2_UP_LIMIT_4, equd4, minVal, "heropower2up"))
			{
				result["used_limit_4"] = minVal;
				used -= minVal;
			}
		}
	}

	if (used > 0)
	{
		ret = logicEquipment.UseEquipment(uid, HERO_POWER_2_UP, equd, used, "heropower2up");

		if(ret)
			return ret;
	}

	hero["hs"][0u] = level;
	hero["hs"][1u] = exp;

	ret = logicHero.Chg(uid, heroud, hero);

	if(ret)
		return ret;

	HERO_LOG("uid=%u,id=%u,act=HeroPower2Up,data=%s",uid, heroud, Json::ToString(hero).c_str());

	result["hs"] = hero["hs"];
	result["used"] = used;

	ret = logicUser.SetUserLimit(uid, dataUser);
	if(ret)
		return ret;

	return R_SUCCESS;
}

int CLogicCMD::HeroPower3Up(unsigned uid, unsigned heroud, unsigned equd, Json::Value &result, unsigned &lasttime,unsigned &seqid)
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

	Json::Value hero, equip;
	CLogicHero logicHero;
	ret = logicHero.Get(uid, heroud, hero);
	if(ret)
		return ret;

	if(!hero.isMember("hs"))
		hero["hs"][0u] = hero["hs"][1u] = hero["hs"][2u] = hero["hs"][3u] = 0;
	else if(!hero["hs"].isArray() || hero["hs"].size() != 4)
		return R_ERR_DATA;
	unsigned level = hero["hs"][0u].asUInt();
	unsigned a = hero["hs"][2u].asUInt();
	unsigned n = hero["hs"][3u].asUInt();
	if(level == 0 || n >= HERO_POWER_3_UP_MAX[(level - 1) / 10])
		return R_ERR_LOGIC;

	CLogicEquipment logicEquipment;
	ret = logicEquipment.UseEquipment(uid, HERO_POWER_3_UP, equd, 1, "heropower3up");
	if(ret)
		return ret;

	++a;
	++n;
	hero["hs"][2u] = a;
	hero["hs"][3u] = n;

	ret = logicHero.Chg(uid, heroud, hero);
	if(ret)
		return ret;

	result["hs"] = hero["hs"];

	ret = logicUser.SetUserLimit(uid, dataUser);
	if(ret)
		return ret;

	return R_SUCCESS;
}

int CLogicCMD::HeroLearnHorse(unsigned uid, unsigned heroud, unsigned equd1, unsigned equd2, Json::Value &result, unsigned lasttime,unsigned seqid, unsigned once)
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

	Json::Value hero;
	CLogicHero logicHero;
	ret = logicHero.Get(uid, heroud, hero);
	if(ret)
		return ret;

	int hexp = 0;
	Json::GetInt(hero, "hexp", hexp);
	unsigned cost_1 = 0;
	unsigned cost_2 = 0;

	CLogicEquipment logicEquipment;
	Json::Value data_1;
	ret = logicEquipment.Get(uid, equd1,data_1);
	if(ret != 0)
	{
		return ret;
	}
	unsigned count_1 = data_1["count"].asInt();

	Json::Value data_2;
	ret = logicEquipment.Get(uid, equd1,data_2);
	if(ret != 0)
	{
		return ret;
	}
	unsigned count_2 = data_2["count"].asInt();

	if(0 == once)
	{
		hexp += HERO_LEARN_HORSE_HEXP;
		cost_1 = HERO_LEARN_HORSE_EQ_1;
		cost_2 = HERO_LEARN_HORSE_EQ_2;
	}
	else if(1 == once)
	{
		//寻找下级经验
		unsigned next_exp = hexp;
		for(int i = 0; i < sizeof(HORSE_MAX_EXP)/sizeof(HORSE_MAX_EXP[0]); ++i)
		{
			if(HORSE_MAX_EXP[i] > hexp)
			{
				next_exp = HORSE_MAX_EXP[i];
				break;
			}
		}

		while(hexp < next_exp)
		{
			if(HERO_LEARN_HORSE_EQ_1 <= count_1 && HERO_LEARN_HORSE_EQ_2 <= count_2)
			{
				cost_1 += HERO_LEARN_HORSE_EQ_1;
				cost_2 += HERO_LEARN_HORSE_EQ_2;
				count_1 -= HERO_LEARN_HORSE_EQ_1;
				count_2 -= HERO_LEARN_HORSE_EQ_2;
				hexp += HERO_LEARN_HORSE_HEXP;
			}
			else
			{
				break;
			}
		}
	}

	if(hexp > HERO_LEARN_HORSE_MAX)
		hexp = HERO_LEARN_HORSE_MAX;

	ret = logicEquipment.UseEquipment(uid, HERO_LEARN_HORSE_EQID_1, equd1, cost_1, "HeroLearnHorse");
	if(ret)
		return ret;
	ret = logicEquipment.UseEquipment(uid, HERO_LEARN_HORSE_EQID_2, equd2, cost_2, "HeroLearnHorse");
	if(ret)
		return ret;

	hero["hexp"] = hexp;

	ret = logicHero.Chg(uid, heroud, hero);
	if(ret)
		return ret;

	result["hexp"] = hero["hexp"];

	ret = logicUser.SetUserLimit(uid, dataUser);
	if(ret)
		return ret;

	return R_SUCCESS;
}

int CLogicCMD::UpgradeHorse(unsigned uid, unsigned horseud, unsigned equd, unsigned equd_2, Json::Value &result, unsigned lasttime,unsigned seqid)
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

	Json::Value equip;
	CLogicEquipment logicEquipment;
	ret = logicEquipment.Get(uid, horseud, equip);
	if(ret)
		return ret;

	int hexp = 0;
	Json::GetInt(equip, "hexp", hexp);

	if(hexp >= UPGRADE_HORSE_MAX || hexp < 0)
		return R_ERR_LOGIC;

	if (!equip.isMember("ch"))
	{
		equip["ch"] = 1;
	}

	//判断当前等级是否可以继续升级
	if (hexp == equip["ch"].asInt() * 10)
	{
		//当等级数==阶*10时，必须升阶之后才能继续升级
		error_log("degree not enough. uid=%u,horseud=%u", uid, horseud);
		LOGIC_ERROR_RETURN_MSG("degree_not_enough");
	}

	ret = logicEquipment.UseEquipment(uid, UPGRADE_HORSE_EQID, equd, UPGRADE_HORSE_EQ[hexp], "UpgradeHorse");

	if(ret)
		return ret;

	//二阶之后，还需要额外消耗固魂丹
	if (equip["ch"].asInt() > 1)
	{
		//二阶，及以上.消耗数量同凝魂丹一致
		ret = logicEquipment.UseEquipment(uid, SUPER_UPGRADE_HORSE_EQID, equd_2, UPGRADE_2_HORSE_EQ[hexp], "UpgradeHorse");

		if(ret)
			return ret;
	}

	++hexp;
	equip["hexp"] = hexp;

	ret = logicEquipment.Chg(uid, horseud, equip);
	if(ret)
		return ret;

	result["hexp"] = equip["hexp"];

	ret = logicUser.SetUserLimit(uid, dataUser);
	if(ret)
		return ret;

	return R_SUCCESS;
}

int CLogicCMD::ElevateHorse(unsigned uid, unsigned horseud, unsigned equd, Json::Value &result, unsigned lasttime,unsigned seqid)
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

	Json::Value equip;
	CLogicEquipment logicEquipment;
	ret = logicEquipment.Get(uid, horseud, equip);

	if(ret)
		return ret;

	int hexp = 0;
	Json::GetInt(equip, "hexp", hexp);

	if (!equip.isMember("ch"))
	{
		equip["ch"] = 1;
	}

	int ch = equip["ch"].asInt();

	if(hexp < 0 || hexp != (equip["ch"].asUInt() * 10))
	{
		error_log("level not enough. uid=%u,horseud=%u,level=%d", uid, horseud, hexp);
		LOGIC_ERROR_RETURN_MSG("level_not_enough");
	}

	if (ch >= DEGREE_HORESE_MAX)
	{
		error_log("level not enough. uid=%u,horseud=%u,level=%d", uid, horseud, hexp);
		LOGIC_ERROR_RETURN_MSG("degree_already_max");
	}

	//消耗道具
	ret = logicEquipment.UseEquipment(uid, ELEVATE_HORSE_EQID, equd, ELEVATE_HORSE_EQ[ch-1], "ElevateHorse");

	if(ret)
		return ret;

	//提升阶级
	equip["ch"] = ch+1;

	ret = logicEquipment.Chg(uid, horseud, equip);

	if(ret)
		return ret;

	result["ch"] = equip["ch"];

	ret = logicUser.SetUserLimit(uid, dataUser);

	if(ret)
		return ret;

	return R_SUCCESS;
}
