#include "DataAchievementManager.h"

int DataAchievementManager::OnInit()
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

void DataAchievementManager::OnExit()
{

}

void DataAchievementManager::OnTimer1()
{

}

void DataAchievementManager::OnTimer2()
{

}

int DataAchievementManager::CheckBuff(unsigned uid)
{
	if (!m_map.count(uid))
	{
		return R_ERR_NO_DATA;
	}

	return 0;
}

int DataAchievementManager::AddBuff(DataAchievement & achievement)
{
	unsigned index = GetFreeIndex();

	uint32_t uid = achievement.uid;
	uint32_t id = achievement.id;

	if(index == -1)
	{
		error_log("[AddBuff] get free index error. uid=%u", uid);
		return R_ERR_DATA;
	}

	if(Add(index, achievement))
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

int DataAchievementManager::LoadBuff(unsigned uid)
{
	//为防止重复加载
	if (m_map.count(uid) > 0)
	{
		return 0;
	}

	vector<DataAchievement> vctachievement(1);
	vctachievement[0].uid = uid;

	int ret = Load(vctachievement);

	if (ret)
	{
		return ret;
	}

	if (0 == vctachievement.size())
	{
		return R_ERR_NO_DATA;
	}

	//加载用户的所有成就数据
	for(int i = 0; i < vctachievement.size(); ++i)
	{
		int index = GetFreeIndex();

		if(index == -1)
		{
			error_log("[LoadBuff] get free index error. uid=%u", uid);
			return R_ERR_DATA;
		}

		m_data->data[index] = vctachievement[i];  //给m_data内的数据赋值
		unsigned id = vctachievement[i].id;

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

DataAchievement & DataAchievementManager::GetAchievement(unsigned uid, unsigned id)
{
	if (!m_map.count(uid) || !m_map[uid].count(id))
	{
		error_log("[GetAchievement] get achievement error. uid=%u, id=%u", uid, id);
		throw std::runtime_error("get_achievement_error");
	}

	unsigned index =  m_map[uid][id];

	return m_data->data[index];
}

DataAchievement & DataAchievementManager::GetAchievement(unsigned index)
{
	if (index >= MAX_INDEX)
	{
		throw std::runtime_error("wrong index param");
	}

	return m_data->data[index];
}

bool DataAchievementManager::UpdateAchievement(unsigned index)
{
	return m_data->MarkChange(index);
}

bool DataAchievementManager::UpdateAchievement(DataAchievement & achievement)
{
	unsigned uid = achievement.uid;
	unsigned id = achievement.id;

	if (!m_map.count(uid) || !m_map[uid].count(id))
	{
		error_log("[UpdateAchievement] get achievement error. uid=%u, id=%u", uid, id);
		throw std::runtime_error("get_achievement_error");
	}

	unsigned index =  m_map[uid][id];

	return  UpdateAchievement(index);
}

bool DataAchievementManager::IsAchieveExist(unsigned uid, unsigned id)
{
	if (m_map.count(uid) && m_map[uid].count(id))
	{
		return true;
	}

	return false;
}

int DataAchievementManager::GetUnDoneAchieveByType(unsigned uid, unsigned type, vector<unsigned> & vctindexs)
{
	if(m_map.count(uid))
	{
		 map<uint32_t, uint32_t>::iterator miter = m_map[uid].begin();

		 //为减少频繁的函数调用，在这里，直接将示例对象的指针赋值
		 ConfigManager * pinstance = ConfigManager::Instance();
		unsigned index =  0;

		 for(; miter != m_map[uid].end(); ++miter)
		 {
			 DataAchievement & achievement = m_data->data[miter->second];

			 //过滤已完成的
			if (achievement.status) //非0，已完成
			{
				continue;
			}

			//判断类型是否和参数一致
			//考虑到可能这个方法可能调用的很频繁，所以使用直接地址访问，而非更合理的函数调用方式来减耦
			if (!pinstance->achieveidIndex.count(achievement.id))
			{
				error_log("[GetUnDoneAchieveByType] ConfigManager->achieveidIndex have no key. uid=%u,id=%u", uid, achievement.id);
				throw runtime_error("achievid_cfg_error");
			}

			index = pinstance->achieveidIndex[achievement.id];

			//过滤类型不一致的
			if (pinstance->achievements.m_config.achievements(index).type() != type)
			{
				continue;
			}

			vctindexs.push_back(miter->second);
		 }
	}

	return 0;
}

int DataAchievementManager::GetUserAchievements(unsigned uid, vector<unsigned> & vctindexs)
{
	if(m_map.count(uid))
	{
		 map<uint32_t, uint32_t>::iterator miter = m_map[uid].begin();

		 for(; miter != m_map[uid].end(); ++miter)
		 {
			 vctindexs.push_back(miter->second);
		 }
	}

	return 0;
}

int DataAchievementManager::FullMessage(unsigned uid, ProtoAchievement::AchievementAllCPP * msg)
{
	if(m_map.count(uid))
	{
		map<uint32_t, uint32_t>::iterator miter = m_map[uid].begin();

		for(; miter != m_map[uid].end(); ++miter)
		{
			m_data->data[miter->second].SetMessage(msg->add_achievement());
		}
	}

	return 0;
}


void DataAchievementManager::DoClear(unsigned uid)
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

void DataAchievementManager::DoSave(unsigned uid)
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

