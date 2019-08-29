/*
 * DataUserInteract.h
 *
 *  Created on: 2019年3月5日
 *      Author: Administrator
 */

#ifndef DATA_USER_INTERACT_H_
#define DATA_USER_INTERACT_H_

#include "Kernel.h"
#include "AsyncDBInterface.h"

struct DataUserInteract {
	uint32_t uid;
	uint32_t ouid;
	uint32_t ts;
	byte level;
	byte help_type;
	string username;
	string pic;

	DataUserInteract() {
		uid = 0;
		ouid = 0;
		ts = 0;
		level = 0;
		help_type = 0;
		username.clear();
		pic.clear();
	}

	bool Encode(CBufferWriter &writer) const {
		PACKET_ENCODE(UInt32, uid);
		PACKET_ENCODE(UInt32, ouid);
		PACKET_ENCODE(UInt32, ts);
		PACKET_ENCODE(Byte,   level);
		PACKET_ENCODE(Byte,   help_type);
		PACKET_ENCODE(String, username);
		PACKET_ENCODE(String, pic);
		return true;
	}

	bool Decode(CBufferReader &reader) {
		PACKET_DECODE(UInt32, uid);
		PACKET_DECODE(UInt32, ouid);
		PACKET_DECODE(UInt32, ts);
		PACKET_DECODE(Byte,   level);
		PACKET_DECODE(Byte,   help_type);
		PACKET_DECODE(String, username);
		PACKET_DECODE(String, pic);
		return true;
	}
};

class CDataUserInteract: public CDataBaseDBC, public AsyncDBInterface {
public:
	CDataUserInteract(int table = DB_USER_INTERACT): CDataBaseDBC(table) {
	}
	void doRequest(CNetPacket *packet);
	int Get(uint32_t uid, uint32_t ouid, DataUserInteract &data);
	int Get(uint32_t uid, vector<DataUserInteract> &datas);
	int Add(const DataUserInteract &data);
	int Set(const DataUserInteract &data);
	int Del(uint32_t uid, uint32_t ouid, uint32_t ts);
	int Add(CNetPacket *packet);
	int Set(CNetPacket *packet);
	int Del(CNetPacket *packet);
};

#endif /* APP_DATA_DATAUSERINTERACT_H_ */
