/*
 * DataBaseExtra.cpp
 *
 *  Created on: 2012-3-1
 *      Author: dada
 */

#include "DataBaseExtra.h"

//DataBaseExtra &DataBaseExtra::operator=(const DataBaseExtra &baseExtra)
//{
//	baseid = baseExtra.baseid;
//	updates = baseExtra.updates;
//	building = baseExtra.building;
//	effect = baseExtra.effect;
//	aiattack = baseExtra.aiattack;
//	manoeuvre = baseExtra.manoeuvre;
//	grower = baseExtra.grower;
//	military = baseExtra.military;
//	hero = baseExtra.hero;
//	recycle = baseExtra.recycle;
//	consume = baseExtra.consume;
//	extra_data = baseExtra.extra_data;
//	return *this;
//}

int CDataBaseExtra::AddBase(DataBaseExtra &base)
{
	DBCREQ_DECLARE(DBC::InsertRequest, base.baseid);
	DBCREQ_SET_KEY(base.baseid);
	DBCREQ_SET_STR(base, updates);
	DBCREQ_SET_STR(base, building);
	DBCREQ_SET_STR(base, effect);
	DBCREQ_SET_STR(base, aiattack);
	DBCREQ_SET_STR(base, manoeuvre);
	DBCREQ_SET_STR(base, grower);
	DBCREQ_SET_STR(base, military);
	DBCREQ_SET_STR(base, hero);
	DBCREQ_SET_STR(base, recycle);
	DBCREQ_SET_STR(base, consume);
	DBCREQ_SET_STR(base, extra_data);
	DBCREQ_EXEC;
	return 0;
}

int CDataBaseExtra::SetBase(const DataBaseExtra &base)
{
	DBCREQ_DECLARE(DBC::UpdateRequest, base.baseid);
	DBCREQ_SET_KEY(base.baseid);
	DBCREQ_SET_STR(base, updates);
	DBCREQ_SET_STR(base, building);
	DBCREQ_SET_STR(base, effect);
	DBCREQ_SET_STR(base, aiattack);
	DBCREQ_SET_STR(base, manoeuvre);
	DBCREQ_SET_STR(base, grower);
	DBCREQ_SET_STR(base, military);
	DBCREQ_SET_STR(base, hero);
	DBCREQ_SET_STR(base, recycle);
	DBCREQ_SET_STR(base, consume);
	DBCREQ_SET_STR(base, extra_data);
	DBCREQ_EXEC;
	return 0;
}

int CDataBaseExtra::GetBase(unsigned baseid, DataBaseExtra &base)
{
	DBCREQ_DECLARE(DBC::GetRequest, baseid);
	DBCREQ_SET_KEY(baseid);
	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(baseid);
	DBCREQ_NEED(updates);
	DBCREQ_NEED(building);
	DBCREQ_NEED(effect);
	DBCREQ_NEED(aiattack);
	DBCREQ_NEED(manoeuvre);
	DBCREQ_NEED(grower);
	DBCREQ_NEED(military);
	DBCREQ_NEED(hero);
	DBCREQ_NEED(recycle);
	DBCREQ_NEED(consume);
	DBCREQ_NEED(extra_data);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;
	DBCREQ_IFFETCHROW;

	DBCREQ_GET_BEGIN();
	DBCREQ_GET_INT(base, baseid);
	DBCREQ_GET_STR(base, updates);
	DBCREQ_GET_STR(base, building);
	DBCREQ_GET_STR(base, effect);
	DBCREQ_GET_STR(base, aiattack);
	DBCREQ_GET_STR(base, manoeuvre);
	DBCREQ_GET_STR(base, grower);
	DBCREQ_GET_STR(base, military);
	DBCREQ_GET_STR(base, hero);
	DBCREQ_GET_STR(base, recycle);
	DBCREQ_GET_STR(base, consume);
	DBCREQ_GET_STR(base, extra_data);
	return 0;
}

int CDataBaseExtra::RemoveBase(unsigned baseid)
{
	DBCREQ_DECLARE(DBC::DeleteRequest, baseid);
	DBCREQ_SET_KEY(baseid);
	DBCREQ_EXEC;
	return 0;
}

int CDataBaseExtra::SetExtraData(unsigned baseid, const string &extra_data)
{
	DBCREQ_DECLARE(DBC::UpdateRequest, baseid);
	DBCREQ_SET_KEY(baseid);
	DBCREQ_SET_STR_V(extra_data);
	DBCREQ_EXEC;
	return 0;
}

int CDataBaseExtra::GetExtraData(unsigned baseid, string &extra_data)
{
	DBCREQ_DECLARE(DBC::GetRequest, baseid);
	DBCREQ_SET_KEY(baseid);
	DBCREQ_GET_STR_V(extra_data);
	return 0;
}

int CDataBaseExtra::SetUpdates(unsigned baseid, const string &updates)
{
	DBCREQ_DECLARE(DBC::UpdateRequest, baseid);
	DBCREQ_SET_KEY(baseid);
	DBCREQ_SET_STR_V(updates);
	DBCREQ_EXEC;
	return 0;
}

int CDataBaseExtra::GetUpdates(unsigned baseid, string &updates)
{
	DBCREQ_DECLARE(DBC::GetRequest, baseid);
	DBCREQ_SET_KEY(baseid);
	DBCREQ_GET_STR_V(updates);
	return 0;
}

int CDataBaseExtra::SetMilitary(unsigned baseid, const string &military)
{
	DBCREQ_DECLARE(DBC::UpdateRequest, baseid);
	DBCREQ_SET_KEY(baseid);
	DBCREQ_SET_STR_V(military);
	DBCREQ_EXEC;
	return 0;
}

int CDataBaseExtra::GetMilitary(unsigned baseid, string &military)
{
	DBCREQ_DECLARE(DBC::GetRequest, baseid);
	DBCREQ_SET_KEY(baseid);
	DBCREQ_GET_STR_V(military);
	return 0;
}

int CDataBaseExtra::SetHero(unsigned baseid, const string &hero)
{
	DBCREQ_DECLARE(DBC::UpdateRequest, baseid);
	DBCREQ_SET_KEY(baseid);
	DBCREQ_SET_STR_V(hero);
	DBCREQ_EXEC;
	return 0;
}

int CDataBaseExtra::SetConsume(unsigned baseid, const string &consume)
{
	DBCREQ_DECLARE(DBC::UpdateRequest, baseid);
	DBCREQ_SET_KEY(baseid);
	DBCREQ_SET_STR_V(consume);
	DBCREQ_EXEC;
	return 0;
}

int CDataBaseExtra::GetConsume(unsigned baseid, string &consume)
{
	DBCREQ_DECLARE(DBC::GetRequest, baseid);
	DBCREQ_SET_KEY(baseid);
	DBCREQ_GET_STR_V(consume);
	return 0;
}

