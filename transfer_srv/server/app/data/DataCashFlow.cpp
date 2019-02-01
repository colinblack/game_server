/*
 * DataCashFlow.cpp
 *
 *  Created on: 2011-12-31
 *      Author: dada
 */

#include "DataCashFlow.h"

int CDataCashFlow::AddCashFlow(const DataCashFlow &flow)
{
	DBCREQ_DECLARE(DBC::InsertRequest, flow.uid);
	DBCREQ_SET_KEY(flow.uid);
	DBCREQ_SET_INT(flow, flow_id);
	DBCREQ_SET_STR(flow, type);
	DBCREQ_SET_INT(flow, count);
	DBCREQ_SET_INT(flow, cash);
	DBCREQ_SET_INT(flow, balance);
	DBCREQ_SET_INT(flow, time);
	DBCREQ_SET_INT(flow, data);
	DBCREQ_EXEC;
	return 0;
}

int CDataCashFlow::GetCashFlows(unsigned uid, unsigned startTime, unsigned endTime, vector<DataCashFlow> &flows)
{
	DBCREQ_DECLARE(DBC::GetRequest, uid);

	DBCREQ_SET_KEY(uid);
	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(flow_id);
	DBCREQ_NEED(type);
	DBCREQ_NEED(count);
	DBCREQ_NEED(cash);
	DBCREQ_NEED(balance);
	DBCREQ_NEED(time);
	DBCREQ_NEED(data);
	if(startTime != 0)
	{
		DBCREQ_SET_CONDITION(GE, time, startTime);
	}
	if(endTime != 0)
	{
		DBCREQ_SET_CONDITION(LE, time, endTime);
	}

	DBCREQ_EXEC;

	DBCREQ_ARRAY_GET_BEGIN(flows);
	DBCREQ_ARRAY_GET_INT(flows, uid);
	DBCREQ_ARRAY_GET_INT(flows, flow_id);
	DBCREQ_ARRAY_GET_STR(flows, type);
	DBCREQ_ARRAY_GET_INT(flows, count);
	DBCREQ_ARRAY_GET_INT(flows, cash);
	DBCREQ_ARRAY_GET_INT(flows, balance);
	DBCREQ_ARRAY_GET_INT(flows, time);
	DBCREQ_ARRAY_GET_INT(flows, data);
	DBCREQ_ARRAY_GET_END();

	return 0;
}
