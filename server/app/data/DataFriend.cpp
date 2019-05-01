#include "DataFriend.h"

int CDataFriend::Get(DataFriend &data)
{
	DBCREQ_DECLARE(DBC::GetRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_CONDITION(EQ, friend_uid, data.friend_uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(friend_uid);
	DBCREQ_NEED(send_gift_ts);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;
	DBCREQ_IFFETCHROW;

	DBCREQ_GET_BEGIN();
	DBCREQ_GET_INT(data, uid);
	DBCREQ_GET_INT(data, friend_uid);
	DBCREQ_GET_INT(data, send_gift_ts);

	return 0;
}

int CDataFriend::Get(vector<DataFriend> &data)
{
	if (0 == data.size())
	{
		return R_ERR_PARAM;
	}

	DBCREQ_DECLARE(DBC::GetRequest, data[0].uid);
	DBCREQ_SET_KEY(data[0].uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(friend_uid);
	DBCREQ_NEED(send_gift_ts);

	data.clear();
	DBCREQ_EXEC;

	DBCREQ_ARRAY_GET_BEGIN(data);
	DBCREQ_ARRAY_GET_INT(data, uid);
	DBCREQ_ARRAY_GET_INT(data, friend_uid);
	DBCREQ_ARRAY_GET_INT(data, send_gift_ts);

	DBCREQ_ARRAY_GET_END();

	return 0;
}

int CDataFriend::Add(DataFriend &data)
{
	DBCREQ_DECLARE(DBC::ReplaceRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_SET_INT(data, friend_uid);
	DBCREQ_SET_INT(data, send_gift_ts);

	DBCREQ_EXEC;

	return 0;
}

int CDataFriend::Set(DataFriend &data)
{
	DBCREQ_DECLARE(DBC::UpdateRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_CONDITION(EQ, friend_uid, data.friend_uid);

	DBCREQ_SET_INT(data, send_gift_ts);
	DBCREQ_EXEC;

	return 0;
}

int CDataFriend::Del(DataFriend &data)
{
	DBCREQ_DECLARE(DBC::DeleteRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_CONDITION(EQ, friend_uid, data.friend_uid);

	DBCREQ_EXEC;

	return 0;
}
