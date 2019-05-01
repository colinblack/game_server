#ifndef DATA_MISSION_H_
#define DATA_MISSION_H_
#include "Kernel.h"

struct DataMission
{
    uint32_t id;
    uint32_t uid;
    uint8_t status;
    uint32_t current;

    DataMission():
    	id(0),
		uid(0),
		status(0),
		current(0)
	{
	}

	void SetMessage(ProtoMission::MissionCPP *msg)
	{
		msg->set_id(id);
		msg->set_status(status);
		msg->add_current(current);
	}
};

class CDataMission :public DBCBase<DataMission, DB_MISSION>
{
public:
	virtual int Get(DataMission &data);
	virtual int Get(vector<DataMission> &data);
	virtual int Add(DataMission &data);
	virtual int Set(DataMission &data);
	virtual int Del(DataMission &data);
};

#endif //DATA_MISSION_H_
