#ifndef DATA_MODEL_TRIAL_MANAGER_H_
#define DATA_MODEL_TRIAL_MANAGER_H_

#include "Kernel.h"
#include "DataModelTrial.h"

class DataModelTrialManager : public DataSingleton<DataModelTrial, DB_MODEL_TRIAL, DB_BASE_BUFF*DB_BASE_FULL, CDataModelTrial, DB_BASE_FULL>,
	public CSingleton<DataModelTrialManager>
{
private:
	friend class CSingleton<DataModelTrialManager>;
	DataModelTrialManager(){};
	virtual ~DataModelTrialManager(){}

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
	int AddBuff(DataModelTrial & modeltrial);
	int LoadBuff(unsigned uid);

	unsigned GetIndex(unsigned uid);

	void DoClear(unsigned uid);
	void DoSave(unsigned uid);

	//如果没有，则新增
	DataModelTrial& GetModelTrial(unsigned uid);

	bool UpdateModelTrial(DataModelTrial& modeltrial);
};

#endif /* DATA_MODEL_TRIAL_MANAGER_H_ */
