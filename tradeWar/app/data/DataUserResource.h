/*
 * DataUserResource.h
 *
 *  Created on: 2015年9月9日
 *      Author: asdf
 */

#ifndef DATA_USER_RESOURCE_H_
#define DATA_USER_RESOURCE_H_

#include "Kernel.h"
#include "AsyncDBInterface.h"

struct MoneyCost {
	uint32_t cash;
	uint32_t coin;
	MoneyCost() {
		cash = 0;
		coin = 0;
	}
	MoneyCost(uint32_t _cash, uint32_t _coin) {
		cash = _cash;
		coin = _coin;
	}
};

struct DataUserResource {
	uint32_t uid;
	uint32_t r1;		//金币
	uint32_t r2;		//货物
	uint32_t r3;		//
	uint32_t r4;		//
	uint32_t tl;		//体力
	uint32_t p1;	 	//民心
	uint32_t p2;		//回收宝箱积分
	uint32_t p3;		//世界战争资源

	DataUserResource() {
		uid = 0;
		r1 = 0;
		r2 = 0;
		r3 = 0;
		r4 = 0;
		tl = 0;
		p1 = 0;
		p2 = 0;
		p3 = 0;
	}

	bool Encode(CBufferWriter &writer) const {
		PACKET_ENCODE(UInt32, uid);
		PACKET_ENCODE(UInt32, r1);
		PACKET_ENCODE(UInt32, r2);
		PACKET_ENCODE(UInt32, r3);
		PACKET_ENCODE(UInt32, r4);
		PACKET_ENCODE(UInt32, tl);
		PACKET_ENCODE(UInt32, p1);
		PACKET_ENCODE(UInt32, p2);
		PACKET_ENCODE(UInt32, p3);
		return true;
	}

	bool Decode(CBufferReader &reader) {
		PACKET_DECODE(UInt32, uid);
		PACKET_DECODE(UInt32, r1);
		PACKET_DECODE(UInt32, r2);
		PACKET_DECODE(UInt32, r3);
		PACKET_DECODE(UInt32, r4);
		PACKET_DECODE(UInt32, tl);
		PACKET_DECODE(UInt32, p1);
		PACKET_DECODE(UInt32, p2);
		PACKET_DECODE(UInt32, p3);
		return true;
	}
};

class CDataUserResource: public CDataBaseDBC, public AsyncDBInterface {
public:
	CDataUserResource(int table = DB_USER_RESOURCE): CDataBaseDBC(table) {
	}
	virtual void doRequest(CNetPacket *packet);
	int Get(uint32_t uid, DataUserResource &data);
	int Add(const DataUserResource &data);
	int Set(const DataUserResource &data);
	int Rep(const DataUserResource &data);
	int Del(uint32_t uid);

	int Add(CNetPacket *packet);
	int Set(CNetPacket *packet);
	int Rep(CNetPacket *packet);
	int Del(CNetPacket *packet);
};

#endif /* DATA_USER_RESOURCE_H_ */
