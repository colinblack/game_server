/*
 * DataAdvance.h
 *
 *  Created on: 2019年6月22日
 *      Author: Administrator
 */

#ifndef DATA_ADVANCE_H_
#define DATA_ADVANCE_H_

#include "Kernel.h"

struct DataAdvance {
	uint32_t uid;
	byte rid;
	byte type;
	uint32_t bless;
	uint32_t tmp_bless;
	byte star;
	byte level;
	byte last_level;
	uint16_t dan1;
	uint16_t dan2;
	uint16_t dan3;
	uint16_t dan4;

	DataAdvance() {
		uid = 0;
		rid = 0;
		type = 0;
		bless = 0;
		tmp_bless = 0;
		star = 0;
		level = 0;
		last_level = 0;
		dan1 = 0;
		dan2 = 0;
		dan3 = 0;
		dan4 = 0;
	}

	const uint16_t* GetDan(uint32_t id) const {
		switch (id) {
		case 0:
			return &dan1;
		case 1:
			return &dan2;
		case 2:
			return &dan3;
		case 3:
			return &dan4;
		default:
			return NULL;
		}
	}

	uint16_t* GetDan(uint32_t id) {
		switch (id) {
		case 0:
			return &dan1;
		case 1:
			return &dan2;
		case 2:
			return &dan3;
		case 3:
			return &dan4;
		default:
			return NULL;
		}
	}

	bool Encode(IBuffer *buff) const {
		PACKET_ENCODE_BEGIN(buff);
		PACKET_ENCODE(UInt32, uid);
		PACKET_ENCODE(Byte, rid);
		PACKET_ENCODE(Byte, type);
		PACKET_ENCODE(UInt32, bless);
		PACKET_ENCODE(UInt32, tmp_bless);
		PACKET_ENCODE(Byte, star);
		PACKET_ENCODE(Byte, level);
		PACKET_ENCODE(Byte, last_level);
		PACKET_ENCODE(UInt16, dan1);
		PACKET_ENCODE(UInt16, dan2);
		PACKET_ENCODE(UInt16, dan3);
		PACKET_ENCODE(UInt16, dan4);
		return true;
	}

	bool Decode(IBuffer *buff) {
		PACKET_DECODE_BEGIN(buff);
		PACKET_DECODE(UInt32, uid);
		PACKET_DECODE(Byte, rid);
		PACKET_DECODE(Byte, type);
		PACKET_DECODE(UInt32, bless);
		PACKET_DECODE(UInt32, tmp_bless);
		PACKET_DECODE(Byte, star);
		PACKET_DECODE(Byte, level);
		PACKET_DECODE(Byte, last_level);
		PACKET_DECODE(UInt16, dan1);
		PACKET_DECODE(UInt16, dan2);
		PACKET_DECODE(UInt16, dan3);
		PACKET_DECODE(UInt16, dan4);
		return true;
	}
};

class CDataAdvance: public CDataBaseDBC {
public:
	CDataAdvance(int table = DB_ADVANCE): CDataBaseDBC(table) {
	}
	int AddData(const DataAdvance &data);
	int SetData(const DataAdvance &data);
	int RepData(const DataAdvance &data);
	int DelData(const DataAdvance &data);
	int GetData(uint32_t uid, DataAdvance &data);
	int GetData(uint32_t uid, vector<DataAdvance> &datas);
};

#endif /* DATA_ADVANCE_H_ */
