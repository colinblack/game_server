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

const UserCfg::ChampionshipCfg& UserCfgWrap::GetChampionshipById(unsigned id) const
{
	if(!ConfigManager::Instance()->champion_id_index.count(id))
	{
		error_log("param error. heroId=%u", id);
		throw runtime_error("param_error");
	}

	unsigned index = ConfigManager::Instance()->champion_id_index[id];
	return cfg_.championship(index);
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
ItemCfgWrap::ItemCfgWrap()
	: cfg_(ConfigManager::Instance()->propsitem.m_config)
{

}

const ConfigItem::PropItem & ItemCfgWrap::GetPropsItem(unsigned propsid) const
{
	if (!ConfigManager::Instance()->ItemIndex.count(propsid))
	{
		error_log("param error. propsid=%u", propsid);
		throw runtime_error("param_error");
	}

	unsigned index = ConfigManager::Instance()->ItemIndex[propsid];

	return cfg_.itemes(index);
}

HeroCfgWrap::HeroCfgWrap()
	: cfg_(ConfigManager::Instance()->hero.m_config)
{
}


const Hero::HeroInfoList& HeroCfgWrap::GetHeroByHeroId(unsigned heroId)
{
	if(!ConfigManager::Instance()->hero_index.count(heroId))
	{
		error_log("param error. heroId=%u", heroId);
		throw runtime_error("param_error");
	}
	unsigned index = ConfigManager::Instance()->hero_index[heroId];
	return cfg_.hero(index);
}


const Hero::HeroLevelExp& HeroCfgWrap::GetHeroByLevel(unsigned level)
{
	if(!ConfigManager::Instance()->hero_level_index.count(level))
	{
		error_log("param error. level=%u", level);
		throw runtime_error("param_error");
	}
	unsigned index = ConfigManager::Instance()->hero_level_index[level];
	return cfg_.levelexp(index);
}

const Hero::HeroSkillUp& HeroCfgWrap::GetSkillInfoByLevel(unsigned level)
{
	if(!ConfigManager::Instance()->hero_skill_level_index.count(level))
	{
		error_log("param error. level=%u", level);
		throw runtime_error("param_error");
	}
	unsigned index = ConfigManager::Instance()->hero_skill_level_index[level];
	return cfg_.skillup(index);
}

const Hero::HeroInfo& HeroCfgWrap::Hero()
{
	return cfg_;
}


CombineCfgWrap::CombineCfgWrap()
	: cfg_(ConfigManager::Instance()->combine.m_config)
{
}


bool CombineCfgWrap::IsFormat(set<unsigned>& heroid)
{
	return ConfigManager::Instance()->combine_heros_index.count(heroid) != 0;
}

const Combine::HeroCombine& CombineCfgWrap::GetCombineByHeroId(set<unsigned>& heroid)
{
	if(!IsFormat(heroid))
	{
		error_log("param error");
		throw runtime_error("param_error");
	}

	unsigned index = ConfigManager::Instance()->combine_heros_index[heroid];
	return cfg_.combineinfo(index);
}

StarsCfgWarp::StarsCfgWarp()
	: cfg_(ConfigManager::Instance()->stars.m_config)
{
}

const Stars::HeroWithStars& StarsCfgWarp::GetStarsInfoById(unsigned heroId)
{
	if(!ConfigManager::Instance()->hero_index.count(heroId))
	{
		error_log("param error. heroId=%u", heroId);
		throw runtime_error("param_error");
	}
	unsigned index = ConfigManager::Instance()->hero_index[heroId];

	return cfg_.starinfo(index);
}


ArchiveCfgWarp::ArchiveCfgWarp()
	: cfg_(ConfigManager::Instance()->archive.m_config)
{
}


const Archive::HeroWithArchive& ArchiveCfgWarp::GetArchiveInfoInfoById(unsigned heroId)
{
	if(!ConfigManager::Instance()->archive_index.count(heroId))
	{
		error_log("param error. heroId=%u", heroId);
		throw runtime_error("param_error");
	}

	unsigned index = ConfigManager::Instance()->archive_index[heroId];

	return cfg_.archiveinfo(index);
}

const Archive::ArchiveRward& ArchiveCfgWarp::GetArchiveRewardByLevel(unsigned level)
{
	if(!ConfigManager::Instance()->archive_level_reward_index.count(level))
	{
		error_log("param error");
		throw runtime_error("param_error");
	}
	unsigned index = ConfigManager::Instance()->archive_level_reward_index[level];

	return cfg_.rewards(index);
}


DragonBallCfgWarp::DragonBallCfgWarp()
	: cfg_(ConfigManager::Instance()->dragon_ball.m_config)
{
}


const DragonBall::HeroWithDragonBall& DragonBallCfgWarp::GetDragonBallInfoById(unsigned heroId)
{
	if(!ConfigManager::Instance()->hero_index.count(heroId))
	{
		error_log("param error. heroId=%u", heroId);
		throw runtime_error("param_error");
	}
	unsigned index = ConfigManager::Instance()->hero_index[heroId];

	return cfg_.dragonballinfo(index);
}



StagesCfgWarp::StagesCfgWarp()
	: cfg_(ConfigManager::Instance()->stages.m_config)
{
}

const Stages::AllStage& StagesCfgWarp::GetStagesInfoById(unsigned id)
{
	if(!ConfigManager::Instance()->stage_index.count(id))
	{
		error_log("param error. heroId=%u", id);
		throw runtime_error("param_error");
	}
	unsigned index = ConfigManager::Instance()->stage_index[id];

	return cfg_.stage(index);
}


AddWeightCfgWarp::AddWeightCfgWarp()
	:cfg_(ConfigManager::Instance()->addWeight.m_config)
{
}


const AddWeight::PlayerAddWeight& AddWeightCfgWarp::GetPlayerAddWeightBylevel(unsigned level)
{
	if(!ConfigManager::Instance()->add_weight_index.count(level))
	{
		error_log("param error. level=%u", level);
		throw runtime_error("param_error");
	}

	return cfg_.addweight().player(level);
}



GradeCfgWarp::GradeCfgWarp()
	:cfg_(ConfigManager::Instance()->grade.m_config)
{
}

const Grade::GradeBattle& GradeCfgWarp::Grade()
{
	return cfg_;
}

NpcCfgWarp::NpcCfgWarp()
	:cfg_(ConfigManager::Instance()->npc.m_config)
{
}

const NpcConfig::NpcInfo&  NpcCfgWarp::GetNpcById(unsigned npcid)
{
	if(!ConfigManager::Instance()->npc_index.count(npcid))
	{
		error_log("param error. npcid=%u", npcid);
		throw runtime_error("param_error");
	}

	unsigned index = ConfigManager::Instance()->npc_index[npcid];

	return cfg_.allnpc(index);
}

RandomCfgWarp::RandomCfgWarp()
	:cfg_(ConfigManager::Instance()->random.m_config)
{
}

const Random::UserInfo& RandomCfgWarp::User(int idx)
{
	if(idx >= cfg_.users_size())
	{
		error_log("param error");
		throw runtime_error("param_error");
	}
	return cfg_.users(idx);
}
const CommonGiftConfig::CommonModifyItem& RandomCfgWarp::GetRewardByLevel(unsigned level)
{
	if(!ConfigManager::Instance()->random_level_index.count(level))
	{
		error_log("param error");
		throw runtime_error("param_error");
	}

	unsigned index = ConfigManager::Instance()->random_level_index[level];
	return cfg_.rewards(index).reward();
}


unsigned RandomCfgWarp::UserSize()
{
	return cfg_.users_size();
}

FriendCfgWarp::FriendCfgWarp()
	:cfg_(ConfigManager::Instance()->friends.m_config)
{
}

const FriendConfig::LevelReward& FriendCfgWarp::GetRewardByLevel(unsigned level)
{
	if(!ConfigManager::Instance()->friend_level_reward_index.count(level))
	{
		error_log("param error");
		throw runtime_error("param_error");
	}

	unsigned index = ConfigManager::Instance()->friend_level_reward_index[level];
	return cfg_.rewards(index);
}

OnhookCfgWarp::OnhookCfgWarp()
	:cfg_(ConfigManager::Instance()->onhook.m_config)
{
}

const Onhook::OnhookInfo& OnhookCfgWarp::GetRewardByStageId(unsigned id)
{
	if(!ConfigManager::Instance()->onhook_stage_index.count(id))
	{
		error_log("param error");
		throw runtime_error("param_error");
	}

	unsigned index = ConfigManager::Instance()->onhook_stage_index[id];
	return cfg_.onhooks(index);
}

MartialClubCfgWarp::MartialClubCfgWarp()
	:cfg_(ConfigManager::Instance()->martialClub.m_config)
{
}

const MartialClub::MartialClubInfo& MartialClubCfgWarp::GetMartialClubByGrade(unsigned grade)
{
	if(!ConfigManager::Instance()->martial_club_grade_index.count(grade))
	{
		error_log("param error, grade=%u", grade);
		throw runtime_error("param_error");
	}
	unsigned index = ConfigManager::Instance()->martial_club_grade_index[grade];
	return cfg_.club(index);
}

RoBotCfgWarp::RoBotCfgWarp()
	:cfg_(ConfigManager::Instance()->robot.m_config)
{
}

const RobotConfig::RobotGradeBattleItem& RoBotCfgWarp::GetGradeRobotByGrade(unsigned grade)
{
	if(!ConfigManager::Instance()->graderobot_grade_index.count(grade))
	{
		error_log("param error");
		throw runtime_error("param_errror");
	}

	unsigned index = ConfigManager::Instance()->graderobot_grade_index[grade];
	return cfg_.gradebattle(index);
}

const RobotConfig::RobotItem& RoBotCfgWarp::GetChampionRobotById(unsigned id)
{
	if(!ConfigManager::Instance()->champion_robot_index.count(id))
	{
		error_log("param error, id: %u", id);
		throw runtime_error("param_error");
	}

	unsigned index = ConfigManager::Instance()->champion_robot_index[id];
	return cfg_.championship().item(index);

}

const RobotConfig::RobotChampionshipItem& RoBotCfgWarp::Championship()
{
	return cfg_.championship();
}

ActiveCfgWrap::ActiveCfgWrap()
	:cfg_(ConfigManager::Instance()->activeCfg.m_config)
{
}

const ActivityConfig::InviteFriendReward& ActiveCfgWrap::GetInviteRewardBySeq(unsigned seq)
{
	if(!ConfigManager::Instance()->invite_reward_index.count(seq))
	{
		error_log("param error");
		throw runtime_error("param_errror");
	}

	unsigned index = ConfigManager::Instance()->invite_reward_index[seq];
	return cfg_.inviterewards(index);
}

const ActivityConfig::AccumulateReward&  ActiveCfgWrap::GetInviteRewardByNum(unsigned num)
{
	if(!ConfigManager::Instance()->invite_addreward_index.count(num))
	{
		error_log("param error");
		throw runtime_error("param_error");
	}

	unsigned index = ConfigManager::Instance()->invite_addreward_index[num];
	return cfg_.accrewards(index);
}

const ActivityConfig::LuckyDrawReward&  ActiveCfgWrap::GetLuckyDrawRewardById(unsigned id)
{
	if(!ConfigManager::Instance()->luck_reward_id_index.count(id))
	{
		error_log("param error");
		throw runtime_error("param_error");
	}

	unsigned index = ConfigManager::Instance()->luck_reward_id_index[id];
	return cfg_.luckyreward(index);
}

