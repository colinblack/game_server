/*
 * EquipShopManager.h
 *
 *  Created on: 2016-09-5
 *      Author: city
 */

#ifndef EQUIP_SHOP_MANAGER_H_
#define EQUIP_SHOP_MANAGER_H_

#include "Kernel.h"
#include "DataEquipShop.h"

class EquipShopManager : public DataSingleton<DataEquipShop, DB_EQUIP_SHOP, DB_BASE_BUFF*DB_EQUIP_SHOP_FULL, CDataEquipShop, DB_EQUIP_SHOP_FULL>, public CSingleton<EquipShopManager>
{
private:
	friend class CSingleton<EquipShopManager>;
	EquipShopManager(){};
	virtual ~EquipShopManager(){}

	typedef map<uint32_t, map<uint8_t, uint32_t> > MapMap;
	typedef map<uint32_t, map<uint8_t, uint32_t> >::iterator MapMap_ITER;
	MapMap m_map;

public:
	virtual void CallDestroy() {Destroy();}
	virtual int OnInit();
	virtual void OnExit();
	virtual void OnTimer1();
	virtual void OnTimer2();

	int CheckBuff(unsigned uid);
	int AddBuff(DataEquipShop & equipshop);
	int LoadBuff(unsigned uid);

	void DoClear(unsigned uid);
	void DoSave(unsigned uid);

	DataEquipShop & GetEquipShop(unsigned uid, uint8_t pid, unsigned &index);

	int AddEquipShop(DataEquipShop & equipshop);
	bool UpdateEquipShop(unsigned index);

	int FullMessage(unsigned uid, User::User* reply);

	template<class T>
	int FullMessage(unsigned uid, T * reply)
	{
		//加载数据
		map<uint8_t, uint32_t>::iterator miter = m_map[uid].begin();

		for(; miter != m_map[uid].end(); ++miter)
		{
			DataCommon::EquipShopCPP * pmsg = reply->add_equippool();
			m_data->data[miter->second].SetMessage(pmsg);
		}

		return 0;
	}

private:
};

#endif /* BASEMANAGER_H_ */

