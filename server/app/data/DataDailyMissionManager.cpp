#include "DataDailyMissionManager.h"

int DataDailyMissionManager::OnInit()
{
	for(unsigned i=0; i < MAX_INDEX; ++i)
	{
		if(!m_data->Empty(i))
		{
			unsigned uid = m_data->data[i].uid;
			unsigned id = m_data->data[i].id;
			unsigned missid = m_data->data[i].missid;

			CreateSelfIndex(uid, missid, id, i);
		}
	}

	return 0;
}

void DataDailyMissionManager::OnExit()
{

}

void DataDailyMissionManager::OnTimer1()
{

}

void DataDailyMissionManager::OnTimer2()
{

}

int DataDailyMissionManager::CheckBuff(unsigned uid)
{
	if(!m_map.count(uid))
		return R_ERR_NO_DATA;

	return 0;
}

int DataDailyMissionManager::AddBuff(DataDailyMission & dailymission)
{
	unsigned index = GetFreeIndex();

	unsigned uid = dailymission.uid;
	unsigned id = dailymission.id ;
	unsigned missid = dailymission.missid;

	if(index == -1)
	{
		error_log("[AddBuff] get free index error. uid=%u", uid);
		return R_ERR_DATA;
	}

	if(Add(index, dailymission))
	{
		CreateSelfIndex(uid, missid, id, index);
	}
	else
	{
		error_log("[AddBuff] Add to dbc failed. uid=%u", uid);
		return R_ERR_DATA;
	}

	return 0;
}

int DataDailyMissionManager::LoadBuff(unsigned uid)
{
	//为防止重复加载
	if (m_map.count(uid) > 0)
	{
		return 0;
	}

	vector<DataDailyMission> dailymissions(1);
	dailymissions[0].uid = uid;

	int ret = Load(dailymissions);

	if (ret)
	{
		return ret;
	}

	if (0 == dailymissions.size())
	{
		return R_ERR_NO_DATA;
	}

	//单个逐个加载
	for(int i = 0; i < dailymissions.size(); ++i)
	{
		unsigned index = GetFreeIndex();

		if(index == -1)
		{
			error_log("[LoadBuff] get free index error. uid=%u", uid);
			return R_ERR_DATA;
		}

		m_data->data[index] = dailymissions[i];  //给m_data内的数据赋值
		unsigned id = dailymissions[i].id;
		unsigned missid = dailymissions[i].missid;

		if(m_data->MardLoad(index))
		{
			m_freeIndex.erase(index);
		}
		else
		{
			error_log("[LoadBuff] mark load failed. uid=%u,id=%d.", uid, id);
			return R_ERROR;
		}

		CreateSelfIndex(uid, missid, id, index);
	}

	return 0;
}

void DataDailyMissionManager::DoClear(unsigned uid)
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
		 m_mapMissidIndex.erase(uid);
	}
}

void DataDailyMissionManager::DoSave(unsigned uid)
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

DataDailyMission& DataDailyMissionManager::GetDailyMission(unsigned uid, unsigned id)
{
	if (!m_map.count(uid) || !m_map[uid].count(id))
	{
		error_log("[GetDailyMission] id is not exists. uid=%u,id=%u", uid, id);
		throw std::runtime_error("get_dailymission_error");
	}

	unsigned index = m_map[uid][id];

	return m_data->data[index];
}

DataDailyMission& DataDailyMissionManager::GetDailyMissionByMissid(unsigned uid, unsigned missid)
{
	if (!m_mapMissidIndex.count(uid) || !m_mapMissidIndex[uid].count(missid))
	{
		error_log("[GetDailyMissionByMissid] missid is not exists. uid=%u,missid=%u", uid, missid);
		throw std::runtime_error("get_dailymission_error");
	}

	unsigned index = m_mapMissidIndex[uid][missid];

	return m_data->data[index];
}

DataDailyMission& DataDailyMissionManager::GetDailyMission(unsigned index)
{
	if (index >= MAX_INDEX)
	{
		error_log("[GetDailyMission] index is error. index=%u", index);
		throw std::runtime_error("get_daily_mission_error");
	}

	return  m_data->data[index];
}

int DataDailyMissionManager::GetDailyMissions(unsigned uid, vector<unsigned> & indexs)
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

bool DataDailyMissionManager::UpdateDailyMission(DataDailyMission& dailymission)
{
	unsigned uid = dailymission.uid;
	unsigned id = dailymission.id;
	unsigned missid = dailymission.missid;

	if (!m_map.count(uid) || !m_map[uid].count(id))
	{
		return false;
	}

	unsigned index = m_map[uid][id];

	//创建每日任务的映射
	m_mapMissidIndex[uid][missid] = index;

	return  m_data->MarkChange(index);
}

int DataDailyMissionManager::ClearMissidIndex(unsigned uid)
{
	if(m_mapMissidIndex.count(uid))
	{
		m_mapMissidIndex[uid].clear();
	}

	return 0;
}

int DataDailyMissionManager::CreateSelfIndex(unsigned uid, unsigned missid, unsigned id, unsigned index)
{
	m_map[uid][id] = index;
	m_mapMissidIndex[uid][missid] = index;

	return 0;
}
