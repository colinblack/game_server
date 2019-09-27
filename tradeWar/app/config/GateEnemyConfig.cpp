/*
 * GateEnemyConfig.cpp
 *
 *  Created on: 2019年4月23日
 *      Author: Administrator
 */

#include "GateEnemyConfig.h"
#include "ConfigJson.h"

GateEnemyConfig::GateEnemyConfig() {

}

GateEnemyConfig::~GateEnemyConfig() {

}

bool GateEnemyConfig::init(const string &path) {
	ConfigJson fileParser(path);
	if (!fileParser.Init()) {
		return false;
	}
	const Json::Value *ptr = fileParser.getMember("enemies.hangUpEarningArr");
	if (ptr == NULL || !ptr->isArray()) {
		error_log("hangUpEarningArr error");
		return false;
	}
	for (size_t i = 0; i < ptr->size(); ++i) {
		const Json::Value &item = ptr->get(i, Json::Value::null);
		if (item.isNull()) {
			continue;
		}
		uint32_t id = item.get("id", 0).asUInt();
		uint32_t num = item.get("income", 0).asUInt();
		m_data.insert(make_pair(id, num));
	}
	return true;
}

uint32_t GateEnemyConfig::getData(uint32_t id) {
	map<uint32_t, uint32_t>::iterator itr = m_data.find(id);
	if (itr == m_data.end()) {
		return 0;
	}
	return itr->second;
}
