#ifndef DATA_OPERA_BATTLE_H_
#define DATA_OPERA_BATTLE_H_
#include "Kernel.h"

struct DataOperaBattle
{
	uint8_t difficulty;
	uint8_t star;
    uint32_t uid;
    uint32_t gateid;

    DataOperaBattle():
    	difficulty(0),
    	star(0),
		uid(0),
		gateid(0)
	{

	}

	void SetMessage(ProtoOperaBattle::OperaBattleCPP * msg)
	{
		msg->set_gateid(gateid);
		msg->set_difficulty(difficulty);
		msg->set_star(star);
	}
};

class CDataOperaBattle :public DBCBase<DataOperaBattle, DB_OPERA_BATTLE>
{
public:
	virtual int Get(DataOperaBattle &data);
	virtual int Get(vector<DataOperaBattle> &data);
	virtual int Add(DataOperaBattle &data);
	virtual int Set(DataOperaBattle &data);
	virtual int Del(DataOperaBattle &data);
};

#endif //DATA_OPERA_BATTLE_H_
