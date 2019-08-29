/*
 * DataTableUidIdData.h
 *
 *  Created on: 2015年9月9日
 *      Author: asdf
 */

#ifndef SERVERS_APP_DATA_DATATABLEUIDIDDATA_H_
#define SERVERS_APP_DATA_DATATABLEUIDIDDATA_H_

#include "Kernel.h"
#include "AsyncDBInterface.h"

// 数据结构定义
#define DECLARE_STRUCT(TN) \
struct Data##TN \
{ \
	uint32_t uid; \
	uint32_t id; \
	string   data; \
};

// 类声明
#define DECLARE_CLASS(TN, MACRO) \
class CData##TN : public CDataBaseDBC, public AsyncDBInterface \
{ \
public: \
	CData##TN(int table = DB_##MACRO) : CDataBaseDBC(table) {} \
	virtual void doRequest(CNetPacket* packet); \
	int Get##TN(uint32_t uid, map<uint32_t, string> &datas); \
	int Get##TN(uint32_t uid, uint32_t id, string &data); \
	int Get##TN(uint32_t uid, vector<Data##TN> &datas); \
	int Add##TN(uint32_t uid, uint32_t id, const string &data); \
	int Add##TN(const Data##TN& data##TN); \
	int RealAdd##TN(CNetPacket* packet); \
	int Set##TN(uint32_t uid, uint32_t id, const string &data); \
	int Set##TN(const Data##TN& data##TN); \
	int RealSet##TN(CNetPacket* packet); \
	int Replace##TN(uint32_t uid, uint32_t id, const string &data); \
	int Replace##TN(const Data##TN& data##TN); \
	int RealReplace##TN(CNetPacket* packet); \
	int RemoveOne##TN(uint32_t uid, uint32_t id); \
	int RealRemoveOne##TN(CNetPacket* packet); \
	int Remove##TN(uint32_t uid); \
	int RealRemove##TN(CNetPacket* packet); \
};



// 定义数据操作类型
#define DEFINE_OP_SERIES(MACRO) \
	const uint32_t OP_ADD_##MACRO = 1101; \
	const uint32_t OP_UPDATE_##MACRO = 1102; \
	const uint32_t OP_REPLACE_##MACRO = 1103; \
	const uint32_t OP_REMOVE_ONE_##MACRO = 1104; \
	const uint32_t OP_REMOVE_##MACRO = 1105;

// encode
#define DB_ENCODE_SERIES_VAR(MACRO, opId) \
	DB_ENCODE_BEGIN(DB_##MACRO, opId); \
	DB_ENCODE(UInt32,uid); \
	DB_ENCODE(UInt32,id); \
	DB_ENCODE(String,data); \
	DB_ENCODE_END;

#define DB_ENCODE_SERIES(TN, MACRO, opId) \
	DB_ENCODE_BEGIN(DB_##MACRO, opId); \
	DB_ENCODE(UInt32,data##TN.uid); \
	DB_ENCODE(UInt32,data##TN.id); \
	DB_ENCODE(String,data##TN.data); \
	DB_ENCODE_END;

// decode
#define DB_DECODE_SERIES(TN) \
	Data##TN data##TN; \
	DB_DECODE_BEGIN(&packet->body); \
	DB_DECODE(UInt32,data##TN.uid); \
	DB_DECODE(UInt32,data##TN.id); \
	DB_DECODE(String,data##TN.data); \
	DB_DECODE_END;


// get
#define GET_ITEM(TN) \
int CData##TN::Get##TN(uint32_t uid, uint32_t id, string &data) \
{ \
	DBCREQ_DECLARE(DBC::GetRequest, uid); \
	DBCREQ_SET_KEY(uid); \
	DBCREQ_SET_CONDITION(EQ, id, id); \
	DBCREQ_GET_STR_V(data); \
	return 0; \
}
// get all in vector
#define GET_ITEM_VEC(TN) \
int CData##TN::Get##TN(uint32_t uid, vector<Data##TN> &datas) \
{ \
	DBCREQ_DECLARE(DBC::GetRequest, uid); \
	DBCREQ_SET_KEY(uid); \
	DBCREQ_NEED_BEGIN(); \
	DBCREQ_NEED(uid); \
	DBCREQ_NEED(id); \
	DBCREQ_NEED(data); \
	DBCREQ_EXEC; \
	DBCREQ_ARRAY_GET_BEGIN(datas); \
	DBCREQ_ARRAY_GET_INT(datas, uid); \
	DBCREQ_ARRAY_GET_INT(datas, id); \
	DBCREQ_ARRAY_GET_STR(datas, data); \
	DBCREQ_ARRAY_GET_END(); \
	return 0; \
}

// get all in map
#define GET_ITEM_MAP(TN) \
int CData##TN::Get##TN(uint32_t uid, map<uint32_t, string> &datas) \
{ \
	DBCREQ_DECLARE(DBC::GetRequest, uid); \
	DBCREQ_SET_KEY(uid); \
	DBCREQ_NEED_BEGIN(); \
	DBCREQ_NEED(id); \
	DBCREQ_NEED(data); \
	DBCREQ_EXEC; \
	datas.clear(); \
	int count = m_dbcret.TotalRows(); \
	for(int i = 0; i < count; i++) \
	{ \
		DBCREQ_IFFETCHROW; \
		datas[m_dbcret.IntValue(1)] = m_dbcret.StringValue(2); \
	} \
	return 0; \
}

// add
#define ADD_ITEM(TN, MACRO) \
int CData##TN::Add##TN(uint32_t uid, uint32_t id, const string& data) \
{ \
	DB_ENCODE_SERIES_VAR(MACRO, OP_ADD_##MACRO) \
	return 0; \
}

#define ADD_ITEM_STRUCT(TN, MACRO) \
int CData##TN::Add##TN(const Data##TN& data##TN) \
{ \
	DB_ENCODE_SERIES(TN, MACRO, OP_ADD_##MACRO) \
	return 0; \
}

#define REAL_ADD_ITEM(TN, MACRO) \
int CData##TN::RealAdd##TN(CNetPacket* packet) \
{ \
	DB_DECODE_SERIES(TN) \
	DBCREQ_DECLARE(DBC::InsertRequest, data##TN.uid); \
	DBCREQ_SET_KEY(data##TN.uid); \
	DBCREQ_SET_INT(data##TN, id); \
	DBCREQ_SET_STR(data##TN, data); \
	DBCREQ_EXEC; \
	return 0; \
}

// set
#define SET_ITEM(TN, MACRO) \
int CData##TN::Set##TN(uint32_t uid, uint32_t id, const string& data) \
{ \
	DB_ENCODE_SERIES_VAR(MACRO, OP_UPDATE_##MACRO) \
	return 0; \
}

#define SET_ITEM_STRUCT(TN, MACRO) \
int CData##TN::Set##TN(const Data##TN& data##TN) \
{ \
	DB_ENCODE_SERIES(TN, MACRO, OP_UPDATE_##MACRO) \
	return 0; \
}

#define REAL_SET_ITEM(TN, MACRO) \
int CData##TN::RealSet##TN(CNetPacket* packet) \
{ \
	DB_DECODE_SERIES(TN) \
	DBCREQ_DECLARE(DBC::UpdateRequest, data##TN.uid); \
	DBCREQ_SET_KEY(data##TN.uid); \
	DBCREQ_SET_CONDITION(EQ, id, data##TN.id); \
	DBCREQ_SET_STR(data##TN, data); \
	DBCREQ_EXEC; \
	return 0; \
}
// replace
#define REPLACE_ITEM(TN, MACRO) \
int CData##TN::Replace##TN(uint32_t uid, uint32_t id, const string& data) \
{ \
	DB_ENCODE_SERIES_VAR(MACRO, OP_REPLACE_##MACRO) \
	return 0; \
}

#define REPLACE_ITEM_STRUCT(TN, MACRO) \
int CData##TN::Replace##TN(const Data##TN& data##TN) \
{ \
	DB_ENCODE_SERIES(TN, MACRO, OP_REPLACE_##MACRO) \
	return 0; \
}

#define REAL_REPLACE_ITEM(TN, MACRO) \
int CData##TN::RealReplace##TN(CNetPacket* packet) \
{ \
	DB_DECODE_SERIES(TN) \
	DBCREQ_DECLARE(DBC::ReplaceRequest, data##TN.uid); \
	DBCREQ_SET_KEY(data##TN.uid); \
	DBCREQ_SET_INT(data##TN, id); \
	DBCREQ_SET_STR(data##TN, data); \
	DBCREQ_EXEC; \
	return 0; \
}

// 根据两个key删除记录
#define REMOVE_ONE_ITEM_KEY2(TN, MACRO, type1, var1, type2, var2) \
int CData##TN::RemoveOne##TN(uint32_t var1, uint32_t var2) \
{ \
	DB_ENCODE_BEGIN(DB_##MACRO, OP_REMOVE_ONE_##MACRO); \
	DB_ENCODE(type1, var1); \
	DB_ENCODE(type2, var2); \
	DB_ENCODE_END; \
	return 0; \
}

// 根据两个key删除记录
#define REAL_REMOVE_ONE_ITEM_KEY2(TN, type1, var1, type2, var2) \
int CData##TN::RealRemoveOne##TN(CNetPacket* packet) \
{ \
	uint32_t var1 = 0; \
	uint32_t var2 = 0; \
	DB_DECODE_BEGIN(&packet->body); \
	DB_DECODE(type1, var1); \
	DB_DECODE(type2, var2); \
	DB_DECODE_END; \
	DBCREQ_DECLARE(DBC::DeleteRequest, var1); \
	DBCREQ_SET_KEY(var1); \
	DBCREQ_SET_CONDITION(EQ, var2, var2); \
	DBCREQ_EXEC; \
	return 0; \
}

// 根据一个key删除记录
#define REMOVE_ITEM_KEY1(TN, MACRO, type1, var1) \
int CData##TN::Remove##TN(uint32_t var1) \
{ \
	DB_ENCODE_BEGIN(DB_##MACRO, OP_REMOVE_##MACRO); \
	DB_ENCODE(type1,var1); \
	DB_ENCODE_END; \
	return 0; \
}

// 根据一个key删除记录
#define REAL_REMOVE_ITEM_KEY1(TN, type1, var1) \
int CData##TN::RealRemove##TN(CNetPacket* packet) \
{ \
	uint32_t var1 = 0; \
	DB_DECODE_BEGIN(&packet->body); \
	DB_DECODE(type1, var1); \
	DB_DECODE_END; \
	DBCREQ_DECLARE(DBC::DeleteRequest, var1); \
	DBCREQ_SET_KEY(var1); \
	DBCREQ_EXEC; \
	return 0; \
}

// 处理请求
#define OP_PROCESS_SERIES(TN, MACRO) \
	OP_PROCESS_BEGIN(CData##TN) \
	OP_PROCESS(OP_ADD_##MACRO, RealAdd##TN) \
	OP_PROCESS(OP_UPDATE_##MACRO, RealSet##TN) \
	OP_PROCESS(OP_REPLACE_##MACRO, RealReplace##TN) \
	OP_PROCESS(OP_REMOVE_ONE_##MACRO, RealRemoveOne##TN) \
	OP_PROCESS(OP_REMOVE_##MACRO, RealRemove##TN) \
	OP_PROCESS_END


// 类定义
#define DEFINE_CLASS(TN, MACRO) \
	GET_ITEM(TN) \
	GET_ITEM_VEC(TN) \
	GET_ITEM_MAP(TN) \
	ADD_ITEM(TN, MACRO) \
	ADD_ITEM_STRUCT(TN, MACRO) \
	REAL_ADD_ITEM(TN, MACRO) \
	SET_ITEM(TN, MACRO) \
	SET_ITEM_STRUCT(TN, MACRO) \
	REAL_SET_ITEM(TN, MACRO) \
	REPLACE_ITEM(TN, MACRO) \
	REPLACE_ITEM_STRUCT(TN, MACRO) \
	REAL_REPLACE_ITEM(TN, MACRO) \
	REMOVE_ONE_ITEM_KEY2(TN, MACRO, UInt32, uid, UInt32, id) \
	REAL_REMOVE_ONE_ITEM_KEY2(TN, UInt32, uid, UInt32, id) \
	REMOVE_ITEM_KEY1(TN, MACRO, UInt32, uid) \
	REAL_REMOVE_ITEM_KEY1(TN, UInt32, uid) \
	OP_PROCESS_SERIES(TN, MACRO)


// 定义头文件
#define TABLE_UID_ID_DATA_HEAD(TN, MACRO) \
	DECLARE_STRUCT(TN) \
	DECLARE_CLASS(TN, MACRO)

// 定义实现文件
#define TABLE_UID_ID_DATA_CXX(TN, MACRO) \
	DEFINE_OP_SERIES(MACRO) \
	DEFINE_CLASS(TN, MACRO)
	

#endif /* SERVERS_APP_DATA_DATATABLEUIDIDDATA_H_ */

