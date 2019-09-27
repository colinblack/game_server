/*
 * OpenServerConfig.cpp
 *
 *  Created on: 2018年12月10日
 *      Author: Administrator
 */

#include "OpenServerConfig.h"
#include "ConfigJson.h"
#include "CommonConfig.h"

OpenServerConfig::OpenServerConfig() {
}

OpenServerConfig::~OpenServerConfig() {
}

bool OpenServerConfig::init(const string &path) {
	ConfigJson fileParser(path);
	if (!fileParser.Init()) {
		return false;
	}
	const Json::Value *data = fileParser.getMember("configType");
	if (data == NULL || !data->isArray()) {
		error_log("data error");
		return false;
	}
	for (size_t i = 0; i < data->size(); ++i) {
		const Json::Value &item = data->get(i, Json::Value(Json::nullValue));
		if (item.isNull() || !item.isObject()) {
			continue;
		}
		if (!parseTask(item["mainTask"], m_week[i])) {
			error_log("mainTask error");
			return false;
		}
		if (!parseTask(item["dailyTask"], m_daily[i])) {
			error_log("dailyTask error");
			return false;
		}
		if (!parseReward(item["payReward"], m_pay[i])) {
			error_log("payReward error");
			return false;
		}
		if (!parseReward(item["freeReward"], m_free[i])) {
			error_log("freeReward error");
			return false;
		}
	}
	return true;
}

bool OpenServerConfig::parseTask(const Json::Value &v, vector<OpenServerConfigTask> &t) {
	if (v.isNull() || !v.isArray()) {
		return false;
	}
	for (size_t i = 0; i < v.size(); ++i) {
		const Json::Value &item = v.get(i, Json::Value(Json::nullValue));
		if (item.isNull() || !item.isObject()) {
			continue;
		}
		OpenServerConfigTask task;
		task.type = item.get("taskType", 0).asUInt();
		if (item["num"].isArray()) {
			parseArray(item["num"], task.require);
		} else {
			task.require.push_back(item.get("num", 0).asUInt());
		}
		if (item["reward"].isArray()) {
			parseArray(item["reward"], task.reward);
		} else {
			task.reward.push_back(item.get("reward", 0).asUInt());
		}
		t.push_back(task);
	}
	return true;
}

bool OpenServerConfig::OpenServerConfig::parseReward(const Json::Value &v, vector<OpenServerConfigReward> &t) {
	if (v.isNull() || !v.isArray()) {
		return false;
	}
	for (size_t i = 0; i < v.size(); ++i) {
		const Json::Value &item = v.get(i, Json::Value(Json::nullValue));
		if (item.isNull() || !item.isObject()) {
			continue;
		}
		OpenServerConfigReward reward;
		reward.id = item.get("level", 0).asUInt();
		reward.reward.Json2Award(item);
		t.push_back(reward);
	}
	return true;
}

bool OpenServerConfig::randomDaily(uint32_t type, set<uint32_t> &ids) {
	map<uint32_t, vector<OpenServerConfigTask> >::const_iterator mitr = m_daily.find(type);
	if (mitr == m_daily.end()) {
		return false;
	}
	if (mitr->second.size() < 3) {
		return false;
	}
	while (ids.size() < 3) {
		uint32_t id = Math::GetRandomInt(mitr->second.size());
		if (!ids.count(id)) {
			ids.insert(id);
		}
	}
	return true;
}

bool OpenServerConfig::getWeekClass(uint32_t type, uint32_t id, uint32_t cnt, uint32_t &c) {
	map<uint32_t, vector<OpenServerConfigTask> >::const_iterator mitr = m_week.find(type);
	if (mitr == m_week.end()) {
		return NULL;
	}
	if (mitr->second.size() <= id) {
		return false;
	}
	vector<OpenServerConfigTask>::const_iterator itr = mitr->second.begin() + id;
	for (size_t i = 0; i < itr->require.size(); ++i) {
		if (cnt >= itr->require[i]) {
			c = i + 1;
		}
	}
	return true;
}

const OpenServerConfigTask* OpenServerConfig::getDaily(uint32_t type, uint32_t id) const {
	map<uint32_t, vector<OpenServerConfigTask> >::const_iterator mitr = m_daily.find(type);
	if (mitr == m_daily.end()) {
		return NULL;
	}
	if (mitr->second.size() <= id) {
		return NULL;
	}
	vector<OpenServerConfigTask>::const_iterator itr = mitr->second.begin();
	return &(*(itr + id));
}

const OpenServerConfigTask* OpenServerConfig::getWeek(uint32_t type, uint32_t id) const {
	map<uint32_t, vector<OpenServerConfigTask> >::const_iterator mitr = m_week.find(type);
	if (mitr == m_week.end()) {
		return NULL;
	}
	if (mitr->second.size() <= id) {
		return NULL;
	}
	vector<OpenServerConfigTask>::const_iterator itr = mitr->second.begin();
	return &(*(itr + id));
}

const OpenServerConfigReward* OpenServerConfig::getReward(uint32_t type, uint32_t id, bool pay) const {
	if (!pay) {
		map<uint32_t, vector<OpenServerConfigReward> >::const_iterator mitr = m_free.find(type);
		if (mitr == m_free.end()) {
			return NULL;
		}
		vector<OpenServerConfigReward>::const_iterator itr = mitr->second.begin();
		for (; itr != mitr->second.end(); ++itr) {
			if (id == itr->id) {
				return &(*itr);
			}
		}
	} else {
		map<uint32_t, vector<OpenServerConfigReward> >::const_iterator mitr = m_pay.find(type);
		if (mitr == m_pay.end()) {
			return NULL;
		}
		vector<OpenServerConfigReward>::const_iterator itr = mitr->second.begin();
		for (; itr != mitr->second.end(); ++itr) {
			if (id == itr->id) {
				return &(*itr);
			}
		}
	}
	return NULL;
}
