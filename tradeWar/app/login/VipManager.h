/*
 * VipManager.h
 *
 *  Created on: 2018年10月17日
 *      Author: Administrator
 */

#ifndef _VIP_MANAGER_H_
#define _VIP_MANAGER_H_

#include "IManager.h"
#include "NetPacket.h"
#include "Award.h"

struct VipData {
	byte lv;
	byte first;
	uint32_t reward_ts;
	uint32_t end_ts;

	VipData() : lv(0), first(0), reward_ts(0), end_ts(0) {
	}

	bool fromJson(const Json::Value &v) {
		if (v.isNull() || !v.isObject()) {
			return false;
		}
		lv = v.get("lv", 0).asUInt();
		first = v.get("f", 0).asUInt();
		reward_ts = v.get("rts", 0).asUInt();
		end_ts = v.get("ets", 0).asUInt();
		return true;
	}

	Json::Value toJson() const {
		Json::Value v;
		v["lv"] = static_cast<uint32_t>(lv);
		v["f"] = static_cast<uint32_t>(first);
		v["rts"] = reward_ts;
		v["ets"] = end_ts;
		return v;
	}
};

class VipManager: public IManager {
public:
	enum {
		VIP_RIGHT_HARVEST = 1,
		VIP_RIGHT_BOAT_RES = 2,
		VIP_RIGHT_OFFLINE = 3,
		VIP_RIGHT_LOOT_ADD = 4,
		VIP_RIGHT_BOAT_TIMES = 5,
		VIP_RIGHT_CAPACITY = 6
	};
	VipManager();
	virtual ~VipManager();
	bool doPacket(CNetPacket *p);
	bool load(uint32_t uid);
	bool onLogin();
	bool save();
	bool push();
	bool reset();
	bool buy(uint32_t id);
	float getRight(uint32_t type);
private:
	bool doReward(CNetPacket *p);
	bool onRewardResp(byte ret, byte lv, const Award &award, const Award &box);
	bool onBoxReward(uint32_t lv, uint32_t id, uint32_t count, Award *result);
private:
	map<byte, VipData> m_data;
	byte m_lv;
};

#endif /* _VIP_MANAGER_H_ */
