/*
 * DataIdCtrl.cpp
 *
 *  Created on: 2013-2-6
 *      Author: Administrator
 */

#include "DataIdCtrl.h"

int CDataIdCtrl::SetId(int key, uint32_t sid, uint64_t curr_id)
{
	DBCREQ_DECLARE(DBC::UpdateRequest, key);
	DBCREQ_SET_KEY(key);

	DBCREQ_SET_INT_S(sid);
	DBCREQ_SET_INT_S(curr_id);

	DBCREQ_EXEC
	return 0;
}

int CDataIdCtrl::GetId(int key, uint32_t sid, uint64_t &curr_id)
{
	DBCREQ_DECLARE(DBC::GetRequest, key);
	DBCREQ_SET_KEY(key);
	DBCREQ_SET_CONDITION(EQ, sid, sid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(curr_id);

	DBCREQ_EXEC
	DBCREQ_IFNULLROW;
	DBCREQ_IFFETCHROW;

	DBCREQ_GET_BEGIN();
	DBCREQ_GET_INT_S(curr_id);

	return 0;
}
