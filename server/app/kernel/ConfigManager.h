/*
 * ConfigManager.h
 *
 *  Created on: 2016-8-22
 *      Author: Ralf
 */

#ifndef CONFIGMANAGER_H_
#define CONFIGMANAGER_H_

#include "Common.h"
#include "ConfigPB.h"
#include "ConfigInc.h"
#include "ProtoInc.h"

/*
 *  配置文件管理器，增加新配置时，把新的pb文件加入ConfigInc.h，定义新的const成员，构造函数中写入配置文件名
 */
class ConfigManager : public CSingleton<ConfigManager>
{
private:
	friend class CSingleton<ConfigManager>;
	virtual ~ConfigManager(){}
	ConfigManager()
		:demo("demo17.json")
		,bag("bag.json")
		,equipment("equip.json")
		,equipshop("olequipmentshop.json")
		,buildings("Buildings.json")
		,passSystem("PassSystem.json")
		,heroInfo("hero.json")
		,heroAttacks("heroattack.json")
		,tavern("tavern.json")
		,user("UserConfig.json")
		,resource("ResourceConfig.json")
		,mission("mission.json")
		,npc("npc.json")
		,sciences("ScienceConfig.json")
		,equipsmelt("equipsmelt.json")
		,vipgift("vipgift.json")
		,weapon("WeaponConfig.json")
		,marketcfg("market.json")
		,worldreward("worldreward.json")
		,exploit("ExploitBoxConfig.json")
		,first_recharge("RewardConfig.json")
		,integral_time("RewardConfig.json")
		,cumulationlogin("RewardConfig.json")
		,country_task("RewardConfig.json")
		,governaffairs("governaffair.json")
		,vip("VIPConfig.json")
		,activity("ActivityTime.json", false)
		,equipsuit("equipsuit.json")
		,pk_field("RewardConfig.json")
		,specailequip("specialequip.json")
		,npcactivity("npcactivity.json")
		,limit_shop("limitShop.json")
		,killrank("killrank.json")
		,official("OfficialConfig.json")
		,foggate("foggate.json")
		,mine("MineConfig.json")
		,cash_back("ActivityConfig.json")
		,pass_activity("ActivityConfig.json")
		,bot("Bot.json")
		,dailymissions("dailymission.json")
		,smelt_activity("ActivityConfig.json")
		,achievements("achievement.json")
		,component("component.json")
		,touch_gold("ActivityConfig.json")
		,huge_discount("HugeDiscount.json")
		,shakedice("shakedice.json")
		,littlecharge("littlecharge.json")
		,enlivenkill("enlivenkill.json")
		,resource_copy("resourceCopy.json")
		,operobattle("operabattle.json")
		,modeltrial("modeltrial.json")
		,crossbusiness("crossbusiness.json")
		,attackharbor("attackharbor.json")
		,elitenpc("worldelite.json")
		,sell_component("sellcomponent.json")
	{
		Init();
	}

	void Init();
	static bool m_init;

public:
	static bool Reload();
	static void Fail(){m_init = false;}
	bool Inited(){return m_init;}

	const ConfigPB<Demo::Demo> demo;
	const ConfigPB<BagConfig::BagCosts> bag;
	const ConfigPB<EquipmentConfig::EquipList> equipment;
	const ConfigPB<EquipmentShopConfig::EquipmentShop> equipshop;
	const ConfigPB<Building::Buildings> buildings;
	const ConfigPB<PassSystemConfig::System> passSystem; //关卡配置

	const ConfigPB<Hero::HeroInfoList> heroInfo; //
	const ConfigPB<HeroAttackConfig::Attack> heroAttacks;
	const ConfigPB<TavernConfig::HeroRecruit> tavern;
	const ConfigPB<UserCfg::User> user;
	const ConfigPB<ResourceConfig::Resource> resource;
	const ConfigPB<MissionConfig::MissionAll> mission;
	const ConfigPB<NPC::NPCList> npc;
	const ConfigPB<ScienceConfig::Science> sciences;
	const ConfigPB<EquipSmeltConfig::EquipSmelt> equipsmelt;
	const ConfigPB<VipGiftConfig::VIPGift> vipgift;   //会员礼包，暂时只配置了黄钻
	const ConfigPB<WeaponConfig::Weapon> weapon;
	const ConfigPB<MarketConfig::MarketAll> marketcfg;
	const ConfigPB<WorldRewardConfig::WorldReward> worldreward;  //争霸奖励
	const ConfigPB<ExploitBoxConfig::Exploit> exploit; //功勋宝箱
	const ConfigPB<RewardConfig::FirstRecharge> first_recharge; //首充
	const ConfigPB<RewardConfig::IntegralTime>	integral_time; //整点/后勤奖励
	const ConfigPB<RewardConfig::CumulationLoginReward> cumulationlogin; //累积登录奖励
	const ConfigPB<RewardConfig::CountryTask> country_task; //国战任务奖励
	const ConfigPB<GovernAffairConfig::GovernAffairs> governaffairs; //政务事件
	const ConfigPB<VIPConfig::UVIP> vip; //vip配置
	const ConfigPB<User::Activity> activity;
	const ConfigPB<EquipSuitConfig::EquipSuit> equipsuit; //套装
	const ConfigPB<RewardConfig::PkField>	pk_field; //竞技场奖励
	const ConfigPB<SpecialEquipConfig::SpecialEquips>  specailequip;  //定制装备
	const ConfigPB<ProtoNPCActivity::NPCActivityConfigCPP>  npcactivity;  //广结名士活动
	const ConfigPB<ShopConfig::LimitShop> limit_shop; //限时商店
	const ConfigPB<KillRankConfig::KillRank> killrank; //杀敌排行榜
	const ConfigPB<OfficialConfig::Official> official; //官职系统
	const ConfigPB<FogGateConfig::FogGates> foggate; //迷雾战
	const ConfigPB<MineConfig::Mine> mine; //小煤窑
	const ConfigPB<ActivityConfig::CashBack> cash_back; //充值返现活动
	const ConfigPB<ActivityConfig::PassActivity> pass_activity; //闯关送钻
	const ConfigPB<BotConfig::BotConfig> bot;
	const ConfigPB<DailyMissionConfig::DailyMissonItemList> dailymissions; //每日任务
	const ConfigPB<ActivityConfig::SmeltActivity> 	smelt_activity; //洗练放送
	const ConfigPB<AchievementConfig::AchievementList> achievements; //成就
	const ConfigPB<ComponentConfig::Component> component; //部件
	const ConfigPB<ActivityConfig::TouchGold> touch_gold; //摸金校尉
	const ConfigPB<ActivityConfig::HugeDiscount> huge_discount; //超值钜惠
	const ConfigPB<ShakeDiceConfig::ShakeDiceAll> shakedice; //摇骰子
	const ConfigPB<LittleChargeConfig::LittleCharge> littlecharge; //充点小钱
	const ConfigPB<EnlivenKillConfig::EnlivenKill> enlivenkill; //杀敌活跃
	const ConfigPB<ResourceCopyConfig::ResourceCopyAll> resource_copy; //资源副本
	const ConfigPB<OperaBattleConfig::BattleRewardAll> operobattle; //剧本战
	const ConfigPB<ModelTrialConfig::ModelTrial> modeltrial; //机型试炼
	const ConfigPB<CrossBusinessConfig::CrossBusinessCfg> crossbusiness; //跨国商人
	const ConfigPB<AttackHarborConfig::AttackPearlHarbor> attackharbor; //偷袭珍珠港
	const ConfigPB<WorldEliteConfig::EliteNPC> elitenpc; //精英部队
	const ConfigPB<SellComponentConfig::SellComponent> sell_component; //部件售卖活动

	map<unsigned, unsigned> m_equipmap;   //eqid->i equip配置文件中部位库中的索引
	map<uint32_t, int> mapEqidPrice;   //equipshop配置文件
	map<unsigned, int>  m_mapHeroIndex;   //酒馆英雄索引映射
	map<unsigned, int> m_mapGateIndex; //酒馆闯关id索引映射
	map<unsigned, pair<int, unsigned> > m_mapMissonIndex;   //mid =>pair<keytype, index>
	map<unsigned, set<unsigned> > m_mapPreMission; //pre->set(mid)
	map<unsigned, unsigned> m_mapBuildIndex;  //建筑配置文件的映射
	map<unsigned, unsigned> m_mapVipLevelIndex;   //黄钻vip等级映射
	map<unsigned, unsigned> m_mapTypeIndex;  //集市资源类型与索引的映射关系
	map<unsigned, unsigned> m_mapHourIndex; //争霸据点奖励配置中，时间与下标的映射关系
	map<unsigned, unsigned> m_afairid; //政务事件id与下标的映射关系
	map<unsigned, unsigned> m_preeqidIndex;  //前置eqid的映射
	map<unsigned, unsigned> specialIndex; //定制装备的映射
	map<unsigned, pair<unsigned, unsigned> >  dayAffaiIndex;//广结名士活动，事件id与天数和下标的映射。id->pari<day, index>
	map<unsigned, unsigned> foggateIndex; //迷雾战，关卡id和下标的映射. gateid->index
	map<unsigned, pair<unsigned, unsigned> > dailymissionIndex;  //每日任务映射. id=>pair<tech,index>
	map<unsigned, unsigned> achieveidIndex;  //成就id与下标的映射关系
	map<unsigned, vector<unsigned> > achieveTypeRelate; //成就id和类型的对应关系
	map<unsigned, unsigned> componentIndex;  //部件id与下标的映射关系
	map<unsigned, unsigned>	copyIndex;  //副本id与下标的映射关系
	map<unsigned, unsigned> operabattleIndex; //剧本战id与下标的映射关系
	map<unsigned, unsigned> trialIndex;  //试炼关卡下标映射关系
	map<unsigned, pair<unsigned, unsigned> > businessIndex;  //跨国商人id和位置映射. id=>pair<openplatform, index>

	const Hero::HeroInfo& GetHero(unsigned id);
	map<unsigned, unsigned> m_heroInfo;
	bool IsHeroStrengthShape(unsigned id, unsigned g, unsigned s);
	map<unsigned, map<unsigned, set<unsigned> > > m_heroShape;
	bool IsHeroG(unsigned id, unsigned g);
	map<unsigned, set<unsigned> > m_heroG;

	const NPC::NPCInfo& GetNPC(unsigned id);
	map<unsigned, unsigned> m_npcInfo;
	bool IsNPCStrengthShape(unsigned id, unsigned g, unsigned s);
	map<unsigned, map<unsigned, set<unsigned> > > m_npcShape;
	bool IsNPCG(unsigned id, unsigned g);
	map<unsigned, set<unsigned> > m_npcG;

	unsigned GetNPCID(unsigned day, unsigned type);
	map<unsigned, unsigned> m_normalNPC;
	map<unsigned, unsigned> m_attackNPC;
	map<unsigned, unsigned> m_defendNPC;

	unsigned GetGid(uint16_t cid);
	unsigned GetScale(uint16_t cid);
	map<unsigned, unsigned> m_cityG;
	map<unsigned, unsigned> m_cityS;

	const ScienceConfig::ScienceItem& GetScience(unsigned id);
	map<unsigned, unsigned> m_ScienceInfo;

	map<unsigned, unsigned> m_weapon_index;
	map<unsigned, std::map<unsigned, unsigned> > m_weapon_lvl_index;

	//npc 副本
	std::map<unsigned, unsigned> m_pass_index;

	map<unsigned, unsigned> m_actmap;
	bool GetActivity(unsigned id, User::ActivityItem& act);

	unsigned GetKillReward(unsigned level);

	map<unsigned, unsigned> m_botAccount;
	int GetBotIndex(unsigned id, unsigned day);
	int NeedChangeBotAccount(unsigned id, unsigned day1, unsigned day2);
	const BotConfig::BotPlayer& GetBotAccount(unsigned id, int index);
	map<pair<unsigned, unsigned>, unsigned> m_botName;
	string GetBotName(unsigned id, unsigned kingdom, unsigned serverid);
	string GetBotChat();

	map<unsigned, unsigned> m_battleReward[e_battle_reward_type_max];
	unsigned m_battleRewardR;
	unsigned GetBattleRewardCount(unsigned t, unsigned d);
	unsigned GetBattleRewardType();

	map<unsigned, vector<unsigned> > m_cityNPC[e_city_sacle_4];
	unsigned m_cityRewardR[e_city_sacle_4];
	unsigned GetCityRewardCount(unsigned id, unsigned t);
	unsigned GetCityRewardType(unsigned id);
	const vector<unsigned>& GetCityNPC(unsigned id, unsigned d);
};

#endif /* CONFIGMANAGER_H_ */
