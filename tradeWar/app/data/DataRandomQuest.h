/*
 * DataRandomQuest.h
 *
 *  Created on: 2018年11月30日
 *      Author: Administrator
 */

#ifndef DATA_RANDOM_QUEST_H_
#define DATA_RANDOM_QUEST_H_

#include "Kernel.h"
#include "AsyncDBInterface.h"

struct DataRandomQuest {
	uint8_t id;
	uint8_t count;
	uint32_t uid;
	uint32_t quest;
	uint32_t ts;
	uint32_t reward1;
	uint32_t reward2;
	uint32_t soldier;
	bool sync;

	DataRandomQuest() {
		id = 0;
		count = 0;
		uid = 0;
		quest = 0;
		ts = 0;
		reward1 = 0;
		reward2 = 0;
		soldier = 0;
		sync = false;
	}

	inline bool operator==(byte id) const {
		return this->id == id;
	}

	bool Encode(CBufferWriter &writer) const {
		PACKET_ENCODE(UInt32, uid);
		PACKET_ENCODE(UInt32, quest);
		PACKET_ENCODE(UInt32, ts);
		PACKET_ENCODE(UInt32, reward1);
		PACKET_ENCODE(UInt32, reward2);
		PACKET_ENCODE(UInt32, soldier);
		PACKET_ENCODE(Byte, id);
		PACKET_ENCODE(Byte, count);
		return true;
	}

	bool Decode(CBufferReader &reader) {
		PACKET_DECODE(UInt32, uid);
		PACKET_DECODE(UInt32, quest);
		PACKET_DECODE(UInt32, ts);
		PACKET_DECODE(UInt32, reward1);
		PACKET_DECODE(UInt32, reward2);
		PACKET_DECODE(UInt32, soldier);
		PACKET_DECODE(Byte, id);
		PACKET_DECODE(Byte, count);
		return true;
	}
};

class CDataRandomQuest: public CDataBaseDBC, public AsyncDBInterface {
public:
	CDataRandomQuest(int table = DB_RANDOM_QUEST) : CDataBaseDBC(table) {
	}
	virtual void doRequest(CNetPacket* packet);
	int Get(uint32_t uid, vector<DataRandomQuest> &datas);
	int Set(const DataRandomQuest &data);
	int Add(const DataRandomQuest &data);
	int Del(uint32_t uid);

	int Set(CNetPacket* packet);
	int Add(CNetPacket* packet);
	int Del(CNetPacket* packet);
};

#endif /* DATA_RANDOM_QUEST_H_ */
