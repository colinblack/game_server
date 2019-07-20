/*
 * DataSkill.h
 *
 *  Created on: 2019年5月25日
 *      Author: Administrator
 */

#ifndef DATA_SKILL_H_
#define DATA_SKILL_H_

#include "Kernel.h"

struct DataSkill {
	uint32_t uid;
	byte rid;
	uint32_t id;		//serial
	uint32_t skill_id;
	uint16_t lv;

	DataSkill() {
		uid = 0;
		rid = 0;
		id = 0;
		skill_id = 0;
		lv = 0;
	}

	bool Encode(IBuffer *buff) const {
		PACKET_ENCODE_BEGIN(buff);
		PACKET_ENCODE(UInt32, uid);
		PACKET_ENCODE(Byte, rid);
		PACKET_ENCODE(UInt32, id);
		PACKET_ENCODE(UInt16, lv);
		return true;
	}

	bool Decode(IBuffer *buff) {
		PACKET_DECODE_BEGIN(buff);
		PACKET_DECODE(UInt32, uid);
		PACKET_DECODE(Byte, rid);
		PACKET_DECODE(UInt32, id);
		PACKET_DECODE(UInt16, lv);
		return true;
	}

	bool operator ==(const DataSkill &oth) {
		return oth.uid == this->uid && oth.id == this->id && oth.rid == this->rid;
	}
};

class CDataSkill: public CDataBaseDBC {
public:
	CDataSkill(int table = DB_SKILL) : CDataBaseDBC(table) {
	}
	~CDataSkill();
	int AddData(const DataSkill &data);
	int SetData(const DataSkill &data);
	int RepData(const DataSkill &data);
	int DelData(const DataSkill &data);
	int GetData(uint32_t uid, DataSkill &data);
	int GetData(uint32_t uid, vector<DataSkill> &datas);
};

#endif /* DATA_SKILL_H_ */
