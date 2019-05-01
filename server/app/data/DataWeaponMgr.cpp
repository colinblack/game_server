/*
 * DataWeapon.cpp
 *
 *  Created on: 2016-9-21
 *      Author: dawx62fac
 */

#include "DataWeaponMgr.h"


int DataWeaponMgr::OnInit()
{
	for(unsigned i=0; i < DB_BASE_BUFF*DB_WEAPON_FACOTR; ++i)
	{
		if(!m_data->Empty(i))
		{
			const DBCWeapon& item = m_data->data[i];
			m_map[item.uid].insert(std::pair<uint8_t, unsigned>(item.id, i));
		}
	}
	return 0;
}

void DataWeaponMgr::DoClear(unsigned uid)
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

bool DataWeaponMgr::CheckUserData(unsigned uid)
{
	int ret = Load(uid);
	if (ret != R_SUCCESS)
	{
		throw std::runtime_error("load_weapon_data_error");
	}

	return true;
}

bool DataWeaponMgr::CheckUserData(unsigned uid, unsigned id)
{
	CheckUserData(uid);

	if (m_map[uid].count(id) == 0)
	{
		NewItem(uid, id);
	}

	return true;
}

void DataWeaponMgr::NewItem(unsigned uid, unsigned id)
{
	DBCWeapon data(uid, id);
	int index = FreeIndex();
	if(base::Add(index, data))
	{
		m_map[uid].insert(std::make_pair<uint8_t, unsigned>(id, index));

		if (m_load_map.count(uid) > 0)
		{
			m_load_map.erase(uid);
		}
	}
	else
	{
		error_log("add_error.uid=%u,id: %u", uid, id);
		throw std::runtime_error("add_science_item_error");
	}
}

int DataWeaponMgr::Load(unsigned uid)
{
	if (m_map.count(uid) > 0) return R_SUCCESS;
	if (m_load_map.count(uid) > 0) return R_SUCCESS;
	if (IsFull())
	{
		error_log("uid:%u, load_data_error", uid);
		return R_ERR_DATA;
	}

	std::vector<DBCWeapon> vWeapon;
	DBCWeapon t_data(uid, 0);
	vWeapon.push_back(t_data);

	int ret = base::Load(vWeapon);
	if (ret == R_SUCCESS)
	{
		for (unsigned i = 0; i < vWeapon.size(); ++i)
		{
			int index = FreeIndex();
			if(!m_data->Empty(index))
			{
				error_log("uid:%u, load_data_error", uid);
				return R_ERR_DATA;
			}

			m_data->data[index] = vWeapon[i];
			if(m_data->MardLoad(index))
			{
				m_freeIndex.erase(index);
				m_map[uid].insert(std::pair<uint8_t, unsigned>(vWeapon[i].id, index));
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

void DataWeaponMgr::DoSave(unsigned uid)
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


int DataWeaponMgr::FreeIndex()
{
	int index = GetFreeIndex();
	if (index < 0)
	{
		error_log("index: %d", index);
		throw std::runtime_error("Get_free_index_error");
	}

	return index;
}

void DataWeaponMgr::CheckParamsId(unsigned id)
{
	const unsigned ids[6] = {11,12,21,22,31,32};
	for(int i = 0; i < 6; ++i)
	{
		if (ids[i] == id) return ;
	}

	error_log("weapon id: %u", id);
	throw std::runtime_error("Weapon_id_params_error");
}



unsigned DataWeaponMgr::GetIndex(unsigned uid, unsigned id)
{
	CheckParamsId(id);

	CheckUserData(uid, id);

	return m_map[uid][id];
}

void DataWeaponMgr::GetIndexs(unsigned uid, std::vector<unsigned>& vIndexs)
{
	vIndexs.clear();

	CheckUserData(uid);

	const std::map<uint8_t, unsigned>& items = m_map[uid];
	std::map<uint8_t, unsigned>::const_iterator it = items.begin();
	for (; it != items.end(); ++it)
	{
		vIndexs.push_back(it->second);
	}
}

DBCWeapon & DataWeaponMgr::GetWeapon(unsigned index)
{
	return m_data->data[index];
}

void DataWeaponMgr::Online(unsigned uid)
{
	Load(uid);
}

void DataWeaponMgr::Offline(unsigned uid)
{
	if (m_load_map.count(uid) > 0)
	{
		m_load_map.erase(uid);
	}
}
