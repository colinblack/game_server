/*
 * SoldierRecoverTrain.h
 *
 *  Created on: 2018年7月28日
 *      Author: Administrator
 */

#ifndef _SOLDIER_RECOVER_TRAIN_H_
#define _SOLDIER_RECOVER_TRAIN_H_

#include "Kernel.h"
#include "IManager.h"

struct SoldierRecoverTrainItem {
	uint32_t id;
	uint32_t ts;
	uint32_t speed;
	uint32_t count;

	SoldierRecoverTrainItem() :
			id(0), ts(0), speed(0), count(0) {
	}
	SoldierRecoverTrainItem(uint32_t _id, uint32_t _ts, uint32_t _speed, uint32_t _c) :
			id(_id), ts(_ts), speed(_speed), count(_c) {
	}

	void FromJson(const Json::Value &value) {
		id = value.get("id", 0).asUInt();
		ts = value.get("ts", 0).asUInt();
		count = value.get("c", 0).asUInt();
		speed = value.get("s", 0).asUInt();
	}

	Json::Value ToJson() {
		Json::Value value;
		value["id"] = id;
		value["ts"] = ts;
		value["c"] = count;
		value["s"] = speed;
		return value;
	}
};

class SoldierRecoverTrain: public IManager {
public:
	SoldierRecoverTrain() {
	}
	virtual ~SoldierRecoverTrain() {
	}
	virtual bool doPacket(CNetPacket *packet);
	bool load(uint32_t uid);
	bool doSave();
	bool doSend();
	void onTimer();
	uint32_t getDelCount(uint32_t type);
private:
	//request
	bool doDelTrain(CNetPacket *packet);
	bool doAddTrain(CNetPacket *packet);
	//response
	void onDelTrainResp(uint32_t uid, byte ret);
	void onAddTrainResp(uint32_t uid, byte ret);
private:
	map<uint32_t, SoldierRecoverTrainItem> m_data;
};

#endif /* _SOLDIER_RECOVER_TRAIN_H_ */
