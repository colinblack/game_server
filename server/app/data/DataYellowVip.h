#ifndef DATA_YELLOWVIP_H_
#define DATA_YELLOWVIP_H_
#include "Kernel.h"

struct DataYellowVip
{
    uint8_t newerstatus;  //新手礼包领取状态
    uint8_t dailystatus;  //每日领取状态
    uint8_t year_daily_status;  //年费黄钻礼包领取状态
    uint8_t qqzone_dailystatus;  //空间每日领取状态

    uint32_t uid;
    uint32_t levelstatus;   //等级奖励领取状态，按位表示是否领取
    uint32_t daily_reward_time;   //每日礼包领取时间，用于重置
    uint32_t year_reward_time;   //年费黄钻礼包领取时间,用于重置
    uint32_t qqzone_daily_time;  //空间每日礼包领取时间,用于重置
    uint32_t qqzone_levelstatus;   //空间等级奖励领取状态，按位表示是否领取

    DataYellowVip():
    	newerstatus(0),
    	dailystatus(0),
    	year_daily_status(0),
    	qqzone_dailystatus(0),
    	uid(0),
    	levelstatus(0),
    	daily_reward_time(0),
    	year_reward_time(0),
    	qqzone_daily_time(0),
    	qqzone_levelstatus(0)
	{
	}

	void SetMessage(ProtoYellowVip::YellowVipCPP *msg)
	{
		msg->set_newerstatus(newerstatus);
		msg->set_dailystatus(dailystatus);
		msg->set_daily_reward_time(daily_reward_time);
		msg->set_yearstatus(year_daily_status);
		msg->set_year_reward_time(year_reward_time);
		msg->set_levelstatus(levelstatus);
		msg->set_qqzone_dailystatus(qqzone_dailystatus);
		msg->set_qqzone_daily_time(qqzone_daily_time);
		msg->set_qqzone_levelstatus(qqzone_levelstatus);
	}
};

class CDataYellowVip :public DBCBase<DataYellowVip, DB_YELLOW_VIP>
{
public:
	virtual int Get(DataYellowVip &data);
	virtual int Add(DataYellowVip &data);
	virtual int Set(DataYellowVip &data);
	virtual int Del(DataYellowVip &data);
};

#endif //DATA_YELLOWVIP_H_
