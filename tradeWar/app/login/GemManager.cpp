/*
 * GemManager.cpp
 *
 *  Created on: 2019年1月4日
 *      Author: Administrator
 */

#include "GemManager.h"
#include "PlayerManager.h"

GemManager::GemManager() {
	m_power = 0;
	m_data.clear();
	m_count.clear();
}

GemManager::~GemManager() {
}

bool GemManager::doPacket(CNetPacket *packet) {
	return true;
}

bool GemManager::load(uint32_t uid) {
	int ret = 0;
	CDataGemPoint dbc;
	vector<DataGemPoint> datas;
	ret = dbc.Get(uid, datas);
	vector<DataGemPoint>::iterator itr = datas.begin();
	for (; itr != datas.end(); ++itr) {
		m_data.insert(make_pair(itr->id, *itr));
		addCount(itr->p1, 1);
		addCount(itr->p2, 1);
		addCount(itr->p3, 1);
		addCount(itr->p4, 1);
	}
	map<uint32_t, uint32_t>::iterator citr = m_count.begin();
	for (; citr != m_count.end(); ++citr) {
		m_power += getGemPower(citr->first) * citr->second;
	}
	m_player->getActManager()->addGem(m_power);
	m_player->getEm()->checkGemLockCount();
	return true;
}

bool GemManager::save(const DataGemPoint &data, bool isNew) {
	CDataGemPoint dbc;
	int ret = 0;
	if (isNew) {
		ret = dbc.Add(data);
	} else {
		ret = dbc.Set(data);
	}
	if (0 != ret) {
		error_log("save gem point error uid=%u id=%u ret=%d", data.uid, data.id, ret);
		return false;
	}
	return true;
}

bool GemManager::push() {
	CNetPacket sp;
	sp.uid = m_player->getUid();
	CBufferWriter writer(sp.GetBody());
	PACKET_ENCODE(Byte, PROTOCOL_CMD_EQUIPMENT);
	PACKET_ENCODE(Byte, PROTOCOL_SUBCMD_GEM_POINT_INFO);
	if (!encode(sp.GetBody())) {
		error_log("encode error uid=%u", m_player->getUid());
		return false;
	}
	PlayerManager::getInstance()->sendToAccess(&sp);
	return true;
}

bool GemManager::encode(IBuffer *buff) {
	CBufferWriter writer(buff);
	PACKET_ENCODE(UInt32, m_data.size());
	map<uint32_t, DataGemPoint>::iterator itr = m_data.begin();
	for (; itr != m_data.end(); ++itr) {
		DataGemPoint &item = itr->second;
		PACKET_ENCODE(UInt32, item.id);
		PACKET_ENCODE(UInt32, GEM_POINT_NUM);
		PACKET_ENCODE(UInt32, item.p1);
		PACKET_ENCODE(UInt32, item.p2);
		PACKET_ENCODE(UInt32, item.p3);
		PACKET_ENCODE(UInt32, item.p4);
	}
	return true;
}

bool GemManager::encode(uint32_t type, IBuffer *buff) {
	CBufferWriter writer(buff);
	if (m_data.count(type)) {
		DataGemPoint &item = m_data[type];
		PACKET_ENCODE(UInt32, item.id);
		PACKET_ENCODE(UInt32, GEM_POINT_NUM);
		PACKET_ENCODE(UInt32, item.p1);
		PACKET_ENCODE(UInt32, item.p2);
		PACKET_ENCODE(UInt32, item.p3);
		PACKET_ENCODE(UInt32, item.p4);
	} else {
		PACKET_ENCODE(UInt32, type);
		PACKET_ENCODE(UInt32, GEM_POINT_NUM);
		PACKET_ENCODE(UInt32, 0);
		PACKET_ENCODE(UInt32, 0);
		PACKET_ENCODE(UInt32, 0);
		PACKET_ENCODE(UInt32, 0);
	}
	return true;
}

bool GemManager::setPoint(uint32_t type, uint32_t point, uint32_t id) {
	bool isNew = m_data.count(type) == 0;
	DataGemPoint &item = m_data[type];
	if (isNew) {
		item.uid = m_player->getUid();
		item.id = type;
	}
	uint32_t *p = NULL;
	switch (point) {
	case 0:
		p = &item.p1;
		break;
	case 1:
		p = &item.p2;
		break;
	case 2:
		p = &item.p3;
		break;
	case 3:
		p = &item.p4;
		break;
	}
	if (p == NULL) {
		error_log("point error type=%u point=%u", type, point);
		return false;
	}
	uint32_t sub_power = 0;
	if (*p != 0) {
		m_player->getEm()->subGemLockCount(*p, 1);
		sub_power = getGemPower(*p);
	}
	uint32_t add_power = getGemPower(id);
	*p = id;
	save(item, isNew);
	uint32_t old_power = m_power;
	if (m_power > sub_power) {
		m_power -= sub_power;
	} else {
		m_power = 0;
	}
	m_power += add_power;
	if (old_power != m_power) {
		m_player->onCombatChange(m_power > old_power ? m_power - old_power : 0);
		m_player->getActManager()->addGem(m_power);
	}
	return true;
}

bool GemManager::getGem(map<byte, uint32_t> &gem) {
	map<uint32_t, DataGemPoint>::const_iterator itr = m_data.begin();
	map<uint32_t, uint32_t> stat;
	for (; itr != m_data.end(); ++itr) {
		const DataGemPoint &p = itr->second;
		if (stat.count(p.p1)) {
			stat[p.p1] += 1;
		} else {
			stat[p.p1] = 1;
		}
		if (stat.count(p.p2)) {
			stat[p.p2] += 1;
		} else {
			stat[p.p2] = 1;
		}
		if (stat.count(p.p3)) {
			stat[p.p3] += 1;
		} else {
			stat[p.p3] = 1;
		}
		if (stat.count(p.p4)) {
			stat[p.p4] += 1;
		} else {
			stat[p.p4] = 1;
		}
	}
	map<uint32_t, uint32_t>::iterator it = stat.begin();
	for (; it != stat.end(); ++it) {
		const EquipConfigItem *cfg = EquipmentConfig::getInstance()->getItemConfig(it->first);
		if (cfg == NULL) {
			continue;
		}
		for (uint32_t lv = 1; lv <= cfg->lv; ++lv) {
			if (gem.count(lv)) {
				gem[lv] += it->second;
			} else {
				gem[lv] = it->second;
			}
		}
	}
	return true;
}

uint32_t GemManager::getPower() {
	return m_power;
}

uint32_t GemManager::getGemPower(uint32_t id) {
	const EquipConfigItem *cfg = EquipmentConfig::getInstance()->getItemConfig(id);
	if (cfg == NULL) {
		return 0;
	}
	return cfg->power;
}

uint32_t GemManager::getCount(uint32_t type) {
	map<uint32_t, uint32_t>::iterator itr = m_count.find(type);
	if (itr == m_count.end()) {
		return 0;
	}
	return itr->second;
}

bool GemManager::addCount(uint32_t type, uint32_t count) {
	if (count == 0) {
		return false;
	}
	const EquipConfigItem *cfg = EquipmentConfig::getInstance()->getItemConfig(type);
	if (cfg == NULL) {
		return false;
	}
	map<uint32_t, uint32_t>::iterator itr = m_count.find(type);
	if (itr == m_count.end()) {
		m_count.insert(make_pair(type, count));
	} else {
		itr->second += count;
	}
	return true;
}
