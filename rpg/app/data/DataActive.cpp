/*
 * DataActive.cpp
 *
 *  Created on: 2019年7月16日
 *      Author: next
 */

#include "DataActive.h"

int CDataActive::AddData(const DataActive &data) {
	DBCREQ_DECLARE(DBC::InsertRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_INT(data, day_active);
	DBCREQ_SET_INT(data, week_active);
	DBCREQ_SET_INT(data, ts);
	DBCREQ_SET_INT(data, reward_1);
	DBCREQ_SET_INT(data, reward_2);
	DBCREQ_SET_INT(data, reward_3);
	DBCREQ_SET_INT(data, reward_4);
	DBCREQ_SET_INT(data, reward_5);

	DBCREQ_EXEC;
	return 0;
}

int CDataActive::SetData(const DataActive &data) {
	DBCREQ_DECLARE(DBC::UpdateRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_INT(data, day_active);
	DBCREQ_SET_INT(data, week_active);
	DBCREQ_SET_INT(data, ts);
	DBCREQ_SET_INT(data, reward_1);
	DBCREQ_SET_INT(data, reward_2);
	DBCREQ_SET_INT(data, reward_3);
	DBCREQ_SET_INT(data, reward_4);
	DBCREQ_SET_INT(data, reward_5);

	DBCREQ_EXEC;
	return 0;
}

int CDataActive::RepData(const DataActive &data) {
	return -1;
}

int CDataActive::DelData(const DataActive &data) {
	DBCREQ_DECLARE(DBC::DeleteRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_EXEC;
	return 0;
}

int CDataActive::GetData(uint32_t uid, DataActive &data) {
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(day_active);
	DBCREQ_NEED(week_active);
	DBCREQ_NEED(ts);
	DBCREQ_NEED(reward_1);
	DBCREQ_NEED(reward_2);
	DBCREQ_NEED(reward_3);
	DBCREQ_NEED(reward_4);
	DBCREQ_NEED(reward_5);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;
	DBCREQ_IFFETCHROW;

	DBCREQ_GET_BEGIN();
	DBCREQ_GET_INT(data, uid);
	DBCREQ_GET_INT(data, day_active);
	DBCREQ_GET_INT(data, week_active);
	DBCREQ_GET_INT(data, ts);
	DBCREQ_GET_INT(data, reward_1);
	DBCREQ_GET_INT(data, reward_2);
	DBCREQ_GET_INT(data, reward_3);
	DBCREQ_GET_INT(data, reward_4);
	DBCREQ_GET_INT(data, reward_5);

	return 0;
}

int CDataActive::GetData(uint32_t uid, vector<DataActive> &datas) {
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(day_active);
	DBCREQ_NEED(week_active);
	DBCREQ_NEED(ts);
	DBCREQ_NEED(reward_1);
	DBCREQ_NEED(reward_2);
	DBCREQ_NEED(reward_3);
	DBCREQ_NEED(reward_4);
	DBCREQ_NEED(reward_5);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;

	DBCREQ_ARRAY_GET_BEGIN(datas);
	DBCREQ_ARRAY_GET_INT(datas, uid);
	DBCREQ_ARRAY_GET_INT(datas, day_active);
	DBCREQ_ARRAY_GET_INT(datas, week_active);
	DBCREQ_ARRAY_GET_INT(datas, ts);
	DBCREQ_ARRAY_GET_INT(datas, reward_1);
	DBCREQ_ARRAY_GET_INT(datas, reward_2);
	DBCREQ_ARRAY_GET_INT(datas, reward_3);
	DBCREQ_ARRAY_GET_INT(datas, reward_4);
	DBCREQ_ARRAY_GET_INT(datas, reward_5);

	DBCREQ_ARRAY_GET_END();
	return 0;
}

