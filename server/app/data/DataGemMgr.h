/*
 * DataGemMgr.h
 *
 *  Created on: 2016-9-26
 *      Author: dawx62fac
 */

#ifndef DATAGEMMGR_H_
#define DATAGEMMGR_H_

#include "DataInc.h"


class DataGemMgr
	: public DataSingleton<DBCGem, DB_GEM, DB_BASE_BUFF*DB_GEM_FACTOR, DBCGemHandler, DB_GEM_FACTOR>
	, public CSingleton<DataGemMgr>
{
//
	typedef DataSingleton<DBCGem, DB_GEM, DB_BASE_BUFF*DB_GEM_FACTOR, DBCGemHandler, DB_GEM_FACTOR> base;
private:
	int FreeIndex();

	void NewItem(unsigned uid, uint8_t id);
public:
	int OnInit();

	virtual void CallDestroy() { Destroy();}

	void DoClear(unsigned uid);
	void DoSave(unsigned uid);

	void Online(unsigned uid);
	void Offline(unsigned uid);

	int Load(unsigned uid);

	int GetIndex(unsigned uid, unsigned id);
private:
	std::map<unsigned, bool> m_load_map; //记录加载过的用户

	std::map<unsigned, std::map<uint8_t, unsigned> > m_map;
};


#endif /* DATAGEMMGR_H_ */
