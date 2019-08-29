/*
 * DataUserResource.cpp
 *
 *  Created on: 2015年9月9日
 *      Author: asdf
 */

#include "DataUserResource.h"
#include "AsyncDBManager.h"

int CDataUserResource::Get(uint32_t uid, DataUserResource &data) {
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(r1);
	DBCREQ_NEED(r2);
	DBCREQ_NEED(r3);
	DBCREQ_NEED(r4);
	DBCREQ_NEED(tl);
	DBCREQ_NEED(p1);
	DBCREQ_NEED(p2);
	DBCREQ_NEED(p3);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;
	DBCREQ_IFFETCHROW;

	DBCREQ_GET_BEGIN();
	DBCREQ_GET_INT(data, uid);
	DBCREQ_GET_INT(data, r1);
	DBCREQ_GET_INT(data, r2);
	DBCREQ_GET_INT(data, r3);
	DBCREQ_GET_INT(data, r4);
	DBCREQ_GET_INT(data, tl);
	DBCREQ_GET_INT(data, p1);
	DBCREQ_GET_INT(data, p2);
	DBCREQ_GET_INT(data, p3);

	return 0;
}

int CDataUserResource::Add(const DataUserResource &data) {
	DB_ENCODE_BEGIN(DB_USER_RESOURCE, e_DBAsyncTypeAdd);
	if (!data.Encode(writer)) {
		return -1;
	}
	DB_ENCODE_END;
	return 0;
}

int CDataUserResource::Set(const DataUserResource &data) {
	DB_ENCODE_BEGIN(DB_USER_RESOURCE, e_DBAsyncTypeSet);
	if (!data.Encode(writer)) {
		return -1;
	}
	DB_ENCODE_END;
	return 0;
}

int CDataUserResource::Rep(const DataUserResource &data) {
	DB_ENCODE_BEGIN(DB_USER_RESOURCE, e_DBAsyncTypeRep);
	if (!data.Encode(writer)) {
		return -1;
	}
	DB_ENCODE_END;
	return 0;
}

int CDataUserResource::Del(uint32_t uid) {
	DataUserResource data;
	data.uid = uid;
	DB_ENCODE_BEGIN(DB_USER_RESOURCE, e_DBAsyncTypeDel);
	if (!data.Encode(writer)) {
		return -1;
	}
	DB_ENCODE_END;
	return 0;
}
int CDataUserResource::Add(CNetPacket *packet) {
	DataUserResource data;
	DB_DECODE_BEGIN(packet->GetBody());
	if (!data.Decode(reader)) {
		return -1;
	}

	DBCREQ_DECLARE(DBC::InsertRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_SET_INT(data, r1);
	DBCREQ_SET_INT(data, r2);
	DBCREQ_SET_INT(data, r3);
	DBCREQ_SET_INT(data, r4);
	DBCREQ_SET_INT(data, tl);
	DBCREQ_SET_INT(data, p1);
	DBCREQ_SET_INT(data, p2);
	DBCREQ_SET_INT(data, p3);

	DBCREQ_EXEC;

	return 0;
}

int CDataUserResource::Set(CNetPacket *packet) {
	DataUserResource data;
	DB_DECODE_BEGIN(packet->GetBody());
	if (!data.Decode(reader)) {
		return -1;
	}

	DBCREQ_DECLARE(DBC::UpdateRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_SET_INT(data, r1);
	DBCREQ_SET_INT(data, r2);
	DBCREQ_SET_INT(data, r3);
	DBCREQ_SET_INT(data, r4);
	DBCREQ_SET_INT(data, tl);
	DBCREQ_SET_INT(data, p1);
	DBCREQ_SET_INT(data, p2);
	DBCREQ_SET_INT(data, p3);

	DBCREQ_EXEC;

	return 0;
}

int CDataUserResource::Rep(CNetPacket *packet) {
	DataUserResource data;
	DB_DECODE_BEGIN(packet->GetBody());
	if (!data.Decode(reader)) {
		return -1;
	}

	DBCREQ_DECLARE(DBC::ReplaceRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_SET_INT(data, r1);
	DBCREQ_SET_INT(data, r2);
	DBCREQ_SET_INT(data, r3);
	DBCREQ_SET_INT(data, r4);
	DBCREQ_SET_INT(data, tl);
	DBCREQ_SET_INT(data, p1);
	DBCREQ_SET_INT(data, p2);
	DBCREQ_SET_INT(data, p3);

	DBCREQ_EXEC;

	return 0;
}

int CDataUserResource::Del(CNetPacket *packet) {
	DataUserResource data;
	DB_DECODE_BEGIN(packet->GetBody());
	if (!data.Decode(reader)) {
		return -1;
	}

	DBCREQ_DECLARE(DBC::DeleteRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_EXEC;

	return 0;
}

OP_PROCESS_BEGIN(CDataUserResource)
OP_PROCESS(e_DBAsyncTypeAdd, Add)
OP_PROCESS(e_DBAsyncTypeSet, Set)
OP_PROCESS(e_DBAsyncTypeRep, Rep)
OP_PROCESS(e_DBAsyncTypeDel, Del)
OP_PROCESS_END


