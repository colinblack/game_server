/*
 * DataMission.cpp
 *
 *  Created on: 2019年6月20日
 *      Author: Administrator
 */

#include "DataMission.h"

int CDataMission::AddData(const DataMission &data) {
	DBCREQ_DECLARE(DBC::InsertRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_SET_INT(data, id);
	DBCREQ_SET_INT(data, ts);
	DBCREQ_SET_INT(data, step);
	DBCREQ_SET_INT(data, status);
	DBCREQ_SET_STR(data, extend);
	DBCREQ_EXEC;

	return 0;
}

int CDataMission::SetData(const DataMission &data) {
	if (data.id == 0) {
		return -1;
	}
	DBCREQ_DECLARE(DBC::UpdateRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_CONDITION(EQ, id, data.id);

	DBCREQ_SET_INT(data, ts);
	DBCREQ_SET_INT(data, step);
	DBCREQ_SET_INT(data, status);
	DBCREQ_SET_STR(data, extend);

	DBCREQ_EXEC;

	return 0;
}

int CDataMission::RepData(const DataMission &data) {
	return -1;
}

int CDataMission::DelData(const DataMission &data) {
	if (data.id == 0) {
		return -1;
	}
	DBCREQ_DECLARE(DBC::DeleteRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_CONDITION(EQ, id, data.id);

	DBCREQ_EXEC;

	return 0;
}

int CDataMission::GetData(uint32_t uid, DataMission &data) {
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);
	DBCREQ_SET_CONDITION(EQ, id, data.id);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(id);
	DBCREQ_NEED(ts);
	DBCREQ_NEED(step);
	DBCREQ_NEED(status);
	DBCREQ_NEED(extend);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;
	DBCREQ_IFFETCHROW;

	DBCREQ_GET_BEGIN();
	DBCREQ_GET_INT(data, uid);
	DBCREQ_GET_INT(data, id);
	DBCREQ_GET_INT(data, ts);
	DBCREQ_GET_INT(data, step);
	DBCREQ_GET_INT(data, status);
	DBCREQ_GET_STR(data, extend);

	return 0;
}

int CDataMission::GetData(uint32_t uid, vector<DataMission> &datas) {
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(id);
	DBCREQ_NEED(ts);
	DBCREQ_NEED(step);
	DBCREQ_NEED(status);
	DBCREQ_NEED(extend);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;

	DBCREQ_ARRAY_GET_BEGIN(datas);
	DBCREQ_ARRAY_GET_INT(datas, uid);
	DBCREQ_ARRAY_GET_INT(datas, id);
	DBCREQ_ARRAY_GET_INT(datas, ts);
	DBCREQ_ARRAY_GET_INT(datas, step);
	DBCREQ_ARRAY_GET_INT(datas, status);
	DBCREQ_ARRAY_GET_STR(datas, extend);
	DBCREQ_ARRAY_GET_END();

	return 0;
}
