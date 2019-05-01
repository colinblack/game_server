#include "DataProduceComponent.h"

int CDataProduceComponent::Get(DataProduceComponent &data)
{
	DBCREQ_DECLARE(DBC::GetRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(current_level);
	DBCREQ_NEED(ispaycash);
	DBCREQ_NEED(times);
	DBCREQ_NEED(paycash_ts);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;
	DBCREQ_IFFETCHROW;

	DBCREQ_GET_BEGIN();
	DBCREQ_GET_INT(data, uid);
	DBCREQ_GET_INT(data, current_level);
	DBCREQ_GET_INT(data, ispaycash);
	DBCREQ_GET_INT(data, times);
	DBCREQ_GET_INT(data, paycash_ts);

	return 0;
}

int CDataProduceComponent::Add(DataProduceComponent &data)
{
	DBCREQ_DECLARE(DBC::InsertRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_SET_INT(data, current_level);
	DBCREQ_SET_INT(data, ispaycash);
	DBCREQ_SET_INT(data, times);
	DBCREQ_SET_INT(data, paycash_ts);

	DBCREQ_EXEC;

	return 0;
}

int CDataProduceComponent::Set(DataProduceComponent &data)
{
	DBCREQ_DECLARE(DBC::UpdateRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_SET_INT(data, current_level);
	DBCREQ_SET_INT(data, ispaycash);
	DBCREQ_SET_INT(data, times);
	DBCREQ_SET_INT(data, paycash_ts);

	DBCREQ_EXEC;

	return 0;
}

int CDataProduceComponent::Del(DataProduceComponent &data)
{
	DBCREQ_DECLARE(DBC::DeleteRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_EXEC;

	return 0;
}
