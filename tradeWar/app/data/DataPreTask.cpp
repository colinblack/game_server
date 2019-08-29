/*
 * DatePerTask.cpp
 *
 *  Created on: 2017年11月16日
 *      Author: Administrator
 */

#include "DataPreTask.h"
#include "AsyncDBManager.h"

#define OP_ADD_PRE_TASK 1
#define OP_DEL_PRE_TASK 2

int CDataPreTask::getPreTasks(uint32_t uid, vector<uint32_t> &ids)
{
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(id);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;

	DBCREQ_ARRAY_GET_BEGIN(ids);
	DBCREQ_ARRAY_GET_INT_S(ids, id);
	DBCREQ_ARRAY_GET_END();

	return 0;
}

int CDataPreTask::getPreTask(uint32_t uid, uint32_t id)
{
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);
	DBCREQ_SET_CONDITION(EQ, id, id);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(id);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;
	DBCREQ_IFFETCHROW;

	DBCREQ_GET_BEGIN();
	DBCREQ_GET_INT_S(id);

	return 0;
}

int CDataPreTask::addPreTask(uint32_t uid, uint32_t id)
{
	DB_ENCODE_BEGIN(DB_PRETASK, OP_ADD_PRE_TASK);
	DB_ENCODE(UInt32, uid);
	DB_ENCODE(UInt32, id);
	DB_ENCODE_END;

	return 0;
}

int CDataPreTask::delPreTask(uint32_t uid)
{
	DB_ENCODE_BEGIN(DB_PRETASK, OP_DEL_PRE_TASK);
	DB_ENCODE(UInt32, uid);
	DB_ENCODE_END;

	return 0;
}

int CDataPreTask::realAddPreTask(CNetPacket* packet)
{
	uint32_t uid;
	uint32_t id;
	DB_DECODE_BEGIN(&packet->body);
	DB_DECODE(UInt32, uid);
	DB_DECODE(UInt32, id);
	DB_DECODE_END;

	DBCREQ_DECLARE(DBC::InsertRequest, uid);
	DBCREQ_SET_KEY(uid);
	DBCREQ_SET_INT_V(id);

	return 0;
}

int CDataPreTask::realDelPreTask(CNetPacket* packet)
{
	uint32_t uid;
	DB_DECODE_BEGIN(&packet->body);
	DB_DECODE(UInt32, uid);
	DB_DECODE_END;

	DBCREQ_DECLARE(DBC::DeleteRequest, uid);
	DBCREQ_SET_KEY(uid);
	DBCREQ_EXEC

	return 0;
}

OP_PROCESS_BEGIN(CDataPreTask)
	OP_PROCESS(OP_ADD_PRE_TASK, realAddPreTask)
	OP_PROCESS(OP_DEL_PRE_TASK, realDelPreTask)
	OP_PROCESS_END

