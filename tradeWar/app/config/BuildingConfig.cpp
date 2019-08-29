/*
 * BuildingConfig.cpp
 *
 *  Created on: 2015-8-31
 *      Author: Administrator
 */
#include "BuildingConfig.h"

BuildingConfig::BuildingConfig() {
}
BuildingConfig::~BuildingConfig() {
}
bool BuildingConfig::initBuilding(const string & path) {
	int ret = 0;
	string buffer;
	ret = File::Read(path, buffer);
	if (ret) {
		return false;
	}
	Json::Reader reader;
	Json::Value content;
	if (!reader.parse(buffer, content)) {
		return false;
	}
	Json::Value &buildings = content["buildings"]["building"];
	if (buildings.isNull() || !buildings.isArray()) {
		return false;
	}
	for (size_t i = 0; i < buildings.size(); ++i) {
		Json::Value &item = buildings[i];
		uint32_t id = GetUInt(item["id"]);
		if (id == 0) {
			error_log("id error index=%u data=%s", i, Json::ToString(item).c_str());
			return false;
		}
		string typeStr;
		if (!Json::GetString(item, "type", typeStr)) {
			typeStr.clear();
		}
		uint32_t type = 0;
		if (!setBuildingTypeInt(typeStr, type)) {
			error_log("type error index=%u data=%s", i, Json::ToString(item).c_str());
			return false;
		}
		BuildingItemConfig& bic = m_mapItemConfig[id];
		bic.id = id;
		bic.group = GetUInt(item["group"]);
		bic.type = type;
		bic.color = GetUInt(item["level"]);
		bic.rely.reserve(128);
		bic.produce.reserve(128);
		bic.cost.reserve(128);
		Json::Value &pathingCost = item["pathingCost"];
		if (pathingCost.isNull() || !pathingCost.isObject()) {
			continue;
		}
	}
	Json::Value &building_power = content["building_power"];
	if (building_power.isNull() || !building_power.isArray()) {
		error_log("building_power error");
		return false;
	}
	for (size_t i = 0; i < building_power.size(); ++i) {
		Json::Value &item = building_power[i];
		uint32_t lv = 0;
		Json::GetUInt(item, "level", lv);
		vector<uint32_t> &powers = m_buildingPower[lv];
		for (size_t j = 0; j < item["power"].size(); ++j) {
			powers.push_back(item["power"][j].asUInt());
		}
	}
	return true;
}
bool BuildingConfig::initBuildingData(const string & path) {
	int ret = 0;
	string buffer;
	ret = File::Read(path, buffer);
	if (ret) {
		return false;
	}
	Json::Reader reader;
	Json::Value content;
	if (!reader.parse(buffer, content)) {
		return false;
	}
	Json::Value &buildings = content["buildings"]["building"];
	if (buildings.isNull() || !buildings.isArray()) {
		return false;
	}
	for (size_t i = 0; i < buildings.size(); ++i) {
		Json::Value &item = buildings[i];
		uint32_t level = GetUInt(item["level"]);
		uint32_t id = GetUInt(item["id"]);
		BuildingItemConfig &bic = m_mapItemConfig[id];
		uint32_t produceVal = GetUInt(item["produce"]);
		uint32_t attribute = GetUInt(item["attribute"]);
		vector<uint32_t>& pVec = bic.produce;
		if (level + 1 > pVec.size()) {
			pVec.resize(level + 1);
		}
		pVec[level] = produceVal;
		vector<uint32_t>& aVec = bic.attribute;
		if (level + 1 > aVec.size()) {
			aVec.resize(level + 1);
		}
		aVec[level] = attribute;
		PropertySets& props = m_mapBasePropsConfig[getBuildingIdx(id, level)];
		parseProp(item, "capacity", props[AP_MAX_CAPACITY].pui);
		parseProp(item, "hd", props[AP_HD].pui);
		parseProp(item, "hp", props[AP_MAX_HP].pui);
		parseProp(item, "md", props[AP_MD].pui);
		parseProp(item, "range", props[AP_RANGE].pui);
		parseProp(item, "splash", props[AP_SPLASH].pui);
		parseProp(item, "damage", props[AP_HA].pui);
		parseProp(item, "rate", props[AP_RP].pui);
		props[AP_BP].pui = 0;
		Json::Value &costs = item["costs"]["cost"];
		if (costs.isNull() || !costs.isObject()) {
			error_log("costs error");
			return false;
		}
		const Json::Value &foodJson = costs["food"];
		if (!foodJson.isNull() && foodJson.isArray()) {
			vector<BuildingBuildCost>& rcVec = bic.cost;
			if (level + 1 > rcVec.size()) {
				rcVec.resize(level + 1);
			}
			BuildingBuildCost& rc = rcVec[level];
			rc.r1 = foodJson.size() > 0 ? foodJson[0u].asUInt() : 0;
			rc.r2 = foodJson.size() > 1 ? foodJson[1u].asUInt() : 0;
		}
		const Json::Value &re = costs["re"];
		if (!re.isNull()) {
			const Json::Value &relyJson = re["data"];
			if (relyJson.isArray()) {
				vector<RelyBuildingAll>& rbVec = bic.rely;
				if (level + 1 > rbVec.size()) {
					rbVec.resize(level + 1);
				}
				RelyBuildingAll& rb = rbVec[level];
				for (size_t j = 0; j < relyJson.size(); ++j) {
					if (relyJson[j].isArray() && relyJson[j].size() >= 3) {
						RelyBuilding rrr;
						rrr.type = relyJson[j][0u].asUInt();
						rrr.id = relyJson[j][1u].asUInt();
						rrr.level = relyJson[j][2u].asUInt();
						rb.data.push_back(rrr);
						if (rrr.type == RELY_BUILDING_GATE) {
							map<uint32_t, uint32_t> &ccc = m_gateBuilding[rrr.level];
							ccc[id] = level;
						}
					}
				}
			}
		}
	}
	return true;
}
bool BuildingConfig::init() {
	if (!initBuilding(Config::GetValue(CONFIG_BUILDING_COMMON))) {
		error_log("building common config init fail");
		return false;
	}
	if (!initBuildingData(Config::GetValue(CONFIG_BUILDING_DATA))) {
		error_log("building data config init fail");
		return false;
	}
	return true;
}
bool BuildingConfig::setBuildingTypeInt(const string& typeStr, unsigned& type) {
	if (typeStr == "storage") {
		type = BUILDING_TYPE_STORAGE;
	} else if (typeStr == "resource") {
		type = BUILDING_TYPE_RESOURCE;
	} else if (typeStr == "special") {
		type = BUILDING_TYPE_SPECIAL;
	} else if (typeStr == "wall") {
		type = BUILDING_TYPE_WALL;
	} else if (typeStr == "shrine") {
		type = BUILDING_TYPE_SHRINE;
	} else if (typeStr == "tower") {
		type = BUILDING_TYPE_TOWER;
	} else if (typeStr == "trap") {
		type = BUILDING_TYPE_TRAP;
	} else if (typeStr == "wuhu") {
		type = BUILDING_TYPE_WUHU;
	} else if (typeStr == "wuhutown") {
		type = BUILDING_TYPE_WUHUTOWN;
	} else if (typeStr == "decoration") {
		type = BUILDING_TYPE_DECORATION;
	} else {
		return false;
	}
	return true;
}
void BuildingConfig::parseProp(const Json::Value &item, const string &key, uint32_t &value) {
	if (item.isMember(key)) {
		if (item[key].isString()) {
			value = CTrans::STOI(item[key].asString());
			return;
		} else if (item[key].isIntegral()) {
			value = item[key].asUInt();
			return;
		}
	}
	value = 0;
}
uint32_t BuildingConfig::GetUInt(const Json::Value &value) {
	if (value.isString()) {
		return CTrans::STOI(value.asString());
	} else if (value.isIntegral()) {
		return value.asUInt();
	}
	return 0;
}
const BuildingItemConfig * BuildingConfig::getItemConfig(uint32_t id) {
	map<uint32_t, BuildingItemConfig>::iterator iter = m_mapItemConfig.find(id);
	if (iter != m_mapItemConfig.end()) {
		return &(iter->second);
	}
	error_log("get_item_config_fail&bid=%u", id);
	return NULL;
}
bool BuildingConfig::getBaseProp(uint32_t id, uint32_t lv, PropertySets& sPropSets) {
	map<uint32_t, PropertySets>::iterator iter = m_mapBasePropsConfig.find(getBuildingIdx(id, lv));
	if (iter == m_mapBasePropsConfig.end()) {
		error_log("getBaseProp_fail&id=%u&level=%u", id, lv);
		return false;
	}
	PropertySets& addProp = iter->second;
	PropertySets::iterator iterProp = addProp.begin();
	for (; iterProp != addProp.end(); ++iterProp) {
		sPropSets[iterProp->first].pi = iterProp->second.pi;
	}
	return true;
}
bool BuildingConfig::getProduce(uint32_t id, uint32_t lv, uint32_t& produce) {
	const BuildingItemConfig* bic = getItemConfig(id);
	if (bic != NULL) {
		const vector<uint32_t>& pVec = bic->produce;
		if (pVec.size() > lv) {
			produce = pVec[lv];
			return true;
		}
	}
	error_log("get_produce_fail&bid=%u&level=%u", id, lv);
	return false;
}
bool BuildingConfig::getAttribute(uint32_t id, uint32_t lv, uint32_t& attribute) {
	const BuildingItemConfig* bic = getItemConfig(id);
	if (bic != NULL) {
		const vector<uint32_t>& pVec = bic->attribute;
		if (pVec.size() > lv) {
			attribute = pVec[lv];
			return true;
		}
	}
	error_log("get_attribute_fail&bid=%u&level=%u", id, lv);
	return false;
}
const RelyBuildingAll* BuildingConfig::getRelyBuilding(uint32_t id, uint32_t lv) {
	const BuildingItemConfig* bic = getItemConfig(id);
	if (bic != NULL) {
		const vector<RelyBuildingAll>& rbVec = bic->rely;
		if (rbVec.size() > lv) {
			return &rbVec[lv];
		}
	}
	error_log("get_build_rely_fail&bid=%u&level=%u", id, lv);
	return NULL;
}
bool BuildingConfig::getRelyBuildingGate(uint32_t gateid, map<uint32_t, uint32_t> &ids) {
	map<uint32_t, map<uint32_t, uint32_t> >::iterator itr = m_gateBuilding.begin();
	for (; itr != m_gateBuilding.end(); ++itr) {
		if (itr->first <= gateid) {
			map<uint32_t, uint32_t> &data = itr->second;
			map<uint32_t, uint32_t>::iterator it = data.begin();
			for (; it != data.end(); ++it) {
				if(!ids.count(it->first)) {
					ids[it->first] = it->second;
				} else {
					if (ids[it->first] < it->second) {
						ids[it->first] = it->second;
					}
				}
			}
		}
	}
	return true;
}
const BuildingBuildCost* BuildingConfig::getBuildCost(uint32_t id, uint32_t lv) {
	const BuildingItemConfig* bic = getItemConfig(id);
	if (bic != NULL) {
		const vector<BuildingBuildCost>& rcVec = bic->cost;
		if (rcVec.size() > lv) {
			return &(rcVec[lv]);
		}
	}
	error_log("get_build_cost_fail&bid=%u&level=%u", id, lv);
	return NULL;
}
bool BuildingConfig::getFootprint(uint32_t id, uint32_t& dx, uint32_t& dy) {
	return false;
}
uint32_t BuildingConfig::getBuildingPower(uint32_t color, uint32_t lv) {
	map<byte, vector<uint32_t> >::iterator itr = m_buildingPower.find(color);
	if (itr == m_buildingPower.end()) {
		return 0;
	}
	if (lv >= itr->second.size()) {
		return 0;
	}
	return itr->second[lv];
}
