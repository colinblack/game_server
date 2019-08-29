/*
 * DataSocial.h
 *
 *  Created on: 2016-5-26
 *      Author: Administrator
 */

#ifndef DATASOCIAL_H_
#define DATASOCIAL_H_

#include "Kernel.h"
#include "AsyncDBInterface.h"

struct DataSocial {
	uint32_t uid;
	uint32_t other_uid;
	uint32_t update_time;
	string pic;

	DataSocial(): uid(0), other_uid(0), update_time(0) {
	}

	bool Encode(CBufferWriter &writer) const {
		PACKET_ENCODE(UInt32, uid);
		PACKET_ENCODE(UInt32, other_uid);
		PACKET_ENCODE(UInt32, update_time);
		PACKET_ENCODE(String, pic);
		return true;
	}

	bool Decode(CBufferReader &reader) {
		PACKET_DECODE(UInt32, uid);
		PACKET_DECODE(UInt32, other_uid);
		PACKET_DECODE(UInt32, update_time);
		PACKET_DECODE(String, pic);
		return true;
	}

	bool operator <(const DataSocial & next) const {
		return this->update_time > next.update_time;
	}

	bool operator ==(uint32_t next) const {
		return this->other_uid == next;
	}
};

class CDataSocial: public CDataBaseDBC, public AsyncDBInterface {
public:
	CDataSocial(int table = DB_SOCIAL) : CDataBaseDBC(table) {
	}
	virtual ~CDataSocial() {
	}
	virtual void doRequest(CNetPacket* packet);

	int Add(const DataSocial &data);
	int Set(const DataSocial &data);
	int Get(uint32_t uid, vector<DataSocial> &datas);
	int Get(uint32_t uid, uint32_t other_uid, DataSocial &data);
	int Del(unsigned uid);

	int Add(CNetPacket* packet);
	int Set(CNetPacket* packet);
	int Del(CNetPacket* packet);
};

#endif /* DATASOCIAL_H_ */
