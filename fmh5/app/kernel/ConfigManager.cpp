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

	for(int i=0;i<activity.m_config.act_size();++i)
		m_actmap[activity.m_config.act(i).id()] = i;
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
