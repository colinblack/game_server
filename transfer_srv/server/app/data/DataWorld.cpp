/*
 * DataWorld.cpp
 *
 *  Created on: 2012-3-13
 *      Author: dada
 */

#include "DataWorld.h"

int CDataWorld::Add(unsigned position, unsigned baseid)
{
	DBCREQ_DECLARE(DBC::InsertRequest, position);
	DBCREQ_SET_KEY(position);
	DBCREQ_SET_INT_V(baseid);
	DBCREQ_EXEC;
	return 0;
}

int CDataWorld::Set(unsigned position, unsigned baseid)
{
	DBCREQ_DECLARE(DBC::UpdateRequest, position);
	DBCREQ_SET_KEY(position);
	DBCREQ_SET_INT_V(baseid);
	DBCREQ_EXEC;
	return 0;
}

int CDataWorld::Get(unsigned position, unsigned &baseid)
{
	DBCREQ_DECLARE(DBC::GetRequest, position);
	DBCREQ_SET_KEY(position);
	DBCREQ_GET_INT_V(baseid);
	return 0;
}

int CDataWorld::Remove(unsigned position)
{
	DBCREQ_DECLARE(DBC::DeleteRequest, position);
	DBCREQ_SET_KEY(position);
	DBCREQ_EXEC;
	return 0;
}

int CDataWorld::Replace(unsigned position, unsigned baseid)
{
	DBCREQ_DECLARE(DBC::ReplaceRequest, position);
	DBCREQ_SET_KEY(position);
	DBCREQ_SET_INT_V(baseid);
	DBCREQ_EXEC;
	return 0;
}

