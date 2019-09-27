/*
 * ChargeHistoryManager.cpp
 *
 *  Created on: 2019年1月3日
 *      Author: Administrator
 */

#include "ChargeHistoryManager.h"
#include "PlayerManager.h"

ChargeHistoryManager::ChargeHistoryManager() {
}

ChargeHistoryManager::~ChargeHistoryManager() {
}

bool ChargeHistoryManager::doPacket(CNetPacket *packet) {
	return true;
}

bool ChargeHistoryManager::load(uint32_t uid) {
	CDataChargeHistory dbc;
	vector<DataChargeHistory> datas;
	dbc.Get(uid, datas);
	for (vector<DataChargeHistory>::iterator itr = datas.begin(); itr != datas.end(); ++itr) {
		m_data.insert(make_pair(itr->ts, *itr));
	}
	return true;
}

bool ChargeHistoryManager::save(const DataChargeHistory &data, bool isNew) {
	int ret = 0;
	CDataChargeHistory dbc;
	if (isNew) {
		ret = dbc.Add(data);
	} else {
		ret = dbc.Set(data);
	}
	if (0 != ret) {
		error_log("save charge history error uid=%u ret=%d", data.uid, ret);
		return false;
	}
	return true;
}

bool ChargeHistoryManager::onLogin() {
	push();
	return true;
}

bool ChargeHistoryManager::doCharge(uint32_t money) {
	map<uint32_t, DataChargeHistory>::iterator itr = m_data.begin();
	for (; itr != m_data.end(); ++itr) {
		DataChargeHistory &item = itr->second;
		if (CTime::GetDayInterval(Time::GetGlobalTime(), item.ts) == 0) {
			item.cash += money;
			save(item, false);
			return true;
		}
	}
	DataChargeHistory &item = m_data[Time::GetGlobalTime()];
	item.uid = m_player->getUid();
	item.ts = Time::GetGlobalTime();
	item.cash = money;
	save(item, true);
	checkSize();
	push();
	return true;
}

uint32_t ChargeHistoryManager::getTotalCharge(uint32_t bts, uint32_t ets) {
	uint32_t total = 0;
	map<uint32_t, DataChargeHistory>::iterator itr = m_data.begin();
	for (; itr != m_data.end(); ++itr) {
		DataChargeHistory &item = itr->second;
		if (item.ts >= bts && item.ts <= ets) {
			total += item.cash;
		}
	}
	return total;
}

uint32_t ChargeHistoryManager::getDailyCharge() {
	map<uint32_t, DataChargeHistory>::iterator itr = m_data.begin();
	for (; itr != m_data.end(); ++itr) {
		DataChargeHistory &item = itr->second;
		if (CTime::GetDayInterval(item.ts, Time::GetGlobalTime()) == 0) {
			return item.cash;
		}
	}
	return 0;
}

uint32_t ChargeHistoryManager::getChargeDays(uint32_t bts, uint32_t ets) {
	uint32_t total = 0;
	map<uint32_t, DataChargeHistory>::iterator itr = m_data.begin();
	for (; itr != m_data.end(); ++itr) {
		DataChargeHistory &item = itr->second;
		if (item.ts >= bts && item.ts <= ets) {
			total += 1;
		}
	}
	return total;
}

bool ChargeHistoryManager::push() {
	CNetPacket sp;
	sp.uid = m_player->getUid();
	CBufferWriter writer(sp.GetBody());
	PACKET_ENCODE(Byte, PROTOCOL_CMD_ACTIVITY);
	PACKET_ENCODE(Byte, PROTOCOL_SUBCMD_ACTIVITY_CHARGE_HISTORY);
	PACKET_ENCODE(UInt32, m_data.size());
	map<uint32_t, DataChargeHistory>::iterator itr = m_data.begin();
	for (; itr != m_data.end(); ++itr) {
		DataChargeHistory &item = itr->second;
		PACKET_ENCODE(UInt32, item.ts);
		PACKET_ENCODE(UInt32, item.cash);
	}
	PlayerManager::getInstance()->sendToAccess(&sp);
	return true;
}

bool ChargeHistoryManager::checkSize() {
	CDataChargeHistory dbc;
	uint32_t uid = m_player->getUid();
	while (m_data.size() > DATA_CHARGE_HISTORY_LEN) {
		map<uint32_t, DataChargeHistory>::iterator itr = m_data.begin();
		dbc.Del(uid, itr->second.ts);
		m_data.erase(itr);
	}
	return true;
}
