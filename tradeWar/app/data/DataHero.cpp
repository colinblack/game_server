#include "DataHero.h"
#include "AsyncDBManager.h"
TABLE_UID_ID_DATA_CXX(Hero, HERO)

/*
#define OP_ADD_HERO 1
#define OP_UPDATE_HERO 2
#define OP_REPLACE_HERO 3
#define OP_REMOVE_ONE_HERO 4
#define OP_REMOVE_HERO 5

#define DB_ENCODE_HERO_SERIES(dataHero, opId) \
	DB_ENCODE_BEGIN(DB_HERO, opId); \
	DB_ENCODE(UInt32,dataHero.uid); \
	DB_ENCODE(UInt32,dataHero.id); \
	DB_ENCODE(String,dataHero.data); \
	DB_ENCODE_END;

#define DB_DECODE_HERO_SERIES(packet) \
	DataHero dataHero; \
	DB_DECODE_BEGIN(&packet->body); \
	DB_DECODE(UInt32,dataHero.uid); \
	DB_DECODE(UInt32,dataHero.id); \
	DB_DECODE(String,dataHero.data); \
	DB_DECODE_END;

// get
int CDataHero::GetHero(unsigned uid, unsigned id, string &data)
{
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);
	DBCREQ_SET_CONDITION(EQ, id, id);

	DBCREQ_GET_STR_V(data);
	return 0;
}
// get all in vector
int CDataHero::GetHero(unsigned uid, vector<DataHero> &datas)
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
int CDataHero::GetHero(unsigned uid, map<unsigned, string> &datas)
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
int CDataHero::AddHero(const DataHero& dataHero)
{
	DB_ENCODE_HERO_SERIES(dataHero, OP_ADD_HERO)
	return 0;
}
int CDataHero::RealAddHero(CNetPacket* packet)
{
	DB_DECODE_HERO_SERIES(packet)

	DBCREQ_DECLARE(DBC::InsertRequest, dataHero.uid);
	DBCREQ_SET_KEY(dataHero.uid);
	DBCREQ_SET_INT(dataHero, uid);
	DBCREQ_SET_INT(dataHero, id);
	DBCREQ_SET_STR(dataHero, data);

	DBCREQ_EXEC;
	return 0;
}
// set
int CDataHero::SetHero(uint32_t uid, uint32_t id, const string& data)
{
	DB_ENCODE_BEGIN(DB_HERO, OP_UPDATE_HERO);
	DB_ENCODE(UInt32, uid);
	DB_ENCODE(UInt32, id);
	DB_ENCODE(String, data);
	DB_ENCODE_END;
	return 0;
}
int CDataHero::SetHero(const DataHero& dataHero)
{
	DB_ENCODE_HERO_SERIES(dataHero, OP_UPDATE_HERO)
	return 0;
}
int CDataHero::RealSetHero(CNetPacket* packet)
{
	DB_DECODE_HERO_SERIES(packet)

	DBCREQ_DECLARE(DBC::UpdateRequest, dataHero.uid);
	DBCREQ_SET_KEY(dataHero.uid);
	DBCREQ_SET_CONDITION(EQ, id, dataHero.id);
	DBCREQ_SET_STR(dataHero, data);
	DBCREQ_EXEC;
	return 0;
}
// replace
int CDataHero::ReplaceHero(const DataHero& dataHero)
{
	DB_ENCODE_HERO_SERIES(dataHero, OP_REPLACE_HERO)
	return 0;
}
int CDataHero::RealReplaceHero(CNetPacket* packet)
{
	DB_DECODE_HERO_SERIES(packet)

	DBCREQ_DECLARE(DBC::ReplaceRequest, dataHero.uid);
	DBCREQ_SET_KEY(dataHero.uid);
	DBCREQ_SET_INT(dataHero, id);
	DBCREQ_SET_STR(dataHero, data);
	DBCREQ_EXEC;
	return 0;
}
// remove one
int CDataHero::RemoveOneHero(unsigned uid, unsigned id)
{
	DB_ENCODE_BEGIN(DB_HERO, OP_REMOVE_ONE_HERO);
	DB_ENCODE(UInt32,uid);
	DB_ENCODE(UInt32,id);
	DB_ENCODE_END;
	return 0;
}
int CDataHero::RealRemoveOneHero(CNetPacket* packet)
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
int CDataHero::RemoveHero(unsigned uid)
{
	DB_ENCODE_BEGIN(DB_HERO, OP_REMOVE_HERO);
	DB_ENCODE(UInt32,uid);
	DB_ENCODE_END;
	return 0;
}
int CDataHero::RealRemoveHero(CNetPacket* packet)
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
OP_PROCESS_BEGIN(CDataHero)
OP_PROCESS(OP_ADD_HERO, RealAddHero)
OP_PROCESS(OP_UPDATE_HERO, RealSetHero)
OP_PROCESS(OP_REPLACE_HERO, RealReplaceHero)
OP_PROCESS(OP_REMOVE_ONE_HERO, RealRemoveOneHero)
OP_PROCESS(OP_REMOVE_HERO, RealRemoveHero)
OP_PROCESS_END
*/
