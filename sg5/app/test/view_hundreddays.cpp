#include "LogicInc.h"
#include <iostream>
#include<math.h>

int sortFunc(const DataHDaysAcvitityPay& left,const DataHDaysAcvitityPay& right){
	return left.pay > right.pay;
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
	if (!shm.CreateOrOpen(Config::GetPath(HUNDREDDAYSACTIVITY_RANK).c_str(), sizeof(AcvitityPayRank), SEM_ID(sem_hundreddaysactivity,semgroup,semserver)))
	{
		cout << "init shm fail" << endl;
		return 1;
	}
	CAutoLock lock(&shm, true);
	AcvitityPayRank *pdata = (AcvitityPayRank *)shm.GetAddress();
	if (!pdata)
	{
		cout << "null addr" << endl;
		return 1;
	}

	int ret = 0;
	CLogicUpdates logiceUpdates;

//	memset(&(pdata->HDAcvitityRank[0]),0,sizeof(DataPoints));

	vector<DataHDaysAcvitityPay> vecPoint;
	for(int i = 0; i<=RANK_SIZE;++i)
	{
		vecPoint.push_back(pdata->HDAcvitityRank[i]);
	}

	sort(vecPoint.begin(),vecPoint.end(),sortFunc);

	for(int i = 0; i<=RANK_SIZE;++i){
		pdata->HDAcvitityRank[i] = vecPoint[i];
	}
	for(int i=0; i<5; i++)
	{
		int rank = i + 1;
		cout<<"uid:"<<pdata->HDAcvitityRank[i].uid<<"  rank:"<<rank<<"  pay:"<<pdata->HDAcvitityRank[i].pay<<endl;
	}
	cout<<"version:"<<pdata->version<<endl;
	cout<<"flag:"<<pdata->flag<<endl;
	cout<<"awardflag[0]:"<<pdata->awardflag[0]<<endl;
	cout<<"awardflag[1]:"<<pdata->awardflag[1]<<endl;
	cout<<"awardflag[2]:"<<pdata->awardflag[2]<<endl;
	cout << "ok" << endl;
	return 0;
}
