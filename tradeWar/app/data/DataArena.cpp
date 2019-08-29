/*
 * DataArena.cpp
 *
 *  Created on: 2019年2月27日
 *      Author: Administrator
 */

#include "DataArena.h"
#include "AsyncDBManager.h"

void CDataArena::doRequest(CNetPacket *p) {
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
int CDataArena::Get(uint32_t uid, DataArena &data) {

	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(ts);
	DBCREQ_NEED(cd);
	DBCREQ_NEED(rank);
	DBCREQ_NEED(energy);
	DBCREQ_NEED(buy_energy);
	DBCREQ_NEED(shop_refresh);
	DBCREQ_NEED(shop);
	DBCREQ_NEED(target);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;
	DBCREQ_IFFETCHROW;

	DBCREQ_GET_BEGIN();
	DBCREQ_GET_INT(data, uid);
	DBCREQ_GET_INT(data, ts);
	DBCREQ_GET_INT(data, cd);
	DBCREQ_GET_INT(data, rank);
	DBCREQ_GET_INT(data, energy);
	DBCREQ_GET_INT(data, buy_energy);
	DBCREQ_GET_INT(data, shop_refresh);
	DBCREQ_GET_STR(data, shop);
	DBCREQ_GET_STR(data, target);

	return 0;
}
int CDataArena::Add(const DataArena &data) {
	DB_ENCODE_BEGIN(DB_ARENA, e_DBAsyncTypeAdd);
	if (!data.Encode(writer)) {
		return -1;
	}
	DB_ENCODE_END;
	return 0;
}
int CDataArena::Set(const DataArena &data) {
	DB_ENCODE_BEGIN(DB_ARENA, e_DBAsyncTypeSet);
	if (!data.Encode(writer)) {
		return -1;
	}
	DB_ENCODE_END;
	return 0;
}
int CDataArena::Del(uint32_t uid) {
	DataArena data;
	data.uid = uid;
	DB_ENCODE_BEGIN(DB_ARENA, e_DBAsyncTypeDel);
	if (!data.Encode(writer)) {
		return -1;
	}
	DB_ENCODE_END;
	return 0;
}
int CDataArena::Add(CNetPacket *p) {
	DataArena data;
	DB_DECODE_BEGIN(p->GetBody());
	if (!data.Decode(reader)) {
		return R_ERR_DATA;
	}
	DBCREQ_DECLARE(DBC::InsertRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_INT(data, ts);
	DBCREQ_SET_INT(data, cd);
	DBCREQ_SET_INT(data, rank);
	DBCREQ_SET_INT(data, energy);
	DBCREQ_SET_INT(data, buy_energy);
	DBCREQ_SET_INT(data, shop_refresh);
	DBCREQ_SET_STR(data, shop);
	DBCREQ_SET_STR(data, target);
	DBCREQ_EXEC;
	return 0;
}
int CDataArena::Set(CNetPacket *p) {
	DataArena data;
	DB_DECODE_BEGIN(p->GetBody());
	if (!data.Decode(reader)) {
		return R_ERR_DATA;
	}
	DBCREQ_DECLARE(DBC::UpdateRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_INT(data, ts);
	DBCREQ_SET_INT(data, cd);
	DBCREQ_SET_INT(data, rank);
	DBCREQ_SET_INT(data, energy);
	DBCREQ_SET_INT(data, buy_energy);
	DBCREQ_SET_INT(data, shop_refresh);
	DBCREQ_SET_STR(data, shop);
	DBCREQ_SET_STR(data, target);
	DBCREQ_EXEC;
	return 0;
}
int CDataArena::Del(CNetPacket *p) {
	DataArena data;
	DB_DECODE_BEGIN(p->GetBody());
	if (!data.Decode(reader)) {
		return R_ERR_DATA;
	}
	DBCREQ_DECLARE(DBC::DeleteRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_EXEC;
	return 0;
}
