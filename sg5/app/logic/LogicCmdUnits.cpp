/*
 * LogicCmdUnits.cpp
 *
 *  Created on: 2016-4-12
 *      Author: dawx62fac
 */

#include "LogicCmdUnits.h"
#include <stdexcept>

//从概率数组中，按照概率,随机抽取结果
static void TurnLuckTable(int * prates, int len, int & target);

////////////////////////////////////////////////////////////////////////////////////////
PreSummerUnit::PreSummerUnit(unsigned uid, unsigned type)
	: m_nUid(uid)
	, m_bSave(false)
{
	m_type = type;
	if(m_type == 1)
	{
		m_bts = CONFIG_PRE_SUMMER2_BEGIN_TS;
		m_ets = CONFIG_PRE_SUMMER2_END_TS;
		m_ver = CONFIG_PRE_SUMMER2_VERSION;
		m_nat = NAT_PRE_SUMMER2;
	}
	else if(m_type == 2)
	{
		m_bts = CONFIG_PRE_SUMMER3_BEGIN_TS;
		m_ets = CONFIG_PRE_SUMMER3_END_TS;
		m_ver = CONFIG_PRE_SUMMER3_VERSION;
		m_nat = NAT_PRE_SUMMER3;
	}
	else
	{
		m_bts = CONFIG_PRE_SUMMER_BEGIN_TS;
		m_ets = CONFIG_PRE_SUMMER_END_TS;
		m_ver = CONFIG_PRE_SUMMER_VERSION;
		m_nat = NAT_PRE_SUMMER;
	}
	CLogicSecinc logicSecinc;
	int ret = logicSecinc.GetSecinc(m_nUid, m_nat, m_jsonData);
	if (R_ERR_NO_DATA == ret)
	{
		m_jsonData["id"] = m_nat;

		for (int i = 0; i < EXCHANGE_ITEMS; i++)
		{
			m_jsonData["a"][i] = 0;
		}

		//积分使用量
		m_jsonData["b"] = 0;
		m_jsonData["v"] = GetVersionCfg();

		m_bSave = true;
	}
	else
	{
		if (ret != R_SUCCESS)
		{
			throw std::runtime_error("get_new_active_data_error");
		}

		//
		unsigned versionCfg = GetVersionCfg();
		if (m_jsonData["v"].asInt() != (int)versionCfg)
		{
			for (int i = 0; i < EXCHANGE_ITEMS; i++)
			{
				m_jsonData["a"][i] = 0;
			}

			m_jsonData["b"] = 0;
			m_jsonData["v"] = versionCfg;

			m_bSave = true;
		}
	}
}

unsigned PreSummerUnit::GetVersionCfg()
{
	unsigned nVersion = 0;
	if (! Config::GetUIntValue(nVersion, m_ver))
	{
		throw std::runtime_error("can't_get_version_cfg");
	}

	return nVersion;
}
bool PreSummerUnit::IsActiving(unsigned nTime)
{
	unsigned beginTime = 0;
	unsigned endTime = 0;

	if (Config::GetUIntValue(beginTime, m_bts)
		&& Config::GetUIntValue(endTime, m_ets))
	{
		//
		if (beginTime == 0 || endTime == 0)
		{
			return false;
		}

		if (endTime < beginTime)
		{
			error_log("Active time config error");
			throw std::runtime_error("Active_time_config_error");
		}

		//活动时间校验
		if (nTime < beginTime ||  nTime > endTime)
		{
			return false;
		}

		return true;
	}

	return false;
}

void PreSummerUnit::Exchange(UserWrap& userWrap, unsigned id, Json::Value& result)
{
	if (id < 1 || id > EXCHANGE_ITEMS)
	{
		throw std::runtime_error("id_params_error");
	}

	if (m_jsonData["a"][id - 1].asInt() != 0)
	{
		throw std::runtime_error("already_exchange");
	}

	//oulong modify 20160801
	/*
	 * 充值1钻石得1积分   每1000积分可以兑换一个9级宝石  一共可以兑换三种 活动期间 每种兑换1次
	 * 改成 ==>
	 * 充值1钻石得1积分  还是3种物品，活动期间每种可以兑换1次，
	 * 第一次兑换的物品需要1000积分，
	 * 第二次兑换的物品需要2000积分，
	 * 第三次兑换的物品需要2500积分
	 */
	int cnt = 0;
	for (int i = 1; i <= EXCHANGE_ITEMS; i++)
	{
		if (m_jsonData["a"][i - 1].asInt() != 0)
		{
			++cnt;
		}
	}

	//todo 获取配置
	XMLPreSummerItem& item = DataIns()->GetPreSummerItem(id, m_type);
	unsigned nNeedPoint = DataIns()->GetPreSummerCost(cnt, m_type);

	int usePoint = m_jsonData["b"].asInt();
	int surplus = GetSurplusPoint(userWrap);
	if (surplus < (int)nNeedPoint)
	{
		throw std::runtime_error("not_enough_recharge_point");
	}

	//todo 发放物品
	const char* reason = "Pre_summer_activity_op";
	CLogicEquipment logicEquipment;
	int ret = logicEquipment.AddOneItem(m_nUid, item.equip.id
			, item.equip.cnt, reason, result["equipment"], true, item.equip.ch, item.equip.quality);
	if (ret != R_SUCCESS)
	{
		throw std::runtime_error("Add_equip_item_failed");
	}

	m_jsonData["a"][id - 1] = 1;
	//
	m_jsonData["b"] = usePoint + nNeedPoint;

	result["newAct"] = m_jsonData;
	result["surplus"] = surplus - nNeedPoint;

	Save();
}

void PreSummerUnit::GetData(UserWrap& userWrap, Json::Value& result)
{
	if (m_bSave)
	{
		result["newAct"] = m_jsonData;
		Save();
	}

	result["surplus"] = GetSurplusPoint(userWrap);
}

unsigned PreSummerUnit::GetSurplusPoint(UserWrap& userWrap)
{
	int nTotal = userWrap.GetRechargePoint(
				Config::GetIntValue(m_bts)
			  , Config::GetIntValue(m_ets));
	int usePoint = m_jsonData["b"].asInt();
	int surplus = nTotal - usePoint;

	return surplus < 0 ? 0 : surplus;
}


void PreSummerUnit::Save()
{
	CLogicSecinc logicSecinc;
	int ret = logicSecinc.SetOneSecinc(m_nUid, m_jsonData);
	if (ret !=  R_SUCCESS)
	{
		throw std::runtime_error("Save_data_failed");
	}
}

CDataXML* PreSummerUnit::DataIns()
{
	CDataXML *dataxml = CDataXML::GetCDataXML();
	if (NULL == dataxml)
	{
		error_log("get dataXML error uid=%d", m_nUid);
		std::runtime_error("get_data_xml_error");
	}

	return dataxml;
}
//-------------------------------------------------------------------
LordUnit::LordUnit(unsigned uid)
	: m_nUid(uid)
{
	CLogicSecinc logicSecinc;
	int ret = logicSecinc.GetSecinc(m_nUid, NAT_LORDS, m_jsonData);
	if (R_ERR_NO_DATA == ret)
	{
		m_jsonData["id"] = NAT_LORDS;
		m_jsonData["time"] = 0;
		m_jsonData["a"] = Json::arrayValue;
	}
	else
	{
		if (ret != R_SUCCESS)
		{
			throw std::runtime_error("get_new_active_data_error");
		}

	}
}

void LordUnit::Save()
{
	CLogicSecinc logicSecinc;
	int ret = logicSecinc.SetOneSecinc(m_nUid, m_jsonData);
	if (ret !=  R_SUCCESS)
	{
		throw std::runtime_error("Save_data_failed");
	}
}

int LordUnit::HttpRequest(const std::string& action, const std::string& data, Json::Value& result)
{
	string url = "action=" + action;
	if (data.size() > 0)
	{
		url.append("&data=").append(Crypt::UrlEncode(data));
	}

	CLogicAllServerBaseMatch logicBaseMatch;
	int ret = logicBaseMatch.RequestBaseMatch(url, result, CONFIG_ALLSERVER_LORDS_CGI, true);
	return ret;
}


void LordUnit::Worship(int id, int type, Json::Value& result)
{
	unsigned time = m_jsonData["time"].asInt();
	if (! Time::IsToday(time))
	{
		m_jsonData["a"].clear();
	}

	//膜拜是否超过次数
	if (m_jsonData["a"].size() >= WORSHIP_CNT)
	{
		error_log("Over_worship_cnt. uid=%u", m_nUid);
		throw std::runtime_error("Over_worship_cnt");
	}

	//是否已经膜拜过该尊主
	for (size_t i = 0; i < m_jsonData["a"].size(); ++i)
	{
		int save_id = m_jsonData["a"][i]["id"].asInt();
		int save_type = m_jsonData["a"][i]["type"].asInt();

		if (save_id == id && save_type == type)
		{
			error_log("Already_worship. uid=%u,id=%d&tye=%d", m_nUid, id, type);
			throw std::runtime_error("Already_worship");
		}
	}

	Json::Value jsonReqData;
	jsonReqData["id"] = id;
	jsonReqData["uid"] = m_nUid;
	jsonReqData["type"] = type;
	int ret = HttpRequest("Worship", Json::ToString(jsonReqData), result);
	if (ret != R_SUCCESS)
	{
		throw std::runtime_error("request_data_error");
	}

	jsonReqData.removeMember("uid");
	m_jsonData["a"].append(jsonReqData);
	m_jsonData["time"] = Time::GetGlobalTime();

	result["worship"] = m_jsonData;

	Save();

	//
	ProvideReward(result["reward"]);
}

ItemAdd LordUnit::GetReward()
{
#if 0
	const unsigned probTb[] = {1,199,250,300,250};
	const unsigned sumProb = 1000;

	const unsigned rewardId[] = {4020, 50053, 11112, 4004, 4452};
	const unsigned rewardCnt[] = {1, 2, 1, 8, 3};

	int randVal = Math::GetRandomInt(sumProb);
	int index = -1;
	for (int i = 0; i < (int)(sizeof(probTb) / probTb[0]); ++i)
	{
		if (probTb[i] > randVal)
		{
			index = i;
			break;
		}
		randVal -= probTb[i];
	}

	if (index < 0)
	{
		throw std::runtime_error("produce_reward_id_error");
	}

	ItemAdd item;
	item.eqid = rewardId[index];
	item.count = rewardCnt[index];
#endif
	ItemAdd item;
	item.eqid = 50093;
	item.count = 1;
	return item;
}

void LordUnit::ProvideReward(Json::Value& result)
{
	//todo 发放奖励
	ItemAdd item = GetReward();
	const char* reason = "lord_worship_reward_op";
	CLogicEquipment logicEquipment;
	int ret = logicEquipment.AddOneItem(m_nUid, item.eqid, item.count, reason, result["equipment"], true);
	if (ret != R_SUCCESS)
	{
		error_log("Provied lord rank reward error! uid=%d, ret=%d", m_nUid, ret);
	}
}

//----------------------------------------------------------------
TemplePrayUnit::TemplePrayUnit(const UserWrap& user)
	: BaseCmdUnit(user.Id())
{
	CLogicSecinc logicSecinc;
	int ret = logicSecinc.GetSecinc(m_nUid, NAT_TEMPLE_PRAY, m_jsonData);
	if (R_ERR_NO_DATA == ret)
	{
		m_jsonData["id"] = NAT_TEMPLE_PRAY;
		m_jsonData["time"] = 0;  //祈福时间
		m_jsonData["a"] = 0;     //祈福次数
	}
	else
	{
		if (ret != R_SUCCESS)
		{
			throw std::runtime_error("get_new_active_data_error");
		}

	}
}

int TemplePrayUnit::Pray(UserWrap& user, const PrayParams& params, Json::Value &result)
{
	unsigned time = m_jsonData["time"].asInt();
	if (! Time::IsToday(time))
	{
		m_jsonData["a"] = 0;
	}

	int cnt = m_jsonData["a"].asInt();

	XMLTempleItem item = DataXmlPtr()->GetTemplePrayItem(params.Id());
	if (params.BuildId() < item.level)
	{
		throw std::runtime_error("build_level_not_enough");
	}

	int nFreeCnt = user.VipLevel() >= VIP_GET_LEVEL ? FREE_VIP_GET_CNT : FREE_COMMON_GET_CNT;
	if (cnt >= nFreeCnt)
	{
#ifdef SG_USE_CASH
		user.CostAsset(0, item.cost, "Temple_pray_op", result["cost"]);
#else
		this->UseEquips(2026, params.Ud(), item.cost, "Temple_pray_op");
		result["equip_cost"] = item.cost;
#endif
	}

	//发放物品
	int index = item.GetRandomEquipIndex();
	GiftEquipment equip = item.equips[index];

	if (R_SUCCESS != CLogicEquipment().AddOneItem(m_nUid
			, equip.id, equip.cnt, "Temple_pray_op"
			, result["equipment"], equip.ch, equip.quality))
	{
		error_log("Temple_pray_op uid: %u, id:%u, gift: %u", m_nUid, params.Id(), equip.id);
		throw std::runtime_error("provide_item_error");
	}

	//save
	m_jsonData["time"] = Time::GetGlobalTime();
	m_jsonData["a"] = ++cnt;

	result["prayid"] = index;
	result["data"] = m_jsonData;

	Save();

	return 0;
}

//-----------------------------------
//开区充值
NewRechargeUnit::NewRechargeUnit(unsigned uid)
	: BaseCmdUnit(uid)
{
	CLogicSecinc logicSecinc;
	int ret = logicSecinc.GetSecinc(m_nUid, NAT_NEW_RECHARGE, m_jsonData);
	if (R_ERR_NO_DATA == ret)
	{
		m_jsonData["id"] = NAT_NEW_RECHARGE;
		m_jsonData["a"] = Json::arrayValue;     //祈福次数
		m_jsonData["a"].resize(BAG_TYPE_CNT);
		for (int  i = 0; i < BAG_TYPE_CNT; ++i)
		{
			m_jsonData["a"][i] = 0;
		}
	}
	else
	{
		if (ret != R_SUCCESS)
		{
			throw std::runtime_error("get_new_active_data_error");
		}
	}
}

bool NewRechargeUnit::IsActiving(unsigned time)
{
	unsigned openTs = Config::GetIntValue("open_ts");
	unsigned endTs = openTs + 30 * 24 * 3600; //一个月

	return (time >= openTs) && (time < endTs);
}

void NewRechargeUnit::GetRewardBagAction(const UserWrap& userWrap, unsigned id, Json::Value& result)
{
	if (! IsActiving(Time::GetGlobalTime()))
	{
		throw std::runtime_error("out_activing_time");
	}

	if (id < 1 || id  > BAG_TYPE_CNT)
	{
		error_log("id: %d, uid=%u", id, m_nUid);
		throw std::runtime_error("params_id_error");
	}

	if (m_jsonData["a"][id - 1].asInt() > 0)
	{
		throw std::runtime_error("already_get_recharge_reward");
	}

	XMLNewRechargeRewardItem item = DataXmlPtr()->GetNewRechargeRewardItem(id);
	if (userWrap.TotalRecharge() < item.needRecharge)
	{
		throw std::runtime_error("not_enough_recharge");
	}

	//发放物品
	ProvideReward(id, item, result);

	m_jsonData["a"][id - 1] = 1;

	result["newrecharge"] = m_jsonData;

	Save();
}

void NewRechargeUnit::ProvideReward(unsigned id, XMLNewRechargeRewardItem& item, Json::Value& result)
{
	/////////////////////////////////////////////////////////////////////////
	std::vector<ItemAdd> equips;
	for (int i = 0; i < XML_DATA_NEW_RECHARGE_REWARD_ITEMS; ++i)
	{
		if (item.items[i].IsEquip())
		{
			ItemAdd itemAdd;
			itemAdd.eqid = item.items[i].m_nId;
			itemAdd.count = item.items[i].m_nCnt;
			itemAdd.q = item.items[i].m_nQuality;
			itemAdd.ch = item.items[i].m_nCh;
			itemAdd.reason = "New_recharge_get_reward_op";

			equips.push_back(itemAdd);
		}
	}

	if (equips.size() > 0)
	{
		for (size_t i = 0; i < equips.size(); ++i)
		{
			equips[i].reason = "New_recharge_get_reward_op";
		}


		AddEquips(equips, result);
	}

	std::vector<std::string> vHeros = item.GetHeros();
	if (vHeros.size() > 0)
	{
		std::vector<std::string> vReasons;
		for (size_t i = 0; i < vHeros.size(); ++i)
		{
			vReasons.push_back("New_recharge_get_reward_op");
		}

		CLogicHero logicHero;
		if (0 != logicHero.AddHeros(m_nUid, vHeros, vReasons, result["heros"]))
		{
			error_log("add heros error. uid=%u,id=%u", m_nUid, id);
		}

		//已经发放装备了，此处不抛异常了
	}
}

GroupBuyDailyUnit::GroupBuyDailyUnit(unsigned uid, const UserWrap& user)
	: BaseCmdUnit(uid)
{
	user.GetUserStats(m_jsonData);

	//开始从注册时间起 15天为一轮
	unsigned ver = m_jsonData["tgver"].asInt();
	unsigned now = Time::GetGlobalTime();
	int  intervalDays =  CTime::GetDayInterval(ver, now);
	intervalDays = intervalDays > 0 ? intervalDays : 0;
	//新的一轮
	if (intervalDays > 15)
	{
		m_jsonData["tgver"] = now; //tgver 版本 时间戳
		m_jsonData["tgrew"].clear();
		m_jsonData["tgrew"].resize(GET_ITEMS);
		for (int i = 0; i < GET_ITEMS; ++i) //领取标记
		{
			m_jsonData["tgrew"][i] = 0;
		}
		m_jsonData["ttg"] = 0; //当天是否购买  前端重置
		m_jsonData["tgp"] = 0; //积分
	}
}

void GroupBuyDailyUnit::BuyAction(UserWrap& user, Json::Value& result)
{
	if (m_jsonData["ttg"].asInt() > 0 )
	{
		throw std::runtime_error("already_buy_today");
	}
	//////////////////////////////////////////////////////////////
	DataXMLGroupBuyDailyBuyItem buyItem;
	DataXmlPtr()->GetGroupBuyDailyBuyTtem(buyItem);

	std::string reason = "groupbuydaily_buy_op";
	user.CostAsset(buyItem.price, 0, reason, result["cost"]);

	//积分计算
	int tgp = m_jsonData["tgp"].asInt();
	m_jsonData["tgp"] = tgp + POINTS_ONCE;

	//////////////////////////////////////////////////////////////
	m_jsonData["ttg"] = 1;

	//保存标记
	user.SetUserStats(m_jsonData);

	//发放物品
	std::vector<ItemAdd> equips;
	for (int i = 0; i < DataXMLGroupBuyDailyBuyItem::EQUIP_ITEMS; ++i)
	{
		if (buyItem.items[i].IsEquip())
		{
			equips.push_back(Equip2ItemAdd(buyItem.items[i], reason));
		}
	}

	AddEquips(equips, result);

	//资源
	user.AddResource(buyItem.rs[0], buyItem.rs[1]
	     , buyItem.rs[2], buyItem.rs[3], reason, result["resource"]);

	//
	result["info"]["tgp"] = m_jsonData["tgp"];
	result["info"]["ttg"] = m_jsonData["ttg"];
	result["info"]["tgver"] = m_jsonData["tgver"];
	result["info"]["tgrew"] = m_jsonData["tgrew"];
}

void GroupBuyDailyUnit::GetRewardAction(unsigned index, UserWrap& user, Json::Value& result)
{
	if (index >= 4)
	{
		throw std::runtime_error("params_index_error");
	}

	if (m_jsonData["tgrew"][index].asInt() > 0)
	{
		throw std::runtime_error("already_get_reward");
	}

	int id = -1;
	if (index >= 0 && index < 3)
	{
		id = index + 1;
	}
	else
	{
		//
		unsigned ver = m_jsonData["tgver"].asInt();
		unsigned registerTime = user.RegisterTime();
		int intervalDays =  CTime::GetDayInterval(registerTime, ver);
		intervalDays = intervalDays > 0 ? intervalDays : 0;
		id = (intervalDays / 15) % 3 + 4;
	}

	//获取设置
	std::string reason = "groupbuydaily_buy_get_reward_op";
	DataXMLGroupBuyDailyReward reward;
	DataXmlPtr()->GetGroupBuyDailyBuyReward(id, reward);

	if (m_jsonData["tgp"].asInt() < (int)reward.point)
	{
		throw std::runtime_error("not_enough_point");
	}

	//
	m_jsonData["tgrew"][index] = 1;
	//保存标记
	user.SetUserStats(m_jsonData);

	AddGiftEquips(reward.items, DataXMLGroupBuyDailyReward::EQUIP_ITEMS, reason, result);

	//
	result["info"]["tgp"] = m_jsonData["tgp"];
	result["info"]["ttg"] = m_jsonData["ttg"];
	result["info"]["tgver"] = m_jsonData["tgver"];
	result["info"]["tgrew"] = m_jsonData["tgrew"];
}

LittleRechargeUnit::LittleRechargeUnit(const UserWrap& user)
	: BaseCmdUnit(user.Id())
{
	//fcharge 字段表示是否领取 前端重置
	user.GetUserStats(m_jsonData);
}

void LittleRechargeUnit::GetReward(UserWrap& user, Json::Value& result)
{
	if (m_jsonData["fcharge"].asInt() > 0)
	{
		throw std::runtime_error("already_get_reward");
	}

	unsigned temp_zoneid = Config::GetZoneByUID(m_nUid);
	unsigned zoneid = MainConfig::GetMergedDomain(temp_zoneid);

	DataXMLLittleRechargeZone zoneCfg;
	DataXmlPtr()->GetLittleRechargeReward(OpenPlatform::IsDS(), zoneid, zoneCfg);

	unsigned nTimeStart = CTime::GetDayBeginTime(Time::GetGlobalTime());
	unsigned nTimeEnd = nTimeStart + 24*60*60;
	unsigned rechargePoint = user.GetRechargePoint(nTimeStart, nTimeEnd);
	unsigned neePoint = OpenPlatform::IsDS() ? 50 : 100;
	if (rechargePoint < neePoint)
	{
		throw std::runtime_error("not_enough_recharge");
	}

	/////////////////////////////////////////////////////////////////////
	m_jsonData["fcharge"] = 1;
	user.SetUserStats(m_jsonData);
	result["info"]["fcharge"] = m_jsonData["fcharge"];

	std::string reason = "little_reward_op";

	unsigned now_ts = Time::GetGlobalTime();
	if (now_ts >= COUNTRY_DAY_REWARD_MONEY_BEGIN_TS && now_ts <= COUNTRY_DAY_REWARD_MONEY_END_TS)    //国庆期间奖励翻倍
	{
		for (int i = 0; i < DataXMLLittleRechargeZone::EQUIP_ITEMS; ++i)
		{
			zoneCfg.items[i].Double();
		}
	}

	AddGiftEquips(zoneCfg.items, DataXMLLittleRechargeZone::EQUIP_ITEMS, reason, result);
}

DailyRewardUnit::DailyRewardUnit(const UserWrap& user)
	: BaseCmdUnit(user.Id())
{
	//donl
	user.GetUserStats(m_jsonData);
}

int DailyRewardUnit::GetReward(UserWrap& user, const BaseCmdParams& params, Json::Value& result)
{
	int cnt = m_jsonData["donl"].asInt();
	if (cnt > 15)
	{
		throw std::runtime_error("over_get_reward_cnt");
	}

	m_jsonData["donl"] = ++cnt;
	m_jsonData["enegyots"] = 0;
	user.SetUserStats(m_jsonData);

	user.AddGCBase(10, "DailyRewardUnit", result);
	result["donl"] = m_jsonData["donl"];
	result["enegyots"] = m_jsonData["enegyots"];

	return R_SUCCESS;
}


AthleticsRankUnit::AthleticsRankUnit(const UserWrap& user)
	: BaseCmdUnit(user.Id())
{
	//rmr
	/*
	 * obj.rank = this._rankMatchReward.rank.value;
	 * obj.coins = this._rankMatchReward.coins.value;
	 * obj.bs = this._rankMatchReward.bs.value;
	 * obj.ts = this._rankMatchReward.ts.value;
	 */
	user.GetUserStats(m_jsonData);
}

int AthleticsRankUnit::GetReward(UserWrap& user, const BaseCmdParams& params,  Json::Value& result)
{
	//coinList:Array = 		[200, 	170, 	140, 	110, 	90, 	70, 	50, 	40, 	30, 	20, 	15, 	10, 	5, 		0];
	//prosperList:Array = 	[15000, 12000, 	10000, 	8000, 	7000, 	6000, 	5000, 	4000, 	3000, 	2000, 	1500, 	1000, 	500, 	0];
	//rankList:Array = 		[1, 	2, 		3, 		4, 		11, 	31, 	51, 	101, 	151, 	201, 	251, 	301, 	501, 	1000];
	if (! m_jsonData["rmr"].isMember("rank"))
	{
		throw std::runtime_error("can't_get_reward");
	}

	int nCoins = m_jsonData["rmr"]["coins"].asInt();
	int nProsper = m_jsonData["rmr"]["bs"].asInt();

	m_jsonData["rmr"].clear();
	m_jsonData["rmr"] = Json::objectValue;

	user.SetUserStats(m_jsonData);

	//
	std::string reason = "Athletics_rank_get_reward_op";
	user.AddProsper(nProsper, reason, result);
	//修改金币

	int ret = CLogicPay().ChangePay(m_nUid, 0, nCoins, reason);
	if (ret != 0)
	{
		error_log("get_sign_in_reward add coins failed. uid=%d, ret=%d", m_nUid, ret);
		throw std::runtime_error("issue_coins_failed");
	}
	result["coins"] = nCoins;
	result["rmr"] = m_jsonData["rmr"];

	return R_SUCCESS;
}

///////////////////////////////////////
MonthGiftParams::MonthGiftParams(const Json::Value& jsonData)
	: BaseCmdParams(jsonData)
{
	index_ = ValueAsUInt("index");
	if (index_ >= DataXMLMonthGiftBagZone::EQUIP_ITEMS)
	{
		throw std::runtime_error("params_index_out_range");
	}
}

unsigned MonthGiftParams::Index() const
{
	return index_;
}

MonthGiftBagUnit::MonthGiftBagUnit(const UserWrap& user)
	: BaseCmdUnit(user.Id())
{
	//
	user.GetUserStats(m_jsonData);

	if (m_jsonData["dwv"].asUInt() != GetVersionCfg(CONFIG_MONTH_LIBAO_VER))
	{
		m_jsonData["dw"].clear();
		m_jsonData["dw"].resize(DataXMLMonthGiftBagZone::EQUIP_ITEMS);

		for (int i = 0; i < DataXMLMonthGiftBagZone::EQUIP_ITEMS; ++i)
		{
			m_jsonData["dw"][i] = 0;
		}

		m_jsonData["dwv"] = GetVersionCfg(CONFIG_MONTH_LIBAO_VER);
	}
}

int MonthGiftBagUnit::GetReward(UserWrap& user, const MonthGiftParams& params, Json::Value& result)
{
	//是否在活动期
	unsigned now = Time::GetGlobalTime();
	if (! IsActiving(now, CONFIG_MONTH_LIBAO_BEGIN_TS, CONFIG_MONTH_LIBAO_END_TS))
	{
		throw std::runtime_error("over_activing");
	}

	if (m_jsonData["dw"][params.Index()].asInt() > 0)
	{
		throw std::runtime_error("already_get_reward");
	}


	PlatformType pltType = OpenPlatform::GetType();

	unsigned temp_zoneid = Config::GetZoneByUID(m_nUid);
	unsigned zoneid = MainConfig::GetMergedDomain(temp_zoneid);
	unsigned nEquipid = DataXmlPtr()->GetMonthGiftBagEquipId(pltType == PT_4399, zoneid, params.Index());

	//
	std::string reason = "MonthGiftBag_op";
	unsigned diamond = GetCostDiamond(params.Index());
	if (R_SUCCESS != user.CostAsset(diamond, 0, reason, result["cost"]))
	{
		error_log("Cost_diamond_error");
		return R_ERROR;
	}

	m_jsonData["dw"][params.Index()] = 1;
	user.SetUserStats(m_jsonData);

	//发放礼包
	CLogicEquipment logicEquipment;
	int ret = logicEquipment.AddOneItem(m_nUid, nEquipid, 1, reason, result["equipments"], true);
	if (ret != R_SUCCESS)
	{
		return ret;
	}

	result["info"]["dw"] = m_jsonData["dw"];
	result["info"]["dwv"] = m_jsonData["dwv"];

	return R_SUCCESS;
}

unsigned MonthGiftBagUnit::GetCostDiamond(unsigned index)
{
	PlatformType pltType = OpenPlatform::GetType();
	if (pltType == PT_4399)
	{
		return 48;
	}
	else
	{
		if (index >= DataXMLMonthGiftBagZone::EQUIP_ITEMS)
		{
			throw std::runtime_error("[MonthGiftBagUnit::GetCostDiamond]_params_error");
		}

		const static unsigned costTb[DataXMLMonthGiftBagZone::EQUIP_ITEMS]
		                             	 	 	 	 	= {288, 3888, 9888};
		return costTb[index];
	}
}

///////////////////////////
KingdomSelectParams::KingdomSelectParams(const Json::Value& jsonData)
	: BaseCmdParams(jsonData)
{
	kingdom_ = ValueAsUInt("kingdom");
	if (kingdom_ < 1 || kingdom_ > 3)
	{
		throw std::runtime_error("kingdom_params_error");
	}

	type_ = ValueAsUInt("type");
}


KingdomSelectUnit::KingdomSelectUnit(const UserWrap& user)
	: BaseCmdUnit(user.Id())
{
	user.GetUserStats(m_jsonData);
}

int KingdomSelectUnit::Select(UserWrap& user, const KingdomSelectParams& params, Json::Value& result)
{
	/*
	if (m_jsonData["nb"].asUInt() > 0)
	{
		throw std::runtime_error("already_select_kingdom");
	}
	*/

	user.SetKingdom(params.Kingdom(), result["info"]);

	m_jsonData["nb"] = 1;
	user.SetUserStats(m_jsonData);

	int nCoins = GetAddCoins(user.Id(), params.Type(), params.Kingdom());
	if (nCoins > 0)
	{
		std::string reason = "select_kingdom_op";
		int ret = CLogicPay().ChangePay(user.Id(), 0, nCoins, reason);
		if (ret != 0)
		{
			error_log("get_sign_in_reward add coins failed. uid=%d, ret=%d", user.Id(), ret);
			throw std::runtime_error("issue_coins_failed");
		}
		result["coins"] = nCoins;
	}

	result["info"]["nb"] = m_jsonData["nb"];

	//
	return R_SUCCESS;
}

int KingdomSelectUnit::GetAddCoins(unsigned uid, unsigned type, unsigned kingdom)
{

	if (type > 0)
	{
#ifdef SG_16_VER
		unsigned nVal = uid % 3;
#else
		unsigned nVal = uid % 5;
#endif
		unsigned nSelect = 0;
		if (nVal == 0) nSelect = 1;
		else if(nVal == 1) nSelect = 2;
		else {
			nSelect = 3;
		}

		return nSelect == kingdom ? 100 : 0;
	}
	else
	{
		return (uid % 3 + 1) == kingdom ? 100 : 0;
	}

}

//////////////////////////////////
CombinedShopParams::CombinedShopParams(const Json::Value& jsonData)
	: BaseCmdParams(jsonData)
{
	index_ = ValueAsUInt("index");
	if (index_ >= DataXMLCombinedShop::ITEMS_CNT)
	{
		throw std::runtime_error("params_index_error");
	}

	ValueAsArray("equips", equips_);
	if (equips_.size() != 3)
	{
		throw std::runtime_error("equips_cnt_error");
	}
}

CombinedShopUnit::CombinedShopUnit(const UserWrap& user)
	: BaseCmdUnit(user.Id())
{
	CLogicSecinc logicSecinc;
	int ret = logicSecinc.GetSecinc(m_nUid, NAT_COMBINED_SHOP, m_jsonData);
	if (R_ERR_NO_DATA == ret)
	{
		m_jsonData["id"] = NAT_COMBINED_SHOP;
		m_jsonData["b"] = Time::GetGlobalTime();
		m_jsonData["a"].resize(DataXMLCombinedShop::ITEMS_CNT);
		for (int i = 0; i < DataXMLCombinedShop::ITEMS_CNT; ++i)
		{
			m_jsonData["a"][i] = 0;
		}
	}
	else
	{
		if (ret != R_SUCCESS)
		{
			throw std::runtime_error("get_new_active_data_error");
		}

		unsigned nTime = m_jsonData["b"].asUInt();
		if (! Time::IsToday(nTime))
		{
			m_jsonData["b"] = Time::GetGlobalTime();
			m_jsonData["a"].clear();
			m_jsonData["a"].resize(DataXMLCombinedShop::ITEMS_CNT);
			for (int i = 0; i < DataXMLCombinedShop::ITEMS_CNT; ++i)
			{
				m_jsonData["a"][i] = 0;
			}
		}
	}
}

int CombinedShopUnit::Buy(UserWrap& user, const CombinedShopParams& params,  Json::Value& result)
{
	DataXMLCombinedShopItem item;
	DataXmlPtr()->GetCombinedShopEquipItem(params.Index(), item);

	int nBuyCnt = m_jsonData["a"][params.Index()].asUInt();
	if (nBuyCnt >= item.limit)
	{
		throw std::runtime_error("get_limit_cnt");
	}

	std::string reason = "Combine_shop_op";
	//发放的物品
	std::vector<unsigned> vEquips = params.Equips();
	std::vector<ItemAdd> vItemAdds;
	for (size_t i = 0; i < vEquips.size(); ++i)
	{
		ItemAdd itemAdd;
		itemAdd.eqid = vEquips[i];
		itemAdd.count = item.GetEquipCnt(vEquips[i]);
		itemAdd.reason = reason;
		vItemAdds.push_back(itemAdd);
	}

	//扣钻石
	if (R_SUCCESS != user.CostAsset(item.cost, 0, reason, result["cost"]))
	{
		error_log("Cost_diamond_error");
		return R_ERROR;
	}

	//存记录档
	m_jsonData["b"] = Time::GetGlobalTime();
	m_jsonData["a"][params.Index()] = nBuyCnt + 1;
	Save();

	//发放礼包
	CLogicEquipment logicEquipment;
	int ret = logicEquipment.AddItems(m_nUid, vItemAdds, result["equipments"], true);
	if (ret != R_SUCCESS)
	{
		return ret;
	}

	//结果返回
	result["info"] = m_jsonData;

	return R_SUCCESS;
}
//////////////////////////////////////
NewerAdvanceParams::NewerAdvanceParams(const Json::Value& jsonData)
	: BaseCmdParams(jsonData)
{
	build_level_ = ValueAsUInt("bd_level");
}

NewerAdvanceUnit::NewerAdvanceUnit(const UserWrap& user)
	: BaseCmdUnit(user.Id())
{
	user.GetUserStats(m_jsonData);
}

int NewerAdvanceUnit::Get(UserWrap& user, const NewerAdvanceParams& params,  Json::Value& result)
{
	DataXMLNewerAdvanceItem item;
	unsigned nTrl = m_jsonData["tlr"].asUInt();
	DataXmlPtr()->GetNewerAdvanceItem(nTrl + 1, item);

	if (params.BuildLevel() < item.level)
	{
		throw std::runtime_error("level_not_enough");
	}

	//存档
	m_jsonData["tlr"] = nTrl + 1;
	result["info"]["tlr"] =  m_jsonData["tlr"];
	user.SetUserStats(m_jsonData);
	//
	if (item.exp > 0)
	{
		user.AddExp(item.exp, "NewerAdvanceUnit", result["user"]);
	}

	if (item.gold > 0)
	{
		std::string reason = "newer_advence_op";
		int ret = CLogicPay().ChangePay(m_nUid, 0, item.gold, reason);
		if (ret != 0)
		{
			error_log("NewerAdvanceUnit add coins failed. uid=%d, ret=%d", m_nUid, ret);
			throw std::runtime_error("issue_coins_failed");
		}
		result["coins"] = item.gold;
	}
	//

	return R_SUCCESS;
}

////////////////////////////////////////////////////////////////////////////////////////
TreasureHuntExchangeParams::TreasureHuntExchangeParams(const Json::Value& jsonData)
	: BaseCmdParams(jsonData)
{
	index_ = ValueAsInt("index");
	is_point_ = ValueAsInt("is_point") > 0;
}

TreasureHuntUnit::TreasureHuntUnit(const UserWrap& user)
	: BaseCmdUnit(user.Id())
{
	if (! IsOpen())
	{
		throw std::runtime_error("out_activity_peroid");
	}

	user.GetUserStats(m_jsonData);

//	Json::GetUInt(stats,"trhs",id);
//	Json::GetUInt(stats,"trpt",point);
//	Json::GetUInt(stats,"trhj",jade);
//	Json::GetUInt(stats,"trhg",gold);
//	Json::GetUInt(stats,"trhd",diamond);
}

bool TreasureHuntUnit::IsOpen() const
{
	if(Time::GetGlobalTime() < Config::GetIntValue(CONFIG_TREASURE_BEGIN_TS)
		|| Time::GetGlobalTime() > Config::GetIntValue(CONFIG_TREASURE_END_TS))
	{
		return false;
	}

	return true;
}

int TreasureHuntUnit::Exchage(UserWrap& user
		, const TreasureHuntExchangeParams& params
		, Json::Value& result)
{
	DataXMLTreasureHuntExchangeItem item;
	DataXmlPtr()->GetTreasureHuntExchangeItem(params.Index(), params.IsPoint(), item);

	//玉石的数目由心的数量转换而来  5颗心=1一个玉石!!!
	int ownVal =  params.IsPoint() ? m_jsonData["trpt"].asInt() : (m_jsonData["trhj"].asInt() / 5);
	if (ownVal < item.cost)
	{
		throw std::runtime_error("point_or_jade_not_enough");
	}

	if (params.IsPoint())
	{
		m_jsonData["trpt"] = ownVal - item.cost;
	}
	else
	{
		m_jsonData["trhj"] = m_jsonData["trhj"].asInt() - item.cost*5;
	}
	user.SetUserStats(m_jsonData);

	std::vector<ItemAdd> items;
	items.push_back(ItemAdd(item.id, item.count, "treasure_hunt_exchange_op"));
	AddEquips(items, result);

	result["info"]["trpt"] = m_jsonData["trpt"];
	result["info"]["trhj"] = m_jsonData["trhj"];

	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////
ChristmasParams::ChristmasParams(const Json::Value& jsonData)
	: BaseCmdParams(jsonData)
{
	id_ = ValueAsInt("id");
}

ChristmasUnit::ChristmasUnit(const UserWrap& user)
	: BaseCmdUnit(user.Id())
{
	if (! IsOpen())
	{
		throw std::runtime_error("out_activity_peroid");
	}

	user.GetUserStats(m_jsonStats_);

	//活动积分
	unsigned start = Config::GetIntValue(CONFIG_TREASURE_BEGIN_TS);
	unsigned end = Config::GetIntValue(CONFIG_ACTIVITY_GALLERY_END_TS);
	total_recharge_point_ = user.GetRechargePoint(start, end);

	bool isReset = false;
	unsigned nVersion = GetVersionCfg();
	if (m_jsonStats_["hzv"].asUInt() != GetVersionCfg())
	{
		m_jsonStats_["hlc"] = 0;  //玩家已使用分数
		m_jsonStats_["hzv"] = nVersion;
		m_jsonStats_["hlt"] = 0;  //cd

		isReset = true;
	}

	CLogicSecinc logicSecinc;
	int ret = logicSecinc.GetSecinc(m_nUid, NAT_SHENGDAN, m_jsonData);
	if (R_ERR_NO_DATA == ret)
	{
		m_jsonData["limit"] = Json::arrayValue;
	}
	else
	{
		if (ret != R_SUCCESS)
		{
			throw std::runtime_error("get_new_active_data_error");
		}

		if (isReset)
		{
			m_jsonData["limit"].clear();
			m_jsonData["limit"] = Json::arrayValue;
		}
	}
}

bool ChristmasUnit::IsOpen() const
{
	if(Time::GetGlobalTime() < Config::GetIntValue(CONFIG_ACTIVITY_GALLERY_BEGIN_TS)
		|| Time::GetGlobalTime() > Config::GetIntValue(CONFIG_ACTIVITY_GALLERY_END_TS))
	{
		return false;
	}

	std::string type = Config::GetValue(CONFIG_ACTIVITY_GALLERY_TYPE);
	if (type != std::string("egg"))
	{
		return false;
	}

	return true;
}

unsigned ChristmasUnit::GetVersionCfg() const
{
	unsigned nVersion = 0;
	if (! Config::GetUIntValue(nVersion, CONFIG_ACTIVITY_GALLERY_VER))
	{
		throw std::runtime_error("can't_get_version_cfg");
	}

	return nVersion;
}

unsigned ChristmasUnit::SurplusPoint() const
{
	unsigned use_point = m_jsonStats_["hlc"].asUInt();
	if (total_recharge_point_ > use_point)
	{
		return total_recharge_point_ - use_point;
	}
	else
	{
		return 0;
	}
}

int ChristmasUnit::Exchage(UserWrap& user, const ChristmasParams& params, Json::Value& result)
{
	DataXMLChristmasExtraItem item;
	unsigned id = params.Id();
	int index = id - 1;
	if (index < 0 || index >= DataXMLChristmas::EXTRA_ITEMS)
	{
		throw std::runtime_error("id_params_error");
	}
	DataXmlPtr()->GetChristmasExtraItem(params.Id(), item);

	int exchange_cnt = m_jsonData["limit"][index].asInt();
	if (item.limit > 0 && exchange_cnt >= item.limit)
	{
		throw std::runtime_error("exchagne_get_to_limit_cnt");
	}

	int suplus_point = SurplusPoint();
	if (suplus_point < item.point)
	{
		throw std::runtime_error("point_not_enough");
	}

	m_jsonStats_["hlc"] = m_jsonStats_["hlc"].asUInt() + item.point;
	//
	if (item.limit > 0)
	{
		m_jsonData["limit"][index] = exchange_cnt + 1;
	}

	Save();

	user.SetUserStats(m_jsonStats_);

	AddGiftEquips(item.item, "christmas_exchage_op", result);

	result["info"]["hlc"] = m_jsonStats_["hlc"];
	result["info"]["limit"] = m_jsonData["limit"];

	return 0;
}

void ChristmasUnit::ProductEquipItem(const DataXMLChristmasEgg& eggs, DataXMLChristmasEggItem& result)
{
	unsigned nTotal = 0;
	for (size_t i = 0; i < DataXMLChristmasEgg::ITEMS_CNT; ++i)
	{
		if (eggs.items[i].id > 0)
		{
			nTotal += eggs.items[i].rate;
		}
		else
		{
			break;
		}
	}

	if (nTotal == 0)
	{
		throw std::runtime_error("eggs_prob_weight_is_null");
	}

	int nRandom = Math::GetRandomInt(nTotal);

	for (size_t i = 0; i < DataXMLChristmasEgg::ITEMS_CNT; ++i)
	{
		if (nRandom < eggs.items[i].rate)
		{
			result = eggs.items[i];
			return ;
		}

		nRandom -= eggs.items[i].rate;
	}

	throw std::runtime_error("product_random_value_error");
}

int ChristmasUnit::KnockEgg(UserWrap& user, const ChristmasParams& params, Json::Value& result)
{
	DataXMLChristmasEgg item;
	unsigned id = params.Id();
	DataXmlPtr()->GetChristmasEggItem(id, item);

	if (item.point == 0)
	{
		int expire_time = m_jsonStats_["hlt"].asInt() + item.cold;
		if (expire_time > Time::GetGlobalTime())
		{
			throw std::runtime_error("need_cold");
		}
 	}
	else
	{
		int suplus_point = SurplusPoint();
		if (suplus_point < item.point)
		{
			throw std::runtime_error("point_not_enough");
		}
	}

	if (item.point == 0)
	{
		m_jsonStats_["hlt"] = Time::GetGlobalTime();
	}
	else
	{
		m_jsonStats_["hlc"] = m_jsonStats_["hlc"].asUInt() + item.point;
	}

	user.SetUserStats(m_jsonStats_);

	DataXMLChristmasEggItem egg_equip;
	ProductEquipItem(item, egg_equip);
	AddGiftEquips(egg_equip.item, "christmas_knock_egg_op", result);

	result["info"]["show"] = egg_equip.show;
	result["info"]["hlt"] = m_jsonStats_["hlt"];
	result["info"]["hlc"] = m_jsonStats_["hlc"];

	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////
PointCmdUnit::PointCmdUnit(const UserWrap& user,const std::string& type)
	: BaseCmdUnit(user.Id())
{
	if (! IsOpen(type))
	{
		throw std::runtime_error("out_activity_peroid");
	}

	//
	LoadUserGiftData(m_jsonData);

	m_jsonPoint_ = m_jsonData["pointreward"];

	unsigned nVersion = GetActivityVersion(CONFIG_PAYRANK_VERSION);
	if (m_jsonPoint_["v"].asInt() != nVersion)
	{
		m_jsonPoint_.clear();

		m_jsonPoint_["v"] = nVersion;
		m_jsonPoint_["lp"] = 0;
		m_jsonPoint_["tp"] = 0;
		m_jsonPoint_["cpbr"] = 0;
	}
}

bool PointCmdUnit::IsOpen(const std::string& type) const
{
	if(Time::GetGlobalTime() < Config::GetIntValue(CONFIG_PAYRANK_BEGIN_TS)
		|| Time::GetGlobalTime() > Config::GetIntValue(CONFIG_PAYRANK_END_TS))
	{
		return false;
	}

	std::string szType = Config::GetValue(CONFIG_PAYRANK_TYPE);
	if (type != szType)
	{
		return false;
	}

	return true;
}

void PointCmdUnit::Save()
{
	m_jsonData["pointreward"] = m_jsonPoint_;

	SaveUserGiftData(m_jsonData);
}


unsigned PointCmdUnit::SurplusPoint(UserWrap& user, int nfactor) const
{
	unsigned nTotal = TotalPoint(user, nfactor);
	unsigned nUse = m_jsonPoint_["lp"].asInt();

	return nTotal > nUse ? nTotal - nUse : 0;
}

unsigned PointCmdUnit::TotalPoint(UserWrap& user, int nfactor) const
{
	if (nfactor <= 0)
	{
		throw std::runtime_error("point_total_params_factor_error");
	}

	unsigned nStart = Config::GetIntValue(CONFIG_PAYRANK_BEGIN_TS);
	unsigned nEnd = Config::GetIntValue(CONFIG_PAYRANK_END_TS);
	std::pair<unsigned, unsigned> cost = user.GetCost(nStart, nEnd);

	return m_jsonPoint_["tp"].asInt() + (cost.first + cost.second) / nfactor;
}

void	PointCmdUnit::CostPoint(unsigned point)
{
	m_jsonPoint_["lp"] =  m_jsonPoint_["lp"].asInt() + point;
}


PointExchangeParams::PointExchangeParams(const Json::Value& jsonData)
	: BaseCmdParams(jsonData)
{
	index_ 	= ValueAsInt("index");
	cnt_ 	= ValueAsInt("cnt");
}

PointExchangeUnit::PointExchangeUnit(const UserWrap& user)
	: PointCmdUnit(user, "payrank")
{

}

int PointExchangeUnit::Exchage(UserWrap& user, const PointExchangeParams& params, Json::Value& result)
{
	DataXMLPointExchageRewardItem item;
	DataXmlPtr()->GetPointExchangeItem(params.Index(), item);

	//
	unsigned total_use = item.require * params.Cnt();
	if (SurplusPoint(user, 1) < total_use)
	{
		throw std::runtime_error("point_not_enough");
	}

	//
	CostPoint(total_use);

	Save();

	int equip_cnt = DataXMLPointExchageRewardItem::ITEM_CNT;
	std::string op = "point_exchange_op";
	for(int i = 0; i < (int)params.Cnt(); i++)
	{
		AddGiftEquips(item.items, equip_cnt, op, result);
	}

	result["info"]["lp"] = m_jsonPoint_["lp"];
	result["info"]["tp"] = m_jsonPoint_["tp"];

	return 0;
}

PointCutPriceBuyParams::PointCutPriceBuyParams(const Json::Value& jsonData)
	 : BaseCmdParams(jsonData)
{
	id_ = ValueAsInt("id");
	if (id_ <= 0 || id_ > DataXMLPointCutPrice::ITEM_CNT)
	{
		throw std::runtime_error("id_params_error");
	}
}

PointCutPriceUnit::PointCutPriceUnit(const UserWrap& user)
	: PointCmdUnit(user, "cutprice")
{

}

bool PointCutPriceUnit::IsBuy(unsigned id)
{
	unsigned flag = m_jsonPoint_["cpbr"].asInt();
	return (flag & (1 << (id - 1))) > 0;
}

void PointCutPriceUnit::SetBuyOp(unsigned id)
{
	unsigned flag = m_jsonPoint_["cpbr"].asInt();
	flag |= (1 << (id - 1));

	m_jsonPoint_["cpbr"] = flag;
}

int PointCutPriceUnit::Buy(UserWrap& user, const PointCutPriceBuyParams& params, Json::Value& result)
{
	DataXMLPointCutPriceItem item;
	DataXmlPtr()->GetPointCutPriceItem(params.Id(), item);

	unsigned id = params.Id();

	unsigned lvl = DataXmlPtr()->GetPointCutPriceLvl(TotalPoint(user, 100));
	if (lvl < item.needLv)
	{
		throw std::runtime_error("level_not_engouth");
	}

	if (IsBuy(id))
	{
		throw std::runtime_error("already_buy");
	}

	std::string op = "point_cut_price_buy_op";
	user.CostAsset(item.price, 0, op, result["pay"]);

	SetBuyOp(id);

	Save();

	std::vector<ItemAdd> equips;
	equips.push_back(ItemAdd(item.item_id, 1, op));
	this->AddEquips(equips, result);

	result["info"]["cpbr"] = m_jsonPoint_["cpbr"];

	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////
BuildingSkinBuyParams::BuildingSkinBuyParams(const Json::Value& jsonData)
	: BaseCmdParams(jsonData)
{
	id_ = ValueAsInt("id");
	if (id_ > DataXMLBuildingSkin::ITEM_CNT)
	{
		throw std::runtime_error("id_params_error");
	}
}

BuildingSkinUseParams::BuildingSkinUseParams(const Json::Value& jsonData)
	: BaseCmdParams(jsonData)
{
	id_ = ValueAsInt("id");
	if (id_ > DataXMLBuildingSkin::ITEM_CNT)
	{
		throw std::runtime_error("id_params_error");
	}

	eq_ud_ = ValueAsInt("eq_ud");
}

BuildingSkinReletParams::BuildingSkinReletParams(const Json::Value& jsonData)
	: BaseCmdParams(jsonData)
{
	id_ = ValueAsInt("id");
	if (id_ > DataXMLBuildingSkin::ITEM_CNT)
	{
		throw std::runtime_error("id_params_error");
	}

	type_ = ValueAsInt("type");
	if (type_ > DataXMLBuildingSkinRelet::ITEM_CNT)
	{
		throw std::runtime_error("type_params_error");
	}
}

BuildingSkinUint::BuildingSkinUint(const UserWrap& user)
	: BaseCmdUnit(user.Id())
{
	user.GetUserTech(m_jsonData);
	m_jsonSkin = m_jsonData["skin"];
}

void BuildingSkinUint::Save(UserWrap& user)
{
	m_jsonData["skin"] = m_jsonSkin;
	user.SetUserTech(m_jsonData);
}

int BuildingSkinUint::Buy(UserWrap& user, const BuildingSkinBuyParams& params, Json::Value& result)
{
	DataXMLBuildingSkinBuy buyItem;
	DataXmlPtr()->GetBuildSkinBuy(params.Id(), buyItem);

	std::string op = "building_skin_buy_op";
	user.CostAsset(buyItem.cost, 0, op, result["pay"]);
	this->AddEquips(buyItem.eqid, op, result);

	return 0;
}

int BuildingSkinUint::Use(UserWrap& user, const BuildingSkinUseParams& params, Json::Value& result)
{
	if (params.Id() == 0 || IsValid(params.Id()))
	{
		m_jsonSkin["c"] = params.Id();
	}
	else
	{
		std::string op = "building_skin_use_op";

		DataXMLBuildingSkinBuy buyItem;
		DataXmlPtr()->GetBuildSkinBuy(params.Id(), buyItem);

		this->UseEquips(buyItem.eqid, params.EqUd(), 1, op);

		m_jsonSkin["t"][params.Id()] = Time::GetGlobalTime() + 7*24*60*60;
		m_jsonSkin["c"] = params.Id();
	}

	Save(user);

	result["info"] = m_jsonSkin;

	return 0;
}

int BuildingSkinUint::Relet(UserWrap& user, const BuildingSkinReletParams& params, Json::Value& result)
{
	DataXMLBuildingSkinReletItem reletItem;
	unsigned id = params.Id();
	DataXmlPtr()->GetBuildSkinRelet(id, params.Type(), reletItem);

	std::string op = "building_skin_relet_op";
	user.CostAsset(reletItem.cost, 0, op, result["pay"]);

	unsigned lost_time = m_jsonSkin["t"][id].asInt();
	unsigned now_time = Time::GetGlobalTime();

	m_jsonSkin["t"][id] = (lost_time < now_time ? now_time : lost_time) + reletItem.time * 24*60*60;

	Save(user);

	result["info"] = m_jsonSkin;

	return 0;
}

bool BuildingSkinUint::IsValid(unsigned id)
{
	if (! Json::IsArray(m_jsonSkin, "t"))
	{
		m_jsonSkin["t"] = Json::arrayValue;
	}

	unsigned lost_time = m_jsonSkin["t"][id].asInt();
	return (lost_time > Time::GetGlobalTime());
}
////////////////////////////////////////////////////////////////////////////////////////
HammerHitUnit::HammerHitUnit(const UserWrap& user)
	: BaseCmdUnit(user.Id())
{
	user.GetUserStats(m_jsonData);
}

int HammerHitUnit::DrawHammer(UserWrap& user, const BaseCmdParams& params, Json::Value& result)
{
	if (m_jsonData["hfl"][1].asInt() > 0)
	{
		throw std::runtime_error("already_draw_hammers");
	}

	m_jsonData["hfl"][1] = 1;
	user.SetUserStats(m_jsonData);

	std::string op = "get_free_hammer_day";
	this->AddEquips(5201, 5, op, result);

	result["info"]["hfl"] = m_jsonData["hfl"];

	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////
TutorLoginUnit::TutorLoginUnit(const UserWrap& user)
	: BaseCmdUnit(user.Id())
{
	user.GetUserStats(m_jsonData);
}

int TutorLoginUnit::Reward(UserWrap& user, const UnitIdCmdParams& params, Json::Value& result)
{
	DataXMLTutorLoginItem tutor_item;
	unsigned id = params.Id();
	DataXmlPtr()->GetTutorLoginItem(id, tutor_item);

	int index = (id - 1) % 7;
	bool bBase = id <= 7;

	bool bGet = bBase ? m_jsonData["tutLg"][index].asInt() > 0
						: m_jsonData["tutlg2"][index].asInt() > 0;
	if (bGet)
	{
		throw std::runtime_error("already_get_reward");
	}

	if (bBase)
	{
		m_jsonData["tutLg"][index] = 1;
	}
	else
	{
		m_jsonData["tutlg2"][index] = 1;
	}

	user.SetUserStats(m_jsonData);
	//
	std::string op = "tutor_login_reward_op";
	if (tutor_item.prosper > 0)
	{
		user.AddProsper(tutor_item.prosper, op, result);
	}

	if (tutor_item.gold > 0)
	{
		user.AddCashCoin(0, tutor_item.gold, op, result);
	}

	user.AddResource(tutor_item.rs[0],
						tutor_item.rs[1],
						tutor_item.rs[2],
						tutor_item.rs[3],
						op, result);

	AddGiftEquips(tutor_item.equips, DataXMLTutorLoginItem::EUIP_CNT, op, result);

	result["info"]["tutLg"] = m_jsonData["tutLg"];
	result["info"]["tutlg2"] = m_jsonData["tutlg2"];

	return 0;
}
////////////////////////////////////////////////////////////////////////////////////
ImperialGiftUnit::ImperialGiftUnit(const UserWrap& user)
	: BaseCmdUnit(user.Id())
{
	user.GetUserStats(m_jsonData);
}

int ImperialGiftUnit::Get(UserWrap& user, const BaseCmdParams& params, Json::Value& result)
{
	if (m_jsonData["baye2"].asUInt() > 0)
	{
		throw std::runtime_error("already_get_gift");
	}

	m_jsonData["baye2"] = 1;

	user.SetUserStats(m_jsonData);

	std::string op = "imperial_gift_op";
	std::vector<ItemAdd> equips;
	equips.push_back(ItemAdd(4060, 1, op));
	equips.push_back(ItemAdd(105, 1, op));
	this->AddEquips(equips, result);

	result["info"]["baye2"] = m_jsonData["baye2"];

	return 0;
}

ImperialGiftOpenParams::ImperialGiftOpenParams(const Json::Value& jsonData)
	: UnitIdCmdParams(jsonData)
{
	equip_ud_ = ValueAsUInt("ud");
}

int ImperialGiftUnit::Open(UserWrap& user, const ImperialGiftOpenParams& params, Json::Value& result)
{
	enum {
		GIFT_EQUIP_ID = 4060,
	};
	DataXMLImperialGiftItem gift;
	DataXmlPtr()->GetImperialGift(params.Id(), gift);

	if (! this->IsExistEquips(GIFT_EQUIP_ID, params.EquipUd(), 1))
	{
		throw std::runtime_error("not_exist_the_gift_bag");
	}

	int index = params.Id() - 1;
	if (m_jsonData["baye"][index].asUInt() > 0)
	{
		throw std::runtime_error("already_open_the_gift");
	}

	if (user.GetUserLevel() < gift.end)
	{
		throw std::runtime_error("user_level_not_enough");
	}

	std::string op = "open_imperial_gift_bag_op";
	user.CostAsset(gift.cost, 0, op, result);

	m_jsonData["baye"][index] = 1;
	user.SetUserStats(m_jsonData);

	//4060
	bool bFlag = true;
	for (int i = 0; i < DataXMLImperialGift::ITEM_CNT; i++)
	{
		if (m_jsonData["baye"][i].asInt() == 0)
		{
			bFlag = false;
			break;
		}
	}

	if (bFlag)
	{
		this->UseEquips(GIFT_EQUIP_ID, params.EquipUd(), 1, op);
	}

	this->AddGiftEquips(gift.equips, DataXMLImperialGiftItem::EUIP_CNT, op, result);

	//读取配置文件时漏了
	if (params.Id() == 5)
	{
		//添加100  器魂
		user.AddWareSoul(100, op, result);
	}

	//漏了第2档的金币
	if (params.Id() == 2)
	{
		//增加80金币
		user.AddCashCoin(0, 80, op, result);
	}

	result["info"]["baye"] = m_jsonData["baye"];

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////
TimeLimitUpgradeRewardParams::TimeLimitUpgradeRewardParams(const Json::Value& jsonData)
	: BaseCmdParams(jsonData)
{
	grade_range_ = ValueAsInt("grade_range");
}

TimeLimitUpgradeUnit::TimeLimitUpgradeUnit(const UserWrap& user)
	: BaseCmdUnit(user.Id())
{

}

CDataOpenAreaActivity* TimeLimitUpgradeUnit::GetOpenAreaActivityPoint()
{
	GET_MEM_DATA_SEM(CDataOpenAreaActivity, OPEN_AREA_PATH, sem_openarea_activity,false)
}

int TimeLimitUpgradeUnit::Reward(UserWrap& user, const TimeLimitUpgradeRewardParams& params, Json::Value& result)
{
	CDataOpenAreaActivity *pdata= GetOpenAreaActivityPoint();
	if(pdata == NULL)
	{
		DB_ERROR_RETURN_MSG("init_openarea_activity_fail");
	}

	int grade_range = params.GradeRange();
	int level = user.GetUserLevel();
	switch(grade_range)
	{
	case 0:
		if(level < 15)
			return R_ERR_LOGIC;
		break;
	case 1:
		if(level < 20)
			return R_ERR_LOGIC;
		break;
	case 2:
		if(level < 30)
			return R_ERR_LOGIC;
		break;
	case 3:
		if(level < 35)
			return R_ERR_LOGIC;
		break;
	case 4:
		if(level < 40)
			return R_ERR_LOGIC;
		break;
	case 5:
		if(level < 45)
			return R_ERR_LOGIC;
		break;
	case 6:
		if(level < 50)
			return R_ERR_LOGIC;
		break;
	case 7:
		if(level < 55)
			return R_ERR_LOGIC;
		break;
	default:
		return R_ERR_LOGIC;
		break;
	}

	Json::Value req_result;
	int ret = pdata->UpdateOpenAreaActivityList(user.Id(), grade_range, req_result);
	if(ret != 0)
	{
		return ret;
	}

	if (req_result["flag"].asInt() == 2)
	{
		DataXMLTimeLimitUpgradeItem item;
		DataXmlPtr()->GetTimeLimitUpgrade(params.GradeRange(), item);

		std::string op = "time_limit_upgrade_reward_op";
		this->AddGiftEquips(item.equips, DataXMLTimeLimitUpgradeItem::EUIP_CNT, op, result);
		if (item.gold > 0)
		{
			user.AddCashCoin(0, item.gold, op, result);
		}
	}

	result["flag"] = req_result["flag"].asInt();

	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////
CServerladderUnit::CServerladderUnit(const UserWrap& user)
	: BaseCmdUnit(user.Id())
{
	user.GetUserStats(m_jsonData);

	m_jsonCrmr = m_jsonData["crmr"];
}

int CServerladderUnit::Reward(UserWrap& user, const BaseCmdParams& params, Json::Value& result)
{
	if (m_jsonCrmr.empty())
	{
		throw std::runtime_error("cannot_get_reward");
	}

	std::string op = "cross_server_ladder_reward_op";

	unsigned nCoins = m_jsonCrmr["coins"].asUInt();
	unsigned prosper = m_jsonCrmr["bs"].asUInt();

	if (nCoins > 0)
	{
		user.AddCashCoin(0, nCoins, op, result);
	}

	if (nCoins > 0)
	{
		user.AddProsper(prosper, op, result);
	}

	m_jsonCrmr.clear();
	m_jsonData["crmr"] = m_jsonCrmr;
	user.SetUserStats(m_jsonData);

	result["info"]["crmr"] = m_jsonCrmr;

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////
YearFortuneUnit::YearFortuneUnit(const UserWrap& user)
	: BaseCmdUnit(user.Id())
{
	unsigned nStart = Config::GetIntValue(CONFIG_VICKY_CHICK_BEGIN_TS);
	unsigned nEnd = Config::GetIntValue(CONFIG_VICKY_CHICK_END_TS);
	unsigned now = Time::GetGlobalTime();

	if (now < nStart || now > nEnd)
	{
		throw std::runtime_error("activity_not_open");
	}

	CLogicSecinc logicSecinc;
	int ret = logicSecinc.GetSecinc(m_nUid, NAT_VICKY_CHICK, m_jsonData);

	if (R_ERR_NO_DATA == ret)
	{
		m_jsonData["id"] = NAT_VICKY_CHICK;

		Reset();
	}
	else
	{
		if (ret != R_SUCCESS)
		{
			throw std::runtime_error("get_new_active_data_error");
		}

		unsigned ts = m_jsonData["ts"].asUInt();
		if (! Time::IsToday(ts))
		{
			Reset();
		}
	}

	for (int i = 0; i < DataXMLYearFortune::LIB_CNT; i++)
	{
		if (m_jsonData["a"][i].asInt() == 0)
		{
			m_jsonData["a"][i] = BuildReward(i);
		}
	}

	m_jsonData["ts"] = Time::GetGlobalTime();
}

void YearFortuneUnit::Reset()
{
	for (int i = 0; i < DataXMLYearFortune::LIB_CNT; i++)
	{
		m_jsonData["a"][i] = 0; //每个库对应奖品id
	}
	for (int i = 0; i < DataXMLYearFortune::STAGE_CNT; i++)
	{
		m_jsonData["b"][i] = 0; //每个阶段对应的领取标记
	}

	m_jsonData["c"] = 0; //当前不包含钻石或金币消费积分的总积分
}

int YearFortuneUnit::BuildReward(int index)
{
	int id = index + 1;
	DataXMLYearFortuneLib lib = DataXmlPtr()->GetYearFortuneLib(id);

	return lib.GetRandomItemOfId();
}

int YearFortuneUnit::Info(UserWrap& user, const BaseCmdParams& params, Json::Value& result)
{
	result["info"] = m_jsonData;

	Save();

	return 0;
}

int YearFortuneUnit::Transfer(UserWrap& user, const BaseCmdParams& params, Json::Value& result)
{
	user.CostAsset(1, 0, "yesr_frotune_activity_transfer_op", result);
	//
	for (int i = 0; i < DataXMLYearFortune::LIB_CNT; i++)
	{
		m_jsonData["a"][i] = BuildReward(i);
	}

	Save();

	result["info"] = m_jsonData;

	return 0;
}

int YearFortuneUnit::TotalPoint(const UserWrap& user) const
{
	unsigned nStart = CTime::GetDayBeginTime(Time::GetGlobalTime());
	unsigned nEnd = nStart + 24*60*60;

	std::pair<unsigned, unsigned> cost = user.GetCost(nStart, nEnd);
	return (cost.first + cost.second / 10) * 10 + m_jsonData["c"].asInt();
}

int YearFortuneUnit::Reward(UserWrap& user, const BaseCmdParams& params, Json::Value& result)
{
	int index = -1;
	for (int i = 0; i < DataXMLYearFortune::STAGE_CNT; i++)
	{
		if (m_jsonData["b"][i].asUInt() == 0)
		{
			index = i;
			break;
		}
	}

	if (index < 0)
	{
		throw std::runtime_error("alreay_get_reward");
	}

	int need_point =  DataXmlPtr()->GetYearFortuneNeedPoint(index);
	if (TotalPoint(user) < need_point)
	{
		throw std::runtime_error("point_not_enough");
	}

	m_jsonData["b"][index] = 1;
	Save();

	std::string op = "year_fortune_reward_op";

	std::vector<GiftEquipItem> vEquips;
	for (int i = 0; i < DataXMLYearFortune::LIB_CNT; i++)
	{
		DataXMLYearFortuneLib lib = DataXmlPtr()->GetYearFortuneLib(i + 1);
		unsigned id = m_jsonData["a"][i].asInt();
		DataXMLYearFortuneItem item = lib.GetItem(id);
		for (int k = 0; k < DataXMLYearFortuneItem::EQUIP_CNT; k++)
		{
			vEquips.push_back(item.equips[k]);
		}

		//重新生成
		 m_jsonData["a"][i] = lib.GetRandomItemOfId();
	}

	Save();

	this->AddGiftEquips(vEquips, op, result);

	result["info"] = m_jsonData;

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////
WinterHolidayRevelayUnit::WinterHolidayRevelayUnit(const UserWrap& user)
	: BaseCmdUnit(user.Id())
{
	unsigned nStart = Config::GetIntValue(CONFIG_HOLIDAY_REVELRY_BEGIN_TS);
	unsigned nEnd = Config::GetIntValue(CONFIG_HOLIDAY_REVELRY_END_TS);
	unsigned now = Time::GetGlobalTime();
	if (now < nStart || now > nEnd)
	{
		throw std::runtime_error("activity_not_open");
	}

	CLogicSecinc logicSecinc;
	int ret = logicSecinc.GetSecinc(m_nUid, NAT_HOLIDAY_REVELAY, m_jsonData);
	unsigned nVersion = GetActivityVersion(CONFIG_HOLIDAY_REVELRY_VER);
	if (R_ERR_NO_DATA == ret)
	{
		m_jsonData["id"] = NAT_HOLIDAY_REVELAY;
		Reset(nVersion);
	}
	else
	{
		if (ret != R_SUCCESS)
		{
			throw std::runtime_error("get_new_active_data_error");
		}

		if (nVersion != m_jsonData["v"].asUInt())
		{
			Reset(nVersion);
		}
	}
}

void WinterHolidayRevelayUnit::Reset(unsigned nVersion)
{
	m_jsonData["v"] = nVersion; //活动版本
	m_jsonData["a"] = 0;  		//已经抽奖使用了的积分
	m_jsonData["b"] = Json::arrayValue;   //礼包领取记录
	int size = DataXmlPtr()->GetWinterHolidayRevelryConfig().GetRewardItemsSize();
	m_jsonData["b"].resize(size);
	for (int i = 0; i < size; i++)
	{
		m_jsonData["b"][i] = 0;
	}

	Save();
}

int WinterHolidayRevelayUnit::TotalRecharge(const UserWrap& user) const
{
	unsigned nStart = Config::GetIntValue(CONFIG_HOLIDAY_REVELRY_BEGIN_TS);
	unsigned nEnd = Config::GetIntValue(CONFIG_HOLIDAY_REVELRY_END_TS);
	return user.GetRechargePoint(nStart, nEnd);
}

WHRevelayDrawRewardParams::WHRevelayDrawRewardParams(const Json::Value& data)
	: BaseCmdParams(data)
{
	cnt_ = ValueAsUInt("cnt");
	if (cnt_ <= 0)
	{
		throw std::runtime_error("cnt_params_error");
	}
}

int WinterHolidayRevelayUnit::DrawReward(UserWrap& user, const WHRevelayDrawRewardParams& params, Json::Value& result)
{
	enum {
		USER_POINT_ONCE = 50,
	};
	int nUsedPoint = m_jsonData["a"].asInt();
	int nTotalPoint = TotalRecharge(user);
	int nUse = USER_POINT_ONCE * params.Cnt();
	if ((nTotalPoint - nUsedPoint) < nUse)
	{
		throw std::runtime_error("point_not_enough");
	}

	m_jsonData["a"] = nUsedPoint + nUse;
	Save();

	const DataWinterHolidayRevelry& config = DataXmlPtr()->GetWinterHolidayRevelryConfig();

	//
	std::string op = "winter_holiday_revelry_draw_reward_op";
	std::vector<ItemAdd> equips;
	for (int i = 0; i < (int)params.Cnt(); i++)
	{
		int idx = config.RandomDrawRewardIndex();
		const DataWinterHolidayRevelry::DataDrawRewardItem& reward = config.DrawRewardItem(idx);
		equips.push_back(ItemAdd(reward.id, reward.count, op));

		result["idxs"][i] = idx;
	}

	this->AddEquips(equips, result);

	result["info"] = m_jsonData;

	return 0;
}

int WinterHolidayRevelayUnit::GetReward(UserWrap& user, const UnitIndexCmdParams& params, Json::Value& result)
{
	int idx = params.Index();
	const DataWinterHolidayRevelry& config
					= DataXmlPtr()->GetWinterHolidayRevelryConfig();

	const DataWinterHolidayRevelry::DataGetRewardItem& reward
											= config.GetRewardItem(idx);
	if (m_jsonData["b"][idx].asUInt() > 0)
	{
		throw std::runtime_error("already_get_reward");
	}

	if (TotalRecharge(user) < reward.need)
	{
		throw std::runtime_error("recharge_not_enough");
	}

	m_jsonData["b"][idx] = 1;
	Save();


	std::string op = "winter_holiday_revelay_get_reward_op";
	this->AddEquips(reward.id, reward.count, op, result);

	result["info"] = m_jsonData;

	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////
TowerActivityUnit::TowerActivityUnit(const UserWrap& user)
	: BaseCmdUnit(user.Id())
{


	unsigned now = Time::GetGlobalTime();
	unsigned nActVersion = Config::GetIntValue(CONFIG_TOWER_ACTIVITY_VER);

	if ((now < Config::GetIntValue(CONFIG_TOWER_ACTIVITY_BEGIN_TS))
	|| (now > Config::GetIntValue(CONFIG_TOWER_ACTIVITY_END_TS )))
	{
		throw std::runtime_error("out_activity_peroid");
	}

	int ret1 = CLogicSecinc().GetSecinc(m_nUid, NAT_TOWER_ACTIVI_1, m_json_newAct1);
	int ret2 = CLogicSecinc().GetSecinc(m_nUid, NAT_TOWER_ACTIVI_2, m_json_newAct2);
	if (R_ERR_NO_DATA == ret1
		|| R_ERR_NO_DATA == ret2
		|| nActVersion != m_json_newAct1["v"].asInt()
		|| !Time::IsToday(m_json_newAct1["c"].asUInt()))
	{
		Reset(nActVersion);
	}
	else
	{
		if (ret1 != R_SUCCESS || ret2 != R_SUCCESS)
		{
			throw std::runtime_error("get_new_active_data_error");
		}
	}

	m_total_treasure_cnt = m_json_newAct1["a"].asInt();
	m_treasure_cnt = m_json_newAct2["d"][TOWER_CNT].asInt();
	m_cur_id = m_json_newAct2["g"].asInt();
}

void TowerActivityUnit::Reset(unsigned nVersion)
{
	m_json_newAct1.clear();
	m_json_newAct2.clear();

	m_json_newAct1["id"] = NAT_TOWER_ACTIVI_1;
	m_json_newAct1["a"] = 0;					// 总共摸金的次数
	m_json_newAct1["c"] = Time::GetGlobalTime(); // 数据重置时间，用于数据隔天充值
	m_json_newAct1["v"] = nVersion;				 // 活动版本

	m_json_newAct2["id"] = NAT_TOWER_ACTIVI_2;
	m_json_newAct2["d"][0u] = 1;		// tombStat [0-4]对应塔楼的解锁状态，[5]此轮探宝次数
	m_json_newAct2["f"] = Json::arrayValue;

	int i = 0;
	for (i = 1; i < TOWER_CNT; ++i)
	{
		m_json_newAct2["d"][i] = 0;
	}
	m_json_newAct2["d"][i] = 0;					// tombCount

	ResetOut(TOWER_DEAFAULT_ID);
}

void TowerActivityUnit::Save()
{
	m_json_newAct1["a"] = m_total_treasure_cnt;
	m_json_newAct2["d"][TOWER_CNT] = m_treasure_cnt;

	CLogicSecinc logicSecinc;
	if (logicSecinc.SetOneSecinc(m_nUid, m_json_newAct1) !=  R_SUCCESS)
	{
		throw std::runtime_error("Save_data_failed");
	}

	if (logicSecinc.SetOneSecinc(m_nUid, m_json_newAct2) !=  R_SUCCESS)
	{
		throw std::runtime_error("Save_data_failed");
	}
}

void TowerActivityUnit::ResetOut(unsigned id)
{
	if (id < 0 || id >= TOWER_CNT)
	{
		throw std::runtime_error("reset_out_paramse_error");
	}

	m_json_newAct2["f"].clear();  //探宝状态记录

	static unsigned out[TOWER_CNT] = {240, 525, 900, 1500, 3000};
	static unsigned foNum[TOWER_CNT] = {24, 52, 90, 150, 300};
	unsigned dragScale = 0;
	unsigned fo = 0;

	for (int i = 0; i < TOWER_REWARD_CNT; ++i)
	{
		fo = Math::GetRandomInt(foNum[id]);
		dragScale = Math::GetRandomInt(2) ? (out[id] + fo) : (out[id] - fo);
		m_json_newAct2["e"][i] = dragScale;
	}

	m_treasure_cnt = 0;
	m_json_newAct2["g"] = id;
	m_cur_id = id;
}

unsigned TowerActivityUnit::GetOut(unsigned index) const
{
	return m_json_newAct2["e"][index].asUInt();
}

bool TowerActivityUnit::IsUnlock(unsigned index) const
{
	return m_json_newAct2["d"][index] == 1;
}

void TowerActivityUnit::SetUnlock(unsigned index)
{
	m_json_newAct2["d"][index] = 1;
}

void TowerActivityUnit::SetTreasure(int cnt, unsigned index)
{
	m_json_newAct2["f"][cnt] = index;
}

bool TowerActivityUnit::IsTreasure(unsigned index)
{
	for (int i = 0; i < m_json_newAct2["f"].size(); i++)
	{
		if (m_json_newAct2["f"][i] == index)
		{
			return true;
		}
	}

	return false;
}

int TowerActivityUnit::ResetImpl(UserWrap& user, const UnitIndexCmdParams& params, Json::Value& result)
{
	ResetOut(params.Index());

	Save();

	result["newAct1"] = m_json_newAct1;
	result["newAct2"] = m_json_newAct2;

	return 0;
}

unsigned TowerActivityUnit::Treasure(int index)
{
	static const unsigned nextTombChance[TOWER_CNT] = {5, 6, 7, 8, 20};

	if (IsTreasure(index))
	{
		throw std::runtime_error("is_already_treasure");
	}

	SetTreasure(m_treasure_cnt ++, index);

	if (m_cur_id < TOWER_CNT - 1 && (! IsUnlock(m_cur_id + 1)))
	{
		int rate = Math::GetRandomInt(100);
		if (rate < nextTombChance[m_cur_id])
		{
			SetUnlock(m_cur_id + 1);
		}
	}

	++m_total_treasure_cnt;

	return GetOut(index);
}

unsigned TowerActivityUnit::GetExtraEquip(int id)
{
	if (id < 0 || id >= TOWER_CNT)
	{
		throw std::runtime_error("get_extra_paramse_error");
	}

	const static unsigned action_prob[TOWER_CNT] = {40, 50, 60, 80, 90};
	int rate = Math::GetRandomInt(100);
	if (rate < action_prob[id])
	{
		static unsigned out[TOWER_CNT] = {240, 525, 900, 1500, 3000};
		static unsigned foNum[TOWER_CNT] = {24, 52, 90, 150, 300};
		unsigned dragScale = 0;
		unsigned fo = 0;

		fo = Math::GetRandomInt(foNum[id]);
		dragScale = Math::GetRandomInt(2) ? (out[id] + fo) : (out[id] - fo);

		return dragScale;
	}
	else
	{
		return 0;
	}
}

unsigned TowerActivityUnit::GetTreasureCost(int cnt) const
{
	static const unsigned payCash[TOWER_CNT] = {2, 5, 10, 20, 50};
	return payCash[m_cur_id] * cnt;
}

TowerTreasureParams::TowerTreasureParams(const Json::Value& data)
	: UnitIndexCmdParams(data)
{
	ud_ = ValueAsUInt("ud");
	if (ud_ <= 0)
	{
		throw std::runtime_error("ud_params_error");
	}
}

TowerOnceParams::TowerOnceParams(const Json::Value& data)
	: BaseCmdParams(data)
{
	ud_ = ValueAsUInt("ud");
	if (ud_ <= 0)
	{
		throw std::runtime_error("ud_params_error");
	}
}

//探宝
int TowerActivityUnit::TreasureImpl(UserWrap& user, const TowerTreasureParams& params, Json::Value& result)
{
	if (params.Index() >= TOWER_REWARD_CNT)
	{
		throw std::runtime_error("index_params_error");
	}

	if (m_treasure_cnt >= TOWER_ACT_CNT
			|| m_total_treasure_cnt >= TOTAL_TOWER_ACT_CNT)
	{
		throw std::runtime_error("over_touch_cnt");
	}

	std::string op = "tower_activity_treasure_op";
	int cost_cnt = GetTreasureCost();
#ifdef SG_USE_CASH
	user.CostAsset(cost_cnt, 0, op, result);
#else
	this->UseEquips(2025 , params.Ud(), cost_cnt, op);
#endif


	unsigned out = Treasure(params.Index());
	unsigned extra_out =  GetExtraEquip(m_cur_id);

	Save();

	if (extra_out > 0)
	{
		std::vector<ItemAdd> items;
		items.push_back(ItemAdd(TOWER_EQUIPS_ID, out, op));
		items.push_back(ItemAdd(TOWER_EXTRA_ID, extra_out, op));

		this->AddEquips(items, result);
	}
	else
	{
		this->AddEquips(TOWER_EQUIPS_ID, out, op, result);
	}


	result["newAct1"] = m_json_newAct1;
	result["newAct2"] = m_json_newAct2;
#ifndef SG_USE_CASH
	result["equip_cost"] = cost_cnt;
#endif

	return 0;
}
//一键
int TowerActivityUnit::OnceImpl(UserWrap& user, const TowerOnceParams& params, Json::Value& result)
{
	if (m_treasure_cnt > 0)
	{
		throw std::runtime_error("already_treasure");
	}

	if (m_total_treasure_cnt + TOWER_ACT_CNT > TOTAL_TOWER_ACT_CNT)
	{
		throw std::runtime_error("not_enough_cnt");
	}

	std::string op = "tower_activity_treasure_once_op";
	int cost_cnt = GetTreasureCost(TOWER_ACT_CNT);
#ifdef SG_USE_CASH
	user.CostAsset(cost_cnt, 0, op, result);
#else
	this->UseEquips(2025 , params.Ud(), cost_cnt, op);
#endif

	unsigned rand_val[TOWER_REWARD_CNT] = {0};
	for (int i = 0; i < TOWER_REWARD_CNT; i++)
	{
		rand_val[i] = i;
	}

	int nTotalEquips = 0;
	int nTotalExtra = 0;
	int len = TOWER_REWARD_CNT;
	for (int i = 0; i < TOWER_ACT_CNT; i++)
	{
		int randindex = Math::GetRandomInt(len);
		int listindex = rand_val[randindex];
		rand_val[randindex] = rand_val[len - 1];
		--len;

		nTotalEquips += Treasure(listindex);
		nTotalExtra += GetExtraEquip(m_cur_id);
	}

	Save();

	if (nTotalExtra > 0)
	{
		std::vector<ItemAdd> items;
		items.push_back(ItemAdd(TOWER_EQUIPS_ID, nTotalEquips, op));
		items.push_back(ItemAdd(TOWER_EXTRA_ID, nTotalExtra, op));

		this->AddEquips(items, result);
	}
	else
	{
		this->AddEquips(TOWER_EQUIPS_ID, nTotalEquips, op, result);
	}

	result["newAct1"] = m_json_newAct1;
	result["newAct2"] = m_json_newAct2;
#ifndef SG_USE_CASH
	result["equip_cost"] = cost_cnt;
#endif

	return 0;
}

//解锁
int TowerActivityUnit::UnlockFloorImpl(UserWrap& user, const BaseCmdParams& params, Json::Value& result)
{
	if (IsUnlock(TOWER_SKIP_ID))
	{
		throw std::runtime_error("is_unlock");
	}

	std::string op = "tower_activity_unlock_floor_op";
	user.CostAsset(200, 0, op, result);

	SetUnlock(TOWER_SKIP_ID);

	ResetOut(TOWER_SKIP_ID);

	Save();

	result["newAct1"] = m_json_newAct1;
	result["newAct2"] = m_json_newAct2;


	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////
TokenIntensifyUnit::TokenIntensifyUnit(const UserWrap& user)
	: BaseCmdUnit(user.Id())
	, cfg_(DataXmlPtr()->GetTokenIntensify())
{
	unsigned now = Time::GetGlobalTime();
	unsigned nActVersion = Config::GetIntValue(CONFIG_TOKEN_INTENSIFY_VER);

	if ((now < Config::GetIntValue(CONFIG_TOKEN_INTENSIFY_BEGIN_TS))
	|| (now > Config::GetIntValue(CONFIG_TOKEN_INTENSIFY_END_TS )))
	{
		throw std::runtime_error("out_activity_peroid");
	}

	int ret = CLogicSecinc().GetSecinc(m_nUid, NAT_TOKEN_INTENSIFY, m_jsonData);
	if (ret == R_ERR_NO_DATA
		|| nActVersion != m_jsonData["v"].asInt()
		|| !Time::IsToday(m_jsonData["ts"].asInt()))
	{
		m_jsonData["id"] = NAT_TOKEN_INTENSIFY;
		Reset(nActVersion);
	}
	else
	{
		if (ret != R_SUCCESS)
		{
			throw std::runtime_error("get_new_active_data_error");
		}
	}
}

void TokenIntensifyUnit::Reset(unsigned nVersion)
{
	if (m_jsonData["v"].asUInt() != nVersion)
	{
		m_jsonData["c"] = 0; //已经使用的积分
		m_jsonData["v"] = nVersion;
	}

	m_jsonData["ts"] = Time::GetGlobalTime();
	//兑换记录
	m_jsonData["a"].clear();  //zone
	m_jsonData["b"].clear();  //common

	for (size_t i = 0; i < cfg_.ZoneItems().size(); i++)
	{
		m_jsonData["a"][i] = 0;
	}

	for (size_t i = 0; i < cfg_.NormalItems().size(); i++)
	{
		m_jsonData["b"][i] = 0;
	}

	ShmPtr()->Reset();
}

ShDataTokenIntensify* TokenIntensifyUnit::GetTokenIntensifyShm()
{
	GET_MEM_DATA_SEM(ShDataTokenIntensify, CONFIG_TOKEN_INTENSIFY_PATH, sem_token_intensify,false)
}

ShDataTokenIntensify*	TokenIntensifyUnit::ShmPtr()
{
	ShDataTokenIntensify* pdata = GetTokenIntensifyShm();
	if (NULL == pdata)
	{
		throw std::runtime_error("read_shm_data_error");
	}

	return pdata;
}

int TokenIntensifyUnit::ListImpl(UserWrap& user, const BaseCmdParams& params, Json::Value& result)
{
	ShDataTokenIntensify* pShm = ShmPtr();
	const std::vector<DataTokenIntensify::ZoneItem>& zoneItems = cfg_.ZoneItems();
	for (size_t i = 0; i < zoneItems.size(); i++)
	{
		const DataTokenIntensify::ZoneItem& zoneItem = zoneItems[i];
		unsigned limit = zoneItem.ZoneLimit();
		unsigned exchanged = pShm->GetExchangeCnt(zoneItem.Index());
		unsigned surplus = limit >= exchanged ? limit - exchanged : 0;
		result["zone_list"][zoneItem.Index()] = surplus;
	}

	result["info"] = m_jsonData;

	return 0;
}

void TokenIntensifyUnit::CostPoint(UserWrap& user, unsigned point)
{
	int used_point = m_jsonData["c"].asInt();


	int total_point = user.GetRechargePoint(
			  Config::GetIntValue(CONFIG_TOKEN_INTENSIFY_BEGIN_TS)
			, Config::GetIntValue(CONFIG_TOKEN_INTENSIFY_END_TS));
	if (used_point + point > total_point)
	{
		throw std::runtime_error("point_not_enough");
	}

	m_jsonData["c"] = used_point + point;
}

int TokenIntensifyUnit::ExchangeZoneImpl(UserWrap& user, const UnitIndexCmdParams& params, Json::Value& result)
{
	ShDataTokenIntensify* pShm = ShmPtr();
	const DataTokenIntensify::ZoneItem& item = cfg_.GetZoneItem(params.Index());

	if (pShm->GetExchangeCnt(params.Index()) >= item.ZoneLimit())
	{
		//throw std::runtime_error("zone_item_reach_limit");
		result["exchange_err_msg"] = "zone_item_reach_limit";

		const std::vector<DataTokenIntensify::ZoneItem>& zoneItems = cfg_.ZoneItems();
		for (size_t i = 0; i < zoneItems.size(); i++)
		{
			const DataTokenIntensify::ZoneItem& zoneItem = zoneItems[i];
			unsigned limit = zoneItem.ZoneLimit();
			unsigned exchanged = pShm->GetExchangeCnt(zoneItem.Index());
			unsigned surplus = limit >= exchanged ? limit - exchanged : 0;
			result["zone_list"][zoneItem.Index()] = surplus;
		}
	}
	else
	{
		int exchanged = m_jsonData["a"][params.Index()].asInt();
		if (exchanged >= item.UserLimit())
		{
			throw std::runtime_error("reach_limit");
		}


		CostPoint(user, item.Point());

		pShm->Accumulaive(params.Index(), 1);
		m_jsonData["a"][params.Index()] = exchanged + 1;

		Save();

		std::string op = "token_intensify_exchange_zone_item_"
				+ CTrans::UTOS(params.Index())
				+ "_"
				+ CTrans::UTOS(item.Point());
		this->AddEquips(item.ItemId(), item.Count(), op, result);

		result["info"] = m_jsonData;
	}

	return 0;
}

int TokenIntensifyUnit::ExchangeCommonImpl(UserWrap& user, const UnitIndexCmdParams& params, Json::Value& result)
{
	const DataTokenIntensify::GoodsItem& item = cfg_.GetGoodsItem(params.Index());

	int exchanged = m_jsonData["b"][params.Index()].asInt();
	if (exchanged >= item.UserLimit())
	{
		throw std::runtime_error("reach_limit");
	}

	CostPoint(user, item.Point());

	m_jsonData["b"][params.Index()] = exchanged + 1;
	Save();

	std::string op = "token_intensify_exchange_normal_item_"
			+ CTrans::UTOS(params.Index())
			+ "_"
			+ CTrans::UTOS(item.Point());
	this->AddEquips(item.ItemId(), item.Count(), op, result);

	result["info"] = m_jsonData;

	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////
WorldTreasureUnit::WorldTreasureUnit(const UserWrap& user)
	: BaseCmdUnit(user.Id())
	, cfg_(DataXmlPtr()->GetConfigWorldTreasure())
{
	unsigned now = Time::GetGlobalTime();
	unsigned nActVersion = Config::GetIntValue(CONFIG_WORLD_TREASURE_VER);
	if (now < Config::GetIntValue(CONFIG_WORLD_TREASURE_BEGIN_TS)
		|| now > Config::GetIntValue(CONFIG_WORLD_TREASURE_END_TS))
	{
		std::runtime_error("out_activty_peroid");
	}

	int ret = CLogicSecinc().GetSecinc(m_nUid, NAT_WORLD_TREASURE, m_jsonData);
	int ret1 = CLogicSecinc().GetSecinc(m_nUid, NAT_WORLD_TREASURE_EXT, m_jsonRecord);

	if ((ret != R_SUCCESS && ret != R_ERR_NO_DATA)
			|| (ret1 != R_SUCCESS && ret1 != R_ERR_NO_DATA))
	{
		throw std::runtime_error("get_new_active_data_error");
	}

	if (ret == R_ERR_NO_DATA
		|| ret1 ==  R_ERR_NO_DATA
		|| nActVersion != m_jsonData["v"].asInt())
	{
		m_jsonData["id"] = NAT_WORLD_TREASURE;
		m_jsonRecord["id"] = NAT_WORLD_TREASURE_EXT;

		Reset(nActVersion);
	}

}

void WorldTreasureUnit::SaveAll()
{
	BaseCmdUnit::Save();

	CLogicSecinc logicSecinc;
	int ret = logicSecinc.SetOneSecinc(m_nUid, m_jsonRecord);
	if (ret !=  R_SUCCESS)
	{
		throw std::runtime_error("Save_data_failed");
	}
}

void WorldTreasureUnit::Reset(unsigned nVersion)
{
	m_jsonData["v"] = nVersion;
	m_jsonData["n"] = 0; //密匙数量
	m_jsonData["m"] = 0; //密匙领取进度

	m_jsonData["a"] = Json::Value(Json::arrayValue);  //初级库
	m_jsonData["b"] = Json::Value(Json::arrayValue);  //中级库
	m_jsonData["c"] = Json::Value(Json::arrayValue);  //高级库
	m_jsonData["d"] = Json::Value(Json::arrayValue);  //天帝库

	ResetLibs();
}

void WorldTreasureUnit::ResetLibs()
{
	for (int type = 0;type < 4; type++)
	{
		Json::Value& json_Lib = ExtractedRecordLib(type);
		for (size_t k = 0; k < cfg_.GetGoodsLib(type).size(); k++)
		{
			json_Lib[k] = -1;
		}
	}

	m_jsonRecord["r"].clear();
	m_jsonRecord["r"] = Json::Value(Json::arrayValue);
}

bool WorldTreasureUnit::IsFull()
{
	for (int type = 0;type < 4; type++)
	{
		Json::Value& json_Lib = ExtractedRecordLib(type);
		for (size_t k = 0; k < cfg_.GetGoodsLib(type).size(); k++)
		{
			if (json_Lib[k].asInt() < 0)
			{
				return false;
			}
		}
	}

	return true;
}

int WorldTreasureUnit::DrawImpl(UserWrap& user, const BaseCmdParams& params, Json::Value& result)
{
	int total_point = user.GetRechargePoint(
		  Config::GetIntValue(CONFIG_WORLD_TREASURE_BEGIN_TS)
		, Config::GetIntValue(CONFIG_WORLD_TREASURE_END_TS));

	int stage = m_jsonData["m"].asInt();
	const ConfigWorldTreasure::AmountItem& cfg = cfg_.GetAmount(stage);

	if (total_point < cfg.Value())
	{
		error_log("total_point: %d, need: %d", total_point, cfg.Value());
		throw std::runtime_error("recharge_point_not_enough");
	}

	m_jsonData["m"] = stage + 1;
	m_jsonData["n"] = m_jsonData["n"].asInt() + cfg.Items();

	SaveAll();

	result["info"] = m_jsonData;

	return 0;
}

Json::Value& WorldTreasureUnit::ExtractedRecordLib(int type)
{
	switch (type)
	{
		case 0: return m_jsonData["a"];
		case 1: return m_jsonData["b"];
		case 2: return m_jsonData["c"];
		case 3: return m_jsonData["d"];
		default: {
			throw std::runtime_error("unknow_lib_type");
		}
	}
}

WorldTreasureExtractParams::WorldTreasureExtractParams(const Json::Value& jsonData)
	: UnitIndexCmdParams(jsonData)
{
	type_ = ValueAsInt("type");
}

int WorldTreasureUnit::ExtractImpl(UserWrap& user, const WorldTreasureExtractParams& params, Json::Value& result)
{
	int type = params.Type();
	int index = params.Index();
	int props = m_jsonData["n"].asInt();
	int cost_props =  cfg_.GetCostProps(type);
	if (props < cost_props)
	{
		throw std::runtime_error("props_not_enough");
	}

	//
	Json::Value& json_Lib = ExtractedRecordLib(type);
	if (index >= (int)json_Lib.size())
	{
		throw std::runtime_error("index_params_error");
	}

	if (json_Lib[index].asInt() >= 0)
	{
		throw std::runtime_error("the_position_already_extract");
	}

	std::vector<int> v_extracted;
	for (int i = 0; i < json_Lib.size(); i++)
	{
		int _v = json_Lib[i].asInt();
		if (_v >= 0)
		{
			v_extracted.push_back(_v);
		}

	}

	int idx = cfg_.RandomItem(v_extracted, type);

	json_Lib[index] = idx;
	m_jsonData["n"] = props - cost_props;

	Json::Value record;
	record[0u] = type;
	record[1u] = idx;
	m_jsonRecord["r"].append(record);

	if (IsFull())
	{
		ResetLibs();
	}

	const ConfigWorldTreasure::GoodsItem& item = cfg_.GetGoodsItem(idx, type);

	SaveAll();

	std::string op = "world_treasure_extract_op";
	this->AddEquips(item.Id(), item.Cnt(), op, result);

	result["info"] = m_jsonData;
	result["record"] = m_jsonRecord;

	return 0;
}
/////////////////////////////////////////////////////////////////////////////////////
SoulFeedbackUnit::SoulFeedbackUnit(const UserWrap& user)
	: BaseCmdUnit(user.Id())
	, cfg_(DataXmlPtr()->GetConfigSoulFeedback())
{
	unsigned now = Time::GetGlobalTime();
	unsigned nActVersion = Config::GetIntValue(CONFIG_SOUL_FEEDBACK_VER);
	if (now < Config::GetIntValue(CONFIG_SOUL_FEEDBACK_BEGIN_TS)
		|| now > Config::GetIntValue(CONFIG_SOUL_FEEDBACK_END_TS))
	{
		std::runtime_error("out_activty_peroid");
	}

	int ret = CLogicSecinc().GetSecinc(m_nUid, NAT_SOUL_FEEDBACK, m_jsonData);

	if (ret != R_SUCCESS && ret != R_ERR_NO_DATA)
	{
		throw std::runtime_error("get_new_active_data_error");
	}

	if (ret == R_ERR_NO_DATA
		|| nActVersion != m_jsonData["v"].asInt())
	{
		m_jsonData["id"] = NAT_SOUL_FEEDBACK;
		Reset(nActVersion);
	}

}

void SoulFeedbackUnit::Reset(unsigned nVersion)
{
	m_jsonData["v"] = nVersion;
	//
	m_jsonData["a"] = Json::Value(Json::arrayValue);
	for (int i = 0; i < cfg_.ItemsSize(); i++)
	{
		m_jsonData["a"][i] = 0;
	}
}

SoulFeedbackDrawParams::SoulFeedbackDrawParams(const Json::Value& jsonData)
	: UnitIndexCmdParams(jsonData)
{
	eq_index_ = ValueAsInt("eq_idx");
}

int SoulFeedbackUnit::DrawImpl(UserWrap& user, const SoulFeedbackDrawParams& params, Json::Value& result)
{
	int index = params.Index();
	int eqIdx = params.EquipIndex();
	const ConfigSoulFeedback::Item& reward_cfg = cfg_.GetRewards(index);
	if (m_jsonData["a"][index].asInt() > 0)
	{
		throw std::runtime_error("already_draw_reward");
	}

	int need_cost = reward_cfg.Amount();
	int total_point = user.GetRechargePoint(
				  Config::GetIntValue(CONFIG_SOUL_FEEDBACK_BEGIN_TS)
				, Config::GetIntValue(CONFIG_SOUL_FEEDBACK_END_TS));
	if (need_cost > total_point)
	{
		throw std::runtime_error("not_enough_recharge_point");
	}

	m_jsonData["a"][index] = 1;

	Save();

	int eqid = reward_cfg.EquipId(eqIdx);
	int eqcnt = reward_cfg.EquipCnt(eqIdx);
	std::string op = "soul_feedback_draw_op";
	this->AddEquips(eqid, eqcnt, op, result);

	result["info"] = m_jsonData;

	return 0;
}

//////////////////////////////////////////////////////////////
AwakenFeedbackUnit::AwakenFeedbackUnit(const UserWrap& user)
	: BaseCmdUnit(user.Id())
	, cfg_(DataXmlPtr()->GetConfigAwakenFeedback())
{
	unsigned now = Time::GetGlobalTime();
	unsigned nActVersion = Config::GetIntValue(CONFIG_AWAKEN_FEEDBACK_VER);
	if (now < Config::GetIntValue(CONFIG_AWAKEN_FEEDBACK_BEGIN_TS)
		|| now > Config::GetIntValue(CONFIG_AWAKEN_FEEDBACK_END_TS))
	{
		std::runtime_error("out_activty_peroid");
	}

	int ret = CLogicSecinc().GetSecinc(m_nUid, NAT_AWAKEN_FEEDBACK, m_jsonData);

	if (ret != R_SUCCESS && ret != R_ERR_NO_DATA)
	{
		throw std::runtime_error("get_new_active_data_error");
	}

	if (ret == R_ERR_NO_DATA
		|| nActVersion != m_jsonData["v"].asInt())
	{
		m_jsonData["id"] = NAT_AWAKEN_FEEDBACK;
		Reset(nActVersion);
	}
}

void AwakenFeedbackUnit::Reset(unsigned nVersion)
{
	m_jsonData["v"] = nVersion;
	//
	m_jsonData["a"] = Json::Value(Json::arrayValue);
	for (int i = 0; i < cfg_.ItemsSize(); i++)
	{
		m_jsonData["a"][i] = 0;
	}
}

int AwakenFeedbackUnit::DrawImpl(UserWrap& user, const SoulFeedbackDrawParams& params, Json::Value& result)
{
	int index = params.Index();
	int eqIdx = params.EquipIndex();
	const ConfigAwakenFeedback::Item& reward_cfg = cfg_.GetRewards(index);
	if (m_jsonData["a"][index].asInt() > 0)
	{
		throw std::runtime_error("already_draw_reward");
	}

	int need_cost = reward_cfg.Amount();
	int total_point = user.GetRechargePoint(
				  Config::GetIntValue(CONFIG_AWAKEN_FEEDBACK_BEGIN_TS)
				, Config::GetIntValue(CONFIG_AWAKEN_FEEDBACK_END_TS));
	if (need_cost > total_point)
	{
		throw std::runtime_error("not_enough_recharge_point");
	}

	m_jsonData["a"][index] = 1;

	Save();

	int eqid = reward_cfg.EquipId(eqIdx);
	int eqcnt = reward_cfg.EquipCnt(eqIdx);
	std::string op = "awaken_feedback_draw_op";
	this->AddEquips(eqid, eqcnt, op, result);

	result["info"] = m_jsonData;

	return 0;
}

//////////////////////////////////////////////////////////////
CastSoulUnit::CastSoulUnit(const UserWrap& user)
	: BaseCmdUnit(user.Id())
	, cfg_(DataXmlPtr()->GetConfigCastSoulDiscount())
{
	unsigned now = Time::GetGlobalTime();
	unsigned nActVersion = Config::GetIntValue(CONFIG_CAST_SOUL_VER);
	if (now < Config::GetIntValue(CONFIG_CAST_SOUL_BEGIN_TS)
		|| now > Config::GetIntValue(CONFIG_CAST_SOUL_END_TS))
	{
		throw std::runtime_error("out_activty_peroid");
	}

	int ret = CLogicSecinc().GetSecinc(m_nUid, NAT_CAST_SOUL, m_jsonData);

	if (ret != R_SUCCESS && ret != R_ERR_NO_DATA)
	{
		throw std::runtime_error("get_new_active_data_error");
	}

	if (ret == R_ERR_NO_DATA
		|| nActVersion != m_jsonData["v"].asInt())
	{
		m_jsonData["id"] = NAT_CAST_SOUL;
		Reset(nActVersion);
	}
}

void CastSoulUnit::Reset(unsigned nVersion)
{
	m_jsonData["v"] = nVersion;
	//
	m_jsonData["a"] = Json::Value(Json::arrayValue);
	for (int i = 0; i < cfg_.ItemsSize(); i++)
	{
		m_jsonData["a"][i] = 0;
	}
}

int CastSoulUnit::DrawImpl(UserWrap& user, const SoulFeedbackDrawParams& params, Json::Value& result)
{
	int index = params.Index();
	int eqIdx = params.EquipIndex();
	const ConfigSoulFeedback::Item& reward_cfg = cfg_.GetRewards(index);
	if (m_jsonData["a"][index].asInt() > 0)
	{
		throw std::runtime_error("already_draw_reward");
	}

	int need_cost = reward_cfg.Amount();
	int total_point = user.GetRechargePoint(
				  Config::GetIntValue(CONFIG_CAST_SOUL_BEGIN_TS)
				, Config::GetIntValue(CONFIG_CAST_SOUL_END_TS));
	if (need_cost > total_point)
	{
		throw std::runtime_error("not_enough_recharge_point");
	}

	m_jsonData["a"][index] = 1;

	Save();

	int eqid = reward_cfg.EquipId(eqIdx);
	int eqcnt = reward_cfg.EquipCnt(eqIdx);
	std::string op = "cast_soul_discount_op";
	this->AddEquips(eqid, eqcnt, op, result);

	result["info"] = m_jsonData;

	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////
GemDiscountUnit::GemDiscountUnit(const UserWrap& user)
	: BaseCmdUnit(user.Id())
	, cfg_(DataXmlPtr()->GetConfigGemDiscount())
{
	unsigned now = Time::GetGlobalTime();
	unsigned nActVersion = Config::GetIntValue(CONFIG_GEM_DISCOUNT_VER);
	if (now < Config::GetIntValue(CONFIG_GEM_DISCOUNT_BEGIN_TS)
		|| now > Config::GetIntValue(CONFIG_GEM_DISCOUNT_END_TS))
	{
		throw std::runtime_error("out_activty_peroid");
	}

	int ret = CLogicSecinc().GetSecinc(m_nUid, NAT_GEM_DISCOUNT, m_jsonData);
	if (ret != R_SUCCESS && ret != R_ERR_NO_DATA)
	{
		throw std::runtime_error("get_new_active_data_error");
	}

	if (ret == R_ERR_NO_DATA
		|| nActVersion != m_jsonData["v"].asInt())
	{
		m_jsonData["id"] = NAT_GEM_DISCOUNT;
		Reset(nActVersion);
	}
}


void GemDiscountUnit::Reset(unsigned nVersion)
{
	m_jsonData["v"] = nVersion;
	//每个物品领取的次数
	m_jsonData["a"] = Json::Value(Json::arrayValue);
	for (int i = 0; i < cfg_.ItemsSize(); i++)
	{
		m_jsonData["a"][i] = 0;
	}
	//总共领取的次数
	m_jsonData["b"] = 0;
}

//领取物品
int GemDiscountUnit::DrawImpl(UserWrap& user, const UnitIndexCmdParams& params, Json::Value& result)
{
	int idx = params.Index();
	const ConfigGemDiscount::Item& cfg = cfg_.GetItem(idx);

	int total_point = user.GetRechargePoint(
						  Config::GetIntValue(CONFIG_GEM_DISCOUNT_BEGIN_TS)
						, Config::GetIntValue(CONFIG_GEM_DISCOUNT_END_TS));
	if (m_jsonData["a"][idx].asInt() >= cfg.Limit())
	{
		throw std::runtime_error("single_goods_reach_limit");
	}

	int use_cnt = cfg_.GetUseCnt(total_point);
	if (use_cnt <= m_jsonData["b"].asInt())
	{
		throw std::runtime_error("reach_all_limit");
	}

	m_jsonData["a"][idx] = m_jsonData["a"][idx].asInt() + 1;
	m_jsonData["b"] = m_jsonData["b"].asInt() + 1;

	Save();

	std::string op = "gem_discount_draw_op";
	this->AddEquips(cfg.EquipId(), cfg.EquipCnt(), op, result);
	result["info"] = m_jsonData;

	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////
TreasureAroundUnit::TreasureAroundUnit(const UserWrap& user)
	: SecincActivityUnit(
		  user.Id()
		, "treasures_around"
		, NAT_TREASURES_AROUND)
	, cfg_(DataXmlPtr()->GetTreasureAllAround())
{
	Init();
}

void TreasureAroundUnit::Reset()
{
	m_jsonData["a"] = Json::arrayValue;
	for (int i = 0; i < cfg_.size(); i++)
	{
		m_jsonData["a"][i] = 0;
	}
}


int TreasureAroundUnit::DrawTenTimes(
		UserWrap& user, const UnitUdCmdParams& params, Json::Value& result)
{
	unsigned ud = params.Ud();
	Json::Value data;

	CLogicEquipment equipment;
	int ret = equipment.Get(m_nUid, ud,data);
	if(ret != 0)
	{
		return ret;
	}
	enum {
		costs = 3
	};

	const unsigned times = 10;
	if(data["count"].asInt() < costs * times)
	{
		error_log("use equip not enough uid=%u", m_nUid);
		return R_ERR_LOGIC;
	}

	for(int i = 0; i < times; ++i)
	{
		std::map<int, int> map_status;
		for (int i = 0; i < cfg_.size(); i++)
		{
			map_status[i] = m_jsonData["a"][i].asInt();
		}
		int idx = cfg_.RandomInLimits(map_status);

		std::string op = "treasure_around_draw_op";
		const JsonLotteryItemCfg& item_cfg = cfg_.Item(idx);
		Json::Value data;
		this->CostPurpleKey(params.Ud(), costs, op, data);
		if(item_cfg.IsLimit())
		{
			m_jsonData["a"][idx] = m_jsonData["a"][idx].asInt() + 1;
		}
		Save();


		this->AddEquips(item_cfg.GoodsId(), item_cfg.GoodsCnt(), op, data);
		if(data.isMember("equip_suit"))
		{
			result["equip_suit"].append(data["equip_suit"]);
		}
		result["equipments"].append(data["equipments"]);
		result["draw2"].append(idx);
	}
	result["equip_cost"] = costs * times;
	result["info"] = m_jsonData;

	//记录日志
	Json::FastWriter writer;
	string equipData = writer.write(result);
	EQUIPMENT_LOG("code=%s,data=%s", "DrawTenTimes", equipData.c_str());

	return 0;
}

int TreasureAroundUnit::DrawImpl(
		UserWrap& user, const UnitUdCmdParams& params, Json::Value& result)
{
	enum {
		costs = 3
	};

	std::map<int, int> map_status;
	for (int i = 0; i < cfg_.size(); i++)
	{
		map_status[i] = m_jsonData["a"][i].asInt();
	}
	int idx = cfg_.RandomInLimits(map_status);

	std::string op = "treasure_around_draw_op";
	const JsonLotteryItemCfg& item_cfg = cfg_.Item(idx);

	this->CostPurpleKey(params.Ud(), costs, op, result);
	if(item_cfg.IsLimit())
	{
		m_jsonData["a"][idx] = m_jsonData["a"][idx].asInt() + 1;
	}

	Save();

	this->AddEquips(item_cfg.GoodsId(), item_cfg.GoodsCnt(), op, result);
	result["info"] = m_jsonData;
	result["draw"] = idx;

	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////
SpiritFosterUnit::SpiritFosterUnit(const UserWrap& user)
	: BaseFeedbackActUnit(user.Id(), "spirit_foster", NAT_SPIRIT_FOSTER)
	, cfg_(DataXmlPtr()->GetSpiritFoster())
{
	Init();
}

////////////////////////////////////////////////////////////////////////////////////////
ChargeHorseUnit::ChargeHorseUnit(const UserWrap& user)
	: BaseFeedbackActUnit(user.Id(), CONFIG_CHARGE_HORSE, NAT_CHARGE_HORSE)
	, cfg_(DataXmlPtr()->GetChargeHorse())
{
	Init();
}

////////////////////////////////////////////////////////////////////////////////////////
void TurnLuckTable(int * prates, int len, int & target)
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
}

FortunatelyUnit::FortunatelyUnit(const UserWrap& user)
	: BaseCmdUnit(user.Id())
{
	int now = Time::GetGlobalTime();

	int start_time = 0, end_time = 0;

	start_time = Config::GetIntValue(CONFIG_FORTUNATELY_BEGIN_TS);
	end_time = Config::GetIntValue(CONFIG_FORTUNATELY_END_TS);

	if(now < start_time || now > end_time )
	{
		throw std::runtime_error("out_activity_time");
	}

	CLogicSecinc logicSecinc;
	int ret = logicSecinc.GetSecinc(m_nUid, NAT_FORTUNATELY_AGAIN, m_jsonData);

	if (R_ERR_NO_DATA == ret)
	{
		Json::Value array(Json::arrayValue);

		for(int i = 0; i < MAX_REWARD_ITEMS; ++i)
		{
			Json::Value temparray(Json::arrayValue);
			temparray[0u] = 0;     	//道具索引
			temparray[1u] = 0;      //道具所在奖池类型
			temparray[2u] = 0;     //是否抽中标志位

			array.append(temparray);
		}

		m_jsonData["a"] = array;    //保存转盘里面待抽奖的物品
		m_jsonData["v"] = 0;
		m_jsonData["id"] = NAT_FORTUNATELY_AGAIN;
	}
	else if (ret)
	{
		error_log("get newact error.uid=%u id=%d", user.Id(), NAT_FORTUNATELY_AGAIN);
		throw std::runtime_error("get_new_active_data_error");
	}
}

int FortunatelyUnit::CheckInitial(UserWrap& user, const BaseCmdParams& params, Json::Value& result)
{
	int ret = R_SUCCESS;

	unsigned version =  FortunatelyUnit::GetVersionCfg();

	if ( m_jsonData["v"].asUInt() != version) // 活动刚开启，或者活动重启
	{
		m_jsonData["v"] = version;

		//免费刷新
		Json::Value tempval;
		DoRefreshWheel(true,  result, tempval);

		//更新newact
		Save();

		result["newAct"] = m_jsonData;
	}

	return 0;
}

int FortunatelyUnit::RefreshWheel(UserWrap& user, const UnitUdCmdParams& params, Json::Value& result)
{
	int ret = R_SUCCESS;

	unsigned version =  FortunatelyUnit::GetVersionCfg();

	if ( m_jsonData["v"].asUInt() != version) // 活动刚开启，或者活动重启
	{
		m_jsonData["v"] = version;
	}

	Json::Value user_flag;
	user.GetUserFlag(user_flag);

	//花钻刷新
	DoRefreshWheel(false, result, user_flag, params.Ud());

	user.SetUserFlag(user_flag);
	//更新newact
	Save();
	
	result["newAct"] = m_jsonData;

	return 0;
}

int FortunatelyUnit::GetReward(UserWrap& user, const FortunatelyUnit::RewardParams& params, Json::Value& result)
{
	Json::Value user_flag;
	user.GetUserFlag(user_flag);
	unsigned version =  FortunatelyUnit::GetVersionCfg();
	int type = params.Type();

	if ( m_jsonData["v"].asUInt() != version) // 活动刚开启，或者活动重启
	{
		m_jsonData["v"] = version;

		Json::Value tempval;    //无用
		Json::Value temp2val;   //无用

		DoRefreshWheel(true, tempval, temp2val);   // 重新刷新奖池档
	}

	int cash = 0;

	//读档，判断抽奖了几次
	unsigned nums = 0;

	//扫描档，计算已经抽奖多少次
	for (unsigned int i = 0; i < m_jsonData["a"].size(); ++i)
	{
		if (m_jsonData["a"][i][2u] == 1)   //已抽
		{
			++nums;
		}
	}

	int prizetype = 0;

	if (2 == type)
	{
		if (nums > 0)
		{
			error_log("[GetReward] equipment is not complete. uid=%u, already-lottery-nums=%u", m_nUid, nums);
			throw std::runtime_error("optional_item_uncomplete");
		}

		prizetype = POOL_SEQUCENCE_ALL;   //一键领取
#ifdef SG_USE_CASH
		cash = 480;
#else
		cash = 96;
#endif
	}
	else
	{
		if (nums < 4)  //0-3
		{
			prizetype = POOL_SEQUENCE_ONE;
#ifdef SG_USE_CASH
			cash = 25;
#else
			cash = 5;
#endif
		}
		else if (nums < 6)  //4 - 5
		{
			prizetype = POOL_SEQUENCE_TWO;
#ifdef SG_USE_CASH
			cash = 60;
#else
			cash = 12;
#endif
		}
		else if (nums < 8)  //6 - 7
		{
			prizetype = POOL_SEQUENCE_THREE;
#ifdef SG_USE_CASH
			cash = 130;
#else
			cash = 26;
#endif
		}
		else
		{
			error_log("[GetReward] equipment have no optional item. uid=%u, already-lottery-nums=%u", m_nUid, nums);
			throw std::runtime_error("optional_item_empty");
		}
	}

	vector<ItemAdd> vctEquips;
	vector<unsigned> vctIndexs;

	int newactRates[MAX_REWARD_ITEMS] = {0};    //从newact中随机抽取下标
	bool isEmpty = true;

	// 0 -- 0,1,2,3  1-4,5    2-6,7
	if (POOL_SEQUENCE_ONE == prizetype || POOL_SEQUENCE_TWO == prizetype || POOL_SEQUENCE_THREE == prizetype)   //单个抽奖
	{
		//根据type和index，判断有哪些道具可供抽取
		for (unsigned i = 0; i < m_jsonData["a"].size(); ++i)
		{
			//1 - 道具是否被抽中的标志位， 1-type
			if (prizetype == m_jsonData["a"][i][1u].asInt() && 1 != m_jsonData["a"][i][2u].asInt())
			{
				isEmpty = false;
				newactRates[i] = DEFAULT_RATE_VALUE;
			}
		}

		if (isEmpty)
		{
			error_log("[GetReward] optional items is empty. type=%d", prizetype);
			throw std::runtime_error("optional_item_empty");
		}

		//从可选物品列表中抽取出一项
		int actIndex = 0;
		TurnLuckTable(newactRates, MAX_REWARD_ITEMS, actIndex);   //随机newact中插入的下标
		vctIndexs.push_back(m_jsonData["a"][actIndex][0u].asUInt() );

		m_jsonData["a"][actIndex][2u] = 1;    //修改是否已抽中的标志位

		result["index"] = actIndex;
	}
	else   //一键抽取，将newact档中的数据全给玩家
	{
		for (unsigned i = 0; i < m_jsonData["a"].size(); ++i)
		{
			vctIndexs.push_back(m_jsonData["a"][i][0u].asUInt() );
			m_jsonData["a"][i][2u] = 1;
		}
	}

	if (cash > 0)
	{
#ifdef SG_USE_CASH
		//先扣钻
		CLogicPay logicPay;
		DataPay   dataPay;

		int negativecash = -(cash);

		int coins = 0;

		bool bsave = false;

		int ret = logicPay.ProcessOrderForBackend(m_nUid, negativecash, coins, dataPay, "Fortunately_Again_GetReward", user_flag, bsave);

		if (ret)
		{
			error_log("[ProvideFortunatelyReward] ProcessOrderForBackend failed! uid=%u. ret=%d", m_nUid, ret);
			throw std::runtime_error("pay_cash_failed");
		}

		result["cash"] = dataPay.cash;
#else
		this->UseEquips(2024 , params.Ud(), cash, "Fortunately_Again_Refresh");
		result["equip_cost"] = cash;
#endif
	}

	ProvideFortunatelyReward(cash, vctIndexs, result, user_flag);

	user.SetUserFlag(user_flag);
	//更新newact
	Save();

	result["newAct"] = m_jsonData;

	return 0;
}

void FortunatelyUnit::ProvideFortunatelyReward(int cash, vector<unsigned> vctIndexs, Json::Value &result, Json::Value & user_flag)
{
	if (0 == vctIndexs.size())
	{
		error_log("[ProvideFortunatelyReward] param error. uid=%u", m_nUid);
		throw std::runtime_error("param_error");
	}

	int ret = R_SUCCESS;

	int equipindex = 0;
	vector<ItemAdd> vctEquips;   //普通装备
	vector<ItemAdd> vctEquipSuit;   //套装

	vector<string> vctHero;
	vector<string> vctcode;

	for(unsigned i = 0; i < vctIndexs.size(); ++i)
	{
		equipindex = vctIndexs[i];

		EquipmentInfo iteminfo;

		ret = DataXmlPtr()->GetSingleEquipItem(equipindex, iteminfo);

		if (ret)
		{
			error_log("[ProvideFortunatelyReward] get_iteminfo error. uid=%u", m_nUid);
			throw std::runtime_error("get_equipinfo_error");
		}

		if (0 == iteminfo.isHero)  //装备
		{
			ItemAdd equipitem;
			equipitem.eqid =  iteminfo.id;
			equipitem.count = iteminfo.count;
			equipitem.reason = "fortunately_again";

			//是否是套装
			if (IS_SET_EQID(equipitem.eqid ))
			{
				equipitem.ch = 5;
				vctEquipSuit.push_back(equipitem);
			}
			else
			{
				vctEquips.push_back(equipitem);
			}

		}
		else
		{
			char szHero[10] = {0};
			sprintf(szHero, "H%u", iteminfo.id);

			for(unsigned i = 0; i < iteminfo.count; ++i)
			{
				vctHero.push_back(szHero);
				vctcode.push_back("fortunately_again");
			}
		}
	}

	CLogicEquipment logicEquip;

	if (0 != vctEquips.size())
	{
		//给予玩家道具
		ret = logicEquip.AddItems(m_nUid, vctEquips, result["equip"], true);

		if(ret)
		{
			error_log("[ProvideFortunatelyReward] Add_Equip_error uid=%u， ret=%u", m_nUid, ret);
			throw std::runtime_error("add_equipitems_failed");
		}
	}

	//处理套装
	if (0 != vctEquipSuit.size())
	{
		Json::Value newEqDatas = Json::Value(Json::arrayValue);

		for (unsigned i = 0; i < vctEquipSuit.size(); ++i)
		{
			unsigned level = unsigned((vctEquipSuit[i].eqid - 150000) / 1000) * 10 + 50;   //套装等级

			unsigned subNum = getSubNumByCh(5);
			vector<EquipSub> sub;
			vector<string> keepstr;
			unsigned stoneID,gold;
			ret = DataXmlPtr()->GetEquipSub(level,stoneID,gold,subNum,keepstr,sub);
			Json::Value newSub;

			for(int j = 0; j < sub.size(); ++j)
				newSub[sub[j].id] = sub[j].value;

			ItemAdd item = vctEquipSuit[i];

			logicEquip.genEquipSet(item, newEqDatas, newSub, 1100);
		}

		ret = logicEquip.UpdateEquipment(m_nUid, 0, newEqDatas, result["equip_suit"], true);

		if(ret)
		{
			error_log("[ProvideReward] add equipment suit failed. uid=%u | equip_id=%u", m_nUid);
			throw std::runtime_error("add_equipmentsuit_failed");
		}
	}

	if (0 != vctHero.size())
	{
		CLogicHero logicHero;

		string heroid = vctHero[0];

		ret = logicHero.AddHeros(m_nUid, vctHero, vctcode, result["hero"]);

		if (ret)
		{
			error_log("[ProvideReward][AddHeros fail, uid=%u, heroid=%s]", m_nUid, heroid.c_str());
			throw std::runtime_error("add_heroitems_failed");
		}
	}
}

int FortunatelyUnit::getSubNumByCh(unsigned ch)
{
	const unsigned subNum[XML_EQUIP_SUB_GOLD + 2] = {0, 1, 3, 5, 5, 5};
	if(ch > XML_EQUIP_SUB_GOLD + 2 || 0 == ch)
		ch = 0;
	else
		--ch;
	return subNum[ch];
}

void FortunatelyUnit::DoRefreshWheel(bool isFree, Json::Value & result, Json::Value & user_flag, int ud)
{
	int ret = R_SUCCESS;

	//重置转盘
	for (unsigned i = 0; i < m_jsonData["a"].size(); ++i)
	{
		m_jsonData["a"][0u] = 0;
		m_jsonData["a"][1u] = 0;
		m_jsonData["a"][2u] = 0;
	}

	const int POOL_MAX = 3;

	int equipNums[POOL_MAX] = {4, 2, 2};

	XMLFortunatelyRewardItems rewarditems;

	int nIndex = 0;
	int newactRates[MAX_REWARD_ITEMS] = {DEFAULT_RATE_VALUE, DEFAULT_RATE_VALUE, DEFAULT_RATE_VALUE, DEFAULT_RATE_VALUE, DEFAULT_RATE_VALUE, DEFAULT_RATE_VALUE, DEFAULT_RATE_VALUE, DEFAULT_RATE_VALUE};    //等概率随机，初始为10

	int type = 0;
	set<unsigned> setItemIndex;

	for (int i = 0; i < POOL_MAX; ++i)
	{
		//先从池中众多不同权重的库中随机取出库
		switch(i)
		{
			case 0:	type = POOL_SEQUENCE_ONE;  break;
			case 1: type = POOL_SEQUENCE_TWO; break;
			case 2: type = POOL_SEQUENCE_THREE; break;

			default: throw std::runtime_error("pool_index_error"); break;
		}

		ret = DataXmlPtr()->GetFortunatelyRewardItem(type, rewarditems);

		if (ret)
		{
			error_log("[DoRefreshWheel] get pool items info error.");
			throw std::runtime_error("pool_index_error");
		}

		//从库中随机取出指定个数的装备
		int max = equipNums[i];

		for (int j = 0; j < max; ++j)
		{
			int wIndex = 0;

			TurnLuckTable(rewarditems.weightrate, MAX_WEIGHT_ITEMS, wIndex);   //得到装备二维数组的第一维度下标

			//获得库中所有物品的index
			int equiprates[MAX_EQUIPMENT_ITEMS] = {0};

			map<unsigned, unsigned> mapItemIndex;

			for(int k = 0; k < MAX_EQUIPMENT_ITEMS; ++k)  //获得装备集合对应的概率数组
			{
				if (rewarditems.weightItems[wIndex][k].index != 0)  //库中的装备都是等概率出现，所以我这里取默认概率10
				{
					equiprates[k] = 10;  //默认概率10
					mapItemIndex[k] = rewarditems.weightItems[wIndex][k].index;
				}
				else
				{
					break;
				}
			}

			int eIndex = 0;

			while(true)
			{
				TurnLuckTable(equiprates, MAX_EQUIPMENT_ITEMS, eIndex);    //随机选择库中的道具

				if (setItemIndex.end() == setItemIndex.find(mapItemIndex[eIndex]))   //第一次抽中
				{
					setItemIndex.insert(mapItemIndex[eIndex]);
					break;
				}
				else
				{
					equiprates[eIndex] = 0;
				}
			}

			TurnLuckTable(newactRates, MAX_REWARD_ITEMS, nIndex);   //随机newact中插入的下标

			Json::Value temparray(Json::arrayValue);

			temparray.append(mapItemIndex[eIndex]);
			temparray.append(type);   //类型
			temparray.append(0);    //标志位

			m_jsonData["a"][nIndex] = temparray;
			newactRates[nIndex] = 0;  //指定索引已经抽中，则重置概率为0
		}
	}

	if (!isFree)   //花钻
	{
#ifdef SG_USE_CASH
		//扣钻，刷新一次，10钻
		int cash = -10;

		CLogicPay logicPay;
		DataPay payData;
		bool bsave = false;

		ret = logicPay.ProcessOrderForBackend(m_nUid, cash, 0, payData, "Fortunately_Again_Refresh", user_flag, bsave);

		if (ret)
		{
			throw std::runtime_error("pay_cash_error");
		}

		result["cash"] = payData.cash;
#else
		int cost = 1;
		this->UseEquips(refresh_key , ud, cost, "Fortunately_Again_Refresh");
		result["equip_cost"] = 1;
#endif
	}
}

unsigned FortunatelyUnit::GetVersionCfg()
{
	unsigned nVersion = 0;

	if (! Config::GetUIntValue(nVersion, CONFIG_FORTUNATELY_VER))
	{
		error_log("get version config error");
		throw std::runtime_error("can't_get_version_cfg");
	}

	return nVersion;
}

void FortunatelyUnit::Save()
{
	CLogicSecinc logicSecinc;

	int ret = logicSecinc.SetOneSecinc(m_nUid, m_jsonData);

	if (ret !=  R_SUCCESS)
	{
		error_log("[Save] update secinc failed. uid=%u, id = %u, ret=%d", m_nUid, m_jsonData["id"].asUInt(), ret);
		throw std::runtime_error("Save_data_failed");
	}
}

TurnPlateUnit::TurnPlateUnit(const UserWrap& user)
	: BaseCmdUnit(user.Id())
{
	int start_time = 0, end_time = 0;

	start_time = Config::GetIntValue(CONFIG_MERRYSOULS_BEGIN_TS);
	end_time = Config::GetIntValue(CONFIG_MERRYSOULS_END_TS);

	unsigned now = Time::GetGlobalTime();
	if(now < start_time || now > end_time )
	{
		throw std::runtime_error("out_activity_time");
	}
}

int TurnPlateUnit::CheckInitial(UserWrap& user, const BaseCmdParams& params, Json::Value& result)
{
	int ret = R_SUCCESS;
	unsigned version =  TurnPlateUnit::GetVersionCfg();

	Json::Value stats;
	user.GetUserStats(stats);

	if ( stats["tpv"].asUInt() != version) // 活动刚开启，或者活动重启
	{
		stats["tpv"] = version;
		user.SetUserStats(stats);

		result["tpv"] = version;
		//免费刷新
		Json::Value tempval;
		DoRefreshWheel(result);
	}

	return 0;
}

unsigned TurnPlateUnit::GetVersionCfg()
{
	unsigned nVersion = 0;

	if (! Config::GetUIntValue(nVersion, CONFIG_MERRYSOULS_VERSION))
	{
		error_log("get version config error");
		throw std::runtime_error("can't_get_version_cfg");
	}

	return nVersion;
}

int TurnPlateUnit::RefreshWheel(UserWrap& user, const RefreshParams& params, Json::Value& result)
{
#ifdef SG_USE_CASH
	int ret = R_SUCCESS;
	int type = params.Type();

	int cash = 0;
	int coin = 0;
	if (REFRESH_BY_CASH == type)
	{
		cash = 10;
	}
	else
	{
		coin = 10;
	}
	user.CostAsset(cash, coin, "TURN_PLATE_REFRESH", result);
#else
	int cost = 1;
	this->UseEquips(refresh_key_low , params.Ud(), 1, "TURN_PLATE_REFRESH");
	result["equip_cost"] = cost;
#endif

	//花钻刷新
	DoRefreshWheel(result);

	return 0;
}


void TurnPlateUnit::DoRefreshWheel(Json::Value & result)
{
	int ret = R_SUCCESS;

	//重置转盘
	const int POOL_MAX = 4;
	const int MAX_LOCAL_VAL = 8;

	int equipNums[POOL_MAX] = {4, 2, 2, 10};

	XMLFortunatelyRewardItems rewarditems;

	int choujRates[MAX_CHOUJIANG_ITEMS] = {0};

	for (int j = 0; j < MAX_CHOUJIANG_ITEMS; ++j)
	{
		choujRates[j] = DEFAULT_RATE_VALUE;   //初始化概率值
	}

	int type = 0;
	set<unsigned> setItemIndex;    //存放选中道具的index值

	Json::Value gift;

	CLogicUserData logicuserdata;
	DataUserData userData;

	ret = logicuserdata.GetUserData(m_nUid, userData);

	if (ret)
	{
		error_log("[DoRefreshWheel] get userdata fail");
		throw std::runtime_error("get_userdata_error");
	}

	if (!userData.gift.empty())
	{
		Json::Reader reader;

		if (!reader.parse(userData.gift, gift))
		{
			error_log("[DoRefreshWheel] get gift fail");
			throw std::runtime_error("get_gift_error");
		}
	}

	int localcount = 0;
	int nIndex = 0;

	for (int i = 0; i < POOL_MAX; ++i)
	{
		//先从池中众多不同权重的库中随机取出库
		switch(i)
		{
			case 0:	type = POOL_TURN_SEQUENCE_ONE;  break;
			case 1: type = POOL_TURN_SEQUENCE_TWO; break;
			case 2: type = POOL_TURN_SEQUENCE_THREE; break;
			case 3: type = POOL_TURN_SEQUENCE_FOUR; break;

			default: throw std::runtime_error("pool_index_error"); break;
		}

		ret = DataXmlPtr()->GetTurnPlateRewardItem(type, rewarditems);

		if (ret)
		{
			error_log("[DoRefreshWheel] get pool items info error.");
			throw std::runtime_error("pool_index_error");
		}

		//从库中随机取出指定个数的装备
		int max = equipNums[i];

		for (int j = 0; j < max; ++j)
		{
			int wIndex = 0;

			TurnLuckTable(rewarditems.weightrate, MAX_WEIGHT_ITEMS, wIndex);   //得到装备二维数组的第一维度下标

			//获得库中所有物品的index
			int equiprates[MAX_EQUIPMENT_ITEMS] = {0};

			map<unsigned, unsigned> mapItemIndex;   //以同个权重下的道具所在的下标为key,value为道具在配置文件中的index值

			for(int k = 0; k < MAX_EQUIPMENT_ITEMS; ++k)  //获得装备集合对应的概率数组
			{
				if (rewarditems.weightItems[wIndex][k].index != 0)  //库中的装备都是等概率出现，所以我这里取默认概率10
				{
					equiprates[k] = 10;  //默认概率10
					mapItemIndex[k] = rewarditems.weightItems[wIndex][k].index;
				}
				else
				{
					break;
				}
			}

			int eIndex = 0;

			while(true)
			{
				TurnLuckTable(equiprates, MAX_EQUIPMENT_ITEMS, eIndex);    //随机选择库中的道具

				if (setItemIndex.end() == setItemIndex.find(mapItemIndex[eIndex]))   //第一次抽中
				{
					setItemIndex.insert(mapItemIndex[eIndex]);
					break;
				}
				else
				{
					equiprates[eIndex] = 0;
				}
			}

			if (!gift.isMember("choujiang"))   //localinfo节点不存在
			{
				InitGiftSub("choujiang", MAX_CHOUJIANG_ITEMS, gift);
			}

			//先将道具放入choujiang,用于界面展示
			TurnLuckTable(choujRates, MAX_CHOUJIANG_ITEMS, nIndex);   //随机newact中插入的下标
			choujRates[nIndex] = 0;  //指定索引已经抽中，则重置概率为0

			gift["choujiang"][nIndex]["index"]["value"] = mapItemIndex[eIndex];
			gift["choujiang"][nIndex]["isPrize"] = false;

			if (localcount < MAX_LOCAL_VAL)  //前面八次,将值放入localinfo
			{
				if (!gift.isMember("localinfo"))   //localinfo节点不存在
				{
					InitGiftSub("localinfo", MAX_LOCAL_VAL, gift);
				}

				gift["localinfo"][localcount]["value"] = nIndex;
			}

			localcount++;
		}
	}

	if (0 == gift["choujiangmsg"]["value"].asInt())
	{
		gift["choujiangmsg"]["value"] = 1;
		result["choujiangmsg"] = gift["choujiangmsg"];
	}

	Json::FastWriter writer;
	userData.gift = writer.write(gift);

	ret = logicuserdata.SetUserData(m_nUid, userData);

	if (ret)
	{
		error_log("[DoRefreshWheel] set userdata fail");
		throw std::runtime_error("set_userdata_error");
	}

	result["localinfo"] = gift["localinfo"];
	result["choujiang"] = gift["choujiang"];
}

void TurnPlateUnit::InitGiftSub(string key, int num, Json::Value & gift)
{
	if ("localinfo" == key)
	{
		Json::Value array(Json::arrayValue);

		for(int m = 0; m < num; ++m)
		{
			Json::Value temp;
			temp["value"] = 0;
			array.append(temp);
		}

		gift["localinfo"] = array;
	}
	else if ("choujiang" == key)
	{
		Json::Value array(Json::arrayValue);

		for(int m = 0; m < num; ++m)
		{
			Json::Value temp;

			Json::Value subtemp;

			subtemp["value"] = 0;

			temp["index"] = subtemp;

			temp["isPrize"] = false;
			array.append(temp);
		}

		gift["choujiang"] = array;
	}

	//初始化其他
	if (!gift.isMember("choujiangmsg"))
	{
		gift["choujiangmsg"]["value"] = 0;
	}

	if (!gift.isMember("cjfree"))
	{
		gift["cjfree"] = 2;
	}

	if (!gift.isMember("cjts"))
	{
		gift["cjts"] = 0;
	}
}

int TurnPlateUnit::GetReward(UserWrap& user, const RewardParams& params, Json::Value& result)
{
	int ret = R_SUCCESS;

	int cash = 0;

	//读档，判断抽奖了几次
	unsigned nums = 0;
	Json::Value gift;
	CLogicUserData logicuserdata;
	ret = logicuserdata.GetGift(m_nUid, gift);
	if (ret)
	{
		error_log("[DoRefreshWheel] get gift fail");
		throw std::runtime_error("get_gift_error");
	}

	//扫描档，计算已经抽奖多少次
	for (unsigned int i = 0; i < gift["choujiang"].size(); ++i)
	{
		if (gift["choujiang"][i]["isPrize"].asBool())   //已抽
		{
			++nums;
		}
	}

	vector<unsigned> vctIndexs;

	int prizetype = 0;

#ifdef SG_USE_CASH
	int firstcash = 25;
	int secondcash = 55;
	int thirdcash = 110;
#else
	int firstcash = 5;
	int secondcash = 11;
	int thirdcash = 22;
#endif

	int type = params.Type();
	if (2 == type)
	{
		if (nums > 0)
		{
			error_log("[GetReward] equipment is not complete. uid=%u, already-lottery-nums=%u", m_nUid, nums);
			throw std::runtime_error("optional_item_uncomplete");
		}

		cash = (firstcash*4) + (secondcash*2) + (thirdcash * 2);

		for (unsigned i = 0; i < gift["localinfo"].size(); ++i)
		{
			int cjindex = gift["localinfo"][i]["value"].asInt();

			if (cjindex < 0 || cjindex >= MAX_CHOUJIANG_ITEMS)
			{
				error_log("[GetReward] get choujiang's value error. uid=%u, local-index=%u", m_nUid, i);
				throw std::runtime_error("get_localinfo_value_error");
			}

			int equipindex = gift["choujiang"][cjindex]["index"]["value"].asInt();
			vctIndexs.push_back(equipindex);

			gift["choujiang"][cjindex]["isPrize"] = true;
		}
	}
	else
	{
		//判断免费次数是否存在
		if (gift["cjfree"].asInt() > 0)
		{
			cash = 0;
			gift["cjfree"] = gift["cjfree"].asInt() - 1;
			gift["cjts"] = Time::GetGlobalTime();

			result["cjfree"] = gift["cjfree"].asInt();
			result["cjts"] = gift["cjts"].asInt();
		}
		else if (nums < 4)  //0-3
		{
			cash = firstcash;
		}
		else if (nums < 6)  //4 - 5
		{
			cash = secondcash;
		}
		else if (nums < 8)  //6 - 7
		{
			cash = thirdcash;
		}
		else
		{
			error_log("[GetReward] equipment have no optional item. uid=%u, already-lottery-nums=%u", m_nUid, nums);
			throw std::runtime_error("optional_item_empty");
		}

		int cjindex = gift["localinfo"][nums]["value"].asInt();

		if (cjindex < 0 || cjindex >= MAX_CHOUJIANG_ITEMS)
		{
			error_log("[GetReward] get choujiang's value error. uid=%u, local-index=%u", m_nUid, nums);
			throw std::runtime_error("get_localinfo_value_error");
		}

		if (gift["choujiang"][cjindex]["isPrize"].asBool())
		{
			error_log("[GetReward] index already be prized. uid=%u, cjindex=%d", m_nUid, cjindex);
			throw std::runtime_error("already_get_prize");
		}

		int equipindex = gift["choujiang"][cjindex]["index"]["value"].asInt();
		vctIndexs.push_back(equipindex);
		gift["choujiang"][cjindex]["isPrize"] = true;
	}

	//更新gift
	ret = logicuserdata.SetGift(m_nUid, gift);
	if (ret)
	{
		error_log("[GetReward] set gift fail");
		throw std::runtime_error("set_gift_error");
	}

	//先扣钻
	if (cash > 0)
	{
#ifdef SG_USE_CASH
		user.CostAsset(cash, 0, "Turnplate_GetReward", result);
#else
		this->UseEquips(2024 , params.Ud(), cash, "Turnplate_GetReward");
		result["equip_cost"] = cash;
#endif
	}
	else if (vctIndexs.size() > 1)
	{
		error_log("[ProvideTrunPlateReward] cash = 0 only when choujiang = 1.now=%u", vctIndexs.size());
		throw std::runtime_error("logic_error");
	}

	ProvideTrunPlateReward(user, cash, vctIndexs, result);
	result["choujiang"] = gift["choujiang"];

	return 0;
}


void TurnPlateUnit::ProvideTrunPlateReward(UserWrap& userWrap, int cash, vector<unsigned> vctIndexs, Json::Value &result)
{
	if (0 == vctIndexs.size())
	{
		error_log("[ProvideTrunPlateReward] param error. uid=%u", m_nUid);
		throw std::runtime_error("param_error");
	}

	int ret = R_SUCCESS;

	int equipindex = 0;
	vector<ItemAdd> vctEquips;   //普通装备
	vector<ItemAdd> vctEquipSuit;   //套装

	vector<string> vctHero;
	vector<string> vctcode;

	for(unsigned i = 0; i < vctIndexs.size(); ++i)
	{
		equipindex = vctIndexs[i];

		EquipmentInfo iteminfo;

		ret = DataXmlPtr()->GetTurnPlateSingleEquipItem(equipindex, iteminfo);

		if (ret)
		{
			error_log("[ProvideTrunPlateReward] get_iteminfo error. uid=%u, index=%d", m_nUid, equipindex);
			throw std::runtime_error("get_equipinfo_error");
		}

		if (0 == iteminfo.isHero)  //装备
		{
			ItemAdd equipitem;
			equipitem.eqid =  iteminfo.id;
			equipitem.count = iteminfo.count;
			equipitem.reason = "turn_plate";

			//是否是套装
			if (IS_SET_EQID(equipitem.eqid ))
			{
				equipitem.ch = 5;
				vctEquipSuit.push_back(equipitem);
			}
			else
			{
				vctEquips.push_back(equipitem);
			}

		}
		else
		{
			char szHero[10] = {0};
			sprintf(szHero, "H%u", iteminfo.id);

			for(unsigned i = 0; i < iteminfo.count; ++i)
			{
				vctHero.push_back(szHero);
				vctcode.push_back("turn_plate");
			}
		}
	}

	CLogicEquipment logicEquip;

	if (0 != vctEquips.size())
	{
		//给予玩家道具
		ret = logicEquip.AddItems(m_nUid, vctEquips, result["equip"], true);

		if(ret)
		{
			error_log("[ProvideTrunPlateReward] Add_Equip_error uid=%u， ret=%u", m_nUid, ret);
			throw std::runtime_error("add_equipitems_failed");
		}
	}

	//处理套装
	if (0 != vctEquipSuit.size())
	{
		Json::Value newEqDatas = Json::Value(Json::arrayValue);

		for (unsigned i = 0; i < vctEquipSuit.size(); ++i)
		{
			unsigned level = unsigned((vctEquipSuit[i].eqid - 150000) / 1000) * 10 + 50;   //套装等级

			unsigned subNum = getSubNumByCh(5);
			vector<EquipSub> sub;
			vector<string> keepstr;
			unsigned stoneID,gold;
			ret = DataXmlPtr()->GetEquipSub(level, stoneID, gold, subNum, keepstr, sub);
			Json::Value newSub;

			for(int j = 0; j < sub.size(); ++j)
				newSub[sub[j].id] = sub[j].value;

			ItemAdd item = vctEquipSuit[i];

			logicEquip.genEquipSet(item, newEqDatas, newSub, 1100);
		}

		ret = logicEquip.UpdateEquipment(m_nUid, 0, newEqDatas, result["equip_suit"], true);

		if(ret)
		{
			error_log("[ProvideTrunPlateReward] add equipment suit failed. uid=%u | equip_id=%u", m_nUid);
			throw std::runtime_error("add_equipmentsuit_failed");
		}
	}

	if (0 != vctHero.size())
	{
		CLogicHero logicHero;

		string heroid = vctHero[0];

		ret = logicHero.AddHeros(m_nUid, vctHero, vctcode, result["hero"]);

		if (ret)
		{
			error_log("[ProvideTrunPlateReward][AddHeros fail, uid=%u, heroid=%s]", m_nUid, heroid.c_str());
			throw std::runtime_error("add_heroitems_failed");
		}
	}
}

int TurnPlateUnit::getSubNumByCh(unsigned ch)
{
	const unsigned subNum[XML_EQUIP_SUB_GOLD + 2] = {0, 1, 3, 5, 5, 5};
	if(ch > XML_EQUIP_SUB_GOLD + 2 || 0 == ch)
		ch = 0;
	else
		--ch;
	return subNum[ch];
}

RechargeOptionalUnit::RechargeOptionalUnit(unsigned uid):
	m_nUid(uid)
{
	CLogicSecinc logicSecinc;
	int ret = logicSecinc.GetSecinc(m_nUid, NAT_RECHARGE_OPTIONAL, m_jsonData);

	if (R_ERR_NO_DATA == ret)
	{
		m_jsonData["a"] = 0;    //活动期间充值数目
		m_jsonData["b"] = 0;    //领取次数
		m_jsonData["v"] = RechargeOptionalUnit::GetVersionCfg();   //版本号
		m_jsonData["id"] = NAT_RECHARGE_OPTIONAL;
	}
	else if (ret)
	{
		error_log("get newact error.uid=%u id=%d", uid, NAT_RECHARGE_OPTIONAL);
		throw std::runtime_error("get_new_active_data_error");
	}
}


void RechargeOptionalUnit::UpdateRecharge(unsigned cash)
{
	//判断版本号是否发生改变
	unsigned version = RechargeOptionalUnit::GetVersionCfg();

	if (version != m_jsonData["v"].asUInt())   //版本号发生改变，重置
	{
		ResetNewact(version);
	}

	m_jsonData["a"] = m_jsonData["a"].asUInt() + cash;

	//存档
	Save();
}

void RechargeOptionalUnit::GetOptionalReward(UserWrap& userWrap, unsigned rewardcnt,Json::Value &data, Json::Value & result)
{
	//判断版本号是否发生改变
	unsigned version = RechargeOptionalUnit::GetVersionCfg();

	if (version != m_jsonData["v"].asUInt())   //版本号发生改变，重置
	{
		ResetNewact(version);
	}

	int ret = R_SUCCESS;

	if (!data.isArray())
	{
		error_log("[GetOptionalReward] data param error.");
		throw std::runtime_error("param_error");
	}

	//获取dataxml对象
	CDataXML *dataXML = CDataXML::GetCDataXML();

	if(!dataXML)
	{
		error_log("[GetOptionalReward] GetCDataXML fail");
		throw std::runtime_error("get_cdataxml_error");
	}

	vector<unsigned> vctIds;
	vector<XMLOptionalItems> vctItems;

	for (unsigned i = 0; i < data.size(); ++i)
	{
		vctIds.push_back(data[i].asUInt());
	}

	unsigned per = 0;

	ret = dataXML->GetOptionalRewardItem(vctIds, vctItems, per);

	if (ret || 0 == per)
	{
		error_log("[GetOptionalReward] get optionalitem from dataxml error. uid = %u.ret = %d. per=%u", m_nUid, ret, per);
		throw std::runtime_error("get_optional_item_error");
	}

	//判断条件是否满足
	unsigned chargecash = 0;
	unsigned usedtime = 0;

	//从user_flag中获取充值额度
	unsigned start_time = Config::GetIntValue(CONFIG_RECHARGE_OPTIONAL_BEGIN_TS);
	unsigned now_time = Time::GetGlobalTime();
	chargecash = userWrap.GetRechargePoint(start_time, now_time);

	Json::GetUInt(m_jsonData, "b", usedtime);

	unsigned usedcash = per * usedtime;

	if (usedcash + per > chargecash)
	{
		error_log("[GetOptionalReward] conditon not match. uid = %u, chargecash=%u, usedtimes=%u", m_nUid, chargecash, usedtime);
		throw std::runtime_error("condition_not_match");
	}

	//条件判断完毕，准备发放道具
	vector<ItemAdd> vctEquips;

	for (unsigned i = 0; i < vctItems.size(); ++i)
	{
		ItemAdd item;

		item.eqid = vctItems[i].eqid;
		item.count = vctItems[i].count * rewardcnt;

		item.reason = "recharge_optional";

		vctEquips.push_back(item);
	}

	//给予玩家道具
	CLogicEquipment logicEquip;

	ret = logicEquip.AddItems(m_nUid, vctEquips, result["equip"], true);

	if(ret)
	{
		error_log("[GetOptionalReward] Add_Equip_error uid=%u， ret=%u", m_nUid, ret);
		throw std::runtime_error("add_equipitems_failed");
	}

	m_jsonData["b"] = m_jsonData["b"].asUInt() + rewardcnt;

	Save();

	result["newAct"] = m_jsonData;
}

void RechargeOptionalUnit::ResetNewact(unsigned version)
{
	m_jsonData["v"] = version;
	m_jsonData["a"] = 0;    //活动期间充值数目
	m_jsonData["b"] = 0;    //领取次数
}

void RechargeOptionalUnit::Save()
{
	CLogicSecinc logicSecinc;

	int ret = logicSecinc.SetOneSecinc(m_nUid, m_jsonData);

	if (ret !=  R_SUCCESS)
	{
		error_log("[Save] update secinc failed. uid=%u, id = %u, ret=%d", m_nUid, m_jsonData["id"].asUInt(), ret);
		throw std::runtime_error("Save_data_failed");
	}
}

unsigned RechargeOptionalUnit::GetVersionCfg()
{
	unsigned nVersion = 0;

	if (! Config::GetUIntValue(nVersion, CONFIG_RECHARGE_OPTIONAL_VER))
	{
		throw std::runtime_error("can't_get_version_cfg");
	}

	return nVersion;
}

bool RechargeOptionalUnit::IsActiving(unsigned nTime)
{
	unsigned beginTime = 0;
	unsigned endTime = 0;

	if (Config::GetUIntValue(beginTime, CONFIG_RECHARGE_OPTIONAL_BEGIN_TS)
		&& Config::GetUIntValue(endTime, CONFIG_RECHARGE_OPTIONAL_END_TS))
	{
		if (beginTime == 0 || endTime == 0)
		{
			return false;
		}

		if (endTime < beginTime)
		{
			error_log("Active time config error");
			throw std::runtime_error("Active_time_config_error");
		}

		//活动时间校验
		if (nTime < beginTime ||  nTime > endTime)
		{
			return false;
		}

		return true;
	}

	return false;
}

PayOptionalUnit::PayOptionalUnit(unsigned uid):
	m_nUid(uid)
{
	CLogicSecinc logicSecinc;
	int ret = logicSecinc.GetSecinc(m_nUid, NAT_VICKY_PAY, m_jsonData);

	if (R_ERR_NO_DATA == ret)
	{
		m_jsonData["a"] = 0;  //已领取奖励次数
		m_jsonData["v"] = 0;   //版本号
		m_jsonData["id"] = NAT_VICKY_PAY;
	}
	else if (ret)
	{
		error_log("get newact error.uid=%u id=%d", uid, NAT_VICKY_PAY);
		throw std::runtime_error("get_new_active_data_error");
	}
}

int PayOptionalUnit::CheckVersion(Json::Value & result)
{
	//判断版本号是否发生改变
	unsigned version = PayOptionalUnit::GetVersionCfg();

	if (version != m_jsonData["v"].asUInt())   //版本号发生改变，重置
	{
		ResetNewact(version);

		//存档
		Save();
		result["newAct"] = m_jsonData;
	}

	return 0;
}

void PayOptionalUnit::GetOptionalReward(UserWrap& userWrap, unsigned rewardcnt,Json::Value &data, Json::Value & result)
{
	//判断版本号是否发生改变
	CheckVersion(result);

	int ret = R_SUCCESS;

	if (!data.isArray())
	{
		error_log("data param error.");
		throw std::runtime_error("param_error");
	}

	//判断条件是否满足
	unsigned usedtime = 0;
	Json::GetUInt(m_jsonData, "a", usedtime);
	unsigned rewarded_cash = per_cash_one_times * usedtime;   //已领取过奖励的消费钻石数
	unsigned start_time = Config::GetIntValue(CONFIG_VICKY_PAY_BEGIN_TS);
	unsigned now = Time::GetGlobalTime();
	//获取指定时间段内的消费钻石数
	unsigned paycash = userWrap.GetCost(start_time, now).first;

	if (rewarded_cash + per_cash_one_times > paycash)
	{
		error_log("conditon not match. uid = %u, paycash=%u, usedtimes=%u", m_nUid, paycash, usedtime);
		throw std::runtime_error("condition_not_match");
	}

	//获取自选物品的配置
	CDataXML *dataXML = CDataXML::GetCDataXML();
	if(!dataXML)
	{
		error_log("GetCDataXML fail");
		throw std::runtime_error("get_cdataxml_error");
	}

	vector<unsigned> vctIds;
	vector<PayOptionalItem> vctItems;
	for (unsigned i = 0; i < data.size(); ++i)
	{
		vctIds.push_back(data[i].asUInt());
	}

	ret = dataXML->GetPayOptionalItem(vctIds, vctItems);

	if (ret)
	{
		error_log("get payoptionalitem from dataxml error. uid = %u.ret = %d", m_nUid, ret);
		throw std::runtime_error("get_payoptional_item_error");
	}

	//发放道具
	vector<ItemAdd> vctEquips;

	for (unsigned i = 0; i < vctItems.size(); ++i)
	{
		ItemAdd item;
		item.eqid = vctItems[i].equip.id;
		item.count = vctItems[i].equip.cnt * rewardcnt;
		item.reason = "pay_optional";

		vctEquips.push_back(item);
	}

	//给予玩家道具
	CLogicEquipment logicEquip;

	ret = logicEquip.AddItems(m_nUid, vctEquips, result["equip"], true);

	if(ret)
	{
		error_log("Add_Equip_error uid=%u， ret=%u", m_nUid, ret);
		throw std::runtime_error("add_equipitems_failed");
	}

	m_jsonData["a"] = m_jsonData["a"].asUInt() + rewardcnt;
	Save();

	result["newAct"] = m_jsonData;
}

void PayOptionalUnit::ResetNewact(unsigned version)
{
	m_jsonData["v"] = version;
	m_jsonData["a"] = 0;    //已领取奖励次数
}

unsigned PayOptionalUnit::GetVersionCfg()
{
	unsigned nVersion = 0;

	if (! Config::GetUIntValue(nVersion, CONFIG_VICKY_PAY_VER))
	{
		throw std::runtime_error("can't_get_version_cfg");
	}

	return nVersion;
}

void PayOptionalUnit::Save()
{
	CLogicSecinc logicSecinc;

	int ret = logicSecinc.SetOneSecinc(m_nUid, m_jsonData);

	if (ret !=  R_SUCCESS)
	{
		error_log("[Save] update secinc failed. uid=%u, id = %u, ret=%d", m_nUid, m_jsonData["id"].asUInt(), ret);
		throw std::runtime_error("Save_data_failed");
	}
}

HeroUpgrideUnit::HeroUpgrideUnit(unsigned uid):
		m_nUid(uid)
{
	CLogicSecinc logicSecinc;
	int ret = logicSecinc.GetSecinc(m_nUid, NAT_PRESENT_GIFT_UPGRADE, m_jsonData);

	if (R_ERR_NO_DATA == ret)
	{
		Json::Value array(Json::arrayValue);

		for(int i = 0; i < MAX_STAR_ITEMS; ++i)
		{
			array.append(0);
		}

		m_jsonData["a"] = array;    //4个可以升星的数组
		m_jsonData["b"] = 0;    //活动期间消耗招募令数目
		m_jsonData["v"] = HeroUpgrideUnit::GetVersionCfg();   //版本号
		m_jsonData["id"] = NAT_PRESENT_GIFT_UPGRADE;
	}
	else if (ret)
	{
		error_log("get newact error.uid=%u id=%d", uid, NAT_PRESENT_GIFT_UPGRADE);
		throw std::runtime_error("get_new_active_data_error");
	}
}

void HeroUpgrideUnit::UpdateZMLUsed(unsigned num)
{
	//判断版本号是否一致
	unsigned version = HeroUpgrideUnit::GetVersionCfg();

	if (version != m_jsonData["v"].asUInt())   //版本号发生改变，重置
	{
		ResetNewact(version);
	}

	m_jsonData["b"] = m_jsonData["b"].asUInt() + num;

	//存档
	Save();
}

void HeroUpgrideUnit::UpgrideHeroNew(UserWrap& userWrap, unsigned index, unsigned target, Json::Value& result)
{
	//判断版本号是否一致
	unsigned version = HeroUpgrideUnit::GetVersionCfg();

	if (version != m_jsonData["v"].asUInt())   //版本号发生改变，重置
	{
		ResetNewact(version);
	}

	int ret = R_SUCCESS;
	//判断参数
	if (index < 1 || index > MAX_STAR_ITEMS)
	{
		throw std::runtime_error("param_error");
	}

	//判断是否已经领取
	if (m_jsonData["a"][index-1].asInt() > 0)
	{
		error_log("[UpgrideHeroNew] already upgrade.uid=%u index=%u", m_nUid, index);
		throw std::runtime_error("already_upgrade");
	}

	//判断积分是否足够
	unsigned beginTime = 0;
	unsigned time_now = Time::GetGlobalTime();

	Config::GetUIntValue(beginTime, CONFIG_RECHARGE_SEND_UPGRADE_BEGIN_TS);

	unsigned cash_point = userWrap.GetRechargePoint(beginTime, time_now);
	unsigned zml_point = m_jsonData["b"].asUInt();

	unsigned all_point = cash_point + zml_point;

	unsigned point_limited[MAX_STAR_ITEMS] = {300, 1000, 5000, 10000};

	if (all_point < point_limited[index - 1])
	{
		error_log("[UpgrideHeroNew] point not enough.uid=%u now=%u, need=%u", m_nUid, all_point, point_limited[index - 1]);
		throw std::runtime_error("point_not_enough");
	}

	CLogicHero logicHero;
	map<unsigned,Json::Value> data;
	ret = logicHero.GetHero(m_nUid, data);

	if (ret)
	{
		error_log("[UpgrideHeroNew] get user's hero error.");
		throw std::runtime_error("get_user_hero_error");
	}

	if(!data.count(target))
	{
		error_log("[UpgrideHeroNew] target not exist");
		throw std::runtime_error("heroud_not_exists");
	}

	//300-4 1000-5 5000-6 10000-7
	unsigned star_limited[MAX_STAR_ITEMS] = {4, 5, 6, 7};

	if (!data[target].isMember("star") || !data[target].isMember("l") )
	{
		error_log("[UpgrideHeroNew] hero data error. no star or level. uid=%u heroud=%u", m_nUid, target);
		throw std::runtime_error("hero_data_error");
	}

	string heroid;

	if(!Json::GetString(data[target], "id", heroid))
	{
		error_log("[UpgrideHeroNew] hero data error, no id. uid=%u heroud=%u", m_nUid, target);
		throw std::runtime_error("hero_data_error");
	}

	unsigned star_target = data[target]["star"].asUInt();
	unsigned lv = data[target]["l"].asUInt();

	//判断等级和星级条件
	if (star_target != star_limited[index - 1] || lv < 70)
	{
		error_log("[UpgrideHeroNew] hero conditon not match. uid=%u heroud=%u,star=%u,need_star=%u,lv=%u", m_nUid, target, star_target, star_limited[index - 1], lv);
		throw std::runtime_error("hero_condition_not_match");
	}

	//条件都符合，直接给英雄升星
	data[target]["star"] = star_target + 1;

	ret = logicHero.Chg(m_nUid, target, data[target]);

	if(ret)
	{
		error_log("ChgHero arget fail uid=%u,target=%u", m_nUid, target);
		throw std::runtime_error("upgrade_hero_fail");
	}

	Json::FastWriter writer;
	string heroData = writer.write(data[target]);

	HERO_LOG("uid=%u,id=%u,heroid=%s,act=%s,code=%s,data=%s",m_nUid, target, heroid.c_str(),"up", "RechargeSendUpgrade", heroData.c_str());

	m_jsonData["a"][index - 1] = 1;

	result["star"] = data[target]["star"].asInt();
	result["newAct"] = m_jsonData;

	Save();
}

void HeroUpgrideUnit::ResetNewact(unsigned version)
{
	m_jsonData["v"] = version;

	for(int i = 0; i < MAX_STAR_ITEMS; ++i)
	{
		m_jsonData["a"][i] = 0;
	}

	m_jsonData["b"] = 0;    //领取次数
}

void HeroUpgrideUnit::Save()
{
	CLogicSecinc logicSecinc;

	int ret = logicSecinc.SetOneSecinc(m_nUid, m_jsonData);

	if (ret !=  R_SUCCESS)
	{
		error_log("[Save] update secinc failed. uid=%u, id = %u, ret=%d", m_nUid, m_jsonData["id"].asUInt(), ret);
		throw std::runtime_error("Save_data_failed");
	}
}

unsigned HeroUpgrideUnit::GetVersionCfg()
{
	unsigned nVersion = 0;

	if (! Config::GetUIntValue(nVersion, CONFIG_RECHARGE_SEND_UPGRADE_VER))
	{
		throw std::runtime_error("can't_get_version_cfg");
	}

	return nVersion;
}

bool HeroUpgrideUnit::IsActiving(unsigned nTime)
{
	unsigned beginTime = 0;
	unsigned endTime = 0;

	if (Config::GetUIntValue(beginTime, CONFIG_RECHARGE_SEND_UPGRADE_BEGIN_TS)
		&& Config::GetUIntValue(endTime, CONFIG_RECHARGE_SEND_UPGRADE_END_TS))
	{
		if (beginTime == 0 || endTime == 0)
		{
			return false;
		}

		if (endTime < beginTime)
		{
			error_log("Active time config error");
			throw std::runtime_error("Active_time_config_error");
		}

		//活动时间校验
		if (nTime < beginTime ||  nTime > endTime)
		{
			return false;
		}

		return true;
	}

	return false;
}


HeroTrainUnit::HeroTrainUnit(unsigned uid):
		BaseCmdUnit(uid)
{

}

void HeroTrainUnit::StartTrain(UserWrap& userWrap, unsigned heroud, unsigned index, unsigned blv, Json::Value & result)
{
	int ret = R_SUCCESS;

	if (index >= MAX_INDEX_ITEM)
	{
		error_log("[HeroTrainUnit] wrong index param. uid=%u, index=%u", m_nUid, index);
		throw std::runtime_error("param_error");
	}

	CLogicHero logicHero;

	ret = logicHero.Get(m_nUid, heroud, m_jsonData);
	//判断训练是否有位
	if (ret)
	{
		throw std::runtime_error("get_hero_data_error");
	}

	//判断武将是否正在训练中
	if (m_jsonData.isMember("tcd") && 0 != m_jsonData["tcd"].asInt())
	{
		error_log("[StartTrain] hero is trainning. uid=%u, heroud=%u", m_nUid, heroud);
		throw std::runtime_error("hero_is_trainning");
	}

	//判断是否有训练空间

	//武将训练
	Json::Value trainq;
	ret = userWrap.GetUserTrainQ(trainq);

	if (ret)
	{
		throw std::runtime_error("get_hero_trainq_error");
	}

	bool isHaveSpace = false;

	int sec = HOUR_INDEX[index] * 3600;   //秒数
	int queue_index = 0;

	for (int i = 0; i < MAX_QUEUE_ITEMS; ++i)
	{
		char szkey[4] = {0};
		sprintf(szkey, "i%d", i);

		if (!trainq.isMember(szkey))   //队列空间不存在
		{
			break;
		}

		if (trainq[szkey].isMember("i") && trainq[szkey]["i"]["hud"].asUInt() != heroud)   //队列正在使用中，且使用中 的英雄非传递过来的英雄
		{
			continue;
		}

		if (trainq[szkey]["o"].asInt() == 0 && sec > trainq[szkey]["r"].asInt())  //队列非永久使用，且剩余时间不足够训练所需
		{
			continue;
		}

		isHaveSpace = true;
		queue_index = i;
		break;
	}

	if (!isHaveSpace)   //没有空间
	{
		error_log("[StartTrain] no queue can be used. uid=%u", m_nUid);
		throw std::runtime_error("have_no_queue");
	}

	//先扣金币和战魂
	int cash = 0;
	int coin = COIN_INDEX[index];

	int herolv =  m_jsonData["l"].asInt();
	int battle = 0;

	if(herolv < 60)
	{
		battle = (int)HOUR_INDEX[index] * (0.05 * pow((herolv * 0.4 + 40), 2.6) - 730);
	}
	else
	{
		battle = (int)HOUR_INDEX[index] * (0.05 * pow((herolv * 1.3 - 17), 2.6) - 730);
	}

	int exp = 0;

	exp = (int) HOUR_INDEX[index] * ((0.0022 * pow(herolv, 3) - 0.3607 * pow(herolv, 2) + 36.816 * herolv + 68.482) * (1 + blv * 0.01)) * 13.3;

	userWrap.ChangeBattle(-battle, "HERO_TRAIN");

	result["battle_spirits"] = userWrap.GetBattleSpirits();

	ret = userWrap.CostAsset(cash, coin, "START_HERO_TRAIN", result);

	if (ret)
	{
		throw std::runtime_error("cost_coin_error");
	}

	//使用训练队列
	char qkey[4] = {0};
	sprintf(qkey, "i%d", queue_index);

	Json::Value idata;

	idata["hid"] = m_jsonData["id"].asString();
	idata["hud"] = heroud;
	idata["l"] = herolv;

	trainq[qkey]["i"] = idata;

	int now = Time::GetGlobalTime();
	trainq["upts"] = now;

	//修改英雄的一些信息
	m_jsonData["tcd"] = sec;
	m_jsonData["ctcd"] = exp;
	m_jsonData["tt"] = HOUR_INDEX[index];
	m_jsonData["cate"] = true;
	//m_jsonData["upts"] = now;

	Save();   //保存英雄信息

	result["hero"] = m_jsonData;

	ret = userWrap.SetUserTrainQ(trainq);

	if (ret)
	{
		throw std::runtime_error("set_hero_train_error");
	}

	result["trainQ"] = trainq;
}

void HeroTrainUnit::ImproveTrainExp(UserWrap& userWrap, unsigned equd, unsigned tindex, Json::Value & result)
{
	int ret = R_SUCCESS;

	//武将训练
	Json::Value trainq;
	ret = userWrap.GetUserTrainQ(trainq);

	if (ret)
	{
		throw std::runtime_error("get_hero_trainq_error");
	}

	char qkey[4] = {0};
	sprintf(qkey, "i%u", tindex);

	if (!trainq.isMember(qkey))
	{
		error_log("[ImproveTrainExp] trainQ don't have key:[%s]. uid=%u", qkey, m_nUid);
		throw std::runtime_error("param_error");
	}

	if (!trainq[qkey].isMember("i"))
	{
		error_log("[ImproveTrainExp] trainQ 's key:[%s] don't trainning. uid=%u", qkey, m_nUid);
		throw std::runtime_error("param_error");
	}

	unsigned heroud = trainq[qkey]["i"]["hud"].asUInt();

	CLogicHero logicHero;

	ret = logicHero.Get(m_nUid, heroud, m_jsonData);
	//判断训练是否有位
	if (ret)
	{
		throw std::runtime_error("get_hero_data_error");
	}

	//获得时间对应的值
	int index = 0;

	for (int i = 0; i < MAX_INDEX_ITEM; ++i)
	{
		if (HOUR_INDEX[i] == m_jsonData["tt"].asInt())
		{
			index = i;
			break;
		}
	}

	//判断是否可以使用道具
	if (m_jsonData.isMember("cate") && !m_jsonData["cate"].asBool() )  //false，不能用
	{
		error_log("[ImproveTrainExp] improve's equipment can not be use. uid=%u, heroud=%u", m_nUid, heroud);
		throw std::runtime_error("euipment_can_not_use");
	}

	//先扣道具
	CLogicEquipment equipment;
	Json::Value equipdata;

	ret = equipment.Get(m_nUid, equd, equipdata);

	if (ret)
	{
		throw std::runtime_error("get_equip_error");
	}

	unsigned count = EQUIP_NUM_INDEX[index];

	UseEquips(SUN_ZI_BING_FA_EQID, equd, count, "Hero_TrainEXP_Improve");

	//翻1.5倍经验
	m_jsonData["cate"] = false;

	int oldexp = m_jsonData["ctcd"].asInt();
	int newexp = (int) oldexp * (float)1.5;

	m_jsonData["ctcd"] = newexp;
	//m_jsonData["upts"] = Time::GetGlobalTime();

	Save();   //保存英雄信息
	result["hero"] = m_jsonData;
}

void HeroTrainUnit::EndTrain(UserWrap& userWrap, unsigned type, unsigned tindex, Json::Value & result)
{
	int ret = R_SUCCESS;

	if (END_TRAIN_BY_CASH != type && END_TRAIN_BY_COIN != type)
	{
		error_log("[EndTrain] type's value error");
		throw std::runtime_error("param_error");
	}

	//武将训练
	Json::Value trainq;
	ret = userWrap.GetUserTrainQ(trainq);

	if (ret)
	{
		throw std::runtime_error("get_hero_trainq_error");
	}

	char qkey[4] = {0};
	sprintf(qkey, "i%u", tindex);

	if (!trainq.isMember(qkey))
	{
		error_log("[EndTrain] trainQ don't have key:[%s]. uid=%u", qkey, m_nUid);
		throw std::runtime_error("param_error");
	}

	if (!trainq[qkey].isMember("i"))
	{
		error_log("[EndTrain] trainQ 's key:[%s] don't trainning. uid=%u", qkey, m_nUid);
		throw std::runtime_error("param_error");
	}

	unsigned heroud = trainq[qkey]["i"]["hud"].asUInt();

	CLogicHero logicHero;

	ret = logicHero.Get(m_nUid, heroud, m_jsonData);
	//判断训练是否有位
	if (ret)
	{
		throw std::runtime_error("get_hero_data_error");
	}

	//获得时间对应的值
	int index = 0;

	for (int i = 0; i < MAX_INDEX_ITEM; ++i)
	{
		if (HOUR_INDEX[i] == m_jsonData["tt"].asInt())
		{
			index = i;
			break;
		}
	}

	int leftTime = 0;
	int now = Time::GetGlobalTime();
	int diff_time = now - m_jsonData["upts"].asInt();

	if (diff_time < 0 )   //处理修改服务器时间可能导致的问题
	{
		error_log("[EndTrain] time error. now is less than upts.uid=%u,now=%d,upts=%d", m_nUid, now, m_jsonData["upts"].asInt());
		throw std::runtime_error("upts_time_error");
	}

	Json::GetInt(m_jsonData, "tcd", leftTime);
	leftTime -= diff_time;

	if (leftTime < 0)
	{
		leftTime = 0;
	}

	//计算要扣的钻数
	double pay1 = pow(leftTime/(double)60, 0.9);
	double pay2	= pow(leftTime/(double)3600, 0.9);

	int pay = (int)ceil(pay1 - pay2);

	int cash = 0;
	int coin = 0;

	if (END_TRAIN_BY_CASH == type)
	{
		cash = pay;
	}
	else
	{
		coin = pay;
	}

	if (pay > 0)
	{
		userWrap.CostAsset(cash, coin, "END_HERO_TRAIN", result);
	}

	int addexp = m_jsonData["ctcd"].asInt();

	//获取人物等级
	int ulevel = userWrap.GetUserLevel();

	AddHeroExp(m_jsonData, ulevel, addexp);

	m_jsonData["tcd"] = 0;
	m_jsonData["tt"] = 0;
	m_jsonData["ctcd"] = 0;
	//m_jsonData["upts"] = now;

	Save();   //保存英雄信息

	result["hero"] = m_jsonData;
	//修改trainQ信息
	trainq[qkey].removeMember("i");

	ret = userWrap.SetUserTrainQ(trainq);

	if (ret)
	{
		throw std::runtime_error("set_hero_train_error");
	}

	result["trainQ"] = trainq;
}

void HeroTrainUnit::Save()
{
	CLogicHero logicHero;

	unsigned heroud = m_jsonData["ud"].asUInt();

	int ret = logicHero.Chg(m_nUid, heroud, m_jsonData);

	if (ret)
	{
		error_log("[Save] update hero failed. uid=%u, heroud=%u", m_nUid, heroud);
		throw std::runtime_error("update_hero_error");
	}
}

SoldierUnit::SoldierUnit(unsigned uid):
		m_nUid(uid)
{
	m_pdataXML = CDataXML::GetCDataXML();

	if(!m_pdataXML)
	{
		error_log("GetInitXML fail");
		throw std::runtime_error("GetInitXML fail");
	}
}

int SoldierUnit::GetResourceCost(unsigned resource)
{
	double p1 = pow(resource/(double)10, 0.5);
	double p2  = pow(resource/(double)1000, 0.5);
	double p3  = pow(resource/(double)100000, 0.5);

	int result = (int) ceil(p1-p2-p3);

	if (result < 1 && resource > 0)
		result = 1;

	return result;
}

int SoldierUnit::GetSoldierTimeCost(unsigned lefttime)
{
	double p1 = pow(lefttime/(double)60, 0.98);
	double p2  = pow(lefttime/(double)3600, 0.98);

	int result = (int) ceil(p1-p2);

	return result;
}

int SoldierUnit::GetTrainNeedSoul(unsigned char grade, int level)
{
	double result = 0;

	if(1 == grade)
	{
		if(level < 60)
		{
			result = 0.35 * pow((0.7 * level), 2.2) + level;
		}
		else
		{
			result = 0.35 * pow((1.3 * level - 36), 2.2) + level;
		}
	}
	else if(2 == grade)
	{
		if(level < 60)
		{
			result = 0.4 * pow((0.7 * level), 2.2) + level + 5;
		}
		else
		{
			result = 0.4 * pow((1.3 * level - 36), 2.2) + level + 5;
		}
	}
	else if(3 == grade)
	{
		if(level < 60)
		{
			result = 0.45 * pow((0.7 * level), 2.2) + 2 * level + 10;
		}
		else
		{
			result = 0.45 * pow((1.3 * level - 36), 2.2) + 2 * level + 10;
		}
	}
	else if(4 == grade)
	{
		if(level < 60)
		{
			result = 0.5 * pow((0.7 * level), 2.2) + 3 * level + 20;
		}
		else
		{
			result = 0.5 * pow((1.3 * level - 36), 2.2) + 3 * level + 20;
		}
	}
	else if(5 == grade)
	{
		if(level < 60)
		{
			result = 0.55 * pow((0.7 * level), 2.2) + 4 * level + 20;
		}
		else
		{
			result = 0.55 * pow((1.3 * level - 36), 2.2) + 4 * level + 20;
		}
	}

	int soul = result;

	return soul;
}

int SoldierUnit::GetResearchNeedSoul(unsigned char grade, int level)
{
	double result = 0;

	if(1 == grade)
	{
		result = 0.1 * pow((level + 40), 2) - 160;
	}
	else if(2 == grade)
	{
		result = 0.1 * pow((level + 40), 2.1) - 220;
	}
	else if(3 == grade)
	{
		if(level < 60)
		{
			result = 3 * pow((0.1 * level + 50), 2.4) - 35860;
		}
		else
		{
			result = 3 * pow((1.1 * level - 11), 2.4) - 35860;
		}
	}
	else if(4 == grade)
	{
		if(level < 60)
		{
			result = 3 * pow((0.1 * level + 50), 2.6) - 78400;
		}
		else
		{
			result = 3 * pow((1.1 * level - 11), 2.6) - 78400;
		}
	}
	else if(5 == grade)
	{
		if (level < 60)
		{
			result = 3 * pow((0.1 * level + 50), 2.8) - 171000;
		}
		else
		{
			result = 3 * pow((1.1 * level - 11), 2.8) - 171000;
		}
	}

	int soul = (int)round(result);

	return soul;
}

int SoldierUnit::AddSoldiers(Json::Value & soldier, int count, string sid)
{
	unsigned i = 0;
	//遍历兵营，查看当前兵种的索引
	for (; i < soldier.size(); ++i)
	{
		if (sid == soldier[i]["id"].asString())
		{
			break;
		}
	}

	if (i < soldier.size())  //找到退出循环
	{
		soldier[i]["amount"] = soldier[i]["amount"].asUInt() + count;
	}
	else  //遍历全部后退出，表示兵营中不存在此类兵种
	{
		Json::Value addsoldier;
		addsoldier["id"] = sid;
		addsoldier["amount"] = count;

		soldier.append(addsoldier);
	}

	return R_SUCCESS;
}

void SoldierUnit::StartTrain(UserWrap& userWrap, string sid, int count, unsigned stype, unsigned costtype, Json::Value &result)
{
	int ret = R_SUCCESS;

	if (START_SOLDIER_BY_RESOURCE != stype && START_SOLDIER_BY_COIN != stype)
	{
		error_log("[StartTrain] type param error. uid=%u", m_nUid);
		throw std::runtime_error("param error");
	}

	Json::Value barrackq;
	userWrap.GetUserBarrackQ(barrackq);

	Json::Value soldierlevel;
	userWrap.GetUserSoldierLevel(soldierlevel);

	//加载研究院的小兵信息
	if (!soldierlevel.isMember(sid))
	{
		error_log("[StartTrain] soldier unlocked. uid=%u, sid=%s", m_nUid, sid.c_str());
		throw std::runtime_error("param error");
	}

	//读取配置，获取小兵训练所需的时间
	unsigned char grade = 0;
	XMLSoldierLevelItems solderitem;

	int id = CTrans::STOI(sid.substr(1).c_str());
	unsigned slevel = soldierlevel[sid]["l"].asUInt();

	ret = m_pdataXML->GetSoldierLevelItem(id, slevel, solderitem, grade);

	if (ret)
	{
		error_log("[StartTrain] get soldierlevelitem error. uid=%u, sid=%s", m_nUid, sid.c_str());
		throw std::runtime_error("get_soldierlevelitem_error");
	}

	if (START_SOLDIER_BY_COIN == stype)   //花金币训练
	{
		int singlecoin = 0;

		if (1 == solderitem.silvertype)
		{
			singlecoin = GetResourceCost(solderitem.silver) + GetSoldierTimeCost(solderitem.ptime);
		}
		else
		{
			singlecoin = GetResourceCost(solderitem.silver / 2) + GetSoldierTimeCost(solderitem.ptime);
		}

		//扣金币
		int pay = count * singlecoin;

		int cash = 0;
		int coin = 0;

		if (END_SOLDIER_BY_CASH == costtype)
		{
			cash = pay;
		}
		else if (END_SOLDIER_BY_COIN == costtype)
		{
			coin = pay;
		}
		else
		{
			error_log("[StartTrain] costtype's value error, uid=%u", m_nUid);
			throw std::runtime_error("param_error");
		}

		userWrap.CostAsset(cash, coin, "START_SOLDIER_TRAIN", result);

		//直接将兵塞进兵营中
		Json::Value soldier;
		userWrap.GetUserSoldier(soldier);
		AddSoldiers(soldier, count, sid);
		userWrap.SetUserSoldier(soldier);

		result["soldier"] = soldier;

		return ;
	}

	//消耗资源的训练
	int sec = solderitem.ptime;  //生产需要的时间
	bool isHaveSpace = false;
	int queue_index = 0;

	for (int i = 0; i < MAX_QUEUE_ITEMS; ++i)
	{
		char szkey[4] = {0};
		sprintf(szkey, "i%d", i);

		if (!barrackq.isMember(szkey))   //队列空间不存在
		{
			break;
		}

		if (barrackq[szkey].isMember("i") && 0 != barrackq[szkey]["i"]["c"].asInt())   //队列正在使用中
		{
			continue;
		}

		if (barrackq[szkey]["o"].asInt() == 0 && (sec * count) > barrackq[szkey]["r"].asInt())  //队列非永久使用，且剩余时间不足够训练所需
		{
			continue;
		}

		isHaveSpace = true;
		queue_index = i;
		break;
	}

	if (!isHaveSpace)   //没有空间
	{
		error_log("[StartTrain] no queue can be used. uid=%u", m_nUid);
		throw std::runtime_error("have_no_queue");
	}

	//消耗粮食
	int r1 = -solderitem.silver;
	r1 *= count;

	userWrap.ChangeResource(r1, 0, 0, 0, "SOLDIER_TRAIN", result);   //内部会抛异常

	int soul = GetTrainNeedSoul(grade, slevel);
	soul *= count;

	userWrap.ChangeBattle(-soul, "SOLDIER_TRAIN");

	result["battle_spirits"] = userWrap.GetBattleSpirits();

	//开始训练
	char qkey[4] = {0};
	sprintf(qkey, "i%d", queue_index);

	Json::Value idata;

	idata["att"] = 0;
	idata["c"] = count;
	idata["id"] = sid;
	idata["lt"] = sec;

	barrackq[qkey]["i"] = idata;
	userWrap.SetUserBarrackQ(barrackq);

	result["barrackQ"] = barrackq;
}

void SoldierUnit::EndTrain(UserWrap& userWrap, unsigned bindex, unsigned etype, Json::Value &result)
{
	//直接消耗金币或者钻石，将队列中兵种的剩余兵全部放入兵营
	int ret = R_SUCCESS;

	if (END_SOLDIER_BY_CASH != etype && END_SOLDIER_BY_COIN != etype)
	{
		error_log("[EndTrain] etype's value error, uid=%u", m_nUid);
		throw std::runtime_error("param_error");
	}

	//武将训练
	Json::Value barrackq;
	userWrap.GetUserBarrackQ(barrackq);

	char qkey[4] = {0};
	sprintf(qkey, "i%u", bindex);

	if (!barrackq.isMember(qkey))
	{
		error_log("[EndTrain] barrackQ don't have key:[%s]. uid=%u", qkey, m_nUid);
		throw std::runtime_error("param_error");
	}

	if (!barrackq[qkey].isMember("i"))
	{
		error_log("[EndTrain] barrackQ 's key:[%s] don't trainning. uid=%u", qkey, m_nUid);
		throw std::runtime_error("param_error");
	}

	if (0 == barrackq[qkey]["i"]["c"].asInt())
	{
		return ;
	}

	//立即完成，先扣钻或者金币
	Json::Value soldierlevel;
	userWrap.GetUserSoldierLevel(soldierlevel);   //为了获取小兵当前等级

	//读取配置，获取小兵训练所需的时间
	unsigned char grade = 0;
	XMLSoldierLevelItems soldieritem;

	string sid = barrackq[qkey]["i"]["id"].asString();

	int id = CTrans::STOI(sid.substr(1).c_str());
	unsigned slevel = soldierlevel[sid]["l"].asUInt();

	ret = m_pdataXML->GetSoldierLevelItem(id, slevel, soldieritem, grade);

	if (ret)
	{
		error_log("[StartTrain] get soldierlevelitem error. uid=%u, sid=%s", m_nUid, sid.c_str());
		throw std::runtime_error("get_soldierlevelitem_error");
	}

	int count = barrackq[qkey]["i"]["c"].asInt();
	int time = 0;

	for (int i = 1; i <= count; ++i)
	{
		if (1 == i)  //第一个小兵的剩余时间，从队列中获得
		{
			time = barrackq[qkey]["i"]["lt"].asUInt();
		}
		else
		{
			int singletime = soldieritem.ptime;
			time += (singletime * (count - 1));
			break;
		}
	}

	time *=6;
	int pay = GetSoldierTimeCost(time);

	int cash = 0;
	int coin = 0;

	if (END_SOLDIER_BY_CASH == etype)
	{
		cash = pay;
	}
	else
	{
		coin = pay;
	}

	if (pay > 0)
	{
		userWrap.CostAsset(cash, coin, "END_SOLDIER_TRAIN", result);
	}

	//直接将兵塞进兵营中
	Json::Value soldier;
	userWrap.GetUserSoldier(soldier);
	AddSoldiers(soldier, count, sid);
	userWrap.SetUserSoldier(soldier);

	result["soldier"] = soldier;

	//训练队列后续处理
	barrackq[qkey].removeMember("i");
	userWrap.SetUserBarrackQ(barrackq);

	result["barrackQ"] = barrackq;
}

void SoldierUnit::StartResearch(UserWrap& userWrap, string sid, unsigned stype, unsigned rlevel, unsigned costtype, Json::Value &result)
{
	int ret = R_SUCCESS;

	if (START_SOLDIER_BY_RESOURCE != stype && START_SOLDIER_BY_COIN != stype)
	{
		error_log("[StartResearch] type param error. uid=%u", m_nUid);
		throw std::runtime_error("param error");
	}

	//加载研究院的小兵信息
	Json::Value soldierlevel;
	userWrap.GetUserSoldierLevel(soldierlevel);

	if (soldierlevel.isMember(sid) && 0 != soldierlevel[sid]["lt"].asInt())
	{
		error_log("[StartResearch] soldier is researching. uid=%u, sid=%s", m_nUid, sid.c_str());
		throw std::runtime_error("soldier_is_researching");
	}

	unsigned level = 0;

	if (!soldierlevel.isMember(sid))  //兵种未解锁
	{
		level = 1;
		Json::Value soldier;

		soldier["l"] = 0;	//当前等级
		soldier["lt"] = 0;  //剩余研究时间

		soldierlevel[sid] = soldier;
	}
	else
	{
		level = soldierlevel[sid]["l"].asUInt() + 1;  //获得的是下一等级的xml信息
	}

	//读取配置，获取小兵训练所需的时间
	unsigned char grade = 0;
	XMLSoldierLevelItems soldieritem;
	int id = CTrans::STOI(sid.substr(1).c_str());
	ret = m_pdataXML->GetSoldierLevelItem(id, level, soldieritem, grade);

	if (ret)
	{
		error_log("[StartResearch] get soldierlevelitem error. uid=%u, sid=%s", m_nUid, sid.c_str());
		throw std::runtime_error("get_soldierlevelitem_error");
	}

	//判断研究院等级是否足够
	Json::Value tech;
	userWrap.GetUserTech(tech);
	int sMaxLv = 0;
	Json::GetInt(tech, "sMaxLv", sMaxLv);

	Json::Value bd;
	CLogicBuilding logicBd;
	ret = logicBd.Get(userWrap.Id(), rlevel, 0, true, bd);
	if(ret)
		throw std::runtime_error("get_bd_error");
	int l = 0, t = 0;
	Json::GetInt(bd, "l", l);
	Json::GetInt(bd, "t", t);

	if (t != 22 || sMaxLv < soldieritem.locklevel || l < soldieritem.locklevel)
	{
		error_log("[StartResearch] research level not enough. now=%u, should=%hhu", min(l, sMaxLv), soldieritem.locklevel);
		throw std::runtime_error("research_level_not_enough");
	}

	if (START_SOLDIER_BY_COIN == stype)   //花金币研究
	{
		int pay = 0;

		if("S4128" == sid || "S4129" == sid) //新兵种消耗*3
		{
			pay = GetResourceCost(soldieritem.cost * 3) + GetSoldierTimeCost(soldieritem.rtime);
		}
		else
		{
			pay = GetResourceCost(soldieritem.cost) + GetSoldierTimeCost(soldieritem.rtime);
		}


		int cash = 0;
		int coin = 0;

		if (END_SOLDIER_BY_CASH == costtype)
		{
			cash = pay;
		}
		else if (END_SOLDIER_BY_COIN == costtype)
		{
			coin = pay;
		}
		else
		{
			error_log("[StartResearch] costtype's value error, uid=%u", m_nUid);
			throw std::runtime_error("param_error");
		}

		//扣金币
		userWrap.CostAsset(cash, coin, "START_SOLDIER_RESEARCH", result);
		soldierlevel[sid]["l"] = level;
		userWrap.SetUserSoldierLevel(soldierlevel);
		result["soldierlevel"] = soldierlevel;

		return ;
	}

	int r2 = 0;
	int r3 = 0;
	int r4 = 0;
	if("S4128" == sid || "S4129" == sid) //如果是新兵种则扣除木材,石料，铁矿
	{
		r2 = -soldieritem.cost;	//消耗木材
		r3 = -soldieritem.cost; //消耗石料
	}
	r4 = -soldieritem.cost;		//消耗铁矿
	userWrap.ChangeResource(0, r2, r3, r4, "SOLDIER_RESEARCH", result);   //内部会抛异常,返回资源给前端

	int soul = GetResearchNeedSoul(grade, level - 1);   //研究计算战魂时，使用的是当前等级

	userWrap.ChangeBattle(-soul, "SOLDIER_RESEARCH");

	result["battle_spirits"] = userWrap.GetBattleSpirits();

	//消耗资源和战魂扣除完毕，开始研究
	soldierlevel[sid]["lt"] = soldieritem.rtime;

	userWrap.SetUserSoldierLevel(soldierlevel);

	result["soldierlevel"] = soldierlevel;
}

void SoldierUnit::CancelResearch(UserWrap& userWrap, string sid, Json::Value &result)
{
	int ret = R_SUCCESS;

	//加载研究院的小兵信息
	Json::Value soldierlevel;
	userWrap.GetUserSoldierLevel(soldierlevel);

	if (!soldierlevel.isMember(sid) || 0 == soldierlevel[sid]["lt"].asInt())
	{
		error_log("[CancelResearch] soldier is not researching. uid=%u, sid=%s", m_nUid, sid.c_str());
		throw std::runtime_error("soldier_is_not_researching");
	}

	//清除lt时间，更新即可
	soldierlevel[sid]["lt"] = 0;

	userWrap.SetUserSoldierLevel(soldierlevel);

	result["soldierlevel"] = soldierlevel;
}

void SoldierUnit::EndResearch(UserWrap& userWrap, string sid, unsigned etype, Json::Value &result)
{
	int ret = R_SUCCESS;

	if (END_SOLDIER_BY_CASH != etype && END_SOLDIER_BY_COIN != etype)
	{
		error_log("[EndResearch] type param error. uid=%u", m_nUid);
		throw std::runtime_error("param error");
	}

	//加载研究院的小兵信息
	Json::Value soldierlevel;
	userWrap.GetUserSoldierLevel(soldierlevel);

	if (!soldierlevel.isMember(sid) || 0 == soldierlevel[sid]["lt"].asInt())
	{
		error_log("[EndResearch] soldier is not researching. uid=%u, sid=%s", m_nUid, sid.c_str());
		throw std::runtime_error("soldier_is_not_researching");
	}

	int level = soldierlevel[sid]["l"].asUInt() + 1;  //获得的是下一等级的xml信息

	//读取配置，获取小兵训练所需的时间
	unsigned char grade = 0;
	XMLSoldierLevelItems soldieritem;
	int id = CTrans::STOI(sid.substr(1).c_str());
	ret = m_pdataXML->GetSoldierLevelItem(id, level, soldieritem, grade);

	if (ret)
	{
		error_log("[EndResearch] get soldierlevelitem error. uid=%u, sid=%s", m_nUid, sid.c_str());
		throw std::runtime_error("get_soldierlevelitem_error");
	}

	int lefttime = soldierlevel[sid]["lt"].asUInt();
	int now = Time::GetGlobalTime();
	int diff_time = now - soldierlevel["upts"].asInt();

	if (diff_time < 0 )   //处理修改服务器时间可能导致的问题
	{
		error_log("[EndResearch] time error. now is less than upts.uid=%u,now=%d,upts=%d", m_nUid, now, soldierlevel["upts"].asInt());
		throw std::runtime_error("upts_time_error");
	}

	lefttime -= diff_time;

	if (lefttime <= 1)
	{
		lefttime = 0;
	}

	int pay = GetSoldierTimeCost(lefttime);  //时间

	int cash = 0;
	int coin = 0;

	if (END_SOLDIER_BY_CASH == etype)
	{
		cash = pay;
	}
	else
	{
		coin = pay;
	}

	if (pay > 0)
	{
		userWrap.CostAsset(cash, coin, "END_SOLDIER_RESEARCH", result);
	}

	//扣钻或者金币之后
	soldierlevel[sid]["l"] = level;
	soldierlevel[sid]["lt"] = 0;

	userWrap.SetUserSoldierLevel(soldierlevel);
	result["soldierlevel"] = soldierlevel;
}

SkillUnit::SkillUnit(unsigned uid):
		BaseCmdUnit(uid),
		m_pdataXML(NULL)
{
	m_pdataXML = CDataXML::GetCDataXML();

	if(!m_pdataXML)
	{
		error_log("GetInitXML fail");
		throw std::runtime_error("GetInitXML fail");
	}
}

double SkillUnit::GetGradeMaxPoint(int point, int grade)
{
	double maxPoint = 0;

	switch(grade)
	{
		case 0: maxPoint = point * 1.2; break;
		case 1: maxPoint = point * 1.4; break;
		case 2: maxPoint = point * 1.7; break;
		case 3: maxPoint = point * 2.0; break;
		case 4:	maxPoint = point * 2.3; break;
		case 5: maxPoint = point * 2.7; break;

		default:  throw std::runtime_error("grade_value_error"); break;
	}

	maxPoint = maxPoint * pow(10, 1);
	return (int)maxPoint / pow(10, 1);
}

void SkillUnit::UpgradeInnateSkill(UserWrap& userWrap, unsigned heroud, Json::Value &result)
{
	int ret = R_SUCCESS;

	CLogicHero logicHero;
	Json::Value herodata;

	ret = logicHero.Get(m_nUid, heroud, herodata);
	//判断训练是否有位
	if (ret)
	{
		throw std::runtime_error("get_hero_data_error");
	}

	//判断天生技升级是否符合要求
	int bornlv = herodata["bornlv"].asInt();   //天生技技能等级
	int grade = herodata["grade"].asInt();   //英雄阶数

	//先判断等级条件是否符合
	if (bornlv > grade)   //天生技等级必须小于英雄阶数
	{
		error_log("[UpgradeInnateSkill] bornlv is greater than grade. bornlv=%d, grade=%d", bornlv, grade);
		throw std::runtime_error("condition_grade_not_match");
	}

	XMLHero xmlhero;
	string hid = herodata["id"].asString();
	ret = m_pdataXML->GetHero(CDataXML::Str2Hero(hid), xmlhero);

	if(ret)
	{
		throw std::runtime_error("get_hero_error");
	}

	int point = xmlhero.point;   //英雄的基础成长值

	double maxpoint = 0;

	if (bornlv == grade)
	{
		maxpoint = GetGradeMaxPoint(point, grade);
	}
	else
	{
		maxpoint = GetGradeMaxPoint(point, bornlv);
	}

	double heropt = herodata["pt"].asDouble();

	if (maxpoint > heropt)
	{
		error_log("[UpgradeInnateSkill] point not enough. maxpoint=%.1f,pt=%.1f", maxpoint, heropt);
		throw std::runtime_error("condition_point_not_match");
	}

	//开始计算需要消耗的威望
	int prosper = int(pow(maxpoint, 2) / 1000) * 100;
	userWrap.ChangeProsper(-prosper, "InnateSkill_Upgrade", result);

	herodata["bornlv"] = bornlv + 1;

	ret = logicHero.Chg(m_nUid, heroud, herodata);

	if (ret)
	{
		error_log("[UpgradeInnateSkill] update hero failed. uid=%u, heroud=%u", m_nUid, heroud);
		throw std::runtime_error("update_hero_error");
	}

	result["bornlv"] = herodata["bornlv"].asInt();
}

void SkillUnit::VerifyTrainQueue(Json::Value & skillq, unsigned sectime, int & queue_index)
{
	int ret = R_SUCCESS;

	//消耗资源的训练
	int sec = sectime;
	bool isHaveSpace = false;

	for (int i = 0; i < MAX_QUEUE_ITEMS; ++i)
	{
		char szkey[4] = {0};
		sprintf(szkey, "i%d", i);

		if (!skillq.isMember(szkey))   //队列空间不存在
		{
			break;
		}

		if (skillq[szkey].isMember("i"))   //队列正在使用中
		{
			continue;
		}

		if (skillq[szkey]["o"].asInt() == 0 && sec > skillq[szkey]["r"].asInt())  //队列非永久使用，且剩余时间不足够训练所需
		{
			continue;
		}

		isHaveSpace = true;
		queue_index = i;
		break;
	}

	if (!isHaveSpace)   //没有空间
	{
		error_log("[VerifyTrainQueue] no queue can be used. uid=%u", m_nUid);
		throw std::runtime_error("have_no_queue");
	}
}

void SkillUnit::CommderSkilLearn(UserWrap& userWrap, unsigned heroud, unsigned equd,Json::Value &result)
{
	int ret = R_SUCCESS;

	//判断英雄等级是否足够。
	CLogicHero logicHero;
	Json::Value herodata;

	ret = logicHero.Get(m_nUid, heroud, herodata);
	if(ret)
	{
		throw std::runtime_error("get_hero_data_error");
	}

	if(herodata["l"].asInt() < 50 || herodata["l"].asInt() > 120)
	{
		throw std::runtime_error("hero_lv_error");
	}

	//判断技能书是否够
	CLogicEquipment equipment;
	Json::Value equipdata;

	ret = equipment.Get(m_nUid, equd, equipdata);
	if(ret)
	{
		throw std::runtime_error("get_equip_error");
	}

	if(equipdata["count"].asInt() < 1 || equipdata["status"] != 0)
	{
		throw std::runtime_error("equip_count_error");
	}

	//修改英雄的争霸技能。
	if(herodata.isMember("zbskud"))
	{
		herodata["zbskud"] = equd;
	}
	else
	{
		Json::Value skill;
		skill["zbskud"] = equd;
		herodata.append(skill);
	}
	ret = logicHero.Chg(m_nUid, heroud, herodata);
	if (ret)
	{
		error_log("[BraveSkillTrain] update hero failed. uid=%u, heroud=%u", m_nUid, heroud);
		throw std::runtime_error("update_hero_error");
	}

	//修改技能书属性
	equipdata["status"] = 1;
	equipment.Chg(m_nUid,equd,equipdata);

	result.append(herodata);
	result.append(equipdata);
}

void SkillUnit::PotianSkilLearn(UserWrap& userWrap, unsigned heroud,string skid,Json::Value &m_data,Json::Value &result)
{
	int ret = R_SUCCESS;

		CLogicHero logicHero;
		Json::Value herodata;

		ret = logicHero.Get(m_nUid, heroud, herodata);
		if (ret)
		{
			throw std::runtime_error("get_hero_data_error");
		}

		//检查技能版本（优化）
		ret = CheakSkillVer(herodata);
		if(!ret)
		{
			error_log("[PotianSkillTrain] cheak_skill_error failed. uid=%u", m_nUid);
			throw std::runtime_error("cheak_skill_error!");
		}

		//先扣道具
		CLogicEquipment equipment;
		Json::Value equipdata;

		for(unsigned i = 0; i < m_data["equds"].size(); ++i)
		{
					unsigned equd = m_data["equds"][i][0u].asUInt();
					unsigned count = m_data["equds"][i][1u].asUInt();

					ret = equipment.Get(m_nUid, equd, equipdata);

					if (ret)
					{
						throw std::runtime_error("get_equip_error");
					}

					//不做校验，只要消耗道具即可
					UseEquips(equipdata["id"].asUInt(), equd, count, "SKILL_TRAIN");  //消耗的技能书=level+1
		}

		//递归查询当前技能所在的index
		bool isLock = true;  //技能是否被锁]
		int level = 0;
		unsigned index = 0;

		for (unsigned i = 0; i < herodata["tskill"].size(); ++i)
		{
			if (herodata["tskill"][i][0u].asInt() == atoi(skid.c_str()))  //技能存在，表示技能已经解锁
			{
				isLock = false;
				index = i;
				level = herodata["tskill"][i][1u].asInt();   //当前技能等级
			}
		}

		if (isLock)   //被锁的，以前没有
		{
			Json::Value skill(Json::arrayValue);
			skill[0u] = atoi(skid.c_str());
			skill[1u] = 1;
			herodata["tskill"].append(skill);
			//herodata["upts"] = Time::GetGlobalTime();
		}else{
				if(level != 0){
					herodata["tskill"][index][1u] = herodata["tskill"][index][1u].asInt()+1;
				}
				else{
						error_log("[PotianSkillTrain]  find tskill failed. uid=%u, heroud=%u", m_nUid, heroud);
						throw std::runtime_error("find tskill failed");
				}
		}
		ret = logicHero.Chg(m_nUid, heroud, herodata);
		if (ret)
		{
			error_log("[PotianSkillTrain] update hero failed. uid=%u, heroud=%u", m_nUid, heroud);
			throw std::runtime_error("update_hero_error");
		}
		result["tskill"] = herodata["tskill"];
		return ;
}


int SkillUnit::CheakSkillVer(Json::Value &herodata)
{
	if(!herodata.isMember("tskill"))
		herodata["tskill"].resize(0);

	if(!herodata["tskill"].isArray())
		return 0;

	if(herodata["tskill"].size() == 0)
		return 1;

	//判断第一个技能是否为数组。
	if(herodata["tskill"][0u].isArray())
	{
		//遍历查询技能id是否有5006-50013中的，有的话移除。
		bool flag = false;
		for (int i = 0; i < herodata["tskill"].size(); i++) {
			int tmp_id = herodata["tskill"][i][0u].asInt();
			if (tmp_id >= 50006 && tmp_id <= 50013) {
				flag = true;
				break;
			}
		}
		if(flag)	{
			Json::Value t;
			t.resize(0);
			for (int i = 0; i < herodata["tskill"].size(); i++) {
				int tmp_id = herodata["tskill"][i][0u].asInt();
				if (tmp_id >= 50006 && tmp_id <= 50013)
					continue;
				t.append(herodata["tskill"][i]);
			}
			herodata["tskill"] = t;
		}
		return 1;
	}
	//判断第一个技能是否为对象
	if(herodata["tskill"][0u].isObject())
	{
		Json::Value tskill(Json::arrayValue);
		//重置及技能队列
		for(int i = 0;i < herodata["tskill"].size();++i)
		{
			int id = 0,lv = 0;
			Json::Value array(Json::arrayValue);
			if(!herodata["tskill"][i].isMember("id"))
				return 0;
			id = CTrans::STOI(herodata["tskill"][i]["id"].asString());
			if(!herodata["tskill"][i].isMember("l"))
				return 0;
			lv =  herodata["tskill"][i]["l"].asInt();
			array[0u] = id;
			array[1u] = lv;
			tskill[i] = array;
		}
		herodata.removeMember("tskill");
		herodata["tskill"] = tskill;

		//遍历查询技能id是否有5006-50013中的，有的话移除。
		bool flag = false;
		for (int i = 0; i < herodata["tskill"].size(); i++) {
			int tmp_id = herodata["tskill"][i][0u].asInt();
			if (tmp_id >= 50006 && tmp_id <= 50013) {
				flag = true;
				break;
			}
		}
		if(flag)	{
			Json::Value t;
			t.resize(0);
			for (int i = 0; i < herodata["tskill"].size(); i++) {
				int tmp_id = herodata["tskill"][i][0u].asInt();
				if (tmp_id >= 50006 && tmp_id <= 50013)
					continue;
				t.append(herodata["tskill"][i]);
			}
			herodata["tskill"] = t;
		}
		return 1;
	}
	return 0;
}

void SkillUnit::StartSkillTrain(UserWrap& userWrap, unsigned heroud, string skid, Json::Value m_data, unsigned sectime, unsigned costpro, Json::Value &result)
{
	int ret = R_SUCCESS;

	CLogicHero logicHero;
	Json::Value herodata;

	ret = logicHero.Get(m_nUid, heroud, herodata);
	//判断训练是否有位
	if (ret)
	{
		throw std::runtime_error("get_hero_data_error");
	}

	//检查技能版本（优化）
	ret = CheakSkillVer(herodata);
	if(!ret)
	{
		error_log("[StartSkillTrain] cheak_skill_error failed. uid=%u", m_nUid);
		throw std::runtime_error("cheak_skill_error!");
	}

	//递归查询当前技能所在的index
	bool isLock = true;  //技能是否被锁]
	int level = 0;
	unsigned index = 0;

	for (unsigned i = 0; i < herodata["tskill"].size(); ++i)
	{
		if (herodata["tskill"][i][0u].asInt() == atoi(skid.c_str()))  //技能存在，表示技能已经解锁
		{
			isLock = false;
			index = i;
			level = herodata["tskill"][i][1u].asInt();   //当前技能等级
		}
	}

	Json::Value skillq;
	userWrap.GetUserSkillQ(skillq);

	int queue_index = 0;

	if (!isLock)   //已解锁，才需要校验
	{
		VerifyTrainQueue(skillq, sectime, queue_index);
	}

	//先扣道具
	CLogicEquipment equipment;
	Json::Value equipdata;

	for(unsigned i = 0; i < m_data["equds"].size(); ++i)
	{
		unsigned equd = m_data["equds"][i][0u].asUInt();
		unsigned count = m_data["equds"][i][1u].asUInt();

		ret = equipment.Get(m_nUid, equd, equipdata);

		if (ret)
		{
			throw std::runtime_error("get_equip_error");
		}

		char tmp_str[32] = {0};
		snprintf(tmp_str, sizeof(tmp_str), "%d", heroud);
		string hud_str = tmp_str;
		string reasons = "START_SKILL_TRAIN:  /*hud = " +  hud_str + " sid = " + skid + "*/";
		//不做校验，只要消耗道具即可
		UseEquips(equipdata["id"].asUInt(), equd, count, reasons);  //消耗的技能书=level+1
	}

	//消耗威望
	int paycos = -costpro;
	//消耗威望
	userWrap.ChangeProsper(paycos, "SKILL_TRAIN", result);

	if (isLock)   //被锁的，则是立即完成，不需要放入技能训练队列
	{
		Json::Value skill(Json::arrayValue);
		skill[0u] = atoi(skid.c_str());
		skill[1u] = 1;

		herodata["tskill"].append(skill);
		//herodata["upts"] = Time::GetGlobalTime();

		ret = logicHero.Chg(m_nUid, heroud, herodata);

		if (ret)
		{
			error_log("[StartSkillTrain] update hero failed. uid=%u, heroud=%u", m_nUid, heroud);
			throw std::runtime_error("update_hero_error");
		}

		result["tskill"] = herodata["tskill"];

		return ;
	}

	//开始训练
	char qkey[4] = {0};
	sprintf(qkey, "i%d", queue_index);

	Json::Value idata;
	idata["hid"] = herodata["id"].asString();
	idata["hud"] = heroud;
	idata["l"] = level;
	idata["sid"] = skid;

	skillq[qkey]["i"] = idata;
	userWrap.SetUserSkillQ(skillq);

	result["skillQ"] = skillq;
	//更新英雄的scd
	herodata["scd"] = sectime;
	herodata["sid"] = skid;

	ret = logicHero.Chg(m_nUid, heroud, herodata);

	if (ret)
	{
		error_log("[StartSkillTrain] update hero failed. uid=%u, heroud=%u", m_nUid, heroud);
		throw std::runtime_error("update_hero_error");
	}
}

int SkillUnit::GetSkillTimeCost(unsigned lefttime, unsigned viplevel)
{
	int freeTime = 300;

	if(viplevel > 0 && viplevel <= MAX_VIP_LEVEL)
	{
		freeTime = FREE_SPEED_TIME[viplevel - 1]*60;
	}

	if (lefttime <= freeTime)
	{
		return 0;
	}

	double p1 = pow(lefttime/static_cast<double>(60), 1.1);
	double p2 = pow(lefttime/static_cast<double>(3600), 1.1);

	return ceil(p1 - p2);
}

void SkillUnit::EndSkillTrain(UserWrap& userWrap,  unsigned sindex, unsigned type, Json::Value &result)
{
	int ret = R_SUCCESS;

	if (END_TRAIN_BY_CASH != type && END_TRAIN_BY_COIN != type &&END_TRAIN_BY_TIME !=type)
	{
		error_log("[EndSkillTrain] type's value error");
		throw std::runtime_error("param_error");
	}

	Json::Value skillq;
	userWrap.GetUserSkillQ(skillq);

	char qkey[4] = {0};
	sprintf(qkey, "i%u", sindex);

	if (!skillq.isMember(qkey))
	{
		error_log("[EndSkillTrain] skillQ don't have key:[%s]. uid=%u", qkey, m_nUid);
		throw std::runtime_error("param_error");
	}

	if (!skillq[qkey].isMember("i"))
	{
		error_log("[EndSkillTrain] skillQ 's key:[%s] don't trainning. uid=%u", qkey, m_nUid);
		throw std::runtime_error("param_error");
	}

	unsigned heroud = skillq[qkey]["i"]["hud"].asUInt();
	CLogicHero logicHero;
	Json::Value herodata;

	ret = logicHero.Get(m_nUid, heroud, herodata);
	//判断训练是否有位
	if (ret)
	{
		throw std::runtime_error("get_hero_data_error");
	}

	//检查技能版本（优化）
	ret = CheakSkillVer(herodata);
	if(!ret)
	{
		error_log("[EndSkillTrain] cheak_skill_error failed. uid=%u", m_nUid);
		throw std::runtime_error("cheak_skill_error!");
	}

	int lefttime = 0;
	Json::GetInt(herodata, "scd", lefttime);

	int now = Time::GetGlobalTime();
	int diff_time = now - herodata["upts"].asInt();

	if (diff_time < 0 )   //处理修改服务器时间可能导致的问题
	{
		error_log("[EndSkillTrain] time error. now is less than upts.uid=%u,now=%d,upts=%d", m_nUid, now, herodata["upts"].asInt());
		throw std::runtime_error("upts_time_error");
	}

	lefttime -= (diff_time);

	if (lefttime < 0)
	{
		lefttime = 0;
	}

	int pay = 0;
	double p1 = pow(lefttime/static_cast<double>(60), 1.1);
	double p2 = pow(lefttime/static_cast<double>(3600), 1.1);
	pay =  ceil(p1 - p2);
	int cash = 0;
	int coin = 0;

	if (END_TRAIN_BY_CASH == type)
	{
		cash = pay;
	}
	else if(END_TRAIN_BY_COIN == type)
	{
		coin = pay;
	}
	else{
		pay = 0;
	}

	if (pay > 0)
	{
		userWrap.CostAsset(cash, coin, "END_SKILL_TRAIN", result);
	}

	string skid = skillq[qkey]["i"]["sid"].asString();
	int index = 0;
	bool isLook = true;
	//完成技能的升级
	for (unsigned i = 0; i < herodata["tskill"].size(); ++i)
	{
		if (herodata["tskill"][i][0u].asInt() == atoi(skid.c_str()))  //技能存在，表示技能已经解锁
		{
			index = i;
			isLook = false;
		}
	}

	if (isLook)
	{
		error_log("[EndSkillTrain] skill is locked. uid=%u, skid=%d", m_nUid, skid);
		throw std::runtime_error("skill_is_locked");
	}

	herodata["tskill"][index][1u] = herodata["tskill"][index][1u].asInt() + 1;

	ret = logicHero.Chg(m_nUid, heroud, herodata);

	if (ret)
	{
		error_log("[EndSkillTrain] update hero failed. uid=%u, heroud=%u", m_nUid, heroud);
		throw std::runtime_error("update_hero_error");
	}

	result["tskill"] = herodata["tskill"];

	//处理技能队列
	skillq[qkey].removeMember("i");
	userWrap.SetUserSkillQ(skillq);

	result["skillQ"] = skillq;
}

void SkillUnit::UpgradeHevenDaoSkill(UserWrap& userWrap, unsigned index, unsigned type, unsigned equd, Json::Value &result)
{
	int ret = R_SUCCESS;

	if (SKILL_OF_HEAVEN != type && SKILL_OF_DAO != type)
	{
		error_log("[UpgradeHevenDaoSkill] type error. uid=%u, type=%u", m_nUid, type);
		throw std::runtime_error("param_error");
	}

	Json::Value user_tech;
	userWrap.GetUserTech(user_tech);

	unsigned max_size = 0;
	string skillkey;
	string levelkey;

	XMLHeavenDaoSkillItem skillitem;

	if (SKILL_OF_HEAVEN == type)
	{
		skillkey = "hskill";
		levelkey = "heaven";

		ret = m_pdataXML->GetHeavenSkillItem(index+1, skillitem);  //id=index+1

		if (ret)
		{
			error_log("[UpgradeHevenDaoSkill] get heaven skill item error.uid=%u", m_nUid);
			throw std::runtime_error("get_skillitem_error");
		}
	}
	else
	{
		skillkey = "dskill";
		levelkey = "daoist";

		ret = m_pdataXML->GetDAOSkillItem(index+1, skillitem);

		if (ret)
		{
			error_log("[UpgradeHevenDaoSkill] get dao skill item error.uid=%u", m_nUid);
			throw std::runtime_error("get_skillitem_error");
		}
	}

	max_size = user_tech[skillkey].size();

	if (index >= max_size)
	{
		error_log("[UpgradeHevenDaoSkill] index value greater than max. uid=%u, index=%u, max=%u", m_nUid, index, max_size);
		throw std::runtime_error("param_error");
	}

	int skilllevel = user_tech[skillkey][index].asInt();   //当前的技能等级

	if (skilllevel >= MAX_SKILL_LEVEL)
	{
		error_log("[UpgradeHevenDaoSkill] skill already max. uid=%u, index=%u", m_nUid, index);
		throw std::runtime_error("skill_already_max");
	}

	if (!user_tech.isMember(levelkey))
	{
		error_log("[UpgradeHevenDaoSkill] tech doesn't have key. uid=%u,key=%s", m_nUid, levelkey.c_str());
		throw std::runtime_error("tech_data_error");
	}

	//计算阶级是否足够
	int heavendaolevel = user_tech[levelkey]["lv"].asInt();
	unsigned grade = ceil(heavendaolevel/static_cast<double>(10));

	if (grade < skillitem.stage)
	{
		error_log("[UpgradeHevenDaoSkill] level is not enough. uid=%u, grade=%u, needgrade=%u", m_nUid, grade, skillitem.stage);
		throw std::runtime_error("condition_not_match");
	}

	unsigned count = skillitem.booknum[skilllevel];

	UseEquips(skillitem.bookid, equd, count, "HEAVEN_DAO_SKILL");   //虽然传的是skilllevel，但实际是获得下一个等级需要消耗的技能书

	//技能升级
	user_tech[skillkey][index] = skilllevel + 1;

	userWrap.SetUserTech(user_tech);

	result[skillkey] = user_tech[skillkey];
}

void SkillUnit::UpgradeCatapultSkill(UserWrap& userWrap, unsigned index, unsigned equd, Json::Value &result)
{
	int ret = R_SUCCESS;
	Json::Value user_tech;
	userWrap.GetUserTech(user_tech);

	unsigned max_size = 0;
	string skillkey;
	string levelkey;

	XMLCatapultSkillItem skillitem;

	skillkey = "cskill";
	levelkey = "catapult";

	ret = m_pdataXML->GetCatapultSkillItem(index+1, skillitem);

	if (ret)
	{
		error_log("[UpgradeCatapultSkill] get catapult skill item error.uid=%u", m_nUid);
		throw std::runtime_error("get_catapult_skillitem_error");
	}
	if(!user_tech.isMember("cskill"))
	{
		user_tech["cskill"].resize(0);
		for(int i = 0; i < MAX_CATAPULT_SKILL_ITEMS; ++i)
		{
			user_tech["cskill"].append(0);
		}
	}
	max_size = user_tech[skillkey].size();

	if (index >= max_size)
	{
		error_log("[UpgradeCatapultSkill] index value greater than max. uid=%u, index=%u, max=%u", m_nUid, index, max_size);
		throw std::runtime_error("param_error");
	}

	int skilllevel = user_tech[skillkey][index].asInt();   //当前的技能等级

	if (skilllevel >= MAX_CATAPULT_SKILL_LEVEL)
	{
		error_log("[UpgradeCatapultSkill] skill already max. uid=%u, index=%u", m_nUid, index);
		throw std::runtime_error("catapult_skill_already_max");
	}

	if (!user_tech.isMember(levelkey))
	{
		error_log("[UpgradeCatapultSkill] tech doesn't have key. uid=%u,key=%s", m_nUid, levelkey.c_str());
		throw std::runtime_error("tech_data_error");
	}

	//计算阶级是否足够
	int catapultlevel = user_tech[levelkey]["lv"].asInt();
	if (catapultlevel < skillitem.unlocklv)
	{
		error_log("[UpgradeCatapultSkill] level is not enough. uid=%u, catapultlevel=%u, unlocklv=%u", m_nUid, catapultlevel, skillitem.unlocklv);
		throw std::runtime_error("condition_not_match");
	}

	unsigned count = skillitem.booknum[skilllevel];

	UseEquips(skillitem.bookid[skilllevel], equd, count, "CATAPULT_SKILL");

	//技能升级
	user_tech[skillkey][index] = skilllevel + 1;

	userWrap.SetUserTech(user_tech);

	result[skillkey] = user_tech[skillkey];
}


FortuneFairyBagUnit::FortuneFairyBagUnit(unsigned uid):
		m_nUid(uid)
{
	CLogicSecinc logicSecinc;
	int ret = logicSecinc.GetSecinc(m_nUid, NAT_FAIRY_BAG, m_jsonData);

	if (R_ERR_NO_DATA == ret)
	{
		m_jsonData["a"]["value"]= 0;    //4个可以升星的数组

		m_jsonData["b"]["value"] = 0;    //福禄值
		m_jsonData["id"] = NAT_FAIRY_BAG;
	}
	else if (ret)
	{
		error_log("get newact error.uid=%u id=%d", uid, NAT_FAIRY_BAG);
		throw std::runtime_error("get_new_active_data_error");
	}
}

void FortuneFairyBagUnit::CalcuteFortune(UserWrap& userWrap, Json::Value & result)
{
	//获取当前时间
	unsigned now = Time::GetGlobalTime();
	unsigned chgval = userWrap.GetSingleDayRecharge(now);  //获取当日充值数
	unsigned fortuval = chgval/5;   //每五钻得一福禄值

	if (fortuval > MAX_FORTUNE_VAL)
	{
		fortuval = MAX_FORTUNE_VAL;
	}

	m_jsonData["b"]["value"] = fortuval;
	Save();
	result["newAct"] = m_jsonData;
}

void FortuneFairyBagUnit::Save()
{
	CLogicSecinc logicSecinc;
	int ret = logicSecinc.SetOneSecinc(m_nUid, m_jsonData);

	if (ret !=  R_SUCCESS)
	{
		throw std::runtime_error("Save_data_failed");
	}
}

void FortuneFairyBagUnit::RecieveFairyBagReward(UserWrap& userWrap, unsigned type, Json::Value & result)
{
	if (TYPE_OF_NORMAL != type && TYPE_OF_ONEHALF != type && TYPE_OF_TRIPLE != type)
	{
		error_log("[RecieveFortune] param type value error. uid=%u, type=%u", m_nUid, type);
		throw std::runtime_error("param_error");
	}

	unsigned now = Time::GetGlobalTime();

	if (!CTime::IsDiffDay(m_jsonData["a"]["value"].asUInt(), now))   //判断当天是否已经领取过
	{
		error_log("[RecieveFortune] already recieve fortune value. uid=%u", m_nUid);
		throw std::runtime_error("fortune_already_recieved");
	}

	int pay = 0;
	int addcoin = 0;

	if (TYPE_OF_NORMAL == type)
	{
		addcoin = m_jsonData["b"]["value"].asInt();
	}
	else if (TYPE_OF_ONEHALF == type)
	{
		addcoin = m_jsonData["b"]["value"].asInt() * 1.5;
		pay = 50;
	}
	else if (TYPE_OF_TRIPLE == type)
	{
		addcoin = m_jsonData["b"]["value"].asInt() * 3;
		pay = 200;
	}

	if (0 == addcoin)
	{
		error_log("[RecieveFortune] fortune value is zero. uid=%u", m_nUid);
		throw std::runtime_error("value_is_zero");
	}

	if (pay > 0)
	{
		//先扣钻
		userWrap.CostAsset(pay, 0, "Fairy_Bag_DOUBLE", result);
	}

	userWrap.AddCashCoin(0, addcoin, "Fairy_Bag_Recieve", result);

	//更新newact中的时间
	m_jsonData["a"]["value"] = now;

	Save();
	result["newAct"] = m_jsonData;
}

DailyChargeCoinUnit::DailyChargeCoinUnit(unsigned uid):
		m_nUid(uid),
		m_activity_endts(0)
{

}

DailyChargeCoinUnit::DailyChargeCoinUnit(unsigned uid, string atype):
	m_nUid(uid),
	m_activetype(atype),
	m_activity_endts(0)
{

}

bool DailyChargeCoinUnit::IsActivityOpen()
{
	if (m_activetype.empty())  //默认为送金币活动
	{
		m_activetype = "coin";
	}

	//判断是否是金币活动
	string type;
	Config::GetValue(type, CONFIG_PAYTOTAL_RETURN_TYPE);

	//先判断当前时间是否在活动范围内
	int start_time = Config::GetIntValue(CONFIG_PAY_TOTAL_BEGIN_TS);  //活动的开启时间
	int end_time = Config::GetIntValue(CONFIG_PAY_TOTAL_END_TS);  //活动的结束时间

	m_activity_endts = end_time;

	int now = Time::GetGlobalTime();

	if (type == m_activetype && now >= start_time && now <= end_time)
	{
		return true;
	}
	else if (m_activetype == "coin")  //当前处理的是充值送金币活动
	{
		//判断是否在开服三天之内
		int open_time = Config::GetIntValue(CONFIG_OPEN_TS);

		if (open_time > now)
		{
			error_log("open_time larger than now. uid=%u,open_time=%u,now=%d", open_time, now);
			return false;
		}

		int diff = CTime::GetDayInterval(open_time, now);

		if (diff >= 3)  //不是每日充值送金币活动
		{
			error_log("[beyond 3 days since server opened. uid=%u", m_nUid);
			return false;
		}
		else
		{
			return true;
		}
	}

	return false;
}

bool DailyChargeCoinUnit::IsFeedback()
{
	if (m_activetype == "daoist" || m_activetype == "heaven")
	{
		return true;
	}

	return false;
}

int DailyChargeCoinUnit::GetDailyChargeCoinReward(UserWrap& userWrap, unsigned index, Json::Value & result)
{
	//判断参数
	if (index < 1 || index > max_index_value)
	{
		error_log("[GetDailyChargeCoinReward] param index value error. uid=%u, index=%u", m_nUid, index);
		throw std::runtime_error("param_error");
	}

	unsigned now = Time::GetGlobalTime();
	Json::Value user_stat;
	userWrap.GetUserStats(user_stat);

	//判断档里是否数据齐全
	bool iscomplete = CheckUserstatComplete(user_stat);

	//如何判断是否跨天？取当前时间与dprts进行对比
	int diff_day = CTime::GetDayInterval(user_stat["dprts"].asUInt(), now);
	bool crossday = false;

	//跨天，重置状态和时间戳
	if (diff_day != 0)
	{
		crossday = true;
		ResetUserstat(user_stat);
	}

	//先保存已改变的stat
	if (!iscomplete || diff_day)
	{
		//更新stats状态
		userWrap.SetUserStats(user_stat);
	}

	//判断是否已领取
	if (user_stat["dpr"][index - 1].asUInt())
	{
		error_log("[GetDailyChargeCoinReward] already get reward. uid=%u, index=%u", m_nUid, index);
		throw std::runtime_error("already_get_reward");
	}

	//获取当日充值数
	Json::Value user_flag;
	userWrap.GetUserFlag(user_flag);

	int charge = 0;

	if (0 == CTime::GetDayInterval(user_flag["dchg"][0u].asUInt(), now) )
	{
		charge = user_flag["dchg"][1u].asUInt();
	}

	//获取索引对应的要求的充值钻数
	//获取dataxml对象
	CDataXML *dataXML = CDataXML::GetCDataXML();

	if(!dataXML)
	{
		error_log("[GetDailyChargeCoinReward] GetCDataXML fail");
		throw std::runtime_error("get_cdataxml_error");
	}

	XMLDailyChargeReward dailyrewarditem;
	int ret = dataXML->GetDailyChargeRewardItem(index - 1, dailyrewarditem);

	if (ret)
	{
		error_log("[GetDailyChargeCoinReward] get reward item error. uid=%u", m_nUid);
		throw std::runtime_error("get_rewardconfig_error");
	}

	if (charge < dailyrewarditem.coin)
	{
		error_log("[GetDailyChargeCoinReward] charge not enough. uid=%u, charge=%u, index=%u", m_nUid, charge, index);
        return -1;
    }

	//发放金币
	userWrap.AddCashCoin(0, dailyrewarditem.reward, "Daily_Charge_Coin", result);
	user_stat["dpr"][index - 1] = 1;
	user_stat["dprts"] = now; //更新领取时间戳

	//更新领取状态
	userWrap.SetUserStats(user_stat);

	result["dpr"] = user_stat["dpr"];
	result["dprts"] = user_stat["dprts"];

	return 0;
}

bool DailyChargeCoinUnit::CheckUserstatComplete(Json::Value & user_stat)
{
	//检查dpr,dprts
	//先检查dptrs
	if (!user_stat.isMember("dprts"))
	{
		user_stat["dprts"] = 0;
	}

	if (IsFeedback())  //充值回馈，兵书和遁甲
	{
		//检查是否有dpst
		if (!user_stat.isMember("dpst"))
		{
			Json::Value array = Json::arrayValue;
			user_stat["dpst"] = array;
		}
		else if (!user_stat["dpst"].isArray())
		{
			user_stat.removeMember("dpst");
			Json::Value array = Json::arrayValue;
			user_stat["dpst"] = array;
		}
		else
		{
			return true;
		}

		for(int i = 0; i < max_heaven_dao_index; ++i)
		{
			user_stat["dpst"][i] = 0;
		}
	}
	else
	{
		//检查是否有dpr
		if (!user_stat.isMember("dpr"))
		{
			Json::Value array = Json::arrayValue;
			user_stat["dpr"] = array;
		}
		else if (!user_stat["dpr"].isArray())
		{
			user_stat.removeMember("dpr");
			Json::Value array = Json::arrayValue;
			user_stat["dpr"] = array;
		}
		else
		{
			return true;
		}

		//给数组初始化
		for(int i = 0; i < max_index_value; ++i)
		{
			user_stat["dpr"][i] = 0;
		}
	}

	return false;
}

int DailyChargeCoinUnit::ResetUserstat(Json::Value & user_stat)
{
	//重置时间戳
	user_stat["dprts"] = Time::GetGlobalTime();

	if (IsFeedback())
	{
		//重置dpst
		for(int i = 0; i < max_heaven_dao_index; ++i)
		{
			user_stat["dpst"][i] = 0;
		}
	}
	else
	{
		//重置dpr
		for(int i = 0; i < max_index_value; ++i)
		{
			user_stat["dpr"][i] = 0;
		}

	}

	return 0;
}

ChargeFeedbackUnit::ChargeFeedbackUnit(unsigned uid, string type):
		DailyChargeCoinUnit(uid, type)
{

}

int ChargeFeedbackUnit::GetChargeFeedbackReward(UserWrap& userWrap, unsigned index, Json::Value & result)
{
	//先判断活动是否开启
	bool isopen = IsActivityOpen();

	if (!isopen)
	{
		error_log("activity %s not open. uid=%u", m_activetype.c_str(), m_nUid);
		throw std::runtime_error("activity_not_open");
	}

	//判断参数
	if (index < 1 || index > max_index_value)
	{
		error_log("param index value error. uid=%u, index=%u,activity=%s", m_nUid, index, m_activetype.c_str());
		throw std::runtime_error("param_error");
	}

	unsigned now = Time::GetGlobalTime();
	Json::Value user_stat;
	userWrap.GetUserStats(user_stat);

	//判断档里是否数据齐全
	bool iscomplete = CheckUserstatComplete(user_stat);

	//如何判断是否跨天？取当前时间与dprts进行对比
	int diff_day = CTime::GetDayInterval(user_stat["dprts"].asUInt(), now);
	bool crossday = false;

	//跨天，重置状态和时间戳
	if (diff_day != 0)
	{
		crossday = true;
		ResetUserstat(user_stat);
	}

	//先保存已改变的stat
	if (!iscomplete || diff_day)
	{
		//更新stats状态
		userWrap.SetUserStats(user_stat);
	}

	//判断是否已领取
	if (user_stat["dpst"][index - 1].asUInt())
	{
		error_log("already get reward. uid=%u, index=%u,activity=%s", m_nUid, index, m_activetype.c_str());
		throw std::runtime_error("already_get_reward");
	}

	//获取当日充值数
	Json::Value user_flag;
	userWrap.GetUserFlag(user_flag);

	int charge = 0;

	if (0 == CTime::GetDayInterval(user_flag["dchg"][0u].asUInt(), now) )
	{
		charge = user_flag["dchg"][1u].asUInt();
	}

	//获取索引对应的要求的充值钻数
	//获取dataxml对象
	CDataXML *dataXML = CDataXML::GetCDataXML();

	if(!dataXML)
	{
		error_log("GetCDataXML fail");
		throw std::runtime_error("get_cdataxml_error");
	}

	XMLChargeFeedbackReward dailyrewarditem;
	int ret = dataXML->GetChargeFeedbackRewardItem(index - 1, m_activetype, dailyrewarditem);

	if (ret)
	{
		error_log("get reward item error. uid=%u, activity=%s", m_nUid, m_activetype.c_str());
		throw std::runtime_error("get_rewardconfig_error");
	}

	if (charge < dailyrewarditem.diamond)
	{
		error_log("charge not enough. uid=%u, charge=%u, index=%u,activity=%s", m_nUid, charge, index, m_activetype.c_str());
        return -1;
    }

	//发放装备
	CLogicEquipment logicEquipment;

	string reason = "Daily_Charge_" + m_activetype;

	ret = logicEquipment.AddOneItem(m_nUid, dailyrewarditem.equip.id, dailyrewarditem.equip.cnt, reason, result["equip"], true,
			dailyrewarditem.equip.ch, dailyrewarditem.equip.quality, m_activity_endts - now);

	user_stat["dpst"][index - 1] = 1;
	user_stat["dprts"] = now; //更新领取时间戳

	//更新领取状态
	userWrap.SetUserStats(user_stat);

	result["dpst"] = user_stat["dpst"];
	result["dprts"] = user_stat["dprts"];

	return 0;
}

CelebrateNewYearUnit::CelebrateNewYearUnit(unsigned uid, string type):
		DailyChargeCoinUnit(uid, type)
{

}

int CelebrateNewYearUnit::GetNewYearReward(UserWrap& userWrap, unsigned index, Json::Value & result)
{
	//先判断活动是否开启
	bool isopen = IsActivityOpen();

	if (!isopen)
	{
		error_log("activity not open. uid=%u", m_nUid);
		throw std::runtime_error("activity_not_open");
	}

	//判断参数
	if (index < 1 || index > max_index_value)
	{
		error_log("param index value error. uid=%u, index=%u", m_nUid, index);
		throw std::runtime_error("param_error");
	}

	unsigned now = Time::GetGlobalTime();
	Json::Value user_stat;
	userWrap.GetUserStats(user_stat);

	//判断档里是否数据齐全
	bool iscomplete = CheckUserstatComplete(user_stat);

	//如何判断是否跨天？取当前时间与dprts进行对比
	int diff_day = CTime::GetDayInterval(user_stat["dprts"].asUInt(), now);
	bool crossday = false;

	//跨天，重置状态和时间戳
	if (diff_day != 0)
	{
		crossday = true;
		ResetUserstat(user_stat);
	}

	//先保存已改变的stat
	if (!iscomplete || diff_day)
	{
		//更新stats状态
		userWrap.SetUserStats(user_stat);
	}

	//判断是否已领取
	if (user_stat["dpr"][index - 1].asUInt())
	{
		error_log("already get reward. uid=%u, index=%u", m_nUid, index);
		throw std::runtime_error("already_get_reward");
	}

	//获取当日充值数
	Json::Value user_flag;
	userWrap.GetUserFlag(user_flag);

	int charge = 0;

	if (0 == CTime::GetDayInterval(user_flag["dchg"][0u].asUInt(), now) )
	{
		charge = user_flag["dchg"][1u].asUInt();
	}

	//获取索引对应的要求的充值钻数
	//获取dataxml对象
	CDataXML *dataXML = CDataXML::GetCDataXML();

	if(!dataXML)
	{
		error_log("GetCDataXML fail");
		throw std::runtime_error("get_cdataxml_error");
	}

	XMLNewYearReward dailyrewarditem;
	int ret = dataXML->GetCeleNewYearRewardItem(index - 1, dailyrewarditem);

	if (ret)
	{
		error_log("get reward item error. uid=%u", m_nUid);
		throw std::runtime_error("get_rewardconfig_error");
	}

	if (charge < dailyrewarditem.diamond)
	{
		error_log("charge not enough. uid=%u, charge=%u, index=%u", m_nUid, charge, index);
        return -1;
    }

	//发放装备
	string reason = "Daily_Charge_" + m_activetype;
	CLogicEquipment logicEquipment;
	ret = logicEquipment.AddOneItem(m_nUid, dailyrewarditem.equip.id, dailyrewarditem.equip.cnt, reason, result["equip"], true);

	//发放金币
	userWrap.AddCashCoin(0, dailyrewarditem.coin, reason, result);

	user_stat["dpr"][index - 1] = 1;
	user_stat["dprts"] = now; //更新领取时间戳

	//更新领取状态
	userWrap.SetUserStats(user_stat);

	result["dpr"] = user_stat["dpr"];
	result["dprts"] = user_stat["dprts"];

	return 0;
}


TreasureBoxUnit::TreasureBoxUnit(unsigned uid):
		 BaseCmdUnit(uid)
{

}

int TreasureBoxUnit::RefreshBox(UserWrap& userWrap, Json::Value & result)
{
	//版本号检查，附带了活动是否开启的判断
	CheckVersion(userWrap, result);

	//扣钻刷新
	int pay = 1;
	userWrap.CostAsset(pay, 0, "Refresh_TreasureBOX", result);

	//扣钻之后，进行刷新
	Json::Value user_stat;
	userWrap.GetUserStats(user_stat);

	try
	{
		Refresh(user_stat, result);
	}
	catch(runtime_error &e)
	{
		userWrap.Save();  //保存最新的stat数据
		throw e;  //继续向上抛
	}

	//更新stats状态
	userWrap.SetUserStats(user_stat);

	return 0;
}

int TreasureBoxUnit::LotteryOnce(UserWrap& userWrap, Json::Value & result)
{
	//版本号检查，附带了活动是否开启的判断
	CheckVersion(userWrap, result);

	try
	{
		Lottery(userWrap, "TreasureBox_Lottery", result);
	}
	catch(runtime_error &e)
	{
		userWrap.Save();  //保存最新的stat数据
		throw e;  //继续向上抛
	}

	return 0;
}

int TreasureBoxUnit::LotteryMulti(UserWrap& userWrap,Json::Value & result)
{
	//版本号检查，附带了活动是否开启的判断
	CheckVersion(userWrap, result);

	try
	{
		for(int i = 0; i < multi_lottery_num; ++i)
		{
			Lottery(userWrap, "TreasureBox_Lottery_Multi", result);
		}
	}
	catch(runtime_error & e)
	{
		userWrap.Save();  //保存最新的stat数据
		throw e;  //继续向上抛
	}

	return 0;
}

int TreasureBoxUnit::CheckVersion(UserWrap& userWrap, Json::Value & result)
{
	bool isopen = IsActivityOpen();

	if (!isopen)
	{
		throw runtime_error("treasure_activity_not_open");
	}

	//获取最新的版本
	Json::Value user_stat;
	userWrap.GetUserStats(user_stat);

	//检查stats数据是否完整
	bool isComplete = CheckUserstatComplete(user_stat);

	//判断版本号是否发生改变
	unsigned config_version = TreasureBoxUnit::GetVersionCfg();

	if (!isComplete || config_version != user_stat["bbv"].asUInt())  //版本号发生改变或者之前的百宝箱数据不完整
	{
		//重置
		ResetTreasureBox(user_stat, config_version);

		try
		{
			//进行百宝箱物品的刷新
			Refresh(user_stat, result);
		}
		catch(runtime_error & e)
		{
			//更新stats状态
			userWrap.SetUserStats(user_stat);
			userWrap.Save();  //保存最新的stat数据
			throw e;  //继续向上抛
		}

		userWrap.SetUserStats(user_stat);
	}

	return 0;
}

int TreasureBoxUnit::Lottery(UserWrap& userWrap, string reason, Json::Value & result)
{
	Json::Value user_stat;
	userWrap.GetUserStats(user_stat);

	//检查stats数据是否完整
	bool isComplete = CheckUserstatComplete(user_stat);

	if (!isComplete)  //数据不完整，补全过
	{
		//更新stats状态
		userWrap.SetUserStats(user_stat);
	}

	//抽奖
	//判断抽奖次数是否足够
	//获取总的抽奖次数，从当前时间段的充值钻数获得
	unsigned now = Time::GetGlobalTime();
	unsigned beginTime = 0;

	Config::GetUIntValue(beginTime, CONFIG_ACTIVITY_GALLERY_BEGIN_TS);

	int cash =  userWrap.GetRechargePoint(beginTime, now);
	int times = cash/per_cash_times;

	if (times < (user_stat["bbc"].asUInt() + 1))  //次数不够
	{
		error_log("[LotteryOnce] times not enough. uid=%u", m_nUid);
		throw runtime_error("times_not_enough");
	}

	//发放奖励
	//获取配置
	CDataXML *dataXML = CDataXML::GetCDataXML();

	if(!dataXML)
	{
		error_log("[GetDailyChargeCoinReward] GetCDataXML fail");
		throw std::runtime_error("get_dataxml_error");
	}

	XMLTreasureBox treasureitem;
	int ret = dataXML->GetSpecificBoxReward(user_stat["bbs"].asUInt(), treasureitem);

	if (ret)
	{
		throw runtime_error("get_box_reward_error");
	}

	GiftEquipItem giftequips[1];
	giftequips[0] = treasureitem.item;

	if (result.isMember("gifts"))
	{
		int size = result["gifts"].size();
		result["gifts"].resize(size + 1);

		AddGiftEquips(giftequips, 1, reason, result["gifts"][size]);
	}
	else
	{
		Json::Value array = Json::arrayValue;
		result["gifts"] = array;
		result["gifts"].resize(1);

		AddGiftEquips(giftequips, 1, reason, result["gifts"][0u]);
	}

	//增加已用次数
	user_stat["bbc"] = user_stat["bbc"].asUInt() + 1;

	//刷新
	Refresh(user_stat, result);

	//更新stats状态
	userWrap.SetUserStats(user_stat);

	return 0;
}

int TreasureBoxUnit::Refresh(Json::Value & user_stat, Json::Value & result)
{
	//获取dataxml对象
	CDataXML *dataXML = CDataXML::GetCDataXML();

	if(!dataXML)
	{
		error_log("[GetDailyChargeCoinReward] GetCDataXML fail");
		throw std::runtime_error("get_dataxml_error");
	}

	//取出所有的百宝箱配置
	DataXMLTreasureBox treasureBoxItems;
	dataXML->GetTreasureBoxRewardItems(treasureBoxItems);

	//先随机出必中的位置
	int reward_index = Math::GetRandomInt(max_treasure_box_items);

	//从reward的配置中随机产生物品
	int rewardrate[MAX_ITEM_NUMS] = {0};

	for(int i = 0; i < treasureBoxItems.rewardnum; ++i)
	{
		rewardrate[i] = treasureBoxItems.rewarditems[i].rate;
	}

	int target = 0;
	//开始转动幸运的转盘
	TurnLuckTable(rewardrate, treasureBoxItems.rewardnum, target);
	user_stat["bbs"] = treasureBoxItems.rewarditems[target].id;

	//设置bbr值
	SetTreasureBBR(user_stat, treasureBoxItems.rewarditems[target].item, reward_index);

	//随机刷新只用于展示的物品
	int special = -1;
	//找出reward中选中的物品在show配置中的对应下标，然后排除
	GiftEquipItem & specialequipitem = treasureBoxItems.rewarditems[target].item;

	for(int i = 0; i < treasureBoxItems.shownum; ++i)
	{
		if (specialequipitem.IsSame(treasureBoxItems.showitems[i].item))
		{
			break;
			special = i;
		}
	}

	int showrate[MAX_ITEM_NUMS] = {0};

	for(int i = 0; i < treasureBoxItems.shownum; ++i)
	{
		//排除reward中选中的物品
		if (special == i)
		{
			showrate[i] = 0;   //排除已经选中的概率
		}
		else
		{
			showrate[i] = treasureBoxItems.showitems[i].rate;
		}
	}

	for(int i = 0; i < max_treasure_box_items; ++i)
	{
		//过滤掉已经出现的抽奖必中的物品
		if (i == reward_index)
		{
			continue;
		}

		//在剩下的位置中随机抽取展示物品
		int showtarget = 0;
		TurnLuckTable(showrate, treasureBoxItems.shownum, showtarget);  //排除在外的下标，已设概率为0

		SetTreasureBBR(user_stat, treasureBoxItems.showitems[showtarget].item, i);

		//设置已选中的位置概率为0
		showrate[showtarget] = 0;
	}

	//user_stat的更新，交给上层
	//设置返回给前端的数据
	result["bbr"] = user_stat["bbr"];
	result["bbv"] = user_stat["bbv"];
	result["bbs"] = user_stat["bbs"];
	result["bbc"] = user_stat["bbc"];

	return 0;
}

bool TreasureBoxUnit::IsActivityOpen()
{
	//判断活动是否开启
	unsigned begints = Config::GetIntValue(CONFIG_ACTIVITY_GALLERY_BEGIN_TS);  //活动的开启时间
	unsigned endts = Config::GetIntValue(CONFIG_ACTIVITY_GALLERY_END_TS);;

	string type;
	Config::GetValue(type, CONFIG_ACTIVITY_GALLERY_TYPE);

	unsigned now = Time::GetGlobalTime();
	//判断类型，再判断时间
	if (type == "baibao" && now >= begints && now <= endts)  //在活动开启范围内
	{
		return true;
	}
	else
	{
		error_log("[TreasureBox] activity not open. uid=%u", m_nUid);
		return false;
	}

	return false;
}

unsigned TreasureBoxUnit::GetVersionCfg()
{
	unsigned nVersion = 0;

	if (! Config::GetUIntValue(nVersion, CONFIG_ACTIVITY_GALLERY_VER))
	{
		error_log("get version config error");
		throw std::runtime_error("can't_get_version_cfg");
	}

	return nVersion;
}

int TreasureBoxUnit::ResetTreasureBox(Json::Value & user_stat, unsigned version)
{
	//重置百宝箱
	user_stat["bbc"] = 0;   //已抽奖次数
	user_stat["bbs"] = 0;  //刷新的物品

	user_stat["bbv"] = version;  //版本号

	//给数组初始化
	for(int i = 0; i < max_treasure_box_items; ++i)
	{
		user_stat["bbr"][i] = "";
	}

	return 0;
}

int TreasureBoxUnit::SetTreasureBBR(Json::Value & user_stat, GiftEquipItem & item, unsigned index)
{
	char szid[20] = {0};

	if (item.m_bIsHero)  //英雄
	{
		sprintf(szid, "H%u", item.m_nId);
	}
	else  //装备，直接记录id即可
	{
		sprintf(szid, "%u", item.m_nId);
	}

	user_stat["bbr"][index] = szid;

	return 0;
}

bool TreasureBoxUnit::CheckUserstatComplete(Json::Value & user_stat)
{
	//检查bbc,bbr,bbs,bbv
	//先检查dptrs
	bool iscomplete = true;

	if (!user_stat.isMember("bbc"))
	{
		iscomplete = false;
		user_stat["bbc"] = 0;
	}

	if (!user_stat.isMember("bbs"))
	{
		iscomplete = false;
		user_stat["bbs"] = 0;
	}

	if (!user_stat.isMember("bbv"))
	{
		iscomplete = false;
		user_stat["bbv"] = 0;
	}

	if (!user_stat.isMember("bbr"))
	{
		iscomplete = false;
		Json::Value array = Json::arrayValue;
		user_stat["bbr"] = array;
	}
	else if (!user_stat["bbr"].isArray())
	{
		iscomplete = false;
		user_stat.removeMember("bbr");
		Json::Value array = Json::arrayValue;
		user_stat["bbr"] = array;
	}
	else
	{
		return iscomplete;
	}

	//给数组初始化
	for(int i = 0; i < max_treasure_box_items; ++i)
	{
		user_stat["bbr"][i] = "";
	}

	return iscomplete;
}

KeepsakeUnit::KeepsakeUnit(unsigned uid):
		 BaseCmdUnit(uid),
		 m_onekey_times(0)
{
	CLogicSecinc logicSecinc;
	int ret = logicSecinc.GetSecinc(m_nUid, NAT_KEEP_SAKE, m_jsonData);

	if (R_ERR_NO_DATA == ret)
	{
		m_jsonData["a"] = 1;    //当前产出npcid
		m_jsonData["b"] = 0; //是否花钻
		m_jsonData["c"] = 0; //召唤的次数
		m_jsonData["ts"] = 0;  //上次召唤的时间

		m_jsonData["id"] = NAT_KEEP_SAKE;

		Save();
	}
	else if (ret)
	{
		error_log("get newact error.uid=%u id=%d", m_nUid, NAT_KEEP_SAKE);
		throw std::runtime_error("get_new_active_data_error");
	}
}

int KeepsakeUnit::SummonNPC(UserWrap& userWrap, Json::Value & result)
{
	//先判断距离上次召唤，是否跨天
	unsigned now = Time::GetGlobalTime();

	if (CTime::GetDayInterval(m_jsonData["ts"].asUInt(), now))  //跨天
	{
		m_jsonData["c"] = 0; //召唤的次数
		m_jsonData["ts"] = now;  //上次召唤的时间

		Save();
	}

	//判断召唤次数是否足够
	if (m_jsonData["c"].asUInt() >= max_summon_times)
	{
		error_log("[SummonNPC] summon times not enough. uid=%u", m_nUid);
		throw runtime_error("summon_times_notenough");
	}

	//扣钻
	userWrap.CostAsset(summon_pay_cash, 0, "Keepsake_SummonNPC", result);

	m_jsonData["c"] = m_jsonData["c"].asUInt() + 1;
	m_jsonData["a"] = max_npc_id - 1;    //当前产出npcid
	m_jsonData["b"] = 1; //是否花钻
	m_jsonData["ts"] = now;

	Save();

	result["newact"] = m_jsonData;

	return 0;
}

int KeepsakeUnit::ProduceKeepsake(UserWrap& userWrap, unsigned equd, Json::Value & result)
{
	//直接调用底层方法即可
	int ret = ProduceKeepsakeInside(userWrap, equd, "Keepsake_Once", result);

	if (ret == ret_code_notenough)
	{
		throw runtime_error("matrial_equip_notenough");
	}

	return 0;
}

int KeepsakeUnit::OneKeyProduce(UserWrap& userWrap, unsigned equd, unsigned times, Json::Value & result)
{
	//批量调用底层产出方法
	int ret = 0;
	m_onekey_times = 0;

	for(; m_onekey_times < times; )
	{
		ret = ProduceKeepsakeInside(userWrap, equd, "Keepsake_OneKey", result);

		if (ret < 0)
		{
			result["code"] = ret;
			break;
		}
	}

	return 0;
}

int  KeepsakeUnit::OneKeyFullLevel(unsigned ud_hero_post, unsigned ud_keepsake, Json::Value & result)
{
	int ret = 0;

	CLogicEquipment logicEquip;
	Json::Value equip;

	ret = logicEquip.Get(m_nUid, ud_hero_post, equip);
	if (ret)
	{
		return ret_code_notenough;
	}
	if (equip["id"].asUInt() != produce_need_equip)
	{
		error_log("[OneKeyFullLevel] wrong equip ud. uid=%u, ud=%u", m_nUid, ud_hero_post);
		throw runtime_error("wrong_equd_param");
	}

	if(PER_EXP_HERO_POST > equip["count"].asUInt())
	{
		error_log("[OneKeyFullLevel] material-props is not enough.uid=%u, ud=%u", m_nUid, ud_hero_post);
		return ret_code_notenough;
	}

	Json::Value dataKeepsakeEquip;
	ret = logicEquip.Get(m_nUid, ud_keepsake, dataKeepsakeEquip);
	if (ret)
	{
		throw runtime_error("get_equip_error");
	}
	//判断令牌是否第一次初始化
	if(!dataKeepsakeEquip.isMember("q"))  //初始1级
	{
		dataKeepsakeEquip["q"] = 1;
	}
	int oldlevel = dataKeepsakeEquip["q"].asUInt();
	//读取配置
	CDataXML *dataXML = DataXmlPtr();
	XMLTokenUpgrade upgradecfg;
	ret = dataXML->GetKeepSakeUpgradeCfg(upgradecfg);
	if (ret)
	{
		error_log("[OneKeyFullLevel] get upgradecfg error. uid=%u", m_nUid);
		throw runtime_error("get_upgrade_cfg_error");
	}

	unsigned character = 1;
	Json::GetUInt(dataKeepsakeEquip, "ch", character);

	unsigned exp = 0;
	if (dataKeepsakeEquip.isMember("xwexp"))
	{
		exp = dataKeepsakeEquip["xwexp"].asUInt();
	}
	unsigned max_exp = upgradecfg.character_upgrade[character - 1].exp[MAX_KEEPSAKE_LEVEL -1];
	if(exp >= max_exp)
	{
		error_log("[OneKeyFullLevel] exp is max. uid=%u", m_nUid);
		return ret_code_max_exp;
	}

	unsigned next_exp = exp;
	if(oldlevel < MAX_KEEPSAKE_LEVEL)
	{
		next_exp = upgradecfg.character_upgrade[character - 1].exp[oldlevel];
	}

	//英雄帖能换取的最大经验
	unsigned left =  equip["count"].asUInt();
	unsigned cost = 0;
	while(exp < next_exp)
	{
		if(PER_EXP_HERO_POST <= left)
		{
			left -= PER_EXP_HERO_POST;
			cost  += PER_EXP_HERO_POST;
			++exp;
		}
		else
		{
			break;
		}
	}
	//消耗材料道具
	UseEquips(produce_need_equip, ud_hero_post, cost, "Keepsake_Once_Full_Level");
	result["left"] = left;

	//等级作为下标
	int i = 0;
	for(; i < MAX_KEEPSAKE_LEVEL; ++i)
	{
		if (upgradecfg.character_upgrade[character - 1].exp[i] > exp)
		{
			break;
		}
	}
	dataKeepsakeEquip["xwexp"] = exp;
	dataKeepsakeEquip["q"] = i;

	//todo 处理部件升级后，解锁副属性
	if (dataKeepsakeEquip["q"].asUInt() > oldlevel)
	{
		UnlockSlave(dataKeepsakeEquip);
	}
	//更新装备信息
	ret = logicEquip.Chg(m_nUid, ud_keepsake, dataKeepsakeEquip);
	if(ret)
	{
		throw runtime_error("update_equip_error");
	}
	result["equip"] = dataKeepsakeEquip;

	//记录信物一键满级日志
	Json::FastWriter writer;
	string equipData = writer.write(dataKeepsakeEquip);
	EQUIPMENT_LOG("uid=%u,id=%u,eqid=%d,act=%s,chg=%d,count=%d,code=%s,data=%s", m_nUid, ud_keepsake, dataKeepsakeEquip["id"].asUInt(), "once_full_level",0, 0, "Keepsake_full_level", equipData.c_str());

	return R_SUCCESS;
}


int KeepsakeUnit::ProduceKeepsakeInside(UserWrap& userWrap, unsigned equd, string reason, Json::Value & result)
{
	int ret = 0;

	//读取配置
	CDataXML *dataXML = DataXmlPtr();

	XMLKeepsakeProduce producecfg;

	ret = dataXML->GetKeepSakeProduceCfg(producecfg);

	if (ret)
	{
		error_log("[ProduceKeepsake] get produce config error. uid=%u", m_nUid);
		throw std::runtime_error("get_produce_config_error");
	}

	//根据npcid，选出掉落的物品类型
	unsigned npcid = m_jsonData["a"].asUInt();

	if (npcid > max_npc_id)
	{
		error_log("[ProduceKeepsake] wrong npcid value. uid=%u,npcid=%u", m_nUid, npcid);
		throw runtime_error("wrong_npc_id");
	}

	//判断数据真实性
	if (m_jsonData["b"].asUInt() && npcid < (max_npc_id - 1))
	{
		error_log("[ProduceKeepsake] wrong newact data. if you pay diamond, npcid must greater than %u. uid=%u", max_npc_id - 1, m_nUid);
		throw runtime_error("user_data_error");
	}

	//判断道具数量是否足够
	unsigned count = producecfg.npcs[npcid - 1].cost;

	CLogicEquipment logicequip;
	Json::Value equip;

	ret = logicequip.Get(m_nUid, equd, equip);

	if (ret)
	{
		return ret_code_notenough;
	}

	if (equip["id"].asUInt() != produce_need_equip)
	{
		error_log("[ProduceKeepsake] wrong equip ud. uid=%u, ud=%u", m_nUid, equd);
		throw runtime_error("wrong_equd_param");
	}

	//道具是否不足
	if (equip["count"].asUInt() < count)
	{
		error_log("[ProduceKeepsake] material-props is not enough.uid=%u, ud=%u", m_nUid, equd);
		return ret_code_notenough;
	}

	//消耗材料道具
	UseEquips(produce_need_equip, equd, count, reason);
	result["restcount"] = equip["count"].asUInt() - count;

	//---------------开始进行掉落----------------

	int kind = 0;

	if (m_jsonData["b"].asUInt())  //花钻召唤
	{
		TurnLuckTable(producecfg.npcs[npcid - 1].summonrate, MAX_FULL_NUM, kind);  //排除在外的下标，已设概率为0
	}
	else
	{
		TurnLuckTable(producecfg.npcs[npcid - 1].fallrate, MAX_FULL_NUM, kind);  //排除在外的下标，已设概率为0
	}

	if (!result.isMember("sakes"))
	{
		Json::Value array = Json::arrayValue;
		result["sakes"] = array;
	}

	//获取用户等级
	int userlevel = userWrap.GetUserLevel();
	unsigned eqid = 0;

	//判断掉落的是残品还是经验石，还是信物
	//随机出掉落的eqid
	if (keepsake_of_defective == kind)   //残品掉落
	{
		ret = dataXML->GetSakeDefective(eqid);

		if (ret)
		{
			error_log("[ProduceKeepsake] get defective sake eqid error. uid=%u", m_nUid);
			throw std::runtime_error("get_defective_error");
		}
	}
	else if (keepsake_of_expprops == kind)  //万物生-经验道具掉落
	{
		ret = dataXML->GetSakeExpProps(eqid);

		if (ret)
		{
			error_log("[ProduceKeepsake] get exp_props sake eqid error. uid=%u", m_nUid);
			throw std::runtime_error("get_expprops_error");
		}
	}
	else if (keepsake_of_convertprops == kind)  //转化石掉落
	{
		eqid = convert_props_eqid;
	}
	else  //掉落信物
	{
		int levelindex = dataXML->GetLevelIndex(userlevel);

		if (-1 == levelindex)
		{
			throw std::runtime_error("get_levelindex_error");
		}

		//品质数组，必须从0开始，而品质的枚举值，是从keepsake_of_green起始
		int chara_index = kind - keepsake_of_green;

		int target = 0;
		//根据等级数组，决定掉落哪些信物，以及根据信物的概率掉落
		TurnLuckTable(producecfg.level_produce[levelindex].character_rate[chara_index], MAX_KEEPSAKE_NUM, target);
		eqid = producecfg.level_produce[levelindex].keepsakeid[target];
	}

	//添加残品或经验石道具
	CLogicEquipment logicEquipment;
	Json::Value equipval;

	if (keepsake_of_defective == kind)
	{
		//残品可叠加
		ret = logicEquipment.AddOneItem(m_nUid, eqid, 1, reason, result["defective"], true);

		if (ret)
		{
			throw std::runtime_error("Add_equip_item_failed");
		}

		++m_onekey_times;
	}
	else if (keepsake_of_expprops == kind)
	{
		//经验石可叠加
		ret = logicEquipment.AddOneItem(m_nUid, eqid, 1, reason, result["expprops"], true);

		if (ret)
		{
			throw std::runtime_error("Add_equip_item_failed");
		}

		++m_onekey_times;
	}
	else if (keepsake_of_convertprops == kind)
	{
		//转化石可叠加
		ret = logicEquipment.AddOneItem(m_nUid, eqid, per_convert_num, reason, result["convertprops"], true);

		if (ret)
		{
			throw std::runtime_error("Add_equip_item_failed");
		}
	}
	else
	{
		//信物不可叠加
		if (!result.isMember("xinwus"))
		{
			Json::Value array = Json::arrayValue;
			result["xinwus"] = array;
		}

		Json::Value tokenvalue;

		ret = logicEquipment.AddOneItem(m_nUid, eqid, 1, reason, tokenvalue, true, kind, 1);  //这里,kind被用来作为品质

		if (ret)
		{
			throw std::runtime_error("Add_equip_item_failed");
		}

		++m_onekey_times;

		result["xinwus"].append(tokenvalue);
	}

	result["sakes"].append(eqid);

	//产出完成之后，判断是否进入下一级
	if (max_npc_id == npcid)  //最大级
	{
		//到达最高级，则重置产出值
		m_jsonData["a"] = 1;
		m_jsonData["b"] = 0; //是否花钻

		ret = ret_code_maxnpc;
	}
	else if (0 == m_jsonData["b"].asUInt()) //没花钻
	{
		//判断是否进入下一级
		int nextrate = producecfg.npcs[npcid - 1].nextrate;
		int random = Math::GetRandomInt(max_nextrate_limit);

		if (random < nextrate)  //进入下一级
		{
			m_jsonData["a"] = m_jsonData["a"].asUInt() + 1;
		}
		else //回到1级
		{
			m_jsonData["a"] = 1;
		}
	}
	else //花钻，百分百进入下一级
	{
		m_jsonData["a"] = m_jsonData["a"].asUInt() + 1;
	}

	Save();

	result["newact"] = m_jsonData;

	return ret;
}

int KeepsakeUnit::OnekeySoldDefective(unsigned equd, Json::Value & result)
{
	//一键卖出残品功能
	CLogicEquipment logicEquip;
	Json::Value defectiveEquip;

	int ret = logicEquip.Get(m_nUid, equd, defectiveEquip);

	if (ret)
	{
		throw runtime_error("get_equip_error");
	}

	int count = defectiveEquip["count"].asUInt();

	//获取残品的eqid
	//读取配置
	CDataXML *dataXML = DataXmlPtr();

	unsigned defective_eqid = 0;
	dataXML->GetSakeDefective(defective_eqid);  //残品

	//删掉残品，
	UseEquips(defective_eqid, equd, count, "Keepsake_OneKeySold");

	int addcount = each_defctive_to_produce * count;

	//增加产出需要的道具A
	ret = logicEquip.AddOneItem(m_nUid, produce_need_equip, addcount, "Keepsake_OneKeySold", result["equips"], true);

	if (ret)
	{
		throw std::runtime_error("Add_equip_item_failed");
	}

	return 0;
}

int KeepsakeUnit::FeedKeepsake(UserWrap& userWrap, unsigned equd, unsigned convertud, Json::Value & data, Json::Value & result)
{
	CLogicEquipment logicEquip;
	Json::Value dataKeepsakeEquip;

	int ret = logicEquip.Get(m_nUid, equd, dataKeepsakeEquip);

	if (ret)
	{
		throw runtime_error("get_equip_error");
	}

	//判断令牌是否第一次初始化
	if(!dataKeepsakeEquip.isMember("q"))  //初始1级
	{
		dataKeepsakeEquip["q"] = 1;
	}

	//条件验证
	VerifyCondition(m_nUid, dataKeepsakeEquip, data);

	unsigned oldexp = 0;

	if (dataKeepsakeEquip.isMember("xwexp"))
	{
		oldexp = dataKeepsakeEquip["xwexp"].asUInt();
	}

	unsigned character = 1;
	Json::GetUInt(dataKeepsakeEquip, "ch", character);

	//读取配置
	CDataXML *dataXML = DataXmlPtr();
	XMLTokenUpgrade upgradecfg;

	ret = dataXML->GetKeepSakeUpgradeCfg(upgradecfg);

	if (ret)
	{
		error_log("[FeedKeepsake] get upgradecfg error. uid=%u", m_nUid);
		throw runtime_error("get_upgrade_cfg_error");
	}

	//获取信物的基础配置
	XMLTokenBase basecfg;
	dataXML->GetKeepSakeBaseCfg(basecfg);

	unsigned exp_props_eqid = 0;
	dataXML->GetSakeExpProps(exp_props_eqid);  //经验石
	unsigned max_exp = upgradecfg.character_upgrade[character - 1].exp[MAX_KEEPSAKE_LEVEL - 1];

	Json::Value dataEquip;
	int add_exp = 0;

	for(int i = 0; i < data.size(); ++i)
	{
		//数组内部数据类型还是数组，存储equd,num
		//先根据ud，获取消耗的道具信息
		unsigned ud = data[i][0u].asUInt();
		unsigned num = data[i][1u].asUInt();

		ret = logicEquip.Get(m_nUid, ud, dataEquip);

		if (ret)
		{
			throw runtime_error("get_equip_error");
		}

		unsigned id = 0;
		unsigned feededch = 1;

		Json::GetUInt(dataEquip, "id", id);
		Json::GetUInt(dataEquip, "ch", feededch);

		if (id == exp_props_eqid)  //经验石
		{
			//直接计算经验等级
			//增加到等级上限所需的提升丹个数，免得多余消耗
			add_exp = (num * exp_props_value); //经验石总的经验 = 数量*单个提供的经验

			if ((oldexp + add_exp) > max_exp)  //经验达到顶峰
			{
				num = (unsigned)ceil((float)(max_exp - oldexp)/exp_props_value);
				add_exp = num * exp_props_value;
			}
		}
		else
		{
			unsigned extraExp = 0;

			if (dataEquip.isMember("xwexp"))
			{
				extraExp = dataEquip["xwexp"].asUInt();
			}

			extraExp += basecfg.character_exp[feededch - 1]; //加上品质对应的经验
			add_exp = extraExp;
			num = 0; //非叠加装备，count在档中存放的是0
			int level = dataEquip["q"].asInt();

			if (0 != convertud)  //排除转化石ud=0的情况
			{
				Json::Value convertEquip;
				ret = logicEquip.Get(m_nUid, convertud, convertEquip);

				if (ret)
				{
					throw runtime_error("get_convertequip_error");
				}

				//获取消耗
				int count = upgradecfg.character_upgrade[feededch - 1].convertcost[level - 1];

				ret = logicEquip.UseEquipment(m_nUid, convertEquip["id"].asUInt(), convertud, count, "Keepsake_Feed");

				if (ret)
				{
					throw runtime_error("use_convert_equip_error");
				}
			}
		}

		//消耗装备或者道具
		ret = logicEquip.UseEquipment(m_nUid, dataEquip["id"].asUInt(), ud, num, "Keepsake_Feed");

		if (ret)
		{
			throw runtime_error("use_equip_error");
		}

		//信物添加经验
		AddExp(dataKeepsakeEquip, add_exp, upgradecfg.character_upgrade[character - 1].exp, MAX_KEEPSAKE_LEVEL);

		//更新装备信息
		ret = logicEquip.Chg(m_nUid, equd, dataKeepsakeEquip);

		if(ret)
		{
			throw runtime_error("update_equip_error");
		}
	}

	//记录信物吞噬日志
	Json::FastWriter writer;
	string equipData = writer.write(dataKeepsakeEquip);
	EQUIPMENT_LOG("uid=%u,id=%u,eqid=%d,act=%s,chg=%d,count=%d,code=%s,data=%s", m_nUid, equd, dataKeepsakeEquip["id"].asUInt(), "eat",0, 0, "Keepsake_Feed", equipData.c_str());

	result["equip"] = dataKeepsakeEquip;

	return 0;
}

int KeepsakeUnit::AddExp(Json::Value & keepsake, int addexp, unsigned * pexp, int length)
{
	//经验的增加
	int oldlevel = keepsake["q"].asUInt();

	//增加经验
	keepsake["xwexp"] = keepsake["xwexp"].asUInt() + addexp;

	//当前经验已达到最高等级的经验
	if (keepsake["xwexp"].asUInt() >= pexp[length - 1])
	{
		keepsake["q"] = length;
		keepsake["xwexp"] = pexp[length - 1];
	}

	//等级作为下标
	int i = 0;

	for(; i < length; ++i)
	{
		if (pexp[i] > keepsake["xwexp"].asUInt())
		{
			break;
		}
	}

	keepsake["q"] = i;

	//todo 处理部件升级后，解锁副属性
	if (keepsake["q"].asUInt() > oldlevel)
	{
		UnlockSlave(keepsake);
	}

	return 0;
}

int KeepsakeUnit::UnlockSlave(Json::Value & keepsake)
{
	//获取信物的基础配置
	CDataXML *dataXML = DataXmlPtr();
	XMLTokenBase basecfg;
	int ret = dataXML->GetKeepSakeBaseCfg(basecfg);

	if (ret)
	{
		error_log("[UnlockSlaveProperty] get basecfg error.");
		throw runtime_error("get_basecfg_error");
	}

	int target = -1;

	//todo 处理升级的时候可能跨级的问题，比如一下子就从1级升到了3级
	for(int i = 0; i < MAX_SLAVE_PROPNUM; ++i)
	{
		//等级等于高于解锁条件的，都调用解锁副属性接口
		if (basecfg.slave_unlock_level[i] <= keepsake["q"].asUInt())
		{
			//解锁副属性
			UnlockSlaveProperty(keepsake, i);
		}
		else  //这个都没通过，就不用循环下一个解锁条件了，因为后面更大
		{
			break;
		}
	}

	return 0;
}

int KeepsakeUnit::UnlockSlaveProperty(Json::Value & keepsake, int target)
{
	unsigned randomval = Math::GetRandomInt(max_slave_property_kind) + 1;   //1-14中随机一类型

	if (!keepsake.isMember("xwsub"))
	{
		Json::Value array(Json::arrayValue);

		keepsake["xwsub"] = array;
	}

	int size = keepsake["xwsub"].size();

	if (size == target)  //该条目未解锁
	{
		keepsake["xwsub"].append(randomval);
	}

	return 0;
}

int KeepsakeUnit::VerifyCondition(unsigned uid, Json::Value & self, Json::Value & others)
{
	//读取配置
	CDataXML *dataXML = DataXmlPtr();

	if (self["q"].asInt() >= MAX_KEEPSAKE_LEVEL)
	{
		error_log("current equd [%u]'s quality is max.",  self["ud"].asUInt());
		throw runtime_error("qlevel_is_already_max");
	}

	CLogicEquipment logicEquip;
	Json::Value dataEquip;

	unsigned selfch = 1;
	Json::GetUInt(self, "ch", selfch);

	unsigned defective_eqid = 0;
	unsigned exp_props_eqid = 0;

	dataXML->GetSakeDefective(defective_eqid);  //残品
	dataXML->GetSakeExpProps(exp_props_eqid);  //经验石

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

		if (dataEquip["id"].asUInt() == exp_props_eqid)  //提升丹
		{
			continue;
		}
		else if (dataEquip["id"].asUInt() == defective_eqid)
		{
			error_log("current eqid[%u]'s not allow feed. it's defective.", defective_eqid);
			throw runtime_error("feed_eqid_error");
		}
		else if (selfch < oterch)  //先判断品质等级是否存在下对上的关系
		{
			error_log("current ud[%u]'s character is lower than resource ud[%u]. not allow feed", self["ud"].asUInt(), ud);
			throw runtime_error("charater_condition_not_fit");
		}
	}

	return R_SUCCESS;
}

//英雄训练
const int HeroTrainUnit::COIN_INDEX[MAX_INDEX_ITEM] = {4,12,20};
const int HeroTrainUnit::HOUR_INDEX[MAX_INDEX_ITEM] = {3,8,12};
const int HeroTrainUnit::EQUIP_NUM_INDEX[MAX_INDEX_ITEM] = {1,2,3};

//技能训练
const int SkillUnit::FREE_SPEED_TIME[MAX_VIP_LEVEL] = {5,6,7,8,9,10,15,15,15,15};


////////////////////////////////////////////////////////////////////////////////////////
StarStoneChangeUnit::StarStoneChangeUnit(const UserWrap& user)
	: SecincActivityUnit(
		  user.Id()
		, CONFIG_STAR_STONE_CHG
		, NAT_STAR_STONE_CHG)
{
	Init();
}

void StarStoneChangeUnit::Reset()
{
	m_jsonData["a"] = 0;
}

int StarStoneChangeUnit::DrawImpl(
		UserWrap& user, const BaseCmdParams& params, Json::Value& result)
{
	const ConfigActivity::StarStoneChange& starstone = ConfigManager::Instance()->m_activitycfg.m_config.starstone();

	if(m_jsonData["a"].asUInt() >= starstone.limit())
		return R_ERR_LOGIC;
	m_jsonData["a"] = m_jsonData["a"].asUInt() + 1;

	unsigned ud = params.ValueAsUInt("ud");
	CLogicEquipment logicEquip;
	Json::Value eq;
	int ret = logicEquip.Get(m_nUid, ud, eq);
	if(ret)
		return ret;

	unsigned src = eq["id"].asUInt(), dst = params.ValueAsUInt("id");
	bool s = false, d = false;
	for(int i=0;i<starstone.src_size();i++)
	{
		if(starstone.src(i) == src)
		{
			s = true;
			break;
		}
	}
	for(int i=0;i<starstone.dst_size();i++)
	{
		if(starstone.dst(i) == dst)
		{
			d = true;
			break;
		}
	}
	if(!s || !d)
		return R_ERR_LOGIC;

	eq["id"] = dst;
	ret = logicEquip.Chg(m_nUid, ud, eq);
	if(ret)
		return ret;

	Save();

	result["newAct"] = m_jsonData;
	result["equip"] = eq;
	EQUIPMENT_LOG("uid=%u,id=%u,eqid=%d,act=%s,chg=%d,count=%d,code=%s,data=%s", m_nUid, ud, dst, "chg", 0, 0, "StarStoneChangeUnit", Json::FastWriter().write(eq).c_str());

	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////
VickyAccXUnit::VickyAccXUnit(const UserWrap& user)
	: BaseFeedbackActUnit(user.Id(), CONFIG_VICKY_ACC_X, NAT_VICKY_ACC_X)
	, cfg_(DataXmlPtr()->GetVickyAccX())
{
	Init();
}
VickyAccXUnit1::VickyAccXUnit1(const UserWrap& user)
	: BaseFeedbackActUnit(user.Id(), CONFIG_VICKY_ACC_X1, NAT_VICKY_ACC_X1)
	, cfg_(DataXmlPtr()->GetVickyAccX1())
{
	Init();
}
VickyAccXUnit2::VickyAccXUnit2(const UserWrap& user)
	: BaseFeedbackActUnit(user.Id(), CONFIG_VICKY_ACC_X2, NAT_VICKY_ACC_X2)
	, cfg_(DataXmlPtr()->GetVickyAccX2())
{
	Init();
}
VickyAccXUnit3::VickyAccXUnit3(const UserWrap& user)
	: BaseFeedbackActUnit(user.Id(), CONFIG_VICKY_ACC_X3, NAT_VICKY_ACC_X3)
	, cfg_(DataXmlPtr()->GetVickyAccX3())
{
	Init();
}
VickyAccXUnit4::VickyAccXUnit4(const UserWrap& user)
	: BaseFeedbackActUnit(user.Id(), CONFIG_VICKY_ACC_X4, NAT_VICKY_ACC_X4)
	, cfg_(DataXmlPtr()->GetVickyAccX4())
{
	Init();
}
VickyAccXUnit5::VickyAccXUnit5(const UserWrap& user)
	: BaseFeedbackActUnit(user.Id(), CONFIG_VICKY_ACC_X5, NAT_VICKY_ACC_X5)
	, cfg_(DataXmlPtr()->GetVickyAccX5())
{
	Init();
}
huangzhongUnit::huangzhongUnit(const UserWrap& user)
	: BaseFeedbackActUnit(user.Id(), CONFIG_huangzhong, NAT_huangzhong)
	, cfg_(DataXmlPtr()->Gethuangzhong())
{
	Init();
}
VickyNewOpenUnit::VickyNewOpenUnit(const UserWrap& user)
	: BaseFeedbackActUnit(user.Id(), CONFIG_VICKY_NEW_OPEN, NAT_VICKY_NEW_OPEN)
	, cfg_(DataXmlPtr()->GetVickyNewOpen())
{
	Init();
}

ChongZhiZiXuan::ChongZhiZiXuan(const UserWrap& user)
	:SecincActivityUnit(user.Id(), CONFIG_CHONGZHI_ZIXUAN, NAT_CHONGZHIZIXUAN)
{
	Init();
}
int ChongZhiZiXuan::Get(UserWrap& user, Json::Value& result)
{
	result["NewAct"] = m_jsonData;
	result["c"] = user.GetRechargePoint(status_cfg_);
	return 0;
}
int ChongZhiZiXuan::DrawImpl(UserWrap& user, const BaseCmdParams& params, Json::Value& result)
{
	int ret = 0;
	unsigned charge = user.GetRechargePoint(status_cfg_);
	unsigned pool = params.ValueAsUInt("type");
	if (pool >= CHONGZHIZIXUAN_POOL_COUNT) {
		error_log("param error. uid=%u,pool=%u", user.Id(), pool);
		throw std::runtime_error("pool_error");
	}
	vector<unsigned> select;
	params.ValueAsArray("select", select);
	if (select.size() != 4) {
		error_log("select size error uid=%u size=%u", user.Id(), select.size());
		throw std::runtime_error("select_size_error");
	}
	CDataXML *dataxml = CDataXML::GetCDataXML();
	if (NULL == dataxml) {
		error_log("get dataXML error uid=%d", user.Id());
		throw std::runtime_error("get_data_xml_error");
	}
	unsigned times = 0;
	dataxml->GetChongZhiZiXuanCharge(pool, charge, times);
	unsigned used = m_jsonData["u"].get(pool, 0).asUInt();
	if (used + 1 > times) {
		error_log("times limit uid=%u,times=%u,now_times=%u,charge=%u,pool=%u",
				user.Id(), times, used, charge, pool);
		throw std::runtime_error("times_error");
	}

	m_jsonData["u"][pool] = used + 1;

	Save();

	vector<GiftEquipItem> reward;
	string code = "chongzhizixuan";
	for (int i = 0; i < select.size(); ++i) {
		dataxml->GetChongZhiZiXuanItem(pool, select[i], reward);
	}

	AddGiftEquips(reward, code, result);
	result["NewAct"] = m_jsonData;
	return 0;
}
void ChongZhiZiXuan::Reset() {
	m_jsonData["u"] = Json::Value(Json::arrayValue);
	for (int i = 0; i < CHONGZHIZIXUAN_POOL_COUNT; ++i) {
		m_jsonData["u"].append(0);
	}
}

////////////////////////////////////////////////////////////////////////////////////////
TaskGiftUnit::TaskGiftUnit(const UserWrap& user)
	: SecincActivityUnit(
		  user.Id()
		, CONFIG_NEWYEAR_GIFT
		, NAT_TASK_GIFT)
{
	Init();
}
void TaskGiftUnit::Reset()
{
	m_jsonData["a"].resize(0);
	m_jsonData["b"].resize(0);
	for(int i=0;i<7;i++)
	{
		m_jsonData["a"].append(0);
		m_jsonData["b"].append(0);
	}
}
int TaskGiftUnit::DrawImpl(UserWrap& user, const UnitIndexCmdParams& params, Json::Value& result)
{
	const ConfigActivity::TaskGift& cfg = ConfigManager::Instance()->m_activitycfg.m_config.hebdomadreward(params.Index());
	if(params.Index() >= m_jsonData["b"].size() || m_jsonData["b"][params.Index()].asUInt())
		return R_ERR_LOGIC;
	m_jsonData["b"][params.Index()] = 1;
	ProvideCommonReward(cfg.reward(), "TaskGift", result);
	Save();
	result["newAct"] = m_jsonData;
	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////
ActivityMeiRenUnit::ActivityMeiRenUnit(const UserWrap& user): SecincActivityUnit(user.Id(), CONFIG_BEAUTY, 0), user_(user) {
	Init();
}
int ActivityMeiRenUnit::DrawImpl(UserWrap& user, const BaseCmdParams& params, Json::Value& result) {
	unsigned id = params.ValueAsUInt("id");
	unsigned reward_flag = 0;
	Json::GetUInt(m_jsonData["reward"]["r"], id, reward_flag);
	if (reward_flag == 1) {
		LOGIC_ERROR_RETURN_MSG("reward_flag_error");
	}
	unsigned point = 0;
	Json::GetUInt(m_jsonData["reward"], "b", point);
	CDataXML *pData = CDataXML::GetCDataXML();
	if (pData == NULL) {
		DATA_ERROR_RETURN_MSG("XML_error");
	}
	XMLBeautyRewardItem cfg;
	int ret = pData->GetBeautyReward(id + 1, cfg);
	if (ret) {
		error_log("GetBeautyReward error uid=%u id=%u ret=%d", user.Id(), id, ret);
		return ret;
	}
	if (point < cfg.require) {
		error_log("point error uid=%u id=%u point=%u require=%u", user.Id(), id, point, cfg.require);
		LOGIC_ERROR_RETURN_MSG("point_error");
	}
	m_jsonData["reward"]["r"][id] = 1;

	Save();

	vector<GiftEquipItem> reward;
	for (int i = 0; i < XML_BEAUTY_REWARD_COUNT; ++i) {
		if (cfg.reward[i].IsEquip()) {
			reward.push_back(cfg.reward[i]);
		}
	}
	string code = "beauty_reward_" + CTrans::ITOS(id);
	AddGiftEquips(reward, code, result);

	Get(result);

	return 0;
}
int ActivityMeiRenUnit::AddPoint(UserWrap& user, const BaseCmdParams& params, Json::Value& result) {
	unsigned id = params.ValueAsUInt("id");
	if (id >= XML_BEAUTY_ACTIVE_ITEM_COUNT) {
		PARAM_ERROR_RETURN_MSG("id_error");
	}
	CDataXML *pData = CDataXML::GetCDataXML();
	if (pData == NULL) {
		DATA_ERROR_RETURN_MSG("XML_error");
	}
	XMLBeautyActiveItem cfg;
	int ret = pData->GetBeautyActive(id + 1, cfg);
	if (ret != 0) {
		error_log("GetBeautyActive error uid=%u id=%u ret=%d", user.Id(), id, ret);
		DATA_ERROR_RETURN_MSG("cfg_error");
	}
	unsigned cur = 0;
	Json::GetUInt(m_jsonData["active"]["a"], id, cur);
	if (cur >= static_cast<unsigned>(cfg.max)) {
		error_log("limit error uid=%u id=%u cur=%u max=%u", user.Id(), id, cur, static_cast<unsigned>(cfg.max));
		return 0;
	}
	m_jsonData["active"]["a"][id] = cur + 1;
	m_jsonData["active"]["p"] = m_jsonData["active"]["p"].asUInt() + cfg.add;

	Save();

	string code = "beauty_active_" + CTrans::ITOS(id);
	ORDERS_LOG("uid=%u&code=%s&price=%u&amount=1&type=0", user.Id(), code.c_str(), static_cast<unsigned>(cfg.add));
	Get(result);
	return 0;
}
int ActivityMeiRenUnit::UsePoint(UserWrap& user, const BaseCmdParams& params, Json::Value& result) {
	unsigned type = params.ValueAsUInt("type");
	unsigned count = params.ValueAsUInt("count");
	switch (type) {
	case e_ACT_MEIREN_POINT_ACTIVE:
		return UseActivePoint(count == 0 ? 1 : count, result);
	case e_ACT_MEIREN_POINT_CONSUME:
		return UseConsumePoint(count == 0 ? 1 : count, result);
	case e_ACT_MEIREN_POINT_CHARGE:
		return UseChargePoint(count == 0 ? 1 : count, result);
	default:
		error_log("type error uid=%u id=%u", user.Id(), type);
		throw std::runtime_error("type_error");
	}
	return 0;
}
int ActivityMeiRenUnit::Get(Json::Value& result) {
	result["newAct"] = Json::Value(Json::arrayValue);
	result["newAct"].append(m_jsonData["reward"]);
	result["newAct"].append(m_jsonData["active"]);
	return 0;
}
void ActivityMeiRenUnit::Init() {
	int ret = 0;
	CLogicSecinc logicSecinc;
	Json::Value active;
	ret = logicSecinc.GetSecinc(m_nUid, NAT_BEAUTY_ACTIVE, active);
	if (R_SUCCESS != ret && R_ERR_NO_DATA != ret) {
		throw std::runtime_error("get_new_active_data_error");
	}
	unsigned v = 0;
	Json::GetUInt(active, "v", v);
	if (v != status_cfg_.Version()) {
		active.clear();
		active["id"] = NAT_BEAUTY_ACTIVE;
		active["v"] = status_cfg_.Version();
		active["ts"] = Time::GetGlobalTime();
		active["p"] = 0;
		active["a"] = Json::Value(Json::arrayValue);
		for (int i = 0; i < XML_BEAUTY_ACTIVE_ITEM_COUNT; ++i) {
			active["a"].append(0);
		}
	} else {
		unsigned ts = 0;
		Json::GetUInt(active, "ts", ts);
		if (CTime::IsDiffDay(ts, Time::GetGlobalTime())) {
			active["ts"] = Time::GetGlobalTime();
			active["a"] = Json::Value(Json::arrayValue);
			for (int i = 0; i < XML_BEAUTY_ACTIVE_ITEM_COUNT; ++i) {
				active["a"].append(0);
			}
		}
	}
	m_jsonData["active"] = active;

	Json::Value reward;
	ret = logicSecinc.GetSecinc(m_nUid, NAT_BEAUTY_REWARD, reward);
	if (R_SUCCESS != ret && R_ERR_NO_DATA != ret) {
		throw std::runtime_error("get_new_active_data_error");
	}
	v = 0;
	Json::GetUInt(reward, "v", v);
	if (v != status_cfg_.Version()) {
		reward.clear();
		reward["id"] = NAT_BEAUTY_REWARD;
		reward["v"] = status_cfg_.Version();
		reward["b"] = 0;
		reward["u"] = Json::Value(Json::arrayValue);
		for (int i = 0; i < e_ACT_MEIREN_POINT_MAX; ++i) {
			reward["u"].append(0);
		}
		reward["r"] = Json::Value(Json::arrayValue);
		for (int i = 0; i < XML_BEAUTY_REWARD_ITEM_COUNT; ++i) {
			reward["r"].append(0);
		}
	}
	m_jsonData["reward"] = reward;
}
void ActivityMeiRenUnit::Save() {
	CLogicSecinc logicSecinc;
	Json::Value newAct = Json::Value(Json::arrayValue);
	newAct.append(m_jsonData["reward"]);
	newAct.append(m_jsonData["active"]);
	int ret = logicSecinc.SetSecinc(m_nUid, newAct);
	if (ret != R_SUCCESS) {
		throw std::runtime_error("Save_data_failed");
	}
	need_save = false;
}
int ActivityMeiRenUnit::UseActivePoint(unsigned count, Json::Value& result) {
	unsigned hold = 0, used = 0, left = 0, point = 0;
	Json::GetUInt(m_jsonData["reward"]["u"], e_ACT_MEIREN_POINT_ACTIVE, used);
	Json::GetUInt(m_jsonData["reward"], "b", point);
	Json::GetUInt(m_jsonData["active"], "p", hold);
	left = hold > used ? hold - used : 0;
	for (int i = 0; i < count; ++i) {
		if (left == 0) {
			break;
		}
		point += ACTIVE_POINT_MIN + Math::GetRandomInt(ACTIVE_POINT_MAX - ACTIVE_POINT_MIN + 1);
		left -= 1;
		used += 1;
	}
	m_jsonData["reward"]["b"] = point;
	m_jsonData["reward"]["u"][e_ACT_MEIREN_POINT_ACTIVE] = used;

	Save();

	Get(result);

	return 0;
}
int ActivityMeiRenUnit::UseConsumePoint(unsigned count, Json::Value& result) {
	unsigned hold = 0, used = 0, left = 0, point = 0;
	hold = user_.GetCost(status_cfg_.StartTS(), status_cfg_.EndTS()).first / 20;
	Json::GetUInt(m_jsonData["reward"]["u"], e_ACT_MEIREN_POINT_CONSUME, used);
	Json::GetUInt(m_jsonData["reward"], "b", point);
	left = hold > used ? hold - used : 0;
	for (int i = 0; i < count; ++i) {
		if (left == 0 || used >= 125) {
			break;
		}
		point += COSUME_POINT_MIN + Math::GetRandomInt(COSUME_POINT_MAX - COSUME_POINT_MIN + 1);
		left -= 1;
		used += 1;
	}
	m_jsonData["reward"]["b"] = point;
	m_jsonData["reward"]["u"][e_ACT_MEIREN_POINT_CONSUME] = used;

	Save();

	Get(result);

	return 0;
}
int ActivityMeiRenUnit::UseChargePoint(unsigned count, Json::Value& result) {
	unsigned hold = 0, used = 0, left = 0, point = 0;
	hold = user_.GetRechargePoint(status_cfg_) / 100;
	Json::GetUInt(m_jsonData["reward"]["u"], e_ACT_MEIREN_POINT_CHARGE, used);
	Json::GetUInt(m_jsonData["reward"], "b", point);
	left = hold > used ? hold - used : 0;
	for (int i = 0; i < count; ++i) {
		if (left == 0) {
			break;
		}
		point += CHARGE_POINT_MIN + Math::GetRandomInt(CHARGE_POINT_MAX - CHARGE_POINT_MIN + 1);
		left -= 1;
		used += 1;
	}
	m_jsonData["reward"]["b"] = point;
	m_jsonData["reward"]["u"][e_ACT_MEIREN_POINT_CHARGE] = used;

	Save();

	Get(result);

	return 0;
}

ActivityInvestment::ActivityInvestment(const UserWrap& user)
		: SecincActivityUnit(user.Id(), CONFIG_INVESTMENT, NAT_INVESTMENT), user_(user) {
	Init();
}
void ActivityInvestment::Reset() {
	m_jsonData["a"] = 0; //单次投资次数
	m_jsonData["c"] = 0; //消耗次数
	m_jsonData["d"] = 0; //总投资收益
	m_jsonData["b"] = 0; //单次投资收益加本金
	m_jsonData["x"] = 0; //单次投资系数
	m_jsonData["r"] = Json::Value(Json::arrayValue); //领奖标记
	for (int i = 0; i < XML_INVESTMENT_REWARD_NUM; ++i) {
		m_jsonData["r"].append(0);
	}
}
int ActivityInvestment::SelectCount(UserWrap& user, const BaseCmdParams& params, Json::Value& result) {
	unsigned count = params.ValueAsUInt("count");
	if (!IsValidActTime()) {
		throw std::runtime_error("select_count_over");
	}
	unsigned cash = user_.GetRechargePoint(status_cfg_);
	unsigned cost = m_jsonData["c"].asUInt() * e_ACT_INVESTMENT_PRICE;
	unsigned hold = cash > cost ? cash - cost : 0;
	if (hold < e_ACT_INVESTMENT_PRICE) {
		throw std::runtime_error("hold_error");
	}
	if (count > hold / e_ACT_INVESTMENT_PRICE) {
		throw std::runtime_error("count_error");
	}
	m_jsonData["a"] = count;
	m_jsonData["b"] = 0;
	m_jsonData["x"] = 0;

	Save();
	Get(result);

	ORDERS_LOG("uid=%u&code=InvestmentCountSelect&price=%u&amount=1", m_nUid, count);

	return 0;
}
int ActivityInvestment::SelectOption(UserWrap& user, const BaseCmdParams& params, Json::Value& result) {
	if (!IsValidActTime()) {
		throw std::runtime_error("select_option_over");
	}
	if (m_jsonData["a"].asUInt() == 0) {
		throw std::runtime_error("select_count_first");
	}
	CDataXML *pData = CDataXML::GetCDataXML();
	if (pData == NULL) {
		throw std::runtime_error("cfg_error");
	}
	vector<unsigned> rate;
	pData->GetInvestmentRate(rate, false);
	unsigned total_rate = 0;
	for (int i = 0; i < e_ACT_INVESTMENT_ITEM_NUM; ++i) {
		random_shuffle(rate.begin(), rate.end());
		total_rate += *(rate.begin());
	}

	unsigned count = m_jsonData["a"].asUInt();
	unsigned cash = count * e_ACT_INVESTMENT_PRICE;
	unsigned add = cash * total_rate / XML_INVESTMENT_RATE_MULTIPLE;
	m_jsonData["c"] = m_jsonData["c"].asUInt() + count;
	m_jsonData["d"] = m_jsonData["d"].asUInt() + add;
	m_jsonData["b"] = add + cash;
	m_jsonData["x"] = total_rate;
	m_jsonData["a"] = 0;

	Save();
	Get(result);

	ORDERS_LOG("uid=%u&code=InvestmentOptionDone&price=%0.2f&amount=%u", m_nUid, static_cast<float>(total_rate) / 10.0f, cash);

	return 0;
}
int ActivityInvestment::Reward(UserWrap& user, const BaseCmdParams& params, Json::Value& result) {
	unsigned id = params.ValueAsUInt("id");
	CDataXML *pData = CDataXML::GetCDataXML();
	if (pData == NULL) {
		throw std::runtime_error("cfg_error");
	}
	XMLInvestmentReward cfg;
	int ret = pData->GetInvestmentReward(id + 1, cfg);
	if (0 != ret) {
		error_log("GetInvestmentReward error uid=%u id=%u", user.Id(), id);
		throw std::runtime_error("cfg_id_error");
	}
	unsigned cash = user.GetRechargePoint(status_cfg_);
	unsigned cost = m_jsonData["c"].asUInt() * e_ACT_INVESTMENT_PRICE;
	//unsigned hold = cash > cost ? cash - cost : 0;
	unsigned hold = m_jsonData["d"].asUInt() + cash;
	if (cfg.require > hold) {
		error_log("require error uid=%u id=%u hold=%u require=%u", user.Id(), id, hold, cfg.require);
		throw std::runtime_error("require_error");
	}
	if (m_jsonData["r"][id].asUInt() == 1) {
		error_log("flag error uid=%u id=%u", user.Id(), id);
		throw std::runtime_error("reward_flag_error");
	}
	m_jsonData["r"][id] = 1;
	Save();
	vector<GiftEquipItem> reward;
	for (int i = 0; i < XML_BEAUTY_REWARD_COUNT; ++i) {
		if (cfg.reward[i].IsEquip()) {
			reward.push_back(cfg.reward[i]);
		}
	}
	string code = "investment_reward_" + CTrans::ITOS(id);
	AddGiftEquips(reward, code, result);
	Get(result);
	return 0;
}
int ActivityInvestment::Get(Json::Value& result) {
	AutoRate();
	result["newAct"] = m_jsonData;
	return 0;
}
bool ActivityInvestment::IsValidActTime() {
	return Time::GetGlobalTime() + 14400 < status_cfg_.EndTS();
}
int ActivityInvestment::AutoRate() {
	if (IsValidActTime()) {
		return 0;
	}
	unsigned cash = user_.GetRechargePoint(status_cfg_);
	unsigned cost = m_jsonData["c"].asUInt() * e_ACT_INVESTMENT_PRICE;
	unsigned hold = cash > cost ? cash - cost : 0;
	if (hold < e_ACT_INVESTMENT_PRICE) {
		return 0;
	}
	CDataXML *pData = CDataXML::GetCDataXML();
	if (pData == NULL) {
		throw std::runtime_error("cfg_error");
	}
	vector<unsigned> rates;
	pData->GetInvestmentRate(rates, true);
	random_shuffle(rates.begin(), rates.end());
	unsigned rate = *(rates.begin());
	unsigned count = hold / e_ACT_INVESTMENT_PRICE;
	m_jsonData["c"] = m_jsonData["c"].asUInt() + count;
	m_jsonData["d"] = m_jsonData["d"].asUInt() + count * e_ACT_INVESTMENT_PRICE * rate / XML_INVESTMENT_RATE_MULTIPLE;
	m_jsonData["a"] = 0;
	m_jsonData["b"] = 0;

	Save();
	return 0;
}
ActivityBirdBridge::ActivityBirdBridge(const UserWrap& user)
	: SecincActivityUnit(user.Id(), CONFIG_BIRDBRIDGE, NAT_ACTIVITY_BIRDBRIDGE) {
	Init();
	_left_code.clear();
	_right_code.clear();
	_center_code.clear();
}
void ActivityBirdBridge::Reset() {
	m_jsonData["r"] = Json::Value(Json::arrayValue);
	m_jsonData["l"] = Json::Value(Json::arrayValue);
	for (int i = 0; i < XML_BIRD_BRIDGE_ITEM_NUM; ++i) {
		m_jsonData["r"][i] = 0;
		m_jsonData["l"][i] = 0;
	}
	m_jsonData["c"] = 0;
}
int ActivityBirdBridge::DrawImpl(UserWrap& user, const BaseCmdParams& params, Json::Value& result) {
	unsigned type = params.ValueAsUInt("type");
	unsigned id = params.ValueAsUInt("id");
	unsigned all = params.ValueAsUInt("yijian");

	int ret = 0;
	if (all == 0 && type > ACT_BIRD_BRIDGE_REWARD_CENTER) {
		LOGIC_ERROR_RETURN_MSG("type_error");
	}
	unsigned totalCharge = user.GetRechargePoint(status_cfg_);
	Json::Value equipLeft;
	Json::Value equipRigth;
	unsigned equipLeftCount = 0;
	unsigned equipRigthCount = 0;
	CLogicEquipment logicEquipment;
	ret = GetEquipById(ACT_BIRD_BRIDGE_LEFT, equipLeft);
	if (0 == ret) {
		Json::GetUInt(equipLeft, "count", equipLeftCount);
	}
	ret = GetEquipById(ACT_BIRD_BRIDGE_RIGHT, equipRigth);
	if (0 == ret) {
		Json::GetUInt(equipRigth, "count", equipRigthCount);
	}
	vector<GiftEquipItem> reward;
	if (all == 1) {
		ret = RewardEdge(m_jsonData["l"], ACT_BIRD_BRIDGE_REWARD_LEFT, 0xFFFFFFFF, totalCharge + equipLeftCount, reward);
		if (ret) {
			return ret;
		}
		ret = RewardEdge(m_jsonData["r"], ACT_BIRD_BRIDGE_REWARD_RIGHT, 0xFFFFFFFF, totalCharge + equipRigthCount, reward);
		if (ret) {
			return ret;
		}
		ret = RewardCenter(totalCharge + equipLeftCount, totalCharge + equipRigthCount, reward);
		if (ret) {
			return ret;
		}
	} else {
		switch (type) {
		case ACT_BIRD_BRIDGE_REWARD_LEFT:
			ret = RewardEdge(m_jsonData["l"], ACT_BIRD_BRIDGE_REWARD_LEFT, id, totalCharge + equipLeftCount, reward);
			break;
		case ACT_BIRD_BRIDGE_REWARD_RIGHT:
			ret = RewardEdge(m_jsonData["r"], ACT_BIRD_BRIDGE_REWARD_RIGHT, id, totalCharge + equipRigthCount, reward);
			break;
		case ACT_BIRD_BRIDGE_REWARD_CENTER:
			ret = RewardCenter(totalCharge + equipLeftCount, totalCharge + equipRigthCount, reward);
			break;
		}
		if (ret != 0) {
			error_log("uid=%u,type=%u,id=%u", user.Id(), type, id);
			return ret;
		}
	}

	result["newAct"] = m_jsonData;

	string code = "birdbridge*" + _left_code + "*" + _right_code + "*" + _center_code;
	if (reward.empty()) {
		error_log("reward empty uid=%u, code=%s", user.Id(), code.c_str());
		return 0;
	}

	Save();

	AddGiftEquips(reward, code, result);

	return 0;
}
int ActivityBirdBridge::RewardCenter(unsigned pointLeft, unsigned pointRight, vector<GiftEquipItem> &reward) {
	int ret = 0;
	int rewardFlag = 0;
	Json::GetInt(m_jsonData, "c", rewardFlag);
	if (rewardFlag != 0) {
		error_log("reward flag error uid=%u", m_nUid);
		return 0;
	}
	CDataXML *pdata = CDataXML::GetCDataXML();
	if (pdata == NULL) {
		throw std::runtime_error("xml_error");
	}
	XMLBirdBridgeItem cfg;
	ret = pdata->GetBirdBridgeItem(ACT_BIRD_BRIDGE_REWARD_CENTER, 0, cfg);
	if (0 != ret) {
		error_log("GetBirdBridgeItem error uid=%u", m_nUid);
		return 0;
	}
	if (pointLeft < cfg.require || pointRight < cfg.require) {
		error_log("require error uid=%u left=%u rigth=%u need=%u", m_nUid, pointLeft, pointRight, cfg.require);
		return 0;
	}
	m_jsonData["c"] = 1;

	for (int j = 0; j < XML_BIRD_BRIDGE_REWARD_NUM; ++j) {
		reward.push_back(cfg.reward[j]);
	}

	_center_code = "1";

	return 0;
}
int ActivityBirdBridge::RewardEdge(Json::Value &act, unsigned type, unsigned id, unsigned point, vector<GiftEquipItem> &reward) {
	int ret = 0;
	vector<unsigned> ids;
	ids.clear();
	if (id == 0xFFFFFFFF) {
		for (size_t i = 0; i < act.size(); ++i) {
			if (act[i].asUInt() == 0) {
				ids.push_back(i);
			}
		}
	} else {
		if (act[id].asUInt() == 0) {
			ids.push_back(id);
		}
	}
	string *code = &_left_code;
	if (type == ACT_BIRD_BRIDGE_REWARD_RIGHT) {
		code = &_right_code;
	}
	CDataXML *pdata = CDataXML::GetCDataXML();
	if (pdata == NULL) {
		throw std::runtime_error("xml_error");
	}
	for (vector<unsigned>::iterator itr = ids.begin(); itr != ids.end(); ++itr) {
		XMLBirdBridgeItem cfg;
		ret = pdata->GetBirdBridgeItem(type, *itr + 1, cfg);
		if (0 != ret) {
			error_log("GetBirdBridgeItem error uid=%u type=%u id=%u ret=%d", m_nUid, type, *itr, ret);
			continue;
		}
		if (point < cfg.require) {
			error_log("require error uid=%u type=%u id=%u hold=%u need=%u", m_nUid, type, *itr, point, cfg.require);
			continue;
		}
		for (int j = 0; j < XML_BIRD_BRIDGE_REWARD_NUM; ++j) {
			reward.push_back(cfg.reward[j]);
		}
		if (!code->empty()) {
			code->append("_");
		}
		code->append(CTrans::ITOS(*itr + 1));
		act[*itr] = 1;
	}

	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////
FreeExchangeUnit::FreeExchangeUnit(const UserWrap& user)
	: SecincActivityUnit(
		  user.Id()
		, CONFIG_FREE_EXCHG
		, NAT_FREE_EXCHG)
{
	Init();
}
void FreeExchangeUnit::Reset()
{
	m_jsonData["u"] = 0;
	m_jsonData["c"].resize(0);
	for(int i=0;i<4;i++)
		m_jsonData["c"].append(0);
}
int FreeExchangeUnit::DrawImpl(UserWrap& user, const BaseCmdParams& params, Json::Value& result)
{
	unsigned const cost[] = {500, 30000, 60000, 100000};
	unsigned const times[] = {40, 1, 1, 1};

	unsigned index = params.ValueAsInt("index");
	vector<unsigned> select_v;
	params.ValueAsArray("select", select_v);
	unsigned count = params.ValueAsInt("count");

	if(index >= 4)
		throw std::runtime_error("free_exchg_index");
	if(count == 0)
		throw std::runtime_error("free_exchg_count");
	set<unsigned> select;
	for(vector<unsigned>::iterator it=select_v.begin();it!=select_v.end();++it)
		select.insert(*it);
	if(index == 0)
	{
		if(select.size() != 4)
			throw std::runtime_error("free_exchg_select");
	}
	else
	{
		if(select.size() != 5)
			throw std::runtime_error("free_exchg_select");
		set<unsigned>::iterator it=select.begin();
		++it;
		if(*it < 3)
			throw std::runtime_error("free_exchg_select");
	}

	if(cost[index] * count + m_jsonData["u"].asUInt() > user.GetRechargePoint(status_cfg_))
		throw std::runtime_error("free_exchg_cost");
	m_jsonData["u"] = cost[index] * count + m_jsonData["u"].asUInt();

	if(count + m_jsonData["c"][index].asUInt() > times[index])
		throw std::runtime_error("free_exchg_times");
	m_jsonData["c"][index] = count + m_jsonData["c"][index].asUInt();

	const ConfigActivity::FreeExchange& cfg = ConfigManager::Instance()->m_activitycfg.m_config.free_exchg(index);
	vector<ItemAdd> equips;
	for(set<unsigned>::iterator it=select.begin();it!=select.end();++it)
	{
		ItemAdd item(cfg.item(*it).id(), cfg.item(*it).c() * count, "free_exchg");
		equips.push_back(item);
	}
	AddEquips(equips, result);

	Save();
	result["newAct"] = m_jsonData;
	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////
