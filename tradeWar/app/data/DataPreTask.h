/*
 * DatePerTask.h
 *
 *  Created on: 2017年11月16日
 *      Author: Administrator
 */

#ifndef DATA_PRETASK_H_
#define DATA_PRETASK_H_

#include "Kernel.h"
#include "AsyncDBInterface.h"

class CDataPreTask: public CDataBaseDBC, public AsyncDBInterface
{
public:
	CDataPreTask(int table = DB_PRETASK) : CDataBaseDBC(table)
	{
	}
	virtual ~CDataPreTask()
	{
	}
	int getPreTasks(uint32_t uid, vector<uint32_t> &ids);
	int getPreTask(uint32_t uid, uint32_t id);
	int addPreTask(uint32_t uid, uint32_t id);
	int delPreTask(uint32_t uid);
	int realAddPreTask(CNetPacket* packet);
	int realDelPreTask(CNetPacket* packet);
	virtual void doRequest(CNetPacket* packet);
};

#endif /* DATA_PRETASK_H_ */
