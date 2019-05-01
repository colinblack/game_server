#ifndef DATA_NPCACTIVITY_MANAGER_H_
#define DATA_NPCACTIVITY_MANAGER_H_

#include "Kernel.h"
#include "DataNPCActivity.h"

class DataNPCActivityManager : public DataSingleton<DataNPCActivity, DB_NPCACTIVITY, DB_BASE_BUFF*DB_BASE_FULL, CDataNPCActivity, DB_BASE_FULL>
	, public CSingleton<DataNPCActivityManager>
{
private:
	friend class CSingleton<DataNPCActivityManager>;
	DataNPCActivityManager(){};
	virtual ~DataNPCActivityManager(){}

	map<unsigned, unsigned> m_map;
public:
	virtual void CallDestroy() {Destroy();}
	virtual int OnInit();
	virtual void OnExit();
	virtual void OnTimer1();
	virtual void OnTimer2();

	int AddBuff(DataNPCActivity & dataNPCActivity);
	int LoadBuff(unsigned uid);

	unsigned GetIndex(unsigned uid);

	void DoClear(unsigned uid);
	void DoSave(unsigned uid);

	//throw std::runtime_error
	DataNPCActivity& Get(unsigned uid);
	bool IsNPCActivityExists(unsigned uid);

	bool UpdateDataNPCActivity(unsigned index);

	bool UpdateDataNPCActivity(DataNPCActivity& DataNPCActivity);
};

#endif /* DATA_NPCACTIVITY_MANAGER_H_ */
