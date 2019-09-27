/*
 * DailyBuyConfig.cpp
 *
 *  Created on: 2018年10月20日
 *      Author: Administrator
 */

#include "DailyBuyConfig.h"
#include "ConfigJson.h"
#include "CommonConfig.h"

DailyBuyConfig::DailyBuyConfig() {
}

DailyBuyConfig::~DailyBuyConfig() {
}

bool DailyBuyConfig::init(const string &path) {
	ConfigJson fileParser(path);
	if (!fileParser.Init()) {
		return false;
	}

	const Json::Value *pool = fileParser.getMember("pool");
	if (pool == NULL || !pool->isArray()) {
		error_log("pool error");
		return false;
	}
	for (size_t i = 0; i < pool->size(); ++i) {
		const Json::Value &pool_item = pool->get(i, Json::Value(Json::nullValue));
		if (pool_item.isNull()) {
			continue;
		}
		DailyBuyPoolItem cfg_item;
		cfg_item.hour = pool_item.get("hour", 0).asUInt();
		cfg_item.cost = pool_item.get("cost", "").asString();
		vector<uint16_t> rate;
		parseArray(pool_item["rate"], rate);
		uint16_t s = 0;
		for (vector<uint16_t>::iterator itr = rate.begin(); itr != rate.end(); ++itr) {
			s += *itr;
			cfg_item.rate.push_back(s);
		}
		const Json::Value &pool_good = pool_item.get("data", Json::Value(Json::nullValue));
		for (size_t j = 0; j < pool_good.size(); ++j) {
			GiftBagItemConfig bag;
			if (initGood(pool_good[j], bag)) {
				cfg_item.data.insert(make_pair(bag.id, bag));
			}
		}
		m_pool.push_back(cfg_item);
	}

	const Json::Value *card = fileParser.getMember("card");
	if (card == NULL || !card->isArray()) {
		error_log("card error");
		return false;
	}
	for (size_t i = 0; i < card->size(); ++i) {
		GiftBagItemConfig bag;
		if (initGood(card->get(i, Json::Value(Json::nullValue)), bag)) {
			m_card.insert(make_pair(bag.id, bag));
		}
	}

	const Json::Value *price = fileParser.getMember("price");
	if (price == NULL || !price->isArray()) {
		error_log("price error");
		return false;
	}
	for (size_t i = 0; i < price->size(); ++i) {
		const Json::Value &price_item = price->get(i, Json::Value(Json::nullValue));
		DailyBuyCardPrice cfg_item;
		cfg_item.id = price_item.get("id", 0).asUInt();
		cfg_item.cash = price_item.get("cash", 0).asUInt();
		parseArray(price_item["rs1"], cfg_item.rs1);
		parseArray(price_item["dis"], cfg_item.dis);
		m_price.insert(make_pair(cfg_item.id, cfg_item));
	}

	return true;
}

bool DailyBuyConfig::initGood(const Json::Value &v, GiftBagItemConfig &d) {
	uint32_t id = 0;
	if (!Json::GetUInt(v, "id", id)) {
		if (!Json::GetUInt(v, "level", id)) {
			return false;
		}
	}
	const Json::Value &rate = v["rate"];
	const Json::Value &ratekey = v["ratekey"];
	const Json::Value &reward = v["reward"];
	if (!rate.isArray() || !ratekey.isArray() || rate.size() != ratekey.size()) {
		error_log("lucky box error,id=%u", id);
		return false;
	}

	d.id = id;
	uint32_t totalRate = 0;
	for (size_t k = 0; k < rate.size(); ++k) {
		totalRate += rate[k].asUInt();
		d.rate.push_back(totalRate);
	}
	for (size_t k = 0; k < ratekey.size(); ++k) {
		string key = ratekey[k].asString();
		if (!reward.isMember(key)) {
			error_log("lucky box ratekey error,id=%u,key=%s", id, key.c_str());
			return false;
		}
		AwardInfo awardInfo;
		if (!Award::JsonItem2Award(reward[key], key, awardInfo)) {
			error_log("JsonItem2Award error,id=%u,reward=%s", id, Json::ToString(reward[key]).c_str());
			return false;
		}
		d.award.get().push_back(awardInfo);
	}

	return true;
}

bool DailyBuyConfig::refresh(uint32_t lv, uint32_t id, AwardInfo &equip, uint32_t &price, uint32_t &dis, uint32_t &cost_type, uint32_t &ts) {
	if (id == 0 || m_pool.size() < id) {
		error_log("id error id=%u size=%u", id, m_pool.size());
		return false;
	}
	DailyBuyPoolItem &pool_item = m_pool[id - 1];
	map<uint32_t, GiftBagItemConfig>::iterator itr = pool_item.data.find(lv);
	if (itr == pool_item.data.end()) {
		error_log("lv error lv=%u id=%u", lv, id);
		return false;
	}
	AwardInfo good;
	if (!randomGood(itr->second, good)) {
		error_log("random pool error lv=%u id=%u", lv, id);
		return false;
	}
	ts = pool_item.hour * 3600;
	itr = m_card.find(good.id);
	if (itr == m_card.end()) {
		error_log("card error lv=%u id=%u cid=%u", lv, id, good.id);
		return false;
	}
	good.Clear();
	if (!randomGood(itr->second, good)) {
		error_log("random card error lv=%u id=%u cid=%u", lv, id, good.id);
		return false;
	}

	map<uint32_t, DailyBuyCardPrice>::iterator it = m_price.find(good.id);
	if (it == m_price.end()) {
		error_log("price error lv=%u id=%u cid=%u", lv, id, good.id);
		return false;
	}
	DailyBuyCardPrice &card_price = it->second;
	if (pool_item.cost == "cash") {
		price = card_price.cash;
		cost_type = 1;
	} else if (pool_item.cost == "rs1") {
		if (card_price.rs1.empty()) {
			error_log("rs1 error lv=%u id=%u cid=%u", lv, id, good.id);
			return false;
		}
		price = card_price.rs1.size() > static_cast<unsigned>(lv - 1) ? card_price.rs1[lv - 1] : 0;
		cost_type = 0;
	}
	uint16_t rate = pool_item.rate.back();
	int r = Math::GetRandomInt(rate == 0 ? 1 : rate);
	for (size_t i = 0; i < pool_item.rate.size(); ++i) {
		if (r <= pool_item.rate[i]) {
			dis = card_price.dis.size() > i ? card_price.dis[i] : 100;
			break;
		}
	}

	if (GiftBagConfig::getInstance()->isBox(good.id)) {
		Award award;
		if (!GiftBagConfig::getInstance()->openLuckyBox(good.id, good.count, award)) {
			error_log("open lucky box error id=%u cnt=%u", good.id, good.count);
			return false;
		}
		if (award.isEmpty()) {
			return false;
		}
		equip = *(award.get().begin());
	} else {
		equip = good;
	}

	return true;
}

bool DailyBuyConfig::randomGood(const GiftBagItemConfig &d, AwardInfo &a) {
	if (d.rate.empty()) {
		error_log("rate empty id=%u", d.id);
		return false;
	}
	uint32_t rate = d.rate.back();
	uint32_t r = Math::GetRandomInt(rate == 0 ? 1 : rate);
	uint32_t i = 0;
	vector<uint32_t>::const_iterator itr = d.rate.begin();
	for (; itr != d.rate.end(); ++itr, ++i) {
		if (r <= *itr) {
			const vector<AwardInfo> &reward = d.award.get();
			if (reward.size() > i) {
				a = reward.at(i);
			}
			return true;
		}
	}
	return false;
}
