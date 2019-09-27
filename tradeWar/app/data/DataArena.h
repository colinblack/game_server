/*
 * DataArena.h
 *
 *  Created on: 2019年2月27日
 *      Author: Administrator
 */

#ifndef DATA_ARENA_H_
#define DATA_ARENA_H_

#include "Kernel.h"
#include "AsyncDBInterface.h"

struct DataArena {
	uint32_t uid;
	uint32_t ts;
	uint32_t cd;             //挑战冷却时间
	uint16_t rank;           //历史最高排名
	uint8_t  energy;         //挑战次数
	uint8_t  buy_energy;     //购买次数
	uint8_t  shop_refresh;   //商店刷新次数
	string   shop;
	string   target;

	DataArena() {
		uid = 0;
		ts = 0;
		cd = 0;
		rank = 0;
		energy = 0;
		buy_energy = 0;
		shop_refresh = 0;
	}

	bool Encode(CBufferWriter &writer) const {
		PACKET_ENCODE(UInt32, uid);
		PACKET_ENCODE(UInt32, ts);
		PACKET_ENCODE(UInt32, cd);
		PACKET_ENCODE(UInt16, rank);
		PACKET_ENCODE(Byte, energy);
		PACKET_ENCODE(Byte, buy_energy);
		PACKET_ENCODE(Byte, shop_refresh);
		PACKET_ENCODE(String, shop);
		PACKET_ENCODE(String, target);
		return true;
	}

	bool Decode(CBufferReader &reader) {
		PACKET_DECODE(UInt32, uid);
		PACKET_DECODE(UInt32, ts);
		PACKET_DECODE(UInt32, cd);
		PACKET_DECODE(UInt16, rank);
		PACKET_DECODE(Byte, energy);
		PACKET_DECODE(Byte, buy_energy);
		PACKET_DECODE(Byte, shop_refresh);
		PACKET_DECODE(String, shop);
		PACKET_DECODE(String, target);
		return true;
	}
};

class CDataArena: public CDataBaseDBC, public AsyncDBInterface {
public:
	CDataArena(int table = DB_ARENA): CDataBaseDBC(table) {
	}
	~CDataArena(){
	}
	void doRequest(CNetPacket *p);
	int Get(uint32_t uid, DataArena &data);
	int Add(const DataArena &data);
	int Set(const DataArena &data);
	int Del(uint32_t uid);
	int Add(CNetPacket *p);
	int Set(CNetPacket *p);
	int Del(CNetPacket *p);
};

#endif /* DATA_ARENA_H_ */
