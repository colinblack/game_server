#include "MemoryOperaBattleManager.h"

int MemoryOperaBattleManager::OnInit()
{
	for(unsigned i = 0; i < MAX_BATTLE_NUM;++i)
	{
		if(m_data->data[i].gateid != 0)
			m_map[m_data->data[i].gateid] = i;
		else
			m_freeIndex.insert(i);
	}

	return 0;
}

MemoryBattleInfo& MemoryOperaBattleManager::GetBattleInfo(unsigned gateid)
{
	if (!m_map.count(gateid))
	{
		throw std::runtime_error("gateid_params_error");
	}

	unsigned index = m_map[gateid];

	return m_data->data[index];
}

MemoryRecord & MemoryOperaBattleManager::GetRecord(unsigned gateid, unsigned diff)
{
	if (!m_map.count(gateid))
	{
		throw std::runtime_error("gateid_params_error");
	}

	unsigned index = m_map[gateid];

	return m_data->data[index].battle_record[diff - 1];
}
