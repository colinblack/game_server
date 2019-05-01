#ifndef DATA_PRODUCE_COMPONENT_H_
#define DATA_PRODUCE_COMPONENT_H_
#include "Kernel.h"

struct DataProduceComponent
{
	uint8_t current_level;   //当前产出等级
	uint8_t ispaycash;   //是否花钻
	uint8_t times; //花钻次数

    uint32_t uid;
    uint32_t paycash_ts;

    DataProduceComponent():
    	current_level(0),
    	ispaycash(0),
    	times(0),
    	uid(0),
    	paycash_ts(0)
	{
	}

	void SetMessage(ProtoComponent::ProduceComponentCPP * msg)
	{
		msg->set_current_level(current_level);
		msg->set_ispaycash(ispaycash);
		msg->set_times(times);
		msg->set_paycash_ts(paycash_ts);
	}
};

class CDataProduceComponent :public DBCBase<DataProduceComponent, DB_COMPONET_PRODUCE>
{
public:
	virtual int Get(DataProduceComponent &data);
	virtual int Add(DataProduceComponent &data);
	virtual int Set(DataProduceComponent &data);
	virtual int Del(DataProduceComponent &data);
};

#endif //DATA_PRODUCE_COMPONENT_H_
