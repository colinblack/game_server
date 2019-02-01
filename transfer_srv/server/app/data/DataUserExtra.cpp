/*
 * DataUserExtra.cpp
 *
 *  Created on: 2012-3-1
 *      Author: dada
 */

#include "DataUserExtra.h"

int CDataUserExtra::AddUser(DataUserExtra &user)
{
	DBCREQ_DECLARE(DBC::InsertRequest, user.uid);
	DBCREQ_SET_KEY(user.uid);
	DBCREQ_SET_INT(user, gate_left_times);
	DBCREQ_SET_INT(user, gate_extra_times);
	DBCREQ_SET_STR(user, stat);
	DBCREQ_SET_STR(user, wf_status);
	DBCREQ_SET_STR(user, lock);
	DBCREQ_SET_STR(user, technology);
	DBCREQ_SET_STR(user, quest);
	DBCREQ_SET_STR(user, bookmark);
	DBCREQ_SET_STR(user, extra_data);
	DBCREQ_SET_STR(user, eggdata);
	DBCREQ_EXEC;
	return 0;
}

int CDataUserExtra::SetUser(const DataUserExtra &user)
{
	DBCREQ_DECLARE(DBC::UpdateRequest, user.uid);
	DBCREQ_SET_KEY(user.uid);
	DBCREQ_SET_INT(user, gate_left_times);
	DBCREQ_SET_INT(user, gate_extra_times);
	DBCREQ_SET_STR(user, stat);
	DBCREQ_SET_STR(user, wf_status);
	DBCREQ_SET_STR(user, lock);
	DBCREQ_SET_STR(user, technology);
	DBCREQ_SET_STR(user, quest);
	DBCREQ_SET_STR(user, bookmark);
	DBCREQ_SET_STR(user, extra_data);
	DBCREQ_SET_STR(user, eggdata);
	DBCREQ_EXEC;
	return 0;
}

int CDataUserExtra::GetUser(unsigned uid, DataUserExtra &user)
{
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(gate_left_times);
	DBCREQ_NEED(gate_extra_times);
	DBCREQ_NEED(stat);
	DBCREQ_NEED(wf_status);
	DBCREQ_NEED(lock);
	DBCREQ_NEED(technology);
	DBCREQ_NEED(quest);
	DBCREQ_NEED(bookmark);
	DBCREQ_NEED(extra_data);
	DBCREQ_NEED(eggdata);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;
	DBCREQ_IFFETCHROW;

	DBCREQ_GET_BEGIN();
	DBCREQ_GET_INT(user, uid);
	DBCREQ_GET_INT(user, gate_left_times);
	DBCREQ_GET_INT(user, gate_extra_times);
	DBCREQ_GET_STR(user, stat);
	DBCREQ_GET_STR(user, wf_status);
	DBCREQ_GET_STR(user, lock);
	DBCREQ_GET_STR(user, technology);
	DBCREQ_GET_STR(user, quest);
	DBCREQ_GET_STR(user, bookmark);
	DBCREQ_GET_STR(user, extra_data);
	DBCREQ_GET_STR(user, eggdata);

	return 0;
}

int CDataUserExtra::RemoveUser(unsigned uid)
{
	DBCREQ_DECLARE(DBC::DeleteRequest, uid);
	DBCREQ_SET_KEY(uid);
	DBCREQ_EXEC;
	return 0;
}

int CDataUserExtra::GetExtraData(unsigned uid, string &extra_data)
{
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);
	DBCREQ_GET_STR_V(extra_data);
	return 0;
}

int CDataUserExtra::SetExtraData(unsigned uid, const string &extra_data)
{
	DBCREQ_DECLARE(DBC::UpdateRequest, uid);
	DBCREQ_SET_KEY(uid);
	DBCREQ_SET_STR_V(extra_data);
	DBCREQ_EXEC;
	return 0;
}

int CDataUserExtra::GetStat(unsigned uid, string &stat)
{
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);
	DBCREQ_GET_STR_V(stat);
	return 0;
}

int CDataUserExtra::SetStat(unsigned uid, const string &stat)
{
	DBCREQ_DECLARE(DBC::UpdateRequest, uid);
	DBCREQ_SET_KEY(uid);
	DBCREQ_SET_STR_V(stat);
	DBCREQ_EXEC;
	return 0;
}

int CDataUserExtra::SetGateTimes(const DataUserExtra &user)
{
	DBCREQ_DECLARE(DBC::UpdateRequest, user.uid);
	DBCREQ_SET_KEY(user.uid);
	DBCREQ_SET_INT(user, gate_left_times);
	DBCREQ_SET_INT(user, gate_extra_times);
	DBCREQ_EXEC;
	return 0;
}

int CDataUserExtra::GetGateTimes(unsigned uid, DataUserExtra &user)
{
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(gate_left_times);
	DBCREQ_NEED(gate_extra_times);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;
	DBCREQ_IFFETCHROW;

	DBCREQ_GET_BEGIN();
	DBCREQ_GET_INT(user, uid);
	DBCREQ_GET_INT(user, gate_left_times);
	DBCREQ_GET_INT(user, gate_extra_times);

	return 0;
}

int CDataUserExtra::GetWfStatus(unsigned uid, string &wf_status)
{
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);
	DBCREQ_GET_STR_V(wf_status);
	return 0;
}

int CDataUserExtra::SetWfStatus(unsigned uid, const string &wf_status)
{
	DBCREQ_DECLARE(DBC::UpdateRequest, uid);
	DBCREQ_SET_KEY(uid);
	DBCREQ_SET_STR_V(wf_status);
	DBCREQ_EXEC;
	return 0;
}

int CDataUserExtra::SetBookmark(unsigned uid, const string &bookmark)
{
	DBCREQ_DECLARE(DBC::UpdateRequest, uid);
	DBCREQ_SET_KEY(uid);
	DBCREQ_SET_STR_V(bookmark);
	DBCREQ_EXEC;
	return 0;
}
