/*
 * WorldConfig.cpp
 *
 *  Created on: 2018年12月25日
 *      Author: Administrator
 */

#include "WorldConfig.h"
#include "ConfigJson.h"
#include "CommonConfig.h"

#define MAX_PRODUCE_TS 10800

WorldConfig::WorldConfig() {
}

WorldConfig::~WorldConfig() {
}

bool WorldConfig::init(const string &path) {
	ConfigJson fileParser(path);
	if (!fileParser.Init()) {
		return false;
	}
	const Json::Value *city = fileParser.getMember("city");
	if (city == NULL || !city->isArray()) {
		error_log("city error");
		return false;
	}
	for (size_t i = 0; i < city->size(); ++i) {
		const Json::Value &item = city->get(i, Json::Value(Json::nullValue));
		if (item.isNull() || !item.isObject()) {
			continue;
		}
		WorldConfigCity cfg;
		cfg.id = item.get("id", 0).asUInt();
		cfg.type = item.get("type", 0).asUInt();
		cfg.npcid = item.get("NPC", 0).asUInt();
		cfg.power = item.get("junli", 0).asUInt();
		cfg.exp = item.get("exp", 0).asUInt();
		cfg.name = item.get("name", "").asString();
		cfg.npcname = item.get("npcname", "").asString();
		m_citys.insert(make_pair(cfg.id, cfg));
	}

	const Json::Value *cityType = fileParser.getMember("cityType");
	if (cityType == NULL || !cityType->isArray()) {
		error_log("cityType error");
		return false;
	}
	for (size_t i = 0; i < cityType->size(); ++i) {
		const Json::Value &item = cityType->get(i, Json::Value(Json::nullValue));
		if (item.isNull() || !item.isObject()) {
			continue;
		}
		uint32_t id = 0;
		Json::GetUInt(item, "id", id);
		if (!m_citys.count(id)) {
			continue;
		}
		WorldConfigCity &cfg = m_citys[id];
		cfg.soldier = item.get("soilderNum", 0).asUInt();
		parseArray(item["outPut"], cfg.produce);
	}

	const Json::Value *shop = fileParser.getMember("shop");
	if (shop == NULL || !shop->isArray()) {
		error_log("shop error");
		return false;
	}
	for (size_t i = 0; i < shop->size(); ++i) {
		const Json::Value &item = shop->get(i, Json::Value(Json::nullValue));
		if (item.isNull() || !item.isObject()) {
			continue;
		}
		WorldConfigShop cfg;
		cfg.id = item.get("id", 0).asUInt();
		cfg.require = item.get("require", 0).asUInt();
		cfg.times = item.get("times", 0).asUInt();
		cfg.reward.Json2Award(item["reward"]);
		m_shops.insert(make_pair(cfg.id, cfg));
	}

	return true;
}

bool WorldConfig::isExists(uint32_t cid, uint32_t pid) const {
	map<uint16_t, WorldConfigCity>::const_iterator itr = m_citys.find(cid);
	if (itr == m_citys.end()) {
		return false;
	}
	if (itr->second.produce.size() <= pid) {
		return false;
	}
	return true;
}

uint32_t WorldConfig::getProduce(uint32_t cid, uint32_t pid, uint32_t ts) const {
	map<uint16_t, WorldConfigCity>::const_iterator itr = m_citys.find(cid);
	if (itr == m_citys.end()) {
		return 0;
	}
	if (itr->second.produce.size() <= pid) {
		return 0;
	}
	uint32_t p = *(itr->second.produce.begin() + pid);
	float pts = ts > MAX_PRODUCE_TS ? MAX_PRODUCE_TS : ts;
	return static_cast<float>(p) / 3600.0f * pts;
}

uint32_t WorldConfig::getShopSize() const {
	return m_shops.size();
}

const WorldConfigShop* WorldConfig::getShopItem(uint32_t id) const {
	map<uint16_t, WorldConfigShop>::const_iterator itr = m_shops.find(id);
	if (itr == m_shops.end()) {
		return NULL;
	}
	return &(itr->second);
}

const map<uint16_t, WorldConfigCity>& WorldConfig::getCity() const {
	return m_citys;
}

uint32_t WorldConfig::getNpcId(uint32_t cid) const {
	map<uint16_t, WorldConfigCity>::const_iterator itr = m_citys.find(cid);
	if (itr == m_citys.end()) {
		return 0;
	}
	return itr->second.npcid;
}

uint32_t WorldConfig::getRank(uint32_t cid, uint32_t pid) const {
	uint32_t rank = 0;
	map<uint16_t, WorldConfigCity>::const_iterator itr = m_citys.begin();
	for (; itr != m_citys.end(); ++itr) {
		if (itr->first < cid) {
			rank += itr->second.produce.size();
		} else if (itr->first == cid) {
			rank += pid + 1;
		} else {
			break;
		}
	}
	return rank;
}

const string* WorldConfig::getName(uint32_t cid) const {
	map<uint16_t, WorldConfigCity>::const_iterator itr = m_citys.find(cid);
	if (itr == m_citys.end()) {
		return NULL;
	}
	return &(itr->second.name);
}

const WorldConfigCity* WorldConfig::getItem(uint32_t cid) const {
	map<uint16_t, WorldConfigCity>::const_iterator itr = m_citys.find(cid);
	if (itr == m_citys.end()) {
		return NULL;
	}
	return &(itr->second);
}
