/*
 * DataShenQi.cpp
 *
 *  Created on: 2019年6月27日
 *      Author: Administrator
 */

#include "DataShenQi.h"

int CDataShenQi::AddData(const DataShenQi &data) {
	DBCREQ_DECLARE(DBC::InsertRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_SET_INT(data, id);
	DBCREQ_SET_INT(data, p1);
	DBCREQ_SET_INT(data, p2);
	DBCREQ_SET_INT(data, p3);
	DBCREQ_SET_INT(data, p4);
	DBCREQ_SET_INT(data, p5);
	DBCREQ_SET_INT(data, p6);

	DBCREQ_EXEC;

	return 0;
}

int CDataShenQi::SetData(const DataShenQi &data) {
	DBCREQ_DECLARE(DBC::UpdateRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_SET_INT(data, id);
	DBCREQ_SET_INT(data, p1);
	DBCREQ_SET_INT(data, p2);
	DBCREQ_SET_INT(data, p3);
	DBCREQ_SET_INT(data, p4);
	DBCREQ_SET_INT(data, p5);
	DBCREQ_SET_INT(data, p6);

	DBCREQ_EXEC;

	return 0;
}

int CDataShenQi::RepData(const DataShenQi &data) {
	return -1;
}

int CDataShenQi::DelData(const DataShenQi &data) {
	DBCREQ_DECLARE(DBC::DeleteRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_EXEC;

	return 0;
}

int CDataShenQi::GetData(uint32_t uid, DataShenQi &data) {
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(id);
	DBCREQ_NEED(p1);
	DBCREQ_NEED(p2);
	DBCREQ_NEED(p3);
	DBCREQ_NEED(p4);
	DBCREQ_NEED(p5);
	DBCREQ_NEED(p6);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;
	DBCREQ_IFFETCHROW;

	DBCREQ_GET_BEGIN();
	DBCREQ_GET_INT(data, uid);
	DBCREQ_GET_INT(data, id);
	DBCREQ_GET_INT(data, p1);
	DBCREQ_GET_INT(data, p2);
	DBCREQ_GET_INT(data, p3);
	DBCREQ_GET_INT(data, p4);
	DBCREQ_GET_INT(data, p5);
	DBCREQ_GET_INT(data, p6);

	return 0;
}

int CDataShenQi::GetData(uint32_t uid, vector<DataShenQi> &datas) {
	return -1;
}
