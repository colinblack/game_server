/*
 * DataUnlockCards.cpp
 *
 *  Created on: 2018年11月23日
 *      Author: colin
 */

#include "DataUnlockCards.h"

int  CDataUnlockCards::Get(DataUnlockCards &data)
{
	DBCREQ_DECLARE(DBC::GetRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_CONDITION(EQ, id, data.id);

    DBCREQ_NEED_BEGIN();
    DBCREQ_NEED(uid);
    DBCREQ_NEED(id);

    DBCREQ_EXEC;
    DBCREQ_IFNULLROW;
    DBCREQ_IFFETCHROW;

    DBCREQ_GET_BEGIN();
    DBCREQ_GET_INT(data, uid);
    DBCREQ_GET_INT(data, id);

    return 0;
}

int CDataUnlockCards::Get(vector<DataUnlockCards>& data)
{
	if (0 == data.size())
	{
		return R_ERR_PARAM;
	}

	DBCREQ_DECLARE(DBC::GetRequest, data[0].uid);
	DBCREQ_SET_KEY(data[0].uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(id);

    data.clear();

    DBCREQ_EXEC;
	DBCREQ_ARRAY_GET_BEGIN(data);
	DBCREQ_ARRAY_GET_INT(data, uid);
	DBCREQ_ARRAY_GET_INT(data, id);


	DBCREQ_ARRAY_GET_END();

	return 0;
}

int CDataUnlockCards::Add(DataUnlockCards& data)
{
	DBCREQ_DECLARE(DBC::InsertRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

    DBCREQ_SET_INT(data, id);

    DBCREQ_EXEC;

    return 0;
}


int CDataUnlockCards::Set(DataUnlockCards &data)
{
	DBCREQ_DECLARE(DBC::UpdateRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_CONDITION(EQ, id, data.id);

   DBCREQ_EXEC;

   return 0;
}

int CDataUnlockCards::Del(DataUnlockCards &data)
{
	DBCREQ_DECLARE(DBC::DeleteRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_CONDITION(EQ, id, data.id);
	DBCREQ_EXEC;

	return 0;
}





