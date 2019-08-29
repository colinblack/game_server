/*
 * DataGemPoint.cpp
 *
 *  Created on: 2019年1月4日
 *      Author: Administrator
 */

#include "DataGemPoint.h"
#include "AsyncDBManager.h"

void CDataGemPoint::doRequest(CNetPacket* p) {
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

int CDataGemPoint::Get(uint32_t uid, uint32_t id, DataGemPoint &data) {
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);
	DBCREQ_SET_CONDITION(EQ, id, id);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(id);
	DBCREQ_NEED(p1);
	DBCREQ_NEED(p2);
	DBCREQ_NEED(p3);
	DBCREQ_NEED(p4);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;
	DBCREQ_IFFETCHROW;

	DBCREQ_GET_BEGIN();
	DBCREQ_GET_INT(data, uid);
	DBCREQ_GET_INT(data, id);
	DBCREQ_GET_INT(data, p1);
	DBCREQ_GET_INT(data, p2);
	DBCREQ_GET_INT(data, p3);
	DBCREQ_GET_INT(data, p4);

	return 0;
}

int CDataGemPoint::Get(uint32_t uid, vector<DataGemPoint> &data) {
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(id);
	DBCREQ_NEED(p1);
	DBCREQ_NEED(p2);
	DBCREQ_NEED(p3);
	DBCREQ_NEED(p4);

	DBCREQ_EXEC;

	DBCREQ_ARRAY_GET_BEGIN(data);
	DBCREQ_ARRAY_GET_INT(data, uid);
	DBCREQ_ARRAY_GET_INT(data, id);
	DBCREQ_ARRAY_GET_INT(data, p1);
	DBCREQ_ARRAY_GET_INT(data, p2);
	DBCREQ_ARRAY_GET_INT(data, p3);
	DBCREQ_ARRAY_GET_INT(data, p4);
	DBCREQ_ARRAY_GET_END();

	return 0;
}

int CDataGemPoint::Add(const DataGemPoint &data) {
	DB_ENCODE_BEGIN(DB_GEM_POINT, e_DBAsyncTypeAdd);
	if (!data.Encode(writer)) {
		return -1;
	}
	DB_ENCODE_END;
	return 0;
}

int CDataGemPoint::Set(const DataGemPoint &data) {
	DB_ENCODE_BEGIN(DB_GEM_POINT, e_DBAsyncTypeSet);
	if (!data.Encode(writer)) {
		return -1;
	}
	DB_ENCODE_END;
	return 0;
}

int CDataGemPoint::Del(const DataGemPoint &data) {
	DB_ENCODE_BEGIN(DB_GEM_POINT, e_DBAsyncTypeDel);
	if (!data.Encode(writer)) {
		return -1;
	}
	DB_ENCODE_END;
	return 0;
}

int CDataGemPoint::Add(CNetPacket* p) {
	DataGemPoint data;
	DB_DECODE_BEGIN(p->GetBody());
	if (!data.Decode(reader)) {
		return -1;
	}
	DB_DECODE_END;

	DBCREQ_DECLARE(DBC::InsertRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_INT(data, id);
	DBCREQ_SET_INT(data, p1);
	DBCREQ_SET_INT(data, p2);
	DBCREQ_SET_INT(data, p3);
	DBCREQ_SET_INT(data, p4);
	DBCREQ_EXEC;

	return 0;
}

int CDataGemPoint::Set(CNetPacket* p) {
	DataGemPoint data;
	DB_DECODE_BEGIN(p->GetBody());
	if (!data.Decode(reader)) {
		return -1;
	}
	DB_DECODE_END;

	DBCREQ_DECLARE(DBC::UpdateRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_CONDITION(EQ, id, data.id);
	DBCREQ_SET_INT(data, p1);
	DBCREQ_SET_INT(data, p2);
	DBCREQ_SET_INT(data, p3);
	DBCREQ_SET_INT(data, p4);
	DBCREQ_EXEC;

	return 0;
}

int CDataGemPoint::Del(CNetPacket* p) {
	DataGemPoint data;
	DB_DECODE_BEGIN(p->GetBody());
	if (!data.Decode(reader)) {
		return -1;
	}
	DB_DECODE_END;

	DBCREQ_DECLARE(DBC::DeleteRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	if (data.id > 0) {
		DBCREQ_SET_CONDITION(EQ, id, data.id);
	}
	DBCREQ_EXEC;

	return 0;
}
