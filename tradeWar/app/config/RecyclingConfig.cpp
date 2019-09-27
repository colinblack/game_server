/*
 * RecyclingConfig.cpp
 *
 *  Created on: 2018年11月28日
 *      Author: Administrator
 */

#include "RecyclingConfig.h"
#include "ConfigJson.h"
#include "CommonConfig.h"

RecyclingConfig::RecyclingConfig() {
}

RecyclingConfig::~RecyclingConfig() {
}

bool RecyclingConfig::init(const string &path) {
	ConfigJson fileParser(path);
	if (!fileParser.Init()) {
		return false;
	}
	const Json::Value *recycling = fileParser.getMember("recycling");
	if (recycling == NULL || !recycling->isArray()) {
		error_log("recycling error");
		return false;
	}
	for (size_t i = 0; i < recycling->size(); ++i) {
		const Json::Value &item = recycling->get(i, Json::Value(Json::nullValue));
		if (item.isNull() || !item.isObject()) {
			continue;
		}
		RecyclingItem cfg;
		cfg.lv = item.get("lv", 0).asUInt();
		cfg.cost = item.get("cost", 0).asUInt();
		cfg.count = item.get("count", 0).asUInt();
		cfg.res = item.get("res", 0).asUInt();
		parseArray(item["skill"], cfg.skill);
		m_data.insert(make_pair(cfg.lv, cfg));
	}
	return true;
}

const RecyclingItem* RecyclingConfig::getItem(uint32_t lv) const {
	map<byte, RecyclingItem>::const_iterator itr = m_data.find(lv);
	if (itr != m_data.end()) {
		return &(itr->second);
	}
	return NULL;
}

uint32_t RecyclingConfig::getR1(uint32_t res) {
	float r = static_cast<float>(25 + Math::GetRandomInt(50)) / 100.0f;
	return static_cast<float>(res) * r;
}
