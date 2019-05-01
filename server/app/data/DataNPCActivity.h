#ifndef DATA_NPC_ACTIVITY_H_
#define DATA_NPC_ACTIVITY_H_
#include "Kernel.h"

struct DataNPCActivity
{
	uint32_t uid;
	uint32_t version;    //活动版本号
	uint32_t affair_id;   //活动事件id
	uint32_t active_value;  //活力值
	uint32_t status;   //活力领取状态
	uint32_t materialnum1;  //材料1数量
	uint32_t materialnum2;   //材料2数量
	uint32_t materialnum3;   //材料3数量

    DataNPCActivity():
    	uid(0),
    	version(0),
    	affair_id(0),
    	active_value(0),
    	status(0),
    	materialnum1(0),
    	materialnum2(0),
    	materialnum3(0)
	{
	}

	void SetMessage(ProtoNPCActivity::NPCActivityCPP *msg)
	{
		msg->set_id(affair_id);
		msg->set_active_value(active_value);
		msg->set_status(status);

		msg->add_material(materialnum1);
		msg->add_material(materialnum2);
		msg->add_material(materialnum3);
	}
};

class CDataNPCActivity :public DBCBase<DataNPCActivity, DB_NPCACTIVITY>
{
public:
	virtual int Get(DataNPCActivity &data);
	virtual int Add(DataNPCActivity &data);
	virtual int Set(DataNPCActivity &data);
	virtual int Del(DataNPCActivity &data);
};

#endif //DATA_NPC_ACTIVITY_H_
