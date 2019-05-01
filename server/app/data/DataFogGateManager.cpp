#include "DataFogGateManager.h"

int DataFogGateManager::OnInit()
{
	for(unsigned i=0; i < MAX_INDEX; ++i)
	{
		if(!m_data->Empty(i))
		{
			uint32_t uid = m_data->data[i].uid;
			uint32_t gateid = m_data->data[i].gateid;

			m_map[uid][gateid] = i;
		}
	}

	return 0;
}

void DataFogGateManager::OnExit()
{

}

void DataFogGateManager::OnTimer1()
{

}

void DataFogGateManager::OnTimer2()
{

}


int DataFogGateManager::CheckBuff(unsigned uid)
{
	if(!m_map.count(uid))
		return R_ERR_NO_DATA;

	return 0;
}

int DataFogGateManager::AddBuff(DataFogGate & foggate)
{
	unsigned index = GetFreeIndex();

	uint32_t uid = foggate.uid;
	uint32_t gateid = foggate.gateid ;

	if(index == -1)
	{
		error_log("[AddBuff] get free index error. uid=%u", uid);
		return R_ERR_DATA;
	}

	if(Add(index, foggate))
	{
		m_map[uid][gateid] = index;
	}
	else
	{
		error_log("[AddBuff] Add to dbc failed. uid=%u", uid);
		return R_ERR_DATA;
	}

	return 0;
}

int DataFogGateManager::LoadBuff(unsigned uid)
{
	//为防止重复加载
	if (m_map.count(uid) > 0)
	{
		return 0;
	}

	vector<DataFogGate> vctfoggate(1);
	vctfoggate[0].uid = uid;

	int ret = Load(vctfoggate);

	if (ret)
	{
		return ret;
	}

	if (0 == vctfoggate.size())
	{
		return R_ERR_NO_DATA;
	}

	//单个逐个加载
	for(int i = 0; i < vctfoggate.size(); ++i)
	{
		unsigned index = GetFreeIndex();

		if(index == -1)
		{
			error_log("[LoadBuff] get free index error. uid=%u", uid);
			return R_ERR_DATA;
		}

		m_data->data[index] = vctfoggate[i];  //给m_data内的数据赋值
		unsigned gateid = vctfoggate[i].gateid;

		if(m_data->MardLoad(index))
		{
			m_freeIndex.erase(index);
		}
		else
		{
			error_log("[LoadBuff] mark load failed. uid=%u,gateid=%d.", uid, gateid);
			return R_ERROR;
		}

		m_map[uid][gateid] = index;
	}

	return 0;
}


void DataFogGateManager::DoClear(unsigned uid)
{
	if(m_map.count(uid))
	{
		 map<uint32_t, uint32_t>::iterator miter = m_map[uid].begin();

		 for(; miter != m_map[uid].end(); )
		 {
			 Clear(miter->second);
			 m_map[uid].erase(miter++);
		 }

		 m_map.erase(uid);
	}
}

void DataFogGateManager::DoSave(unsigned uid)
{
	if(m_map.count(uid))
	{
		 map<uint32_t, uint32_t>::iterator miter = m_map[uid].begin();

		 for(; miter != m_map[uid].end(); ++miter)
		 {
			 AddSave(miter->second);
		 }
	}
}

DataFogGate& DataFogGateManager::GetFogGate(unsigned uid, unsigned gateid)
{
	if (!m_map.count(uid) || !m_map[uid].count(gateid))
	{
		error_log("[GetFogGate] gateid is not exists. uid=%u,gateid=%u", uid, gateid);
		throw std::runtime_error("get_foggate_error");
	}

	unsigned index = m_map[uid][gateid];

	return m_data->data[index];
}

DataFogGate& DataFogGateManager::GetFogGate(unsigned index)
{
	if (index >= MAX_INDEX)
	{
		error_log("[GetFogGate] index is error. index=%u", index);
		throw std::runtime_error("get_foggate_error");
	}

	return  m_data->data[index];
}

int DataFogGateManager::GetFogGates(unsigned uid, vector<unsigned> & indexs)
{
	if(m_map.count(uid))
	{
		 map<uint32_t, uint32_t>::iterator miter = m_map[uid].begin();

		 for(; miter != m_map[uid].end(); ++miter)
		 {
			 indexs.push_back(miter->second);
		 }
	}

	return 0;
}

bool DataFogGateManager::IsFogGateExists(unsigned uid, unsigned gateid)
{
	if (!m_map.count(uid) || !m_map[uid].count(gateid))
	{
		return false;
	}

	return true;
}

bool DataFogGateManager::UpdateFogGate(DataFogGate& foggate)
{
	unsigned uid = foggate.uid;
	unsigned gateid = foggate.gateid;

	if (!m_map.count(uid) || !m_map[uid].count(gateid))
	{
		return false;
	}

	unsigned index = m_map[uid][gateid];

	return  m_data->MarkChange(index);
}

