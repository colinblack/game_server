/*
 * DataAttr.h
 *
 *  Created on: 2019年6月27日
 *      Author: Administrator
 */

#ifndef DATA_ATTR_H_
#define DATA_ATTR_H_

#include "Kernel.h"

struct DataAttr {
	uint32_t uid;
	uint32_t type;
	uint32_t id;
	uint32_t v1;
	uint32_t v2;
	uint32_t v3;
	uint32_t v4;
	uint32_t v5;
	uint32_t v6;
	uint32_t v7;
	uint32_t v8;
	uint32_t v9;
	uint32_t v10;
	DataAttr() {
		uid = 0;
		type =0;
		id = 0;
		v1 = 0;
		v2 = 0;
		v3 = 0;
		v4 = 0;
		v5 = 0;
		v6 = 0;
		v7 = 0;
		v8 = 0;
		v9 = 0;
		v10 = 0;
	}
	const uint32_t* GetPos(uint32_t id) const {
		switch (id) {
		case 0:
			return &v1;
		case 1:
			return &v2;
		case 2:
			return &v3;
		case 3:
			return &v4;
		case 4:
			return &v5;
		case 5:
			return &v6;
		case 6:
			return &v7;
		case 7:
			return &v8;
		case 8:
			return &v9;
		case 9:
			return &v10;
		default:
			return NULL;
		}
	}

	uint32_t* GetPos(uint32_t id) {
		switch (id) {
		case 0:
			return &v1;
		case 1:
			return &v2;
		case 2:
			return &v3;
		case 3:
			return &v4;
		case 4:
			return &v5;
		case 5:
			return &v6;
		case 6:
			return &v7;
		case 7:
			return &v8;
		case 8:
			return &v9;
		case 9:
			return &v10;
		default:
			return NULL;
		}
	}

	void ClearAttr() {
		v1 = v2 = v3 = v4 = v5 = v6 = v7= v8= v9= v10= 0;
	}

	bool Encode(IBuffer *buff) const {
		PACKET_ENCODE_BEGIN(buff);
		PACKET_ENCODE(UInt32, uid);
		PACKET_ENCODE(UInt32, type);
		PACKET_ENCODE(UInt32, id);
		PACKET_ENCODE(UInt32, v1);
		PACKET_ENCODE(UInt32, v2);
		PACKET_ENCODE(UInt32, v3);
		PACKET_ENCODE(UInt32, v4);
		PACKET_ENCODE(UInt32, v5);
		PACKET_ENCODE(UInt32, v6);
		PACKET_ENCODE(UInt32, v7);
		PACKET_ENCODE(UInt32, v8);
		PACKET_ENCODE(UInt32, v9);
		PACKET_ENCODE(UInt32, v10);
		return true;
	}

	bool Decode(IBuffer *buff) {
		PACKET_DECODE_BEGIN(buff);
		PACKET_DECODE(UInt32, uid);
		PACKET_DECODE(UInt32, type);
		PACKET_DECODE(UInt32, id);
		PACKET_DECODE(UInt32, v1);
		PACKET_DECODE(UInt32, v2);
		PACKET_DECODE(UInt32, v3);
		PACKET_DECODE(UInt32, v4);
		PACKET_DECODE(UInt32, v5);
		PACKET_DECODE(UInt32, v6);
		PACKET_DECODE(UInt32, v7);
		PACKET_DECODE(UInt32, v8);
		PACKET_DECODE(UInt32, v9);
		PACKET_DECODE(UInt32, v10);
		return true;
	}
};

class CDataAttr: public CDataBaseDBC {
public:
	CDataAttr(int table = DB_ATTR) : CDataBaseDBC(table) {
	}
	int AddData(const DataAttr &data);
	int SetData(const DataAttr &data);
	int RepData(const DataAttr &data);
	int DelData(const DataAttr &data);
	int GetData(uint32_t uid,DataAttr &data);
	int GetData(uint32_t uid, vector<DataAttr> &datas);
};

#endif /* DATA_ATTR_H_ */
