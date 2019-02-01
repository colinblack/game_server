/*
 * DataHequActivity.cpp
 *
 *  Created on: 2013-07-17
 *      Author: Administrator
 */

#include "DataHequActivity.h"


CDataAlliancePoint::CDataAlliancePoint(){
	m_init = false;
}
CDataAlliancePoint::~CDataAlliancePoint() {
	// TODO Auto-generated destructor stub
}

int  CDataAlliancePoint::Init(const std::string &path, semdat sem)
{
	if(m_init)
	{
		return 0;
	}
	int semgroup = 0;
	int semserver = 0;
	Config::GetDomain(semserver);
	if(!semserver)
		Config::GetDB(semserver);
	if(!m_sh.CreateOrOpen(path.c_str(), sizeof(DataHequAlliancePoint), SEM_ID(sem,semgroup,semserver)))
	{
		error_log("[init_alliance_point_data_fail][path=%s]", path.c_str());
		return R_ERROR;
	}
	CAutoLock lock(&m_sh, true);
	if(!m_sh.HasInit())
	{
		DataHequAlliancePoint *pdata = (DataHequAlliancePoint *)m_sh.GetAddress();
		if(pdata == NULL)
		{
			DB_ERROR_RETURN_MSG("init_alliance_point_fail");
		}
		memset(pdata, 0, sizeof(*pdata));
		m_sh.SetInitDone();
	}
	m_init = true;
	return 0;
}

int sortFuncAlliancePoint(const AlliancePoint& left,const AlliancePoint& right){
	return left.point > right.point;
}

int CDataAlliancePoint::UpdateAlliancePointRankList(const AlliancePoint &points)
{
	DataHequAlliancePoint *pdata = (DataHequAlliancePoint *)m_sh.GetAddress();
	if(pdata == NULL)
	{
		DB_ERROR_RETURN_MSG("init_alliancepoint_fail");
	}
	CAutoLock lock(&m_sh, true);

	//版本控制
	if(pdata->version != Config::GetIntValue(CONFIG_HEQU_ACTIVITY_VER))
	{
		memset(pdata, 0, sizeof(*pdata));
		pdata->version = Config::GetIntValue(CONFIG_HEQU_ACTIVITY_VER);
	}

	int flag = 0;
	if((Time::GetGlobalTime() >=Config::GetIntValue(CONFIG_HEQU_ACTIVITY_BEGIN_TS))
		&& (Time::GetGlobalTime() <= Config::GetIntValue(CONFIG_HEQU_ACTIVITY_END_TS)))
	{
		for(int i = 0;i < ALLIANCE_POINT_RANK_SIZE; ++i)
		{
			if(pdata->point[i].alliance_id == points.alliance_id)
			{
				pdata->point[i].point += points.point;
				flag = i;
				break;
			}
			else if(pdata->point[i].alliance_id == 0 )
			{
				pdata->point[i] = points;
				flag = i;
				break;
			}

			if(i == ALLIANCE_POINT_RANK_SIZE-1 && points.point > pdata->point[i].point)
			{
				pdata->point[i] = points;
				flag = i;
			}
		}

		AlliancePoint Point;
		if(flag >=10 && pdata->point[flag].point >  pdata->point[9].point)
		{
			Point = pdata->point[9];
			pdata->point[9] = pdata->point[flag];
			pdata->point[flag] = Point;
		}

		vector <AlliancePoint> vecPoint;
		vecPoint.clear();
		for(int i = 0; i < 10;++i)
		{
			vecPoint.push_back(pdata->point[i]);
		}

		sort(vecPoint.begin(),vecPoint.end(),sortFuncAlliancePoint);

		for(int i = 0; i < 10;++i){
			pdata->point[i] = vecPoint[i];
		}
	}
	return 0;
}

int CDataAlliancePoint::GetAlliancePointRankList( vector <AlliancePoint> &vecPoints)
{
	DataHequAlliancePoint *pdata = (DataHequAlliancePoint *)m_sh.GetAddress();
	if(pdata == NULL)
	{
		DB_ERROR_RETURN_MSG("init_alliancepoint_fail");
	}
	CAutoLock lock(&m_sh, true);
	//版本控制
	if(pdata->version != Config::GetIntValue(CONFIG_HEQU_ACTIVITY_VER))
	{
		memset(pdata, 0, sizeof(*pdata));
		pdata->version = Config::GetIntValue(CONFIG_HEQU_ACTIVITY_VER);
	}

	for(int i = 0; i < 10;++i)
	{
		vecPoints.push_back(pdata->point[i]);
	}

	return 0;
}

int CDataAlliancePoint::RewardAlliancePointRankList( vector <AlliancePoint> &rewardPoints)
{
	DataHequAlliancePoint *pdata = (DataHequAlliancePoint *)m_sh.GetAddress();
	if(pdata == NULL)
	{
		DB_ERROR_RETURN_MSG("init_alliancepoint_fail");
	}
	CAutoLock lock(&m_sh, true);

	if((Time::GetGlobalTime() > Config::GetIntValue(CONFIG_HEQU_ACTIVITY_END_TS))
		&& (Time::GetGlobalTime() <= Config::GetIntValue(CONFIG_HEQU_ACTIVITY_END_TS) + 24*60*60)
		&& pdata->reward == 0)
	{
		pdata->reward = 1;
		for(int i = 0; i < 10;++i)
		{
			if(pdata->point[i].alliance_id !=0)
			{
				rewardPoints.push_back(pdata->point[i]);
			}
		}
	}
	return 0;
}


CDataWorldAttack::CDataWorldAttack(){
	m_init = false;
}
CDataWorldAttack::~CDataWorldAttack() {
	// TODO Auto-generated destructor stub
}

int  CDataWorldAttack::Init(const std::string &path, semdat sem)
{
	if(m_init)
	{
		return 0;
	}
	int semgroup = 0;
	int semserver = 0;
	Config::GetDomain(semserver);
	if(!semserver)
		Config::GetDB(semserver);
	if(!m_sh.CreateOrOpen(path.c_str(), sizeof(DataHequWorldAttack), SEM_ID(sem,semgroup,semserver)))
	{
		error_log("[init_alliance_point_data_fail][path=%s]", path.c_str());
		return R_ERROR;
	}
	CAutoLock lock(&m_sh, true);
	if(!m_sh.HasInit())
	{
		DataHequWorldAttack *pdata = (DataHequWorldAttack *)m_sh.GetAddress();
		if(pdata == NULL)
		{
			DB_ERROR_RETURN_MSG("init_alliance_point_fail");
		}
		memset(pdata, 0, sizeof(*pdata));
		m_sh.SetInitDone();
	}
	m_init = true;
	return 0;
}

int sortFuncWorldAttack(const HequWorldAttack& left,const HequWorldAttack& right){
	return left.attack_num > right.attack_num;
}

int CDataWorldAttack::UpdateWorldAttackRankList(const HequWorldAttack &attack_num)
{
	DataHequWorldAttack *pdata = (DataHequWorldAttack *)m_sh.GetAddress();
	if(pdata == NULL)
	{
		DB_ERROR_RETURN_MSG("init_worldattack_fail");
	}
	CAutoLock lock(&m_sh, true);

	//版本控制
	if(pdata->version != Config::GetIntValue(CONFIG_HEQU_ACTIVITY_VER))
	{
		memset(pdata, 0, sizeof(*pdata));
		pdata->version = Config::GetIntValue(CONFIG_HEQU_ACTIVITY_VER);
	}

	int flag = 0;
	if((Time::GetGlobalTime() >=Config::GetIntValue(CONFIG_HEQU_ACTIVITY_BEGIN_TS))
		&& (Time::GetGlobalTime() <= Config::GetIntValue(CONFIG_HEQU_ACTIVITY_END_TS)))
	{
		for(int i = 0;i < WORLD_ATTACK_RANK_SIZE; ++i)
		{
			if(pdata->attack[i].uid == attack_num.uid)
			{
				pdata->attack[i].attack_num += attack_num.attack_num;
				flag = i;
				break;
			}
			else if(pdata->attack[i].uid == 0 )
			{
				pdata->attack[i] = attack_num;
				flag = i;
				break;
			}

			if(i == WORLD_ATTACK_RANK_SIZE-1 && attack_num.attack_num > pdata->attack[i].attack_num)
			{
				pdata->attack[i] = attack_num;
				flag = i;
			}
		}

		HequWorldAttack Attack;
		if(flag >=10 && pdata->attack[flag].attack_num >  pdata->attack[9].attack_num)
		{
			Attack = pdata->attack[9];
			pdata->attack[9] = pdata->attack[flag];
			pdata->attack[flag] = Attack;
		}

		vector <HequWorldAttack> VecAttack;
		VecAttack.clear();
		for(int i = 0; i < 10;++i)
		{
			VecAttack.push_back(pdata->attack[i]);
		}

		sort(VecAttack.begin(),VecAttack.end(),sortFuncWorldAttack);

		for(int i = 0; i < 10;++i){
			pdata->attack[i] = VecAttack[i];
		}
	}
	return 0;
}

int CDataWorldAttack::UpdateNewWorldAttackRankList(multimap<unsigned, unsigned> herokill, map<unsigned, string> heroname)
{
	DataHequWorldAttack *pdata = (DataHequWorldAttack *)m_sh.GetAddress();
	if(pdata == NULL)
	{
		DB_ERROR_RETURN_MSG("init_worldattack_fail");
	}
	CAutoLock lock(&m_sh, true);

	//版本控制
	if(pdata->version != Config::GetIntValue(CONFIG_HEQU_ACTIVITY_VER))
	{
		memset(pdata, 0, sizeof(*pdata));
		pdata->version = Config::GetIntValue(CONFIG_HEQU_ACTIVITY_VER);
	}

	for(multimap<unsigned, unsigned>::reverse_iterator it=herokill.rbegin();it!=herokill.rend();++it)
	{
		if(!IsValidUid(it->second))
			continue;

		HequWorldAttack Attack;
		Attack.uid = it->second;
		Attack.attack_num = it->first;
		string name = heroname[it->second];
		memcpy(Attack.name, name.c_str(), sizeof(Attack.name) - 1);

		int flag = 0;
		for(int i = 0;i < WORLD_ATTACK_RANK_SIZE; ++i)
		{
			if(pdata->attack[i].uid == Attack.uid)
			{
				pdata->attack[i].attack_num += Attack.attack_num;
				flag = i;
				break;
			}
			else if(pdata->attack[i].uid == 0 )
			{
				pdata->attack[i] = Attack;
				flag = i;
				break;
			}

			if(i == WORLD_ATTACK_RANK_SIZE-1 && Attack.attack_num > pdata->attack[i].attack_num)
			{
				pdata->attack[i] = Attack;
				flag = i;
			}
		}

		HequWorldAttack Attack_temp;
		if(flag >=10 && pdata->attack[flag].attack_num >  pdata->attack[9].attack_num)
		{
			Attack_temp = pdata->attack[9];
			pdata->attack[9] = pdata->attack[flag];
			pdata->attack[flag] = Attack_temp;
		}

		if(flag < 10 || (flag >=10 && pdata->attack[flag].attack_num >  pdata->attack[9].attack_num))  //前十有变动才重新排序
		{
			vector <HequWorldAttack> VecAttack;
			VecAttack.clear();
			for(int i = 0; i < 10;++i)
			{
				VecAttack.push_back(pdata->attack[i]);
			}

			sort(VecAttack.begin(),VecAttack.end(),sortFuncWorldAttack);

			for(int i = 0; i < 10;++i){
				pdata->attack[i] = VecAttack[i];
			}
		}

	}
	return 0;
}

int CDataWorldAttack::GetWorldAttackRankList( vector <HequWorldAttack> &attack_num)
{
	DataHequWorldAttack *pdata = (DataHequWorldAttack *)m_sh.GetAddress();
	if(pdata == NULL)
	{
		DB_ERROR_RETURN_MSG("init_worldattack_fail");
	}
	CAutoLock lock(&m_sh, true);
	//版本控制
	if(pdata->version != Config::GetIntValue(CONFIG_HEQU_ACTIVITY_VER))
	{
		memset(pdata, 0, sizeof(*pdata));
		pdata->version = Config::GetIntValue(CONFIG_HEQU_ACTIVITY_VER);
	}

	for(int i = 0; i < 10;++i)
	{
		attack_num.push_back(pdata->attack[i]);
	}

	return 0;
}

int CDataWorldAttack::GetWorldAttackSelfData( unsigned uid,HequWorldAttack &attack_num)
{
	DataHequWorldAttack *pdata = (DataHequWorldAttack *)m_sh.GetAddress();
	if(pdata == NULL)
	{
		DB_ERROR_RETURN_MSG("init_worldattack_fail");
	}
	CAutoLock lock(&m_sh, true);

	for(int i = 0; i < WORLD_ATTACK_RANK_SIZE;++i)
	{
		if(uid == pdata->attack[i].uid)
		{
			attack_num = pdata->attack[i];
			break;
		}
	}

	return 0;
}

int CDataWorldAttack::RewardWorldAttackRankList( vector <HequWorldAttack> &reward_num)
{
	DataHequWorldAttack *pdata = (DataHequWorldAttack *)m_sh.GetAddress();
	if(pdata == NULL)
	{
		DB_ERROR_RETURN_MSG("init_worldattack_fail");
	}
	CAutoLock lock(&m_sh, true);

	if((Time::GetGlobalTime() > Config::GetIntValue(CONFIG_HEQU_ACTIVITY_END_TS))
		&& (Time::GetGlobalTime() <= Config::GetIntValue(CONFIG_HEQU_ACTIVITY_END_TS) + 24*60*60)
		&& pdata->reward == 0)
	{
		pdata->reward = 1;
		for(int i = 0; i < WORLD_ATTACK_RANK_SIZE;++i)
		{
			if(pdata->attack[i].uid !=0)
			{
				reward_num.push_back(pdata->attack[i]);
			}
		}
	}
	return 0;
}

