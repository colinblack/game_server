/*
 * DataNPCPassManager.h
 *
 *  Created on: 2016-9-8
 *      Author: dawx62fac
 */

#ifndef DATANPCPASSMANAGER_H_
#define DATANPCPASSMANAGER_H_

#include "DataInc.h"
#include "DataNPCPass.h"

class DataNPCPassMgr
	: public DataSingleton<DataNPCPass, DB_NPC_PASS, DB_BASE_BUFF*DB_NPC_PASS_FACTOR, DBCDataNPCPassHandler, DB_NPC_PASS_FACTOR>
	, public CSingleton<DataNPCPassMgr>
{
//
	typedef DataSingleton<DataNPCPass, DB_NPC_PASS, DB_BASE_BUFF*DB_NPC_PASS_FACTOR, DBCDataNPCPassHandler, DB_NPC_PASS_FACTOR> base;
private:

	int 	FreeIndex();


public:
	int OnInit();

	virtual void CallDestroy() { Destroy();}

	void DoClear(unsigned uid);
	void DoSave(unsigned uid);

	int 	GetIndex(unsigned uid, unsigned id);
	void 	GetIndexs(unsigned uid, std::vector<unsigned>& vIndexs);

	//
	int LoadBuffer(unsigned uid);

	//记录闯关次数
	void PassSuccess(unsigned uid, unsigned id);
private:
	std::multimap<unsigned, unsigned> m_mapTb;
};

#endif /* DATANPCPASSMANAGER_H_ */
