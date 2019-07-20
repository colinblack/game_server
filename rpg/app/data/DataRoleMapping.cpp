/*
 * DataRoleMapping.cpp
 *
 *  Created on: 2013-2-6
 *      Author: Administrator
 */

#include "DataRoleMapping.h"

int CDataRoleMapping::AddMapping(const string &role_name, unsigned sid, unsigned uid) {
	unsigned crc = CCRC::GetCrc32(role_name);
	if (crc > UID_MAX) {
		crc %= UID_MAX;
		if (crc < UID_MIN) {
			crc += UID_MIN;
		}
	}
	DBCREQ_DECLARE(DBC::InsertRequest, crc);
	DBCREQ_SET_KEY(role_name.c_str());

	DBCREQ_SET_INT_S(uid);
	DBCREQ_SET_INT_S(sid);

	DBCREQ_EXEC;

	return 0;
}

int CDataRoleMapping::GetMapping(const string &role_name, unsigned sid, unsigned &uid) {
	unsigned crc = CCRC::GetCrc32(role_name);
	if (crc > UID_MAX) {
		crc %= UID_MAX;
		if (crc < UID_MIN) {
			crc += UID_MIN;
		}
	}
	DBCREQ_DECLARE(DBC::GetRequest, crc);
	DBCREQ_SET_KEY(role_name.c_str());
	DBCREQ_SET_CONDITION(EQ, sid, sid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;
	DBCREQ_IFFETCHROW;

	DBCREQ_GET_BEGIN();
	DBCREQ_GET_INT_S(uid);

	return 0;
}
