#include "ConfigWrap.h"

CompoundConfigWrap::CompoundConfigWrap():
	compound_cfg(ConfigManager::Instance()->m_CompoundConfig.m_config)
{

}

const CompoundShredConfig::ShredItem & CompoundConfigWrap::GetShredItemCfg(unsigned shredid)
{
	if (!ConfigManager::Instance()->m_compoundId.count(shredid))
	{
		error_log("shred compound config error. shredid=%u", shredid);
		throw runtime_error("shred_compound_config_error");
	}

	unsigned index = ConfigManager::Instance()->m_compoundId[shredid];

	return compound_cfg.shred_compounds(index);
}

GroupBuyingConfigWrap::GroupBuyingConfigWrap():
		group_cfg(ConfigManager::Instance()->m_groupbuyConfig.m_config)
{

}

const GroupBuyingConfig::GroupBuyingItem & GroupBuyingConfigWrap::GetGroupBuyingItemcfg(unsigned id)
{
	if (group_cfg.tuangou_size() < id)
	{
		error_log("group buying item config error. id=%u", id);
		throw runtime_error("config_error");
	}

	return group_cfg.tuangou(id - 1);
}

int GroupBuyingConfigWrap::GetStageByCount(unsigned id, unsigned count)
{
	if (group_cfg.tuangou_size() < id)
	{
		error_log("group buying item config error. id=%u", id);
		throw runtime_error("config_error");
	}

	int stage = 0;

	int len = group_cfg.tuangou(id - 1).people_size();

	for(int i = len - 1; i >= 0; --i)
	{
		if (count >= group_cfg.tuangou(id - 1).people(i).count())
		{
			stage = i;
			break;
		}
	}

	return stage;
}

ScrollActivityConfigWrap::ScrollActivityConfigWrap():
		scroll_cfg(ConfigManager::Instance()->m_scrollactivitycfg.m_config)
{

}

const ConfigScrollActivity::RefreshPolicy & ScrollActivityConfigWrap::GetRefreshPolicy(unsigned type)
{
	if (type < 1|| type > scroll_cfg.refresh_size())
	{
		error_log("param error. type=%u", type);
		throw runtime_error("param_error");
	}

	return scroll_cfg.refresh(type - 1);
}

int ScrollActivityConfigWrap::GetInitAffairId(unsigned day)
{
	if (day < 1 || day > scroll_cfg.activity_affairs_size() || scroll_cfg.activity_affairs(day -1).affairs_size() == 0)
	{
		return 0;
	}

	return scroll_cfg.activity_affairs(day -1).affairs(0u).id();
}

int ScrollActivityConfigWrap::GetLandNum(unsigned type, unsigned level)
{
	if (type < 1 || type > scroll_cfg.refresh_size())
	{
		return 0;
	}

	if (level < 1 || level > scroll_cfg.refresh(type - 1).land_num_size())
	{
		return 0;
	}

	return scroll_cfg.refresh(type - 1).land_num(level - 1);
}

int ScrollActivityConfigWrap::GetMaterialNum(unsigned type, unsigned level)
{
	if (type < 1 || type > scroll_cfg.refresh_size())
	{
		return 0;
	}

	if (level < 1 || level > scroll_cfg.refresh(type - 1).material_num_size())
	{
		return 0;
	}

	return scroll_cfg.refresh(type - 1).material_num(level - 1);
}

const ConfigScrollActivity::Affair & ScrollActivityConfigWrap::GetAffairCfgById(unsigned id)
{
	if (!ConfigManager::Instance()->m_scrollIndex.count(id))
	{
		error_log("wrong affair id. id=%u", id);
		throw runtime_error("wrong_affair_id");
	}

	int dindex = ConfigManager::Instance()->m_scrollIndex[id].first;
	int aindex = ConfigManager::Instance()->m_scrollIndex[id].second;

	return scroll_cfg.activity_affairs(dindex).affairs(aindex);
}

int ScrollActivityConfigWrap::GetNextAffair(unsigned id)
{
	int nextid = 0;

	if (!ConfigManager::Instance()->m_scrollIndex.count(id))
	{
		error_log("wrong affair id. id=%u", id);
		return 0;
	}

	int dindex = ConfigManager::Instance()->m_scrollIndex[id].first;
	int aindex = ConfigManager::Instance()->m_scrollIndex[id].second;

	if (scroll_cfg.activity_affairs(dindex).affairs_size() > (aindex+1))  //非最后一个id
	{
		nextid = scroll_cfg.activity_affairs(dindex).affairs(aindex+1).id();  //下一个元素的id
	}

	return nextid;
}

const ConfigScrollActivity::ActiveValueReward & ScrollActivityConfigWrap::GetActiveRewardCfg(unsigned index)
{
	if (index < 1 || index > scroll_cfg.active_value_reward_size())
	{
		error_log("param error. index=%u", index);
		throw runtime_error("param_error");
	}

	return scroll_cfg.active_value_reward(index - 1);
}

const ConfigScrollActivity::ExtraReward & ScrollActivityConfigWrap::GetExtraRewardCfg(unsigned day)
{
	if (day < 1 || day > scroll_cfg.extra_reward_size())
	{
		error_log("param error. day=%u", day);
		throw runtime_error("param_error");
	}

	return scroll_cfg.extra_reward(day - 1);
}

KingTreasureConfigWrap::KingTreasureConfigWrap():
		treasure_cfg(ConfigManager::Instance()->m_kingtreasurecfg.m_config)
{

}

int KingTreasureConfigWrap::GetCostCount()
{
	return treasure_cfg.cost();
}

const ConfigKingTreasure::TreasureBox & KingTreasureConfigWrap::GetTreasureBoxById(unsigned id)
{
	if (!ConfigManager::Instance()->m_treasureIndex.count(id))
	{
		error_log("param error. id=%u", id);
		throw runtime_error("param_error");
	}

	unsigned index = ConfigManager::Instance()->m_treasureIndex[id];

	return treasure_cfg.king_treasures(index);
}

ScrollFeedbackConfigWrap::ScrollFeedbackConfigWrap():
		feedback_cfg(ConfigManager::Instance()->m_scrollfeedbackcfg.m_config)
{

}

const ConfigScrollFeedback::FeedBackItem & ScrollFeedbackConfigWrap::GetFeedbackByIndex(unsigned index)
{
	if (index < 1 || index > feedback_cfg.scrollfeedback_size())
	{
		error_log("index param error. index=%u", index);
		throw runtime_error("param_error");
	}

	return feedback_cfg.scrollfeedback(index - 1);
}

TokenUpgradeConfigWrap::TokenUpgradeConfigWrap():
		token_cfg(ConfigManager::Instance()->m_tokenupgradecfg.m_config)
{

}

const ConfigTokenUpgrade::ChargeReceive & TokenUpgradeConfigWrap::GetReceiveConfigByIndex(unsigned index)
{
	if (index > token_cfg.charge_receive_size())
	{
		error_log("param index error. index=%u", index);
		throw runtime_error("param_error");
	}

	return token_cfg.charge_receive(index - 1);
}

ActivityConfigWrap::ActivityConfigWrap():
		activity_cfg(ConfigManager::Instance()->m_activitycfg.m_config)
{

}

const ConfigActivity::BuildSuitItem &  ActivityConfigWrap::GetBuildSuitConfigByIndex(unsigned index)
{
	if (index > activity_cfg.buildsuit_size())
	{
		error_log("param index error. index=%u", index);
		throw runtime_error("param_error");
	}

	return activity_cfg.buildsuit(index - 1);
}

const ConfigActivity::ExchangeItem & ActivityConfigWrap::GetExchangeConfigById(unsigned id)
{
	if (id > activity_cfg.blesspoint().exchange_size())
	{
		error_log("param index error. id=%u", id);
		throw runtime_error("param_error");
	}

	return activity_cfg.blesspoint().exchange(id - 1);
}

const ConfigActivity::DiamondReward & ActivityConfigWrap::GetDoubleExtraConfigByIndex(unsigned index)
{
	if (index > activity_cfg.double_welfare().extra_reward_size())
	{
		error_log("param index error. index=%u", index);
		throw runtime_error("param_error");
	}

	return activity_cfg.double_welfare().extra_reward(index - 1);
}

double ActivityConfigWrap::GetCoefficient(unsigned cost)
{
	double coefficient = 0;

	int size = activity_cfg.double_welfare().cost_coefficient_size();

	for(int i = size - 1; i >= 0; --i)
	{
		if (activity_cfg.double_welfare().cost_coefficient(i).cost() <= cost)
		{
			coefficient = activity_cfg.double_welfare().cost_coefficient(i).coefficient();
			break;
		}
	}

	return coefficient;
}

int ActivityConfigWrap::GetMaximum()
{
	return activity_cfg.double_welfare().maximum();
}

const ConfigActivity::PearlAdvance & ActivityConfigWrap::GetPearlAdvanceConfig(unsigned index)
{
	if (index > activity_cfg.pearl_advance_size())
	{
		error_log("param index error. index=%u", index);
		throw runtime_error("param_error");
	}

	return activity_cfg.pearl_advance(index - 1);
}

const ConfigActivity::SpriteVitalityItem & ActivityConfigWrap::GetSpriteConfig(unsigned index)
{
	if (index < 1 || index > activity_cfg.spiritvitality_size())
	{
		error_log("param index error. index=%u", index);
		throw runtime_error("param_error");
	}

	return activity_cfg.spiritvitality(index - 1);
}

int ActivityConfigWrap::GetForgeShopSize()
{
	return activity_cfg.forge().shop_size();
}

const ConfigActivity::ShopItem & ActivityConfigWrap::GetForgeShopConfig(unsigned index)
{
	if (index < 1 || index > activity_cfg.forge().shop_size())
	{
		error_log("param error. index=%u", index);
	}

	return activity_cfg.forge().shop(index - 1);
}

int ActivityConfigWrap::GetForgeSmeltRelation(map<unsigned, pair<unsigned, unsigned> > & relations)
{
	for(int i = 0; i < activity_cfg.forge().smelt_size(); ++i)
	{
		unsigned eqid = activity_cfg.forge().smelt(i).eqid();
		unsigned cost = activity_cfg.forge().smelt(i).cost();
		unsigned get = activity_cfg.forge().smelt(i).get();

		relations[eqid].first = cost;
		relations[eqid].second = get;
	}

	return 0;
}

const ConfigActivity::ForgeSmelt & ActivityConfigWrap::GetForgeSmeltCfg()
{
	return activity_cfg.forge();
}

const ConfigActivity::HeroDial & ActivityConfigWrap::GetHeroDialCfg()
{
	return activity_cfg.herodial();
}

int ActivityConfigWrap::GetKingdomItemSize()
{
	return activity_cfg.kingdomwar_size();
}

const ConfigActivity::KingdomWar & ActivityConfigWrap::GetKingdomWarConfig(unsigned index)
{
	if (index < 1 || index > activity_cfg.kingdomwar_size())
	{
		error_log("param error. index=%u", index);
		throw runtime_error("param_error");
	}

	return activity_cfg.kingdomwar(index - 1);
}

const ConfigActivity::OneDiamondWelfare & ActivityConfigWrap::GetOneDiamondCfg(unsigned index)
{
	if (index > activity_cfg.onediamondwelfare_size())
	{
		error_log("param error. index=%u", index);
		throw runtime_error("param_error");
	}

	return activity_cfg.onediamondwelfare(index - 1);
}

const RewardConfig::RewardItemCfg & ActivityConfigWrap::GetFortunePackExtracfg()
{
	return activity_cfg.fortune_packs().extra_reward();
}

const ConfigActivity::RewardItem & ActivityConfigWrap::GetFortunePackItemCfg(unsigned id)
{
	if (id < 1 || id > activity_cfg.fortune_packs().goods_size())
	{
		error_log("param error. id=%u", id);
		throw runtime_error("param_error");
	}

	return activity_cfg.fortune_packs().goods(id - 1);
}

const ConfigActivity::SevenDayPacks & ActivityConfigWrap::GetSevendayPacksItemcfg(unsigned index)
{
	if (index < 1 || index > activity_cfg.sevenday_packs_size())
	{
		error_log("param error. index=%u", index);
		throw runtime_error("param_error");
	}

	return activity_cfg.sevenday_packs(index - 1);
}

const ConfigActivity::DiamondReward & ActivityConfigWrap::GetIcePhoenixItemcfg(unsigned index)
{
	if (index < 1 || index > activity_cfg.icephoenix_size())
	{
		error_log("param error. index=%u", index);
		throw runtime_error("param_error");
	}

	return activity_cfg.icephoenix(index - 1);
}

const ConfigActivity::DiamondReward & ActivityConfigWrap::GetAutumnFeedbackItemcfg(unsigned index)
{
	if (index < 1 || index > activity_cfg.autumn_feedback_size())
	{
		error_log("param error. index=%u", index);
		throw runtime_error("param_error");
	}

	return activity_cfg.autumn_feedback(index - 1);
}

//保护旗帜配置
const ConfigActivity::DiamondReward & ActivityConfigWrap::GetProtectFlagItemcfg(unsigned index)
{
	if (index < 1 || index > activity_cfg.protectflag_size())
	{
		error_log("param error. index=%u", index);
		throw runtime_error("param_error");
	}

	return activity_cfg.protectflag(index - 1);
}


const ConfigActivity::DiamondReward & ActivityConfigWrap::GetRotaryTableChargeItemcfg(unsigned index)
{
	if (index < 1 || index > activity_cfg.rotary_table().chargereward_size())
	{
		error_log("param error. index=%u", index);
		throw runtime_error("param_error");
	}

	return activity_cfg.rotary_table().chargereward(index - 1);
}

const ConfigActivity::DiamondReward & ActivityConfigWrap::GetBatmanTreasureChargeItemcfg(unsigned index)
{
	if (index < 0 || index >= activity_cfg.batmantreasure().xiaobing_chargereward_size())
	{
		error_log("param error. index=%u", index);
		throw runtime_error("param_error");
	}

	return activity_cfg.batmantreasure().xiaobing_chargereward(index);
}

const ConfigActivity::DiamondReward & ActivityConfigWrap::GetSummerAccChargeItemcfg(unsigned index)
{
	if (index < 0 || index >= activity_cfg.summer_charge().acc_chargereward_size())
	{
		error_log("param error. index=%u", index);
		throw runtime_error("param_error");
	}

	return activity_cfg.summer_charge().acc_chargereward(index);
}

const ConfigActivity::DiamondReward & ActivityConfigWrap::GetSummerDailyChargeItemcfg(unsigned index)
{
	if (index < 0 || index >= activity_cfg.summer_charge().daily_chargereward_size())
	{
		error_log("param error. index=%u", index);
		throw runtime_error("param_error");
	}

	return activity_cfg.summer_charge().daily_chargereward(index);
}

unsigned  ActivityConfigWrap::GetRotaryTableChargeCfgSize()
{
	return activity_cfg.rotary_table().chargereward_size();
}

const ConfigActivity::RotaryTableCfg & ActivityConfigWrap::GetRotaryTableRandomItemcfg(unsigned index)
{
	if (index < 0 || index >= activity_cfg.rotary_table().randomreward_size())
	{
		error_log("param error. index=%u", index);
		throw runtime_error("param_error");
	}

	return activity_cfg.rotary_table().randomreward(index);
}

unsigned  ActivityConfigWrap::GetRotaryTableRandomCfgSize()
{
	return activity_cfg.rotary_table().randomreward_size();
}

const RewardConfig::RewardItemCfg & ActivityConfigWrap::GetRotaryTableFixedItemcfg()
{
	return activity_cfg.rotary_table().fixedreward();
}

const RewardConfig::RewardItemCfg & ActivityConfigWrap::GetRotaryTableCostItemcfg()
{
	return activity_cfg.rotary_table().rotarytablecost();
}


unsigned ActivityConfigWrap::GetKeyNum(unsigned charge)
{
	unsigned num = 0;

	for(int i = 0; i < activity_cfg.keyluxurygift().charge_key_size(); ++i)
	{
		if (charge >= activity_cfg.keyluxurygift().charge_key(i).diamond())
		{
			num += activity_cfg.keyluxurygift().charge_key(i).keynum();
		}
		else
		{
			break;
		}
	}

	return num;
}

unsigned ActivityConfigWrap::GetLuxuryItemSize()
{
	return activity_cfg.keyluxurygift().stuff_items_size();
}

const ConfigActivity::StuffItem & ActivityConfigWrap::GetLuxuryGiftItem(unsigned index) const
{
	if (index < 1 || index > activity_cfg.keyluxurygift().stuff_items_size())
	{
		error_log("param error. index=%u", index);
		throw runtime_error("param_error");
	}

	return activity_cfg.keyluxurygift().stuff_items(index - 1);
}

unsigned ActivityConfigWrap::GetChargeCfgItemSize() const
{
	return activity_cfg.enjoy_smallgift().charge_gift_size();
}

unsigned ActivityConfigWrap::GetConsumeCfgItemSize() const
{
	return activity_cfg.enjoy_smallgift().consume_gift_size();
}

const ConfigActivity::DiamondReward & ActivityConfigWrap::GetChargeItemCfg(unsigned index) const
{
	if (index < 0 || index > activity_cfg.enjoy_smallgift().charge_gift_size())
	{
		error_log("param error. index=%u", index);
		throw runtime_error("param_error");
	}

	return activity_cfg.enjoy_smallgift().charge_gift(index -1);
}

const ConfigActivity::ConsumeGiftItem & ActivityConfigWrap::GetConsumeItemCfg(unsigned index) const
{
	if (index < 0 || index > activity_cfg.enjoy_smallgift().consume_gift_size())
	{
		error_log("param error. index=%u", index);
		throw runtime_error("param_error");
	}

	return activity_cfg.enjoy_smallgift().consume_gift(index -1);
}

/*
const ConfigActivity::BlackGoldEnhance & ActivityConfigWrap::GetBlackGoldEnhanceCfg(unsigned index)
{
	if (index < 1 || index > activity_cfg.blackgold_enhance_size())
	{
		error_log("param index error. index=%u", index);
		throw runtime_error("param_error");
	}

	return activity_cfg.blackgold_enhance(index - 1);
}

*/

FunctionsConfigWrap::FunctionsConfigWrap():
		functions_cfg(ConfigManager::Instance()->m_functionscfg.m_config)
{

}

const ConfigFunction::OpenSpecialEquipItem & FunctionsConfigWrap::GetSpecialEquipItemCfg(unsigned int eqid) const
{
	for(int i = 0; i < functions_cfg.open_special_equip_size(); ++i)
	{
		if (functions_cfg.open_special_equip(i).eqid() == eqid)
		{
			return functions_cfg.open_special_equip(i);
		}
	}

	error_log("param error. eqid=%u", eqid);
	throw runtime_error("param_error");
}

