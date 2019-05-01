#include "DataDailyMission.h"

int CDataDailyMission::Get(DataDailyMission &data)
{
	DBCREQ_DECLARE(DBC::GetRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_CONDITION(EQ, id, data.id);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(id);
	DBCREQ_NEED(missid);
	DBCREQ_NEED(status);
	DBCREQ_NEED(star);
	DBCREQ_NEED(current);
	DBCREQ_NEED(base);
	DBCREQ_NEED(gettime);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;
	DBCREQ_IFFETCHROW;

	DBCREQ_GET_BEGIN();
	DBCREQ_GET_INT(data, uid);
	DBCREQ_GET_INT(data, id);
	DBCREQ_GET_INT(data, missid);
	DBCREQ_GET_INT(data, status);
	DBCREQ_GET_INT(data, star);
	DBCREQ_GET_INT(data, current);
	DBCREQ_GET_INT(data, base);
	DBCREQ_GET_INT(data, gettime);

	return 0;
}

int CDataDailyMission::Get(vector<DataDailyMission> &data)
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
	DBCREQ_NEED(missid);
	DBCREQ_NEED(status);
	DBCREQ_NEED(star);
	DBCREQ_NEED(current);
	DBCREQ_NEED(base);
	DBCREQ_NEED(gettime);

	data.clear();
	DBCREQ_EXEC;

	DBCREQ_ARRAY_GET_BEGIN(data);
	DBCREQ_ARRAY_GET_INT(data, uid);
	DBCREQ_ARRAY_GET_INT(data, id);
	DBCREQ_ARRAY_GET_INT(data, missid);
	DBCREQ_ARRAY_GET_INT(data, status);
	DBCREQ_ARRAY_GET_INT(data, star);
	DBCREQ_ARRAY_GET_INT(data, current);
	DBCREQ_ARRAY_GET_INT(data, base);
	DBCREQ_ARRAY_GET_INT(data, gettime);

	DBCREQ_ARRAY_GET_END();

	return 0;
}

int CDataDailyMission::Add(DataDailyMission &data)
{
	DBCREQ_DECLARE(DBC::ReplaceRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_SET_INT(data, id);
	DBCREQ_SET_INT(data, missid);
	DBCREQ_SET_INT(data, status);
	DBCREQ_SET_INT(data, star);
	DBCREQ_SET_INT(data, current);
	DBCREQ_SET_INT(data, base);
	DBCREQ_SET_INT(data, gettime);

	DBCREQ_EXEC;

	return 0;
}

int CDataDailyMission::Set(DataDailyMission &data)
{
	DBCREQ_DECLARE(DBC::UpdateRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_CONDITION(EQ, id, data.id);

	DBCREQ_SET_INT(data, missid);
	DBCREQ_SET_INT(data, status);
	DBCREQ_SET_INT(data, star);
	DBCREQ_SET_INT(data, current);
	DBCREQ_SET_INT(data, base);
	DBCREQ_SET_INT(data, gettime);

	DBCREQ_EXEC;

	return 0;
}

int CDataDailyMission::Del(DataDailyMission &data)
{
	DBCREQ_DECLARE(DBC::DeleteRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_CONDITION(EQ, id, data.id);

	DBCREQ_EXEC;

	return 0;
}
