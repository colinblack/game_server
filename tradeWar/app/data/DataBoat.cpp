/*
 * DataBoat.cpp
 *
 *  Created on: 2018年11月8日
 *      Author: Administrator
 */

#include "DataBoat.h"
#include "AsyncDBManager.h"

enum {
	REQ_ADD = 1,
	REQ_SET = 2,
	REQ_DEL = 3
};

void CDataBoat::doRequest(CNetPacket* p) {
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
int CDataBoat::Add(const DataBoat &data) {
	DB_ENCODE_BEGIN(DB_BOAT, REQ_ADD);
	if (!data.Encode(writer)) {
		return R_ERR_DATA;
	}
	DB_ENCODE_END;
	return 0;
}
int CDataBoat::Set(const DataBoat &data) {
	DB_ENCODE_BEGIN(DB_BOAT, REQ_SET);
	if (!data.Encode(writer)) {
		return R_ERR_DATA;
	}
	DB_ENCODE_END;
	return 0;
}
int CDataBoat::Get(uint32_t uid, DataBoat &data) {
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(reset_ts);
	DBCREQ_NEED(refresh_count);
	DBCREQ_NEED(speed_up);
	DBCREQ_NEED(star);
	DBCREQ_NEED(star_reward);
	DBCREQ_NEED(reset_flag);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;
	DBCREQ_IFFETCHROW;

	DBCREQ_GET_BEGIN();
	DBCREQ_GET_INT(data, uid);
	DBCREQ_GET_INT(data, reset_ts);
	DBCREQ_GET_INT(data, refresh_count);
	DBCREQ_GET_INT(data, speed_up);
	DBCREQ_GET_INT(data, star);
	DBCREQ_GET_INT(data, star_reward);
	DBCREQ_GET_INT(data, reset_flag);

	return 0;

}
int CDataBoat::Del(uint32_t uid) {
	DataBoat data;
	data.uid = uid;
	DB_ENCODE_BEGIN(DB_BOAT, REQ_DEL);
	if (!data.Encode(writer)) {
		return R_ERR_DATA;
	}
	DB_ENCODE_END;
	return 0;
}

int CDataBoat::Add(CNetPacket *p) {
	DataBoat data;
	DB_DECODE_BEGIN(p->GetBody());
	if (!data.Decode(reader)) {
		return R_ERR_DATA;
	}
	DBCREQ_DECLARE(DBC::InsertRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_INT(data, reset_ts);
	DBCREQ_SET_INT(data, refresh_count);
	DBCREQ_SET_INT(data, speed_up);
	DBCREQ_SET_INT(data, star);
	DBCREQ_SET_INT(data, star_reward);
	DBCREQ_SET_INT(data, reset_flag);
	DBCREQ_EXEC;
	return 0;
}
int CDataBoat::Set(CNetPacket *p) {
	DataBoat data;
	DB_DECODE_BEGIN(p->GetBody());
	if (!data.Decode(reader)) {
		return R_ERR_DATA;
	}
	DBCREQ_DECLARE(DBC::UpdateRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_INT(data, reset_ts);
	DBCREQ_SET_INT(data, refresh_count);
	DBCREQ_SET_INT(data, speed_up);
	DBCREQ_SET_INT(data, star);
	DBCREQ_SET_INT(data, star_reward);
	DBCREQ_SET_INT(data, reset_flag);
	DBCREQ_EXEC;
	return 0;
}
int CDataBoat::Del(CNetPacket *p) {
	DataBoat data;
	DB_DECODE_BEGIN(p->GetBody());
	if (!data.Decode(reader)) {
		return R_ERR_DATA;
	}
	DBCREQ_DECLARE(DBC::DeleteRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_EXEC;
	return 0;
}

