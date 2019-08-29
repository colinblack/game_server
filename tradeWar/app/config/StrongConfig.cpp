/*
 * StrongConfig.cpp
 *
 *  Created on: 2018年9月18日
 *      Author: Administrator
 */

#include "StrongConfig.h"
#include "ConfigJson.h"
#include "CommonConfig.h"

StrongConfig::StrongConfig() {
}

StrongConfig::~StrongConfig() {
}

bool StrongConfig::init(const string &path) {
	ConfigJson fileParser(path);
	if (!fileParser.Init()) {
		return false;
	}
	const Json::Value *soldier = fileParser.getMember("soldier");
	if (soldier == NULL || !soldier->isArray()) {
		error_log("soldier error");
		return false;
	}
	for (size_t i = 0; i < soldier->size(); ++i) {
		const Json::Value &item = soldier->get(i, Json::Value(Json::nullValue));
		if (item.isNull() || !item.isObject()) {
			continue;
		}
		StrongItem cfg;
		cfg.id = String::s2i(item["id"].asString().substr(1), 0);
		parseArray(item["cost"], cfg.cost);
		parseArray(item["reward"], cfg.reward);
		m_soldier.insert(make_pair(cfg.id, cfg));
	}

	const Json::Value *tower = fileParser.getMember("tower");
	if (tower == NULL || !tower->isArray()) {
		error_log("soldier error");
		return false;
	}
	for (size_t i = 0; i < tower->size(); ++i) {
		const Json::Value &item = tower->get(i, Json::Value(Json::nullValue));
		if (item.isNull() || !item.isObject()) {
			continue;
		}
		StrongItem cfg;
		cfg.id = String::s2i(item["type"].asString(), 0);
		parseArray(item["cost"], cfg.cost);
		m_tower.insert(make_pair(cfg.id, cfg));
	}

	const Json::Value *limitLv = fileParser.getMember("limitLv");
	if (limitLv != NULL) {
		parseArray(*limitLv, m_tower_level_limit);
	}

	const Json::Value *strongPower = fileParser.getMember("strongPower");
	if (strongPower == NULL || !strongPower->isArray()) {
		error_log("strongPower error");
		return false;
	}
	for (size_t i = 0; i < strongPower->size(); ++i) {
		const Json::Value &item = strongPower->get(i, Json::Value(Json::nullValue));
		if (item.isNull() || !item.isObject()) {
			continue;
		}
		StrongPower cfg;
		cfg.color = item.get("color", 0).asUInt();
		parseArray(item["junli"], cfg.power);
		m_strong_power.push_back(cfg);
	}
	return true;
}

uint32_t StrongConfig::getSoldierCost(uint32_t id, uint32_t lv) {
	map<uint32_t, StrongItem>::iterator itr = m_soldier.find(id);
	if (itr == m_soldier.end() || itr->second.cost.size() <= lv) {
		return 0;
	}
	return itr->second.cost[lv];
}

uint32_t StrongConfig::getSoldierReward(uint32_t id, uint32_t lv) {
	map<uint32_t, StrongItem>::iterator itr = m_soldier.find(id);
	if (itr == m_soldier.end() || itr->second.reward.size() <= lv) {
		return 0;
	}
	return itr->second.reward[lv];
}

uint32_t StrongConfig::getTower(uint32_t id, uint32_t lv) {
	map<uint32_t, StrongItem>::iterator itr = m_tower.find(id);
	if (itr == m_tower.end() || itr->second.cost.size() <= lv) {
		return 0;
	}
	return itr->second.cost[lv];
}

uint32_t StrongConfig::getTowerLevelLimit(uint32_t lv) {
	if (m_tower_level_limit.size() <= lv) {
		return -1;
	}
	return m_tower_level_limit[lv];
}

uint32_t StrongConfig::getStrongPower(uint32_t color, uint32_t f, uint32_t t) {
	uint32_t power = 0;
	for (size_t i = 0; i < m_strong_power.size(); ++i) {
		if (m_strong_power[i].color != color) {
			continue;
		}
		for (size_t j = f; j < m_strong_power[i].power.size() && j < t; ++j) {
			power += m_strong_power[i].power[j];
		}
		break;
	}
	return power;
}
