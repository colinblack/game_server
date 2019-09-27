/*
 * RandomQuestConfig.cpp
 *
 *  Created on: 2018年11月30日
 *      Author: Administrator
 */

#include "RandomQuestConfig.h"
#include "ConfigJson.h"
#include "CommonConfig.h"

RandomQuestConfig::RandomQuestConfig() {
}

RandomQuestConfig::~RandomQuestConfig() {
}

bool RandomQuestConfig::init(const string &path) {
	ConfigJson fileParser(path);
	if (!fileParser.Init()) {
		return false;
	}
	const Json::Value *reward = fileParser.getMember("reward");
	if (reward == NULL || !reward->isArray()) {
		error_log("reward error");
		return false;
	}
	for (size_t i = 0; i < reward->size(); ++i) {
		const Json::Value &item = reward->get(i, Json::Value(Json::nullValue));
		if (item.isNull() || !item.isObject()) {
			continue;
		}
		RandomQuestReward cfg;
		Json::GetUInt(item, "id", cfg.id);
		if (item.isMember("cost")) {
			Json::GetUInt(item["cost"], "cash", cfg.cost);
		}
		cfg.reward.Json2Award(item["reward"]);
		m_reward.insert(make_pair(cfg.id, cfg));
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
		RandomQuestSoldier cfg;
		Json::GetUInt(item, "id", cfg.id);
		for (size_t j = 0; j < item["soldier"].size(); ++j) {
			if (!item["soldier"][j].isString()) {
				error_log("%s", Json::ToString(item).c_str());
				continue;
			}
			cfg.soldier.push_back(CTrans::STOI(item["soldier"][j].asString().substr(1)));
		}
		m_soldier.insert(make_pair(cfg.id, cfg));
	}

	const Json::Value *government = fileParser.getMember("government");
	if (government == NULL || !government->isArray()) {
		error_log("government error");
		return false;
	}
	for (size_t i = 0; i < government->size(); ++i) {
		const Json::Value &item = government->get(i, Json::Value(Json::nullValue));
		if (item.isNull() || !item.isObject()) {
			continue;
		}
		RandomQuest cfg;
		Json::GetUInt(item, "id", cfg.id);
		uint32_t rate = 0;
		for (size_t j = 0; j < item["rate"].size(); ++j) {
			rate += item["rate"][j].asUInt();
			cfg.rate.push_back(rate);
		}
		for (size_t j = 0; j < item["ratekey"].size(); ++j) {
			rate = CTrans::STOI(item["ratekey"][j].asString());
			cfg.rateKey.push_back(rate);
		}
		cfg.reward1.Json2Award(item["reward1"]);
		cfg.reward2.Json2Award(item["reward2"]);
		m_quest.insert(make_pair(cfg.id, cfg));
	}

	const Json::Value *ra = fileParser.getMember("box.random");
	if (ra == NULL || !ra->isArray()) {
		error_log("random error");
		return false;
	}
	uint32_t box_rate = 0;
	for (size_t i = 0; i < ra->size(); ++i) {
		const Json::Value &item = ra->get(i, Json::Value(Json::nullValue));
		if (item.isNull() || !item.isObject()) {
			continue;
		}
		box_rate += item.get("rate", 0).asUInt();
		RandomQuestBoxRandom cfg;
		cfg.rate = box_rate;
		cfg.reward.Json2Award(item["reward"]);
		m_boxRandom.push_back(cfg);
	}

	const Json::Value *level = fileParser.getMember("box.level");
	if (level == NULL || !level->isArray()) {
		error_log("level error");
		return false;
	}
	for (size_t i = 0; i < level->size(); ++i) {
		const Json::Value &item = level->get(i, Json::Value(Json::nullValue));
		if (item.isNull() || !item.isObject()) {
			continue;
		}
		RandomQuestBoxLevel cfg;
		cfg.lv = item.get("lv", 0).asUInt();
		cfg.count = item.get("count", 0).asUInt();
		cfg.cost = item.get("cost", 0).asUInt();
		cfg.rs1 = item.get("rs1", 0).asUInt();
		cfg.rs2 = item.get("rs2", 0).asUInt();
		parseArray(item["skill"], cfg.skill);
		m_boxLevel.insert(make_pair(cfg.lv, cfg));
	}
	return true;
}

const RandomQuest* RandomQuestConfig::getQuestByLv(uint32_t lv) const {
	uint32_t id = lv * 100 + 1;
	if (Math::GetRandomInt(100) < 10) {
		id += 1;
	}
	map<uint32_t, RandomQuest>::const_iterator itr = m_quest.find(id);
	return itr == m_quest.end() ? NULL : &(itr->second);
}

const RandomQuest* RandomQuestConfig::getQuestById(uint32_t id) const {
	map<uint32_t, RandomQuest>::const_iterator itr = m_quest.find(id);
	return itr == m_quest.end() ? NULL : &(itr->second);
}

const RandomQuestReward* RandomQuestConfig::getReward(uint32_t id) const {
	map<uint32_t, RandomQuestReward>::const_iterator itr = m_reward.find(id);
	return itr == m_reward.end() ? NULL : &(itr->second);
}

const RandomQuestSoldier* RandomQuestConfig::getSoldier(uint32_t id) const {
	map<uint32_t, RandomQuestSoldier>::const_iterator itr = m_soldier.find(id);
	return itr == m_soldier.end() ? NULL : &(itr->second);
}

const RandomQuestBoxLevel* RandomQuestConfig::getBoxLevel(uint32_t lv) const {
	map<uint32_t, RandomQuestBoxLevel>::const_iterator itr = m_boxLevel.find(lv);
	return itr == m_boxLevel.end() ? NULL : &(itr->second);
}

const Award* RandomQuestConfig::getBoxRandom() const {
	if (m_boxRandom.empty()) {
		return NULL;
	}
	int m = m_boxRandom.back().rate;
	uint32_t r = Math::GetRandomInt(m == 0 ? 1 : m);
	for (size_t i = 0; i < m_boxRandom.size(); ++i) {
		if (r < m_boxRandom[i].rate) {
			return &(m_boxRandom[i].reward);
		}
	}
	return NULL;
}

bool RandomQuestConfig::randomReward(uint32_t id, uint32_t &id1, uint32_t &id2) {
	map<uint32_t, RandomQuest>::iterator itr = m_quest.find(id);
	if (itr == m_quest.end()) {
		error_log("id not exists id=%u", id);
		return false;
	}
	RandomQuest &cfg = itr->second;
	if (cfg.rate.size() < 2 || cfg.rateKey.size() < 2 || cfg.rate.size() != cfg.rateKey.size()) {
		error_log("rate error id=%u r=%u rk=%u", id, cfg.rate.size(), cfg.rateKey.size());
		return false;
	}
	uint32_t m = cfg.rate.back();
	if (m < 2) {
		error_log("rate error id=%u r=%u", id, m);
		return false;
	}
	set<uint32_t> ids;
	uint32_t ctrl = 0;
	while (ids.size() < 2) {
		uint32_t r = Math::GetRandomInt(m);
		for (size_t i = 0; i < cfg.rate.size(); ++i) {
			if (r < cfg.rate[i]) {
				ids.insert(cfg.rateKey[i]);
				break;
			}
		}
		if(++ctrl > 10) {
			error_log("ctrl error id=%u", id);
			return false;
		}
	}
	id1 = *ids.begin();
	id2 = *ids.rbegin();

	return true;
}

bool RandomQuestConfig::randomSoldier(uint32_t id, uint32_t &id1) {
	map<uint32_t, RandomQuest>::iterator itr = m_quest.find(id);
	if (itr == m_quest.end()) {
		error_log("id not exists id=%u", id);
		return false;
	}
	RandomQuest &cfg = itr->second;
	if (cfg.rate.empty() || cfg.rateKey.empty() || cfg.rate.size() != cfg.rateKey.size()) {
		error_log("rate error id=%u r=%u rk=%u", id, cfg.rate.size(), cfg.rateKey.size());
		return false;
	}
	uint32_t m = cfg.rate.back();
	uint32_t r = Math::GetRandomInt(m == 0 ? 1 : m);
	for (size_t i = 0; i < cfg.rate.size(); ++i) {
		if (r < cfg.rate[i]) {
			id1 = cfg.rateKey[i];
			return true;
		}
	}
	return false;
}
