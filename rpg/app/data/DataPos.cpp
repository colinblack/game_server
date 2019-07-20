/*
 * DataPos.cpp
 *
 *  Created on: 2013-3-13
 *      Author: colin
 */
#include "DataPos.h"

int CDataPos::AddData(const DataPos &data)
{
	DBCREQ_DECLARE(DBC::InsertRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_INT(data, fb_id);
	DBCREQ_SET_INT(data, map_id);
	DBCREQ_SET_INT(data, x);
	DBCREQ_SET_INT(data, y);
	DBCREQ_SET_INT(data, dir);
	DBCREQ_SET_INT(data, update_time);
	DBCREQ_SET_INT(data, from_x);
	DBCREQ_SET_INT(data, from_y);
	DBCREQ_SET_INT(data, from_map_id);
	DBCREQ_EXEC;
	return 0;
}

int CDataPos::SetData(const DataPos &data)
{
	DBCREQ_DECLARE(DBC::UpdateRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_INT(data, map_id);
	DBCREQ_SET_INT(data, fb_id);
	DBCREQ_SET_INT(data, x);
	DBCREQ_SET_INT(data, y);
	DBCREQ_SET_INT(data, dir);
	DBCREQ_SET_INT(data, update_time);
	DBCREQ_SET_INT(data, from_x);
	DBCREQ_SET_INT(data, from_y);
	DBCREQ_SET_INT(data, from_map_id);
	DBCREQ_EXEC;
	return 0;
}

int CDataPos::RepData(const DataPos &data) {
	return -1;
}

int CDataPos::DelData(const DataPos &data) {
	DBCREQ_DECLARE(DBC::DeleteRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_EXEC;
	return 0;
}

int CDataPos::GetData(uint32_t uid, DataPos &data)
{
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(fb_id);
	DBCREQ_NEED(map_id);
	DBCREQ_NEED(x);
	DBCREQ_NEED(y);
	DBCREQ_NEED(dir);
	DBCREQ_NEED(update_time);
	DBCREQ_NEED(from_x);
	DBCREQ_NEED(from_y);
	DBCREQ_NEED(from_map_id);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;
	DBCREQ_IFFETCHROW;

	DBCREQ_GET_BEGIN();
	DBCREQ_GET_INT(data, uid);
	DBCREQ_GET_INT(data, fb_id);
	DBCREQ_GET_INT(data, map_id);
	DBCREQ_GET_INT(data, x);
	DBCREQ_GET_INT(data, y);
	DBCREQ_GET_INT(data, dir);
	DBCREQ_GET_INT(data, update_time);
	DBCREQ_GET_INT(data, from_x);
	DBCREQ_GET_INT(data, from_y);
	DBCREQ_GET_INT(data, from_map_id);

	return 0;
}

int CDataPos::GetData(uint32_t uid, vector<DataPos> &datas) {
	return -1;
}
