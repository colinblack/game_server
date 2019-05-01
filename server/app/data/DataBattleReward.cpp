/*
 * DataBattleReward.cpp
 *
 *  Created on: 2016-12-6
 *      Author: Ralf
 */

#include "DataBattleReward.h"


int CDataBattleReward::Get(DataBattleReward &data)
{
	DBCREQ_DECLARE(DBC::GetRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(rts);
	DBCREQ_NEED(r);
	DBCREQ_NEED(ccd);
	DBCREQ_NEED(cts);
	DBCREQ_NEED(ctimes);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;
	DBCREQ_IFFETCHROW;

	DBCREQ_GET_BEGIN();
	DBCREQ_GET_INT(data, uid);
	DBCREQ_GET_INT(data, rts);
	DBCREQ_GET_INT(data, r);
	DBCREQ_GET_INT(data, ccd);
	DBCREQ_GET_INT(data, cts);
	DBCREQ_GET_INT(data, ctimes);
	return 0;
}

int CDataBattleReward::Add(DataBattleReward &data)
{
	DBCREQ_DECLARE(DBC::InsertRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_INT(data, rts);
	DBCREQ_SET_INT(data, r);
	DBCREQ_SET_INT(data, ccd);
	DBCREQ_SET_INT(data, cts);
	DBCREQ_SET_INT(data, ctimes);

	DBCREQ_EXEC;
	return 0;
}

int CDataBattleReward::Set(DataBattleReward &data)
{
	DBCREQ_DECLARE(DBC::UpdateRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_INT(data, rts);
	DBCREQ_SET_INT(data, r);
	DBCREQ_SET_INT(data, ccd);
	DBCREQ_SET_INT(data, cts);
	DBCREQ_SET_INT(data, ctimes);

	DBCREQ_EXEC;
	return 0;
}

