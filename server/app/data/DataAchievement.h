#ifndef DATA_ACHIEVEMENT_H_
#define DATA_ACHIEVEMENT_H_
#include "Kernel.h"

struct DataAchievement
{
    uint32_t id;
    uint32_t uid;
    uint8_t status;
    uint32_t current;

    DataAchievement():
    	id(0),
		uid(0),
		status(0),
		current(0)
	{
	}

	void SetMessage(ProtoAchievement::AchievementCPP *msg)
	{
		msg->set_id(id);
		msg->set_status(status);
		msg->add_current(current);
	}
};

class CDataAchievement :public DBCBase<DataAchievement, DB_ACHIEVEMENT>
{
public:
	virtual int Get(DataAchievement &data);
	virtual int Get(vector<DataAchievement> &data);
	virtual int Add(DataAchievement &data);
	virtual int Set(DataAchievement &data);
	virtual int Del(DataAchievement &data);
};

#endif //DATA_ACHIEVEMENT_H_
