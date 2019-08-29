/*
 * TransportManager.cpp
 *
 *  Created on: 2018年1月15日
 *      Author: Administrator
 */

#include <fstream>
#include "TransportManager.h"
#include "ProtocolBoat.h"
#include "all_server.h"
#include "BoatConfig.h"

TransportManager::TransportManager() {
	m_runing.clear();
}

TransportManager::~TransportManager() {
}

bool TransportManager::doPacket(CNetPacket *p) {
	switch (p->subCmd) {
	case PROTOCOL_SUBCMD_TRANSPORT_START:
		doStart(p);
		break;
	case PROTOCOL_SUBCMD_TRANSPORT_SEARCH:
		doSearch(p);
		break;
	case PROTOCOL_SUBCMD_TRANSPORT_ROB:
		doRob(p);
		break;
	case PROTOCOL_SUBCMD_TRANSPORT_SPEED_UP:
		doSpeedUp(p);
		break;
	case PROTOCOL_SUBCMD_TRANSPORT_TARGET:
		doGetTarget(p);
		break;
	}
	debug_log("uid=%u,cmd=%u,sub=%u", p->uid, static_cast<uint32_t>(p->cmd), static_cast<uint32_t>(p->subCmd));
	return true;
}

bool TransportManager::doLoad() {
	string path = Config::GetValue(CONFIG_MERCHANT_SHIP);
	if (path.empty()) {
		error_log("path error!");
		return false;
	}
	fstream input(path.c_str(), ios::in | ios::binary);
	if (!input.good()) {
		error_log("open file error path=%s", path.c_str());
		return false;
	}
	MerchantShip::MerchantShip pdata;
	if (!pdata.ParseFromIstream(&input)) {
		error_log("parse error path=%s", path.c_str());
		return false;
	}
	for (int i = 0; i < pdata.items_size(); ++i) {
		RuningShip ship;
		ship.Parse(pdata.items(i));
		uint64_t key = (static_cast<uint64_t>(ship.uid) << 32) | ship.id;
		m_runing.insert(make_pair(key, ship));
		set<uint64_t> &slv = m_level[ship.lv];
		slv.insert(key);
	}

	for (int i = 0; i < pdata.wait_size(); ++i) {
		m_wait.insert(make_pair(pdata.wait(i).uid(), pdata.wait(i).key()));
	}

	CBoatConfig::getInstance()->getAllNpc(m_npc);
	debug_log("npc len %u", m_npc.size());
	return true;
}
bool TransportManager::doSave() {
	string path = Config::GetValue(CONFIG_MERCHANT_SHIP);
	fstream output(path.c_str(), ios::out | ios::binary);
	if (!output.good()) {
		error_log("open file error path=%s", path.c_str());
		return false;
	}

	MerchantShip::MerchantShip pdata;
	for (map<uint64_t, RuningShip>::iterator itr = m_runing.begin(); itr != m_runing.end(); ++itr) {
		itr->second.Serialize(pdata.add_items());
	}

	for (map<uint32_t, uint64_t>::iterator itr = m_wait.begin(); itr != m_wait.end(); ++itr) {
		MerchantShip::MerchantShipWait *w = pdata.add_wait();
		w->set_uid(itr->first);
		w->set_key(itr->second);
	}

	if (!pdata.SerializeToOstream(&output)) {
		error_log("serialize error path=%s", path.c_str());
		return false;
	}

	return true;
}
void TransportManager::onSecondTimer() {
	set<uint64_t> del;
	map<uint64_t, RuningShip>::iterator itr = m_runing.begin();
	for (; itr != m_runing.end(); ++itr) {
		if (itr->second.endTs < Time::GetGlobalTime()) {
			del.insert(itr->first);
		}
	}
	for (set<uint64_t>::iterator it = del.begin(); it != del.end(); ++it) {
		set<uint64_t> &slv = m_level[m_runing[*it].lv];
		slv.erase(*it);
		m_runing.erase(*it);
	}
}

bool TransportManager::doStart(CNetPacket *p) {
	CBoatAsrvStartProtocol proto;
	if (!proto.Decode(p->GetBody())) {
		return false;
	}
	uint64_t key = (static_cast<uint64_t>(proto.uid) << 32) | proto.id;
	RuningShip &ship = m_runing[key];
	ship.uid = proto.uid;
	ship.id = proto.id;
	ship.totalRes = proto.res;
	ship.endTs = proto.ts;
	ship.lv = proto.lv;
	ship.lostRes = 0;
	set<uint64_t> &slv = m_level[ship.lv];
	slv.insert(key);
	debug_log("uid=%u,lv=%u,res=%u,id=%u,ets=%u,num=%u", ship.uid, ship.lv, ship.totalRes, ship.id, ship.endTs, m_runing.size());
	return true;
}

bool TransportManager::doSpeedUp(CNetPacket *p) {
	CBoatAsrvSpeedUpProtocol proto;
	if (!proto.Decode(p->GetBody())) {
		error_log("decode error");
		return false;
	}
	uint64_t uid = proto.uid;
	uint32_t id = proto.id;
	uint64_t key = (uid << 32) | id;
	map<uint64_t, RuningShip>::iterator itr = m_runing.find(key);
	if (itr == m_runing.end()) {
		error_log("boat not exists uid=%u id=%u", uid, id);
		return false;
	}
	itr->second.endTs = proto.ts;

	debug_log("uid=%u,id=%u,ts=%u", uid, id, proto.ts);

	return true;
}

bool TransportManager::doSearch(CNetPacket *p) {
	CBoatAsrvSearchProtocol proto;
	if (!proto.Decode(p->GetBody())) {
		return false;
	}
	uint32_t uid = proto.uid;
	uint32_t ulv = proto.lv;
	uint32_t ts = proto.ts;

	if (ts > 20) {
		do {
			int r = Math::GetRandomInt(100);
			if (ulv > 1 && r < 10) {
				ulv -= 1;
				break;
			}
			if (r < 90) {
				break;
			}
			if (ulv < 30 && r < 100) {
				ulv += 1;
			}
		} while (false);
	}

	uint64_t oldWait = 0;
	if (m_wait.count(uid) && m_runing.count(m_wait[uid])) {
		oldWait = m_wait[uid];
		m_runing[m_wait[uid]].waitTs = 0;
		m_wait.erase(uid);
	}
	vector<uint64_t> pool;

	uint32_t lv = ulv;
	if (m_npc.count(lv)) {
		const vector<uint64_t> &npc = m_npc[lv];
		pool.insert(pool.end(), npc.begin(), npc.end());
	}
	bool need_user = true;
	int r = Math::GetRandomInt(100);
	if (lv < 3) {
		if (r < 90) {
			need_user = false;
		}
	} else {
		if (r < 20) {
			need_user = false;
		}
	}
	if (pool.empty()) {
		need_user = true;
	}
	if (need_user && m_level.count(lv)) {
		const set<uint64_t> &users = m_level[lv];
		for (set<uint64_t>::iterator itr = users.begin(); itr != users.end(); ++itr) {
			RuningShip &ship = m_runing[*itr];
			if (ship.waitTs > Time::GetGlobalTime()) {
				error_log("wait ts uid=%u ouid=%u lv=%u", uid, ship.uid, lv);
				continue;
			}
			if (ship.uid == uid || ship.uid == 0) {
				error_log("zone uid=%u ouid=%u lv=%u", uid, ship.uid, lv);
				continue;
			}
			if (ship.totalRes == 0) {
				error_log("not res uid=%u ouid=%u lv=%u", uid, ship.uid, lv);
				continue;
			}
			if (static_cast<float>(ship.lostRes) / static_cast<float>(ship.totalRes) * 100.0f >= 50.0f) {
				error_log("not res uid=%u ouid=%u lv=%u", uid, ship.uid, lv);
				continue;
			}
			if (*itr == oldWait) {
				error_log("waiting uid=%u ouid=%u lv=%u", uid, ship.uid, lv);
				continue;
			}
			pool.push_back(*itr);
		}
	} else {
		error_log("user empty lv=%u", lv);
	}

	if (pool.empty()) {
		return false;
	}

	uint32_t target_uid = 0;
	uint32_t target_id = 0;

	uint64_t key = pool[Math::GetRandomInt(pool.size())];
	if (m_runing.count(key)) {
		RuningShip &tar = m_runing[key];
		tar.waitTs = Time::GetGlobalTime() + 600;
		m_wait[uid] = key;
		target_uid = tar.uid;
		target_id = tar.id;
	} else {
		target_uid = key & 0xFFFFFFFF;
		target_id = 1;
	}

	CNetPacket sp;
	sp.uid = uid;
	CBufferWriter writer(sp.GetBody());
	writer.AppendByte(PROTOCOL_CMD_BOAT);
	writer.AppendByte(PROTOCOL_SUBCMD_MERCHANT_ASRV_TARGET);
	writer.AppendUInt32(target_uid);
	writer.AppendUInt32(target_id);
	AsrvServer::getInstance()->sendToLogin(&sp);

	debug_log("uid=%u,ouid=%u,oid=%u,oldWait=%llu,ts=%u,lv=%u,need_user=%d",
			uid, target_uid, target_id, oldWait, ts, lv, need_user);

	return true;
}

bool TransportManager::doRob(CNetPacket *p) {
	CBoatAsrvRobProtocol proto;
	if (!proto.Decode(p->GetBody())) {
		error_log("decode error");
		return false;
	}
	uint64_t uid = proto.uid;
	uint32_t id = proto.id;
	uint64_t key = (uid << 32) | id;
	uint32_t res = proto.res;
	map<uint64_t, RuningShip>::iterator itr = m_runing.find(key);
	if (itr == m_runing.end()) {
		error_log("boat not exists uid=%u id=%u", uid, id);
		return false;
	}
	if (m_wait.count(uid)) {
		m_wait.erase(uid);
	}
	RuningShip &ship = itr->second;
	ship.waitTs = 0;
	ship.lostRes = std::min(static_cast<float>(ship.totalRes) * 0.5f, static_cast<float>(ship.lostRes + res));
	ship.challenge.insert(uid);
	debug_log("uid=%u,id=%u,res=%u,tres=%u,lres=%u", uid, id, res, ship.totalRes, ship.lostRes);
	return true;
}

bool TransportManager::doGetTarget(CNetPacket *p) {
	uint32_t uid = p->uid;
	uint32_t target_uid = 0;
	uint32_t target_id = 0;
	CBoatRevengeProtocol proto;
	if (!proto.Decode(p->GetBody())) {
		error_log("decode error");
		onGetTarget(uid, target_uid, target_id);
		return false;
	}

	for (uint32_t id = 1; id <= MAX_MERCHANT_NUM; ++id) {
		uint64_t key = (static_cast<uint64_t>(proto.target_uid) << 32) | id;
		if (!m_runing.count(key)) {
			error_log("no run uid=%u ouid=%u", uid, proto.target_uid);
			continue;
		}
		const RuningShip &ship = m_runing[key];
		if (ship.waitTs > Time::GetGlobalTime()) {
			error_log("wait ts uid=%u ouid=%u", uid, ship.uid);
			continue;
		}
		if (ship.uid == uid) {
			continue;
		}
		if (ship.totalRes == 0) {
			error_log("not res uid=%u ouid=%u", uid, ship.uid);
			continue;
		}
		if (static_cast<float>(ship.lostRes) / static_cast<float>(ship.totalRes) * 100.0f >= 50.0f) {
			error_log("not res uid=%u ouid=%u", uid, ship.uid);
			continue;
		}
		target_uid = ship.uid;
		target_id = id;
	}
	onGetTarget(uid, target_uid, target_id);

	return true;
}

void TransportManager::onGetTarget(uint32_t uid, uint32_t target_uid, uint32_t target_id) {
	CNetPacket sp;
	sp.uid = uid;
	CBufferWriter writer(sp.GetBody());
	writer.AppendByte(PROTOCOL_CMD_BOAT);
	writer.AppendByte(PROTOCOL_SUBCMD_MERCHANT_ASRV_REVENGE);
	writer.AppendUInt32(target_uid);
	writer.AppendUInt32(target_id);
	AsrvServer::getInstance()->sendToLogin(&sp);
	debug_log("uid=%u tuid=%u tid=%u", uid, target_uid, target_id);
}
