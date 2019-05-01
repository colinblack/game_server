#include "DataOperaBattle.h"

int CDataOperaBattle::Get(DataOperaBattle &data)
{
	DBCREQ_DECLARE(DBC::GetRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_CONDITION(EQ, gateid, data.gateid);
	DBCREQ_SET_CONDITION(EQ, difficulty, data.difficulty);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(gateid);
	DBCREQ_NEED(difficulty);
	DBCREQ_NEED(star);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;
	DBCREQ_IFFETCHROW;

	DBCREQ_GET_BEGIN();
	DBCREQ_GET_INT(data, uid);
	DBCREQ_GET_INT(data, gateid);
	DBCREQ_GET_INT(data, difficulty);
	DBCREQ_GET_INT(data, star);

	return 0;
}

int CDataOperaBattle::Get(vector<DataOperaBattle> &data)
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
	DBCREQ_NEED(difficulty);
	DBCREQ_NEED(star);

	data.clear();
	DBCREQ_EXEC;

	DBCREQ_ARRAY_GET_BEGIN(data);
	DBCREQ_ARRAY_GET_INT(data, uid);
	DBCREQ_ARRAY_GET_INT(data, gateid);
	DBCREQ_ARRAY_GET_INT(data, difficulty);
	DBCREQ_ARRAY_GET_INT(data, star);

	DBCREQ_ARRAY_GET_END();

	return 0;
}

int CDataOperaBattle::Add(DataOperaBattle &data)
{
	DBCREQ_DECLARE(DBC::ReplaceRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_SET_INT(data, gateid);
	DBCREQ_SET_INT(data, difficulty);
	DBCREQ_SET_INT(data, star);

	DBCREQ_EXEC;

	return 0;
}

int CDataOperaBattle::Set(DataOperaBattle &data)
{
	DBCREQ_DECLARE(DBC::UpdateRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_CONDITION(EQ, gateid, data.gateid);
	DBCREQ_SET_CONDITION(EQ, difficulty, data.difficulty);

	DBCREQ_SET_INT(data, star);
	DBCREQ_EXEC;

	return 0;
}

int CDataOperaBattle::Del(DataOperaBattle &data)
{
	DBCREQ_DECLARE(DBC::DeleteRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_CONDITION(EQ, gateid, data.gateid);
	DBCREQ_SET_CONDITION(EQ, difficulty, data.difficulty);

	DBCREQ_EXEC;

	return 0;
}
