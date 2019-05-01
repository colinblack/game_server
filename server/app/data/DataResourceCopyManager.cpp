#include "DataResourceCopyManager.h"

int DataResourceCopyManager::OnInit()
{
	for(unsigned i=0; i < MAX_INDEX; ++i)
	{
		if(!m_data->Empty(i))
		{
			uint32_t uid = m_data->data[i].uid;
			uint32_t id = m_data->data[i].id;

			m_map[uid][id] = i;
		}
	}

	return 0;
}

void DataResourceCopyManager::OnExit()
{

}

void DataResourceCopyManager::OnTimer1()
{

}

void DataResourceCopyManager::OnTimer2()
{

}

DataResourceCopy& DataResourceCopyManager::GetResourceCopy(unsigned uid, unsigned id)
{
	int ret = 0;

	if (!m_map.count(uid))
	{
		//可能是没有load进来，进行重新load一遍
		LoadBuff(uid);
	}

	if (!m_map.count(uid) || !m_map[uid].count(id))
	{
		//没有该数据，则新增
		ret = NewResrouceCopy(uid, id);

		if (ret)
		{
			throw runtime_error("add_resource_copy_error");
		}
	}

	unsigned index = m_map[uid][id];

	return m_data->data[index];
}

DataResourceCopy& DataResourceCopyManager::GetResourceCopy(unsigned index)
{
	if (index >= MAX_INDEX)
	{
		error_log("index is error. index=%u", index);
		throw std::runtime_error("get_resourcecopy_error");
	}

	return  m_data->data[index];
}

int DataResourceCopyManager::NewResrouceCopy(unsigned uid, unsigned id)
{
	DataResourceCopy resourcecopy;

	resourcecopy.uid = uid;
	resourcecopy.id = id;

	return AddBuff(resourcecopy);
}

int DataResourceCopyManager::GetResourceCopies(unsigned uid, vector<unsigned> & indexs)
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

bool DataResourceCopyManager::UpdateResourceCopy(DataResourceCopy& resourcecopy)
{
	unsigned uid = resourcecopy.uid;
	unsigned id = resourcecopy.id;

	if (!m_map.count(uid) || !m_map[uid].count(id))
	{
		return false;
	}

	unsigned index = m_map[uid][id];

	return  m_data->MarkChange(index);
}

int DataResourceCopyManager::CheckBuff(unsigned uid)
{
	if(!m_map.count(uid))
		return R_ERR_NO_DATA;

	return 0;
}

int DataResourceCopyManager::AddBuff(DataResourceCopy & resourcecopy)
{
	unsigned index = GetFreeIndex();

	uint32_t uid = resourcecopy.uid;
	uint32_t id = resourcecopy.id ;

	if(index == -1)
	{
		error_log("[AddBuff] get free index error. uid=%u", uid);
		return R_ERR_DATA;
	}

	if(Add(index, resourcecopy))
	{
		m_map[uid][id] = index;
	}
	else
	{
		error_log("[AddBuff] Add to dbc failed. uid=%u", uid);
		return R_ERR_DATA;
	}

	return 0;
}

int DataResourceCopyManager::LoadBuff(unsigned uid)
{
	//为防止重复加载
	if (m_map.count(uid) > 0)
	{
		return 0;
	}

	vector<DataResourceCopy> vctfriend(1);
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
		unsigned id = vctfriend[i].id;

		if(m_data->MardLoad(index))
		{
			m_freeIndex.erase(index);
		}
		else
		{
			error_log("[LoadBuff] mark load failed. uid=%u,id=%d.", uid, id);
			return R_ERROR;
		}

		m_map[uid][id] = index;
	}

	return 0;
}

void DataResourceCopyManager::DoClear(unsigned uid)
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

void DataResourceCopyManager::DoSave(unsigned uid)
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
