#ifndef DATA_FRIEND_H_
#define DATA_FRIEND_H_
#include "Kernel.h"

struct DataFriend
{
    uint32_t uid;
    uint32_t friend_uid;
    uint32_t send_gift_ts;

    DataFriend():
		uid(0),
		friend_uid(0),
		send_gift_ts(0)
	{

	}

	void SetMessage(ProtoFriend::FriendCPP * msg)
	{
		msg->set_friend_uid(friend_uid);
		msg->set_send_gift_ts(send_gift_ts);
	}
};

class CDataFriend :public DBCBase<DataFriend, DB_FRIEND>
{
public:
	virtual int Get(DataFriend &data);
	virtual int Get(vector<DataFriend> &data);
	virtual int Add(DataFriend &data);
	virtual int Set(DataFriend &data);
	virtual int Del(DataFriend &data);
};

#endif //DATA_FRIEND_H_
