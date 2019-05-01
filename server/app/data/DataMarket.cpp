#include "DataMarket.h"

int CDataMarket::Get(DataMarket &data)
{
	DBCREQ_DECLARE(DBC::GetRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(type1);
	DBCREQ_NEED(character1);
	DBCREQ_NEED(type2);
	DBCREQ_NEED(character2);
	DBCREQ_NEED(type3);
	DBCREQ_NEED(character3);
	DBCREQ_NEED(refreshtime);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;
	DBCREQ_IFFETCHROW;

	DBCREQ_GET_BEGIN();
	DBCREQ_GET_INT(data, uid);
	DBCREQ_GET_INT(data, type1);
	DBCREQ_GET_INT(data, character1);
	DBCREQ_GET_INT(data, type2);
	DBCREQ_GET_INT(data, character2);
	DBCREQ_GET_INT(data, type3);
	DBCREQ_GET_INT(data, character3);
	DBCREQ_GET_INT(data, refreshtime);

	return 0;
}

int CDataMarket::Add(DataMarket &data)
{
	DBCREQ_DECLARE(DBC::InsertRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_SET_INT(data, type1);
	DBCREQ_SET_INT(data, character1);
	DBCREQ_SET_INT(data, type2);
	DBCREQ_SET_INT(data, character2);
	DBCREQ_SET_INT(data, type3);
	DBCREQ_SET_INT(data, character3);
	DBCREQ_SET_INT(data, refreshtime);

	DBCREQ_EXEC;

	return 0;
}

int CDataMarket::Set(DataMarket &data)
{
	DBCREQ_DECLARE(DBC::UpdateRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_SET_INT(data, type1);
	DBCREQ_SET_INT(data, character1);
	DBCREQ_SET_INT(data, type2);
	DBCREQ_SET_INT(data, character2);
	DBCREQ_SET_INT(data, type3);
	DBCREQ_SET_INT(data, character3);
	DBCREQ_SET_INT(data, refreshtime);

	DBCREQ_EXEC;

	return 0;
}

int CDataMarket::Del(DataMarket &data)
{
	DBCREQ_DECLARE(DBC::DeleteRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_EXEC;

	return 0;
}
