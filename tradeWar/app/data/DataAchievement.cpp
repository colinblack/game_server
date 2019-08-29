/*
 * DataAchievement.cpp
 *
 *  Created on: 2018年8月11日
 *      Author:
 */

#include "DataAchievement.h"
#include "AsyncDBManager.h"

#define OP_ADD_ACHIEVEMENT 1
#define OP_SET_ACHIEVEMENT 2
#define OP_DEL_ACHIEVEMENT 3

int CDataAchievement::AddAchievement(const DataAchievement& data) {
	DB_ENCODE_BEGIN(DB_ACHIEVEMENT, OP_ADD_ACHIEVEMENT);
	DB_ENCODE(UInt32, data.uid);
	DB_ENCODE(UInt32, data.type);
	DB_ENCODE(UInt32, data.id);
	DB_ENCODE(UInt32, data.count);
	DB_ENCODE_END;

	return 0;
}
int CDataAchievement::GetAchievement(uint32_t uid, vector<DataAchievement>& data) {
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(type);
	DBCREQ_NEED(id);
	DBCREQ_NEED(count);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;

	DBCREQ_ARRAY_GET_BEGIN(data);
	DBCREQ_ARRAY_GET_INT(data, uid);
	DBCREQ_ARRAY_GET_INT(data, type);
	DBCREQ_ARRAY_GET_INT(data, id);
	DBCREQ_ARRAY_GET_INT(data, count);
	DBCREQ_ARRAY_GET_END();

	return 0;
}
int CDataAchievement::SetAchievement(const DataAchievement& data) {
	DB_ENCODE_BEGIN(DB_ACHIEVEMENT, OP_SET_ACHIEVEMENT);
	DB_ENCODE(UInt32, data.uid);
	DB_ENCODE(UInt32, data.type);
	DB_ENCODE(UInt32, data.id);
	DB_ENCODE(UInt32, data.count);
	DB_ENCODE_END;

	return 0;
}
int CDataAchievement::DelAchievement(uint32_t uid) {
	DB_ENCODE_BEGIN(DB_ACHIEVEMENT, OP_DEL_ACHIEVEMENT);
	DB_ENCODE(UInt32, uid);
	DB_ENCODE_END;

	return 0;
}
int CDataAchievement::RealAddAchievement(CNetPacket* packet) {
	DataAchievement data;
	DB_DECODE_BEGIN(packet->GetBody());
	DB_DECODE(UInt32, data.uid);
	DB_DECODE(UInt32, data.type);
	DB_DECODE(UInt32, data.id);
	DB_DECODE(UInt32, data.count);
	DB_DECODE_END;

	DBCREQ_DECLARE(DBC::InsertRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_INT(data, type);
	DBCREQ_SET_INT(data, id);
	DBCREQ_SET_INT(data, count);
	DBCREQ_EXEC;

	return 0;
}
int CDataAchievement::RealSetAchievement(CNetPacket* packet) {
	DataAchievement data;
	DB_DECODE_BEGIN(packet->GetBody());
	DB_DECODE(UInt32, data.uid);
	DB_DECODE(UInt32, data.type);
	DB_DECODE(UInt32, data.id);
	DB_DECODE(UInt32, data.count);
	DB_DECODE_END;

	DBCREQ_DECLARE(DBC::UpdateRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_CONDITION(EQ, type, data.type);
	DBCREQ_SET_INT(data, id);
	DBCREQ_SET_INT(data, count);
	DBCREQ_EXEC;

	return 0;
}
int CDataAchievement::RealDelAchievement(CNetPacket* packet) {
	uint32_t uid = 0;
	DB_DECODE_BEGIN(packet->GetBody());
	DB_DECODE(UInt32, uid);
	DB_DECODE_END;

	DBCREQ_DECLARE(DBC::DeleteRequest, uid);
	DBCREQ_SET_KEY(uid);
	DBCREQ_EXEC;

	return 0;
}

OP_PROCESS_BEGIN(CDataAchievement)
OP_PROCESS(OP_ADD_ACHIEVEMENT, RealAddAchievement)
OP_PROCESS(OP_SET_ACHIEVEMENT, RealSetAchievement)
OP_PROCESS(OP_DEL_ACHIEVEMENT, RealDelAchievement)
OP_PROCESS_END
