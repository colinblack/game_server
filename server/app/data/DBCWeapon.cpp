/*
 * DBCWeapon.cpp
 *
 *  Created on: 2016-9-20
 *      Author: dawx62fac
 */


#include "DBCWeapon.h"

DBCWeapon::DBCWeapon()
	: uid(0)
	, id(0)
	, level(0) //等级   为0时表示未解锁
	, cast(0)  //铸造
	, gem(0)   //宝石
{
}

DBCWeapon::DBCWeapon(uint32_t uid_, uint8_t id_)
	: uid(uid_)
	, id(id_)
	, level(0) //等级   为时表示未解锁
	, cast(0)  //铸造
	, gem(0)   //宝石
{

}

bool DBCWeapon::IsNormal() const
{
	return level > 0;
}

void DBCWeapon::Unlock()
{
	if (level > 0)
	{
		throw std::runtime_error("weapon_unlock_status_error");
	}

	level = 1;
}

void DBCWeapon::Cast(unsigned nMul)
{
	if (level <= 0)
	{
		throw std::runtime_error("weapon_cast_status_error");
	}

	cast += nMul * 5;
	if (cast >= 100)
	{
		level += 1;
		cast = 0;
	}
}

void DBCWeapon::FullMessage(ProtoWeapon::WeaponInfoCPP* obj)
{
	obj->set_id(id);
	obj->set_level(level);
	obj->set_cast(cast);
}

/////////////////////////////////////////////////////////////////////////////////////////
int DBCWeaponHandler::Get(DBCWeapon &data)
{
	warn_log("unrealized_interface");
	return -1;
}

int DBCWeaponHandler::Get(vector<DBCWeapon> &data)
{
	if (data.empty())
	{
		return R_ERROR;
	}

	unsigned uid = data.begin()->uid;
	data.clear();

	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(id);
	DBCREQ_NEED(level);
	DBCREQ_NEED(cast);
	DBCREQ_NEED(gem);

	DBCREQ_EXEC;

	DBCREQ_ARRAY_GET_BEGIN(data);
	DBCREQ_ARRAY_GET_INT(data, uid);
	DBCREQ_ARRAY_GET_INT(data, id);
	DBCREQ_ARRAY_GET_INT(data, level);
	DBCREQ_ARRAY_GET_INT(data, cast);
	DBCREQ_ARRAY_GET_INT(data, gem);
	DBCREQ_ARRAY_GET_END();

	return 0;
}

int DBCWeaponHandler::Add(DBCWeapon &data)
{
	DBCREQ_DECLARE(DBC::InsertRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_INT(data, id);
	DBCREQ_SET_INT(data, level);
	DBCREQ_SET_INT(data, cast);
	DBCREQ_SET_INT(data, gem);

	DBCREQ_EXEC;
	return 0;
}
int DBCWeaponHandler::Set(DBCWeapon &data)
{
	DBCREQ_DECLARE(DBC::UpdateRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_CONDITION(EQ, id, data.id);

	DBCREQ_SET_INT(data, id);
	DBCREQ_SET_INT(data, level);
	DBCREQ_SET_INT(data, cast);
	DBCREQ_SET_INT(data, gem);

	DBCREQ_EXEC;

	return 0;
}
int DBCWeaponHandler::Del(DBCWeapon &data)
{
	warn_log("unrealized_interface");
	return -1;
}

