/*
 * DataRoleAttr.h
 *
 * Create on: 2019.7 8
 *
 * autor: next
 */


#ifndef _DATA_SUIT_H_
#define _DATA_SUIT_H_
#include "Kernel.h"

struct DataRoleSuit {
	uint32_t uid;
	uint32_t rid;
	uint32_t type;
	uint32_t id;
	uint32_t slot_1;
	uint32_t slot_2;
	uint32_t slot_3;
	uint32_t slot_4;
	uint32_t slot_5;
	uint32_t slot_6;
	uint32_t slot_7;
	uint32_t slot_8;
	uint32_t flag;
	uint32_t reseve;

	DataRoleSuit() {
		memset(this,0,sizeof(*this));
	}

	bool init(uint32_t p_uid, uint32_t p_rid, uint32_t p_type, uint32_t p_id){
		memset(this,0,sizeof(*this));
		uid = p_uid;
		rid = p_rid;
		type = p_type;
		id = p_id;
		return true;
	}
};


// 称号
struct DataTitle {
	uint32_t uid;
	uint32_t rid;
	uint32_t type;
	uint32_t id;
	uint32_t slot_1;
	uint32_t slot_2;
	uint32_t slot_3;
	uint32_t slot_4;
	uint32_t slot_5;
	uint32_t slot_6;
	uint32_t slot_7;
	uint32_t slot_8;
	uint32_t flag;
	uint32_t reseve;

	DataTitle() {
		memset(this,0,sizeof(*this));
	}

	bool init(uint32_t p_uid,uint32_t p_rid, uint32_t p_type, uint32_t p_id){
		memset(this,0,sizeof(*this));
		uid = p_uid;
		type = p_type;
		id = p_id;
		rid = p_rid;
		return true;
	}
};


//符文
struct DataRoleRune{
	uint32_t uid;
	uint32_t rid;
	uint32_t type;
	uint32_t id;
	uint32_t normalRune[NORMAL_RUNE_COUNT];
	uint32_t specialRune[SPECIAL_RUNE_COUNT];
	DataRoleRune() {
		memset(this,0,sizeof(*this));
	}
};

struct DataRoleAttr {
	uint32_t uid;
	uint32_t rid;
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

	DataRoleAttr() {
		uid = 0;
		rid = 0;
		type = 0;
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

	bool Encode(IBuffer *buff) const {
		PACKET_ENCODE_BEGIN(buff);
		PACKET_ENCODE(UInt32, uid);
		PACKET_ENCODE(UInt32, rid);
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
		PACKET_DECODE(UInt32, rid);
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

class CDataRoleAttr: public CDataBaseDBC {
public:
	CDataRoleAttr(int table = DB_ROLE_ATTR): CDataBaseDBC(table) {
	}
	int AddData(const DataRoleAttr &data);
	int SetData(const DataRoleAttr &data);
	int RepData(const DataRoleAttr &data);
	int DelData(const DataRoleAttr &data);
	int GetData(uint32_t uid, DataRoleAttr &data);
	int GetData(uint32_t uid, vector<DataRoleAttr> &datas);
};

#endif /*_DATA_SUIT_H_*/
