/*
 * DataAllianceMapping.cpp
 *
 *  Created on: 2011-9-29
 *      Author: dada
 */

#include "DataAllianceMapping.h"

int CDataAllianceMapping::AddMapping(const string &alliance_name, unsigned alliance_id)
{
	DBCREQ_DECLARE(DBC::InsertRequest, CCRC::GetCrc32(alliance_name));
	DBCREQ_SET_KEY(alliance_name.c_str());
	DBCREQ_SET_INT_V(alliance_id);
	DBCREQ_EXEC;
	return 0;
}

int CDataAllianceMapping::GetMapping(const string &alliance_name, unsigned &alliance_id)
{
	DBCREQ_DECLARE(DBC::GetRequest, CCRC::GetCrc32(alliance_name));
	DBCREQ_SET_KEY(alliance_name.c_str());
	DBCREQ_GET_INT_V(alliance_id);
	return 0;
}

int CDataAllianceMapping::RemoveMapping(const string &alliance_name)
{
	DBCREQ_DECLARE(DBC::DeleteRequest, CCRC::GetCrc32(alliance_name));
	DBCREQ_SET_KEY(alliance_name.c_str());
	DBCREQ_EXEC;
	return 0;
}
