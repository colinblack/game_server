/*
 * DataTreasure.h
 *
 *  Created on: 2019年7月1日
 *  Author: next
 */

#ifndef _DATA_TREASURE_H_
#define _DATA_TREASURE_H_

#include "Kernel.h"

struct DataTreasure {
	uint32_t uid;
	byte type;
	byte level;
	byte star;
	uint32_t bless;
	uint16_t dan1;
	uint16_t dan2;

	DataTreasure() {
		uid = 0;
		type = 0;
		level = 0;
		star = 0;
		bless = 0;
		dan1 = 0;
		dan2 = 0;
	}

	const uint16_t* GetDan(uint32_t id) const {
		switch(id) {
		case 0:
			return &dan1;
		case 1:
			return &dan2;
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
		default:
			return NULL;
		}
	}

	bool Encode(IBuffer *buff) const {
		PACKET_ENCODE_BEGIN(buff);
		PACKET_ENCODE(UInt32, uid);
		PACKET_ENCODE(Byte, type);
		PACKET_ENCODE(Byte, level);
		PACKET_ENCODE(Byte, star);
		PACKET_ENCODE(UInt32, bless);
		PACKET_ENCODE(UInt16, dan1);
		PACKET_ENCODE(UInt16, dan2);
		return true;
	}

	bool Decode(IBuffer *buff) {
		PACKET_DECODE_BEGIN(buff);
		PACKET_DECODE(UInt32, uid);
		PACKET_DECODE(Byte, type);
		PACKET_DECODE(Byte, level);
		PACKET_DECODE(Byte, star);
		PACKET_DECODE(UInt32, bless);
		PACKET_DECODE(UInt16, dan1);
		PACKET_DECODE(UInt16, dan2);
		return true;
	}
};

class CDataTreasure: public CDataBaseDBC {
public:
	CDataTreasure(int table = DB_TREASURE):CDataBaseDBC(table) {
	}
	int AddData(const DataTreasure &data);
	int SetData(const DataTreasure &data);
	int RepData(const DataTreasure &data);
	int DelData(const DataTreasure &data);
	int GetData(uint32_t uid, DataTreasure &data);
	int GetData(uint32_t uid, vector<DataTreasure> &datas);
};

#endif /*_DATA_TREASURE_H_*/
