/*
 * DataPay.cpp
 *
 *  Created on: 2011-7-9
 *      Author: dada
 */

#include "DataPay.h"

int CDataPay::AddPay(unsigned uid, unsigned cash)
{
	DBCREQ_DECLARE(DBC::InsertRequest, uid);
	DBCREQ_SET_KEY(uid);
	DBCREQ_SET_INT_V(cash);
	DBCREQ_EXEC;
	return 0;
}

int CDataPay::SetPay(unsigned uid, unsigned cash)
{
	DBCREQ_DECLARE(DBC::UpdateRequest, uid);
	DBCREQ_SET_KEY(uid);
	DBCREQ_SET_INT_V(cash);
	DBCREQ_EXEC;
	return 0;
}

int CDataPay::GetPay(unsigned uid, unsigned &cash)
{
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);
	DBCREQ_GET_INT_V(cash);
	return 0;
}

int CDataPay::RemovePay(unsigned uid)
{
	DBCREQ_DECLARE(DBC::DeleteRequest, uid);
	DBCREQ_SET_KEY(uid);
	DBCREQ_EXEC;
	return 0;
}

