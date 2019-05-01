#include "DataProduceComponentManager.h"

int DataProduceComponentManager::OnInit()
{
	for(unsigned i = 0; i < MAX_INDEX; ++i)
	{
		if(!m_data->Empty(i))
			m_map[m_data->data[i].uid] = i;
	}

	return 0;
}

void DataProduceComponentManager::OnExit()
{

}

void DataProduceComponentManager::OnTimer1()
{

}

void DataProduceComponentManager::OnTimer2()
{

}

int DataProduceComponentManager::CheckBuff(unsigned uid)
{
	if (!m_map.count(uid))
	{
		return R_ERR_NO_DATA;
	}

	return 0;
}

int DataProduceComponentManager::New(unsigned uid)
{
	if (m_map.count(uid) > 0)
	{
		return R_SUCCESS;
	}

	if (IsFull()) return R_ERR_DATA;

	DataProduceComponent compproduce;
	compproduce.uid = uid;
	compproduce.current_level = 1;  //初始产出等级为1

	return AddBuff(compproduce);
}


int DataProduceComponentManager::AddBuff(DataProduceComponent& compproduce)
{
	unsigned index = GetFreeIndex();

	if(index == -1)
		return R_ERR_DATA;

	if(Add(index, compproduce))
	{
		m_map[compproduce.uid] = index;
		return 0;
	}
	else
		return R_ERR_DATA;
}

int DataProduceComponentManager::LoadBuff(unsigned uid)
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

unsigned DataProduceComponentManager::GetIndex(unsigned uid)
{
	if(m_map.count(uid))
		return m_map[uid];

	return -1;
}

void DataProduceComponentManager::DoClear(unsigned uid)
{
	if(m_map.count(uid))
	{
		Clear(m_map[uid]);
		m_map.erase(uid);
	}
}

void DataProduceComponentManager::DoSave(unsigned uid)
{
	if(m_map.count(uid))
		AddSave(m_map[uid]);
}

DataProduceComponent& DataProduceComponentManager::Get(unsigned uid)
{
	int index = GetIndex(uid);

	if (index < 0)
	{
		error_log("uid: %u, index=%u", uid, index);
		throw std::runtime_error("get_comp_produce_error");
	}

	return  m_data->data[index];
}

bool DataProduceComponentManager::UpdateDataCompProduce(DataProduceComponent& compproduce)
{
	unsigned index = GetIndex(compproduce.uid);

	if (-1 == index)
	{
		return false;
	}

	return m_data->MarkChange(index);
}

