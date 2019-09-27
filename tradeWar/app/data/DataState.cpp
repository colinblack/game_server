/*
 * DataState.cpp
 *
 *  Created on: 2015年12月11日
 *      Author: asdf
 */

#include "DataState.h"
#include "AsyncDBManager.h"

const uint32_t OP_ADD_STATE = 1101;
const uint32_t OP_UPDATE_STATE = 1102;
const uint32_t OP_REPLACE_STATE = 1103;
const uint32_t OP_REMOVE_ONE_STATE = 1104;
const uint32_t OP_REMOVE_STATE = 1105;

#define DB_ENCODE_STATE_SERIES(opId) \
	DB_ENCODE_BEGIN(DB_STATE, opId); \
	DB_ENCODE(UInt32,uid); \
	DB_ENCODE(UInt32,id); \
	DB_ENCODE(String,data); \
	DB_ENCODE_END;

#define DB_ENCODE_STATE_STRUCT_SERIES(opId) \
	DB_ENCODE_BEGIN(DB_STATE, opId); \
	DB_ENCODE(UInt32,dataState.uid); \
	DB_ENCODE(UInt32,dataState.id); \
	DB_ENCODE(String,dataState.data); \
	DB_ENCODE_END;

#define DB_DECODE_STATE_SERIES() \
	DataState dataState; \
	DB_DECODE_BEGIN(&packet->body); \
	DB_DECODE(UInt32,dataState.uid); \
	DB_DECODE(UInt32,dataState.id); \
	DB_DECODE(String,dataState.data); \
	DB_DECODE_END;


map<uint32_t, uint32_t> CDataState::m_stat;

int CDataState::GetState(uint32_t uid, uint32_t id, string &data)
{
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);
	DBCREQ_SET_CONDITION(EQ, id, id);
	DBCREQ_GET_STR_V(data);
	return 0;
}

int CDataState::GetStates(uint32_t uid, vector<DataState>& vState)
{
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(id);
	DBCREQ_NEED(data);
	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;

	DBCREQ_ARRAY_GET_BEGIN(vState);
	DBCREQ_ARRAY_GET_INT(vState, uid);
	DBCREQ_ARRAY_GET_INT(vState, id);
	DBCREQ_ARRAY_GET_STR(vState, data);
	DBCREQ_ARRAY_GET_END();
	return 0;
}
int CDataState::AddState(uint32_t uid, uint32_t id, const string& data)
{
	DB_ENCODE_STATE_SERIES(OP_ADD_STATE)
	return 0;
}
int CDataState::AddState(const DataState& dataState)
{
	DB_ENCODE_STATE_STRUCT_SERIES(OP_ADD_STATE)
	return 0;
}
int CDataState::RealAddState(CNetPacket* packet)
{
	DB_DECODE_STATE_SERIES()
	DBCREQ_DECLARE(DBC::InsertRequest, dataState.uid);
	DBCREQ_SET_KEY(dataState.uid);
	DBCREQ_SET_INT(dataState, id);
	DBCREQ_SET_STR(dataState, data);
	DBCREQ_EXEC;
	return 0;
}

int CDataState::addStateSync(const DataState& dataState)
{
	DBCREQ_DECLARE(DBC::InsertRequest, dataState.uid);
	DBCREQ_SET_KEY(dataState.uid);
	DBCREQ_SET_INT(dataState, id);
	DBCREQ_SET_STR(dataState, data);
	DBCREQ_EXEC;
	return 0;
}

int CDataState::SetState(uint32_t uid, uint32_t id, const string& data)
{
	if(m_stat.find(id) == m_stat.end())
	{
		m_stat[id] = 0;
	}
	m_stat[id]++;

	DB_ENCODE_STATE_SERIES(OP_UPDATE_STATE)
	return 0;
}
int CDataState::SetState(const DataState& dataState)
{
	if(m_stat.find(dataState.id) == m_stat.end())
	{
		m_stat[dataState.id] = 0;
	}
	m_stat[dataState.id]++;

	DB_ENCODE_STATE_STRUCT_SERIES(OP_UPDATE_STATE)
	return 0;
}
int CDataState::RealSetState(CNetPacket* packet)
{
	DB_DECODE_STATE_SERIES()
	DBCREQ_DECLARE(DBC::UpdateRequest, dataState.uid);
	DBCREQ_SET_KEY(dataState.uid);
	DBCREQ_SET_CONDITION(EQ, id, dataState.id);
	DBCREQ_SET_STR(dataState, data);
	DBCREQ_EXEC;
	return 0;
}

int CDataState::setStateSync(const DataState& dataState)
{
	DBCREQ_DECLARE(DBC::UpdateRequest, dataState.uid);
	DBCREQ_SET_KEY(dataState.uid);
	DBCREQ_SET_CONDITION(EQ, id, dataState.id);
	DBCREQ_SET_STR(dataState, data);
	DBCREQ_EXEC;
	return 0;
}


int CDataState::ReplaceState(uint32_t uid, uint32_t id, const string& data)
{
	DB_ENCODE_STATE_SERIES(OP_REPLACE_STATE)
	return 0;
}

int CDataState::ReplaceState(const DataState& dataState)
{
	DB_ENCODE_STATE_STRUCT_SERIES(OP_REPLACE_STATE)
	return 0;
}

int CDataState::RealReplaceState(CNetPacket* packet)
{
	DB_DECODE_STATE_SERIES()
	DBCREQ_DECLARE(DBC::ReplaceRequest, dataState.uid);
	DBCREQ_SET_KEY(dataState.uid);
	DBCREQ_SET_INT(dataState, id);
	DBCREQ_SET_STR(dataState, data);
	DBCREQ_EXEC;
	return 0;
}

int CDataState::RemoveOneState(uint32_t uid, uint32_t id)
{
	DB_ENCODE_BEGIN(DB_STATE, OP_REMOVE_ONE_STATE);
	DB_ENCODE(UInt32, uid);
	DB_ENCODE(UInt32, id);
	DB_ENCODE_END;
	return 0;
}

int CDataState::RealRemoveOneState(CNetPacket* packet)
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

int CDataState::RemoveState(uint32_t uid)
{
	DB_ENCODE_BEGIN(DB_STATE, OP_REMOVE_STATE);
	DB_ENCODE(UInt32, uid);
	DB_ENCODE_END;
	return 0;
}

int CDataState::RealRemoveState(CNetPacket* packet)
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

OP_PROCESS_BEGIN(CDataState)
OP_PROCESS(OP_ADD_STATE, RealAddState)
OP_PROCESS(OP_UPDATE_STATE, RealSetState)
OP_PROCESS(OP_REPLACE_STATE, RealReplaceState)
OP_PROCESS(OP_REMOVE_ONE_STATE, RealRemoveOneState)
OP_PROCESS(OP_REMOVE_STATE, RealRemoveState)
OP_PROCESS_END


bool CDataState::printStat()
{
	if(m_stat.size() == 300 || Time::GetGlobalTime() % 300 == 0) // 五分钟打一次日志
	{
		info_log("state_data_stat_head statSize=%u", m_stat.size());
		for(map<uint32_t, uint32_t>::iterator iter = m_stat.begin(); iter != m_stat.end(); ++iter)
		{
			info_log("state_data_stat id=%u count=%u", iter->first, iter->second);
		}
		m_stat.clear();
	}
	return true;
}
