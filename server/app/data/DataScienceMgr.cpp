/*
 * DataScienceMgr.cpp
 *
 *  Created on: 2016-9-14
 *      Author: dawx62fac
 */


#include "DataScienceMgr.h"

int DataScienceMgr::OnInit()
{
	for(unsigned i=0; i < DB_BASE_BUFF*DB_SCIENCE_FACOTR; ++i)
	{
		if(!m_data->Empty(i))
		{
			const DBCScience& item = m_data->data[i];
			m_map[item.uid].insert(std::pair<uint16_t, unsigned>(item.id, i));
		}
	}
	return 0;
}


int DataScienceMgr::FreeIndex()
{
	int index = GetFreeIndex();
	if (index < 0)
	{
		error_log("index: %d", index);
		throw std::runtime_error("Get_free_index_error");
	}

	return index;
}

void DataScienceMgr::Online(unsigned uid)
{
	Load(uid);
}

void DataScienceMgr::Offline(unsigned uid)
{
	if (m_new_map.count(uid) > 0)
	{
		m_new_map.erase(uid);
	}
}

int DataScienceMgr::Load(unsigned uid)
{
	if (m_map.count(uid) > 0) return R_SUCCESS;

	if (m_new_map.count(uid) > 0) return R_SUCCESS;


	if (IsFull()) return R_ERR_DATA;

	std::vector<DBCScience> vSciences;
	DBCScience t_data(uid, 0);
	vSciences.push_back(t_data);

	int ret = base::Load(vSciences);
	if (ret == R_SUCCESS)
	{
		for (unsigned i = 0; i < vSciences.size(); ++i)
		{
			int index = FreeIndex();
			if(!m_data->Empty(index))
			{
				return R_ERR_DATA;
			}

			m_data->data[index] = vSciences[i];
			if(m_data->MardLoad(index))
			{
				m_freeIndex.erase(index);
				m_map[uid].insert(std::pair<uint16_t, unsigned>(vSciences[i].id, index));
			}
			else
			{
				return R_ERR_DATA;
			}
		}
	}
	else if (R_ERR_NO_DATA == ret)
	{
		m_new_map[uid] = true;
		return R_SUCCESS;
	}

	return ret;
}

void DataScienceMgr::NewItem(unsigned uid, unsigned id)
{
	DBCScience data(uid, id);
	int index = FreeIndex();
	if(Add(index, data))
	{
		m_map[uid].insert(std::make_pair<uint16_t, unsigned>(id, index));

		if (m_new_map.count(uid) > 0)
		{
			m_new_map.erase(uid);
		}
	}
	else
	{
		error_log("add_error.uid=%u,id: %u", uid, id);
		throw std::runtime_error("add_science_item_error");
	}
}

int DataScienceMgr::GetIndex(unsigned uid, unsigned id)
{
	if (id < 1 || id > 200)
	{
		error_log("uid: %u, id:%u", uid, id);
		throw std::runtime_error("science_id_params_error");
	}

	if (m_map.count(uid) <= 0 && Load(uid) != R_SUCCESS)
	{
		error_log("load_science_data_error.uid=%u,id=%d", uid, id);
		throw std::runtime_error("load_science_data_error");
	}

	if (m_map.count(uid) <= 0 || m_map[uid].count(id) <= 0)
	{
		NewItem(uid, id);
	}

	return m_map[uid][id];
}

void DataScienceMgr::GetIndexs(unsigned uid, const std::vector<uint16_t>& vIds, std::vector<unsigned>& result)
{
	result.clear();

	if (m_map.count(uid) <= 0 && Load(uid) != R_SUCCESS)
	{
		error_log("load_science_data_error.uid=%u", uid);
		throw std::runtime_error("load_science_data_error");
	}

	for (size_t i = 0; i < vIds.size(); ++i)
	{
		if (m_map[uid].count(vIds[i]) > 0)
		{
			result.push_back(m_map[uid][vIds[i]]);
		}
	}
}

void DataScienceMgr::GetSciences(unsigned uid, std::vector<unsigned>& result)
{
	result.clear();

	if (m_map.count(uid) <= 0 && Load(uid) != R_SUCCESS)
	{
		error_log("load_science_data_error.uid=%u", uid);
		throw std::runtime_error("load_science_data_error");
	}

	const std::map<uint16_t, unsigned>& items = m_map[uid];

	std::map<uint16_t, unsigned>::const_iterator it = items.begin();
	for (; it != items.end(); ++it)
	{
		result.push_back(it->second);
	}
}

void DataScienceMgr::GetSciences(unsigned uid, std::vector<DBCScience>& result)
{
	result.clear();

	if (m_map.count(uid) <= 0 && Load(uid) != R_SUCCESS)
	{
		error_log("load_science_data_error.uid=%u", uid);
		throw std::runtime_error("load_science_data_error");
	}

	const std::map<uint16_t, unsigned>& items = m_map[uid];


	std::map<uint16_t, unsigned>::const_iterator it = items.begin();
	for (; it != items.end(); ++it)
	{
		const DBCScience& dbcItem = m_data->data[it->second];
		result.push_back(dbcItem);
	}
}

void DataScienceMgr::DoClear(unsigned uid)
{
	std::map<unsigned, std::map<uint16_t, unsigned> >::iterator it = m_map.find(uid);
	if (it != m_map.end())
	{
		std::map<uint16_t, unsigned>::iterator  itor = it->second.begin();
		for (; itor != it->second.end(); ++itor)
		{
			base::Clear(itor->second);
		}

		m_map.erase(uid);

		if (m_new_map.count(uid) > 0)
		{
			m_new_map.erase(uid);
		}
	}
}

void DataScienceMgr::DoSave(unsigned uid)
{
	std::map<unsigned, std::map<uint16_t, unsigned> >::iterator it = m_map.find(uid);
	if (it != m_map.end())
	{
		std::map<uint16_t, unsigned>::iterator  itor = it->second.begin();
		for (; itor != it->second.end(); ++itor)
		{
			base::AddSave(itor->second);
		}
	}
}


