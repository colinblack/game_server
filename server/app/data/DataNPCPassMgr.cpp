/*
 * DataNPCPassMgr.cpp
 *
 *  Created on: 2016-9-8
 *      Author: dawx62fac
 */



#include "DataNPCPassMgr.h"

int DataNPCPassMgr::OnInit()
{
	for(unsigned i = 0; i < DB_BASE_BUFF*DB_NPC_PASS_FACTOR; ++i)
	{
		if(! m_data->Empty(i))
		{
			m_mapTb.insert(std::make_pair(m_data->data[i].uid, i));
		}
	}
	return 0;
}

int DataNPCPassMgr::FreeIndex()
{
	int index = GetFreeIndex();
	if (index < 0)
	{
		error_log("index: %d", index);
		throw std::runtime_error("Get_free_index_error");
	}

	return index;
}


int DataNPCPassMgr::LoadBuffer(unsigned uid)
{
	if (m_mapTb.count(uid) > 0)  return R_SUCCESS;

	if (IsFull()) return R_ERR_DATA;

	std::vector<DataNPCPass> vPass;
	DataNPCPass t_data;
	t_data.uid = uid;
	vPass.push_back(t_data);

	int ret = base::Load(vPass);
	if (ret == R_SUCCESS)
	{
		for (unsigned i = 0; i < vPass.size(); ++i)
		{
			int index = FreeIndex();
			if(!m_data->Empty(index))
			{
				return R_ERR_DATA;
			}

			m_data->data[index] = vPass[i];
			if(m_data->MardLoad(index))
			{
				m_mapTb.insert(std::make_pair(uid, index));
				m_freeIndex.erase(index);
			}
			else
			{
				return R_ERR_DATA;
			}
		}
	}
	else if (R_ERR_NO_DATA == ret)
	{
		return R_SUCCESS;
	}

	return ret;
}

void DataNPCPassMgr::GetIndexs(unsigned uid, std::vector<unsigned>& vIndexs)
{
	vIndexs.clear();

	typedef std::multimap<unsigned, unsigned>::iterator mumap_it;
	std::pair<mumap_it, mumap_it> mapbuidls = m_mapTb.equal_range(uid);
	for (mumap_it k = mapbuidls.first; k != mapbuidls.second; ++k)
	{
		vIndexs.push_back(k->second);
	}
}

int DataNPCPassMgr::GetIndex(unsigned uid, unsigned id)
{
	typedef std::multimap<unsigned, unsigned>::iterator mumap_it;
	std::pair<mumap_it, mumap_it> mapbuidls = m_mapTb.equal_range(uid);
	for (mumap_it k = mapbuidls.first; k != mapbuidls.second; ++k)
	{
		if (m_data->data[k->second].id == id)
		{
			return k->second;
		}
	}

	return -1;
}

void DataNPCPassMgr::PassSuccess(unsigned uid, unsigned id)
{
	int index = GetIndex(uid, id);
	if (index >= 0)
	{
		//
		m_data->data[index].pass_cnt += 1;
		m_data->MarkChange(index);
	}
	else
	{
		DataNPCPass data(uid, id);
		data.pass_cnt = 1;

		int nFreeIndex = FreeIndex();
		if (base::Add(nFreeIndex, data))
		{
			m_mapTb.insert(std::make_pair(uid, nFreeIndex));
		}
	}
}


void DataNPCPassMgr::DoClear(unsigned uid)
{
	typedef std::multimap<unsigned, unsigned>::iterator mumap_it;
	mumap_it t_p = m_mapTb.find(uid);
	while(t_p != m_mapTb.end())
	{
		base::Clear(t_p->second);
		m_mapTb.erase(t_p);
		t_p = m_mapTb.find(uid);
	}

}
void DataNPCPassMgr::DoSave(unsigned uid)
{
	typedef std::multimap<unsigned, unsigned>::iterator mumap_it;
	std::pair<mumap_it, mumap_it> mapbuidls = m_mapTb.equal_range(uid);
	for (mumap_it k = mapbuidls.first; k != mapbuidls.second; ++k)
	{
		base::AddSave(k->second);
	}
}

