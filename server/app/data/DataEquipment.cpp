#include "DataEquipment.h"


uint8_t DataEquipment::GetAttrVal(int index) const
{
	if (index < 0 || index >= 4)
	{
		throw std::runtime_error("data_equipment_attrVal_index_error");
	}
	uint8_t attr[4] = {subt1, subt2, subt3, subt4};
	return attr[index];
}

uint8_t DataEquipment::GetAttrLvL(int index) const
{
	if (index < 0 || index >= 4)
	{
		throw std::runtime_error("data_equipment_attrVal_index_error");
	}
	uint8_t attrLvL[4] = {sublv1, sublv2, sublv3, sublv4};
	return attrLvL[index];
}

uint8_t* DataEquipment::AttrVal(int index)
{
	if (index < 0 || index >= 4)
	{
		throw std::runtime_error("data_equipment_attrVal_index_error");
	}
	uint8_t* attr[4] = {&subt1, &subt2, &subt3, &subt4};
	return attr[index];
}

uint8_t* DataEquipment::AttrLvL(int index)
{
	if (index < 0 || index >= 4)
	{
		throw std::runtime_error("data_equipment_attrVal_index_error");
	}
	uint8_t* attrLvL[4] = {&sublv1, &sublv2, &sublv3, &sublv4};
	return attrLvL[index];
}
///////////////////////////////////////////////////////
int CDataEquipment::Get(DataEquipment &data)
{
	DBCREQ_DECLARE(DBC::GetRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_CONDITION(EQ, ud, data.ud);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(ud);
	DBCREQ_NEED(eqid);
	DBCREQ_NEED(num);
	DBCREQ_NEED(deltime);
	DBCREQ_NEED(heroid);
	DBCREQ_NEED(star);
	DBCREQ_NEED(issold);
	DBCREQ_NEED(born1);
	DBCREQ_NEED(born2);
	DBCREQ_NEED(subt1);
	DBCREQ_NEED(sublv1);
	DBCREQ_NEED(subt2);
	DBCREQ_NEED(sublv2);
	DBCREQ_NEED(subt3);
	DBCREQ_NEED(sublv3);
	DBCREQ_NEED(subt4);
	DBCREQ_NEED(sublv4);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;
	DBCREQ_IFFETCHROW;

	DBCREQ_GET_BEGIN();
	DBCREQ_GET_INT(data, uid);
	DBCREQ_GET_INT(data, ud);
	DBCREQ_GET_INT(data, eqid);
	DBCREQ_GET_INT(data, num);
	DBCREQ_GET_INT(data, deltime);
	DBCREQ_GET_INT(data, heroid);
	DBCREQ_GET_INT(data, star);
	DBCREQ_GET_INT(data, issold);
	DBCREQ_GET_INT(data, born1);
	DBCREQ_GET_INT(data, born2);
	DBCREQ_GET_INT(data, subt1);
	DBCREQ_GET_INT(data, sublv1);
	DBCREQ_GET_INT(data, subt2);
	DBCREQ_GET_INT(data, sublv2);
	DBCREQ_GET_INT(data, subt3);
	DBCREQ_GET_INT(data, sublv3);
	DBCREQ_GET_INT(data, subt4);
	DBCREQ_GET_INT(data, sublv4);

	return 0;
}

int CDataEquipment::Get(vector<DataEquipment> &data)
{
	if (0 == data.size())
	{
		return R_ERR_PARAM;
	}

	DBCREQ_DECLARE(DBC::GetRequest, data[0].uid);
	DBCREQ_SET_KEY(data[0].uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(ud);
	DBCREQ_NEED(eqid);
	DBCREQ_NEED(num);
	DBCREQ_NEED(deltime);
	DBCREQ_NEED(heroid);
	DBCREQ_NEED(star);
	DBCREQ_NEED(issold);
	DBCREQ_NEED(born1);
	DBCREQ_NEED(born2);
	DBCREQ_NEED(subt1);
	DBCREQ_NEED(sublv1);
	DBCREQ_NEED(subt2);
	DBCREQ_NEED(sublv2);
	DBCREQ_NEED(subt3);
	DBCREQ_NEED(sublv3);
	DBCREQ_NEED(subt4);
	DBCREQ_NEED(sublv4);

	data.clear();
	DBCREQ_EXEC;

	DBCREQ_ARRAY_GET_BEGIN(data);
	DBCREQ_ARRAY_GET_INT(data, uid);
	DBCREQ_ARRAY_GET_INT(data, ud);
	DBCREQ_ARRAY_GET_INT(data, eqid);
	DBCREQ_ARRAY_GET_INT(data, num);
	DBCREQ_ARRAY_GET_INT(data, deltime);
	DBCREQ_ARRAY_GET_INT(data, heroid);
	DBCREQ_ARRAY_GET_INT(data, star);
	DBCREQ_ARRAY_GET_INT(data, issold);
	DBCREQ_ARRAY_GET_INT(data, born1);
	DBCREQ_ARRAY_GET_INT(data, born2);
	DBCREQ_ARRAY_GET_INT(data, subt1);
	DBCREQ_ARRAY_GET_INT(data, sublv1);
	DBCREQ_ARRAY_GET_INT(data, subt2);
	DBCREQ_ARRAY_GET_INT(data, sublv2);
	DBCREQ_ARRAY_GET_INT(data, subt3);
	DBCREQ_ARRAY_GET_INT(data, sublv3);
	DBCREQ_ARRAY_GET_INT(data, subt4);
	DBCREQ_ARRAY_GET_INT(data, sublv4);

	DBCREQ_ARRAY_GET_END();

	return 0;
}

int CDataEquipment::Add(DataEquipment &data)
{
	DBCREQ_DECLARE(DBC::ReplaceRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_SET_INT(data, ud);
	DBCREQ_SET_INT(data, eqid);
	DBCREQ_SET_INT(data, num);
	DBCREQ_SET_INT(data, deltime);
	DBCREQ_SET_INT(data, heroid);
	DBCREQ_SET_INT(data, star);
	DBCREQ_SET_INT(data, issold);
	DBCREQ_SET_INT(data, born1);
	DBCREQ_SET_INT(data, born2);
	DBCREQ_SET_INT(data, subt1);
	DBCREQ_SET_INT(data, sublv1);
	DBCREQ_SET_INT(data, subt2);
	DBCREQ_SET_INT(data, sublv2);
	DBCREQ_SET_INT(data, subt3);
	DBCREQ_SET_INT(data, sublv3);
	DBCREQ_SET_INT(data, subt4);
	DBCREQ_SET_INT(data, sublv4);

	DBCREQ_EXEC;

	return 0;
}

int CDataEquipment::Set(DataEquipment &data)
{
	DBCREQ_DECLARE(DBC::UpdateRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_CONDITION(EQ, ud, data.ud);

	DBCREQ_SET_INT(data, eqid);
	DBCREQ_SET_INT(data, num);
	DBCREQ_SET_INT(data, deltime);
	DBCREQ_SET_INT(data, heroid);
	DBCREQ_SET_INT(data, star);
	DBCREQ_SET_INT(data, issold);
	DBCREQ_SET_INT(data, born1);
	DBCREQ_SET_INT(data, born2);
	DBCREQ_SET_INT(data, subt1);
	DBCREQ_SET_INT(data, sublv1);
	DBCREQ_SET_INT(data, subt2);
	DBCREQ_SET_INT(data, sublv2);
	DBCREQ_SET_INT(data, subt3);
	DBCREQ_SET_INT(data, sublv3);
	DBCREQ_SET_INT(data, subt4);
	DBCREQ_SET_INT(data, sublv4);

	DBCREQ_EXEC;

	return 0;
}

int CDataEquipment::Del(DataEquipment &data)
{
	DBCREQ_DECLARE(DBC::DeleteRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_CONDITION(EQ, ud, data.ud);

	DBCREQ_EXEC;

	return 0;
}
