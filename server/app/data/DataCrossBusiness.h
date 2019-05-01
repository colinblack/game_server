#ifndef DATA_CROSS_BUSINESS_H_
#define DATA_CROSS_BUSINESS_H_
#include "Kernel.h"

struct DataCrossBusiness
{
	uint8_t status;

    uint32_t uid;
    uint32_t slot1;
    uint32_t slot2;
    uint32_t slot3;
    uint32_t slot4;
    uint32_t slot5;
    uint32_t slot6;
    uint32_t refreshts;

    DataCrossBusiness():
    	status(0),
		uid(0),
    	slot1(0),
    	slot2(0),
    	slot3(0),
    	slot4(0),
    	slot5(0),
    	slot6(0),
		refreshts(0)
	{

	}

	void SetMessage(ProtoCrossBusiness::CrossBusinessCPP * msg)
	{
		msg->set_refreshts(refreshts);
		msg->set_slot1(slot1);
		msg->set_slot2(slot2);
		msg->set_slot3(slot3);
		msg->set_slot4(slot4);
		msg->set_slot5(slot5);
		msg->set_slot6(slot6);
		msg->set_status(status);
	}
};

class CDataCrossBusiness :public DBCBase<DataCrossBusiness, DB_CROSS_BUSINESS>
{
public:
	virtual int Get(DataCrossBusiness &data);
	virtual int Add(DataCrossBusiness &data);
	virtual int Set(DataCrossBusiness &data);
	virtual int Del(DataCrossBusiness &data);
};

#endif //DATA_CROSS_BUSINESS_H_
