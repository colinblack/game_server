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
	if (!shm.CreateOrOpen(Config::GetPath(HEQU_ALLIANCE_POINT).c_str(), sizeof(DataHequAlliancePoint), SEM_ID(sem_alliance_point,semgroup,semserver)))
	{
		cout << "init shm fail" << endl;
		return 1;
	}
	CAutoLock lock(&shm, true);
	DataHequAlliancePoint *pdata = (DataHequAlliancePoint *)shm.GetAddress();
	if (!pdata)
	{
		cout << "null addr" << endl;
		return 1;
	}


//	memset(&(pdata->pointRank[0]),0,sizeof(DataPoints));

	cout<<"reward"<<pdata->reward<<endl;
	cout<<"version:"<<pdata->version<<endl;
	for(int i=0; i<ALLIANCE_POINT_RANK_SIZE; ++i)
	{
		if(pdata->point[i].alliance_id != 0)
		{
			int rank = i + 1;
			cout<<"ranktest:"<<rank<<" alliance_id:"<<pdata->point[i].alliance_id<<"name:"<<pdata->point[i].name<<"point:"<<pdata->point[i].point<<endl;
		}

	}
	cout << "ok" << endl;
	return 0;
}
