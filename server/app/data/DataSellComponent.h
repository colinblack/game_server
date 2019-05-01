#ifndef DATA_SELL_COMPONENT_H_
#define DATA_SELL_COMPONENT_H_
#include "Kernel.h"

struct DataSellComponent
{
    uint32_t uid;
    uint32_t opents;
    uint32_t num1;
    uint32_t num2;

    DataSellComponent():
		uid(0),
		opents(0),
		num1(0),
		num2(0)
	{

	}

	void SetMessage(ProtoActivity::SellComponentCPP * msg)
	{
		msg->set_num1(num1);
		msg->set_num2(num2);
	}
};

class CDataSellComponent :public DBCBase<DataSellComponent, DB_SELL_COMPONENT>
{
public:
	virtual int Get(DataSellComponent &data);
	virtual int Add(DataSellComponent &data);
	virtual int Set(DataSellComponent &data);
	virtual int Del(DataSellComponent &data);
};

#endif //DATA_SELL_COMPONENT_H_
