/*
 * DataShenQi.h
 *
 *  Created on: 2019年6月27日
 *      Author: Administrator
 */

#ifndef DATA_SHENQI_H_
#define DATA_SHENQI_H_

#include "Kernel.h"

struct DataShenQi {
	uint32_t uid;
	byte id;
	uint32_t p1;
	uint32_t p2;
	uint32_t p3;
	uint32_t p4;
	uint32_t p5;
	uint32_t p6;

	DataShenQi() {
		uid = 0;
		id = 0;
		p1 = 0;
		p2 = 0;
		p3 = 0;
		p4 = 0;
		p5 = 0;
		p6 = 0;
	}

	const uint32_t* GetPiece(uint32_t id) const {
		switch (id) {
		case 0:
			return &p1;
		case 1:
			return &p2;
		case 2:
			return &p3;
		case 3:
			return &p4;
		case 4:
			return &p5;
		case 5:
			return &p6;
		default:
			return NULL;
		}
	}

	uint32_t* GetPiece(uint32_t id) {
		switch (id) {
		case 0:
			return &p1;
		case 1:
			return &p2;
		case 2:
			return &p3;
		case 3:
			return &p4;
		case 4:
			return &p5;
		case 5:
			return &p6;
		default:
			return NULL;
		}
	}

	void ClearPiece() {
		p1 = p2 = p3 = p4 = p5 = p6 = 0;
	}

	bool Encode(IBuffer *buff) const {
		PACKET_ENCODE_BEGIN(buff);
		PACKET_ENCODE(UInt32, uid);
		PACKET_ENCODE(Byte,   id);
		PACKET_ENCODE(UInt32, p1);
		PACKET_ENCODE(UInt32, p2);
		PACKET_ENCODE(UInt32, p3);
		PACKET_ENCODE(UInt32, p4);
		PACKET_ENCODE(UInt32, p5);
		PACKET_ENCODE(UInt32, p6);
		return true;
	}

	bool Decode(IBuffer *buff) {
		PACKET_DECODE_BEGIN(buff);
		PACKET_DECODE(UInt32, uid);
		PACKET_DECODE(Byte,   id);
		PACKET_DECODE(UInt32, p1);
		PACKET_DECODE(UInt32, p2);
		PACKET_DECODE(UInt32, p3);
		PACKET_DECODE(UInt32, p4);
		PACKET_DECODE(UInt32, p5);
		PACKET_DECODE(UInt32, p6);
		return true;
	}
};

class CDataShenQi: public CDataBaseDBC {
public:
	CDataShenQi(int table = DB_SHENQI) : CDataBaseDBC(table) {
	}
	int AddData(const DataShenQi &data);
	int SetData(const DataShenQi &data);
	int RepData(const DataShenQi &data);
	int DelData(const DataShenQi &data);
	int GetData(uint32_t uid, DataShenQi &data);
	int GetData(uint32_t uid, vector<DataShenQi> &datas);
};

#endif /* DATA_SHENQI_H_ */
