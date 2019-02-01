/*
 * LogicCMD2.cpp
 *
 *  Created on: 2016-11-15
 *      Author: Ralf
 */



#include "LogicCMD.h"
#include "LogicUnitWrap.h"
#include "LogicCmdUnits.h"
#include <math.h>


int CLogicCMD::IntensifyWeaponBySoul(
		  unsigned uid
		, unsigned index
		, Json::Value& result
		, unsigned lasttime
		, unsigned seqid)

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
	if (index >= 10)
	{
		error_log("[IntensifyWeaponBySoul][index_param_error,uid=%u,index=%d]", uid, index);
		PARAM_ERROR_RETURN_MSG("index_param_error");
	}

	Json::Value jsonTech;
	if (! Json::FromString(jsonTech, dataUser.user_tech))
	{
		error_log("[IntensifyWeaponBySoul][get_user_tech_failed,uid=%u]", uid);
		DB_ERROR_RETURN_MSG("get_user_tech_failed");
	}

	Json::Value jsonPart;
	if (! Json::GetArray(jsonTech, "part", jsonPart))
	{
		error_log("[IntensifyWeaponBySoul][parse_tech_part_error,uid=%u]", uid);
		DB_ERROR_RETURN_MSG("parse_tech_part");
	}

	//获取武馆等级
	unsigned buildingLevel = 0;
	if ((ret = GetGeneralBuildingLevel(uid, buildingLevel)) != R_SUCCESS)
	{
		error_log("[IntensifyWeaponBySoul][get_build_type_5_error,uid=%u]", uid);
		DB_ERROR_RETURN_MSG("get_build_type_5 failed");
	}

	unsigned curLevel = jsonPart[index].asInt();
	//不能超过当前武将馆等级，并且小于等于120
	if (curLevel >= XML_WEAPON_SOUL_ITEMS_MAX || curLevel >= buildingLevel)
	{
		error_log("[IntensifyWeaponBySoul][completely_level,uid=%u,buidLv=%d]", uid, buildingLevel);
		LOGIC_ERROR_RETURN_MSG("completely_level");
	}

	int nCost = 0;
	//TODO 计算消耗
	if ((ret = CalcWeaponBySoulCost(uid, curLevel + 1, nCost)) != R_SUCCESS)
	{
		error_log("[IntensifyWeaponBySoul][calc_weapon_soul_cost_error,uid=%u,ret=%d]", uid, ret);
		LOGIC_ERROR_RETURN_MSG("calc_weapon_soul_cost error");
	}

	//---------------------------------------------------
	//器魂消耗
	Json::Value jsonGodE;
	if (! Json::GetObject(jsonTech, "godE", jsonGodE))
	{
		error_log("[IntensifyWeaponBySoul][tech_godE_node_error,uid=%u]", uid);
		DATA_ERROR_RETURN_MSG("tech_godE_node error");
	}

	Json::Value jsonQlE;
	if (! Json::GetArray(jsonGodE, "qlE", jsonQlE))
	{
		error_log("[IntensifyWeaponBySoul][tech_godE_qlE_node_error,uid=%u]", uid);
		DATA_ERROR_RETURN_MSG("tech_godE_qlE_node error");
	}

	int qlEIndex = 0;
	int nQlE = jsonQlE[qlEIndex].asInt();
	if (nQlE < nCost)
	{
		error_log("[IntensifyWeaponBySoul][Soul_not_enough,uid=%u,qlE=%d]", uid, nQlE);
		REFUSE_RETURN_MSG("Soul_not_enough");
	}

	jsonQlE[qlEIndex] = nQlE - nCost;
	jsonTech["godE"]["qlE"] = jsonQlE;

	result["souls"] = nQlE - nCost;
	RESOURCE_LOG("[IntensifyWeaponBySoul][uid=%d,chg_qi_hun=%d,surplus=%d,code=%s]"
									, uid, nCost, nQlE - nCost, "intensify_weapon_op");
	//@end

	//
	jsonPart[index] = curLevel + 1;
	jsonTech["part"] = jsonPart;
	dataUser.user_tech = Json::ToString(jsonTech);

	if ((ret = logicUser.SetUser(uid, dataUser)) != 0)
	{
		error_log("get_daily_quest_reward add experience failed. uid=%d,ret=%d", uid,ret);
		return ret;
	}

	return R_SUCCESS;
}

int CLogicCMD::IntensifyWeaponBySoul(
		  unsigned uid
		, unsigned index
		, unsigned equipUd1 //限时武魂凝露
		, unsigned equipUd2  //武魂凝露
		, unsigned equipUd3  //限级武魂
		, unsigned equipUd4  //限级武魂2
		, Json::Value& result
		, unsigned lasttime
		, unsigned seqid)

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
	if (index >= 10)
	{
		PARAM_ERROR_RETURN_MSG("index_param_error");
	}

	Json::Value jsonTech;
	if (! Json::FromString(jsonTech, dataUser.user_tech))
	{
		error_log("[IntensifyWeaponBySoul][get_user_tech_failed,uid=%u]", uid);
		DB_ERROR_RETURN_MSG("get_user_tech_failed");
	}

	Json::Value jsonPart;
	if (! Json::GetArray(jsonTech, "part", jsonPart))
	{
		error_log("[IntensifyWeaponBySoul][parse_tech_part_error,uid=%u]", uid);
		DB_ERROR_RETURN_MSG("parse_tech_part");
	}

	//获取武馆等级
	unsigned buildingLevel = 0;
	if ((ret = GetGeneralBuildingLevel(uid, buildingLevel)) != R_SUCCESS)
	{
		error_log("[IntensifyWeaponBySoul][get_build_type_5_error,uid=%u]", uid);
		DB_ERROR_RETURN_MSG("get_build_type_5 failed");
	}

	unsigned curLevel = jsonPart[index].asInt();
	//不能超过当前武将馆等级，并且小于等于120
	if (curLevel >= XML_WEAPON_SOUL_ITEMS_MAX || curLevel >= buildingLevel)
	{
		error_log("[IntensifyWeaponBySoul][completely_level,uid=%u,buidLv=%d]", uid, buildingLevel);
		LOGIC_ERROR_RETURN_MSG("completely_level");
	}

	int nCost = 0;
	//TODO 计算消耗
	if ((ret = CalcWeaponBySoulCost(uid, curLevel + 1, nCost)) != R_SUCCESS)
	{
		error_log("[IntensifyWeaponBySoul][calc_weapon_soul_cost_error,uid=%u,ret=%d]", uid, ret);
		LOGIC_ERROR_RETURN_MSG("calc_weapon_soul_cost error");
	}

	//--------------------------------------------------------------------------
	std::string szReason = "IntensifyWeaponBySoul";
	CLogicEquipment loigcEquipment;
	Json::Value dataEquip;
	int  equips = 0;
	//1.消费限时武魂凝露
	if (equipUd1 > 0 && curLevel < 100)
	{
		dataEquip.clear();
		if (0 == loigcEquipment.Get(uid, equipUd1, dataEquip))
		{
			equips = dataEquip["count"].asInt();
		}

		//时间有效
		if (equips > 0)
		{
			int minVal = std::min(equips, nCost);
			nCost -= minVal;
			equips -= minVal;
			if (0 == loigcEquipment.UseEquipment(uid, 15002, equipUd1, minVal, szReason))
			{
				//命名是二次修改导致
				result["equipUd2"] = equipUd1;
				result["equipCnt2"] = equips;
			}
		}
	}

	//2.限级武魂
	if (equipUd3 > 0  && nCost > 0 && curLevel > 50 && curLevel <= 70)
	{
		dataEquip.clear();
		if (0 == loigcEquipment.Get(uid, equipUd3, dataEquip))
		{
			equips = dataEquip["count"].asInt();
		}

		//
		if (equips > 0)
		{
			int minVal = std::min(equips, nCost);
			nCost -= minVal;
			equips -= minVal;
			if (0 == loigcEquipment.UseEquipment(uid, 15011, equipUd3, minVal, szReason))
			{
				result["equipUd3"] = equipUd3;
				result["equipCnt3"] = equips;
			}
		}
	}

	//3.限级武魂2
	if (equipUd4 > 0  && nCost > 0 && curLevel > 50 && curLevel <= 80)
	{
		dataEquip.clear();
		if (0 == loigcEquipment.Get(uid, equipUd4, dataEquip))
		{
			equips = dataEquip["count"].asInt();
		}

		//
		if (equips > 0)
		{
			int minVal = std::min(equips, nCost);
			nCost -= minVal;
			equips -= minVal;

			if (0 == loigcEquipment.UseEquipment(uid, 15012, equipUd4, minVal, szReason))
			{
				result["equipUd4"] = equipUd4;
				result["equipCnt4"] = equips;
			}
		}
	}

	//4.消费武魂凝露
	if (equipUd2 > 0 && nCost > 0  && curLevel < 100)
	{
		equips = 0;
		//消耗钻石 //先扣除武魂凝露
		dataEquip.clear();
		if (0 == loigcEquipment.Get(uid, equipUd2, dataEquip))
		{
			equips = dataEquip["count"].asInt();
		}

		if (equips > 0)
		{
			int minVal = std::min(equips, nCost);
			nCost -= minVal;
			equips -= minVal;
			if (0 == loigcEquipment.UseEquipment(uid, 15001, equipUd2, minVal, szReason))
			{
				//命名是二次修改导致
				result["equipUd"] = equipUd2;
				result["equipCnt"] = equips;
			}
		}
	}

	if (nCost > 0)
	{
		Json::Value user_flag;

		if (! Json::FromString(user_flag, dataUser.user_flag))
		{
			error_log("[IntensifyWeaponBySoul][get_user_flag_error,uid=%u]", uid);
			DATA_ERROR_RETURN_MSG("get_user_flag_error");
		}

		bool bsave = false;
		CLogicPay logicPay;
		DataPay payData;
		ret = logicPay.ProcessOrderForBackend(uid, -nCost, 0, payData, "IntensifyWeaponBySoul_cost_"+CTrans::UTOS(index), user_flag, bsave);
		if(ret != R_SUCCESS)
		{
			DATA_ERROR_RETURN_MSG("cost_diamod_error");
			return ret;
		}

		result["pointpay"].resize(0);
		if(bsave)
		{
			result["pointpay"] = user_flag["user_pay"];
			dataUser.user_flag = Json::ToString(user_flag);
		}

		result["coins"] = payData.coins;
		result["diamond"] = payData.cash;
		//@end
	}

	//
	jsonPart[index] = curLevel + 1;
	jsonTech["part"] = jsonPart;
	dataUser.user_tech = Json::ToString(jsonTech);

	if ((ret = logicUser.SetUser(uid, dataUser)) != 0)
	{
		error_log("get_daily_quest_reward add experience failed. uid=%d,ret=%d", uid,ret);
		return ret;
	}

	return R_SUCCESS;
}
int CLogicCMD::GetPartStone(unsigned uid, Json::Value& result, unsigned lasttime, unsigned seqid)
{
	const int GetPartStoneConfigNum = 57;
	const int GetPartStoneConfig[GetPartStoneConfigNum][2] = {
			{5,25},
			{10,25},
			{15,30},
			{20,30},
			{25,35},
			{30,35},
			{35,40},
			{40,40},
			{41,45},
			{42,45},
			{43,45},
			{44,45},
			{45,45},
			{46,45},
			{47,45},
			{48,45},
			{49,45},
			{50,45},
			{52,50},
			{54,50},
			{56,50},
			{58,50},
			{60,50},
			{62,50},
			{64,50},
			{66,50},
			{68,50},
			{70,50},
			{71,55},
			{72,55},
			{73,55},
			{74,55},
			{75,55},
			{76,60},
			{77,60},
			{78,60},
			{79,60},
			{80,60},
			{81,65},
			{82,65},
			{83,65},
			{84,65},
			{85,65},
			{86,70},
			{87,70},
			{88,70},
			{89,70},
			{90,70},
			{91,70},
			{92,70},
			{93,70},
			{94,70},
			{95,70},
			{96,70},
			{97,70},
			{98,70},
			{99,70}
	};

	if(Time::GetGlobalTime() < Config::GetIntValue(CONFIG_PART_STONE_BEGIN_TS)
	|| Time::GetGlobalTime() >= Config::GetIntValue(CONFIG_PART_STONE_END_TS))
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
	Json::Value user_tech;
	reader.parse(dataUser.user_tech,user_tech);

	Json::Value newAct;
	CLogicSecinc logicSecinc;
	ret = logicSecinc.GetSecinc(uid, NAT_PART_STONE, newAct);
	if (ret == R_ERR_NO_DATA)
	{
		newAct["id"] = NAT_PART_STONE;
		newAct["p"].resize(0);
		for(unsigned i=0;i<10;++i)
			newAct["p"].append(0);

	}
	else if(ret)
		return ret;

	int p[10], count = 0, pm = 100, t = -1;
	for(unsigned i=0;i<10;++i)
	{
		p[i] = newAct["p"][i].asInt();
		if(p[i] < pm)
			pm = p[i];
	}
	for(unsigned i=0;i<GetPartStoneConfigNum;++i)
	{
		if(pm < GetPartStoneConfig[i][0])
		{
			t = i;
			break;
		}
	}
	if(t == -1)
		return R_ERR_LOGIC;

	CDataXML *dataXML = CDataXML::GetCDataXML();
	if(!dataXML)
	{
		error_log("GetInitXML fail");
		return R_ERR_DB;
	}
	for(unsigned i=0;i<10;++i)
	{
		if(p[i] < GetPartStoneConfig[t][0])
		{
			for(unsigned j=p[i]+1;j<=GetPartStoneConfig[t][0];++j)
			{
				XMLWeaponSoulCostItem item;
				ret = dataXML->GetWeaponSoulCostItem(j, item);
				if(ret)
					return ret;
				count += item.cost;
			}
		}
	}

	count = count * GetPartStoneConfig[t][1] / 100;
	newAct["p"] = user_tech["part"];

	ret = logicSecinc.SetOneSecinc(uid, newAct);
	if(ret)
		return ret;
	result["newAct"] = newAct;

	CLogicEquipment loigcEquipment;
	ret = loigcEquipment.AddOneItem(uid, 15002, count, "GetPartStone",result["equip"], true, 0, 0, Config::GetIntValue(CONFIG_PART_STONE_END_TS)-Time::GetGlobalTime());
	if(ret)
		return ret;

	ret = logicUser.SetUserLimit(uid, dataUser);
	if(ret)
		return ret;

	return R_SUCCESS;
}

int CLogicCMD::GetGeneralBuildingLevel(unsigned uid, unsigned& level)
{
	Json::Value jsonBd;
	CLogicBuilding logicBd;
	int ret = logicBd.Get(uid, 5, 0,true, jsonBd);
	if (ret != 0)
	{
		//DB_ERROR_RETURN_MSG("get_build_type_5 failed");
		error_log("get_build_type_5 failed. uid=%u", uid);
		return R_ERROR;
	}

	if (! Json::GetUInt(jsonBd, "l", level))
	{
		error_log("get_build_type_5 node l failed. uid=%u", uid);
		return R_ERROR;
	}

	return R_SUCCESS;
}

int CLogicCMD::CalcWeaponBySoulCost(unsigned uid, unsigned level, int& cost)
{
	CDataXML *dataxml = CDataXML::GetCDataXML();
	if (NULL == dataxml)
	{
		error_log("get dataXML error uid=%d", uid);
		return R_ERROR;
	}

	int ret = 0;
	XMLWeaponSoulCostItem item;
	if (( ret = dataxml->GetWeaponSoulCostItem(level, item)) != R_SUCCESS)
	{
		error_log("get_weapon_soul_cost_item failed uid=%d,ret=%d", uid, ret);
		return ret;
	}

	//TODO 计算折扣 武魂折扣活动 被屏蔽了  没有处理

	cost  = item.cost;

	return R_SUCCESS;
}

int CLogicCMD::PreSummerExchange(unsigned uid, unsigned id, unsigned type,
		Json::Value& result, unsigned lasttime, unsigned seqid)
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

		PreSummerUnit preSummerUnit(uid, type);
		preSummerUnit.Exchange(userWrap, id, result);

		userWrap.Save();
	}
	catch (const std::exception& e)
	{
		error_log("%s", e.what());
		::SetError(R_ERROR, e.what());
		return R_ERROR;
	}

	return R_SUCCESS;
}

int CLogicCMD::PreSummerCurPoint(unsigned uid, unsigned type, Json::Value& result
		, unsigned lasttime	, unsigned seqid)
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

		PreSummerUnit preSummerUnit(uid, type);
		preSummerUnit.GetData(userWrap, result);

		userWrap.Save();
	}
	catch (const std::exception& e)
	{
		error_log("%s", e.what());
		::SetError(R_ERROR, e.what());
		return R_ERROR;
	}

	return R_SUCCESS;
}

int CLogicCMD::LordWorship(unsigned uid, int id, int type, Json::Value &result, unsigned lasttime, unsigned seqid)
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

		LordUnit lordUnit(uid);
		lordUnit.Worship(id, type, result["result"]);

		userWrap.Save();
	}
	catch (const std::exception& e)
	{
		error_log("%s", e.what());
		::SetError(R_ERROR, e.what());
		return R_ERROR;
	}

	return R_SUCCESS;
}

int CLogicCMD::GroupBuyDailyBuy(unsigned uid, Json::Value &result, unsigned lasttime, unsigned seqid)
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

		GroupBuyDailyUnit groupBuyDaily(uid, userWrap);
		groupBuyDaily.BuyAction(userWrap, result);

		userWrap.Save();
	}
	catch (const std::exception& e)
	{
		error_log("%s", e.what());
		::SetError(R_ERROR, e.what());
		return R_ERROR;
	}

	return R_SUCCESS;
}

int CLogicCMD::GroupBuyDailyReward(unsigned uid, int index, Json::Value &result, unsigned lasttime, unsigned seqid)
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

		GroupBuyDailyUnit groupBuyDaily(uid, userWrap);
		groupBuyDaily.GetRewardAction(index, userWrap, result);

		userWrap.Save();
	}
	catch (const std::exception& e)
	{
		error_log("%s", e.what());
		::SetError(R_ERROR, e.what());
		return R_ERROR;
	}

	return R_SUCCESS;
}

int CLogicCMD::NewRecharge(unsigned uid, int id, Json::Value &result, unsigned lasttime, unsigned seqid)
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

		NewRechargeUnit newrechargeUnit(uid);
		newrechargeUnit.GetRewardBagAction(userWrap, id, result);

		userWrap.Save();
	}
	catch (const std::exception& e)
	{
		error_log("%s", e.what());
		::SetError(R_ERROR, e.what());
		return R_ERROR;
	}

	return R_SUCCESS;
}

int CLogicCMD::LittleRecharge(unsigned uid, Json::Value &result, unsigned lasttime, unsigned seqid)
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

		LittleRechargeUnit littleRecharge(userWrap);
		littleRecharge.GetReward(userWrap, result);

		userWrap.Save();
	}
	catch (const std::exception& e)
	{
		error_log("%s", e.what());
		::SetError(R_ERROR, e.what());
		return R_ERROR;
	}

	return R_SUCCESS;
}

int CLogicCMD::RecruitHero(unsigned uid, string heroid, Json::Value& result, unsigned zmlud, int index, unsigned lasttime, unsigned seqid)
{
	int ret = 0;

	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	ret = logicUser.GetUser(uid, dataUser);

	if(ret)
	{
		error_log(" get_user_info_failed,uid = %u",uid);
		return ret;
	}

	if ((ret = checkLastSaveUID(dataUser)) != R_SUCCESS)
	{
		return ret;
	}

	if ((ret = checkLastSaveTime(dataUser, lasttime, seqid)) != R_SUCCESS)
	{
		return ret;
	}

	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	//校验英雄是否存在于刷新的列表中
	if (index <= 0 || index > 3)
	{
		error_log("[RecruitHero][index_param_error, uid=%u]", uid);
		DB_ERROR_RETURN_MSG("index_param_error");
	}

	Json::Value stats;
	Json::Reader reader;

	reader.parse(dataUser.user_stat, stats);

	if (!stats.isMember("chh") || (!stats["chh"].isArray()) )
	{
		error_log("[RecruitHero][userstat_chh_error, uid=%u]", uid);
		DB_ERROR_RETURN_MSG("userstat_chh_error");
	}

	string strhero;

	string strval = stats["chh"][index - 1].asString();

	if (strval.size() < 4)
	{
		error_log("[RecruitHero][userstat_chh_index_value_error, uid=%u, index=%d]", uid, index);
		DB_ERROR_RETURN_MSG("userstat_chh_index_value_error");
	}

	strhero = strval.substr(0, strval.size() - 4);

	if (strhero != heroid)
	{
		error_log("[RecruitHero][heroid_index_not_match, uid=%u, heroid=%s, index=%d]", uid, heroid.c_str(), index);
		PARAM_ERROR_RETURN_MSG("heroid_index_not_match error");
	}

	//校验招贤令个数是否足够
    CLogicEquipment equipment;
    Json::Value zhaoMuLing;

    equipment.Get(uid, zmlud, zhaoMuLing);

    CDataXML *pDataXML = CDataXML::GetCDataXML();

    if(!pDataXML)
    {
    	error_log("[RecruitHero][GetCDataXML failed, uid=%u]", uid);
    	return R_ERR_DATA;
    }

    XMLHero hero;
    string strhid = heroid.substr(1, heroid.size() - 1);
    int hid = CTrans::STOI(strhid.c_str());

    ret = pDataXML->GetHero(hid, hero);

    if(ret)
    {
    	error_log("GetHero fail uid=%u, heroid=%d", uid, hid);
    	return R_ERR_DATA;
    }

    if (zhaoMuLing["count"].asUInt() < hero.hirecost)
    {
		error_log("[RecruitHero][zhaomuling_not_enough, uid=%u, heroid=%s]", uid, heroid.c_str());
		LOGIC_ERROR_RETURN_MSG("zhaomuling_not_enough");
    }

	//扣除招贤令
	ret = equipment.UseEquipment(uid, ZHAO_MU_LING, zmlud, hero.hirecost, "RECRUIT_HERO");

	if(ret != 0)
	{
		error_log("[RecruitHero][UseEquipment fail, uid=%u, heroid=%s]", uid, heroid.c_str());
		return ret;
	}

	result["count"] = zhaoMuLing["count"].asUInt() - hero.hirecost;

	//充值送星级活动
	try
	{
		unsigned time_now = Time::GetGlobalTime();

		if (HeroUpgrideUnit::IsActiving(time_now))  //在活动时间范围内
		{
			HeroUpgrideUnit  herounit(uid);
			herounit.UpdateZMLUsed(hero.hirecost);
		}
	}
	catch(const std::exception& e)
	{
		error_log("[RecruitHero] %s, uid=%u", e.what(), uid);
	}

    //满足条件，开始进行招募结算
	CLogicHero logicHero;

	ret = logicHero.AddOneHero(uid, heroid, "RECRUIT_HERO", result["hero"]);

	if (ret)
	{
		error_log("[RecruitHero][AddOneHero fail, uid=%u, heroid=%s]", uid, heroid.c_str());
		return ret;
	}

	//更改user_stat中的英雄数据
	stats["chh"][index - 1] = "H0,0,0";

	//更新用户信息
	Json::FastWriter writer;
	dataUser.user_stat = writer.write(stats);

	if ((ret = logicUser.SetUser(uid, dataUser)) != 0)
	{
		error_log("[RecruitHero]SetUser failed. uid=%d, ret=%d", uid, ret);
		return ret;
	}

	return R_SUCCESS;
}


int CLogicCMD::QQPanelGiftBag(unsigned uid, Json::Value& result, unsigned lasttime, unsigned seqid)
{
	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	int ret = logicUser.GetUser(uid,dataUser);
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

	//1.取dataUser里的user_stat里的QY， 没有的话，给玩家添加QY=0
	Json::Value stats;
	Json::Reader reader;
	reader.parse(dataUser.user_stat,stats);
	if (!stats.isMember("QY"))
	{
		stats["QY"] = 0;
	}
	unsigned qy = 1;
	Json::GetUInt(stats,"QY",qy);

	//2.如果QY==1时，代表已经领取了， 直接返回
	if (qy)
	{
		error_log("only can get qqpanel gift once,uid = %u",uid);
		return R_ERR_LOGIC;
	}

	//3.将QY置为1，然后给玩家发装备
	stats["QY"] = 1;
	result["QY"] = 1;
	CLogicEquipment logicEquipment;
	vector<ItemAdd> items;
	for (int ix = 0; ix != QQPANEL_ADD_EQUIP_KINDS; ++ix)
	{
		ItemAdd temp;
		temp.eqid = QQPANEL_ADD_EQUIP_ID[ix];
		temp.count = QQPANEL_ADD_EQUIP_COUNT[ix];
		temp.reason = "QQyy";
		items.push_back(temp);
	}
	if(items.size())
		ret = logicEquipment.AddItems(uid,items,result["equip"], true);
	if(ret)
		return ret;

	Json::FastWriter writer;
	dataUser.user_stat = writer.write(stats);
	ret = logicUser.SetUser(uid, dataUser);
	if (ret)
		return ret;

	return R_SUCCESS;
}


int CLogicCMD::YellowDiamondNewUserGiftBag(unsigned uid, Json::Value& result, unsigned lasttime, unsigned seqid)
{
	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	int ret = logicUser.GetUser(uid,dataUser);
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

	//说明：因为奖励很普通，所以黄钻用户检测 交由前端去做，后端不再二次检测
	//1.取dataUser里的user_stat里的vnr， 没有的话，给玩家添加vnr=0
	Json::Value stats;
	Json::Reader reader;
	reader.parse(dataUser.user_stat,stats);
	if (!stats.isMember("vnr"))
	{
		stats["vnr"] = 0;
	}
	unsigned vnr = 1;
	Json::GetUInt(stats,"vnr",vnr);

	//2.如果vnr==1时，代表已经领取了， 直接返回
	if (vnr)
	{
		error_log("only can get yellow_diamond_new_user_gift once,uid = %u",uid);
		return R_ERR_LOGIC;
	}

	//3.将vnr置为1，然后给玩家发装备
	stats["vnr"] = 1;
	result["vnr"] = 1;
	CLogicEquipment logicEquipment;
	vector<ItemAdd> items;
	for (int ix = 0; ix != YELLOW_DIAMOND_NEWUSER_EQUIP_KINDS; ++ix)
	{
		ItemAdd temp;
		temp.eqid = YELLOW_DIAMOND_NEWUSER_ADD_EQUIP_ID[ix];
		temp.count = YELLOW_DIAMOND_NEWUSER_ADD_EQUIP_COUNT[ix];
		temp.reason = "txvip_tutor";
		items.push_back(temp);
	}
	if(items.size())
		ret = logicEquipment.AddItems(uid,items,result["equip"], true);
	if(ret)
		return ret;

	Json::FastWriter writer;
	dataUser.user_stat = writer.write(stats);
	ret = logicUser.SetUser(uid, dataUser);
	if (ret)
		return ret;

	return R_SUCCESS;
}

int CLogicCMD::YellowDiamondDailyGiftBag(unsigned uid, unsigned yellow_level, bool is_year, Json::Value& result, unsigned lasttime, unsigned seqid)
{
	if (yellow_level < 1 || yellow_level > 9 || is_year > 1)
	{
		error_log("para error: yellow_level or is_year");
		return R_ERR_PARAM;
	}

	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	int ret = logicUser.GetUser(uid,dataUser);
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

	Json::Value stats;
	Json::Reader reader;
	reader.parse(dataUser.user_stat,stats);
	if (!stats.isMember("vdrt"))
	{
		stats["vdrt"] = 0;
	}
	if (Time::IsToday(stats["vdrt"].asUInt()))
	{
		error_log("one day only can get YellowDiamondDailyGiftBag once,uid = %u",uid);
		return R_ERR_LOGIC;
	}
	stats["vdrt"] = Time::GetGlobalTime();
	result["vdrt"] = Time::GetGlobalTime();

	CLogicEquipment logicEquipment;
	vector<ItemAdd> items;
	ItemAdd temp;
	temp.eqid = 4015;
	temp.count = yellow_level;
	temp.reason = "txvip_daily";
	items.push_back(temp);

	if (is_year)
	{
		temp.eqid = 4004;
		temp.count = 1;
		temp.reason = "txvip_daily";
		items.push_back(temp);
	}

	if(items.size())
		ret = logicEquipment.AddItems(uid,items,result["equip"], true);
	if(ret)
		return ret;

	Json::FastWriter writer;
	dataUser.user_stat = writer.write(stats);
	ret = logicUser.SetUser(uid, dataUser);
	if (ret)
		return ret;

	return R_SUCCESS;
}


int CLogicCMD::BlueDiamondNewUserGiftBag(unsigned uid, Json::Value& result, unsigned lasttime, unsigned seqid)
{
	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	int ret = logicUser.GetUser(uid,dataUser);
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

	//1.取dataUser里的user_stat里的bnr， 没有的话，给玩家添加bnr=0
	Json::Value stats;
	Json::Reader reader;
	reader.parse(dataUser.user_stat,stats);
	if (!stats.isMember("bnr"))
	{
		stats["bnr"] = 0;
	}
	unsigned bnr = 1;
	Json::GetUInt(stats,"bnr",bnr);

	//2.如果bnr==1时，代表已经领取了， 直接返回
	if (bnr)
	{
		error_log("only can get blue_diamond_new_user_gift once,uid = %u",uid);
		return R_ERR_LOGIC;
	}

	//3.将bnr置为1，然后给玩家发装备
	stats["bnr"] = 1;
	result["bnr"] = 1;
	CLogicEquipment logicEquipment;
	vector<ItemAdd> items;
	for (int ix = 0; ix != BLUE_DIAMOND_NEWUSER_EQUIP_KINDS; ++ix)
	{
		ItemAdd temp;
		temp.eqid = BLUE_DIAMOND_NEWUSER_ADD_EQUIP_ID[ix];
		temp.count = BLUE_DIAMOND_NEWUSER_ADD_EQUIP_COUNT[ix];
		temp.reason = "blue_new";
		items.push_back(temp);
	}
	if(items.size())
		ret = logicEquipment.AddItems(uid,items,result["equip"], true);
	if(ret)
		return ret;

	Json::FastWriter writer;
	dataUser.user_stat = writer.write(stats);
	ret = logicUser.SetUser(uid, dataUser);
	if (ret)
		return ret;

	return R_SUCCESS;
}


bool CLogicCMD::AidForBlueDiamondDailyGiftBag(const string& str_gift_get, Json::Value& stats, Json::Value& result)
{
	if (!stats.isMember(str_gift_get.c_str()))
		stats[str_gift_get.c_str()] = 0;
	if (Time::IsToday(stats[str_gift_get.c_str()].asUInt()))
		return false;
	stats[str_gift_get.c_str()] = Time::GetGlobalTime();
	result[str_gift_get.c_str()] = Time::GetGlobalTime();
	return true;
}


int CLogicCMD::BlueDiamondDailyGiftBagSingle(unsigned uid, unsigned blue_level, bool is_year, bool is_luxury, unsigned kinds_blue_gift, Json::Value& result, unsigned lasttime, unsigned seqid)
{
	if (blue_level < 1 || blue_level > 7 || kinds_blue_gift > 2)
	{
		error_log("para value error: blue_level or kinds_blue_gift");
		return R_ERR_PARAM;
	}
	if ((1==kinds_blue_gift) && !is_luxury)
	{
		error_log("para logic error: get blue luxury gift must be luxury user, uid=%u", uid);
		return R_ERR_LOGIC;
	}
	if ((2==kinds_blue_gift) && !is_year)
	{
		error_log("para logic error: get blue year gift must be year user, uid=%u", uid);
		return R_ERR_LOGIC;
	}

	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	int ret = logicUser.GetUser(uid,dataUser);
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

	//是否可以领取
	Json::Value stats;
	Json::Reader reader;
	reader.parse(dataUser.user_stat,stats);
	string str_gift_get = "bdrt";
	if (kinds_blue_gift)
	{
		str_gift_get = (1==kinds_blue_gift)?"lbdrt":"ybdrt";
	}
	if (!AidForBlueDiamondDailyGiftBag(str_gift_get, stats, result))
	{
		error_log("one day only can get BlueDiamondDailyGiftBagSingle once,uid = %u",uid);
		return R_ERR_LOGIC;
	}

	//发装备
	CLogicEquipment logicEquipment;
	vector<ItemAdd> items;
	ItemAdd temp;
	if (0 == kinds_blue_gift)       //0:普通每日礼包
	{
		temp.eqid = 4015;
		temp.count = BLUE_DIAMOND_DAILY_4015_GIFT_COUNT[blue_level-1];
		temp.reason = "blue_daily";
		items.push_back(temp);
		temp.eqid = 50040;
		temp.count = BLUE_DIAMOND_DAILY_50040_GIFT_COUNT[blue_level-1];
		temp.reason = "blue_daily";
		items.push_back(temp);
	} else if (1 == kinds_blue_gift) //1:豪华礼包
	{
		temp.eqid = 4015;
		temp.count = 2;
		temp.reason = "blue_luxury_daily";
		items.push_back(temp);
	}else 							//2:年费礼包
	{
		temp.eqid = 4015;
		temp.count = 2;
		temp.reason = "blue_year_daily";
		items.push_back(temp);
	}

	if(items.size())
		ret = logicEquipment.AddItems(uid,items,result["equip"], true);
	if(ret)
		return ret;

	Json::FastWriter writer;
	dataUser.user_stat = writer.write(stats);
	ret = logicUser.SetUser(uid, dataUser);
	if (ret)
		return ret;

	return R_SUCCESS;
}


int CLogicCMD::BlueDiamondDailyGiftBagOneKeyBackAll(unsigned uid, unsigned blue_level, bool is_year, bool is_luxury, Json::Value& result, unsigned lasttime, unsigned seqid)
{
	if (blue_level < 1 || blue_level > 7)
	{
		error_log("para value error: blue_level");
		return R_ERR_PARAM;
	}

	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	int ret = logicUser.GetUser(uid,dataUser);
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

	//判断能够一键领取的 礼包种类
	Json::Value stats;
	Json::Reader reader;
	reader.parse(dataUser.user_stat,stats);
	string str_gift_get = "bdrt";
	bool can_get_bdrt = false, can_get_lbdrt = false, can_get_ybdrt = false;
	can_get_bdrt = AidForBlueDiamondDailyGiftBag(str_gift_get, stats, result);
	if (is_luxury)
	{
		str_gift_get = "lbdrt";
		can_get_lbdrt = AidForBlueDiamondDailyGiftBag(str_gift_get, stats, result);
	}
	if (is_year)
	{
		str_gift_get = "ybdrt";
		can_get_ybdrt = AidForBlueDiamondDailyGiftBag(str_gift_get, stats, result);
	}

	//发装备
	CLogicEquipment logicEquipment;
	vector<ItemAdd> items;
	ItemAdd temp;
	if (can_get_bdrt)
	{
		temp.eqid = 4015;
		temp.count = BLUE_DIAMOND_DAILY_4015_GIFT_COUNT[blue_level-1];
		temp.reason = "blue_daily";
		items.push_back(temp);
		temp.eqid = 50040;
		temp.count = BLUE_DIAMOND_DAILY_50040_GIFT_COUNT[blue_level-1];
		temp.reason = "blue_daily";
		items.push_back(temp);
	}
	if (can_get_lbdrt)
	{
		temp.eqid = 4015;
		temp.count = 2;
		temp.reason = "blue_luxury_daily";
		items.push_back(temp);
	}
	if (can_get_ybdrt)
	{
		temp.eqid = 4015;
		temp.count = 2;
		temp.reason = "blue_year_daily";
		items.push_back(temp);
	}

	if(items.size())
		ret = logicEquipment.AddItems(uid,items,result["equip"], true);
	if(ret)
		return ret;

	Json::FastWriter writer;
	dataUser.user_stat = writer.write(stats);
	ret = logicUser.SetUser(uid, dataUser);
	if (ret)
		return ret;

	return R_SUCCESS;
}


int CLogicCMD::BlueDiamondLevelGiftBag(unsigned uid, Json::Value& result, unsigned lasttime, unsigned seqid)
{
	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	int ret = logicUser.GetUser(uid,dataUser);
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

	//安全检测
	Json::Value stats;
	Json::Reader reader;
	reader.parse(dataUser.user_stat,stats);
	if (!stats.isMember("gbdrt"))
	{
		stats["gbdrt"] = 1;
	}
	if (!stats["gbdrt"].asUInt())
	{
		stats["gbdrt"] = 1;
	}

	unsigned will_get_gift_index = dataUser.level / 10;
	if (0 == will_get_gift_index)
	{
		will_get_gift_index = 1;
	}else if (will_get_gift_index > 10)
	{
		will_get_gift_index = 10;
	}

	unsigned gbdrt = 1;
	Json::GetUInt(stats,"gbdrt",gbdrt);
	if (gbdrt > will_get_gift_index || gbdrt > 10 || gbdrt < 1)
	{
		error_log("have got the gift or gbdrt is illegal,uid = %u",uid);
		return R_ERR_LOGIC;
	}

	//改status
	stats["gbdrt"] = will_get_gift_index + 1;
	result["gbdrt"] = will_get_gift_index + 1;

	//发装备
	CLogicEquipment logicEquipment;
	vector<ItemAdd> items;
	ItemAdd temp;
	temp.eqid = BLUE_DIAMOND_LEVEL_GIFT_ADD_EQUIP_ID[will_get_gift_index-1];
	temp.count = BLUE_DIAMOND_LEVEL_GIFT_ADD_EQUIP_COUNT[will_get_gift_index-1];
	temp.reason = "blue_grow_daily";
	items.push_back(temp);
	if(items.size())
		ret = logicEquipment.AddItems(uid,items,result["equip"], true);
	if(ret)
		return ret;

	Json::FastWriter writer;
	dataUser.user_stat = writer.write(stats);
	ret = logicUser.SetUser(uid, dataUser);
	if (ret)
		return ret;

	return R_SUCCESS;
}

int CLogicCMD::GetCashFromActivity(Json::Value & user_flag, int begints, int endts, unsigned & cash)
{
	if (!user_flag.isMember("chgs") || !user_flag["chgs"].isArray())
	{
		error_log("[GetCashFromActivity] user_flag->chgs not exists or is not array");
		return R_ERR_DATA;
	}

	unsigned cashtemp = 0;

	for (int i = 0; i < user_flag["chgs"].size(); ++i)
	{
		int time = user_flag["chgs"][i][0u].asInt();

		if (time >= begints && time <= endts)   //在开始-结束之内的充值钻数
		{
			cashtemp += user_flag["chgs"][i][1u].asUInt();
		}
	}

	cash = cashtemp;

	return R_SUCCESS;
}

int CLogicCMD::GetNewJueshiWushuang(unsigned uid, unsigned id, Json::Value& result, unsigned lasttime, unsigned seqid)
{
	int now = Time::GetGlobalTime();

	int start_time = 0, end_time = 0;

	start_time = Config::GetIntValue(CONFIG_NEWJUESHIWS_BEGIN_TS);
	end_time = Config::GetIntValue(CONFIG_NEWJUESHIWS_END_TS);

	if(now < start_time || now > end_time )
	{
		error_log("new_jueshiws_activity_time_error");
		return R_ERR_AUTH;
	}

	CLogicUser logicUser;
	DataUser dataUser;

	AUTO_LOCK_USER(uid)

	int ret = logicUser.GetUser(uid, dataUser);   //要调用user_flag

	if(ret)
	{
		error_log("get_user_info_failed,uid = %u", uid);
		return ret;
	}

	ret = checkLastSaveUID(dataUser);

	if(ret)
	{
		return ret;
	}

	ret = checkLastSaveTime(dataUser, lasttime, seqid);

	if(ret)
	{
		return ret;
	}

	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	CDataXML *dataXML = CDataXML::GetCDataXML();

	if(!dataXML)
	{
		error_log("GetCDataXML fail");
		return R_ERR_DB;
	}

	XMLNewJueShiWS jueshiitem;

	unsigned index = 0;

	ret = dataXML->GetNewJueShiWSItem(id, jueshiitem, index);

	if (ret)
	{
		error_log("[GetNewJueshiWushuang] get new_jue_shi_ws_item failed!, uid=%u, id=%u", uid, id);
		return ret;
	}

	Json::Value newAct;
	CLogicSecinc logicSecinc;
	ret = logicSecinc.GetSecinc(uid, NAT_NEW_JUESHIWS, newAct);

	int version = Config::GetIntValue(CONFIG_NEWJUESHIWS_VER);

	if (R_ERR_NO_DATA == ret)
	{
		Json::Value array(Json::arrayValue);

		for (int i = 0; i < MAX_HERO_NUM; i++)
		{
			array.append(0);
		}

		newAct["id"] = NAT_NEW_JUESHIWS;
		newAct["a"] = array; //兑换英雄的标志位
		newAct["b"] = 0;   //已使用积分
		newAct["v"] = version;  //版本号
		newAct["ts"] = 0;
	} else if (R_SUCCESS != ret)
	{
		return ret;
	}

	//判断是否新版本
	if (newAct["v"].asInt() != version)
	{
		for (int i = 0; i < MAX_HERO_NUM; i++)
		{
			newAct["a"][i] = 0;
		}

		newAct["v"] = version;
		newAct["ts"] = 0;
	}

	//判断指定英雄是否已兑换
	if (newAct["a"][index].asInt())
	{
		error_log("[GetNewJueshiWushuang] get new_jue_shi_ws_hero_already, uid=%u, id=%u", uid, id);
		LOGIC_ERROR_RETURN_MSG("already_get_hero");
	}

	//判断充值的积分是否足够
	Json::Value user_flag;
	Json::Reader reader;

	reader.parse(dataUser.user_flag, user_flag);

	unsigned cash = 0;

	GetCashFromActivity(user_flag, start_time, now, cash);   //获得从活动开始到现在这个时间内，总的充值钻数

	if (cash < newAct["b"].asUInt())
	{
		error_log("[GetNewJueshiWushuang] data error. recharge [%u] is less than expend [%u].", cash, newAct["b"].asUInt());
		return R_ERR_DATA;
	}

	unsigned leftcash = cash - newAct["b"].asUInt();

	if (leftcash < jueshiitem.point )
	{
		error_log("[GetNewJueshiWushuang] condition not enough. uid=%u, point_now=%u, point_should=%u", uid, leftcash, jueshiitem.point);
		LOGIC_ERROR_RETURN_MSG("condition_not_enough");
	}

	if (newAct["b"].asUInt() + jueshiitem.point > 200000)
	{
		error_log("[GetNewJueshiWushuang] condition is enough. uid=%u, point_now=%u, point_should=%u", uid, leftcash, jueshiitem.point);
		LOGIC_ERROR_RETURN_MSG("condition_is_enough");
	}

	if (jueshiitem.isHero)
	{
		//兑换英雄
		CLogicHero logicHero;

		char heroid[20] = {0};
		sprintf(heroid, "H%u", jueshiitem.heroid);

		ret = logicHero.AddOneHero(uid, heroid, "New_Jueshi_Wushuang", result["hero"]);

		if (ret)
		{
			error_log("[GetNewJueshiWushuang][AddOneHero fail, uid=%u, heroid=%s]", uid, heroid);
			return ret;
		}
	}
	else
	{
		std::string op = "New_Jueshi_Wushuang";
		ret = CLogicEquipment().AddOneItem(uid, jueshiitem.heroid, 1,op, result["equipments"], true);
		if (ret)
		{
			error_log("[GetNewJueshiWushuang][AddOneEquipmentItem fail, uid=%u, equip_id=%d]", uid, jueshiitem.heroid);
			return ret;
		}
	}


	newAct["a"][index] = 1;
	newAct["ts"] = now;
	newAct["b"] = jueshiitem.point + newAct["b"].asUInt();

	result["newAct"] = newAct;

	if ((ret = logicSecinc.SetOneSecinc(uid, newAct)) != 0)
	{
		error_log("[GetNewJueshiWushuang] update secinc failed. uid=%u, id = %u, ret=%d", uid, newAct["id"].asUInt(), ret);
		return ret;
	}

	//更新用户
	ret = logicUser.SetUser(uid, dataUser);

	if (ret)
	{
		error_log("[GetNewJueshiWushuang] set user failed. uid=%u", uid);
		return ret;
	}

	return R_SUCCESS;
}

int CLogicCMD::FeedToken(unsigned uid, unsigned equd, Json::Value & data, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	CLogicUser logicUser;
	DataUser dataUser;

	AUTO_LOCK_USER(uid)

	int ret = logicUser.GetUserLimit(uid, dataUser);

	if(ret)
	{
		error_log("get_user_info_failed,uid = %u", uid);
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


	CLogicEquipment logicEquip;
	Json::Value dataTokenEquip;

	ret = logicEquip.Get(uid, equd, dataTokenEquip);

	if (ret)
	{
		return ret;
	}

	unsigned exp = 0;
	//判断令牌是否第一次初始化
	if(!dataTokenEquip.isMember("q"))
	{
		dataTokenEquip["q"] = 0;
	}

	//条件验证
	ret = VerifyCondition(uid, dataTokenEquip, data);

	if (ret)
	{
		return ret;
	}

	if (dataTokenEquip.isMember("lexp"))
	{
		exp = dataTokenEquip["lexp"].asUInt();
	}

	unsigned ch = 1;
	Json::GetUInt(dataTokenEquip, "ch", ch);

	if (ch < 1)
	{
		error_log("wrong character value.uid=%u", uid);
		return R_ERROR;
	}

	unsigned max_exp = TOKEN_CHARACTER_EXP[ch - 1][TOKEN_LEVEL_MAX];

	Json::Value dataEquip;

	for(int i = 0; i < data.size(); ++i)
	{
		//数组内部数据类型还是数组，存储equd,num
		//先根据ud，获取消耗的道具信息
		unsigned ud = data[i][0u].asUInt();
		unsigned num = data[i][1u].asUInt();

		int result = logicEquip.Get(uid, ud, dataEquip);


		if (result)
		{
			return result;
		}

		unsigned id = 0;
		unsigned feededch = 1;

		Json::GetUInt(dataEquip, "id", id);
		Json::GetUInt(dataEquip, "ch", feededch);

		if (id == FEED_TOKEN_DAN)  //提升丹
		{
			//直接计算经验等级
			//增加到等级上限所需的提升丹个数，免得多余消耗
			unsigned exptemp = 0;
			exptemp = exp;
			exp += (num * 30); //每个提升丹，30经验

			if (exp >= max_exp)  //经验达到顶峰
			{
				num = (unsigned)ceil((float)(max_exp - exptemp)/30);
				exp = max_exp;
			}
		}
		else
		{
			unsigned extraExp = 0;

			if (dataEquip.isMember("lexp"))
			{
				extraExp = dataEquip["lexp"].asUInt();
			}

			extraExp += EXTRA_CHARATER_EXP[ feededch - 1];
			exp += extraExp;

			num = 0; //非叠加装备，count在档中存放的是0
		}

		//消耗装备或者道具
		result = logicEquip.UseEquipment(uid, dataEquip["id"].asUInt(), ud, num, "feed_token");

		if (result)
		{
			return result;
		}
	}

	unsigned ql = 0;
	//计算提升之后的等级
	Json::GetUInt(dataTokenEquip, "q", ql);

	unsigned level = ql; //起始值

	for(; level <= TOKEN_LEVEL_MAX; ++level)
	{
		if (exp < TOKEN_CHARACTER_EXP[ch - 1][level])
		{
			break;
		}
	}

	ql = level - 1;

	if (ql == TOKEN_LEVEL_MAX)
	{
		exp = TOKEN_CHARACTER_EXP[ch - 1][TOKEN_LEVEL_MAX];
	}

	dataTokenEquip["q"] = ql;
	dataTokenEquip["lexp"] = exp;

	//更新装备信息
	ret = logicEquip.Chg(uid, equd, dataTokenEquip);

	if(ret)
	{
		return ret;
	}

	result["equip"] = dataTokenEquip;

	//更新用户信息
	ret = logicUser.SetUserLimit(uid, dataUser);

	if(ret)
	{
		error_log("set_user_info_failed,uid = %u", uid);
		return ret;
	}

	return R_SUCCESS;
}

int CLogicCMD::VerifyCondition(unsigned uid, Json::Value & self, Json::Value & others)
{
	if (self["q"].asInt() >= TOKEN_LEVEL_MAX)
	{
		error_log("current equd [%u]'s quality is max.",  self["ud"].asUInt());
		LOGIC_ERROR_RETURN_MSG("qlevel_is_already_max");
	}

	CLogicEquipment logicEquip;
	Json::Value dataEquip;

	unsigned selfch = 1;
	Json::GetUInt(self, "ch", selfch);

	for(int i = 0; i < others.size(); ++i)
	{
		//数组内部数据类型还是数组，存储equd,num
		//先根据ud，获取消耗的道具信息
		unsigned ud = others[i][0u].asUInt();

		int ret = logicEquip.Get(uid, ud, dataEquip);

		if (ret)
		{
			return ret;
		}

		unsigned oterch = 1;
		Json::GetUInt(dataEquip, "ch", oterch);

		if (dataEquip["id"].asUInt() == FEED_TOKEN_DAN)  //提升丹
		{
			continue;
		}
		else if (selfch < oterch)  //先判断品质等级是否存在下对上的关系
		{
			error_log("current eqid[%u]'s character is lower than resource eqid[%u]. not allow feed", self["ud"].asUInt(), ud);
			LOGIC_ERROR_RETURN_MSG("charater_condition_not_fit");
		}
	}

	return R_SUCCESS;
}

int CLogicCMD::GetUsedCashFromActivity(Json::Value & user_flag, int begints, int endts, unsigned & cash)
{
	if (!user_flag.isMember("user_pay") || !user_flag["user_pay"].isArray())
	{
		error_log("[GetUsedCashFromActivity] user_flag->user_pay not exists or is not array");
		return R_ERR_DATA;
	}

	unsigned cashtemp = 0;

	for (unsigned i = 0; i < user_flag["user_pay"].size(); ++i)
	{
		int time = user_flag["user_pay"][i][0u].asInt();

		if (time >= begints && time <= endts)   //在开始-结束之内的充值钻数
		{
			cashtemp += user_flag["user_pay"][i][1u].asUInt();
		}
	}

	cash = cashtemp;

	return R_SUCCESS;
}

int CLogicCMD::GetOpportunityKnockReward(unsigned uid, unsigned times, unsigned equd, Json::Value & data, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	int now = Time::GetGlobalTime();

	int start_time = 0, end_time = 0;

	start_time = Config::GetIntValue(CONFIG_OPPOR_KNOCK_BEGIN_TS);
	end_time = Config::GetIntValue(CONFIG_OPPOR_KNOCK_END_TS);

	if(now < start_time || now > end_time )
	{
		error_log("opportunity_knock_activity_time_error");
		return R_ERR_AUTH;
	}

	CLogicUser logicUser;
	DataUser dataUser;

	AUTO_LOCK_USER(uid)

	int ret = logicUser.GetUser(uid, dataUser);  //要使用user_flag,因此使用GetUser

	if(ret)
	{
		error_log("get_user_info_failed,uid = %u", uid);
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

	//获取newact信息
	//newact,前端负责初始化
	Json::Value newAct;
	CLogicSecinc logicSecinc;
	ret = logicSecinc.GetSecinc(uid, NAT_OPPOR_KNOCK, newAct);

	if (ret)
	{
		error_log("[GetOpportunityKnockReward] get newact failed. id=%u", NAT_OPPOR_KNOCK);
		return ret;
	}

	int version = Config::GetIntValue(CONFIG_OPPOR_KNOCK_VER);

	if (!newAct.isMember("v"))   //版本号不存在，初始化
	{
		newAct["v"] = version;
		newAct["b"] = 0;
	}

	if (newAct["v"].asInt() != version)   //版本号不一致，开始新活动
	{
		newAct["b"] = 0;   //已用积分清空；
		newAct["v"] = version;
	}

	//id, "a":[id,id,id,id],"b":0  --b表示已用积分
	Json::Value user_flag;
	Json::Reader reader;

	reader.parse(dataUser.user_flag, user_flag);

	unsigned points = 0;

	GetUsedCashFromActivity(user_flag, start_time, now, points);

	unsigned excludeNum = 0;

	//是否有额外的积分消耗
	if (data.isObject() && data.isMember("left") && data["left"].isArray())
	{
		excludeNum += data["left"].size();
	}

	if (data.isObject() && data.isMember("right") && data["right"].isArray())
	{
		excludeNum += data["right"].size();
	}

	//优先消耗积分
	//计算当前积分共支出几轮消耗
	unsigned needpoints = 240 + (80)*excludeNum;

	unsigned usedpoints = 0;

	if (newAct.isMember("b"))
	{
		usedpoints = newAct["b"].asUInt();
	}

	unsigned point_times = 0;

	if (points <= usedpoints)
	{
		point_times = 0;
	}
	else
	{
		point_times = (points - usedpoints)/needpoints;
	}

	for(unsigned i = 0; i < times; ++i)
	{
		if ( i < point_times)   //积分转动
		{
			ret = ProvideReward(uid, excludeNum, equd, data, newAct, result, user_flag, true);
		}
		else   //钻石转动
		{
			ret = ProvideReward(uid, excludeNum, equd, data, newAct, result, user_flag, false);
		}

		if (ret)
		{
			return ret;
		}
	}

	result["pointpay"] = user_flag["user_pay"];

	Json::FastWriter writer;
	dataUser.user_flag = writer.write(user_flag);

	//更新用户
	ret = logicUser.SetUser(uid, dataUser);

	if (ret)
	{
		error_log("[GetOpportunityKnockReward] set user failed. uid=%u", uid);
		return ret;
	}

	return R_SUCCESS;
}

int CLogicCMD::ProvideReward(unsigned uid, unsigned excludeNum, unsigned equd, Json::Value & data, Json::Value & newact, Json::Value & result, Json::Value & user_flag, bool isPointPay)
{
	//获得刷新概率的信息
	CDataXML *dataXML = CDataXML::GetCDataXML();

	if(!dataXML)
	{
		error_log("GetCDataXML fail");
		return R_ERR_DB;
	}

	int ret = R_SUCCESS;
	unsigned needpoints = 240 + (80)*excludeNum;
	int * prate = NULL;

	if (!isPointPay)   //积分不足,自动使用钻石
	{
		ret = dataXML->GetTurnRate(TURN_BY_CASH, prate);

		if (ret)
		{
			error_log("[ProvideReward] get cash rate failed!");
			return ret;
		}

		//消耗钻石
		CLogicPay logicPay;
		DataPay   dataPay;

		int cash = -(60+20*excludeNum);

		int coins = 0;

		bool bsave = false;
#ifdef SG_USE_CASH
		ret = logicPay.ProcessOrderForBackend(uid, cash, coins, dataPay, "opportunity_knock", user_flag, bsave);

		if (ret)
		{
			error_log("[ProvideReward] ProcessOrderForBackend failed! uid=%u. ret=%d", uid, ret);
			return ret;
		}

		result["cash"] = dataPay.cash;
#else
		CLogicEquipment equipment;
		ret = equipment.UseEquipment(uid, purple_key, equd, -cash/5, "GetOpportunityKnockReward");
		if(ret)
			return ret;
#endif
	}
	else
	{
		ret = dataXML->GetTurnRate(TURN_BY_POINT, prate);

		if (ret)
		{
			error_log("[ProvideReward] get point rate failed!");
			return ret;
		}


		newact["b"] = newact["b"].asUInt() + needpoints;
	}

	//1，2，3，4，LEFT,RIGHT
	int index = 0;
	//第一次转转盘
	TurnLuckTable(prate, TURN_TABLE_ITEMS_MAX, index);

	vector<ItemAdd>  equip_items;
	bool isNeedRefresh = false;

	//result中的装备信息必须是个数组
	if (!result.isMember("randoms") || !result["randoms"].isArray())
	{
		result.removeMember("randoms");
		Json::Value array(Json::arrayValue);

		result["randoms"] = array;
	}

	Json::Value onerandom(Json::arrayValue);
	onerandom[0u] = index;

	EquipmentRateInfo rewarditem;

	if (index >= 0 && index <= 3)   //转盘转的位置是中间蓝色道具栏
	{
		//根据index，去newact中获取对应的id，然后再去dataxml中获取装备信息
		unsigned id = newact["a"][index].asUInt();
		ret = dataXML->GetOpporKnockRewardById(id, rewarditem);

		if (ret)
		{
			error_log("[ProvideReward] GetOpporKnockRewardById failed! index=%d, id=%u", index, id);
			return ret;
		}

		isNeedRefresh = true;
	}
	else
	{
		//先获得左边奖池的所有装备
		XMLSecondPoolItem seconditems;
		int exclude[3] = {-1, -1, -1};

		if (4 == index) //转盘转到的是左边黄色道具栏
		{
			ret = dataXML->GetSecondPoolItem(POOL_TO_LEFT, seconditems);

			//读取排除的格子的索引
			if (data.isObject() && data.isMember("left") && data["left"].isArray())
			{
				for(unsigned i = 0; i < data["left"].size(); ++i)
				{
					exclude[i] = data["left"][i].asInt();
				}
			}
		}
		else
		{
			ret = dataXML->GetSecondPoolItem(POOL_TO_RIGHT, seconditems);

			//读取排除的格子的索引
			if (data.isObject() && data.isMember("right") && data["right"].isArray())
			{
				for(unsigned i = 0; i < data["right"].size(); ++i)
				{
					exclude[i] = data["right"][i].asInt();
				}
			}
		}

		if (ret)
		{
			error_log("[ProvideReward] GetSecondPoolItem failed! index=%d", index);
			return ret;
		}

		//接下来，要处理内层转动
		map<int, int> mapIndex;    //映射，概率数组与奖池数组的索引映射,key是概率数组的索引，value是奖池数组的索引

		int secondrate[EXTRA_ITEMS_MAX] = {0};   //概率数组
		int sindex = 0;

		for(int i = 0; i < seconditems.itemcount; ++i)
		{
			if (i == exclude[0] || i == exclude[1] || i == exclude[2]) //指定索引被排除
			{
				continue;
			}

			secondrate[sindex] =  seconditems.allitems[i].rate;  //值是奖池索引对应的概率值

			mapIndex.insert(make_pair(sindex, i));
			++sindex;
		}

		//开始第二轮转动
		int target = 0;

		TurnLuckTable(secondrate, sindex, target);


		int secondindex = mapIndex[target]; //第二轮转动中，选中的奖池的索引

		onerandom[1u] = secondindex;

		rewarditem = seconditems.allitems[secondindex];
	}

	//每次转动的随机结果记录
	result["randoms"].append(onerandom);

	//result中的装备信息必须是个数组
	if (!result.isMember("reward") || !result["reward"].isArray())
	{
		result.removeMember("reward");
		Json::Value array(Json::arrayValue);
		result["reward"] = array;
	}

	Json::Value rewardJson;

	//发送装备或者英雄
	if (0 == rewarditem.isHero)   //装备
	{
		CLogicEquipment logicEquip;

		unsigned eqid = rewarditem.eqid;
		unsigned count = rewarditem.count;

		ret = logicEquip.AddOneItem(uid, eqid, count, "opportunity_knock", rewardJson["equip"], true);

		if(ret)
		{
			error_log("[ProvideReward] Add_Equip_error uid=%u， eqid=%u", uid, eqid);
			return R_ERR_DATA;
		}
	}
	else if (1 == rewarditem.isHero)
	{
		CLogicHero logicHero;
		vector<string> vctheroid;
		vector<string> vctcode;

		char heroid[10] = {0};
		sprintf(heroid, "H%u", rewarditem.eqid);

		for(unsigned i = 0; i < rewarditem.count; ++i)
		{
			vctheroid.push_back(heroid);
			vctcode.push_back("opportunity_knock");
		}

		ret = logicHero.AddHeros(uid, vctheroid, vctcode, rewardJson["hero"]);

		if (ret)
		{
			error_log("[ProvideReward][AddHeros fail, uid=%u, heroid=%s]", uid, heroid);
			return ret;
		}
	}
	else
	{
		error_log("[ProvideReward] data error! item 's equip and hero have no data.", index);
		return R_ERR_DATA;
	}

	result["reward"].append(rewardJson);

	CLogicSecinc logicSecinc;

	//如果当前抽中的是蓝色道具栏的物品，则物品还要再刷新一次
	if (isNeedRefresh)
	{
		ret = RefreshNewItems(uid, index, newact);

		if (ret)
		{
			error_log("[ProvideReward] refresh new Items failed.uid=%u", uid);
		}
	}

	//实时更新newact的值
	if ((ret = logicSecinc.SetOneSecinc(uid, newact)) != 0)
	{
		error_log("[ProvideReward] update secinc failed. uid=%u, id = %u, ret=%d", uid, newact["id"].asUInt(), ret);
		return ret;
	}

	//返回每一次的newact.所以类型是个数组
	if (!result.isMember("newactlist") || !result["newactlist"].isArray())
	{
		result.removeMember("newactlist");
		Json::Value array(Json::arrayValue);
		result["newactlist"] = array;
	}

	result["newactlist"].append(newact);

	return R_SUCCESS;
}

int CLogicCMD::RefreshNewItems(unsigned uid, unsigned oldindex, Json::Value &newact)
{
	int ret = R_SUCCESS;
	//获得刷新概率的信息
	CDataXML *dataXML = CDataXML::GetCDataXML();

	if(!dataXML)
	{
		error_log("GetCDataXML fail");
		return R_ERR_DB;
	}

	XMLRefreshPoolItem refreshitem;

	ret = dataXML->GetRefreshPoolItem(refreshitem);

	if (ret)
	{
		error_log("[RefreshNewItems] GetRefreshPoolItem failed. uid=%u", uid);
		return ret;
	}

	//采用和第二次转盘相同的思路
	//定义个概率数组以及map映射
	map<int, int> mapIndex;    //映射，概率数组与刷新奖池数组的id映射,key是概率数组的索引，value是奖池数组元素的id，因为我只需要id值就够了

	int refreshrate[REFRESH_ITEMS_MAX] = {0};   //概率数组
	int index = 0;

	for(int i = 0; i < refreshitem.itemcount; ++i)
	{
		unsigned id = 0;
		unsigned rate = 0;

		id = refreshitem.allitems[i].id;  //奖池索引对应的id值
		rate = refreshitem.allitems[i].rate;  //奖池索引对应的概率值

		if (newact["a"][0u].asUInt() == id || newact["a"][1u].asUInt() == id || newact["a"][2u].asUInt() == id  || newact["a"][3u].asUInt() == id)  //当前已经出现在界面的装备先排除掉
		{
			continue;
		}

		refreshrate[index] =  rate;  //值是奖池索引对应的概率值
		mapIndex.insert(make_pair(index, id));
		++index;
	}

	//随机从奖池中抽取剩下物品，替换当前被抽中的物品
	int target = 0;
	TurnLuckTable(refreshrate, index, target);

	newact["a"][oldindex] = mapIndex[target];

	return R_SUCCESS;
}

int CLogicCMD::TurnLuckTable(int * prates, int len, int & target)
{
	//获得概率总和
	int max = 0, last = 0;

	for(int i = 0 ; i < len; ++i)
	{
		max += prates[i];
	}

	int random = 0;

	//产生随机值
	random = Math::GetRandomInt(max);

	int j = 0;

	for (; j < len; ++j )
	{
		if (random < (last + prates[j]))
		{
			break;
		}

		last += prates[j];
	}

	target = j;

	return R_SUCCESS;
}

int CLogicCMD::GetRechargeOptionalReward(unsigned uid, unsigned rewardcnt,Json::Value & data, Json::Value & result, unsigned lasttime, unsigned seqid)
{
	int now = Time::GetGlobalTime();

	int start_time = 0, end_time = 0;

	start_time = Config::GetIntValue(CONFIG_RECHARGE_OPTIONAL_BEGIN_TS);
	end_time = Config::GetIntValue(CONFIG_RECHARGE_OPTIONAL_END_TS);

	if(now < start_time || now > end_time )
	{
		error_log("[GetRechargeOptionalReward]	recharge_optional_activity_time_error");
		return R_ERR_AUTH;
	}

	try
	{
		AUTO_LOCK_USER(uid);

		UserWrap userWrap(uid, false);

		int ret = userWrap.CheckSession(lasttime, seqid, result);

		if (ret != R_SUCCESS)
		{
			return ret;
		}

		RechargeOptionalUnit rechargeUnit(uid);
		rechargeUnit.GetOptionalReward(userWrap, rewardcnt,data, result);

		userWrap.Save();
	}
	catch (const std::exception& e)
	{
		::SetError(R_ERROR, e.what());
		return R_ERROR;
	}

	return R_SUCCESS;
}

int CLogicCMD::CheckPayOptionVersion(unsigned uid, Json::Value & result, unsigned lasttime, unsigned seqid)
{
	int now = Time::GetGlobalTime();
	int start_time = 0, end_time = 0;

	start_time = Config::GetIntValue(CONFIG_VICKY_PAY_BEGIN_TS);
	end_time = Config::GetIntValue(CONFIG_VICKY_PAY_END_TS);

	if(now < start_time || now > end_time )
	{
		error_log("pay_optional_activity_time_error");
		return R_ERR_AUTH;
	}

	try
	{
		AUTO_LOCK_USER(uid);

		UserWrap userWrap(uid, false);

		int ret = userWrap.CheckSession(lasttime, seqid, result);

		if (ret != R_SUCCESS)
		{
			return ret;
		}

		PayOptionalUnit payunit(uid);
		payunit.CheckVersion(result);

		userWrap.Save();
	}
	catch (const std::exception& e)
	{
		::SetError(R_ERROR, e.what());
		return R_ERROR;
	}

	return R_SUCCESS;
}

int CLogicCMD::GetPayOptionalReward(unsigned uid, unsigned rewardcnt,Json::Value &data, Json::Value & result, unsigned lasttime, unsigned seqid)
{
	int now = Time::GetGlobalTime();
	int start_time = 0, end_time = 0;

	start_time = Config::GetIntValue(CONFIG_VICKY_PAY_BEGIN_TS);
	end_time = Config::GetIntValue(CONFIG_VICKY_PAY_END_TS);

	if(now < start_time || now > end_time )
	{
		error_log("pay_optional_activity_time_error");
		return R_ERR_AUTH;
	}

	try
	{
		AUTO_LOCK_USER(uid);

		UserWrap userWrap(uid, false);

		int ret = userWrap.CheckSession(lasttime, seqid, result);

		if (ret != R_SUCCESS)
		{
			return ret;
		}

		PayOptionalUnit payunit(uid);
		payunit.GetOptionalReward(userWrap, rewardcnt,data, result);

		userWrap.Save();
	}
	catch (const std::exception& e)
	{
		::SetError(R_ERROR, e.what());
		return R_ERROR;
	}

	return R_SUCCESS;
}

int CLogicCMD::UpgradeHeroForRecharge(unsigned uid, unsigned index, unsigned heroud, Json::Value & result, unsigned lasttime, unsigned seqid)
{
	int now = Time::GetGlobalTime();

	int start_time = 0, end_time = 0;

	start_time = Config::GetIntValue(CONFIG_RECHARGE_SEND_UPGRADE_BEGIN_TS);
	end_time = Config::GetIntValue(CONFIG_RECHARGE_SEND_UPGRADE_END_TS);

	if(now < start_time || now > end_time )
	{
		error_log("[UpgradeHeroForRecharge]	recharge_send_upgrade_activity_time_error");
		return R_ERR_AUTH;
	}

	try
	{
		AUTO_LOCK_USER(uid);

		UserWrap userWrap(uid, false);

		int ret = userWrap.CheckSession(lasttime, seqid, result);

		if (ret != R_SUCCESS)
		{
			return ret;
		}

		HeroUpgrideUnit heroUnit(uid);
		heroUnit.UpgrideHeroNew(userWrap, index, heroud, result);

		userWrap.Save();
	}
	catch (const std::exception& e)
	{
		::SetError(R_ERROR, e.what());
		return R_ERROR;
	}

	return R_SUCCESS;
}

int CLogicCMD::StartHeroTrain(unsigned uid, unsigned index, unsigned heroud, unsigned blv, Json::Value & result, unsigned lasttime, unsigned seqid)
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

		HeroTrainUnit herounit(uid);
		herounit.StartTrain(userWrap, heroud, index, blv, result);

		userWrap.Save();
	}
	catch (const std::exception& e)
	{
		::SetError(R_ERROR, e.what());
		return R_ERROR;
	}

	return R_SUCCESS;
}

int CLogicCMD::ImroveHeroTrainExp(unsigned uid, unsigned equd, unsigned tindex, Json::Value & result, unsigned lasttime, unsigned seqid)
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

		HeroTrainUnit herounit(uid);
		herounit.ImproveTrainExp(userWrap, equd, tindex, result);

		userWrap.Save();
	}
	catch (const std::exception& e)
	{
		::SetError(R_ERROR, e.what());
		return R_ERROR;
	}

	return R_SUCCESS;
}

int CLogicCMD::EndHeroTrain(unsigned uid, unsigned type, unsigned tindex, Json::Value & result, unsigned lasttime, unsigned seqid)
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

		HeroTrainUnit herounit(uid);
		herounit.EndTrain(userWrap, type, tindex, result);

		userWrap.Save();
	}
	catch (const std::exception& e)
	{
		::SetError(R_ERROR, e.what());
		return R_ERROR;
	}

	return R_SUCCESS;
}

int CLogicCMD::StartSoldierTrain(unsigned uid, string sid, int count, unsigned type, unsigned costtype, Json::Value & result, unsigned lasttime, unsigned seqid)
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

		SoldierUnit soldierunit(uid);
		soldierunit.StartTrain(userWrap, sid, count, type, costtype, result);

		userWrap.Save();
	}
	catch (const std::exception& e)
	{
		::SetError(R_ERROR, e.what());
		return R_ERROR;
	}

	return R_SUCCESS;
}

int CLogicCMD::EndSoldierTrain(unsigned uid, unsigned type, unsigned bindex, Json::Value & result, unsigned lasttime, unsigned seqid)
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

		SoldierUnit soldierunit(uid);
		soldierunit.EndTrain(userWrap, bindex, type, result);

		userWrap.Save();
	}
	catch (const std::exception& e)
	{
		::SetError(R_ERROR, e.what());
		return R_ERROR;
	}

	return R_SUCCESS;
}

int CLogicCMD::StartSoldierResearch(unsigned uid, string sid, unsigned rlevel, unsigned type, unsigned costtype, Json::Value & result, unsigned lasttime, unsigned seqid)
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

		SoldierUnit soldierunit(uid);
		soldierunit.StartResearch(userWrap, sid, type, rlevel, costtype, result);

		userWrap.Save();
	}
	catch (const std::exception& e)
	{
		::SetError(R_ERROR, e.what());
		return R_ERROR;
	}

	return R_SUCCESS;
}

int CLogicCMD::CancelSoldierResearch(unsigned uid, string sid, Json::Value & result, unsigned lasttime, unsigned seqid)
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

		SoldierUnit soldierunit(uid);
		soldierunit.CancelResearch(userWrap, sid, result);

		userWrap.Save();
	}
	catch (const std::exception& e)
	{
		::SetError(R_ERROR, e.what());
		return R_ERROR;
	}

	return R_SUCCESS;
}

int CLogicCMD::EndSoldierResearch(unsigned uid, string sid, unsigned type, Json::Value & result, unsigned lasttime, unsigned seqid)
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

		SoldierUnit soldierunit(uid);
		soldierunit.EndResearch(userWrap, sid, type, result);

		userWrap.Save();
	}
	catch (const std::exception& e)
	{
		::SetError(R_ERROR, e.what());
		return R_ERROR;
	}

	return R_SUCCESS;
}


int CLogicCMD::SynthSoldierSkill(unsigned uid, unsigned equd, unsigned type, Json::Value & data, Json::Value &result, unsigned lasttime, unsigned seqid, int kind, unsigned expud, unsigned expcount)
{
	string synth_kind = (kind == Soldier ? "Soldier": "KingdomWar");
	if(type != 2 && 1 > data.size())
	{
		error_log("[synth %s] data is null ,uid = %u", synth_kind.c_str(), uid);
		return R_ERR_PARAM;
	}

	CLogicUser 	logicUser;
	DataUser 	dataUser;
	AUTO_LOCK_USER(uid)

	int ret = logicUser.GetUserLimit(uid, dataUser);
	if(ret)
	{
		error_log("[synth %s] get_user_info_failed,uid = %u", synth_kind.c_str(), uid);
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

	CLogicEquipment logicEquip;

	Json::Value dataSynthEquip;

	ret = logicEquip.Get(uid, equd, dataSynthEquip);
	if (ret)
	{
		return ret;
	}

	unsigned synth_exp = 0;
	//判断等级是否初始化
	if(!dataSynthEquip.isMember("q"))
	{
		dataSynthEquip["q"] = 1;
	}

	unsigned synth_level = dataSynthEquip["q"].asInt();
	//宝物已达到最高等级
	if(synth_level >= SOLDIER_SKILL_LEVEL_MAX)
	{
		error_log("[synth %s] current equd [%u]'s quality is max.", synth_kind.c_str(), dataSynthEquip["ud"].asUInt());
		LOGIC_ERROR_RETURN_MSG("qlevel_is_already_max");
	}

	if (dataSynthEquip.isMember("lexp"))
	{
		synth_exp = dataSynthEquip["lexp"].asUInt();
	}

	unsigned synth_ch = 1;
	Json::GetUInt(dataSynthEquip, "ch", synth_ch);

	if (synth_ch < 1)
	{
		error_log("[synth %s] wrong character value.uid=%u", synth_kind.c_str(), uid);
		return R_ERROR;
	}

	Json::Value dataEquip;

	unsigned id = 0;
	unsigned ch	= 1;
	unsigned level = 1;
	unsigned ud = 0;
	unsigned status = 0;
	const unsigned *initial_exp = (kind == Soldier ? INITIAL_CHARATER_EXP : INITIAL_CHARATER_EXP_1);
    const unsigned exp_stone_id = (kind == Soldier ? EXP_STONE_ID : EXP_STONE_ID_1);
    const unsigned exp_stone_value = (kind == Soldier ? EXP_STONE_VALUE : EXP_STONE_VALUE_1);

	if(0 == type)	//批量合成
	{
		for(int i = 0; i < data.size(); ++i)
		{
			ud = data[i]["ud"].asUInt();
			ret = logicEquip.Get(uid, ud, dataEquip);
			if (ret)
			{
				error_log("[SynthSoldierSkill] [uid= %d]get_equip_error", uid);
				return ret;
			}

			Json::GetUInt(dataEquip, "id",	id);
			Json::GetUInt(dataEquip, "ch",	ch);
			Json::GetUInt(dataEquip, "status",	status);

			if((ch <= synth_ch) && (0 != id) && 0 == status) ////低品质不能吞噬高品质
			{
				unsigned exp = 0;
				if(exp_stone_id == id)
				{
					exp += exp_stone_value; //经验石直接加经验
				}
				else
				{
					if (dataEquip.isMember("lexp"))
					{
						exp = dataEquip["lexp"].asUInt();
					}
					exp += initial_exp[ch - 1];
				}
				synth_exp += exp;
				//消耗装备或者道具
				ret = logicEquip.UseEquipment(uid, dataEquip["id"].asUInt(), ud, 1, synth_kind);
				if (ret)
				{
					error_log("[SynthSoldierSkill] [uid= %d]use_equip_error", uid);
					return ret;
				}
			}
		}
	}
	else if(1 == type) //单个合成
	{
		ud = data[0u]["ud"].asUInt();
		ret = logicEquip.Get(uid, ud, dataEquip);
		if (ret)
		{
			return ret;
		}

		Json::GetUInt(dataEquip, "ch", ch);
		Json::GetUInt(dataEquip, "status",	status);
		Json::GetUInt(dataEquip, "id",	id);
		if(synth_ch < ch)	//低品质不能吞噬高品质
		{
			LOGIC_ERROR_RETURN_MSG("level greater synthlevel");
		}
		if(0 != status)
		{
			LOGIC_ERROR_RETURN_MSG("equip can not be used");
		}

		unsigned exp = 0;
		if(exp_stone_id == id)
		{
			exp += exp_stone_value; //经验石直接加经验
		}
		else
		{
			if (dataEquip.isMember("lexp"))
			{
				exp = dataEquip["lexp"].asUInt();
			}

			exp += initial_exp[ch - 1];
		}
		synth_exp += exp;

		ret = logicEquip.UseEquipment(uid, dataEquip["id"].asUInt(), ud, 1, synth_kind);
		if (ret)
		{
			error_log("[SynthSoldierSkill] [uid= %d]use_equip_error", uid);
			return ret;
		}
	}
	else if(2 == type) //批量经验道具合成
	{
		//消耗装备或者道具
		ret = logicEquip.UseEquipment(uid, exp_stone_id, expud, expcount, synth_kind);
		if (ret)
		{
			error_log("[SynthSoldierSkill] [uid= %d]use_equip_error", uid);
			return ret;
		}
		synth_exp += exp_stone_value * expcount;
	}

	//计算提升之后的等级
	const unsigned (*exp_array)[10] = (kind == Soldier ? SOLDIER_SKILL_CHARACTER_EXP : KINGDOM_WAR_EXP);
	int i = SOLDIER_SKILL_LEVEL_MAX - 1;
	for(; i >= 0; --i)
	{
		if(synth_exp >= exp_array[synth_ch - 1][i])
		{
			++i;
			break;
		}
	}
	level = i;

	if (level >= SOLDIER_SKILL_LEVEL_MAX)
	{
		synth_exp = exp_array[synth_ch - 1][SOLDIER_SKILL_LEVEL_MAX - 1];
	}

	dataSynthEquip["q"] = level;
	dataSynthEquip["lexp"] = synth_exp;

	//更新装备信息
	ret = logicEquip.Chg(uid, equd, dataSynthEquip);

	if(ret)
	{
		return ret;
	}

	result["equip"] = dataSynthEquip;
	Json::FastWriter writer;
	string after_update = writer.write(result);
	EQUIPMENT_LOG("uid=%u,act=%s, kind=%s, after update=%s",
				uid, "SynthSoldierSkill", synth_kind.c_str(), after_update.c_str());

	//更新用户信息
	ret = logicUser.SetUserLimit(uid, dataUser);
	if(ret)
	{
		error_log("[synth %s] set_user_info_failed,uid = %u", synth_kind.c_str(), uid);
		return ret;
	}

	return R_SUCCESS;
}


int CLogicCMD::UpgradeInnateSkill(unsigned uid, unsigned heroud, Json::Value & result, unsigned lasttime, unsigned seqid)
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

		SkillUnit skillunit(uid);
		skillunit.UpgradeInnateSkill(userWrap, heroud, result);

		userWrap.Save();
	}
	catch (const std::exception& e)
	{
		::SetError(R_ERROR, e.what());
		return R_ERROR;
	}

	return R_SUCCESS;
}

int CLogicCMD::CommderSkilLearn(unsigned uid, unsigned heroud,unsigned equd,  Json::Value & result, unsigned lasttime, unsigned seqid)
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

			SkillUnit skillunit(uid);
			skillunit.CommderSkilLearn(userWrap, heroud, equd,result);
			userWrap.Save();
		}
		catch (const std::exception& e)
		{
			::SetError(R_ERROR, e.what());
			return R_ERROR;
		}

		return R_SUCCESS;
}

int CLogicCMD::PotianSkilLearn(unsigned uid, unsigned heroud,string skid, Json::Value &m_data, Json::Value & result, unsigned lasttime, unsigned seqid)
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

		SkillUnit skillunit(uid);
		skillunit.PotianSkilLearn(userWrap, heroud, skid, m_data,result);

		userWrap.Save();
	}
	catch (const std::exception& e)
	{
		::SetError(R_ERROR, e.what());
		return R_ERROR;
	}

	return R_SUCCESS;


}


int CLogicCMD::StartSkillTrain(unsigned uid, unsigned heroud, string skid, Json::Value equds, unsigned sectime, unsigned costpro, Json::Value & result, unsigned lasttime, unsigned seqid)
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

		SkillUnit skillunit(uid);
		skillunit.StartSkillTrain(userWrap, heroud, skid, equds, sectime, costpro, result);

		userWrap.Save();
	}
	catch (const std::exception& e)
	{
		::SetError(R_ERROR, e.what());
		return R_ERROR;
	}

	return R_SUCCESS;
}

int CLogicCMD::EndSkillTrain(unsigned uid, unsigned sindex, unsigned type, Json::Value & result, unsigned lasttime, unsigned seqid)
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

		SkillUnit skillunit(uid);
		skillunit.EndSkillTrain(userWrap, sindex, type, result);

		userWrap.Save();
	}
	catch (const std::exception& e)
	{
		::SetError(R_ERROR, e.what());
		return R_ERROR;
	}

	return R_SUCCESS;
}

int CLogicCMD::UpgradeHevenDaoSkill(unsigned uid, unsigned index, unsigned type, unsigned equd, Json::Value & result, unsigned lasttime, unsigned seqid)
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

		SkillUnit skillunit(uid);
		skillunit.UpgradeHevenDaoSkill(userWrap, index, type, equd, result);

		userWrap.Save();
	}
	catch (const std::exception& e)
	{
		::SetError(R_ERROR, e.what());
		return R_ERROR;
	}

	return R_SUCCESS;
}

int CLogicCMD::UpgradeCatapultSkill(unsigned uid, unsigned index, unsigned equd, Json::Value & result, unsigned lasttime, unsigned seqid)
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

		SkillUnit skillunit(uid);
		skillunit.UpgradeCatapultSkill(userWrap, index, equd, result);

		userWrap.Save();
	}
	catch (const std::exception& e)
	{
		::SetError(R_ERROR, e.what());
		return R_ERROR;
	}

	return R_SUCCESS;
}

int CLogicCMD::CalcuteFairyBag(unsigned uid, Json::Value & result, unsigned lasttime, unsigned seqid)
{
	int now = Time::GetGlobalTime();

	int start_time = 0, end_time = 0;

	start_time = Config::GetIntValue(CONFIG_ACTIVITY_TRE_BOWL_B_TS);
	end_time = Config::GetIntValue(CONFIG_ACTIVITY_TRE_BOWL_E_TS);

	if(now < start_time || now > end_time )
	{
		error_log("[CalcuteFortuneValue] fairy_bag_activity_time_error");
		return R_ERR_AUTH;
	}

	try
	{
		AUTO_LOCK_USER(uid);

		UserWrap userWrap(uid, false);

		int ret = userWrap.CheckSession(lasttime, seqid, result);

		if (ret != R_SUCCESS)
		{
			return ret;
		}

		FortuneFairyBagUnit fairybagunit(uid);
		fairybagunit.CalcuteFortune(userWrap, result);

		userWrap.Save();
	}
	catch (const std::exception& e)
	{
		::SetError(R_ERROR, e.what());
		return R_ERROR;
	}

	return R_SUCCESS;
}

int CLogicCMD::GetFairyBagReward(unsigned uid, unsigned type, Json::Value & result, unsigned lasttime, unsigned seqid)
{
	int now = Time::GetGlobalTime();

	int start_time = 0, end_time = 0;

	start_time = Config::GetIntValue(CONFIG_ACTIVITY_TRE_BOWL_B_TS);
	end_time = Config::GetIntValue(CONFIG_ACTIVITY_TRE_BOWL_E_TS);

	if(now < start_time || now > end_time )
	{
		error_log("[GetFairyBagReward] fairy_bag_activity_time_error");
		return R_ERR_AUTH;
	}

	try
	{
		AUTO_LOCK_USER(uid);

		UserWrap userWrap(uid, false);

		int ret = userWrap.CheckSession(lasttime, seqid, result);

		if (ret != R_SUCCESS)
		{
			return ret;
		}

		FortuneFairyBagUnit fairybagunit(uid);
		fairybagunit.RecieveFairyBagReward(userWrap, type, result);

		userWrap.Save();
	}
	catch (const std::exception& e)
	{
		::SetError(R_ERROR, e.what());
		return R_ERROR;
	}

	return R_SUCCESS;
}

int CLogicCMD::GetDailyChargeCoinReward(unsigned uid, unsigned index, Json::Value & result, unsigned lasttime, unsigned seqid)
{
	int now = Time::GetGlobalTime();

	int start_time = 0, end_time = 0;

	start_time = Config::GetIntValue(CONFIG_PAY_TOTAL_BEGIN_TS);  //活动的开启时间
	end_time = Config::GetIntValue(CONFIG_PAY_TOTAL_END_TS);  //活动的结束时间

	//todo 获取开服时间，判断活动是否开启
	int open_time = Config::GetIntValue(CONFIG_OPEN_TS);

	if (open_time > now)
	{
		error_log("[GetDailyChargeReward] open_time larger than now. uid=%u,open_time=%u,now=%d", open_time, now);
		return R_ERR_AUTH;
	}

	//判断是否是金币活动
	string type;
	Config::GetValue(type, CONFIG_PAYTOTAL_RETURN_TYPE);

	int diff = CTime::GetDayInterval(open_time, now);

	if (diff >= 3 && type != "coin")  //不是每日充值送金币活动
	{
		error_log("[GetDailyChargeReward] daily_charge_coin_activity_time_error. uid=%u", uid);
		return R_ERR_AUTH;
	}
	//开服的三天之内，自动开启活动，即差值0,1,2
	else if(diff >= 3 && (now < start_time || now > end_time ))
	{
		error_log("[GetDailyChargeReward] daily_charge_coin_activity_time_error. uid=%u", uid);
		return R_ERR_AUTH;
	}

	try
	{
		AUTO_LOCK_USER(uid);

		UserWrap userWrap(uid, false);

		int ret = userWrap.CheckSession(lasttime, seqid, result);

		if (ret != R_SUCCESS)
		{
			return ret;
		}

		//每日充值返金币
		DailyChargeCoinUnit dailycharge(uid);

		ret = dailycharge.GetDailyChargeCoinReward(userWrap, index, result);
		userWrap.Save();
        
		if (ret != R_SUCCESS)
		{
			return ret;
		}
	}
	catch (const std::exception& e)
	{
		::SetError(R_ERROR, e.what());
		return R_ERROR;
	}

	return R_SUCCESS;
}

int CLogicCMD::GetChargeFeedbackHeavenReward(unsigned uid, unsigned index, Json::Value & result, unsigned lasttime, unsigned seqid)
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

		ChargeFeedbackUnit feedback(uid, "heaven");
		ret = feedback.GetChargeFeedbackReward(userWrap, index, result);

		userWrap.Save();

		if (ret != R_SUCCESS)
		{
			return ret;
		}
	}
	catch (const std::exception& e)
	{
		::SetError(R_ERROR, e.what());
		return R_ERROR;
	}

	return R_SUCCESS;
}

int CLogicCMD::GetChargeFeedbackDaoistReward(unsigned uid, unsigned index, Json::Value & result, unsigned lasttime, unsigned seqid)
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

		ChargeFeedbackUnit feedback(uid, "daoist");
		ret = feedback.GetChargeFeedbackReward(userWrap, index, result);

		userWrap.Save();

		if (ret != R_SUCCESS)
		{
			return ret;
		}
	}
	catch (const std::exception& e)
	{
		::SetError(R_ERROR, e.what());
		return R_ERROR;
	}

	return R_SUCCESS;
}

int CLogicCMD::GetCelebrateNewYearReward(unsigned uid, unsigned index, Json::Value & result, unsigned lasttime, unsigned seqid)
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

		CelebrateNewYearUnit celebratenewyear(uid, "newcharge");
		ret = celebratenewyear.GetNewYearReward(userWrap, index, result);

		userWrap.Save();

		if (ret != R_SUCCESS)
		{
			return ret;
		}
	}
	catch (const std::exception& e)
	{
		::SetError(R_ERROR, e.what());
		return R_ERROR;
	}

	return R_SUCCESS;
}

int CLogicCMD::CheckTreasureVersion(unsigned uid, Json::Value &result, unsigned lasttime, unsigned seqid)
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

		//todo 百宝箱的版本检查
		TreasureBoxUnit treasureboxunit(uid);

		treasureboxunit.CheckVersion(userWrap, result);

		userWrap.Save();
	}
	catch (const std::exception& e)
	{
		::SetError(R_ERROR, e.what());
		return R_ERROR;
	}

	return R_SUCCESS;
}

int CLogicCMD::RefreshTreasureBox(unsigned uid, Json::Value &result, unsigned lasttime, unsigned seqid)
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

		//todo 刷新百宝箱物品
		TreasureBoxUnit treasureboxunit(uid);

		treasureboxunit.RefreshBox(userWrap, result);
		userWrap.Save();
	}
	catch (const std::exception& e)
	{
		::SetError(R_ERROR, e.what());
		return R_ERROR;
	}

	return 0;
}

int CLogicCMD::LotteryTreasureBoxReward(unsigned uid, Json::Value &result, unsigned lasttime, unsigned seqid)
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

		//todo 抽奖
		TreasureBoxUnit treasureboxunit(uid);

		treasureboxunit.LotteryOnce(userWrap, result);

		userWrap.Save();
	}
	catch (const std::exception& e)
	{
		::SetError(R_ERROR, e.what());
		return R_ERROR;
	}

	return 0;
}

int CLogicCMD::LotteryMultiTreasureBoxReward(unsigned uid, Json::Value &result, unsigned lasttime, unsigned seqid)
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

		//todo 十次抽奖
		TreasureBoxUnit treasureboxunit(uid);
		treasureboxunit.LotteryMulti(userWrap, result);

		userWrap.Save();
	}
	catch (const std::exception& e)
	{
		::SetError(R_ERROR, e.what());
		return R_ERROR;
	}

	return 0;
}

int CLogicCMD::OnceKeepsakeProduce(unsigned uid, unsigned equd, Json::Value &result, unsigned lasttime, unsigned seqid)
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

		//todo 单次产出
		KeepsakeUnit keepsakeunit(uid);
		keepsakeunit.ProduceKeepsake(userWrap, equd, result);

		userWrap.Save();
	}
	catch (const std::exception& e)
	{
		::SetError(R_ERROR, e.what());
		return R_ERROR;
	}

	return 0;
}

int CLogicCMD::OneKeyKeepsakeProduce(unsigned uid, unsigned equd, unsigned times, Json::Value &result, unsigned lasttime, unsigned seqid)
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

		//todo 一键产出
		KeepsakeUnit keepsakeunit(uid);
		keepsakeunit.OneKeyProduce(userWrap, equd, times, result);

		userWrap.Save();
	}
	catch (const std::exception& e)
	{
		::SetError(R_ERROR, e.what());
		return R_ERROR;
	}

	return 0;
}


int CLogicCMD::KeepsakeOneKeyFullLevel(unsigned uid,unsigned ud_hero_post, unsigned ud_keepsake, Json::Value &result, unsigned lasttime, unsigned seqid)
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
		KeepsakeUnit keepsakeunit(uid);
		keepsakeunit.OneKeyFullLevel(ud_hero_post, ud_keepsake, result);

		userWrap.Save();
	}
	catch(const std::exception& e)
	{
		::SetError(R_ERROR, e.what());
		return R_ERROR;
	}

	return R_SUCCESS;
}

int CLogicCMD::SummonNPC(unsigned uid, Json::Value &result, unsigned lasttime, unsigned seqid)
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

		//todo 召唤NPC
		KeepsakeUnit keepsakeunit(uid);
		keepsakeunit.SummonNPC(userWrap, result);

		userWrap.Save();
	}
	catch (const std::exception& e)
	{
		::SetError(R_ERROR, e.what());
		return R_ERROR;
	}

	return 0;
}

int CLogicCMD::OneKeySoldDefective(unsigned uid, unsigned equd, Json::Value &result, unsigned lasttime, unsigned seqid)
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

		//todo 一键卖出残品
		KeepsakeUnit keepsakeunit(uid);
		keepsakeunit.OnekeySoldDefective(equd, result);

		userWrap.Save();
	}
	catch (const std::exception& e)
	{
		::SetError(R_ERROR, e.what());
		return R_ERROR;
	}

	return 0;
}

int CLogicCMD::FeedKeepsake(unsigned uid, unsigned equd, unsigned convertud, Json::Value & data, Json::Value &result, unsigned lasttime, unsigned seqid)
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

		//todo 吞噬信物
		KeepsakeUnit keepsakeunit(uid);
		keepsakeunit.FeedKeepsake(userWrap, equd, convertud, data, result);

		userWrap.Save();
	}
	catch (const std::exception& e)
	{
		::SetError(R_ERROR, e.what());
		return R_ERROR;
	}

	return 0;
}

int CLogicCMD::CheckEquipStrengthenVersion(unsigned uid, Json::Value &result, unsigned lasttime, unsigned seqid)
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

		//todo 检查活动版本号
		EquipStrengthenUnit strengthenunit(uid);
		strengthenunit.CheckVersion(result);

		userWrap.Save();
	}
	catch (const std::exception& e)
	{
		::SetError(R_ERROR, e.what());
		return R_ERROR;
	}

	return 0;
}

int CLogicCMD::GetStrengthenChargeReward(unsigned uid, unsigned index, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	try
	{
		AUTO_LOCK_USER(uid);

		UserWrap userWrap(uid, false);  //需调用充值记录，所以这里是false

		int ret = userWrap.CheckSession(lasttime, seqid, result);

		if (ret != R_SUCCESS)
		{
			return ret;
		}

		//todo 领取充值奖励
		EquipStrengthenUnit strengthenunit(uid);
		strengthenunit.GetChargeReward(userWrap, index, result);

		userWrap.Save();
	}
	catch (const std::exception& e)
	{
		::SetError(R_ERROR, e.what());
		return R_ERROR;
	}

	return 0;
}

int CLogicCMD::HouHuiYouQi(unsigned uid, unsigned b_index, unsigned s_index, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	//参数边界检测
	if (b_index > HOUHUIYOUQI_BIG_TALBE_NUM || s_index > HOUHUIYOUQI_SMALL_TALBE_NUM)
	{
		PARAM_ERROR_RETURN_MSG("index is illegal");
	}

	//活动是否开启
	unsigned start_time = Config::GetIntValue(CONFIG_LARGE_FAVORABLE_BEGIN_TS);
	unsigned end_time = Config::GetIntValue(CONFIG_LARGE_RAVORABLE_END_TS);
	unsigned now = Time::GetGlobalTime();
	if(now < start_time || now > end_time)
	{
		error_log("houhuiyouqi_time_error");
		return R_ERR_AUTH;
	}

	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	int ret = 0;
	ret = logicUser.GetUser(uid, dataUser);
	if(ret)
	{
		error_log("get_user_info_failed,uid = %u", uid);
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

	//计算当日充值cash
	Json::Reader reader;
	Json::FastWriter writer;
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
		if(Time::IsToday(ts))
		{
			chargeTotal += user_flag["chgs"][i][1u].asUInt();
		}
	}

	//b_index权限检查(当日充值cash是否满足)
	CDataXML *dataXML = CDataXML::GetCDataXML();
	if(!dataXML)
	{
		error_log("GetInitXML fail");
		return R_ERR_DB;
	}
	unsigned zoneid = Config::GetZoneByUID(uid);
	unsigned big_table_right = 0;
	ret = dataXML->GetHouHuiYouQiBigTableRight(zoneid, chargeTotal, big_table_right);
	if (ret || (!big_table_right) || (b_index > big_table_right))
	{
		PARAM_ERROR_RETURN_MSG("big index right is illegal");
	}

	//secinc初始化   {"a":["111111100000","010000010100","000000000000","000000000000","000000000000"],"id":74,"ts":1473040781}
	Json::Value SecincData;
	CLogicSecinc logicSecinc;
	ret = logicSecinc.GetSecinc(uid, NAT_HOUHUIYOUQI, SecincData);
	if (ret && (ret != R_ERR_NO_DATA))
	{
		error_log("[HouHuiYouQi] get newact failed. id=%u", NAT_HOUHUIYOUQI);
		return ret;
	}
	if(!SecincData.isMember("id"))
	{
		SecincData["id"] = NAT_HOUHUIYOUQI;
	}
	if(!SecincData.isMember("ts") || !Time::IsToday(SecincData["ts"].asUInt())
		|| !SecincData.isMember("a"))
	{
		Json::Value array(Json::arrayValue);
		for (int i = 0; i < HOUHUIYOUQI_BIG_TALBE_NUM; i++)
			array.append("000000000000");
		SecincData["a"] = array;
	}

	//s_index权限检查(1.今天是否已经购买过  2.是否已经购买到了上限)
	string buy_status = SecincData["a"][b_index-1].asString();
	if (buy_status[s_index-1] == '1')
	{
		PARAM_ERROR_RETURN_MSG("one day can only buy once");
	}

	unsigned have_buy_count = 0;
	for(int ix = 0; ix != buy_status.size(); ++ix)
	{
		have_buy_count += (buy_status[ix]== '0' ? 0 : 1);
	}
	if (have_buy_count >= HOUHUIYOUQI_SMALL_TALBE_CAN_BUY)
	{
		PARAM_ERROR_RETURN_MSG("can not buy more");
	}

	//扣钻石
	XMLHouHuiYouQiItem houHuiYouQiItem;
	ret = dataXML->GetHouHuiYouQiItem(zoneid, b_index, s_index, houHuiYouQiItem);
	if (ret)
		return ret;

	unsigned need_cash = houHuiYouQiItem.is_cash_? houHuiYouQiItem.cost_ : 0;
	unsigned need_coins =  houHuiYouQiItem.is_cash_? 0 : houHuiYouQiItem.cost_;
	CLogicPay logicPay;
	DataPay payData;
	bool bsave = false;
	string log_reason = "activity_youhui_"+ CTrans::UTOS(houHuiYouQiItem.id_) + ":" + CTrans::UTOS(houHuiYouQiItem.count_);
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

	//发物品
	CLogicEquipment logicEquipment;
	if (IS_SET_EQID(houHuiYouQiItem.id_))
	{
		unsigned level = unsigned((houHuiYouQiItem.id_ - 150000) / 1000) * 10 + 50;   //套装等级
		unsigned subNum = getSubNumByCh(5);
		vector<EquipSub> sub;
		vector<string> keepstr;
		unsigned stoneID,gold;
		ret = dataXML->GetEquipSub(level,stoneID,gold,subNum, keepstr, sub);
		Json::Value newSub;
		for(int j = 0; j < sub.size(); ++j)
			newSub[sub[j].id] = sub[j].value;
		log_reason = "activity_buy_yuandan_" + CTrans::UTOS(houHuiYouQiItem.id_);
		ItemAdd add_suid(houHuiYouQiItem.id_, houHuiYouQiItem.count_, log_reason, 5,  0);
		Json::Value newEqDatas = Json::Value(Json::arrayValue);
		logicEquipment.genEquipSet(add_suid, newEqDatas, newSub, 1100);

		ret = logicEquipment.UpdateEquipment(uid, 0, newEqDatas, result["add_equip"], true);
	} else
	{
		ret = logicEquipment.AddOneItem(uid, houHuiYouQiItem.id_, houHuiYouQiItem.count_, "activity_buy_yuandan_" + CTrans::UTOS(houHuiYouQiItem.id_), result["add_equip"], true);
	}
	if(ret)
	{
		error_log("[Add_Equip_error][uid=%u][equip_id=%u]", uid, houHuiYouQiItem.id_);
		return R_ERR_DATA;
	}

	//newAct
	SecincData["ts"] = Time::GetGlobalTime();
	buy_status[s_index-1] = '1';
	SecincData["a"][b_index-1] = buy_status.c_str();
	result["newAct"] = SecincData;
	ret = logicSecinc.SetOneSecinc(uid, SecincData);
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


int CLogicCMD::BigHarvestRewardCoins(unsigned uid, const Json::Value &bid_arr, unsigned fcm, Json::Value &result, unsigned lasttime, unsigned seqid)
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

	//获取主城等级
	CLogicBuilding logicBd;
	Json::Value Bd;
	ret = logicBd.Get(uid, 1, 0, true, Bd);
	if (ret)
		return ret;
	int home_lvl = 0;
	if (Bd.isMember("l") && Bd["l"].isIntegral())
	{
		home_lvl = Bd["l"].asInt();
	} else
	{
		DATA_ERROR_RETURN_MSG("hometown no level");
	}

	//遍历资源建筑, 计算金币
	unsigned sum_add_coins = 0;
	unsigned len = bid_arr.size();
	for (int i = 0; i < len; ++i)
	{
		Json::Value source_building;
		unsigned bid = bid_arr[i].asUInt();
		ret = logicBd.Get(uid, bid, 0, false, source_building);
		if (ret)
			return ret;
		unsigned source_building_level = 0;
		if (source_building.isMember("l") && source_building["l"].isIntegral())
		{
			source_building_level = source_building["l"].asUInt();
		} else
		{
			DATA_ERROR_RETURN_MSG("source_building no level");
		}

		if ((source_building_level == home_lvl)  &&
			(Time::GetGlobalTime() >= source_building["fullt"].asUInt() + 3600))   //等级相等 && 在1小时内
		{
			float rate = (dataUser.prosper / 200 + source_building_level * 2) / 100;   //威望和资源等级
			unsigned add_gold = 0;
			add_gold = int(rate * 10 / 3 + 1);
			if (add_gold > 4)
			{
				if (dataUser.prosper > 50000)
				{
					add_gold = 5;
				} else
				{
					add_gold = 4;
				}
			}
			if (dataUser.prosper >= add_gold*2  &&  add_gold)
			{
				sum_add_coins += add_gold;
				source_building["fullt"] = Time::GetGlobalTime();
				ret = logicBd.Chg(uid, bid, 0, false, source_building);
				if (ret)
					return ret;
			}
		}
	}

	sum_add_coins = (int)(sum_add_coins * FCM_VALUE[fcm]);
	if(sum_add_coins)
	{
		//添加金币
		CLogicPay logicPay;
		DataPay payData;
		std::string szReason = "big_harvest_reward_coins";
		if ((ret = logicPay.ChangePay(uid, 0, sum_add_coins, szReason, payData)) != 0)
		{
			error_log("big_harvest_reward_coins add coins failed. uid=%d, ret=%d", uid, ret);
			return ret;
		}
		result["coins"] = payData.coins;
		result["coins2"] = payData.cash;
	}

	ret = logicUser.SetUserLimit(uid, dataUser);
	if(ret)
		return ret;

	return R_SUCCESS;
}


int CLogicCMD::MoneyTreeRewardCoins(unsigned uid, unsigned fcm, Json::Value &result, unsigned lasttime, unsigned seqid)
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

	//找发财树
	CLogicBuilding logicBuilding;
	Json::Value all_buildings;
	ret = logicBuilding.GetAllBuilding(uid, all_buildings);
	if(ret)
		return ret;

	bool find_tree = false;
	Json::Value money_tree;
	for (unsigned i = 0; i < all_buildings.size(); i++)
	{
		if(all_buildings[i].isMember("t") && all_buildings[i]["t"].asUInt() == 50)
		{
			money_tree = all_buildings[i];
			find_tree = true;
		}
	}
	if (!find_tree)
	{
		DATA_ERROR_RETURN_MSG("not find money tree");
	}

	//一天只能领取一次
	if ((money_tree["lharvest"].asUInt() + 86400) > Time::GetGlobalTime())
	{
		LOGIC_ERROR_RETURN_MSG("one day can get once");
	}

	//计算需要的水滴数
	unsigned money_tree_level = (!money_tree.isMember("l"))?1:money_tree["l"].asUInt();
	unsigned need_waters = 0;
	if (money_tree_level < 5)
	{
		need_waters = 5;
	} else
	{
		need_waters = money_tree_level;
	}
	if (need_waters > 20)
		need_waters = 20;

	//拥有的水滴是否够了
	int have_waters = 0;
	vector<unsigned> other_person;
	other_person.clear();
	for(int ix = 0; ix != money_tree["watern"].size(); ++ix)
	{
		unsigned temp_uid = money_tree["watern"][ix].asUInt();
		if(uid != temp_uid)
		{
			other_person.push_back(temp_uid);
		} else
		{
			++have_waters;
		}
	}
	have_waters += other_person.size();
	if (have_waters < need_waters)
	{
		LOGIC_ERROR_RETURN_MSG("water is not enough");
	}

	//水滴够了，计算金币
	unsigned add_coins = 0;
	if (money_tree["extrag"].asUInt() > need_waters)
	{
		money_tree["extrag"] = need_waters;
	}
	if (money_tree_level < 10)
	{
		add_coins = 2*need_waters + money_tree["extrag"].asUInt();
	} else
	{
		add_coins = 20 + (money_tree_level-10) * 1.5 + money_tree["extrag"].asUInt();
	}

	//update building
	money_tree["extrag"] = 0;
	money_tree["lharvest"] = Time::GetGlobalTime();
	money_tree["lowaterts"] = 0;
	money_tree["upts"] = Time::GetGlobalTime();
	money_tree["watern"].resize(0);
	ret = logicBuilding.Chg(uid, money_tree["id"].asUInt(), 0, false, money_tree);
	if (ret)
		return ret;
	result["bd"] = money_tree;

	add_coins = (int)(add_coins * FCM_VALUE[fcm]);
	if(add_coins)
	{
		//发金币
		CLogicPay logicPay;
		DataPay payData;
		std::string szReason = "money_tree_reward_coins";
		if ((ret = logicPay.ChangePay(uid, 0, add_coins, szReason, payData)) != 0)
		{
			error_log("money_tree_reward_coins add coins failed. uid=%d, ret=%d", uid, ret);
			return ret;
		}
		result["coins"] = payData.coins;
		result["coins2"] = payData.cash;
	}

	ret = logicUser.SetUserLimit(uid, dataUser);
	if(ret)
		return ret;

	return R_SUCCESS;
}


int CLogicCMD::ChaoZhiZheKou(unsigned uid, unsigned b_index, unsigned s_index, unsigned count, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	//参数边界检测
	if (b_index < 1 || b_index > CHAOZHIZHEKOU_BIG_TALBE_NUM ||
		s_index < 1 || s_index > CHAOZHIZHEKOU_SMALL_TALBE_NUM)
	{
		PARAM_ERROR_RETURN_MSG("index is illegal");
	}

	//活动是否开启
	unsigned start_time = Config::GetIntValue(CONFIG_ACTIVITY_YUANDAN_B_TS);
	unsigned end_time = Config::GetIntValue(CONFIG_ACTIVITY_YUANDAN_E_TS);
	unsigned now = Time::GetGlobalTime();
	if(now < start_time || now > end_time)
	{
		error_log("caozhizhekou_time_error");
		return R_ERR_AUTH;
	}

	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	int ret = 0;
	ret = logicUser.GetUser(uid, dataUser);
	if(ret)
	{
		error_log("get_user_info_failed,uid = %u", uid);
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

	//计算当日充值cash
	Json::Reader reader;
	Json::FastWriter writer;
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
		if(Time::IsToday(ts))
		{
			chargeTotal += user_flag["chgs"][i][1u].asUInt();
		}
	}

	//b_index权限检查(当日充值cash是否满足)
	CDataXML *dataXML = CDataXML::GetCDataXML();
	if(!dataXML)
	{
		error_log("GetInitXML fail");
		return R_ERR_DB;
	}
	unsigned zoneid = Config::GetZoneByUID(uid);
	unsigned big_table_right = 0;
	ret = dataXML->GetChaoZhiZheKouBigTableRight(zoneid, chargeTotal, big_table_right);
	if (ret || (!big_table_right) || (b_index > big_table_right))
	{
		PARAM_ERROR_RETURN_MSG("big index right is illegal");
	}

	//secinc初始化   {"a":[[0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0]],"b":1473750990,"id":61}
	Json::Value SecincData;
	CLogicSecinc logicSecinc;
	ret = logicSecinc.GetSecinc(uid, NAT_SUPER_REDUCE, SecincData);
	if (ret && (ret != R_ERR_NO_DATA))
	{
		error_log("[ChaoZhiZheKou] get newact failed. id=%u", NAT_SUPER_REDUCE);
		return ret;
	}

	if(!SecincData.isMember("id"))
	{
		SecincData["id"] = NAT_SUPER_REDUCE;
	}

	if(!SecincData.isMember("b") || !Time::IsToday(SecincData["b"].asUInt())
		|| !SecincData.isMember("a"))
	{
		for (int i = 0; i < CHAOZHIZHEKOU_BIG_TALBE_NUM; i++)
		{
			for(int j = 0; j < 10; ++j)  //因为前端多存了2个
			{
				SecincData["a"][i][j] = 0;
			}
		}
	}

	//s_index权限检查(是否已经购买到了上限)
	XMLChaoZhiZheKouItem chaoZhiZheKouItem;
	ret = dataXML->GetChaoZhiZheKouItem(zoneid, b_index, s_index, chaoZhiZheKouItem);

	if (ret)
		return ret;

	if (SecincData["a"][b_index-1][s_index-1].asUInt() + count > chaoZhiZheKouItem.limit_)
	{
		PARAM_ERROR_RETURN_MSG("can buy no more");
	}

	//扣钻石
	unsigned need_cash = chaoZhiZheKouItem.is_cash_? chaoZhiZheKouItem.cost_ : 0;
	unsigned need_coins =  chaoZhiZheKouItem.is_cash_? 0 : chaoZhiZheKouItem.cost_;

	need_cash *= count;  //根据购买次数，计算花的钻石和金币个数
	need_coins *= count;

	CLogicPay logicPay;
	DataPay payData;
	bool bsave = false;
	string log_reason = "activity_chaozhizhekou_"+ CTrans::UTOS(chaoZhiZheKouItem.id_) + ":" + CTrans::UTOS(chaoZhiZheKouItem.count_);

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

	//发物品
	CLogicEquipment logicEquipment;

	if (IS_SET_EQID(chaoZhiZheKouItem.id_))
	{
		unsigned level = unsigned((chaoZhiZheKouItem.id_ - 150000) / 1000) * 10 + 50;   //套装等级
		unsigned subNum = getSubNumByCh(5);
		vector<EquipSub> sub;
		vector<string> keepstr;
		unsigned stoneID,gold;
		ret = dataXML->GetEquipSub(level,stoneID,gold,subNum, keepstr, sub);
		Json::Value newSub;
		for(int j = 0; j < sub.size(); ++j)
			newSub[sub[j].id] = sub[j].value;
		log_reason = "activity_chaozhizhekou_" + CTrans::UTOS(chaoZhiZheKouItem.id_);
		ItemAdd add_suid(chaoZhiZheKouItem.id_, chaoZhiZheKouItem.count_ * count, log_reason, 5,  0);
		Json::Value newEqDatas = Json::Value(Json::arrayValue);
		logicEquipment.genEquipSet(add_suid, newEqDatas, newSub, 1100);

		ret = logicEquipment.UpdateEquipment(uid, 0, newEqDatas, result["add_equip"], true);
	}
	else
	{
		ret = logicEquipment.AddOneItem(uid, chaoZhiZheKouItem.id_, chaoZhiZheKouItem.count_ * count, "activity_chaozhizhekou_" + CTrans::UTOS(chaoZhiZheKouItem.id_), result["add_equip"], true);
	}

	if(ret)
	{
		error_log("[Add_Equip_error][uid=%u][equip_id=%u]", uid, chaoZhiZheKouItem.id_);
		return R_ERR_DATA;
	}

	//newAct
	SecincData["b"] = Time::GetGlobalTime();
	SecincData["a"][b_index-1][s_index-1] = SecincData["a"][b_index-1][s_index-1].asUInt() + count;
	result["newAct"] = SecincData;

	ret = logicSecinc.SetOneSecinc(uid, SecincData);

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


int CLogicCMD::YueHuiJuXian(unsigned uid, unsigned b_index, unsigned s_index, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	//参数边界检测
	if (b_index > YUEHUIJUXIAN_BIG_TALBE_NUM || s_index > YUEHUIJUXIAN_SMALL_TALBE_NUM)
	{
		PARAM_ERROR_RETURN_MSG("index is illegal");
	}

	//活动是否开启
	unsigned start_time = Config::GetIntValue(CONFIG_ACTIVITY_YUANDAN_B_TS);
	unsigned end_time = Config::GetIntValue(CONFIG_ACTIVITY_YUANDAN_E_TS);
	unsigned now = Time::GetGlobalTime();
	if(now < start_time || now > end_time)
	{
		error_log("yuehuijuxian_time_error");
		return R_ERR_AUTH;
	}

	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	int ret = 0;
	ret = logicUser.GetUser(uid, dataUser);
	if(ret)
	{
		error_log("get_user_info_failed,uid = %u", uid);
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

	//计算当日充值cash
	Json::Reader reader;
	Json::FastWriter writer;
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
		if(Time::IsToday(ts))
		{
			chargeTotal += user_flag["chgs"][i][1u].asUInt();
		}
	}

	//b_index权限检查(当日充值cash是否满足)
	CDataXML *dataXML = CDataXML::GetCDataXML();
	if(!dataXML)
	{
		error_log("GetInitXML fail");
		return R_ERR_DB;
	}
	unsigned zoneid = Config::GetZoneByUID(uid);
	unsigned big_table_right = 0;
	ret = dataXML->GetYueHuiJuXianBigTableRight(zoneid, chargeTotal, big_table_right);
	if (ret || (!big_table_right) || (b_index > big_table_right))
	{
		PARAM_ERROR_RETURN_MSG("big index right is illegal");
	}

	//secinc初始化   {"a":1473869296,"b":[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],"id":11}
	Json::Value SecincData;
	CLogicSecinc logicSecinc;
	ret = logicSecinc.GetSecinc(uid, NAT_YUANDAN_SOHP, SecincData);
	if (ret && (ret != R_ERR_NO_DATA))
	{
		error_log("[YueHuiJuXian] get newact failed. id=%u", NAT_YUANDAN_SOHP);
		return ret;
	}
	if(!SecincData.isMember("id"))
	{
		SecincData["id"] = NAT_YUANDAN_SOHP;
	}
	if(!SecincData.isMember("a") || !Time::IsToday(SecincData["a"].asUInt())
		|| !SecincData.isMember("b"))
	{
		for (int i = 0; i < YUEHUIJUXIAN_BIG_TALBE_NUM*YUEHUIJUXIAN_SMALL_TALBE_NUM; ++i)
		{
			SecincData["b"][i] = 0;
		}
	}

	//s_index权限检查(1.今天是否已经购买过)
	unsigned buy_arr_order = (b_index - 1) * YUEHUIJUXIAN_SMALL_TALBE_NUM + s_index - 1;
	if (buy_arr_order >= YUEHUIJUXIAN_BIG_TALBE_NUM*YUEHUIJUXIAN_SMALL_TALBE_NUM)
	{
		PARAM_ERROR_RETURN_MSG("index out of range");
	}
	if (SecincData["b"][buy_arr_order].asUInt() == 1)
	{
		PARAM_ERROR_RETURN_MSG("one day can only buy once");
	}

	//扣钻石
	XMLYueHuiJuXianItem yueHuiJuXianItem;
	ret = dataXML->GetYueHuiJuXianItem(zoneid, b_index, s_index, yueHuiJuXianItem);
	if (ret)
		return ret;

	unsigned need_cash = yueHuiJuXianItem.is_cash_? yueHuiJuXianItem.cost_ : 0;
	unsigned need_coins =  yueHuiJuXianItem.is_cash_? 0 : yueHuiJuXianItem.cost_;
	CLogicPay logicPay;
	DataPay payData;
	bool bsave = false;
	string log_reason = "activity_yuehuijuxian_"+ CTrans::UTOS(yueHuiJuXianItem.id_) + ":" + CTrans::UTOS(yueHuiJuXianItem.count_);
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

	//发物品
	CLogicEquipment logicEquipment;
	if (IS_SET_EQID(yueHuiJuXianItem.id_))
	{
		unsigned level = unsigned((yueHuiJuXianItem.id_ - 150000) / 1000) * 10 + 50;   //套装等级
		unsigned subNum = getSubNumByCh(5);
		vector<EquipSub> sub;
		vector<string> keepstr;
		unsigned stoneID,gold;
		ret = dataXML->GetEquipSub(level,stoneID,gold,subNum, keepstr, sub);
		Json::Value newSub;
		for(int j = 0; j < sub.size(); ++j)
			newSub[sub[j].id] = sub[j].value;
		log_reason = "activity_yuehuijuxian_" + CTrans::UTOS(yueHuiJuXianItem.id_);
		ItemAdd add_suid(yueHuiJuXianItem.id_, yueHuiJuXianItem.count_, log_reason, 5,  0);
		Json::Value newEqDatas = Json::Value(Json::arrayValue);
		logicEquipment.genEquipSet(add_suid, newEqDatas, newSub, 1100);

		ret = logicEquipment.UpdateEquipment(uid, 0, newEqDatas, result["add_equip"], true);
	} else
	{
		ret = logicEquipment.AddOneItem(uid, yueHuiJuXianItem.id_, yueHuiJuXianItem.count_, "activity_yuehuijuxian_" + CTrans::UTOS(yueHuiJuXianItem.id_), result["add_equip"], true);
	}
	if(ret)
	{
		error_log("[Add_Equip_error][uid=%u][equip_id=%u]", uid, yueHuiJuXianItem.id_);
		return R_ERR_DATA;
	}

	//newAct
	SecincData["a"] = Time::GetGlobalTime();
	SecincData["b"][buy_arr_order] = 1;
	result["newAct"] = SecincData;
	ret = logicSecinc.SetOneSecinc(uid, SecincData);
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


int CLogicCMD::LimitBuyOfZone(unsigned uid, unsigned index, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	//参数边界检测
	if (index > LIMITBUYOFZONE_TALBE_NUM || !index)
	{
		PARAM_ERROR_RETURN_MSG("index is illegal");
	}

	//活动是否开启
	unsigned start_time = Config::GetIntValue(CONFIG_ACTIVITY_RESTRICTION_B_TS);
	unsigned end_time = Config::GetIntValue(CONFIG_ACTIVITY_RESTRICTION_E_TS);
	unsigned now = Time::GetGlobalTime();
	if(now < start_time || now > end_time)
	{
		error_log("limitbuyofzone_time_error");
		return R_ERR_AUTH;
	}

	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	int ret = 0;
	ret = logicUser.GetUser(uid, dataUser);
	if(ret)
	{
		error_log("get_user_info_failed,uid = %u", uid);
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

	//计算活动期间消费cash
	Json::Reader reader;
	Json::FastWriter writer;
	Json::Value user_flag;
	reader.parse(dataUser.user_flag, user_flag);
	if (!user_flag.isMember("user_pay") || !user_flag["user_pay"].isArray())
	{
		error_log("user_pay error");
		DATA_ERROR_RETURN_MSG("user_pay error");
	}
	unsigned size = user_flag["user_pay"].size();
	unsigned consumeTotal = 0;
	for (unsigned i = 0; i < size; ++i)
	{
		unsigned ts  = user_flag["user_pay"][i][0u].asUInt();
		if(ts >= start_time && ts <= end_time)
		{
			consumeTotal += user_flag["user_pay"][i][1u].asUInt();
		}
	}

	//index权限检查(活动期间消费cash是否满足)
	CDataXML *dataXML = CDataXML::GetCDataXML();
	if(!dataXML)
	{
		error_log("GetInitXML fail");
		return R_ERR_DB;
	}
	int zoneid = 0;
	Config::GetDomain(zoneid);
	unsigned table_right = 0;
	ret = dataXML->GetLimitBuyOfZoneTableRight(zoneid, consumeTotal, table_right);
	if (ret || (!table_right) || (index > table_right))
	{
		PARAM_ERROR_RETURN_MSG("index right is illegal");
	}

	//secinc初始化   {"a":{"value":1448940450},"id":18}
	Json::Value SecincData;
	CLogicSecinc logicSecinc;
	ret = logicSecinc.GetSecinc(uid, NAT_LIMIT_BUY, SecincData);
	if (ret && (ret != R_ERR_NO_DATA))
	{
		error_log("[LimitBuyOfZone] get newact failed. id=%u", NAT_LIMIT_BUY);
		return ret;
	}
	if(!SecincData.isMember("id"))
	{
		SecincData["id"] = NAT_LIMIT_BUY;
	}

	//是否冷却
	if(SecincData.isMember("a") &&
	   SecincData["a"].isMember("value") &&
	   (SecincData["a"]["value"].asUInt() > Time::GetGlobalTime()))
	{
		LOGIC_ERROR_RETURN_MSG("still freeze");
	}

	//是否被抢完了
	CDataRestric *pdata= CLogicRestric::GetRestricData();
	if(pdata == NULL)
	{
		DB_ERROR_RETURN_MSG("init_RestricData_fail");
	}
	vector <unsigned> num;
	ret = pdata->GetRestricItemsNum(num);
	if(ret != 0)
	{
		return ret;
	}
	unsigned remain_cnt = num[index-1];
	if (!remain_cnt)
	{
		for(int i=0; i<num.size(); ++i)
		{
			result["id"][i] = num[i];
		}
		result["flag"] = false;
		return R_SUCCESS;
	}

	//更新共享内存
	bool flag = false;
	ret = pdata->UpdateRare(index-1, num, flag);
	if(ret)
	{
		return ret;
	}
	result["flag"] = flag;
	for(int i=0; i<num.size(); ++i)
	{
		result["id"][i] = num[i];
	}
	if (!flag)
	{
		return R_SUCCESS;
	}

	//可以购买
	XMLLimitBuyOfZoneItem limitBuyOfZoneItem;
	ret = dataXML->GetLimitBuyOfZoneItem(zoneid, index, limitBuyOfZoneItem);
	if (ret)
		return ret;

	//扣钻石
	unsigned need_cash = limitBuyOfZoneItem.cash_;
	CLogicPay logicPay;
	DataPay payData;
	bool bsave = false;
	string log_reason = "activity_limitbuy_"+ CTrans::UTOS(limitBuyOfZoneItem.id_);
	ret = logicPay.ProcessOrderForBackend(uid, -need_cash, 0, payData, log_reason, user_flag, bsave);
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

	//发物品
	CLogicEquipment logicEquipment;
	if (IS_SET_EQID(limitBuyOfZoneItem.eqid_))
	{
		unsigned level = unsigned((limitBuyOfZoneItem.eqid_ - 150000) / 1000) * 10 + 50;   //套装等级
		unsigned subNum = getSubNumByCh(5);
		vector<EquipSub> sub;
		vector<string> keepstr;
		unsigned stoneID,gold;
		ret = dataXML->GetEquipSub(level,stoneID,gold,subNum, keepstr, sub);
		Json::Value newSub;
		for(int j = 0; j < sub.size(); ++j)
			newSub[sub[j].id] = sub[j].value;
		log_reason = "activity_limitbuy_" + CTrans::UTOS(limitBuyOfZoneItem.id_);
		ItemAdd add_suid(limitBuyOfZoneItem.eqid_, limitBuyOfZoneItem.eq_cnt_, log_reason, limitBuyOfZoneItem.eq_ch_,  limitBuyOfZoneItem.eq_q_);
		Json::Value newEqDatas = Json::Value(Json::arrayValue);
		logicEquipment.genEquipSet(add_suid, newEqDatas, newSub, 1100);

		ret = logicEquipment.UpdateEquipment(uid, 0, newEqDatas, result["add_equip"], true);
	} else
	{
		ret = logicEquipment.AddOneItem(uid, limitBuyOfZoneItem.eqid_, limitBuyOfZoneItem.eq_cnt_, "activity_limitbuy_" + CTrans::UTOS(limitBuyOfZoneItem.id_), result["add_equip"], true, limitBuyOfZoneItem.eq_ch_,  limitBuyOfZoneItem.eq_q_);
	}
	if(ret)
	{
		error_log("[Add_Equip_error][uid=%u][equip_id=%u]", uid, limitBuyOfZoneItem.id_);
		return R_ERR_DATA;
	}

	//newAct
	SecincData["a"]["value"] = Time::GetGlobalTime() + 900;
	result["newAct"] = SecincData;
	ret = logicSecinc.SetOneSecinc(uid, SecincData);
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


int CLogicCMD::FiveDefendGrow(unsigned uid, unsigned order, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	if (order > 5 || !order)
	{
		error_log("param error: order out of range");
		return R_ERR_PARAM;
	}

	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	int ret = 0;
	ret = logicUser.GetUser(uid, dataUser);
	if(ret)
	{
		error_log("get_user_info_failed,uid = %u", uid);
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

	//数据初始化
	Json::Value user_tech;
	user_tech.clear();
	Json::Reader reader;
	reader.parse(dataUser.user_tech,user_tech);
	if((!user_tech.isMember("wxd"))   ||
	    (!user_tech["wxd"].isArray()) ||
		(user_tech["wxd"].size() != FIVE_DEFEND_KINDS))
	{
		for(int ix = 0; ix != FIVE_DEFEND_KINDS; ++ix)
		{
			user_tech["wxd"][ix] = 0;
		}
	}
	if (user_tech["wxd"][order-1] >= 100)
	{
		DATA_ERROR_RETURN_MSG("five_level_data_is_error");
	}

	//需要多少道具
	CDataXML *dataXML = CDataXML::GetCDataXML();
	if(!dataXML)
	{
		error_log("GetInitXML fail");
		return R_ERR_DB;
	}

	unsigned curr_five_level = user_tech["wxd"][order-1].asUInt();
	XMLFiveDefendGrowItem five_item;
	ret = dataXML->GetFiveDefendGrowItem(curr_five_level+1, five_item);
	if (ret)
	{
		DATA_ERROR_RETURN_MSG("five_level_get_item_error");
	}
	unsigned need_props_cnt = five_item.cost_;
	if (curr_five_level+1 != five_item.level_)
	{
		DATA_ERROR_RETURN_MSG("five_level_get_item_dismatch_error");
	}

	//扣除道具
	CLogicEquipment logicEquip;
	Json::Value equip_data;
	ret = logicEquip.GetEquipment(uid, 0, equip_data);
	if(ret)
		return ret;

	for(int i=0; i<equip_data.size(); ++i)
	{
		if(equip_data[i]["id"].asUInt() == FIVE_DEFEND_SOUL_DAN)
		{
			string reason = "fivedefendgrow";
			if (equip_data[i]["count"].asUInt() < need_props_cnt)
			{
				LOGIC_ERROR_RETURN_MSG("have_not_enough_five_dan");
			}
			ret = logicEquip.UseEquipment(uid, equip_data[i]["id"].asUInt(), equip_data[i]["ud"].asUInt(), need_props_cnt, reason);
			if(ret)
				return ret;
			equip_data[i]["count"] = equip_data[i]["count"].asUInt() - need_props_cnt;
			result["del_equip"] = equip_data[i];
			break;
		}
	}

	//加等级
	user_tech["wxd"][order-1] = user_tech["wxd"][order-1].asUInt() + 1;
	Json::FastWriter writer;
	dataUser.user_tech = writer.write(user_tech);
	result["wxd"] = user_tech["wxd"];

	ret = logicUser.SetUser(uid, dataUser);
	if(ret)
		return ret;

	return R_SUCCESS;
}


int CLogicCMD::FiveAttackGrow(unsigned uid, const Json::Value & data, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	int ret = 0;
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

	//检查 输入参数
	unsigned count = 0, five_id = 0;
	if(!Json::GetUInt(data, "count", count) || !Json::GetUInt(data, "gem_id", five_id))
	{
		error_log("para_error");
		return R_ERR_PARAM;
	}

	//判断是否有万能灵珠
	unsigned snap_eqid = 0;
	Json::GetUInt(data, "snap_gem_id", snap_eqid);

	if((!IS_FIVE_ATTACK_STONE_EQID(five_id)) || (snap_eqid > 0 && !IS_UNLIMIT_PEARL(snap_eqid)) || (0 == five_id%10) ||
		(count < FIVE_ATTACK_SYNTHETIC_COUNT - 1)  || (count >= FIVE_ATTACK_SYNTHETIC_COUNT && count % FIVE_ATTACK_SYNTHETIC_COUNT))
	{
		return R_ERR_PARAM;
	}

	CLogicEquipment logicEquip;

	//是否真的有相应数目的五行攻击珠
	Json::Value equip_data;
	ret = logicEquip.GetEquipment(uid, 0, equip_data);
	if(ret)
		return ret;

	vector <unsigned> del_five_ids;
	vector <unsigned> del_five_equids;
	vector <string>  del_data_ids;
	Json::FastWriter writer;
	unsigned sub_count = 0, reselt_id = 0;

	vector<unsigned> del_unlimited_ids;  //待删除的万能灵珠
	unsigned nowts = Time::GetGlobalTime();

	for(int i=0; i<equip_data.size(); ++i)
	{
		if(equip_data[i]["id"].asInt() == five_id  && equip_data[i].isMember("status") && equip_data[i]["status"].asUInt() == 0)
		{
			//当参数中有万能灵珠的存在时，那么必须要等到查到灵珠的ud时，循环才能停止
			if(sub_count == count && (0 == snap_eqid || del_unlimited_ids.size() > 0))
			{
				break;
			}
			else if (sub_count < count)
			{
				//当要消耗的普通灵珠数量不够要求时，将查到的灵珠添加进集合，如果数量已够，则不做任何操作，等待万能灵珠满足条件，就退出循环
				del_five_ids.push_back(equip_data[i]["ud"].asUInt());
				del_five_equids.push_back(equip_data[i]["id"].asUInt());
				del_data_ids.push_back(writer.write(equip_data[i]));
				result["del_equip"][reselt_id] = equip_data[i];

				++reselt_id;
				++sub_count;
			}
		}
		else if (snap_eqid > 0 && del_unlimited_ids.size() == 0 && equip_data[i]["id"].asInt() == snap_eqid && equip_data[i].isMember("ats") && equip_data[i]["ats"].asUInt() > nowts)
		{
			//当不存在可以消耗的万能灵珠时，才添加
			del_unlimited_ids.push_back(equip_data[i]["ud"].asUInt());
		}
	}

	if(sub_count != count)
	{
		error_log("[syntheticgem_five_count_lacking][uid=%u,five_id=%u,five_count=%u,sub_count=%u]",
				uid, five_id, count, sub_count);
		return R_ERROR;
	}

	if (snap_eqid > 0 && 0 == del_unlimited_ids.size())
	{
		error_log("[syntheticgem_five] snap eqid error. uid=%u,eqid=%u", uid, snap_eqid);
		LOGIC_ERROR_RETURN_MSG("snap_param_error");
	}

	for(int j = 0; j < del_unlimited_ids.size(); ++j)
	{
		//不可叠加装备，count=0
		ret = logicEquip.UseEquipment(uid, snap_eqid, del_unlimited_ids[j], 0, "back_synthetic_five_del");

		if (ret)
		{
			return ret;
		}
	}

	//删除低级珠
	for(int i=0; i< del_five_ids.size(); i++)
	{
		ret = logicEquip.Del(uid, del_five_ids[i]);
		if(ret)
			return ret;

		EQUIPMENT_LOG("uid=%u,id=%u,eqid=%d,act=%s,chg=%d,count=%d,code=%s,data=%s",uid,del_five_ids[i],del_five_equids[i],
						"del",-1,0,"back_synthetic_five_del",del_data_ids[i].c_str());
	}

	//添加高级珠
	unsigned synthetic_five_id = five_id + 1;
	unsigned synthetic_count = 0;

	if (snap_eqid > 0)
	{
		synthetic_count = 1;
	}
	else
	{
		synthetic_count = int(count / FIVE_ATTACK_SYNTHETIC_COUNT);
	}

	ret = logicEquip.AddOneItem(uid, synthetic_five_id, synthetic_count,"back_synthetic_five_add",result["add_equip"], true);
	if(ret)
		return ret;

	ret = logicUser.SetUserLimit(uid, dataUser);
	if(ret)
		return ret;
	return R_SUCCESS;
}


int CLogicCMD::FiveAttackActivity(unsigned uid, const Json::Value data, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	int ret = 0;
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

	//活动是否开启
	unsigned start_time = Config::GetIntValue(CONFIG_WUXING_PEARL_BEGIN_TS);
	unsigned end_time = Config::GetIntValue(CONFIG_WUXING_PEARL_END_TS);
	unsigned now = Time::GetGlobalTime();
	if(now < start_time || now > end_time)
	{
		error_log("wuxing_activity_time_error");
		return R_ERR_AUTH;
	}

	//看是否领取过了, 领取过的话， logic_error  {"a":0,"id":87,"v":20161009}
	CLogicSecinc Secinc;
	Json::Value SecincData;
	ret = Secinc.GetSecinc(uid, NAT_WUXING_PEARL, SecincData);
	if (ret == R_ERR_NO_DATA)
	{
		SecincData["id"] = NAT_WUXING_PEARL;
		SecincData["a"] = 0;
		SecincData["v"] = Config::GetIntValue(CONFIG_WUXING_PEARL_VER);
	} else if (ret)
	{
		return ret;
	}

	//当开下一次活动时
	if(SecincData["v"].asInt() != Config::GetIntValue(CONFIG_WUXING_PEARL_VER))
	{
		SecincData["id"] = NAT_WUXING_PEARL;
		SecincData["a"] = 0;
		SecincData["v"] = Config::GetIntValue(CONFIG_WUXING_PEARL_VER);
	}

	if (SecincData["a"].asUInt())
	{
		LOGIC_ERROR_RETURN_MSG("can only get one in activity");
	}

	//充的钻石数是否够了 (活动时间内)
	Json::Reader reader;
	Json::FastWriter writer;
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
		if(ts >= start_time && ts <= end_time)
		{
			chargeTotal += user_flag["chgs"][i][1u].asUInt();
		}
	}

	//读取配置文件, 获取物品id, 和cash充值条件
	CDataXML *dataXML = CDataXML::GetCDataXML();
	if(!dataXML)
	{
		DB_ERROR_RETURN_MSG("GetInitXML_fail");
	}

	unsigned cond = 0;
	unsigned eqid = 0;
	unsigned eq_count = 0;
	ret = dataXML->GetWuxingPearlData(1, cond, eqid, eq_count);
	if (ret)
	{
		DB_ERROR_RETURN_MSG("GetWuXingActivityItem_fail");
	}
	if (!cond || !eqid || !eq_count)
	{
		DB_ERROR_RETURN_MSG("GetWuXingActivityItem_fail2");
	}

	if (chargeTotal < cond)
	{
		LOGIC_ERROR_RETURN_MSG("cash charge is not enough");
	}

	//添加五行包
	CLogicEquipment logicEquip;
	ret = logicEquip.AddOneItem(uid, eqid, eq_count,"five_attack_activity",result["add_equip"], true);
	if(ret)
		return ret;

	//标识领取
	SecincData["a"] = 1;
	ret = Secinc.SetOneSecinc(uid, SecincData);
	if (ret)
	{
		error_log("FiveAttackActivity SetOneSecinc failed. uid=%u, ret=%d", uid, ret);
		return ret;
	}
	result["newAct"] = SecincData;

	ret = logicUser.SetUser(uid, dataUser);
	if(ret)
		return ret;

	return R_SUCCESS;
}


