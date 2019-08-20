#include "ConfigManager.h"

#define METHOD_GET_DIAMOND_ITEMCFG(activity, field)	\
	const ConfigActivity::DiamondReward & Get##activity##Itemcfg(unsigned index) \
	{ \
		if (index < 1 || static_cast<int>(index) > activity_cfg.field##_size()) \
		{ \
			error_log("param error. index=%u", index);\
			throw runtime_error("param_error");\
		}\
		return activity_cfg.field(index - 1);\
	}\

#define METHOD_GET_DIAMOND_SIZE(activity, field)	\
	unsigned Get##activity##Size() const\
	{ \
		return activity_cfg.field##_size(); \
	}\


//碎片合成
class CompoundConfigWrap
{
public:
	CompoundConfigWrap();

	const CompoundShredConfig::ShredItem & GetShredItemCfg(unsigned shredid);
private:
	const CompoundShredConfig::ShredCompounds & compound_cfg;
};

//百服团购
class GroupBuyingConfigWrap
{
public:
	GroupBuyingConfigWrap();

	//根据团购id，获取选项
	const GroupBuyingConfig::GroupBuyingItem & GetGroupBuyingItemcfg(unsigned id);

	int GetStageByCount(unsigned id, unsigned count);

private:
	const GroupBuyingConfig::GroupBuyingItemsCfg & group_cfg;
};

//古卷专项活动
class ScrollActivityConfigWrap
{
public:
	ScrollActivityConfigWrap();

	const ConfigScrollActivity::ScrollActivity & GetScrollCfg() {return scroll_cfg;}

	//根据类型，获取地块的配置
	const ConfigScrollActivity::RefreshPolicy & GetRefreshPolicy(unsigned type);

	//获取初始的事件id
	int GetInitAffairId(unsigned day);

	//获取最大地块数
	int GetLandNum(unsigned type, unsigned level);

	//获取单个地块能收获的材料数
	int GetMaterialNum(unsigned type, unsigned level);

	//根据事件id，获取事件的配置
	const ConfigScrollActivity::Affair & GetAffairCfgById(unsigned id);

	//根据现有id，获取下一个事件id
	int GetNextAffair(unsigned id);

	//根据下标，获取下标对应的配置
	const ConfigScrollActivity::ActiveValueReward & GetActiveRewardCfg(unsigned index);

	//根据活动时间天数，获取额外奖励配置
	const ConfigScrollActivity::ExtraReward & GetExtraRewardCfg(unsigned day);

private:
	const ConfigScrollActivity::ScrollActivity & scroll_cfg;
};

//天帝宝库活动
class KingTreasureConfigWrap
{
public:
	KingTreasureConfigWrap();

	//获取开箱子的消耗
	int GetCostCount();

	const ConfigKingTreasure::KingTreasure & GetTreasureCfg() {return treasure_cfg;}

	//根据箱子id,获取箱子配置
	const ConfigKingTreasure::TreasureBox & GetTreasureBoxById(unsigned id);

private:
	const ConfigKingTreasure::KingTreasure & treasure_cfg;
};

//古卷回馈活动
class ScrollFeedbackConfigWrap
{
public:
	ScrollFeedbackConfigWrap();

	const ConfigScrollFeedback::FeedBackItem & GetFeedbackByIndex(unsigned index);

private:
	const ConfigScrollFeedback::ScrollFeedBack & feedback_cfg;
};

//令牌提升
class TokenUpgradeConfigWrap
{
public:
	TokenUpgradeConfigWrap();

	const ConfigTokenUpgrade::ChargeReceive & GetReceiveConfigByIndex(unsigned index);

	const ConfigTokenUpgrade::ChargeLottery & GetLotteryConfig() {return token_cfg.charge_lottery();}

private:
	const ConfigTokenUpgrade::TokenUpgrade & token_cfg;
};

//活动整合
class ActivityConfigWrap
{
public:
	ActivityConfigWrap();

	const ConfigActivity::Activities & GetActivityCfg() {return activity_cfg;}

	//获取打造套装的配置
	const ConfigActivity::BuildSuitItem & GetBuildSuitConfigByIndex(unsigned index);

	//获取兑换的配置
	const ConfigActivity::ExchangeItem & GetExchangeConfigById(unsigned id);

	//获取双倍福利额外奖励的配置
	const ConfigActivity::DiamondReward & GetDoubleExtraConfigByIndex(unsigned index);

	//获取倍数系数
	double GetCoefficient(unsigned cost);

	//获取代金券最大值
	int GetMaximum();

	//获取灵珠兑换的配置
	const ConfigActivity::PearlAdvance & GetPearlAdvanceConfig(unsigned index);

	//获取精元礼包的配置
	const ConfigActivity::SpriteVitalityItem & GetSpriteConfig(unsigned index);

	//获取熔炉的商店的最大长度
	int GetForgeShopSize();

	const ConfigActivity::ShopItem & GetForgeShopConfig(unsigned index);

	//获取熔炼的物品对应关系
	int GetForgeSmeltRelation(map<unsigned, pair<unsigned, unsigned> > & relations);

	//获取熔炉的配置
	const ConfigActivity::ForgeSmelt & GetForgeSmeltCfg();

	//获取紫将转盘的配置
	const ConfigActivity::HeroDial & GetHeroDialCfg();

	//获取三国争霸充值奖励的最大长度
	int GetKingdomItemSize();

	//获取争霸奖励配置
	const ConfigActivity::KingdomWar & GetKingdomWarConfig(unsigned index);

	//获取一钻福利的配置
	const ConfigActivity::OneDiamondWelfare & GetOneDiamondCfg(unsigned index);

	//好运礼包-获取额外奖励
	const RewardConfig::RewardItemCfg & GetFortunePackExtracfg();
	//好运礼包-获取物品
	const ConfigActivity::RewardItem & GetFortunePackItemCfg(unsigned id);

	//七天好礼配置
	const ConfigActivity::SevenDayPacks & GetSevendayPacksItemcfg(unsigned index);

	//冰凰来袭配置
	const ConfigActivity::DiamondReward & GetIcePhoenixItemcfg(unsigned index);

	//秋日回馈配置
	const ConfigActivity::DiamondReward & GetAutumnFeedbackItemcfg(unsigned index);

	//保护旗帜配置
	const ConfigActivity::DiamondReward & GetProtectFlagItemcfg(unsigned index);

	//转盘狂惠---获取充值配置
	const ConfigActivity::DiamondReward & GetRotaryTableChargeItemcfg(unsigned index);
	unsigned  GetRotaryTableChargeCfgSize();
	const ConfigActivity::RotaryTableCfg & GetRotaryTableRandomItemcfg(unsigned index);
	unsigned  GetRotaryTableRandomCfgSize();
	const RewardConfig::RewardItemCfg & GetRotaryTableFixedItemcfg();
	const RewardConfig::RewardItemCfg & GetRotaryTableCostItemcfg();

	//转盘回馈--物品cfg
	const ConfigActivity::DiamondReward & GetRotaryTableFeedbackChargeItemcfg(unsigned index);
	const ConfigActivity::RotaryTableCfg & GetRotaryTableFeedBackItemcfg(unsigned index);
	const  ConfigActivity::SingleReward & GetAccChargeItemcfg(unsigned index);
	const RewardConfig::RewardItemCfg & GetRotaryTableFeedbackFixedItemcfg();
	unsigned GetRotaryTableFeedBackItemSize();

	//小兵宝物---配置读取
	const ConfigActivity::DiamondReward & GetBatmanTreasureChargeItemcfg(unsigned index);

	//暑假精选---根据索引获取累积充值档索引
	const ConfigActivity::DiamondReward & GetSummerAccChargeItemcfg(unsigned index);
	//暑假精选---根据索引获取每日充值档索引
	const ConfigActivity::DiamondReward & GetSummerDailyChargeItemcfg(unsigned index);

	//通过宏定义实现函数定义体相同的一些函数
	METHOD_GET_DIAMOND_ITEMCFG(YearEndGift, year_endgift);
	METHOD_GET_DIAMOND_SIZE(YearEndGift, year_endgift);

	//密钥豪礼----------------begin
	//根据充值数获取应得的密钥数
	unsigned GetKeyNum(unsigned charge);

	//获取长度
	unsigned GetLuxuryItemSize();

	//获取物品项配置
	const ConfigActivity::StuffItem & GetLuxuryGiftItem(unsigned index) const;
	//密钥豪礼----------------end

	//畅享小礼----------------begin
	//充值额度长度
	unsigned GetChargeCfgItemSize() const;
	//消费额度长度
	unsigned GetConsumeCfgItemSize() const;

	const ConfigActivity::DiamondReward & GetChargeItemCfg(unsigned index) const;

	const ConfigActivity::ConsumeGiftItem & GetConsumeItemCfg(unsigned index) const;
	//畅享小礼----------------end

	//获取幸运好礼配置
	const ConfigActivity::LuckyGift & GetLuckyGiftCfg() const {return activity_cfg.lucky_gift();}

	//获取每日充值自选
	const ConfigActivity::PayOptionalActivity & GetPayOptionalActivityCfg() const {return activity_cfg.payoptionalactivity();}

	//获取喜迎国庆配置
	const ConfigActivity::ChinaDayActivity & GetChinaDayActivityCfg() const {return activity_cfg.chinadayavtivity();}

	//获取元旦庆典配置
	const ConfigActivity::NewYearActivity & GetNewYearActivityCfg() const {return activity_cfg.newyearactivity();}

	//获取转盘狂惠配置
	const ConfigActivity::RotaryTableCrazyReward & GetRotaryTableActivityCfg() const {return activity_cfg.rotary_table();}

	//获取转盘回馈配置
	const ConfigActivity::RotaryTableFeedBackReward & GetRotaryTableFeedBackCfg() const {return activity_cfg.zhuanpanhuikui();}

	//获取小兵宝物配置
	const ConfigActivity::BatmanTreasureCfg & GetBatmanTreasureCfg() const {return activity_cfg.batmantreasure();}

	//获取暑假精选活动配置
	const ConfigActivity::SummerChargeRewardCfg & GetSummerChargeRewardCfg() const {return activity_cfg.summer_charge();}

	//获取暑假回馈活动配置
	const ConfigActivity::SummerHolidaysRewardCfg & GetSummerHolidaysRewardCfg() const {return activity_cfg.summer_holidays();}

	//获取开服好礼配置
	const ConfigActivity::KaiFuGift & GetKaifuActivityCfg() const {return activity_cfg.kaifu();}

	/*
	//获取黑金强化的配置
	const ConfigActivity::BlackGoldEnhance & GetBlackGoldEnhanceCfg(unsigned index);
	*/

	//红人榜
	const ConfigActivity::HongBao & GetHongBao() const {return activity_cfg.newyearactive();}

private:
	const ConfigActivity::Activities &activity_cfg;
};

//功能配置的整合
class FunctionsConfigWrap
{
public:
	FunctionsConfigWrap();

	//获取指定的eqid下的item信息
	const ConfigFunction::OpenSpecialEquipItem & GetSpecialEquipItemCfg(unsigned int eqid) const;
private:
	const ConfigFunction::Functions & functions_cfg;
};

class WuhunActivityWrap
{
public:
	WuhunActivityWrap();
	int GetAccChargeItemSize() const {
		return activity_cfg.zhulidaxingdong_size();
	}
	const WuhunActivity::AccChangeItem & GetAccChargeItemCfg(unsigned index);
	const WuhunActivity::QunXingHuiJu& GetQunXingHuiJu();
private:
	const WuhunActivity::Activities & activity_cfg;
};
