/*
 * LogicKingdom.h
 *
 *  Created on: 2014-6-6
 *      Author: Ralf
 */

#ifndef LOGICKINGDOM_H_
#define LOGICKINGDOM_H_

#include "LogicInc.h"

#define KINGDOM_HISTORY_ADD_JOB 0
#define KINGDOM_HISTORY_DEL_JOB 1
#define KINGDOM_HISTORY_TALK 2
#define KINGDOM_HISTORY_CLEAN 3

class CLogicKingdom
{
public:
	static CDataKingdom* GetCDataKingdom();

	int GetJobs(unsigned kingdom,Json::Value &result);
	int GetKingdom(unsigned kingdom,Json::Value &result);
	int ChangeJob(unsigned kingdom,KingdomJob kingdomjob,unsigned uid,string& name,unsigned touid,string& toname,unsigned aid, string& aname);
	int ChangeKing(unsigned kingdom,unsigned uid,string& name,unsigned aid, string& aname);
	int SetNotice(unsigned kingdom,unsigned uid, string& notice);
	int ForbidTalk(unsigned kingdom,unsigned uid, string name,unsigned forbiduid, string forbidname);
	int CleanProtect(unsigned kingdom,unsigned uid, string name,unsigned cleanuid,string cleanname);

	int CheckJob(unsigned kingdom,KingdomJob kingdomjob,unsigned uid);
	int CheckJobs(unsigned kingdom,vector<KingdomJob> kingdomjob,unsigned uid);

	int CleanKingdom();
	int RewardKingdom();

	int RepairKingdom();

	int RepairAllianceID();
};

#endif /* LOGICKINGDOM_H_ */
