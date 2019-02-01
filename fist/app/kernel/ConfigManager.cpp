/*
 * ConfigManager.cpp
 *
 *  Created on: 2016-8-22
 *      Author: Ralf
 */


#include "ConfigManager.h"

bool ConfigManager::m_init = true;

bool ConfigManager::Reload()
{
	ConfigManager *temp = new ConfigManager;
	if(!m_init)
	{
		m_init = true;
		delete temp;
		return false;
	}
	delete temp;
	Destroy();
	temp = Instance();
	return true;
}

void ConfigManager::Init()
{
	if(!m_init)
		return;

	for(int i=0;i<demo.m_config.battle_size();++i)
	{
		if(demo.m_config.battle(i).begin() > demo.m_config.battle(i).end())
		{
			error_log("battle error begin=%u, end=%u", demo.m_config.battle(i).begin(), demo.m_config.battle(i).end());
			Fail();
			return;
		}
		for(int j=demo.m_config.battle(i).begin();j<=demo.m_config.battle(i).end();++j)
			m_server[j] = i;
	}

	for(int i=0;i<activity.m_config.act_size();++i)
		m_actmap[activity.m_config.act(i).id()] = i;

	//道具
	ItemIndex.clear();

	for(int i = 0; i < propsitem.m_config.itemes_size(); ++i)
	{
		unsigned id = propsitem.m_config.itemes(i).id();
		ItemIndex[id] = i;
	}

    hero_index.clear();
    for(int i = 0; i < hero.m_config.hero_size(); ++i)
    {
    	unsigned id =  hero.m_config.hero(i).id();
    	hero_index[id] = i;
    }

    stage_index.clear();
    for(int i = 0; i < stages.m_config.stage_size(); ++i)
    {
    	unsigned id = stages.m_config.stage(i).id();
    	stage_index[id] = i;
    }

    npc_index.clear();
	for(int i = 0; i < npc.m_config.allnpc_size(); ++i)
	{
		unsigned npc_id = npc.m_config.allnpc(i).id();
		npc_index[npc_id] = i;
	}


    add_weight_index.clear();
    for(int i = 0; i < addWeight.m_config.addweight().player_size(); ++i)
    {
    	unsigned level = addWeight.m_config.addweight().player(i).level();
    	add_weight_index[level] = i;
    }

    hero_level_index.clear();
    for(int i = 0; i < hero.m_config.levelexp_size(); ++i)
    {
    	unsigned level = hero.m_config.levelexp(i).level();
    	hero_level_index[level] = i;
    }

    hero_skill_level_index.clear();
    for(int i = 0; i < hero.m_config.skillup_size(); ++i)
    {
    	unsigned level = hero.m_config.skillup(i).level();
    	hero_skill_level_index[level] = i;
    }

    combine_heros_index.clear();
    for(int i = 0; i < combine.m_config.combineinfo_size(); ++i)
    {
    	auto& heroid = combine.m_config.combineinfo(i).heroid();
    	combine_heros_index[set<unsigned>(heroid.begin(), heroid.end())] = i;
    }

    hero_level_exp.clear();
    unsigned exp = 0;
    for(int i = 0; i < hero.m_config.levelexp_size(); ++i)
    {
    	hero_level_exp.push_back(exp);
    	exp += hero.m_config.levelexp(i).exp();
    }

    archive_index.clear();

    for(int i = 0; i < archive.m_config.archiveinfo_size(); ++i)
    {
    	unsigned id = archive.m_config.archiveinfo(i).id();
    	archive_index[id] = i;
    }

    archive_level_reward_index.clear();
	for(int i = 0; i < archive.m_config.rewards_size(); ++i)
	{
		unsigned level = archive.m_config.rewards(i).level();
		archive_level_reward_index[level] = i;
	}


    random_level_index.clear();
    for(int i = 0; i < random.m_config.rewards_size(); ++i)
    {
    	unsigned level = random.m_config.rewards(i).level();
    	random_level_index[level] = i;
    }

    archive_chip.clear();
    for(int i = 0; i < propsitem.m_config.itemes_size(); ++i)
    {
    	unsigned type = propsitem.m_config.itemes(i).type();
    	unsigned chipId = propsitem.m_config.itemes(i).id();
    	if(ARCHIVE_CHIP_TYPE == type)
    	{
    		unsigned heroId = propsitem.m_config.itemes(i).heroid();
    		archive_chip[heroId].push_back(chipId);
    	}
    }
    power_props_index.clear();
    power_props_index = {{8, 0}, {9, 1}, {10, 2}};

    friend_level_reward_index.clear();
    for(int i = 0; i < friends.m_config.rewards_size(); ++i)
    {
    	unsigned level = friends.m_config.rewards(i).level();
    	friend_level_reward_index[i] = level;
    }

    onhook_stage_index.clear();
    for(int i = 0; i < onhook.m_config.onhooks_size(); ++i)
    {
    	unsigned id = onhook.m_config.onhooks(i).stageid();
    	onhook_stage_index[i] = id;
    }
    martial_club_grade_index.clear();
    for(int i = 0; i < martialClub.m_config.club_size(); ++i)
    {
    	unsigned grade = martialClub.m_config.club(i).grade();
    	martial_club_grade_index[grade] = i;
    }
    graderobot_grade_index.clear();
    for(int i = 0; i < robot.m_config.gradebattle_size(); ++i)
    {
    	unsigned grade = robot.m_config.gradebattle(i).grade();
    	graderobot_grade_index[grade] = i;
    }
    champion_robot_index.clear();
    for(int i = 0; i < robot.m_config.championship().item_size(); ++i)
    {
    	unsigned id = robot.m_config.championship().item(i).id();
    	champion_robot_index[id] = i;
    }
    champion_id_index.clear();
    for(int i = 0; i < user.m_config.championship_size(); ++i)
    {
    	unsigned id =  user.m_config.championship(i).id();
    	champion_id_index[id] = i;
    }


    invite_reward_index.clear();
    for(int i = 0; i < activeCfg.m_config.inviterewards_size(); ++i)
    {
    	unsigned seq = activeCfg.m_config.inviterewards(i).seq();
    	invite_reward_index[seq] = i;
    }
    invite_addreward_index.clear();
    for(int i = 0; i < activeCfg.m_config.accrewards_size(); ++i)
    {
    	unsigned num = activeCfg.m_config.accrewards(i).num();
    	invite_addreward_index[num] = i;
    }
    luck_reward_range_index.clear();
    for(int i = 0; i < activeCfg.m_config.luckyreward_size(); ++i)
    {
    	unsigned range = activeCfg.m_config.luckyreward(i).range();
    	unsigned id = activeCfg.m_config.luckyreward(i).id();
    	luck_reward_range_index[range][id] = i;
    }
    luck_reward_id_index.clear();
    for(int i = 0; i < activeCfg.m_config.luckyreward_size(); ++i)
    {
    	unsigned id = activeCfg.m_config.luckyreward(i).id();
    	luck_reward_id_index[id] = i;
    }

}


bool ConfigManager::GetActivity(unsigned id, User::ActivityItem& act)
{
	if(m_actmap.count(id))
	{
		act = activity.m_config.act(m_actmap[id]);
		return true;
	}
	return false;
}

int ConfigManager::GetPowerPropIndex(unsigned propid)
{
	if(0 != power_props_index.count(propid))
		return power_props_index[propid];
	return -1;
}


const Demo::Server& ConfigManager::GetServer(unsigned server)
{
	if(!m_server.count(server))
		throw std::runtime_error("no server");
	return demo.m_config.battle(m_server[server]);
}
bool ConfigManager::IsServerMergeTogather(unsigned s1, unsigned s2)
{
	if(!m_server.count(s1) || !m_server.count(s2))
	{
		s1 =  MainConfig::GetMergedDomain(s1);
		s2 =  MainConfig::GetMergedDomain(s2);
		if(s1 && s2 && s1 == s2)
			return true;
		return false;
	}
	if( m_server[s1] == m_server[s2])
		return true;
	return false;
}
unsigned ConfigManager::GetMainServer(unsigned server)
{
	if(!m_server.count(server))
	{
		server =  MainConfig::GetMergedDomain(server);
		if(server)
			return server;
		throw std::runtime_error("no server");
	}
	return demo.m_config.battle(m_server[server]).begin();
}
bool ConfigManager::IsNeedConnect(unsigned server)
{
	return !IsServerMergeTogather(server, Config::GetIntValue(CONFIG_SRVID));
}
bool ConfigManager::IsNeedConnectByUID(unsigned uid)
{
	return IsNeedConnect(Config::GetZoneByUID(uid));
}
bool ConfigManager::IsNeedConnectByAID(unsigned aid)
{
	return IsNeedConnect(Config::GetZoneByAID(aid));
}
