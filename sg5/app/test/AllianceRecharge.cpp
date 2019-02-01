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

	if (argc == 3)
	{
		unsigned uid = atoi(argv[1]);
		unsigned cash = atoi(argv[2]);

		if(IsValidUid(uid) && cash)
		{
			AllianceMember recharge;
			CLogicRechargeAlliance Rechargealliance;

			recharge.uid = uid;
			recharge.cash = cash;

			int ret = Rechargealliance.UpdateRechargeAllianceData(recharge);
			if(0 != ret)
				cout << "ret=" <<ret<< endl;
			else
				cout << "ok" << endl;
		}
		return 0;
	}

	int semgroup = 0;
	int semserver = 0;
	Config::GetDB(semserver);
	CShareMemory shm;
	if (!shm.CreateOrOpen(MainConfig::GetAllServerPath(CONFIG_ALLIANCE_RECHARGE_DATA).c_str(), sizeof(AllianceRechargeData), SEM_ID(sem_recharge_alliance,semgroup,semserver)))
	{
		cout << "init shm fail" << endl;
		return 1;
	}
	AllianceRechargeData *pdata = (AllianceRechargeData *)shm.GetAddress();
	CAutoLock lock(&shm, true);
	if (!pdata)
	{
		cout << "null addr" << endl;
		return 1;
	}

	for(int i=0; i<1000; i++)
	{
		for(int j = 0;j<100;j++)
		{
			if(pdata->num_of_union[i].alliance_id !=0 && pdata->num_of_union[i].num_of_people[j].uid != 0)
			{
				cout<<pdata->num_of_union[i].alliance_id<<"::"<<pdata->num_of_union[i].num_of_people[j].uid<<"---"<<pdata->num_of_union[i].num_of_people[j].name<<"---"<<pdata->num_of_union[i].num_of_people[j].cash<<endl;
			}
		}
	}

	return 0;
}
