/*
 * DataCashBack.cpp
 *
 *  Created on: 2016-11-22
 *      Author: dawx62fac
 */


#include "DataCashBack.h"

DBCCashBack::DBCCashBack()
	: uid(0)
	, version(0)
	, total(0)
	, reward_flag(0)
	, ts_op(0)
{
}

void DBCCashBack::Reset(unsigned version_)
{
	version = version_;
	reward_flag = 0;
	ts_op = Time::GetGlobalTime();
	total = 0;
}
/////////////////////////////////////////////////////////////////////////////
int DBCCashBackHandler::Get(DBCCashBack &data)
{
	DBCREQ_DECLARE(DBC::GetRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(version);
	DBCREQ_NEED(total);
	DBCREQ_NEED(reward_flag);
	DBCREQ_NEED(ts_op);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;
	DBCREQ_IFFETCHROW;

	DBCREQ_GET_BEGIN();
	DBCREQ_GET_INT(data, uid);
	DBCREQ_GET_INT(data, version);
	DBCREQ_GET_INT(data, total);
	DBCREQ_GET_INT(data, reward_flag);
	DBCREQ_GET_INT(data, ts_op);

	return 0;
}

int DBCCashBackHandler::Add(DBCCashBack &data)
{
	DBCREQ_DECLARE(DBC::InsertRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_SET_INT(data, version);
	DBCREQ_SET_INT(data, total);
	DBCREQ_SET_INT(data, reward_flag);
	DBCREQ_SET_INT(data, ts_op);

	DBCREQ_EXEC;

	return 0;
}

int DBCCashBackHandler::Set(DBCCashBack &data)
{
	DBCREQ_DECLARE(DBC::UpdateRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_SET_INT(data, version);
	DBCREQ_SET_INT(data, total);
	DBCREQ_SET_INT(data, reward_flag);
	DBCREQ_SET_INT(data, ts_op);

	DBCREQ_EXEC;
	return 0;
}

int DBCCashBackHandler::Get(vector<DBCCashBack> &data)
{
	warn_log("nonsupport_interface");
	return 0;
}

int DBCCashBackHandler::Del(DBCCashBack &data)
{
	//
	warn_log("nonsupport_interface");
	return 0;
}
