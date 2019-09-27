/*
 * SevenDaysConfig.cpp
 *
 *  Created on: 2018年9月7日
 *      Author: rein
 */

#include "SevenDaysConfig.h"
#include "Award.h"
#include "ConfigJson.h"

SevenDaysConfig::SevenDaysConfig() {
}

SevenDaysConfig::~SevenDaysConfig() {
}

bool SevenDaysConfig::init(const string &path) {
	ConfigJson fileParser(path);
	if (!fileParser.Init()) {
		return false;
	}
	const Json::Value *sevenDays = fileParser.getMember("sevenDays");
	if (sevenDays == NULL || !sevenDays->isArray()) {
		error_log("sevenDays error");
		return false;
	}
	for (size_t i = 0; i < sevenDays->size(); ++i) {
		const Json::Value &item = sevenDays->get(i, Json::Value(Json::nullValue));
		if (item.isNull()) {
			continue;
		}
		byte id = item.get("id", 0xff).asUInt();
		if (id == 0xff) {
			continue;
		}
		Award award;
		if (!award.Json2Award(item["reward"])) {
			continue;
		}
		m_data.insert(make_pair(id, award));
	}

	return true;
}

bool SevenDaysConfig::initSign(const string &path) {
	ConfigJson fileParser(path);
	if (!fileParser.Init()) {
		return false;
	}
	const Json::Value *sevenDays = fileParser.getMember("sevenDays");
	if (sevenDays == NULL || !sevenDays->isArray()) {
		error_log("sevenDays error");
		return false;
	}
	for (size_t i = 0; i < sevenDays->size(); ++i) {
		const Json::Value &item = sevenDays->get(i, Json::Value(Json::nullValue));
		if (item.isNull()) {
			continue;
		}
		byte id = item.get("id", 0xff).asUInt();
		if (id == 0xff) {
			continue;
		}
		SignReward award;
		if (!award.award.Json2Award(item["reward"])) {
			continue;
		}
		award.type = item.get("type", 0).asUInt();

		m_sign.insert(make_pair(id, award));
	}

	return true;
}

const Award* SevenDaysConfig::getAward(byte id) {
	map<byte, Award>::iterator itr = m_data.find(id);
	if (itr == m_data.end()) {
		return NULL;
	}
	return &(itr->second);
}

const SignReward* SevenDaysConfig::getSign(byte id) {
	map<byte, SignReward>::iterator itr = m_sign.find(id);
	if (itr == m_sign.end()) {
		return NULL;
	}
	return &(itr->second);
}

uint32_t SevenDaysConfig::getCount() {
	return static_cast<uint32_t>(m_data.size());
}

