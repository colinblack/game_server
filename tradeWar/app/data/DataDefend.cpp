/*
 * DataDefend.cpp
 *
 *  Created on: 2017年11月14日
 *      Author: Administrator
 */

#include "DataDefend.h"
#include "AsyncDBManager.h"

#define OP_ADD_ 1
#define OP_SET_ 2
#define OP_DEL_ 3


OP_PROCESS_BEGIN(CDataDefend)
OP_PROCESS(OP_ADD_, Add)
OP_PROCESS(OP_SET_, Set)
OP_PROCESS(OP_DEL_, Del)
OP_PROCESS_END

int CDataDefend::Add(const DataDefend &data)
{
	DB_ENCODE_BEGIN(DB_DEFEND, OP_ADD_);
	DB_ENCODE(UInt32, data.uid);
	DB_ENCODE(UInt32, data.level);
	DB_ENCODE(Byte, data.star);
	DB_ENCODE_END;
	return 0;
}

int CDataDefend::Add(CNetPacket *packet)
{
	DataDefend data;
	DB_DECODE_BEGIN(&packet->body);
	DB_DECODE(UInt32, data.uid);
	DB_DECODE(UInt32, data.level);
	DB_DECODE(Byte, data.star);
	DB_DECODE_END;

	DBCREQ_DECLARE(DBC::InsertRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_INT(data, level);
	DBCREQ_SET_INT(data, star);
	DBCREQ_EXEC;
	return 0;
}

int CDataDefend::Set(const DataDefend &data)
{
	DB_ENCODE_BEGIN(DB_DEFEND, OP_SET_);
	DB_ENCODE(UInt32, data.uid);
	DB_ENCODE(UInt32, data.level);
	DB_ENCODE(Byte, data.star);
	DB_ENCODE_END;
	return 0;
}

int CDataDefend::Set(CNetPacket *packet)
{
	DataDefend data;
	DB_DECODE_BEGIN(&packet->body);
	DB_DECODE(UInt32, data.uid);
	DB_DECODE(UInt32, data.level);
	DB_DECODE(Byte, data.star);
	DB_DECODE_END;

	DBCREQ_DECLARE(DBC::UpdateRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_CONDITION(EQ, level, data.level);
	DBCREQ_SET_INT(data, star);
	DBCREQ_EXEC;
	return 0;
}

int CDataDefend::Del(uint32_t uid)
{
	DB_ENCODE_BEGIN(DB_DEFEND, OP_DEL_);
	DB_ENCODE(UInt32, uid);
	DB_ENCODE_END;
	return 0;
}

int CDataDefend::Del(CNetPacket *packet)
{
	uint32_t uid = 0;
	DB_DECODE_BEGIN(&packet->body);
	DB_DECODE(UInt32, uid);

	DBCREQ_DECLARE(DBC::DeleteRequest, uid);
	DBCREQ_SET_KEY(uid);
	DBCREQ_EXEC;
	return 0;
}

int CDataDefend::Get(uint32_t uid, uint32_t level, DataDefend &data)
{
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);
	DBCREQ_SET_CONDITION(EQ, level, level);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(level);
	DBCREQ_NEED(star);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;
	DBCREQ_IFFETCHROW

	DBCREQ_GET_BEGIN();
	DBCREQ_GET_INT(data, uid);
	DBCREQ_GET_INT(data, level);
	DBCREQ_GET_INT(data, star);

	return 0;
}

int CDataDefend::Get(uint32_t uid, vector<DataDefend> &data)
{
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(level);
	DBCREQ_NEED(star);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;

	DBCREQ_ARRAY_GET_BEGIN(data);
	DBCREQ_ARRAY_GET_INT(data, uid);
	DBCREQ_ARRAY_GET_INT(data, level);
	DBCREQ_ARRAY_GET_INT(data, star);
	DBCREQ_ARRAY_GET_END();

	return 0;
}
