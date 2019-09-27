/*
 * DataBoatTrain.cpp
 *
 *  Created on: 2018年11月8日
 *      Author: Administrator
 */

#include "DataBoatTrain.h"
#include "AsyncDBManager.h"

enum {
	REQ_ADD = 1,
	REQ_SET = 2,
	REQ_DEL = 3
};

void CDataBoatTrain::doRequest(CNetPacket* p) {
	switch (p->stime) {
	case REQ_ADD:
		Add(p);
		break;
	case REQ_SET:
		Set(p);
		break;
	case REQ_DEL:
		Del(p);
		break;
	}
}

int CDataBoatTrain::Add(const DataBoatTrain &data) {
	DB_ENCODE_BEGIN(DB_BOAT_TRAIN, REQ_ADD);
	if (!data.Encode(writer)) {
		return R_ERR_DATA;
	}
	DB_ENCODE_END;
	return 0;
}
int CDataBoatTrain::Set(const DataBoatTrain &data) {
	DB_ENCODE_BEGIN(DB_BOAT_TRAIN, REQ_SET);
	if (!data.Encode(writer)) {
		return R_ERR_DATA;
	}
	DB_ENCODE_END;
	return 0;
}
int CDataBoatTrain::Get(uint32_t uid, vector<DataBoatTrain> &datas) {
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(start_ts);
	DBCREQ_NEED(end_ts);
	DBCREQ_NEED(total_res);
	DBCREQ_NEED(lost_res);
	DBCREQ_NEED(used_count);
	DBCREQ_NEED(id);
	DBCREQ_NEED(level);
	DBCREQ_NEED(first);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;

	DBCREQ_ARRAY_GET_BEGIN(datas);
	DBCREQ_ARRAY_GET_INT(datas, uid);
	DBCREQ_ARRAY_GET_INT(datas, start_ts);
	DBCREQ_ARRAY_GET_INT(datas, end_ts);
	DBCREQ_ARRAY_GET_INT(datas, total_res);
	DBCREQ_ARRAY_GET_INT(datas, lost_res);
	DBCREQ_ARRAY_GET_INT(datas, used_count);
	DBCREQ_ARRAY_GET_INT(datas, id);
	DBCREQ_ARRAY_GET_INT(datas, level);
	DBCREQ_ARRAY_GET_INT(datas, first);
	DBCREQ_ARRAY_GET_END();

	return 0;
}
int CDataBoatTrain::Get(uint32_t uid, uint8_t id, DataBoatTrain &data) {
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);
	DBCREQ_SET_CONDITION(EQ, id, id);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(start_ts);
	DBCREQ_NEED(end_ts);
	DBCREQ_NEED(total_res);
	DBCREQ_NEED(lost_res);
	DBCREQ_NEED(used_count);
	DBCREQ_NEED(id);
	DBCREQ_NEED(level);
	DBCREQ_NEED(first);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;
	DBCREQ_IFFETCHROW;

	DBCREQ_GET_BEGIN();
	DBCREQ_GET_INT(data, uid);
	DBCREQ_GET_INT(data, start_ts);
	DBCREQ_GET_INT(data, end_ts);
	DBCREQ_GET_INT(data, total_res);
	DBCREQ_GET_INT(data, lost_res);
	DBCREQ_GET_INT(data, used_count);
	DBCREQ_GET_INT(data, id);
	DBCREQ_GET_INT(data, level);
	DBCREQ_GET_INT(data, first);

	return 0;
}
int CDataBoatTrain::Del(uint32_t uid) {
	DataBoatTrain data;
	data.uid = uid;
	DB_ENCODE_BEGIN(DB_BOAT_TRAIN, REQ_DEL);
	if (!data.Encode(writer)) {
		return R_ERR_DATA;
	}
	DB_ENCODE_END;
	return 0;
}
int CDataBoatTrain::Add(CNetPacket *p) {
	DataBoatTrain data;
	DB_DECODE_BEGIN(p->GetBody());
	if (!data.Decode(reader)) {
		return R_ERR_DATA;
	}
	DBCREQ_DECLARE(DBC::InsertRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_INT(data, start_ts);
	DBCREQ_SET_INT(data, end_ts);
	DBCREQ_SET_INT(data, total_res);
	DBCREQ_SET_INT(data, lost_res);
	DBCREQ_SET_INT(data, used_count);
	DBCREQ_SET_INT(data, id);
	DBCREQ_SET_INT(data, level);
	DBCREQ_SET_INT(data, first);
	DBCREQ_EXEC;
	return 0;
}
int CDataBoatTrain::Set(CNetPacket *p) {
	DataBoatTrain data;
	DB_DECODE_BEGIN(p->GetBody());
	if (!data.Decode(reader)) {
		return R_ERR_DATA;
	}
	DBCREQ_DECLARE(DBC::UpdateRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_CONDITION(EQ, id, data.id);
	DBCREQ_SET_INT(data, start_ts);
	DBCREQ_SET_INT(data, end_ts);
	DBCREQ_SET_INT(data, total_res);
	DBCREQ_SET_INT(data, lost_res);
	DBCREQ_SET_INT(data, used_count);
	DBCREQ_SET_INT(data, level);
	DBCREQ_SET_INT(data, first);
	DBCREQ_EXEC;
	return 0;
}
int CDataBoatTrain::Del(CNetPacket *p) {
	DataBoatTrain data;
	DB_DECODE_BEGIN(p->GetBody());
	if (!data.Decode(reader)) {
		return R_ERR_DATA;
	}
	DBCREQ_DECLARE(DBC::DeleteRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_EXEC;
	return 0;
}

