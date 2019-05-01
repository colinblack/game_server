#include "DataFriendManager.h"

int DataFriendManager::OnInit()
{
	for(unsigned i=0; i < MAX_INDEX; ++i)
	{
		if(!m_data->Empty(i))
		{
			uint32_t uid = m_data->data[i].uid;
			uint32_t frienduid = m_data->data[i].friend_uid;

			m_map[uid][frienduid] = i;
		}
	}

	return 0;
}

void DataFriendManager::OnExit()
{

}

void DataFriendManager::OnTimer1()
{

}

void DataFriendManager::OnTimer2()
{

}


int DataFriendManager::CheckBuff(unsigned uid)
{
	if(!m_map.count(uid))
		return R_ERR_NO_DATA;

	return 0;
}

int DataFriendManager::AddBuff(DataFriend & datafriend)
{
	unsigned index = GetFreeIndex();

	uint32_t uid = datafriend.uid;
	uint32_t frienduid = datafriend.friend_uid ;

	if(index == -1)
	{
		error_log("[AddBuff] get free index error. uid=%u", uid);
		return R_ERR_DATA;
	}

	if(Add(index, datafriend))
	{
		m_map[uid][frienduid] = index;
	}
	else
	{
		error_log("[AddBuff] Add to dbc failed. uid=%u", uid);
		return R_ERR_DATA;
	}

	return 0;
}

int DataFriendManager::LoadBuff(unsigned uid)
{
	//为防止重复加载
	if (m_map.count(uid) > 0)
	{
		return 0;
	}

	vector<DataFriend> vctfriend(1);
	vctfriend[0].uid = uid;

	int ret = Load(vctfriend);

	if (ret)
	{
		return ret;
	}

	if (0 == vctfriend.size())
	{
		return R_ERR_NO_DATA;
	}

	//单个逐个加载
	for(int i = 0; i < vctfriend.size(); ++i)
	{
		unsigned index = GetFreeIndex();

		if(index == -1)
		{
			error_log("[LoadBuff] get free index error. uid=%u", uid);
			return R_ERR_DATA;
		}

		m_data->data[index] = vctfriend[i];  //给m_data内的数据赋值
		unsigned frienduid = vctfriend[i].friend_uid;

		if(m_data->MardLoad(index))
		{
			m_freeIndex.erase(index);
		}
		else
		{
			error_log("[LoadBuff] mark load failed. uid=%u,frienduid=%d.", uid, frienduid);
			return R_ERROR;
		}

		m_map[uid][frienduid] = index;
	}

	return 0;
}


void DataFriendManager::DoClear(unsigned uid)
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

void DataFriendManager::DoSave(unsigned uid)
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

DataFriend& DataFriendManager::GetFriend(unsigned uid, unsigned frienduid)
{
	if (!m_map.count(uid) || !m_map[uid].count(frienduid))
	{
		error_log("[GetFriend] frienduid is not exists. uid=%u,friend_uid=%u", uid, frienduid);
		throw std::runtime_error("get_friend_error");
	}

	unsigned index = m_map[uid][frienduid];

	return m_data->data[index];
}

DataFriend& DataFriendManager::GetFriend(unsigned index)
{
	if (index >= MAX_INDEX)
	{
		error_log("[GetFriend] index is error. index=%u", index);
		throw std::runtime_error("get_friend_error");
	}

	return  m_data->data[index];
}

bool DataFriendManager::IsFriendExist(unsigned uid, unsigned othuid)
{
	if (!m_map.count(uid) || !m_map[uid].count(othuid))
	{
		return false;
	}

	return true;
}

int DataFriendManager::GetFriends(unsigned uid, vector<unsigned> & indexs)
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

bool DataFriendManager::UpdateFriend(DataFriend& datafriend)
{
	unsigned uid = datafriend.uid;
	unsigned friend_uid = datafriend.friend_uid;

	if (!m_map.count(uid) || !m_map[uid].count(friend_uid))
	{
		return false;
	}

	unsigned index = m_map[uid][friend_uid];

	return  m_data->MarkChange(index);
}

bool DataFriendManager::DeleteFriend(DataFriend & datafriend)
{
	unsigned uid = datafriend.uid;
	unsigned frienduid = datafriend.friend_uid;

	if (!m_map.count(uid) || !m_map[uid].count(frienduid))
	{
		error_log("get friend error. uid=%u, id=%u", uid, frienduid);
		throw std::runtime_error("get_friend_error");
	}

	unsigned index =  m_map[uid][frienduid];

	bool isSuccess = DeleteDBC(index);

	if (!isSuccess)
	{
		return false;
	}

	m_map[uid].erase(frienduid);

	 return true;
}

bool DataFriendManager::DeleteDBC(unsigned index)
{
	//mark删除状态
	m_data->MarkDel(index);

	//添加至操作队列
	AddSave(index);

	return true;
}
