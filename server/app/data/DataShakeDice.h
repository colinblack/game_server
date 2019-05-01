#ifndef DATA_SHAKE_DICE_H_
#define DATA_SHAKE_DICE_H_
#include "Kernel.h"

struct DataShakeDice
{
	uint8_t map1_status;
	uint8_t map2_status;
	uint8_t map3_status;
	uint8_t dice_times;
	uint8_t reset_times;
	uint8_t steps;
	uint8_t curmap;
	uint8_t extra_reward_status;
	uint8_t curpos;

    uint32_t uid;
    uint32_t version;
    uint32_t operate_ts;
    uint32_t map1_rewards;
    uint32_t map2_rewards;
    uint32_t map3_rewards;

    DataShakeDice():
    	map1_status(0),
    	map2_status(0),
    	map3_status(0),
    	dice_times(0),
    	reset_times(0),
    	steps(0),
    	curmap(0),
    	extra_reward_status(0),
    	curpos(0),
		uid(0),
		version(0),
		operate_ts(0),
		map1_rewards(0),
		map2_rewards(0),
		map3_rewards(0)
	{

	}

    void Clear()
    {
		version = 0;
    	curmap = 0;
    	map1_status = 0;
    	map2_status = 0;
    	map3_status = 0;
    	dice_times = 0;
    	reset_times = 0;
    	steps = 0;
		operate_ts = 0;
    	extra_reward_status = 0;
		curpos = 0;
		map1_rewards = 0;
		map2_rewards = 0;
		map3_rewards = 0;
    }

	void SetMessage(ProtoShakeDice::ShakeDiceCPP * msg)
	{
		msg->set_version(version);
		msg->set_curmap(curmap);
		msg->set_map1_status(map1_status);
		msg->set_map2_status(map2_status);
		msg->set_map3_status(map3_status);
		msg->set_dice_times(dice_times);
		msg->set_reset_times(reset_times);
		msg->set_steps(steps);
		msg->set_operate_ts(operate_ts);
		msg->set_extra_reward_status(extra_reward_status);
		msg->set_map1_rewards(map1_rewards);
		msg->set_map2_rewards(map2_rewards);
		msg->set_map3_rewards(map3_rewards);
		msg->set_curpos(curpos);
	}
};

class CDataShakeDice :public DBCBase<DataShakeDice, DB_SHAKE_DICE>
{
public:
	virtual int Get(DataShakeDice &data);
	virtual int Add(DataShakeDice &data);
	virtual int Set(DataShakeDice &data);
	virtual int Del(DataShakeDice &data);
};

#endif //DATA_SHAKE_DICE_H_
