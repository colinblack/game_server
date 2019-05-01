#ifndef DATA_HERO_H_
#define DATA_HERO_H_
#include "Kernel.h"

struct DataHero
{
    uint32_t heroid;
    uint32_t uid;
    uint8_t level;
    uint64_t exp;
    uint8_t status;
    uint32_t attacknum;
    uint32_t ovonum;
    uint32_t killnum;

    DataHero():
    	heroid(0),
		uid(0),
		level(0),
		exp(0),
		status(0),
		attacknum(0),
		ovonum(0),
		killnum(0)
	{

	}

    bool AddExp(int exp, int user_lvl);

	void SetMessage(ProtoHero::HeroBaseInfoCPP *msg)
	{
		msg->set_heroid(heroid);
		msg->set_status(status);
		msg->set_level(level);
		msg->set_exp(exp);
		msg->set_attacknum(attacknum);
		msg->set_ovonum(ovonum);
		msg->set_killnum(killnum);
	}
};

class CDataHero :public DBCBase<DataHero, DB_HERO>
{
public:
	virtual int Get(DataHero &data);
	virtual int Get(vector<DataHero> &data);
	virtual int Add(DataHero &data);
	virtual int Set(DataHero &data);
	virtual int Del(DataHero &data);
};

#endif //DATA_HERO_H_
