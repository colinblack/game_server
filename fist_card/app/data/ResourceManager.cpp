/*
 * ResourceManager.cpp
 *
 *  Created on: 2016-9-2
 *      Author: Ralf
 */

#include "ResourceManager.h"
#include "LogicHeroManager.h"

int ResourceManager::OnInit() {
	for(unsigned i=0;i<MEMORY_PROPERTY_NUM;++i)
	{
		if(m_data->item[i].uid != 0)
		{
			m_map[m_data->item[i].uid] = i;
		}

		else
			m_freeIndex.insert(i);

	}
	return 0;
}

int ResourceManager::Add(unsigned uid, unsigned heroId)
{
	try
	{
		unsigned i = GetFreeIndex();
		if(i == (unsigned)-1)
			return R_ERR_DATA;
		m_freeIndex.erase(i);
		m_map[uid] = i;
		m_data->item[i].uid = uid;

		memset(m_data->item[i].heros, 0 , sizeof(m_data->item[i].heros));
		HeroInfo& hero =  m_data->item[i].heros[0];
		hero.id = heroId;
		LogicHeroManager::Instance()->GetHeroAttr(uid, heroId, hero.attr);
		LogicHeroManager::Instance()->GetSkill(uid, heroId, hero);
		m_data->item[i].ts = Time::GetGlobalTime();
	}
	catch(const std::exception& e)
	{
		(void)e;
	}

	return 0;
}
