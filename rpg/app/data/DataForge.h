/*
 * DataForge.h
 *
 *  Created on: 2019年7月3日
 *      Author: Administrator
 */

#ifndef DATA_FORGE_H_
#define DATA_FORGE_H_

#include "Kernel.h"

struct DataForge {
	uint32_t uid;
	byte rid;
	byte type;
	uint16_t strength;
	uint32_t purify;
	uint32_t zhulingLevel;
	uint32_t zhulingAdvance;
	string extend;

	DataForge() {
		uid = 0;
		rid = 0;
		type = 0;
		strength = 0;
		purify = 0;
		zhulingLevel = 0;
		zhulingAdvance = 0;
		extend.clear();
	}

	bool operator ==(const DataForge &oth) {
		return uid == oth.uid && rid == oth.rid && type == oth.type;
	}

	bool Encode(IBuffer *buff) const {
		PACKET_ENCODE_BEGIN(buff);
		PACKET_ENCODE(UInt32, uid);
		PACKET_ENCODE(Byte, rid);
		PACKET_ENCODE(Byte, type);
		PACKET_ENCODE(UInt16, strength);
		PACKET_ENCODE(UInt32, purify);
		PACKET_ENCODE(UInt32, zhulingLevel);
		PACKET_ENCODE(UInt32, zhulingAdvance);
		PACKET_ENCODE(String, extend);
		return true;
	}

	bool Decode(IBuffer *buff) {
		PACKET_DECODE_BEGIN(buff);
		PACKET_DECODE(UInt32, uid);
		PACKET_DECODE(Byte, rid);
		PACKET_DECODE(Byte, type);
		PACKET_DECODE(UInt16, strength);
		PACKET_DECODE(UInt32, purify);
		PACKET_DECODE(UInt32, zhulingLevel);
		PACKET_DECODE(UInt32, zhulingAdvance);
		PACKET_DECODE(String, extend);
		return true;
	}
};

class CDataForge: public CDataBaseDBC {
public:
	CDataForge(int table = DB_FORGE) : CDataBaseDBC(table) {
	}
	int AddData(const DataForge &data);
	int SetData(const DataForge &data);
	int RepData(const DataForge &data);
	int DelData(const DataForge &data);
	int GetData(uint32_t uid, DataForge &data);
	int GetData(uint32_t uid, vector<DataForge> &datas);
};

#endif /* DATA_FORGE_H_ */
