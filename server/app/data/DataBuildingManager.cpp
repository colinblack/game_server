/*
 * DataBuildingManager.cpp
 *
 *  Created on: 2016-8-31
 *      Author: dawx62fac
 */

#include <stdexcept>


#include "DataBuildingManager.h"
#include "BaseManager.h"
#include "BuildingCfgWrap.h"


int DataBuildQueue::OnInit()
{
	for(unsigned i=0; i < DB_BASE_BUFF*DB_BASE_FULL; ++i)
	{
		if(!m_data->Empty(i))
		{
			m_map[m_data->data[i].uid] = i;
		}
	}
	return 0;
}

int DataBuildQueue::FreeIndex()
{
	int index = GetFreeIndex();
	if (index < 0)
	{
		error_log("index: %d", index);
		throw std::runtime_error("Get_free_index_error");
	}

	return index;
}

int DataBuildQueue::GetIndex(unsigned uid)
{
	std::map<unsigned, unsigned>::const_iterator it = m_map.find(uid);
	if (it == m_map.end())
	{
		return -1;
	}
	else
	{
		return it->second;
	}
}

unsigned DataBuildQueue::UserId2Index(unsigned uid)
{
	std::map<unsigned, unsigned>::const_iterator it = m_map.find(uid);
	if (it == m_map.end())
	{
		//throw std::runtime_error("buff_not_data");
		int ret = Load(uid);
		if (R_SUCCESS == ret)
		{
			std::map<unsigned, unsigned>::const_iterator new_it = m_map.find(uid);
			if (new_it != m_map.end())
			{
				return new_it->second;
			}
		}
	}
	else
	{
		return it->second;
	}

	error_log("db_or_data_error: uid: %u", uid);
	throw std::runtime_error("data_error");
}

//新建
int DataBuildQueue::New(unsigned uid)
{
	if (m_map.count(uid) > 0)
	{
		return R_SUCCESS;
	}

	if (IsFull()) return R_ERR_DATA;

	int index = FreeIndex();
	DBCBuidingQueueData data(uid);
	if(Add(index, data))
	{
		m_map[uid] = index;
	}
	else
	{
		return R_ERR_DATA;
	}

	return R_SUCCESS;
}

int DataBuildQueue::Load(unsigned uid)
{
	if (m_map.count(uid) > 0)
	{
		return R_SUCCESS;
	}

	if (IsFull()) return R_ERR_DATA;

	int index = FreeIndex();
	m_data->data[index].uid = uid;
	int ret = base::Load(index);
	if (R_ERR_NO_DATA == ret)
	{
		ret = New(uid);
		index = GetIndex(uid);
		if (index >= 0)
		{
			m_map[uid] = index;
		}

		return ret;
	}
	else
	{
		if (ret != 0) return ret;

		m_map[uid] = index;
	}


	return 0;

}

void DataBuildQueue::DoClear(unsigned uid)
{
	if(m_map.count(uid))
	{
		Clear(m_map[uid]);
		m_map.erase(uid);
	}
}
void DataBuildQueue::DoSave(unsigned uid)
{
	if(m_map.count(uid))
	{
		AddSave(m_map[uid]);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////
int DataBuildingManager::OnInit()
{
	for(unsigned i=0; i<DB_BASE_BUFF*DB_BUILDING_FACTOR; ++i)
	{
		if(!m_data->Empty(i))
		{
			int type = BuildId2Type(m_data->data[i].id);
			m_mapTb[type - 1].insert(std::make_pair(m_data->data[i].uid, i));
		}
	}
	return 0;
}

bool DataBuildingManager::IsInMap(unsigned uid)
{

	for (int type = FOLK_HOUSE_TYPE; type <=  BARRACKS_TYPE; ++type)
	{
		if (m_mapTb[type - 1].count(uid) > 0)
		{
			return true;
		}
	}

	if (m_new_user.count(uid) > 0)
	{
		return true;
	}

	return  false;
}

int DataBuildingManager::FreeIndex()
{
	int index = GetFreeIndex();
	if (index < 0)
	{
		error_log("index: %d", index);
		throw std::runtime_error("Get_free_index_error");
	}

	return index;
}

int DataBuildingManager::BuildId2Type(unsigned id) const
{
	int type = id / 100;
	if (type <= 0  || type >= BUID_TYPES)
	{
		error_log("build_id: %d", id);
		throw std::runtime_error("build_id_cfg_error");
	}

	return type;
}

//
int DataBuildingManager::IndexFromBuildId(unsigned uid, unsigned id)
{
	int type = BuildId2Type(id) - 1;

	typedef std::multimap<unsigned, unsigned>::iterator mumap_it;
	std::pair<mumap_it, mumap_it> mapbuidls = m_mapTb[type].equal_range(uid);
	for (mumap_it k = mapbuidls.first; k != mapbuidls.second; ++k)
	{
		if (m_data->data[k->second].id == id)
		{
			return k->second;
		}
	}

	return -1;
}

void DataBuildingManager::GetBuildIds(unsigned uid, unsigned type, std::vector<unsigned>& result)
{
	result.clear();

	std::vector<unsigned> vBuildIndexs;
	IndexsBuildsByType(uid, type, vBuildIndexs);
	for (size_t i = 0;i < vBuildIndexs.size(); ++i)
	{
		result.push_back(m_data->data[vBuildIndexs[i]].id);
	}
}


void DataBuildingManager::IndexsBuildsByType(unsigned uid, unsigned type, std::vector<unsigned>& result)
{
	result.clear();

	if (! IsInMap(uid))
	{
		Load(uid);
	}


	if (type == 0)
	{
		typedef std::multimap<unsigned, unsigned>::iterator mumap_it;
		for (int i = FOLK_HOUSE_TYPE; i <= BARRACKS_TYPE; ++i)
		{
			std::pair<mumap_it, mumap_it> mapbuidls = m_mapTb[i - 1].equal_range(uid);

			for (mumap_it k = mapbuidls.first; k != mapbuidls.second; ++k)
			{
				result.push_back(k->second);
			}
		}
	}
	else
	{
		if (type > 5)
		{
			throw std::runtime_error("sync_builds_data_type_error");
		}

		typedef std::multimap<unsigned, unsigned>::iterator mumap_it;
		std::pair<mumap_it, mumap_it> mapbuidls = m_mapTb[type - 1].equal_range(uid);

		for (mumap_it k = mapbuidls.first; k != mapbuidls.second; ++k)
		{
			result.push_back(k->second);
		}
	}
}

unsigned DataBuildingManager::GetIndex(unsigned uid, unsigned build_id)
{
	int index = IndexFromBuildId(uid, build_id);
	if (index < 0)
	{
		int ret = Load(uid);
		if (ret !=  R_SUCCESS)
		{
			error_log("data_error.uid=%u", uid);
			throw std::runtime_error("data_error");
		}

		index = IndexFromBuildId(uid, build_id);
		if (index < 0)
		{
			index = NewItem(uid, build_id);
		}
	}

	return index;
}


int DataBuildingManager::NewItem(unsigned uid, unsigned build_id)
{
	BuildCfgWrap buildCfgWrap;
	DBCBuildingData data(uid, buildCfgWrap.Item(build_id));
	//data.Unlock();
	int index = FreeIndex();
	if(Add(index, data))
	{
		int nType = BuildId2Type((unsigned)build_id) - 1;
		m_mapTb[nType].insert(std::make_pair(uid, index));

		if (m_new_user.count(uid) > 0)
		{
			m_new_user.erase(uid);
		}
	}
	else
	{
		error_log("add_error.uid=%u,buildid: %u", uid, build_id);
		throw std::runtime_error("add_item_error");
	}

	return index;
}

int DataBuildingManager::New(unsigned uid)
{
	if (IsInMap(uid)) return R_SUCCESS;

	if (IsFull()) return R_ERR_DATA;

	m_new_user[uid] = true;

	return R_SUCCESS;
}

int DataBuildingManager::Load(unsigned uid)
{
	if (IsInMap(uid)) return R_SUCCESS;

	if (IsFull()) return R_ERR_DATA;

	std::vector<DBCBuildingData> vBuilds;
	DBCBuildingData t_data;
	t_data.uid = uid;
	vBuilds.push_back(t_data);

	int ret = base::Load(vBuilds);
	if (ret == R_SUCCESS)
	{
		for (unsigned i = 0; i < vBuilds.size(); ++i)
		{
			int index = FreeIndex();
			if(!m_data->Empty(index))
			{
				return R_ERR_DATA;
			}

			m_data->data[index] = vBuilds[i];
			if(m_data->MardLoad(index))
			{
				m_freeIndex.erase(index);
				int nType = BuildId2Type(vBuilds[i].id) - 1;
				m_mapTb[nType].insert(std::make_pair(uid, index));
			}
			else
			{
				return R_ERR_DATA;
			}
		}
	}
	else if (R_ERR_NO_DATA == ret)
	{
		ret = New(uid);
	}

	return ret;
}

void DataBuildingManager::DoClear(unsigned uid)
{
	typedef std::multimap<unsigned, unsigned>::iterator mumap_it;
	for (int type = FOLK_HOUSE_TYPE; type <= BARRACKS_TYPE; ++type)
	{
		mumap_it t_p = m_mapTb[type - 1].find(uid);
		while(t_p != m_mapTb[type - 1].end())
		{
			Clear(t_p->second);
			m_mapTb[type - 1].erase(t_p);
			t_p = m_mapTb[type - 1].find(uid);
		}
	}

	if (m_new_user.count(uid) > 0)
	{
		m_new_user.erase(uid);
	}
}
void DataBuildingManager::DoSave(unsigned uid)
{
	typedef std::multimap<unsigned, unsigned>::iterator mumap_it;
	for (int type = FOLK_HOUSE_TYPE; type <= BARRACKS_TYPE; ++type)
	{

		std::pair<mumap_it, mumap_it> mapbuidls = m_mapTb[type - 1].equal_range(uid);
		for (mumap_it k = mapbuidls.first; k != mapbuidls.second; ++k)
		{
			AddSave(k->second);
		}
	}
}








