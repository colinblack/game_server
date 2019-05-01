#ifndef DATA_SELL_COMPONENT_MANAGER_H_
#define DATA_SELL_COMPONENT_MANAGER_H_

#include "Kernel.h"
#include "DataSellComponent.h"

class DataSellComponentManager : public DataSingleton<DataSellComponent, DB_SELL_COMPONENT, DB_BASE_BUFF*DB_BASE_FULL, CDataSellComponent, DB_BASE_FULL>,
	public CSingleton<DataSellComponentManager>
{
private:
	friend class CSingleton<DataSellComponentManager>;
	DataSellComponentManager(){};
	virtual ~DataSellComponentManager(){}

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
	int AddBuff(DataSellComponent & sellcomponent);
	int LoadBuff(unsigned uid);

	unsigned GetIndex(unsigned uid);

	void DoClear(unsigned uid);
	void DoSave(unsigned uid);

	//如果没有，则新增
	DataSellComponent& GetSellComponent(unsigned uid);

	bool UpdateSellComponent(DataSellComponent& sellcomponent);
};

#endif /* DATA_SELL_COMPONENT_MANAGER_H_ */
