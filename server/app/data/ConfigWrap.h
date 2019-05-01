/*
 * ConfigWrap.h
 *
 *  Created on: 2016-9-12
 *      Author: dawx62fac
 */

#ifndef USERCFGWRAP_H_
#define USERCFGWRAP_H_

#include "DataInc.h"


class UserCfgWrap
{
public:
	UserCfgWrap();

	const UserCfg::User& User() const;
	const UserCfg::UserBase& UserBase() const;
private:
	const UserCfg::User& cfg_;
};

//装备商店
class EquipShopConfigWrap
{
public:
	EquipShopConfigWrap();

	const EquipmentShopConfig::EquipmentShop & EquipShop() {return m_equipshop;}

	//是否是募兵令
	bool IsOrder(unsigned eqid);

	//是否是黄金
	bool IsIron(unsigned eqid);

	//根据eqid获取物品数量
	int GetNumByEqid(unsigned eqid);

private:
	const EquipmentShopConfig::EquipmentShop & m_equipshop;
};

//酒馆
class TavernConfigWrap
{
public:
	TavernConfigWrap();

	const TavernConfig::HeroRecruit&  Tavern() const;

	unsigned GetFirstHeroId();   //获取第一个解封的英雄id

	int GetSecondGateId();  //获取第二个英雄解锁要求的任务关

	unsigned GetHeroIdByGate(unsigned gateid);  //根据闯关id获取英雄id

	//根据闯关id判断解锁需要的闯关次数
	unsigned GetNeedTimesById(unsigned gateid);

	bool IsGateCanUnlock(unsigned gateid);  //当前闯关id是否解锁英雄

private:
	const TavernConfig::HeroRecruit& m_taverncfg;
};

class ResourceCfgWrap
{
public:
	ResourceCfgWrap();
	//获取倍数
	unsigned GetMultiple(bool isFree);
private:
	const ResourceConfig::Resource& cfg_;
};

class ScienceCfgWrap
{
public:
	ScienceCfgWrap();

	void GetIdsByType(ScienceType type, std::vector<uint16_t>& vIds) const;
	const ScienceConfig::ScienceItem& Item(unsigned id) const;

	bool IsExistId(unsigned id) const;
private:
	const ScienceConfig::Science& cfg_;
};

class WeaponCfgWrap
{
public:
	WeaponCfgWrap();

	const WeaponConfig::WeaponItem& Item(unsigned id) const;
	const WeaponConfig::WeaponLvL& LvL(unsigned id, unsigned level) const;
private:
	const WeaponConfig::Weapon& cfg_;
};

class NPCPassCfgWrap
{
public:
	NPCPassCfgWrap();
	const PassSystemConfig::System& SystemCfg() const;

public:
	const PassSystemConfig::System& cfg_;

	const PassSystemConfig::PassItem& Item(unsigned id) const;
};

class ExploitBoxCfgWrap
{
public:
	ExploitBoxCfgWrap();

	unsigned GetExploitBoxStage(unsigned level, unsigned exploit) const;
	unsigned GetBoxCntByStage(unsigned level, int stage) const;

	const ExploitBoxConfig::ExploitItem& Item(unsigned level) const;
	const ExploitBoxConfig::ExploitBox& Box() const;

	const ExploitBoxConfig::ExploitReward& BoxReward(unsigned level) const;
	const CommonGiftConfig::BaseReward& BaseReward(unsigned level) const;
	unsigned GetRewardMul(const ExploitBoxConfig::ExploitReward& boxReward) const;
private:
	unsigned GetExtraBoxByStage(int stage, const ExploitBoxConfig::ExploitRandomMul& cfg) const;
	unsigned GetRandomValue(const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >& values) const;
private:
	const ExploitBoxConfig::Exploit& cfg_;
};

class IntegralTimeCfgWrap
{
public:
	IntegralTimeCfgWrap();

	const ::RewardConfig::IntegralReward& Reward() const;

	//
private:
	const RewardConfig::IntegralTime& cfg_;
};

class PkFieldCfgWrap
{
public:
	PkFieldCfgWrap();
	//rank 起始值为 1
	const CommonGiftConfig::BaseReward& GetReward(unsigned rank);
private:
	const RewardConfig::PkField& cfg_;
};

class ActivityCfgWrap
{
public:
	ActivityCfgWrap();

	const User::ActivityItem& GetItem(unsigned id) const;
private:
	const User::Activity& cfg_;
};

class LimitShopCfgWrap
{
public:
	LimitShopCfgWrap();

	const ShopConfig::LimitShopItem& GetItem(unsigned opendays, unsigned id) const;
private:
	const ShopConfig::LimitShopItems& GetItems(unsigned opendays) const;
private:
	const ShopConfig::LimitShop& cfg_;
};

class TouchGoldCfgWrap
{
public:
	TouchGoldCfgWrap();

	unsigned 	Output(unsigned tomb_id) const;
	const  		ActivityConfig::TouchGoldItem& GetItem(unsigned tomb_id) const;

	//
	unsigned    GetUnlockCost(unsigned tomb_id) const;
private:
	const ActivityConfig::TouchGold& cfg_;
};

class HugeDiscountCfgWrap
{
public:
	HugeDiscountCfgWrap();

	unsigned GetOpenCash(unsigned id) const;

	const ::ActivityConfig::HugeDiscountItem& GoodItemCfg(unsigned page_id, unsigned id, unsigned open_day) const;
	const ::ActivityConfig::HugeDiscountGood& GoodCfg(unsigned page_id, unsigned open_day) const;
	const ::ActivityConfig::HugeDiscountPage& PageItemCfg(unsigned id) const;
	const ActivityConfig::HugeDiscount& Cfg() const { return cfg_; }
private:
	const ActivityConfig::HugeDiscount& cfg_;
};

class CashBackCfgWrap
{
public:
	CashBackCfgWrap();

	const ActivityConfig::CashBackItem& GetItem(unsigned id) const;
	int MaxId() const;
private:
	const ActivityConfig::CashBack& cfg_;
};

class SmeltActivityCfgWrap
{
public:
	SmeltActivityCfgWrap();

	const ActivityConfig::SmeltActivityItem& GetItem(unsigned id) const;
	const ActivityConfig::SmeltActivity& Cfg() const;
private:
	const ActivityConfig::SmeltActivity& cfg_;
}; //smelt_activity

class VIPCfgWrap
{
public:
	VIPCfgWrap();

	typedef ::google::protobuf::RepeatedPtrField< ::RewardConfig::Reward > VIPRewardType;

	unsigned GetVIPLevel(unsigned cash) const;

	const VIPConfig::UVIPBasePower& BasePower() const;
	const VIPConfig::UVIPLvlPower& LVLPower() const;

	const VIPRewardType& GetRewardByLevel(unsigned level) const;

	const VIPConfig::UVIPItem& Cfg() const;

private:
	const VIPConfig::UVIPItem& cfg_;
};

class CountryTaskCfgWrap
{
public:
	typedef ::google::protobuf::RepeatedPtrField< ::RewardConfig::Reward > PersonalRewardType;
	CountryTaskCfgWrap();

	const PersonalRewardType& PersonalReward(unsigned task_no) const;

	int GetTechCoefficent(unsigned level);
	float GetBaseFactor(unsigned open_days, unsigned kills) const;
	float GetExpandFactor(unsigned open_days, unsigned kills) const;
	const CommonGiftConfig::BaseReward& BaseCountryReward(unsigned open_days, unsigned kills);
private:
	//const RewardConfig::CountryTask& cfg_;
	const RewardConfig::CountryTaskItem& cfg_;

	unsigned GetBaseIndex(unsigned open_days, unsigned kills) const;
	unsigned GetKillsIndex(unsigned open_days, unsigned kills) const;
};

class OfficialCfgWrap
{
public:
	OfficialCfgWrap();
	//获取加成
	//unsigned YieldAdd(unsigned departement, unsigned job);

	const OfficialConfig::OfficialJob& GetJobCfg(unsigned departement, unsigned job) const;
	const OfficialConfig::OfficialDepartment& GetDepartment(unsigned departement) const;
private:
	const OfficialConfig::Official& cfg_;
};

class PassActivityCfgWrap
{
public:
	PassActivityCfgWrap();
	const ActivityConfig::PassActivity& Cfg() const;
	const ActivityConfig::PassActivityItem& Item(unsigned id) const;
	int Index(unsigned id) const;
private:
	const ActivityConfig::PassActivity& cfg_;
};

class MineCfgWrap
{
public:
	MineCfgWrap();

	int GetNormalDonateCost() const;
	int GetKingdomDonateCost() const;

	int HarvestNormalMine(int level) const;
	int HarvestKingdomMine(int level) const;

	int GetKingdomOpenCost() const;
	int GetNormalOpenCost(unsigned exp) const;
	int Exp2Level(unsigned exp) const;
	int GetOpenExp() const;
	int GetDonateExp() const;

	int GetNormalDonateCnt(int level) const;
	int GetKingdomDonateCnt() const;

	int GetKingdomReward() const;

	const MineConfig::Normal& NormalCfg() const;
private:
	const MineConfig::MineItem& cfg_;
};

class MissionConfigWrap
{
public:
	MissionConfigWrap();

	const MissionConfig::MissionAll & Mission() const;

	struct MissionBase
	{
		int id;
		int type;
		int pre;
	};

	int GetMissionBase(unsigned id, MissionBase & missonbase);

	/*
	 * 根据任务id获取双重条件
	 * param  id(in)
	 * exception runtime_error
	 * return
	 */
	const MissionConfig::DoubleCondition & GetDoubleConditon(unsigned id) const;

	/*
	 * 根据任务id获取三重条件
	 * param  id(in)
	 * exception runtime_error
	 * return
	 */
	const MissionConfig::TripleCondition & GetTripleCondition(unsigned id) const;

	/*
	 * 根据任务id获取reward配置
	 * param  id(in)
	 * exception runtime_error
	 * return
	 */
	const MissionConfig::MissionReward & GetRewardConfig(unsigned id) const;

	//获取登录任务的id
	int GetLoginMissionId();

private:
	const MissionConfig::MissionAll& m_missioncfg;
};

class SmeltConfigWrap
{
public:
	SmeltConfigWrap();

	const EquipSmeltConfig::EquipSmelt & EquipSmelt() const;

	/*
	 * 获取品质对应的最大等级.
	 * param  character(in)
	 * return -1表示失败
	 */
	int GetCharacterMaxlevel(int character) const;

	/*
	 * 获取套装类型对应的最大等级.
	 * param  type(in)
	 * return -1表示失败
	 */
	int GetSuitMaxLevel(int type);

	/*
	 * 根据洗练类型以及属性等级获取升级概率
	 * param  type(in),level(in)
	 * return -1表示失败
	 */
	int GetUpgradeRate(int type, int level);

	/*
	 * 根据洗练属性和属性等级获取属性值大小
	 * param  type(in),level(in)
	 * return -1表示失败
	 */
	int GetValueByTypeAndlevel(int type, int level);

private:
	const EquipSmeltConfig::EquipSmelt & m_smeltcfg;
};

//VIP礼包，包括黄钻礼包配置
class VipGiftConfigWrap
{
public:
	VipGiftConfigWrap();
	const VipGiftConfig::VIPGift & VipGift() {return m_vipgiftcfg;}

	//获取黄钻新手礼包
	const VipGiftConfig::FinalReward & GetNewerRewardCfg() const;

	//根据等级获取黄钻会员的每日礼包
	const VipGiftConfig::FinalReward & GetDailyRewardCfg(int level) const;

	//获取年费黄钻的每日礼包
	const VipGiftConfig::FinalReward & GetYearDailyRewardCfg() const;

	//获取黄钻等级礼包的配置
	const VipGiftConfig::UpgradeGift & GetUpgradeCfg(int index) const;

	//获取空间每日礼包配置
	const VipGiftConfig::FinalReward & GetQQZoneDailyRewardCfg() const;

	//获取空间等级礼包的配置
	const VipGiftConfig::UpgradeGift & GetQQZoneUpgradeCfg(int index) const;

private:
	const VipGiftConfig::VIPGift & m_vipgiftcfg;
};

//集市配置
class MarketConfigWrap
{
public:
	MarketConfigWrap();
	const MarketConfig::MarketAll & Market() {return m_marketcfg;}

	//获取类型和品质对应的值
	int GetValueByTypeAndCharacter(int type, int character);

	//获取黑市的相关信息
	const MarketConfig::BlackMarketItem & GetBlackMarket() const;

private:
	const MarketConfig::MarketAll & m_marketcfg;
};

//争霸奖励配置，包括据点奖励
class WorldRewardConfigWrap
{
public:
	WorldRewardConfigWrap();

	const WorldRewardConfig::WorldReward & WorldReward() {return m_worldreward;}

	//获取银币基数
	int GetCoinBase();

	//获取镔铁基数
	int GetIronBase();

	//获取时间倍数
	int GetTimeMultiple(unsigned hour);

	//获取科技系数
	int GetTechCoefficent(unsigned level);

private:
	const WorldRewardConfig::WorldReward & m_worldreward;
};

//政务事件相关配置
class GovernAffairConfigWrap
{
public:
	GovernAffairConfigWrap();

	const GovernAffairConfig::GovernAffairs & GovernAffair() {return m_governaffairs;}

	const GovernAffairConfig::AffairsItem & GetAffairById(unsigned mid);

	int GetCoefficient(unsigned level);

	//根据建筑类型和建筑等级和，返回增加的政务事件次数
	int GetAddedAffairTimes(unsigned type, unsigned levelsum);

private:
	const GovernAffairConfig::GovernAffairs & m_governaffairs;
};

//套装合成配置
class EquipSuitConfigWrap
{
public:
	EquipSuitConfigWrap();

	const EquipSuitConfig::EquipSuit & Equipsuit(){return m_equipsuit;}

	//根据前置eqid获取套装配置
	const EquipSuitConfig::SuitEquip & GetEquipSuit(unsigned preeqid);

	//套装属性计算
	void GetFightAttr(int type, int num, HeroFightAttr& attr);

	DemoHeroProperty Type2Property(int type) const;

private:
	const EquipSuitConfig::EquipSuit & m_equipsuit;
};

//定制装备配置
class SpecialEquipConfigWrap
{
public:
	SpecialEquipConfigWrap();

	const SpecialEquipConfig::SpecialEquips & SpecialEquips() {return specialequip;}

	bool IsSpecialEquip(unsigned eqid);

	const SpecialEquipConfig::SpecialEquipItem & GetSpecialEquipItem(unsigned eqid) const;

private:
	const SpecialEquipConfig::SpecialEquips & specialequip;
};

//广结名士活动配置
class NPCAcitivityConfigWrap
{
public:
	NPCAcitivityConfigWrap();

	const ProtoNPCActivity::NPCActivityConfigCPP & NPCActivity() {return m_npcactivity;}

	//根据天数，获取第一个活动事件
	int GetFirstAffair(unsigned day);

	//获取当前事件id的下一个事件id
	int GetNextAffair(unsigned id);

	//获取事件的配置
	const ProtoNPCActivity::AffairConfigCPP & GetAffairConfig(unsigned id) const;

	int GetOpenPlatfromIndex(unsigned diff);

	//获取活力值奖励的配置
	const ProtoNPCActivity::OpenPlatformRewardConfigCPP & GetOpenPlatReward(unsigned diff);

private:
	const ProtoNPCActivity::NPCActivityConfigCPP  & m_npcactivity;
};

//杀敌排行榜配置
class KillRankConfigWrap
{
public:
	KillRankConfigWrap();

	const KillRankConfig::KillRank & KillRank(){return killrank_cfg;}

private:
	const KillRankConfig::KillRank & killrank_cfg;
};

//迷雾战配置
class FogGateConfigWrap
{
public:
	FogGateConfigWrap();

	const FogGateConfig::FogGates & FogGates() {return foggate_cfg;}

	const FogGateConfig::FogGate & GetFogGate(unsigned gateid);
private:
	const FogGateConfig::FogGates & foggate_cfg;
};

//每日任务配置
class DailyMissionConfigWrap
{
public:
	DailyMissionConfigWrap();

	const DailyMissionConfig::DailyMissonItemList & DailyMission() {return dailymission_cfg;}

	//根据任务id获取任务配置
	const DailyMissionConfig::DailyMission & GetDailyMissionCfg(unsigned id);

	//根据科技获取该科技的任务库
	const DailyMissionConfig::DailyMissionsItem & GetDailyMissionItem(unsigned tech);

private:
	const DailyMissionConfig::DailyMissonItemList & dailymission_cfg;
};

//成就配置
class AchievementConfigWrap
{
public:
	AchievementConfigWrap();

	const AchievementConfig::AchievementList & Achievementcfg() {return achieve_cfg;}

	const AchievementConfig::Achievement & GetAchievementcfg(unsigned id);

	//根据类型获取成就id集合
	vector<unsigned> GetAchievesByType(unsigned type);

private:
	const AchievementConfig::AchievementList & achieve_cfg;
};

//部件系统配置
class ComponentConfigWrap
{
public:
	ComponentConfigWrap();

	const ComponentConfig::Component & Component() {return component_cfg;}

	//获取产出的配置
	const ComponentConfig::Produce & GetProduce(int level, bool iscash = false);

	//获取部件的基础信息配置
	const ComponentConfig::ComponentBase & GetComponentBaseConfig(unsigned compid);

	//是否正常部件. true-是, false-否
	bool IsNormalComponent(unsigned compid);

	//获取部件id的固有经验
	int GetExpByCompid(unsigned compid);

	//获取普通部件消耗的材料
	int GetNormalResourceCost(unsigned compid, unsigned level, unsigned & coin, unsigned & wood);

	//获取经验部件消耗的材料
	int GetPropsResouceCost(unsigned compid, unsigned & coin, unsigned & wood);

	//获取部件的等级和经验的数组配置
	const ComponentConfig::ComponentExp & GetExpLevelConfig(unsigned compid);

	bool IsMaxLevel(unsigned compid, unsigned level);

	//计算基本属性
	int GetBaseAttr(unsigned compid, vector<unsigned> & types, unsigned level, bool isMaster, HeroFightAttr& attr);

	//计算百分比属性
	int GetPercentAttr(unsigned compid, unsigned level, bool isMaster, map<unsigned, unsigned> &types, map<unsigned, double> & propertys);

private:
	const ComponentConfig::Component & component_cfg;
};

//摇骰子配置
class ShakeDiceConfigWrap
{
public:
	struct BaseConfig
	{
        unsigned reset_times;
        unsigned reset_cash;
        unsigned free_times;
        unsigned dice_cash;

        BaseConfig():
        	reset_times(0),
        	reset_cash(0),
        	free_times(0),
        	dice_cash(0)
        {

        }
	};

	ShakeDiceConfigWrap();

	//获取基础配置
	int GetShakeBaseConfig(BaseConfig & base);

	//根据开服时间差获取开服相关的索引
	int GetOpenPlatfromIndex(unsigned diff);

	//根据开服索引获取奖励
	const ShakeDiceConfig::MapInfo & GetMapInfoConfig(unsigned diff, unsigned mapid);

private:
	const ShakeDiceConfig::ShakeDice & shake_cfg;
};

//充点小钱配置
class LittleChargeConfigWrap
{
public:
	LittleChargeConfigWrap();

	int GetCashCondition();

	const LittleChargeConfig::OpenPlatFormReward & GetRewardConfigByDiff(unsigned diff);

private:
	const LittleChargeConfig::LittleCharge & little_charge_cfg;
};

//杀敌活跃配
class EnlivenKillConfigWrap
{
public:
	EnlivenKillConfigWrap();

	const EnlivenKillConfig::EnlivenKill & GetEnlivenConfig() {return enliven_cfg;}

	//获取开服时间相关的杀敌额度配置
	const EnlivenKillConfig::OpenPlatform & GetOpenPlatformConfigByDiff(unsigned diff);

	//获取每日杀敌奖励配置
	const EnlivenKillConfig::DailyKillReward & GetDailyKillRankRewardCfg(unsigned index);
private:
	const EnlivenKillConfig::EnlivenKill & enliven_cfg;
};

//资源副本配置
class ResourceCopyConfigWrap
{
public:
	ResourceCopyConfigWrap();

	const ResourceCopyConfig::ResourceCopy & GetResourceCopyConfigById(unsigned id);
private:
	const ResourceCopyConfig::ResourceCopyAll & resourcecopy_cfg;
};

//剧本战配置
class OperaBattleConfigWrap
{
public:
	OperaBattleConfigWrap();

	//根据闯关和难度获取配置
	const OperaBattleConfig::DifficultyReward & GetDifficultyRewardConfig(unsigned gateid, unsigned diff);

private:
	const OperaBattleConfig::BattleRewardAll & battle_cfg;
};

//机型试炼配置
class ModelTrialConfigWrap
{
public:
	ModelTrialConfigWrap();

	//获取每日挑战最大次数
	int GetMaxBuytimes();

	int GetPrice(unsigned times);

	const ModelTrialConfig::TrialGate & GetTrialGateConfig(unsigned gateid);

private:
	const ModelTrialConfig::ModelTrial & trial_cfg;
};

//跨国商人
class CrossBusinessConfigWrap
{
public:
	CrossBusinessConfigWrap();

	int GetRefreshCash();

	//根据开服时间差获取开服相关的索引
	int GetOpenPlatfromIndex(unsigned diff);

	//根据开服天数获取槽里的物品库信息
	const CrossBusinessConfig::OpenPlatformSlots & GetSlotsByDiff(unsigned diff);

	const CrossBusinessConfig::SlotGoods & GetGoodsById(unsigned id);

private:
	const CrossBusinessConfig::CrossBusinessCfg & cross_cfg;
};

//偷袭珍珠港
class AttackHarborConfigWrap
{
public:
	AttackHarborConfigWrap();

	const AttackHarborConfig::AttackPearlHarbor & GetHarborConfig() {return harbor_cfg;}

	//获取NPC刷新有关的开服索引
	int GetOpenIndex(unsigned diff);

	//获取国家排名奖励有关的开服索引
	const AttackHarborConfig::OpenPlatformReward & GetRewardByRankDiff(unsigned diff, unsigned rank);

	int GetTimeFrequency();

private:
	const AttackHarborConfig::AttackPearlHarbor & harbor_cfg;
};

//精英部队
class EliteNPCConfigWrap
{
public:
	EliteNPCConfigWrap();

	//根据开服时间和npc类型获取npc集合
	const WorldEliteConfig::TypeNPC & GetTypeNPC(unsigned diff, uint8_t type);

private:
	const WorldEliteConfig::EliteNPC & elite_cfg;
};

//部件售卖活动
class SellComponentConfigWrap
{
public:
	SellComponentConfigWrap();

	//获取商品配置
	const SellComponentConfig::GoodInfo & GetGoodsInfoByIndex(unsigned index);

private:
	const SellComponentConfig::SellComponent & sell_comp_cfg;
};

#endif /* USERCFGWRAP_H_ */
