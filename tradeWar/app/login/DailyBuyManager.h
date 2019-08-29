/*
 * DailyBuyManager.h
 *
 *  Created on: 2018年10月20日
 *      Author: Administrator
 */

#ifndef DAILY_BUY_MANAGER_H_
#define DAILY_BUY_MANAGER_H_

#include "IManager.h"
#include "Award.h"

struct DailyBuyItem {
	byte id;
	byte buy;
	byte cost_type;
	byte good_discount;
	byte good_type;
	uint32_t good_id;
	uint32_t good_count;
	uint32_t good_price;
	uint32_t refresh_ts;

	DailyBuyItem() {
		id = 0;
		buy = 0;
		cost_type = 0;
		good_discount = 0;
		good_type = 0;
		good_id = 0;
		good_count = 0;
		good_price = 0;
		refresh_ts = 0;
	}

	bool fromJson(const Json::Value &v) {
		if (v.isNull() || !v.isObject()) {
			return false;
		}
		id = v.get("id", 0).asUInt();
		buy = v.get("b", 0).asUInt();
		cost_type = v.get("ct", 0).asUInt();
		good_discount = v.get("gd", 0).asUInt();
		good_type = v.get("gt", 0).asUInt();
		good_id = v.get("gi", 0).asUInt();
		good_count = v.get("gc", 0).asUInt();
		good_price = v.get("gp", 0).asUInt();
		refresh_ts = v.get("rts", 0).asUInt();
		return true;
	}

	Json::Value toJson() const {
		Json::Value v;
		v["id"] = static_cast<uint32_t>(id);
		v["b"] = static_cast<uint32_t>(buy);
		v["ct"] = static_cast<uint32_t>(cost_type);
		v["gd"] = static_cast<uint32_t>(good_discount);
		v["gt"] = static_cast<uint32_t>(good_type);
		v["gi"] = good_id;
		v["gc"] = good_count;
		v["gp"] = good_price;
		v["rts"] = refresh_ts;
		return v;
	}
};

class DailyBuyManager: public IManager {
public:
	DailyBuyManager();
	virtual ~DailyBuyManager();
	bool doPacket(CNetPacket *p);
	bool load(uint32_t uid);
	bool save();
	bool push();
	bool reset();
private:
	bool doQuery(CNetPacket *p);
	bool doBuy(CNetPacket *p);
	bool doRefresh(CNetPacket *p);
	bool onResp(byte sub, byte ret, const Award *award = NULL);
	bool refresh(bool all);
private:
	map<byte, DailyBuyItem> m_data;
	vector<byte> m_index;
	uint32_t m_reset_ts;
	uint32_t m_refresh_times;
};

#endif /* DAILY_BUY_MANAGER_H_ */

