/*
 * DataBase.cpp
 *
 *  Created on: 2011-7-11
 *      Author: dada
 */

#include "DataBase.h"

int CDataBase::AddBase(DataBase &base)
{
	DBCREQ_DECLARE(DBC::InsertRequest, base.baseid);
	DBCREQ_SET_KEY(base.baseid);
	DBCREQ_SET_INT(base, uid);
	DBCREQ_SET_INT(base, base_index);
	DBCREQ_SET_INT(base, type);
	DBCREQ_SET_STR(base, base_name);
	DBCREQ_SET_INT(base, seed);
	DBCREQ_SET_INT(base, position);
	DBCREQ_SET_INT(base, create_time);
	DBCREQ_SET_INT(base, save_time);
	DBCREQ_SET_INT(base, saveby_uid);
	DBCREQ_SET_INT(base, protected_time);
	DBCREQ_SET_INT(base, last_active_time);
	DBCREQ_SET_INT(base, status);
	DBCREQ_SET_INT(base, damage);
	DBCREQ_SET_INT(base, destroyed);
	DBCREQ_SET_INT(base, value);
	DBCREQ_SET_INT(base, attack_level);
	DBCREQ_SET_INT(base, bomb_level);
	DBCREQ_EXEC;
	return 0;
}

int CDataBase::SetBase(const DataBase &base)
{
	DBCREQ_DECLARE(DBC::UpdateRequest, base.baseid);
	DBCREQ_SET_KEY(base.baseid);
	DBCREQ_SET_INT(base, uid);
	DBCREQ_SET_INT(base, base_index);
	DBCREQ_SET_INT(base, type);
	DBCREQ_SET_STR(base, base_name);
	DBCREQ_SET_INT(base, seed);
	DBCREQ_SET_INT(base, position);
	DBCREQ_SET_INT(base, create_time);
	DBCREQ_SET_INT(base, save_time);
	DBCREQ_SET_INT(base, saveby_uid);
	DBCREQ_SET_INT(base, protected_time);
	DBCREQ_SET_INT(base, last_active_time);
	DBCREQ_SET_INT(base, status);
	DBCREQ_SET_INT(base, damage);
	DBCREQ_SET_INT(base, destroyed);
	DBCREQ_SET_INT(base, value);
	DBCREQ_SET_INT(base, attack_level);
	DBCREQ_SET_INT(base, bomb_level);
	DBCREQ_EXEC;
	return 0;
}

int CDataBase::GetBase(unsigned baseid, DataBase &base)
{
	DBCREQ_DECLARE(DBC::GetRequest, baseid);
	DBCREQ_SET_KEY(baseid);
	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(baseid);
	DBCREQ_NEED(uid);
	DBCREQ_NEED(base_index);
	DBCREQ_NEED(type);
	DBCREQ_NEED(base_name);
	DBCREQ_NEED(seed);
	DBCREQ_NEED(position);
	DBCREQ_NEED(create_time);
	DBCREQ_NEED(save_time);
	DBCREQ_NEED(saveby_uid);
	DBCREQ_NEED(protected_time);
	DBCREQ_NEED(last_active_time);
	DBCREQ_NEED(status);
	DBCREQ_NEED(damage);
	DBCREQ_NEED(destroyed);
	DBCREQ_NEED(value);
	DBCREQ_NEED(attack_level);
	DBCREQ_NEED(bomb_level);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;
	DBCREQ_IFFETCHROW;

	DBCREQ_GET_BEGIN();
	DBCREQ_GET_INT(base, baseid);
	DBCREQ_GET_INT(base, uid);
	DBCREQ_GET_INT(base, base_index);
	DBCREQ_GET_INT(base, type);
	DBCREQ_GET_STR(base, base_name);
	DBCREQ_GET_INT(base, seed);
	DBCREQ_GET_INT(base, position);
	DBCREQ_GET_INT(base, create_time);
	DBCREQ_GET_INT(base, save_time);
	DBCREQ_GET_INT(base, saveby_uid);
	DBCREQ_GET_INT(base, protected_time);
	DBCREQ_GET_INT(base, last_active_time);
	DBCREQ_GET_INT(base, status);
	DBCREQ_GET_INT(base, damage);
	DBCREQ_GET_INT(base, destroyed);
	DBCREQ_GET_INT(base, value);
	DBCREQ_GET_INT(base, attack_level);
	DBCREQ_GET_INT(base, bomb_level);

	return 0;
}

int CDataBase::RemoveBase(unsigned baseid)
{
	DBCREQ_DECLARE(DBC::DeleteRequest, baseid);
	DBCREQ_SET_KEY(baseid);
	DBCREQ_EXEC;
	return 0;
}

int CDataBase::SetActiveTime(unsigned baseid, unsigned last_active_time)
{
	DBCREQ_DECLARE(DBC::UpdateRequest, baseid);
	DBCREQ_SET_KEY(baseid);
	DBCREQ_SET_INT_V(last_active_time);
	DBCREQ_EXEC;
	return 0;
}

int CDataBase::SetPosition(unsigned baseid, unsigned position)
{
	DBCREQ_DECLARE(DBC::UpdateRequest, baseid);
	DBCREQ_SET_KEY(baseid);
	DBCREQ_SET_INT_V(position);
	DBCREQ_EXEC;
	return 0;
}

int CDataBase::GetPosition(unsigned baseid, unsigned &position)
{
	DBCREQ_DECLARE(DBC::GetRequest, baseid);
	DBCREQ_SET_KEY(baseid);
	DBCREQ_GET_INT_V(position);
	return 0;
}

