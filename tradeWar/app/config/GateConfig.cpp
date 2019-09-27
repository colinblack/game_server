/*
 * GateConfig.cpp
 *
 *  Created on: 2015-12-10
 *      Author: Administrator
 */

#include "GateConfig.h"
#include "ConfigJson.h"

GateConfig::GateConfig() {
	m_defend_count = 3;
}

GateConfig::~GateConfig() {
}

bool GateConfig::initTrade(const string & path) {
	ConfigJson fileParser(path);
	if (!fileParser.Init()) {
		return false;
	}
	const Json::Value *gate = fileParser.getMember("gates.gate");
	if (gate == NULL || !gate->isArray()) {
		error_log("gate error");
		return false;
	}
	map<uint32_t, uint32_t> chapter;
	vector<uint32_t> levels;
	int tmp = 0;
	for (size_t i = 0; i < gate->size(); ++i) {
		const Json::Value &item = gate->get(i, Json::nullValue);
		if (item.isNull() || !item.isObject()) {
			continue;
		}
		string leveStr;
		if (!Json::GetString(item, "level", leveStr)) {
			continue;
		}
		string chapterStr;
		if (!Json::GetString(item, "chapter", chapterStr)) {
			continue;
		}
		uint32_t c = String::s2i(chapterStr, 0);
		uint32_t lv = String::s2i(leveStr, 0);
		//解析章节id和levels映射
		if(c != 0 && c != tmp) {
			if(levels.size() == 0) {
				tmp = c;
			}else {
				level_map.insert(make_pair(tmp, levels));
				tmp = c;
				levels.clear();
			}
		}
		levels.push_back(lv);

		if (!chapter.count(c)) {
			chapter[c] = lv;
		} else if (chapter[c] < lv) {
			chapter[c] = lv;
		}
	}
	//添加最后一个章节和levels的映射
	if(tmp != 0) {
		level_map.insert(make_pair(tmp, levels));
	}

	map<uint32_t, uint32_t>::iterator itr = chapter.begin();
	for (; itr != chapter.end(); ++itr) {
		m_trade.insert(make_pair(itr->second, itr->first));
	}

	const Json::Value *gateStar = fileParser.getMember("gates.gateStar");
	if(gateStar == NULL || !gateStar->isArray()) {
		error_log("gateStar error");
		return false;
	}
	for(int i = 0; i < gateStar->size(); ++i) {
		GateStar gate_star;
		const Json::Value &item = gateStar->get(i, Json::nullValue);
		if(item.isNull() || !item.isObject()) {
			continue;
		}

		string chapterStr;
		if(!Json::GetString(item, "chapter", chapterStr)) {
			continue;
		}
		gate_star.chapter = String::s2i(chapterStr, 0);
		Json::Value star_reward = item.get("starReward", Json::nullValue);
		if(star_reward.isNull() || !star_reward.isArray()) {
			continue;
		}
		for(int j = 0; j < star_reward.size(); ++j) {
			StarReward reward;
			Json::Value reward_item = star_reward.get(j, Json::nullValue);
			if(!reward_item.isNull() || reward_item.isObject()) {
				reward.award.Json2Award(reward_item["reward"]);
			}

			reward.id = reward_item.get("id", 0).asUInt();
			reward.star = reward_item.get("star", 0).asUInt();
			reward.box = reward_item.get("box", 0).asUInt();
			gate_star.rewards[j] = reward;
		}
		star_box.insert(make_pair(gate_star.chapter, gate_star));
	}
	return true;
}

bool GateConfig::initDefend(const string & path)
{
	ConfigJson fileParser(path);
	if (!fileParser.Init()) {
		return false;
	}
	const Json::Value *gate = fileParser.getMember("gates.gate");
	if (gate == NULL || !gate->isArray()) {
		error_log("gate error");
		return false;
	}

	for (size_t i = 0; i < gate->size(); ++i) {
		const Json::Value &item = gate->get(i, Json::Value(Json::nullValue));
		if (item.isNull() || !item.isObject()) {
			continue;
		}
		DefendGateItem cfg;
		cfg.id = item.get("id", 0).asUInt();
		cfg.lv = item.get("level", 0).asUInt();
		cfg.award.Json2Award(item.get("reward", Json::Value(Json::nullValue)));
		m_defend.insert(make_pair(cfg.id, cfg));
	}

	const Json::Value *gate_count = fileParser.getMember("gates.count");
	if (gate_count != NULL && gate_count->isIntegral()) {
		m_defend_count = gate_count->asUInt();
	}

	return true;
}

uint32_t GateConfig::isOpenMap(uint32_t level) {
	map<uint32_t, uint32_t>::iterator itr = m_trade.find(level);
	if (itr == m_trade.end()) {
		return 0;
	}
	return itr->second;
}

const DefendGateItem* GateConfig::getDefend(uint16_t lv) {
	map<uint32_t, DefendGateItem>::const_iterator itr = m_defend.find(lv);
	if (itr == m_defend.end()) {
		return NULL;
	}
	return &(itr->second);
}

uint32_t GateConfig::getChapterCnt() {
	return star_box.size();
}

bool GateConfig::getLevels(uint32_t chapter_id, vector<uint32_t> &data) {
	if(chapter_id > GateConfig::getInstance()->getChapterCnt()) {
		error_log("chapter id error %d", chapter_id);
		return false;
	}
	data = level_map[chapter_id];
	return true;
}
uint32_t GateConfig::getStarlimit(uint32_t chap_id, uint32_t index) {
	if(chap_id > GateConfig::getInstance()->getChapterCnt()) {
			error_log("chapter id error %d", chap_id);
			return 0;
		}
	if(index >= CHAPTER_BOX_CNT) {
			error_log("star box index error:%d", index);
			return 0;
		}
	return star_box[chap_id].rewards[index].star;
}

uint32_t GateConfig::getchapIdByLevel(uint32_t level) {
	int chapId = 0;
	for(map<uint32_t, vector<uint32_t> >::iterator it = level_map.begin(); it != level_map.end(); ++it) {
		if(std::count(it->second.begin(), it->second.end(), level)) {
			chapId = it->first;
			break;
		}
	}
	return chapId;
}

bool GateConfig::getReward(uint32_t chap_id, uint32_t id, Award &reward) {
	if(chap_id > GateConfig::getInstance()->getChapterCnt()) {
		error_log("chapter id error %d", chap_id);
		return false;
	}
	if(id > CHAPTER_BOX_CNT) {
		error_log("star box index error:%d", id);
		return false;
	}
	reward = star_box[chap_id].rewards[id-1].award;
	return true;
}

uint32_t GateConfig::getBox(uint32_t chap_id, uint32_t id) {
	if(chap_id > GateConfig::getInstance()->getChapterCnt()) {
		error_log("chapter id error %d", chap_id);
		return 0;
	}
	if(id > CHAPTER_BOX_CNT) {
		error_log("star box index error:%d", id);
		return 0;
	}
	return star_box[chap_id].rewards[id-1].box;
}
