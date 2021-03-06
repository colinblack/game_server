/*
 * DataIdCtrl.cpp
 *
 *  Created on: 2011-7-14
 *      Author: dada
 */

#include "DataIdCtrl.h"

int CDataIdCtrl::SetId(int key, uint64_t curr_id)
{
	DBCREQ_DECLARE(DBC::UpdateRequest, key);
	DBCREQ_SET_KEY(key);
	DBCREQ_SET_INT_V(curr_id);
	DBCREQ_EXEC;
	return 0;
}

int CDataIdCtrl::GetId(int key, uint64_t &curr_id)
{
	DBCREQ_DECLARE(DBC::GetRequest, key);
	DBCREQ_SET_KEY(key);
	DBCREQ_GET_INT_V(curr_id);
	return 0;
}
