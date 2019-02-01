/*
 * DataKingdom.h
 *
 *  Created on: 2014-6-6
 *      Author: Ralf
 */

#ifndef DATAKINGDOM_H_
#define DATAKINGDOM_H_

#include "Kernel.h"

#define JOB_NUM 9
#define JOB_EVENT_NUM 20

enum KingdomJob
{
	Job_None 			= 0,

	Job_King 			= 1,
	Job_General			= 2,
	Job_Minister		= 3,
	Job_Sec_General_1 	= 4,
	Job_Sec_General_2 	= 5,
	Job_Sec_General_3	= 6,
	Job_Sec_Minister_1	= 7,
	Job_Sec_Minister_2 	= 8,
	Job_Sec_Minister_3 	= 9,

	Job_Max,
};

struct Job
{
	unsigned uid;
	char name[32];
	unsigned aid;
	char aname[32];
	unsigned n;

	Job& operator=(const Job &t)
	{
		uid = t.uid;
		aid = t.aid;
		n = t.n;
		memcpy(name, t.name,31);
		memcpy(aname, t.aname,31);
		return *this;
	}
};

struct Event
{
	unsigned uid1;
	unsigned job1;
	char name1[32];
	unsigned uid2;
	unsigned job2;
	char name2[32];
	unsigned type;
	unsigned ts;

	Event& operator=(const Event &t)
	{
		uid1 = t.uid1;
		job1 = t.job1;
		uid2 = t.uid2;
		job2 = t.job2;
		type = t.type;
		ts = t.ts;
		memcpy(name1, t.name1,31);
		memcpy(name2, t.name2,31);
		return *this;
	}
};

struct King
{
	unsigned uid;
	char name[32];
	unsigned aid;
	char aname[32];
	unsigned ts;

	King& operator=(const King &t)
	{
		uid = t.uid;
		aid = t.aid;
		ts = t.ts;
		memcpy(name, t.name,31);
		memcpy(aname, t.aname,31);
		return *this;
	}
};

struct DataKingdom
{
	Job jobs[JOB_NUM];
	char notice[100];
	Event history[JOB_EVENT_NUM];
	King kings[JOB_EVENT_NUM];

	DataKingdom& operator=(const DataKingdom &t)
	{
		for(int i=0;i<JOB_NUM;++i)
			jobs[i] = t.jobs[i];
		for(int j=0;j<JOB_EVENT_NUM;++j)
		{
			history[j] = t.history[j];
			kings[j] = t.kings[j];
		}
		memcpy(notice, t.notice,99);
		return *this;
	}
};

class CDataKingdom
{
public:
	CDataKingdom();
	int Init(const string &path, semdat sem=sem_kingdom);

	int GetJob(unsigned kingdom, KingdomJob kingdomjob, Job &job);
	int GetJobs(unsigned kingdom,Job job[JOB_NUM]);
	int GetKingdom(unsigned kingdom,DataKingdom& datakingdom);

	int SetJob(unsigned kingdom, KingdomJob kingdomjob, Job &job, Event& histroy);
	int SetKing(unsigned kingdom, Job &job, King& king);
	int SetNotice(unsigned kingdom,unsigned uid, string& notice);

	int SetJob(unsigned kingdom, KingdomJob kingdomjob, Job &job);
	int SetHistory(unsigned kingdom, Event& histroy);
	int SetKings(unsigned kingdom, King& king);

	int CheckSetJob(unsigned kingdom,unsigned uid, KingdomJob kingdomjob, Job& job, KingdomJob& myjob);
	int CheckSetNotice(unsigned kingdom,unsigned uid, KingdomJob& myjob);
	int CheckForbid(unsigned kingdom,unsigned uid, KingdomJob& myjob);
	int CheckCleanProtect(unsigned kingdom,unsigned uid, KingdomJob& myjob);

	int CleanKingdom(unsigned kingdom);
	int ResetJobN(unsigned kingdom);

	int RepairAllianceID();
protected:
	int check_kingdom(unsigned kingdom);
	int check_job(KingdomJob kingdomjob);
	CShareMemory m_sh[3];
	bool m_init;
};
#endif /* DATAKINGDOM_H_ */
