/*
 * DataBoatRobLog.h
 *
 *  Created on: 2018年8月24日
 *      Author: rein
 */

#ifndef DATA_BOAT_ROB_LOG_H_
#define DATA_BOAT_ROB_LOG_H_

#include "Kernel.h"
#include "AsyncDBInterface.h"

struct DataBoatRobLog {
	uint32_t uid;
	uint32_t ts;
	uint32_t userid;
	uint32_t res;
	uint32_t exp;
	byte type;
	byte win;
	byte star;
	byte damage;
	byte train_id;
	byte revenge_count;
	string username;
	string soldier;
	string tower;
	string soldier_dead;
	string skill;

	DataBoatRobLog() {
		uid = 0;
		ts = 0;
		userid = 0;
		res = 0;
		exp = 0;
		type = 0;
		win = 0;
		star = 0;
		damage = 0;
		train_id = 0;
		revenge_count = 0;
	}

	bool Encode(CBufferWriter &writer) const {
		PACKET_ENCODE(UInt32, uid);
		PACKET_ENCODE(UInt32, ts);
		PACKET_ENCODE(UInt32, userid);
		PACKET_ENCODE(UInt32, res);
		PACKET_ENCODE(UInt32, exp);
		PACKET_ENCODE(Byte, type);
		PACKET_ENCODE(Byte, win);
		PACKET_ENCODE(Byte, star);
		PACKET_ENCODE(Byte, damage);
		PACKET_ENCODE(Byte, train_id);
		PACKET_ENCODE(Byte, revenge_count);
		PACKET_ENCODE(String, username);
		PACKET_ENCODE(String, soldier);
		PACKET_ENCODE(String, tower);
		PACKET_ENCODE(String, soldier_dead);
		PACKET_ENCODE(String, skill);
		return true;
	}

	bool Decode(CBufferReader &reader) {
		PACKET_DECODE(UInt32, uid);
		PACKET_DECODE(UInt32, ts);
		PACKET_DECODE(UInt32, userid);
		PACKET_DECODE(UInt32, res);
		PACKET_DECODE(UInt32, exp);
		PACKET_DECODE(Byte, type);
		PACKET_DECODE(Byte, win);
		PACKET_DECODE(Byte, star);
		PACKET_DECODE(Byte, damage);
		PACKET_DECODE(Byte, train_id);
		PACKET_DECODE(Byte, revenge_count);
		PACKET_DECODE(String, username);
		PACKET_DECODE(String, soldier);
		PACKET_DECODE(String, tower);
		PACKET_DECODE(String, soldier_dead);
		PACKET_DECODE(String, skill);
		return true;
	}
};

enum BOAT_ROB_RESULT {
	BOAT_ROB_RESULT_WIN = 1,
	BOAT_ROB_RESULT_LOST = 2
};
enum BOAT_ROB_LOG_STATUS {
	BOAT_ROB_LOG_STATUS_ATT = 1,
	BOAT_ROB_LOG_STATUS_DEF = 2
};

DECLARE_DBC_DATA_CLASS(CDataBoatRobLog, DB_BOAT_ROB_LOG)
	int Add(const DataBoatRobLog &data);
	int Get(uint32_t uid, vector<DataBoatRobLog> &datas);
	int GetLimit(uint32_t uid, vector<DataBoatRobLog> &datas);
	int Get(uint32_t uid, uint32_t ts, DataBoatRobLog &data);
	int GetRevengeCount(uint32_t uid, uint32_t ts, byte &revenge_count);
	int SetRevengeCount(uint32_t uid, uint32_t ts, byte revenge_count);
	int Set(const DataBoatRobLog &data);
	int Del(uint32_t uid, uint32_t ts);

	virtual void doRequest(CNetPacket *packet);
	int RealAdd(CNetPacket *packet);
	int RealSet(CNetPacket *packet);
	int RealDel(CNetPacket *packet);
	int RealSetRevengeCount(CNetPacket *packet);
DECLARE_DBC_DATA_CLASS_END

#endif /* DATA_BOAT_ROB_LOG_H_ */
