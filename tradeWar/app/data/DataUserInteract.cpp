/*
 * DataUserInteract.cpp
 *
 *  Created on: 2019年3月5日
 *      Author: Administrator
 */

#include "DataUserInteract.h"
#include "AsyncDBManager.h"

void CDataUserInteract::doRequest(CNetPacket *packet) {
	switch (packet->stime) {
	case e_DBAsyncTypeAdd:
		Add(packet);
		break;
	case e_DBAsyncTypeSet:
		Set(packet);
		break;
	case e_DBAsyncTypeDel:
		Del(packet);
		break;
	}
}
int CDataUserInteract::Get(uint32_t uid, uint32_t ouid, DataUserInteract &data) {
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);
	DBCREQ_SET_CONDITION(EQ, ouid, ouid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(ouid);
	DBCREQ_NEED(ts);
	DBCREQ_NEED(level);
	DBCREQ_NEED(help_type);
	DBCREQ_NEED(username);
	DBCREQ_NEED(pic);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;
	DBCREQ_IFFETCHROW;

	DBCREQ_GET_BEGIN();
	DBCREQ_GET_INT(data, uid);
	DBCREQ_GET_INT(data, ouid);
	DBCREQ_GET_INT(data, ts);
	DBCREQ_GET_INT(data, level);
	DBCREQ_GET_INT(data, help_type);
	DBCREQ_GET_STR(data, username);
	DBCREQ_GET_STR(data, pic);

	return 0;
}
int CDataUserInteract::Get(uint32_t uid, vector<DataUserInteract> &datas) {
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(ouid);
	DBCREQ_NEED(ts);
	DBCREQ_NEED(level);
	DBCREQ_NEED(help_type);
	DBCREQ_NEED(username);
	DBCREQ_NEED(pic);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;

	DBCREQ_ARRAY_GET_BEGIN(datas);
	DBCREQ_ARRAY_GET_INT(datas, uid);
	DBCREQ_ARRAY_GET_INT(datas, ouid);
	DBCREQ_ARRAY_GET_INT(datas, ts);
	DBCREQ_ARRAY_GET_INT(datas, level);
	DBCREQ_ARRAY_GET_INT(datas, help_type);
	DBCREQ_ARRAY_GET_STR(datas, username);
	DBCREQ_ARRAY_GET_STR(datas, pic);
	DBCREQ_ARRAY_GET_END();

	return 0;
}
int CDataUserInteract::Add(const DataUserInteract &data) {
	DB_ENCODE_BEGIN(DB_USER_INTERACT, e_DBAsyncTypeAdd);
	if (!data.Encode(writer)) {
		return -1;
	}
	DB_ENCODE_END;
	return 0;
}
int CDataUserInteract::Set(const DataUserInteract &data) {
	DB_ENCODE_BEGIN(DB_USER_INTERACT, e_DBAsyncTypeSet);
	if (!data.Encode(writer)) {
		return -1;
	}
	DB_ENCODE_END;
	return 0;
}
int CDataUserInteract::Del(uint32_t uid, uint32_t ouid, uint32_t ts) {
	DataUserInteract data;
	data.uid = uid;
	data.ouid = ouid;
	data.ts = ts;
	DB_ENCODE_BEGIN(DB_USER_INTERACT, e_DBAsyncTypeDel);
	if (!data.Encode(writer)) {
		return -1;
	}
	DB_ENCODE_END;
	return 0;
}
int CDataUserInteract::Add(CNetPacket *packet) {
	DataUserInteract data;
	DB_DECODE_BEGIN(packet->GetBody());
	if (!data.Decode(reader)) {
		return R_ERR_DATA;
	}
	DBCREQ_DECLARE(DBC::InsertRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_INT(data, ouid);
	DBCREQ_SET_INT(data, ts);
	DBCREQ_SET_INT(data, level);
	DBCREQ_SET_INT(data, help_type);
	DBCREQ_SET_STR(data, username);
	DBCREQ_SET_STR(data, pic);
	DBCREQ_EXEC;
	return 0;
}
int CDataUserInteract::Set(CNetPacket *packet) {
	DataUserInteract data;
	DB_DECODE_BEGIN(packet->GetBody());
	if (!data.Decode(reader)) {
		return R_ERR_DATA;
	}
	DBCREQ_DECLARE(DBC::UpdateRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_CONDITION(EQ, ouid, data.ouid);
	DBCREQ_SET_INT(data, ts);
	DBCREQ_SET_INT(data, level);
	DBCREQ_SET_INT(data, help_type);
	DBCREQ_SET_STR(data, username);
	DBCREQ_SET_STR(data, pic);
	DBCREQ_EXEC;
	return 0;
}
int CDataUserInteract::Del(CNetPacket *packet) {
	DataUserInteract data;
	DB_DECODE_BEGIN(packet->GetBody());
	if (!data.Decode(reader)) {
		return R_ERR_DATA;
	}
	DBCREQ_DECLARE(DBC::DeleteRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_CONDITION(EQ, ouid, data.ouid);
	DBCREQ_SET_CONDITION(EQ, ts, data.ts);
	DBCREQ_EXEC;
	return 0;
}
