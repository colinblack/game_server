#ifndef DATA_COMPONENT_H_
#define DATA_COMPONENT_H_
#include "Kernel.h"

struct DataComponent
{
	uint8_t position; //在装备区的位置
    uint8_t master;  //主属性类型
    uint8_t slave1; //副属性1类型
    uint8_t slave2; //副属性2类型
    uint8_t slave3; //副属性3类型

    uint32_t ud;
    uint32_t uid;
    uint32_t compid;
    uint32_t level;
    uint32_t exp;
    uint32_t heroid;

    DataComponent():
    	position(0),
		master(0),
		slave1(0),
		slave2(0),
		slave3(0),
		ud(0),
		uid(0),
		compid(0),
		level(0),
		exp(0),
		heroid(0)
	{

	}

	void SetMessage(ProtoComponent::ComponentCPP * msg)
	{
		msg->set_compud(ud);
		msg->set_compid(compid);
		msg->set_level(level);
		msg->set_exp(exp);
		msg->set_heroid(heroid);
		msg->set_position(position);
		msg->set_master(master);
		msg->clear_slave();  //批量数组，添加前要先清除

		{
			vector<uint8_t> vctsubs;
			AddtoVct(slave1)
			AddtoVct(slave2)
			AddtoVct(slave3)

			for(size_t i = 0; i < vctsubs.size(); ++i)
			{
				msg->add_slave(vctsubs[i]);
			}
		}

	}

	bool operator < (const DataComponent & oth) const
	{
		return exp < oth.exp;
	}
};

class CDataComponent :public DBCBase<DataComponent, DB_COMPONET>
{
public:
	virtual int Get(DataComponent &data);
	virtual int Get(vector<DataComponent> &data);
	virtual int Add(DataComponent &data);
	virtual int Set(DataComponent &data);
	virtual int Del(DataComponent &data);
};

#endif //DATA_COMPONENT_H_
