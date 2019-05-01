
#ifndef EQUIPMENT_MANAGER_H_
#define EQUIPMENT_MANAGER_H_

#include "Kernel.h"
#include "DataEquipment.h"

class EquipmentManager : public DataSingleton<DataEquipment, DB_EQUIPMENT, DB_BASE_BUFF*DB_EQUIPMENT_FULL, CDataEquipment, DB_EQUIPMENT_FULL>, public CSingleton<EquipmentManager>
{
private:
	friend class CSingleton<EquipmentManager>;
	EquipmentManager(){};
	virtual ~EquipmentManager(){}

	typedef map<uint32_t, map<uint32_t, uint32_t> > MapMap;  //uid->ud =>index
	typedef map<uint32_t, map<uint32_t, uint32_t> >::iterator MapMap_ITER;
	MapMap m_map;

	typedef map<uint32_t, map<uint32_t, set<uint32_t> > > MapMapSet;   //uid->eqid => ud
	typedef map<uint32_t, map<uint8_t, set<uint32_t> > >::iterator MapMapSet_ITER;
	MapMapSet m_mapequd;

public:

	struct EquipConfInfo
	{
		uint8_t character;
		int pid;
		int type;
		int price;

		EquipConfInfo():
			character(0),
			pid(0),
			type(0),
			price(0)
		{
		}
	};

public:
	virtual void CallDestroy() {Destroy();}
	virtual int OnInit();
	virtual void OnExit();
	virtual void OnTimer1();
	virtual void OnTimer2();

	//初始化用户的最大ud
	int InitUserEquip(unsigned uid);

	int CheckBuff(unsigned uid);
	int AddBuff(DataEquipment & equipment);
	int LoadBuff(unsigned uid);

	void DoClear(unsigned uid);
	void DoSave(unsigned uid);

	/**
	 * 获取英雄身上所有装备
	 */
	void GetHeroEquips(unsigned uid, unsigned heroid, std::vector<DataEquipment>& equips);

	DataEquipment & GetEquipment(unsigned uid, unsigned ud, unsigned &index);

	DataEquipment & GetEquipmentNoIndex(unsigned uid, unsigned ud);

	bool UpdateEquipment(unsigned index);

	//删除装备，包括删除DBC以及内存
	bool DeleteEquipment(DataEquipment & equip);

	//装备是否存在
	bool IsEquipmentExists(unsigned uid, unsigned ud);

	//是否可叠加
	bool IsAllowOverlay(unsigned eqid);

	//根据eqid，获取下一个可用的ud
	unsigned GetUserNextUd(unsigned uid, unsigned eqid, unsigned count);

	int FullMessage(unsigned uid, User::User* reply);

	//获取可装备的道具index
	int GetOptionalEquipment(unsigned uid, vector<unsigned> & vctindexs);

	//根据index获取装备
	DataEquipment &  GetEquipmentByIndex(unsigned index);

	//获取英雄身上的装备
	int GetHeroEquipment(unsigned uid, unsigned heroid, vector<unsigned> & vctindexs);

	//获取用户身上的装备，排除已售出的
	int GetEquipments(unsigned uid, vector<unsigned> & vctindexs);

	//从配置文件中获取eqid对应的pid
	int GetEquipmentPid(unsigned eqid);

	//从配置文件中获取配置信息
	int GetEquipmentConfig(unsigned uid, unsigned eqid, EquipConfInfo & equipinfo);

	//获取当前用户已售出的装备
	int GetSoldEquipment(unsigned uid, vector<unsigned> & vctindexs);

private:
	//删除表里的数据
	bool DeleteDBCEquipment(unsigned index);

	int CreateSelfIndex(unsigned uid, unsigned eqid, unsigned equd, unsigned index);

	int DeleteSelfIndex(unsigned uid, unsigned eqid, unsigned equd);

private:
	map<unsigned, unsigned> m_userMaxEqud;
};

#endif /* EQUIPMENT_MANAGER_H_ */
