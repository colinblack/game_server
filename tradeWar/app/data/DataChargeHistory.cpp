#include "DataChargeHistory.h"
#include "AsyncDBManager.h"

void CDataChargeHistory::doRequest(CNetPacket* p) {
	switch (p->stime) {
	case e_DBAsyncTypeAdd:
		Add(p);
		break;
	case e_DBAsyncTypeSet:
		Set(p);
		break;
	case e_DBAsyncTypeDel:
		Del(p);
		break;
	}
}

int CDataChargeHistory::Get(uint32_t uid, uint32_t ts, DataChargeHistory &data)
{
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);
	DBCREQ_SET_CONDITION(EQ, ts, ts);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(ts);
	DBCREQ_NEED(cash);
	DBCREQ_NEED(cost);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;
	DBCREQ_IFFETCHROW;

	DBCREQ_GET_BEGIN();
	DBCREQ_GET_INT(data, uid);
	DBCREQ_GET_INT(data, ts);
	DBCREQ_GET_INT(data, cash);
	DBCREQ_GET_INT(data, cost);

	return 0;
}

int CDataChargeHistory::Get(uint32_t uid, vector<DataChargeHistory> &data)
{
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(ts);
	DBCREQ_NEED(cash);
	DBCREQ_NEED(cost);

	data.clear();
	DBCREQ_EXEC;

	DBCREQ_ARRAY_GET_BEGIN(data);
	DBCREQ_ARRAY_GET_INT(data, uid);
	DBCREQ_ARRAY_GET_INT(data, ts);
	DBCREQ_ARRAY_GET_INT(data, cash);
	DBCREQ_ARRAY_GET_INT(data, cost);

	DBCREQ_ARRAY_GET_END();

	return 0;
}

int CDataChargeHistory::Add(const DataChargeHistory &data)
{
	DB_ENCODE_BEGIN(DB_CHARGE_HISTORY, e_DBAsyncTypeAdd);
	if (!data.Encode(writer)) {
		return -1;
	}
	DB_ENCODE_END;
	return 0;
}

int CDataChargeHistory::Set(const DataChargeHistory &data)
{
	DB_ENCODE_BEGIN(DB_CHARGE_HISTORY, e_DBAsyncTypeSet);
	if (!data.Encode(writer)) {
		return -1;
	}
	DB_ENCODE_END;
	return 0;
}

int CDataChargeHistory::Del(uint32_t uid, uint32_t ts)
{
	DataChargeHistory data;
	data.uid = uid;
	data.ts = ts;
	DB_ENCODE_BEGIN(DB_CHARGE_HISTORY, e_DBAsyncTypeDel);
	if (!data.Encode(writer)) {
		return -1;
	}
	DB_ENCODE_END;
	return 0;
}

int CDataChargeHistory::Add(CNetPacket* p) {
	DataChargeHistory data;
	DB_DECODE_BEGIN(p->GetBody());
	if (!data.Decode(reader)) {
		return -1;
	}
	DB_DECODE_END;

	DBCREQ_DECLARE(DBC::ReplaceRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_SET_INT(data, ts);
	DBCREQ_SET_INT(data, cash);
	DBCREQ_SET_INT(data, cost);

	DBCREQ_EXEC;
	return 0;
}
int CDataChargeHistory::Set(CNetPacket* p) {
	DataChargeHistory data;
	DB_DECODE_BEGIN(p->GetBody());
	if (!data.Decode(reader)) {
		return -1;
	}
	DB_DECODE_END;
	DBCREQ_DECLARE(DBC::UpdateRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_CONDITION(EQ, ts, data.ts);

	DBCREQ_SET_INT(data, cash);
	DBCREQ_SET_INT(data, cost);

	DBCREQ_EXEC;
	return 0;
}
int CDataChargeHistory::Del(CNetPacket* p) {
	DataChargeHistory data;
	DB_DECODE_BEGIN(p->GetBody());
	if (!data.Decode(reader)) {
		return -1;
	}
	DB_DECODE_END;

	DBCREQ_DECLARE(DBC::DeleteRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	if (data.ts > 0) {
		DBCREQ_SET_CONDITION(EQ, ts, data.ts);
	}

	DBCREQ_EXEC;
	return 0;
}
