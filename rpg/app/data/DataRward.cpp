/*
 * DataReward.cpp
 *
 *  Created on: 2019年7月19日
 *      Author: colin
 */

#include "DataReward.h"

int CDataReward::AddData(const DataReward &data) {
	DBCREQ_DECLARE(DBC::InsertRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_INT(data, free_count);
	DBCREQ_SET_INT(data, today_is_sign);
	DBCREQ_SET_INT(data, sign_num);
	DBCREQ_SET_CHAR(data, target_gots, TARGET_GOTS_SIZE);
	DBCREQ_SET_INT(data, sign_ts);
	DBCREQ_SET_CHAR(data, level_rewards_flags, LEVEL_REWARDS_SIZE);

	DBCREQ_EXEC;
	return 0;
}


int CDataReward::SetData(const DataReward &data) {
	DBCREQ_DECLARE(DBC::UpdateRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_INT(data, free_count);
	DBCREQ_SET_INT(data, today_is_sign);
	DBCREQ_SET_INT(data, sign_num);
	DBCREQ_SET_CHAR(data, target_gots, TARGET_GOTS_SIZE);
	DBCREQ_SET_INT(data, sign_ts);
	DBCREQ_SET_CHAR(data, level_rewards_flags, LEVEL_REWARDS_SIZE);

	DBCREQ_EXEC;
	return 0;
}


int CDataReward::RepData(const DataReward &data) {
	return -1;
}

int CDataReward::DelData(const DataReward &data) {
	DBCREQ_DECLARE(DBC::DeleteRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_EXEC;
	return 0;
}


int CDataReward::GetData(uint32_t uid, DataReward &data) {
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(free_count);
	DBCREQ_NEED(today_is_sign);
	DBCREQ_NEED(sign_num);
	DBCREQ_NEED(target_gots);
	DBCREQ_NEED(sign_ts);
	DBCREQ_NEED(level_rewards_flags);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;
	DBCREQ_IFFETCHROW;

	DBCREQ_GET_BEGIN();
	DBCREQ_GET_INT(data, uid);
	DBCREQ_GET_INT(data, free_count);
	DBCREQ_GET_INT(data, today_is_sign);
	DBCREQ_GET_INT(data, sign_num);
	DBCREQ_GET_CHAR(data, target_gots, TARGET_GOTS_SIZE);
	DBCREQ_GET_INT(data, sign_ts);
	DBCREQ_GET_CHAR(data, level_rewards_flags, LEVEL_REWARDS_SIZE);

	return 0;
}


int CDataReward::GetData(uint32_t uid, vector<DataReward> &datas) {
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(free_count);
	DBCREQ_NEED(today_is_sign);
	DBCREQ_NEED(sign_num);
	DBCREQ_NEED(target_gots);
	DBCREQ_NEED(sign_ts);
	DBCREQ_NEED(level_rewards_flags);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;

	DBCREQ_ARRAY_GET_BEGIN(datas);
	DBCREQ_ARRAY_GET_INT(datas, uid);
	DBCREQ_ARRAY_GET_INT(datas, free_count);
	DBCREQ_ARRAY_GET_INT(datas, today_is_sign);
	DBCREQ_ARRAY_GET_INT(datas, sign_num);
	DBCREQ_ARRAY_GET_CHAR(datas, target_gots, TARGET_GOTS_SIZE);
	DBCREQ_ARRAY_GET_INT(datas, sign_ts);
	DBCREQ_ARRAY_GET_CHAR(datas, level_rewards_flags, LEVEL_REWARDS_SIZE);

	DBCREQ_ARRAY_GET_END();
	return 0;
}


