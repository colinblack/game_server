/*
 * DataTimeLimitProp.cpp
 *
 *  Created on: 2016-11-29
 *      Author: dawx62fac
 */


#include "DataTimeLimitProp.h"

DBCTimeLimitProp::DBCTimeLimitProp(unsigned uid_, unsigned id_)
	: uid(uid_), id(id_), op_time(0)
{
}

DBCTimeLimitProp::DBCTimeLimitProp()
	: uid(0), id(0), op_time(0)
{
}

/////////////////////////////////////////////////////////////
int DBCTimeLimitPropHandler::Get(DBCTimeLimitProp &data)
{
	warn_log("unrealized_interface");
	return -1;
}

int DBCTimeLimitPropHandler::Get(vector<DBCTimeLimitProp> &data)
{
	if (data.empty())
	{
		return R_ERROR;
	}

	unsigned uid = data.begin()->uid;
	data.clear();

	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(id);
	DBCREQ_NEED(op_time);

	DBCREQ_EXEC;

	DBCREQ_ARRAY_GET_BEGIN(data);
	DBCREQ_ARRAY_GET_INT(data, uid);
	DBCREQ_ARRAY_GET_INT(data, id);
	DBCREQ_ARRAY_GET_INT(data, op_time);
	DBCREQ_ARRAY_GET_END();

	return 0;
}

int DBCTimeLimitPropHandler::Add(DBCTimeLimitProp &data)
{
	DBCREQ_DECLARE(DBC::InsertRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_INT(data, id);
	DBCREQ_SET_INT(data, op_time);

	DBCREQ_EXEC;
	return 0;
}

int DBCTimeLimitPropHandler::Set(DBCTimeLimitProp &data)
{
	DBCREQ_DECLARE(DBC::UpdateRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_CONDITION(EQ, id, data.id);

	DBCREQ_SET_INT(data, id);
	DBCREQ_SET_INT(data, op_time);

	DBCREQ_EXEC;

	return 0;
}

int DBCTimeLimitPropHandler::Del(DBCTimeLimitProp &data)
{
	DBCREQ_DECLARE(DBC::DeleteRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_CONDITION(EQ, id, data.id);
	DBCREQ_EXEC;
	return 0;
}

