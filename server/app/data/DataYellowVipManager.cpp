#include "DataYellowVipManager.h"

int DataYellowVipManager::OnInit()
{
	for(unsigned i=0;i<DB_BASE_BUFF*DB_YELLOWVIP_FULL;++i)
	{
		if(!m_data->Empty(i))
			m_map[m_data->data[i].uid] = i;
	}

	return 0;
}

void DataYellowVipManager::OnExit()
{

}

void DataYellowVipManager::OnTimer1()
{

}

void DataYellowVipManager::OnTimer2()
{

}

int DataYellowVipManager::AddBuff(DataYellowVip & datayellowvip)
{
	unsigned index = GetFreeIndex();

	if(index == -1)
		return R_ERR_DATA;

	if(Add(index, datayellowvip))
	{
		m_map[datayellowvip.uid] = index;
		return 0;
	}
	else
		return R_ERR_DATA;
}

int DataYellowVipManager::LoadBuff(unsigned uid)
{
	//为防止重复加载
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

unsigned DataYellowVipManager::GetIndex(unsigned uid)
{
	if(m_map.count(uid))
		return m_map[uid];

	return -1;
}

void DataYellowVipManager::DoClear(unsigned uid)
{
	if(m_map.count(uid))
	{
		Clear(m_map[uid]);
		m_map.erase(uid);
	}
}

void DataYellowVipManager::DoSave(unsigned uid)
{
	if(m_map.count(uid))
		AddSave(m_map[uid]);
}

DataYellowVip& DataYellowVipManager::Get(unsigned uid)
{
	int index = GetIndex(uid);

	if (index < 0)
	{
		error_log("uid: %u, index=%u", uid, index);
		throw std::runtime_error("get_yellowvip_info_from_buff_error");
	}

	return  m_data->data[index];
}

bool DataYellowVipManager::IsDataYellowVipExists(unsigned uid)
{
	if (m_map.count(uid))
	{
		return true;
	}

	return false;
}

bool DataYellowVipManager::UpdateDataYellowVip(unsigned index)
{
	return m_data->MarkChange(index);
}

bool DataYellowVipManager::UpdateDataYellowVip(DataYellowVip & datayellowvip)
{
	unsigned index = GetIndex(datayellowvip.uid);

	if (-1 == index)
	{
		return false;
	}

	return UpdateDataYellowVip(index);
}
