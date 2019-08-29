#include "DataEquipment.h"
#include "AsyncDBManager.h"
TABLE_UID_ID_DATA_CXX(Equipment, EQUIPMENT)
/*
#define OP_ADD_EQUIPMENT 1
#define OP_UPDATE_EQUIPMENT 2
#define OP_REPLACE_EQUIPMENT 3
#define OP_REMOVE_ONE_EQUIPMENT 4
#define OP_REMOVE_EQUIPMENT 5

#define DB_ENCODE_EQUIPMENT_SERIES(dataEquipment, opId) \
	DB_ENCODE_BEGIN(DB_EQUIPMENT, opId); \
	DB_ENCODE(UInt32,dataEquipment.uid); \
	DB_ENCODE(UInt32,dataEquipment.id); \
	DB_ENCODE(String,dataEquipment.data); \
	DB_ENCODE_END;

#define DB_DECODE_EQUIPMENT_SERIES(packet) \
	DataEquipment dataEquipment; \
	DB_DECODE_BEGIN(&packet->body); \
	DB_DECODE(UInt32,dataEquipment.uid); \
	DB_DECODE(UInt32,dataEquipment.id); \
	DB_DECODE(String,dataEquipment.data); \
	DB_DECODE_END;

// get
int CDataEquipment::GetEquipment(unsigned uid, unsigned id, string &data)
{
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);
	DBCREQ_SET_CONDITION(EQ, id, id);

	DBCREQ_GET_STR_V(data);
	return 0;
}
// get all in vector
int CDataEquipment::GetEquipment(unsigned uid, vector<DataEquipment> &datas)
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
// add
int CDataEquipment::AddEquipment(const DataEquipment& dataEquipment)
{
	DB_ENCODE_EQUIPMENT_SERIES(dataEquipment, OP_ADD_EQUIPMENT)
	return 0;
}
int CDataEquipment::RealAddEquipment(CNetPacket* packet)
{
	DB_DECODE_EQUIPMENT_SERIES(packet)

	DBCREQ_DECLARE(DBC::InsertRequest, dataEquipment.uid);
	DBCREQ_SET_KEY(dataEquipment.uid);
	DBCREQ_SET_INT(dataEquipment, uid);
	DBCREQ_SET_INT(dataEquipment, id);
	DBCREQ_SET_STR(dataEquipment, data);

	DBCREQ_EXEC;
	return 0;
}
// set
int CDataEquipment::SetEquipment(uint32_t uid, uint32_t id, const string& data)
{
	DB_ENCODE_BEGIN(DB_EQUIPMENT, OP_UPDATE_EQUIPMENT);
	DB_ENCODE(UInt32, uid);
	DB_ENCODE(UInt32, id);
	DB_ENCODE(String, data);
	DB_ENCODE_END;
	return 0;
}
int CDataEquipment::SetEquipment(const DataEquipment& dataEquipment)
{
	DB_ENCODE_EQUIPMENT_SERIES(dataEquipment, OP_UPDATE_EQUIPMENT)
	return 0;
}
int CDataEquipment::RealSetEquipment(CNetPacket* packet)
{
	DB_DECODE_EQUIPMENT_SERIES(packet)

	DBCREQ_DECLARE(DBC::UpdateRequest, dataEquipment.uid);
	DBCREQ_SET_KEY(dataEquipment.uid);
	DBCREQ_SET_CONDITION(EQ, id, dataEquipment.id);
	DBCREQ_SET_STR(dataEquipment, data);
	DBCREQ_EXEC;
	return 0;
}
// replace
int CDataEquipment::ReplaceEquipment(const DataEquipment& dataEquipment)
{
	DB_ENCODE_EQUIPMENT_SERIES(dataEquipment, OP_REPLACE_EQUIPMENT)
	return 0;
}
int CDataEquipment::RealReplaceEquipment(CNetPacket* packet)
{
	DB_DECODE_EQUIPMENT_SERIES(packet)

	DBCREQ_DECLARE(DBC::ReplaceRequest, dataEquipment.uid);
	DBCREQ_SET_KEY(dataEquipment.uid);
	DBCREQ_SET_INT(dataEquipment, id);
	DBCREQ_SET_STR(dataEquipment, data);
	DBCREQ_EXEC;
	return 0;
}
// remove one
int CDataEquipment::RemoveOneEquipment(unsigned uid, unsigned id)
{
	DB_ENCODE_BEGIN(DB_EQUIPMENT, OP_REMOVE_ONE_EQUIPMENT);
	DB_ENCODE(UInt32,uid);
	DB_ENCODE(UInt32,id);
	DB_ENCODE_END;
	return 0;
}
int CDataEquipment::RealRemoveOneEquipment(CNetPacket* packet)
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
int CDataEquipment::RemoveEquipment(unsigned uid)
{
	DB_ENCODE_BEGIN(DB_EQUIPMENT, OP_REMOVE_EQUIPMENT);
	DB_ENCODE(UInt32,uid);
	DB_ENCODE_END;
	return 0;
}
int CDataEquipment::RealRemoveEquipment(CNetPacket* packet)
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
OP_PROCESS_BEGIN(CDataEquipment)
OP_PROCESS(OP_ADD_EQUIPMENT, RealAddEquipment)
OP_PROCESS(OP_UPDATE_EQUIPMENT, RealSetEquipment)
OP_PROCESS(OP_REPLACE_EQUIPMENT, RealReplaceEquipment)
OP_PROCESS(OP_REMOVE_ONE_EQUIPMENT, RealRemoveOneEquipment)
OP_PROCESS(OP_REMOVE_EQUIPMENT, RealRemoveEquipment)
OP_PROCESS_END
*/
