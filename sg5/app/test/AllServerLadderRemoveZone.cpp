/*
 * AllServerLadderRemoveZone.cpp
 *
 *  Created on: 2015-1-4
 *      Author: Ralf
 */



#include "LogicInc.h"

int main(int argc, char *argv[])
{
	if (!Kernel::Init(APP_CONFIG_PATH))
	{
		cout << "init kernel fail" << endl;
		return 1;
	}

	Config::SetDomain(0);

	if (argc != 2) {
		cout << "usage: " << argv[0] << " serverid " << endl;
		return 1;
	}
	unsigned serverid = atoi(argv[1]);
	if (!serverid) {
		cout << "serverid wrong!" << endl;
		return 1;
	}

	int semgroup = 0;
	int semserver = 0;
	Config::GetDB(semserver);

	string dataPath = MainConfig::GetAllServerPath(CONFIG_ALL_SERVER_LADDER_PATH);
	const semdat sem[3] = {sem_ladderallserver_1, sem_ladderallserver_2, sem_ladderallserver_3};

	for (int level=1; level<=3; level++)
	{
		string filePath;
		String::Format(filePath, "%s.%d", dataPath.c_str(), level);
		CShareMemory shm;
		if (!shm.CreateOrOpen(filePath.c_str(), sizeof(LadderData), SEM_ID(sem[level-1],semgroup,semserver)))
		{
			cout << "init shm fail" << endl;
			return 1;
		}
		CAutoLock lock(&shm, true);
		LadderData *pdata = (LadderData *)shm.GetAddress();
		if (!pdata)
		{
			cout << "null addr" << endl;
			return 1;
		}
		int ret;
		for (int i = 0; i < LADDER_ITEM_NUMBER; i++)
		{
			if(IsValidUid(pdata->ladder[i].uid) && serverid == Config::GetZoneByUID(pdata->ladder[i].uid))
			{
				memset(&(pdata->ladder[i]),0,sizeof(LadderItem));
				pdata->ladder[i].uid = 401;
				pdata->ladder[i].level = 13;
				pdata->ladder[i].upts = Time::GetGlobalTime();
				snprintf(pdata->ladder[i].name, sizeof(pdata->ladder[i].name), "挑战我吧");
				snprintf(pdata->ladder[i].pic, sizeof(pdata->ladder[i].pic), "http://s4.app100630637.qqopenapp.com/images/arena.png");
			}
		}
	}

	cout << "ok" << endl;
	return 0;
}

