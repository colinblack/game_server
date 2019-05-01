#include "DataComponentManager.h"

int DataComponentManager::OnInit()
{
	for(unsigned i=0; i < MAX_INDEX; ++i)
	{
		if(!m_data->Empty(i))
		{
			uint32_t uid = m_data->data[i].uid;
			uint32_t ud = m_data->data[i].ud;

			m_map[uid][ud] = i;
		}
	}

	return 0;
}

void DataComponentManager::OnExit()
{

}

void DataComponentManager::OnTimer1()
{

}

void DataComponentManager::OnTimer2()
{

}

int DataComponentManager::InitUserComponent(unsigned uid)
{
	//遍历uid下的所有ud
	map<uint32_t, uint32_t>::iterator miter;
	unsigned maxud = 0;

	for(miter = m_map[uid].begin(); miter != m_map[uid].end(); ++miter)
	{
		if (miter->first > maxud)
		{
			maxud = miter->first;
		}
	}

	m_userMaxCompud[uid] = maxud;

	return 0;
}

int DataComponentManager::CheckBuff(unsigned uid)
{
	if(!m_map.count(uid))
		return R_ERR_NO_DATA;

	return 0;
}

int DataComponentManager::AddBuff(DataComponent & component)
{
	unsigned index = GetFreeIndex();

	uint32_t uid = component.uid;
	uint32_t ud = component.ud ;

	if(index == -1)
	{
		error_log("[AddBuff] get free index error. uid=%u", uid);
		return R_ERR_DATA;
	}

	if(Add(index, component))
	{
		m_map[uid][ud] = index;
	}
	else
	{
		error_log("[AddBuff] Add to dbc failed. uid=%u", uid);
		return R_ERR_DATA;
	}

	return 0;
}

int DataComponentManager::LoadBuff(unsigned uid)
{
	//为防止重复加载
	if (m_map.count(uid) > 0)
	{
		return 0;
	}

	vector<DataComponent> vctcomponent(1);
	vctcomponent[0].uid = uid;

	int ret = Load(vctcomponent);

	if (ret)
	{
		return ret;
	}

	if (0 == vctcomponent.size())
	{
		return R_ERR_NO_DATA;
	}

	//单个逐个加载
	for(int i = 0; i < vctcomponent.size(); ++i)
	{
		unsigned index = GetFreeIndex();

		if(index == -1)
		{
			error_log("[LoadBuff] get free index error. uid=%u", uid);
			return R_ERR_DATA;
		}

		m_data->data[index] = vctcomponent[i];  //给m_data内的数据赋值
		unsigned ud = vctcomponent[i].ud;

		if(m_data->MardLoad(index))
		{
			m_freeIndex.erase(index);
		}
		else
		{
			error_log("[LoadBuff] mark load failed. uid=%u,compud=%d.", uid, ud);
			return R_ERROR;
		}

		m_map[uid][ud] = index;
	}

	return 0;
}


void DataComponentManager::DoClear(unsigned uid)
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

void DataComponentManager::DoSave(unsigned uid)
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

DataComponent& DataComponentManager::GetComponent(unsigned uid, unsigned ud)
{
	if (!m_map.count(uid) || !m_map[uid].count(ud))
	{
		error_log("[GetComponent] ud is not exists. uid=%u,ud=%u", uid, ud);
		throw std::runtime_error("get_component_error");
	}

	unsigned index = m_map[uid][ud];

	return m_data->data[index];
}

DataComponent& DataComponentManager::GetComponent(unsigned index)
{
	if (index >= MAX_INDEX)
	{
		error_log("[GetComponent] index is error. index=%u", index);
		throw std::runtime_error("get_componet_error");
	}

	return  m_data->data[index];
}

int DataComponentManager::GetComponents(unsigned uid, vector<unsigned> & indexs)
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

bool DataComponentManager::IsComponentExists(unsigned uid, unsigned ud)
{
	if (!m_map.count(uid) || !m_map[uid].count(ud))
	{
		return false;
	}

	return true;
}

bool DataComponentManager::UpdateDataComponent(DataComponent& component)
{
	unsigned uid = component.uid;
	unsigned ud = component.ud;

	if (!m_map.count(uid) || !m_map[uid].count(ud))
	{
		return false;
	}

	unsigned index = m_map[uid][ud];

	return  m_data->MarkChange(index);
}

bool DataComponentManager::DeleteComponent(DataComponent& component)
{
	unsigned uid = component.uid;
	unsigned ud = component.ud;

	if (!m_map.count(uid) || !m_map[uid].count(ud))
	{
		error_log("[DeleteComponent] get component error. uid=%u, compud=%u", uid, ud);
		throw std::runtime_error("get_component_error");
	}

	unsigned index = m_map[uid][ud];

	//删除dbc
	bool isSuccess = DeleteDBCComponent(index);

	if (!isSuccess)
	{
		return false;
	}

	//清除映射
	m_map[uid].erase(ud);

	return true;
}

unsigned DataComponentManager::GetUserNextUd(unsigned uid)
{
	m_userMaxCompud[uid] = m_userMaxCompud[uid] + 1;  //自增当前的ud

	return m_userMaxCompud[uid];
}

int DataComponentManager::GetNumOfDereliction(unsigned uid)
{
	int num = 0;

	if(m_map.count(uid))
	{
		 map<uint32_t, uint32_t>::iterator miter = m_map[uid].begin();

		 for(; miter != m_map[uid].end(); ++miter)
		 {
			 //判断是否无主
			 if (0 == m_data->data[miter->second].heroid)
			 {
				 ++num;
			 }
		 }
	}

	return num;
}

int DataComponentManager::GetOptionalComponents(unsigned uid, vector<unsigned> & indexs)
{
	if(m_map.count(uid))
	{
		 map<uint32_t, uint32_t>::iterator miter = m_map[uid].begin();

		 for(; miter != m_map[uid].end(); ++miter)
		 {
			 DataComponent& component = m_data->data[miter->second];

			 //过滤有主部件
			 if (0 == m_data->data[miter->second].heroid)
			 {
				 indexs.push_back(miter->second);
			 }
		 }
	}

	return 0;
}

int DataComponentManager::GetHeroComponents(unsigned uid, unsigned heroid, vector<unsigned> & indexs)
{
	if(m_map.count(uid))
	{
		 map<uint32_t, uint32_t>::iterator miter = m_map[uid].begin();

		 for(; miter != m_map[uid].end(); ++miter)
		 {
			 DataComponent& component = m_data->data[miter->second];

			 if (heroid == m_data->data[miter->second].heroid)
			 {
				 indexs.push_back(miter->second);
			 }
		 }
	}

	return 0;
}

bool DataComponentManager::DeleteDBCComponent(unsigned index)
{
	//mark删除状态
	m_data->MarkDel(index);

	//添加至操作队列
	AddSave(index);

	return true;
}
