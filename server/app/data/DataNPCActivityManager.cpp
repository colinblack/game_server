#include "DataNPCActivityManager.h"

int DataNPCActivityManager::OnInit()
{
	for(unsigned i=0;i<DB_BASE_BUFF*DB_BASE_FULL;++i)
	{
		if(!m_data->Empty(i))
			m_map[m_data->data[i].uid] = i;
	}

	return 0;
}

void DataNPCActivityManager::OnExit()
{

}

void DataNPCActivityManager::OnTimer1()
{

}

void DataNPCActivityManager::OnTimer2()
{

}

int DataNPCActivityManager::AddBuff(DataNPCActivity & datanpcactivity)
{
	unsigned index = GetFreeIndex();

	if(index == -1)
		return R_ERR_DATA;

	if(Add(index, datanpcactivity))
	{
		m_map[datanpcactivity.uid] = index;
		return 0;
	}
	else
		return R_ERR_DATA;
}

int DataNPCActivityManager::LoadBuff(unsigned uid)
{
	if (m_map.count(uid) > 0)
	{
		return 0;
	}

	unsigned index = GetFreeIndex();

	if(index == -1)
		return R_ERR_DATA;

	m_data->data[index].uid = uid;
	int ret = Load(index);

	if(ret == 0)
	{
		m_map[uid] = index;
		return 0;
	}
	else
	{
		return ret;
	}
}

void DataNPCActivityManager::DoClear(unsigned uid)
{
	if(m_map.count(uid))
	{
		Clear(m_map[uid]);
		m_map.erase(uid);
	}
}

void DataNPCActivityManager::DoSave(unsigned uid)
{
	if(m_map.count(uid))
		AddSave(m_map[uid]);
}

DataNPCActivity& DataNPCActivityManager::Get(unsigned uid)
{
	int index = GetIndex(uid);

	if (index < 0)
	{
		error_log("uid: %u, index=%u", uid, index);
		throw std::runtime_error("get_npcactivity_info_error");
	}

	return  m_data->data[index];
}

unsigned DataNPCActivityManager::GetIndex(unsigned uid)
{
	if(m_map.count(uid))
		return m_map[uid];

	return -1;
}

bool DataNPCActivityManager::IsNPCActivityExists(unsigned uid)
{
	if (m_map.count(uid))
	{
		return true;
	}

	return false;
}

bool DataNPCActivityManager::UpdateDataNPCActivity(unsigned index)
{
	return m_data->MarkChange(index);
}

bool DataNPCActivityManager::UpdateDataNPCActivity(DataNPCActivity & datanpcactivity)
{
	unsigned index = GetIndex(datanpcactivity.uid);

	if (-1 == index)
	{
		return false;
	}

	return UpdateDataNPCActivity(index);
}
