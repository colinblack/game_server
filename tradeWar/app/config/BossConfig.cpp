/*
 * BossConfig.cpp
 *
 *  Created on: 2019年2月25日
 *      Author: Administrator
 */

#include "BossConfig.h"
#include "ConfigJson.h"

BossConfig::BossConfig() {
	m_rank_size = 0;
}
BossConfig::~BossConfig() {
}
bool BossConfig::init(const string &path) {
	ConfigJson fileParser(path);
	if (!fileParser.Init()) {
		return false;
	}
	const Json::Value *boss = fileParser.getMember("boss");
	if (boss == NULL || !boss->isArray()) {
		error_log("boss error");
		return false;
	}
	for (size_t i = 0; i < boss->size(); ++i) {
		const Json::Value &item = boss->get(i, Json::Value(Json::nullValue));
		if (item.isNull()) {
			continue;
		}
		BossConfigItem cfg;
		cfg.id = item.get("id", 0).asUInt();
		cfg.hp = item.get("hp", 0).asUInt();
		cfg.reward.Json2Award(item["reward"]);
		m_data.insert(make_pair(cfg.id, cfg));
	}

	const Json::Value *ranks = fileParser.getMember("ranks");
	for (size_t i = 0; i < ranks->size(); ++i) {
		const Json::Value &item = ranks->get(i, Json::Value(Json::nullValue));
		if (item.isNull()) {
			continue;
		}
		string r = item.get("rank", "").asString();
		vector<string> line;
		CBasic::StringSplitTrim(r, "-", line);
		if (line.size() != 2) {
			continue;
		}
		BossConfigRank cfg;
		cfg.f = CTrans::STOI(line[0]);
		cfg.t = CTrans::STOI(line[1]);
		cfg.reward.Json2Award(item["reward"]);
		if (cfg.t > m_rank_size) {
			m_rank_size = cfg.t;
		}
		m_rank.push_back(cfg);
	}

	const Json::Value *shops = fileParser.getMember("shops");
	for (size_t i = 0; i < shops->size(); ++i) {
		const Json::Value &item = shops->get(i, Json::Value(Json::nullValue));
		if (item.isNull()) {
			continue;
		}
		BossConfigShop cfg;
		cfg.id = item.get("id", 0).asUInt();
		cfg.require = item.get("require", 0).asUInt();
		cfg.count = item.get("count", 0).asUInt();
		cfg.reward.Json2Award(item["reward"]);
		m_shop.insert(make_pair(cfg.id, cfg));
	}
	return true;
}
const BossConfigItem* BossConfig::getItem(byte id) const {
	map<byte, BossConfigItem>::const_iterator itr = m_data.find(id);
	if (itr == m_data.end()) {
		return NULL;
	}
	return &(itr->second);
}
const BossConfigShop* BossConfig::getShop(byte id) const {
	map<byte, BossConfigShop>::const_iterator itr = m_shop.find(id);
	if (itr == m_shop.end()) {
		return NULL;
	}
	return &(itr->second);
}
const Award* BossConfig::getRank(uint32_t r) const {
	vector<BossConfigRank>::const_iterator itr = m_rank.begin();
	for (; itr != m_rank.end(); ++itr) {
		if (r >= itr->f && r <= itr->t) {
			return &(itr->reward);
		}
	}
	return NULL;
}
uint32_t BossConfig::getRankSize() const {
	return m_rank_size;
}
uint32_t BossConfig::getShopSize() const {
	return m_shop.size();
}
