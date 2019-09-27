/*
 * DataGuard.cpp
 *
 *  Created on: 2019年3月15日
 *      Author: Administrator
 */

#include "DataGuard.h"
#include "AsyncDBManager.h"

void CDataGuard::doRequest(CNetPacket *p) {
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
int CDataGuard::Get(uint32_t uid, vector<DataGuard> &datas) {
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(id);
	DBCREQ_NEED(soldier);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;

	DBCREQ_ARRAY_GET_BEGIN(datas);
	DBCREQ_ARRAY_GET_INT(datas, uid);
	DBCREQ_ARRAY_GET_INT(datas, id);
	DBCREQ_ARRAY_GET_INT(datas, soldier);
	DBCREQ_ARRAY_GET_END();

	return 0;
}
int CDataGuard::Add(const DataGuard &data) {
	DB_ENCODE_BEGIN(DB_GUARD, e_DBAsyncTypeAdd);
	if (!data.Encode(writer)) {
		return -1;
	}
	DB_ENCODE_END;
	return 0;
}
int CDataGuard::Set(const DataGuard &data) {
	DB_ENCODE_BEGIN(DB_GUARD, e_DBAsyncTypeSet);
	if (!data.Encode(writer)) {
		return -1;
	}
	DB_ENCODE_END;
	return 0;
}
int CDataGuard::Del(uint32_t uid, uint32_t id) {
	DataGuard data;
	data.uid = uid;
	data.id = id;
	DB_ENCODE_BEGIN(DB_GUARD, e_DBAsyncTypeDel);
	if (!data.Encode(writer)) {
		return -1;
	}
	DB_ENCODE_END;
	return 0;
}
int CDataGuard::Add(CNetPacket *p) {
	DataGuard data;
	DB_DECODE_BEGIN(p->GetBody());
	if (!data.Decode(reader)) {
		return R_ERR_DATA;
	}
	DBCREQ_DECLARE(DBC::InsertRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_INT(data, id);
	DBCREQ_SET_INT(data, soldier);
	DBCREQ_EXEC;
	return 0;
}
int CDataGuard::Set(CNetPacket *p) {
	DataGuard data;
	DB_DECODE_BEGIN(p->GetBody());
	if (!data.Decode(reader)) {
		return R_ERR_DATA;
	}
	DBCREQ_DECLARE(DBC::UpdateRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_CONDITION(EQ, id, data.id);
	DBCREQ_SET_INT(data, soldier);
	DBCREQ_EXEC;
	return 0;
}
int CDataGuard::Del(CNetPacket *p) {
	DataGuard data;
	DB_DECODE_BEGIN(p->GetBody());
	if (!data.Decode(reader)) {
		return R_ERR_DATA;
	}
	DBCREQ_DECLARE(DBC::DeleteRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	if (data.id > 0) {
		DBCREQ_SET_CONDITION(EQ, id, data.id);
	}
	DBCREQ_EXEC;
	return 0;
}
