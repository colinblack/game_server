/*
 * UserCfgWrap.cpp
 *
 *  Created on: 2016-9-12
 *      Author: dawx62fac
 */

#include "ConfigWrap.h"

UserCfgWrap::UserCfgWrap()
	: cfg_(ConfigManager::Instance()->user.m_config)
{
}

const UserCfg::User& UserCfgWrap::User() const
{
	return cfg_;
}

const UserCfg::UserBase& UserCfgWrap::UserBase() const
{
	return cfg_.user_init();
}

///////////////////////////////////////////////////////////////////////////////
ResourceCfgWrap::ResourceCfgWrap()
	: cfg_(ConfigManager::Instance()->resource.m_config)
{
}

unsigned ResourceCfgWrap::GetMultiple(bool isFree)
{
	unsigned nTotal = 0;
	for (int i = 0; i < cfg_.flamen_size(); i++)
	{
		nTotal += isFree ? cfg_.flamen(i).free_prob() : cfg_.flamen(i).buy_prob();
	}

	int nRandomVal = Math::GetRandomInt(nTotal);

	for (int i = 0; i < cfg_.flamen_size(); ++i)
	{
		int nVal = isFree ? cfg_.flamen(i).free_prob() : cfg_.flamen(i).buy_prob();
		if (nRandomVal < nVal)
		{
			return cfg_.flamen(i).multiple();
		}

		nRandomVal -= nVal;
	}

	error_log("random_flamen_mul_error, nTotal: %d", nTotal);
	throw std::runtime_error("random_flamen_mul_error");
}
///////////////////////////////////////////////////////////////////////////////
ScienceCfgWrap::ScienceCfgWrap()
	: cfg_(ConfigManager::Instance()->sciences.m_config)
{
}

void ScienceCfgWrap::GetIdsByType(ScienceType type, std::vector<uint16_t>& vIds) const
{
	vIds.clear();
	for (int i = 0; i < cfg_.sciences_size(); i++)
	{
		if (cfg_.sciences(i).type() == (unsigned)type)
		{
			vIds.push_back(cfg_.sciences(i).id());
		}
	}

	if (vIds.empty())
	{
		error_log("science_type: %d", type);
		throw std::runtime_error("science_type_params_error");
	}
}

const ScienceConfig::ScienceItem& ScienceCfgWrap::Item(unsigned id) const
{
	for (int i = 0; i < cfg_.sciences_size(); i++)
	{
		if (cfg_.sciences(i).id() == id)
		{
			return cfg_.sciences(i);
		}
	}

	error_log("science_id: %d", id);
	throw std::runtime_error("science_id_cfg_error");
}

bool ScienceCfgWrap::IsExistId(unsigned id) const
{
	for (int i = 0; i < cfg_.sciences_size(); i++)
	{
		if (cfg_.sciences(i).id() == id)
		{
			return true;
		}
	}

	return false;
}

///////////////////////////////////////////////////////////////////////////////
WeaponCfgWrap::WeaponCfgWrap()
	: cfg_(ConfigManager::Instance()->weapon.m_config)
{
}

const WeaponConfig::WeaponItem& WeaponCfgWrap::Item(unsigned id) const
{
	const std::map<unsigned, unsigned>& vMap = ConfigManager::Instance()->m_weapon_index;
	std::map<unsigned, unsigned>::const_iterator it = vMap.find(id);
	if (it == vMap.end())
	{
		error_log("weapon_cfg_error. id:%d", id);
		throw std::runtime_error("weapon_cfg_error");
	}

	return cfg_.weapons(it->second);
}

const WeaponConfig::WeaponLvL& WeaponCfgWrap::LvL(unsigned id, unsigned level) const
{
	typedef map<unsigned, std::map<unsigned, unsigned> > W_MAP;
	const W_MAP& vMap =  ConfigManager::Instance()->m_weapon_lvl_index;
	W_MAP::const_iterator it = vMap.find(id);
	if (it == vMap.end())
	{
		error_log("weapon_cfg_error. id:%d", id);
		throw std::runtime_error("weapon_cfg_error");
	}

	std::map<unsigned, unsigned>::const_iterator l_it = it->second.find(level);
	if (l_it == it->second.end())
	{
		error_log("weapon_cfg_error. id:%d,level:%d", id, level);
		throw std::runtime_error("weapon_cfg_error");
	}

	return this->Item(id).lvls(l_it->second);
}
///////////////////////////////////////////////////////
NPCPassCfgWrap::NPCPassCfgWrap()
	: cfg_(ConfigManager::Instance()->passSystem.m_config)
{
}

const PassSystemConfig::System& NPCPassCfgWrap::SystemCfg() const
{
	return cfg_;
}

const PassSystemConfig::PassItem& NPCPassCfgWrap::Item(unsigned id) const
{
	const std::map<unsigned, unsigned>& vMap = ConfigManager::Instance()->m_pass_index;
	std::map<unsigned, unsigned>::const_iterator it = vMap.find(id);
	if (it == vMap.end())
	{
		error_log("pass_npc_cfg_error. id:%d", id);
		throw std::runtime_error("pass_npc_cfg_error");
	}

	return cfg_.all_upc_pass(it->second);
}
///////////////////////////////////////////////////////////////////////////
ExploitBoxCfgWrap::ExploitBoxCfgWrap()
	: cfg_(ConfigManager::Instance()->exploit.m_config)
{

}

const ExploitBoxConfig::ExploitBox& ExploitBoxCfgWrap::Box() const
{
	return cfg_.exploit();
}

const ExploitBoxConfig::ExploitItem& ExploitBoxCfgWrap::Item(unsigned level) const
{
	for (int i = 0; i < cfg_.exploit().out_size(); ++i)
	{
		if (cfg_.exploit().out(i).box_level() == level)
		{
			return cfg_.exploit().out(i);
		}
	}

	error_log("exploit_box_cfg_error. level:%d", level);
	throw std::runtime_error("exploit_box_cfg_error");
}

unsigned ExploitBoxCfgWrap::GetExploitBoxStage(unsigned level, unsigned exploit) const
{
	const ExploitBoxConfig::ExploitItem& item_cfg = Item(level);
	for (int i = 0; i < item_cfg.exploit_amount_size(); ++i)
	{
		if (exploit < item_cfg.exploit_amount(i))
		{
			return i;
		}
	}

	return item_cfg.exploit_amount_size();
}

unsigned ExploitBoxCfgWrap::GetBoxCntByStage(unsigned level, int stage) const
{
	const ExploitBoxConfig::ExploitItem& itemcfg = Item(level);
	if (stage < 1 || stage > itemcfg.box_cnt_size())
	{
		return 0;
	}

	return itemcfg.box_cnt(stage - 1) + GetExtraBoxByStage(stage, Box().random_mul());
}

unsigned ExploitBoxCfgWrap::GetExtraBoxByStage(int stage, const ExploitBoxConfig::ExploitRandomMul& cfg) const
{
	if (stage == 3)
	{
		return GetRandomValue(cfg.stage_3());
	}
	else if (stage == 5)
	{
		return GetRandomValue(cfg.stage_5());
	}

	return 0;
}

unsigned ExploitBoxCfgWrap::GetRandomValue(const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >& values) const
{
	if (values.size() <= 0)
	{
		return 0;
	}

	int index = Math::GetRandomInt(values.size());
	return values.Get(index);
}

unsigned ExploitBoxCfgWrap::GetRewardMul(const ExploitBoxConfig::ExploitReward& boxReward) const
{
	if (! boxReward.is_mul())
	{
		return 1;
	}

	const int nMul[4] = {1, 2, 3, 5};

	if (cfg_.exploit().prob_size() != 4)
	{
		error_log("expoit_prob_cfg_error");
		throw std::runtime_error("expoit_prob_cfg_error");
	}

	int nTotal = 0;
	for (int i = 0; i < cfg_.exploit().prob_size(); i++)
	{
		nTotal += cfg_.exploit().prob(i);
	}

	int nRandom = Math::GetRandomInt(nTotal);
	int index = -1;
	for (int i = 0; i < cfg_.exploit().prob_size(); i++)
	{
		if (nRandom < (int)cfg_.exploit().prob(i))
		{
			index = i;
			break;
		}

		nRandom -= cfg_.exploit().prob(i);
	}

	if (index < 0)
	{
		error_log("expoit_reward_mul_random_error");
		throw std::runtime_error("expoit_reward_mul_random_error");
	}

	return nMul[index];

}

const CommonGiftConfig::BaseReward& ExploitBoxCfgWrap::BaseReward(unsigned level) const
{
	const ExploitBoxConfig::ExploitItem& itemcfg = Item(level);
	std::vector<unsigned> vProb;
	for (int i = 0; i < itemcfg.base_reward_size(); ++i)
	{
		vProb.push_back(itemcfg.base_reward(i).prob());
	}

	if (vProb.empty())
	{
		throw std::runtime_error("expoit_box_reward_base_cfg_error");
	}

	int index = LogicCommonUtil::GetRandomIndex(vProb);

	return itemcfg.base_reward(index).base();
}

const ExploitBoxConfig::ExploitReward& ExploitBoxCfgWrap::BoxReward(unsigned level) const
{
	const ExploitBoxConfig::ExploitItem& itemcfg = Item(level);
	int nTotal = 0;
	for (int i = 0; i < itemcfg.reward_size(); ++i)
	{
		nTotal += itemcfg.reward(i).prob();
	}

	if (nTotal == 0)
	{
		error_log("expoit_box_reward_cfg_error, level: %d", level);
		throw std::runtime_error("expoit_box_reward_cfg_error");
	}

	int nRandom = Math::GetRandomInt(nTotal);
	for (int  i = 0; i < itemcfg.reward_size(); ++i)
	{
		if (nRandom < (int)itemcfg.reward(i).prob())
		{
			return itemcfg.reward(i);
		}

		nRandom -= itemcfg.reward(i).prob();
	}

	error_log("expoit_box_reward_random_error, level: %d", level);
	throw std::runtime_error("expoit_box_reward_random_error");
}

//////////////////////////////////////////////////////////////////////////
IntegralTimeCfgWrap::IntegralTimeCfgWrap()
	: cfg_(ConfigManager::Instance()->integral_time.m_config)
{
}

const ::RewardConfig::IntegralReward& IntegralTimeCfgWrap::Reward() const
{
	int nTotal  = 0;
	for (int i = 0; i < cfg_.integral_time_size(); i++)
	{
		nTotal += cfg_.integral_time(i).prob();
	}

	if (nTotal == 0)
	{
		error_log("initegral_time_reward_cfg_error");
		throw std::runtime_error("initegral_time_reward_cfg_error");
	}

	int nRandom = Math::GetRandomInt(nTotal);
	for (int  i = 0; i < cfg_.integral_time_size(); ++i)
	{
		if (nRandom < (int)cfg_.integral_time(i).prob())
		{
			return cfg_.integral_time(i);
		}

		nRandom -= cfg_.integral_time(i).prob();
	}

	error_log("initegral_time_reward_random_error");
	throw std::runtime_error("initegral_time_reward_random_error");
}
///////////////////////////////////////////////////////////////////////////
PkFieldCfgWrap::PkFieldCfgWrap()
	: cfg_(ConfigManager::Instance()->pk_field.m_config)
{
}

const CommonGiftConfig::BaseReward& PkFieldCfgWrap::GetReward(unsigned rank)
{
	for (int i = 0; i < cfg_.pk_field().size(); ++i)
	{
		const RewardConfig::PkFieldReward& item = cfg_.pk_field().Get(i);
		if (! item.has_rank_end())
		{
			if (item.rank_start() == rank)
			{
				return item.base();
			}
		}
		else
		{
			if (rank >= item.rank_start() && rank <= item.rank_end())
			{
				return item.base();
			}
		}
	}

	error_log("pk_field_rank_reward: %d", rank);
	throw std::runtime_error("rank_out_reward");
}
///////////////////////////////////////////////////////////////////////////
VIPCfgWrap::VIPCfgWrap()
	: cfg_(ConfigManager::Instance()->vip.m_config.vip())
{
}

unsigned VIPCfgWrap::GetVIPLevel(unsigned cash) const
{
	for (int i = 0; i < cfg_.cash_size(); ++i)
	{
		if (cash < cfg_.cash(i))
		{
			return i;
		}
	}

	return cfg_.cash_size();
}

const VIPCfgWrap::VIPRewardType& VIPCfgWrap::GetRewardByLevel(unsigned level) const
{
	switch (level)
	{
	case 1: return cfg_.reward_1();
	case 2: return cfg_.reward_2();
	case 3: return cfg_.reward_3();
	case 4: return cfg_.reward_4();
	case 5: return cfg_.reward_5();
	case 6: return cfg_.reward_6();
	case 7: return cfg_.reward_7();
	case 8: return cfg_.reward_8();
	case 9: return cfg_.reward_9();
	case 10: return cfg_.reward_10();
	default: break;
	}

	error_log("vip_reward_cfg_error. level: %u", level);
	throw std::runtime_error("vip_reward_cfg_error.");
}

const VIPConfig::UVIPBasePower& VIPCfgWrap::BasePower() const
{
	return cfg_.base_power();
}

const VIPConfig::UVIPItem& VIPCfgWrap::Cfg() const
{
	return cfg_;
}

///////////////////////////////////////////////////////////////////////////
CountryTaskCfgWrap::CountryTaskCfgWrap()
	: cfg_(ConfigManager::Instance()->country_task.m_config.country_task())

{
}

unsigned CountryTaskCfgWrap::GetBaseIndex(unsigned open_days, unsigned kills) const
{
	int index = -1;
	for (int i = cfg_.base_reward_size() - 1; i >= 0; --i)
	{
		if (open_days >= cfg_.base_reward(i).day())
		{
			index = i;
			break;
		}
	}

	if (index < 0)
	{
		error_log("country_task_base_reward_cfg_error.");
		throw std::runtime_error("country_task_base_reward_cfg_error.");
	}

	return index;
}

unsigned CountryTaskCfgWrap::GetKillsIndex(unsigned open_days, unsigned kills) const
{
	unsigned index = GetBaseIndex(open_days, kills);

	int kill_index = 0;
	const RewardConfig::CountryTaskBaseItem& baseCfg = cfg_.base_reward(index);
	for (int i = baseCfg.kills_size() - 1; i >= 0; i--)
	{
		if (kills > baseCfg.kills(i))
		{
			kill_index = i + 1;
			break;
		}
	}

	return kill_index;
}

int CountryTaskCfgWrap::GetTechCoefficent(unsigned level)
{
	if (level > cfg_.tech_coefficient_size())
	{
		throw runtime_error("wrong_tech_level");
	}

	return cfg_.tech_coefficient(level - 1);
}

float CountryTaskCfgWrap::GetBaseFactor(unsigned open_days, unsigned kills) const
{
	unsigned kills_index = GetKillsIndex(open_days, kills);

	if ((int)kills_index >= cfg_.base_factor_size())
	{
		error_log("country_task_reward_cfg_base_factor_error. size:%d, index:%d"
				, cfg_.base_factor_size(), kills_index);
	}

	return cfg_.base_factor(kills_index);
}

float CountryTaskCfgWrap::GetExpandFactor(unsigned open_days, unsigned kills) const
{
	unsigned kills_index = GetKillsIndex(open_days, kills);

	if ((int)kills_index >= cfg_.expand_factor_size())
	{
		error_log("country_task_reward_cfg_expand_factor_error. size:%d, index:%d"
				, cfg_.expand_factor_size(), kills_index);
	}

	return cfg_.expand_factor(kills_index);
}

const CommonGiftConfig::BaseReward& CountryTaskCfgWrap::BaseCountryReward(unsigned open_days, unsigned kills)
{
	unsigned base_index = GetBaseIndex(open_days, kills);

	//const RewardConfig::CountryTaskItem& task_cfg = cfg_.base


	if ((int)base_index >= cfg_.base_reward_size())
	{
		error_log("country_task_base_reward_cfg_error. size:%d, index:%d"
				, cfg_.base_reward_size(), base_index);
		throw std::runtime_error("country_task_base_reward_cfg_error.");
	}

	return cfg_.base_reward(base_index).base();
}

const CountryTaskCfgWrap::PersonalRewardType& CountryTaskCfgWrap::PersonalReward(unsigned task_no) const
{
	if (task_no == 1)
	{
		return cfg_.reward_1();
	}
	else if(task_no == 2)
	{
		return cfg_.reward_2();
	}
	else if (task_no == 3)
	{
		return cfg_.reward_3();
	}
	else
	{
		error_log("CountryTask_PersonalReward_cfg_error. task_no: %d", task_no);
		throw std::runtime_error("CountryTask_PersonalReward_cfg_error");
	}
}
///////////////////////////////////////////////////////////////////////////
OfficialCfgWrap::OfficialCfgWrap()
	: cfg_(ConfigManager::Instance()->official.m_config)
{

}

const OfficialConfig::OfficialJob& OfficialCfgWrap::GetJobCfg(unsigned departement, unsigned job) const
{
	const OfficialConfig::OfficialDepartment& department_cfg = GetDepartment(departement);
	for (int i = 0; i < department_cfg.job_size(); i++)
	{
		if (department_cfg.job(i).id() == job)
		{
			return department_cfg.job(i);
		}
	}

	//找不到，找同类型的配置
	if (job > 0)
	{
		for (int i = 0; i < department_cfg.job_size(); i++)
		{
			if ((department_cfg.job(i).id() / 10) == (job / 10))
			{
				return department_cfg.job(i);
			}
		}
	}

	error_log("official_cfg_error. department: %u, job: %u", departement, job);
	throw std::runtime_error("official_cfg_error");
}

const OfficialConfig::OfficialDepartment& OfficialCfgWrap::GetDepartment(unsigned departement) const
{
	for (int i = 0; i < cfg_.official_size(); i++)
	{
		if (cfg_.official(i).department() == departement)
		{
			return cfg_.official(i);
		}
	}

	error_log("official_cfg_error. department: %u", departement);
	throw std::runtime_error("official_cfg_error");
}

//unsigned OfficialCfgWrap::YieldAdd(unsigned departement, unsigned job)
//{
//	const OfficialConfig::OfficialJob& jobCfg = GetJobCfg(departement, job);
//
//}
///////////////////////////////////////////////////////////////////////////
PassActivityCfgWrap::PassActivityCfgWrap()
	: cfg_(ConfigManager::Instance()->pass_activity.m_config)
{
}

const ActivityConfig::PassActivity& PassActivityCfgWrap::Cfg() const
{
	return cfg_;
}

const ActivityConfig::PassActivityItem& PassActivityCfgWrap::Item(unsigned id) const
{
	return cfg_.pass_activity(Index(id));
}

int PassActivityCfgWrap::Index(unsigned id) const
{
	for (int i = 0; i < cfg_.pass_activity_size(); i++)
	{
		if (id == cfg_.pass_activity(i).id())
		{
			return i;
		}
	}

	error_log("pass_activity_cfg_error. id: %u", id);
	throw std::runtime_error("pass_activity_cfg_error");
}

///////////////////////////////////////////////////////////////////////////
MineCfgWrap::MineCfgWrap()
	: cfg_(ConfigManager::Instance()->mine.m_config.mine())
{
}

int MineCfgWrap::Exp2Level(unsigned exp) const
{
	const MineConfig::Normal& normal = NormalCfg();
	for (int i = normal.exp_size() - 1; i >= 0; i--)
	{
		if (exp >= normal.exp(i))
		{
			return i + 1;
		}
	}

	error_log("mine_cfg_error. exp: %d", exp);
	throw std::runtime_error("not_config_exp_table");
}

const MineConfig::Normal& MineCfgWrap::NormalCfg() const
{
	return cfg_.normal();
}

int MineCfgWrap::GetNormalOpenCost(unsigned exp) const
{
	const MineConfig::Normal& normal = NormalCfg();
	int level = Exp2Level(exp);
	if (level > normal.open_cost_size())
	{
		error_log("mine_open_cost_cfg_error. level: %d", level);
		throw std::runtime_error("mine_open_cost_cfg_error");
	}

	return normal.open_cost(level - 1);
}

int MineCfgWrap::GetKingdomOpenCost() const
{
	return cfg_.kingdom().open_cost();
}

int MineCfgWrap::GetNormalDonateCost() const
{
	return cfg_.normal().donate_cost();
}

int MineCfgWrap::GetNormalDonateCnt(int level) const
{
	const MineConfig::Normal& normal = NormalCfg();
	if (level <= 0 || level > normal.donate_cnt_size())
	{
		error_log("mine_cfg_donate_cnt. level: %d", level);
		throw std::runtime_error("mine_cfg_donate_cnt_error");
	}

	return normal.donate_cnt(level - 1);
}

int MineCfgWrap::GetKingdomDonateCnt() const
{
	return cfg_.kingdom().donate_cnt();
}

int MineCfgWrap::GetKingdomReward() const
{
	return cfg_.kingdom().reward();
}

int MineCfgWrap::HarvestNormalMine(int level) const
{
	const MineConfig::Normal& normal = NormalCfg();
	if (level <= 0 || level > normal.harvest_size())
	{
		error_log("mine_cfg_harvest. level: %d", level);
		throw std::runtime_error("mine_cfg_harvest_error");
	}

	return normal.harvest(level - 1);
}

int MineCfgWrap::HarvestKingdomMine(int level) const
{
	int size = cfg_.kingdom().harvest_size();
	if (level <= 0 || size <= 0)
	{
		error_log("mine_cfg_harvest. level: %d", level);
		throw std::runtime_error("mine_cfg_harvest_error");
	}

	if (level > size)
	{
		return	cfg_.kingdom().harvest(size - 1);
	}

	return	cfg_.kingdom().harvest(level - 1);
}

int MineCfgWrap::GetKingdomDonateCost() const
{
	return cfg_.kingdom().donate_cost();
}

int MineCfgWrap::GetOpenExp() const
{
	return cfg_.open_exp();
}

int MineCfgWrap::GetDonateExp() const
{
	return cfg_.donate_exp();
}
///////////////////////////////////////////////////////////////////////////
ActivityCfgWrap::ActivityCfgWrap()
	: cfg_(ConfigManager::Instance()->activity.m_config)
{
}

const User::ActivityItem& ActivityCfgWrap::GetItem(unsigned id) const
{
	for(int i = 0; i < cfg_.act_size(); ++i)
	{
		if (cfg_.act(i).id() == id)
		{
			return cfg_.act(i);
		}
	}

	error_log("unknown_activity_cfg. id: %u", id);
	throw std::runtime_error("unknown_activity_cfg");
}
//////////////////////////////////////////////////////////////////////////
LimitShopCfgWrap::LimitShopCfgWrap()
	: cfg_(ConfigManager::Instance()->limit_shop.m_config)
{
}

const ShopConfig::LimitShopItems& LimitShopCfgWrap::GetItems(unsigned opendays) const
{
	for (int i = cfg_.limit_shop_size() - 1; i >= 0; --i)
	{
		if (opendays >= cfg_.limit_shop(i).open_day())
		{
			return cfg_.limit_shop(i);
		}
	}

	error_log("limit_shop_items_cfg_error.");
	throw std::runtime_error("limit_shop_items_cfg_error.");
}

const ShopConfig::LimitShopItem& LimitShopCfgWrap::GetItem(unsigned opendays, unsigned id) const
{
	const ShopConfig::LimitShopItems& itemsCfg = GetItems(opendays);

	for (int i = 0; i < itemsCfg.items_size(); i++)
	{
		if (itemsCfg.items(i).id() == id)
		{
			return itemsCfg.items(i);
		}
	}

	error_log("limit_shop_cfg_error. id: %u", id);
	throw std::runtime_error("limit_shop_cfg_error");
}
///////////////////////////////////////////////////////////////////////////
TouchGoldCfgWrap::TouchGoldCfgWrap()
	: cfg_(ConfigManager::Instance()->touch_gold.m_config)
{

}

const  ActivityConfig::TouchGoldItem& TouchGoldCfgWrap::GetItem(unsigned tomb_id) const
{
	for (int i = 0; i < cfg_.touch_gold_size(); i++)
	{
		if (cfg_.touch_gold(i).id() == tomb_id)
		{
			return cfg_.touch_gold(i);
		}
	}

	error_log("touch_gold_cfg_error. id: %u", tomb_id);
	throw std::runtime_error("touch_gold_cfg_error");
}

unsigned TouchGoldCfgWrap::Output(unsigned tomb_id) const
{
	const ActivityConfig::TouchGoldItem& item = GetItem(tomb_id);
	std::vector<unsigned> vProb;
	for (int i = 0; i < item.out_size(); i++)
	{
		vProb.push_back(item.out(i).prob());
	}

	int index = LogicCommonUtil::GetRandomIndex(vProb);
	return  item.out(index).value();
}

unsigned TouchGoldCfgWrap::GetUnlockCost(unsigned tomb_id) const
{
	const ActivityConfig::TouchGoldItem& item = GetItem(tomb_id);
	if (item.has_unlock())
	{
		return item.unlock();
	}

	throw std::runtime_error("the_tomb_cannot_unlock");
}
///////////////////////////////////////////////////////////////////////////
HugeDiscountCfgWrap::HugeDiscountCfgWrap()
	: cfg_(ConfigManager::Instance()->huge_discount.m_config)
{
}

unsigned HugeDiscountCfgWrap::GetOpenCash(unsigned id) const
{
	return PageItemCfg(id).cash_account();
}

const ::ActivityConfig::HugeDiscountPage& HugeDiscountCfgWrap::PageItemCfg(unsigned id) const
{
	for (int i = 0; i < cfg_.huge_discount_size(); i++)
	{
		if (cfg_.huge_discount(i).page_id() == id)
		{
			return cfg_.huge_discount(i);
		}
	}

	error_log("cfg_error. id: %u", id);
	throw std::runtime_error("huge_discount_page_id_cfg_error.");
}

const ::ActivityConfig::HugeDiscountGood& HugeDiscountCfgWrap::GoodCfg(unsigned page_id, unsigned open_day) const
{
	const ::ActivityConfig::HugeDiscountPage& page_cfg = PageItemCfg(page_id);
	for (int i = page_cfg.goods_size() - 1; i >= 0; --i)
	{
		if (open_day >= page_cfg.goods(i).open_day())
		{
			return page_cfg.goods(i);
		}
	}

	error_log("huge_discount_items_cfg_error. page_id: %u, oepn_day: %u", page_id, open_day);
	throw std::runtime_error("huge_discount_items_cfg_error.");
}

const ::ActivityConfig::HugeDiscountItem& HugeDiscountCfgWrap::GoodItemCfg(unsigned page_id, unsigned id, unsigned open_day) const
{
	const ::ActivityConfig::HugeDiscountGood& good_cfg = GoodCfg(page_id, open_day);
	for (int i = 0; i < good_cfg.items_size(); i++)
	{
		if( good_cfg.items(i).id() == id)
		{
			return good_cfg.items(i);
		}
	}

	error_log("cfg_error. page_id:%u, id: %u, open_day: %u", page_id, id, open_day);
	throw std::runtime_error("huge_discount_page_id_cfg_error.");
}

///////////////////////////////////////////////////////////////////////////
CashBackCfgWrap::CashBackCfgWrap()
	: cfg_(ConfigManager::Instance()->cash_back.m_config)
{
}

int CashBackCfgWrap::MaxId() const
{
	int size = cfg_.cash_back_size();
	if (size <= 0)
	{
		error_log("cash_back_cfg_error. ");
		throw std::runtime_error("cash_back_cfg_error");
	}

	return cfg_.cash_back(size - 1).id();
}

const ActivityConfig::CashBackItem& CashBackCfgWrap::GetItem(unsigned id) const
{
	for (int i = 0; i < cfg_.cash_back_size(); i++)
	{
		if (cfg_.cash_back(i).id() == id)
		{
			return cfg_.cash_back(i);
		}
	}

	error_log("cash_back_cfg_error. id: %u", id);
	throw std::runtime_error("cash_back_cfg_error");
}

///////////////////////////////////////////////////////////////////////////
SmeltActivityCfgWrap::SmeltActivityCfgWrap()
	: cfg_(ConfigManager::Instance()->smelt_activity.m_config)
{

}

const ActivityConfig::SmeltActivityItem& SmeltActivityCfgWrap::GetItem(unsigned id) const
{
	for (int i = 0; i < cfg_.smelt_activity_size(); i++)
	{
		if (cfg_.smelt_activity(i).id() == id)
		{
			return cfg_.smelt_activity(i);
		}
	}

	error_log("smelt_activity_cfg_error. id: %u", id);
	throw std::runtime_error("smelt_activity");
}

const ActivityConfig::SmeltActivity& SmeltActivityCfgWrap::Cfg() const
{
	return cfg_;
}

////////////////////////////////////////////////////////////////////////////
EquipShopConfigWrap::EquipShopConfigWrap():
		m_equipshop(ConfigManager::Instance()->equipshop.m_config)
{

}

bool EquipShopConfigWrap::IsOrder(unsigned eqid)
{
	if (m_equipshop.special().order(0u) <= eqid && m_equipshop.special().order(1u) >= eqid)
	{
		return true;
	}

	return false;
}

bool EquipShopConfigWrap::IsIron(unsigned eqid)
{
	if (m_equipshop.special().iron(0u) <= eqid && m_equipshop.special().iron(1u) >= eqid)
	{
		return true;
	}

	return false;
}

int EquipShopConfigWrap::GetNumByEqid(unsigned eqid)
{
	int num = 0;

	for(int i = 0; i < m_equipshop.eqid_num_size(); ++i)
	{
		if (m_equipshop.eqid_num(i).eqid() == eqid)
		{
			num = m_equipshop.eqid_num(i).num();
			break;
		}
	}

	return num;
}

TavernConfigWrap::TavernConfigWrap():
		m_taverncfg(ConfigManager::Instance()->tavern.m_config)
{

}

const TavernConfig::HeroRecruit&  TavernConfigWrap::Tavern() const
{
	return m_taverncfg;
}

unsigned TavernConfigWrap::GetFirstHeroId()
{
	return m_taverncfg.heroes(0u).heroid();
}

int TavernConfigWrap::GetSecondGateId()
{
	return m_taverncfg.heroes(1u).condition().gateid();
}

bool TavernConfigWrap::IsGateCanUnlock(unsigned gateid)
{
	if (!ConfigManager::Instance()->m_mapGateIndex.count(gateid))  //闯关id不在配置文件中
	{
		return false;
	}

	return true;
}

unsigned TavernConfigWrap::GetHeroIdByGate(unsigned gateid)
{
	bool isCan = IsGateCanUnlock(gateid);

	if (!isCan)
	{
		return -1;
	}

	int index = ConfigManager::Instance()->m_mapGateIndex[gateid];

	unsigned heroid = m_taverncfg.heroes(index).heroid();

	return heroid;
}

unsigned TavernConfigWrap::GetNeedTimesById(unsigned gateid)
{
	bool isCan = IsGateCanUnlock(gateid);

	if (!isCan)
	{
		return -1;
	}

	int index = ConfigManager::Instance()->m_mapGateIndex[gateid];
	unsigned times = m_taverncfg.heroes(index).condition().times();

	return times;
}

/////////////////////////////////////任务//////////////////////////////////////////

MissionConfigWrap::MissionConfigWrap():
		m_missioncfg(ConfigManager::Instance()->mission.m_config)
{

}

const MissionConfig::MissionAll &  MissionConfigWrap::Mission() const
{
	return m_missioncfg;
}

int MissionConfigWrap::GetMissionBase(unsigned id, MissionBase & missonbase)
{
	if (!ConfigManager::Instance()->m_mapMissonIndex.count(id))
	{
		return R_ERROR;
	}

	unsigned keytype = ConfigManager::Instance()->m_mapMissonIndex[id].first;
	unsigned mindex = ConfigManager::Instance()->m_mapMissonIndex[id].second;

	const MissionConfig::Mission & mission = m_missioncfg.missions();

	switch(keytype)
	{
		case mission_condition_whether:
			missonbase.pre = mission.whether(mindex).pre();
			missonbase.id = mission.whether(mindex).id();
			missonbase.type = mission.whether(mindex).type();
			break;
		case mission_condition_single:
			missonbase.pre = mission.single(mindex).pre();
			missonbase.id = mission.single(mindex).id();
			missonbase.type = mission.single(mindex).type();
			break;
		case mission_condition_double:
			missonbase.pre = mission._double(mindex).pre();
			missonbase.id = mission._double(mindex).id();
			missonbase.type = mission._double(mindex).type();
			break;
		case mission_condition_triple:
			missonbase.pre = mission.triple(mindex).pre();
			missonbase.id = mission.triple(mindex).id();
			missonbase.type = mission.triple(mindex).type();
			break;
		case mission_condition_assemble:
			missonbase.pre = mission.assemble(mindex).pre();
			missonbase.id = mission.assemble(mindex).id();
			missonbase.type = mission.assemble(mindex).type();
			break;
		default:break;
	}

	return 0;
}

const MissionConfig::DoubleCondition & MissionConfigWrap::GetDoubleConditon(unsigned id) const
{
	if (!ConfigManager::Instance()->m_mapMissonIndex.count(id))
	{
		throw std::runtime_error("wrong id");
	}

	unsigned keytype = ConfigManager::Instance()->m_mapMissonIndex[id].first;
	unsigned mindex = ConfigManager::Instance()->m_mapMissonIndex[id].second;

	const MissionConfig::Mission & mission = m_missioncfg.missions();

	if (mission_condition_double != keytype)
	{
		throw std::runtime_error("wrong_condition_type");
	}

	return mission._double(mindex).condition();
}

const MissionConfig::TripleCondition & MissionConfigWrap::GetTripleCondition(unsigned id) const
{
	if (!ConfigManager::Instance()->m_mapMissonIndex.count(id))
	{
		throw std::runtime_error("wrong id");
	}

	unsigned keytype = ConfigManager::Instance()->m_mapMissonIndex[id].first;
	unsigned mindex = ConfigManager::Instance()->m_mapMissonIndex[id].second;

	const MissionConfig::Mission & mission = m_missioncfg.missions();

	if (mission_condition_triple != keytype)
	{
		throw std::runtime_error("wrong_condition_type");
	}

	return mission.triple(mindex).condition();
}

const MissionConfig::MissionReward & MissionConfigWrap::GetRewardConfig(unsigned id) const
{
	if (!ConfigManager::Instance()->m_mapMissonIndex.count(id))
	{
		throw std::runtime_error("wrong_id");
	}

	unsigned keytype = ConfigManager::Instance()->m_mapMissonIndex[id].first;
	unsigned mindex = ConfigManager::Instance()->m_mapMissonIndex[id].second;

	const MissionConfig::Mission & mission = m_missioncfg.missions();

	switch(keytype)
	{
		case mission_condition_whether:
			return  mission.whether(mindex).reward(); break;
		case mission_condition_single:
			return  mission.single(mindex).reward();
			break;
		case mission_condition_double:
			return  mission._double(mindex).reward();
			break;
		case mission_condition_triple:
			return  mission.triple(mindex).reward();
			break;
		case mission_condition_assemble:
			return  mission.assemble(mindex).reward();
			break;
		default:
			throw std::runtime_error("wrong_id_type");
	}
}

int MissionConfigWrap::GetLoginMissionId()
{
	int id = 0;

	const MissionConfig::Mission & mission = m_missioncfg.missions();

	for(int i = 0; i < mission.whether_size(); ++i)
	{
		if (mission.whether(i).type() == 1)
		{
			id = mission.whether(i).id();
			break;
		}
	}

	return id;
}

///////////////////装备洗练//////////////////////
SmeltConfigWrap::SmeltConfigWrap():
		m_smeltcfg(ConfigManager::Instance()->equipsmelt.m_config)
{

}

const EquipSmeltConfig::EquipSmelt &  SmeltConfigWrap::EquipSmelt() const
{
	return m_smeltcfg;
}

int SmeltConfigWrap::GetCharacterMaxlevel(int character) const
{
	int maxlevel = -1;

	for(int i = 0; i < m_smeltcfg.chlevel_size(); ++i)
	{
		if (m_smeltcfg.chlevel(i).ch() == character)
		{
			maxlevel = m_smeltcfg.chlevel(i).maxlevel();
			break;
		}
	}

	return maxlevel;
}

int SmeltConfigWrap::GetSuitMaxLevel(int type)
{
	int maxlevel = -1;

	for(int i = 0; i < m_smeltcfg.suitlevel_size(); ++i)
	{
		if (m_smeltcfg.suitlevel(i).type() == type)
		{
			maxlevel = m_smeltcfg.suitlevel(i).maxlevel();
			break;
		}
	}

	return 	maxlevel;
}

int SmeltConfigWrap::GetUpgradeRate(int type, int level)
{
	int rate = -1;

	switch(type)
	{
		case smelt_type_of_normal: rate = m_smeltcfg.normal(level);  break;
		case smelt_type_of_super:rate = m_smeltcfg.super(level); break;
		default: break;
	}

	return rate;
}

int SmeltConfigWrap::GetValueByTypeAndlevel(int type, int level)
{
	int val = 0;

	for(int i= 0; i < m_smeltcfg.levelpro_size(); ++i)
	{
		if (m_smeltcfg.levelpro(i).level() == level)
		{
			//从该元素中取出类型对应的数值类型
			val = m_smeltcfg.levelpro(i).property(type - 1);
			break;
		}
	}

	return val;
}

VipGiftConfigWrap::VipGiftConfigWrap():
		m_vipgiftcfg(ConfigManager::Instance()->vipgift.m_config)
{
}

const VipGiftConfig::FinalReward & VipGiftConfigWrap::GetNewerRewardCfg() const
{
	return m_vipgiftcfg.yellowvip().newer().reward();
}

const VipGiftConfig::FinalReward & VipGiftConfigWrap::GetDailyRewardCfg(int level) const
{
	const VipGiftConfig::PrivilegeGift & privilege = m_vipgiftcfg.yellowvip().privilege();
	//如果level超出数组限制，则抛出异常
	if (!ConfigManager::Instance()->m_mapVipLevelIndex.count(level))
	{
		throw std::runtime_error("wrong param level");
	}

	unsigned index = ConfigManager::Instance()->m_mapVipLevelIndex[level];

	return privilege.leveldaily(index).reward();
}

const VipGiftConfig::FinalReward & VipGiftConfigWrap::GetYearDailyRewardCfg() const
{
	return m_vipgiftcfg.yellowvip().privilege().yeardaily().reward();
}

const VipGiftConfig::UpgradeGift & VipGiftConfigWrap::GetUpgradeCfg(int index) const
{
	return m_vipgiftcfg.yellowvip().upgrade(index);
}

const VipGiftConfig::FinalReward & VipGiftConfigWrap::GetQQZoneDailyRewardCfg() const
{
	return m_vipgiftcfg.qqzone().privilege().daily().reward();
}

const VipGiftConfig::UpgradeGift &  VipGiftConfigWrap::GetQQZoneUpgradeCfg(int index) const
{
	return m_vipgiftcfg.qqzone().upgrade(index);
}

MarketConfigWrap::MarketConfigWrap():
		m_marketcfg(ConfigManager::Instance()->marketcfg.m_config)
{
}

int MarketConfigWrap::GetValueByTypeAndCharacter(int type, int character)
{
	if (!ConfigManager::Instance()->m_mapTypeIndex.count(type))
	{
		return 0;
	}

	unsigned index = ConfigManager::Instance()->m_mapTypeIndex[type];

	return m_marketcfg.market(index).reward(character - 1);
}

const MarketConfig::BlackMarketItem & MarketConfigWrap::GetBlackMarket() const
{
	return m_marketcfg.blackmarket();
}


WorldRewardConfigWrap::WorldRewardConfigWrap():
		m_worldreward(ConfigManager::Instance()->worldreward.m_config)
{
}

int WorldRewardConfigWrap::GetCoinBase()
{
	return m_worldreward.stronghold().coinbase();
}

int WorldRewardConfigWrap::GetIronBase()
{
	return m_worldreward.stronghold().ironbase();
}

int WorldRewardConfigWrap::GetTechCoefficent(unsigned level)
{
	if (level > m_worldreward.stronghold().tech_coefficient_size())
	{
		throw runtime_error("wrong_tech_level");
	}

	return m_worldreward.stronghold().tech_coefficient(level - 1);
}

int WorldRewardConfigWrap::GetTimeMultiple(unsigned hour)
{
	int multiple = 0;

	if (!ConfigManager::Instance()->m_mapHourIndex.count(hour))
	{
		error_log("wrong param hour. hour=%u", hour);
		return multiple;
	}

	unsigned index = ConfigManager::Instance()->m_mapHourIndex[hour];

	return m_worldreward.stronghold().timemultiple(index).multiple();
}

GovernAffairConfigWrap::GovernAffairConfigWrap():
		m_governaffairs(ConfigManager::Instance()->governaffairs.m_config)
{

}

const GovernAffairConfig::AffairsItem & GovernAffairConfigWrap::GetAffairById(unsigned mid)
{
	if (!ConfigManager::Instance()->m_afairid.count(mid))
	{
		error_log("[GetAffairById] get affair cfg error. affairid=%u", mid);
		throw std::runtime_error("get_affair_cfg_error");
	}

	unsigned index = ConfigManager::Instance()->m_afairid[mid];

	return m_governaffairs.govern_affairs(index);
}

int GovernAffairConfigWrap::GetCoefficient(unsigned level)
{
	int coefficient = 1;

	 //从高等级等级数组中开始对比，找出第一个符合条件的等级系数
	for(int i = m_governaffairs.coefficients_size(); i >= 1; --i)
	{
		if (m_governaffairs.coefficients(i - 1).levelrange(0u) <= level)
		{
			coefficient = m_governaffairs.coefficients(i - 1).coefficient();
			break;
		}
	}

	return coefficient;
}

int GovernAffairConfigWrap::GetAddedAffairTimes(unsigned type, unsigned levelsum)
{
	int times = 0;

	for(int i = 0; i < m_governaffairs.build_affairtimes_size(); ++i)
	{
		const GovernAffairConfig::BuildRelationTimes & buildreation = m_governaffairs.build_affairtimes(i);
		if (buildreation.type() == type)
		{
			for(int j = 0; j < buildreation.sublevelsum_size(); ++j)
			{
				if (buildreation.sublevelsum(j) == levelsum)
				{
					times = 1;
					break;
				}
			}

			break;
		}
	}

	return times;
}

EquipSuitConfigWrap::EquipSuitConfigWrap():
		m_equipsuit(ConfigManager::Instance()->equipsuit.m_config)
{

}

const EquipSuitConfig::SuitEquip & EquipSuitConfigWrap::GetEquipSuit(unsigned preeqid)
{
	if (!ConfigManager::Instance()->m_preeqidIndex.count(preeqid))
	{
		error_log("[GetAffairById] get equipsuit cfg error. preeqid=%u", preeqid);
		throw std::runtime_error("get_suit_cfg_error");
	}

	unsigned index = ConfigManager::Instance()->m_preeqidIndex[preeqid];

	return m_equipsuit.suitequip(index);
}

void EquipSuitConfigWrap::GetFightAttr(int type, int num, HeroFightAttr& attr)
{
	attr.Clear();

	//三重循环，最内遍历属性类型，次内遍历套装，外侧遍历套装类型
	for(int i = 0; i < m_equipsuit.suitproperty_size(); ++i)
	{
		const EquipSuitConfig::SuitProperty& suitproperty = m_equipsuit.suitproperty(i);

		if (suitproperty.type() == type)
		{
			for(int j = 0; j < suitproperty.property_size(); ++j)
			{
				if (num >= suitproperty.property(j).num())  //套装数量大于等于条件数量，则取该套装的属性
				{
					HeroFightAttr attrSuit;

					for(int k = 0; k < suitproperty.property(j).ptype_size(); ++k)
					{
						int subtype = suitproperty.property(j).ptype(k);
						int value = suitproperty.property(j).value(k);

						attrSuit.AddAttr(Type2Property(subtype), value);
					}

					attr += attrSuit;
				}
				else //套装数目配置是越来越大，第一个都不满足，后面的都不需要再循环了
				{
					break;
				}
			}
		}
	}
}

DemoHeroProperty EquipSuitConfigWrap::Type2Property(int type) const
{
	if (type < 1 || type > 7)
	{
		error_log("equip_type: %d", type);
		throw std::runtime_error("get_cfg_params_equip_type_error");
	}

	DemoHeroProperty propTb[7] = {
		DemoHeroProperty_attack,
		DemoHeroProperty_defend	,
		DemoHeroProperty_hp,
		DemoHeroProperty_skill_extra,
		DemoHeroProperty_skill_anti,
		DemoHeroProperty_attack_extra,
		DemoHeroProperty_attack_anti
	};

	return propTb[type - 1];
}

SpecialEquipConfigWrap::SpecialEquipConfigWrap():
		specialequip(ConfigManager::Instance()->specailequip.m_config)
{

}

bool SpecialEquipConfigWrap::IsSpecialEquip(unsigned eqid)
{
	if (ConfigManager::Instance()->specialIndex.count(eqid))
	{
		return true;
	}

	return false;
}

const SpecialEquipConfig::SpecialEquipItem & SpecialEquipConfigWrap::GetSpecialEquipItem(unsigned eqid) const
{
	if (!ConfigManager::Instance()->specialIndex.count(eqid))
	{
		error_log("[GetSpecialEquipItem] eqid not in specialequip config. eqid=%u", eqid);
		throw runtime_error("get_special_equip_cfg_error");
	}

	unsigned index = ConfigManager::Instance()->specialIndex[eqid];

	return specialequip.specialequip(index);
}

NPCAcitivityConfigWrap::NPCAcitivityConfigWrap():
		m_npcactivity(ConfigManager::Instance()->npcactivity.m_config)
{

}

int NPCAcitivityConfigWrap::GetFirstAffair(unsigned day)
{
	int id = 0;

	for(int i = 0; i < m_npcactivity.activity_affairs_size(); ++i)
	{
		//符合配置的天数
		if (day == m_npcactivity.activity_affairs(i).day())
		{
			id = m_npcactivity.activity_affairs(i).affairs(0u).id();
			break;
		}
	}

	return id;
}

int NPCAcitivityConfigWrap::GetNextAffair(unsigned id)
{
	int nextid = 0;

	if (!ConfigManager::Instance()->dayAffaiIndex.count(id))
	{
		error_log("[GetNextAffair] wrong affair id. id=%u", id);
		return 0;
	}

	int xindex = ConfigManager::Instance()->dayAffaiIndex[id].first;
	int yindex = ConfigManager::Instance()->dayAffaiIndex[id].second;

	if (m_npcactivity.activity_affairs(xindex).affairs_size() > (yindex+1))  //非最后一个id
	{
		nextid = m_npcactivity.activity_affairs(xindex).affairs(yindex+1).id();
	}

	return nextid;
}

const ProtoNPCActivity::AffairConfigCPP & NPCAcitivityConfigWrap::GetAffairConfig(unsigned id) const
{
	if (!ConfigManager::Instance()->dayAffaiIndex.count(id))
	{
		error_log("[GetAffairConfig] wrong affair id. id=%u", id);
		throw std::runtime_error("get_affair_config_error");
	}

	int xindex = ConfigManager::Instance()->dayAffaiIndex[id].first;
	int yindex = ConfigManager::Instance()->dayAffaiIndex[id].second;

	return m_npcactivity.activity_affairs(xindex).affairs(yindex);
}

int NPCAcitivityConfigWrap::GetOpenPlatfromIndex(unsigned diff)
{
	//左闭右开
	//因为开服时间段的开服天数配置都相同，所以取最容易获取的
	int index = 0;

	int max = m_npcactivity.open_platform_reward_size();

	for(int i = max- 1; i >= 0; --i)
	{
		if (m_npcactivity.open_platform_reward(i).startday() <= diff)  //条件值<= 实际的开服天数
		{
			index = i;
			break;
		}
	}

	return index;
}

const ProtoNPCActivity::OpenPlatformRewardConfigCPP & NPCAcitivityConfigWrap::GetOpenPlatReward(unsigned diff)
{
	//左闭右开
	int max = m_npcactivity.open_platform_reward_size();

	for(int i = max- 1; i >= 0; --i)
	{
		if (m_npcactivity.open_platform_reward(i).startday() <= diff)  //条件值<= 实际的开服天数
		{
			return m_npcactivity.open_platform_reward(i);
		}
	}

	return m_npcactivity.open_platform_reward(0);
}

KillRankConfigWrap::KillRankConfigWrap():
		killrank_cfg(ConfigManager::Instance()->killrank.m_config)
{

}

FogGateConfigWrap::FogGateConfigWrap():
		foggate_cfg(ConfigManager::Instance()->foggate.m_config)
{

}

const FogGateConfig::FogGate & FogGateConfigWrap::GetFogGate(unsigned gateid)
{
	if (!ConfigManager::Instance()->foggateIndex.count(gateid))
	{
		error_log("[GetFogGate] wrong gateid. gateid=%u", gateid);
		throw std::runtime_error("get_foggate_config_error");
	}

	unsigned index = ConfigManager::Instance()->foggateIndex[gateid];

	return foggate_cfg.foggates(index);
}

DailyMissionConfigWrap::DailyMissionConfigWrap():
		dailymission_cfg(ConfigManager::Instance()->dailymissions.m_config)
{

}

const DailyMissionConfig::DailyMission & DailyMissionConfigWrap::GetDailyMissionCfg(unsigned id)
{
	if (!ConfigManager::Instance()->dailymissionIndex.count(id))
	{
		error_log("[GetDailyMission] wrong missionid. missid=%u", id);
		throw std::runtime_error("get_dailymission_config_error");
	}

	unsigned tech_index = ConfigManager::Instance()->dailymissionIndex[id].first;
	unsigned miss_index = ConfigManager::Instance()->dailymissionIndex[id].second;

	return dailymission_cfg.daily_missions(tech_index).missions(miss_index);
}

const DailyMissionConfig::DailyMissionsItem & DailyMissionConfigWrap::GetDailyMissionItem(unsigned tech)
{
	int max_tech = dailymission_cfg.daily_missions_size() - 1;

	if (max_tech < tech)
	{
		error_log("[GetDailyMissionItem] error tech. tech=%u,max=%d", tech, max_tech);
		throw runtime_error("error_tech");
	}

	return dailymission_cfg.daily_missions(tech);
}

AchievementConfigWrap::AchievementConfigWrap():
		achieve_cfg(ConfigManager::Instance()->achievements.m_config)
{

}

const AchievementConfig::Achievement & AchievementConfigWrap::GetAchievementcfg(unsigned id)
{
	if (!ConfigManager::Instance()->achieveidIndex.count(id))
	{
		error_log("[GetAchievementcfg] wrong achievement id. id=%u", id);
		throw std::runtime_error("get_achievement_config_error");
	}

	unsigned index = ConfigManager::Instance()->achieveidIndex[id];

	return achieve_cfg.achievements(index);
}

vector<unsigned> AchievementConfigWrap::GetAchievesByType(unsigned type)
{
	if (!ConfigManager::Instance()->achieveTypeRelate.count(type))
	{
		vector<unsigned> temp;
		return temp;
	}

	return ConfigManager::Instance()->achieveTypeRelate[type];
}

ComponentConfigWrap::ComponentConfigWrap():
		component_cfg(ConfigManager::Instance()->component.m_config)
{

}

const ComponentConfig::Produce & ComponentConfigWrap::GetProduce(int level, bool iscash)
{
	const ComponentConfig::ComponentProduce & produce = component_cfg.component().compont_produce();

	if (iscash)
	{
		for(int i = 0; i < produce.cash_produce_size(); ++i)
		{
			if (produce.cash_produce(i).level() == level)
			{
				 return produce.cash_produce(i);
			}
		}
	}
	else
	{
		for(int i = 0; i < produce.common_size(); ++i)
		{
			if (produce.common(i).level() == level)
			{
				 return produce.common(i);
			}
		}
	}

	throw runtime_error("error_level_param");
}

const ComponentConfig::ComponentBase & ComponentConfigWrap::GetComponentBaseConfig(unsigned compid)
{
	if (!ConfigManager::Instance()->componentIndex.count(compid))
	{
		error_log("[GetComponentBaseConfig] wrong compid. compid=%u", compid);
		throw std::runtime_error("get_componentbase_config_error");
	}

	unsigned index = ConfigManager::Instance()->componentIndex[compid];

	return component_cfg.component().component_base(index);
}

bool ComponentConfigWrap::IsNormalComponent(unsigned compid)
{
	//根据compid读取配置
	const ComponentConfig::ComponentBase & base_config = GetComponentBaseConfig(compid);

	if (component_type_normal == base_config.type())
	{
		return true;
	}

	return false;
}

int ComponentConfigWrap::GetExpByCompid(unsigned compid)
{
	int exp = 0;
	const ComponentConfig::ComponentBase &  componentbase = GetComponentBaseConfig(compid);

	if (component_type_normal == componentbase.type())  //普通部件，根据品质获得经验大小
	{
		unsigned character = componentbase.character();

		if (character < 1)
		{
			error_log("[GetExpByCompid] wrong character. compid=%u", compid);
			throw runtime_error("wrong_comp_config");
		}

		unsigned index = character - 1;

		const ComponentConfig::ComponentExp & expconfig = component_cfg.component().character_objects(index).component_exp();
		exp = expconfig.base_exp();
	}
	else if (component_type_props == componentbase.type())  //经验道具，根据部件id获得经验大小
	{
		for(int i = 0; i < component_cfg.component().component_props_size(); ++i)
		{
			if (component_cfg.component().component_props(i).compid() == compid)
			{
				exp = component_cfg.component().component_props(i).exp();
			}
		}
	}

	return exp;
}

int ComponentConfigWrap::GetNormalResourceCost(unsigned compid, unsigned level, unsigned & coin, unsigned & wood)
{
	//根据品质和等级，获取对应的资源消耗
	const ComponentConfig::ComponentBase &  componentbase = GetComponentBaseConfig(compid);
	unsigned character = componentbase.character();

	if (character < 1)
	{
		error_log("[GetNormalResourceCost] wrong character. compid=%u", compid);
		throw runtime_error("wrong_comp_config");
	}

	unsigned index = character - 1;

	//等级判断
	unsigned level_size = component_cfg.component().character_objects(index).component_upgrade().level_cost_size();

	if (level > level_size || level < 1)
	{
		error_log("[GetNormalResourceCost] level error. compid=%u,level=%u,max_level=%u", compid, level, level_size);
		throw runtime_error("component_level_error");
	}

	const ComponentConfig::LevelCost costconfig = component_cfg.component().character_objects(index).component_upgrade().level_cost(level - 1);

	coin = costconfig.coin();
	wood = costconfig.wood();

	return 0;
}

int ComponentConfigWrap::GetPropsResouceCost(unsigned compid, unsigned & coin, unsigned & wood)
{
	//直接查看道具对应的资源消耗
	for(int i = 0; i < component_cfg.component().component_props_size(); ++i)
	{
		if (component_cfg.component().component_props(i).compid() == compid)
		{
			coin = component_cfg.component().component_props(i).coin();
			wood = component_cfg.component().component_props(i).wood();
		}
	}

	return 0;
}

const ComponentConfig::ComponentExp & ComponentConfigWrap::GetExpLevelConfig(unsigned compid)
{
	//获取品质
	const ComponentConfig::ComponentBase &  componentbase = GetComponentBaseConfig(compid);
	unsigned character = componentbase.character();

	if (character < 1)
	{
		error_log("[GetExpLevelConfig] wrong character. compid=%u", compid);
		throw runtime_error("wrong_comp_config");
	}

	unsigned index = character - 1;

	return component_cfg.component().character_objects(index).component_exp();
}

bool ComponentConfigWrap::IsMaxLevel(unsigned compid, unsigned level)
{
	const ComponentConfig::ComponentExp & expconfig = GetExpLevelConfig(compid);
	int maxlevel = expconfig.exp_level_size();

	if (level >= maxlevel)
	{
		return true;
	}

	return false;
}

int ComponentConfigWrap::GetBaseAttr(unsigned compid, vector<unsigned> & types, unsigned level, bool isMaster, HeroFightAttr& attr)
{
	//获取品质
	const ComponentConfig::ComponentBase &  componentbase = GetComponentBaseConfig(compid);
	unsigned character = componentbase.character();

	if (character < 1)
	{
		error_log("[GetBaseAttr] wrong character. compid=%u", compid);
		throw runtime_error("wrong_comp_config");
	}

	unsigned index = character - 1;
	const ComponentConfig::ComponentProperty & propertycfg = component_cfg.component().character_objects(index).component_property();
	int maxlevel = 0;

	if (isMaster)
	{
		maxlevel = propertycfg.master_size();
	}
	else
	{
		maxlevel = propertycfg.slave_size();
	}

	if (level < 1 || level > maxlevel)
	{
		error_log("[GetBaseAttr] wrong level param. compid=%u,level=%u,maxlevel=%d", compid, level, maxlevel);
		throw runtime_error("wrong_level_param");
	}

	attr.Clear();
	EquipSuitConfigWrap suitconfig;

	if (isMaster)  //主属性
	{
		//属性计算
		for(int i = 0; i < types.size(); ++i)
		{
			int subtype = types[i];
			int value = (int)propertycfg.master(level - 1).value(subtype - 1);

			attr.AddAttr(suitconfig.Type2Property(subtype), value);
		}
	}
	else  //副属性
	{
		//属性计算
		for(int i = 0; i < types.size(); ++i)
		{
			int subtype = types[i];
			int value = (int)propertycfg.slave(level - 1).value(subtype - 1);

			attr.AddAttr(suitconfig.Type2Property(subtype), value);
		}
	}

	return 0;
}

int ComponentConfigWrap::GetPercentAttr(unsigned compid, unsigned level, bool isMaster, map<unsigned, unsigned> &types,
		map<unsigned, double> & propertys)
{
	//获取品质
	const ComponentConfig::ComponentBase &  componentbase = GetComponentBaseConfig(compid);
	unsigned character = componentbase.character();

	if (character < 1)
	{
		error_log("[GetPercentAttr] wrong character. compid=%u", compid);
		throw runtime_error("wrong_comp_config");
	}

	unsigned index = character - 1;

	const ComponentConfig::ComponentProperty & propertycfg = component_cfg.component().character_objects(index).component_property();

	int maxlevel = 0;

	if (isMaster)
	{
		maxlevel = propertycfg.master_size();
	}
	else
	{
		maxlevel = propertycfg.slave_size();
	}

	if (level < 1 || level > maxlevel)
	{
		error_log("[GetBaseAttr] wrong level param. compid=%u,level=%u,maxlevel=%d", compid, level, maxlevel);
		throw runtime_error("wrong_level_param");
	}

	if (isMaster)  //主属性
	{
		//属性计算
		for(map<unsigned, unsigned>::iterator diter = types.begin(); diter != types.end(); ++diter)
		{
			int subtype = diter->first;
			double value = propertycfg.master(level - 1).value(subtype - 1);
			value *= diter->second;  //重复出现次数

			propertys[subtype] += value;
		}
	}
	else  //副属性
	{
		//属性计算
		for(map<unsigned, unsigned>::iterator diter = types.begin(); diter != types.end(); ++diter)
		{
			int subtype = diter->first;
			double value = propertycfg.slave(level - 1).value(subtype - 1);
			value *= diter->second;  //重复出现次数

			propertys[subtype] += value;
		}
	}

	return 0;
}

ShakeDiceConfigWrap::ShakeDiceConfigWrap():
		shake_cfg(ConfigManager::Instance()->shakedice.m_config.shakedice())
{

}

int ShakeDiceConfigWrap::GetShakeBaseConfig(BaseConfig & base)
{
	base.reset_times = shake_cfg.reset_times();
	base.reset_cash = shake_cfg.reset_cash();
	base.free_times = shake_cfg.free_times();
	base.dice_cash = shake_cfg.dice_cash();

	return 0;
}

int ShakeDiceConfigWrap::GetOpenPlatfromIndex(unsigned diff)
{
	//左闭右开
	//因为开服时间段的开服天数配置都相同，所以取最容易获取的
	int index = 0;

	int max = shake_cfg.open_platform_map_size();

	for(int i = max- 1; i >= 0; --i)
	{
		if (shake_cfg.open_platform_map(i).startday() <= diff)  //条件值<= 实际的开服天数
		{
			index = i;
			break;
		}
	}

	return index;
}

const ShakeDiceConfig::MapInfo & ShakeDiceConfigWrap::GetMapInfoConfig(unsigned diff, unsigned mapid)
{
	unsigned open_index = GetOpenPlatfromIndex(diff);

	if (mapid > shake_cfg.open_platform_map(open_index).mapinfo_size())
	{
		error_log("mapid error. mapid=%u", mapid);
		throw runtime_error("shake_dice_config_error");
	}

	return shake_cfg.open_platform_map(open_index).mapinfo(mapid - 1);
}

LittleChargeConfigWrap::LittleChargeConfigWrap():
		little_charge_cfg(ConfigManager::Instance()->littlecharge.m_config)
{

}

int LittleChargeConfigWrap::GetCashCondition()
{
	return little_charge_cfg.condition();
}

const LittleChargeConfig::OpenPlatFormReward & LittleChargeConfigWrap::GetRewardConfigByDiff(unsigned diff)
{
	int index = 0;

	int max = little_charge_cfg.open_platform_size();

	for(int i = max- 1; i >= 0; --i)
	{
		if (little_charge_cfg.open_platform(i).startday() <= diff)  //条件值<= 实际的开服天数
		{
			index = i;
			break;
		}
	}

	return little_charge_cfg.open_platform(index);
}

EnlivenKillConfigWrap::EnlivenKillConfigWrap():
		enliven_cfg(ConfigManager::Instance()->enlivenkill.m_config)
{

}

const EnlivenKillConfig::OpenPlatform & EnlivenKillConfigWrap::GetOpenPlatformConfigByDiff(unsigned diff)
{
	int index = 0;

	int max = enliven_cfg.open_platform_size();

	for(int i = max- 1; i >= 0; --i)
	{
		if (enliven_cfg.open_platform(i).startday() <= diff)  //条件值<= 实际的开服天数
		{
			index = i;
			break;
		}
	}

	return enliven_cfg.open_platform(index);
}

const EnlivenKillConfig::DailyKillReward & EnlivenKillConfigWrap::GetDailyKillRankRewardCfg(unsigned index)
{
	//如果传过来的参数大于配置的数组，则取最后一个
	if (enliven_cfg.daily_kill_reward_size() < index)
	{
		index = enliven_cfg.daily_kill_reward_size();
	}

	return enliven_cfg.daily_kill_reward(index - 1);
}

ResourceCopyConfigWrap::ResourceCopyConfigWrap():
		resourcecopy_cfg(ConfigManager::Instance()->resource_copy.m_config)
{

}

const ResourceCopyConfig::ResourceCopy & ResourceCopyConfigWrap::GetResourceCopyConfigById(unsigned id)
{
	if (!ConfigManager::Instance()->copyIndex.count(id))
	{
		error_log("wrong copeid. id=%u", id);
		throw std::runtime_error("get_resource_copy_config_error");
	}

	unsigned index = ConfigManager::Instance()->copyIndex[id];

	return resourcecopy_cfg.resource_copies(index);
}

OperaBattleConfigWrap::OperaBattleConfigWrap():
		battle_cfg(ConfigManager::Instance()->operobattle.m_config)
{

}

const OperaBattleConfig::DifficultyReward & OperaBattleConfigWrap::GetDifficultyRewardConfig(unsigned gateid, unsigned diff)
{
	if (!ConfigManager::Instance()->operabattleIndex.count(gateid))
	{
		error_log("wrong gateid. gateid=%u", gateid);
		throw std::runtime_error("get_operabattle_config_error");
	}

	unsigned index = ConfigManager::Instance()->operabattleIndex[gateid];

	if (diff < 1 || diff > battle_cfg.battle_rewards(index).difficulty_size())
	{
		error_log("wrong diff.bigger than array size. gateid=%u, diff=%u", gateid, diff);
		throw std::runtime_error("get_operabattle_config_error");
	}

	return battle_cfg.battle_rewards(index).difficulty(diff - 1);
}

ModelTrialConfigWrap::ModelTrialConfigWrap():
		trial_cfg(ConfigManager::Instance()->modeltrial.m_config)
{

}

int ModelTrialConfigWrap::GetMaxBuytimes()
{
	return trial_cfg.maxtimes();
}

int ModelTrialConfigWrap::GetPrice(unsigned times)
{
	int max = trial_cfg.times_price_size();

	if (times > max)
	{
		throw runtime_error("wrong_times");
	}

	return trial_cfg.times_price(times - 1);
}

const ModelTrialConfig::TrialGate & ModelTrialConfigWrap::GetTrialGateConfig(unsigned gateid)
{
	if (!ConfigManager::Instance()->trialIndex.count(gateid))
	{
		error_log("wrong gateid. gateid=%u", gateid);
		throw std::runtime_error("get_modeltrial_config_error");
	}

	unsigned index = ConfigManager::Instance()->trialIndex[gateid];

	return trial_cfg.gates(index);
}

CrossBusinessConfigWrap::CrossBusinessConfigWrap():
		cross_cfg(ConfigManager::Instance()->crossbusiness.m_config)
{

}

int CrossBusinessConfigWrap::GetRefreshCash()
{
	return cross_cfg.cash_refresh();
}

int CrossBusinessConfigWrap::GetOpenPlatfromIndex(unsigned diff)
{
	int index = 0;

	int max = cross_cfg.open_platform_shop_size();

	for(int i = max- 1; i >= 0; --i)
	{
		if (cross_cfg.open_platform_shop(i).startday() <= diff)  //条件值<= 实际的开服天数
		{
			index = i;
			break;
		}
	}

	return index;
}

const CrossBusinessConfig::OpenPlatformSlots & CrossBusinessConfigWrap::GetSlotsByDiff(unsigned diff)
{
	int index = GetOpenPlatfromIndex(diff);

	return cross_cfg.open_platform_shop(index);
}

const CrossBusinessConfig::SlotGoods & CrossBusinessConfigWrap::GetGoodsById(unsigned id)
{
	if (!ConfigManager::Instance()->businessIndex.count(id))
	{
		error_log("wrong slotid. id=%u", id);
		throw std::runtime_error("get_slot_config_error");
	}

	unsigned open_index = ConfigManager::Instance()->businessIndex[id].first;
	unsigned slot_index = ConfigManager::Instance()->businessIndex[id].second;

	return cross_cfg.open_platform_shop(open_index).slots(slot_index);
}

AttackHarborConfigWrap::AttackHarborConfigWrap():
		harbor_cfg(ConfigManager::Instance()->attackharbor.m_config)
{

}

int AttackHarborConfigWrap::GetOpenIndex(unsigned diff)
{
	int index = 0;

	const AttackHarborConfig::NPCRefresh & npcrefresh = harbor_cfg.npcrefresh(0);
	int max = npcrefresh.open_platform_npc_size();

	for(int i = max- 1; i >= 0; --i)
	{
		if (npcrefresh.open_platform_npc(i).startday() <= diff)  //条件值<= 实际的开服天数
		{
			index = i;
			break;
		}
	}

	return index;
}

const AttackHarborConfig::OpenPlatformReward & AttackHarborConfigWrap::GetRewardByRankDiff(unsigned diff, unsigned rank)
{
	int index = 0;

	const AttackHarborConfig::CountryRankReward & npcreward = harbor_cfg.country_reward(rank - 1);

	int max = npcreward.open_platform_reward_size();

	for(int i = max- 1; i >= 0; --i)
	{
		if (npcreward.open_platform_reward(i).startday() <= diff)  //条件值<= 实际的开服天数
		{
			index = i;
			break;
		}
	}

	return npcreward.open_platform_reward(index);
}

int AttackHarborConfigWrap::GetTimeFrequency()
{
	return harbor_cfg.refresh_frequency();
}

EliteNPCConfigWrap::EliteNPCConfigWrap():
		elite_cfg(ConfigManager::Instance()->elitenpc.m_config)
{

}

const WorldEliteConfig::TypeNPC & EliteNPCConfigWrap::GetTypeNPC(unsigned diff, uint8_t type)
{
	int index = 0;
	int max = elite_cfg.open_platform_npc_size();

	for(int i = max- 1; i >= 0; --i)
	{
		if (elite_cfg.open_platform_npc(i).startday() <= diff)  //条件值<= 实际的开服天数
		{
			index = i;
			break;
		}
	}

	if (type < 1 || type > elite_cfg.open_platform_npc(index).npcall_size())
	{
		error_log("wrong type param. type=%hhu", type);
		throw runtime_error("wrong_type_param");
	}

	return elite_cfg.open_platform_npc(index).npcall(type - 1);
}

SellComponentConfigWrap::SellComponentConfigWrap():
		sell_comp_cfg(ConfigManager::Instance()->sell_component.m_config)
{

}

const SellComponentConfig::GoodInfo & SellComponentConfigWrap::GetGoodsInfoByIndex(unsigned index)
{
	if (index < 1 || index > sell_comp_cfg.goodsall_size())
	{
		error_log("invalid param index. index=%u", index);
		throw runtime_error("wrong_param");
	}

	return sell_comp_cfg.goodsall(index - 1);
}
