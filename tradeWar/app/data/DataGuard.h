/*
 * DataGuard.h
 *
 *  Created on: 2019年3月15日
 *      Author: Administrator
 */

#ifndef DATA_GUARD_H_
#define DATA_GUARD_H_

#include "Kernel.h"
#include "AsyncDBInterface.h"

struct DataGuard {
	uint32_t uid;
	uint32_t id;
	uint32_t soldier;

	DataGuard() {
		uid = 0;
		id = 0;
		soldier = 0;
	}

	bool Encode(CBufferWriter &writer) const {
		PACKET_ENCODE(UInt32, uid);
		PACKET_ENCODE(UInt32, id);
		PACKET_ENCODE(UInt32, soldier);
		return true;
	}

	bool Decode(CBufferReader &reader) {
		PACKET_DECODE(UInt32, uid);
		PACKET_DECODE(UInt32, id);
		PACKET_DECODE(UInt32, soldier);
		return true;
	}
};

class CDataGuard: public CDataBaseDBC, public AsyncDBInterface {
public:
	CDataGuard(int table = DB_GUARD): CDataBaseDBC(table) {
	}
	virtual ~CDataGuard() {
	}
	void doRequest(CNetPacket *p);

	int Get(uint32_t uid, vector<DataGuard> &datas);
	int Add(const DataGuard &data);
	int Set(const DataGuard &data);
	int Del(uint32_t uid, uint32_t id);

	int Add(CNetPacket *p);
	int Set(CNetPacket *p);
	int Del(CNetPacket *p);
};

#endif /* DATA_GUARD_H_ */
