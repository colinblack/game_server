/*
 * LogicCmdBase.cpp
 *
 *  Created on: 2016-8-17
 *      Author: dawx62fac
 */


#include "LogicCmdBase.h"
#include <stdexcept>

BaseCmdUnit::BaseCmdUnit(unsigned uid)
 	: m_nUid(uid)
{
	if (! IsValidUid(uid))
	{
		throw std::runtime_error("invalid_uid");
	}

	need_save = false;
}

BaseCmdUnit::~BaseCmdUnit()
{
	try
	{
		if (need_save)
		{
			Save();
		}
	}
	catch(runtime_error &e)
	{
		;
	}
}

void BaseCmdUnit::Save()
{
	CLogicSecinc logicSecinc;
	int ret = logicSecinc.SetOneSecinc(m_nUid, m_jsonData);
	if (ret !=  R_SUCCESS)
	{
		throw std::runtime_error("Save_data_failed");
	}

	need_save = false;
}

int BaseCmdUnit::TurnVecLuckTable(vector<unsigned> & prates, int len, int & target)
{
	//获得概率总和
	int max = 0, last = 0;

	for(int i = 0 ; i < len && i < prates.size(); ++i)
	{
		max += prates[i];
	}

	int random = 0;

	//产生随机值
	if (0 == max)
	{
		return 0;
	}

	random = Math::GetRandomInt(max);

	int j = 0;

	for (; j < len && j < prates.size(); ++j )
	{
		if (random < (last + prates[j]))
		{
			break;
		}

		last += prates[j];
	}

	target = j;

	return 0;
}

int BaseCmdUnit::SetBitCurrent(unsigned & current, int pos)
{
	//方法？用一个1000的值与current进行或运算即可。而1000中1的位置，就是pos的值.即将1直接左移pos个位置即可
	unsigned target = 1;
	target = target <<pos;

	current = current | target;

	return 0;
}

bool BaseCmdUnit::CheckPosIsZero(unsigned value, unsigned pos)
{
	//第一个1，左移pos，然后与value进行&运算，如果该位为1，则值为1，反之，为0
	unsigned target = 1;

	target = target <<pos;

	int result = value & target;

	return result ? false : true;
}

CDataXML* BaseCmdUnit::DataXmlPtr()
{
	CDataXML* pdataXML = CDataXML::GetCDataXML();
	if(! pdataXML)
	{
		error_log("GetInitXML fail");
		throw std::runtime_error("GetInitXML fail");
	}

	return pdataXML;
}

bool BaseCmdUnit::IsActiving(unsigned nTime, const std::string& start, const std::string& end)
{
	unsigned beginTime = 0;
	unsigned endTime = 0;

	if (Config::GetUIntValue(beginTime, start)
		&& Config::GetUIntValue(endTime, end))
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

unsigned BaseCmdUnit::GetVersionCfg(const std::string& szVersion)
{
	unsigned nVersion = 0;
	if (! Config::GetUIntValue(nVersion, szVersion))
	{
		throw std::runtime_error("can't_get_version_cfg");
	}

	return nVersion;
}

int BaseCmdUnit::GetEquipSubByCh(unsigned ch)
{
	const unsigned subNum[XML_EQUIP_SUB_GOLD + 2] = {0, 1, 3, 5, 5, 5};
	if(ch > XML_EQUIP_SUB_GOLD + 2 || ch == 0)
	{
		throw std::runtime_error("GetEquipSubByCh_ch_params_error");
	}

	return subNum[ch - 1];
}

void BaseCmdUnit::HandleOneSuitEquip(const ItemAdd& item, Json::Value& newEquip)
{
	//newEquip = Json::arrayValue;

	unsigned level = unsigned((item.eqid - 150000) / 1000) * 10 + 50;   //套装等级

	unsigned subNum = GetEquipSubByCh(5);
	vector<EquipSub> sub;
	vector<string> keepstr;
	unsigned stoneID,gold;
	int ret = DataXmlPtr()->GetEquipSub(level,stoneID,gold,subNum,keepstr,sub);
	Json::Value newSub;

	for(int j = 0; j < (int)sub.size(); ++j)
		newSub[sub[j].id] = sub[j].value;

	ItemAdd cpItem = item;
	ret = CLogicEquipment().genEquipSet(cpItem, newEquip, newSub, 1100);
	if(ret != 0)
	{
		error_log("add equipment suit failed. uid=%u | equip_id=%u", m_nUid);
		throw std::runtime_error("add_equipmentsuit_failed");
	}
}

void BaseCmdUnit::AddSuitEquips(const std::vector<ItemAdd>& int_items, Json::Value& result)
{
	Json::Value newEqDatas = Json::arrayValue;

	for (size_t i = 0; i < int_items.size(); ++i)
	{
		ItemAdd cpitem = int_items[i];
		cpitem.ch = 5;
		HandleOneSuitEquip(cpitem, newEqDatas);
	}

	int ret = CLogicEquipment().UpdateEquipment(m_nUid, 0, newEqDatas, result, true);
	if(ret != 0)
	{
		error_log("add equipment suit failed. uid=%u | equip_id=%u", m_nUid);
		throw std::runtime_error("add_equipmentsuit_failed");
	}
}

void BaseCmdUnit::AddSuitEquips(unsigned eqid,  const std::string& op, Json::Value& result)
{
	std::vector<ItemAdd> vItems;
	vItems.push_back(ItemAdd(eqid, 1, op));

	AddSuitEquips(vItems, result);
}

void BaseCmdUnit::AddEquips(unsigned eqid, const std::string& op, Json::Value& result)
{
	std::vector<ItemAdd> equips;
	equips.push_back(ItemAdd(eqid, 1, op));
	this->AddEquips(equips, result);
}

void BaseCmdUnit::AddEquips(unsigned eqid, unsigned cnt, const std::string& op, Json::Value& result)
{
	std::vector<ItemAdd> equips;
	equips.push_back(ItemAdd(eqid, cnt, op));
	this->AddEquips(equips, result);
}


void BaseCmdUnit::AddEquips(const std::vector<ItemAdd>& items, Json::Value& result)
{
	std::vector<ItemAdd> commonEquips;
	std::vector<ItemAdd> suitEquips;

	for (size_t i = 0; i < items.size(); ++i)
	{
		//套装
		if (IS_SET_EQID(items[i].eqid))
		{
			suitEquips.push_back(items[i]);
		}
		else
		{
			commonEquips.push_back(items[i]);
		}
	}

	int ret = 0;
	CLogicEquipment logicEquipMent;
	if (commonEquips.size() > 0)
	{
		ret = logicEquipMent.AddItems(m_nUid, commonEquips, result["equipments"], true);
		if(ret)
		{
			error_log("Add_Equip_error uid=%u， ret=%u", m_nUid, ret);
			throw std::runtime_error("add_equipitems_failed");
		}
	}

	if (suitEquips.size() > 0)
	{
		AddSuitEquips(suitEquips, result["equip_suit"]);
	}
}

void BaseCmdUnit::CostPurpleKey(unsigned ud, unsigned count, string reason, Json::Value& result)
{
	UseEquips(purple_key, ud, count, reason);
	result["equip_cost"] = count;
}


void BaseCmdUnit::CostGreenKey(unsigned ud, unsigned count, string reason, Json::Value& result)
{
	UseEquips(green_key, ud, count, reason);
	result["equip_cost"] = count;
}


void BaseCmdUnit::UseEquips(unsigned eqid, unsigned ud, unsigned count, string reason)
{
	if (ud == 0)
	{
		error_log("use_Equip_error uid=%u， ud=%d", m_nUid, ud);
		throw std::runtime_error("equip_ud_params_error");
	}

	CLogicEquipment equipment;
	int ret = equipment.UseEquipment(m_nUid, eqid, ud, count, reason);

	if(ret != 0)
	{
		error_log("use_Equip_error uid=%u， ret=%u", m_nUid, ret);
		throw std::runtime_error("use_equipitems_failed");
	}
}

bool BaseCmdUnit::IsExistEquips(unsigned eqid, unsigned ud, unsigned count) const
{
	return CLogicEquipment().Try(m_nUid, eqid, ud, count) == 0;
}

void BaseCmdUnit::AddHeroExp(Json::Value & herodata, int userlv, int add_exp)
{
	int exp = 0;

	Json::GetInt(herodata, "exp", exp);

	exp += add_exp;

	if (exp < 0)
	{
		exp = 0;
	}

	int level = herodata["l"].asInt();

	int max_level = (int) sizeof(hero_lvl_exp)/sizeof(hero_lvl_exp[0]);

	if (exp >=  hero_lvl_exp[max_level - 1])
	{
		level = max_level;
	}
	else
	{
		for (int i = level; i < max_level; i++)
		{
			if (exp < hero_lvl_exp[i])
			{
				level = i;
				break;
			}
		}
	}

	if (level > userlv)   //英雄等级不能大于人物等级
	{
		level = userlv;
		exp = hero_lvl_exp[level];
	}

	herodata["l"] = level;
	herodata["exp"] = exp;

	int hero_ud = 0;
	Json::GetInt(herodata, "ud", hero_ud);
	HERO_LEVEL_LOG("uid=%u,l=%u,ud=%u",m_nUid, level, hero_ud);
}

ItemAdd BaseCmdUnit::Equip2ItemAdd(const GiftEquipItem& equip, const std::string& reason)
{
	ItemAdd itemAdd;
	itemAdd.eqid = equip.m_nId;
	itemAdd.count = equip.m_nCnt;
	itemAdd.q = equip.m_nQuality;
	itemAdd.ch = equip.m_nCh;
	itemAdd.reason = reason;

	return itemAdd;
}

void BaseCmdUnit::AddGiftEquips(
				const GiftEquipItem& equip
				, const std::string& reason
				, Json::Value& result)
{
	GiftEquipItem equips[1];
	equips[0] = equip;

	AddGiftEquips(equips, 1, reason, result);
}

void BaseCmdUnit::AddGiftEquips(
				std::vector<GiftEquipItem>& equips
				, const std::string& reason
				, Json::Value& result)
{
	//装备
	std::vector<ItemAdd> vItemAdds;

	//英雄
	std::vector<std::string> vHeros;
	std::vector<std::string> vReasons;

	for (unsigned i = 0; i < equips.size(); ++i)
	{
		if (equips[i].IsEquip())
		{
			vItemAdds.push_back(Equip2ItemAdd(equips[i], reason));
		}
		else if (equips[i].IsHero())
		{
			vHeros.push_back(CDataXML::Hero2Str(equips[i].m_nId));
			vReasons.push_back(reason);
		}
	}

	//道具
	if (vItemAdds.size() > 0)
	{
		AddEquips(vItemAdds, result);
	}

	//英雄
	if (vHeros.size() > 0)
	{
		CLogicHero logicHero;
		if (0 != logicHero.AddHeros(m_nUid, vHeros, vReasons, result["heros"]))
		{
			error_log("add heros error. uid=%u", m_nUid);
			throw std::runtime_error("add_hero_error");
		}
	}
}

void BaseCmdUnit::AddGiftEquips(
		GiftEquipItem equips[],
		unsigned size,
		const std::string& reason,
		Json::Value& result)
{

	//装备
	std::vector<ItemAdd> vItemAdds;

	//英雄
	std::vector<std::string> vHeros;
	std::vector<std::string> vReasons;

	for (unsigned i = 0; i < size; ++i)
	{
		if (equips[i].IsEquip())
		{
			vItemAdds.push_back(Equip2ItemAdd(equips[i], reason));
		}
		else if (equips[i].IsHero())
		{
			vHeros.push_back(CDataXML::Hero2Str(equips[i].m_nId));
			vReasons.push_back(reason);
		}
	}

	//道具
	if (vItemAdds.size() > 0)
	{
		AddEquips(vItemAdds, result);
	}

	//英雄
	if (vHeros.size() > 0)
	{
		CLogicHero logicHero;
		if (0 != logicHero.AddHeros(m_nUid, vHeros, vReasons, result["heros"]))
		{
			error_log("add heros error. uid=%u", m_nUid);
			throw std::runtime_error("add_hero_error");
		}
	}
}

void BaseCmdUnit::LoadUserGiftData(Json::Value& jsonData) const
{
	jsonData.clear();

	std::string szUserGift;
	if ((CDataUserData().GetGift(m_nUid, szUserGift)) != 0)
	{
		error_log("[get_user_gift failed.uid=%u]", m_nUid);
		throw std::runtime_error("get_user_gift failed");
	}
	Json::Reader().parse(szUserGift, jsonData);
}

void BaseCmdUnit::SaveUserGiftData(const Json::Value& jsonData) const
{
	if (0 != CDataUserData().SetGift(m_nUid, Json::ToString(jsonData)))
	{
		throw std::runtime_error("save_user_gift_error");
	}
}

unsigned BaseCmdUnit::GetActivityVersion(const std::string& szVersion) const
{
	unsigned nVersion = 0;
	if (! Config::GetUIntValue(nVersion, szVersion))
	{
		throw std::runtime_error("can't_get_version_cfg");
	}

	return nVersion;
}

void BaseCmdUnit::TopZoneHttpRequest(const std::string& cgi
		, const std::string& action
		, const Json::Value& req_data
		, Json::Value& result)
{
	std::string data = Json::ToString(req_data);
	string url = "action=" + action;
	if (data.size() > 0)
	{
		url.append("&data=").append(Crypt::UrlEncode(data));
	}

	CLogicAllServerBaseMatch logicBaseMatch;
	int ret = logicBaseMatch.RequestBaseMatch(url, result, cgi, true);
	if (0 != ret)
	{
		throw std::runtime_error("RequestBaseMatch_error");
	}
}

int BaseCmdUnit::ProvideCommonReward(const RewardConfig::RewardItemCfg & rewardcfg,const string & reason, Json::Value & result, unsigned endts, unsigned count)
{
	if(count == 0)
	{
		error_log("count=0!");
		throw runtime_error("count=0!");
	}
	//处理装备奖励
	vector<ItemAdd> equips;
	unsigned nowts = Time::GetGlobalTime();

	for(int i = 0; i < rewardcfg.equips_size(); ++i)
	{
		const RewardConfig::EquipItem&  equipcfg = rewardcfg.equips(i);
		ItemAdd item(equipcfg.eqid(), equipcfg.c() * count, reason, equipcfg.ch(), equipcfg.q());

		if (equipcfg.has_ltime() && endts > nowts)
		{
			//限时道具
			item.ats = endts - nowts;
		}

		equips.push_back(item);
	}

	if (equips.size() > 0)
	{
		AddEquips(equips, result);
	}

	//处理英雄
	vector<string> heros;
	vector<string> reasons;

	for(int i = 0; i < rewardcfg.heros_size(); ++i)
	{
		const RewardConfig::HeroItem&  herocfg = rewardcfg.heros(i);

		for(int j = 0; j < herocfg.c() * count; ++j)
		{
			heros.push_back(herocfg.id());
			reasons.push_back(reason);
		}
	}

	//英雄
	if (heros.size() > 0)
	{
		CLogicHero logicHero;

		if (0 != logicHero.AddHeros(m_nUid, heros, reasons, result["heros"]))
		{
			error_log("add heros error. uid=%u", m_nUid);
			throw std::runtime_error("add_hero_error");
		}
	}

	//加资源
	UserWrap userwrap(m_nUid, true);
	unsigned rs[4] = {0};
	bool ischange = false;

	for(int i = 0; i < rewardcfg.res_size(); ++i)
	{
		if (0 != rewardcfg.res(i))
		{
			ischange = true;
		}

		rs[i] = rewardcfg.res(i) * count;
	}

	if (ischange)
	{
		userwrap.AddResource(rs[0], rs[1], rs[2], rs[3], reason, result);
	}

	//金币，钻石
	int coin = 0, cash = 0;

	if (rewardcfg.has_gold())
	{
		coin = rewardcfg.gold() * count;
	}

	if (rewardcfg.has_diamond())
	{
		cash = rewardcfg.diamond() * count;
	}

	if (coin > 0 || cash > 0)
	{
		userwrap.AddCashCoin(cash, coin, reason, result);
	}

	//能量，战魂，经验等
	if (rewardcfg.has_energy())
	{
		userwrap.AddGCBase(rewardcfg.energy() * count, reason, result);
	}

	if (rewardcfg.has_prosper())
	{
		userwrap.AddProsper(rewardcfg.prosper() * count, reason, result);
	}

	if (rewardcfg.has_exp())
	{
		userwrap.AddExp(rewardcfg.exp() * count, reason, result);
	}

	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////
BaseActivityUnit::BaseActivityUnit(unsigned uid, const std::string& name, unsigned sid)
	: BaseCmdUnit(uid)
	, status_cfg_(name)
	,sid_(sid)
{
	if (! status_cfg_.IsActive())
	{
		throw std::runtime_error("out_activity_time");
	}
}

bool BaseActivityUnit::IsNewVersion(int version) const
{
	return (status_cfg_.Version() != version);
}

int BaseActivityUnit::GetVersion()
{
	return status_cfg_.Version();
}

int BaseActivityUnit::GetBeginTs()
{
	return status_cfg_.StartTS();
}

int BaseActivityUnit::GetEndTs()
{
	return status_cfg_.EndTS();
}

unsigned BaseActivityUnit::GetChargeByTime(UserWrap& userWrap, unsigned endts)
{
	unsigned begints = status_cfg_.StartTS();

	unsigned charge = userWrap.GetRechargePoint(begints, endts);

	return charge;
}

int BaseActivityUnit::CheckActVersion()
{
	//没有版本号字段，无视
	if (!m_jsonData.isMember("v"))
	{
		return 0;
	}

	unsigned oldversion = m_jsonData["v"].asUInt();

	if(status_cfg_.Version() != oldversion)
	{
		//调用重置函数
		ResetAct();
	}

	return 0;
}

int BaseActivityUnit::ResetAct()
{
	return 0;
}

SecincActivityUnit::SecincActivityUnit(unsigned uid, const std::string& name, int nat_id)
	: BaseActivityUnit(uid, name)
	, nat_id_(nat_id)
{

}

void SecincActivityUnit::Init()
{
	int ret = CLogicSecinc().GetSecinc(m_nUid, nat_id_, m_jsonData);
	if (ret != R_SUCCESS && ret != R_ERR_NO_DATA)
	{
		throw std::runtime_error("get_new_active_data_error");
	}

	if (ret == R_ERR_NO_DATA
		|| IsNewVersion(m_jsonData["v"].asInt()))
	{
		m_jsonData["id"] = nat_id_;
		m_jsonData["v"] = status_cfg_.Version();
		Reset();
	}
}

//////////////////////////////////////////////////////////////////////////////////////
BaseCmdParams::BaseCmdParams(const Json::Value& jsonData)
	: json_params_(jsonData)
{
	if (! Json::GetUInt(jsonData, "seqid", seqid_))
	{
		throw std::runtime_error("params_seqid_error");
	}

	if (! Json::GetUInt(jsonData, "lastime", lasttime_))
	{
		throw std::runtime_error("params_lasttime_error");
	}
}

unsigned BaseCmdParams::SeqId() const
{
	return seqid_;
}

unsigned BaseCmdParams::LastTime() const
{
	return lasttime_;
}

unsigned BaseCmdParams::ValueAsUInt(const std::string& key)  const
{
	unsigned val = 0;
	if (! Json::GetUInt(json_params_, key.c_str(), val))
	{
		throw std::runtime_error("params_error");
	}

	return val;
}

int BaseCmdParams::ValueAsInt(const std::string& key, int def) const
{
	int val = 0;
	if (! Json::GetInt(json_params_, key.c_str(), val))
	{
		return def;
	}

	return val;
}

int BaseCmdParams::ValueAsInt(const std::string& key)  const
{
	int val = 0;
	if (! Json::GetInt(json_params_, key.c_str(), val))
	{
		throw std::runtime_error("params_error");
	}

	return val;
}

std::string BaseCmdParams::ValueAsString(const std::string& key) const
{
	std::string val;
	if (! Json::GetString(json_params_, key.c_str(), val))
	{
		throw std::runtime_error("params_error");
	}

	return val;
}

void BaseCmdParams::ValueAsArray(const std::string& key, std::vector<unsigned>& vals) const
{
	if (! json_params_[key].isArray())
	{
		throw std::runtime_error("params_error");
	}

	vals.clear();
	for (unsigned i = 0; i < json_params_[key].size(); ++i)
	{
		vals.push_back(json_params_[key][i].asUInt());
	}
}

///////////////////////////////////////////////////////////////////////////////////
UnitIdCmdParams::UnitIdCmdParams(const Json::Value& jsonData)
	: BaseCmdParams(jsonData)
{
	id_ = ValueAsInt("id");
	if (id_ <= 0)
	{
		throw std::runtime_error("id_params_error");
	}
}

UnitIndexCmdParams::UnitIndexCmdParams(const Json::Value& jsonData)
	: BaseCmdParams(jsonData)
{
	index_ = ValueAsInt("index");
	if (index_ < 0)
	{
		throw std::runtime_error("index_params_error");
	}
}


UnitUdCmdParams::UnitUdCmdParams(const Json::Value& jsonData)
	: BaseCmdParams(jsonData)
{
	ud_ = ValueAsInt("ud", 0);
}


//////////////////////////////////////////////////////////////////////////////////////
BaseFeedbackActUnit::BaseFeedbackActUnit(
		unsigned uid, const std::string& name, int nat_id)
		: SecincActivityUnit(uid, name, nat_id)
{

}

void BaseFeedbackActUnit::Reset()
{
	m_jsonData["a"] = Json::Value(Json::arrayValue);
	for (int i = 0; i < GetDrawItems(); i++)
	{
		m_jsonData["a"][i] = 0;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
int BaseFeedbackActUnit::DrawImpl(UserWrap& user, const BaseFeedbackActUnit::DrawParams& params, Json::Value& result)
{
	int index = params.Index();
	int eqIdx = params.EquipIndex();

	const JsonFeedbackItem& item_cfg = GetFeedbackItem(index);
	if (m_jsonData["a"][index].asInt() > 0)
	{
		throw std::runtime_error("already_draw_reward");
	}

	int need_cost = item_cfg.Amount();
	int total_point = user.GetRechargePoint(status_cfg_);
	if (need_cost > total_point)
	{
		throw std::runtime_error("not_enough_recharge_point");
	}

	m_jsonData["a"][index] = 1;

	Save();

	int eqid = item_cfg.EquipId(eqIdx);
	int eqcnt = item_cfg.EquipCnt(eqIdx);

	this->AddEquips(eqid, eqcnt, DrawOp(), result);

	result["info"] = m_jsonData;

	return 0;
}
