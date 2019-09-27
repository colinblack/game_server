/*
 * DataActivity.cpp
 *
 *  Created on: 2018年12月3日
 *      Author: Administrator
 */

#include "DataActivity.h"
#include "AsyncDBManager.h"

void CDataActivity::doRequest(CNetPacket *p) {
	switch (p->stime) {
	case e_DBAsyncTypeAdd:
		Add(p);
		break;
	case e_DBAsyncTypeSet:
		Set(p);
		break;
	case e_DBAsyncTypeDel:
		Del(p);
		break;
	}
}

int CDataActivity::Add(const DataActivity &data) {
	DB_ENCODE_BEGIN(DB_ACTIVITY, e_DBAsyncTypeAdd);
	if (!data.Encode(writer)) {
		return -1;
	}
	DB_ENCODE_END;
	return 0;
}
int CDataActivity::Set(const DataActivity &data) {
	DB_ENCODE_BEGIN(DB_ACTIVITY, e_DBAsyncTypeSet);
	if (!data.Encode(writer)) {
		return -1;
	}
	DB_ENCODE_END;
	return 0;
}
int CDataActivity::Get(uint32_t uid, uint32_t id, DataActivity &data) {
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);
	DBCREQ_SET_CONDITION(EQ, id, id);
	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(id);
	DBCREQ_NEED(ver);
	DBCREQ_NEED(ts);
	DBCREQ_NEED(score);
	DBCREQ_NEED(flag);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;
	DBCREQ_IFFETCHROW;

	DBCREQ_GET_BEGIN();
	DBCREQ_GET_INT(data, uid);
	DBCREQ_GET_INT(data, id);
	DBCREQ_GET_INT(data, ver);
	DBCREQ_GET_INT(data, ts);
	DBCREQ_GET_INT(data, score);
	DBCREQ_GET_INT(data, flag);

	return 0;
}

int CDataActivity::Get(uint32_t uid, vector<DataActivity> &datas) {
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(id);
	DBCREQ_NEED(ver);
	DBCREQ_NEED(ts);
	DBCREQ_NEED(score);
	DBCREQ_NEED(flag);

	DBCREQ_EXEC;

	DBCREQ_ARRAY_GET_BEGIN(datas);
	DBCREQ_ARRAY_GET_INT(datas, uid);
	DBCREQ_ARRAY_GET_INT(datas, id);
	DBCREQ_ARRAY_GET_INT(datas, ver);
	DBCREQ_ARRAY_GET_INT(datas, ts);
	DBCREQ_ARRAY_GET_INT(datas, score);
	DBCREQ_ARRAY_GET_INT(datas, flag);
	DBCREQ_ARRAY_GET_END();

	return 0;
}

int CDataActivity::Del(uint32_t uid) {
	DataActivity data;
	data.uid = uid;
	DB_ENCODE_BEGIN(DB_ACTIVITY, e_DBAsyncTypeDel);
	if (!data.Encode(writer)) {
		return -1;
	}
	DB_ENCODE_END;
	return 0;
}

int CDataActivity::Add(CNetPacket *p) {
	DataActivity data;
	DB_DECODE_BEGIN(p->GetBody());
	if (!data.Decode(reader)) {
		return -1;
	}
	DB_DECODE_END;

	DBCREQ_DECLARE(DBC::InsertRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_INT(data, id);
	DBCREQ_SET_INT(data, ver);
	DBCREQ_SET_INT(data, ts);
	DBCREQ_SET_INT(data, score);
	DBCREQ_SET_INT(data, flag);
	DBCREQ_EXEC;

	return 0;
}
int CDataActivity::Set(CNetPacket *p) {
	DataActivity data;
	DB_DECODE_BEGIN(p->GetBody());
	if (!data.Decode(reader)) {
		return -1;
	}
	DB_DECODE_END;

	DBCREQ_DECLARE(DBC::UpdateRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_CONDITION(EQ, id, data.id);
	DBCREQ_SET_INT(data, ver);
	DBCREQ_SET_INT(data, ts);
	DBCREQ_SET_INT(data, score);
	DBCREQ_SET_INT(data, flag);
	DBCREQ_EXEC;
	return 0;
}
int CDataActivity::Del(CNetPacket *p) {
	DataActivity data;
	DB_DECODE_BEGIN(p->GetBody());
	if (!data.Decode(reader)) {
		return -1;
	}
	DB_DECODE_END;

	DBCREQ_DECLARE(DBC::DeleteRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_EXEC;
	return 0;
}

int CDataActivity::TestAdd(const DataActivity &data) {
	DBCREQ_DECLARE(DBC::InsertRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_INT(data, id);
	DBCREQ_SET_INT(data, ver);
	DBCREQ_SET_INT(data, ts);
	DBCREQ_SET_INT(data, score);
	DBCREQ_SET_INT(data, flag);
	DBCREQ_EXEC;
	return 0;
}

int CDataActivity::TestSet(const DataActivity &data) {
	DBCREQ_DECLARE(DBC::UpdateRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_CONDITION(EQ, id, data.id);
	DBCREQ_SET_INT(data, ver);
	DBCREQ_SET_INT(data, ts);
	DBCREQ_SET_INT(data, score);
	DBCREQ_SET_INT(data, flag);
	DBCREQ_EXEC;
	return 0;
}
