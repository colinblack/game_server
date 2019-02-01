#include "LogicInc.h"
#include <iostream>
#include<math.h>

int main(int argc, char *argv[])
{
	if (!Kernel::Init(APP_CONFIG_PATH))
	{
		cout << "init kernel fail" << endl;
		return 1;
	}

	Config::SetDomain(0);
	int semgroup = 0;
	int semserver = 0;
	Config::GetDB(semserver);
	CShareMemory shm;
	if (!shm.CreateOrOpen(Config::GetPath(CONFIG_TOP_TEN_USER_PATH).c_str(), sizeof(DataTopTenUser), SEM_ID(sem_toptenuser,semgroup,semserver)))
	{
		cout << "init shm fail" << endl;
		return 1;
	}
	CAutoLock lock(&shm, true);
	DataTopTenUser *pdata = (DataTopTenUser *)shm.GetAddress();
	if (!pdata)
	{
		cout << "null addr" << endl;
		return 1;
	}


	cout<<"reward_flag:"<<pdata->reward_flag<<endl;
	for(int i=0; i<10; i++)
	{
		cout<<"uid:"<<pdata->heroPower[i].uid<<"  power:"<<pdata->heroPower[i].power<<endl;
	}

	for(int i=0; i<10; i++)
	{
		cout<<"uid:"<<pdata->userPlunder[i].uid<<"  userPlunder:"<<pdata->userPlunder[i].plunder<<endl;
	}

	for(int i=0; i<10; i++)
	{
		cout<<"uid:"<<pdata->userLevel[i].uid<<"  level:"<<pdata->userLevel[i].level<<endl;
	}

	cout << "ok" << endl;
	return 0;
}
