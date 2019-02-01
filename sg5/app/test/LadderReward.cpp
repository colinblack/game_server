#include "LogicInc.h"
#include <iostream>
#include<math.h>

void CalcCoins1000(int rank, int &coins, int &bs)
{
	coins = 0;
	bs = 0;
	if (rank == 1)
	{
		coins = 200;
		bs = 15000;
	}
	else if (rank == 2)
	{
		coins = 170;
		bs = 12000;
	}
	else if (rank == 3)
	{
		coins = 140;
		bs = 10000;
	}
	else if (rank <= 10)
	{
		coins = 110;
		bs = 8000;
	}
	else if (rank <= 30)
	{
		coins = 90;
		bs = 7000;
	}
	else if (rank <= 50)
	{
		coins = 70;
		bs = 6000;
	}
	else if (rank <= 100)
	{
		coins = 50;
		bs = 5000;
	}
	else if (rank <= 150)
	{
		coins = 40;
		bs = 4000;
	}
	else if (rank <= 200)
	{
		coins = 30;
		bs = 3000;
	}
	else if (rank <= 250)
	{
		coins = 20;
		bs = 2000;
	}
	else if (rank <= 300)
	{
		coins = 15;
		bs = 1500;
	}
	else if (rank <= 500)
	{
		coins = 10;
		bs = 1000;
	}
	else
	{
		coins = 5;
		bs = 500;
	}
}

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
	if (!shm.CreateOrOpen(Config::GetPath(CONFIG_LADDER_PATH).c_str(), sizeof(LadderData), SEM_ID(sem_ladder,semgroup,semserver)))
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
	CDataUser logicUser;
	CLogicUpdates logicUpdates;
	set<int> uid_flag;
	for (int i = 0; i < LADDER_ITEM_NUMBER; i++)
	{
		unsigned uid = pdata->ladder[i].uid;

		if(0 == uid)
		{
			pdata->ladder[i].uid = 401;
			pdata->ladder[i].level = 13;
		}

		if(IsValidUid(uid))
		{
			if(!uid_flag.count(uid))
			{
				uid_flag.insert(uid);
			}
			else
			{
				memset(&(pdata->ladder[i]),0,sizeof(LadderItem));
				pdata->ladder[i].uid = 401;
				pdata->ladder[i].level = 13;
				uid = 401;
			}
		}

		if (!IsValidUid(uid) || pdata->ladder[i].level < 10)
			continue;
		int coins = 0;
		int bs = 0;
		CalcCoins1000(i + 1, coins, bs);
		cout << "uid=" << uid << ",rank=" << i+1 << ",coins=" << coins << ",bs=" << bs << endl;
		Json::Value updates;
		updates.resize(1);
		updates[(unsigned)0]["s"] = "LADDER";
		updates[(unsigned)0]["rank"] = i + 1;
		updates[(unsigned)0]["coins"] = coins;
		updates[(unsigned)0]["bs"] = bs;
		updates[(unsigned)0]["ts"] = (unsigned)time(0);
		ret = logicUpdates.AddUpdates(uid, updates);
		if (0 != ret)
		{
			cout << "AddUpdates error uid=" << uid << endl;
		}
	}
	cout << "ok" << endl;
	return 0;
}
