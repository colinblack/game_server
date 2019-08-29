#include "ExpConfig.h"
#include "ConfigJson.h"
#include "CommonConfig.h"

ExpConfig::ExpConfig() {
}

ExpConfig::~ExpConfig() {
}
bool ExpConfig::init(const string& path) {
	ConfigJson fileParser(path);
	if (!fileParser.Init()) {
		return false;
	}
	Json::Reader reader;
	const Json::Value *heroExp = fileParser.getMember("hero_exp");
	if (heroExp == NULL) {
		error_log("hero_exp error");
		return false;
	}
	if (heroExp->isString()) {
		Json::Value v;
		reader.parse(heroExp->asString(), v);
		parseArray(v, m_heroExp);
	} else if (heroExp->isArray()) {
		parseArray(*heroExp, m_heroExp);
	}

	const Json::Value *userExp = fileParser.getMember("user_exp");
	if (userExp == NULL) {
		error_log("user_exp error");
		return false;
	}
	if (userExp->isString()) {
		Json::Value v;
		reader.parse(userExp->asString(), v);
		parseArray(v, m_userExp);
	} else if (userExp->isArray()) {
		parseArray(*userExp, m_userExp);
	}

	const Json::Value *levels = fileParser.getMember("levels");
	if (levels == NULL || !levels->isArray()) {
		error_log("levels error");
		return false;
	}
	for (size_t i = 0; i < levels->size(); ++i) {
		const Json::Value &item = levels->get(i, Json::Value(Json::nullValue));
		if (item.isNull() || !item.isObject()) {
			continue;
		}
		ExpLevelItem cfg;
		cfg.level = item.get("level", 0).asUInt();
		cfg.star = item.get("star", 0).asUInt();
		cfg.reward = item.get("attackReward", 0).asUInt();
		cfg.firstCost = item.get("firstAttackCost", 0).asUInt();
		cfg.refreshCost = item.get("refreshCostAdd", 0).asUInt();
		cfg.attackReward = item.get("attackReward", 0).asUInt();
		cfg.award.Json2Award(item["reward"]);
		m_levels.insert(make_pair(cfg.level, cfg));
	}
	return true;
}
// 返回:英雄等级
uint32_t ExpConfig::getNextHeroLevel(uint32_t curLevel, uint32_t exp) {
	if (curLevel == 0) {
		error_log("invalid param: curLevel=%u", curLevel);
		return 0;
	}
	uint32_t idx = curLevel - 1;
	for (; idx + 1 < m_heroExp.size() && m_heroExp[idx + 1] <= exp; ++idx) {
	}
	return idx + 1; // return level
}

uint32_t ExpConfig::getNextUserLevel(uint32_t exp) {
	if (m_userExp.empty()) {
		return 1u;
	}
	uint32_t len = m_userExp.size() - 1;
	if (exp >= m_userExp[len]) {
		return len;
	}
	int left = 0;
	int right = len;
	while(left <= right) {
		int m = (left + right) / 2;
		if (m_userExp[m] == exp) {
			return m + 1;
		}else if(m_userExp[m] > exp) {
			right = m - 1;
		}else{
			left = m + 1;
		}
	}
	return left;
}

bool ExpConfig::getHeroExp(uint32_t level, uint32_t& heroExp) {
	uint32_t idx = level - 1;
	if (idx < m_heroExp.size()) {
		heroExp = m_heroExp[idx];
		return true;
	}
	return false;
}

bool ExpConfig::getUserExp(uint32_t level, uint32_t& userExp) {
	uint32_t idx = level - 1;
	if (idx < m_userExp.size()) {
		userExp = m_userExp[idx];
		return true;
	}
	return false;
}

uint32_t ExpConfig::getExpLevelSize() const {
	return m_levels.size();
}

const ExpLevelItem* ExpConfig::getExpLevel(uint16_t level) const {
	map<uint16_t, ExpLevelItem>::const_iterator itr = m_levels.find(level);
	if (itr == m_levels.end()) {
		return NULL;
	}
	return &(itr->second);
}

