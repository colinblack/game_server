/*
 * DataAdvance.cpp
 *
 *  Created on: 2019年6月22日
 *      Author: Administrator
 */

#include "DataAdvance.h"

int CDataAdvance::AddData(const DataAdvance &data) {
	DBCREQ_DECLARE(DBC::InsertRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_SET_INT(data, rid);
	DBCREQ_SET_INT(data, type);
	DBCREQ_SET_INT(data, bless);
	DBCREQ_SET_INT(data, tmp_bless);
	DBCREQ_SET_INT(data, star);
	DBCREQ_SET_INT(data, level);
	DBCREQ_SET_INT(data, dan1);
	DBCREQ_SET_INT(data, dan2);
	DBCREQ_SET_INT(data, dan3);
	DBCREQ_SET_INT(data, dan4);

	DBCREQ_EXEC;

	return 0;
}

int CDataAdvance::SetData(const DataAdvance &data) {
	DBCREQ_DECLARE(DBC::UpdateRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_CONDITION(EQ, rid, data.rid);
	DBCREQ_SET_CONDITION(EQ, type, data.type);

	DBCREQ_SET_INT(data, bless);
	DBCREQ_SET_INT(data, tmp_bless);
	DBCREQ_SET_INT(data, star);
	DBCREQ_SET_INT(data, level);
	DBCREQ_SET_INT(data, last_level);
	DBCREQ_SET_INT(data, dan1);
	DBCREQ_SET_INT(data, dan2);
	DBCREQ_SET_INT(data, dan3);
	DBCREQ_SET_INT(data, dan4);

	DBCREQ_EXEC;

	return 0;
}

int CDataAdvance::RepData(const DataAdvance &data) {
	return -1;
}

int CDataAdvance::DelData(const DataAdvance &data) {
	DBCREQ_DECLARE(DBC::DeleteRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_CONDITION(EQ, rid, data.rid);
	DBCREQ_SET_CONDITION(EQ, type, data.type);

	DBCREQ_EXEC;

	return 0;
}

int CDataAdvance::GetData(uint32_t uid, DataAdvance &data) {
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);
	DBCREQ_SET_CONDITION(EQ, rid, data.rid);
	DBCREQ_SET_CONDITION(EQ, type, data.type);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(rid);
	DBCREQ_NEED(type);
	DBCREQ_NEED(bless);
	DBCREQ_NEED(tmp_bless);
	DBCREQ_NEED(star);
	DBCREQ_NEED(level);
	DBCREQ_NEED(last_level);
	DBCREQ_NEED(dan1);
	DBCREQ_NEED(dan2);
	DBCREQ_NEED(dan3);
	DBCREQ_NEED(dan4);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;
	DBCREQ_IFFETCHROW;

	DBCREQ_GET_BEGIN();
	DBCREQ_GET_INT(data, uid);
	DBCREQ_GET_INT(data, rid);
	DBCREQ_GET_INT(data, type);
	DBCREQ_GET_INT(data, bless);
	DBCREQ_GET_INT(data, tmp_bless);
	DBCREQ_GET_INT(data, star);
	DBCREQ_GET_INT(data, level);
	DBCREQ_GET_INT(data, last_level);
	DBCREQ_GET_INT(data, dan1);
	DBCREQ_GET_INT(data, dan2);
	DBCREQ_GET_INT(data, dan3);
	DBCREQ_GET_INT(data, dan4);

	return 0;
}

int CDataAdvance::GetData(uint32_t uid, vector<DataAdvance> &datas) {
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(rid);
	DBCREQ_NEED(type);
	DBCREQ_NEED(bless);
	DBCREQ_NEED(tmp_bless);
	DBCREQ_NEED(star);
	DBCREQ_NEED(level);
	DBCREQ_NEED(last_level);
	DBCREQ_NEED(dan1);
	DBCREQ_NEED(dan2);
	DBCREQ_NEED(dan3);
	DBCREQ_NEED(dan4);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;

	DBCREQ_ARRAY_GET_BEGIN(datas);
	DBCREQ_ARRAY_GET_INT(datas, uid);
	DBCREQ_ARRAY_GET_INT(datas, rid);
	DBCREQ_ARRAY_GET_INT(datas, type);
	DBCREQ_ARRAY_GET_INT(datas, bless);
	DBCREQ_ARRAY_GET_INT(datas, tmp_bless);
	DBCREQ_ARRAY_GET_INT(datas, star);
	DBCREQ_ARRAY_GET_INT(datas, level);
	DBCREQ_ARRAY_GET_INT(datas, last_level);
	DBCREQ_ARRAY_GET_INT(datas, dan1);
	DBCREQ_ARRAY_GET_INT(datas, dan2);
	DBCREQ_ARRAY_GET_INT(datas, dan3);
	DBCREQ_ARRAY_GET_INT(datas, dan4);
	DBCREQ_ARRAY_GET_END();

	return 0;
}
