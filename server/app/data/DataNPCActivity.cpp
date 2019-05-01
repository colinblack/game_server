#include "DataNPCActivity.h"

int CDataNPCActivity::Get(DataNPCActivity &data)
{
	DBCREQ_DECLARE(DBC::GetRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(version);
	DBCREQ_NEED(affair_id);
	DBCREQ_NEED(active_value);
	DBCREQ_NEED(status);
	DBCREQ_NEED(materialnum1);
	DBCREQ_NEED(materialnum2);
	DBCREQ_NEED(materialnum3);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;
	DBCREQ_IFFETCHROW;

	DBCREQ_GET_BEGIN();
	DBCREQ_GET_INT(data, uid);
	DBCREQ_GET_INT(data, version);
	DBCREQ_GET_INT(data, affair_id);
	DBCREQ_GET_INT(data, active_value);
	DBCREQ_GET_INT(data, status);
	DBCREQ_GET_INT(data, materialnum1);
	DBCREQ_GET_INT(data, materialnum2);
	DBCREQ_GET_INT(data, materialnum3);

	return 0;
}

int CDataNPCActivity::Add(DataNPCActivity &data)
{
	DBCREQ_DECLARE(DBC::InsertRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_SET_INT(data, version);
	DBCREQ_SET_INT(data, affair_id);
	DBCREQ_SET_INT(data, active_value);
	DBCREQ_SET_INT(data, status);
	DBCREQ_SET_INT(data, materialnum1);
	DBCREQ_SET_INT(data, materialnum2);
	DBCREQ_SET_INT(data, materialnum3);

	DBCREQ_EXEC;

	return 0;
}

int CDataNPCActivity::Set(DataNPCActivity &data)
{
	DBCREQ_DECLARE(DBC::UpdateRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_SET_INT(data, version);
	DBCREQ_SET_INT(data, affair_id);
	DBCREQ_SET_INT(data, active_value);
	DBCREQ_SET_INT(data, status);
	DBCREQ_SET_INT(data, materialnum1);
	DBCREQ_SET_INT(data, materialnum2);
	DBCREQ_SET_INT(data, materialnum3);

	DBCREQ_EXEC;

	return 0;
}

int CDataNPCActivity::Del(DataNPCActivity &data)
{
	DBCREQ_DECLARE(DBC::DeleteRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_EXEC;

	return 0;
}
