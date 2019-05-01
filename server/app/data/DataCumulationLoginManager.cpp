#include "DataCumulationLoginManager.h"

int DataCumulationLoginManager::OnInit()
{
	for(unsigned i = 0; i < DB_BASE_BUFF*DB_CUMULATIONLOGIN_FULL; ++i)
	{
		if(!m_data->Empty(i))
			m_map[m_data->data[i].uid] = i;
	}

	return 0;
}

void DataCumulationLoginManager::OnExit()
{

}

void DataCumulationLoginManager::OnTimer1()
{

}

void DataCumulationLoginManager::OnTimer2()
{

}

int DataCumulationLoginManager::LoadBuff(unsigned uid)
{
	//为防止重复加载
	if (m_map.count(uid) > 0)
	{
		return R_SUCCESS;
	}

	if (IsFull()) return R_ERR_DATA;

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

	return ret;
}

int DataCumulationLoginManager::New(unsigned uid)
{
	if (m_map.count(uid) > 0)
	{
		return R_SUCCESS;
	}

	if (IsFull()) return R_ERR_DATA;

	DataCumulationLogin datacumulation;
	datacumulation.uid = uid;

	return AddBuff(datacumulation);
}


int DataCumulationLoginManager::CheckBuff(unsigned uid)
{
	if (!m_map.count(uid))
	{
		return R_ERR_NO_DATA;
	}

	return 0;
}

int DataCumulationLoginManager::AddBuff(DataCumulationLogin& datacumulation)
{
	unsigned index = GetFreeIndex();

	if(index == -1)
		return R_ERR_DATA;

	if(Add(index, datacumulation))
	{
		m_map[datacumulation.uid] = index;
		return 0;
	}
	else
		return R_ERR_DATA;
}

unsigned DataCumulationLoginManager::GetIndex(unsigned uid)
{
	if(m_map.count(uid))
		return m_map[uid];

	return -1;
}

void DataCumulationLoginManager::DoClear(unsigned uid)
{
	if(m_map.count(uid))
	{
		Clear(m_map[uid]);
		m_map.erase(uid);
	}
}

void DataCumulationLoginManager::DoSave(unsigned uid)
{
	if(m_map.count(uid))
		AddSave(m_map[uid]);
}

DataCumulationLogin& DataCumulationLoginManager::Get(unsigned uid)
{
	int index = GetIndex(uid);

	if (index < 0)
	{
		error_log("uid: %u, index=%u", uid, index);
		throw std::runtime_error("get_cumulationlogin_info_error");
	}

	return  m_data->data[index];
}

bool DataCumulationLoginManager::UpdateDataCumulation(unsigned index)
{
	return m_data->MarkChange(index);
}

bool DataCumulationLoginManager::UpdateDataCumulation(DataCumulationLogin& datacumulation)
{
	unsigned index = GetIndex(datacumulation.uid);

	if (-1 == index)
	{
		return false;
	}

	return UpdateDataCumulation(index);
}
