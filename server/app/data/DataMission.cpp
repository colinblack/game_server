#include "DataMission.h"

int CDataMission::Get(DataMission &data)
{
	DBCREQ_DECLARE(DBC::GetRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_CONDITION(EQ, id, data.id);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(id);
	DBCREQ_NEED(status);
	DBCREQ_NEED(current);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;
	DBCREQ_IFFETCHROW;

	DBCREQ_GET_BEGIN();
	DBCREQ_GET_INT(data, uid);
	DBCREQ_GET_INT(data, id);
	DBCREQ_GET_INT(data, status);
	DBCREQ_GET_INT(data, current);

	return 0;
}

int CDataMission::Get(vector<DataMission> &data)
{
	if (0 == data.size())
	{
		return R_ERR_PARAM;
	}

	DBCREQ_DECLARE(DBC::GetRequest, data[0].uid);
	DBCREQ_SET_KEY(data[0].uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(id);
	DBCREQ_NEED(status);
	DBCREQ_NEED(current);

	data.clear();
	DBCREQ_EXEC;

	DBCREQ_ARRAY_GET_BEGIN(data);
	DBCREQ_ARRAY_GET_INT(data, uid);
	DBCREQ_ARRAY_GET_INT(data, id);
	DBCREQ_ARRAY_GET_INT(data, status);
	DBCREQ_ARRAY_GET_INT(data, current);

	DBCREQ_ARRAY_GET_END();

	return 0;
}

int CDataMission::Add(DataMission &data)
{
	//warn_log("add mission . uid=%u,mid=%u", data.uid, data.id);
	DBCREQ_DECLARE(DBC::InsertRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_SET_INT(data, id);
	DBCREQ_SET_INT(data, status);
	DBCREQ_SET_INT(data, current);

	DBCREQ_EXEC;


	return 0;
}

int CDataMission::Set(DataMission &data)
{
	//warn_log("update mission . uid=%u,mid=%u", data.uid, data.id);
	DBCREQ_DECLARE(DBC::UpdateRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_CONDITION(EQ, id, data.id);

	DBCREQ_SET_INT(data, status);
	DBCREQ_SET_INT(data, current);

	DBCREQ_EXEC;


	return 0;
}

int CDataMission::Del(DataMission &data)
{
	//warn_log("del mission . uid=%u,mid=%u", data.uid, data.id);
	DBCREQ_DECLARE(DBC::DeleteRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_CONDITION(EQ, id, data.id);

	DBCREQ_EXEC;


	return 0;
}
