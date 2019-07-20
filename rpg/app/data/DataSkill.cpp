/*
 * DataSkill.cpp
 *
 *  Created on: 2019年5月25日
 *      Author: Administrator
 */

#include "DataSkill.h"

CDataSkill::~CDataSkill() {
}

int CDataSkill::AddData(const DataSkill &data) {
	DBCREQ_DECLARE(DBC::InsertRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_SET_INT(data, rid);
	DBCREQ_SET_INT(data, id);
	DBCREQ_SET_INT(data, lv);

	DBCREQ_EXEC;

	return 0;
}

int CDataSkill::SetData(const DataSkill &data) {
	DBCREQ_DECLARE(DBC::UpdateRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_CONDITION(EQ, rid, data.rid);
	DBCREQ_SET_CONDITION(EQ, id, data.id);

	DBCREQ_SET_INT(data, lv);

	DBCREQ_EXEC;

	return 0;
}

int CDataSkill::RepData(const DataSkill &data) {
	return -1;
}

int CDataSkill::DelData(const DataSkill &data) {
	DBCREQ_DECLARE(DBC::DeleteRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	if (data.rid != 0) {
		DBCREQ_SET_CONDITION(EQ, rid, data.rid);
	}
	if (data.rid != 0) {
		DBCREQ_SET_CONDITION(EQ, id, data.id);
	}

	DBCREQ_EXEC;

	return 0;
}

int CDataSkill::GetData(uint32_t uid, DataSkill &data) {
	if (data.id == 0) {
		return -1;
	}
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);
	DBCREQ_SET_CONDITION(EQ, id, data.id);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(rid);
	DBCREQ_NEED(id);
	DBCREQ_NEED(lv);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;
	DBCREQ_IFFETCHROW;

	DBCREQ_GET_BEGIN();
	DBCREQ_GET_INT(data, uid);
	DBCREQ_GET_INT(data, rid);
	DBCREQ_GET_INT(data, id);
	DBCREQ_GET_INT(data, lv);

	return 0;
}

int CDataSkill::GetData(uint32_t uid, vector<DataSkill> &datas) {
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(rid);
	DBCREQ_NEED(id);
	DBCREQ_NEED(lv);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;

	DBCREQ_ARRAY_GET_BEGIN(datas);
	DBCREQ_ARRAY_GET_INT(datas, uid);
	DBCREQ_ARRAY_GET_INT(datas, rid);
	DBCREQ_ARRAY_GET_INT(datas, id);
	DBCREQ_ARRAY_GET_INT(datas, lv);
	DBCREQ_ARRAY_GET_END();

	return 0;
}
