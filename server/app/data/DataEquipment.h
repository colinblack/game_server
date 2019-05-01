#ifndef DATA_EQUIPMENT_H_
#define DATA_EQUIPMENT_H_
#include "Kernel.h"

struct DataEquipment
{
    uint32_t ud;
    uint32_t uid;
    uint32_t eqid;
    uint32_t num;
    uint32_t deltime;
    uint32_t heroid;
    uint8_t star;
    uint8_t issold;
    uint32_t born1;
    uint32_t born2;
    uint8_t subt1;  //洗练属性
    uint8_t sublv1; //洗练属性等级
    uint8_t subt2;
    uint8_t sublv2;
    uint8_t subt3;
    uint8_t sublv3;
    uint8_t subt4;
    uint8_t sublv4;

	DataEquipment():
		ud(0),
		uid(0),
		eqid(0),
		num(0),
		deltime(0),
		heroid(0),
		star(0),
		issold(0),
		born1(0),
		born2(0),
		subt1(0),
		sublv1(0),
		subt2(0),
		sublv2(0),
		subt3(0),
		sublv3(0),
		subt4(0),
		sublv4(0)
	{

	}


	void SetMessage(DataCommon::EquipmentCPP *msg)
	{
		msg->set_equd(ud);
		msg->set_eqid(eqid);
		msg->set_num(num);
		msg->set_deltime(deltime);
		msg->set_heroid(heroid);
		msg->set_star(star);
		msg->set_issold(issold);

		{
			vector<uint32_t> vctsubs;

			AddtoVct(born1)
			AddtoVct(born2)

			for(size_t i = 0; i < vctsubs.size(); ++i)
			{
				msg->add_bornval(vctsubs[i]);
			}
		}

		{
			vector<uint8_t> vctsubs;
			AddtoVct(subt1)
			AddtoVct(subt2)
			AddtoVct(subt3)
			AddtoVct(subt4)

			for(size_t i = 0; i < vctsubs.size(); ++i)
			{
				DataCommon::EquipSubsCPP * sub = msg->add_subs();
				sub->set_type(vctsubs[i]);
			}
		}

		{
			vector<uint8_t> vctsubs;
			AddtoVct(sublv1)
			AddtoVct(sublv2)
			AddtoVct(sublv3)
			AddtoVct(sublv4)

			for(size_t i = 0; i < vctsubs.size(); ++i)
			{
				DataCommon::EquipSubsCPP * sub = msg->mutable_subs(i);
				sub->set_level(vctsubs[i]);
			}
		}
	}

	bool operator > (DataEquipment & oth)
	{
		//假设品质相同，先判断星级
		if(star > oth.star)
		{
			return true;
		}
		else if (star < oth.star)
		{
			return false;
		}

		//星级相同，比较属性和
		uint32_t sum = born1+born2+sublv1+sublv2+sublv3+sublv4;
		uint32_t sumoth = oth.born1+oth.born2+oth.sublv1+oth.sublv2+oth.sublv3+oth.sublv4;

		if (sum > sumoth)
		{
			return true;
		}

		return false;
	}

	//
	uint8_t GetAttrVal(int index) const;
	uint8_t GetAttrLvL(int index) const;
	uint8_t* AttrVal(int index);
	uint8_t* AttrLvL(int index);
};

class CDataEquipment :public DBCBase<DataEquipment, DB_EQUIPMENT>
{
public:
	virtual int Get(DataEquipment &data);
	virtual int Get(vector<DataEquipment> &data);
	virtual int Add(DataEquipment &data);
	virtual int Set(DataEquipment &data);
	virtual int Del(DataEquipment &data);
};

#endif //DATA_EQUIP_SHOP_H_
