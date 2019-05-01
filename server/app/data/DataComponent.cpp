#include "DataComponent.h"

int CDataComponent::Get(DataComponent &data)
{
	DBCREQ_DECLARE(DBC::GetRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_CONDITION(EQ, ud, data.ud);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(ud);
	DBCREQ_NEED(compid);
	DBCREQ_NEED(level);
	DBCREQ_NEED(exp);
	DBCREQ_NEED(heroid);
	DBCREQ_NEED(position);
	DBCREQ_NEED(master);
	DBCREQ_NEED(slave1);
	DBCREQ_NEED(slave2);
	DBCREQ_NEED(slave3);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;
	DBCREQ_IFFETCHROW;

	DBCREQ_GET_BEGIN();
	DBCREQ_GET_INT(data, uid);
	DBCREQ_GET_INT(data, ud);
	DBCREQ_GET_INT(data, compid);
	DBCREQ_GET_INT(data, level);
	DBCREQ_GET_INT(data, exp);
	DBCREQ_GET_INT(data, heroid);
	DBCREQ_GET_INT(data, position);
	DBCREQ_GET_INT(data, master);
	DBCREQ_GET_INT(data, slave1);
	DBCREQ_GET_INT(data, slave2);
	DBCREQ_GET_INT(data, slave3);

	return 0;
}

int CDataComponent::Get(vector<DataComponent> &data)
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
	DBCREQ_NEED(compid);
	DBCREQ_NEED(level);
	DBCREQ_NEED(exp);
	DBCREQ_NEED(heroid);
	DBCREQ_NEED(position);
	DBCREQ_NEED(master);
	DBCREQ_NEED(slave1);
	DBCREQ_NEED(slave2);
	DBCREQ_NEED(slave3);

	data.clear();
	DBCREQ_EXEC;

	DBCREQ_ARRAY_GET_BEGIN(data);
	DBCREQ_ARRAY_GET_INT(data, uid);
	DBCREQ_ARRAY_GET_INT(data, ud);
	DBCREQ_ARRAY_GET_INT(data, compid);
	DBCREQ_ARRAY_GET_INT(data, level);
	DBCREQ_ARRAY_GET_INT(data, exp);
	DBCREQ_ARRAY_GET_INT(data, heroid);
	DBCREQ_ARRAY_GET_INT(data, position);
	DBCREQ_ARRAY_GET_INT(data, master);
	DBCREQ_ARRAY_GET_INT(data, slave1);
	DBCREQ_ARRAY_GET_INT(data, slave2);
	DBCREQ_ARRAY_GET_INT(data, slave3);

	DBCREQ_ARRAY_GET_END();

	return 0;
}

int CDataComponent::Add(DataComponent &data)
{
	DBCREQ_DECLARE(DBC::ReplaceRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_SET_INT(data, ud);
	DBCREQ_SET_INT(data, compid);
	DBCREQ_SET_INT(data, level);
	DBCREQ_SET_INT(data, exp);
	DBCREQ_SET_INT(data, heroid);
	DBCREQ_SET_INT(data, position);
	DBCREQ_SET_INT(data, master);
	DBCREQ_SET_INT(data, slave1);
	DBCREQ_SET_INT(data, slave2);
	DBCREQ_SET_INT(data, slave3);

	DBCREQ_EXEC;

	return 0;
}

int CDataComponent::Set(DataComponent &data)
{
	DBCREQ_DECLARE(DBC::UpdateRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_CONDITION(EQ, ud, data.ud);


	DBCREQ_SET_INT(data, compid);
	DBCREQ_SET_INT(data, level);
	DBCREQ_SET_INT(data, exp);
	DBCREQ_SET_INT(data, heroid);
	DBCREQ_SET_INT(data, position);
	DBCREQ_SET_INT(data, master);
	DBCREQ_SET_INT(data, slave1);
	DBCREQ_SET_INT(data, slave2);
	DBCREQ_SET_INT(data, slave3);

	DBCREQ_EXEC;

	return 0;
}

int CDataComponent::Del(DataComponent &data)
{
	DBCREQ_DECLARE(DBC::DeleteRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_CONDITION(EQ, ud, data.ud);

	DBCREQ_EXEC;

	return 0;
}
