/*
 * DataBagExtend.cpp
 *
 *  Created on: 2019年7月1日
 *      Author: Administrator
 */

#include "DataBagExtend.h"

int CDataBagExtend::AddData(const DataBagExtend &data) {
	DBCREQ_DECLARE(DBC::InsertRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_SET_INT(data, bag);
	DBCREQ_SET_INT(data, num);

	DBCREQ_EXEC;

	return 0;
}

int CDataBagExtend::SetData(const DataBagExtend &data) {
	DBCREQ_DECLARE(DBC::UpdateRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_CONDITION(EQ, bag, data.bag);

	DBCREQ_SET_INT(data, num);

	DBCREQ_EXEC;

	return 0;
}

int CDataBagExtend::RepData(const DataBagExtend &data) {
	return 0;
}

int CDataBagExtend::DelData(const DataBagExtend &data) {
	DBCREQ_DECLARE(DBC::DeleteRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_CONDITION(EQ, bag, data.bag);

	DBCREQ_EXEC;

	return 0;
}

int CDataBagExtend::GetData(uint32_t uid, DataBagExtend &data) {
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);
	DBCREQ_SET_CONDITION(EQ, bag, data.bag);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(bag);
	DBCREQ_NEED(num);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;
	DBCREQ_IFFETCHROW;

	DBCREQ_GET_BEGIN();
	DBCREQ_GET_INT(data, uid);
	DBCREQ_GET_INT(data, bag);
	DBCREQ_GET_INT(data, num);

	return 0;
}

int CDataBagExtend::GetData(uint32_t uid, vector<DataBagExtend> &datas) {
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(bag);
	DBCREQ_NEED(num);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;

	DBCREQ_ARRAY_GET_BEGIN(datas);
	DBCREQ_ARRAY_GET_INT(datas, uid);
	DBCREQ_ARRAY_GET_INT(datas, bag);
	DBCREQ_ARRAY_GET_INT(datas, num);
	DBCREQ_ARRAY_GET_END();

	return 0;
}
