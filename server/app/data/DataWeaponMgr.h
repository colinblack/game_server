/*
 * DataWeaponMgr.h
 *
 *  Created on: 2016-9-21
 *      Author: dawx62fac
 */

#ifndef DATAWEAPONMGR_H_
#define DATAWEAPONMGR_H_


#include "DataInc.h"



class DataWeaponMgr
	: public DataSingleton<DBCWeapon, DB_WEAPON, DB_BASE_BUFF*DB_WEAPON_FACOTR, DBCWeaponHandler, DB_WEAPON_FACOTR>
	, public CSingleton<DataWeaponMgr>
{
//
	typedef DataSingleton<DBCWeapon, DB_WEAPON, DB_BASE_BUFF*DB_WEAPON_FACOTR, DBCWeaponHandler, DB_WEAPON_FACOTR> base;
private:
	int FreeIndex();

	void NewItem(unsigned uid, unsigned id);

	bool CheckUserData(unsigned uid);
	bool CheckUserData(unsigned uid, unsigned id);
public:
	int OnInit();

	virtual void CallDestroy() { Destroy();}

	void DoClear(unsigned uid);
	void DoSave(unsigned uid);

	void Online(unsigned uid);
	void Offline(unsigned uid);
	////////////////////////////////////////////////////////////////////
	void CheckParamsId(unsigned id);

	int Load(unsigned uid);

	unsigned GetIndex(unsigned uid, unsigned id);	//
	void     GetIndexs(unsigned uid, std::vector<unsigned>& vIndexs);

	DBCWeapon & GetWeapon(unsigned index);

private:
	std::map<unsigned, std::map<uint8_t, unsigned> > m_map;

	std::map<unsigned, bool> m_load_map; //记录加载过的用户
};

#endif /* DATAWEAPONMGR_H_ */
