/*
 * DataBarbarianKing.cpp
 *
 *  Created on: 2014-4-3
 *      Author: dawx123
 */
#include "DataBarbarianKing.h"

CDataBarbarianKing::CDataBarbarianKing()
{
	m_init = false;
}

CDataBarbarianKing::~CDataBarbarianKing()
{
}

int CDataBarbarianKing::Init(const std::string &path, semdat sem)
{
	if(m_init)
	{
		return 0;
	}
	if (path.empty())
	{
		error_log("[init_DataBarbarianKing_data_fail][path=%s]", path.c_str());
		return R_ERROR;
	}

	int semgroup = 0;
	int semserver = 0;
	Config::GetDomain(semserver);
	if(!semserver)
		Config::GetDB(semserver);

	for (int i = 0; i < BK_GROUP_MAX; i++)
	{
		string mapfile = path;
		if (path[path.length() - 1] != '/')
			mapfile.append("/");
		mapfile.append(CTrans::ITOS(i)).append(".BarbarianKing");
		if(!m_sh[i].CreateOrOpen(mapfile.c_str(), sizeof(DataBarbarianKing), SEM_ID(sem,semgroup,semserver)))
		{
			error_log("[init_BarbarianKing_data_fail][path=%s]", mapfile.c_str());
			return R_ERROR;
		}
		CAutoLock lock(&(m_sh[i]), true);
		if(!m_sh[i].HasInit())
		{
			DataBarbarianKing *pdata = (DataBarbarianKing *)m_sh[i].GetAddress();
			memset(pdata, 0, sizeof(*pdata));
			m_sh[i].SetInitDone();
		}
	}
	m_init = true;
	return 0;
}

int CDataBarbarianKing::GetBKList(unsigned group, vector<BKChallenger> &challenger)
{
	if(group >= BK_GROUP_MAX)
	{
		error_log("group error");
		return R_ERR_PARAM;
	}
	DataBarbarianKing *pdata = (DataBarbarianKing *)m_sh[group].GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(&(m_sh[group]), true);
	for(int i=0;i<pdata->num;++i)
		challenger.push_back(pdata->challenger[i]);
	return 0;
}

int CDataBarbarianKing::SetBKChallenger(unsigned group, BKChallenger &challenger)
{
	if(group >= BK_GROUP_MAX)
	{
		error_log("group error");
		return R_ERR_PARAM;
	}
	DataBarbarianKing *pdata = (DataBarbarianKing *)m_sh[group].GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(&(m_sh[group]), true);

	if (CTime::GetDayInterval(pdata->startTS, Time::GetGlobalTime()) != 0)//restart
	{
		memset(pdata, 0x00, sizeof(DataBarbarianKing));
		pdata->startTS = Time::GetGlobalTime();
	}

	if(pdata->minIndex == -1)// had rewarded,need restart
		return 0;

	if(challenger.point <= pdata->challenger[pdata->minIndex].point && pdata->num == BK_MAX)//比最小小且满
		return 0;
	bool flag = true;
	unsigned temp = -1, tempIndex = -1;
	for(int i=0;i<pdata->num;++i)
	{
		if(pdata->challenger[i].uid == challenger.uid)//之前有记录
		{
			flag = false;
			if(pdata->challenger[i].point < challenger.point)//只记录最高分
			{
				pdata->challenger[i].point = challenger.point;
				if(pdata->minIndex != i)//之前不是最小
					return 0;
			}
			else
				return 0;
		}
		if(i != pdata->minIndex && pdata->challenger[i].point < temp)//寻找之前的最小之外最小的
		{
			temp = pdata->challenger[i].point;
			tempIndex = i;
		}
	}
	if(flag)//需要新加入
	{
		if(pdata->num == 0)
		{
			pdata->challenger[0] = challenger;
			pdata->minIndex = 0;
			pdata->num = 1;
		}
		else if(pdata->num < BK_MAX)//新增记录
		{
			pdata->challenger[pdata->num] = challenger;
			if(pdata->challenger[pdata->num].point < pdata->challenger[pdata->minIndex].point)//小于之前最小的
				pdata->minIndex = pdata->num;
			++pdata->num;
		}
		else//替代之前的最小
		{
			pdata->challenger[pdata->minIndex] = challenger;
			if(temp < pdata->challenger[pdata->minIndex].point)//大于之前的最小之外最小的
				pdata->minIndex = tempIndex;
		}
	}
	else if(tempIndex < pdata->num)//之前的最小加分了
	{
		if(pdata->challenger[tempIndex].point < pdata->challenger[pdata->minIndex].point)//大于之前的最小之外最小的
			pdata->minIndex = tempIndex;
	}

	return 0;
}

int CDataBarbarianKing::SetReward(unsigned group)
{
	if(group >= BK_GROUP_MAX)
	{
		error_log("group error");
		return R_ERR_PARAM;
	}
	DataBarbarianKing *pdata = (DataBarbarianKing *)m_sh[group].GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(&(m_sh[group]), true);
	pdata->minIndex = -1;

	return 0;
}
