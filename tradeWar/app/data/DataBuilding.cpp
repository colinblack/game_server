#include "DataBuilding.h"
#include "AsyncDBManager.h"
TABLE_UID_ID_DATA_CXX(Building, BUILDING)

/*
#define OP_ADD_BUILDING 1
#define OP_UPDATE_BUILDING 2
#define OP_REPLACE_BUILDING 3
#define OP_REMOVE_ONE_BUILDING 4
#define OP_REMOVE_BUILDING 5

#define DB_ENCODE_BUILDING_SERIES(dataBuilding, opId) \
	DB_ENCODE_BEGIN(DB_BUILDING, opId); \
	DB_ENCODE(UInt32,dataBuilding.uid); \
	DB_ENCODE(UInt32,dataBuilding.id); \
	DB_ENCODE(String,dataBuilding.data); \
	DB_ENCODE_END;

#define DB_DECODE_BUILDING_SERIES(packet) \
	DataBuilding dataBuilding; \
	DB_DECODE_BEGIN(&packet->body); \
	DB_DECODE(UInt32,dataBuilding.uid); \
	DB_DECODE(UInt32,dataBuilding.id); \
	DB_DECODE(String,dataBuilding.data); \
	DB_DECODE_END;

// get
int CDataBuilding::GetBuilding(unsigned uid, unsigned id, string &data)
{
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);
	DBCREQ_SET_CONDITION(EQ, id, id);

	DBCREQ_GET_STR_V(data);
	return 0;
}
// get all in vector
int CDataBuilding::GetBuilding(unsigned uid, vector<DataBuilding> &datas)
{
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(id);
	DBCREQ_NEED(data);

	DBCREQ_EXEC;

	DBCREQ_ARRAY_GET_BEGIN(datas);
	DBCREQ_ARRAY_GET_INT(datas, uid);
	DBCREQ_ARRAY_GET_INT(datas, id);
	DBCREQ_ARRAY_GET_STR(datas, data);
	DBCREQ_ARRAY_GET_END();

	return 0;
}
// get all in map
int CDataBuilding::GetBuilding(unsigned uid, map<unsigned, string> &datas)
{
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(id);
	DBCREQ_NEED(data);

	DBCREQ_EXEC;

	datas.clear();
	int count = m_dbcret.TotalRows();
	for(int i = 0; i < count; i++)
	{
		DBCREQ_IFFETCHROW;
		datas[m_dbcret.IntValue(1)] = m_dbcret.StringValue(2);
	}
	return 0;
}
// add
int CDataBuilding::AddBuilding(const DataBuilding& dataBuilding)
{
	DB_ENCODE_BUILDING_SERIES(dataBuilding, OP_ADD_BUILDING)
	return 0;
}
int CDataBuilding::RealAddBuilding(CNetPacket* packet)
{
	DB_DECODE_BUILDING_SERIES(packet)

	DBCREQ_DECLARE(DBC::InsertRequest, dataBuilding.uid);
	DBCREQ_SET_KEY(dataBuilding.uid);
	DBCREQ_SET_INT(dataBuilding, uid);
	DBCREQ_SET_INT(dataBuilding, id);
	DBCREQ_SET_STR(dataBuilding, data);

	DBCREQ_EXEC;
	return 0;
}
// set
int CDataBuilding::SetBuilding(uint32_t uid, uint32_t id, const string& data)
{
	DB_ENCODE_BEGIN(DB_BUILDING, OP_UPDATE_BUILDING);
	DB_ENCODE(UInt32, uid);
	DB_ENCODE(UInt32, id);
	DB_ENCODE(String, data);
	DB_ENCODE_END;
	return 0;
}
int CDataBuilding::SetBuilding(const DataBuilding& dataBuilding)
{
	DB_ENCODE_BUILDING_SERIES(dataBuilding, OP_UPDATE_BUILDING)
	return 0;
}
int CDataBuilding::RealSetBuilding(CNetPacket* packet)
{
	DB_DECODE_BUILDING_SERIES(packet)

	DBCREQ_DECLARE(DBC::UpdateRequest, dataBuilding.uid);
	DBCREQ_SET_KEY(dataBuilding.uid);
	DBCREQ_SET_CONDITION(EQ, id, dataBuilding.id);
	DBCREQ_SET_STR(dataBuilding, data);
	DBCREQ_EXEC;
	return 0;
}
// replace
int CDataBuilding::ReplaceBuilding(const DataBuilding& dataBuilding)
{
	DB_ENCODE_BUILDING_SERIES(dataBuilding, OP_REPLACE_BUILDING)
	return 0;
}
int CDataBuilding::RealReplaceBuilding(CNetPacket* packet)
{
	DB_DECODE_BUILDING_SERIES(packet)

	DBCREQ_DECLARE(DBC::ReplaceRequest, dataBuilding.uid);
	DBCREQ_SET_KEY(dataBuilding.uid);
	DBCREQ_SET_INT(dataBuilding, id);
	DBCREQ_SET_STR(dataBuilding, data);
	DBCREQ_EXEC;
	return 0;
}
// remove one
int CDataBuilding::RemoveOneBuilding(unsigned uid, unsigned id)
{
	DB_ENCODE_BEGIN(DB_BUILDING, OP_REMOVE_ONE_BUILDING);
	DB_ENCODE(UInt32,uid);
	DB_ENCODE(UInt32,id);
	DB_ENCODE_END;
	return 0;
}
int CDataBuilding::RealRemoveOneBuilding(CNetPacket* packet)
{
	uint32_t uid = 0;
	uint32_t id = 0;
	DB_DECODE_BEGIN(&packet->body);
	DB_DECODE(UInt32, uid);
	DB_DECODE(UInt32, id);
	DB_DECODE_END;

	DBCREQ_DECLARE(DBC::DeleteRequest, uid);
	DBCREQ_SET_KEY(uid);
	DBCREQ_SET_CONDITION(EQ, id, id);
	DBCREQ_EXEC;
	return 0;
}
// remove all
int CDataBuilding::RemoveBuilding(unsigned uid)
{
	DB_ENCODE_BEGIN(DB_BUILDING, OP_REMOVE_BUILDING);
	DB_ENCODE(UInt32,uid);
	DB_ENCODE_END;
	return 0;
}
int CDataBuilding::RealRemoveBuilding(CNetPacket* packet)
{
	uint32_t uid = 0;
	DB_DECODE_BEGIN(&packet->body);
	DB_DECODE(UInt32, uid);
	DB_DECODE_END;

	DBCREQ_DECLARE(DBC::DeleteRequest, uid);
	DBCREQ_SET_KEY(uid);
	DBCREQ_EXEC;
	return 0;
}

///////////////////////
OP_PROCESS_BEGIN(CDataBuilding)
OP_PROCESS(OP_ADD_BUILDING, RealAddBuilding)
OP_PROCESS(OP_UPDATE_BUILDING, RealSetBuilding)
OP_PROCESS(OP_REPLACE_BUILDING, RealReplaceBuilding)
OP_PROCESS(OP_REMOVE_ONE_BUILDING, RealRemoveOneBuilding)
OP_PROCESS(OP_REMOVE_BUILDING, RealRemoveBuilding)
OP_PROCESS_END
*/
