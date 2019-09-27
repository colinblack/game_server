/*
 * DataBoatTrain.h
 *
 *  Created on: 2018年11月8日
 *      Author: Administrator
 */

#ifndef DATA_BOAT_TRAIN_H_
#define DATA_BOAT_TRAIN_H_

#include "Kernel.h"
#include "AsyncDBInterface.h"

struct DataBoatTrain {
	uint32_t uid;
	uint32_t start_ts;
	uint32_t end_ts;
	uint32_t total_res;
	uint32_t lost_res;
	uint8_t used_count;
	uint8_t id;
	uint8_t level;
	uint8_t first;

	DataBoatTrain() {
		uid = 0;
		start_ts = 0;
		end_ts = 0;
		total_res = 0;
		lost_res = 0;
		used_count = 0;
		id = 0;
		level = 0;
		first = 0;
	}

	void Clean() {
		uid = 0;
		start_ts = 0;
		end_ts = 0;
		total_res = 0;
		lost_res = 0;
		used_count = 0;
		id = 0;
		level = 0;
	}

	DataBoatTrain& operator=(const DataBoatTrain &data) {
		uid = data.uid;
		start_ts = data.start_ts;
		end_ts = data.end_ts;
		total_res = data.total_res;
		lost_res = data.lost_res;
		used_count = data.used_count;
		id = data.id;
		level = data.level;
		first = data.first;
		return *this;
	}

	bool Encode(CBufferWriter &writer) const {
		PACKET_ENCODE(UInt32, uid);
		PACKET_ENCODE(UInt32, start_ts);
		PACKET_ENCODE(UInt32, end_ts);
		PACKET_ENCODE(UInt32, total_res);
		PACKET_ENCODE(UInt32, lost_res);
		PACKET_ENCODE(Byte, used_count);
		PACKET_ENCODE(Byte, id);
		PACKET_ENCODE(Byte, level);
		PACKET_ENCODE(Byte, first);
		return true;
	}

	bool Decode(CBufferReader &reader) {
		PACKET_DECODE(UInt32, uid);
		PACKET_DECODE(UInt32, start_ts);
		PACKET_DECODE(UInt32, end_ts);
		PACKET_DECODE(UInt32, total_res);
		PACKET_DECODE(UInt32, lost_res);
		PACKET_DECODE(Byte, used_count);
		PACKET_DECODE(Byte, id);
		PACKET_DECODE(Byte, level);
		PACKET_DECODE(Byte, first);
		return true;
	}
};

class CDataBoatTrain: public CDataBaseDBC, public AsyncDBInterface {
public:
	CDataBoatTrain(int table = DB_BOAT_TRAIN): CDataBaseDBC(table) {
	}
	virtual ~CDataBoatTrain() {
	}
	void doRequest(CNetPacket* p);

	int Add(const DataBoatTrain &data);
	int Set(const DataBoatTrain &data);
	int Get(uint32_t uid, vector<DataBoatTrain> &datas);
	int Get(uint32_t uid, uint8_t id, DataBoatTrain &data);
	int Del(uint32_t uid);

	int Add(CNetPacket *p);
	int Set(CNetPacket *p);
	int Del(CNetPacket *p);
};

#endif /* DATA_BOAT_TRAIN_H_ */
