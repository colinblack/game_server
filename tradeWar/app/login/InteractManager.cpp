/*
 * InteractManager.cpp
 *
 *  Created on: 2019年3月5日
 *      Author: Administrator
 */

#include "InteractManager.h"
#include "PlayerManager.h"

#define USER_INTERACT_SIZE 20
#define USER_INTERACT_TIMEOUT 604800

InteractManager::InteractManager() {
	m_ts = 0;
}
InteractManager::~InteractManager() {
}
bool InteractManager::doPacket(CNetPacket *packet) {
	return true;
}
inline bool cmpUser(const DataUserInteract &right, const DataUserInteract &left) {
	return right.ts < left.ts;
}
bool InteractManager::load(uint32_t uid) {
	CDataUserInteract dbc;
	dbc.Get(uid, m_data);
	vector<DataUserInteract>::iterator itr = m_data.begin();
	for (; itr != m_data.end(); ++itr) {
		if (CTime::GetDayInterval(itr->ts, Time::GetGlobalTime()) == 0) {
			m_daily.insert(itr->ouid);
		}
	}
	sort(m_data.begin(), m_data.end(), cmpUser);
	m_ts = Time::GetGlobalTime();
	return true;
}
bool InteractManager::getData(IBuffer *buff) {
	if (buff == NULL) {
		return false;
	}
	CDataUserInteract dbc;
	uint32_t osize = buff->GetSize();
	PACKET_ENCODE_BEGIN(buff);
	PACKET_ENCODE(UInt32, 0);
	uint32_t cnt = 0;
	uint32_t now_ts = Time::GetGlobalTime();
	vector<DataUserInteract>::iterator itr = m_data.begin();
	for (; itr != m_data.end();) {
		if (now_ts > itr->ts + USER_INTERACT_TIMEOUT) {
			dbc.Del(itr->uid, itr->ouid, itr->ts);
			itr = m_data.erase(itr);
			continue;
		}
		PACKET_ENCODE(UInt32, itr->ouid);
		PACKET_ENCODE(UInt32, itr->ts);
		PACKET_ENCODE(UInt32, itr->level);
		PACKET_ENCODE(UInt32, itr->help_type);
		PACKET_ENCODE(String, itr->username);
		PACKET_ENCODE(Byte, 0);
		PACKET_ENCODE(String, itr->pic);
		PACKET_ENCODE(Byte, 0);
		++itr;
		++cnt;
	}
	uint32_t nsize = buff->GetSize();
	if (!buff->SetSize(osize)) {
		return false;
	}
	PACKET_ENCODE(UInt32, cnt);
	if (!buff->SetSize(nsize)) {
		return false;
	}
	return true;
}
bool InteractManager::setData(uint32_t uid, uint32_t lv, uint32_t type, const string &name, const string &pic) {
	uint32_t my_uid = m_player->getUid();
	reset();
	if (m_daily.count(uid) || my_uid == uid) {
		return false;
	}
	m_daily.insert(uid);
	CDataUserInteract dbc;
	DataUserInteract data;
	data.uid = my_uid;
	data.ouid = uid;
	data.ts = Time::GetGlobalTime();
	data.level = lv;
	data.help_type = type;
	data.username = name;
	data.pic = pic;
	m_data.push_back(data);
	dbc.Add(data);
	while (m_data.size() > USER_INTERACT_SIZE) {
		vector<DataUserInteract>::iterator itr = m_data.begin();
		dbc.Del(itr->uid, itr->ouid, itr->ts);
		m_data.erase(itr);
	}
	return true;
}
bool InteractManager::checkDaily(uint32_t uid) {
	reset();
	set<uint32_t>::const_iterator itr = m_daily.find(uid);
	return itr != m_daily.end();
}
bool InteractManager::reset() {
	if (CTime::GetDayInterval(Time::GetGlobalTime(), m_ts) == 0) {
		return false;
	}
	m_ts = Time::GetGlobalTime();
	m_daily.clear();
	return true;
}
