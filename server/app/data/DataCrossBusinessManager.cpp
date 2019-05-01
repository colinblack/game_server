#include "DataCrossBusinessManager.h"

int DataCrossBusinessManager::OnInit()
{
	for(unsigned i = 0; i < MAX_INDEX; ++i)
	{
		if(!m_data->Empty(i))
			m_map[m_data->data[i].uid] = i;
	}

	return 0;
}

void DataCrossBusinessManager::OnExit()
{

}

void DataCrossBusinessManager::OnTimer1()
{

}

void DataCrossBusinessManager::OnTimer2()
{

}

int DataCrossBusinessManager::CheckBuff(unsigned uid)
{
	if (!m_map.count(uid))
	{
		return R_ERR_NO_DATA;
	}

	return 0;
}

bool DataCrossBusinessManager::IsCrossBusinessExists(unsigned uid)
{
	if (!m_map.count(uid))
	{
		//可能是没有load进来，进行重新load一遍
		LoadBuff(uid);
	}

	if (!m_map.count(uid))
	{
		return false;
	}

	return true;
}

DataCrossBusiness& DataCrossBusinessManager::GetCrossBusiness(unsigned uid)
{
	int ret = 0;

	if (!m_map.count(uid))
	{
		throw runtime_error("get_crossbusiness_error");
	}

	unsigned index = m_map[uid];

	return m_data->data[index];
}

bool DataCrossBusinessManager::UpdateCrossBusiness(DataCrossBusiness& crossbusiness)
{
	unsigned index = GetIndex(crossbusiness.uid);

	if (-1 == index)
	{
		return false;
	}

	return m_data->MarkChange(index);
}

int DataCrossBusinessManager::New(unsigned uid)
{
	if (m_map.count(uid) > 0)
	{
		return R_SUCCESS;
	}

	if (IsFull()) return R_ERR_DATA;

	DataCrossBusiness crossbusiness;
	crossbusiness.uid = uid;

	return AddBuff(crossbusiness);
}

int DataCrossBusinessManager::AddBuff(DataCrossBusiness & crossbusiness)
{
	unsigned index = GetFreeIndex();

	if(index == -1)
		return R_ERR_DATA;

	if(Add(index, crossbusiness))
	{
		m_map[crossbusiness.uid] = index;
		return 0;
	}
	else
		return R_ERR_DATA;
}

int DataCrossBusinessManager::LoadBuff(unsigned uid)
{
	//判断是否已加载
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

unsigned DataCrossBusinessManager::GetIndex(unsigned uid)
{
	if(m_map.count(uid))
		return m_map[uid];

	return -1;
}

void DataCrossBusinessManager::DoClear(unsigned uid)
{
	if(m_map.count(uid))
	{
		Clear(m_map[uid]);
		m_map.erase(uid);
	}
}

void DataCrossBusinessManager::DoSave(unsigned uid)
{
	if(m_map.count(uid))
		AddSave(m_map[uid]);
}
