/*
 * DataUserMapping.cpp
 *
 *  Created on: 2015-9-9
 *      Author: Administrator
 */

#include "DataUserMapping.h"

int CDataUserMapping::AddMapping(unsigned serverId, unsigned platform, const string & openid, unsigned uid)
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
	req.Set("srv_id", serverId);
	req.Set("platform", platform);
	req.Set("uid", uid);
	req.Set("updatetime", Time::GetGlobalTime());
	DBCREQ_EXEC;
	return 0;
}

int CDataUserMapping::GetMapping(unsigned serverId, unsigned platform, const string & openid, unsigned & uid)
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
	req.EQ("srv_id", serverId);
	req.Need("uid", 1);
	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;
	DBCREQ_IFFETCHROW;
	uid = m_dbcret.IntValue(1);
	return 0;
}

int CDataUserMapping::GetAllMapping(const string &openid, vector<pair<unsigned, unsigned> >& vUid)
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
	DBCREQ_SET_KEY(openid.c_str());

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(srv_id);
	DBCREQ_NEED(uid);

	DBCREQ_EXEC;

	DBCREQ_ARRAY_GET_BEGIN(vUid);
	DBCREQ_ARRAY_GET_INT(vUid, first);
	DBCREQ_ARRAY_GET_INT(vUid, second);
	DBCREQ_ARRAY_GET_END();

	return 0;
}

int CDataUserMapping::RemoveMapping(const string & openid)
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
	DBCREQ_EXEC;
	return 0;
}

int CDataUserMapping::SetLastLogin(unsigned serverId, unsigned platform, const string &openid)
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
	DBCREQ_DECLARE(DBC::UpdateRequest, crc);
	req.SetKey(openid.c_str());
	req.EQ("srv_id", serverId);
	req.EQ("platform", platform);
	req.Set("lastlogintime", Time::GetGlobalTime());
	DBCREQ_EXEC;
	return 0;
}

