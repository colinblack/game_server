/*
 * DataEquip.h
 *
 *  Created on: 2019年6月25日
 *      Author: Administrator
 */

#ifndef DATA_EQUIP_H_
#define DATA_EQUIP_H_

#include "Kernel.h"

struct DataEquip {
	uint32_t uid;
	uint32_t ud;
	uint32_t id;
	uint32_t num;
	uint32_t ts;
	uint16_t bag;
	string ext;

	DataEquip() {
		uid = 0;
		ud = 0;
		id = 0;
		num = 0;
		ts = 0;
		bag = 0;
		ext.clear();
	}

	bool Encode(IBuffer *buff) const {
		PACKET_ENCODE_BEGIN(buff);
		PACKET_ENCODE(UInt32, uid);
		PACKET_ENCODE(UInt32, ud);
		PACKET_ENCODE(UInt32, id);
		PACKET_ENCODE(UInt32, num);
		PACKET_ENCODE(UInt32, ts);
		PACKET_ENCODE(UInt16, bag);
		PACKET_ENCODE(String, ext);
		return true;
	}

	bool Decode(IBuffer *buff) {
		PACKET_DECODE_BEGIN(buff);
		PACKET_DECODE(UInt32, uid);
		PACKET_DECODE(UInt32, ud);
		PACKET_DECODE(UInt32, id);
		PACKET_DECODE(UInt32, num);
		PACKET_DECODE(UInt32, ts);
		PACKET_DECODE(UInt16, bag);
		PACKET_DECODE(String, ext);
		return true;
	}
};

class CDataEquip: public CDataBaseDBC {
public:
	CDataEquip(int table = DB_EQUIP): CDataBaseDBC(table) {
	}
	int AddData(const DataEquip &data);
	int SetData(const DataEquip &data);
	int RepData(const DataEquip &data);
	int DelData(const DataEquip &data);
	int GetData(uint32_t uid, DataEquip &data);
	int GetData(uint32_t uid, vector<DataEquip> &datas);
};

#endif /* DATA_EQUIP_H_ */
