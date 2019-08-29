/*
 * DataRandomQuest.cpp
 *
 *  Created on: 2018年11月30日
 *      Author: Administrator
 */

#include "DataRandomQuest.h"
#include "AsyncDBManager.h"

enum {
	REQ_ADD = 1,
	REQ_SET = 2,
	REQ_DEL = 3
};

void CDataRandomQuest::doRequest(CNetPacket* packet) {
	switch (packet->stime) {
	case REQ_ADD:
		Add(packet);
		break;
	case REQ_SET:
		Set(packet);
		break;
	case REQ_DEL:
		Del(packet);
		break;
	}
}

int CDataRandomQuest::Get(uint32_t uid, vector<DataRandomQuest> &datas) {
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(quest);
	DBCREQ_NEED(ts);
	DBCREQ_NEED(id);
	DBCREQ_NEED(count);
	DBCREQ_NEED(reward1);
	DBCREQ_NEED(reward2);
	DBCREQ_NEED(soldier);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;

	DBCREQ_ARRAY_GET_BEGIN(datas);
	DBCREQ_ARRAY_GET_INT(datas, uid);
	DBCREQ_ARRAY_GET_INT(datas, quest);
	DBCREQ_ARRAY_GET_INT(datas, ts);
	DBCREQ_ARRAY_GET_INT(datas, id);
	DBCREQ_ARRAY_GET_INT(datas, count);
	DBCREQ_ARRAY_GET_INT(datas, reward1);
	DBCREQ_ARRAY_GET_INT(datas, reward2);
	DBCREQ_ARRAY_GET_INT(datas, soldier);
	DBCREQ_ARRAY_GET_END();

	return 0;
}

int CDataRandomQuest::Set(const DataRandomQuest &data) {
	DB_ENCODE_BEGIN(DB_RANDOM_QUEST, REQ_SET);
	if (!data.Encode(writer)) {
		return R_ERR_DATA;
	}
	DB_ENCODE_END;
	return 0;
}

int CDataRandomQuest::Add(const DataRandomQuest &data) {
	DB_ENCODE_BEGIN(DB_RANDOM_QUEST, REQ_ADD);
	if (!data.Encode(writer)) {
		return R_ERR_DATA;
	}
	DB_ENCODE_END;
	return 0;
}

int CDataRandomQuest::Del(uint32_t uid) {
	DataRandomQuest data;
	data.uid = uid;
	DB_ENCODE_BEGIN(DB_RANDOM_QUEST, REQ_DEL);
	if (!data.Encode(writer)) {
		return R_ERR_DATA;
	}
	DB_ENCODE_END;
	return 0;
}

int CDataRandomQuest::Set(CNetPacket* packet) {
	DataRandomQuest data;
	DB_DECODE_BEGIN(packet->GetBody());
	if (!data.Decode(reader)) {
		return R_ERR_DATA;
	}
	DBCREQ_DECLARE(DBC::UpdateRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_CONDITION(EQ, id, data.id);
	DBCREQ_SET_INT(data, quest);
	DBCREQ_SET_INT(data, ts);
	DBCREQ_SET_INT(data, count);
	DBCREQ_SET_INT(data, reward1);
	DBCREQ_SET_INT(data, reward2);
	DBCREQ_SET_INT(data, soldier);
	DBCREQ_EXEC;
	return 0;
}

int CDataRandomQuest::Add(CNetPacket* packet) {
	DataRandomQuest data;
	DB_DECODE_BEGIN(packet->GetBody());
	if (!data.Decode(reader)) {
		return R_ERR_DATA;
	}
	DBCREQ_DECLARE(DBC::InsertRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_INT(data, id);
	DBCREQ_SET_INT(data, quest);
	DBCREQ_SET_INT(data, ts);
	DBCREQ_SET_INT(data, count);
	DBCREQ_SET_INT(data, reward1);
	DBCREQ_SET_INT(data, reward2);
	DBCREQ_SET_INT(data, soldier);
	DBCREQ_EXEC;
	return 0;
}

int CDataRandomQuest::Del(CNetPacket* packet) {
	DataRandomQuest data;
	DB_DECODE_BEGIN(packet->GetBody());
	if (!data.Decode(reader)) {
		return R_ERR_DATA;
	}
	DBCREQ_DECLARE(DBC::DeleteRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_EXEC;
	return 0;
}
