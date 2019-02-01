/*
 * DataVipCharge.cpp
 *
 *  Created on: 2014-3-6
 *      Author: dada
 */

#include "DataVipCharge.h"
#include "crc.h"

int CDataVipCharge::AddVipCharge(const string &openid,int total,int used)
{
	unsigned crc = CCRC::GetCrc32(openid);
	if (crc > UID_MAX) {
		crc %= UID_MAX;
		if (crc < UID_MIN) {
			crc += UID_MIN;
		}
	}

	unsigned updatetime = Time::GetGlobalTime();
	DBCREQ_DECLARE(DBC::InsertRequest, crc);
	DBCREQ_SET_KEY(openid.c_str());
	DBCREQ_SET_INT_S(total);
	DBCREQ_SET_INT_S(used);
	DBCREQ_SET_INT_S(updatetime);

	DBCREQ_EXEC;
	return 0;

}

int CDataVipCharge::AddBlueYearVipCharge(const string &openid, int hero_total,int hero_used)
{
	unsigned crc = CCRC::GetCrc32(openid);
		if (crc > UID_MAX) {
			crc %= UID_MAX;
			if (crc < UID_MIN) {
				crc += UID_MIN;
			}
		}

		DBCREQ_DECLARE(DBC::InsertRequest, crc);
		DBCREQ_SET_KEY(openid.c_str());
		DBCREQ_SET_INT_S(hero_total);
		DBCREQ_SET_INT_S(hero_used);

		DBCREQ_EXEC;
		return 0;
}

int CDataVipCharge::UpdateVipChargeUsed(const string &openid,int total,int used)
{
	unsigned crc = CCRC::GetCrc32(openid);
	if (crc > UID_MAX) {
		crc %= UID_MAX;
		if (crc < UID_MIN) {
			crc += UID_MIN;
		}
	}

	unsigned updatetime = Time::GetGlobalTime();
	DBCREQ_DECLARE(DBC::UpdateRequest, crc);
	DBCREQ_SET_KEY(openid.c_str());
	DBCREQ_SET_INT_S(total);
	DBCREQ_SET_INT_S(used);
	DBCREQ_SET_INT_S(updatetime);
	DBCREQ_EXEC;
	return 0;
}

int CDataVipCharge::UpdateBlueYearVipChargeUsed(const string &openid,int hero_total,int hero_used)
{
	unsigned crc = CCRC::GetCrc32(openid);
	if (crc > UID_MAX) {
		crc %= UID_MAX;
		if (crc < UID_MIN) {
			crc += UID_MIN;
		}
	}

	DBCREQ_DECLARE(DBC::UpdateRequest, crc);
	DBCREQ_SET_KEY(openid.c_str());
	DBCREQ_SET_INT_S(hero_total);
	DBCREQ_SET_INT_S(hero_used);
	DBCREQ_EXEC;
	return 0;
}

int CDataVipCharge::GetVipCharge(const string &openid, int &total,int &used,unsigned &updatetime)
{
	unsigned crc = CCRC::GetCrc32(openid);
	if (crc > UID_MAX) {
		crc %= UID_MAX;
		if (crc < UID_MIN) {
			crc += UID_MIN;
		}
	}

	DBCREQ_DECLARE(DBC::GetRequest, crc);
	DBCREQ_SET_KEY(openid.c_str());

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(total);
	DBCREQ_NEED(used);
	DBCREQ_NEED(updatetime);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;
	DBCREQ_IFFETCHROW;

	DBCREQ_GET_BEGIN();
	DBCREQ_GET_INT_S(total);
	DBCREQ_GET_INT_S(used);
	DBCREQ_GET_INT_S(updatetime);

	return 0;
}

int CDataVipCharge::GetBlueYearVipCharge(const string &openid, int &hero_total,int &hero_used)
{
	unsigned crc = CCRC::GetCrc32(openid);
	if (crc > UID_MAX) {
		crc %= UID_MAX;
		if (crc < UID_MIN) {
			crc += UID_MIN;
		}
	}

	DBCREQ_DECLARE(DBC::GetRequest, crc);
	DBCREQ_SET_KEY(openid.c_str());

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(hero_total);
	DBCREQ_NEED(hero_used);


	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;
	DBCREQ_IFFETCHROW;

	DBCREQ_GET_BEGIN();
	DBCREQ_GET_INT_S(hero_total);
	DBCREQ_GET_INT_S(hero_used);


	return 0;
}
