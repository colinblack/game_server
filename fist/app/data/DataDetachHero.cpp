/*
 * DataDetachHero.cpp
 *
 *  Created on: 2018年11月16日
 *      Author: colin
 */

#include "DataDetachHero.h"

int CDataDetachHero::Get(DataDetachHero &data)
{
    DBCREQ_DECLARE(DBC::GetRequest, data.uid);
    DBCREQ_SET_KEY(data.uid);
    DBCREQ_SET_CONDITION(EQ, id, data.id);

    DBCREQ_NEED_BEGIN();
    DBCREQ_NEED(uid);
    DBCREQ_NEED(id);
    DBCREQ_NEED(detach_uid);
    DBCREQ_NEED(detach_slot);
    DBCREQ_NEED(club_level);
    DBCREQ_NEED(hero_num);
    DBCREQ_NEED(detach_coins);
    DBCREQ_NEED(start_ts);

    DBCREQ_EXEC;
    DBCREQ_IFNULLROW;
    DBCREQ_IFFETCHROW;

    DBCREQ_GET_BEGIN();
    DBCREQ_GET_INT(data, uid);
    DBCREQ_GET_INT(data, id);
    DBCREQ_GET_INT(data, detach_uid);
    DBCREQ_GET_INT(data, detach_slot);
    DBCREQ_GET_INT(data, club_level);
    DBCREQ_GET_INT(data, hero_num);
    DBCREQ_GET_INT(data, detach_coins);
    DBCREQ_GET_INT(data, start_ts);

    return 0;
}

int CDataDetachHero::Get(vector<DataDetachHero>&data)
{
	if (0 == data.size())
	{
		return R_ERR_PARAM;
	}

	DBCREQ_DECLARE(DBC::GetRequest, data[0].uid);
	DBCREQ_SET_KEY(data[0].uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(id);
	DBCREQ_NEED(detach_uid);
	DBCREQ_NEED(detach_slot);
	DBCREQ_NEED(club_level);
	DBCREQ_NEED(hero_num);
	DBCREQ_NEED(detach_coins);
	DBCREQ_NEED(start_ts);

	data.clear();

	DBCREQ_EXEC;
	DBCREQ_ARRAY_GET_BEGIN(data);
	DBCREQ_ARRAY_GET_INT(data, uid);
	DBCREQ_ARRAY_GET_INT(data, id);
	DBCREQ_ARRAY_GET_INT(data, detach_uid);
	DBCREQ_ARRAY_GET_INT(data, detach_slot);
	DBCREQ_ARRAY_GET_INT(data, club_level);
	DBCREQ_ARRAY_GET_INT(data, hero_num);
	DBCREQ_ARRAY_GET_INT(data, detach_coins);
	DBCREQ_ARRAY_GET_INT(data, start_ts);

	DBCREQ_ARRAY_GET_END();

	return 0;
}

int CDataDetachHero::Add(DataDetachHero &data)
{
    DBCREQ_DECLARE(DBC::InsertRequest, data.uid);
    DBCREQ_SET_KEY(data.uid);

    DBCREQ_SET_INT(data, id);
    DBCREQ_SET_INT(data, detach_uid);
    DBCREQ_SET_INT(data, detach_slot);
    DBCREQ_SET_INT(data, club_level);
    DBCREQ_SET_INT(data, hero_num);
    DBCREQ_SET_INT(data, detach_coins);
    DBCREQ_SET_INT(data, start_ts);

    DBCREQ_EXEC;

	return 0;
}

int CDataDetachHero::Set(DataDetachHero &data)
{
    DBCREQ_DECLARE(DBC::UpdateRequest, data.uid);
    DBCREQ_SET_KEY(data.uid);
    DBCREQ_SET_CONDITION(EQ, id, data.id);

    DBCREQ_SET_INT(data, detach_uid);
    DBCREQ_SET_INT(data, detach_slot);
    DBCREQ_SET_INT(data, club_level);
    DBCREQ_SET_INT(data, hero_num);
    DBCREQ_SET_INT(data, detach_coins);
    DBCREQ_SET_INT(data, start_ts);

    DBCREQ_EXEC;

	return 0;

}

int CDataDetachHero::Del(DataDetachHero &data)
{
	DBCREQ_DECLARE(DBC::DeleteRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
    DBCREQ_SET_CONDITION(EQ, id, data.id);
	DBCREQ_EXEC;

	return 0;
}


