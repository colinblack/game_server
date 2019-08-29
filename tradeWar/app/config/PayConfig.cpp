/*
 * PayConfig.cpp
 *
 *  Created on: 2018年11月9日
 *      Author: Administrator
 */

#include "PayConfig.h"
#include "ConfigJson.h"

PayConfig::PayConfig() {
}

PayConfig::~PayConfig() {
}

bool PayConfig::init() {
	string path = Config::GetValue("wanbapay");
	if (Config::GetValue(CONFIG_WEIXIN) == "1") {
		path = Config::GetValue("weixinpay");
	}
	ConfigJson fileParser(path);
	if (!fileParser.Init()) {
		return false;
	}
	const Json::Value *buy = fileParser.getMember("buy");
	if (buy == NULL || !buy->isArray()) {
		error_log("buy error");
		return false;
	}
	for (size_t i = 0; i < buy->size(); ++i) {
		const Json::Value &item = buy->get(i, Json::Value(Json::nullValue));
		if (item.isNull() || !item.isObject()) {
			continue;
		}
		PayItem cfg;
		cfg.id = item.get("id", 0).asUInt();
		cfg.money = item.get("money", 0).asUInt();
		cfg.type = item.get("type", 0).asUInt();
		cfg.gift = item.get("gift", 0).asUInt();
		m_data.insert(make_pair(cfg.id, cfg));
	}
	return true;
}

const PayItem* PayConfig::getItem(uint32_t id) const {
	map<uint32_t, PayItem>::const_iterator itr = m_data.find(id);
	if (itr == m_data.end()) {
		return NULL;
	}
	return &(itr->second);
}
