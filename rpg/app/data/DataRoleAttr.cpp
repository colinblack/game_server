/*
 * DataRoleAttr.cpp
 *
 * Create on: 2019.7 8
 *
 * autor: next
 */

#include "DataRoleAttr.h"

int CDataRoleAttr::AddData(const DataRoleAttr &data) {
	DBCREQ_DECLARE(DBC::InsertRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_SET_INT(data, rid);
	DBCREQ_SET_INT(data, type);
	DBCREQ_SET_INT(data, id);
	DBCREQ_SET_INT(data, v1);
	DBCREQ_SET_INT(data, v2);
	DBCREQ_SET_INT(data, v3);
	DBCREQ_SET_INT(data, v4);
	DBCREQ_SET_INT(data, v5);
	DBCREQ_SET_INT(data, v6);
	DBCREQ_SET_INT(data, v7);
	DBCREQ_SET_INT(data, v8);
	DBCREQ_SET_INT(data, v9);
	DBCREQ_SET_INT(data, v10);

	DBCREQ_EXEC;

	return 0;
}
int CDataRoleAttr::SetData(const DataRoleAttr &data) {
	DBCREQ_DECLARE(DBC::UpdateRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_CONDITION(EQ, rid, data.rid);
	DBCREQ_SET_CONDITION(EQ, type, data.type);
	DBCREQ_SET_CONDITION(EQ, id, data.id);

	DBCREQ_SET_INT(data, v1);
	DBCREQ_SET_INT(data, v2);
	DBCREQ_SET_INT(data, v3);
	DBCREQ_SET_INT(data, v4);
	DBCREQ_SET_INT(data, v5);
	DBCREQ_SET_INT(data, v6);
	DBCREQ_SET_INT(data, v7);
	DBCREQ_SET_INT(data, v8);
	DBCREQ_SET_INT(data, v9);
	DBCREQ_SET_INT(data, v10);

	DBCREQ_EXEC;
	return 0;
}
int CDataRoleAttr::RepData(const DataRoleAttr &data) {
	return -1;
}
int CDataRoleAttr::DelData(const DataRoleAttr &data) {
	DBCREQ_DECLARE(DBC::UpdateRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_CONDITION(EQ, rid, data.rid);
	DBCREQ_SET_CONDITION(EQ, type, data.type);
	DBCREQ_SET_CONDITION(EQ, id, data.id);

	DBCREQ_EXEC;

	return 0;
}
int CDataRoleAttr::GetData(uint32_t uid, DataRoleAttr &data) {
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);
	DBCREQ_SET_CONDITION(EQ, rid, data.rid);
	DBCREQ_SET_CONDITION(EQ, type, data.type);
	DBCREQ_SET_CONDITION(EQ, id, data.id);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(rid);
	DBCREQ_NEED(type);
	DBCREQ_NEED(id);
	DBCREQ_NEED(v1);
	DBCREQ_NEED(v2);
	DBCREQ_NEED(v3);
	DBCREQ_NEED(v4);
	DBCREQ_NEED(v5);
	DBCREQ_NEED(v6);
	DBCREQ_NEED(v7);
	DBCREQ_NEED(v8);
	DBCREQ_NEED(v9);
	DBCREQ_NEED(v10);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;
	DBCREQ_IFFETCHROW;

	DBCREQ_GET_BEGIN();
	DBCREQ_GET_INT(data, uid);
	DBCREQ_GET_INT(data, rid);
	DBCREQ_GET_INT(data, type);
	DBCREQ_GET_INT(data, id);
	DBCREQ_GET_INT(data, v1);
	DBCREQ_GET_INT(data, v2);
	DBCREQ_GET_INT(data, v3);
	DBCREQ_GET_INT(data, v4);
	DBCREQ_GET_INT(data, v5);
	DBCREQ_GET_INT(data, v6);
	DBCREQ_GET_INT(data, v7);
	DBCREQ_GET_INT(data, v8);
	DBCREQ_GET_INT(data, v9);
	DBCREQ_GET_INT(data, v10);

	return 0;
}
int CDataRoleAttr::GetData(uint32_t uid, vector<DataRoleAttr> &datas) {
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(rid);
	DBCREQ_NEED(type);
	DBCREQ_NEED(id);
	DBCREQ_NEED(v1);
	DBCREQ_NEED(v2);
	DBCREQ_NEED(v3);
	DBCREQ_NEED(v4);
	DBCREQ_NEED(v5);
	DBCREQ_NEED(v6);
	DBCREQ_NEED(v7);
	DBCREQ_NEED(v8);
	DBCREQ_NEED(v9);
	DBCREQ_NEED(v10);
	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;

	DBCREQ_ARRAY_GET_BEGIN(datas);
	DBCREQ_ARRAY_GET_INT(datas, uid);
	DBCREQ_ARRAY_GET_INT(datas, rid);
	DBCREQ_ARRAY_GET_INT(datas, type);
	DBCREQ_ARRAY_GET_INT(datas, id);
	DBCREQ_ARRAY_GET_INT(datas, v1);
	DBCREQ_ARRAY_GET_INT(datas, v2);
	DBCREQ_ARRAY_GET_INT(datas, v3);
	DBCREQ_ARRAY_GET_INT(datas, v4);
	DBCREQ_ARRAY_GET_INT(datas, v5);
	DBCREQ_ARRAY_GET_INT(datas, v6);
	DBCREQ_ARRAY_GET_INT(datas, v7);
	DBCREQ_ARRAY_GET_INT(datas, v8);
	DBCREQ_ARRAY_GET_INT(datas, v9);
	DBCREQ_ARRAY_GET_INT(datas, v10);
	DBCREQ_ARRAY_GET_END();

	return 0;
}
