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
unsigned ConfigManager::GetRandomOpen()
{
	if(demo.m_config.open_size())
		return demo.m_config.open(Math::GetRandomInt(demo.m_config.open_size()));
	return Math::GetRandomInt(demo.m_config.battle(demo.m_config.battle_size()-1).end()) + 1;
}
void ConfigManager::GetAllServer(set<unsigned>& allServer)
{
	for(int i = 0; i < demo.m_config.battle_size(); ++i)
	{
		allServer.insert(demo.m_config.battle(i).begin());
	}
}
