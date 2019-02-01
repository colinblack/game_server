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

/*
 *  配置文件管理器，增加新配置时，把新的pb文件加入ConfigInc.h，定义新的const成员，构造函数中写入配置文件名
 */
class ConfigManager : public CSingleton<ConfigManager>
{
private:
	friend class CSingleton<ConfigManager>;
	virtual ~ConfigManager(){}
	ConfigManager()
		:demo("demo.json")
		,user("UserConfig.json")
		,activity("ActivityTime.json", false)
		,propsitem("item.json")
		,hero("hero.json")
		,combine("combine.json")
		,stars("stars.json")
		,archive("archive.json")
		,dragon_ball("dragonball.json")
		,battleDemoConfig("battleDemoConfig.json")
		,stages("stages.json")
		,addWeight("addweight.json")
		,grade("grade.json")
		,npc("npcConfig.json")
		,random("random.json")
		,friends("friend.json")
		,onhook("onhook.json")
		,martialClub("martialClub.json")
		,robot("RobotConfig.json")
		,activeCfg("activityConfig.json")
		,cardsCfg("cards.json")
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
	const ConfigPB<UserCfg::User> user;
	const ConfigPB<User::Activity> activity;
	const ConfigPB<ConfigItem::Items> 	propsitem;
	const ConfigPB<Hero::HeroInfo> hero;
	const ConfigPB<Combine::HeroCombineInfo> combine;
	const ConfigPB<Stars::StarInfo> stars;
	const ConfigPB<Archive::ArchiveInfo> archive;
	const ConfigPB<DragonBall::DragonBallInfo> dragon_ball;
	const ConfigPB<BattleDemoConfig::BattleDemoConfig> 	battleDemoConfig;
	const ConfigPB<Stages::StagesInfo> stages;
	const ConfigPB<AddWeight::AddWeightInfo> addWeight;
	const ConfigPB<Grade::GradeBattle> grade;
	const ConfigPB<NpcConfig::Npc> npc;
	const ConfigPB<Random::Random> random;
	const ConfigPB<FriendConfig::FriendInfo> friends;
	const ConfigPB<Onhook::Onhook> onhook;
	const ConfigPB<MartialClub::MartialClubCfg> martialClub;
	const ConfigPB<RobotConfig::Robots> robot;
	const ConfigPB<ActivityConfig::Activity> activeCfg;
	const ConfigPB<Cards::CardsCfg> cardsCfg;

	map<unsigned, unsigned> m_actmap;
	map<unsigned, unsigned > ItemIndex;  //id->index，道具
	map<unsigned, unsigned> hero_index; //英雄ID与索引的映射
	map<unsigned, unsigned> hero_level_index; //英雄等级与索引映射
	map<unsigned, unsigned> hero_skill_level_index; //英雄技能等级与索引映射

	map<unsigned, unsigned> stage_index; //关卡ID与索引的映射
	map<unsigned, unsigned> npc_index; //npcid=>idx
	map<unsigned , unsigned> add_weight_index; //玩家等级与索引映射
	map<set<unsigned>, unsigned> combine_heros_index; //组合heroid与索引映射
	vector<uint64_t> hero_level_exp; //英雄等级经验
	map<unsigned, unsigned> archive_index; //图鉴id与索引映射
	map<unsigned, unsigned> archive_level_reward_index; //图鉴等级与奖励索引
	map<unsigned, unsigned> random_level_index; //随机挑战玩家等级与索引关系
	map<unsigned, vector<unsigned>> archive_chip;//所有英雄拥有的图鉴碎片
	map<unsigned, int> power_props_index;  //体力道具id对应索引
	map<unsigned, unsigned> friend_level_reward_index; //挑战好友玩家等级对饮索引
	map<unsigned, unsigned> onhook_stage_index; //挂机奖励关卡对应索引
	map<unsigned, unsigned> martial_club_grade_index; //武馆星级对应索引
	map<unsigned, unsigned>	graderobot_grade_index;	//排位赛假玩家和排位对应索引
	map<unsigned, unsigned> champion_robot_index;	//杯赛假玩家id对应索引
	map<unsigned, unsigned> champion_id_index;	//杯赛id对应索引
	map<unsigned, unsigned> invite_reward_index; //邀请奖励与需要对应索引
	map<unsigned, unsigned> invite_addreward_index; //累积邀请奖励与需要对应索引
	map<unsigned, map<unsigned, unsigned>> luck_reward_range_index; //幸运抽奖范围对应索引
	map<unsigned, unsigned> luck_reward_id_index; //幸运抽检id对应索引
	map<unsigned, unsigned> card_id_index;		  //卡牌信息id对应索引
	map<unsigned, unsigned> card_update_id_index; //卡牌升星id对应索引
	map<unsigned, unsigned> card_dup_id_index;	//卡牌复制id对应索引
	map<unsigned, unsigned> card_purchase_id_index;	//卡牌购买id对应索引
	map<unsigned, unsigned> hero_cards_id_index; //购买英雄所带英雄卡英雄id对应索引

	bool GetActivity(unsigned id, User::ActivityItem& act);
	int GetPowerPropIndex(unsigned propid);
	map<unsigned, unsigned> m_server;
	const Demo::Server& GetServer(unsigned server);
	bool IsServerMergeTogather(unsigned s1, unsigned s2);
	unsigned GetMainServer(unsigned server);
	bool IsNeedConnect(unsigned server);
	bool IsNeedConnectByUID(unsigned uid);
	bool IsNeedConnectByAID(unsigned aid);
};

#endif /* CONFIGMANAGER_H_ */
