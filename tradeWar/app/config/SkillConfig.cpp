/*
 * SkillConfig.cpp
 *
 *  Created on: 2015年12月19日
 *      Author: aaron
 */

#include "SkillConfig.h"
#include "ConfigJson.h"
#include "CommonConfig.h"

CSkillConfig::CSkillConfig() {
}

CSkillConfig::~CSkillConfig() {
}

bool CSkillConfig::init(const string &path) {
	ConfigJson reader(path);
	if (!reader.Init()) {
		return false;
	}
	const Json::Value *skills = reader.getMember("skills");
	if (skills == NULL || !skills->isArray()) {
		error_log("skills");
		return false;
	}
	for (size_t i = 0; i < skills->size(); ++i) {
		const Json::Value &item = skills->get(i, Json::nullValue);
		if (item.isNull() || !item.isObject()) {
			continue;
		}
		SkillConfig cfg;
		if (!Json::GetUInt(item, "skill", cfg.id)) {
			continue;
		}
		cfg.q = item.get("q", 0).asUInt();
		parseArray(item["cost"], cfg.cost);
		m_config.push_back(cfg);
	}
	return true;
}

const SkillConfig* CSkillConfig::getConfig(uint32_t id) {
	vector<SkillConfig>::const_iterator itr = find(m_config.begin(), m_config.end(), id);
	if (itr != m_config.end()) {
		return &(*itr);
	}
	return NULL;
}

bool CSkillConfig::getCost(uint32_t id, uint32_t lv, uint32_t &cost) {
	lv = lv > 0 ? lv - 1 : 0;
	vector<SkillConfig>::iterator itr = find(m_config.begin(), m_config.end(), id);
	if (itr == m_config.end()) {
		return false;
	}
	if (itr->cost.size() <= lv) {
		return false;
	}
	cost = itr->cost[lv];
	return true;
}

