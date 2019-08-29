/*
 * DataArenaLog.h
 *
 *  Created on: 2019年2月27日
 *      Author: Administrator
 */

#ifndef DATA_ARENA_LOG_H_
#define DATA_ARENA_LOG_H_

#include "Kernel.h"
#include "AsyncDBInterface.h"

struct DataArenaLog {
	uint32_t uid;
	uint32_t ts;
	uint32_t userid;
	uint16_t from_rank;
	uint16_t to_rank;
	uint8_t win;
	uint8_t type;
	uint8_t userlevel;
	string username;
	string pic;
	string soldier;
	string tower;
	string soldier_dead;
	string skill;

	DataArenaLog() {
		uid = 0;
		ts = 0;
		userid = 0;
		from_rank = 0;
		to_rank = 0;
		win = 0;
		type = 0;
		userlevel = 0;
		username.clear();
		pic.clear();
		soldier.clear();
		tower.clear();
		soldier_dead.clear();
		skill.clear();
	}

	bool Encode(CBufferWriter &writer) const {
		PACKET_ENCODE(UInt32, uid);
		PACKET_ENCODE(UInt32, ts);
		PACKET_ENCODE(UInt32, userid);
		PACKET_ENCODE(UInt16, from_rank);
		PACKET_ENCODE(UInt16, to_rank);
		PACKET_ENCODE(Byte, win);
		PACKET_ENCODE(Byte, type);
		PACKET_ENCODE(Byte, userlevel);
		PACKET_ENCODE(String, username);
		PACKET_ENCODE(String, pic);
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
		PACKET_DECODE(UInt16, from_rank);
		PACKET_DECODE(UInt16, to_rank);
		PACKET_DECODE(Byte, win);
		PACKET_DECODE(Byte, type);
		PACKET_DECODE(Byte, userlevel);
		PACKET_DECODE(String, username);
		PACKET_DECODE(String, pic);
		PACKET_DECODE(String, soldier);
		PACKET_DECODE(String, tower);
		PACKET_DECODE(String, soldier_dead);
		PACKET_DECODE(String, skill);
		return true;
	}
};

class CDataArenaLog: public CDataBaseDBC, public AsyncDBInterface {
public:
	CDataArenaLog(int table = DB_ARENA_LOG): CDataBaseDBC(table) {
	}
	~CDataArenaLog() {
	}
	void doRequest(CNetPacket *p);
	int Get(uint32_t uid, vector<DataArenaLog> &datas);
	int Add(const DataArenaLog &data);
	int Set(const DataArenaLog &data);
	int Del(uint32_t uid, uint32_t ts);
	int Add(CNetPacket *p);
	int Set(CNetPacket *p);
	int Del(CNetPacket *p);
};

#endif /* DATA_ARENA_LOG_H_ */
