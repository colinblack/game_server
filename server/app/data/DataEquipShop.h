#ifndef DATA_EQUIP_SHOP_H_
#define DATA_EQUIP_SHOP_H_
#include "Kernel.h"

struct DataEquipShop
{
	uint32_t uid;
	uint32_t eqid;
	uint8_t pid;   //位置
	uint8_t status;   //是否可购买
	uint8_t subt1;
	uint8_t subt2;
	uint8_t subt3;
	uint8_t subt4;

	DataEquipShop():
		uid(0),
		eqid(0),
		pid(0),
		status(1),
		subt1(0),
		subt2(0),
		subt3(0),
		subt4(0)
	{

	}

	void SetMessage(DataCommon::EquipShopCPP *msg)
	{
		msg->set_eqid(eqid);
		msg->set_status(status);

		vector<uint8_t> vctsubs;

		AddtoVct(subt1)
		AddtoVct(subt2)
		AddtoVct(subt3)
		AddtoVct(subt4)

		for(size_t i = 0; i < vctsubs.size(); ++i)
		{
			msg->add_subs(vctsubs[i]);
		}
	}

	void Clear()
	{
		eqid = 0;
		status = 1;   //是否可购买
		subt1 = 0;
		subt2 = 0;
		subt3 = 0;
		subt4 = 0;
	}

	void GetEquipSubs(vector<uint8_t> & vctsubs)
	{
		AddtoVct(subt1)
		AddtoVct(subt2)
		AddtoVct(subt3)
		AddtoVct(subt4)
	}
};

class CDataEquipShop :public DBCBase<DataEquipShop, DB_EQUIP_SHOP>
{
public:
	virtual int Get(DataEquipShop &data);
	virtual int Get(vector<DataEquipShop> &data);
	virtual int Add(DataEquipShop &data);
	virtual int Set(DataEquipShop &data);
	virtual int Del(DataEquipShop &data);
};

#endif //DATA_EQUIP_SHOP_H_
