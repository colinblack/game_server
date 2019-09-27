#include "DataActiveness.h"
#include "AsyncDBManager.h"

#define OP_ADD_ACTIVENESS 1
#define OP_UPDATE_ACTIVENESS 2
#define OP_REMOVE_ACTIVENESS 3

int CDataActiveness::AddActiveness(const DataActiveness &data)
{
	DB_ENCODE_BEGIN(DB_ACTIVENESS, OP_ADD_ACTIVENESS);
	DB_ENCODE(UInt32, data.uid);
	DB_ENCODE(UInt32, data.ts);
	DB_ENCODE(UInt32, data.score);
	DB_ENCODE(UInt32, data.reward);
	DB_ENCODE(String, data.data);
	DB_ENCODE_END;

	return 0;
}

int CDataActiveness::UpdateActiveness(const DataActiveness &data)
{
	DB_ENCODE_BEGIN(DB_ACTIVENESS, OP_UPDATE_ACTIVENESS);
	DB_ENCODE(UInt32, data.uid);
	DB_ENCODE(UInt32, data.ts);
	DB_ENCODE(UInt32, data.score);
	DB_ENCODE(UInt32, data.reward);
	DB_ENCODE(String, data.data);
	DB_ENCODE_END;

	return 0;
}

int CDataActiveness::RemoveActiveness(uint32_t uid)
{
	DB_ENCODE_BEGIN(DB_ACTIVENESS, OP_REMOVE_ACTIVENESS);
	DB_ENCODE(UInt32, uid);
	DB_ENCODE_END;

	return 0;
}

int CDataActiveness::GetActiveness(uint32_t uid, DataActiveness& data)
{
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(ts);
	DBCREQ_NEED(score);
	DBCREQ_NEED(reward);
	DBCREQ_NEED(data);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;
	DBCREQ_IFFETCHROW;

	DBCREQ_GET_BEGIN();
	DBCREQ_GET_INT(data, uid);
	DBCREQ_GET_INT(data, ts);
	DBCREQ_GET_INT(data, score);
	DBCREQ_GET_INT(data, reward);
	DBCREQ_GET_STR(data, data);

	return 0;
}

int CDataActiveness::RealAddActiveness(CNetPacket *packet)
{
	DataActiveness dataActiveness;

	DB_DECODE_BEGIN(&packet->body);
	DB_DECODE(UInt32, dataActiveness.uid);
	DB_DECODE(UInt32, dataActiveness.ts);
	DB_DECODE(UInt32, dataActiveness.score);
	DB_DECODE(UInt32, dataActiveness.reward);
	DB_DECODE(String, dataActiveness.data);
	DB_DECODE_END

	DBCREQ_DECLARE(DBC::InsertRequest, dataActiveness.uid);
	DBCREQ_SET_KEY(dataActiveness.uid);

	DBCREQ_SET_INT(dataActiveness, ts);
	DBCREQ_SET_INT(dataActiveness, score);
	DBCREQ_SET_INT(dataActiveness, reward);
	DBCREQ_SET_STR(dataActiveness, data);

	DBCREQ_EXEC;

	return 0;
}

int CDataActiveness::RealRemoveActiveness(CNetPacket *packet)
{
	uint32_t uid;
	DB_DECODE_BEGIN(&packet->body);
	DB_DECODE(UInt32, uid);
	DB_DECODE_END;

	DBCREQ_DECLARE(DBC::DeleteRequest, uid);
	DBCREQ_SET_KEY(uid);

	DBCREQ_EXEC;

	return 0;
}

int CDataActiveness::RealUpdateActiveness(CNetPacket *packet)
{
	DataActiveness dataActiveness;

	DB_DECODE_BEGIN(&packet->body);
	DB_DECODE(UInt32, dataActiveness.uid);
	DB_DECODE(UInt32, dataActiveness.ts);
	DB_DECODE(UInt32, dataActiveness.score);
	DB_DECODE(UInt32, dataActiveness.reward);
	DB_DECODE(String, dataActiveness.data);
	DB_DECODE_END;

	DBCREQ_DECLARE(DBC::UpdateRequest, dataActiveness.uid);
	DBCREQ_SET_KEY(dataActiveness.uid);

	DBCREQ_SET_INT(dataActiveness, ts);
	DBCREQ_SET_INT(dataActiveness, score);
	DBCREQ_SET_INT(dataActiveness, reward);
	DBCREQ_SET_STR(dataActiveness, data);

	DBCREQ_EXEC;

	return 0;
}

OP_PROCESS_BEGIN(CDataActiveness)
	OP_PROCESS(OP_ADD_ACTIVENESS, RealAddActiveness)
	OP_PROCESS(OP_UPDATE_ACTIVENESS, RealUpdateActiveness)
	OP_PROCESS(OP_REMOVE_ACTIVENESS, RealRemoveActiveness)
	OP_PROCESS_END
