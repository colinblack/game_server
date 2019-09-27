/*
 * DataGemPoint.h
 *
 *  Created on: 2019年1月4日
 *      Author: Administrator
 */

#ifndef DATA_GEM_POINT_H_
#define DATA_GEM_POINT_H_

#include "Kernel.h"
#include "AsyncDBInterface.h"

struct DataGemPoint {
	uint32_t uid;
	uint32_t id;
	uint32_t p1;
	uint32_t p2;
	uint32_t p3;
	uint32_t p4;

	DataGemPoint() {
		uid = 0;
		id = 0;
		p1 = 0;
		p2 = 0;
		p3 = 0;
		p4 = 0;
	}

	bool Encode(CBufferWriter &writer) const {
		PACKET_ENCODE(UInt32, uid);
		PACKET_ENCODE(UInt32, id);
		PACKET_ENCODE(UInt32, p1);
		PACKET_ENCODE(UInt32, p2);
		PACKET_ENCODE(UInt32, p3);
		PACKET_ENCODE(UInt32, p4);
		return true;
	}

	bool Decode(CBufferReader &reader) {
		PACKET_DECODE(UInt32, uid);
		PACKET_DECODE(UInt32, id);
		PACKET_DECODE(UInt32, p1);
		PACKET_DECODE(UInt32, p2);
		PACKET_DECODE(UInt32, p3);
		PACKET_DECODE(UInt32, p4);
		return true;
	}
};
class CDataGemPoint: public CDataBaseDBC, public AsyncDBInterface {
public:
	CDataGemPoint(int table = DB_GEM_POINT): CDataBaseDBC(table) {
	}
	void doRequest(CNetPacket* p);
	int Get(uint32_t uid, uint32_t id, DataGemPoint &data);
	int Get(uint32_t uid, vector<DataGemPoint> &data);
	int Add(const DataGemPoint &data);
	int Set(const DataGemPoint &data);
	int Del(const DataGemPoint &data);
	int Add(CNetPacket* p);
	int Set(CNetPacket* p);
	int Del(CNetPacket* p);
};

#endif /* DATA_GEM_POINT_H_ */
