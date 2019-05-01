#include "DataSellComponent.h"

int CDataSellComponent::Get(DataSellComponent &data)
{
	DBCREQ_DECLARE(DBC::GetRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(opents);
	DBCREQ_NEED(num1);
	DBCREQ_NEED(num2);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;
	DBCREQ_IFFETCHROW;

	DBCREQ_GET_BEGIN();
	DBCREQ_GET_INT(data, uid);
	DBCREQ_GET_INT(data, opents);
	DBCREQ_GET_INT(data, num1);
	DBCREQ_GET_INT(data, num2);

	return 0;
}

int CDataSellComponent::Add(DataSellComponent &data)
{
	DBCREQ_DECLARE(DBC::ReplaceRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_SET_INT(data, opents);
	DBCREQ_SET_INT(data, num1);
	DBCREQ_SET_INT(data, num2);

	DBCREQ_EXEC;

	return 0;
}

int CDataSellComponent::Set(DataSellComponent &data)
{
	DBCREQ_DECLARE(DBC::UpdateRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_SET_INT(data, opents);
	DBCREQ_SET_INT(data, num1);
	DBCREQ_SET_INT(data, num2);

	DBCREQ_EXEC;

	return 0;
}

int CDataSellComponent::Del(DataSellComponent &data)
{
	DBCREQ_DECLARE(DBC::DeleteRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_EXEC;

	return 0;
}
