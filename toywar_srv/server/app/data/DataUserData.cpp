/*
 * DataUserData.cpp
 *
 *  Created on: 2011-11-1
 *      Author: dada
 */

#include "DataUserData.h"

int CDataUserData::AddData(unsigned uid, const string &data)
{
	DBCREQ_DECLARE(DBC::InsertRequest, uid);
	DBCREQ_SET_KEY(uid);
	DBCREQ_SET_STR_V(data);
	DBCREQ_EXEC;
	return 0;
}
int CDataUserData::SetData(unsigned uid, const string &data)
{
	DBCREQ_DECLARE(DBC::UpdateRequest, uid);
	DBCREQ_SET_KEY(uid);
	DBCREQ_SET_STR_V(data);
	DBCREQ_EXEC;
	return 0;
}
int CDataUserData::GetData(unsigned uid, string &data)
{
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);
	DBCREQ_GET_STR_V(data);
	return 0;
}

int CDataUserData::RemoveData(unsigned uid)
{
	DBCREQ_DECLARE(DBC::DeleteRequest, uid);
	DBCREQ_SET_KEY(uid);
	DBCREQ_EXEC;
	return 0;
}
