#include "DataSellComponentManager.h"

int DataSellComponentManager::OnInit()
{
	for(unsigned i = 0; i < MAX_INDEX; ++i)
	{
		if(!m_data->Empty(i))
			m_map[m_data->data[i].uid] = i;
	}

	return 0;
}

void DataSellComponentManager::OnExit()
{

}

void DataSellComponentManager::OnTimer1()
{

}

void DataSellComponentManager::OnTimer2()
{

}

int DataSellComponentManager::CheckBuff(unsigned uid)
{
	if (!m_map.count(uid))
	{
		return R_ERR_NO_DATA;
	}

	return 0;
}

DataSellComponent& DataSellComponentManager::GetSellComponent(unsigned uid)
{
	int ret = 0;

	if (!m_map.count(uid))
	{
		//可能是没有load进来，进行重新load一遍
		LoadBuff(uid);
	}

	if (!m_map.count(uid))
	{
		//没有该数据，则新增
		ret = New(uid);

		if (ret)
		{
			throw runtime_error("add_sellcomponent_error");
		}
	}

	unsigned index = m_map[uid];

	return m_data->data[index];
}

bool DataSellComponentManager::UpdateSellComponent(DataSellComponent& sellcomponent)
{
	unsigned index = GetIndex(sellcomponent.uid);

	if (-1 == index)
	{
		return false;
	}

	return m_data->MarkChange(index);
}

int DataSellComponentManager::New(unsigned uid)
{
	if (m_map.count(uid) > 0)
	{
		return R_SUCCESS;
	}

	if (IsFull()) return R_ERR_DATA;

	DataSellComponent sellcomponent;
	sellcomponent.uid = uid;

	return AddBuff(sellcomponent);
}

int DataSellComponentManager::AddBuff(DataSellComponent & sellcomponent)
{
	unsigned index = GetFreeIndex();

	if(index == -1)
		return R_ERR_DATA;

	if(Add(index, sellcomponent))
	{
		m_map[sellcomponent.uid] = index;
		return 0;
	}
	else
		return R_ERR_DATA;
}

int DataSellComponentManager::LoadBuff(unsigned uid)
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

unsigned DataSellComponentManager::GetIndex(unsigned uid)
{
	if(m_map.count(uid))
		return m_map[uid];

	return -1;
}

void DataSellComponentManager::DoClear(unsigned uid)
{
	if(m_map.count(uid))
	{
		Clear(m_map[uid]);
		m_map.erase(uid);
	}
}

void DataSellComponentManager::DoSave(unsigned uid)
{
	if(m_map.count(uid))
		AddSave(m_map[uid]);
}
