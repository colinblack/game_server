/*
 * DataUser.cpp
 *
 *  Created on: 2011-5-26
 *      Author: dada
 */

#include "DataUser.h"

int CDataUser::AddUser(DataUser &user)
{
	DBCREQ_DECLARE(DBC::InsertRequest, user.uid);
	DBCREQ_SET_KEY(user.uid);
	DBCREQ_SET_INT(user, register_platform);
	DBCREQ_SET_INT(user, register_time);
	DBCREQ_SET_INT(user, invite_uid);
	DBCREQ_SET_INT(user, last_login_platform);
	DBCREQ_SET_INT(user, last_login_time);
	DBCREQ_SET_INT(user, last_active_time);
	DBCREQ_SET_INT(user, login_times);
	DBCREQ_SET_INT(user, invite_count);
	DBCREQ_SET_INT(user, status);
	DBCREQ_SET_INT(user, main_base_id);
	DBCREQ_SET_INT(user, level);
	DBCREQ_SET_INT(user, point);
	DBCREQ_SET_INT(user, value);
	DBCREQ_SET_INT(user, tutorial_stage);
	DBCREQ_SET_INT(user, r1);
	DBCREQ_SET_INT(user, r1_max);
	DBCREQ_SET_INT(user, r2);
	DBCREQ_SET_INT(user, r2_max);
	DBCREQ_SET_INT(user, r3);
	DBCREQ_SET_INT(user, r3_max);
	DBCREQ_SET_INT(user, r4);
	DBCREQ_SET_INT(user, r4_max);
	DBCREQ_SET_INT(user, alliance_id);
	DBCREQ_SET_INT(user, unread_message);
	DBCREQ_SET_INT(user, world);
	DBCREQ_EXEC;
	return 0;
}

int CDataUser::SetUser(const DataUser &user)
{
	DBCREQ_DECLARE(DBC::UpdateRequest, user.uid);
	DBCREQ_SET_KEY(user.uid);
	DBCREQ_SET_INT(user, register_platform);
	DBCREQ_SET_INT(user, register_time);
	DBCREQ_SET_INT(user, invite_uid);
	DBCREQ_SET_INT(user, last_login_platform);
	DBCREQ_SET_INT(user, last_login_time);
	DBCREQ_SET_INT(user, last_active_time);
	DBCREQ_SET_INT(user, login_times);
	DBCREQ_SET_INT(user, invite_count);
	DBCREQ_SET_INT(user, status);
	DBCREQ_SET_INT(user, main_base_id);
	DBCREQ_SET_INT(user, level);
	DBCREQ_SET_INT(user, point);
	DBCREQ_SET_INT(user, value);
	DBCREQ_SET_INT(user, tutorial_stage);
	DBCREQ_SET_INT(user, r1);
	DBCREQ_SET_INT(user, r1_max);
	DBCREQ_SET_INT(user, r2);
	DBCREQ_SET_INT(user, r2_max);
	DBCREQ_SET_INT(user, r3);
	DBCREQ_SET_INT(user, r3_max);
	DBCREQ_SET_INT(user, r4);
	DBCREQ_SET_INT(user, r4_max);
	DBCREQ_SET_INT(user, alliance_id);
	DBCREQ_SET_INT(user, unread_message);
	DBCREQ_SET_INT(user, world);
	DBCREQ_EXEC;
	return 0;
}

int CDataUser::GetUser(unsigned uid, DataUser &user)
{
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(register_platform);
	DBCREQ_NEED(register_time);
	DBCREQ_NEED(invite_uid);
	DBCREQ_NEED(last_login_platform);
	DBCREQ_NEED(last_login_time);
	DBCREQ_NEED(last_active_time);
	DBCREQ_NEED(login_times);
	DBCREQ_NEED(invite_count);
	DBCREQ_NEED(status);
	DBCREQ_NEED(main_base_id);
	DBCREQ_NEED(level);
	DBCREQ_NEED(point);
	DBCREQ_NEED(value);
	DBCREQ_NEED(tutorial_stage);
	DBCREQ_NEED(r1);
	DBCREQ_NEED(r1_max);
	DBCREQ_NEED(r2);
	DBCREQ_NEED(r2_max);
	DBCREQ_NEED(r3);
	DBCREQ_NEED(r3_max);
	DBCREQ_NEED(r4);
	DBCREQ_NEED(r4_max);
	DBCREQ_NEED(alliance_id);
	DBCREQ_NEED(unread_message);
	DBCREQ_NEED(world);


	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;
	DBCREQ_IFFETCHROW;

	DBCREQ_GET_BEGIN();
	DBCREQ_GET_INT(user, uid);
	DBCREQ_GET_INT(user, register_platform);
	DBCREQ_GET_INT(user, register_time);
	DBCREQ_GET_INT(user, invite_uid);
	DBCREQ_GET_INT(user, last_login_platform);
	DBCREQ_GET_INT(user, last_login_time);
	DBCREQ_GET_INT(user, last_active_time);
	DBCREQ_GET_INT(user, login_times);
	DBCREQ_GET_INT(user, invite_count);
	DBCREQ_GET_INT(user, status);
	DBCREQ_GET_INT(user, main_base_id);
	DBCREQ_GET_INT(user, level);
	DBCREQ_GET_INT(user, point);
	DBCREQ_GET_INT(user, value);
	DBCREQ_GET_INT(user, tutorial_stage);
	DBCREQ_GET_INT(user, r1);
	DBCREQ_GET_INT(user, r1_max);
	DBCREQ_GET_INT(user, r2);
	DBCREQ_GET_INT(user, r2_max);
	DBCREQ_GET_INT(user, r3);
	DBCREQ_GET_INT(user, r3_max);
	DBCREQ_GET_INT(user, r4);
	DBCREQ_GET_INT(user, r4_max);
	DBCREQ_GET_INT(user, alliance_id);
	DBCREQ_GET_INT(user, unread_message);
	DBCREQ_GET_INT(user, world);
	return 0;
}

int CDataUser::RemoveUser(unsigned uid)
{
	DBCREQ_DECLARE(DBC::DeleteRequest, uid);
	DBCREQ_SET_KEY(uid);
	DBCREQ_EXEC;
	return 0;
}

int CDataUser::SetMainBaseId(unsigned uid, unsigned main_base_id)
{
	DBCREQ_DECLARE(DBC::UpdateRequest, uid);
	DBCREQ_SET_KEY(uid);
	DBCREQ_SET_INT_V(main_base_id);
	DBCREQ_EXEC;
	return 0;
}

int CDataUser::GetMainBaseId(unsigned uid, unsigned &main_base_id)
{
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);
	DBCREQ_GET_INT_V(main_base_id);
	return 0;
}

int CDataUser::SetAllianceId(unsigned uid, unsigned alliance_id)
{
	DBCREQ_DECLARE(DBC::UpdateRequest, uid);
	DBCREQ_SET_KEY(uid);
	DBCREQ_SET_INT_V(alliance_id);
	DBCREQ_EXEC;
	return 0;
}

int CDataUser::GetAllianceId(unsigned uid, unsigned &alliance_id)
{
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);
	DBCREQ_GET_INT_V(alliance_id);
	return 0;
}

int CDataUser::SetWorld(unsigned uid, int world)
{
	DBCREQ_DECLARE(DBC::UpdateRequest, uid);
	DBCREQ_SET_KEY(uid);
	DBCREQ_SET_INT_V(world);
	DBCREQ_EXEC;
	return 0;
}

int CDataUser::GetWorld(unsigned uid, int &world)
{
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);
	DBCREQ_GET_INT_V(world);
	return 0;
}

int CDataUser::GetActiveTime(unsigned uid, unsigned last_active_time)
{
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);
	DBCREQ_GET_INT_V(last_active_time);
	return 0;
}

int CDataUser::SetActiveTime(unsigned uid, unsigned last_active_time)
{
	DBCREQ_DECLARE(DBC::UpdateRequest, uid);
	DBCREQ_SET_KEY(uid);
	DBCREQ_SET_INT_V(last_active_time);
	DBCREQ_EXEC;
	return 0;
}

int CDataUser::SetStatus(unsigned uid, int status)
{
	DBCREQ_DECLARE(DBC::UpdateRequest, uid);
	DBCREQ_SET_KEY(uid);
	DBCREQ_SET_INT_V(status);
	DBCREQ_EXEC;
	return 0;
}

int CDataUser::AddInviteCount(unsigned uid, int invite_count)
{
	DBCREQ_DECLARE(DBC::UpdateRequest, uid);
	DBCREQ_SET_KEY(uid);
	DBCREQ_ADD_INT_V(invite_count);
	DBCREQ_EXEC;
	return 0;
}

int CDataUser::SetUnreadMessage(unsigned uid, int unread_message)
{
	DBCREQ_DECLARE(DBC::UpdateRequest, uid);
	DBCREQ_SET_KEY(uid);
	DBCREQ_SET_INT_V(unread_message);
	DBCREQ_EXEC;
	return 0;
}

