#ifndef DATA_DAILY_MISSION_H_
#define DATA_DAILY_MISSION_H_
#include "Kernel.h"

struct DataDailyMission
{
	uint8_t status; //任务状态
	uint8_t star; //星级
	uint8_t id;

    uint32_t uid;
    uint32_t missid;  //任务id
    uint32_t current;  //当前完成进度
    uint32_t base;   //领取任务时的基值
    uint32_t gettime;   //领取任务的时间

    DataDailyMission():
    	status(0),
    	star(0),
		id(0),
		uid(0),
		missid(0),
		current(0),
		base(0),
		gettime(0)
	{

	}

	void SetMessage(ProtoDailyMission::DailyMissionCPP * msg)
	{
		msg->set_missid(missid);
		msg->set_star(star);
		msg->set_status(status);
		msg->set_current(current);
	}

	void Clear()
	{
    	status = 0;
    	star = 0;
		missid = 0;
		current = 0;
		base = 0;
	}
};

class CDataDailyMission :public DBCBase<DataDailyMission, DB_DAILY_MISSION>
{
public:
	virtual int Get(DataDailyMission &data);
	virtual int Get(vector<DataDailyMission> &data);
	virtual int Add(DataDailyMission &data);
	virtual int Set(DataDailyMission &data);
	virtual int Del(DataDailyMission &data);
};

#endif //DATA_DAILY_MISSION_H_
