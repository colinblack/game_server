/*
* DataSocial.cpp
*
*  Created on: 2016-5-26
*      Author: Administrator
*/

#include "DataSocial.h"
#include "AsyncDBManager.h"

enum {
	REQ_ADD = 1,
	REQ_SET = 2,
	REQ_DEL = 3
};

void CDataSocial::doRequest(CNetPacket* packet) {
	switch (packet->stime) {
	case REQ_ADD:
		Add(packet);
		break;
	case REQ_SET:
		Set(packet);
		break;
	case REQ_DEL:
		Del(packet);
		break;
	}
}

int CDataSocial::Add(const DataSocial &data) {
	DB_ENCODE_BEGIN(DB_SOCIAL, REQ_ADD);
	if (!data.Encode(writer)) {
		return R_ERR_DATA;
	}
	DB_ENCODE_END;
	return 0;
}
int CDataSocial::Set(const DataSocial &data) {
	DB_ENCODE_BEGIN(DB_SOCIAL, REQ_SET);
	if (!data.Encode(writer)) {
		return R_ERR_DATA;
	}
	DB_ENCODE_END;
	return 0;
}
int CDataSocial::Get(uint32_t uid, vector<DataSocial> &datas) {
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(other_uid);
	DBCREQ_NEED(update_time);
	DBCREQ_NEED(pic);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;

	DBCREQ_ARRAY_GET_BEGIN(datas);
	DBCREQ_ARRAY_GET_INT(datas, uid);
	DBCREQ_ARRAY_GET_INT(datas, other_uid);
	DBCREQ_ARRAY_GET_INT(datas, update_time);
	DBCREQ_ARRAY_GET_STR(datas, pic);
	DBCREQ_ARRAY_GET_END();

	return 0;
}
int CDataSocial::Get(uint32_t uid, uint32_t other_uid, DataSocial &data) {
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);
	DBCREQ_SET_CONDITION(EQ, other_uid, other_uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(other_uid);
	DBCREQ_NEED(update_time);
	DBCREQ_NEED(pic);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;
	DBCREQ_IFFETCHROW;

	DBCREQ_GET_BEGIN();
	DBCREQ_GET_INT(data, uid);
	DBCREQ_GET_INT(data, other_uid);
	DBCREQ_GET_INT(data, update_time);
	DBCREQ_GET_STR(data, pic);

	return 0;
}
int CDataSocial::Del(unsigned uid) {
	DataSocial data;
	data.uid = uid;
	DB_ENCODE_BEGIN(DB_SOCIAL, REQ_DEL);
	if (!data.Encode(writer)) {
		return R_ERR_DATA;
	}
	DB_ENCODE_END;
	return 0;
}

int CDataSocial::Add(CNetPacket* packet) {
	DataSocial data;
	DB_DECODE_BEGIN(packet->GetBody());
	if (!data.Decode(reader)) {
		return R_ERR_DATA;
	}
	DBCREQ_DECLARE(DBC::InsertRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_INT(data, other_uid);
	DBCREQ_SET_INT(data, update_time);
	DBCREQ_SET_STR(data, pic);
	DBCREQ_EXEC;

	return 0;
}
int CDataSocial::Set(CNetPacket* packet) {
	DataSocial data;
	DB_DECODE_BEGIN(packet->GetBody());
	if (!data.Decode(reader)) {
		return R_ERR_DATA;
	}
	DBCREQ_DECLARE(DBC::UpdateRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_CONDITION(EQ, other_uid, data.other_uid);
	DBCREQ_SET_INT(data, update_time);
	DBCREQ_SET_STR(data, pic);
	DBCREQ_EXEC;

	return 0;
}
int CDataSocial::Del(CNetPacket* packet){

	DataSocial data;
	DB_DECODE_BEGIN(packet->GetBody());
	if (!data.Decode(reader)) {
		return R_ERR_DATA;
	}
	DBCREQ_DECLARE(DBC::DeleteRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_EXEC;
	return 0;
}

