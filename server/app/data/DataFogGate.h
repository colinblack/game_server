#ifndef DATA_FOGGATE_H_
#define DATA_FOGGATE_H_
#include "Kernel.h"

struct DataFogGate
{
    uint8_t leftnpc;  //剩余npc

    uint32_t uid;
    uint32_t gateid;

    DataFogGate():
    	leftnpc(0),
		uid(0),
		gateid(0)
	{

	}

	void SetMessage(ProtoFogGate::FogGateCPP * msg)
	{
		msg->set_gateid(gateid);
		msg->set_leftnpc(leftnpc);
	}
};

class CDataFogGate :public DBCBase<DataFogGate, DB_FOGGATE>
{
public:
	virtual int Get(DataFogGate &data);
	virtual int Get(vector<DataFogGate> &data);
	virtual int Add(DataFogGate &data);
	virtual int Set(DataFogGate &data);
	virtual int Del(DataFogGate &data);
};

#endif //DATA_FOGGATE_H_
