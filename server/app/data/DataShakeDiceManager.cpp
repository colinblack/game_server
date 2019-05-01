#include "DataShakeDiceManager.h"

int DataShakeDiceManager::OnInit()
{
	for(unsigned i = 0; i < MAX_INDEX; ++i)
	{
		if(!m_data->Empty(i))
			m_map[m_data->data[i].uid] = i;
	}

	return 0;
}

void DataShakeDiceManager::OnExit()
{

}

void DataShakeDiceManager::OnTimer1()
{

}

void DataShakeDiceManager::OnTimer2()
{

}

int DataShakeDiceManager::CheckBuff(unsigned uid)
{
	if (!m_map.count(uid))
	{
		return R_ERR_NO_DATA;
	}

	return 0;
}

int DataShakeDiceManager::New(unsigned uid)
{
	if (m_map.count(uid) > 0)
	{
		return R_SUCCESS;
	}

	if (IsFull()) return R_ERR_DATA;

	DataShakeDice shakedice;
	shakedice.uid = uid;
	shakedice.curmap = 1;  //当前地图1
	shakedice.map1_status = 1; //地图1正在进行中
	shakedice.curpos = 1;  //当前位置是1

	return AddBuff(shakedice);
}


int DataShakeDiceManager::AddBuff(DataShakeDice& shakedice)
{
	unsigned index = GetFreeIndex();

	if(index == -1)
		return R_ERR_DATA;

	if(Add(index, shakedice))
	{
		m_map[shakedice.uid] = index;
		return 0;
	}
	else
		return R_ERR_DATA;
}

int DataShakeDiceManager::LoadBuff(unsigned uid)
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

unsigned DataShakeDiceManager::GetIndex(unsigned uid)
{
	if(m_map.count(uid))
		return m_map[uid];

	return -1;
}

void DataShakeDiceManager::DoClear(unsigned uid)
{
	if(m_map.count(uid))
	{
		Clear(m_map[uid]);
		m_map.erase(uid);
	}
}

void DataShakeDiceManager::DoSave(unsigned uid)
{
	if(m_map.count(uid))
		AddSave(m_map[uid]);
}

DataShakeDice& DataShakeDiceManager::GetShakeDice(unsigned uid)
{
	int index = GetIndex(uid);

	if (index < 0)
	{
		error_log("uid: %u, index=%u", uid, index);
		throw std::runtime_error("get_shakedice_error");
	}

	return  m_data->data[index];
}

bool DataShakeDiceManager::UpdateDataShakeDice(DataShakeDice& shakedice)
{
	unsigned index = GetIndex(shakedice.uid);

	if (-1 == index)
	{
		return false;
	}

	return m_data->MarkChange(index);
}

