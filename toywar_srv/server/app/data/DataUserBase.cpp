/*
 * DataUserBase.cpp
 *
 *  Created on: 2011-7-9
 *      Author: dada
 */

#include "DataUserBase.h"

int CDataUserBase::AddUserBase(unsigned uid, int base_index, unsigned baseid)
{
	DBCREQ_DECLARE(DBC::InsertRequest, uid);
	DBCREQ_SET_KEY(uid);
	DBCREQ_SET_INT_V(base_index);
	DBCREQ_SET_INT_V(baseid);
	DBCREQ_EXEC;
	return 0;
}

int CDataUserBase::SetUserBase(unsigned uid, int base_index, unsigned baseid)
{
	DBCREQ_DECLARE(DBC::UpdateRequest, uid);
	DBCREQ_SET_KEY(uid);
	DBCREQ_SET_CONDITION(EQ, base_index, base_index);
	DBCREQ_SET_INT_V(baseid);
	DBCREQ_EXEC;
	return 0;
}
int CDataUserBase::GetUserBase(unsigned uid, int base_index, unsigned &baseid)
{
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);
	DBCREQ_SET_CONDITION(EQ, base_index, base_index);
	DBCREQ_GET_INT_V(baseid);
	return 0;
}

int CDataUserBase::GetUserBases(unsigned uid, map<int, unsigned> &bases)
{
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	req.SetKey(uid);
	req.Need("base_index", 1);
	req.Need("baseid", 2);
	DBCREQ_EXEC;
	bases.clear();
	int count = m_dbcret.TotalRows();
	for(int i = 0; i < count; i++)
	{
		DBCREQ_IFFETCHROW;
		bases[m_dbcret.IntValue(1)] = m_dbcret.IntValue(2);
	}
	return 0;
}

int CDataUserBase::RemoveUserBase(unsigned uid, int base_index)
{
	DBCREQ_DECLARE(DBC::DeleteRequest, uid);
	DBCREQ_SET_KEY(uid);
	DBCREQ_SET_CONDITION(EQ, base_index, base_index);
	DBCREQ_EXEC;
	return 0;
}

int CDataUserBase::RemoveUserBases(unsigned uid)
{
	DBCREQ_DECLARE(DBC::DeleteRequest, uid);
	DBCREQ_SET_KEY(uid);
	DBCREQ_EXEC;
	return 0;
}
