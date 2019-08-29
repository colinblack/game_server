/*
 * EquipmentConfig.cpp
 *
 *  Created on: 2015-8-31
 *      Author: Administrator
 */

#include "EquipmentConfig.h"
#include "ConfigJson.h"

EquipmentConfig::EquipmentConfig() {
}

EquipmentConfig::~EquipmentConfig() {
}

template<typename T>
inline bool EquipmentConfig::getJsonValue(const Json::Value &v, T &d) {
	if (v.isString()) {
		d = String::s2i(v.asString(), 0);
	} else if (v.isIntegral()) {
		d = v.asInt();
	} else {
		d = 0;
	}
	return true;
}

bool EquipmentConfig::init(const string &path) {
	ConfigJson fileParser(path);
	if (!fileParser.Init()) {
		return false;
	}
	int ret = 0;
	string buffer;
	ret = File::Read(path, buffer);
	if (ret) {
		error_log("read error");
		return false;
	}
	Json::Value content;
	Json::Reader reader;
	if (!reader.parse(buffer, content)) {
		error_log("parse error");
		return false;
	}
	const Json::Value *equipment = fileParser.getMember("tools.tool");
	if (equipment == NULL || !equipment->isArray()) {
		error_log("tool error");
		return false;
	}
	for (size_t i = 0; i < equipment->size(); ++i) {
		const Json::Value &item = equipment->get(i, Json::nullValue);
		if (item.isNull() || !item.isObject()) {
			continue;
		}
		EquipConfigItem eic;
		getJsonValue(item["id"], eic.id);
		getJsonValue(item["type"], eic.type);
		getJsonValue(item["color"], eic.color);
		getJsonValue(item["lv"], eic.lv);
		if (eic.type == EQUIP_TYPE_GEM) {
			getJsonValue(item["junli"], eic.power);
			eic.gem_type = item.get("gemType", 0).asUInt();
			set<uint32_t> &pool = m_gem[eic.gem_type];
			pool.insert(eic.id);
		}
		m_data.insert(make_pair(eic.id, eic));
	}
	return true;
}

const EquipConfigItem* EquipmentConfig::getItemConfig(uint32_t type) {
	map<uint32_t, EquipConfigItem>::iterator hIter = m_data.find(type);
	return (hIter != m_data.end()) ? &(hIter->second) : NULL;
}

uint32_t EquipmentConfig::getLevel(uint32_t type) {
	map<uint32_t, EquipConfigItem>::iterator it = m_data.find(type);
	if (it != m_data.end()) {
		return it->second.lv;
	}
	return 0;
}

uint32_t EquipmentConfig::getGemId(uint16_t gem_type, uint16_t lv) {
	map<uint16_t, set<uint32_t> >::iterator itr = m_gem.find(gem_type);
	if (itr == m_gem.end()) {
		return 0;
	}
	if (itr->second.size() < lv) {
		return 0;
	}
	set<uint32_t>::const_iterator it = itr->second.begin();
	for (uint16_t i = 1; i < lv; ++i) {
		if (it == itr->second.end()) {
			return 0;
		}
		++it;
	}
	return *it;
}
