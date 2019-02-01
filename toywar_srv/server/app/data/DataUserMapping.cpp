/*
 * DataUserMapping.cpp
 *
 *  Created on: 2011-7-8
 *      Author: dada
 */

#include "DataUserMapping.h"
#include "crc.h"

int CDataUserMapping::AddMapping(const string &openid, int platform, unsigned uid)
{
	unsigned crc = CCRC::GetCrc32(openid);
	if (crc > UID_MAX)
	{
		crc %= UID_MAX;
		if (crc < UID_MIN)
		{
			crc += UID_MIN;
		}
	}
	DBCREQ_DECLARE(DBC::InsertRequest, crc);
	req.SetKey(openid.c_str());
	req.Set("uid", uid);
	req.Set("platform", platform);
	req.Set("updatetime", Time::GetGlobalTime());
	DBCREQ_EXEC;
	return 0;
}

int CDataUserMapping::GetMapping(const string &openid, int platform, unsigned &uid)
{
	unsigned crc = CCRC::GetCrc32(openid);
	if (crc > UID_MAX)
	{
		crc %= UID_MAX;
		if (crc < UID_MIN)
		{
			crc += UID_MIN;
		}
	}
	DBCREQ_DECLARE(DBC::GetRequest, crc);
	req.SetKey(openid.c_str());
	req.EQ("platform", platform);
	req.Need("uid", 1);
	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;
	DBCREQ_IFFETCHROW;
	uid = m_dbcret.IntValue(1);
	return 0;
}

int CDataUserMapping::RemoveMapping(const string &openid, int platform)
{
	unsigned crc = CCRC::GetCrc32(openid);
	if (crc > UID_MAX)
	{
		crc %= UID_MAX;
		if (crc < UID_MIN)
		{
			crc += UID_MIN;
		}
	}
	DBCREQ_DECLARE(DBC::DeleteRequest, crc);
	DBCREQ_SET_KEY(openid.c_str());
	DBCREQ_SET_CONDITION(EQ, platform, platform);
	DBCREQ_EXEC;
	return 0;
}

