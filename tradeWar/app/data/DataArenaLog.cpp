/*
 * DataArenaLog.cpp
 *
 *  Created on: 2019年2月27日
 *      Author: Administrator
 */

#include "DataArenaLog.h"
#include "AsyncDBManager.h"

void CDataArenaLog::doRequest(CNetPacket *p) {
	int ret = 0;
	switch (p->stime) {
	case e_DBAsyncTypeAdd:
		ret = Add(p);
		break;
	case e_DBAsyncTypeSet:
		ret = Set(p);
		break;
	case e_DBAsyncTypeDel:
		ret = Del(p);
		break;
	default:
		ret = R_ERR_PARAM;
		break;
	}
	if (0 != ret) {
		error_log("ret=%d,op=%u", ret, p->stime);
	}
}
int CDataArenaLog::Get(uint32_t uid, vector<DataArenaLog> &datas) {
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(ts);
	DBCREQ_NEED(userid);
	DBCREQ_NEED(from_rank);
	DBCREQ_NEED(to_rank);
	DBCREQ_NEED(win);
	DBCREQ_NEED(type);
	DBCREQ_NEED(userlevel);
	DBCREQ_NEED(username);
	DBCREQ_NEED(pic);
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
	DBCREQ_ARRAY_GET_INT(datas, from_rank);
	DBCREQ_ARRAY_GET_INT(datas, to_rank);
	DBCREQ_ARRAY_GET_INT(datas, win);
	DBCREQ_ARRAY_GET_INT(datas, type);
	DBCREQ_ARRAY_GET_INT(datas, userlevel);
	DBCREQ_ARRAY_GET_STR(datas, username);
	DBCREQ_ARRAY_GET_STR(datas, pic);
	DBCREQ_ARRAY_GET_STR(datas, soldier);
	DBCREQ_ARRAY_GET_STR(datas, tower);
	DBCREQ_ARRAY_GET_STR(datas, soldier_dead);
	DBCREQ_ARRAY_GET_STR(datas, skill);
	DBCREQ_ARRAY_GET_END();

	return 0;
}
int CDataArenaLog::Add(const DataArenaLog &data) {
	DB_ENCODE_BEGIN(DB_ARENA_LOG, e_DBAsyncTypeAdd);
	if (!data.Encode(writer)) {
		return -1;
	}
	DB_ENCODE_END;
	return 0;
}
int CDataArenaLog::Set(const DataArenaLog &data) {
	DB_ENCODE_BEGIN(DB_ARENA_LOG, e_DBAsyncTypeSet);
	if (!data.Encode(writer)) {
		return -1;
	}
	DB_ENCODE_END;
	return 0;
}
int CDataArenaLog::Del(uint32_t uid, uint32_t ts) {
	DataArenaLog data;
	data.uid = uid;
	data.ts = ts;
	DB_ENCODE_BEGIN(DB_ARENA_LOG, e_DBAsyncTypeDel);
	if (!data.Encode(writer)) {
		return -1;
	}
	DB_ENCODE_END;
	return 0;
}
int CDataArenaLog::Add(CNetPacket *p) {
	DataArenaLog data;
	DB_DECODE_BEGIN(p->GetBody());
	if (!data.Decode(reader)) {
		return R_ERR_DATA;
	}
	DBCREQ_DECLARE(DBC::InsertRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_INT(data, ts);
	DBCREQ_SET_INT(data, userid);
	DBCREQ_SET_INT(data, from_rank);
	DBCREQ_SET_INT(data, to_rank);
	DBCREQ_SET_INT(data, win);
	DBCREQ_SET_INT(data, type);
	DBCREQ_SET_INT(data, userlevel);
	DBCREQ_SET_STR(data, username);
	DBCREQ_SET_STR(data, pic);
	DBCREQ_SET_STR(data, soldier);
	DBCREQ_SET_STR(data, tower);
	DBCREQ_SET_STR(data, soldier_dead);
	DBCREQ_SET_STR(data, skill);
	DBCREQ_EXEC;
	return 0;
}
int CDataArenaLog::Set(CNetPacket *p) {
	DataArenaLog data;
	DB_DECODE_BEGIN(p->GetBody());
	if (!data.Decode(reader)) {
		return R_ERR_DATA;
	}
	DBCREQ_DECLARE(DBC::UpdateRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_CONDITION(EQ, ts, data.ts);
	DBCREQ_SET_INT(data, userid);
	DBCREQ_SET_INT(data, from_rank);
	DBCREQ_SET_INT(data, to_rank);
	DBCREQ_SET_INT(data, win);
	DBCREQ_SET_INT(data, type);
	DBCREQ_SET_INT(data, userlevel);
	DBCREQ_SET_STR(data, username);
	DBCREQ_SET_STR(data, pic);
	DBCREQ_SET_STR(data, soldier);
	DBCREQ_SET_STR(data, tower);
	DBCREQ_SET_STR(data, soldier_dead);
	DBCREQ_SET_STR(data, skill);
	DBCREQ_EXEC;
	return 0;
}
int CDataArenaLog::Del(CNetPacket *p) {
	DataArenaLog data;
	DB_DECODE_BEGIN(p->GetBody());
	if (!data.Decode(reader)) {
		return R_ERR_DATA;
	}
	DBCREQ_DECLARE(DBC::DeleteRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_CONDITION(EQ, ts, data.ts);
	DBCREQ_EXEC;
	return 0;
}
