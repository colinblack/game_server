#include "DataModelTrial.h"

int CDataModelTrial::Get(DataModelTrial &data)
{
	DBCREQ_DECLARE(DBC::GetRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(curpos);
	DBCREQ_NEED(fight_times);
	DBCREQ_NEED(buy_times);
	DBCREQ_NEED(resetts);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;
	DBCREQ_IFFETCHROW;

	DBCREQ_GET_BEGIN();
	DBCREQ_GET_INT(data, uid);
	DBCREQ_GET_INT(data, curpos);
	DBCREQ_GET_INT(data, fight_times);
	DBCREQ_GET_INT(data, buy_times);
	DBCREQ_GET_INT(data, resetts);

	return 0;
}

int CDataModelTrial::Add(DataModelTrial &data)
{
	DBCREQ_DECLARE(DBC::ReplaceRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_SET_INT(data, curpos);
	DBCREQ_SET_INT(data, fight_times);
	DBCREQ_SET_INT(data, buy_times);
	DBCREQ_SET_INT(data, resetts);

	DBCREQ_EXEC;

	return 0;
}

int CDataModelTrial::Set(DataModelTrial &data)
{
	DBCREQ_DECLARE(DBC::UpdateRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_SET_INT(data, curpos);
	DBCREQ_SET_INT(data, fight_times);
	DBCREQ_SET_INT(data, buy_times);
	DBCREQ_SET_INT(data, resetts);

	DBCREQ_EXEC;

	return 0;
}

int CDataModelTrial::Del(DataModelTrial &data)
{
	DBCREQ_DECLARE(DBC::DeleteRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_EXEC;

	return 0;
}
