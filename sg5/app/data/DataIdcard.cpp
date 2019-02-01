/*
 * DataIdcard.cpp
 *
 *  Created on: 2018-3-13
 *      Author: Ralf
 */


#include "DataIdcard.h"
#include "crc.h"

int CDataIdcard::AddIdcard(const string &idcard, string& open_id){
	unsigned crc = CCRC::GetCrc32(idcard);
	if (crc > UID_MAX) {
		crc %= UID_MAX;
		if (crc < UID_MIN) {
			crc += UID_MIN;
		}
	}
	DBCREQ_DECLARE(DBC::ReplaceRequest, crc);
	DBCREQ_SET_KEY(idcard.c_str());
	DBCREQ_SET_STR_S(open_id);
	DBCREQ_EXEC;
	return 0;
}
int CDataIdcard::GetAllIdcard(const string &idcard, set<string> &open_id){
	unsigned crc = CCRC::GetCrc32(idcard);
	if (crc > UID_MAX) {
		crc %= UID_MAX;
		if (crc < UID_MIN) {
			crc += UID_MIN;
		}
	}

	DBCREQ_DECLARE(DBC::GetRequest, crc);
	DBCREQ_SET_KEY(idcard.c_str());

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(open_id);

	DBCREQ_EXEC;

	for(size_t i = 0; i < m_dbcret.TotalRows(); i++)
	{
		DBCREQ_IFFETCHROW;
		reqItemIndex = 0;
		open_id.insert(m_dbcret.StringValue(++reqItemIndex));
	}

	return 0;
}
