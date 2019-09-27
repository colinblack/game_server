/*
 * DataTask.cpp
 *
 *  Created on: 2015-7-8
 *      Author: DAWX966552
 */
#include "DataTask.h"
#include "AsyncDBManager.h"
#define OP_ADD_TASK 1
#define OP_SET_TASK 2
#define OP_DEL_TASK 3
#define OP_DEL_TASKS 4

int CDataTask::AddTask(const DataTask& task)
{
	DB_ENCODE_BEGIN(DB_TASK, OP_ADD_TASK);
	DB_ENCODE(UInt32,task.uid);
	DB_ENCODE(UInt32,task.id);
	DB_ENCODE(UInt32,task.curr);
	DB_ENCODE(Byte,task.type);
	DB_ENCODE(Byte,task.status);
	DB_ENCODE_END;

	return 0;
}

int CDataTask::RealAddTask(CNetPacket *packet)
{
	DataTask task;
	DB_DECODE_BEGIN(packet->GetBody());
	DB_DECODE(UInt32, task.uid);
	DB_DECODE(UInt32, task.id);
	DB_DECODE(UInt32, task.curr);
	DB_DECODE(Byte, task.type);
	DB_DECODE(Byte, task.status);
	DB_DECODE_END;

	DBCREQ_DECLARE(DBC::InsertRequest, task.uid);
	DBCREQ_SET_KEY(task.uid);
	DBCREQ_SET_INT(task, id);
	DBCREQ_SET_INT(task, curr);
	DBCREQ_SET_INT(task, type);
	DBCREQ_SET_INT(task, status);
	DBCREQ_EXEC;

	return 0;
}

int CDataTask::GetTasks(uint32_t uid, vector<DataTask>& vecTasks)
{
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(id);
	DBCREQ_NEED(curr);
	DBCREQ_NEED(type);
	DBCREQ_NEED(status);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;

	DBCREQ_ARRAY_GET_BEGIN(vecTasks);
	DBCREQ_ARRAY_GET_INT(vecTasks, uid);
	DBCREQ_ARRAY_GET_INT(vecTasks, id);
	DBCREQ_ARRAY_GET_INT(vecTasks, curr);
	DBCREQ_ARRAY_GET_INT(vecTasks, type);
	DBCREQ_ARRAY_GET_INT(vecTasks, status);
	DBCREQ_ARRAY_GET_END();

	return 0;
}

int CDataTask::SetTask(const DataTask& task)
{
	DB_ENCODE_BEGIN(DB_TASK, OP_SET_TASK);
	DB_ENCODE(UInt32, task.uid);
	DB_ENCODE(UInt32, task.id);
	DB_ENCODE(UInt32, task.curr);
	DB_ENCODE(Byte, task.type);
	DB_ENCODE(Byte, task.status);
	DB_ENCODE_END;

	return 0;
}

int CDataTask::RealSetTask(CNetPacket* packet)
{
	DataTask task;
	DB_DECODE_BEGIN(packet->GetBody());
	DB_DECODE(UInt32, task.uid);
	DB_DECODE(UInt32, task.id);
	DB_DECODE(UInt32, task.curr);
	DB_DECODE(Byte, task.type);
	DB_DECODE(Byte, task.status);
	DB_DECODE_END;

	DBCREQ_DECLARE(DBC::UpdateRequest, task.uid);
	DBCREQ_SET_KEY(task.uid);
	DBCREQ_SET_CONDITION(EQ, id, task.id);

	DBCREQ_SET_INT(task, curr);
	DBCREQ_SET_INT(task, type);
	DBCREQ_SET_INT(task, status);
	DBCREQ_EXEC;

	return 0;
}

int CDataTask::DelTask(uint32_t uid, uint32_t id)
{
	DB_ENCODE_BEGIN(DB_TASK, OP_DEL_TASK);
	DB_ENCODE(UInt32, uid);
	DB_ENCODE(UInt32,id);
	DB_ENCODE_END;
	return 0;
}

int CDataTask::RealDelTask(CNetPacket* packet)
{
	uint32_t uid, id;
	DB_DECODE_BEGIN(packet->GetBody());
	DB_DECODE(UInt32, uid);
	DB_DECODE(UInt32, id);
	DB_DECODE_END;

	DBCREQ_DECLARE(DBC::DeleteRequest, uid);
	DBCREQ_SET_KEY(uid);
	DBCREQ_SET_CONDITION(EQ, id, id);
	DBCREQ_EXEC;
	return 0;
}

int CDataTask::DelTasks(uint32_t uid)
{
	DB_ENCODE_BEGIN(DB_TASK, OP_DEL_TASKS);
	DB_ENCODE(UInt32, uid);
	DB_ENCODE_END;
	return 0;
}

int CDataTask::RealDelTasks(CNetPacket* packet)
{
	uint32_t uid;
	DB_DECODE_BEGIN(packet->GetBody());
	DB_DECODE(UInt32, uid);
	DB_DECODE_END;

	DBCREQ_DECLARE(DBC::DeleteRequest, uid);
	DBCREQ_SET_KEY(uid);
	DBCREQ_EXEC;
	return 0;
}

OP_PROCESS_BEGIN(CDataTask)
OP_PROCESS(OP_ADD_TASK, RealAddTask)
OP_PROCESS(OP_SET_TASK, RealSetTask)
OP_PROCESS(OP_DEL_TASK, RealDelTask)
OP_PROCESS(OP_DEL_TASKS, RealDelTasks)
OP_PROCESS_END

