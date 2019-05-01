#ifndef DATA_MARKET_H_
#define DATA_MARKET_H_
#include "Kernel.h"

struct DataMarket
{
	uint8_t type1 ;      /*第一格资源类型*/
	uint8_t character1 ;   /*第一格资源品质*/
	uint8_t type2 ;  /*第二格资源类型*/
	uint8_t character2 ;  /*第二格资源品质*/
	uint8_t type3 ;    /*第三格资源类型*/
	uint8_t character3 ; /*第三格资源品质*/
    uint32_t refreshtime ;   /*下次集市刷新时间*/
	uint32_t uid ;

    DataMarket():
    	type1(0),
    	character1(0),
    	type2(0),
    	character2(0),
    	type3(0),
    	character3(0),
    	refreshtime(0),
    	uid(0)
	{
	}

	void SetMessage(ProtoMarket::MarketCPP *msg)
	{
		msg->set_refreshtime(refreshtime);
		msg->set_type1(type1);
		msg->set_character1(character1);
		msg->set_type2(type2);
		msg->set_character2(character2);
		msg->set_type3(type3);
		msg->set_character3(character3);
	}
};

class CDataMarket :public DBCBase<DataMarket, DB_MARKET>
{
public:
	virtual int Get(DataMarket &data);
	virtual int Add(DataMarket &data);
	virtual int Set(DataMarket &data);
	virtual int Del(DataMarket &data);
};

#endif //DATA_MARKET_H_
