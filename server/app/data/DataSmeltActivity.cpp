/*
 * DataSmeltActivity.cpp
 *
 *  Created on: 2016-12-5
 *      Author: dawx62fac
 */

#include "DataSmeltActivity.h"

DBCSmeltActivity::DBCSmeltActivity()
	: uid(0)
	, version(0)
	, total(0)
	, reward_1_cnt(0)
	, reward_2_cnt(0)
	, reward_3_cnt(0)
{

}

void DBCSmeltActivity::Reset(unsigned version_)
{
	version = version_;
	total = 0;
	reward_1_cnt = 0;
	reward_2_cnt = 0;
	reward_3_cnt = 0;
}

uint16_t DBCSmeltActivity::GetRewardCnt(int id) const
{
	if (id < 1 || id > 3)
	{
		throw std::runtime_error("id_params_error");
	}

	uint16_t rewards[3] = {reward_1_cnt, reward_2_cnt, reward_3_cnt};
	return (rewards[id - 1]);
}

uint16_t* DBCSmeltActivity::RewardCnt(int id)
{
	if (id < 1 || id > 3)
	{
		throw std::runtime_error("id_params_error");
	}

	uint16_t* rewards[3] = {&reward_1_cnt, &reward_2_cnt, &reward_3_cnt};
	return rewards[id - 1];
}
////////////////////////////////////////////////////////////////////////////////
int DBCSmeltActivityHandler::Get(DBCSmeltActivity &data)
{
	DBCREQ_DECLARE(DBC::GetRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(version);
	DBCREQ_NEED(total);
	DBCREQ_NEED(reward_1_cnt);
	DBCREQ_NEED(reward_2_cnt);
	DBCREQ_NEED(reward_3_cnt);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;
	DBCREQ_IFFETCHROW;

	DBCREQ_GET_BEGIN();
	DBCREQ_GET_INT(data, uid);
	DBCREQ_GET_INT(data, version);
	DBCREQ_GET_INT(data, total);
	DBCREQ_GET_INT(data, reward_1_cnt);
	DBCREQ_GET_INT(data, reward_2_cnt);
	DBCREQ_GET_INT(data, reward_3_cnt);

	return 0;
}

int DBCSmeltActivityHandler::Get(vector<DBCSmeltActivity> &data)
{
	warn_log("nonsupport_interface");
	return 0;
}

int DBCSmeltActivityHandler::Add(DBCSmeltActivity &data)
{
	DBCREQ_DECLARE(DBC::InsertRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_SET_INT(data, version);
	DBCREQ_SET_INT(data, total);
	DBCREQ_SET_INT(data, reward_1_cnt);
	DBCREQ_SET_INT(data, reward_2_cnt);
	DBCREQ_SET_INT(data, reward_3_cnt);

	DBCREQ_EXEC;

	return 0;
}
int DBCSmeltActivityHandler::Set(DBCSmeltActivity &data)
{
	DBCREQ_DECLARE(DBC::UpdateRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_SET_INT(data, version);
	DBCREQ_SET_INT(data, total);
	DBCREQ_SET_INT(data, reward_1_cnt);
	DBCREQ_SET_INT(data, reward_2_cnt);
	DBCREQ_SET_INT(data, reward_3_cnt);

	DBCREQ_EXEC;

	return 0;
}

int DBCSmeltActivityHandler::Del(DBCSmeltActivity &data)
{
	warn_log("nonsupport_interface");
	return 0;
}
