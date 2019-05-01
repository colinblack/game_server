/*
 * DataScience.cpp
 *
 *  Created on: 2016-9-14
 *      Author: dawx62fac
 */

#include "DataScience.h"
#include "DataInc.h"

DBCScience::DBCScience()
	: uid(0), id(0), status(0), value(0)
{
}

DBCScience::DBCScience(uint32_t uid_, uint16_t id_)
	: uid(uid_)
	, id(id_)
	, status(-1)
	, value(0)
{

}

bool DBCScience::RefreshStatus(const ScienceConfig::ScienceItem& cfg)
{
	if(status == 2)
	{
		unsigned now = Time::GetGlobalTime();
		if (value <= now)
		{
			status = 0;
			value = cfg.val();
			return true;
		}
	}

	return false;
}

//bool DBCScience::RefreshStatus()
//{
//	if(status == 2)
//	{
//		const ScienceConfig::ScienceItem& item = ScienceCfgWrap().Item(id);
//		return RefreshStatus(item);
//	}
//
//	return false;
//}

void DBCScience::FinishUnlock(const ScienceConfig::ScienceItem& item)
{
	status = 0;
	value = item.val();
}

void DBCScience::Capital(const ScienceConfig::ScienceItem& item)
{
	if (status == -1)
	{
		status = 1;
		value = 1;
	}
	else if (status == 1)
	{
		value += 1;
		if (value == item.capital_cnt())
		{
			status = 2;
			value = Time::GetGlobalTime() + item.cd();
		}
	}
	else
	{
		throw std::runtime_error("science_capital_status_error");
	}
}

bool DBCScience::Normal() const
{
	return status == 0;
}


bool DBCScience::IsCapitaling() const
{
	return status == 1;
}

bool DBCScience::IsUnlocking() const //解锁中
{
	return status == 2;
}

bool DBCScience::IsCanCapital() const
{
	return status == 1 || status == -1;
}

void DBCScience::FullMessage(ProtoScience::ScienceItemCPP* obj)  const
{
	obj->set_id(id);
	obj->set_status(status);
	obj->set_value(value);
}
/////////////////////////////////////////////////////////////////////////////////////////
int DBCScienceHandler::Get(DBCScience &data)
{
	warn_log("unrealized_interface");
	return -1;
}

int DBCScienceHandler::Get(vector<DBCScience> &data)
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
	DBCREQ_NEED(status);
	DBCREQ_NEED(value);

	DBCREQ_EXEC;

	DBCREQ_ARRAY_GET_BEGIN(data);
	DBCREQ_ARRAY_GET_INT(data, uid);
	DBCREQ_ARRAY_GET_INT(data, id);
	DBCREQ_ARRAY_GET_INT(data, status);
	DBCREQ_ARRAY_GET_INT(data, value);
	DBCREQ_ARRAY_GET_END();

	return 0;
}

int DBCScienceHandler::Add(DBCScience &data)
{
	DBCREQ_DECLARE(DBC::InsertRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_INT(data, id);
	DBCREQ_SET_INT(data, status);
	DBCREQ_SET_INT(data, value);

	DBCREQ_EXEC;
	return 0;
}
int DBCScienceHandler::Set(DBCScience &data)
{
	DBCREQ_DECLARE(DBC::UpdateRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_CONDITION(EQ, id, data.id);

	DBCREQ_SET_INT(data, id);
	DBCREQ_SET_INT(data, status);
	DBCREQ_SET_INT(data, value);

	DBCREQ_EXEC;

	return 0;
}
int DBCScienceHandler::Del(DBCScience &data)
{
	warn_log("unrealized_interface");
	return -1;
}

