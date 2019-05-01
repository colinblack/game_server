#ifndef DATA_COMPONENT_MANAGER_H_
#define DATA_COMPONENT_MANAGER_H_

#include "Kernel.h"
#include "DataComponent.h"

class DataComponentManager : public DataSingleton<DataComponent, DB_COMPONET, DB_BASE_BUFF*DB_COMPONET_FULL, CDataComponent, DB_COMPONET_FULL>,
	public CSingleton<DataComponentManager>
{
private:
	friend class CSingleton<DataComponentManager>;
	DataComponentManager(){};
	virtual ~DataComponentManager(){}

	typedef map<uint32_t, map<uint32_t, uint32_t> > MapMap;  //uid->ud =>index
	typedef map<uint32_t, map<uint32_t, uint32_t> >::iterator MapMap_ITER;
	MapMap m_map;

public:
	virtual void CallDestroy() {Destroy();}
	virtual int OnInit();
	virtual void OnExit();
	virtual void OnTimer1();
	virtual void OnTimer2();

	int CheckBuff(unsigned uid);
	int AddBuff(DataComponent & component);
	int LoadBuff(unsigned uid);

	//初始化用户的最大ud
	int InitUserComponent(unsigned uid);

	void DoClear(unsigned uid);
	void DoSave(unsigned uid);

	DataComponent& GetComponent(unsigned uid, unsigned ud);

	DataComponent& GetComponent(unsigned index);

	//获取所有部件
	int GetComponents(unsigned uid, vector<unsigned> & indexs);

	//部件是否存在
	bool IsComponentExists(unsigned uid, unsigned ud);

	//更新部件
	bool UpdateDataComponent(DataComponent& component);

	//删除装备，只删除索引
	bool DeleteComponent(DataComponent& component);

	//根据部件id，获取下一个可用的ud
	unsigned GetUserNextUd(unsigned uid);

	//返回无主部件的数量
	int GetNumOfDereliction(unsigned uid);

	//返回无主部件，包括经验道具
	int GetOptionalComponents(unsigned uid, vector<unsigned> & indexs);

	//获取英雄装备的部件
	int GetHeroComponents(unsigned uid, unsigned heroid, vector<unsigned> & indexs);

private:
	bool DeleteDBCComponent(unsigned index);

private:
	map<unsigned, unsigned> m_userMaxCompud;
	static const int MAX_INDEX = DB_BASE_BUFF*DB_COMPONET_FULL;
};

#endif /* DATA_COMPONENT_MANAGER_H_ */
