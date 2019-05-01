#include "DataEquipShop.h"

int CDataEquipShop::Get(DataEquipShop &data)
{
	DBCREQ_DECLARE(DBC::GetRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_CONDITION(EQ, pid, data.pid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(eqid);
	DBCREQ_NEED(pid);
	DBCREQ_NEED(status);
	DBCREQ_NEED(subt1);
	DBCREQ_NEED(subt2);
	DBCREQ_NEED(subt3);
	DBCREQ_NEED(subt4);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;
	DBCREQ_IFFETCHROW;

	DBCREQ_GET_BEGIN();
	DBCREQ_GET_INT(data, uid);
	DBCREQ_GET_INT(data, eqid);
	DBCREQ_GET_INT(data, pid);
	DBCREQ_GET_INT(data, status);
	DBCREQ_GET_INT(data, subt1);
	DBCREQ_GET_INT(data, subt2);
	DBCREQ_GET_INT(data, subt3);
	DBCREQ_GET_INT(data, subt4);

	return 0;
}

int CDataEquipShop::Get(vector<DataEquipShop> &datas)
{
	if (0 == datas.size())
	{
		return R_ERR_PARAM;
	}

	DBCREQ_DECLARE(DBC::GetRequest, datas[0].uid);
	DBCREQ_SET_KEY(datas[0].uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(eqid);
	DBCREQ_NEED(pid);
	DBCREQ_NEED(status);
	DBCREQ_NEED(subt1);
	DBCREQ_NEED(subt2);
	DBCREQ_NEED(subt3);
	DBCREQ_NEED(subt4);

	datas.clear();

	DBCREQ_EXEC;

	DBCREQ_ARRAY_GET_BEGIN(datas);
	DBCREQ_ARRAY_GET_INT(datas, uid);
	DBCREQ_ARRAY_GET_INT(datas, eqid);
	DBCREQ_ARRAY_GET_INT(datas, pid);
	DBCREQ_ARRAY_GET_INT(datas, status);
	DBCREQ_ARRAY_GET_INT(datas, subt1);
	DBCREQ_ARRAY_GET_INT(datas, subt2);
	DBCREQ_ARRAY_GET_INT(datas, subt3);
	DBCREQ_ARRAY_GET_INT(datas, subt4);

	DBCREQ_ARRAY_GET_END();

	return 0;
}

int CDataEquipShop::Add(DataEquipShop &data)
{
	DBCREQ_DECLARE(DBC::InsertRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_SET_INT(data, eqid);
	DBCREQ_SET_INT(data, status);
	DBCREQ_SET_INT(data, pid);
	DBCREQ_SET_INT(data, subt1);
	DBCREQ_SET_INT(data, subt2);
	DBCREQ_SET_INT(data, subt3);
	DBCREQ_SET_INT(data, subt4);

	DBCREQ_EXEC;

	return 0;
}

int CDataEquipShop::Set(DataEquipShop &data)
{
	DBCREQ_DECLARE(DBC::UpdateRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_CONDITION(EQ, pid, data.pid);

	DBCREQ_SET_INT(data, eqid);
	DBCREQ_SET_INT(data, status);
	DBCREQ_SET_INT(data, subt1);
	DBCREQ_SET_INT(data, subt2);
	DBCREQ_SET_INT(data, subt3);
	DBCREQ_SET_INT(data, subt4);

	DBCREQ_EXEC;

	return 0;
}

int CDataEquipShop::Del(DataEquipShop &data)
{
	DBCREQ_DECLARE(DBC::DeleteRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_CONDITION(EQ, pid, data.pid);

	DBCREQ_EXEC;

	return 0;
}
