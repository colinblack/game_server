/*
 * DataPos.h
 *
 *  Created on: 2013-3-13
 *      Author: colin
 */

#ifndef DATA_POS_H_
#define DATA_POS_H_

#include "Kernel.h"

struct DataPos {
	unsigned uid;
	unsigned fb_id;
	unsigned map_id;
	unsigned x;
	unsigned y;
	unsigned dir;
	unsigned update_time;
	unsigned from_x;
	unsigned from_y;
	unsigned from_map_id;

	DataPos() {
		uid = 0;
		fb_id = 0;
		map_id = 0;
		x = 0;
		y = 0;
		dir = 0;
		update_time = 0;
		from_x = 0;
		from_y = 0;
		from_map_id = 0;
	}

	DataPos& operator=(const DataPos &other) {
		uid = other.uid;
		fb_id = other.fb_id;
		map_id = other.map_id;
		x = other.x;
		y = other.y;
		dir = other.dir;
		update_time = other.update_time;
		from_x = other.from_x;
		from_y = other.from_y;
		from_map_id = other.from_map_id;
		return *this;
	}

	bool Encode(IBuffer *buff) const {
		PACKET_ENCODE_BEGIN(buff);
		PACKET_ENCODE(UInt32, uid);
		PACKET_ENCODE(UInt32, fb_id);
		PACKET_ENCODE(UInt32, map_id);
		PACKET_ENCODE(UInt32, x);
		PACKET_ENCODE(UInt32, y);
		PACKET_ENCODE(UInt32, dir);
		PACKET_ENCODE(UInt32, update_time);
		PACKET_ENCODE(UInt32, from_x);
		PACKET_ENCODE(UInt32, from_y);
		PACKET_ENCODE(UInt32, from_map_id);
		return true;
	}

	bool Decode(IBuffer *buff) {
		PACKET_DECODE_BEGIN(buff);
		PACKET_DECODE(UInt32, uid);
		PACKET_DECODE(UInt32, fb_id);
		PACKET_DECODE(UInt32, map_id);
		PACKET_DECODE(UInt32, x);
		PACKET_DECODE(UInt32, y);
		PACKET_DECODE(UInt32, dir);
		PACKET_DECODE(UInt32, update_time);
		PACKET_DECODE(UInt32, from_x);
		PACKET_DECODE(UInt32, from_y);
		PACKET_DECODE(UInt32, from_map_id);
		return true;
	}
};

class CDataPos: public CDataBaseDBC {
public:
	CDataPos(int table = DB_POS) : CDataBaseDBC(table) {
	}
	int AddData(const DataPos &data);
	int SetData(const DataPos &data);
	int RepData(const DataPos &data);
	int DelData(const DataPos &data);
	int GetData(uint32_t uid, DataPos &data);
	int GetData(uint32_t uid, vector<DataPos> &datas);
};

#endif /* DATA_POS_H_ */
