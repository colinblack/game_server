#include "DataOperaBattleManager.h"

int DataOperaBattleManager::OnInit()
{
	for(unsigned i=0; i < MAX_INDEX; ++i)
	{
		if(!m_data->Empty(i))
		{
			uint32_t uid = m_data->data[i].uid;
			unsigned gateid = m_data->data[i].gateid;
			unsigned difficulty = m_data->data[i].difficulty;

			m_map[uid][gateid][difficulty] = i;
		}
	}

	return 0;
}

void DataOperaBattleManager::OnExit()
{

}

void DataOperaBattleManager::OnTimer1()
{

}

void DataOperaBattleManager::OnTimer2()
{

}


int DataOperaBattleManager::CheckBuff(unsigned uid)
{
	if(!m_map.count(uid))
		return R_ERR_NO_DATA;

	return 0;
}

int DataOperaBattleManager::AddBuff(DataOperaBattle & operabattle)
{
	unsigned index = GetFreeIndex();

	uint32_t uid = operabattle.uid;
	unsigned gateid = operabattle.gateid;
	unsigned difficulty = operabattle.difficulty;

	if(index == -1)
	{
		error_log("[AddBuff] get free index error. uid=%u", uid);
		return R_ERR_DATA;
	}

	if(Add(index, operabattle))
	{
		m_map[uid][gateid][difficulty] = index;
	}
	else
	{
		error_log("[AddBuff] Add to dbc failed. uid=%u", uid);
		return R_ERR_DATA;
	}

	return 0;
}

int DataOperaBattleManager::LoadBuff(unsigned uid)
{
	//为防止重复加载
	if (m_map.count(uid) > 0)
	{
		return 0;
	}

	vector<DataOperaBattle> vctbattle(1);
	vctbattle[0].uid = uid;

	int ret = Load(vctbattle);

	if (ret)
	{
		return ret;
	}

	if (0 == vctbattle.size())
	{
		return R_ERR_NO_DATA;
	}

	//单个逐个加载
	for(int i = 0; i < vctbattle.size(); ++i)
	{
		unsigned index = GetFreeIndex();

		if(index == -1)
		{
			error_log("[LoadBuff] get free index error. uid=%u", uid);
			return R_ERR_DATA;
		}

		m_data->data[index] = vctbattle[i];  //给m_data内的数据赋值
		unsigned gateid = vctbattle[i].gateid;
		unsigned difficulty = vctbattle[i].difficulty;

		if(m_data->MardLoad(index))
		{
			m_freeIndex.erase(index);
		}
		else
		{
			error_log("[LoadBuff] mark load failed. uid=%u,gateid=%d,diff=%u.", uid, gateid, difficulty);
			return R_ERROR;
		}

		m_map[uid][gateid][difficulty] = index;
	}

	return 0;
}

void DataOperaBattleManager::DoClear(unsigned uid)
{
	if(m_map.count(uid))
	{
		map<uint32_t, map<uint32_t, uint32_t> >::iterator miter;

		for(miter = m_map[uid].begin(); miter != m_map[uid].end(); )
		{
			//清理第二层
			unsigned gateid = miter->first;
			map<uint32_t, uint32_t>::iterator uiter;

			//清理第三层
			for(uiter = m_map[uid][gateid].begin(); uiter != m_map[uid][gateid].end(); )
			{
				 Clear(uiter->second);
				 m_map[uid][gateid].erase(uiter++);
			}

			m_map[uid].erase(miter++);
		}

		m_map.erase(uid);
	}
}

void DataOperaBattleManager::DoSave(unsigned uid)
{
	if(m_map.count(uid))
	{
		map<uint32_t, map<uint32_t, uint32_t> >::iterator miter;

		for(miter = m_map[uid].begin(); miter != m_map[uid].end(); ++miter)
		{
			unsigned gateid = miter->first;
			map<uint32_t, uint32_t>::iterator uiter;

			for(uiter = m_map[uid][gateid].begin(); uiter != m_map[uid][gateid].end(); ++uiter)
			{
				AddSave(uiter->second);
			}
		}
	}
}

DataOperaBattle& DataOperaBattleManager::GetDiffBattle(unsigned uid, unsigned gateid, unsigned diff)
{
	if (!m_map.count(uid) || !m_map[uid].count(gateid) || !m_map[uid][gateid].count(diff))
	{
		error_log("[GetFriend] gateid and difficulty is not exists. uid=%u,gateid=%u,difficulty=%u", uid, gateid, diff);
		throw std::runtime_error("get_difficulty_battle_error");
	}

	unsigned index = m_map[uid][gateid][diff];

	return m_data->data[index];
}

DataOperaBattle& DataOperaBattleManager::GetDiffBattle(unsigned index)
{
	if (index >= MAX_INDEX)
	{
		error_log("[GetFriend] index is error. index=%u", index);
		throw std::runtime_error("get_difficulty_battle_error");
	}

	return  m_data->data[index];
}

bool DataOperaBattleManager::IsDiffBattleExist(unsigned uid, unsigned gateid, unsigned diff)
{
	if (!m_map.count(uid) || !m_map[uid].count(gateid) || !m_map[uid][gateid].count(diff))
	{
		return false;
	}

	return true;
}

int DataOperaBattleManager::GetBattles(unsigned uid, vector<unsigned> & indexs)
{
	if(m_map.count(uid))
	{
		map<uint32_t, map<uint32_t, uint32_t> >::iterator miter;

		for(miter = m_map[uid].begin(); miter != m_map[uid].end(); ++miter)
		{
			unsigned gateid = miter->first;
			map<uint32_t, uint32_t>::iterator uiter;

			for(uiter = m_map[uid][gateid].begin(); uiter != m_map[uid][gateid].end(); ++uiter)
			{
				indexs.push_back(uiter->second);
			}
		}
	}

	return 0;
}

bool DataOperaBattleManager::UpdateDiffBattle(DataOperaBattle& operabattle)
{
	unsigned uid = operabattle.uid;
	unsigned gateid = operabattle.gateid;
	unsigned difficulty = operabattle.difficulty;

	if (!m_map.count(uid) || !m_map[uid].count(gateid) || !m_map[uid][gateid].count(difficulty))
	{
		return false;
	}

	unsigned index = m_map[uid][gateid][difficulty];

	return  m_data->MarkChange(index);
}
