#include "DataFriendGift.h"

int CDataFriendGift::Get(DataFriendGift &data)
{
	DBCREQ_DECLARE(DBC::GetRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(prestige);
	DBCREQ_NEED(grades);
	DBCREQ_NEED(receive_gift_times);
	DBCREQ_NEED(receive_gift_ts);
	DBCREQ_NEED(send_gift_times);
	DBCREQ_NEED(send_gift_ts);
	DBCREQ_NEED(log_data);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;
	DBCREQ_IFFETCHROW;

	DBCREQ_GET_BEGIN();
	DBCREQ_GET_INT(data, uid);
	DBCREQ_GET_INT(data, prestige);
	DBCREQ_GET_INT(data, grades);
	DBCREQ_GET_INT(data, receive_gift_times);
	DBCREQ_GET_INT(data, receive_gift_ts);
	DBCREQ_GET_INT(data, send_gift_times);
	DBCREQ_GET_INT(data, send_gift_ts);
	DBCREQ_GET_CHAR(data, log_data, FRIEND_GIFT_LOG_LEN);

	return 0;
}

int CDataFriendGift::Add(DataFriendGift &data)
{
	DBCREQ_DECLARE(DBC::ReplaceRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_SET_INT(data, prestige);
	DBCREQ_SET_INT(data, grades);
	DBCREQ_SET_INT(data, receive_gift_times);
	DBCREQ_SET_INT(data, receive_gift_ts);
	DBCREQ_SET_INT(data, send_gift_times);
	DBCREQ_SET_INT(data, send_gift_ts);
	DBCREQ_SET_CHAR(data, log_data, FRIEND_GIFT_LOG_LEN);

	DBCREQ_EXEC;

	return 0;
}

int CDataFriendGift::Set(DataFriendGift &data)
{
	DBCREQ_DECLARE(DBC::UpdateRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_SET_INT(data, prestige);
	DBCREQ_SET_INT(data, grades);
	DBCREQ_SET_INT(data, receive_gift_times);
	DBCREQ_SET_INT(data, receive_gift_ts);
	DBCREQ_SET_INT(data, send_gift_times);
	DBCREQ_SET_INT(data, send_gift_ts);
	DBCREQ_SET_CHAR(data, log_data, FRIEND_GIFT_LOG_LEN);

	DBCREQ_EXEC;

	return 0;
}

int CDataFriendGift::Del(DataFriendGift &data)
{
	DBCREQ_DECLARE(DBC::DeleteRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_EXEC;

	return 0;
}
