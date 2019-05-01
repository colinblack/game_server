/*
 * DataNPCPass.h
 *
 *  Created on: 2016-9-8
 *      Author: dawx62fac
 */

#ifndef DATANPCPASS_H_
#define DATANPCPASS_H_

#include "Kernel.h"

class DataNPCPass
{
public:
	unsigned uid;
	unsigned id;
	unsigned pass_cnt; //成功闯关次数

	DataNPCPass();
	DataNPCPass(unsigned uid, unsigned id);

	void FullMessage(ProtoPass::NPCPassRecord* obj) const;
};

class DBCDataNPCPassHandler : public DBCBase<DataNPCPass, DB_NPC_PASS>
{
public:
	virtual int Get(DataNPCPass &data);
	virtual int Get(vector<DataNPCPass> &data);
	virtual int Add(DataNPCPass &data);
	virtual int Set(DataNPCPass &data);
	virtual int Del(DataNPCPass &data);
};


#endif /* DATANPCPASS_H_ */
