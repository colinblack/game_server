#include "DataFriendGiftManager.h"

int DataFriendGiftManager::OnInit()
{
	for(unsigned i = 0; i < MAX_INDEX; ++i)
	{
		if(!m_data->Empty(i))
			m_map[m_data->data[i].uid] = i;
	}

	return 0;
}

void DataFriendGiftManager::OnExit()
{

}

void DataFriendGiftManager::OnTimer1()
{

}

void DataFriendGiftManager::OnTimer2()
{

}

int DataFriendGiftManager::CheckBuff(unsigned uid)
{
	if (!m_map.count(uid))
	{
		return R_ERR_NO_DATA;
	}

	return 0;
}

int DataFriendGiftManager::New(unsigned uid)
{
	if (m_map.count(uid) > 0)
	{
		return R_SUCCESS;
	}

	if (IsFull()) return R_ERR_DATA;

	DataFriendGift friendgift;
	friendgift.uid = uid;
	friendgift.grades = 1;  //默认就是1档

	return AddBuff(friendgift);
}


int DataFriendGiftManager::AddBuff(DataFriendGift& friendgift)
{
	unsigned index = GetFreeIndex();

	if(index == -1)
		return R_ERR_DATA;

	if(Add(index, friendgift))
	{
		m_map[friendgift.uid] = index;
		return 0;
	}
	else
		return R_ERR_DATA;
}

int DataFriendGiftManager::LoadBuff(unsigned uid)
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

unsigned DataFriendGiftManager::GetIndex(unsigned uid)
{
	if(m_map.count(uid))
		return m_map[uid];

	return -1;
}

void DataFriendGiftManager::DoClear(unsigned uid)
{
	if(m_map.count(uid))
	{
		Clear(m_map[uid]);
		m_map.erase(uid);
	}
}

void DataFriendGiftManager::DoSave(unsigned uid)
{
	if(m_map.count(uid))
		AddSave(m_map[uid]);
}

DataFriendGift& DataFriendGiftManager::GetFriendGift(unsigned uid)
{
	int index = GetIndex(uid);

	if (index < 0)
	{
		error_log("uid: %u, index=%u", uid, index);
		throw std::runtime_error("get_friendgift_error");
	}

	return  m_data->data[index];
}

bool DataFriendGiftManager::UpdateDataFriendGift(DataFriendGift& friendgift)
{
	unsigned index = GetIndex(friendgift.uid);

	if (-1 == index)
	{
		return false;
	}

	return m_data->MarkChange(index);
}

