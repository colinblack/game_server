/*
 * DataTrump.cpp
 *
 *  Created on: 2019年7月24日
 *      Author: colin
 */

#include "DataTrump.h"

int CDataTrump::AddData(const DataTrump &data) {
	DBCREQ_DECLARE(DBC::InsertRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_SET_INT(data, unlock);
	DBCREQ_SET_INT(data, active_count);
	DBCREQ_SET_INT(data, current_fight);
	DBCREQ_SET_CHAR(data, active_map, ACTIVE_TRUMP_SKILL_COUNT);

	DBCREQ_EXEC;

	return 0;
}

int CDataTrump::SetData(const DataTrump &data) {
	DBCREQ_DECLARE(DBC::UpdateRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_INT(data, unlock);
	DBCREQ_SET_INT(data, active_count);
	DBCREQ_SET_INT(data, current_fight);
	DBCREQ_SET_CHAR(data, active_map, ACTIVE_TRUMP_SKILL_COUNT);

	DBCREQ_EXEC;

	return 0;
}

int CDataTrump::RepData(const DataTrump &data) {
	return -1;
}

int CDataTrump::DelData(const DataTrump &data) {
	DBCREQ_DECLARE(DBC::DeleteRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_EXEC;

	return 0;
}

int CDataTrump::GetData(uint32_t uid, DataTrump &data) {
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(unlock);
	DBCREQ_NEED(active_count);
	DBCREQ_NEED(current_fight);
	DBCREQ_NEED(active_map);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;
	DBCREQ_IFFETCHROW;

	DBCREQ_GET_BEGIN();
	DBCREQ_GET_INT(data, uid);
	DBCREQ_GET_INT(data, unlock);
	DBCREQ_GET_INT(data, active_count);
	DBCREQ_GET_INT(data, current_fight);
	DBCREQ_GET_CHAR(data, active_map, ACTIVE_TRUMP_SKILL_COUNT);


	return 0;
}

int CDataTrump::GetData(uint32_t uid, vector<DataTrump> &datas) {
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(unlock);
	DBCREQ_NEED(active_count);
	DBCREQ_NEED(current_fight);
	DBCREQ_NEED(activeMap);


	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;

	DBCREQ_ARRAY_GET_BEGIN(datas);
	DBCREQ_ARRAY_GET_INT(datas, uid);
	DBCREQ_ARRAY_GET_INT(datas, unlock);
	DBCREQ_ARRAY_GET_INT(datas, active_count);
	DBCREQ_ARRAY_GET_INT(datas, current_fight);
	DBCREQ_ARRAY_GET_CHAR(datas, active_map, ACTIVE_TRUMP_SKILL_COUNT);



	DBCREQ_ARRAY_GET_END();

	return 0;
}




