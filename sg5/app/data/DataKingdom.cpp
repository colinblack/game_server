/*
 * DataKingdom.cpp
 *
 *  Created on: 2014-6-6
 *      Author: Ralf
 */

#include "DataKingdom.h"

CDataKingdom::CDataKingdom()
{
	m_init = false;
}

int CDataKingdom::Init(const string &path, semdat sem)
{
	if(m_init)
	{
		return 0;
	}
	if (path.empty())
	{
		error_log("[init_kingdom_data_fail][path=%s]", path.c_str());
		return R_ERROR;
	}

	int semgroup = 0;
	int semserver = 0;
	Config::GetDomain(semserver);
	if(!semserver)
		Config::GetDB(semserver);

	for (int k = 0; k < 3; k++)
	{
		string mapfile = path;
		if (path[path.length() - 1] != '/')
			mapfile.append("/");
		mapfile.append(CTrans::ITOS(k)).append(".kingdom");
		if(!m_sh[k].CreateOrOpen(mapfile.c_str(), sizeof(DataKingdom), SEM_ID(sem,semgroup,semserver)))
		{
			error_log("[init_kingdom_data_fail][path=%s]", mapfile.c_str());
			return R_ERROR;
		}
		CAutoLock lock(&(m_sh[k]), true);
		if(!m_sh[k].HasInit())
		{
			DataKingdom *pdata = (DataKingdom *)m_sh[k].GetAddress();
			memset(pdata, 0, sizeof(*pdata));
			m_sh[k].SetInitDone();
		}
	}
	m_init = true;
	return 0;
}

int CDataKingdom::GetJob(unsigned kingdom, KingdomJob kingdomjob, Job &job)
{
	if(check_job(kingdomjob))
		return R_ERR_PARAM;
	if(check_kingdom(kingdom))
		return R_ERR_PARAM;
	DataKingdom *pdata = (DataKingdom *)m_sh[kingdom-1].GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(&(m_sh[kingdom-1]), true);

	job = pdata->jobs[kingdomjob-1];

	return 0;
}

int CDataKingdom::GetJobs(unsigned kingdom,Job job[JOB_NUM])
{
	if(check_kingdom(kingdom))
		return R_ERR_PARAM;
	DataKingdom *pdata = (DataKingdom *)m_sh[kingdom-1].GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(&(m_sh[kingdom-1]), true);

	for(unsigned i=0;i<JOB_NUM;++i)
		job[i] = pdata->jobs[i];

	return 0;
}

int CDataKingdom::GetKingdom(unsigned kingdom,DataKingdom& datakingdom)
{
	if(check_kingdom(kingdom))
		return R_ERR_PARAM;
	DataKingdom *pdata = (DataKingdom *)m_sh[kingdom-1].GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(&(m_sh[kingdom-1]), true);

	datakingdom = *pdata;

	return 0;
}

int CDataKingdom::SetJob(unsigned kingdom, KingdomJob kingdomjob, Job &job)
{
	if(check_job(kingdomjob))
		return R_ERR_PARAM;
	if(check_kingdom(kingdom))
		return R_ERR_PARAM;
	DataKingdom *pdata = (DataKingdom *)m_sh[kingdom-1].GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(&(m_sh[kingdom-1]), true);

	pdata->jobs[kingdomjob-1] = job;

	return 0;
}

int CDataKingdom::SetJob(unsigned kingdom, KingdomJob kingdomjob, Job &job, Event& histroy)
{
	if(kingdomjob == Job_King)
		return R_ERR_PARAM;

	if(check_job(kingdomjob))
		return R_ERR_PARAM;
	if(check_kingdom(kingdom))
		return R_ERR_PARAM;
	DataKingdom *pdata = (DataKingdom *)m_sh[kingdom-1].GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(&(m_sh[kingdom-1]), true);

	unsigned n = pdata->jobs[kingdomjob-1].n;
	pdata->jobs[kingdomjob-1] = job;
	if(pdata->jobs[kingdomjob-1].uid)
		pdata->jobs[kingdomjob-1].n = 1;
	else
		pdata->jobs[kingdomjob-1].n = n;

	for(int i=JOB_EVENT_NUM-1;i>0;--i)
		pdata->history[i] = pdata->history[i-1];
	pdata->history[0] = histroy;

	return 0;
}

int CDataKingdom::SetKing(unsigned kingdom, Job &job, King& king)
{
	if(check_kingdom(kingdom))
		return R_ERR_PARAM;
	DataKingdom *pdata = (DataKingdom *)m_sh[kingdom-1].GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(&(m_sh[kingdom-1]), true);

	pdata->jobs[Job_King-1] = job;
	pdata->jobs[Job_King-1].n = 0;

	for(int j=Job_General-1;j<JOB_NUM;++j)
	{
		if(pdata->jobs[j].uid == job.uid)
			memset(&pdata->jobs[j],0,sizeof(Job));
	}

	for(int i=JOB_EVENT_NUM-1;i>0;--i)
		pdata->kings[i] = pdata->kings[i-1];
	pdata->kings[0] = king;

	return 0;
}

int CDataKingdom::SetNotice(unsigned kingdom,unsigned uid, string& notice)
{
	if(check_kingdom(kingdom))
		return R_ERR_PARAM;
	DataKingdom *pdata = (DataKingdom *)m_sh[kingdom-1].GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(&(m_sh[kingdom-1]), true);

	memcpy(pdata->notice, notice.c_str(),99);

	return 0;
}

int CDataKingdom::SetHistory(unsigned kingdom, Event& histroy)
{
	if(check_kingdom(kingdom))
		return R_ERR_PARAM;
	DataKingdom *pdata = (DataKingdom *)m_sh[kingdom-1].GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(&(m_sh[kingdom-1]), true);

	for(int i=JOB_EVENT_NUM-1;i>0;--i)
		pdata->history[i] = pdata->history[i-1];
	pdata->history[0] = histroy;

	return 0;
}

int CDataKingdom::SetKings(unsigned kingdom, King& king)
{
	if(check_kingdom(kingdom))
		return R_ERR_PARAM;
	DataKingdom *pdata = (DataKingdom *)m_sh[kingdom-1].GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(&(m_sh[kingdom-1]), true);

	for(int i=JOB_EVENT_NUM-1;i>0;--i)
			pdata->kings[i] = pdata->kings[i-1];
	pdata->kings[0] = king;

	return 0;
}

int CDataKingdom::CheckSetJob(unsigned kingdom,unsigned uid, KingdomJob kingdomjob, Job& job, KingdomJob& myjob)
{
	if(kingdomjob == Job_King)
		return R_ERR_PARAM;
	if(check_job(kingdomjob))
		return R_ERR_PARAM;
	if(check_kingdom(kingdom))
		return R_ERR_PARAM;
	DataKingdom *pdata = (DataKingdom *)m_sh[kingdom-1].GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(&(m_sh[kingdom-1]), true);

	for(unsigned m=0;m<JOB_NUM;++m)
	{
		if(uid == pdata->jobs[m].uid)
		{
			myjob = (KingdomJob)(m+1);
			break;
		}
	}

	job = pdata->jobs[kingdomjob-1];

	if(((kingdomjob >= Job_General && kingdomjob <= Job_Minister) && (uid == pdata->jobs[Job_King-1].uid))
	|| ((kingdomjob >= Job_Sec_General_1 && kingdomjob <= Job_Sec_General_3) && (uid == pdata->jobs[Job_King-1].uid || uid == pdata->jobs[Job_General-1].uid))
	|| ((kingdomjob >= Job_Sec_Minister_1 && kingdomjob <= Job_Sec_Minister_3) && (uid == pdata->jobs[Job_King-1].uid || uid == pdata->jobs[Job_Minister-1].uid))
	|| uid == pdata->jobs[kingdomjob-1].uid)
	{
		if(pdata->jobs[kingdomjob-1].n)
			return R_ERR_DATA_LIMIT;

		return 0;
	}

	return R_ERR_LOGIC;
}

int CDataKingdom::CheckSetNotice(unsigned kingdom,unsigned uid, KingdomJob& myjob)
{
	if(check_kingdom(kingdom))
		return R_ERR_PARAM;
	DataKingdom *pdata = (DataKingdom *)m_sh[kingdom-1].GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(&(m_sh[kingdom-1]), true);

	for(unsigned m=0;m<JOB_NUM;++m)
	{
		if(uid == pdata->jobs[m].uid)
		{
			myjob = (KingdomJob)(m+1);
			break;
		}
	}

	if(pdata->jobs[Job_King-1].uid == uid
	|| pdata->jobs[Job_General-1].uid == uid
	|| pdata->jobs[Job_Minister-1].uid == uid)
		return 0;

	return R_ERR_LOGIC;
}

int CDataKingdom::CheckForbid(unsigned kingdom,unsigned uid, KingdomJob& myjob)
{
	if(check_kingdom(kingdom))
		return R_ERR_PARAM;
	DataKingdom *pdata = (DataKingdom *)m_sh[kingdom-1].GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(&(m_sh[kingdom-1]), true);

	for(unsigned m=0;m<JOB_NUM;++m)
	{
		if(uid == pdata->jobs[m].uid)
		{
			myjob = (KingdomJob)(m+1);
			break;
		}
	}

	if(pdata->jobs[Job_King-1].uid == uid
	|| pdata->jobs[Job_Minister-1].uid == uid
	|| pdata->jobs[Job_Sec_Minister_1-1].uid == uid
	|| pdata->jobs[Job_Sec_Minister_2-1].uid == uid
	|| pdata->jobs[Job_Sec_Minister_3-1].uid == uid)
		return 0;

	return R_ERR_LOGIC;
}

int CDataKingdom::CheckCleanProtect(unsigned kingdom,unsigned uid, KingdomJob& myjob)
{
	if(check_kingdom(kingdom))
		return R_ERR_PARAM;
	DataKingdom *pdata = (DataKingdom *)m_sh[kingdom-1].GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(&(m_sh[kingdom-1]), true);

	for(unsigned m=0;m<JOB_NUM;++m)
	{
		if(uid == pdata->jobs[m].uid)
		{
			myjob = (KingdomJob)(m+1);
			break;
		}
	}

	if(pdata->jobs[Job_King-1].uid == uid
	|| pdata->jobs[Job_General-1].uid == uid
	|| pdata->jobs[Job_Sec_General_1-1].uid == uid
	|| pdata->jobs[Job_Sec_General_2-1].uid == uid
	|| pdata->jobs[Job_Sec_General_3-1].uid == uid)
		return 0;

	return R_ERR_LOGIC;
}

int CDataKingdom::check_kingdom(unsigned kingdom)
{
	if(kingdom > 3 || kingdom < 1)
		return 1;
	return 0;
}
int CDataKingdom::check_job(KingdomJob kingdomjob)
{
	if(kingdomjob > Job_None && kingdomjob < Job_Max)
		return 0;
	return 1;
}

int CDataKingdom::CleanKingdom(unsigned kingdom)
{
	if(check_kingdom(kingdom))
		return R_ERR_PARAM;
	DataKingdom *pdata = (DataKingdom *)m_sh[kingdom-1].GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(&(m_sh[kingdom-1]), true);

	memset(pdata, 0, sizeof(*pdata));

	return 0;
}

int CDataKingdom::ResetJobN(unsigned kingdom)
{
	if(check_kingdom(kingdom))
		return R_ERR_PARAM;
	DataKingdom *pdata = (DataKingdom *)m_sh[kingdom-1].GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(&(m_sh[kingdom-1]), true);

	for(unsigned i=0;i<JOB_NUM;++i)
		pdata->jobs[i].n = 0;

	return 0;
}

int CDataKingdom::RepairAllianceID()
{
	for(unsigned kingdom=1;kingdom<3;++kingdom)
	{
		DataKingdom *pdata = (DataKingdom *)m_sh[kingdom-1].GetAddress();
		if(pdata == NULL)
		{
			return R_ERR_DB;
		}
		CAutoLock lock(&(m_sh[kingdom-1]), true);

		for(unsigned i=0;i<JOB_NUM;++i)
		{
			if(pdata->jobs[i].aid > 4000000000)
				pdata->jobs[i].aid -= 2000000000;
		}
		for(unsigned j=0;j<JOB_EVENT_NUM;++j)
		{
			if(pdata->kings[j].aid > 4000000000)
				pdata->kings[j].aid -= 2000000000;
		}
	}
	return 0;
}
