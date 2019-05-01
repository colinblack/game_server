#include "DataMissionManager.h"

int DataMissionManager::OnInit()
{
	for(unsigned i=0; i < DB_BASE_BUFF*DB_MISSION_FULL; ++i)
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

void DataMissionManager::OnExit()
{

}

void DataMissionManager::OnTimer1()
{

}

void DataMissionManager::OnTimer2()
{

}

int DataMissionManager::CheckBuff(unsigned uid)
{
	if (!m_map.count(uid))
	{
		return R_ERR_NO_DATA;
	}

	return 0;
}

int DataMissionManager::AddBuff(DataMission & mission)
{
	unsigned index = GetFreeIndex();

	uint32_t uid = mission.uid;
	uint32_t id = mission.id;

	if(index == -1)
	{
		error_log("[AddBuff] get free index error. uid=%u", uid);
		return R_ERR_DATA;
	}

	if(Add(index, mission))
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

int DataMissionManager::LoadBuff(unsigned uid)
{
	//为防止重复加载
	if (m_map.count(uid) > 0)
	{
		return 0;
	}

	vector<DataMission> vctmission(1);
	vctmission[0].uid = uid;

	int ret = Load(vctmission);

	if (ret)
	{
		return ret;
	}

	if (0 == vctmission.size())
	{
		return R_ERR_NO_DATA;
	}

	//加载用户的所有任务数据
	for(int i = 0; i < vctmission.size(); ++i)
	{
		int index = GetFreeIndex();

		if(index == -1)
		{
			error_log("[LoadBuff] get free index error. uid=%u", uid);
			return R_ERR_DATA;
		}

		m_data->data[index] = vctmission[i];  //给m_data内的数据赋值
		unsigned id = vctmission[i].id;

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

DataMission & DataMissionManager::GetMission(unsigned uid, unsigned id)
{
	if (!m_map.count(uid) || !m_map[uid].count(id))
	{
		error_log("[GetMission] get mission error. uid=%u, id=%u", uid, id);
		throw std::runtime_error("get_mission_error");
	}

	unsigned index =  m_map[uid][id];
	return m_data->data[index];
}

int DataMissionManager::GetMissionIndex(unsigned uid, unsigned id)
{
	if (!m_map.count(uid) || !m_map[uid].count(id))
	{
		return -1;
	}

	return m_map[uid][id];
}

bool DataMissionManager::UpdateMission(unsigned index)
{
	return m_data->MarkChange(index);
}

bool DataMissionManager::UpdateMission(DataMission & mission)
{
	unsigned uid = mission.uid;
	unsigned id = mission.id;

	if (!m_map.count(uid) || !m_map[uid].count(id))
	{
		error_log("[UpdateMission] get mission error. uid=%u, id=%u", uid, id);
		throw std::runtime_error("get_mission_error");
	}

	unsigned index =  m_map[uid][id];

	return  UpdateMission(index);
}

bool DataMissionManager::DeleteDBCMission(unsigned index)
{
	//mark删除状态
	m_data->MarkDel(index);

	//添加至操作队列
	AddSave(index);

	return true;
}

bool DataMissionManager::DeleteMission(DataMission & mission)
{
	unsigned uid = mission.uid;
	unsigned id = mission.id;

	if (!m_map.count(uid) || !m_map[uid].count(id))
	{
		error_log("[DeleteMission] get mission error. uid=%u, id=%u", uid, id);
		throw std::runtime_error("get_mission_error");
	}

	unsigned index =  m_map[uid][id];

	bool isSuccess = DeleteDBCMission(index);

	if (!isSuccess)
	{
		return false;
	}

	m_map[uid].erase(id);

	 return true;
}

int DataMissionManager::GetUnDoneMission(unsigned uid, vector<unsigned> & vctindexs)
{
	if(m_map.count(uid))
	{
		 map<uint32_t, uint32_t>::iterator miter = m_map[uid].begin();

		 for(; miter != m_map[uid].end(); ++miter)
		 {
				if (!m_data->data[miter->second].status)
				{
					vctindexs.push_back(miter->second);
				}
		 }
	}

	return 0;
}

int DataMissionManager::GetUserMissions(unsigned uid, vector<unsigned> & vctindexs)
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

DataMission & DataMissionManager::GetMissionByIndex(unsigned index)
{
	if (index >= (DB_BASE_BUFF*DB_MISSION_FULL))
	{
		throw std::runtime_error("wrong index param");
	}

	return m_data->data[index];
}

int DataMissionManager::FullMessage(unsigned uid, ProtoMission::MissionAllCPP * msg)
{
	if(m_map.count(uid))
	{
		 map<uint32_t, uint32_t>::iterator miter = m_map[uid].begin();

		 for(; miter != m_map[uid].end(); ++miter)
		 {
				m_data->data[miter->second].SetMessage(msg->add_missions());
		 }
	}

	return 0;
}

void DataMissionManager::DoClear(unsigned uid)
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

void DataMissionManager::DoSave(unsigned uid)
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

