/*
 * ActivityTimeManager.cpp
 *
 *  Created on: 2018年12月3日
 *      Author: Administrator
 */

#include "ActivityTimeManager.h"
#include "PlayerManager.h"

ActivityTimeManager::ActivityTimeManager() {
}

ActivityTimeManager::~ActivityTimeManager() {
}

bool ActivityTimeManager::init() {
	m_data.clear();
	int ret = 0;
	string buff;
	string path = Config::GetValue("act_time");
	ret = File::Read(path, buff);
	if (0 != ret) {
		error_log("read file error path=%s", path.c_str());
		return false;
	}
	Json::Reader reader;
	Json::Value value;
	if (!reader.parse(buff, value)) {
		error_log("parse buff error buff=%s msg=%s", buff.c_str(), reader.getFormatedErrorMessages().c_str());
		return false;
	}
	if (value.isNull() || !value.isObject()) {
		error_log("value error buff=%s", buff.c_str());
		return false;
	}
	Json::Value::Members members(value.getMemberNames());
	for (Json::Value::Members::iterator itr = members.begin(); itr != members.end(); ++itr) {
		string key = *itr;
		ActivityTime item;
		item.id = CTrans::STOI(key);
		item.bts = value[key].get("bts", 0).asUInt();
		item.ets = value[key].get("ets", 0).asUInt();
		item.ver = value[key].get("ver", 0).asUInt();
		item.type = value[key].get("type", 0).asUInt();
		m_data.insert(make_pair(item.id, item));
	}
	return true;
}

bool ActivityTimeManager::reload() {
	init();
	PlayerManager::getInstance()->sendActTime();
	return true;
}

bool ActivityTimeManager::sendInfo(uint32_t uid) {
	CNetPacket sp;
	sp.uid = uid;
	CBufferWriter writer(sp.GetBody());
	writer.AppendByte(PROTOCOL_CMD_ACTIVITY);
	writer.AppendByte(PROTOCOL_SUBCMD_ACTIVITY_TIME);
	writer.AppendUInt32(0);
	uint32_t cnt = 0;
	map<uint32_t, ActivityTime>::iterator itr = m_data.begin();
	for (; itr != m_data.end(); ++itr) {
		const ActivityTime &act = itr->second;
		PACKET_ENCODE(UInt32, act.id);
		PACKET_ENCODE(UInt32, act.bts);
		PACKET_ENCODE(UInt32, act.ets);
		PACKET_ENCODE(UInt32, act.ver);
		PACKET_ENCODE(UInt32, act.type);
		++cnt;
	}
	memcpy(sp.GetBody()->GetNativeBuffer() + 2, (byte*)(&cnt), sizeof(cnt));
	PlayerManager::getInstance()->sendToAccess(&sp);
	return true;
}

bool ActivityTimeManager::isOpen(uint32_t id) const {
	map<uint32_t, ActivityTime>::const_iterator itr = m_data.find(id);
	return itr == m_data.end() ? false : itr->second.IsOpen();
}

bool ActivityTimeManager::isEnd(uint32_t id) const {
	map<uint32_t, ActivityTime>::const_iterator itr = m_data.find(id);
	if (itr == m_data.end()) {
		return false;
	}
	const ActivityTime &act_time = itr->second;
	if (act_time.ets > act_time.bts && act_time.ets < Time::GetGlobalTime()) {
		return true;
	}
	return false;
}

bool ActivityTimeManager::getValidId(vector<uint32_t> &ids) const {
	ids.clear();
	map<uint32_t, ActivityTime>::const_iterator itr = m_data.begin();
	for (; itr != m_data.end(); ++itr) {
		if (itr->second.IsOpen()) {
			ids.push_back(itr->first);
		}
	}
	return true;
}

uint32_t ActivityTimeManager::getVer(uint32_t id) const {
	map<uint32_t, ActivityTime>::const_iterator itr = m_data.find(id);
	return itr == m_data.end() ? 0u : itr->second.ver;
}

uint32_t ActivityTimeManager::getBts(uint32_t id) const {
	map<uint32_t, ActivityTime>::const_iterator itr = m_data.find(id);
	return itr == m_data.end() ? -1 : itr->second.ver;
}

uint32_t ActivityTimeManager::getOpenDay(uint32_t id) const {
	map<uint32_t, ActivityTime>::const_iterator itr = m_data.find(id);
	if (itr == m_data.end()) {
		return 0;
	}
	if (!itr->second.IsOpen()) {
		return 0;
	}
	return CTime::GetDayInterval(itr->second.bts, Time::GetGlobalTime()) + 1;
}

const ActivityTime* ActivityTimeManager::getActTime(uint32_t id) const {
	map<uint32_t, ActivityTime>::const_iterator itr = m_data.find(id);
	return itr == m_data.end() ? NULL : &(itr->second);
}
