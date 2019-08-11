/*
 * DataForge.cpp
 *
 *  Created on: 2019年7月3日
 *      Author: Administrator
 */

#include "DataForge.h"

int CDataForge::AddData(const DataForge &data) {
	DBCREQ_DECLARE(DBC::InsertRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_SET_INT(data, rid);
	DBCREQ_SET_INT(data, type);
	DBCREQ_SET_INT(data, strength);
	DBCREQ_SET_INT(data, purify);
	DBCREQ_SET_INT(data, zhulingLevel);
	DBCREQ_SET_INT(data, zhulingAdvance);
	DBCREQ_SET_STR(data, extend);

	DBCREQ_EXEC;

	return 0;
}

int CDataForge::SetData(const DataForge &data) {
	DBCREQ_DECLARE(DBC::UpdateRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_CONDITION(EQ, rid, data.rid);
	DBCREQ_SET_CONDITION(EQ, type, data.type);

	DBCREQ_SET_INT(data, strength);
	DBCREQ_SET_INT(data, purify);
	DBCREQ_SET_INT(data, zhulingLevel);
	DBCREQ_SET_INT(data, zhulingAdvance);
	DBCREQ_SET_STR(data, extend);


	DBCREQ_EXEC;

	return 0;
}

int CDataForge::RepData(const DataForge &data) {
	return -1;
}

int CDataForge::DelData(const DataForge &data) {
	DBCREQ_DECLARE(DBC::DeleteRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_CONDITION(EQ, rid, data.rid);
	DBCREQ_SET_CONDITION(EQ, type, data.type);

	DBCREQ_EXEC;

	return 0;
}

int CDataForge::GetData(uint32_t uid, DataForge &data) {
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);
	DBCREQ_SET_CONDITION(EQ, rid, data.rid);
	DBCREQ_SET_CONDITION(EQ, type, data.type);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(rid);
	DBCREQ_NEED(type);
	DBCREQ_NEED(strength);
	DBCREQ_NEED(purify);
	DBCREQ_NEED(zhulingLevel);
	DBCREQ_NEED(zhulingAdvance);
	DBCREQ_NEED(extend);


	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;
	DBCREQ_IFFETCHROW;

	DBCREQ_GET_BEGIN();
	DBCREQ_GET_INT(data, uid);
	DBCREQ_GET_INT(data, rid);
	DBCREQ_GET_INT(data, type);
	DBCREQ_GET_INT(data, strength);
	DBCREQ_GET_INT(data, purify);
	DBCREQ_GET_INT(data, zhulingLevel);
	DBCREQ_GET_INT(data, zhulingAdvance);
	DBCREQ_GET_STR(data, extend);



	return 0;
}

int CDataForge::GetData(uint32_t uid, vector<DataForge> &datas) {
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(rid);
	DBCREQ_NEED(type);
	DBCREQ_NEED(strength);
	DBCREQ_NEED(purify);
	DBCREQ_NEED(zhulingLevel);
	DBCREQ_NEED(zhulingAdvance);
	DBCREQ_NEED(extend);


	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;

	DBCREQ_ARRAY_GET_BEGIN(datas);
	DBCREQ_ARRAY_GET_INT(datas, uid);
	DBCREQ_ARRAY_GET_INT(datas, rid);
	DBCREQ_ARRAY_GET_INT(datas, type);
	DBCREQ_ARRAY_GET_INT(datas, strength);
	DBCREQ_ARRAY_GET_INT(datas, purify);
	DBCREQ_ARRAY_GET_INT(datas, zhulingLevel);
	DBCREQ_ARRAY_GET_INT(datas, zhulingAdvance);
	DBCREQ_ARRAY_GET_STR(datas, extend);
	DBCREQ_ARRAY_GET_END();

	return 0;
}
