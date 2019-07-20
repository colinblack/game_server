/*
 * DataMission.h
 *
 *  Created on: 2019年6月20日
 *      Author: Administrator
 */

#ifndef DATA_MISSION_H_
#define DATA_MISSION_H_

#include "Kernel.h"

struct DataMission {
	uint32_t uid;
	uint32_t id;
	uint32_t ts;
	byte step;
	byte status;
	string extend;

	DataMission() {
		uid = 0;
		id = 0;
		ts = 0;
		step = 0;
		status = 0;
		extend.clear();
	}

	bool Encode(IBuffer *buff) const {
		PACKET_ENCODE_BEGIN(buff);
		PACKET_ENCODE(UInt32, uid);
		PACKET_ENCODE(UInt32, id);
		PACKET_ENCODE(UInt32, ts);
		PACKET_ENCODE(Byte, step);
		PACKET_ENCODE(Byte, status);
		PACKET_ENCODE(String, extend);
		return true;
	}

	bool Decode(IBuffer *buff) {
		PACKET_DECODE_BEGIN(buff);
		PACKET_DECODE(UInt32, uid);
		PACKET_DECODE(UInt32, id);
		PACKET_DECODE(UInt32, ts);
		PACKET_DECODE(Byte, step);
		PACKET_DECODE(Byte, status);
		PACKET_DECODE(String, extend);
		return true;
	}
};

class CDataMission: public CDataBaseDBC {
public:
	CDataMission(int table = DB_MISSION): CDataBaseDBC(table) {
	}
	~CDataMission() {
	}
	int AddData(const DataMission &data);
	int SetData(const DataMission &data);
	int RepData(const DataMission &data);
	int DelData(const DataMission &data);
	int GetData(uint32_t uid, DataMission &data);
	int GetData(uint32_t uid, vector<DataMission> &datas);
};

#endif /* DATA_MISSION_H_ */
