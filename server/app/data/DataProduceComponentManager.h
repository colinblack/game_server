/*
 * DataCumulationLoginManager.h
 *
 *  Created on: 2016-10-12
 *      Author: city
 */

#ifndef DATA_PRODUCE_COMPONENT_MANAGER_H_
#define DATA_PRODUCE_COMPONENT_MANAGER_H_

#include "Kernel.h"
#include "DataProduceComponent.h"

class DataProduceComponentManager : public DataSingleton<DataProduceComponent, DB_COMPONET_PRODUCE, DB_BASE_BUFF*DB_BASE_FULL, CDataProduceComponent, DB_BASE_FULL>,
	public CSingleton<DataProduceComponentManager>
{
private:
	friend class CSingleton<DataProduceComponentManager>;
	DataProduceComponentManager(){};
	virtual ~DataProduceComponentManager(){}

	map<unsigned, unsigned> m_map;
	static const int MAX_INDEX = DB_BASE_BUFF*DB_BASE_FULL;
public:
	virtual void CallDestroy() {Destroy();}
	virtual int OnInit();
	virtual void OnExit();
	virtual void OnTimer1();
	virtual void OnTimer2();

	int New(unsigned uid);

	int CheckBuff(unsigned uid);
	int AddBuff(DataProduceComponent & compproduce);
	int LoadBuff(unsigned uid);

	unsigned GetIndex(unsigned uid);

	void DoClear(unsigned uid);
	void DoSave(unsigned uid);

	//throw std::runtime_error
	DataProduceComponent& Get(unsigned uid);

	bool UpdateDataCompProduce(DataProduceComponent& compproduce);
};

#endif /* DATA_PRODUCE_COMPONENT_MANAGER_H_ */
