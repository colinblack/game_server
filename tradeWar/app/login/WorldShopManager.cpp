/*
 * WorldShopManager.cpp
 *
 *  Created on: 2018年12月25日
 *      Author: Administrator
 */

#include "WorldShopManager.h"
#include "PlayerManager.h"
#include "ConfigInc.h"

WorldShopManager::WorldShopManager() {
	m_data.clear();
	m_ts = 0;
	m_attack_count = 0;
}

WorldShopManager::~WorldShopManager() {
}

bool WorldShopManager::doPacket(CNetPacket *p) {
	return true;
}

bool WorldShopManager::load(uint32_t uid) {
	int ret = 0;
	CDataState dbc;
	DataState data;
	data.uid = uid;
	data.id = PLAYER_DATA_STATE_WORLD_SHOP;
	ret = dbc.GetState(data.uid, data.id, data.data);
	if (0 == ret) {
		Json::Value v;
		Json::Reader reader;
		if (reader.parse(data.data, v)) {
			Json::GetUInt(v, "ts", m_ts);
			Json::GetUInt(v, "ac", m_attack_count);
			if (v.isMember("b") && v["v"].isArray()) {
				for (size_t i = 0; i < v["b"].size(); ++i) {
					m_data.push_back(v["b"].get(i, 0).asUInt());
				}
			}
		}
	} else if (R_ERR_NO_DATA == ret) {
		ret = dbc.AddState(data.uid, data.id, "");
	} else {
		return false;
	}
	if (reset()) {
		save();
	}
	return true;
}

bool WorldShopManager::save() {
	Json::Value v;
	v["ts"] = m_ts;
	v["ac"] = m_attack_count;
	v["b"] = Json::Value(Json::arrayValue);
	for (size_t i = 0; i < m_data.size(); ++i) {
		v["b"].append(static_cast<uint32_t>(m_data[i]));
	}
	CDataState dbc;
	DataState data;
	data.uid = m_player->getUid();
	data.id = PLAYER_DATA_STATE_WORLD_SHOP;
	data.data = Json::ToString(v);
	if (0 != dbc.SetState(data)) {
		return false;
	}
	return true;
}

bool WorldShopManager::reset() {
	if (CTime::GetDayInterval(Time::GetGlobalTime(), m_ts) == 0) {
		return false;
	}
	m_ts = Time::GetGlobalTime();
	uint32_t len = WorldConfig::getInstance()->getShopSize();
	if (m_data.size() != len) {
		m_data.resize(len);
	}
	for (uint32_t i = 0; i < len; ++i) {
		m_data[i] = 0;
	}
	m_attack_count = WORLD_MAX_ATTACK_COUNT;
	return true;
}

bool WorldShopManager::buy(uint32_t id) {
	reset();
	uint32_t len = WorldConfig::getInstance()->getShopSize();
	if (id > len) {
		error_log("id error uid=%u id=%u", m_player->getUid(), id);
		return false;
	}
	if (m_data.size() != len) {
		m_data.resize(len, 0);
	}
	const WorldConfigShop *cfg = WorldConfig::getInstance()->getShopItem(id);
	if (cfg == NULL) {
		error_log("cfg error uid=%u id=%u", m_player->getUid(), id);
		return false;
	}
	uint32_t index = id > 0 ? id - 1 : id;
	if (m_data[index] >= cfg->times) {
		error_log("times error uid=%u id=%u", m_player->getUid(), id);
		return false;
	}
	string code = "world_shop_" + CTrans::ITOS(id);
	ResourceCost cost;
	cost.p3 = cfg->require;
	if (!m_player->getRm()->useResources(cost, code)) {
		error_log("cost error uid=%u id=%u", m_player->getUid(), id);
		return false;
	}
	m_data[index] += 1;
	save();
	if (!m_player->doReward(&(cfg->reward), code)) {
		error_log("reward error uid=%u id=%u", m_player->getUid(), id);
		return false;
	}
	return true;
}

bool WorldShopManager::getInfo(IBuffer *buff) {
	if (buff == NULL) {
		return false;
	}
	reset();
	CBufferWriter writer(buff);
	uint32_t len = WorldConfig::getInstance()->getShopSize();
	PACKET_ENCODE(UInt32, len);
	for (uint32_t i = 0; i < len; ++i) {
		if (m_data.size() > i) {
			PACKET_ENCODE(UInt32, m_data[i]);
		} else {
			PACKET_ENCODE(UInt32, 0);
		}
	}
	return true;
}

bool WorldShopManager::useAttackCount() {
	reset();
	if (m_attack_count == 0) {
		return false;
	}
	m_attack_count -= 1;
	save();
	return true;
}

bool WorldShopManager::addAttackCount() {
	reset();
	if (m_attack_count == WORLD_MAX_ATTACK_COUNT) {
		return true;
	}
	if (m_attack_count + 1 > WORLD_MAX_ATTACK_COUNT) {
		m_attack_count = WORLD_MAX_ATTACK_COUNT;
	} else {
		m_attack_count += 1;
	}
	save();
	return true;
}

uint32_t WorldShopManager::getAttackCount() {
	reset();
	return m_attack_count;
}
