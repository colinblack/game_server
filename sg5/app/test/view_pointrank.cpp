#include "LogicInc.h"
#include <iostream>
#include<math.h>


int sortFunc(const DataPoints& left,const DataPoints& right){
	return left.points > right.points;
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
	if (!shm.CreateOrOpen(Config::GetPath(POINTS_RANK).c_str(), sizeof(PointsRank), SEM_ID(sem_pointsrank,semgroup,semserver)))
	{
		cout << "init shm fail" << endl;
		return 1;
	}
	CAutoLock lock(&shm, true);
	PointsRank *pdata = (PointsRank *)shm.GetAddress();
	if (!pdata)
	{
		cout << "null addr" << endl;
		return 1;
	}


//	memset(&(pdata->pointRank[0]),0,sizeof(DataPoints));

	vector<DataPoints> vecPoint;
	for(int i = 0; i<=RANK_SIZE;++i){
		vecPoint.push_back(pdata->pointRank[i]);
	}

	sort(vecPoint.begin(),vecPoint.end(),sortFunc);

	for(int i = 0; i<=RANK_SIZE;++i){
		pdata->pointRank[i] = vecPoint[i];
	}

	for(int i=0; i<=RANK_SIZE; i++)
	{
		int rank = i + 1;
		cout<<"ranktest:"<<rank<<" name:"<<pdata->pointRank[i].name<<"uid:"<<pdata->pointRank[i].uid<<"point:"<<pdata->pointRank[i].points<<endl;
	}
	cout << "ok" << endl;
	return 0;
}
