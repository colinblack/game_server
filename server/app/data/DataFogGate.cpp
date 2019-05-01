#include "DataFogGate.h"

int CDataFogGate::Get(DataFogGate &data)
{
	DBCREQ_DECLARE(DBC::GetRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_CONDITION(EQ, gateid, data.gateid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(gateid);
	DBCREQ_NEED(leftnpc);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;
	DBCREQ_IFFETCHROW;

	DBCREQ_GET_BEGIN();
	DBCREQ_GET_INT(data, uid);
	DBCREQ_GET_INT(data, gateid);
	DBCREQ_GET_INT(data, leftnpc);

	return 0;
}

int CDataFogGate::Get(vector<DataFogGate> &data)
{
	if (0 == data.size())
	{
		return R_ERR_PARAM;
	}

	DBCREQ_DECLARE(DBC::GetRequest, data[0].uid);
	DBCREQ_SET_KEY(data[0].uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(gateid);
	DBCREQ_NEED(leftnpc);

	data.clear();
	DBCREQ_EXEC;

	DBCREQ_ARRAY_GET_BEGIN(data);
	DBCREQ_ARRAY_GET_INT(data, uid);
	DBCREQ_ARRAY_GET_INT(data, gateid);
	DBCREQ_ARRAY_GET_INT(data, leftnpc);


	DBCREQ_ARRAY_GET_END();

	return 0;
}

int CDataFogGate::Add(DataFogGate &data)
{
	DBCREQ_DECLARE(DBC::ReplaceRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_SET_INT(data, gateid);
	DBCREQ_SET_INT(data, leftnpc);

	DBCREQ_EXEC;

	return 0;
}

int CDataFogGate::Set(DataFogGate &data)
{
	DBCREQ_DECLARE(DBC::UpdateRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_CONDITION(EQ, gateid, data.gateid);


	DBCREQ_SET_INT(data, leftnpc);
	DBCREQ_EXEC;

	return 0;
}

int CDataFogGate::Del(DataFogGate &data)
{
	DBCREQ_DECLARE(DBC::DeleteRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_CONDITION(EQ, gateid, data.gateid);

	DBCREQ_EXEC;

	return 0;
}
