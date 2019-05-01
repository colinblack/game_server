/*
 * DataGem.cpp
 *
 *  Created on: 2016-9-23
 *      Author: dawx62fac
 */


#include "DataGem.h"


DBCGem::DBCGem()
	: uid(0), level(0), number(0)
{
}


DBCGem::DBCGem(unsigned uid_, uint8_t level_)
	: uid(uid_), level(level_), number(0)
{
}


/////////////////////////////////////////////////////////////////////////////////////////
int DBCGemHandler::Get(DBCGem &data)
{
	warn_log("unrealized_interface");
	return -1;
}

int DBCGemHandler::Get(vector<DBCGem> &data)
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
	DBCREQ_NEED(level);
	DBCREQ_NEED(number);

	DBCREQ_EXEC;

	DBCREQ_ARRAY_GET_BEGIN(data);
	DBCREQ_ARRAY_GET_INT(data, uid);
	DBCREQ_ARRAY_GET_INT(data, level);
	DBCREQ_ARRAY_GET_INT(data, number);
	DBCREQ_ARRAY_GET_END();

	return 0;
}

int DBCGemHandler::Add(DBCGem &data)
{
	DBCREQ_DECLARE(DBC::InsertRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_INT(data, level);
	DBCREQ_SET_INT(data, number);

	DBCREQ_EXEC;
	return 0;
}
int DBCGemHandler::Set(DBCGem &data)
{
	DBCREQ_DECLARE(DBC::UpdateRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_CONDITION(EQ, level, data.level);
	DBCREQ_SET_INT(data, number);

	DBCREQ_EXEC;

	return 0;
}
int DBCGemHandler::Del(DBCGem &data)
{
	warn_log("unrealized_interface");
	return -1;
}

