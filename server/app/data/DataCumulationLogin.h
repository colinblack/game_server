#ifndef DATA_CUMULATION_LOGIN_H_
#define DATA_CUMULATION_LOGIN_H_
#include "Kernel.h"

struct DataCumulationLogin
{
    uint32_t uid;
    uint32_t status;   //奖励领取状态，按位表示是否领取

    DataCumulationLogin():
    	uid(0),
    	status(0)
	{
	}

	void SetMessage(ProtoCumulation::CumulationCPP *msg)
	{
		msg->set_status(status);
	}
};

class CDataCumulationLogin :public DBCBase<DataCumulationLogin, DB_CUMULATION_LOGIN>
{
public:
	virtual int Get(DataCumulationLogin &data);
	virtual int Add(DataCumulationLogin &data);
	virtual int Set(DataCumulationLogin &data);
	virtual int Del(DataCumulationLogin &data);
};

#endif //DATA_YELLOWVIP_H_
