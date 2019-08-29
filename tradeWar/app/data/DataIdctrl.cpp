/*
 * DataIdctrl.cpp
 *
 *  Created on: 2015-9-9
 *      Author: Administrator
 */

#include "DataIdctrl.h"

int CDataIdCtrl::SetId(int key, uint32_t curr_id, uint32_t serverid)
{
	DBCREQ_DECLARE(DBC::UpdateRequest, key);
	DBCREQ_SET_KEY(key);
	DBCREQ_SET_CONDITION(EQ, srv_id, serverid);
	DBCREQ_SET_INT_V(curr_id);
	return 0;
}

int CDataIdCtrl::GetId(int key, uint32_t &curr_id, uint32_t serverid)
{
	DBCREQ_DECLARE(DBC::GetRequest, key);
	DBCREQ_SET_KEY(key);
	DBCREQ_SET_CONDITION(EQ, srv_id, serverid);
	DBCREQ_GET_INT_V(curr_id);
	return 0;
}



