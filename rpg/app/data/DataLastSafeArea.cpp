/*
 * DataLastSafeArea.cpp
 *
 *  Created on: 2013-5-13
 *      Author: Administrator
 */

#include "DataLastSafeArea.h"

CDataLastSafeArea::~CDataLastSafeArea() {
}

int CDataLastSafeArea::addLastSafeArea(const DataLastSafeArea &data) {

	DBCREQ_DECLARE(DBC::InsertRequest, data.rid);
	DBCREQ_SET_KEY(data.rid);
	DBCREQ_SET_INT(data, mapId);
	DBCREQ_SET_INT(data, x);
	DBCREQ_SET_INT(data, y);
	DBCREQ_EXEC;
	return 0;
}

int CDataLastSafeArea::updateLastSafeArea(const DataLastSafeArea &data) {
	DBCREQ_DECLARE(DBC::UpdateRequest, data.rid);
	DBCREQ_SET_KEY(data.rid);
	DBCREQ_SET_INT(data, mapId);
	DBCREQ_SET_INT(data, x);
	DBCREQ_SET_INT(data, y);
	DBCREQ_EXEC;

	return 0;
}

int CDataLastSafeArea::getLastSafeArea(DataLastSafeArea &data) {
	DBCREQ_DECLARE(DBC::GetRequest, data.rid);
	DBCREQ_SET_KEY(data.rid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(rid);
	DBCREQ_NEED(mapId);
	DBCREQ_NEED(x);
	DBCREQ_NEED(y);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;
	DBCREQ_IFFETCHROW;

	DBCREQ_GET_BEGIN();
	DBCREQ_GET_INT(data, rid);
	DBCREQ_GET_INT(data, mapId);
	DBCREQ_GET_INT(data, x);
	DBCREQ_GET_INT(data, y);
	return 0;
}
