/*
 * DataActivity.h
 *
 *  Created on: 2018年12月3日
 *      Author: Administrator
 */

#ifndef DATA_ACTIVITY_H_
#define DATA_ACTIVITY_H_

#include "Kernel.h"
#include "AsyncDBInterface.h"

#define ACTIVITY_DATA_LEN 15

struct DataActivity {
	uint32_t uid;
	uint32_t id;
	uint32_t ver;
	uint32_t ts;
	uint32_t score;
	uint32_t flag;

	DataActivity() {
		uid = 0;
		id = 0;
		ver = 0;
		ts = 0;
		score = 0;
		flag = 0;
	}

	void Clear() {
		flag = 0;
		score = 0;
	}

	bool Encode(CBufferWriter &writer) const {
		PACKET_ENCODE(UInt32, uid);
		PACKET_ENCODE(UInt32, id);
		PACKET_ENCODE(UInt32, ver);
		PACKET_ENCODE(UInt32, score);
		PACKET_ENCODE(UInt32, ts);
		PACKET_ENCODE(UInt32, flag);
		return true;
	}

	bool Decode(CBufferReader &reader) {
		PACKET_DECODE(UInt32, uid);
		PACKET_DECODE(UInt32, id);
		PACKET_DECODE(UInt32, ver);
		PACKET_DECODE(UInt32, score);
		PACKET_DECODE(UInt32, ts);
		PACKET_DECODE(UInt32, flag);
		return true;
	}
};

class CDataActivity: public CDataBaseDBC, public AsyncDBInterface {
public:
	CDataActivity(int table = DB_ACTIVITY): CDataBaseDBC(table) {
	}
	void doRequest(CNetPacket *p);
	int Add(const DataActivity &data);
	int Set(const DataActivity &data);
	int Get(uint32_t uid, uint32_t id, DataActivity &data);
	int Get(uint32_t uid, vector<DataActivity> &datas);
	int Del(uint32_t uid);

	int Add(CNetPacket *p);
	int Set(CNetPacket *p);
	int Del(CNetPacket *p);

	int TestAdd(const DataActivity &data);
	int TestSet(const DataActivity &data);
};

#endif /* DATA_ACTIVITY_H_ */
