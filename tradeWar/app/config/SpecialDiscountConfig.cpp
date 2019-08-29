/*
 * SpecialDiscountConfig.cpp
 *
 *  Created on: 2018年11月9日
 *      Author: Administrator
 */

#include "SpecialDiscountConfig.h"
#include "ConfigJson.h"

SpecialDiscountConfig::SpecialDiscountConfig() {
}

SpecialDiscountConfig::~SpecialDiscountConfig() {
}

bool SpecialDiscountConfig::init() {
	string path = Config::GetValue("specialdiscount");
	if (Config::GetValue(CONFIG_WEIXIN) == "1") {
		path = Config::GetValue("specialdiscount_wx");
	}
	ConfigJson fileParser(path);
	if (!fileParser.Init()) {
		return false;
	}
	const Json::Value *special = fileParser.getMember("special");
	if (special == NULL || !special->isArray()) {
		error_log("special error");
		return false;
	}
	for (size_t i = 0; i < special->size(); ++i) {
		const Json::Value &item = special->get(i, Json::Value(Json::nullValue));
		if (item.isNull() || !item.isObject()) {
			continue;
		}
		SpecialDiscountItem cfg;
		cfg.id = item.get("id", 0).asUInt();
		cfg.lv = item.get("level", 0).asUInt();
		cfg.reward.Json2Award(item["reward"]);
		m_data.insert(make_pair(cfg.id, cfg));
	}
	return true;
}

const SpecialDiscountItem* SpecialDiscountConfig::getItem(uint32_t id) const {
	map<uint32_t, SpecialDiscountItem>::const_iterator itr = m_data.find(id);
	if (itr == m_data.end()) {
		return NULL;
	}
	return &(itr->second);
}

uint32_t SpecialDiscountConfig::getSize() const {
	return m_data.size();
}
