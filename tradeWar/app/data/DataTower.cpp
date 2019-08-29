/*
 * DataTower.cpp
 *
 *  Created on: 2018年8月1日
 *      Author: rein
 */

#include "DataTower.h"
#include "AsyncDBManager.h"

#define OP_ADD_TOWER 1
#define OP_SET_TOWER 2
#define OP_DEL_TOWER 3

int CDataTower::AddTower(const DataTower& data) {
	DB_ENCODE_BEGIN(DB_TOWER, OP_ADD_TOWER);
	DB_ENCODE(UInt32, data.uid);
	DB_ENCODE(UInt32, data.id);
	DB_ENCODE(UInt32, data.level);;
	DB_ENCODE_END;

	return 0;
}
int CDataTower::GetTowers(uint32_t uid, vector<DataTower>& datas) {
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(id);
	DBCREQ_NEED(level);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;

	DBCREQ_ARRAY_GET_BEGIN(datas);
	DBCREQ_ARRAY_GET_INT(datas, uid);
	DBCREQ_ARRAY_GET_INT(datas, id);
	DBCREQ_ARRAY_GET_INT(datas, level);
	DBCREQ_ARRAY_GET_END();

	return 0;
}
int CDataTower::SetTower(const DataTower& data) {
	DB_ENCODE_BEGIN(DB_TOWER, OP_SET_TOWER);
	DB_ENCODE(UInt32, data.uid);
	DB_ENCODE(UInt32, data.id);
	DB_ENCODE(UInt32, data.level);;
	DB_ENCODE_END;

	return 0;
}
int CDataTower::DelTower(uint32_t uid) {
	DB_ENCODE_BEGIN(DB_TOWER, OP_DEL_TOWER);
	DB_ENCODE(UInt32, uid);
	DB_ENCODE_END;

	return 0;
}
int CDataTower::RealAddTower(CNetPacket *packet) {
	DataTower tower;
	DB_DECODE_BEGIN(&packet->body);
	DB_DECODE(UInt32, tower.uid);
	DB_DECODE(UInt32, tower.id);
	DB_DECODE(UInt32, tower.level);
	DB_DECODE_END;

	DBCREQ_DECLARE(DBC::InsertRequest, tower.uid);
	DBCREQ_SET_KEY(tower.uid);
	DBCREQ_SET_INT(tower, id);
	DBCREQ_SET_INT(tower, level);
	DBCREQ_EXEC;

	return 0;
}
int CDataTower::RealSetTower(CNetPacket *packet) {
	DataTower tower;
	DB_DECODE_BEGIN(&packet->body);
	DB_DECODE(UInt32, tower.uid);
	DB_DECODE(UInt32, tower.id);
	DB_DECODE(UInt32, tower.level);
	DB_DECODE_END;

	DBCREQ_DECLARE(DBC::UpdateRequest, tower.uid);
	DBCREQ_SET_KEY(tower.uid);
	DBCREQ_SET_CONDITION(EQ, id, tower.id);

	DBCREQ_SET_INT(tower, level);
	DBCREQ_EXEC;

	return 0;
}
int CDataTower::RealDelTower(CNetPacket *packet) {
	DataTower tower;
	DB_DECODE_BEGIN(&packet->body);
	DB_DECODE(UInt32, tower.uid);
	DB_DECODE_END;

	DBCREQ_DECLARE(DBC::DeleteRequest, tower.uid);
	DBCREQ_SET_KEY(tower.uid);
	DBCREQ_EXEC;

	return 0;
}

OP_PROCESS_BEGIN(CDataTower)
OP_PROCESS(OP_ADD_TOWER, RealAddTower)
OP_PROCESS(OP_SET_TOWER, RealSetTower)
OP_PROCESS(OP_DEL_TOWER, RealDelTower)
OP_PROCESS_END

