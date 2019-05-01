#ifndef DATA_CROSS_BUSINESS_MANAGER_H_
#define DATA_CROSS_BUSINESS_MANAGER_H_

#include "Kernel.h"
#include "DataCrossBusiness.h"

class DataCrossBusinessManager : public DataSingleton<DataCrossBusiness, DB_CROSS_BUSINESS, DB_BASE_BUFF*DB_BASE_FULL, CDataCrossBusiness, DB_BASE_FULL>,
	public CSingleton<DataCrossBusinessManager>
{
private:
	friend class CSingleton<DataCrossBusinessManager>;
	DataCrossBusinessManager(){};
	virtual ~DataCrossBusinessManager(){}

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
	int AddBuff(DataCrossBusiness & crossbusiness);
	int LoadBuff(unsigned uid);

	unsigned GetIndex(unsigned uid);

	void DoClear(unsigned uid);
	void DoSave(unsigned uid);

	bool IsCrossBusinessExists(unsigned uid);

	//如果没有，则新增
	DataCrossBusiness& GetCrossBusiness(unsigned uid);

	bool UpdateCrossBusiness(DataCrossBusiness& crossbusiness);
};

#endif /* DATA_CROSS_BUSINESS_MANAGER_H_ */
