/*
 * DataRole.h
 *
 *  Created on: 2019年6月20日
 *      Author: Administrator
 */

#ifndef DATA_ROLE_H_
#define DATA_ROLE_H_

#include "Kernel.h"

struct DataRole {
	uint32_t uid;
	uint32_t combat;
	uint8_t id;
	uint8_t sex;
	uint8_t career;
	string name;

	DataRole() {
		uid = 0;
		combat = 0;
		id = 0;
		sex = 0;
		career = 0;
	}

	bool Encode(IBuffer *buff) const {
		PACKET_ENCODE_BEGIN(buff);
		PACKET_ENCODE(UInt32, uid);
		PACKET_ENCODE(UInt32, combat);
		PACKET_ENCODE(Byte, id);
		PACKET_ENCODE(Byte, sex);
		PACKET_ENCODE(Byte, career);
		PACKET_ENCODE(String, name);
		return true;
	}

	bool Decode(IBuffer *buff) {
		PACKET_DECODE_BEGIN(buff);
		PACKET_DECODE(UInt32, uid);
		PACKET_DECODE(UInt32, combat);
		PACKET_DECODE(Byte, id);
		PACKET_DECODE(Byte, sex);
		PACKET_DECODE(Byte, career);
		PACKET_DECODE(String, name);
		return true;
	}
};

class CDataRole: public CDataBaseDBC {
public:
	CDataRole(int table = DB_ROLE): CDataBaseDBC(table) {
	}
	virtual ~CDataRole() {
	}
	int AddData(const DataRole &data);
	int SetData(const DataRole &data);
	int RepData(const DataRole &data);
	int DelData(const DataRole &data);
	int GetData(uint32_t uid, DataRole &data);
	int GetData(uint32_t uid, vector<DataRole> &datas);
};

#endif /* DATA_ROLE_H_ */
