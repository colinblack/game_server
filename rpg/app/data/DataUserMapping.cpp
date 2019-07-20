/*
 * DataUserMapping.cpp
 *
 *  Created on: 2013-2-2
 *      Author: Administrator
 */

#include "DataUserMapping.h"

int CDataUserMapping::AddMapping(const string &openid, unsigned sid, unsigned platform, unsigned uid) {
	unsigned crc = CCRC::GetCrc32(openid);
	if (crc > UID_MAX) {
		crc %= UID_MAX;
		if (crc < UID_MIN) {
			crc += UID_MIN;
		}
	}
	unsigned updatetime = Time::GetGlobalTime();
	DBCREQ_DECLARE(DBC::InsertRequest, crc);
	DBCREQ_SET_KEY(openid.c_str());

	DBCREQ_SET_INT_S(platform);
	DBCREQ_SET_INT_S(sid);
	DBCREQ_SET_INT_S(uid);
	DBCREQ_SET_INT_S(updatetime);

	DBCREQ_EXEC;

	return 0;
}

int CDataUserMapping::GetMapping(const string &openid, unsigned sid, unsigned platform, unsigned &uid) {
	unsigned crc = CCRC::GetCrc32(openid);
	if (crc > UID_MAX) {
		crc %= UID_MAX;
		if (crc < UID_MIN) {
			crc += UID_MIN;
		}
	}
	DBCREQ_DECLARE(DBC::GetRequest, crc);
	DBCREQ_SET_KEY(openid.c_str());
	DBCREQ_SET_CONDITION(EQ, sid, sid);
	DBCREQ_SET_CONDITION(EQ, platform, platform);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;
	DBCREQ_IFFETCHROW;

	DBCREQ_GET_BEGIN();
	DBCREQ_GET_INT_S(uid);

	return 0;
}
