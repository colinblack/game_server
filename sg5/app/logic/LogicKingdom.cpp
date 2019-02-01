/*
 * LogicKingdom.cpp
 *
 *  Created on: 2014-6-6
 *      Author: Ralf
 */

#include "LogicKingdom.h"


CDataKingdom* CLogicKingdom::GetCDataKingdom()
{
	GET_MEM_DATA_SEM(CDataKingdom, CONFIG_ALLIANCE_BATTLE_DIR, sem_kingdom,false);
}

int CLogicKingdom::GetJobs(unsigned kingdom,Json::Value &result)
{
	CDataKingdom* dataKingdom = GetCDataKingdom();
	if (!dataKingdom)
	{
		DB_ERROR_RETURN_MSG("init_dataKingdom_fail");
	}

	Job jobs[JOB_NUM];
	int ret = dataKingdom->GetJobs(kingdom,jobs);
	if (ret != 0)
	{
		error_log("[GetJobs][ret=%d]",ret);
		DB_ERROR_RETURN_MSG("GetJobs_fail");
	}

	result["kingdom"] = kingdom;
	result["jobs"].resize(JOB_NUM);
	for(int i=0;i<JOB_NUM;++i)
	{
		result["jobs"][i]["job"] = i+1;
		result["jobs"][i]["uid"] = jobs[i].uid;
		result["jobs"][i]["name"] = jobs[i].name;
		result["jobs"][i]["aid"] = jobs[i].aid;
		result["jobs"][i]["aname"] = jobs[i].aname;
		result["jobs"][i]["n"] = jobs[i].n;
	}

	return 0;
}

int CLogicKingdom::GetKingdom(unsigned kingdom,Json::Value &result)
{
	CDataKingdom* dataKingdom = GetCDataKingdom();
	if (!dataKingdom)
	{
		DB_ERROR_RETURN_MSG("init_dataKingdom_fail");
	}

	DataKingdom data;
	int ret = dataKingdom->GetKingdom(kingdom,data);
	if (ret != 0)
	{
		error_log("[GetKingdom][ret=%d]",ret);
		DB_ERROR_RETURN_MSG("GetKingdom_fail");
	}

	int i;
	result["kingdom"] = kingdom;
	result["jobs"].resize(JOB_NUM);
	for(i=0;i<JOB_NUM;++i)
	{
		result["jobs"][i]["job"] = i+1;
		result["jobs"][i]["uid"] = data.jobs[i].uid;
		result["jobs"][i]["name"] = data.jobs[i].name;
		result["jobs"][i]["aid"] = data.jobs[i].aid;
		result["jobs"][i]["aname"] = data.jobs[i].aname;
		result["jobs"][i]["n"] = data.jobs[i].n;
	}
	result["notice"] = data.notice;
	result["history"].resize(JOB_EVENT_NUM);
	for(i=0;i<JOB_EVENT_NUM;++i)
	{
		result["history"][i]["uid1"] = data.history[i].uid1;
		result["history"][i]["job1"] = data.history[i].job1;
		result["history"][i]["name1"] = data.history[i].name1;
		result["history"][i]["uid2"] = data.history[i].uid2;
		result["history"][i]["job2"] = data.history[i].job2;
		result["history"][i]["name2"] = data.history[i].name2;
		result["history"][i]["type"] = data.history[i].type;
		result["history"][i]["ts"] = data.history[i].ts;
	}
	result["kings"].resize(JOB_EVENT_NUM);
	for(i=0;i<JOB_EVENT_NUM;++i)
	{
		result["kings"][i]["uid"] = data.kings[i].uid;
		result["kings"][i]["name"] = data.kings[i].name;
		result["kings"][i]["aid"] = data.kings[i].aid;
		result["kings"][i]["aname"] = data.kings[i].aname;
		result["kings"][i]["ts"] = data.kings[i].ts;
	}

	return 0;
}

int CLogicKingdom::ChangeJob(unsigned kingdom,KingdomJob kingdomjob,unsigned uid,string& name,unsigned touid,string& toname,unsigned aid, string& aname)
{
	CDataKingdom* dataKingdom = GetCDataKingdom();
	if (!dataKingdom)
	{
		DB_ERROR_RETURN_MSG("init_dataKingdom_fail");
	}

	CDataUser db;
	Job job;
	Event history;
	KingdomJob myjob;

	int ret = dataKingdom->CheckSetJob(kingdom,uid,kingdomjob,job,myjob);
	if(ret == R_ERR_DATA_LIMIT)
	{
		if(touid)
			return R_ERR_DATA_LIMIT;
	}
	else if (ret != 0)
	{
		if(ret == R_ERR_LOGIC)
		{
			db.SetStatus(uid,Job_None);
		}

		error_log("[SetJob][ret=%d]",ret);
		DB_ERROR_RETURN_MSG("SetJob_fail");
	}
	unsigned olduid = job.uid;
	string oldname = job.name;

	job.uid = touid;
	strcpy(job.name,toname.c_str());
	job.aid = aid;
	strcpy(job.aname,aname.c_str());

	history.uid1 = uid;
	history.job1 = myjob;
	strcpy(history.name1,name.c_str());
	history.uid2 = touid?touid:olduid;
	history.job2 = kingdomjob;
	touid?strcpy(history.name2,toname.c_str()):strcpy(history.name2,oldname.c_str());
	history.type = touid?KINGDOM_HISTORY_ADD_JOB:KINGDOM_HISTORY_DEL_JOB;
	history.ts = Time::GetGlobalTime();

	if(IsValidUid(olduid))
	{
		ret = db.SetStatus(olduid,Job_None);
		if(ret)
		{
			error_log("[SetJob][ret=%d]",ret);
			DB_ERROR_RETURN_MSG("SetJob_fail");
		}
	}

	ret = dataKingdom->SetJob(kingdom,kingdomjob,job,history);
	if (ret != 0)
	{
		error_log("[SetJob][ret=%d]",ret);
		DB_ERROR_RETURN_MSG("SetJob_fail");
	}

	if(IsValidUid(touid))
	{
		ret = db.SetStatus(touid,kingdomjob);
		if(ret)
		{
			error_log("[SetJob][ret=%d]",ret);
			DB_ERROR_RETURN_MSG("SetJob_fail");
		}
	}

	Json::Value updates;
	updates["s"] = "JOBCHANGED";
	updates["uid1"] = uid;
	updates["job1"] = myjob;
	updates["name1"] = name;
	updates["uid2"] = touid?touid:olduid;
	updates["job2"] = kingdomjob;
	updates["name2"] = touid?toname:oldname;
	updates["type"] = touid?KINGDOM_HISTORY_ADD_JOB:KINGDOM_HISTORY_DEL_JOB;
	updates["ts"] = Time::GetGlobalTime();

	CLogicUpdates logicUpdates;
	if(IsValidUid(olduid))
		logicUpdates.AddUpdates(olduid, updates);
	if(IsValidUid(touid))
		logicUpdates.AddUpdates(touid, updates);

	return 0;
}

int CLogicKingdom::ChangeKing(unsigned kingdom,unsigned uid,string& name,unsigned aid, string& aname)
{
	CDataKingdom* dataKingdom = GetCDataKingdom();
	if (!dataKingdom)
	{
		DB_ERROR_RETURN_MSG("init_dataKingdom_fail");
	}

	CDataUser db;
	Job job;
	King king;

	int ret = dataKingdom->GetJob(kingdom,Job_King,job);
	if (ret != 0)
	{
		error_log("[GetJob][ret=%d]",ret);
		DB_ERROR_RETURN_MSG("GetJob_fail");
	}
	unsigned olduid = job.uid;

	job.uid = uid;
	strcpy(job.name,name.c_str());
	job.aid = aid;
	strcpy(job.aname,aname.c_str());

	king.uid = uid;
	strcpy(king.name,name.c_str());
	king.aid = aid;
	strcpy(king.aname,aname.c_str());
	king.ts = Time::GetGlobalTime();

	if(IsValidUid(olduid))
	{
		ret = db.SetStatus(olduid,Job_None);
		if(ret)
		{
			error_log("[SetJob][ret=%d]",ret);
			DB_ERROR_RETURN_MSG("SetJob_fail");
		}
	}

	ret = dataKingdom->SetKing(kingdom,job,king);
	if (ret != 0)
	{
		error_log("[SetJob][ret=%d]",ret);
		DB_ERROR_RETURN_MSG("SetJob_fail");
	}

	if(IsValidUid(uid))
	{
		ret = db.SetStatus(uid,Job_King);
		if(ret)
		{
			error_log("[SetJob][ret=%d]",ret);
			DB_ERROR_RETURN_MSG("SetJob_fail");
		}
	}

	Json::Value updates;
	updates["s"] = "JOBCHANGED";
	updates["uid1"] = 0;
	updates["job1"] = Job_None;
	updates["name1"] = "";
	updates["uid2"] = uid;
	updates["job2"] = Job_King;
	updates["name2"] = name;
	updates["type"] = KINGDOM_HISTORY_ADD_JOB;
	updates["ts"] = Time::GetGlobalTime();

	CLogicUpdates logicUpdates;
	if(IsValidUid(olduid))
		logicUpdates.AddUpdates(olduid, updates);
	if(IsValidUid(uid))
		logicUpdates.AddUpdates(uid, updates);

	return 0;
}

int CLogicKingdom::SetNotice(unsigned kingdom,unsigned uid, string& notice)
{
	CDataKingdom* dataKingdom = GetCDataKingdom();
	if (!dataKingdom)
	{
		DB_ERROR_RETURN_MSG("init_dataKingdom_fail");
	}

	KingdomJob myjob;
	int ret = dataKingdom->CheckSetNotice(kingdom,uid,myjob);
	if (ret != 0)
	{
		if(ret == R_ERR_LOGIC)
		{
			CDataUser db;
			db.SetStatus(uid,Job_None);
		}

		error_log("[SetJob][ret=%d]",ret);
		DB_ERROR_RETURN_MSG("SetJob_fail");
	}

	ret = dataKingdom->SetNotice(kingdom,uid,notice);
	if (ret != 0)
	{
		error_log("[SetJob][ret=%d]",ret);
		DB_ERROR_RETURN_MSG("SetJob_fail");
	}

	return 0;
}

int CLogicKingdom::ForbidTalk(unsigned kingdom,unsigned uid, string name,unsigned forbiduid, string forbidname)
{
	CDataKingdom* dataKingdom = GetCDataKingdom();
	if (!dataKingdom)
	{
		DB_ERROR_RETURN_MSG("init_dataKingdom_fail");
	}

	KingdomJob myjob;
	int ret = dataKingdom->CheckForbid(kingdom, uid,myjob);
	if(ret)
	{
		if(ret == R_ERR_LOGIC)
		{
			CDataUser db;
			db.SetStatus(uid,Job_None);
		}
		error_log("[ForbidTalk][ret=%d]",ret);
		DB_ERROR_RETURN_MSG("ForbidTalk_fail");
	}

	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	ret = logicUser.GetUser(uid,dataUser);
	if(ret)
		return ret;
	Json::Value stats;
	Json::Reader reader;
	if(!reader.parse(dataUser.user_stat,stats))
	{
		error_log("[parse][uid=%u]",uid);
		DB_ERROR_RETURN_MSG("ForbidTalk_fail");
	}
	if(!stats.isMember("tequan"))
	{
		stats["tequan"].resize(5);
		stats["tequan"][0u] = 0;
		stats["tequan"][1u] = 0;
		stats["tequan"][2u] = 0;
		stats["tequan"][3u] = 0;
		stats["tequan"][4u] = 0;
	}
	int used = stats["tequan"][1u].asInt() + 1;
	stats["tequan"][1u] = used;
	dataUser.user_stat = Json::ToString(stats);
	int setRet = logicUser.SetUser(uid, dataUser);
	if(setRet)
		return setRet;

	CLogicAdmin logicAdmin;
	logicAdmin.AddForbidUser(forbiduid,Time::GetGlobalTime()+3600);

	Event history;
	history.uid1 = uid;
	history.job1 = myjob;
	strcpy(history.name1,name.c_str());
	history.uid2 = forbiduid;
	history.job2 = Job_None;
	strcpy(history.name2,forbidname.c_str());
	history.type = KINGDOM_HISTORY_TALK;
	history.ts = Time::GetGlobalTime();
	dataKingdom->SetHistory(kingdom, history);

	Json::Value temp;
	temp["s"] = "Kingdom_Forbid_Talk";
	temp["uid"] = uid;
	temp["job"] = myjob;
	temp["name"] = name;
	temp["ts"] = Time::GetGlobalTime();
	DataEmail email;
	CLogicEmail logicEmail;
	vector<uint64_t> toUidList;
	toUidList.push_back(forbiduid);
	email.attach_flag = 0;
	email.attachments = "";
	email.uid = ADMIN_UID;
	email.post_ts = Time::GetGlobalTime();
	email.title = "Kingdom_Forbid_Talk";
	email.text = Json::ToString(temp);
	logicEmail.AddEmail(email,toUidList,true);

	info_log("uid=%u,forbiduid=%u,used=%d",uid,forbiduid,used);

	return 0;
}

int CLogicKingdom::CleanProtect(unsigned kingdom,unsigned uid, string name,unsigned cleanuid,string cleanname)
{
	CDataKingdom* dataKingdom = GetCDataKingdom();
	if (!dataKingdom)
	{
		DB_ERROR_RETURN_MSG("init_dataKingdom_fail");
	}

	KingdomJob myjob;
	int ret = dataKingdom->CheckCleanProtect(kingdom, uid,myjob);
	if(ret)
	{
		if(ret == R_ERR_LOGIC)
		{
			CDataUser db;
			db.SetStatus(uid,Job_None);
		}
		error_log("[CleanProtect][ret=%d]",ret);
		DB_ERROR_RETURN_MSG("CleanProtect_fail");
	}

	int used;
	{
		CLogicUser logicUser;
		DataUser dataUser;
		AUTO_LOCK_USER(uid)
		ret = logicUser.GetUser(uid,dataUser);
		if(ret)
			return ret;
		Json::Value stats;
		Json::Reader reader;
		if(!reader.parse(dataUser.user_stat,stats))
		{
			error_log("[parse][uid=%u]",uid);
			DB_ERROR_RETURN_MSG("CleanProtect_fail");
		}
		if(!stats.isMember("tequan"))
		{
			stats["tequan"].resize(5);
			stats["tequan"][0u] = 0;
			stats["tequan"][1u] = 0;
			stats["tequan"][2u] = 0;
			stats["tequan"][3u] = 0;
			stats["tequan"][4u] = 0;
		}
		used = stats["tequan"][0u].asInt() + 1;
		stats["tequan"][0u] = used;
		dataUser.user_stat = Json::ToString(stats);
		int setRet = logicUser.SetUser(uid, dataUser);
		if(setRet)
			return setRet;
	}

	{
		CLogicAdmin logicAdmin;
		AUTO_LOCK_USER(cleanuid)
		logicAdmin.ChangeProtectTs(cleanuid, 0);
	}

	Event history;
	history.uid1 = uid;
	history.job1 = myjob;
	strcpy(history.name1,name.c_str());
	history.uid2 = cleanuid;
	history.job2 = Job_None;
	strcpy(history.name2,cleanname.c_str());
	history.type = KINGDOM_HISTORY_CLEAN;
	history.ts = Time::GetGlobalTime();
	dataKingdom->SetHistory(kingdom, history);

	info_log("uid=%u,cleanuid=%u,used=%d",uid,cleanuid,used);

	return 0;
}

int CLogicKingdom::CheckJob(unsigned kingdom,KingdomJob kingdomjob,unsigned uid)
{
	CDataKingdom* dataKingdom = GetCDataKingdom();
	if (!dataKingdom)
	{
		DB_ERROR_RETURN_MSG("init_dataKingdom_fail");
	}

	Job job;
	int ret = dataKingdom->GetJob(kingdom,kingdomjob,job);
	if (ret != 0)
	{
		error_log("[CheckJob][ret=%d]",ret);
		DB_ERROR_RETURN_MSG("GetJob_fail");
	}

	if(job.uid != uid)
		return R_ERR_LOGIC;

	return 0;
}

int CLogicKingdom::CheckJobs(unsigned kingdom,vector<KingdomJob> kingdomjob,unsigned uid)
{
	CDataKingdom* dataKingdom = GetCDataKingdom();
	if (!dataKingdom)
	{
		DB_ERROR_RETURN_MSG("init_dataKingdom_fail");
	}

	Job jobs[JOB_NUM];
	int ret = dataKingdom->GetJobs(kingdom,jobs);
	if (ret != 0)
	{
		error_log("[CheckJobs][ret=%d]",ret);
		DB_ERROR_RETURN_MSG("GetJob_fail");
	}

	for(int i=0;i<kingdomjob.size();++i)
	{
		if(jobs[kingdomjob[i]-1].uid == uid)
			return 0;
	}

	return R_ERR_LOGIC;
}

int CLogicKingdom::CleanKingdom()
{
	CDataKingdom* dataKingdom = GetCDataKingdom();
	if (!dataKingdom)
	{
		DB_ERROR_RETURN_MSG("init_dataKingdom_fail");
	}

	for(unsigned k=1;k<=3;++k)
	{
		Job jobs[JOB_NUM];
		int ret = dataKingdom->GetJobs(k,jobs);
		if (ret != 0)
		{
			error_log("[CleanKingdom][ret=%d]",ret);
			continue;
		}

		CDataUser db;
		for(unsigned i=0;i<JOB_NUM;++i)
		{
			unsigned uid = jobs[i].uid;
			if(IsValidUid(uid))
			{
				ret = db.SetStatus(uid,Job_None);
				if(ret)
					error_log("[CleanKingdom][uid=%d]",uid);
				else
					info_log("[CleanKingdom][uid=%d]",uid);
			}
		}

		dataKingdom->CleanKingdom(k);
	}

	return 0;
}

int CLogicKingdom::RewardKingdom()
{
	CDataKingdom* dataKingdom = GetCDataKingdom();
	if (!dataKingdom)
	{
		DB_ERROR_RETURN_MSG("init_dataKingdom_fail");
	}

	CLogicAdmin logicAdmin;

	for(unsigned k=1;k<=3;++k)
	{
		Job jobs[JOB_NUM];
		int ret = dataKingdom->GetJobs(k,jobs);
		if (ret != 0)
		{
			error_log("[RewardKingdom][ret=%d]",ret);
			continue;
		}

		for(unsigned i=0;i<JOB_NUM;++i)
		{
			unsigned uid = jobs[i].uid;
			unsigned p;
			unsigned b;
			if(i+1 == Job_King)
				p = 5000;
			else if(i+1 >= Job_General && i+1 <= Job_Minister)
				p = 3000;
			else if(i+1 >= Job_Sec_General_1 && i+1 <= Job_Sec_Minister_3)
				p = 1000;
			else
				continue;

			if(IsValidUid(uid))
			{
				ret = logicAdmin.ChangeProsper(uid, p, b);
				if(ret)
					error_log("[ChangeProsper][uid=%u,k=%u,p=%u]",uid,k,p);
				else
					RESOURCE_LOG("[RewardKingdom][uid=%u,chgProsper=%d,prosper=%u]", uid,p,b);
			}
		}

		ret = dataKingdom->ResetJobN(k);
		if(ret)
			error_log("[ResetJobN][kingdom=%d]",k);
	}

	return 0;
}

int CLogicKingdom::RepairKingdom()
{
	CDataKingdom* dataKingdom = GetCDataKingdom();
	if (!dataKingdom)
	{
		DB_ERROR_RETURN_MSG("init_dataKingdom_fail");
	}

	for(unsigned k=1;k<=3;++k)
	{
		Job jobs[JOB_NUM];
		int ret = dataKingdom->GetJobs(k,jobs);
		if (ret != 0)
		{
			error_log("[RepairKingdom][ret=%d]",ret);
			continue;
		}

		CDataUser db;
		for(unsigned i=0;i<JOB_NUM;++i)
		{
			unsigned uid = jobs[i].uid;
			if(IsValidUid(uid))
			{
				ret = db.SetStatus(uid,i+1);
				if(ret)
					error_log("[RepairKingdom][uid=%d]",uid);
				else
					info_log("[RepairKingdom][uid=%d]",uid);
			}
		}
	}

	return 0;
}

int CLogicKingdom::RepairAllianceID()
{
	CDataKingdom* dataKingdom = GetCDataKingdom();
	if (!dataKingdom)
	{
		DB_ERROR_RETURN_MSG("init_dataKingdom_fail");
	}

	return dataKingdom->RepairAllianceID();
}
