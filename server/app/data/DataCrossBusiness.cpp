#include "DataCrossBusiness.h"

int CDataCrossBusiness::Get(DataCrossBusiness &data)
{
	DBCREQ_DECLARE(DBC::GetRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(refreshts);
	DBCREQ_NEED(slot1);
	DBCREQ_NEED(slot2);
	DBCREQ_NEED(slot3);
	DBCREQ_NEED(slot4);
	DBCREQ_NEED(slot5);
	DBCREQ_NEED(slot6);
	DBCREQ_NEED(status);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;
	DBCREQ_IFFETCHROW;

	DBCREQ_GET_BEGIN();
	DBCREQ_GET_INT(data, uid);
	DBCREQ_GET_INT(data, refreshts);
	DBCREQ_GET_INT(data, slot1);
	DBCREQ_GET_INT(data, slot2);
	DBCREQ_GET_INT(data, slot3);
	DBCREQ_GET_INT(data, slot4);
	DBCREQ_GET_INT(data, slot5);
	DBCREQ_GET_INT(data, slot6);
	DBCREQ_GET_INT(data, status);

	return 0;
}

int CDataCrossBusiness::Add(DataCrossBusiness &data)
{
	DBCREQ_DECLARE(DBC::ReplaceRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_SET_INT(data, refreshts);
	DBCREQ_SET_INT(data, slot1);
	DBCREQ_SET_INT(data, slot2);
	DBCREQ_SET_INT(data, slot3);
	DBCREQ_SET_INT(data, slot4);
	DBCREQ_SET_INT(data, slot5);
	DBCREQ_SET_INT(data, slot6);
	DBCREQ_SET_INT(data, status);

	DBCREQ_EXEC;

	return 0;
}

int CDataCrossBusiness::Set(DataCrossBusiness &data)
{
	DBCREQ_DECLARE(DBC::UpdateRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_SET_INT(data, refreshts);
	DBCREQ_SET_INT(data, slot1);
	DBCREQ_SET_INT(data, slot2);
	DBCREQ_SET_INT(data, slot3);
	DBCREQ_SET_INT(data, slot4);
	DBCREQ_SET_INT(data, slot5);
	DBCREQ_SET_INT(data, slot6);
	DBCREQ_SET_INT(data, status);

	DBCREQ_EXEC;

	return 0;
}

int CDataCrossBusiness::Del(DataCrossBusiness &data)
{
	DBCREQ_DECLARE(DBC::DeleteRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_EXEC;

	return 0;
}
