#ifndef DATA_FRIEND_GIFT_H_
#define DATA_FRIEND_GIFT_H_
#include "Kernel.h"

struct DataFriendGift
{
	uint8_t receive_gift_times;
	uint8_t send_gift_times;
	uint8_t grades;

    uint32_t uid;
    uint32_t prestige;
    uint32_t receive_gift_ts;
    uint32_t send_gift_ts;

    char log_data[FRIEND_GIFT_LOG_LEN];

    DataFriendGift():
    	receive_gift_times(0),
    	send_gift_times(0),
    	grades(0),
		uid(0),
		prestige(0),
		receive_gift_ts(0),
		send_gift_ts(0)
	{
    	memset(log_data, 0, sizeof(log_data));
	}

	void SetMessage(ProtoFriend::FriendGiftCPP * msg)
	{
		msg->set_receive_gift_times(receive_gift_times);
		msg->set_receive_gift_ts(receive_gift_ts);
		msg->set_send_gift_times(send_gift_times);
		msg->set_send_gift_ts(send_gift_ts);
		msg->set_prestige(prestige);
		msg->set_grades(grades);
		msg->set_log_data(log_data);
	}
};

class CDataFriendGift :public DBCBase<DataFriendGift, DB_FRIEND_GIFT>
{
public:
	virtual int Get(DataFriendGift &data);
	virtual int Add(DataFriendGift &data);
	virtual int Set(DataFriendGift &data);
	virtual int Del(DataFriendGift &data);
};

#endif //DATA_FRIEND_GIFT_H_
