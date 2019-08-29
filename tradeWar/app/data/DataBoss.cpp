/*
 * DataBoss.cpp
 *
 *  Created on: 2019年2月25日
 *      Author: Administrator
 */

#include "DataBoss.h"
#include "AsyncDBManager.h"

void CDataBoss::doRequest(CNetPacket *p) {
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

int CDataBoss::Get(uint32_t uid, DataBoss &data) {

	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(ts);
	DBCREQ_NEED(curr_hurt);
	DBCREQ_NEED(curr_id);
	DBCREQ_NEED(total_hurt);
	DBCREQ_NEED(soldier);
	DBCREQ_NEED(shop);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;
	DBCREQ_IFFETCHROW;

	DBCREQ_GET_BEGIN();
	DBCREQ_GET_INT(data, uid);
	DBCREQ_GET_INT(data, ts);
	DBCREQ_GET_INT(data, curr_hurt);
	DBCREQ_GET_INT(data, curr_id);
	DBCREQ_GET_INT(data, total_hurt);
	DBCREQ_GET_STR(data, soldier);
	DBCREQ_GET_STR(data, shop);

	return 0;
}

int CDataBoss::Add(const DataBoss &data) {
	DB_ENCODE_BEGIN(DB_BOSS, e_DBAsyncTypeAdd);
	if (!data.Encode(writer)) {
		return -1;
	}
	DB_ENCODE_END;
	return 0;
}

int CDataBoss::Set(const DataBoss &data) {
	DB_ENCODE_BEGIN(DB_BOSS, e_DBAsyncTypeSet);
	if (!data.Encode(writer)) {
		return -1;
	}
	DB_ENCODE_END;
	return 0;
}

int CDataBoss::Del(uint32_t uid) {
	DataBoss data;
	data.uid = uid;
	DB_ENCODE_BEGIN(DB_BOSS, e_DBAsyncTypeDel);
	if (!data.Encode(writer)) {
		return -1;
	}
	DB_ENCODE_END;
	return 0;
}

int CDataBoss::Add(CNetPacket *p) {
	DataBoss data;
	DB_DECODE_BEGIN(p->GetBody());
	if (!data.Decode(reader)) {
		return R_ERR_DATA;
	}
	DBCREQ_DECLARE(DBC::InsertRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_INT(data, ts);
	DBCREQ_SET_INT(data, curr_hurt);
	DBCREQ_SET_INT(data, curr_id);
	DBCREQ_SET_INT(data, total_hurt);
	DBCREQ_SET_STR(data, soldier);
	DBCREQ_SET_STR(data, shop);
	DBCREQ_EXEC;
	return 0;
}

int CDataBoss::Set(CNetPacket *p) {
	DataBoss data;
	DB_DECODE_BEGIN(p->GetBody());
	if (!data.Decode(reader)) {
		return R_ERR_DATA;
	}
	DBCREQ_DECLARE(DBC::UpdateRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_INT(data, ts);
	DBCREQ_SET_INT(data, curr_hurt);
	DBCREQ_SET_INT(data, curr_id);
	DBCREQ_SET_INT(data, total_hurt);
	DBCREQ_SET_STR(data, soldier);
	DBCREQ_SET_STR(data, shop);
	DBCREQ_EXEC;
	return 0;
}

int CDataBoss::Del(CNetPacket *p) {
	DataBoss data;
	DB_DECODE_BEGIN(p->GetBody());
	if (!data.Decode(reader)) {
		return R_ERR_DATA;
	}
	DBCREQ_DECLARE(DBC::DeleteRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_EXEC;
	return 0;
}
