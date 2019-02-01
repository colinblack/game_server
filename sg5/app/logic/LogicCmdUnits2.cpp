#include "LogicCMD.h"

const int FortunePacksActivityUnit::extra_num_relation[MAX_EXTRA_ITEMS] ={1,5,10,15,20,30,35,40,45,50,60,70,80,90};

EquipStrengthenUnit::EquipStrengthenUnit(unsigned uid):
	m_nUid(uid)
{
	CLogicSecinc logicSecinc;
	int ret = logicSecinc.GetSecinc(m_nUid, NAT_EQUIPSTRENGTHEN, m_jsonData);

	if (R_ERR_NO_DATA == ret)
	{
		Json::Value array(Json::arrayValue);

		for(int i = 0; i < max_status_length; ++i)
		{
			array[i] = 0;
		}

		m_jsonData["a"] = array;    //领取状态数组
		m_jsonData["v"] = 0;  //版本号

		m_jsonData["id"] = NAT_EQUIPSTRENGTHEN;

		Save();
	}
	else if (ret)
	{
		error_log("get newact error.uid=%u id=%d", m_nUid, NAT_EQUIPSTRENGTHEN);
		throw std::runtime_error("get_new_active_data_error");
	}
}

int EquipStrengthenUnit::GetChargeReward(UserWrap& userWrap, unsigned index, Json::Value & result)
{
	//版本号判断
	CheckVersion(result);

	//判断index参数合法性
	if (index < 1 || index > max_status_length)
	{
		error_log("wrong index param. uid=%u,index=%u", m_nUid, index);
		throw runtime_error("wrong_param");
	}

	//判断是否已经领取过奖励
	int pos = index - 1;

	if (m_jsonData["a"][pos].asUInt())
	{
		error_log("already get the charge reward. uid=%u,index=%u", m_nUid, index);
		throw runtime_error("already_get_reward");
	}

	RewardInfo reward_info;
	GetRewardInfo(index, reward_info);

	//获取指定时间内的充值额度
	unsigned begints = Config::GetIntValue(CONFIG_EQUIP_STRENGTHEN_BEGIN_TS);  //活动的开启时间
	unsigned now = Time::GetGlobalTime();

	unsigned charget_cash = userWrap.GetRechargePoint(begints, now);

	if (charget_cash < reward_info.quota)
	{
		error_log("charge cash is not enough. uid=%u,needcash=%u.charge_cash=%u", m_nUid, reward_info.quota, charget_cash);
		throw runtime_error("charge_cash_not_enough");
	}

	//满足条件，发放奖励
	vector<ItemAdd> equips;
	ItemAdd luckstone(reward_info.luck_stone_id, reward_info.luck_stone_num, "EquipStrengthenEvent");
	ItemAdd strengstone(reward_info.strongthen_stone_id, reward_info.strongthen_stone_num, "EquipStrengthenEvent");

	equips.push_back(luckstone);
	equips.push_back(strengstone);
	CLogicEquipment logicEquipMent;

	int ret = logicEquipMent.AddItems(m_nUid, equips, result["equipments"], true);

	if(ret)
	{
		error_log("Add_Equip_error uid=%u， ret=%u", m_nUid, ret);
		throw std::runtime_error("add_equipitems_failed");
	}

	//修改领取状态
	m_jsonData["a"][pos] = 1;
	Save();

	result["newAct"] = m_jsonData;

	return 0;
}

int EquipStrengthenUnit::CheckVersion(Json::Value & result)
{
	//先判断是否在活动时间之内
	CheckActivityOpen();

	//获取版本配置
	unsigned version = GetVersionCfg(CONFIG_EQUIP_STRENGTHEN_VER);

	if (m_jsonData["v"].asUInt() != version)
	{
		//版本号不同，需要重置活动
		ResetActivity(version);

		Save();
	}

	result["newAct"] = m_jsonData;

	return 0;
}

unsigned EquipStrengthenUnit::GetVersionCfg(const string& szVersion)
{
	unsigned nVersion = 0;

	if (! Config::GetUIntValue(nVersion, szVersion))
	{
		throw std::runtime_error("can't_get_version_cfg");
	}

	return nVersion;
}

int EquipStrengthenUnit::CheckActivityOpen()
{
	//判断活动是否开启
	unsigned begints = Config::GetIntValue(CONFIG_EQUIP_STRENGTHEN_BEGIN_TS);  //活动的开启时间
	unsigned endts = Config::GetIntValue(CONFIG_EQUIP_STRENGTHEN_END_TS);;

	unsigned now = Time::GetGlobalTime();
	if (now >= begints && now <= endts)  //在活动开启范围内
	{
		return 0;
	}

	throw runtime_error("activity_not_open");
}

int EquipStrengthenUnit::ResetActivity(unsigned version)
{
	//先修改版本号
	m_jsonData["v"] = version;

	for(unsigned i = 0; i < m_jsonData["a"].size(); ++i)
	{
		m_jsonData["a"][i] = 0;
	}

	return 0;
}

int EquipStrengthenUnit::GetRewardInfo(unsigned index, RewardInfo & rewardinfo)
{
	unsigned quota = 0, luck_id = 0, luck_num = 0, en_id = 0, en_num = 1, q_level = 0;

	switch(index)
	{
		case 1: quota = 10; luck_id = QLIMIT_LUCK_STONE_6_ID; luck_num = 30; q_level = 6;
				break;
		case 2: quota = 1000; luck_id = QLIMIT_LUCK_STONE_7_ID; luck_num = 90; q_level = 7;
				break;
		case 3: quota = 3500; luck_id = QLIMIT_LUCK_STONE_8_ID; luck_num = 350; q_level = 8;
				break;
		case 4: quota = 10000; luck_id = QLIMIT_LUCK_STONE_9_ID; luck_num = 1500; q_level = 9;
				break;
		default: break;
	}

	en_id = GET_EN_STONE_ID(q_level);

	rewardinfo.quota = quota;
	rewardinfo.luck_stone_id = luck_id;
	rewardinfo.luck_stone_num = luck_num;
	rewardinfo.strongthen_stone_id = en_id;
	rewardinfo.strongthen_stone_num = en_num;

	return 0;
}

void EquipStrengthenUnit::Save()
{
	CLogicSecinc logicSecinc;

	int ret = logicSecinc.SetOneSecinc(m_nUid, m_jsonData);

	if (ret !=  R_SUCCESS)
	{
		error_log("[Save] update secinc failed. uid=%u, id = %u, ret=%d", m_nUid, m_jsonData["id"].asUInt(), ret);
		throw std::runtime_error("Save_data_failed");
	}
}

HeQuActivityUnit::HeQuActivityUnit(unsigned uid):
	BaseCmdUnit(uid)
{

}

int HeQuActivityUnit::GetChargeReward(UserWrap& userWrap, unsigned index, Json::Value & result)
{
	//判断活动是否开启
	bool isopen = IsActivityOpen();

	if (!isopen)
	{
		throw std::runtime_error("activity_not_open");
	}

	//获取配置，包含了参数判断
	HeQuChargeItem chargeitem;
	int ret = DataXmlPtr()->GetChargeRewardItem(index, chargeitem);

	if (ret)
	{
		throw runtime_error("get_config_error");
	}

	Json::Value user_stat;
	userWrap.GetUserStats(user_stat);

	//判断档里是否数据齐全
	CheckUserstatComplete(user_stat);

	//判断是否已经领取
	int pos = index - 1;

	if (user_stat["hqchg"][pos].asUInt() > 0)
	{
		error_log("charge reward already been gotten. uid=%u,index=%u", m_nUid, index);
		throw runtime_error("reward_already_gotten");
	}

	//未领取，判断充值额度是否足够
	//检查到现在为止的充值数目
	unsigned begin_time = 0;
	unsigned now = Time::GetGlobalTime();

	Config::GetUIntValue(begin_time, CONFIG_HEQU_ACTIVITY_BEGIN_TS);
	unsigned cash_point = userWrap.GetRechargePoint(begin_time, now);

	//判断条件是否满足
	if (cash_point < chargeitem.cash)
	{
		error_log("charge not enough. uid=%u,index=%u,now=%u", m_nUid, index, cash_point);
		throw runtime_error("charge_not_enough");
	}

	//发放奖励
	AddGiftEquips(chargeitem.items, chargeitem.itemnum, "HeQu_Charge", result);

	//设置奖励领取状态
	user_stat["hqchg"][pos] = 1;
	userWrap.SetUserStats(user_stat);

	result["hqchg"] = user_stat["hqchg"];

	return 0;
}

int HeQuActivityUnit::GetVIPCelebrate(UserWrap& userWrap, unsigned vindex, unsigned sindex, Json::Value & result)
{
	//判断活动是否开启
	bool isopen = IsActivityOpen();

	if (!isopen)
	{
		throw std::runtime_error("activity_not_open");
	}

	//获取vip奖励配置，内部包含了参数判断
	HeQuVIPItem vipitem;

	int ret = DataXmlPtr()->GetVIPRewardItem(vindex, sindex, vipitem);

	if (ret)
	{
		throw runtime_error("get_config_error");
	}

	Json::Value user_stat;
	userWrap.GetUserStats(user_stat);

	//判断档里是否数据齐全
	CheckUserstatComplete(user_stat);

	//判断是否还有vip奖励待领取
	unsigned vip_level = userWrap.VipLevel();

	if (vip_level < vipitem.limit_vip)
	{
		error_log("vip level not enough to get this reward. uid=%u,need_vip=%u,vip=%u", m_nUid, vipitem.limit_vip, vip_level);
		throw runtime_error("vip_level_not_enough");
	}

	int already = user_stat["hqvip"][vindex - 1][sindex - 1].asUInt();
	const int viplevel_list[MAX_VIP_ITEMS] = {6, 7, 8, 9, 10};

	CLogicVipRebates logicVipRebates;
	vector<VipUser> uids;
	logicVipRebates.getVips(viplevel_list[vindex - 1], uids);

	if (already >= uids.size())
	{
		error_log("hequ vip reward already been gotten. uid=%u,already=%d,have=%u", m_nUid, already, uids.size());
		throw runtime_error("reward_already_gotten");
	}

	//发放奖励
	char reason[100] = {0};
	sprintf(reason, "HeQu_VIP%d", viplevel_list[vindex - 1]);

	AddGiftEquips(vipitem.items, vipitem.itemnum, reason, result);

	//设置奖励领取状态
	user_stat["hqvip"][vindex - 1][sindex - 1] = user_stat["hqvip"][vindex - 1][sindex - 1].asUInt() + 1;

	userWrap.SetUserStats(user_stat);

	result["hqvip"] = user_stat["hqvip"];

	return 0;
}

int HeQuActivityUnit::GetCombineZoneRecompense(UserWrap& userWrap, unsigned index, Json::Value & result)
{
	//判断活动是否开启
	bool isopen = IsActivityOpen();

	if (!isopen)
	{
		throw std::runtime_error("activity_not_open");
	}

	//获取配置，包含了参数判断
	HeQuRecompense recomitem;
	int ret = DataXmlPtr()->GetRecompenseRewardItem(index, recomitem);

	if (ret)
	{
		throw runtime_error("get_config_error");
	}

	Json::Value user_stat;
	userWrap.GetUserStats(user_stat);

	//判断档里是否数据齐全
	CheckUserstatComplete(user_stat);

	//判断是否已经领取
	int pos = index - 1;

	if (user_stat["hqbc"][pos].asUInt() > 0)
	{
		error_log("hequ buchang reward already been gotten. uid=%u,index=%u", m_nUid, index);
		throw runtime_error("reward_already_gotten");
	}

	int userlevel = userWrap.GetUserLevel();

	//判断条件是否满足
	if (userlevel < recomitem.minlevel || userlevel > recomitem.maxlevel)
	{
		error_log("userlevel not match level condition. uid=%u,index=%u,level=%d", m_nUid, index, userlevel);
		throw runtime_error("userlevel_not_match");
	}

	//发放奖励
	AddGiftEquips(recomitem.items, recomitem.itemnum, "HeQu_Buchang", result);

	//设置奖励领取状态
	for(int i = 0; i < MAX_RECOMPENSE_ITEMS; ++i)
	{
		if (pos == i)
		{
			user_stat["hqbc"][i] = 1;
		}
		else
		{
			user_stat["hqbc"][i] = 2;
		}
	}

	userWrap.SetUserStats(user_stat);

	result["hqbc"] = user_stat["hqbc"];

	return 0;
}

bool HeQuActivityUnit::CheckUserstatComplete(Json::Value & user_stat)
{
	//补偿
	if (!user_stat.isMember("hqbc") || !user_stat["hqbc"].isArray())
	{
		user_stat.removeMember("hqbc");
		Json::Value array = Json::arrayValue;
		user_stat["hqbc"] = array;

		for(int i = 0; i < MAX_RECOMPENSE_ITEMS; ++i)
		{
			user_stat["hqbc"][i] = 0;
		}
	}

	//充值
	if (!user_stat.isMember("hqchg") || !user_stat["hqchg"].isArray())
	{
		Json::Value array = Json::arrayValue;
		user_stat["hqchg"] = array;

		for(int i = 0; i < max_charge_index; ++i)
		{
			user_stat["hqchg"][i] = 0;
		}
	}

	//vip全服同庆奖励
	if (!user_stat.isMember("hqvip") || !user_stat["hqvip"].isArray())
	{
		user_stat.removeMember("hqvip");
		Json::Value array = Json::arrayValue;
		user_stat["hqvip"] = array;

		for(int i = 0; i < MAX_VIP_ITEMS; ++i)
		{
			Json::Value array = Json::arrayValue;

			for(int j = 0; j < MAX_VIP_SUBQUENT; ++j)
			{
				array[j] = 0;
			}

			user_stat["hqvip"][i] = array;
		}
	}

	return true;
}

bool HeQuActivityUnit::IsActivityOpen()
{
	//判断活动是否开启
	unsigned begints = Config::GetIntValue(CONFIG_HEQU_ACTIVITY_BEGIN_TS);  //活动的开启时间
	unsigned endts = Config::GetIntValue(CONFIG_HEQU_ACTIVITY_END_TS);;

	string type;
	Config::GetValue(type, CONFIG_ACTIVITY_GALLERY_TYPE);

	unsigned now = Time::GetGlobalTime();
	//判断类型，再判断时间
	if (now >= begints && now <= endts)  //在活动开启范围内
	{
		return true;
	}
	else
	{
		error_log("activity not open. uid=%u", m_nUid);
		return false;
	}

	return false;
}

AncientScrollUnit::AncientScrollUnit(const UserWrap& user):
		BaseCmdUnit(user.Id())
{

}

int AncientScrollUnit::InjectScroll(UserWrap& userWrap, const AncientParam & param, Json::Value & result)
{
	userWrap.GetUserTech(m_jsonData);

	//判断古卷的科技是否初始化
	CheckScrollInit();

	//判断当前的科技等级是否达到最大
	unsigned id = param.Id();
	//从科技中获取当前的科技等级
	unsigned level = m_jsonData["ancientScroll"][id - 1]["level"].asUInt();

	if (level >= MAX_SCROLL_LEVEL- 1)
	{
		error_log("item is max level. uid=%u", m_nUid);
		throw runtime_error("item_is_max_level");
	}

	//判断是否与最低等级相差10级
	int minLevel = GetMinLevel();

	if (m_jsonData["ancientScroll"][id - 1]["level"].asUInt() >= (minLevel + max_level_distance))
	{
		error_log("scroll level distance between min and current is more than [%u]. uid=%u,id=%u", max_level_distance, m_nUid, id);
		throw runtime_error("level_distance_too_high");
	}

	unsigned nextlevel = level + 1;

	ScrollItem scrollitem;
	DataXmlPtr()->GetAncientItem(id, nextlevel, scrollitem);

	unsigned equd = param.Ud();

	//扣除资源和相应的道具
	//判断资源是否满足
	Json::Value res;
	userWrap.GetResource(res);

	int r1 = 0, r2 = 0, r3 = 0, r4 = 0;
	r1 = scrollitem.res[0];
	r2 = scrollitem.res[1];
	r3 = scrollitem.res[2];
	r4 = scrollitem.res[3];

	if (res["r1"].asUInt() < r1 || res["r2"].asUInt() < r2 ||res["r3"].asUInt() < r3 ||res["r4"].asUInt() <r4)
	{
		error_log("resource not enough. uid=%u", m_nUid);
		throw runtime_error("resource_not_enough");
	}

	char reason[50] = {0};
	sprintf(reason, "AncientScroll_%u", id);

	//扣除道具
	CLogicEquipment logicEquipMent;
	const int SCROLL_UPGRADE_EQID = 2029;
	int ret = logicEquipMent.UseEquipment(m_nUid, SCROLL_UPGRADE_EQID, equd, scrollitem.needeq, reason);

	if (ret)
	{
		error_log("UseEquipment error. uid=%u,ud=%u,ret=%d", m_nUid, equd, ret);
		throw runtime_error("use_eqiup_error");
	}

	//扣除资源
	userWrap.ChangeResource(-r1, -r2, -r3, -r4, reason, result);

	//注资次数增加
	unsigned times = m_jsonData["ancientScroll"][id - 1]["times"].asUInt();
	times += 1;

	if (times >= scrollitem.zhuzi)
	{
		//达到注资次数，卷轴升级
		level = nextlevel;
		times = 0;
	}

	m_jsonData["ancientScroll"][id - 1]["times"]  = times;
	m_jsonData["ancientScroll"][id - 1]["level"]  = level;

	//更新卷轴科技
	userWrap.SetUserTech(m_jsonData);

	result["ancientScroll"] = m_jsonData["ancientScroll"];

	return 0;
}

int AncientScrollUnit::GetMinLevel()
{
	unsigned minLevel = m_jsonData["ancientScroll"][0u]["level"].asUInt();

	for(int i = 1; i < m_jsonData["ancientScroll"].size(); ++i)
	{
		unsigned level = m_jsonData["ancientScroll"][i]["level"].asUInt();

		if (level < minLevel)
		{
			minLevel = level;
		}
	}

	return minLevel;
}

int AncientScrollUnit::CheckScrollInit()
{
	if (!m_jsonData.isMember("ancientScroll"))
	{
		//未初始化
		Json::Value item(Json::arrayValue);

		for(int i = 0; i < ANCIENT_SCROLL_ITEMS; ++i)
		{
			Json::Value itemobj;

			itemobj["id"] = i+1;
			itemobj["level"] = 0;  //0级
			itemobj["times"] = 0;  //注资次数

			item[i] = itemobj;
		}

		m_jsonData["ancientScroll"] = item;
	}
	else if (m_jsonData["ancientScroll"].size() < ANCIENT_SCROLL_ITEMS)
	{
		//扩展古卷奇书的属性列表
		int old_size = m_jsonData["ancientScroll"].size();

		m_jsonData["ancientScroll"].resize(ANCIENT_SCROLL_ITEMS);

		for(int i = old_size; i < ANCIENT_SCROLL_ITEMS; ++i)
		{
			Json::Value itemobj;

			itemobj["id"] = i+1;
			itemobj["level"] = 0;  //0级
			itemobj["times"] = 0;  //注资次数

			m_jsonData["ancientScroll"][i] = itemobj;
		}
	}

	return 0;
}

CompoundShredUnit::CompoundShredUnit(const UserWrap& user):
		BaseCmdUnit(user.Id())
{

}

int CompoundShredUnit::ShredCompound(UserWrap& userWrap, const UnitUdCmdParams & param, Json::Value & result)
{
	unsigned equd = param.Ud();
	unsigned cost_count = param.ValueAsUInt("cost");

	//根据equd，获取装备信息
	CLogicEquipment logicEquipMent;
	Json::Value equipdata;

	logicEquipMent.Get(m_nUid, equd, equipdata);

	unsigned count = equipdata["count"].asUInt();
	unsigned eqid = equipdata["id"].asUInt();

	//根据装备id加载碎片的配置
	const CompoundShredConfig::ShredItem & shreditem = CompoundConfigWrap().GetShredItemCfg(eqid);

	int addcount = cost_count/shreditem.count();
	int costcount = addcount * shreditem.count();

	if (count < costcount)
	{
		error_log("shred not enough. uid=%u,have=%u,need=%u", m_nUid, count, costcount);
		throw runtime_error("shred_not_enough");
	}

	//扣除碎片
	logicEquipMent.UseEquipment(m_nUid, eqid, equd, costcount, "ShredCompound");

	//合成新道具或新英雄
	if (shreditem.ishero())
	{
		//合成英雄
		vector<string> heros;
		vector<string> reasons;

		for(int i = 0; i < addcount; ++i)
		{
			char heroid[50] = {0};
			sprintf(heroid, "H%u", shreditem.compoundid());

			heros.push_back(heroid);
			reasons.push_back("ShredCompound");
		}

		CLogicHero logichero;

		if (0 != logichero.AddHeros(m_nUid, heros, reasons, result["hero"]))
		{
			error_log("add heros error. uid=%u", m_nUid);
			throw std::runtime_error("add_hero_error");
		}
	}
	else
	{
		//合成道具
		unsigned comeqid = shreditem.compoundid();

		vector<ItemAdd> items;
		ItemAdd item(comeqid, addcount, "ShredCompound");
		items.push_back(item);

		AddEquips(items, result);
	}

	return 0;
}

ScrollActivityUnit::ScrollActivityUnit(unsigned uid):
		BaseActivityUnit(uid, CONFIG_SCROLL_ACTIVITY)
{
	CLogicSecinc logicSecinc;
	int ret = logicSecinc.GetSecinc(m_nUid, NAT_SCROLL_SPECIAL, m_jsonData);

	if (R_ERR_NO_DATA == ret)
	{
		//初始化古卷专项活动数据，与重置操作相同
		Reset();
	}
	else if (ret)
	{
		error_log("get newact error.uid=%u id=%d", uid, NAT_SCROLL_SPECIAL);
		throw std::runtime_error("get_new_active_data_error");
	}
}

int ScrollActivityUnit::GainMaterial(unsigned type, unsigned count)
{
	//参数判断
	if (type < 1 || type > max_material_type)
	{
		error_log("param error. type=%u", type);
		throw runtime_error("param_error");
	}

	//版本号检查
	CheckVersion();

	m_jsonData["d"][type - 1] = m_jsonData["d"][type - 1].asUInt() + count;

	Save();

	return 0;
}

int ScrollActivityUnit::LoadScrollActivity(Json::Value & result)
{
	CheckVersion();

	unsigned now = Time::GetGlobalTime();
	ScrollActivityConfigWrap scrollcfgwrap;

	//检查是否跨天
	if (CTime::GetDayInterval(m_jsonData["a"].asUInt(), now))
	{
		//跨天，则事件id取第一个
		int days = GetDistanceDays();

		m_jsonData["b"] = scrollcfgwrap.GetInitAffairId(days);  //当前事件的新id
		m_jsonData["a"] = now;

		Save(); //先保存，以免后面抛异常
	}

	result["NewAct"] = m_jsonData;

	return 0;
}

int ScrollActivityUnit::CompleteAffair(unsigned type, Json::Value & result)
{
	CheckVersion();

	//判断参数是否合法
	if (complete_type_props != type && complete_type_cash != type)
	{
		error_log("type param error. uid=%u,type=%u", m_nUid, type);
		throw std::runtime_error("param_error");
	}

	unsigned now = Time::GetGlobalTime();
	ScrollActivityConfigWrap scrollcfgwrap;

	//检查是否跨天
	if (CTime::GetDayInterval(m_jsonData["a"].asUInt(), now))
	{
		//跨天，则事件id取第一个
		int days = GetDistanceDays();

		m_jsonData["b"] = scrollcfgwrap.GetInitAffairId(days);  //当前事件的新id
		m_jsonData["a"] = now;

		Save(); //先保存，以免后面抛异常
	}

	unsigned affair_id = m_jsonData["b"].asUInt();

	if (0 == affair_id)
	{
		error_log("wrong affair id. uid=%u,id=%u", m_nUid, affair_id);
		throw runtime_error("no_activity_affair");
	}

	//根据事件id,获取事件配置
	const ConfigScrollActivity::Affair & affaircfg = scrollcfgwrap.GetAffairCfgById(affair_id);
	unsigned active_value = 0;

	if (complete_type_props == type)
	{
		//扣除材料
		unsigned type = affaircfg.props().type();
		unsigned count = affaircfg.props().count();
		active_value =  affaircfg.props().active_value();

		if (m_jsonData["d"][type - 1].asUInt() < count)
		{
			error_log("material not enough. uid=%u,id=%u,mtype=%u", m_nUid, affair_id, type);
			throw runtime_error("material_not_enough");
		}

		m_jsonData["d"][type - 1] = m_jsonData["d"][type - 1].asUInt() - count;
	}
	else
	{
		unsigned cash = affaircfg.cash().count();
		active_value =  affaircfg.cash().active_value();

		//扣钻石
		UserWrap userwrap(m_nUid, true);
		userwrap.CostAsset(cash, 0, "ScrollActivity_Affair", result);
	}

	//加活跃值
	m_jsonData["c"] = m_jsonData["c"].asUInt() + active_value;

	//发奖励
	if (complete_type_props == type)
	{
		ProvideCommonReward(affaircfg.props().reward(), "ScrollActivity_Affair", result);
	}
	else
	{
		ProvideCommonReward(affaircfg.cash().reward(), "ScrollActivity_Affair", result);
	}

	//刷新下一个活动事件id
	m_jsonData["b"] = scrollcfgwrap.GetNextAffair(affair_id);

	Save();

	result["NewAct"] = m_jsonData;

	return 0;
}

int ScrollActivityUnit::GetActiveReward(unsigned index, Json::Value & result)
{
	CheckVersion();

	ScrollActivityConfigWrap scrollcfgwrap;

	const ConfigScrollActivity::ActiveValueReward & activevaluecfg = scrollcfgwrap.GetActiveRewardCfg(index);

	//判断活跃值是否满足要求
	if (m_jsonData["c"].asUInt() < activevaluecfg.value())
	{
		error_log("active value is not enough. uid=%u,index=%u", m_nUid, index);
		throw runtime_error("active_value_not_enough");
	}

	//判断奖励是否领取
	int pos = index - 1;
	bool ishave = Has_DemoReform(m_jsonData["e"].asUInt(), pos);

	if (ishave)
	{
		error_log("active reward already been gotten. uid=%u,index=%u", m_nUid, index);
		throw runtime_error("reward_already_gotten");
	}

	//发奖励
	ProvideCommonReward(activevaluecfg.reward(), "ScrollActivity_Active", result);

	const ConfigScrollActivity::ScrollActivity & scrollactcfg = scrollcfgwrap.GetScrollCfg();

	if (scrollactcfg.active_value_reward_size() == index)
	{
		//领取最后一个大奖，判断是否有额外奖励需要发送
		int diff_day = GetDistanceDays();

		if (diff_day < max_activity_days)
		{
			//获取额外奖励的配置
			const ConfigScrollActivity::ExtraReward &  extracfg = scrollcfgwrap.GetExtraRewardCfg(diff_day);
			ProvideCommonReward(extracfg.reward(), "ScrollActivity_Extra", result["extra"]);
		}
	}

	//设置领取标志位
	unsigned activebits = m_jsonData["e"].asUInt();
	Set_DemoReform(activebits, pos);

	m_jsonData["e"] = activebits;

	Save();

	result["NewAct"] = m_jsonData;

	return 0;
}

int ScrollActivityUnit::GetDistanceDays()
{
	//天数
	unsigned starts = GetBeginTs();

	unsigned now = Time::GetGlobalTime();

	int diff_day = CTime::GetDayInterval(starts, now);

	int day = diff_day + 1;  //包含活动开始当天

	return day;
}

int ScrollActivityUnit::CheckVersion()
{
	//判断版本号是否发生改变
	unsigned oldversion = m_jsonData["v"].asUInt();

	bool isnew = IsNewVersion(oldversion);

	if (isnew)
	{
		Reset();
	}

	return 0;
}

int ScrollActivityUnit::Reset()
{
	m_jsonData["a"] = Time::GetGlobalTime();  //事件刷新的时间

	int days = GetDistanceDays();

	m_jsonData["b"] = ScrollActivityConfigWrap().GetInitAffairId(days);  //当前事件的id
	m_jsonData["c"] = 0;  //活力值
	m_jsonData["e"] = 0;  //活力值奖励领取状态，位标志
	m_jsonData["v"] = GetVersion();  //版本号
	m_jsonData["id"] = NAT_SCROLL_SPECIAL;  //id

	m_jsonData["d"] = Json::arrayValue;  //三种材料的数量

	for(int i = 0; i < max_material_type; ++i)
	{
		m_jsonData["d"][i] = 0;   //材料数量清0
	}

	Save();

	return 0;
}

KingTreasureActivityUnit::KingTreasureActivityUnit(unsigned uid):
		BaseActivityUnit(uid, CONFIG_KING_TREASURE)
{
	//先解决共享内存数据的版本号问题
	static CDataTreasureDepot* pdata = CDataTreasureDepot::GetCDataTreasureDepot();

	if (NULL == pdata)
	{
		throw std::runtime_error("get_kingtreasure_data_error");
	}

	unsigned version = GetVersion();
	pdata->CheckVersion(version);   //检查共享内存中的版本号

	CLogicSecinc logicSecinc;
	int ret = logicSecinc.GetSecinc(m_nUid, NAT_KING_TREASURE, m_jsonData);

	if (R_ERR_NO_DATA == ret)
	{
		//初始化天帝宝库活动数据，与重置操作相同
		Reset();
	}
	else if (ret)
	{
		error_log("get newact error.uid=%u id=%d", uid, NAT_KING_TREASURE);
		throw std::runtime_error("get_new_active_data_error");
	}
}

int KingTreasureActivityUnit::OpenTreasureBox(unsigned equd, Json::Value & result)
{
	CheckVersion();

	//判断此时的状态是否可以开箱子
	if (m_jsonData["b"].asUInt())
	{
		error_log("treasure box already opened. uid=%u", m_nUid);
		throw runtime_error("box_already_open");
	}

	const ConfigKingTreasure::KingTreasure &  treasurecfg = KingTreasureConfigWrap().GetTreasureCfg();

	int cost = treasurecfg.cost();

	if (0 == cost)
	{
		error_log("cost config error. uid=%u", m_nUid);
		throw runtime_error("config_error");
	}

	//扣除道具
	CLogicEquipment logicEquipMent;
	int ret = logicEquipMent.UseEquipment(m_nUid, king_token_eqid, equd, cost, "KingTreasure_Open");

	if (ret)
	{
		error_log("use equipment error. uid=%u,equd=%u", m_nUid, equd);
		throw runtime_error("param_error");
	}

	//随机从所有的宝箱中根据权重选出宝箱
	vector<unsigned> rates;
	map<unsigned, unsigned> mpos;
	int num = 0;
	static CDataTreasureDepot* pdata = CDataTreasureDepot::GetCDataTreasureDepot();

	for(int i = 0; i < treasurecfg.king_treasures_size(); ++i)
	{
		//排除有次数限制，并且次数已经达到的箱子
		if (treasurecfg.king_treasures(i).limit() > 0)
		{
			//判断是否达到次数
			unsigned used = pdata->GetUsedTimes(treasurecfg.king_treasures(i).id());

			if (used >= treasurecfg.king_treasures(i).limit())
			{
				//次数已达到限制上限，排除该选项
				continue;
			}
		}

		unsigned rate = treasurecfg.king_treasures(i).weight();
		rates.push_back(rate);

		mpos[num++] = i;
	}

	int pos = 0;
	TurnVecLuckTable(rates, rates.size(), pos);

	unsigned tpos = mpos[pos];

	//往newact中更新
	m_jsonData["a"] = treasurecfg.king_treasures(tpos).id();  //箱子id
	m_jsonData["b"] = 1;

	Save();

	//判断是否需要记录该物品的抽取次数
	if (treasurecfg.king_treasures(tpos).limit() > 0)
	{
		//增加抽取次数
		pdata->AddUsedTimes(treasurecfg.king_treasures(tpos).id(), 1);
	}

	result["NewAct"] = m_jsonData;

	return 0;
}

int KingTreasureActivityUnit::ReceiveReward(Json::Value & result)
{
	CheckVersion();

	//如何避免重复领取呢？根据箱子状态
	if (0 == m_jsonData["b"].asUInt())
	{
		error_log("treasure box not opened. uid=%u", m_nUid);
		throw runtime_error("box_not_open");
	}

	unsigned id = m_jsonData["a"].asUInt();

	//根据箱子的id，去获取对应的奖励
	const ConfigKingTreasure::TreasureBox & boxcfg = KingTreasureConfigWrap().GetTreasureBoxById(id);

	//发奖励
	ProvideCommonReward(boxcfg.reward(), "KingTreasure_Receive", result);
	m_jsonData["b"] = 0;   //修改箱子的状态

	Save();

	result["NewAct"] = m_jsonData;

	return 0;
}

int KingTreasureActivityUnit::RecycleReward(Json::Value & result)
{
	CheckVersion();

	//如何避免重复领取呢？根据箱子状态
	if (0 == m_jsonData["b"].asUInt())
	{
		error_log("treasure box not opened. uid=%u", m_nUid);
		throw runtime_error("box_not_open");
	}

	unsigned id = m_jsonData["a"].asUInt();

	//根据箱子的id，去获取对应的奖励
	const ConfigKingTreasure::TreasureBox & boxcfg = KingTreasureConfigWrap().GetTreasureBoxById(id);
	int count = boxcfg.collect();

	AddEquips(king_token_eqid, count, "KingTreasure_Recycle", result);

	m_jsonData["b"] = 0;   //修改箱子的状态

	Save();

	result["NewAct"] = m_jsonData;

	return 0;
}

int KingTreasureActivityUnit::CheckVersion()
{
	//判断版本号是否发生改变
	unsigned oldversion = m_jsonData["v"].asUInt();

	bool isnew = IsNewVersion(oldversion);

	if (isnew)
	{
		Reset();
	}

	return 0;
}

int KingTreasureActivityUnit::Reset()
{
	m_jsonData["a"] = 0;  //箱子id
	m_jsonData["b"] = 0;  //宝箱状态.0-关闭，1-开启

	m_jsonData["v"] = GetVersion();  //版本号

	m_jsonData["id"] = NAT_KING_TREASURE;  //id

	Save();

	return 0;
}

ScrollFeedbackActivityUnit::ScrollFeedbackActivityUnit(unsigned uid):
		BaseActivityUnit(uid, CONFIG_SCROLL_FEEDBACK)
{
	CLogicSecinc logicSecinc;
	int ret = logicSecinc.GetSecinc(m_nUid, NAT_SCROLL_FEEDBACK, m_jsonData);

	if (R_ERR_NO_DATA == ret)
	{
		//初始化古卷回馈活动数据，与重置操作相同
		ResetAct();
	}
	else if (ret)
	{
		error_log("get newact error.uid=%u id=%d", uid, NAT_SCROLL_FEEDBACK);
		throw std::runtime_error("get_new_active_data_error");
	}
}

int ScrollFeedbackActivityUnit::ReceiveFeedback(unsigned index, UserWrap& userWrap, Json::Value & result)
{
	//判断参数
	if (index < 1 || index > item_max_index)
	{
		error_log("param error. uid=%u,index=%u", m_nUid,index);
		throw runtime_error("param error");
	}

	//判断版本是否发生变化
	CheckActVersion();

	//获取今日的充值金额
	//判断积分是否足够
	unsigned nowts = Time::GetGlobalTime();
	unsigned charge = GetChargeByTime(userWrap, nowts);

	//判断充值金额是否满足配置
	//先获取配置
	const ConfigScrollFeedback::FeedBackItem & itemcfg = ScrollFeedbackConfigWrap().GetFeedbackByIndex(index);

	if (charge < itemcfg.diamond())
	{
		error_log("charge not enough. uid=%u,index=%u,charge=%u", m_nUid, index, charge);
		throw runtime_error("charge_not_enough");
	}

	//判断是否已经领取过该位置的奖励
	if (m_jsonData["a"][index - 1].asUInt())
	{
		error_log("reward already been received. uid=%u,index=%u", m_nUid, index);
		throw runtime_error("reward_aleardy_received");
	}

	//发奖励
	ProvideCommonReward(itemcfg.reward(), "Scroll_Feedback", result);

	m_jsonData["a"][index - 1] = 1;   //设置奖励领取状态

	Save();

	result["NewAct"] = m_jsonData;

	return 0;
}

int ScrollFeedbackActivityUnit::ResetAct()
{
	if (!m_jsonData.isMember("a"))
	{
		Json::Value array(Json::arrayValue);

		m_jsonData["a"] = array;
	}

	for(int i = 0; i < item_max_index; ++i)
	{
		m_jsonData["a"][i] = 0;  //重置奖励领取状态
	}

	m_jsonData["ts"] = Time::GetGlobalTime();  //重置的时间
	m_jsonData["v"] = GetVersion();  //版本号

	m_jsonData["id"] = NAT_SCROLL_FEEDBACK;  //id

	Save();

	return 0;
}

SevenDaysAwakenActivityUnit::SevenDaysAwakenActivityUnit(unsigned uid):
		BaseActivityUnit(uid, CONFIG_SEVENDAYS_AWAKEN)
{
	CLogicSecinc logicSecinc;
	int ret = logicSecinc.GetSecinc(m_nUid, NAT_SEVENDAY_AWAKEN, m_jsonData);
	need_save = false;

	if (R_ERR_NO_DATA == ret)
	{
		//初始化七日觉醒活动数据，与重置操作相同
		Reset();
	}
	else if (ret)
	{
		error_log("get newact error.uid=%u id=%d", uid, NAT_SEVENDAY_AWAKEN);
		throw std::runtime_error("get_new_active_data_error");
	}
}

int SevenDaysAwakenActivityUnit::ReceiveGift(unsigned type, UserWrap& userWrap, Json::Value & result)
{
	if (type_of_daily != type && type_of_seven != type)
	{
		error_log("param error. uid=%u,type=%u", m_nUid, type);
		throw runtime_error("param_error");
	}

	//判断版本号是否发生改变
	unsigned oldversion = m_jsonData["v"].asUInt();

	bool isnew = IsNewVersion(oldversion);

	if (isnew)
	{
		Reset();
	}

	//判断是否跨天
	unsigned now = Time::GetGlobalTime();
	int diff_day = CTime::GetDayInterval(m_jsonData["ts"].asUInt(), now);

	if (diff_day)
	{
		//跨天，重置每日礼包的领取状态
		m_jsonData["b"] = 0;   //每日满300钻的礼包领取状态
		m_jsonData["ts"] = now;  //领取奖励时间

		need_save = true;
	}

	Json::Value user_flag;

	userWrap.GetUserFlag(user_flag);

	//优先处理七日礼包
	if (type_of_seven == type)
	{
		//发放满足七日条件的礼包-内置条件判断
		ProvideSevenDaysGift(user_flag, result);
	}
	else
	{
		//发放每日充值条件的礼包-内置条件判断
		ProvideDailyGift(user_flag, result);
	}

	Save();

	result["NewAct"] = m_jsonData;

	return 0;
}

int SevenDaysAwakenActivityUnit::ProvideDailyGift(Json::Value & user_flag, Json::Value & result)
{
	//判断当日充值是否满足要求
	unsigned charge = 0;
	unsigned now = Time::GetGlobalTime();

	if (0 == CTime::GetDayInterval(user_flag["dchg"][0u].asUInt(), now) )
	{
		charge = user_flag["dchg"][1u].asUInt();
	}

	if (charge < daily__charge_cash)
	{
		error_log("charge not enough. uid=%u,charge=%u", m_nUid, charge);
		throw runtime_error("charge_not_enough");
	}

	//是否已经领取当天的礼包奖励
	if (m_jsonData["b"].asUInt() > 0)
	{
		error_log("reward already been received. uid=%u", m_nUid);
		throw runtime_error("reward_aleardy_received");
	}

	//发放奖励
	CLogicEquipment logicEquipment;
	int ret = logicEquipment.AddOneItem(m_nUid, daily_gift_eqid, 1, "SevenDayAwaken_Daily", result["equipments"], true);

	if (ret)
	{
		throw std::runtime_error("Add_equip_item_failed");
	}

	m_jsonData["b"] = 1;   //设置每日满300钻的礼包领取状态

	return 0;
}

int SevenDaysAwakenActivityUnit::ProvideSevenDaysGift(Json::Value & user_flag, Json::Value & result)
{
	//判断是否满足7日洗髓真丹的领取条件
	unsigned size = user_flag["chgs"].size();

	unsigned nStartTime = GetBeginTs();
	unsigned nEndTime = GetEndTs();
	int days = 0;

	for (unsigned i = 0; i < size; ++i)
	{
		unsigned ts  = user_flag["chgs"][i][0u].asUInt();

		if(ts >= nStartTime && ts <= nEndTime)
		{
			unsigned charge = user_flag["chgs"][i][1u].asUInt();

			if (charge >= daily__charge_cash)
			{
				++days;
			}
		}
	}

	if (days < special_command_days)
	{
		error_log("charge days not enough. uid=%u,days=%d", m_nUid, days);
		throw runtime_error("charge_days_not_enough");
	}

	if (m_jsonData["a"].asUInt() > 0)
	{
		error_log("reward already been received. uid=%u", m_nUid);
		throw runtime_error("reward_aleardy_received");
	}

	//发放奖励
	CLogicEquipment logicEquipment;
	int ret = logicEquipment.AddOneItem(m_nUid, HERO_POWER_2_UP_AWAKEN, 1, "SevenDayAwaken_Special", result["equipments"], true);

	if (ret)
	{
		throw std::runtime_error("Add_equip_item_failed");
	}

	m_jsonData["a"] = 1;

	return 0;
}

int SevenDaysAwakenActivityUnit::Reset()
{
	m_jsonData["a"] = 0;   //7日礼包的洗髓真丹的领取状态
	m_jsonData["b"] = 0;   //每日满300钻的礼包领取状态

	m_jsonData["ts"] = Time::GetGlobalTime();  //跨天刷新时间
	m_jsonData["v"] = GetVersion();  //版本号

	m_jsonData["id"] = NAT_SEVENDAY_AWAKEN;  //id

	need_save = true;

	return 0;
}

TokenUpgradeActivityUnit::TokenUpgradeActivityUnit(const UserWrap& user):
		BaseActivityUnit(user.Id(), CONFIG_TOKEN_UPGRADE)
{
	CLogicSecinc logicSecinc;
	int ret = logicSecinc.GetSecinc(m_nUid, NAT_TOKEN_UPGRADE, m_jsonData);
	need_save = false;

	if (R_ERR_NO_DATA == ret)
	{
		//初始化令牌提升活动数据，与重置操作相同
		Reset();
	}
	else if (ret)
	{
		error_log("get newact error.uid=%u id=%d", m_nUid, NAT_TOKEN_UPGRADE);
		throw std::runtime_error("get_new_active_data_error");
	}
}

int TokenUpgradeActivityUnit::ReceivePointGift(UserWrap& userWrap, const BaseCmdParams & param, Json::Value & result)
{
	unsigned index = param.ValueAsUInt("index");

	if (index < 1 || index > item_max_index)
	{
		error_log("param error. uid=%u,index=%u", m_nUid, index);
	}

	//判断版本是否发生变化
	CheckVersion();

	//获取活动期间内的充值数目
	unsigned begints = GetBeginTs();
	unsigned nowts = Time::GetGlobalTime();

	unsigned charge = userWrap.GetRechargePoint(begints, nowts);

	//根据index，获取配置
	const ConfigTokenUpgrade::ChargeReceive & receivecfg = TokenUpgradeConfigWrap().GetReceiveConfigByIndex(index);

	if (charge < receivecfg.point())
	{
		error_log("charge not enough. uid=%u,index=%u,charge=%u", m_nUid, index, charge);
		throw runtime_error("charge_not_enough");
	}

	//是否已经领取该位置处的奖励
	if (m_jsonData["a"][index - 1].asUInt() > 0)
	{
		error_log("reward already been received. uid=%u,index=%u", m_nUid, index);
		throw runtime_error("reward_aleardy_received");
	}

	//发放奖励
	ProvideCommonReward(receivecfg.reward(), "TokenUpgrade_Point", result);

	m_jsonData["a"][index - 1] = 1;   //设置奖励领取状态
	Save();

	result["NewAct"] = m_jsonData;

	return 0;
}

int TokenUpgradeActivityUnit::PointLottery(UserWrap& userWrap, const BaseCmdParams & param, Json::Value & result)
{
	//判断版本是否发生变化
	CheckVersion();

	//获取活动期间内的充值数目
	unsigned begints = GetBeginTs();
	unsigned nowts = Time::GetGlobalTime();

	unsigned charge = userWrap.GetRechargePoint(begints, nowts);

	//获取抽奖配置
	const ConfigTokenUpgrade::ChargeLottery &  lotterycfg = TokenUpgradeConfigWrap().GetLotteryConfig();

	//判断抽奖次数是否达到上限
	if (m_jsonData["b"].asUInt() >= lotterycfg.limit())
	{
		error_log("charge times not enough. uid=%u", m_nUid);
		throw runtime_error("times_not_enough");
	}

	//判断积分是否足够
	unsigned used_point = m_jsonData["b"].asUInt() * lotterycfg.cost();

	if (charge < (used_point + lotterycfg.cost()))
	{
		error_log("charge not enough. uid=%u,charge=%u", m_nUid, charge);
		throw runtime_error("charge_not_enough");
	}

	vector<unsigned> rates;

	for(int i = 0; i < lotterycfg.turntable_size(); ++i)
	{
		unsigned weight = lotterycfg.turntable(i).weight();

		rates.push_back(weight);
	}

	//抽奖
	int pos = 0;
	TurnVecLuckTable(rates, rates.size(), pos);

	//发放物品
	ProvideCommonReward(lotterycfg.turntable(pos).reward(), "TokenUpgrade_Lottary", result);

	m_jsonData["b"] = m_jsonData["b"].asUInt() + 1;  //次数加1
	Save();

	result["NewAct"] = m_jsonData;
	result["pos"] = pos;

	return 0;
}

int TokenUpgradeActivityUnit::CheckVersion()
{
	//判断版本号是否发生改变
	unsigned oldversion = m_jsonData["v"].asUInt();

	bool isnew = IsNewVersion(oldversion);

	if (isnew)
	{
		Reset();
	}

	return 0;
}

int TokenUpgradeActivityUnit::Reset()
{
	if (!m_jsonData.isMember("a"))
	{
		Json::Value array(Json::arrayValue);

		m_jsonData["a"] = array;
	}

	for(int i = 0; i < item_max_index; ++i)
	{
		m_jsonData["a"][i] = 0;  //重置奖励领取状态
	}

	m_jsonData["b"] = 0;   //已抽奖次数

	m_jsonData["v"] = GetVersion();  //版本号

	m_jsonData["id"] = NAT_TOKEN_UPGRADE;  //id

	need_save = true;

	return 0;
}

BuildSuitActivityUnit::BuildSuitActivityUnit(const UserWrap& user):
		BaseActivityUnit(user.Id(), CONFIG_BUILD_SUIT)
{
	CLogicSecinc logicSecinc;
	int ret = logicSecinc.GetSecinc(m_nUid, NAT_BUILD_SUIT, m_jsonData);
	need_save = false;

	if (R_ERR_NO_DATA == ret)
	{
		//初始化祝福积分活动
		Reset();
	}
	else if (ret)
	{
		error_log("get newact error.uid=%u id=%d", m_nUid, NAT_BUILD_SUIT);
		throw std::runtime_error("get_new_active_data_error");
	}
}

int BuildSuitActivityUnit::ReceiveChargeGift(UserWrap& userWrap, const UnitIndexCmdParams & param, Json::Value & result)
{
	unsigned index = param.Index();

	if (index < 1 || index > item_max_index)
	{
		error_log("param error. uid=%u,index=%u", m_nUid, index);
		throw runtime_error("param_error");
	}

	//判断版本是否发生变化
	CheckVersion();

	//获取活动期间内的充值数目
	unsigned begints = GetBeginTs();
	unsigned nowts = Time::GetGlobalTime();

	unsigned charge = userWrap.GetRechargePoint(begints, nowts);

	//根据index，获取配置
	const ConfigActivity::BuildSuitItem & itemcfg = ActivityConfigWrap().GetBuildSuitConfigByIndex(index);

	if (charge < itemcfg.diamond())
	{
		error_log("charge not enough. uid=%u,index=%u,charge=%u", m_nUid, index, charge);
		throw runtime_error("charge_not_enough");
	}

	//是否已经领取该位置处的奖励
	if (m_jsonData["a"][index - 1].asUInt() > 0)
	{
		error_log("reward already been received. uid=%u,index=%u", m_nUid, index);
		throw runtime_error("reward_aleardy_received");
	}

	//发放奖励
	ProvideCommonReward(itemcfg.reward(), "BuildSuit_Charge", result);

	m_jsonData["a"][index - 1] = 1;   //设置奖励领取状态
	Save();

	result["NewAct"] = m_jsonData;

	return 0;
}

int BuildSuitActivityUnit::CheckVersion()
{
	//判断版本号是否发生改变
	unsigned oldversion = m_jsonData["v"].asUInt();

	bool isnew = IsNewVersion(oldversion);

	if (isnew)
	{
		Reset();
	}

	return 0;
}

int BuildSuitActivityUnit::Reset()
{
	if (!m_jsonData.isMember("a"))
	{
		Json::Value array(Json::arrayValue);

		m_jsonData["a"] = array;
	}

	for(int i = 0; i < item_max_index; ++i)
	{
		m_jsonData["a"][i] = 0;  //重置奖励领取状态
	}

	m_jsonData["v"] = GetVersion();  //版本号
	m_jsonData["id"] = NAT_BUILD_SUIT;  //id
	need_save = true;

	return 0;
}


BlessPointActivityUnit::BlessPointActivityUnit(const UserWrap& user):
		BaseActivityUnit(user.Id(), CONFIG_BLESS_POINT)
{
	CLogicSecinc logicSecinc;
	int ret = logicSecinc.GetSecinc(m_nUid, NAT_BLESS_POINT, m_jsonData);
	need_save = false;

	if (R_ERR_NO_DATA == ret)
	{
		//初始化祝福积分活动数据，与重置操作相同
		ResetAct();
	}
	else if (ret)
	{
		error_log("get newact error.uid=%u id=%d", m_nUid, NAT_BLESS_POINT);
		throw std::runtime_error("get_new_active_data_error");
	}
}

int BlessPointActivityUnit::BlessExchange(UserWrap& userWrap, const BlessParam & param, Json::Value & result)
{
	//判断版本是否发生变化
	CheckActVersion();

	unsigned heroud = param.Ud();
	unsigned id = param.Id();

	//先根据id，获取兑换的条件
	const ConfigActivity::ExchangeItem & exchangecfg = ActivityConfigWrap().GetExchangeConfigById(id);

	//获取等级和数量的条件
	unsigned cond_num = exchangecfg.condition(0u);
	unsigned cond_level = exchangecfg.condition(1u);

	if (0 != cond_num || 0 != cond_level)
	{
		//判断英雄身上的装备条件
		bool isok = CheckHeroEquips(heroud, cond_num, cond_level);

		if (!isok)
		{
			throw runtime_error("condition_not_match");
		}
	}

	//判断积分是否满足当前的兑换需求
	int pos = id - 1;
	int cost = exchangecfg.first() + m_jsonData["a"][pos].asUInt() * exchangecfg.accumulate();

	//获取活动期间内的充值数目
	unsigned begints = GetBeginTs();
	unsigned nowts = Time::GetGlobalTime();

	unsigned charge = userWrap.GetRechargePoint(begints, nowts);

	if (charge < (cost + m_jsonData["b"].asUInt()))
	{
		error_log("charge not enough. uid=%u, charge=%u", m_nUid, charge);
		throw runtime_error("charge_not_enough");
	}

	//发放奖励
	ProvideCommonReward(exchangecfg.reward(), "BlessPoint_Exchange", result);

	m_jsonData["a"][pos] = m_jsonData["a"][pos].asUInt() + 1;   //增加兑换次数
	m_jsonData["b"] = m_jsonData["b"].asUInt() + cost;  //增加消耗的积分

	Save();

	result["NewAct"] = m_jsonData;

	return 0;
}

bool BlessPointActivityUnit::CheckHeroEquips(unsigned heroud, unsigned cond_num, unsigned cond_level)
{
	CLogicHero logichero;

	Json::Value herodata;

	int ret = logichero.Get(m_nUid, heroud, herodata);

	if (ret)
	{
		error_log("get hero data error. uid=%u,heroud=%u", m_nUid, heroud);
		throw runtime_error("get_herodata_error");
	}

	char key[10] = {0};
	vector<unsigned> equips;

	for(int i = 1; i <= 10; ++i)
	{
		sprintf(key, "e%d", i);

		if (!herodata["heq"].isMember(key))
		{
			break;
		}

		equips.push_back(herodata["heq"][key].asUInt());
	}

	unsigned num = 0;

	if (equips.size() >= cond_num)
	{
		//数量有要求，至少装备的数量要满足条件
		CLogicEquipment logicequip;

		for(int i = 0; i < equips.size(); ++i)
		{
			//获取装备数据
			Json::Value equipdata;

			ret = logicequip.Get(m_nUid, equips[i], equipdata);

			if (ret)
			{
				continue;
			}

			if (!equipdata.isMember("bls"))
			{
				continue;
			}

			if (equipdata["bls"].asUInt() >= cond_level)
			{
				++num;
			}
		}

		if (num >= cond_num)
		{
			return true;
		}
	}

	error_log("match level equip not enough. uid=%u,heroud=%u, num=%u", m_nUid, heroud, num);

	return false;
}

int BlessPointActivityUnit::ResetAct()
{
	if (!m_jsonData.isMember("a"))
	{
		Json::Value array(Json::arrayValue);

		m_jsonData["a"] = array;
	}

	for(int i = 0; i < item_max_index; ++i)
	{
		m_jsonData["a"][i] = 0;  //重置兑换次数
	}

	m_jsonData["b"] = 0; //已使用积分
	m_jsonData["v"] = GetVersion();  //版本号
	m_jsonData["id"] = NAT_BLESS_POINT;  //id

	need_save = true;

	return 0;
}

DoubleWelfareActivityUnit::DoubleWelfareActivityUnit(const UserWrap& user):
		BaseActivityUnit(user.Id(), CONFIG_DOUBLE_WELFARE)
{
	CLogicSecinc logicSecinc;
	int ret = logicSecinc.GetSecinc(m_nUid, NAT_DOUBLE_WELFARE, m_jsonData);

	need_save = false;

	if (R_ERR_NO_DATA == ret)
	{
		//初始化双倍福利活动数据，与重置操作相同
		ResetAct();
	}
	else if (ret)
	{
		error_log("get newact error.uid=%u id=%d", m_nUid, NAT_DOUBLE_WELFARE);
		throw std::runtime_error("get_new_active_data_error");
	}
}

int DoubleWelfareActivityUnit::GetExtraReward(UserWrap& userWrap, const UnitIndexCmdParams & param, Json::Value & result)
{
	unsigned index = param.Index();

	if (index < 1 || index > item_max_index)
	{
		error_log("param error. uid=%u,index=%u", m_nUid, index);
		throw runtime_error("param_error");
	}

	//判断版本是否发生变化
	CheckActVersion();

	//获取活动期间内的充值数目
	unsigned begints = GetBeginTs();
	unsigned nowts = Time::GetGlobalTime();

	unsigned charge = userWrap.GetRechargePoint(begints, nowts);

	//根据index，获取配置
	const ConfigActivity::DiamondReward & itemcfg = ActivityConfigWrap().GetDoubleExtraConfigByIndex(index);

	if (charge < itemcfg.diamond())
	{
		error_log("charge not enough. uid=%u,index=%u,charge=%u", m_nUid, index, charge);
		throw runtime_error("charge_not_enough");
	}

	//是否已经领取该位置处的奖励
	if (m_jsonData["a"][index - 1].asUInt() > 0)
	{
		error_log("reward already been received. uid=%u,index=%u", m_nUid, index);
		throw runtime_error("reward_aleardy_received");
	}

	//发放奖励
	ProvideCommonReward(itemcfg.reward(), "DoubleWelfare_Extra", result);
	m_jsonData["a"][index - 1] = 1;   //设置奖励领取状态

	Save();

	result["NewAct"] = m_jsonData;

	return 0;
}

int DoubleWelfareActivityUnit::GetChareReward(UserWrap& userWrap, const BaseCmdParams & param, Json::Value & result)
{
	//判断版本是否发生变化
	CheckActVersion();

	//获取活动期间内的充值数目
	unsigned begints = GetBeginTs();
	unsigned nowts = Time::GetGlobalTime();

	unsigned charge = userWrap.GetRechargePoint(begints, nowts);

	//获取活动期间内的钻石消费数目
	unsigned cost = userWrap.GetCost(begints, nowts).first;

	ActivityConfigWrap activifywrap;

	//根据消费的钻石，获取倍数系数
	double coefficient = activifywrap.GetCoefficient(cost);
	int maximum = activifywrap.GetMaximum();

	int sum = round(charge * coefficient);

	if (sum > maximum)
	{
		sum = maximum;
	}

	//判断是否有剩余的代金券领取
	unsigned fetched = m_jsonData["b"].asUInt();   //已领取的代金券

	if (sum <= fetched)
	{
		error_log("have no left reward. uid=%u", m_nUid);
		throw runtime_error("no_left_reward");
	}

	//发放剩余的代金券
	//处理装备奖励
	vector<ItemAdd> equips;
	ItemAdd item(SHOP_PAY_VOUCHER, sum - fetched, "DoubleWelfare_Charge");
	equips.push_back(item);

	AddEquips(equips, result);

	//更新已领取的代金券的数量
	m_jsonData["b"] = sum;

	Save();

	result["NewAct"] = m_jsonData;

	return 0;
}

int DoubleWelfareActivityUnit::ResetAct()
{
	if (!m_jsonData.isMember("a"))
	{
		Json::Value array(Json::arrayValue);

		m_jsonData["a"] = array;
	}

	for(int i = 0; i < item_max_index; ++i)
	{
		m_jsonData["a"][i] = 0;  //重置兑换次数
	}

	m_jsonData["b"] = 0; //已领取代金券的数量
	m_jsonData["v"] = GetVersion();  //版本号
	m_jsonData["id"] = NAT_DOUBLE_WELFARE;  //id

	need_save = true;

	return 0;
}

PearlAdvanceActivityUnit::PearlAdvanceActivityUnit(const UserWrap& user):
		BaseActivityUnit(user.Id(), CONFIG_PEARL_ADVANCE)
{
	CLogicSecinc logicSecinc;
	int ret = logicSecinc.GetSecinc(m_nUid, NAT_PEARL_ADVANCE, m_jsonData);

	need_save = false;

	if (R_ERR_NO_DATA == ret)
	{
		//初始化双倍福利活动数据，与重置操作相同
		ResetAct();
	}
	else if (ret)
	{
		error_log("get newact error.uid=%u id=%d", m_nUid, NAT_PEARL_ADVANCE);
		throw std::runtime_error("get_new_active_data_error");
	}
}

int PearlAdvanceActivityUnit::ExchangePearl(UserWrap& userWrap, const UnitIndexCmdParams & param, Json::Value & result)
{
	unsigned index = param.Index();

	if (index < 1 || index > item_max_index)
	{
		error_log("param error. uid=%u,index=%u", m_nUid, index);
		throw runtime_error("param_error");
	}

	//判断版本是否发生变化
	CheckActVersion();

	const ConfigActivity::PearlAdvance & pearlcfg = ActivityConfigWrap().GetPearlAdvanceConfig(index);

	//判断兑换次数是否达到上限
	if (m_jsonData["a"][index - 1].asUInt() >= pearlcfg.maximum())
	{
		error_log("exchange times already max. uid=%u", m_nUid);
		throw runtime_error("times_already_max");
	}

	//判断积分是否足够
	unsigned nowts = Time::GetGlobalTime();
	unsigned charge = GetChargeByTime(userWrap, nowts);

	int used = m_jsonData["a"][index - 1].asInt();
	unsigned usedpoint = m_jsonData["b"].asUInt();

	if (charge < usedpoint + pearlcfg.cost())
	{
		error_log("charge not enough. uid=%u,charge=%u", m_nUid, charge);
		throw runtime_error("charge_not_enough");
	}

	//判断是否有符合数目的灵珠
	bool ismatch = CheckEquipCondition(pearlcfg, used + 1);

	if (!ismatch)
	{
		throw runtime_error("condition_not_match");
	}

	//符合条件，发放奖励
	unsigned endts = GetEndTs();
	ProvideCommonReward(pearlcfg.reward(), "PearlAdvance_Charge", result, endts);

	m_jsonData["a"][index - 1] = used + 1;    	//更新兑换次数
	m_jsonData["b"] = usedpoint + pearlcfg.cost();    //更新消耗的积分

	Save();

	result["NewAct"] = m_jsonData;

	return 0;
}

bool PearlAdvanceActivityUnit::CheckEquipCondition(const ConfigActivity::PearlAdvance & pearlcfg, int need)
{
	map<unsigned, unsigned> need_equip;

	for(int i = 0; i < pearlcfg.cond_eqid_size(); ++i)
	{
		unsigned eqid = pearlcfg.cond_eqid(i);
		need_equip[eqid] = 1;
	}

	//获取用户的所有道具，然后遍历符合条件的道具数量
	Json::Value equip_data;

	CLogicEquipment logicEquip;
	int ret = logicEquip.GetEquipment(m_nUid, 0, equip_data);

	if (ret)
	{
		return false;
	}

	unsigned count = 0;

	for (int i = 0; i < equip_data.size(); ++i)
	{
		unsigned eqid = equip_data[i]["id"].asUInt();

		if (need_equip.count(eqid))
		{
			count += 1;   //灵珠不可叠加，所以直接+1

			if (count >= need)
			{
				return true;
			}
		}
	}

	error_log("match equip not enough. uid=%u,num=%u", m_nUid, count);

	return false;
}

int PearlAdvanceActivityUnit::ResetAct()
{
	if (!m_jsonData.isMember("a"))
	{
		Json::Value array(Json::arrayValue);

		m_jsonData["a"] = array;
	}

	for(int i = 0; i < item_max_index; ++i)
	{
		m_jsonData["a"][i] = 0;  //重置兑换次数
	}

	m_jsonData["b"] = 0;  //已用积分

	m_jsonData["v"] = GetVersion();  //版本号
	m_jsonData["id"] = NAT_PEARL_ADVANCE;  //id

	need_save = true;

	return 0;
}

UniqueDialActivityUnit::UniqueDialActivityUnit(const UserWrap& user):
		BaseActivityUnit(user.Id(), CONFIG_UNIQUE_DIAL)
{
	CLogicSecinc logicSecinc;
	int ret = logicSecinc.GetSecinc(m_nUid, NAT_UNIQUEKNOWLEDGE_DIAL, m_jsonData);

	need_save = false;

	if (R_ERR_NO_DATA == ret)
	{
		//初始化双倍福利活动数据，与重置操作相同
		ResetAct();
	}
	else if (ret)
	{
		error_log("get newact error.uid=%u id=%d", m_nUid, NAT_UNIQUEKNOWLEDGE_DIAL);
		throw std::runtime_error("get_new_active_data_error");
	}
}

int UniqueDialActivityUnit::BeginLottery(UserWrap& userWrap, BaseCmdParams & param, Json::Value & result)
{
	//判断版本是否发生变化
	CheckActVersion();

	//判断充值金额是否足够
	unsigned nowts = Time::GetGlobalTime();
	unsigned charge = GetChargeByTime(userWrap, nowts);

	int times = charge/10000;  //每10000钻，获得一次抽奖次数

	if (times < (m_jsonData["a"].asUInt() + 1))
	{
		error_log("lottery times not enough. uid=%u.charge=%u", m_nUid, charge);
		throw runtime_error("lottery_times_not_enough");
	}

	if (m_jsonData["a"].asUInt() >= 20)
	{
		error_log("lottery times is enough. uid=%u.charge=%u", m_nUid, charge);
		throw runtime_error("lottery_times_is_enough");
	}

	//随机产生奖励
	const ConfigActivity::Activities & activitycfg = ActivityConfigWrap().GetActivityCfg();

	vector<unsigned> weights;

	for(int i = 0; i < activitycfg.unique_knowledge_dial_size(); ++i)
	{
		unsigned weight = activitycfg.unique_knowledge_dial(i).weight();

		weights.push_back(weight);
	}

	//开始转动转盘
	int target = 0;

	TurnVecLuckTable(weights, weights.size(), target);

	result["id"] = activitycfg.unique_knowledge_dial(target).id();

	//发放抽中的物品
	ProvideCommonReward(activitycfg.unique_knowledge_dial(target).item(), "UniqueKnowledge_Dial_Lottery", result);

	m_jsonData["a"] = m_jsonData["a"].asUInt() + 1;    	//更新抽奖次数

	Save();

	result["NewAct"] = m_jsonData;

	return 0;
}

int UniqueDialActivityUnit::ResetAct()
{
	m_jsonData["a"] = 0;  //抽奖次数

	m_jsonData["v"] = GetVersion();  //版本号
	m_jsonData["id"] = NAT_UNIQUEKNOWLEDGE_DIAL;  //id

	need_save = true;

	return 0;
}

SpiritVitalityActivityUnit::SpiritVitalityActivityUnit(const UserWrap& user):
		BaseActivityUnit(user.Id(), CONFIG_SPIRIT_VITALITY)
{
	CLogicSecinc logicSecinc;
	int ret = logicSecinc.GetSecinc(m_nUid, NAT_SPIRIT_VITALITY, m_jsonData);
	need_save = false;

	if (R_ERR_NO_DATA == ret)
	{
		//初始化精元礼包活动数据
		ResetAct();
	}
	else if (ret)
	{
		error_log("get newact error.uid=%u id=%d", m_nUid, NAT_SPIRIT_VITALITY);
		throw std::runtime_error("get_new_active_data_error");
	}
}

int SpiritVitalityActivityUnit::ReceiveChargeGift(UserWrap& userWrap, const UnitIndexCmdParams & param, Json::Value & result)
{
	unsigned index = param.Index();

	if (index < 1 || index > item_max_index)
	{
		error_log("param error. uid=%u,index=%u", m_nUid, index);
		throw runtime_error("param_error");
	}

	//判断版本是否发生变化
	CheckActVersion();

	//获取活动期间内的充值数目
	unsigned nowts = Time::GetGlobalTime();
	unsigned charge = GetChargeByTime(userWrap, nowts);

	//根据index，获取配置
	const ConfigActivity::SpriteVitalityItem & itemcfg = ActivityConfigWrap().GetSpriteConfig(index);

	if (charge < itemcfg.diamond())
	{
		error_log("charge not enough. uid=%u,index=%u,charge=%u", m_nUid, index, charge);
		throw runtime_error("charge_not_enough");
	}

	//是否已经领取该位置处的奖励
	if (m_jsonData["a"][index - 1].asUInt() > 0)
	{
		error_log("reward already been received. uid=%u,index=%u", m_nUid, index);
		throw runtime_error("reward_aleardy_received");
	}

	//发放奖励
	ProvideCommonReward(itemcfg.reward(), "SpiritVitality_Charge", result);

	m_jsonData["a"][index - 1] = 1;   //设置奖励领取状态
	Save();

	result["NewAct"] = m_jsonData;

	return 0;
}

int SpiritVitalityActivityUnit::ResetAct()
{
	if (!m_jsonData.isMember("a"))
	{
		Json::Value array(Json::arrayValue);

		m_jsonData["a"] = array;
	}

	for(int i = 0; i < item_max_index; ++i)
	{
		m_jsonData["a"][i] = 0;  //重置奖励领取状态
	}

	m_jsonData["v"] = GetVersion();  //版本号
	m_jsonData["id"] = NAT_SPIRIT_VITALITY;  //id

	need_save = true;

	return 0;
}

ForgeSmeltActivityUnit::ForgeSmeltActivityUnit(const UserWrap& user):
		BaseActivityUnit(user.Id(), CONFIG_FORGE_SMELT)
{
	CLogicSecinc logicSecinc;
	int ret = logicSecinc.GetSecinc(m_nUid, NAT_FORGE_SMELT, m_jsonData);
	need_save = false;

	if (R_ERR_NO_DATA == ret)
	{
		//初始化熔炉
		m_jsonData["c"] = 0;  //当前熔炉值

		ResetAct();
	}
	else if (ret)
	{
		error_log("get newact error.uid=%u id=%d", m_nUid, NAT_FORGE_SMELT);
		throw std::runtime_error("get_new_active_data_error");
	}
}

int ForgeSmeltActivityUnit::ForgeSmelt(UserWrap& userWrap, const BaseCmdParams & param, Json::Value & result)
{
	//判断版本是否发生变化
	CheckActVersion();

	//判断是否跨天
	CheckDifferDay();

	//取出所有待熔炼的物品
	const Json::Value & paramdata = param.ParamsObj();
	CLogicEquipment logicEquipMent;
	map<unsigned, pair<unsigned, unsigned> > smelt_relation;

	ActivityConfigWrap activitywrap;

	//获取熔炉熔炼的物品
	activitywrap.GetForgeSmeltRelation(smelt_relation);

	//获取熔炉值的上限配置
	const ConfigActivity::ForgeSmelt & smeltcfg = activitywrap.GetForgeSmeltCfg();

	//判断当前熔炉值是否达到上限
	unsigned forgelimit = smeltcfg.forge_limit();
	unsigned daily_limit = smeltcfg.daily_limit();

	if (m_jsonData["c"].asUInt() >= forgelimit)
	{
		error_log("forge value is already max. uid=%u", m_nUid);
		throw runtime_error("forge_already_max");
	}

	//判断今日获取熔炉值是否达到上限
	if (m_jsonData["b"].asUInt() >= daily_limit)
	{
		error_log("daily forge value is already max. uid=%u", m_nUid);
		throw runtime_error("daily_forge_already_max");
	}

	//返回实际消耗的物品和个数
	for(unsigned i = 0; i < paramdata["items"].size(); ++i)
	{
		//循环处理
		unsigned equd = paramdata["items"][i]["ud"].asUInt();
		unsigned times = paramdata["items"][i]["c"].asUInt();  //熔炼的次数

		if (0 == times)
		{
			continue;
		}

		//根据ud获取装备信息
		Json::Value equipdata;

		logicEquipMent.Get(m_nUid, equd, equipdata);

		unsigned eqid = equipdata["id"].asUInt();

		if (!smelt_relation.count(eqid))
		{
			error_log("param error. equip can not be smelt. uid=%u,equd=%u", m_nUid, equd);
			throw runtime_error("param_error");
		}

		//根据给定的熔炉值计算需要消耗几倍的装备
		int realvalue = times * smelt_relation[eqid].second;  //实际增加的熔炉值
		int cost_count = times * smelt_relation[eqid].first;  //实际消耗的物品

		if (cost_count > equipdata["count"].asUInt())
		{
			error_log("equip num not enough. uid=%u, equd=%u,needcount=%d", m_nUid, equd, cost_count);
			throw runtime_error("equip_not_enough");
		}

		//判断过程当中是否会出现熔炉值溢出问题
		if (m_jsonData["c"].asUInt() + realvalue > forgelimit)
		{
			error_log("forge value is already max. uid=%u", m_nUid);
			throw runtime_error("forge_forbidden_reach_max");
		}

		//判断今日获取熔炉值是否达到上限
		if (m_jsonData["b"].asUInt() + realvalue > daily_limit)
		{
			error_log("daily forge value is already max. uid=%u", m_nUid);
			throw runtime_error("daily_forge_forbidden_reach_max");
		}

		//消耗物品
		int ret = logicEquipMent.UseEquipment(m_nUid, eqid, equd, cost_count, "ForgeSmelt");

		if (ret)
		{
			error_log("use equip error. uid=%u,equd=%u", m_nUid, equd);
			throw runtime_error("use_equip_error");
		}

		//熔炉值增加
		m_jsonData["b"] = m_jsonData["b"].asUInt() + realvalue;
		m_jsonData["c"] = m_jsonData["c"].asUInt() + realvalue;

		need_save = true;
	}

	Save();

	result["NewAct"] = m_jsonData;

	return 0;
}

int ForgeSmeltActivityUnit::BuyGoods(UserWrap& userWrap, const UnitIndexCmdParams & param, Json::Value & result)
{
	//判断版本是否发生变化
	CheckActVersion();

	//判断是否跨天
	CheckDifferDay();

	unsigned index = param.Index();

	//获取熔炉商店的配置
	const ConfigActivity::ShopItem & forgeshopcfg = ActivityConfigWrap().GetForgeShopConfig(index);

	//判断该位置物品是否已购买
	int pos = index - 1;

	if (m_jsonData["a"][pos].asUInt() > 0)
	{
		error_log("goods already bought. uid=%u,index=%u", m_nUid, index);
		throw runtime_error("goods_already_bought");
	}

	//判断熔炉值是否足够
	if (m_jsonData["c"].asUInt() < forgeshopcfg.forgecost())
	{
		error_log("forge value not enough. uid=%u,index=%u", m_nUid, index);
		throw runtime_error("forge_not_enough");
	}

	if (forgeshopcfg.diamond() > 0)
	{
		//扣钻
		userWrap.CostAsset(forgeshopcfg.diamond(), 0, "ForgeShop", result);
	}

	//扣除熔炉值
	m_jsonData["c"] = m_jsonData["c"].asUInt() - forgeshopcfg.forgecost();

	//发放奖励
	ProvideCommonReward(forgeshopcfg.item(), "ForgeShop", result);

	m_jsonData["a"][pos] = 1;

	Save();

	result["NewAct"] = m_jsonData;

	return 0;
}

int ForgeSmeltActivityUnit::CheckDifferDay()
{
	//检查是否跨天
	unsigned nowts = Time::GetGlobalTime();

	if (CTime::GetDayInterval(m_jsonData["t"].asUInt(), nowts))
	{
		ResetAct();
	}

	//检查熔炉商店物品项是否有扩展
	int size = ActivityConfigWrap().GetForgeShopSize();
	int oldsize = m_jsonData["a"].size();

	if (oldsize < size)
	{
		for(int i = oldsize; i < size; ++i)
		{
			m_jsonData["a"][i] = 0;
		}
	}

	return 0;
}

int ForgeSmeltActivityUnit::ResetAct()
{
	//这里，写的是重置的逻辑，与初始化的不同
	//活动重置与每天的重置相同.
	//商店的购买状态，每日获取到的熔炉值
	if (!m_jsonData.isMember("a"))
	{
		Json::Value array(Json::arrayValue);

		m_jsonData["a"] = array;
	}

	int size = ActivityConfigWrap().GetForgeShopSize();

	for(int i = 0; i < size; ++i)
	{
		m_jsonData["a"][i] = 0;  //重置商店购买状态
	}

	m_jsonData["b"] = 0; // 每日获取的熔炉值
	m_jsonData["t"] = Time::GetGlobalTime();  //每日重置时间

	m_jsonData["v"] = GetVersion();  //版本号
	m_jsonData["id"] = NAT_FORGE_SMELT;  //id

	need_save = true;

	return 0;
}

HeroesDialActivityUnit::HeroesDialActivityUnit(const UserWrap& user):
		BaseActivityUnit(user.Id(), CONFIG_HERO_DIAL)
{
	CLogicSecinc logicSecinc;
	int ret = logicSecinc.GetSecinc(m_nUid, NAT_HERO_DIAL, m_jsonData);
	need_save = false;

	if (R_ERR_NO_DATA == ret)
	{
		//初始化紫将转盘
		ResetAct();
	}
	else if (ret)
	{
		error_log("get newact error.uid=%u id=%d", m_nUid, NAT_HERO_DIAL);
		throw std::runtime_error("get_new_active_data_error");
	}
}

int HeroesDialActivityUnit::TurnHeroTable(UserWrap& userWrap, const BaseCmdParams & param, Json::Value & result)
{
	unsigned type = param.ValueAsUInt("type");

	if (type != turn_type_once && type != turn_type_ten)
	{
		error_log("param error. uid=%u,type=%u", m_nUid, type);
		throw runtime_error("param_error");
	}

	//判断版本是否发生变化
	CheckActVersion();

	//获取活动期间内的充值数目
	unsigned nowts = Time::GetGlobalTime();
	unsigned charge = GetChargeByTime(userWrap, nowts);

	const ConfigActivity::HeroDial & herodialcfg = ActivityConfigWrap().GetHeroDialCfg();

	int nexttimes = 0;

	if (turn_type_once == type)
	{
		nexttimes = 1;
	}
	else
	{
		nexttimes = 10;
	}

	//判断充值的钻石是否足够
	int turntimes = charge/herodialcfg.per();

	if (turntimes < (m_jsonData["a"].asUInt() + nexttimes))
	{
		error_log("turn times not enough. uid=%u,have=%d", m_nUid, turntimes);
		throw runtime_error("times_not_enough");
	}

	//判断转盘次数是否超过最大次数
	if (m_jsonData["a"].asUInt() + nexttimes > herodialcfg.limit())
	{
		error_log("turn times can not beyond limit. uid=%u,type=%d", m_nUid, type);
		throw runtime_error("times_beyond_max");
	}

	//开始转动
	for(int i = 0; i < nexttimes; ++i)
	{
		StartTurn(userWrap, herodialcfg, result);
	}

	Save();

	result["NewAct"] = m_jsonData;

	return 0;
}

int HeroesDialActivityUnit::StartTurn(UserWrap& userWrap, const ConfigActivity::HeroDial & herodialcfg, Json::Value &result)
{
	//根据配置的权重，取随机结果
	vector<unsigned> weights;

	for(int i = 0; i < herodialcfg.heroes_size(); ++i)
	{
		unsigned weight = herodialcfg.heroes(i).weight();
		weights.push_back(weight);
	}

	int target = 0;
	TurnVecLuckTable(weights, weights.size(), target);

	//发放奖励物品
	Json::Value jsonherovalue;
	ProvideCommonReward(herodialcfg.heroes(target).reward(), "HeroDial", jsonherovalue);

	if (!result.isMember("herodial"))
	{
		result["herodial"] = Json::arrayValue;
	}

	result["herodial"].append(jsonherovalue);

	if (!result.isMember("ids"))
	{
		result["ids"] = Json::arrayValue;
	}

	result["ids"].append(herodialcfg.heroes(target).id());

	m_jsonData["a"] = m_jsonData["a"].asUInt() + 1;

	need_save = true;

	return 0;
}

int HeroesDialActivityUnit::ResetAct()
{
	m_jsonData["a"] = 0; //已转动次数

	m_jsonData["v"] = GetVersion();  //版本号
	m_jsonData["id"] = NAT_HERO_DIAL;  //id

	need_save = true;

	return 0;
}


KingdomWarActivityUnit::KingdomWarActivityUnit(const UserWrap& user):
		BaseActivityUnit(user.Id(), CONFIG_KINGDOM_WAR)
{
	CLogicSecinc logicSecinc;
	int ret = logicSecinc.GetSecinc(m_nUid, NAT_KINGDOM_WAR, m_jsonData);
	need_save = false;

	if (R_ERR_NO_DATA == ret)
	{
		//初始化三国争霸活动
		ResetAct();
	}
	else if (ret)
	{
		error_log("get newact error.uid=%u id=%d", m_nUid, NAT_KINGDOM_WAR);
		throw std::runtime_error("get_new_active_data_error");
	}
}

int KingdomWarActivityUnit::GetChargeReward(UserWrap& userWrap, const UnitIndexCmdParams & param, Json::Value & result)
{
	ActivityConfigWrap activitywrap;
	unsigned index = param.Index();
	unsigned size = activitywrap.GetKingdomItemSize();

	if (index < 1 || index > size)
	{
		error_log("param error. uid=%u,index=%u", m_nUid, index);
		throw runtime_error("param error");
	}

	//判断版本是否发生变化
	CheckActVersion();

	//检查配置的奖励长度是否有变化
	CheckItemSize();

	//获取活动期间内的充值数目
	unsigned nowts = Time::GetGlobalTime();
	unsigned charge = GetChargeByTime(userWrap, nowts);

	//根据index，获取配置
	const ConfigActivity::KingdomWar & itemcfg = activitywrap.GetKingdomWarConfig(index);

	if (charge < itemcfg.diamond())
	{
		error_log("charge not enough. uid=%u,index=%u,charge=%u", m_nUid, index, charge);
		throw runtime_error("charge_not_enough");
	}

	//是否已经领取该位置处的奖励
	if (m_jsonData["a"][index - 1].asUInt() > 0)
	{
		error_log("reward already been received. uid=%u,index=%u", m_nUid, index);
		throw runtime_error("reward_aleardy_received");
	}

	//发放奖励
	ProvideCommonReward(itemcfg.reward(), "KingdomWar_Charge", result);

	m_jsonData["a"][index - 1] = 1;   //设置奖励领取状态

	Save();

	result["NewAct"] = m_jsonData;

	return 0;
}

int KingdomWarActivityUnit::CheckItemSize()
{
	int size = ActivityConfigWrap().GetKingdomItemSize();

	int oldsize = m_jsonData["a"].size();

	if (oldsize < size)
	{
		for(int i = oldsize; i < size; ++i)
		{
			m_jsonData["a"][i] = 0;
		}

		need_save = true;
	}

	return 0;
}

int KingdomWarActivityUnit::ResetAct()
{
	if (!m_jsonData.isMember("a"))
	{
		Json::Value array(Json::arrayValue);

		m_jsonData["a"] = array;
	}

	int size = ActivityConfigWrap().GetKingdomItemSize();

	for(int i = 0; i < size; ++i)
	{
		m_jsonData["a"][i] = 0;  //重置充值奖励领取状态
	}

	m_jsonData["v"] = GetVersion();  //版本号
	m_jsonData["id"] = NAT_KINGDOM_WAR;  //id

	need_save = true;

	return 0;
}

ProtectiveFlagUnit::ProtectiveFlagUnit(const UserWrap& user):
		BaseCmdUnit(user.Id())
{

}

int ProtectiveFlagUnit::Upgrade(UserWrap& userWrap, const BaseCmdParams & param, Json::Value & result)
{
	unsigned flagud = param.ValueAsUInt("ud");
	unsigned type = param.ValueAsUInt("type");
	unsigned aud = param.ValueAsUInt("aud");   //升级消耗的道具A
	unsigned bud = param.ValueAsUInt("bud");  //保护旗帜建造令ud

	CLogicBuilding logicbuild;

	Json::Value builddata;
	int ret = logicbuild.Get(m_nUid, flagud, 0, true, builddata);

	if (ret)
	{
		return ret;
	}

	if (type_upgrade_once != type && type_upgrade_onekey != type)
	{
		error_log("param error. uid=%u,type=%u", m_nUid, type);
		throw runtime_error("param_error");
	}

	if (0 == aud)
	{
		error_log("param error. uid=%u,aud=%u", m_nUid, aud);
		throw runtime_error("param_error");
	}

	if (!builddata.isMember("exp"))
	{
		builddata["exp"] = 0;
	}

	//判断是否达到最大等级
	DataXMLProtectFlag * protectflagcfg = NULL;
	DataXmlPtr()->GetProtectFlagPointer(&protectflagcfg);

	if (NULL == protectflagcfg)
	{
		error_log("read config error. uid=%u", m_nUid);
		throw runtime_error("config_error");
	}

	//判断经验是否达到最大值，如果是，则不能再进行升级
	unsigned exp = builddata["exp"].asUInt();
	int oldlevel = GetLevelByExp(protectflagcfg->exps, MAX_FLAG_LEVEL, exp);

	if (oldlevel >= MAX_FLAG_LEVEL)
	{
		error_log("level is already max. uid=%u", m_nUid);
		throw runtime_error("level_already_max");
	}

	const int single_exp = 10;  //单次改造增加的经验值

	CLogicEquipment logicequip;

	int count = 0;
	int bcount = 0; //建造令 消耗个数
	int newexp = 0;

	if (type_upgrade_once == type)
	{
		//判断是否升新的一级
		newexp = exp + single_exp;
		int level = GetLevelByExp(protectflagcfg->exps, MAX_FLAG_LEVEL, newexp);

		if (level > oldlevel)
		{
			//升级了，需要消耗旗帜建造令，具体数值读配置。照策划需求，是从5*(1..n)往上升一级时才消耗，但是为了简化处理
			//直接做成了配置，然后每级配置消耗的建造令，如果没有，就是0。以当前等级作为下标
			bcount = protectflagcfg->eqcount[oldlevel];

			builddata["l"] = level;
		}

		count = 1;
	}
	else
	{
		//一键升级
		//先计算距离下一级还差多少经验
		newexp = protectflagcfg->exps[oldlevel];
		count = (newexp - exp)/single_exp;  //需要消耗的道具A个数
		bcount = protectflagcfg->eqcount[oldlevel];

		builddata["l"] = oldlevel + 1;
	}

	//消耗旗帜建造令
	if (bcount > 0)
	{
		ret = logicequip.UseEquipment(m_nUid, protect_flag_build, bud, bcount, "FlagUpgrade");

		if (ret)
		{
			error_log("use equipment error. uid=%u, ud=%u", m_nUid, bud);
			throw runtime_error("use_equip_error");
		}
	}

	//消耗道具A
	ret = logicequip.UseEquipment(m_nUid, flag_upgrade_costA, aud, count, "FlagUpgrade");

	if (ret)
	{
		error_log("use equipment error. uid=%u,ud=%u", m_nUid, aud);
		throw runtime_error("use_equip_error");
	}

	builddata["exp"] = newexp;

	//更新旗帜经验
	ret = logicbuild.Chg(m_nUid, flagud, 0, true, builddata);

	result["build"] = builddata;

	return ret;
}

int ProtectiveFlagUnit::GetLevelByExp(unsigned * pexp, int size, int exp)
{
	//从后往前，查找第一个大于数组元素的下标
	int level = 1;

	for(int i = size - 1; i >= 0; --i)
	{
		if (pexp[i] <= exp)
		{
			level = i + 1;
			break;
		}
	}

	return level;
}

OneDiamondWelfareActivityUnit::OneDiamondWelfareActivityUnit(const UserWrap& user):
		BaseActivityUnit(user.Id(), CONFIG_ONEDIAMOND)
{
	sid = NAT_ONE_DIAMOND_WELFARE;
	CLogicSecinc logicSecinc;
	int ret = logicSecinc.GetSecinc(m_nUid, sid, m_jsonData);
	need_save = false;

	if (R_ERR_NO_DATA == ret)
	{
		//初始化一钻福利活动
		ResetAct();
	}
	else if (ret)
	{
		error_log("get newact error.uid=%u id=%d", m_nUid, sid);
		throw std::runtime_error("get_new_active_data_error");
	}
}

int OneDiamondWelfareActivityUnit::BuyGoods(UserWrap& userWrap, const BaseCmdParams & param, Json::Value & result)
{
	unsigned lindex = param.ValueAsUInt("lindex");
	unsigned rindex = param.ValueAsUInt("rindex");

	if (lindex < 1 || lindex > diamond_kinds_item || rindex < 1 || rindex > reward_item)
	{
		error_log("param error. uid=%u,lindex=%u,rindex=%u", m_nUid, lindex, rindex);
		throw runtime_error("param_error");
	}

	//判断版本是否发生变化
	CheckActVersion();

	const ConfigActivity::OneDiamondWelfare & onediamondcfg = ActivityConfigWrap().GetOneDiamondCfg(lindex);

	if (rindex > onediamondcfg.items_size())
	{
		error_log("param error. uid=%u,rindex=%u", m_nUid, rindex);
		throw runtime_error("param_error");
	}

	//获取活动期间内的充值数目
	unsigned nowts = Time::GetGlobalTime();
	unsigned charge = GetChargeByTime(userWrap, nowts);

	if (charge < onediamondcfg.diamond())
	{
		error_log("charge not enough. uid=%u,lindex=%u,charge=%u", m_nUid, lindex, charge);
		throw runtime_error("charge_not_enough");
	}

	//购买次数是否足够
	unsigned times = m_jsonData["a"][lindex - 1][rindex - 1].asUInt();
	if (times >= max_buy_times)
	{
		error_log("goods was sold out. uid=%u,lindex=%u,rindex=%u", m_nUid, lindex, rindex);
		throw runtime_error("goods_sold_out");
	}

	//扣钻
	int cash = 0;

	if (times == 0)
	{
		//首次购买
		cash = first_buy_price;
	}
	else
	{
		cash = onediamondcfg.items(rindex - 1).price();
	}

	userWrap.CostAsset(cash, 0, "OneDiamondWelfare", result);

	//发放奖励
	ProvideCommonReward(onediamondcfg.items(rindex - 1).reward(), "OneDiamondWelfare", result);

	m_jsonData["a"][lindex - 1][rindex - 1] = times + 1;   //增加购买次数

	Save();

	result["NewAct"] = m_jsonData;

	return 0;
}

int OneDiamondWelfareActivityUnit::ResetAct()
{
	if (!m_jsonData.isMember("a"))
	{
		Json::Value array(Json::arrayValue);

		m_jsonData["a"] = array;
	}

	for(int i = 0; i < diamond_kinds_item; ++i)
	{
		Json::Value insidearray(Json::arrayValue);

		for(int j = 0; j < reward_item; ++j)
		{
			insidearray[j] = 0;
		}

		m_jsonData["a"][i] = insidearray;  //重置物品领取状态
	}

	m_jsonData["v"] = GetVersion();  //版本号
	m_jsonData["id"] = sid;  //id

	need_save = true;

	return 0;
}

QiXiFeedbackActivityUnit::QiXiFeedbackActivityUnit(const UserWrap& user):
		BaseActivityUnit(user.Id(), CONFIG_QIXI_FEEDBACK)
{
	sid = NAT_QIXI_FEEDBACK;

	CLogicSecinc logicSecinc;
	int ret = logicSecinc.GetSecinc(m_nUid, sid, m_jsonData);

	need_save = false;

	if (R_ERR_NO_DATA == ret)
	{
		//初始化七夕回馈
		ResetAct();
	}
	else if (ret)
	{
		error_log("get newact error.uid=%u id=%d", m_nUid, sid);
		throw std::runtime_error("get_new_active_data_error");
	}
}

int QiXiFeedbackActivityUnit::GetFeedback(UserWrap& userWrap, const BaseCmdParams & param, Json::Value & result)
{
	//判断版本是否发生变化
	CheckActVersion();

	//判断奖励是否已经领取
	if (m_jsonData["a"].asUInt())
	{
		error_log("reward already gotten. uid=%u", m_nUid);
		throw runtime_error("reward_already_gotten");
	}

	unsigned nowts = Time::GetGlobalTime();
	unsigned begints = GetBeginTs();

	bool iscondition = userWrap.IsHaveRechargeGoal(begints, nowts, 400);

	if (!iscondition)
	{
		error_log("charge not enoush. uid=%u", m_nUid);
		throw runtime_error("charge_not_enough");
	}

	//发奖
	CLogicPay logicPay;
	DataPay payData;

	int ret = logicPay.ChangePay(m_nUid, 400, 0, "QiXiFeedback", payData);

	if (ret != 0)
		return ret;

	result["coins"] = payData.coins;	//金币
	result["coins2"] = payData.cash;	//钻石

	//设置已领取标志
	m_jsonData["a"] = 1;
	Save();

	result["NewAct"] = m_jsonData;

	return 0;
}

int QiXiFeedbackActivityUnit::ResetAct()
{
	m_jsonData["a"] = 0;  //奖励领取标志

	m_jsonData["v"] = GetVersion();  //版本号
	m_jsonData["id"] = sid;  //id

	need_save = true;

	return 0;
}

FortunePacksActivityUnit::FortunePacksActivityUnit(const UserWrap& user):
		BaseActivityUnit(user.Id(), CONFIG_FORTUNE_PACKS)
{
	sid = NAT_FORTUNE_PACKS;

	CLogicSecinc logicSecinc;
	int ret = logicSecinc.GetSecinc(m_nUid, sid, m_jsonData);

	need_save = false;

	if (R_ERR_NO_DATA == ret)
	{
		//初始化
		ResetAct();
	}
	else if (ret)
	{
		error_log("get newact error.uid=%u id=%d", m_nUid, sid);
		throw std::runtime_error("get_new_active_data_error");
	}
}

int FortunePacksActivityUnit::ResetAct()
{
	m_jsonData["a"] = 0;  //参与的号数

	if (!m_jsonData.isMember("b"))
	{
		Json::Value array(Json::arrayValue);

		m_jsonData["b"] = array;
	}

	for(int i = 0; i < item_max_index; ++i)
	{
		m_jsonData["b"][i] = 0;  //重置物品购买状态
	}

	m_jsonData["v"] = GetVersion();  //版本号
	m_jsonData["id"] = sid;  //id

	need_save = true;

	return 0;
}

int FortunePacksActivityUnit::OpenWindow(UserWrap& userWrap, const BaseCmdParams & param, Json::Value & result)
{
	//检查共享内存中的版本号
	unsigned version = GetVersion();

	CDataFortunePacks* pdata = CDataFortunePacks::GetCDataFortunePacks();
	pdata->CheckVersion(version);

	//判断版本是否发生变化
	CheckActVersion();
	Json::Value users(Json::arrayValue);

	GetGiftedUsers(pdata, users);

	result["users"] = users;
	result["NewAct"] = m_jsonData;

	return 0;
}

//购买物品
int FortunePacksActivityUnit::Purchase(UserWrap& userWrap, const UnitIdCmdParams & param, Json::Value & result)
{
	unsigned id = param.Id();

	//判断参数
	if (id < 1 || id > item_max_index)
	{
		error_log("param error. uid=%u,id=%u", m_nUid, id);
		throw runtime_error("param_error");
	}

	//检查共享内存中的版本号
	unsigned version = GetVersion();

	CDataFortunePacks* pdata = CDataFortunePacks::GetCDataFortunePacks();
	pdata->CheckVersion(version);

	//判断版本是否发生变化
	CheckActVersion();

	//判断充值钻数是否符合条件
	unsigned nowts = Time::GetGlobalTime();
	unsigned charge = GetChargeByTime(userWrap, nowts);

	if (charge < charge_condition)
	{
		error_log("charge not enough. uid=%u", m_nUid);
		throw runtime_error("charge_not_enough");
	}

	int pos = id - 1;

	//判断是否已购买
	if (m_jsonData["b"][pos].asUInt())
	{
		error_log("this goods already been boughten. uid=%u,id=%u", m_nUid, id);
		throw runtime_error("goods_already_bought");
	}

	ActivityConfigWrap activitywrap;

	const ConfigActivity::RewardItem & goodscfg = activitywrap.GetFortunePackItemCfg(id);

	//扣钻
	userWrap.CostAsset(goodscfg.price(), 0, "FortunePack_Buy", result);

	//发放物品
	ProvideCommonReward(goodscfg.reward(), "FortunePack_Buy", result);

	m_jsonData["b"][pos] = 1;

	if (0 == m_jsonData["a"].asUInt())
	{
		//第一次参与活动，获取当前参与活动的玩家个数
		unsigned num = pdata->GetParticipateNum();
		m_jsonData["a"] = num + 1;

		//判断是否有额外奖励
		unsigned extranum = pdata->GetExtraNum();  //额外奖励赠送个数
		bool isextra = false;

		if (extranum < MAX_EXTRA_ITEMS && m_jsonData["a"].asUInt() == extra_num_relation[extranum])
		{
			//奖励未发送完，且当前玩家满足额外奖励所需的人数要求
			isextra = true;
			const RewardConfig::RewardItemCfg & extracfg = activitywrap.GetFortunePackExtracfg();

			ProvideCommonReward(extracfg, "FortunePack_Extra", result["extra"]);
		}

		pdata->Participate(m_nUid, isextra);

		//额外奖励存在时，发送最新的玩家列表给前端
		if (isextra)
		{
			Json::Value users(Json::arrayValue);
			GetGiftedUsers(pdata, users);

			result["users"] = users;
		}
	}

	Save();

	result["NewAct"] = m_jsonData;

	return 0;
}

int FortunePacksActivityUnit::GetGiftedUsers(CDataFortunePacks* pdata, Json::Value & users)
{
	//获取已获取礼包的用户名单
	vector<unsigned> uids;

	pdata->GetGiftedUsers(uids);

	CLogicUserBasic logicUserBasic;
	PlatformType platform = OpenPlatform::GetType();

	for(int i = 0; i < uids.size(); ++i)
	{
		unsigned uidtemp = uids[i];
		DataUserBasic userBasic;

		int ret = logicUserBasic.GetUserBasicLimit(uidtemp, platform, userBasic);

		if (ret != 0)
			return ret;

		users.append(userBasic.name);
	}

	return 0;
}

SevenDayPacksActivityUnit::SevenDayPacksActivityUnit(const UserWrap& user):
		BaseActivityUnit(user.Id(), CONFIG_SEVENDAYS_PACKS)
{
	sid = NAT_SEVENDAY_PACKS;

	CLogicSecinc logicSecinc;
	int ret = logicSecinc.GetSecinc(m_nUid, sid, m_jsonData);

	need_save = false;

	if (R_ERR_NO_DATA == ret)
	{
		//初始化
		ResetAct();
	}
	else if (ret)
	{
		error_log("get newact error.uid=%u id=%d", m_nUid, sid);
		throw std::runtime_error("get_new_active_data_error");
	}
}

int SevenDayPacksActivityUnit::ResetAct()
{
	if (!m_jsonData.isMember("a"))
	{
		Json::Value array(Json::arrayValue);

		m_jsonData["a"] = array;
	}

	for(int i = 0; i < item_max_index; ++i)
	{
		m_jsonData["a"][i] = 0;  //重置奖励领取状态
	}

	m_jsonData["v"] = GetVersion();  //版本号
	m_jsonData["id"] = sid;  //id

	need_save = true;

	return 0;
}

int SevenDayPacksActivityUnit::GetReward(UserWrap& userWrap, const UnitIndexCmdParams & param, Json::Value & result)
{
	unsigned index = param.Index();

	//先判断参数的合法性
	if (index < 1 || index > item_max_index)
	{
		error_log("param error. uid=%u, index=%u", m_nUid, index);
		throw runtime_error("param_error");
	}

	//判断版本是否发生变化
	CheckActVersion();

	//判断充值的条件是否满足
	unsigned begints = GetBeginTs();
	unsigned nowts = Time::GetGlobalTime();

	unsigned days = userWrap.GetRechargeGoalDays(begints, nowts, charge_condition);

	if (days < index)
	{
		error_log("charge days not enough. uid=%u,index=%u,days=%u", m_nUid, index, days);
		throw runtime_error("charge_days_not_enough");
	}

	//判断奖励是否已经领取
	int pos = index - 1;

	if (m_jsonData["a"][pos].asUInt() > 0)
	{
		error_log("reward already got. uid=%u,index=%u", m_nUid, index);
		throw runtime_error("reward_already_got");
	}

	const ConfigActivity::SevenDayPacks & sevencfg = ActivityConfigWrap().GetSevendayPacksItemcfg(index);

	char reason[40] = {0};
	sprintf(reason, "SevenDayPacks_%u", index);

	//发放奖励
	ProvideCommonReward(sevencfg.reward(), reason, result);

	//设置奖励领取状态
	m_jsonData["a"][pos] = 1;

	Save();

	result["NewAct"] = m_jsonData;

	return 0;
}

ChargeQuotaActivityBase::ChargeQuotaActivityBase(unsigned uid, const std::string& actname,
		int sid_, int itemsize_):
		BaseActivityUnit(uid, actname)
{
	sid = sid_;
	itemsize = itemsize_;

	CLogicSecinc logicSecinc;
	int ret = logicSecinc.GetSecinc(m_nUid, sid, m_jsonData);

	need_save = false;

	if (R_ERR_NO_DATA == ret)
	{
		//初始化
		ResetAct();
	}
	else if (ret)
	{
		error_log("get newact error.uid=%u id=%d", m_nUid, sid);
		throw std::runtime_error("get_new_active_data_error");
	}
}

int ChargeQuotaActivityBase::ResetAct()
{
	if (!m_jsonData.isMember("a"))
	{
		Json::Value array(Json::arrayValue);

		m_jsonData["a"] = array;
	}

	for(int i = 0; i < itemsize; ++i)
	{
		m_jsonData["a"][i] = 0;  //重置奖励领取状态
	}

	m_jsonData["v"] = GetVersion();  //版本号
	m_jsonData["id"] = sid;  //id

	need_save = true;

	return 0;
}

int ChargeQuotaActivityBase::CheckItemSize()
{
	return 0;
}

int ChargeQuotaActivityBase::Reward(UserWrap& userWrap, unsigned index, const ConfigActivity::DiamondReward & itemcfg, string reason, Json::Value & result)
{
	if (index < 1 || index > itemsize)
	{
		error_log("param error. uid=%u,index=%u", m_nUid, index);
		throw runtime_error("param error");
	}

	//判断版本是否发生变化
	CheckActVersion();

	//检查充值额度的档位数
	CheckItemSize();

	//获取活动期间内的充值数目
	unsigned nowts = Time::GetGlobalTime();
	unsigned charge = GetChargeByTime(userWrap, nowts);

	//根据配置，判断充值条件是否满足
	if (charge < itemcfg.diamond())
	{
		error_log("charge not enough. uid=%u,index=%u,charge=%u", m_nUid, index, charge);
		throw runtime_error("charge_not_enough");
	}

	//是否已经领取该位置处的奖励
	if (m_jsonData["a"][index - 1].asUInt() > 0)
	{
		error_log("reward already been received. uid=%u,index=%u", m_nUid, index);
		throw runtime_error("reward_aleardy_received");
	}

	//发放奖励
	ProvideCommonReward(itemcfg.reward(), reason, result);

	m_jsonData["a"][index - 1] = 1;   //设置奖励领取状态

	Save();

	result["NewAct"] = m_jsonData;

	return 0;
}

IcePhoenixActivityUnix::IcePhoenixActivityUnix(const UserWrap& user):
		ChargeQuotaActivityBase(user.Id(), CONFIG_ICEPHOENIX, NAT_ICE_PHOENIX, item_max_index)
{

}

int IcePhoenixActivityUnix::GetChargeReward(UserWrap& userWrap, const UnitIndexCmdParams & param, Json::Value & result)
{
	//根据index，获取配置
	unsigned index = param.Index();

	const ConfigActivity::DiamondReward & itemcfg = ActivityConfigWrap().GetIcePhoenixItemcfg(index);

	Reward(userWrap, index, itemcfg, "IcePhoenix", result);

	return 0;
}

AutumnFeedbackActivityUnix::AutumnFeedbackActivityUnix(const UserWrap& user):
		ChargeQuotaActivityBase(user.Id(), CONFIG_AUTUMN_FEEDBACK, NAT_AUTUMN_FEEDBACK, item_max_index)
{

}

int AutumnFeedbackActivityUnix::GetChargeReward(UserWrap& userWrap, const UnitIndexCmdParams & param, Json::Value & result)
{
	//根据index，获取配置
	unsigned index = param.Index();

	const ConfigActivity::DiamondReward & itemcfg = ActivityConfigWrap().GetAutumnFeedbackItemcfg(index);

	Reward(userWrap, index, itemcfg, "AutumnFeedback", result);

	return 0;
}

ProtectFlagActivityUnix::ProtectFlagActivityUnix(const UserWrap& user):
		ChargeQuotaActivityBase(user.Id(), CONFIG_PROTECT_FLAG, NAT_PROTECT_FLAG, item_max_index)
{

}

int ProtectFlagActivityUnix::GetChargeReward(UserWrap& userWrap, const UnitIndexCmdParams & param, Json::Value & result)
{
	//根据index，获取配置
	unsigned index = param.Index();

	const ConfigActivity::DiamondReward & itemcfg = ActivityConfigWrap().GetProtectFlagItemcfg(index);

	Reward(userWrap, index, itemcfg, "ProtectFlag", result);

	return 0;
}


NewYearActivityUnix::NewYearActivityUnix(const UserWrap& user):
		BaseActivityUnit(user.Id(), CONFIG_NEWYEAR_GIFT)
{
	const ConfigActivity::NewYearActivity & cfg = ActivityConfigWrap().GetNewYearActivityCfg();
	itemsize_ = cfg.charge_reward_size();
	combinebuyitem_ = cfg.buy_items_size();

	sid_ = NAT_NEWYEARE_GIFT;
	CLogicSecinc logicSecinc;
	int ret = logicSecinc.GetSecinc(m_nUid, sid_, m_jsonData);

	need_save = false;

	if (R_ERR_NO_DATA == ret)
	{
		//初始化
		ResetAct();
	}
	else if (ret)
	{
		error_log("get newact error.uid=%u id=%d", m_nUid, sid_);
		throw std::runtime_error("get_new_active_data_error");
	}
}

int NewYearActivityUnix::ResetAct()
{
	if (!m_jsonData.isMember("a"))
	{
		Json::Value array(Json::arrayValue);

		m_jsonData["a"] = array;
	}
	for(int i = 0; i < itemsize_; ++i)
	{
		m_jsonData["a"][i] = 0;  //重置奖励领取状态
	}


	if (!m_jsonData.isMember("b"))
	{
		Json::Value array(Json::arrayValue);

		m_jsonData["b"] = array;
	}
	for(int i = 0; i < combinebuyitem_; ++i)
	{
		m_jsonData["b"][i] = 0;  //每种组合商店购买次数记录
	}

	m_jsonData["c"] = 0;  //在线30分钟领取记录
	m_jsonData["ts1"] = Time::GetGlobalTime();//在线30分钟领取奖励时间戳标记
	m_jsonData["ts2"] = Time::GetGlobalTime();//组合商店购买时间戳标记
	m_jsonData["v"] = GetVersion();  //版本号
	m_jsonData["id"] = NAT_NEWYEARE_GIFT;  //id

	need_save = true;

	return 0;

}

int NewYearActivityUnix::ResetAct(int reset_type)
{
	if(reset_charge_reward_tag == reset_type) {
		for(int i = 0; i < itemsize_; ++i)
		{
			m_jsonData["a"][i] = 0;  //重置奖励领取状态
		}
	} else if(reset_combine_shop_get_tag == reset_type) {
		for(int i = 0; i < combinebuyitem_; ++i)
		{
			m_jsonData["b"][i] = 0;  //每种组合商店购买次数记录
		}

	} else {
		m_jsonData["c"] = 0;  //每种组合商店购买次数记录
	}

	m_jsonData["v"] = GetVersion();  //版本号
	m_jsonData["id"] = NAT_NEWYEARE_GIFT;  //id

	need_save = true;

	return 0;
}

OpenServerActivityUnix::OpenServerActivityUnix(const UserWrap& user):
		BaseActivityUnit(user.Id(), CONFIG_OPENSERVER_GIFT)
{
	sid_ = NAT_OPENSERVER_GIFT;
	CLogicSecinc logicSecinc;
	int ret = logicSecinc.GetSecinc(m_nUid, sid_, m_jsonData);

	need_save = false;

	if (R_ERR_NO_DATA == ret)
	{
		//初始化
		ResetAct();
	}
	else if (ret)
	{
		error_log("get newact error.uid=%u id=%d", m_nUid, sid_);
		throw std::runtime_error("get_new_active_data_error");
	}
}

void OpenServerActivityUnix::ResetDiscountAct()
{
	for(int i = 0; i < 2; ++i)
	{
		m_jsonData["a"][i] = 0;  //折扣商店购买标记
	}
	need_save = true;
}
int OpenServerActivityUnix::ResetAct()
{
	if (!m_jsonData.isMember("a"))
	{
		Json::Value array(Json::arrayValue);

		m_jsonData["a"] = array;
	}
	for(int i = 0; i < 2; ++i)
	{
		m_jsonData["a"][i] = 0;  //折扣商店购买标记
	}


	if (!m_jsonData.isMember("b"))
	{
		Json::Value array(Json::arrayValue);

		m_jsonData["b"] = array;
	}
	for(int i = 0; i < achievement_item_max; ++i)
	{
		m_jsonData["b"][i] = 0;  //每种组合商店购买次数记录
	}

	m_jsonData["ts"] = Time::GetGlobalTime();//在线30分钟领取奖励时间戳标记
	m_jsonData["id"] = NAT_OPENSERVER_GIFT;  //id

	need_save = true;

	return 0;

}

SummerHolidaysActivityUnix::SummerHolidaysActivityUnix(const UserWrap& user):
		BaseActivityUnit(user.Id(), CONFIG_SUMMERREWARD_GIFT)
{
	const ConfigActivity::SummerHolidaysRewardCfg & cfg =  ActivityConfigWrap().GetSummerHolidaysRewardCfg();
	m_acc_chargeitemsize = cfg.chargereward_size();
	m_exchangeitemsize = cfg.summer_holidays_ticket_size();

	sid_ = NAT_SUMMERREWARD;
	CLogicSecinc logicSecinc;
	int ret = logicSecinc.GetSecinc(m_nUid, sid_, m_jsonData);

	need_save = false;

	if (R_ERR_NO_DATA == ret)
	{
		//初始化
		ResetAct();
	}
	else if (ret)
	{
		error_log("get newact error.uid=%u id=%d", m_nUid, sid_);
		throw std::runtime_error("get_new_active_data_error");
	}
}

int SummerHolidaysActivityUnix::ResetAct()
{
	if (!m_jsonData.isMember("a"))
	{
		Json::Value array(Json::arrayValue);

		m_jsonData["a"] = array;
	}
	for(int i = 0; i < m_acc_chargeitemsize; ++i)
	{
		m_jsonData["a"][i] = 0;  //重置奖励领取状态
	}
	if (!m_jsonData.isMember("b"))
	{
		Json::Value array(Json::arrayValue);

		m_jsonData["b"] = array;
	}
	for(int i = 0; i < m_exchangeitemsize; ++i)
	{
		m_jsonData["b"][i] = 0;  //重置兑换状态
	}
	m_jsonData["c"] = 0;  //使用了多少张兑换券

	m_jsonData["v"] = GetVersion();  //版本号
	m_jsonData["id"] = NAT_SUMMERREWARD;  //id

	need_save = true;

	return 0;
}

int SummerHolidaysActivityUnix::CheckItemSize(int flag)
{
	if(check_acc_item == flag) {
		int oldsize = m_jsonData["a"].size();
		if (oldsize < m_acc_chargeitemsize)
		{
			for(int i = oldsize; i < m_acc_chargeitemsize; ++i)
			{
				m_jsonData["a"][i] = 0;
			}
		}
	}else if(check_exhange_item == flag) {
		int oldsize = m_jsonData["b"].size();
		if (oldsize < m_exchangeitemsize)
		{
			for(int i = oldsize; i < m_exchangeitemsize; ++i)
			{
				m_jsonData["b"][i] = 0;
			}
		}
	}

	need_save = true;
	return 0;
}

int SummerHolidaysActivityUnix::GetChargeReward(UserWrap& userWrap, const UnitIndexCmdParams & param, Json::Value & result)
{
	//根据index，获取配置
	unsigned index = param.Index();

	const ConfigActivity::SummerHolidaysRewardCfg & cfg =  ActivityConfigWrap().GetSummerHolidaysRewardCfg();
	m_acc_chargeitemsize = cfg.chargereward_size();
	if (index < 0 || index >= m_acc_chargeitemsize)
	{
		error_log("param error. uid=%u,index=%u", m_nUid, index);
		throw runtime_error("param error");
	}
	const ConfigActivity::DiamondReward & itemcfg = cfg.chargereward(index);

	//判断版本是否发生变化
	CheckActVersion();

	//检查充值额度的档位数
	CheckItemSize(check_acc_item);

	//获取活动期间内的充值数目
	unsigned nowts = Time::GetGlobalTime();
	unsigned charge = GetChargeByTime(userWrap, nowts);

	//根据配置，判断充值条件是否满足
	if (charge < itemcfg.diamond())
	{
		error_log("charge not enough. uid=%u,index=%u,charge=%u", m_nUid, index, charge);
		throw runtime_error("charge_not_enough");
	}

	//是否已经领取该位置处的奖励
	if (m_jsonData["a"][index].asUInt() > 0)
	{
		error_log("reward already been received. uid=%u,index=%u", m_nUid, index);
		throw runtime_error("reward_aleardy_received");
	}

	//发放奖励
	ProvideCommonReward(itemcfg.reward(), "SummerHolidaysReward", result);

	m_jsonData["a"][index] = 1;   //设置奖励领取状态

	Save();

	result["NewAct"] = m_jsonData;

	return 0;
}

int SummerHolidaysActivityUnix::ExchangeItem(UserWrap& userWrap, const UnitIndexCmdParams & param, Json::Value & result)
{
	//根据index，获取配置
	unsigned index = param.Index();

	const ConfigActivity::SummerHolidaysRewardCfg & cfg =  ActivityConfigWrap().GetSummerHolidaysRewardCfg();
	m_exchangeitemsize = cfg.summer_holidays_ticket_size();
	if (index < 0 || index >= m_exchangeitemsize)
	{
		error_log("param error. uid=%u,index=%u", m_nUid, index);
		throw runtime_error("param error");
	}

	//---------校验
	//1.判断版本是否发生变化
	CheckActVersion();

	//2.检查充值额度的档位数
	CheckItemSize(check_exhange_item);

	//3.校验对应的档位是否已超过兑换次数
	unsigned used_exchange_cnt = m_jsonData["b"][index].asUInt();
	if(used_exchange_cnt >= cfg.summer_holidays_ticket(index).exchange_count_max())
	{
		throw runtime_error("exchange_count_is_maxed");
	}

	//4.校验兑换券是否已使用完
	//获取活动期间内的充值数目
	unsigned nowts = Time::GetGlobalTime();
	unsigned charge = GetChargeByTime(userWrap, nowts);

	//根据充值额度计算玩家拥有多少兑换券
	unsigned exchange_ticket = charge / cfg.per_ticket_need_diamond();
	exchange_ticket = (exchange_ticket > cfg.exchange_ticket_max()) ? cfg.exchange_ticket_max():exchange_ticket;

	unsigned used_exchange_ticket = m_jsonData["c"].asUInt();
	if(used_exchange_ticket >= exchange_ticket)
	{
		throw runtime_error("exchange_ticket_used_over");
	}

	//校验兑换券是否足够
	if(used_exchange_ticket + cfg.summer_holidays_ticket(index).need_cost_ticket() > exchange_ticket)
	{
		throw runtime_error("exchange_ticket_is_not_enough");
	}

	//-----------校验通过、做兑换处理
	//1.更新使用过的兑换券数量
	m_jsonData["c"] = m_jsonData["c"].asUInt() + cfg.summer_holidays_ticket(index).need_cost_ticket();
	//2.更新该档位对应的兑换次数
	m_jsonData["b"][index] = m_jsonData["b"][index].asUInt() + 1;
	//3.发放兑换奖励
	ProvideCommonReward(cfg.summer_holidays_ticket(index).reward(), "SummerHolidaysReward", result);

	Save();

	result["NewAct"] = m_jsonData;

	return 0;
}


SummerRewardActivityUnix::SummerRewardActivityUnix(const UserWrap& user):
		BaseActivityUnit(user.Id(), CONFIG_SUMMERCHAEGE_GIFT)
{
	const ConfigActivity::SummerChargeRewardCfg & cfg =  ActivityConfigWrap().GetSummerChargeRewardCfg();
	m_acc_chargeitemsize = cfg.acc_chargereward_size();
	m_daily_chargeitemsize = cfg.daily_chargereward_size();

	sid_ = NAT_SUMMERCHARGE;
	CLogicSecinc logicSecinc;
	int ret = logicSecinc.GetSecinc(m_nUid, sid_, m_jsonData);

	need_save = false;

	if (R_ERR_NO_DATA == ret)
	{
		//初始化
		ResetAct();
	}
	else if (ret)
	{
		error_log("get newact error.uid=%u id=%d", m_nUid, sid_);
		throw std::runtime_error("get_new_active_data_error");
	}
}

int SummerRewardActivityUnix::ResetAct()
{
	if (!m_jsonData.isMember("a"))
	{
		Json::Value array(Json::arrayValue);

		m_jsonData["a"] = array;
	}
	for(int i = 0; i < m_acc_chargeitemsize; ++i)
	{
		m_jsonData["a"][i] = 0;  //重置奖励领取状态
	}
	if (!m_jsonData.isMember("b"))
	{
		Json::Value array(Json::arrayValue);

		m_jsonData["b"] = array;
	}
	for(int i = 0; i < m_daily_chargeitemsize; ++i)
	{
		m_jsonData["b"][i] = 0;  //重置奖励领取状态
	}

	m_jsonData["c"] = 0;  //每日充值领取的ts
	m_jsonData["v"] = GetVersion();  //版本号
	m_jsonData["id"] = NAT_SUMMERCHARGE;  //id

	need_save = true;

	return 0;
}

int SummerRewardActivityUnix::CheckItemSize(int flag)
{
	if(check_acc_item == flag) {
		int oldsize = m_jsonData["a"].size();
		if (oldsize < m_acc_chargeitemsize)
		{
			for(int i = oldsize; i < m_acc_chargeitemsize; ++i)
			{
				m_jsonData["a"][i] = 0;
			}
		}
	}else if(check_daily_item == flag) {
		int oldsize = m_jsonData["b"].size();
		if (oldsize < m_daily_chargeitemsize)
		{
			for(int i = oldsize; i < m_daily_chargeitemsize; ++i)
			{
				m_jsonData["b"][i] = 0;
			}
		}
	}

	need_save = true;
	return 0;
}

int SummerRewardActivityUnix::GetSummerAccReward(UserWrap& userWrap, const UnitIndexCmdParams & param, Json::Value & result)
{
	//根据index，获取配置
	unsigned index = param.Index();

	const ConfigActivity::DiamondReward & itemcfg = ActivityConfigWrap().GetSummerAccChargeItemcfg(index);
	m_acc_chargeitemsize = ActivityConfigWrap().GetSummerChargeRewardCfg().acc_chargereward_size();

	if (index < 0 || index >= m_acc_chargeitemsize)
	{
		error_log("param error. uid=%u,index=%u", m_nUid, index);
		throw runtime_error("param error");
	}

	//判断版本是否发生变化
	CheckActVersion();

	//检查充值额度的档位数
	CheckItemSize(check_acc_item);

	//获取活动期间内的充值数目
	unsigned nowts = Time::GetGlobalTime();
	unsigned charge = GetChargeByTime(userWrap, nowts);

	//根据配置，判断充值条件是否满足
	if (charge < itemcfg.diamond())
	{
		error_log("charge not enough. uid=%u,index=%u,charge=%u", m_nUid, index, charge);
		throw runtime_error("charge_not_enough");
	}

	//是否已经领取该位置处的奖励
	if (m_jsonData["a"][index].asUInt() > 0)
	{
		error_log("reward already been received. uid=%u,index=%u", m_nUid, index);
		throw runtime_error("reward_aleardy_received");
	}

	//发放奖励
	ProvideCommonReward(itemcfg.reward(), "SummerAccChargeReward", result);

	m_jsonData["a"][index] = 1;   //设置奖励领取状态

	Save();

	result["NewAct"] = m_jsonData;

	return 0;
}

int SummerRewardActivityUnix::GetSummerDailyReward(UserWrap& userWrap, const UnitIndexCmdParams & param, Json::Value & result)
{
	//根据index，获取配置
	unsigned index = param.Index();

	const ConfigActivity::DiamondReward & itemcfg = ActivityConfigWrap().GetSummerDailyChargeItemcfg(index);
	m_daily_chargeitemsize = ActivityConfigWrap().GetSummerChargeRewardCfg().daily_chargereward_size();

	if (index < 0 || index >= m_daily_chargeitemsize)
	{
		error_log("param error. uid=%u,index=%u", m_nUid, index);
		throw runtime_error("param error");
	}

	//判断版本是否发生变化
	CheckActVersion();

	//检查充值额度的档位数
	CheckItemSize(check_daily_item);

	//根据每日领取的ts充值每日领取标记
	unsigned reward_ts = m_jsonData["c"].asUInt();
	if(!Time::IsToday(reward_ts))
	{
		for(int i = 0; i < m_daily_chargeitemsize; ++i)
		{
			m_jsonData["b"][i] = 0;  //重置奖励领取状态
		}
	}

	//获取活动期间内的充值数目
	unsigned start_ts = GetCurDateStartTs();
	unsigned nowts = Time::GetGlobalTime();
	unsigned charge = userWrap.GetRechargePoint(start_ts, nowts);

	//根据配置，判断充值条件是否满足
	if (charge < itemcfg.diamond())
	{
		error_log("charge not enough. uid=%u,index=%u,charge=%u", m_nUid, index, charge);
		throw runtime_error("charge_not_enough");
	}

	//是否已经领取该位置处的奖励
	if (m_jsonData["b"][index].asUInt() > 0)
	{
		error_log("reward already been received. uid=%u,index=%u", m_nUid, index);
		throw runtime_error("reward_aleardy_received");
	}

	//发放奖励
	ProvideCommonReward(itemcfg.reward(), "SummerDailyChargeReward", result);

	m_jsonData["b"][index] = 1;   //设置奖励领取状态
	m_jsonData["c"] = Time::GetGlobalTime();

	Save();

	result["NewAct"] = m_jsonData;

	return 0;
}

unsigned SummerRewardActivityUnix::GetCurDateStartTs()
{
	//获取当天凌晨ts
	unsigned cur_hour_ts = Time::GetGlobalTime();
	time_t nts = cur_hour_ts;
	struct tm ptm;
	if(localtime_r(&nts, &ptm) != NULL)
	{
		cur_hour_ts  -= ptm.tm_hour * 3600;
		cur_hour_ts  -= ptm.tm_min * 60;
		cur_hour_ts  -= ptm.tm_sec;
	}
	return cur_hour_ts;
}



BatmanTreasureActivityUnix::BatmanTreasureActivityUnix(const UserWrap& user):
		BaseActivityUnit(user.Id(), CONFIG_BATMANTREASURE_GIFT)
{
	const ConfigActivity::BatmanTreasureCfg & cfg =  ActivityConfigWrap().GetBatmanTreasureCfg();
	m_chargeitemsize = cfg.xiaobing_chargereward_size();

	sid_ = NAT_BATMANTREASURE;
	CLogicSecinc logicSecinc;
	int ret = logicSecinc.GetSecinc(m_nUid, sid_, m_jsonData);

	need_save = false;

	if (R_ERR_NO_DATA == ret)
	{
		//初始化
		ResetAct();
	}
	else if (ret)
	{
		error_log("get newact error.uid=%u id=%d", m_nUid, sid_);
		throw std::runtime_error("get_new_active_data_error");
	}
}

int BatmanTreasureActivityUnix::ResetAct()
{
	if (!m_jsonData.isMember("a"))
	{
		Json::Value array(Json::arrayValue);

		m_jsonData["a"] = array;
	}
	for(int i = 0; i < m_chargeitemsize; ++i)
	{
		m_jsonData["a"][i] = 0;  //重置奖励领取状态
	}
	m_jsonData["b"] = 0;

	m_jsonData["v"] = GetVersion();  //版本号
	m_jsonData["id"] = NAT_BATMANTREASURE;  //id

	need_save = true;

	return 0;
}

int BatmanTreasureActivityUnix::CheckItemSize()
{
	int oldsize = m_jsonData["a"].size();
	if (oldsize < m_chargeitemsize)
	{
		for(int i = oldsize; i < m_chargeitemsize; ++i)
		{
			m_jsonData["a"][i] = 0;
		}

		need_save = true;
	}
	return 0;
}

int BatmanTreasureActivityUnix::GetChargeReward(UserWrap& userWrap, const UnitIndexCmdParams & param, Json::Value & result)
{
	//根据index，获取配置
	unsigned index = param.Index();

	const ConfigActivity::DiamondReward & itemcfg = ActivityConfigWrap().GetBatmanTreasureChargeItemcfg(index);
	m_chargeitemsize = ActivityConfigWrap().GetBatmanTreasureCfg().xiaobing_chargereward_size();

	if (index < 0 || index >= m_chargeitemsize)
	{
		error_log("param error. uid=%u,index=%u", m_nUid, index);
		throw runtime_error("param error");
	}

	//判断版本是否发生变化
	CheckActVersion();

	//检查充值额度的档位数
	CheckItemSize();

	//获取活动期间内的充值数目
	unsigned nowts = Time::GetGlobalTime();
	unsigned charge = GetChargeByTime(userWrap, nowts);

	//根据配置，判断充值条件是否满足
	if (charge < itemcfg.diamond())
	{
		error_log("charge not enough. uid=%u,index=%u,charge=%u", m_nUid, index, charge);
		throw runtime_error("charge_not_enough");
	}

	//是否已经领取该位置处的奖励
	if (m_jsonData["a"][index].asUInt() > 0)
	{
		error_log("reward already been received. uid=%u,index=%u", m_nUid, index);
		throw runtime_error("reward_aleardy_received");
	}

	//发放奖励
	ProvideCommonReward(itemcfg.reward(), "BatmanTreasureChargeReward", result);

	m_jsonData["a"][index] = 1;   //设置奖励领取状态

	Save();

	result["NewAct"] = m_jsonData;

	return 0;
}

int BatmanTreasureActivityUnix::Draw(UserWrap& userWrap, const BaseCmdParams & param, Json::Value & result)
{
	//判断版本是否发生变化
	CheckActVersion();

	//获取活动期间内的充值数目
	unsigned nowts = Time::GetGlobalTime();
	unsigned charge = GetChargeByTime(userWrap, nowts);
	unsigned integral = charge;//一钻一积分

	//-------校验
	unsigned draw_cnt_max = ActivityConfigWrap().GetBatmanTreasureCfg().draw_cnt_max();
	unsigned draw_cost_integral = ActivityConfigWrap().GetBatmanTreasureCfg().draw_cost_integral();
	unsigned used_draw_cnt = m_jsonData["b"].asUInt();

	//---校验抽奖次数
	if(used_draw_cnt >= draw_cnt_max)
	{
		throw std::runtime_error("draw_cnt_is_max");
	}

	//校验积分是否足够
	if(used_draw_cnt * draw_cost_integral + draw_cost_integral > integral)
	{
		throw std::runtime_error("integral_is_not_enough");
	}

	//--------校验通过、按权重抽奖
	int target = 0;
	vector<unsigned>weights;
	weights.clear();
	for(int i = 0; i < ActivityConfigWrap().GetBatmanTreasureCfg().unique_xiaobing_dial_size(); i++)
	{
		weights.push_back(ActivityConfigWrap().GetBatmanTreasureCfg().unique_xiaobing_dial(i).weight());
	}

	TurnLuckTable(weights,weights.size(),target);

	//---------发放物品
	const RewardConfig::RewardItemCfg & itemcfg = ActivityConfigWrap().GetBatmanTreasureCfg().unique_xiaobing_dial(target).item();
	ProvideCommonReward(itemcfg, "BatmanTreasureChargeReward", result);

	//记录抽奖次数
	m_jsonData["b"] = m_jsonData["b"].asUInt() + 1;
	m_jsonData["pos"] = target;

	Save();

	result["NewAct"] = m_jsonData;
	return 0;
}

int BatmanTreasureActivityUnix::TurnLuckTable(vector<unsigned> & prates, int len, int & target)
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

	return 0;
}



RotaryTableActivityUnix::RotaryTableActivityUnix(const UserWrap& user):
		BaseActivityUnit(user.Id(), CONFIG_ROTARYTABLE_GIFT)
{
	const ConfigActivity::RotaryTableCrazyReward & cfg = ActivityConfigWrap().GetRotaryTableActivityCfg();
	m_chargeitemsize = cfg.chargereward_size();

	sid_ = NAT_ROTARYTABLE;
	CLogicSecinc logicSecinc;
	int ret = logicSecinc.GetSecinc(m_nUid, sid_, m_jsonData);

	need_save = false;

	if (R_ERR_NO_DATA == ret)
	{
		//初始化
		ResetAct();
	}
	else if (ret)
	{
		error_log("get newact error.uid=%u id=%d", m_nUid, sid_);
		throw std::runtime_error("get_new_active_data_error");
	}
}

int RotaryTableActivityUnix::ResetAct()
{
	if (!m_jsonData.isMember("a"))
	{
		Json::Value array(Json::arrayValue);

		m_jsonData["a"] = array;
	}
	for(int i = 0; i < m_chargeitemsize; ++i)
	{
		m_jsonData["a"][i] = 0;  //重置奖励领取状态
	}

	m_jsonData["v"] = GetVersion();  //版本号
	m_jsonData["id"] = NAT_ROTARYTABLE;  //id

	need_save = true;

	return 0;
}

int RotaryTableActivityUnix::CheckItemSize()
{
	int oldsize = m_jsonData["a"].size();
	if (oldsize < m_chargeitemsize)
	{
		for(int i = oldsize; i < m_chargeitemsize; ++i)
		{
			m_jsonData["a"][i] = 0;
		}

		need_save = true;
	}

	return 0;
}

int RotaryTableActivityUnix::GetChargeReward(UserWrap& userWrap, const UnitIndexCmdParams & param, Json::Value & result)
{
	//根据index，获取配置
	unsigned index = param.Index() + 1;

	const ConfigActivity::DiamondReward & itemcfg = ActivityConfigWrap().GetRotaryTableChargeItemcfg(index);
	m_chargeitemsize = ActivityConfigWrap().GetRotaryTableChargeCfgSize();

	if (index < 1 || index > m_chargeitemsize)
	{
		error_log("param error. uid=%u,index=%u", m_nUid, index);
		throw runtime_error("param error");
	}

	//判断版本是否发生变化
	CheckActVersion();

	//检查充值额度的档位数
	CheckItemSize();

	//获取活动期间内的充值数目
	unsigned nowts = Time::GetGlobalTime();
	unsigned charge = GetChargeByTime(userWrap, nowts);

	//根据配置，判断充值条件是否满足
	if (charge < itemcfg.diamond())
	{
		error_log("charge not enough. uid=%u,index=%u,charge=%u", m_nUid, index, charge);
		throw runtime_error("charge_not_enough");
	}

	//是否已经领取该位置处的奖励
	if (m_jsonData["a"][index - 1].asUInt() > 0)
	{
		error_log("reward already been received. uid=%u,index=%u", m_nUid, index);
		throw runtime_error("reward_aleardy_received");
	}

	//发放奖励
	ProvideCommonReward(itemcfg.reward(), "RotaryTableChargeReward", result);

	m_jsonData["a"][index - 1] = 1;   //设置奖励领取状态

	Save();

	result["NewAct"] = m_jsonData;

	return 0;
}

int RotaryTableActivityUnix::GetRandomReward(UserWrap& userWrap, const UnitIdCmdParams & param, Json::Value & result)
{
	//判断版本是否发生变化
	CheckActVersion();

	//跨服请求、获取随机奖励
	Json::Value tempdata;
	Json::Value data;
	string url = "action=RotaryTableDraw";
	data["uid"] = userWrap.Id();
	data["costItemUd"] = param.Id();
	data["version"] = GetVersion();
	if(GetEndTs() < Time::GetGlobalTime() || GetBeginTs() > Time::GetGlobalTime())
	{
		LOGIC_ERROR_RETURN_MSG("activity_over");
	}

	string datastr = Json::ToString(data);
	url.append("&data=").append(Crypt::UrlEncode(datastr));
	CLogicAllServerBaseMatch logicBaseMatch;
	int ret = logicBaseMatch.RequestBaseMatch(url,tempdata,CONFIG_ALLS_MATCH_SERVER_PATH,true);
	if(ret)
		return ret;
	if (tempdata.isMember("list"))
		result["list"] = tempdata["list"];
	else
		result["list"] = Json::Value(Json::arrayValue);
	return 0;
}

YearEndGiftActivityUnix::YearEndGiftActivityUnix(const UserWrap& user):
		ChargeQuotaActivityBase(user.Id(), CONFIG_YEAREND_GIFT, NAT_YEAREND_GIFT, item_max_index)
{

}

int YearEndGiftActivityUnix::CheckItemSize()
{
	int oldsize = m_jsonData["a"].size();

	if (oldsize < itemsize)
	{
		for(int i = oldsize; i < itemsize; ++i)
		{
			m_jsonData["a"][i] = 0;
		}

		need_save = true;
	}

	return 0;
}

int OpenServerActivityUnix::GetAchievementGift(UserWrap& userWrap, const BaseCmdParams & param, Json::Value & result)
{
	unsigned index_parent = param.ValueAsInt("index_p");
	unsigned index_child = param.ValueAsInt("index_c");

	unsigned int bitFlag = 1;
	bitFlag = bitFlag <<(index_child - 1);
	bool isReceive = false;//领取标记
	int Achievement = 0; //是否有指定的成就

	if(index_parent < achievement_item_min || index_parent > achievement_item_max) {
		error_log("param error. index_parent=%u", index_parent);
		throw runtime_error("param_error");
	}
	else{
		if(m_jsonData["b"][index_parent - 1].asUInt() & bitFlag)
			isReceive = true;
		else
			isReceive = false;
	}

	const ConfigActivity::KaiFuGift & cfg = ActivityConfigWrap().GetKaifuActivityCfg();
	const ConfigActivity::KaifuAchievement & itemcfg = cfg.achievement();

	if(isReceive) {
		error_log("already Receive");
		throw runtime_error("already Receive");
	} else {
		if(index_parent == jiangling_level_achievement) {
			Achievement = judgeLevel(itemcfg,userWrap,index_child);
			if(Achievement == 0) {
				const RewardConfig::RewardItemCfg& rewardcfg = itemcfg.soul_lv(index_child -1).reward();
				HandleAchievementGift(rewardcfg,index_parent,index_child,result);
			}
			else {
				error_log("no this achivement！");
				throw runtime_error("no this achivement！");
			}
		} else if(index_parent == jiangling_growth_achievement) {
			Achievement = judgeGrowth(itemcfg,userWrap,index_child);
			if(Achievement == 0) {
				const RewardConfig::RewardItemCfg& rewardcfg = itemcfg.soul_growth(index_child - 1).reward();
				HandleAchievementGift(rewardcfg,index_parent,index_child,result);
			}
			else {
				error_log("no this achivement！");
				throw runtime_error("no this achivement！");
			}

		} else if(index_parent == wuhun_achievement) {
			Achievement = judgeEternal(itemcfg,userWrap,index_child);
			if(Achievement == 0) {
				const RewardConfig::RewardItemCfg& rewardcfg = itemcfg.wuhun(index_child -1).reward();
				HandleAchievementGift(rewardcfg,index_parent,index_child,result);
			}
			else {
				error_log("no this achivement！");
				throw runtime_error("no this achivement！");
			}

		} else if(index_parent == juexue_achievement) {
			Achievement = judgeJueXue(itemcfg,userWrap,index_child);
			if(Achievement == 0) {
				const RewardConfig::RewardItemCfg& rewardcfg = itemcfg.juexue(index_child -1).reward();
				HandleAchievementGift(rewardcfg,index_parent,index_child,result);
			}
			else {
				error_log("no this achivement！");
				throw runtime_error("no this achivement！");
			}
		} else if(index_parent == shengxing_achievement) {
			Achievement = judgeShengXing(itemcfg,userWrap,index_child);
			if(Achievement == 0) {
				const RewardConfig::RewardItemCfg& rewardcfg = itemcfg.star(index_child -1).reward();
				HandleAchievementGift(rewardcfg,index_parent,index_child,result);
			}
			else {
				error_log("no this achivement！");
				throw runtime_error("no this achivement！");
			}
		} else if(index_parent == bingshu_achievement) {
			Achievement = judgeBingShu(itemcfg,userWrap,index_child);
			if(Achievement == 0) {
				const RewardConfig::RewardItemCfg& rewardcfg = itemcfg.heaven(index_child - 1).reward();
				HandleAchievementGift(rewardcfg,index_parent,index_child,result);
			}
			else {
				error_log("no this achivement！");
				throw runtime_error("no this achivement！");
			}

		} else if(index_parent == dunjia_achievement) {
			Achievement = judgeDunJia(itemcfg,userWrap,index_child);
			if(Achievement == 0) {
				const RewardConfig::RewardItemCfg& rewardcfg = itemcfg.daoist(index_child -1).reward();
				HandleAchievementGift(rewardcfg,index_parent,index_child,result);
			}
			else {
				error_log("no this achivement！");
				throw runtime_error("no this achivement！");
			}

		}
	}
	return 0;
}

int OpenServerActivityUnix::HandleAchievementGift(const RewardConfig::RewardItemCfg& itemCfg,int index_parent,int index_child,Json::Value & result)
{
	unsigned int bitFlag = 1;
	bitFlag = bitFlag <<(index_child - 1);
	string reason = "OpenServer_Gift";
	ProvideCommonReward(itemCfg, reason, result);

	m_jsonData["b"][index_parent - 1] = m_jsonData["b"][index_parent - 1].asUInt() + bitFlag;

	Save();
	result["NewAct"] = m_jsonData;
	return 0;
}

int OpenServerActivityUnix::judgeBingShu(const ConfigActivity::KaifuAchievement& itemcfg,UserWrap& userWrap, int index)
{
	Json::Value tech;
	userWrap.GetUserTech(tech);
	Json::Value heaven;
	int result = -1;
	if(tech.isMember("heaven")) {
		heaven = tech["heaven"];
		int level = heaven["lv"].asInt();

		int config_jie;
		int config_ceng;
		const ConfigActivity::MsgHeaven heaven_attr = itemcfg.heaven(index - 1);
		config_jie = heaven_attr.jie();
		config_ceng = heaven_attr.ceng();

		if(level >= (config_jie - 1 )*10 + config_ceng)
			result = 0;
	}
	return result;

}

int OpenServerActivityUnix::judgeDunJia(const ConfigActivity::KaifuAchievement& itemcfg,UserWrap& userWrap, int index)
{
	Json::Value tech;
	userWrap.GetUserTech(tech);
	Json::Value daoist;
	int result = -1;
	if(tech.isMember("daoist")) {
		daoist = tech["daoist"];
		int level = daoist["lv"].asInt();

		int config_jie;
		int config_ceng;
		const ConfigActivity::MsgDaoist daoist_attr = itemcfg.daoist(index - 1);
		config_jie = daoist_attr.jie();
		config_ceng = daoist_attr.ceng();

		if(level >= (config_jie - 1 )*10 + config_ceng)
			result = 0;
	}

	return result;
}

int OpenServerActivityUnix::judgeLevel(const ConfigActivity::KaifuAchievement& itemcfg,UserWrap& userWrap, int index)
{
	Json::Value tech;
	userWrap.GetUserTech(tech);
	unsigned soul = 0;
	Json::GetUInt(tech, "soul", soul);

	int result = -1;
	const ConfigActivity::MsgSoulLevel soul_lv= itemcfg.soul_lv(index - 1);
	int config_level = soul_lv.lv();

	unsigned level = 0;
	unsigned exp = SOUL_EXP * soul;
	for(int i=SOUL_LVL-1;i>=0;--i)
	{
		if(exp >= SOUL_LVL_EXP[i])
		{
			level = i + 1;
			break;
		}
	}

	if(level >= config_level)
		result = 0;
	return result;

}

int OpenServerActivityUnix::judgeGrowth(const ConfigActivity::KaifuAchievement& itemcfg,UserWrap& userWrap, int index)
{
	Json::Value tech;
	userWrap.GetUserTech(tech);
	int result = -1;

	unsigned sgrowth = 0;
	Json::GetUInt(tech, "sgrowth", sgrowth);
	sgrowth = sgrowth/10;

	const ConfigActivity::MsgSoulGrowth growth_lv= itemcfg.soul_growth(index - 1);
	int config_growth_lv = growth_lv.growth();

	if(sgrowth >= config_growth_lv)
		result = 0;
	return result;
}

int OpenServerActivityUnix::judgeEternal(const ConfigActivity::KaifuAchievement& itemcfg,UserWrap& userWrap, int index)
{
	Json::Value tech;
	userWrap.GetUserTech(tech);
	int result = -1;

	const ConfigActivity::MsgWuhun wuhun_attr= itemcfg.wuhun(index - 1);
	int config_partcount = wuhun_attr.partcount();
	int config_partlv = wuhun_attr.partlv();

	Json::Value jsonPart;
	Json::GetArray(tech, "part", jsonPart);
	int count = 0;
	for(int i = 0; i < jsonPart.size(); i++) {
		if(jsonPart[i].asInt() >= config_partlv)
			count++;
	}

	if(count >= config_partcount)
		result = 0;
	return result;
}

int OpenServerActivityUnix::judgeJueXue(const ConfigActivity::KaifuAchievement& itemcfg,UserWrap& userWrap, int index)
{
	int result = -1;

	CLogicHero logicHero;
	Json::Value data;
	logicHero.GetHero(userWrap.Id(), data);
	int config_quality;
	int config_count;

	const ConfigActivity::MsgJuexue juexue_attr = itemcfg.juexue(index - 1);
	config_quality = juexue_attr.quality();
	config_count = juexue_attr.count();

	for(int i = 0; i < data.size(); i++) {
		int hero_def = 0;
		Json::GetInt(data[i], "def", hero_def);
		if(hero_def == 1) {
			if(data[i].isMember("juexue") && data[i]["juexue"].isArray()) {
				if(data[i]["juexue"].size() >= 1) {

					int count = 0;
					for(int k = 0; k <  data[i]["juexue"].size(); k++) {
						int id = data[i]["juexue"][k]["id"].asInt();
						int value = id % 1000;
						if(value >= config_quality)
							count ++;
					}
					if(count >= config_count)
						result = 0;
					else {
						error_log("config_quality=%d,config_count=%d,count=%d",config_quality,config_count,count);
					}
				}
			}
			break;
		}
	}
	return result;
}

int OpenServerActivityUnix::judgeShengXing(const ConfigActivity::KaifuAchievement& itemcfg,UserWrap& userWrap, int index)
{
	int result = -1;

	CLogicHero logicHero;
	Json::Value data;
	logicHero.GetHero(userWrap.Id(), data);
	unsigned start_target;

	int config_star;
	int config_type;
	const ConfigActivity::MsgStar shengxing_attr = itemcfg.star(index - 1);
	config_star = shengxing_attr.star();
	config_type = shengxing_attr.type();

	for(int i = 0; i < data.size(); i++) {
		int hero_def = 0;
		Json::GetInt(data[i], "def", hero_def);
		if(hero_def == 1) {
			if(!Json::GetUInt(data[i],"star",start_target))
				start_target = 1;

			string str_heroId;
			unsigned heroId;
			XMLHero hero;

			if(!Json::GetString(data[i],"id",str_heroId))
			{
				error_log("[source hid or star error]");
				return R_ERR_DATA;
			}
			str_heroId = str_heroId.substr(1);
			heroId = CTrans::STOI(str_heroId);

			CDataXML *pDataXML = CDataXML::GetCDataXML();
			if(!pDataXML)
			{
				cout << "GetCDataXML fail" << endl;
				return R_ERR_DATA;
			}
			int ret = pDataXML->GetHero(heroId, hero);
			if(ret)
			{
				error_log("GetHero fail");
				return R_ERR_DATA;
			}
			int type = hero.type;

			if(type >= config_type && start_target >= config_star)
				result = 0;
			break;
		}
	}
	return result;
}


int OpenServerActivityUnix::HandleDiscountShopBuy(UserWrap& user,const ConfigActivity::KaifuDiscountShop & itemcfg,string reason,int index,Json::Value& result)
{
	int cost = itemcfg.p_price();
	if (R_SUCCESS != user.CostAsset(cost, 0, reason, result["cost"]))
	{
		error_log("Cost_diamond_error");
		return R_ERROR;
	}
	//发放奖励
	ProvideCommonReward(itemcfg.item(), reason, result);

	//设置奖励领取状态
	unsigned bit = 1;
	bit = bit<<(index -1);
	if(index > check_bit_max) {
		m_jsonData["a"][1] = m_jsonData["a"][1].asUInt() + bit;
	} else {
		m_jsonData["a"][0u] = m_jsonData["a"][0u].asUInt() + bit;
	}

	m_jsonData["ts"] = Time::GetGlobalTime();
	Save();
	result["NewAct"] = m_jsonData;
	return 0;
}


int OpenServerActivityUnix::GetDiscountShopGift(UserWrap& user, const UnitIndexCmdParams& params,  Json::Value& result)
{
	unsigned index = params.Index();
	const ConfigActivity::KaiFuGift & cfg = ActivityConfigWrap().GetKaifuActivityCfg();
	const ConfigActivity::KaifuDiscountShop & itemcfg = cfg.shop(index -1);

	string reason = "OpenServer_Gift";
	if(index < check_bit_min || index > 2*check_bit_max) {
		error_log("param error. index=%u", index);
		throw runtime_error("param_error");
	}
	if(!Time::IsToday(m_jsonData["ts"].asUInt())) {
		//处理 购买
		ResetDiscountAct();
		HandleDiscountShopBuy(user,itemcfg,reason,index,result);
	}else {
		unsigned int bitFlag = 1;
		bitFlag = bitFlag <<(index - 1);
		bool isReceive = false;//领取标记

		if(index > check_bit_max && index <= 2*check_bit_max) {
			if(m_jsonData["a"][1].asUInt() & bitFlag)
				isReceive = true;
			else
				isReceive = false;
		}
		else if(index >= check_bit_min && index <= check_bit_max) {
			if(m_jsonData["a"][0u].asUInt() & bitFlag)
				isReceive = true;
			else
				isReceive = false;
		}
		if(!isReceive) {
			// 处理折扣商店购买
			HandleDiscountShopBuy(user,itemcfg,reason,index,result);
		}else {
			error_log("already Receive");
			throw runtime_error("already Receive");
		}

	}
	return 0;
}

int NewYearActivityUnix::GetChargeReward(UserWrap& userWrap, const UnitIndexCmdParams & param, Json::Value & result)
{
	//根据index，获取配置
	unsigned index = param.Index();

	const ConfigActivity::NewYearActivity & cfg = ActivityConfigWrap().GetNewYearActivityCfg();
	const ConfigActivity::DiamondReward & itemcfg = cfg.charge_reward(index - 1);

	if (index < 1 || index > itemsize_)
	{
		error_log("param error. index=%u", index);
		throw runtime_error("param_error");
	}

	//判断版本是否发生变化
	CheckActVersion();

	//获取活动期间内的充值数目
	unsigned nowts = Time::GetGlobalTime();
	unsigned charge = GetChargeByTime(userWrap, nowts);

	//根据配置，判断充值条件是否满足
	if (charge < itemcfg.diamond())
	{
		error_log("charge not enough. uid=%u,index=%u,charge=%u", m_nUid, index, charge);
		throw runtime_error("charge_not_enough");
	}

	//是否已经领取该位置处的奖励
	if (m_jsonData["a"][index - 1].asUInt() > 0)
	{
		error_log("reward already been received. uid=%u,index=%u", m_nUid, index);
		throw runtime_error("reward_aleardy_received");
	}

	//发放奖励
	string reason = "NewYear_Gift";
	ProvideCommonReward(itemcfg.reward(), reason, result);

	m_jsonData["a"][index - 1] = 1;   //设置奖励领取状态

	Save();

	result["NewAct"] = m_jsonData;

	return 0;
}

int NewYearActivityUnix::BuyItemFromCombinedShop(UserWrap& user, const BaseCmdParams& params,  Json::Value& result)
{
	//根据index，获取配置
	unsigned index = params.ValueAsUInt("index");
	unsigned item_index [3];
	item_index[0] = params.ValueAsUInt("index_1");
	item_index[1] = params.ValueAsUInt("index_2");
	item_index[2] = params.ValueAsUInt("index_3");

	//check index
	if(index < 1 || index > combinebuyitem_)
	{
		error_log("param error. index=%u", index);
		throw runtime_error("param_error");
	}
	//check equip_index
	for(int i = 0; i < combinebuyitem_; i++)
	{
		if(item_index[i] < 1 || item_index[i] > combine_shop_per_item_cnt_max)
		{
			error_log("param error. item_index[%d]=%u", i,item_index[i]);
			throw runtime_error("param_error");
		}
	}

	//判断版本是否发生变化
	CheckActVersion();

	const ConfigActivity::NewYearActivity & cfg = ActivityConfigWrap().GetNewYearActivityCfg();
	const ConfigActivity::DiamondRewardLimit & itemcfg = cfg.buy_items(index - 1);
	unsigned int cost = itemcfg.diamond();//消耗的钻石
	int limit = itemcfg.limit();//限领次数

	if(!Time::IsToday(m_jsonData["ts2"].asUInt()))
	{
		ResetAct(reset_combine_shop_get_tag);//重置组合商店的领取记录标记
	}
	else
	{
		int nBuyCnt = m_jsonData["b"][index - 1].asUInt();
		if (nBuyCnt > limit)
		{
			throw std::runtime_error("get_limit_cnt");
		}
	}

	const RewardConfig::RewardItemCfg & itemcfgrwd = itemcfg.reward();

	string reason = "NewYear_Gift";
	vector<ItemAdd> equips_v;
	unsigned nowts = Time::GetGlobalTime();

	for(int i = 0; i < combine_shop_select_item_cnt_max; ++i)
	{
		const RewardConfig::EquipItem&  equipcfg = itemcfgrwd.equips(item_index[i] - 1);
		ItemAdd item(equipcfg.eqid(), equipcfg.c(), reason, equipcfg.ch(), equipcfg.q());

		/*
		if (equipcfg.has_ltime() && endts > nowts)
		{
			//限时道具
			item.ats = endts - nowts;
		}
		*/
		equips_v.push_back(item);
	}

	if (equips_v.size() > 0)
	{
		AddEquips(equips_v, result);
	}


	//发放奖励

	//ProvideCommonReward(itemcfg.reward(), reason, result);

	//扣钻石
	if (R_SUCCESS != user.CostAsset(cost, 0, reason, result["cost"]))
	{
		error_log("Cost_diamond_error");
		return R_ERROR;
	}

	m_jsonData["b"][index - 1] = m_jsonData["b"][index - 1].asUInt() + 1;   //设置奖励领取状态
	m_jsonData["ts2"] = Time::GetGlobalTime();
	Save();

	result["NewAct"] = m_jsonData;
	return 0;
}

int NewYearActivityUnix::GetOnlineReward(UserWrap& user, const BaseCmdParams& params,  Json::Value& result)
{

	//判断版本是否发生变化
	CheckActVersion();

	if(!Time::IsToday(m_jsonData["ts1"].asUInt()))
	{
		ResetAct(reset_day_reward_tag);//重置组合商店的领取记录标记
	}
	else
	{
		if(1 == m_jsonData["c"].asUInt()) {
			throw std::runtime_error("already_get_reward");
		}
	}

	const ConfigActivity::NewYearActivity & cfg = ActivityConfigWrap().GetNewYearActivityCfg();
	const RewardConfig::RewardItemCfg & itemcfg = cfg.online_reward();

	string reason = "NewYear_Gift";
	//发放奖励
	ProvideCommonReward(itemcfg, reason, result);

	m_jsonData["c"] = 1;   //设置领取状态
	m_jsonData["ts1"] = Time::GetGlobalTime();
	Save();

	result["NewAct"] = m_jsonData;

	return 0;
}




int YearEndGiftActivityUnix::GetChargeReward(UserWrap& userWrap, const UnitIndexCmdParams & param, Json::Value & result)
{
	//根据index，获取配置
	unsigned index = param.Index();

	const ConfigActivity::DiamondReward & itemcfg = ActivityConfigWrap().GetYearEndGiftItemcfg(index);
	itemsize = ActivityConfigWrap().GetYearEndGiftSize();

	Reward(userWrap, index, itemcfg, "YearEnd_Gift", result);

	return 0;
}

ProtectGoddessUnix::ProtectGoddessUnix(const UserWrap& user):
		BaseCmdUnit(user.Id())
{

}

int ProtectGoddessUnix::GetPointReward(UserWrap& userWrap, const UnitIdCmdParams & param, Json::Value & result)
{
	unsigned id = param.Id();

	if (id < 1 || id > MAX_REWARD_ITEM)
	{
		error_log("param error. uid=%u,id=%u", m_nUid, id);
		throw runtime_error("param_error");
	}

	Json::Value user_stat;
	userWrap.GetUserStats(user_stat);
	unsigned point = 0;
	Json::GetUInt(user_stat, "nsp", point);

	ProtectGoddessRewardItem * item = NULL;

	int ret = DataXmlPtr()->GetProtectGoddessRewardItem(id, &item);

	if (ret)
	{
		throw runtime_error("get_reward_item error");
	}

	//判断积分条件是否满足
	if (item->point > point)
	{
		error_log("point not enough. uid=%u,id=%u,point=%u", m_nUid, id, point);
		throw runtime_error("point_not_enough");
	}

	//判断奖励是否已经领取
	unsigned status = 0;
	Json::GetUInt(user_stat, "nsr", status);

	int pos = id - 1;

	if (!CheckPosIsZero(status, pos))
	{
		error_log("reward already got. uid=%u,id=%u", m_nUid, id);
		throw runtime_error("reward_already_got");
	}

	//发送奖励
	AddGiftEquips(item->items, item->itemnum, "ProtectGoddess", result);

	//设置奖励领取状态
	SetBitCurrent(status, pos);

	user_stat["nsr"] = status;
	userWrap.SetUserStats(user_stat);

	result["nsr"] = status;
	return 0;
}

KeyLuxuryGiftActivityUnit::KeyLuxuryGiftActivityUnit(const UserWrap& user):
		BaseActivityUnit(user.Id(), CONFIG_KEY_LUXURYGIFT)
{
	sid = NAT_KEYLUXURY_GIFT;

	CLogicSecinc logicSecinc;
	int ret = logicSecinc.GetSecinc(m_nUid, sid, m_jsonData);

	need_save = false;

	if (R_ERR_NO_DATA == ret)
	{
		//初始化
		ResetAct();
	}
	else if (ret)
	{
		error_log("get newact error.uid=%u id=%d", m_nUid, sid);
		throw std::runtime_error("get_new_active_data_error");
	}
}

int KeyLuxuryGiftActivityUnit::CheckItemSize()
{
	int size = ActivityConfigWrap().GetLuxuryItemSize();

	int oldsize = m_jsonData["a"].size();

	if (oldsize < size)
	{
		for(int i = oldsize; i < size; ++i)
		{
			m_jsonData["a"][i] = 0;
		}

		need_save = true;
	}

	return 0;
}

int KeyLuxuryGiftActivityUnit::ResetAct()
{
	if (!m_jsonData.isMember("a"))
	{
		Json::Value array(Json::arrayValue);

		m_jsonData["a"] = array;
	}

	int size = ActivityConfigWrap().GetLuxuryItemSize();

	for(int i = 0; i < size; ++i)
	{
		m_jsonData["a"][i] = 0;  //重置物品项兑换次数
	}

	m_jsonData["b"] = 0;  //已兑换密钥数

	m_jsonData["v"] = GetVersion();  //版本号
	m_jsonData["id"] = sid;  //id

	need_save = true;

	return 0;
}

int KeyLuxuryGiftActivityUnit::GetReward(UserWrap& userWrap, const UnitIndexCmdParams & param, Json::Value & result)
{
	unsigned index = param.Index();

	//判断版本是否发生变化
	CheckActVersion();

	//检查配置项的长度
	CheckItemSize();

	//判断兑换次数是否达到上限
	ActivityConfigWrap activitywrap;
	const ConfigActivity::StuffItem & itemcfg = activitywrap.GetLuxuryGiftItem(index);

	int pos = index - 1;

	if (itemcfg.limit() > 0 && m_jsonData["a"][pos] >= itemcfg.limit())
	{
		error_log("exchange times already max. uid=%u,index=%u", m_nUid, index);
		throw runtime_error("times_already_max");
	}

	//获取充值数目
	unsigned nowts = Time::GetGlobalTime();
	unsigned charge = GetChargeByTime(userWrap, nowts);

	unsigned keynum = activitywrap.GetKeyNum(charge);

	if (m_jsonData["b"].asUInt() + itemcfg.costkey() > keynum)
	{
		error_log("key not enough. uid=%u,index=%u", m_nUid, index);
		throw runtime_error("key_not_enough");
	}

	//发奖励
	ProvideCommonReward(itemcfg.reward(), "KeyLuxuryGift", result);

	m_jsonData["b"] = m_jsonData["b"].asUInt() + itemcfg.costkey();
	m_jsonData["a"][pos] = m_jsonData["a"][pos].asUInt() + 1;

	Save();

	result["NewAct"] = m_jsonData;

	return 0;
}

SoldierSpiritUnit::SoldierSpiritUnit(const UserWrap& user):
		BaseCmdUnit(user.Id())
{

}

int SoldierSpiritUnit::Inject(UserWrap& userWrap, const UnitUdCmdParams & param, Json::Value & result)
{
	Json::Value user_tech;
	userWrap.GetUserTech(user_tech);

	//判断科技是否有当前字段
	if (!user_tech.isMember("soldier_spirit"))
	{
		user_tech["soldier_spirit"] = 0;
	}

	//判断兵魂等级是否最大
	if (user_tech["soldier_spirit"].asUInt() >= soldier_spirit_maxlevel)
	{
		error_log("soldier spirit level is max. uid=%u", m_nUid);
		throw runtime_error("level_already_max");
	}

	//消耗道具
	unsigned ud = param.Ud();

	CLogicEquipment logicEquipMent;
	int ret = logicEquipMent.UseEquipment(m_nUid, soldier_spirit_eqid, ud, 1, "soldier_spirit_inject");

	if (ret)
	{
		throw runtime_error("use_equip_error");
	}

	//升级
	user_tech["soldier_spirit"] = user_tech["soldier_spirit"].asUInt() + 1;

	userWrap.SetUserTech(user_tech);

	result["soldier_spirit"] = user_tech["soldier_spirit"];

	return 0;
}

EnjoySmallGiftActivityUnit::EnjoySmallGiftActivityUnit(const UserWrap& user):
		BaseActivityUnit(user.Id(), CONFIG_ENJOY_SMALLGIFT, NAT_ENJOY_SMALLGIFT)
{
	CLogicSecinc logicSecinc;
	int ret = logicSecinc.GetSecinc(m_nUid, sid_, m_jsonData);

	need_save = false;

	if (R_ERR_NO_DATA == ret)
	{
		//初始化
		ResetAct();
	}
	else if (ret)
	{
		error_log("get newact error.uid=%u id=%d", m_nUid, sid_);
		throw std::runtime_error("get_new_active_data_error");
	}
}

int EnjoySmallGiftActivityUnit::CheckItemSize()
{
	//处理充值额度奖励状态
	int chargesize = ActivityConfigWrap().GetChargeCfgItemSize();

	int oldsize = m_jsonData["a"].size();

	if (oldsize < chargesize)
	{
		for(int i = oldsize; i < chargesize; ++i)
		{
			m_jsonData["a"][i] = 0;
		}

		need_save = true;
	}

	//处理消费额度奖励状态
	int consumesize = ActivityConfigWrap().GetConsumeCfgItemSize();

	int oldb_size = m_jsonData["b"].size();

	if (oldb_size < consumesize)
	{
		for(int i = oldb_size; i < consumesize; ++i)
		{
			m_jsonData["b"][i] = 0;
		}

		need_save = true;
	}

	return 0;
}

int EnjoySmallGiftActivityUnit::ResetAct()
{
	//处理充值额度奖励领取状态
	if (!m_jsonData.isMember("a"))
	{
		Json::Value array(Json::arrayValue);

		m_jsonData["a"] = array;
	}

	int chargesize = ActivityConfigWrap().GetChargeCfgItemSize();

	for(int i = 0; i < chargesize; ++i)
	{
		m_jsonData["a"][i] = 0;  //重置充值额度奖励领取状态
	}

	//处理消费额度奖励领取状态
	if (!m_jsonData.isMember("b"))
	{
		Json::Value array(Json::arrayValue);

		m_jsonData["b"] = array;
	}

	int consumesize = ActivityConfigWrap().GetConsumeCfgItemSize();

	for(int i = 0; i < consumesize; ++i)
	{
		m_jsonData["b"][i] = 0;  //重置消费额度奖励领取状态
	}

	m_jsonData["t"] = Time::GetGlobalTime();  //重置奖励的时间
	m_jsonData["v"] = GetVersion();  //版本号
	m_jsonData["id"] = sid_;  //id

	need_save = true;

	return 0;
}

int EnjoySmallGiftActivityUnit::GetReward(UserWrap& userWrap, const GiftParam & param, Json::Value & result)
{
	//判断版本是否发生变化
	CheckActVersion();

	//检查配置项的长度
	CheckItemSize();

	//检查是否跨天
	if (CTime::GetDayInterval(m_jsonData["t"].asUInt(), Time::GetGlobalTime()) > 0)
	{
		//跨天，则重置活动数据
		ResetAct();
	}

	unsigned type = param.Type();
	unsigned index = param.Index();

	if (type != reward_type_charge && type != reward_type_consume)
	{
		error_log("param error. uid=%u,type=%u", m_nUid, type);
		throw runtime_error("param_error");
	}

	int pos = index - 1;

	if (type == reward_type_charge)
	{
		//获取充值数目
		unsigned nowts = Time::GetGlobalTime();
		unsigned charge = userWrap.GetSingleDayRecharge(nowts);  //获取当日充值数

		const ConfigActivity::DiamondReward & chargecfg = ActivityConfigWrap().GetChargeItemCfg(index);

		if (charge < chargecfg.diamond())
		{
			error_log("charge not enough. uid=%u,index=%u", m_nUid, index);
			throw runtime_error("charge_not_enough");
		}

		//判断奖励是否已经领取
		if (m_jsonData["a"][pos].asUInt() > 0)
		{
			error_log("charge reward already gotten. uid=%u,index=%u", m_nUid, index);
			throw runtime_error("reward_already_gotten");
		}

		//发奖励
		ProvideCommonReward(chargecfg.reward(), "EnjoySmallGift_Charge", result);

		//设置奖励领取状态
		m_jsonData["a"][pos] = 1;
	}
	else
	{
		unsigned nowts = Time::GetGlobalTime();
		unsigned costcash = userWrap.GetSingleDayConsume(nowts);  //当日消费钻石数

		const ConfigActivity::ConsumeGiftItem & consumecfg = ActivityConfigWrap().GetConsumeItemCfg(index);

		if (costcash < consumecfg.consume())
		{
			error_log("consume not enough. uid=%u,index=%u", m_nUid, index);
			throw runtime_error("consume_not_enough");
		}

		//判断奖励是否已经领取
		if (m_jsonData["b"][pos].asUInt() > 0)
		{
			error_log("consume reward already gotten. uid=%u,index=%u", m_nUid, index);
			throw runtime_error("reward_already_gotten");
		}

		//发奖励
		ProvideCommonReward(consumecfg.reward(), "EnjoySmallGift_Consume", result);

		//设置奖励领取状态
		m_jsonData["b"][pos] = 1;
	}

	Save();

	result["NewAct"] = m_jsonData;

	return 0;
}

LuckyGiftActivityUnit::LuckyGiftActivityUnit(const UserWrap& user):
		BaseActivityUnit(user.Id(), CONFIG_LUCKY_GIFT, NAT_LUCKY_GIFT)
{
	CLogicSecinc logicSecinc;
	int ret = logicSecinc.GetSecinc(m_nUid, sid_, m_jsonData);

	need_save = false;

	if (R_ERR_NO_DATA == ret)
	{
		//初始化
		ResetAct();
	}
	else if (ret)
	{
		error_log("get newact error.uid=%u id=%d", m_nUid, sid_);
		throw std::runtime_error("get_new_active_data_error");
	}
}

int LuckyGiftActivityUnit::ResetAct()
{
	m_jsonData["a"] = 0; //重置已使用的积分数目

	m_jsonData["v"] = GetVersion();  //版本号
	m_jsonData["id"] = sid_;  //id

	need_save = true;

	return 0;
}

int LuckyGiftActivityUnit::TurnTable(UserWrap& userWrap,  const BaseCmdParams & param, Json::Value & result)
{
	//判断版本是否发生变化
	CheckActVersion();

	unsigned type = param.ValueAsUInt("type");
	unsigned times = param.ValueAsUInt("times");

	if (type != turn_type_key && type != turn_type_point)
	{
		error_log("param error.uid=%u,type=%u", m_nUid, type);
		throw std::runtime_error("param_error");
	}

	const ConfigActivity::LuckyGift &  luckygiftcfg = ActivityConfigWrap().GetLuckyGiftCfg();

	if (turn_type_key == type)
	{
		//扣除材料
		unsigned ud = param.ValueAsUInt("ud");
		unsigned num = times * luckygiftcfg.keycost();
		CLogicEquipment logicEquipMent;

		int ret = logicEquipMent.UseEquipment(m_nUid, purple_key, ud, num, "LuckyGift");

		if (ret)
		{
			throw std::runtime_error("use_equip_error");
		}
	}
	else
	{
		//扣除充值积分
		unsigned needcost = times * luckygiftcfg.pointcost();
		unsigned nowts = Time::GetGlobalTime();
		unsigned charge = GetChargeByTime(userWrap, nowts);  //获取活动时间内的充值数目

		if (m_jsonData["a"].asUInt() + needcost > charge)
		{
			error_log("point not enough.uid=%u,charge=%u,cost=%u", m_nUid, charge, needcost);
			throw std::runtime_error("point_not_enough");
		}

		m_jsonData["a"] = m_jsonData["a"].asUInt() + needcost;
	}

	Json::Value turnresult(Json::arrayValue);

	//转动
	for(int i = 0; i < times; ++i)
	{
		TurnImpl(luckygiftcfg, turnresult);
	}

	Save();

	result["NewAct"] = m_jsonData;
	result["lucky"] = turnresult;

	return 0;
}

int LuckyGiftActivityUnit::TurnImpl(const ConfigActivity::LuckyGift & luckygiftcfg, Json::Value & subresult)
{
	//从配置的每个子库中挑选出一个物品
	vector<unsigned> weights;

	for(int i = 0; i < luckygiftcfg.stuff_items_size(); ++i)
	{
		Json::Value tempresult;
		weights.clear();

		for(int j = 0; j < luckygiftcfg.stuff_items(i).items_size(); ++j)
		{
			weights.push_back(luckygiftcfg.stuff_items(i).items(j).weight());
		}

		int target = 0;
		TurnVecLuckTable(weights, weights.size(), target);

		ProvideCommonReward(luckygiftcfg.stuff_items(i).items(target).reward(), "LuckyGift", tempresult);
		subresult.append(tempresult);
	}

	return 0;
}

/*
BlackEnhanceActivityUnit::BlackEnhanceActivityUnit(const UserWrap& user):
		BaseActivityUnit(user.Id(), CONFIG_BLACK_ENHANCE)
{
	CLogicSecinc logicSecinc;
	int ret = logicSecinc.GetSecinc(m_nUid, NAT_BLACK_GOLD_ENHANCE, m_jsonData);
	need_save = false;

	if (R_ERR_NO_DATA == ret)
	{
		//初始化黑金强化
		ResetAct();
	}
	else if (ret)
	{
		error_log("get newact error.uid=%u id=%d", m_nUid, NAT_BLACK_GOLD_ENHANCE);
		throw std::runtime_error("get_new_active_data_error");
	}
}

int BlackEnhanceActivityUnit::LuckyStoneExchange(UserWrap& userWrap, const EnhanceParam & param, Json::Value & result)
{
	//判断版本是否发生变化
	CheckActVersion();

	unsigned heroud = param.Ud();
	unsigned index = param.Index();

	//根据index获取配置
	const ConfigActivity::BlackGoldEnhance & enhance = ActivityConfigWrap().GetBlackGoldEnhanceCfg(index);

	//判断充值金额是否足够
	unsigned nowts = Time::GetGlobalTime();
	unsigned charge = GetChargeByTime(userWrap, nowts);

	//获取已兑换次数
	int used_times = m_jsonData["a"][index - 1].asInt();

	//先判断是否有可用次数
	if (enhance.limit() != 0 && used_times >= enhance.limit())
	{
		error_log("times used out. uid=%u,heroud=%u", m_nUid, heroud);
		throw runtime_error("times_used_out");
	}

	//判断积分是否足够
	int cost = 0;
	int curtimes = used_times + 1;   //当前次数，包含本次

	if (enhance.start() == 0 || curtimes < enhance.start())
	{
		cost =  enhance.first();
	}
	else
	{
		cost = enhance.first() + (curtimes - enhance.start() + 1) * enhance.accumulate();
	}

	if (charge < (cost + m_jsonData["b"].asUInt()))
	{
		error_log("charge not enough. uid=%u, charge=%u", m_nUid, charge);
		throw runtime_error("charge_not_enough");
	}

	//判断装备强化等级数目是否符合条件
	//获取等级和数量的条件
	unsigned cond_level = enhance.condition(1u);
	unsigned cond_num = enhance.condition(2u);

	if (0 != cond_num || 0 != cond_level)
	{
		//判断英雄身上的装备条件
		bool isok = CheckHeroEquips(heroud, cond_num, cond_level);

		if (!isok)
		{
			throw runtime_error("condition_not_match");
		}
	}

	//发放装备
	unsigned endts = GetEndTs();
	ProvideCommonReward(enhance.reward(), "BlackGold_Enhance", result, endts);

	//加上消耗的积分以及次数
	 m_jsonData["a"][index - 1] = curtimes;
	 m_jsonData["b"] = cost + m_jsonData["b"].asUInt();

	Save();

	result["NewAct"] = m_jsonData;

	return 0;
}

bool BlackEnhanceActivityUnit::CheckHeroEquips(unsigned heroud, unsigned cond_num, unsigned cond_level)
{
	CLogicHero logichero;

	Json::Value herodata;

	int ret = logichero.Get(m_nUid, heroud, herodata);

	if (ret)
	{
		error_log("get hero data error. uid=%u,heroud=%u", m_nUid, heroud);
		throw runtime_error("get_herodata_error");
	}

	char key[10] = {0};
	vector<unsigned> equips;

	for(int i = 1; i <= 10; ++i)
	{
		sprintf(key, "e%d", i);

		if (!herodata["heq"].isMember(key))
		{
			break;
		}

		equips.push_back(herodata["heq"][key].asUInt());
	}

	unsigned num = 0;

	if (equips.size() >= cond_num)
	{
		//数量有要求，至少装备的数量要满足条件
		CLogicEquipment logicequip;

		for(int i = 0; i < equips.size(); ++i)
		{
			//获取装备数据
			Json::Value equipdata;

			ret = logicequip.Get(m_nUid, equips[i], equipdata);

			if (ret)
			{
				continue;
			}

			if (!equipdata.isMember("q"))
			{
				continue;
			}

			if (equipdata["q"].asUInt() >= cond_level)
			{
				++num;
			}
		}

		if (num >= cond_num)
		{
			return true;
		}
	}

	error_log("match level equip not enough. uid=%u,heroud=%u, num=%u", m_nUid, heroud, num);

	return false;
}

int BlackEnhanceActivityUnit::ResetAct()
{
	if (!m_jsonData.isMember("a"))
	{
		Json::Value array(Json::arrayValue);

		m_jsonData["a"] = array;
	}

	for(int i = 0; i < item_max_index; ++i)
	{
		m_jsonData["a"][i] = 0;  //重置兑换次数
	}

	m_jsonData["b"] = 0; //已使用积分
	m_jsonData["v"] = GetVersion();  //版本号
	m_jsonData["id"] = NAT_BLACK_GOLD_ENHANCE;  //id

	need_save = true;

	return 0;
}
*/
