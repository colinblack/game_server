/*
 * DataBoss.h
 *
 *  Created on: 2019年2月25日
 *      Author: Administrator
 */

#ifndef DATA_BOSS_H_
#define DATA_BOSS_H_

#include "Kernel.h"
#include "AsyncDBInterface.h"

struct DataBoss {
	uint32_t uid;
	uint32_t ts;
	uint32_t curr_hurt;
	uint32_t curr_id;
	uint64_t total_hurt;
	string   soldier;
	string   shop;

	DataBoss() {
		uid = 0;
		ts = 0;
		curr_hurt = 0;
		curr_id = 0;
		total_hurt = 0;
		soldier.clear();
		shop.clear();
	}

	bool Encode(CBufferWriter &writer) const {
		PACKET_ENCODE(UInt32, uid);
		PACKET_ENCODE(UInt32, ts);
		PACKET_ENCODE(UInt32, curr_hurt);
		PACKET_ENCODE(UInt32, curr_id);
		PACKET_ENCODE(UInt64, total_hurt);
		PACKET_ENCODE(String, soldier);
		PACKET_ENCODE(String, shop);
		return true;
	}

	bool Decode(CBufferReader &reader) {
		PACKET_DECODE(UInt32, uid);
		PACKET_DECODE(UInt32, ts);
		PACKET_DECODE(UInt32, curr_hurt);
		PACKET_DECODE(UInt32, curr_id);
		PACKET_DECODE(UInt64, total_hurt);
		PACKET_DECODE(String, soldier);
		PACKET_DECODE(String, shop);
		return true;
	}
};

struct DataBossSoldier {
	uint32_t id;
	uint32_t cnt;

	DataBossSoldier() {
		id = 0;
		cnt = 0;
	}

	void ToJson(Json::Value &v) {
		v = Json::Value(Json::objectValue);
		v["id"] = id;
		v["c"] = cnt;
	}

	void FromJson(const Json::Value &v) {
		if (v.isNull() || !v.isObject()) {
			return;
		}
		Json::GetUInt(v, "id", id);
		Json::GetUInt(v, "c", cnt);
	}
};


class CDataBoss: public CDataBaseDBC, public AsyncDBInterface {
public:
	CDataBoss(int table = DB_BOSS): CDataBaseDBC(table) {
	}
	virtual ~CDataBoss() {
	}
	void doRequest(CNetPacket *p);

	int Get(uint32_t uid, DataBoss &data);
	int Add(const DataBoss &data);
	int Set(const DataBoss &data);
	int Del(uint32_t uid);

	int Add(CNetPacket *p);
	int Set(CNetPacket *p);
	int Del(CNetPacket *p);
};

#endif /* DATA_BOSS_H_ */
