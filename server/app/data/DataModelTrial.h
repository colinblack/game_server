#ifndef DATA_MODEL_TRIAL_H_
#define DATA_MODEL_TRIAL_H_
#include "Kernel.h"

struct DataModelTrial
{
	uint8_t fight_times;
	uint8_t buy_times;

    uint32_t uid;
    uint32_t curpos;
    uint32_t resetts;

    DataModelTrial():
    	fight_times(0),
    	buy_times(0),
		uid(0),
		curpos(0),
		resetts(0)
	{

	}

	void SetMessage(ProtoModelTrial::ModelTrialCPP * msg)
	{
		msg->set_curpos(curpos);
		msg->set_fight_times(fight_times);
		msg->set_buy_times(buy_times);
		msg->set_resetts(resetts);
	}
};

class CDataModelTrial :public DBCBase<DataModelTrial, DB_MODEL_TRIAL>
{
public:
	virtual int Get(DataModelTrial &data);
	virtual int Add(DataModelTrial &data);
	virtual int Set(DataModelTrial &data);
	virtual int Del(DataModelTrial &data);
};

#endif //DATA_MODEL_TRIAL_H_
