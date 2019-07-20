/*
 * DataActive.h
 *
 *  Created on: 2019年7月16日
 *  Author: next
 */

#ifndef _DATA_ACTIVE_H_
#define _DATA_ACTIVE_H_

#include "Kernel.h"

enum RewardSize {
	ACTIVE_REWARD_1    = 0,
	ACTIVE_REWARD_2    = 1,
	ACTIVE_REWARD_3    = 2,
	ACTIVE_REWARD_4    = 3,
	ACTIVE_REWARD_5    = 4,
	ACTIVE_REWARD_SIZE = 5
};

struct DataActiveEtr {
	uint32_t uid;
	uint32_t day_active;
	uint32_t week_active;
	uint32_t ts;
	uint8_t reward[ACTIVE_REWARD_SIZE];
};

//每日&周活跃度
struct DataActive {
	uint32_t uid;
	uint32_t day_active;
	uint32_t week_active;
	uint32_t ts;
	uint8_t reward_1;
	uint8_t reward_2;
	uint8_t reward_3;
	uint8_t reward_4;
	uint8_t reward_5;

	DataActive() {
		uid = 0;
		day_active = 0;
		week_active = 0;
		ts = 0;
		reward_1 = 0;
		reward_2 = 0;
		reward_3 = 0;
		reward_4 = 0;
		reward_5 = 0;
	}

	bool Encode(IBuffer *buff) const {
		PACKET_ENCODE_BEGIN(buff);
		PACKET_ENCODE(UInt32, uid);
		PACKET_ENCODE(UInt32, day_active);
		PACKET_ENCODE(UInt32, week_active);
		PACKET_ENCODE(UInt32, ts);
		PACKET_ENCODE(Byte, reward_1);
		PACKET_ENCODE(Byte, reward_2);
		PACKET_ENCODE(Byte, reward_3);
		PACKET_ENCODE(Byte, reward_4);
		PACKET_ENCODE(Byte, reward_5);
		return true;
	}

	bool Decode(IBuffer *buff) {
		PACKET_DECODE_BEGIN(buff);
		PACKET_DECODE(UInt32, uid);
		PACKET_DECODE(UInt32, day_active);
		PACKET_DECODE(UInt32, week_active);
		PACKET_DECODE(UInt32, ts);
		PACKET_DECODE(Byte, reward_1);
		PACKET_DECODE(Byte, reward_2);
		PACKET_DECODE(Byte, reward_3);
		PACKET_DECODE(Byte, reward_4);
		PACKET_DECODE(Byte, reward_5);
		return true;
	}
};

class CDataActive: public CDataBaseDBC {
public:
	CDataActive(int table = DB_ACTIVE):CDataBaseDBC(table) {
	}
	int AddData(const DataActive &data);
	int SetData(const DataActive &data);
	int RepData(const DataActive &data);
	int DelData(const DataActive &data);
	int GetData(uint32_t uid, DataActive &data);
	int GetData(uint32_t uid, vector<DataActive> &datas);
};

#endif /*_DATA_ACTIVE_H_*/
