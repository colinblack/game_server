/*
 * DataCumulationLoginManager.h
 *
 *  Created on: 2016-10-12
 *      Author: city
 */

#ifndef DATA_CUMULATION_LOGIN_MANAGER_H_
#define DATA_CUMULATION_LOGIN_MANAGER_H_

#include "Kernel.h"
#include "DataCumulationLogin.h"

class DataCumulationLoginManager : public DataSingleton<DataCumulationLogin, DB_CUMULATION_LOGIN, DB_BASE_BUFF*DB_CUMULATIONLOGIN_FULL, CDataCumulationLogin, DB_CUMULATIONLOGIN_FULL>,
	public CSingleton<DataCumulationLoginManager>
{
private:
	friend class CSingleton<DataCumulationLoginManager>;
	DataCumulationLoginManager(){};
	virtual ~DataCumulationLoginManager(){}

	map<unsigned, unsigned> m_map;
public:
	virtual void CallDestroy() {Destroy();}
	virtual int OnInit();
	virtual void OnExit();
	virtual void OnTimer1();
	virtual void OnTimer2();

	int New(unsigned uid);

	int CheckBuff(unsigned uid);
	int AddBuff(DataCumulationLogin & datacumulation);
	int LoadBuff(unsigned uid);

	unsigned GetIndex(unsigned uid);

	void DoClear(unsigned uid);
	void DoSave(unsigned uid);

	//throw std::runtime_error
	DataCumulationLogin& Get(unsigned uid);

	bool UpdateDataCumulation(unsigned index);

	bool UpdateDataCumulation(DataCumulationLogin& datacumulation);

};

#endif /* DATA_CUMULATION_LOGIN_MANAGER_H_ */
