/*
 * LogicUserManager.cpp
 *
 *  Created on: 2016-9-12
 *      Author: dawx62fac
 */

#include "LogicUserManager.h"

UVIPPower::UVIPPower()
	: integral_cnt_(0)
	, market_cnt_(0)
	, sacrifice_cnt_(0)
	, order_cnt_(0)
	, bmarket_add_(0)
	, refresh_cnt_(0)
	, market_add_(0)
	, auto_build_cnt_(0)
	, order_limit_(0)
	, iron_add_(0)
	, resource_yield_add_(0)
	, fight_exp_add_(0)
	, polity_task_factor_(0.0f)
	, storage_capacity_add_(0)

{
	memset(weapon_prob_, 0, sizeof(weapon_prob_));
}

UVIPPower::UVIPPower(unsigned level)
	: integral_cnt_(0)
	, market_cnt_(0)
	, sacrifice_cnt_(0)
	, order_cnt_(0)
	, bmarket_add_(0)
	, refresh_cnt_(0)
	, market_add_(0)
	, auto_build_cnt_(0)
	, order_limit_(0)
	, iron_add_(0)
	, resource_yield_add_(0)
	, fight_exp_add_(0)
	, polity_task_factor_(0.0f)
	, storage_capacity_add_(0)
{
	memset(weapon_prob_, 0, sizeof(weapon_prob_));

	VIPCfgWrap cfg;
	const VIPConfig::UVIPBasePower& baseCfg = cfg.BasePower();

	int index = level - 1;
	if (index < baseCfg.integral_cnt_size())
	{
		integral_cnt_ = baseCfg.integral_cnt(index);
	}

	if (index < baseCfg.market_cnt_size())
	{
		market_cnt_ = baseCfg.market_cnt(index);
	}

	if (index < baseCfg.sacrifice_cnt_size())
	{
		sacrifice_cnt_ = baseCfg.sacrifice_cnt(index);
	}

	if (index < baseCfg.order_cnt_size())
	{
		order_cnt_ = baseCfg.order_cnt(index);
	}

	if (index < baseCfg.bmarket_add_size())
	{
		bmarket_add_ = baseCfg.bmarket_add(index);
	}

	if (index < baseCfg.refresh_cnt_size())
	{
		refresh_cnt_ = baseCfg.refresh_cnt(index);
	}

	if (index < baseCfg.market_add_size())
	{
		market_add_ = baseCfg.market_add(index);
	}

	if (index < baseCfg.auto_build_cnt_size())
	{
		auto_build_cnt_ = baseCfg.auto_build_cnt(index);
	}

	if (index < baseCfg.order_limit_size())
	{
		order_limit_ = baseCfg.order_limit(index);
	}

	if (index < baseCfg.iron_add_size())
	{
		iron_add_ = baseCfg.iron_add(index);
	}

	for (int i = 1; i <= (int)level; i++)
	{
		int index = i - 1;
		if (index < cfg.Cfg().lvl_power_size())
		{
			const VIPConfig::UVIPLvlPower& lvl_cfg = cfg.Cfg().lvl_power(index);
			InitFromLvlPower(lvl_cfg);
		}
	}
}

void UVIPPower::InitFromLvlPower(const VIPConfig::UVIPLvlPower& extra)
{
	if (extra.has_resource_yield_add())
	{
		resource_yield_add_ = extra.resource_yield_add();
	}

	if (extra.has_polity_task_factor())
	{
		polity_task_factor_ = extra.polity_task_factor();
	}

	if (extra.has_fight_exp_add())
	{
		fight_exp_add_ = extra.fight_exp_add();
	}

	if (extra.weapon_prob_size() > 0)
	{
		for (int i = 0; i < extra.weapon_prob_size() && i < 4; i++)
		{
			weapon_prob_[i] = extra.weapon_prob(i);
		}
	}

	if (extra.has_storage_capacity_add())
	{
		storage_capacity_add_ = extra.storage_capacity_add();
	}
}

void UVIPPower::RestoreEveryBasePower(DataBase& base)
{
	//notice: 数据溢出
	base.integral_time_cnt  += integral_cnt_;
	//集市暂时没有
	//base.market += market_cnt_;
	base.sacrifice += sacrifice_cnt_;
	//vip 也加上限 @oulong 20170206
	if (base.sacrifice > 25)
	{
		base.sacrifice = 25;
	}

	if (base.order  < order_limit_)
	{
		base.order += order_cnt_;
		base.order = base.order > order_limit_ ? order_limit_ : base.order;
	}


	base.refresh += refresh_cnt_;
}

float UVIPPower::GetMarketAdd() const
{
	return (float)bmarket_add_ / 100;
}

unsigned UVIPPower::GetAutoBuildCnt() const
{
	return auto_build_cnt_;
}

void UVIPPower::WeaponProbAdd(std::vector<unsigned>& result) const
{
	result.clear();

	for(int  i = 0; i < 4; i++)
	{
		result.push_back(weapon_prob_[i]);
	}
}

/////////////////////////////////////////////////////////////////////
DBCUserBaseWrap::DBCUserBaseWrap(unsigned uid)
	: container_(BaseManager::Instance())
	, index_(_Index(uid))
	, data_(container_->m_data->data[index_])
{
}

DBCUserBaseWrap::DBCUserBaseWrap(unsigned index, DataBase& data)
	: container_(BaseManager::Instance())
	, index_(index)
	, data_(data)
{

}

int DBCUserBaseWrap::_Index(unsigned uid)
{
	int index = container_->GetIndex(uid);
	if (index < 0)
	{
		error_log("get_user_data_error.uid=%u", uid);
		throw std::runtime_error("get_user_data_error");
	}

	return index;
}

bool DBCUserBaseWrap::AddExp(int exp)
{
	unsigned old_lvl = data_.level;

	if (exp > 0)
	{
		data_.AddExp(exp);
		Save();

		if (data_.level > old_lvl)
		{
			OnUserUpgradeReward(old_lvl);
		}

		return true;
	}

	return false;
}

void DBCUserBaseWrap::OnUserUpgradeReward(unsigned old_level)
{
	int reward_s_cnt = 0;
	for (int i = old_level + 1; i <= data_.level; ++i)
	{
		reward_s_cnt += (i % 5 == 0) ? 5 : 2;
		//添加祭祀次数
	}

	if (data_.sacrifice < 25)
	{
		data_.sacrifice = data_.sacrifice + reward_s_cnt;
		data_.sacrifice = data_.sacrifice > 25 ? 25 : data_.sacrifice;
	}
	//end

	Save();

	LogicResourceManager::Instance()->SyncUserLevel(data_.uid, data_.level);

	ProtoPush::UserUpLevel* msg = new ProtoPush::UserUpLevel;
	msg->set_uid(data_.uid);
	msg->set_old_level(old_level);
	msg->set_new_level(data_.level);
	msg->set_exp(data_.exp);
	msg->set_sacrifice(data_.sacrifice);
	msg->set_reward_s(reward_s_cnt);

	LogicManager::Instance()->sendMsg(data_.uid, msg);

	//官职系统开放了  产量有变化
	if (data_.level >= OFFICIAL_OPEN_LEVEL)
	{
		LogicBuildManager::Instance()->SyncYield(data_.uid);
	}
}

void DBCUserBaseWrap::UseFreeFlamen(int cnt)
{
	if (data_.sacrifice >= cnt)
	{
		data_.sacrifice -= cnt;
	}
	else
	{
		data_.sacrifice = 0;
	}

	Save();
}

void DBCUserBaseWrap::FlamenCostCnt(int type, int cnt)
{
	if (cnt == 0) return ;

	data_.AddFlamenBuyCnt(type, cnt);

	Save();
}

void DBCUserBaseWrap::AddCash(int cash, const std::string& reason)
{
	if (cash <= 0)
	{
		error_log("[AddCash] wrong param. uid=%u, cash=%d", data_.uid, cash);
		throw std::runtime_error("invalid_cash_param");
	}

	COINS_LOG("[%s][uid=%u,ocash=%u,ncash=%u,chgcash=%d]"
			, reason.c_str(), data_.uid, data_.cash, data_.cash+cash, cash);

	data_.cash += cash;

	Save();
}

void DBCUserBaseWrap::CostCash(int cash, const std::string& reason)
{
	if (cash <= 0)
	{
		error_log("[CostCash] wrong param. uid=%u, cash=%d", data_.uid, cash);
		throw std::runtime_error("invalid_cash_param");
	}

	if (cash > (int)data_.cash)
	{
		error_log("[CostCash] cash not enough uid=%u,chgcash=%d,cash=%u", data_.uid, cash, data_.cash);
		throw std::runtime_error("cash_not_enough");
	}

	unsigned old_cash = data_.cash;
	data_.cash -= cash;

	COINS_LOG("[%s][uid=%u,ocash=%u,ncash=%u,chgcash=%d]", reason.c_str(), data_.uid, old_cash, data_.cash, -cash);
	Save();

	OfflineResourceItem&  resourceitem = LogicResourceManager::Instance()->Get(data_.uid);
	resourceitem.AddCost(cash);
}

void DBCUserBaseWrap::SetJobSalary()
{
	data_.job_reward_ts = Time::GetGlobalTime();

	Save();
}

void  DBCUserBaseWrap::OpenNormalHole(int exp)
{
	data_.mine_normal_ts = Time::GetGlobalTime();
	data_.mine_exp += exp;

	Save();
}

void  DBCUserBaseWrap::OpenKingdomHole(int exp)
{
	data_.mine_exp += exp;

	Save();
}

void  DBCUserBaseWrap::DonateHole(int exp)
{
	data_.mine_exp += exp;

	Save();
}

void  DBCUserBaseWrap::GetKingdomMineReward()
{
	data_.mine_reward_ts = Time::GetGlobalTime();

	Save();
}

void DBCUserBaseWrap::SetTokenOpTs(unsigned ts)
{
	data_.token_op_ts = ts;

	Save();
}

void DBCUserBaseWrap::AddResource(std::map<unsigned, unsigned>& resource, const std::string& reason)
{
	if (resource.empty()) return ;

	DataBase oldBase = data_;
	std::map<unsigned, unsigned>::iterator it = resource.begin();
	for (;it != resource.end(); ++it)
	{
		data_.AddResource(it->first, it->second);
	}

	RESOURCE_LOG("[%s]uid=%u,coin:%u,add_coins:%d,wood:%u,add_wood:%d,food:%u,add_food:%d,iron:%u,add_iron:%d",reason.c_str(), data_.uid,
					data_.coin, data_.coin - oldBase.coin,
					data_.wood, data_.wood - oldBase.wood,
					data_.food, data_.food - oldBase.food,
					data_.iron, data_.iron - oldBase.iron);

	Save();
}

void DBCUserBaseWrap::AddResource(int coins, int wood, int food, int iron, const std::string& reason)
{
	if (coins < 0 || wood < 0 || food < 0 || iron < 0)
	{
		error_log("[AddUserResource] wrong param. uid=%u, coins=%d,wood=%d,food=%d,iron=%d", data_.uid, coins, wood, food, iron);
		throw std::runtime_error("invalid_param");
	}

	RestoreResource();

	data_.coin += coins;
	data_.wood += wood;
	data_.food += food;
	data_.iron += iron;

	Save();

	RESOURCE_LOG("[%s][uid=%u,chgcoin=%d,coin=%u,chgwood=%d,wood=%u,chgfood=%d,food=%u,chgiron=%d,iron=%u]",
				reason.c_str(), data_.uid, coins, data_.coin, wood, data_.wood, food, data_.food, iron, data_.iron);
}

void DBCUserBaseWrap::RestoreResource()
{
	unsigned uid = data_.uid;
	unsigned now = Time::GetGlobalTime();
	if (data_.up_res_time == 0 || now <= data_.up_res_time)
	{
		data_.up_res_time = now;
		return ;
	}

	//大于一分钟才更新
	if (data_.up_res_time + 60 > now) return;
	//
	/*
	uint32_t coin;//铜币
	uint32_t wood;//木材
	uint32_t food;//粮食
	uint32_t iron;//镔铁
	*/

	bool bAdd = false;
	uint32_t* res[4] = {&data_.coin, &data_.wood, &data_.food, &data_.iron};
	unsigned  add_a_res[4] = {0};
	try
	{
		//不计算兵营
		int i = 0;
		for (int type = DataBuildingManager::FOLK_HOUSE_TYPE;
				type <= DataBuildingManager::MINE_FIELD_TYPE && i < 4;
				++type,++i)
		{
			//最多能增加的资源
			unsigned capacity = LogicBuildManager::Instance()->GetCapacity(uid, type);
			if (capacity == 0) continue;
			unsigned free_add = (capacity > *res[i]) ? capacity - *res[i] : 0;
			if (free_add == 0) continue;

			unsigned need_add = LogicBuildManager::Instance()->ProductValue(uid, type, data_.up_res_time, now);
#if 0
			unsigned interval_minit = (now - data_.up_res_time) / 60;
			unsigned yields = LogicBuildManager::Instance()->Yields(uid, type);
			unsigned need_add = yields / 60 * interval_minit;
#endif
			if (need_add > free_add)
			{
				need_add = free_add;
			}

			if (need_add == 0) continue;

			add_a_res[i] = need_add;

			*res[i] += need_add;

			bAdd = true;
		}

		data_.up_res_time = now;

		if (bAdd)
		{
			Save();
			RESOURCE_LOG("[Resource_restore]uid=%u,coin:%u,add_coins:%u,wood:%u,add_wood:%u,food:%u,add_food:%u,iron:%u,add_iron:%u"
					, uid, data_.coin, add_a_res[0],
					data_.wood, add_a_res[1],
					data_.food, add_a_res[2],
					data_.iron, add_a_res[3]);
		}

	}
	catch(const std::exception& e)
	{
		error_log("uid=%u,%s", uid, e.what());
	}
}

void DBCUserBaseWrap::CostUserResource(int coins, int wood, int food, int iron, const string& reason)
{
	RestoreResource();

	unsigned uid = data_.uid;
	if (coins < 0 || wood < 0 || food < 0 || iron < 0)
	{
		error_log("[CostUserResource] wrong param. uid=%u, coins=%d,wood=%d,food=%d,iron=%d, %s", uid, coins, wood, food, iron, reason.c_str());
		throw std::runtime_error("invalid_param");
	}

	if (coins > (int)data_.coin)
	{
		error_log("[CostUserResource] coin not enough uid=%u,coinchg=%d,coin=%u,%s", uid, coins, data_.coin, reason.c_str());
		throw std::runtime_error("coin_not_enough");
	}

	if (wood > (int)data_.wood)
	{
		error_log("[CostUserResource] wood not enough uid=%u,woodchg=%d,wood=%u, %s", uid, wood, data_.wood, reason.c_str());
		throw std::runtime_error("wood_not_enough");
	}

	if (food > (int)data_.food)
	{
		error_log("[CostUserResource] food not enough uid=%u,foodchg=%d,food=%u, %s", uid, food, data_.food, reason.c_str());
		throw std::runtime_error("food_not_enough");
	}

	if (iron > (int)data_.iron)
	{
		error_log("[CostUserResource] iron not enough. uid=%u,ironchg=%d,iron=%u, %s", uid, iron, data_.iron, reason.c_str());
		throw std::runtime_error("iron_not_enough");
	}

	data_.coin -= coins;
	data_.wood -= wood;
	data_.food -= food;
	data_.iron -= iron;

	Save();

	RESOURCE_LOG("[%s][uid=%u,chgcoin=%d,coin=%u,chgwood=%d,wood=%u,chgfood=%d,food=%u,chgiron=%d,iron=%u]",
				reason.c_str(), data_.uid, -coins, data_.coin, -wood, data_.wood, -food, data_.food, -iron, data_.iron);
}

void DBCUserBaseWrap::FullMessage(DataCommon::UserResourceCPP* obj)
{
	obj->set_coin(data_.coin);
	obj->set_wood(data_.wood);
	obj->set_food(data_.food);
	obj->set_iron(data_.iron);
	obj->set_cash(data_.cash);
}

void DBCUserBaseWrap::CostHarmmer(unsigned cnt, const std::string& reason)
{
	if (data_.harmmer < cnt)
	{
		error_log("not_enough_harmmer. uid=%u, cnt=%d", data_.uid, cnt);
		throw std::runtime_error("not_enough_harmmer");
	}

	data_.harmmer -= cnt;

	RESOURCE_LOG("[%s]uid:%u, cost:%d,surplus:%d", reason.c_str(), data_.uid, cnt, data_.harmmer);

	Save();
}

bool DBCUserBaseWrap::IsPassNPC(unsigned id, unsigned nCnt)
{
	if (data_.npc_pass < id)
	{
		return false;
	}

	if (nCnt > 1)
	{
		int pass_cnt = 0;
		NPCPassCfgWrap npcCfg;
		const PassSystemConfig::PassItem& npcCfgItem = npcCfg.Item(id);
		if (! npcCfgItem.is_record_cnt())
		{
			error_log("npc_pass_not_record. id:%u, nCnt:%d", id, nCnt);
			return false;
		}

		int index = DataNPCPassMgr::Instance()->GetIndex(data_.uid, id);
		pass_cnt = index >= 0 ? DataNPCPassMgr::Instance()->m_data->data[index].pass_cnt : 1;

		return pass_cnt >= (int)nCnt;
	}
	else
	{
		return true;
	}
}

void DBCUserBaseWrap::AddBuildExploit(int cnt)
{
	data_.preward += cnt;

	Save();
}

void DBCUserBaseWrap::AddTicket(int t)
{
	data_.ticket += t;

	Save();
}

void DBCUserBaseWrap::ClearBuildExploit()
{
	data_.preward = 0;
	Save();
}

void DBCUserBaseWrap::AddExploitBox(unsigned cnt)
{
	if (cnt <= 0)
	{
		return ;
	}


	data_.rewardb += cnt;
	if (data_.rewardb > 99)
	{
		data_.rewardb = 99;
	}

	EQUIPMENT_LOG("uid:%u, add_exploit_box=%d,exploit_box=%u", data_.uid, cnt, data_.rewardb);

	Save();
}

void DBCUserBaseWrap::UseExploitBox(unsigned cnt)
{
	if (data_.rewardb < cnt)
	{
		throw std::runtime_error("exploit_box_not_enough");
	}
	else
	{
		data_.rewardb -= cnt;
	}

	EQUIPMENT_LOG("use_exploit_box=%d,exploit_box=%u", cnt, data_.rewardb);

	Save();
}

void DBCUserBaseWrap::UseIntegralReward()
{
	if (data_.integral_time_cnt <= 0)
	{
		throw std::runtime_error("integral_time_cnt_not_enough");
	}

	data_.integral_time_cnt -= 1;

	Save();
}


void DBCUserBaseWrap::Reward(const ::CommonGiftConfig::BaseReward& base
				, ::DataCommon::CommonBaseRewardCPP* obj
				, const std::string& reason, float nMul)
{
	string strlog;

	char szchgtemp[1000] = {0};
	sprintf(szchgtemp, "[%s] uid=%u,", reason.c_str(), data_.uid);
	strlog += szchgtemp;

	if (base.has_coin())
	{
		unsigned coin = base.coin() * nMul;
		data_.coin += coin;

		sprintf(szchgtemp, "chgcoin=%u,coin=%u,", coin, data_.coin);
		strlog += szchgtemp;

		obj->mutable_coin()->set_value(obj->mutable_coin()->value() + coin);
		obj->mutable_coin()->set_total_value(data_.coin);
	}

	if (base.has_wood())
	{
		unsigned wood = base.wood() * nMul;
		data_.wood += base.wood();

		sprintf(szchgtemp, "chgwood=%u,wood=%u,", wood, data_.wood);
		strlog += szchgtemp;

		obj->mutable_wood()->set_value(obj->mutable_wood()->value() + wood);
		obj->mutable_wood()->set_total_value(data_.wood);
	}

	if (base.has_food())
	{
		unsigned food = base.food() * nMul;
		data_.food += food;
		obj->mutable_food()->set_value(obj->mutable_food()->value() +food);
		obj->mutable_food()->set_total_value(data_.food);

		sprintf(szchgtemp, "chgfood=%u,wood=%u,", food, data_.food);
		strlog += szchgtemp;
	}

	if (base.has_iron())
	{
		unsigned iron = base.iron() * nMul;
		data_.iron += iron;
		obj->mutable_iron()->set_value(obj->mutable_iron()->value() +iron);
		obj->mutable_iron()->set_total_value(data_.iron);

		sprintf(szchgtemp, "chgiron=%u,iron=%u,", iron, data_.iron);
		strlog += szchgtemp;
	}

	if (base.has_hammer())
	{
		unsigned hammer = base.hammer() * nMul;
		data_.harmmer += hammer;

		obj->mutable_hammer()->set_value(obj->mutable_hammer()->value() +hammer);
		obj->mutable_hammer()->set_total_value(data_.harmmer);

		sprintf(szchgtemp, "chghammer=%u,hammer=%u,", hammer, data_.harmmer);
		strlog += szchgtemp;
	}

	if (base.has_order())
	{
		unsigned order = base.order() * nMul;
		data_.order += order;

		obj->mutable_order()->set_value(obj->mutable_order()->value() +order);
		obj->mutable_order()->set_total_value(data_.order);

		sprintf(szchgtemp, "chgorder=%u,order=%u,", order, data_.order);
		strlog += szchgtemp;
	}

	if (base.has_exp())
	{
		unsigned exp = nMul * base.exp();
		AddExp(exp);
		obj->mutable_exp()->set_value(obj->mutable_exp()->value() + exp);
		obj->mutable_exp()->set_total_value(data_.exp);

		sprintf(szchgtemp, "chgexp=%u,exp=%llu,", exp, data_.exp);
		strlog += szchgtemp;
	}

	if (base.has_cash())
	{
		//调用加钻石的接口
		unsigned cash = base.cash() * nMul;
		AddCash(cash, reason);

		obj->mutable_cash()->set_value(obj->mutable_cash()->value() + cash);
		obj->mutable_cash()->set_total_value(data_.cash);
	}

	if (base.has_refresh())
	{
		unsigned refresh = base.refresh() * nMul;
		data_.refresh += refresh;

		obj->mutable_refresh()->set_value(obj->mutable_refresh()->value() + refresh);
		obj->mutable_refresh()->set_total_value(data_.refresh);

		sprintf(szchgtemp, "chgrefresh=%u,refresh=%u,", refresh, data_.refresh);
		strlog += szchgtemp;
	}

	if (base.has_arefresh())
	{
		unsigned arefresh = base.arefresh() * nMul;
		data_.arefresh += arefresh;

		obj->mutable_refresh()->set_value(obj->mutable_arefresh()->value() + arefresh);
		obj->mutable_refresh()->set_total_value(data_.refresh);

		sprintf(szchgtemp, "chgarefresh=%u,arefresh=%u,", arefresh, data_.arefresh);
		strlog += szchgtemp;
	}

	if (base.has_sacrifice())
	{
		unsigned sacrifice = base.sacrifice() * nMul;
		data_.sacrifice += sacrifice;

		obj->mutable_sacrifice()->set_value(obj->mutable_sacrifice()->value() + sacrifice);
		obj->mutable_sacrifice()->set_total_value(data_.sacrifice);

		sprintf(szchgtemp, "chgsacrifice=%u,sacrifice=%u,", sacrifice, data_.sacrifice);
		strlog += szchgtemp;
	}

	//集市用作龙鳞
	if (base.has_market())
	{
		unsigned market = base.market() * nMul;
		data_.market += market;

		obj->mutable_market()->set_value(obj->mutable_market()->value() + market);
		obj->mutable_market()->set_total_value(data_.market);

		sprintf(szchgtemp, "chgmarket=%u,market=%u,", market, data_.market);
		strlog += szchgtemp;
	}

	/*废弃
	//影子
	if (base.has_shadow())
	{
		unsigned shadow = base.shadow() * nMul;
		unsigned nTotal = data_.shadow + shadow;
		if (nTotal > 250)
		{
			data_.shadow = 250;
			error_log("uid: %u, shadow data overflow. should_value: %u, overflow: %u"
					, data_.uid, nTotal, nTotal - shadow);
		}
		else
		{
			data_.shadow = nTotal;
		}

		sprintf(szchgtemp, "chgshadow=%u,shadow=%u,", shadow, data_.shadow);
		strlog += szchgtemp;
	}
	*/


	Save();

	RESOURCE_LOG(strlog.c_str());
}

bool DBCUserBaseWrap::IsGetFirstRechargeReward() const
{
	return data_.first_recharge == 1;
}

void DBCUserBaseWrap::SetFirstRechargeRewardStatus()
{
	data_.first_recharge = 2;

	Save();
}

void DBCUserBaseWrap::SetAutoBuild()
{
	data_.auto_build_flag = 1;

	Save();
}

bool DBCUserBaseWrap::IsAutoBuildPower() const
{
	return data_.auto_build_flag == 1;
}

bool DBCUserBaseWrap::FinalOfflineResource(const OfflineResourceItem& offline)
{
	unsigned uid = data_.uid;
	if (offline.coin <= 0 && offline.wood <= 0 && offline.food <= 0
			&& offline.iron <= 0 && offline.ufood <= 0 && offline.gem <= 0)
	{
		return false;
	}

	data_.coin += offline.coin;
	data_.wood += offline.wood;
	data_.food += offline.food;
	data_.iron += offline.iron;

	//增加龙鳞的上线结算
	data_.market += offline.gem;

	data_.food = (data_.food  > offline.ufood) ?
			data_.food  - offline.ufood : 0;

	RESOURCE_LOG("[Resource_restore]uid=%u,coin:%u,add_coins:%d,wood:%u,add_wood:%d,food:%u,add_food:%d,iron:%u,add_iron:%d,market=%u,add_market=%u"
				, uid, data_.coin, offline.coin,
				data_.wood, offline.wood,
				data_.food, int(offline.food) - int(offline.ufood),
				data_.iron, offline.iron,
				data_.market, offline.gem
				);


	Save();

	return true;
}

void DBCUserBaseWrap::FinalBattleReward(BattleReward& r)
{
	if (r.coin <= 0 && r.wood <= 0 && r.food <= 0 && r.iron <= 0 && r.gem <= 0)
	{
		return;
	}

	unsigned uid = data_.uid;

	data_.coin += r.coin;
	data_.wood += r.wood;
	data_.food += r.food;
	data_.iron += r.iron;

	//增加龙鳞的战斗结算
	data_.market += r.gem;

	RESOURCE_LOG("[Resource_restore]uid=%u,coin:%u,add_coins:%d,wood:%u,add_wood:%d,food:%u,add_food:%d,iron:%u,add_iron:%d,market=%u,add_market=%u"
				, uid, data_.coin, r.coin,
				data_.wood, r.wood,
				data_.food, r.food,
				data_.iron, r.iron,
				data_.market, r.gem
			);

	Save();
}

int  DBCUserBaseWrap::BuildUpgrade(unsigned buildid, unsigned buildLvl)
{
	unsigned uid = data_.uid;

	BuildCfgWrap buildCfg;
	const Building::LvLs& lvlsCfg = buildCfg.LvLs(buildid, buildLvl);

	RestoreResource();

	if (data_.coin < lvlsCfg.cost_coins())
	{
		error_log("coins_not_enough.uid=%u, coins:%d, cost: %d", uid, data_.coin, lvlsCfg.cost_coins());
		return R_ERROR;
	}

	if (data_.wood < lvlsCfg.cost_wood())
	{
		error_log("woods_not_enough.uid=%u,  wood:%d, cost_wood:%d", uid, data_.wood, lvlsCfg.cost_wood());
		return R_ERROR;
	}

	data_.coin -= lvlsCfg.cost_coins();
	data_.wood -= lvlsCfg.cost_wood();

	RESOURCE_LOG("[build_Upgrade_op]uid:%u, cost_coin:%d,surplus_coins:%d, cost_wood:%d, surplus_wood:%d"
			, uid, lvlsCfg.cost_coins(), data_.coin, lvlsCfg.cost_wood(), data_.wood);

	//建筑升级之后才增加经验
	//AddExp(data_, lvlsCfg.out_exp());
	//data_.preward += lvlsCfg.out_exploit();

	Save();

	return R_SUCCESS;
}

int DBCUserBaseWrap::RealUseRecruitProp(unsigned nCnt) const
{
	return data_.order >= nCnt ? nCnt :  data_.order;
}

int DBCUserBaseWrap::UseRecruitProp(unsigned nCnt)
{
	int nUseCnt = nCnt;
	if (data_.order >= nCnt)
	{
		data_.order -= nCnt;
	}
	else
	{
		nUseCnt = data_.order;
		data_.order = 0;
	}

	if (nUseCnt > 0)
	{
		RESOURCE_LOG("Cost_recruit_prop. user:%u, cnt: %d, surplus: %d"
												, data_.uid, nUseCnt, data_.order);

		Save();
	}

	return nUseCnt;
}

int DBCUserBaseWrap::AddRecruitProp(unsigned count, const string& reason)
{
	data_.order += count;
	RESOURCE_LOG("[%s][uid=%u,chgorder=%d,order=%u]", reason.c_str(), data_.uid, count, data_.order);
	Save();

	return 0;
}

int DBCUserBaseWrap::AddGoldHammer(unsigned count, const string& reason)
{
	data_.harmmer += count;
	RESOURCE_LOG("[%s][uid=%u,chghammer=%d,hammer=%u]", reason.c_str(), data_.uid, count, data_.harmmer);
	Save();

	return 0;
}

int DBCUserBaseWrap::AddMarket(unsigned count, const string & reason)
{
	data_.market += count;
	RESOURCE_LOG("[%s][uid=%u,chgmarket=%d,market=%u]", reason.c_str(), data_.uid, count, data_.market);
	Save();

	return 0;
}

int DBCUserBaseWrap::CostMarket(int count, const string & reason)
{
	if (count < 0)
	{
		error_log("count must be positive. uid=%u, cnt=%d", data_.uid, count);
		throw std::runtime_error("count_must_positive");
	}

	if (data_.market < count)
	{
		error_log("not_enough_market. uid=%u, cnt=%d", data_.uid, count);
		throw std::runtime_error("not_enough_market");
	}

	data_.market -= count;

	RESOURCE_LOG("[%s]uid:%u, chgmarket=%d,market=%u", reason.c_str(), data_.uid, -count, data_.market);

	Save();
	return 0;
}

int DBCUserBaseWrap::CostTicket(int count, const string & reason)
{
	if (count < 0)
	{
		error_log("count must be positive. uid=%u, cnt=%d", data_.uid, count);
		throw std::runtime_error("count_must_positive");
	}

	if (data_.ticket < count)
	{
		error_log("not_enough_ticket. uid=%u, cnt=%d", data_.uid, count);
		throw std::runtime_error("not_enough_ticket");
	}

	data_.ticket -= count;

	RESOURCE_LOG("[%s]uid:%u, chgticket=%d,ticket=%u", reason.c_str(), data_.uid, -count, data_.ticket);

	Save();
}

int DBCUserBaseWrap::AsynType2ResourceType(ASYN_TYPE type)
{
	switch(type)
	{
		case e_asyn_coin: return COINTS_TYPE;
		case e_asyn_wood: return WOOD_TYPE;
		case e_asyn_food: return FOOD_TYPE;
		case e_asyn_iron: return IRON_TYPE;
		default:
		{
			error_log("unknow_asyn_type: ", type);
			throw std::runtime_error("unknow_asyn_type");
		}
	}
}

void DBCUserBaseWrap::AddAsynItem(unsigned id, unsigned count, const std::string& op)
{
	//	e_asyn_cash				= 0,
	//	e_asyn_coin				= 1,
	//	e_asyn_wood				= 2,
	//	e_asyn_food				= 3,
	//	e_asyn_iron				= 4,
	//
	if ((ASYN_TYPE)id == e_asyn_cash)
	{
		this->AddCash(count, op);
	}
	else if ((ASYN_TYPE)id == e_asyn_accrecharge)
	{
		data_.acccharge += count;
		data_.ticket += count;
		//RefreshVIPLevel(true);
		LogicUserManager::Instance()->NotifyRecharge(data_.uid, count);

		if (data_.acccharge >= 100 && data_.first_recharge == 0)
		{
			data_.first_recharge = 1;
		}

		//LogicCashBack::Instance()->Accumulation(data_.uid, count);
		GET_RMI(data_.uid).AddPay(count);

		Common::NoticePay* m = new Common::NoticePay;
		m->set_cash(data_.cash);
		m->set_vip_level(data_.viplevel);
		m->set_acc_recharge(data_.acccharge);
	}
	else if (id >= e_asyn_coin && id <= e_asyn_iron)
	{
		std::map<unsigned, unsigned> resource;
		resource[AsynType2ResourceType((ASYN_TYPE)id)] = count;
		this->AddResource(resource, op);
	}
	else if (id >= e_asyn_npc_1 && id <= e_asyn_npc_3)
	{
		//todo: npc activity, should check is on
		NPCActivity::Instance()->AddNPCActivityMaterial(data_.uid, id, count);
	}
	else if(id == e_asyn_exp)
	{
		this->AddExp(count);
	}
	else if (id == e_asyn_market)
	{
		this->AddMarket(count, op);
	}
	else if (id >= e_asyn_max)
	{
		LogicEquipmentManager::Instance()->AddEquipment(data_.uid, id, count, op);
	}

}

void DBCUserBaseWrap::FinalAsynData()
{
	unsigned uid = data_.uid;
	const AsynMap& map_data = AsynManager::Instance()->GetMap();
	if (map_data.count(uid) <= 0)
	{
		return ;
	}

	const AsynMap::const_iterator asyn_it = map_data.find(uid);
	if (asyn_it == map_data.end())
	{
		return ;
	}

	const std::map<unsigned, unsigned>& user_map = asyn_it->second;
	for (std::map<unsigned, unsigned>::const_iterator it = user_map.begin();
			it != user_map.end();
			++it)
	{
		try
		{
			const AsynItem& as_item = AsynManager::Instance()->m_data->item[it->second];
			AddAsynItem(as_item.id, as_item.count);
		}
		catch(const std::exception& e)
		{
			error_log("%s", e.what());
		}

	}

	AsynManager::Instance()->Del(uid);
}

bool DBCUserBaseWrap::SetNPCPassId(unsigned id)
{
	if (data_.npc_pass < id)
	{
		data_.npc_pass = id;

		Save();

		return true;
	}

	return false;
}

unsigned DBCUserBaseWrap::GetRegisterHours() const
{
	unsigned now = Time::GetGlobalTime();
	if (now > data_.register_time)
	{
		return (now - data_.register_time) / (60*60);
	}
	else
	{
		return 0;
	}
}

void DBCUserBaseWrap::SetPassActivityRewardFlag(int idx)
{
	if (idx < 0 || idx >= 16)
	{
		error_log("pass_activity_index_overflow. index: %d", idx);
		throw std::runtime_error("pass_activity_index_overflow");
	}

	if ((data_.pass_reward & (1 << idx)) > 0)
	{
		throw std::runtime_error("already_set_reward_flag");
	}

	data_.pass_reward |= 1 << idx;

	Save();
}

bool DBCUserBaseWrap::IsSetPassActivityRewardFlag(int idx) const
{
	if (idx < 0 || idx >= 16)
	{
		error_log("pass_activity_index_overflow. index: %d", idx);
		throw std::runtime_error("pass_activity_index_overflow");
	}

	return (data_.pass_reward & (1 << idx)) > 0;
}

void DBCUserBaseWrap::ResetCountryTaskStatus()
{
	data_.ResetCountryTaskStatus();

	Save();
}

void DBCUserBaseWrap::ResetCountryTaskStatus(unsigned offline_time)
{
	unsigned now = Time::GetGlobalTime();

	if (now < offline_time || now >= offline_time + 24*60*60)
	{
		ResetCountryTaskStatus();
		return ;
	}

	bool bDiffDay = CTime::IsDiffDay(offline_time, now);
	if (GetCountryTaskStage(bDiffDay, offline_time) != GetCountryTaskStage(bDiffDay, now))
	{
		ResetCountryTaskStatus();
	}

}

void DBCUserBaseWrap::RestoreRecruitProp(int interval_days)
{
	enum {
		RESTORE_PROT_ONCE_CNT = 50,
		RECRUIT_PROP_LIMIT_CNT = 150
	};

	//to change  只恢复非vip玩家的募兵令
	if (data_.viplevel == 0)
	{
		if (interval_days > 0 && data_.order < RECRUIT_PROP_LIMIT_CNT)
		{
			data_.order += RESTORE_PROT_ONCE_CNT;
			if (data_.order > RECRUIT_PROP_LIMIT_CNT)
			{
				data_.order = RECRUIT_PROP_LIMIT_CNT;
			}
		}

		Save();
	}
}

void DBCUserBaseWrap::EveryDayAction(int di)
{
	//todo: day interval
	if(di == 1)
	{
		++data_.login_times;
	}
	else
	{
		data_.login_times = 0;
	}
	data_.login_days ++;

	///////////////////////
	//募兵令的恢复
	RestoreRecruitProp(di);
	//整点/后勤奖励
	data_.RefreshIntegralTime();

	RestoreEveryVIPReward();
	ResetPkCnt();

	//祭司初始化
	data_.flamen_coins_cnt = 0;
	data_.flamem_wood_cnt = 0;
	data_.flamem_food_cnt = 0;
	data_.flamem_iron_cnt = 0;

	//清除领取每日任务次数
	data_.daily_reward_times = 0;
	data_.daily_free_times = 0;

	//重置充点小钱领取状态
	LogicCommonUtil::SetZeroCurrent(data_.shadow, 0);

	Save();
}

unsigned DBCUserBaseWrap::GetCountryTaskStage(bool isDiffDay, unsigned ts) const
{
	unsigned hour = LogicCommonUtil::GetHourByTime(ts);
	if (! isDiffDay)
	{
		if (hour < BATTLE_MISSION_1_S)
		{
			return 1;
		}
		else if (hour <  BATTLE_MISSION_2_S)
		{
			return 2;
		}
		else if (hour < BATTLE_MISSION_3_S)
		{
			return 3;
		}
		else
		{
			return 4;
		}
	}
	else
	{
		//解决跨天问题导致的bug
		if (hour >= BATTLE_MISSION_3_S || hour < BATTLE_MISSION_1_S)
		{
			return 5;
		}
		else
		{
			return ts;
		}
	}
}

bool DBCUserBaseWrap::IsGetMissionPersonalReward(unsigned task_no) const
{
	if (task_no < 1 || task_no > 3)
	{
		throw std::runtime_error("task_no_params_error");
	}

	if (task_no == 3)
	{
		return data_.mp3 == 0;
	}
	else
	{
		uint8_t val[3] = {data_.mp1, data_.mp2, data_.mp3};
		return val[task_no - 1] == 1;
	}
}

void DBCUserBaseWrap::SetGetMissionPersonalRewardStatus(unsigned task_no)
{
	if (task_no < 1 || task_no > 3)
	{
		throw std::runtime_error("task_no_params_error");
	}

	if (task_no == 3)
	{
		data_.mp3 = 1;
	}
	else
	{
		uint8_t* val[3] = {&data_.mp1, &data_.mp2, &data_.mp3};
		*(val[task_no - 1]) = 2;
	}

	Save();

}

bool DBCUserBaseWrap::IsGetMissionCountryReward(unsigned task_no) const
{
	uint8_t val[2] = {data_.mk1, data_.mk2};
	if (task_no < 1 || task_no > 2)
	{
		throw std::runtime_error("task_no_params_error");
	}

	return val[task_no - 1] == 0;
}

void DBCUserBaseWrap::SetGetMissionCountryRewardStatus(unsigned task_no)
{

	if (task_no < 1 || task_no > 2)
	{
		throw std::runtime_error("task_no_params_error");
	}

	uint8_t* val[2] = {&data_.mk1, &data_.mk2};

	*(val[task_no - 1]) = 1;

	Save();
}

//////////////////////////////////////////////////////////////
//vip
UVIPPower DBCUserBaseWrap::VIPPower() const
{
	if (data_.viplevel <= 0)
	{
		return UVIPPower();
	}

	try
	{
		return UVIPPower(data_.viplevel);
	}
	catch(const std::exception& e)
	{
		error_log("uid:%u, %s", data_.uid, e.what());
	}

	return UVIPPower();
}

void DBCUserBaseWrap::RefreshVIPLevel(bool isPush)
{
	uint8_t level = data_.viplevel;
	data_.viplevel = VIPCfgWrap().GetVIPLevel(data_.acccharge);
	if (data_.viplevel > level)
	{
		data_.auto_build_flag = 1;

		Save();

		unsigned uid = data_.uid;

		if (isPush)
		{
			//建筑产能可能有变化
			LogicBuildManager::Instance()->SyncYield(uid);
		}
		//
		//战斗产出角色经验可能改变
		OfflineResourceItem& resItem = LogicResourceManager::Instance()->Get(uid);
		resItem.viplevel = data_.viplevel;
		LogicScienceMgr::Instance()->Sync(uid, resItem);
	}
}

void 	DBCUserBaseWrap::RestoreEveryVIPReward()
{
	if (data_.viplevel > 0)
	{
		VIPPower().RestoreEveryBasePower(data_);

		Save();
	}
}


void 	DBCUserBaseWrap::SetVIPReward()
{
	if (data_.vip_reward < data_.viplevel)
	{
		data_.vip_reward = data_.viplevel;
		Save();
	}
}

void DBCUserBaseWrap::ResetPkCnt()
{
	data_.ladder = PK_FIELD_CNT_INIT;
	Save();
}

void 	DBCUserBaseWrap::UserPkCnt(int cnt)
{
	if (cnt <= 0)
	{
		throw std::runtime_error("UserPkCnt_params_error");
	}

	if (data_.ladder < cnt)
	{
		throw std::runtime_error("pk_cnt_not_enough");
	}

	data_.ladder -= cnt;

	Save();
}

void 	DBCUserBaseWrap::SetPkRewardTime(unsigned nTime)
{
	data_.ladder_ts = nTime;

	Save();
}

void DBCUserBaseWrap::FullData(const BotConfig::BotPlayer* obj)
{
	if (NULL ==  obj) return ;

	data_.level = obj->level();
	data_.viplevel = obj->viplevel();

	Save();
}

void DBCUserBaseWrap::AddArefreshCnt(int cnt)
{
	if (cnt < 0)
	{
		throw std::runtime_error("cnt_params_error");
	}

	if ((int)data_.arefresh + cnt >= 256)
	{
		data_.arefresh = 256;
	}
	else
	{
		data_.arefresh += cnt;
	}

	Save();
}

///////////////////////////////////////////////////////////////////////////////////
LogicUserManager::LogicUserManager()
	: baseData_(BaseManager::Instance())
{
	if (baseData_ == NULL)
	{
		error_log("base_data_manager_instance_error");
		throw std::runtime_error("base_data_manager_instance_error");
	}

	start_time = Time::GetGlobalTime();
}

void LogicUserManager::OnTimer1()
{
	unsigned now = Time::GetGlobalTime();

	if (now >= start_time + affair_time_interval)
	{
		int times = 1;  //1个时间间隔

		//加载在线用户
	    const map<unsigned, Common::Login>& uidmap = UserManager::Instance()->GetUser();
	    vector<unsigned> uids;

	    for(map<unsigned, Common::Login>::const_iterator it = uidmap.begin(); it != uidmap.end(); ++it)
        {
	    	uids.push_back(it->first);
        }

	    //增加政务次数
	    for(vector<unsigned>::iterator it = uids.begin(); it != uids.end(); ++it)
		{
	    	AddAndPushMissonTimes(*it, times);
		}

	    start_time = now;
	}

	while(! recharge_records_.empty())
	{
		const _RechargeRecord& record = recharge_records_.front();
		try
		{
			DBCUserBaseWrap user(record.uid);
			user.RefreshVIPLevel();

			Common::NoticePay* m = new Common::NoticePay;
			m->set_cash(user.Obj().cash);
			m->set_vip_level(user.Obj().viplevel);
			m->set_acc_recharge(user.Obj().acccharge);

			LogicManager::Instance()->sendMsg(record.uid, m);

		}
		catch (const std::exception& e)
		{
			error_log("uid: %u, %s", record.uid, e.what());
		}

		recharge_records_.pop_front();
	}
}

void LogicUserManager::NotifyRecharge(unsigned uid, unsigned cash)
{
	recharge_records_.push_back(_RechargeRecord(uid, cash));
}

int LogicUserManager::LoginCheck(unsigned uid)
{
	//计算累积的政务次数
	DBCUserBaseWrap userwrap(uid);
	unsigned now = Time::GetGlobalTime();

	if (0 == userwrap.Obj().last_off_time)  //新手玩家，程序异常中断导致下线时间仍然为0
	{
		return 0;
	}

	if (now < userwrap.Obj().last_off_time)  //当前时间小于上次下线时间，除非更改了服务器时间，才有可能发生这情况，暂不做处理
	{
		return 0;
	}

	unsigned diff = now - userwrap.Obj().last_off_time;
	int times = diff/affair_time_interval;  //X个时间间隔
	userwrap.Obj().mission_time += times;

	if (userwrap.Obj().mission_time > mission_times_max)
	{
		userwrap.Obj().mission_time = mission_times_max;
	}

	userwrap.Save();

	return 0;
}

bool LogicUserManager::AddExp(unsigned uid, int exp)
{
	return  DBCUserBaseWrap(uid).AddExp(exp);
}

int LogicUserManager::UseRecruitProp(unsigned uid, unsigned nCnt)
{
	int index = baseData_->GetIndex(uid);
	if (index < 0)
	{
		error_log("get_user_data_error. uid=%u", uid);
		throw std::runtime_error("get_user_data_error");
	}

	DataBase& database = baseData_->m_data->data[index];
	int nUseCnt = nCnt;
	if (database.order >= nCnt)
	{
		database.order -= nCnt;
	}
	else
	{
		nUseCnt = database.order;
		database.order = 0;
	}

	if (nUseCnt > 0)
	{
		RESOURCE_LOG("Cost_recruit_prop. user:%u, cnt: %d, surplus: %d"
												, uid, nUseCnt, database.order);

		baseData_->m_data->MarkChange(index);
	}

	return nUseCnt;
}

void LogicUserManager::CostUserResource(unsigned uid, int coins, int wood, int food, int iron, string reason, Json::Value & result)
{
	DBCUserBaseWrap userWrap(uid);
	userWrap.CostUserResource(coins, wood, food, iron, reason);

	result["coin"] = userWrap.Obj().coin;
	result["wood"] = userWrap.Obj().wood;
	result["food"] = userWrap.Obj().food;
	result["iron"] = userWrap.Obj().iron;
}


void LogicUserManager::AddUserResource(unsigned uid, int coins, int wood, int food, int iron, string reason, Json::Value & result)
{
	if (coins < 0 || wood < 0 || food < 0 || iron < 0)
	{
		error_log("[AddUserResource] wrong param. uid=%u, coins=%d,wood=%d,food=%d,iron=%d", uid, coins, wood, food, iron);
		throw std::runtime_error("invalid_param");
	}

	DBCUserBaseWrap userWrap(uid);
	userWrap.AddResource(coins, wood, food, iron, reason);

	const DataBase& base = userWrap.Obj();

	result["coin"] = base.coin;
	result["wood"] = base.wood;
	result["food"] = base.food;
	result["iron"] = base.iron;
}


void LogicUserManager::CostCash(unsigned uid, int cash, string reason, unsigned & newcash)
{
	DBCUserBaseWrap userWrap(uid);
	userWrap.CostCash(cash, reason);

	newcash = userWrap.Obj().cash;
}

int LogicUserManager::EveryDayAction()
{
	std::vector<unsigned> vUsers;
	UserManager::Instance()->GetOnlineUsers(vUsers);

	for (size_t i = 0; i < vUsers.size(); ++i)
	{
		try
		{
			DBCUserBaseWrap user(vUsers[i]);
			user.EveryDayAction();

			ProtoPush::OnceEveryDayReward* msg = new ProtoPush::OnceEveryDayReward;
			msg->set_integral_time_cnt(user.Obj().integral_time_cnt);
			msg->set_market(0);//集市取消
			msg->set_sacrifice(user.Obj().sacrifice);
			msg->set_order(user.Obj().order);
			msg->set_refresh(user.Obj().refresh);
			msg->set_ladder(user.Obj().ladder);
			msg->set_freerefresh(user.Obj().daily_free_times);
			msg->set_reward_times(user.Obj().daily_reward_times);

			LogicManager::Instance()->sendMsg(vUsers[i], msg);
		}
		catch(const std::exception& e)
		{
			error_log("uid: %u, %s", vUsers[i], e.what());
		}

	}

	return R_SUCCESS;
}

int LogicUserManager::Process(unsigned uid, User::CostCashReq* req, User::CostCashResp* resp)
{
	DBCUserBaseWrap user(uid);
	if (req->cash() > user.Obj().cash)
	{
		throw std::runtime_error("cash_not_enough");
	}

	if (req->op_code().empty())
	{
		throw std::runtime_error("need_op_code");
	}

	user.CostCash(req->cash(), req->op_code());

	if (resp)
	{
		resp->set_cash(user.Obj().cash);
		resp->set_operation(req->operation());
	}

	return R_SUCCESS;
}

int LogicUserManager::Process(unsigned uid, ProtoReward::FirstRechargeReq* req, ProtoReward::FirstRechargeResp* resp)
{
	DBCUserBaseWrap user(uid);
	if (! user.IsGetFirstRechargeReward())
	{
		throw std::runtime_error("status_error");
	}

	user.SetFirstRechargeRewardStatus();

	//
	std::string reason = "fisrt_recharge_reward";
	const RewardConfig::FirstRechargeReward& cfg
			= ConfigManager::Instance()->first_recharge.m_config.first_recharge();
	for (int i = 0; i < cfg.reward_size(); i++)
	{
		const RewardConfig::Reward& rewardCfg = cfg.reward(i);
		if (rewardCfg.has_equips())
		{
			unsigned eqid = rewardCfg.equips().eqid();
			unsigned cnt = rewardCfg.equips().count();

			LogicEquipmentManager::Instance()->AddEquipment(uid, eqid, cnt, reason, resp->mutable_equips());
			resp->add_equips_cnt(cnt);
		}

		if (rewardCfg.has_base())
		{
			user.Reward(rewardCfg.base(), resp->mutable_base(), reason);
		}

		if (rewardCfg.has_hero()
				&& ! DataHeroManager::Instance()->isHeroExists(uid, rewardCfg.hero()))
		{
			LogicHeroManager::Instance()->UnlockHero(uid, rewardCfg.hero(), "FirstRecharge", resp->add_heros());
		}
	}

	user.SetAutoBuild();

	resp->set_first_recharge(user.Obj().first_recharge);
	resp->set_auto_build_flag(user.Obj().auto_build_flag);

	return R_SUCCESS;
}

float LogicUserManager::GetIntegralTimeFactor(unsigned level)
{
	if (level >= 1 && level <= 40)
	{
		return 1.0f;
	}
	else if (level <= 59)
	{
		return 1.3f;
	}
	else if (level <= 79)
	{
		return 1.5f;
	}
	else if (level <= 90)
	{
		return 1.8f;
	}
	else
	{
		return 2.0f;
	}
}

int LogicUserManager::Process(unsigned uid, ProtoReward::IntegralTimeReq* req, ProtoReward::IntegralTimeResp* resp)
{
	DBCUserBaseWrap user(uid);
	if (user.Obj().integral_time_cnt <= 0)
	{
		throw std::runtime_error("reward_cnt_not_enough");
	}

	user.UseIntegralReward();

	std::string reason = "integral_time_reward";
	//
	const ::RewardConfig::IntegralReward& rewardCfg = IntegralTimeCfgWrap().Reward();
	user.Reward(rewardCfg.base(), resp->mutable_base(), reason, GetIntegralTimeFactor(user.Obj().level));

	resp->set_new_cnt(user.Obj().integral_time_cnt);

	return R_SUCCESS;
}

int LogicUserManager::Process(unsigned uid, ProtoGovernAffair::OpenAffairWindowReq* req, ProtoGovernAffair::OpenAffairWindowResp * respmsg)
{
	return OpenAffairWindow(uid, respmsg);
}

int LogicUserManager::OpenAffairWindow(unsigned uid, ProtoGovernAffair::OpenAffairWindowResp * respmsg)
{
	DBCUserBaseWrap userwrap(uid);

	if (userwrap.Obj().mission_time > 0 && 0 == userwrap.Obj().mission_id)  //任务id为0，重新刷新
	{
		RefreshAffair(uid);
	}

	respmsg->mutable_affair()->set_mission_id(userwrap.Obj().mission_id);
	respmsg->mutable_affair()->set_mission_time(userwrap.Obj().mission_time);
	respmsg->mutable_affair()->set_loyal(userwrap.Obj().loyal);

	return 0;
}

int LogicUserManager::Process(unsigned uid, ProtoGovernAffair::GetAffairRewardReq* req, ProtoGovernAffair::GetAffairRewardResp * respmsg)
{
	unsigned index = req->index();

	GetAffairReward(uid, index, respmsg);

	//政务事件外部接口
	AffairExternalInterface(uid);

	return 0;
}

int LogicUserManager::AffairExternalInterface(unsigned uid)
{
	//接入政务事件任务
	LogicMissionManager::MissionParam missionparam;
	missionparam.type = mission_type_governaffair;

	LogicMissionManager::Instance()->VerifyMissionComplete(uid, missionparam);

	//todo 接入每日政务事件任务
	LogicDailyMissionManager::DailyMissionParam dailymissionparam;
	dailymissionparam.type = daily_mission_type_affair;

	LogicDailyMissionManager::Instance()->VerifyDailyMissionComplete(uid, dailymissionparam);

	//todo 接入政务事件成就
    LogicAchievementManager::AchievementParam achievementparam;
	achievementparam.type = achievement_type_affair;

	LogicAchievementManager::Instance()->VerifyAchievementComplete(uid, achievementparam);

	return 0;
}

int LogicUserManager::GetAffairReward(unsigned uid, unsigned index, ProtoGovernAffair::GetAffairRewardResp * respmsg)
{
	DBCUserBaseWrap userwrap(uid);

	if (index < 1 || index > 2)
	{
		error_log("[GetAfairReward] index param invalid. uid=%u,index=%u", uid, index);
		throw std::runtime_error("param_error");
	}

	//判断是否有政务次数
	if (userwrap.Obj().mission_time < 1)
	{
		error_log("[GetAfairReward] affair time not enough.uid=%u,times=%hhu", uid, userwrap.Obj().mission_time);
		throw std::runtime_error("affair_time_not_enough");
	}

	//读取配置
	const GovernAffairConfig::AffairsItem & affair = GovernAffairConfigWrap().GetAffairById(userwrap.Obj().mission_id);
	const GovernAffairConfig::RewardItem & reward = affair.reward(index - 1);

	if (reward.has_paycash())
	{
		unsigned cash = reward.paycash();

		if (cash > 0)
		{
			userwrap.CostCash(cash, "GovernAffairReward");
		}
	}

	map<unsigned, unsigned> add_resource;
	//根据用户等级，计算系数
	int coefficient_int = GovernAffairConfigWrap().GetCoefficient(userwrap.Obj().level);
	float coefficient = (float)coefficient_int + userwrap.VIPPower().PolityTaskFactor();

	if (reward.has_coin())
	{
		unsigned coin = reward.coin() * coefficient;
		add_resource[resource_type_coin] = coin;
		userwrap.AddResource(add_resource, "GovernAffairReward");
	}
	else if (reward.has_wood())
	{
		unsigned wood = reward.wood() * coefficient;
		add_resource[resource_type_wood] = wood;
		userwrap.AddResource(add_resource, "GovernAffairReward");
	}
	else if (reward.has_food())
	{
		unsigned food = reward.food() * coefficient;
		add_resource[resource_type_food] = food;
		userwrap.AddResource(add_resource, "GovernAffairReward");
	}
	else if (reward.has_loyal()) //民忠
	{
		int loyal = reward.loyal();   //民忠不计算系数
		userwrap.Obj().loyal += loyal;

		if (userwrap.Obj().loyal > loyal_value_max)  //民忠上限200
		{
			userwrap.Obj().loyal = loyal_value_max;
		}
	}

	userwrap.Obj().mission_time -= 1;

	if (0 == userwrap.Obj().mission_time)
	{
		userwrap.Obj().mission_id = 0;
	}
	else   //还有政务次数，则重新刷新政务事件
	{
		RefreshAffair(uid);
	}

	userwrap.Save();

	respmsg->set_coin(userwrap.Obj().coin);
	respmsg->set_wood(userwrap.Obj().wood);
	respmsg->set_food(userwrap.Obj().food);
	respmsg->set_cash(userwrap.Obj().cash);

	respmsg->mutable_affair()->set_mission_id(userwrap.Obj().mission_id);
	respmsg->mutable_affair()->set_mission_time(userwrap.Obj().mission_time);
	respmsg->mutable_affair()->set_loyal(userwrap.Obj().loyal);

	return 0;
}

int LogicUserManager::Process(unsigned uid, ProtoGovernAffair::LoyalExchangeReq* req, ProtoGovernAffair::LoyalExchangeResp * respmsg)
{
	int ret = LoyalExchange(uid, respmsg);

	if (ret)
	{
		return ret;
	}

	//民忠兑换外部接口
	LoyalExternalInterface(uid);

	return 0;
}

int LogicUserManager::LoyalExternalInterface(unsigned uid)
{
	//todo 接入民忠兑换成就
    LogicAchievementManager::AchievementParam achievementparam;
	achievementparam.type = achievement_type_loyalexchange;

	LogicAchievementManager::Instance()->VerifyAchievementComplete(uid, achievementparam);

	return 0;
}

int LogicUserManager::LoyalExchange(unsigned uid, ProtoGovernAffair::LoyalExchangeResp * respmsg)
{
	DBCUserBaseWrap userwrap(uid);

	if (userwrap.Obj().loyal < loyal_exchange_limit)
	{
		error_log("[LoyalExchange] loyal not enough.uid=%u,loyal=%hhu", uid, userwrap.Obj().loyal);
		throw std::runtime_error("loyal_not_enough");
	}

	userwrap.Obj().loyal -= loyal_exchange_limit;

	//分别获取钞票、钢材、原油、黄金的产量
	//获得该类型的总产量
	int coin_productivity = LogicBuildManager::Instance()->Yields(uid, 1);
	int wood_productivity = LogicBuildManager::Instance()->Yields(uid, 2);
	int food_productivity = LogicBuildManager::Instance()->Yields(uid, 3);
	int iron_productivity = LogicBuildManager::Instance()->Yields(uid, 4);

	const GovernAffairConfig::GovernAffairs governconfig = GovernAffairConfigWrap().GovernAffair();

	int coin = coin_productivity * governconfig.loyal_reward().coin();
	int wood = wood_productivity * governconfig.loyal_reward().wood();
	int food = food_productivity * governconfig.loyal_reward().food();
	int iron = iron_productivity * governconfig.loyal_reward().iron();

	userwrap.AddResource(coin, wood, food, iron, "Loyal_Exchange");
	userwrap.Save();

	//返回给前端
	respmsg->mutable_coin()->set_value(coin);
	respmsg->mutable_coin()->set_total_value(userwrap.Obj().coin);

	respmsg->mutable_wood()->set_value(wood);
	respmsg->mutable_wood()->set_total_value(userwrap.Obj().wood);

	respmsg->mutable_food()->set_value(food);
	respmsg->mutable_food()->set_total_value(userwrap.Obj().food);

	respmsg->mutable_iron()->set_value(iron);
	respmsg->mutable_iron()->set_total_value(userwrap.Obj().iron);

	respmsg->set_loyal(userwrap.Obj().loyal);

	return 0;
}

int LogicUserManager::RefreshAffair(unsigned uid)
{
	//从配置中，获取所有政务事件
	const GovernAffairConfig::GovernAffairs &  affairs = GovernAffairConfigWrap().GovernAffair();
	vector<unsigned> rates;
	map<int, unsigned> id_related_index;   //事件id与集合下标的映射关系

	for(int i = 0; i < affairs.govern_affairs_size(); ++i)
	{
		unsigned rate = affairs.govern_affairs(i).rate();
		unsigned id = affairs.govern_affairs(i).id();

		rates.push_back(rate);
		id_related_index[i] = id;
	}

	//随机产生新事件
	int target = 0;
	LogicCommonUtil::TurnLuckTable(rates, rates.size(), target);
	unsigned mission_id = id_related_index[target];

	DBCUserBaseWrap userwrap(uid);
	userwrap.Obj().mission_id = mission_id;
	userwrap.Save();

	return 0;
}


int LogicUserManager::VerifyGovernAffairTimes(unsigned uid, unsigned buildid)
{
	int type = 0;

	try
	{
		type = DataBuildingManager::Instance()->BuildId2Type(buildid);  //获取建筑类型
	}
	catch(std::runtime_error & e)
	{
		error_log("[VerifyGovernAffairTimes] error happen. reason=%s", e.what());
		return R_ERROR;
	}

	//根据类型，获取子建筑等级之和
	vector<DBCBuildingData> vctBuilds;
	LogicBuildManager::Instance()->GetBuildingByType(uid, type, vctBuilds);
	int sublevel_sum = 0;

	for(int i = 0; i < vctBuilds.size(); ++i)
	{
		sublevel_sum += vctBuilds[i].level;
	}

	//读取配置，查看该等级之和是否有政务次数增加
	int times = GovernAffairConfigWrap().GetAddedAffairTimes(type, sublevel_sum);

	if (times > 0)
	{
		AddAndPushMissonTimes(uid, times);
	}

	return 0;
}

int LogicUserManager::AddAndPushMissonTimes(unsigned uid, unsigned times)
{
	AddMissionTimes(uid, times);

	DBCUserBaseWrap userwrap(uid);
	//政务次数从0到1
	if (1 == userwrap.Obj().mission_time)
	{
		//推送消息给前端
		ProtoPush::TimesAddPushReq * timesmsg = new ProtoPush::TimesAddPushReq;
		timesmsg->set_mission_times(userwrap.Obj().mission_time);

		LogicManager::Instance()->sendMsg(uid, timesmsg);
	}

	return 0;
}

int LogicUserManager::AddMissionTimes(unsigned uid, unsigned times)
{
	if (0 == times)
	{
		return 0;
	}

	DBCUserBaseWrap userwrap(uid);

	bool isNeedRefresh = false;

	if (0 == userwrap.Obj().mission_time)
	{
		isNeedRefresh = true;
	}

	userwrap.Obj().mission_time += times;

	if (userwrap.Obj().mission_time > mission_times_max)
	{
		userwrap.Obj().mission_time = mission_times_max;
	}

	userwrap.Save();

	return 0;
}

void LogicUserManager::OpReward(DBCUserBaseWrap& user
		, const ::RewardConfig::Reward& rewardCfg
		, const std::string& reason
		, User::RewardBagInfo* obj)
{
	try
	{
		unsigned uid = user.Obj().uid;

		if (rewardCfg.has_equips())
		{
			unsigned eqid = rewardCfg.equips().eqid();
			unsigned cnt = rewardCfg.equips().count();


			LogicEquipmentManager::Instance()->AddEquipment(uid, eqid, cnt, reason, obj->mutable_equips());

		}

		if (rewardCfg.has_base())
		{
			user.Reward(rewardCfg.base(), obj->mutable_base(), reason);
		}

		if (rewardCfg.has_hero()
				&& ! DataHeroManager::Instance()->isHeroExists(uid, rewardCfg.hero()))
		{
			LogicHeroManager::Instance()->UnlockHero(uid, rewardCfg.hero(), reason, obj->add_heros());
		}

		//部件
		if (rewardCfg.has_component())
		{
			if (! LogicCompProduceManager::Instance()->IsPackageFull(uid))
			{
				DataComponent component;
				const ::RewardConfig::Component& comp_cfg = rewardCfg.component();
				component.uid = uid;
				component.compid = comp_cfg.id();
				component.master = ComponentConfigWrap().GetComponentBaseConfig(comp_cfg.id()).master();
				component.level = comp_cfg.level();
				component.exp = comp_cfg.exp();
				if (comp_cfg.has_slave1())
				{
					component.slave1 = comp_cfg.slave1();
				}

				if (comp_cfg.has_slave2())
				{
					component.slave2 = comp_cfg.slave2();
				}

				if (comp_cfg.has_slave3())
				{
					component.slave3 = comp_cfg.slave3();
 				}
				LogicComponentManager::Instance()->AddComponentUnderlying(component, reason, obj->add_components());
			}
			else
			{
				error_log("componect_package_full. Provide failed. id: %d. op:%s"
						, rewardCfg.component().id(),reason.c_str());
			}
		}
	}
	catch(const std::exception& e)
	{
		error_log("uid:%u, %s", user.Obj().uid, e.what());
	}
}

int LogicUserManager::Process(unsigned uid, ProtoReward::VIPReq* req, ProtoReward::VIPResp* resp)
{
	DBCUserBaseWrap user(uid);

	if (user.Obj().vip_reward >= user.Obj().viplevel)
	{
		throw std::runtime_error("all_vip_reward_already_get");
	}

	std::map<unsigned, unsigned> mapEquips;
	std::string reason = "vip_reward_bag_op";
	for (int i = user.Obj().vip_reward + 1; i <= (int)user.Obj().viplevel; ++i)
	{
		const VIPCfgWrap::VIPRewardType& rewards = VIPCfgWrap().GetRewardByLevel(i);
		for (int k = 0; k < rewards.size(); ++k)
		{
			try
			{
				const ::RewardConfig::Reward& rewardCfg = rewards.Get(k);
				if (rewardCfg.has_equips())
				{
					unsigned eqid = rewardCfg.equips().eqid();
					unsigned cnt = rewardCfg.equips().count();

					LogicEquipmentManager::Instance()->AddEquipment(uid, eqid, cnt, reason, resp->mutable_equips());
					mapEquips[eqid] = mapEquips[eqid] + cnt;
				}

				if (rewardCfg.has_base())
				{
					user.Reward(rewardCfg.base(), resp->mutable_base(), reason);
				}

				if (rewardCfg.has_hero()
						&& ! DataHeroManager::Instance()->isHeroExists(uid, rewardCfg.hero()))
				{
					LogicHeroManager::Instance()->UnlockHero(uid, rewardCfg.hero(), reason, resp->add_heros());
				}
			}
			catch(const std::exception& e)
			{
				error_log("uid:%u, %s", uid, e.what());
			}
		}
	}

	user.SetVIPReward();

	for (std::map<unsigned, unsigned>::const_iterator it = mapEquips.begin();
			it != mapEquips.end(); ++it)
	{
		resp->add_equips_id(it->first);
		resp->add_equips_cnt(it->second);
	}

	resp->set_vip_level(user.Obj().viplevel);
	resp->set_vip_reward(user.Obj().vip_reward);

	return R_SUCCESS;
}

int LogicUserManager::Process(unsigned uid, User::OpenNormalGifgBagReq* req, User::OpenGifgBagResp* resp)
{
	unsigned id = req->eqid();
	unsigned ud = req->equd();

	DBCUserBaseWrap user(uid);

	std::string reason = "use_normal_gift_bag";
	unsigned rest_cnt = 0;
	LogicEquipmentManager::Instance()->UseEquipment(uid, id, ud, 1, reason, rest_cnt);

	//
	std::string open_code = "open_normal_gift_bag";
	const EquipmentConfig::NormalGiftBag& giftCfg = EquipCfgWrap().GetNormalGiftBag(id);
	for(int i = 0; i < giftCfg.gifts_size(); ++i)
	{
		const ::RewardConfig::Reward& rewardCfg = giftCfg.gifts(i);
		OpReward(user, rewardCfg, open_code, resp->mutable_bag_info());
	}

	resp->set_equd(ud);
	resp->set_count(rest_cnt);

	return R_SUCCESS;
}

int LogicUserManager::Process(unsigned uid, User::UseTimeLimitPropReq* req, User::UseTimeLimitPropResp* resp)
{
	unsigned id = req->eqid();
	unsigned ud = req->equd();
	unsigned cnt = 1;

	DBCUserBaseWrap user(uid);

	unsigned rest_cnt = 0;
	std::string reason = "use_limit_prop_op";
	LogicEquipmentManager::Instance()->UseEquipment(uid, id, ud, cnt, reason, rest_cnt);

	LogicTimeLimitPropMgr::Instance()->UseProp(uid, id);

	resp->set_equd(ud);
	resp->set_count(rest_cnt);

	DBCTimeLimitPropWrap(uid, id).FullMessage(resp->mutable_item());

	return R_SUCCESS;
}



void LogicUserManager::SetBotPlayerData(unsigned uid, const BotConfig::BotPlayer* obj)
{
	if (NULL == obj) return ;

	DBCUserBaseWrap user(uid);
	user.FullData(obj);

	LogicScienceMgr::Instance()->SetBotPlayerData(uid, obj);
	LogicWeaponsMgr::Instance()->SetBotPlayerData(uid, obj);

	LogicHeroManager::Instance()->AdminFireHero(uid, true);
	LogicEquipmentManager::Instance()->AdminClear(uid, true);
	for(int i=0;i<obj->hero_size();++i)
		LogicHeroManager::Instance()->AdminRecuruitHero(uid, &obj->hero(i), true);

	LogicResourceManager::Instance()->Sync(user.Obj());
}

void LogicUserManager::GetLuckBagGiftIndexs(const EquipmentConfig::LuckGiftBag& cfg, std::vector<int>& result)
{
	result.clear();
	int numbers = cfg.numbers();

	std::vector<int> vIndexs;
	std::vector<unsigned> vProb;
	for (int i = 0; i < cfg.gifts_size(); i++)
	{
		vIndexs.push_back(i);
		vProb.push_back(cfg.gifts(i).prob());
	}

	//根据概率表产生numbers个物品
	while(numbers > 0)
	{
		int index = LogicCommonUtil::GetRandomIndex(vProb);
		result.push_back(vIndexs[index]);

		vIndexs.erase(vIndexs.begin() + index);
		vProb.erase(vProb.begin() + index);

		--numbers;
	}
}

int LogicUserManager::Process(unsigned uid, User::OpenLuckGifgBagReq* req, User::OpenGifgBagResp* resp)
{
	unsigned id = req->eqid();
	unsigned ud = req->equd();

	DBCUserBaseWrap user(uid);

	std::string reason = "use_luck_gift_bag";
	unsigned rest_cnt = 0;
	LogicEquipmentManager::Instance()->UseEquipment(uid, id, ud, 1, reason, rest_cnt);

	std::string open_code = "open_luck_gift_bag";
	const EquipmentConfig::LuckGiftBag& giftCfg = EquipCfgWrap().GetLuckGiftBag(id);

	std::vector<int> vIndexs;
	this->GetLuckBagGiftIndexs(giftCfg, vIndexs);
	for (size_t i = 0; i < vIndexs.size(); ++i)
	{
		//这里做一下转换
		const ::EquipmentConfig::LuckGiftBagItem& GiftCfg = giftCfg.gifts(vIndexs[i]);
		::RewardConfig::Reward rewardcfg;
		if (GiftCfg.has_equips())
		{
			rewardcfg.mutable_equips()->CopyFrom(GiftCfg.equips());
		}

		if (GiftCfg.has_hero())
		{
			rewardcfg.set_hero(GiftCfg.hero());
		}

		if (GiftCfg.has_base())
		{
			rewardcfg.mutable_base()->CopyFrom(GiftCfg.base());
		}

		if (GiftCfg.has_component())
		{
			rewardcfg.mutable_component()->CopyFrom(GiftCfg.component());
		}
		OpReward(user, rewardcfg, reason, resp->mutable_bag_info());
	}

	resp->set_equd(ud);
	resp->set_count(rest_cnt);

	return R_SUCCESS;
}

int LogicUserManager::Process(unsigned uid, User::UseUpdateSmeltPropReq* req, User::UseUpdateSmeltPropResp* resp)
{
	//装备
	DBCUserBaseWrap user(uid);
	unsigned prop_id = req->prop_id();
	unsigned prop_ud = req->prop_ud();

	if (! LogicEquipmentManager::Instance()->IsOwnerEquipments(uid, prop_id, prop_ud, 1))
	{
		throw std::runtime_error("equips_count_not_enough");
	}
	//
	unsigned equip_ud = req->equip_ud();

	DBCEquipmentWrap equipment(uid, equip_ud);
	if (equipment.Obj().star < 3)
	{
		throw std::runtime_error("equipment_star_not_enough");
	}

	//
	if (equipment.IsReachLevel(5))
	{
		throw std::runtime_error("already_reach_5_level");
	}


	if (equipment.IsFullLevel())
	{
		throw std::runtime_error("equipment_level_is_full");
	}

	unsigned rest_cnt = 0;
	std::string reason = "update_smelt_prop_op";
	LogicEquipmentManager::Instance()->UseEquipment(uid, prop_id, prop_ud, 1, reason, rest_cnt);

	equipment.UpgradeAttr();

	if (equipment.IsDressed())
	{
		DBCHeroWrap(uid, equipment.Obj().heroid).FullMessage(resp->mutable_hero(), true);
	}

	equipment.Obj().SetMessage(resp->mutable_equip());
	resp->set_prop_ud(prop_ud);
	resp->set_prop_cnt(rest_cnt);

	return R_SUCCESS;
}

int LogicUserManager::Process(unsigned uid, User::UseSpecificSmeltPropReq* req, User::UseSpecificSmeltPropResp* resp)
{
	//装备
	DBCUserBaseWrap user(uid);
	unsigned prop_id = req->prop_id();
	unsigned prop_ud = req->prop_ud();

	if (! LogicEquipmentManager::Instance()->IsOwnerEquipments(uid, prop_id, prop_ud, 1))
	{
		throw std::runtime_error("equips_count_not_enough");
	}
	//
	unsigned equip_ud = req->equip_ud();
	unsigned type     = req->type();

	DBCEquipmentWrap equipment(uid, equip_ud);

	unsigned rest_cnt = 0;
	std::string reason = "specific_smelt_prop_op";
	LogicEquipmentManager::Instance()->UseEquipment(uid, prop_id, prop_ud, 1, reason, rest_cnt);

	equipment.AssignAttr(type);

	if (equipment.IsDressed())
	{
		DBCHeroWrap(uid, equipment.Obj().heroid).FullMessage(resp->mutable_hero(), true);
	}

	equipment.Obj().SetMessage(resp->mutable_equip());
	resp->set_prop_ud(prop_ud);
	resp->set_prop_cnt(rest_cnt);

	return R_SUCCESS;
}

