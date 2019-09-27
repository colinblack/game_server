/*
 * DailyBuyConfig.h
 *
 *  Created on: 2018年10月20日
 *      Author: Administrator
 */

#ifndef DAILY_BUY_CONFIG_H_
#define DAILY_BUY_CONFIG_H_

#include "Kernel.h"
#include "GiftBagConfig.h"

struct DailyBuyPoolItem {
	byte hour;
	string cost;
	map<uint32_t, GiftBagItemConfig> data;
	vector<uint16_t> rate;

	DailyBuyPoolItem() {
		hour = 0;
		cost.clear();
		data.clear();
		rate.clear();
	}
};

struct DailyBuyCardPrice {
	uint32_t id;
	uint32_t cash;
	vector<uint32_t> rs1;
	vector<uint32_t> dis;

	DailyBuyCardPrice() {
		id = 0;
		cash = 0;
		rs1.clear();
		dis.clear();
	}
};

class DailyBuyConfig {
SINGLETON_CLASS(DailyBuyConfig);
	bool init(const string &path);
	bool initGood(const Json::Value &v, GiftBagItemConfig &d);
	bool refresh(uint32_t lv, uint32_t id, AwardInfo &equip, uint32_t &price, uint32_t &dis, uint32_t &cost_type, uint32_t &ts);
	bool randomGood(const GiftBagItemConfig &d, AwardInfo &a);
	uint32_t getPoolLen() const {
		return m_pool.size();
	}
private:
	vector<DailyBuyPoolItem> m_pool;
	map<uint32_t, GiftBagItemConfig> m_card;
	map<uint32_t, DailyBuyCardPrice> m_price;
};

#endif /* DAILY_BUY_CONFIG_H_ */
