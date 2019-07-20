/*
 * DataEquip.cpp
 *
 *  Created on: 2019年6月25日
 *      Author: Administrator
 */

#include "DataEquip.h"

int CDataEquip::AddData(const DataEquip &data) {
	DBCREQ_DECLARE(DBC::InsertRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_SET_INT(data, ud);
	DBCREQ_SET_INT(data, id);
	DBCREQ_SET_INT(data, num);
	DBCREQ_SET_INT(data, ts);
	DBCREQ_SET_INT(data, bag);
	DBCREQ_SET_STR(data, ext);

	DBCREQ_EXEC;

	return 0;
}

int CDataEquip::SetData(const DataEquip &data) {
	DBCREQ_DECLARE(DBC::UpdateRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_CONDITION(EQ, ud, data.ud);

	DBCREQ_SET_INT(data, id);
	DBCREQ_SET_INT(data, num);
	DBCREQ_SET_INT(data, ts);
	DBCREQ_SET_INT(data, bag);
	DBCREQ_SET_STR(data, ext);

	DBCREQ_EXEC;

	return 0;
}

int CDataEquip::RepData(const DataEquip &data) {
	return -1;
}

int CDataEquip::DelData(const DataEquip &data) {
	DBCREQ_DECLARE(DBC::DeleteRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_CONDITION(EQ, ud, data.ud);

	DBCREQ_EXEC;

	return 0;
}

int CDataEquip::GetData(uint32_t uid, DataEquip &data) {
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);
	DBCREQ_SET_CONDITION(EQ, ud, data.ud);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(ud);
	DBCREQ_NEED(id);
	DBCREQ_NEED(num);
	DBCREQ_NEED(ts);
	DBCREQ_NEED(bag);
	DBCREQ_NEED(ext);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;
	DBCREQ_IFFETCHROW;

	DBCREQ_GET_BEGIN();
	DBCREQ_GET_INT(data, uid);
	DBCREQ_GET_INT(data, ud);
	DBCREQ_GET_INT(data, id);
	DBCREQ_GET_INT(data, num);
	DBCREQ_GET_INT(data, ts);
	DBCREQ_GET_INT(data, bag);
	DBCREQ_GET_INT(data, ext);

	return 0;
}

int CDataEquip::GetData(uint32_t uid, vector<DataEquip> &datas) {
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(ud);
	DBCREQ_NEED(id);
	DBCREQ_NEED(num);
	DBCREQ_NEED(ts);
	DBCREQ_NEED(bag);
	DBCREQ_NEED(ext);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;

	DBCREQ_ARRAY_GET_BEGIN(datas);
	DBCREQ_ARRAY_GET_INT(datas, uid);
	DBCREQ_ARRAY_GET_INT(datas, ud);
	DBCREQ_ARRAY_GET_INT(datas, id);
	DBCREQ_ARRAY_GET_INT(datas, num);
	DBCREQ_ARRAY_GET_INT(datas, ts);
	DBCREQ_ARRAY_GET_INT(datas, bag);
	DBCREQ_ARRAY_GET_STR(datas, ext);
	DBCREQ_ARRAY_GET_END();

	return 0;
}
