/*
 * VipConfig.cpp
 *
 *  Created on: 2016年9月23日
 *      Author: asdf
 */
#include "VipConfig.h"
#include "ConfigJson.h"

VipConfig::~VipConfig() {
}

VipConfig::VipConfig() {
	m_items.clear();
}

bool VipConfig::init(const string & path) {
	ConfigJson fileParser(path);
	if (!fileParser.Init()) {
		return false;
	}
	const Json::Value *detail = fileParser.getMember("vip.detail");
	if (detail == NULL || !detail->isArray()) {
		error_log("detail error");
		return false;
	}
	for (size_t i = 0; i < detail->size(); ++i) {
		const Json::Value &item = detail->get(i, Json::Value(Json::nullValue));
		VipConfigItem config;
		if (!Json::GetUInt(item, "id", config.id)) {
			error_log("id error");
			return false;
		}
		if (!Json::GetUInt(item, "ts", config.ts)) {
			error_log("ts error");
			return false;
		}
		config.box = item.get("box", 0).asUInt();
		if (!initRight(item["tq"], &(config.right))) {
			error_log("tq error");
			return false;
		}
		if (!item.isMember("data")) {
			error_log("data error");
			return false;
		}
		if (!config.award.Json2Award(item["data"]["reward"])) {
			error_log("reward error");
			return false;
		}
		if (!config.first.Json2Award(item["data"]["freward"])) {
			error_log("reward error");
			return false;
		}
		m_items[config.id] = config;
	}

	const Json::Value *gift = fileParser.getMember("vip.gift");
	if (gift == NULL || !gift->isArray()) {
		error_log("gift error");
		return false;
	}
	for (size_t i = 0; i < gift->size(); ++i) {
		const Json::Value &item = gift->get(i, Json::Value(Json::nullValue));
		if (item.isNull() || !item.isObject()) {
			error_log("item error");
			return false;
		}
		if (!item.isMember("data")) {
			error_log("data error");
			return false;
		}
		MonthGiftConfigItem cfg;
		cfg.id = item.get("id", 0).asUInt();
		cfg.box = item.get("box", 0).asUInt();
		cfg.reward.Json2Award(item["data"]["reward"]);
		m_gift.insert(make_pair(cfg.id, cfg));
	}
	return true;
}

bool VipConfig::initRight(const Json::Value &value, VipConftRight *pRight) {
	memset(pRight, 0, sizeof(VipConftRight));

	if (!value.isObject() || pRight == NULL) {
		return false;
	}

	Json::GetUInt(value, "harvest", pRight->harvest);
	Json::GetUInt(value, "boatres", pRight->boatres);
	Json::GetUInt(value, "offline", pRight->offline);
	Json::GetUInt(value, "lootAdd", pRight->lootadd);
	Json::GetUInt(value, "boattimes", pRight->boattimes);
	Json::GetUInt(value, "capacity", pRight->capacity);

	return true;
}

const VipConfigItem* VipConfig::getItem(uint32_t level) {
	map<uint32_t, VipConfigItem>::iterator iter = m_items.find(level);
	return (iter != m_items.end()) ? &(iter->second) : NULL;
}

uint32_t VipConfig::getTs(uint32_t level) {
	map<uint32_t, VipConfigItem>::const_iterator itr = m_items.find(level);
	if (itr == m_items.end()) {
		return 0;
	}
	return itr->second.ts;
}

uint32_t VipConfig::getHarvest(uint32_t level) {
	map<uint32_t, VipConfigItem>::const_iterator itr = m_items.find(level);
	if (itr == m_items.end()) {
		return 0;
	}
	return itr->second.right.harvest;
}

uint32_t VipConfig::getBoatRes(uint32_t level) {
	map<uint32_t, VipConfigItem>::const_iterator itr = m_items.find(level);
	if (itr == m_items.end()) {
		return 0;
	}
	return itr->second.right.boatres;
}

uint32_t VipConfig::getOffline(uint32_t level) {
	map<uint32_t, VipConfigItem>::const_iterator itr = m_items.find(level);
	if (itr == m_items.end()) {
		return 0;
	}
	return itr->second.right.offline;
}

uint32_t VipConfig::getLootAdd(uint32_t level) {
	map<uint32_t, VipConfigItem>::const_iterator itr = m_items.find(level);
	if (itr == m_items.end()) {
		return 0;
	}
	return itr->second.right.lootadd;
}

uint32_t VipConfig::getBoatTimes(uint32_t level) {
	map<uint32_t, VipConfigItem>::const_iterator itr = m_items.find(level);
	if (itr == m_items.end()) {
		return 0;
	}
	return itr->second.right.boattimes;
}

uint32_t VipConfig::getCapacity(uint32_t level) {
	map<uint32_t, VipConfigItem>::const_iterator itr = m_items.find(level);
	if (itr == m_items.end()) {
		return 0;
	}
	return itr->second.right.capacity;
}

const MonthGiftConfigItem* VipConfig::getGift(uint32_t id) const {
	map<byte, MonthGiftConfigItem>::const_iterator itr = m_gift.find(id);
	if (itr == m_gift.end()) {
		return NULL;
	}
	return &(itr->second);
}

uint32_t VipConfig::getGiftSize() const {
	return m_gift.size();
}
