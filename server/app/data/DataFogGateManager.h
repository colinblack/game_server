#ifndef DATA_FOGGATE_MANAGER_H_
#define DATA_FOGGATE_MANAGER_H_

#include "Kernel.h"
#include "DataFogGate.h"

class DataFogGateManager : public DataSingleton<DataFogGate, DB_FOGGATE, DB_BASE_BUFF*DB_FOGGATE_FULL, CDataFogGate, DB_FOGGATE_FULL>,
	public CSingleton<DataFogGateManager>
{
private:
	friend class CSingleton<DataFogGateManager>;
	DataFogGateManager(){};
	virtual ~DataFogGateManager(){}

	typedef map<uint32_t, map<uint32_t, uint32_t> > MapMap;  //uid->gateid =>index
	typedef map<uint32_t, map<uint32_t, uint32_t> >::iterator MapMap_ITER;
	MapMap m_map;

public:
	virtual void CallDestroy() {Destroy();}
	virtual int OnInit();
	virtual void OnExit();
	virtual void OnTimer1();
	virtual void OnTimer2();

	int CheckBuff(unsigned uid);
	int AddBuff(DataFogGate & foggate);
	int LoadBuff(unsigned uid);

	void DoClear(unsigned uid);
	void DoSave(unsigned uid);

	//throw std::runtime_error
	DataFogGate& GetFogGate(unsigned uid, unsigned gateid);

	DataFogGate& GetFogGate(unsigned index);

	//获取所有关卡
	int GetFogGates(unsigned uid, vector<unsigned> & indexs);

	//迷雾是否存在
	bool IsFogGateExists(unsigned uid, unsigned gateid);

	bool UpdateFogGate(DataFogGate& foggate);

private:
	static const int MAX_INDEX = DB_BASE_BUFF*DB_FOGGATE_FULL;
};

#endif /* DATA_FOGGATE_MANAGER_H_ */
