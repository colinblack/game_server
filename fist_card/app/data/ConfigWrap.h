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
	const UserCfg::ChampionshipCfg& GetChampionshipById(unsigned id) const;

private:
	const UserCfg::User& cfg_;
};

class ActivityCfgWrap
{
public:
	ActivityCfgWrap();

	const User::ActivityItem& GetItem(unsigned id) const;
private:
	const User::Activity& cfg_;
};

class ItemCfgWrap
{
public:
	ItemCfgWrap();

	//获取道具配置
	const ConfigItem::PropItem & GetPropsItem(unsigned propsid) const;
private:
	const ConfigItem::Items & cfg_;
};

class HeroCfgWrap{
public:
	HeroCfgWrap();
	const Hero::HeroInfo& Hero();
	const Hero::HeroInfoList& GetHeroByHeroId(unsigned heroId);
	const Hero::HeroLevelExp& GetHeroByLevel(unsigned level);
	const Hero::HeroSkillUp& GetSkillInfoByLevel(unsigned level);
	const Hero::CardByGetHero& GetCardsByHeroId(unsigned heroId);

private:
	const Hero::HeroInfo &cfg_;

};

class CombineCfgWrap{
public:
	CombineCfgWrap();
	//整型是否能提升组合属性
	bool IsFormat(set<unsigned>& heroid);
	const Combine::HeroCombine& GetCombineByHeroId(set<unsigned>& heroid);

private:
	const Combine::HeroCombineInfo &cfg_;
};

class StarsCfgWarp{
public:
	StarsCfgWarp();
	const Stars::HeroWithStars& GetStarsInfoById(unsigned heroId);

private:
	const Stars::StarInfo &cfg_;
};

class ArchiveCfgWarp{
public:
	ArchiveCfgWarp();
	const Archive::HeroWithArchive& GetArchiveInfoInfoById(unsigned heroId);
	const Archive::ArchiveRward& GetArchiveRewardByLevel(unsigned level);

private:
	const Archive::ArchiveInfo &cfg_;
};

class DragonBallCfgWarp{
public:
	DragonBallCfgWarp();
	const DragonBall::HeroWithDragonBall& GetDragonBallInfoById(unsigned heroId);

private:
	const DragonBall::DragonBallInfo &cfg_;
};

class StagesCfgWarp{
public:
	StagesCfgWarp();
	const Stages::AllStage& GetStagesInfoById(unsigned id);
private:
	const Stages::StagesInfo &cfg_;
};

class AddWeightCfgWarp{
public:
	AddWeightCfgWarp();
	const AddWeight::PlayerAddWeight& GetPlayerAddWeightBylevel(unsigned level);

private:
	const AddWeight::AddWeightInfo &cfg_;
};

class GradeCfgWarp{
public:
	GradeCfgWarp();
	const Grade::GradeBattle& Grade();

private:
	const Grade::GradeBattle &cfg_;

};

class NpcCfgWarp{
public:
	NpcCfgWarp();
	const NpcConfig::NpcInfo& GetNpcById(unsigned npcid);

private:
	const NpcConfig::Npc &cfg_;
};

class RandomCfgWarp{
public:
	RandomCfgWarp();
	const Random::UserInfo& User(int idx);
	const CommonGiftConfig::CommonModifyItem& GetRewardByLevel(unsigned level);

	unsigned UserSize();
private:
	const Random::Random &cfg_;
};

class FriendCfgWarp{
public:
	FriendCfgWarp();
	const FriendConfig::LevelReward& GetRewardByLevel(unsigned level);

private:
	const FriendConfig::FriendInfo &cfg_;
};

class OnhookCfgWarp{
public:
	OnhookCfgWarp();
	const Onhook::OnhookInfo& GetRewardByStageId(unsigned id);
private:
	const Onhook::Onhook &cfg_;

};

class MartialClubCfgWarp{
public:
	MartialClubCfgWarp();
	const MartialClub::MartialClubInfo& GetMartialClubByGrade(unsigned grade);
private:
	const MartialClub::MartialClubCfg &cfg_;
};

class RoBotCfgWarp{
public:
	RoBotCfgWarp();
	const RobotConfig::RobotChampionshipItem& Championship();
	const RobotConfig::RobotItem& GetChampionRobotById(unsigned id);
	const RobotConfig::RobotGradeBattleItem& GetGradeRobotByGrade(unsigned grade);
private:
	const RobotConfig::Robots &cfg_;
};

class ActiveCfgWrap{
public:
	ActiveCfgWrap();
	const ActivityConfig::Activity& Activity(){return cfg_;}
	const ActivityConfig::InviteFriendReward& GetInviteRewardBySeq(unsigned seq);
	const ActivityConfig::AccumulateReward&  GetInviteRewardByNum(unsigned num);
	const ActivityConfig::LuckyDrawReward&  GetLuckyDrawRewardById(unsigned id);
private:
	const ActivityConfig::Activity &cfg_;
};

class CardsCfgWrap{
public:
	CardsCfgWrap();
	const Cards::CardsCfg& Obj();
	const Cards::CardInfo& GetCardsCfgById(unsigned id);
	const Cards::CardUpdateStar& GetStartUpdateCfgById(unsigned id);
	const Cards::CardDup& GetStartDupCfgById(unsigned id);
	const Cards::CardPurchase& GetPurchaseCfgById(unsigned id);

private:
	const Cards::CardsCfg &cfg_;
};


#endif /* USERCFGWRAP_H_ */
