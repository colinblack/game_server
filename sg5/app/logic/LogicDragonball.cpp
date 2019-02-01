#include "LogicDragonball.h"

Json::Value CLogicDragonball::m_ConfigValue;
bool CLogicDragonball::m_bInit = false;

CDataDragonball* CLogicDragonball::GetCDataDragonball()
{
	GET_MEM_DATA_SEM(CDataDragonball, CONFIG_DRAGONBALL_DATA ,sem_dragonball,false)
	/*static CDataDragonball* pdragonball = NULL;
	if (!pdragonball)
	{
		pdragonball = new CDataDragonball();
		if (pdragonball->Init(Config::GetValue(CONFIG_DRAGONBALL_DATA)) != 0)
		{
			delete pdragonball;
			pdragonball = NULL;
		}
	}
	return pdragonball;*/
}

int CLogicDragonball::WhichDragonballHold(unsigned uid, unsigned &ballId, unsigned &ts, DragonballActivityStatus flag)
{
	if(flag == DragonballActivityStatus_max)
		flag = IsDragonballActivityTs();
	if(flag == DragonballActivityStatus_none)
	{
		ballId = 0;
		ts = 0;
		return 0;
	}

	CDataDragonball* pball = GetCDataDragonball();
	if (!pball)
	{
		DB_ERROR_RETURN_MSG("get_ball_instance_fail");
	}

	int ret = pball->WhichDragonballHold(uid, ballId, ts, flag==DragonballActivityStatus_attack);
	if (ret != 0)
	{
		DB_ERROR_RETURN_MSG("get_dragonball_fail");
	}

	if(ballId && flag==DragonballActivityStatus_show)
		ballId = INVALID_BALL_ID;

	return 0;
}

int CLogicDragonball::GetDragonballs(Json::Value &data)
{
	DragonballData balls;
	DragonballActivityStatus flag = IsDragonballActivityTs();

	if(flag != DragonballActivityStatus_none)
	{
		CDataDragonball* pball = GetCDataDragonball();
		if (!pball)
		{
			DB_ERROR_RETURN_MSG("get_ball_instance_fail");
		}

		int ret = pball->ViewAllDragonball(balls,flag==DragonballActivityStatus_attack);
		if (ret != 0)
		{
			DB_ERROR_RETURN_MSG("get_dragonball_fail");
		}
	}

	DataUser user;
	CLogicUser logicUser;
	data.resize(DRAGONBALL_ID_MAX - DRAGONBALL_ID_MIN + 1);
	for (int i = DRAGONBALL_ID_MIN; i <= DRAGONBALL_ID_MAX; i++)
	{
		unsigned index = DragonballIdToIndex(i);
		if (flag==DragonballActivityStatus_show || !IsValidUid(balls.ball[index].holderUid))
		{
			data[index]["ballid"] = INVALID_BALL_ID;
		}
		else
		{
			data[index]["ballid"] = i;
		}
		data[index]["uid"] = balls.ball[index].holderUid;
		data[index]["name"] = balls.ball[index].name;
		data[index]["union_id"] = balls.ball[index].allianceId;
		data[index]["union_name"] = balls.ball[index].aname;
		data[index]["ts"] = balls.ball[index].ts;
		if(IsValidUid(balls.ball[index].holderUid)
		&& logicUser.GetUserLimit(balls.ball[index].holderUid, user) == 0)
			data[index]["level"] = user.level;
	}
	return 0;
}

int CLogicDragonball::ViewAllDragonball(DragonballData &balls)
{
	CDataDragonball* pball = GetCDataDragonball();
	if (!pball)
	{
		DB_ERROR_RETURN_MSG("get_ball_instance_fail");
	}
	int ret = pball->ViewAllDragonball(balls);
	if (ret != 0)
	{
		DB_ERROR_RETURN_MSG("get_dragonball_fail");
	}
	return 0;
}

bool CLogicDragonball::EnableAttackForDragonball(unsigned ballid, unsigned level)
{
	if(level >= 30)
		return true;
	return false;
	//取消等级限制

	switch(ballid)
	{
	case 1: return (level >= 30 && level <= 44);
	case 2: return (level >= 45 && level <= 54);
	case 3: return (level >= 55 && level <= 64);
	case 4: return (level >= 65 && level <= 70);
	case 5: return (level >= 71 && level <= 75);
	case 6: return (level >= 76 && level <= 80);
	case 7: return (level > 80);
	default: break;
	}
	return false;
}

int CLogicDragonball::SnatchDragonball(unsigned ballid, unsigned snatchUid, string &snatchName, unsigned &preUid)
{
	CDataDragonball* pball = GetCDataDragonball();
	if (!pball)
	{
		DB_ERROR_RETURN_MSG("get_ball_instance_fail");
	}
	unsigned preTs = 0;
	string preName;
	int ret = pball->SetDragonball(ballid, snatchUid, snatchName, Time::GetGlobalTime(), preUid, preTs, preName);
	if (ret != 0)
	{
		DB_ERROR_RETURN_MSG("set_dragonball_fail");
	}
	unsigned detlatime = Time::GetGlobalTime() - preTs;
	if(detlatime > 86400)
		return -1;

	AllianceBall aBall;
	SetAlliance(aBall);
	PayAlliance(aBall);

	Json::Value updates;
	updates.resize(1);
	updates[(unsigned)0]["s"] = "DRAGONBALLLOSS";
	updates[(unsigned)0]["name"] = snatchName;
	updates[(unsigned)0]["ballid"] = ballid;
	updates[(unsigned)0]["tm"] = detlatime;
	updates[(unsigned)0]["ts"] = Time::GetGlobalTime();
	CLogicUpdates logicUpdates;
	logicUpdates.AddUpdates(preUid, updates,false, true);

	Json::Value updates2;
	updates2.resize(1);
	updates2[(unsigned)0]["s"] = "DRAGONBALLHOLD";
	updates2[(unsigned)0]["name"] = preName;
	updates2[(unsigned)0]["ballid"] = ballid;
	updates2[(unsigned)0]["ballts"] = Time::GetGlobalTime();
	updates2[(unsigned)0]["ts"] = Time::GetGlobalTime();
	logicUpdates.AddUpdates(snatchUid, updates2);

	preUid = snatchUid;

	return 0;
}

int CLogicDragonball::GetAllianceDragons(map<unsigned,AllianceBall>& allianceBalls){

	CDataDragonball* pball = GetCDataDragonball();
	if (!pball)
	{
		DB_ERROR_RETURN_MSG("get_ball_instance_fail");
	}

	return pball->GetAllianceDragons(allianceBalls);
}

int CLogicDragonball::PayAlliance(AllianceBall& aBall){
	int gap = (Time::GetGlobalTime() - aBall.ts) / 600;
	int reward = gap * 5;
	if (reward < 0) reward = 0;
	return 0;
	if(aBall.allianceId > 0 && reward > 0){
		CLogicAlliance logicAlliance;
		logicAlliance.ChangeResource(aBall.allianceId,0ll,0ll,0ll,0ll,0ll,reward,"DRAGONBALL");

		DataAlliance alliance;
		int ret = logicAlliance.GetAllianceLimit(aBall.allianceId, alliance);
		if(ret != 0)
		{
			return ret;
		}

		CLogicUpdates logicUpdates;
		Json::Value updates;
		updates.resize(1);
		updates[(unsigned)0]["s"] = "DBALLREWARD_ALLIANCE";
		updates[(unsigned)0]["tm"] = Time::GetGlobalTime() - aBall.ts;
		updates[(unsigned)0]["ts"] = Time::GetGlobalTime();
		logicUpdates.AddUpdates(alliance.leader_uid, updates);
	}

	return 0;
}

int CLogicDragonball::SetAlliance(AllianceBall& aBall){
	CDataDragonball* pball = GetCDataDragonball();
	if (!pball)
	{
		DB_ERROR_RETURN_MSG("get_ball_instance_fail");
	}

	return pball->SetAlliance(aBall);
}

int CLogicDragonball::ResetAlliance(){
	CDataDragonball* pball = GetCDataDragonball();
	if (!pball)
	{
		DB_ERROR_RETURN_MSG("get_ball_instance_fail");
	}

	return pball->ResetAlliance();
}

DragonballActivityStatus CLogicDragonball::IsDragonballActivityTs(void)
{
	if(!m_bInit)
	{
		string rangeTime = Config::GetValue(CONFIG_DRAGONBALL_ACTIVITY_TS);
		Json::Reader().parse(rangeTime, m_ConfigValue);
		m_bInit = true;
	}

	time_t now;
	time(&now);
	struct tm *pTm = localtime(&now);
	int tempSec = pTm->tm_sec;
	int tempMin = pTm->tm_min;
	int tempHour = pTm->tm_hour;
	int tempWeek = pTm->tm_wday;
	unsigned tempNow = tempSec + tempMin * 60 + tempHour *3600;

	if(m_ConfigValue.size() > 0)
	{
		if(m_ConfigValue.size() > 1)
		{
			bool flag = true;
			for(int i=0;i<m_ConfigValue[1u].size();++i)
			{
				if(tempWeek == m_ConfigValue[1u][i].asUInt())
				{
					flag = false;
					break;
				}
			}
			if(flag)
				return DragonballActivityStatus_none;
		}
		else
		{
			if(tempWeek != 2 && tempWeek != 6)
				return DragonballActivityStatus_none;
		}

		if(tempNow >= m_ConfigValue[0u][0u].asUInt() && tempNow <= m_ConfigValue[0u][1u].asUInt())
		{
			return DragonballActivityStatus_attack;
		}
		else if(tempNow >=  m_ConfigValue[0u][1u].asUInt())
		{
			return DragonballActivityStatus_show;
		}
	}
	return DragonballActivityStatus_none;
}


