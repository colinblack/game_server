/*
 * DataNPCPass.cpp
 *
 *  Created on: 2016-9-9
 *      Author: dawx62fac
 */

#include "DataNPCPass.h"

DataNPCPass::DataNPCPass()
	: uid(0)
	, id(0)
	, pass_cnt(0)
{
}

DataNPCPass::DataNPCPass(unsigned uid_, unsigned id_)
	: uid(uid_)
	, id(id_)
	, pass_cnt(0)
{

}

void DataNPCPass::FullMessage(ProtoPass::NPCPassRecord* obj) const
{
	obj->set_id(id);
	obj->set_cnt(pass_cnt);
}

/////////////////////////////////////////////////////////////
int DBCDataNPCPassHandler::Get(DataNPCPass &data)
{
	warn_log("unrealized_interface");
	return -1;
}

int DBCDataNPCPassHandler::Get(vector<DataNPCPass> &data)
{
	if (data.empty())
	{
		warn_log("parmas_error");
		return R_ERROR;
	}

	unsigned uid = data.begin()->uid;
	data.clear();

	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(id);
	DBCREQ_NEED(pass_cnt);

	DBCREQ_EXEC;

	DBCREQ_ARRAY_GET_BEGIN(data);
	DBCREQ_ARRAY_GET_INT(data, uid);
	DBCREQ_ARRAY_GET_INT(data, id);
	DBCREQ_ARRAY_GET_INT(data, pass_cnt);
	DBCREQ_ARRAY_GET_END();

	return 0;
}

int DBCDataNPCPassHandler::Add(DataNPCPass &data)
{
	DBCREQ_DECLARE(DBC::InsertRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_INT(data, id);
	DBCREQ_SET_INT(data, pass_cnt);

	DBCREQ_EXEC;

	return 0;
}

int DBCDataNPCPassHandler::Set(DataNPCPass &data)
{
	DBCREQ_DECLARE(DBC::UpdateRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_CONDITION(EQ, id, data.id);

	DBCREQ_SET_INT(data, id);
	DBCREQ_SET_INT(data, pass_cnt);

	DBCREQ_EXEC;

	return 0;
}

int DBCDataNPCPassHandler::Del(DataNPCPass &data)
{
	warn_log("unrealized_interface");
	return -1;
}
