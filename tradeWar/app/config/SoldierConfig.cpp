/*
 * SoldierConfig.cpp
 *
 *  Created on: 2016-4-14
 *      Author: Administrator
 */

#include "SoldierConfig.h"
#include "CommonConfig.h"

SoldierConfig::SoldierConfig() {
}
SoldierConfig::~SoldierConfig() {
}
bool SoldierConfig::init(const string& path) {
	int ret = 0;
	string buffer;
	ret = File::Read(path, buffer);
	if (ret) {
		return false;
	}
	Json::Value content;
	Json::Reader reader;
	if (!reader.parse(buffer, content)) {
		return false;
	}
	Json::Value &soldier = content["soldiers"]["soldier"];
	if (soldier.isNull() || !soldier.isArray()) {
		return false;
	}
	for (size_t i = 0; i < soldier.size(); ++i) {
		Json::Value &item = soldier[i];
		string idStr, availableStr, lockLevelStr;
		if (!Json::GetString(item, "id", idStr)) {
			continue;
		}
		if (!Json::GetString(item, "available", availableStr)) {
			availableStr.clear();
		}
		if (String::s2i(availableStr, 0) == 0) {
			continue;
		}
		uint32_t id = CTrans::STOI(idStr.substr(1, idStr.length() - 1));
		SoldierItemConfig& mic = m_mapItemConfig[id];
		mic.id = id;
		Json::GetUInt(item, "type", mic.type);
		mic.q = item.get("q", 0).asUInt();
		parseArray(item["research"]["r1"], mic.research);
		parseArray(item["repairTime"], mic.repair_time);
		if (item.isMember("space2") && item["space2"].isArray() && item["space2"].size() == 2) {
			mic.space2 = item["space2"][0u].asUInt() * item["space2"][1u].asUInt();
		}
	}
	Json::Value &level_power = content["level_power"];
	if (level_power.isNull() || !level_power.isArray()) {
		error_log("level_power error");
		return false;
	}
	for (size_t i = 0; i < level_power.size(); ++i) {
		Json::Value &item = level_power[i];
		byte color = item.get("color", 0).asUInt();
		vector<uint32_t> &level_power_item = m_levelPower[color];
		level_power_item.clear();
		for (size_t j = 0; j < item["power"].size(); ++j) {
			level_power_item.push_back(item["power"][j].asUInt());
		}
	}
	return true;
}
const SoldierItemConfig* SoldierConfig::getItemConfig(uint32_t id) {
	map<uint32_t, SoldierItemConfig>::iterator iter = m_mapItemConfig.find(id);
	return (iter != m_mapItemConfig.end()) ? &iter->second : NULL;
}
bool SoldierConfig::getSoldierConfig(uint32_t id, uint32_t level, PropertySets& props) {
	const SoldierItemConfig* pCon = getItemConfig(id);
	if (pCon == NULL) {
		error_log("mic is NULL id=%u", id);
		return false;
	}
	props[AP_QUALITY].pui = pCon->q;
	return true;
}
bool SoldierConfig::getSoldierUpgradeCost(uint32_t id, uint32_t level, ResourceCost& cost) {
	const SoldierItemConfig* pCon = getItemConfig(id);
	if (pCon == NULL) {
		error_log("mic is NULL id=%u", id);
		return false;
	}
	if (!getArrValue(pCon->research, level, cost.r1)) {
		error_log("getArrValue");
	}
	return true;
}
bool SoldierConfig::getSoldierOriType(uint32_t id, uint32_t& oriType) {
	const SoldierItemConfig* pCon = getItemConfig(id);
	if (pCon == NULL) {
		error_log("mic is NULL id=%u", id);
		return false;
	}
	oriType = pCon->type;
	return true;
}
bool SoldierConfig::isExist(uint32_t id) {
	return m_mapItemConfig.find(id) != m_mapItemConfig.end();
}
uint32_t SoldierConfig::GetSoldierRepairTime(uint32_t type, uint32_t level) {
	const SoldierItemConfig* pConf = getItemConfig(type);
	if (pConf == NULL) {
		return 0;
	}
	return pConf->repair_time.size() > level ? pConf->repair_time[level] : 0;
}
uint32_t SoldierConfig::getLevelPower(byte color, uint32_t lv) {
	if (lv < 2) {
		return 0;
	}
	lv -= 2;
	map<byte, vector<uint32_t> >::iterator itr = m_levelPower.find(color);
	if (itr == m_levelPower.end()) {
		return 0;
	}
	if (lv >= itr->second.size()) {
		return 0;
	}
	return itr->second[lv];
}
bool SoldierConfig::getArrValue(const vector<uint32_t>& arr, uint32_t idx, uint32_t& value) {
	if (idx >= arr.size()) {
		error_log("level out of limit size=%u idx=%u", arr.size(), idx);
		return false;
	}
	value = *(arr.begin() + idx);
	return true;
}
