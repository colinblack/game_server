/*
 * DataGemMgr.cpp
 *
 *  Created on: 2016-9-26
 *      Author: dawx62fac
 */

#include "DataGemMgr.h"




int DataGemMgr::OnInit()
{
	for(unsigned i=0; i < DB_BASE_BUFF*DB_GEM_FACTOR; ++i)
	{
		if(!m_data->Empty(i))
		{
			const DBCGem& item = m_data->data[i];
			m_map[item.uid].insert(std::pair<uint8_t, unsigned>(item.level, i));
		}
	}
	return 0;
}

int DataGemMgr::FreeIndex()
{
	int index = GetFreeIndex();
	if (index < 0)
	{
		error_log("index: %d", index);
		throw std::runtime_error("Get_free_index_error");
	}

	return index;
}

void DataGemMgr::DoClear(unsigned uid)
{
	std::map<unsigned, std::map<uint8_t, unsigned> >::iterator it = m_map.find(uid);
	if (it != m_map.end())
	{
		std::map<uint8_t, unsigned>::iterator  itor = it->second.begin();
		for (; itor != it->second.end(); ++itor)
		{
			base::Clear(itor->second);
		}

		m_map.erase(uid);

		if (m_load_map.count(uid) > 0)
		{
			m_load_map.erase(uid);
		}
	}
}

void DataGemMgr::DoSave(unsigned uid)
{
	std::map<unsigned, std::map<uint8_t, unsigned> >::iterator it = m_map.find(uid);
	if (it != m_map.end())
	{
		std::map<uint8_t, unsigned>::iterator  itor = it->second.begin();
		for (; itor != it->second.end(); ++itor)
		{
			base::AddSave(itor->second);
		}
	}
}

void DataGemMgr::Online(unsigned uid)
{
	Load(uid);
}

void DataGemMgr::Offline(unsigned uid)
{
	if (m_load_map.count(uid) > 0)
	{
		m_load_map.erase(uid);
	}
}

void DataGemMgr::NewItem(unsigned int uid, uint8_t level)
{
	DBCGem data(uid, level);
	int index = FreeIndex();
	if(Add(index, data))
	{
		m_map[uid].insert(std::make_pair<uint8_t, unsigned>(level, index));

		if (m_load_map.count(uid) > 0)
		{
			m_load_map.erase(uid);
		}
	}
	else
	{
		error_log("add_error.uid=%u,level: %u", uid, level);
		throw std::runtime_error("add_gem_item_error");
	}
}

int DataGemMgr::Load(unsigned uid)
{
	if (m_map.count(uid) > 0) return R_SUCCESS;
	if (m_load_map.count(uid) > 0) return R_SUCCESS;
	if (IsFull())
	{
		error_log("uid:%u, load_data_error", uid);
		return R_ERR_DATA;
	}

	std::vector<DBCGem> vGem;
	DBCGem t_data(uid, 0);
	vGem.push_back(t_data);

	int ret = base::Load(vGem);
	if (ret == R_SUCCESS)
	{
		for (unsigned i = 0; i < vGem.size(); ++i)
		{
			int index = FreeIndex();
			if(!m_data->Empty(index))
			{
				error_log("uid:%u, load_data_error", uid);
				return R_ERR_DATA;
			}

			m_data->data[index] = vGem[i];
			if(m_data->MardLoad(index))
			{
				m_freeIndex.erase(index);
				m_map[uid].insert(std::pair<uint8_t, unsigned>(vGem[i].level, index));
			}
			else
			{
				error_log("uid:%u, load_data_error", uid);
				return R_ERR_DATA;
			}
		}
	}
	else if (R_ERR_NO_DATA == ret)
	{
		m_load_map[uid] = true;
		return R_SUCCESS;
	}

	return ret;
}


