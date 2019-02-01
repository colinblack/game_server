/*
 * DataFriend.cpp
 *
 *  Created on: 2012-3-2
 *      Author: dada
 */

#include "DataFriend.h"

int CDataFriend::AddFriend(const DataFriend &dataFriend)
{
	DBCREQ_DECLARE(DBC::InsertRequest, dataFriend.uid);
	DBCREQ_SET_KEY(dataFriend.uid);
	DBCREQ_SET_INT(dataFriend, platform);
	DBCREQ_SET_INT(dataFriend, last_update_time);
	DBCREQ_SET_STR(dataFriend, friends);
	DBCREQ_SET_STR(dataFriend, friends_mapping);
	DBCREQ_EXEC;
	return 0;
}

int CDataFriend::SetFriend(const DataFriend &dataFriend)
{
	DBCREQ_DECLARE(DBC::UpdateRequest, dataFriend.uid);
	DBCREQ_SET_KEY(dataFriend.uid);
	DBCREQ_SET_CONDITION(EQ, platform, dataFriend.platform);
	DBCREQ_SET_INT(dataFriend, last_update_time);
	DBCREQ_SET_STR(dataFriend, friends);
	DBCREQ_SET_STR(dataFriend, friends_mapping);
	DBCREQ_EXEC;
	return 0;
}

int CDataFriend::GetFriend(unsigned uid, int platform, DataFriend &dataFriend)
{
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);
	DBCREQ_SET_CONDITION(EQ, platform, platform);
	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(platform);
	DBCREQ_NEED(last_update_time);
	DBCREQ_NEED(friends);
	DBCREQ_NEED(friends_mapping);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;
	DBCREQ_IFFETCHROW;

	DBCREQ_GET_BEGIN();
	DBCREQ_GET_INT(dataFriend, uid);
	DBCREQ_GET_INT(dataFriend, platform);
	DBCREQ_GET_INT(dataFriend, last_update_time);
	DBCREQ_GET_STR(dataFriend, friends);
	DBCREQ_GET_STR(dataFriend, friends_mapping);

	return 0;
}

int CDataFriend::RemoveFriend(unsigned uid)
{
	DBCREQ_DECLARE(DBC::DeleteRequest, uid);
	DBCREQ_SET_KEY(uid);
	DBCREQ_EXEC;
	return 0;
}

int CDataFriend::GetFriends(unsigned uid, int platform, string &friends)
{
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);
	DBCREQ_SET_CONDITION(EQ, platform, platform);
	DBCREQ_GET_STR_V(friends);
	return 0;
}
