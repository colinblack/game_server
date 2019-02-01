#include "LogicCMD.h"
#include <climits>

ConvertToBackendUnit::ConvertToBackendUnit(const UserWrap& user):
		BaseCmdUnit(user.Id())
{

}

int ConvertToBackendUnit::RecoverEnergyByTime(UserWrap& userWrap, const BaseCmdParams & param, Json::Value & result)
{
	//获取user_stat
	Json::Value user_stat;
	userWrap.GetUserStats(user_stat);

	unsigned nowts = Time::GetGlobalTime();

	if (!user_stat.isMember("lget"))
	{
		user_stat["lget"] = nowts - energy_interval;
	}

	//计算当前的时间差是否大于30min
	if (nowts < user_stat["lget"].asUInt())
	{
		error_log("time error. uid=%u", m_nUid);
		return 0;
	}

	unsigned times = (nowts - user_stat["lget"].asUInt())/1800; //计算次数

	if (times == 0)
	{
		//时间还没到
		result["diffts"] = energy_interval - nowts + user_stat["lget"].asUInt(); //距离半小时到时还有多久
		return 0;
	}

	unsigned buy = userWrap.GetEnergyBuy() ;
	unsigned base = userWrap.GetEnergyBase() ;

	//判断能量是否已到上限
	if(buy + base>= energy_limit)
	{
		error_log("energy beyond max. uid=%u", m_nUid);
		throw runtime_error("energy_beyond_max");
	}

	//计算能够增加的能量值
	unsigned add = min(time_energy_add*times, energy_limit - buy - base);
	userWrap.AddEnergyBase(add, "TimeRecover", result);
	user_stat["lget"] = nowts;

	userWrap.SetUserStats(user_stat);
	result["lget"] = nowts;

	return 0;
}

int ConvertToBackendUnit::RecoveryByInviteFriends(UserWrap& userWrap, const BaseCmdParams & param, Json::Value & result)
{
	//获取user_stat
	Json::Value user_stat;
	userWrap.GetUserStats(user_stat);

	unsigned nowts = Time::GetGlobalTime();

	if (!user_stat.isMember("dgt"))
	{
		Json::Value dgtval(Json::arrayValue);
		dgtval.resize(2);
		dgtval[0u] = 0;
		dgtval[1u] = 1;
	}

	//判断是否已加过能量
	if (user_stat["dgt"][1u].asUInt() == 0)
	{
		error_log("energy already added. uid=%u", m_nUid);
		throw runtime_error("energy_already_added");
	}

	//增加能量
	userWrap.AddEnergyBase(invite_energy_add, "InviteRecover", result);

	//设置能量领取状态
	user_stat["dgt"][1u] = 0;
	userWrap.SetUserStats(user_stat);

	result["dgt"] = user_stat["dgt"];

	return 0;
}

int ConvertToBackendUnit::BuyEnergy(UserWrap& userWrap, const BaseCmdParams & param, Json::Value & result)
{
	//钻石价格与购买次数相关
	int cash_times[max_buy_times] = {20, 20, 40, 40, 60};

	//获取user_stat
	Json::Value user_stat;
	userWrap.GetUserStats(user_stat);

	unsigned nowts = Time::GetGlobalTime();

	if (!user_stat.isMember("hbe"))
	{
		user_stat["hbe"] = 0;
	}

	unsigned buytimes = user_stat["hbe"].asUInt() ;

	if (buytimes >= max_buy_times)
	{
		error_log("buy times already max. uid=%u", m_nUid);
		throw runtime_error("max_buy_times");
	}

	//购买能量，先扣钻
	userWrap.CostAsset(cash_times[buytimes], 0, "BuyEnergy", result);

	//增加能量
	userWrap.AddEnergyBuy(energy_add, "BuyEnergy", result);

	user_stat["hbe"] = buytimes + 1;  //更新当日购买次数

	userWrap.SetUserStats(user_stat);
	result["hbe"] = user_stat["hbe"].asUInt();

	return 0;
}

int ConvertToBackendUnit::OpenEnergyBag(UserWrap& userWrap, const BaseCmdParams & param, Json::Value & result)
{
	//参数检查
	const Json::Value & dataparam = param.ParamsObj();

	if (!dataparam.isMember("uds") || !dataparam["uds"].isArray())
	{
		error_log("param error. uds not exist or not array. uid=%u", m_nUid);
		throw runtime_error("param_error");
	}

	int ret = 0;
	CLogicEquipment logicequip;
	int sum = 0;

	for(int i = 0; i < dataparam["uds"].size(); ++i)
	{
		unsigned ud = dataparam["uds"][i]["ud"].asUInt();
		unsigned count = dataparam["uds"][i]["count"].asUInt();

		Json::Value dataequip;
		//根据ud获取equip信息
		ret = logicequip.Get(m_nUid, ud, dataequip);

		if (ret)
		{
			break;
		}

		//判断id是否是能量包的id
		int energy = 0;
		unsigned eqid = dataequip["id"].asUInt();

		switch(eqid)
		{
			case equip_energy_bag_1: energy = 10; break;  //能量包1增加10点能量
			case equip_energy_bag_2: energy = 50; break;  //能量包2增加50点能量
			default:break;
		}

		if (0 == energy)
		{
			error_log("wrong equip. not energy bag. uid=%u,ud=%u,eqid=%u", m_nUid, ud, eqid);
			break;
		}

		//消耗装备
		ret = logicequip.UseEquipment(m_nUid, eqid, ud, count, "OpenEnergyBag");

		if (ret)
		{
			break;
		}

		//增加能量
		sum  += count * energy;  //乘以消耗的能量包个数
	}

	userWrap.AddEnergyBase(sum, "OpenEnergyBag", result);

	return 0;
}

int ConvertToBackendUnit::GainResource(UserWrap& userWrap, const BaseCmdParams & param, Json::Value & result)
{
	//参数检查
	const Json::Value & dataparam = param.ParamsObj();

	if (!dataparam.isMember("bids") || !dataparam["bids"].isArray())
	{
		error_log("param error. bids not exist or not array. uid=%u", m_nUid);
		throw runtime_error("param_error");
	}

	unsigned fcm = 0;
	Json::GetUInt(dataparam,"fcm",fcm);
	if(fcm >= e_fcm_max)
		return R_ERR_PARAM;

	CLogicBuilding logicbuild;
	int ret = 0;
	CDataXML* pdataxml = DataXmlPtr();
	unsigned nowts = Time::GetGlobalTime();
	map<unsigned, unsigned> resourcemax;
	map<unsigned, unsigned> resource;

	userWrap.GetResourceMax(resourcemax);
	int addres[4] = {0};

	for(int i = 0; i < dataparam["bids"].size(); ++i)
	{
		unsigned id = dataparam["bids"][i].asUInt();

		Json::Value builddata;
		ret = logicbuild.Get(m_nUid, id, 0, true, builddata);

		if (ret)
		{
			error_log("get build error. uid=%u,id=%u", m_nUid, id);
			throw runtime_error("get_build_error");
		}

		int type = builddata["t"].asInt();
		//检查是否是资源装备
		if (!IsResourceBuild(type))
		{
			error_log("build type error. uid=%u,id=%u", m_nUid, id);
			throw runtime_error("build_type_error");
		}

		//读取配置
		XMLBuildingItem builditemcfg;
		ret = pdataxml->GetBuilding(type, builddata["l"].asUInt(), builditemcfg);

		if (ret)
		{
			error_log("get build config error. uid=%u,id=%u", m_nUid, id);
			throw runtime_error("get_build_config_error");
		}

		//每秒产量
		double rate = builditemcfg.produce / static_cast<double>(600);

		//bkts应为上次收获的时间
		unsigned bkts = builddata["bkts"].asUInt();  //bkts不存在时，取0
		unsigned diff_ts = nowts > bkts ? nowts - bkts : 0;  //距离上次收获，N个10分钟
		unsigned interval = diff_ts / resource_gain_interval;  //后端的时间间隔次数
		unsigned leftts = diff_ts - (interval*resource_gain_interval);  //没达到收获时间间隔的秒数

		unsigned front_diff_ts = nowts > builddata["upts"].asUInt() ? nowts - builddata["upts"].asUInt() : 0;  //每10分钟计算一次
		unsigned front_interval = front_diff_ts/resource_gain_interval;  //前端的时间间隔次数

		//用户能够容纳的最大数
		int restype = GetResourceTye(type);
		userWrap.GetResource(resource);

		unsigned left = resourcemax[restype] > resource[restype] ? resourcemax[restype] - resource[restype] : 0;

		unsigned front_yield = front_interval * builditemcfg.produce;  //计算前端产量.实际上，前端的总产量 = st+前端时间差内的产量.防止外挂修改st
		front_yield = min(builddata["st"].asUInt() + front_yield, (unsigned)builditemcfg.capacity);  //前端的应有产量
		unsigned back_yield = interval * builditemcfg.produce;  //计算后端产量
		back_yield = min(back_yield, (unsigned)builditemcfg.capacity);  //产量上限

		unsigned real_product = min(front_yield, back_yield); //实际上应该有的产量，考虑了资源被掠夺

		//存在掠夺，所以前端的值可能较小
		unsigned save = min(left, real_product);

		memset(addres, 0, sizeof(addres));
		addres[restype - 1] = save;

		for(int i=0;i<4;i++)
			addres[i] = (int)(addres[i] * FCM_VALUE[fcm]);

		userWrap.AddResource(addres[0], addres[1], addres[2], addres[3], "GainResource", result);

		//更新时间戳
		builddata["st"] = real_product - save;
		builddata["upts"] = nowts;
		builddata["bkts"] = nowts - (unsigned)((real_product - save) / rate) - leftts;  //要减去没达到时间间隔的秒数，不然那部分时间的资源就会被丢弃

		//存档
		ret = logicbuild.Chg(m_nUid, id, 0, true, builddata);

		if (ret)
		{
			error_log("update build error. uid=%u,id=%u", m_nUid, id);
			throw runtime_error("update_build_error");
		}

		if (!result.isMember("builds"))
		{
			Json::Value array(Json::arrayValue);
			result["builds"] = array;
		}

		result["builds"].append(builddata);
	}

	return 0;
}

bool ConvertToBackendUnit::IsResourceBuild(int type)
{
	switch(type)
	{
		case resource_build_farm:
		case resource_build_quarry:
		case resource_build_iron_field:
		case resource_build_wood_field:
			return true;
		default: return false;
	}
}

int ConvertToBackendUnit::GetResourceTye(int type)
{
	switch(type)
	{
		case resource_build_farm: return resource_rice;
		case resource_build_quarry: return  resource_stone;
		case resource_build_iron_field: return resource_iron;
		case resource_build_wood_field: return resource_wood;
		default: throw runtime_error("wrong_build_type");
	}
}

OpenSpecialPackUnit::OpenSpecialPackUnit(const UserWrap& user):
		BaseCmdUnit(user.Id())
{

}

int OpenSpecialPackUnit::Choose(UserWrap& userWrap, const BaseCmdParams & param, Json::Value & result)
{
	//获取参数
	unsigned int ud = param.ValueAsUInt("ud");
	unsigned int selected_eqid = param.ValueAsUInt("selected_eqid");  //选中的装备id
	unsigned count = 1;
	try
	{
		count = param.ValueAsUInt("count");
	}
	catch(exception& e){}
	count = max(1u, count);

	CLogicEquipment logicequip;
	Json::Value equipdata;

	int ret = logicequip.Get(m_nUid, ud, equipdata);

	if (ret)
	{
		throw runtime_error("get_equip_error");
	}

	unsigned int eqid = equipdata["id"].asUInt();
	//参数校验
	const ConfigFunction::OpenSpecialEquipItem & specialitemcfg = FunctionsConfigWrap().GetSpecialEquipItemCfg(eqid);

	int target = -1;

	//判断选择的eqid是否在物品列表中
	for(int i = 0; i < specialitemcfg.replace_equips_size(); ++i)
	{
		if (specialitemcfg.replace_equips(i).equips_size() > 0 && specialitemcfg.replace_equips(i).equips(0u).eqid() == selected_eqid)
		{
			target = i;
			break;
		}
	}

	if (-1 == target)
	{
		error_log("can not find selected_eqid in equips's list. uid=%u,ud=%u,select=%u", m_nUid, ud, selected_eqid);
		throw runtime_error("select_eqid_error");
	}

	//参数正确。则开始兑换。先消耗礼包
	ret = logicequip.UseEquipment(m_nUid, eqid, ud, count, "SpecialPack_Open");

	if (ret)
	{
		error_log("use equip error. uid=%u, ud=%u.", m_nUid, ud);
		throw runtime_error("use_equip_error");
	}

	//发放对应的物品
	ProvideCommonReward(specialitemcfg.replace_equips(target), "SpecialPack_Open", result, 0, count);

	return 0;
}

JueXueBreakUnit::JueXueBreakUnit(const UserWrap& user):
		BaseCmdUnit(user.Id())
{

}

int JueXueBreakUnit::BreakThrough(UserWrap& userWrap, const BaseCmdParams & param, Json::Value & result)
{
	//判断绝学来自于哪里
	unsigned int index = param.ValueAsUInt("index");
	unsigned int equd = param.ValueAsUInt("ud");

	Json::Value tech;
	userWrap.GetUserTech(tech);

	//绝学背包长度判断
	if (tech["baglist"].size() < index)
	{
		error_log("param error. uid=%u,index=%u", m_nUid, index);
		throw runtime_error("param_error");
	}

	Json::Value & datajuexue = tech["baglist"][index];

	//判断是否已经突破.0-id; 1-exp; 2-isbreak
	if (datajuexue.size() > 2 && datajuexue[2u].asUInt() == 1)
	{
		error_log("juexue's breakthrough already done. uid=%u,index=%u", m_nUid, index);
		throw runtime_error("breakthrough_already_done");
	}

	unsigned int id = datajuexue[0u].asUInt();
	unsigned int exp = datajuexue[1u].asUInt();

	int character = id % 10;  //品质

	if (character < juexue_character_orange)
	{
		//品质低于橙色，不开放突破功能
		error_log("juexue's character not enough. uid=%u,index=%u", m_nUid, index);
		throw runtime_error("character_not_enough");
	}

	int level = GetJueXueLevel(exp, character);

	if (level != break_through_level)
	{
		//等级不等于10级，不能突破
		error_log("juexue's level not match condition. uid=%u,index=%u", m_nUid, index);
		throw runtime_error("level_not_match_condition");
	}

	//消耗道具
	CLogicEquipment logicequip;
	int ret = logicequip.UseEquipment(m_nUid, break_through_eqid, equd, break_through_eqnum, "JueXue_Breakthrough");

	if (ret)
	{
		error_log("use equip error. uid=%u,ud=%u", m_nUid, equd);
		throw runtime_error("use_equip_error");
	}

	//设置突破标志
	datajuexue[2u] = 1;
	userWrap.SetUserTech(tech);

	result["juexue"] = datajuexue;

	return 0;
}

int JueXueBreakUnit::GetJueXueLevel(unsigned int exp, int character)
{
	//参数校验
	if (character >= juexue_character_max)
	{
		error_log("param error. character=%d", character);
		throw runtime_error("character_error");
	}

	//根据绝学经验，计算绝学等级
	//经验品质相关数组。
	unsigned int character_exp[juexue_character_max][juexue_level_max] = {
			{0,100,200,400,800,1600,3200,6400,12800,25600, INT_MAX, INT_MAX},
			{0,200,400,800,1600,3200,6400,12800,25600,51200, INT_MAX, INT_MAX},
			{0,400,800,1600,3200,6400,12800,25600,51200,102400, INT_MAX, INT_MAX},
			{0,800,1600,3200,6400,12800,25600,51200,102400,204800, 409600, 819200},
			{0,1200,2400,4800,9600,19200,38400,76800,153600,307200, 614400, 1228800}
	};

	for(int i = juexue_level_max - 1; i >= 0; --i)
	{
		if (exp >= character_exp[character][i])
		{
			return i+1;  //等级
		}
	}

	//最小1级
	return 1;
}
