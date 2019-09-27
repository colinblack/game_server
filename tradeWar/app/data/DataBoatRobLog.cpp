/*
 * DataBoatRobLog.cpp
 *
 *  Created on: 2018年8月24日
 *      Author: rein
 */

#include "DataBoatRobLog.h"
#include "AsyncDBManager.h"

#define OP_ADD_BOAT_LOG 1
#define OP_SET_BOAT_LOG 2
#define OP_DEL_BOAT_LOG 3
#define OP_UPD_BOAT_LOG 4

int CDataBoatRobLog::Add(const DataBoatRobLog &data) {
	DB_ENCODE_BEGIN(DB_BOAT_ROB_LOG, OP_ADD_BOAT_LOG);
	if (!data.Encode(writer)) {
		return R_ERR_DATA;
	}
	DB_ENCODE_END;
	return 0;
}
int CDataBoatRobLog::Get(uint32_t uid, vector<DataBoatRobLog> &datas) {
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(ts);
	DBCREQ_NEED(userid);
	DBCREQ_NEED(res);
	DBCREQ_NEED(exp);
	DBCREQ_NEED(type);
	DBCREQ_NEED(win);
	DBCREQ_NEED(star);
	DBCREQ_NEED(damage);
	DBCREQ_NEED(train_id);
	DBCREQ_NEED(revenge_count);
	DBCREQ_NEED(username);
	DBCREQ_NEED(soldier);
	DBCREQ_NEED(tower);
	DBCREQ_NEED(soldier_dead);
	DBCREQ_NEED(skill);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;

	DBCREQ_ARRAY_GET_BEGIN(datas);
	DBCREQ_ARRAY_GET_INT(datas, uid);
	DBCREQ_ARRAY_GET_INT(datas, ts);
	DBCREQ_ARRAY_GET_INT(datas, userid);
	DBCREQ_ARRAY_GET_INT(datas, res);
	DBCREQ_ARRAY_GET_INT(datas, exp);
	DBCREQ_ARRAY_GET_INT(datas, type);
	DBCREQ_ARRAY_GET_INT(datas, win);
	DBCREQ_ARRAY_GET_INT(datas, star);
	DBCREQ_ARRAY_GET_INT(datas, damage);
	DBCREQ_ARRAY_GET_INT(datas, train_id);
	DBCREQ_ARRAY_GET_INT(datas, revenge_count);
	DBCREQ_ARRAY_GET_STR(datas, username);
	DBCREQ_ARRAY_GET_STR(datas, soldier);
	DBCREQ_ARRAY_GET_STR(datas, tower);
	DBCREQ_ARRAY_GET_STR(datas, soldier_dead);
	DBCREQ_ARRAY_GET_STR(datas, skill);
	DBCREQ_ARRAY_GET_END();

	return 0;
}
int CDataBoatRobLog::GetLimit(uint32_t uid, vector<DataBoatRobLog> &datas) {
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(ts);
	DBCREQ_NEED(userid);
	DBCREQ_NEED(res);
	DBCREQ_NEED(type);
	DBCREQ_NEED(train_id);
	DBCREQ_NEED(revenge_count);
	DBCREQ_NEED(username);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;

	DBCREQ_ARRAY_GET_BEGIN(datas);
	DBCREQ_ARRAY_GET_INT(datas, uid);
	DBCREQ_ARRAY_GET_INT(datas, ts);
	DBCREQ_ARRAY_GET_INT(datas, userid);
	DBCREQ_ARRAY_GET_INT(datas, res);
	DBCREQ_ARRAY_GET_INT(datas, type);
	DBCREQ_ARRAY_GET_INT(datas, train_id);
	DBCREQ_ARRAY_GET_INT(datas, revenge_count);
	DBCREQ_ARRAY_GET_STR(datas, username);
	DBCREQ_ARRAY_GET_END();

	return 0;
}
int CDataBoatRobLog::Get(uint32_t uid, uint32_t ts, DataBoatRobLog &data) {
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);
	DBCREQ_SET_CONDITION(EQ, ts, ts);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(ts);
	DBCREQ_NEED(userid);
	DBCREQ_NEED(res);
	DBCREQ_NEED(exp);
	DBCREQ_NEED(type);
	DBCREQ_NEED(win);
	DBCREQ_NEED(star);
	DBCREQ_NEED(damage);
	DBCREQ_NEED(train_id);
	DBCREQ_NEED(revenge_count);
	DBCREQ_NEED(username);
	DBCREQ_NEED(soldier);
	DBCREQ_NEED(tower);
	DBCREQ_NEED(soldier_dead);
	DBCREQ_NEED(skill);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;
	DBCREQ_IFFETCHROW;

	DBCREQ_GET_BEGIN();
	DBCREQ_GET_INT(data, uid);
	DBCREQ_GET_INT(data, ts);
	DBCREQ_GET_INT(data, userid);
	DBCREQ_GET_INT(data, res);
	DBCREQ_GET_INT(data, exp);
	DBCREQ_GET_INT(data, type);
	DBCREQ_GET_INT(data, win);
	DBCREQ_GET_INT(data, star);
	DBCREQ_GET_INT(data, damage);
	DBCREQ_GET_INT(data, train_id);
	DBCREQ_GET_INT(data, revenge_count);
	DBCREQ_GET_STR(data, username);
	DBCREQ_GET_STR(data, soldier);
	DBCREQ_GET_STR(data, tower);
	DBCREQ_GET_STR(data, soldier_dead);
	DBCREQ_GET_STR(data, skill);

	return 0;
}
int CDataBoatRobLog::GetRevengeCount(uint32_t uid, uint32_t ts, byte &revenge_count) {
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);
	DBCREQ_SET_CONDITION(EQ, ts, ts);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(revenge_count);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;
	DBCREQ_IFFETCHROW;

	DBCREQ_GET_BEGIN();
	DBCREQ_GET_INT_S(revenge_count);

	return 0;
}
int CDataBoatRobLog::SetRevengeCount(uint32_t uid, uint32_t ts, byte revenge_count) {
	DB_ENCODE_BEGIN(DB_BOAT_ROB_LOG, OP_UPD_BOAT_LOG);
	writer.AppendInt32(uid);
	writer.AppendInt32(ts);
	writer.AppendByte(revenge_count);
	DB_ENCODE_END;
	return 0;
}
int CDataBoatRobLog::Set(const DataBoatRobLog &data) {
	DB_ENCODE_BEGIN(DB_BOAT_ROB_LOG, OP_SET_BOAT_LOG);
	if (!data.Encode(writer)) {
		return R_ERR_DATA;
	}
	DB_ENCODE_END;
	return 0;
}
int CDataBoatRobLog::Del(uint32_t uid, uint32_t ts) {
	DataBoatRobLog data;
	data.uid = uid;
	data.ts = ts;

	DB_ENCODE_BEGIN(DB_BOAT_ROB_LOG, OP_DEL_BOAT_LOG);
	if (!data.Encode(writer)) {
		return R_ERR_DATA;
	}
	DB_ENCODE_END;
	return 0;
}
int CDataBoatRobLog::RealAdd(CNetPacket *packet) {
	DataBoatRobLog data;
	DB_DECODE_BEGIN(packet->GetBody());
	if (!data.Decode(reader)) {
		return R_ERR_DATA;
	}

	DBCREQ_DECLARE(DBC::InsertRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_SET_INT(data, ts);
	DBCREQ_SET_INT(data, userid);
	DBCREQ_SET_INT(data, res);
	DBCREQ_SET_INT(data, exp);
	DBCREQ_SET_INT(data, type);
	DBCREQ_SET_INT(data, win);
	DBCREQ_SET_INT(data, star);
	DBCREQ_SET_INT(data, damage);
	DBCREQ_SET_INT(data, train_id);
	DBCREQ_SET_INT(data, revenge_count);
	DBCREQ_SET_STR(data, username);
	DBCREQ_SET_STR(data, soldier);
	DBCREQ_SET_STR(data, tower);
	DBCREQ_SET_STR(data, soldier_dead);
	DBCREQ_SET_STR(data, skill);

	DBCREQ_EXEC;

	return 0;
}
int CDataBoatRobLog::RealSet(CNetPacket *packet) {
	DataBoatRobLog data;
	DB_DECODE_BEGIN(packet->GetBody());
	if (!data.Decode(reader)) {
		return R_ERR_DATA;
	}

	DBCREQ_DECLARE(DBC::UpdateRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_CONDITION(EQ, ts, data.ts);

	DBCREQ_SET_INT(data, userid);
	DBCREQ_SET_INT(data, res);
	DBCREQ_SET_INT(data, exp);
	DBCREQ_SET_INT(data, type);
	DBCREQ_SET_INT(data, win);
	DBCREQ_SET_INT(data, star);
	DBCREQ_SET_INT(data, damage);
	DBCREQ_SET_INT(data, train_id);
	DBCREQ_SET_INT(data, revenge_count);
	DBCREQ_SET_STR(data, username);
	DBCREQ_SET_STR(data, soldier);
	DBCREQ_SET_STR(data, tower);
	DBCREQ_SET_STR(data, soldier_dead);
	DBCREQ_SET_STR(data, skill);

	DBCREQ_EXEC;

	return 0;
}
int CDataBoatRobLog::RealDel(CNetPacket *packet) {
	DataBoatRobLog data;
	DB_DECODE_BEGIN(packet->GetBody());
	if (!data.Decode(reader)) {
		return R_ERR_DATA;
	}

	DBCREQ_DECLARE(DBC::DeleteRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_CONDITION(EQ, ts, data.ts);
	DBCREQ_EXEC
	return 0;
}
int CDataBoatRobLog::RealSetRevengeCount(CNetPacket *packet) {
	DB_DECODE_BEGIN(packet->GetBody());
	uint32_t uid = 0;
	reader.GetUInt32(uid);
	uint32_t ts = 0;
	reader.GetUInt32(ts);
	byte revenge_count = 0;
	reader.GetByte(revenge_count);

	DBCREQ_DECLARE(DBC::UpdateRequest, uid);
	DBCREQ_SET_KEY(uid);
	DBCREQ_SET_CONDITION(EQ, ts, ts);
	DBCREQ_SET_INT_S(revenge_count);
	DBCREQ_EXEC
	return 0;
}

OP_PROCESS_BEGIN(CDataBoatRobLog)
OP_PROCESS(OP_ADD_BOAT_LOG, RealAdd)
OP_PROCESS(OP_SET_BOAT_LOG, RealSet)
OP_PROCESS(OP_DEL_BOAT_LOG, RealDel)
OP_PROCESS(OP_UPD_BOAT_LOG, RealSetRevengeCount)
OP_PROCESS_END
