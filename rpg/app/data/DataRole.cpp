/*
 * DataRole.cpp
 *
 *  Created on: 2019年6月20日
 *      Author: Administrator
 */

#include "DataRole.h"

int CDataRole::AddData(const DataRole &data) {
	DBCREQ_DECLARE(DBC::InsertRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_SET_INT(data, combat);
	DBCREQ_SET_INT(data, id);
	DBCREQ_SET_INT(data, sex);
	DBCREQ_SET_INT(data, career);
	DBCREQ_SET_STR(data, name);

	DBCREQ_EXEC;

	return 0;
}

int CDataRole::SetData(const DataRole &data) {
	if (data.id == 0) {
		return -1;
	}
	DBCREQ_DECLARE(DBC::UpdateRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_CONDITION(EQ, id, data.id);

	DBCREQ_SET_INT(data, combat);
	DBCREQ_SET_INT(data, sex);
	DBCREQ_SET_INT(data, career);
	DBCREQ_SET_STR(data, name);

	DBCREQ_EXEC;

	return 0;
}

int CDataRole::RepData(const DataRole &data) {
	if (data.id == 0) {
		return -1;
	}
	DBCREQ_DECLARE(DBC::ReplaceRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_CONDITION(EQ, id, data.id);

	DBCREQ_SET_INT(data, combat);
	DBCREQ_SET_INT(data, sex);
	DBCREQ_SET_INT(data, career);
	DBCREQ_SET_STR(data, name);

	DBCREQ_EXEC;

	return 0;
}

int CDataRole::DelData(const DataRole &data) {
	if (data.id == 0) {
		return -1;
	}
	DBCREQ_DECLARE(DBC::DeleteRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_CONDITION(EQ, id, data.id);
	DBCREQ_EXEC;

	return 0;
}

int CDataRole::GetData(uint32_t uid, DataRole &data) {
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);
	DBCREQ_SET_CONDITION(EQ, id, data.id);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(combat);
	DBCREQ_NEED(id);
	DBCREQ_NEED(sex);
	DBCREQ_NEED(career);
	DBCREQ_NEED(name);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;
	DBCREQ_IFFETCHROW;

	DBCREQ_GET_BEGIN();
	DBCREQ_GET_INT(data, uid);
	DBCREQ_GET_INT(data, combat);
	DBCREQ_GET_INT(data, id);
	DBCREQ_GET_INT(data, sex);
	DBCREQ_GET_INT(data, career);
	DBCREQ_GET_STR(data, name);

	return 0;
}

int CDataRole::GetData(uint32_t uid, vector<DataRole> &datas) {
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(combat);
	DBCREQ_NEED(id);
	DBCREQ_NEED(sex);
	DBCREQ_NEED(career);
	DBCREQ_NEED(name);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;

	DBCREQ_ARRAY_GET_BEGIN(datas);
	DBCREQ_ARRAY_GET_INT(datas, uid);
	DBCREQ_ARRAY_GET_INT(datas, combat);
	DBCREQ_ARRAY_GET_INT(datas, id);
	DBCREQ_ARRAY_GET_INT(datas, sex);
	DBCREQ_ARRAY_GET_INT(datas, career);
	DBCREQ_ARRAY_GET_STR(datas, name);
	DBCREQ_ARRAY_GET_END();

	return 0;
}
