/*
 * DataBoat.h
 *
 *  Created on: 2018年11月8日
 *      Author: Administrator
 */

#ifndef DATA_BOAT_H_
#define DATA_BOAT_H_

#include "Kernel.h"
#include "AsyncDBInterface.h"

struct DataBoat {
	uint32_t uid;
	uint32_t reset_ts;        // 重置时间
	uint32_t refresh_count;   // 刷新目标次数
	byte speed_up;            // 加速次数
	byte star;                // 掠夺星星
	byte star_reward;         // 掠夺星星奖励
	byte reset_flag;          // 钻石重置标记

	DataBoat() {
		uid = 0;
		reset_ts = 0;
		refresh_count = 0;
		speed_up = 0;
		star = 0;
		star_reward = 0;
		reset_flag = 0;
	}

	bool Encode(CBufferWriter &writer) const {
		PACKET_ENCODE(UInt32, uid);
		PACKET_ENCODE(UInt32, reset_ts);
		PACKET_ENCODE(UInt32, refresh_count);
		PACKET_ENCODE(Byte, speed_up);
		PACKET_ENCODE(Byte, star);
		PACKET_ENCODE(Byte, star_reward);
		PACKET_ENCODE(Byte, reset_flag);
		return true;
	}

	bool Decode(CBufferReader &reader) {
		PACKET_DECODE(UInt32, uid);
		PACKET_DECODE(UInt32, reset_ts);
		PACKET_DECODE(UInt32, refresh_count);
		PACKET_DECODE(Byte, speed_up);
		PACKET_DECODE(Byte, star);
		PACKET_DECODE(Byte, star_reward);
		PACKET_DECODE(Byte, reset_flag);
		return true;
	}
};

class CDataBoat: public CDataBaseDBC, public AsyncDBInterface {
public:
	CDataBoat(int table = DB_BOAT): CDataBaseDBC(table){
	}
	virtual ~CDataBoat(){
	}
	void doRequest(CNetPacket* p);

	int Add(const DataBoat &data);
	int Set(const DataBoat &data);
	int Get(uint32_t uid, DataBoat &data);
	int Del(uint32_t uid);

	int Add(CNetPacket *p);
	int Set(CNetPacket *p);
	int Del(CNetPacket *p);
};

#endif /* DATA_BOAT_H_ */
