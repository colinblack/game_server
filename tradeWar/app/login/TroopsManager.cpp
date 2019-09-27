/*
 * TroopsManager.cpp
 *
 *  Created on: 2018年7月16日
 *      Author: Administrator
 */

#include "TroopsManager.h"
#include "PlayerManager.h"
#include "ProtocolInc.h"
#include "SoldierConfig.h"
#include "BoatConfig.h"
#include "SkillConfig.h"
#include "DataGuard.h"

#define TROOPS_DEFAULT_VEHICLE 301
#define TROOPS_DEFAULT_VEHICLE_MIN_X 3
#define TROOPS_DEFAULT_VEHICLE_MAX_X 4
#define TROOPS_DEFAULT_VEHICLE_MIN_Y 2
#define TROOPS_DEFAULT_VEHICLE_MAX_Y 5

TroopsManager::TroopsManager(): m_defend_score(0) {
}

TroopsManager::~TroopsManager() {
}

bool TroopsManager::doPacket(CNetPacket* packet) {
	switch (packet->subCmd) {
	case PROTOCOL_SUNCMD_TROOPS_GET_DEFEND:
		sendDefend();
		break;
	case PROTOCOL_SUNCMD_TROOPS_SET_DEFEND:
		doSetDefend(packet);
		break;
	case PROTOCOL_SUNCMD_TROOPS_GET_ATTACK:
		sendAttack();
		break;
	case PROTOCOL_SUNCMD_TROOPS_SET_ATTACK:
		doSetAttack(packet);
		break;
	default:
		error_log("unknow subcmd uid=%u subcmd=%d", packet->uid, static_cast<int>(packet->subCmd));
		break;
	}
	return true;
}

bool TroopsManager::load(uint32_t uid) {
	initAttack();
	initDefend();
	calcDefendScore();
	return true;
}

bool TroopsManager::doSend() {
	sendAttack();
	sendDefend();
	return true;
}

bool TroopsManager::packDefend(IBuffer *buff) {
	if (buff == NULL) {
		return false;
	}
	PACKET_ENCODE_BEGIN(buff);
	PACKET_ENCODE(UInt32, m_defend.size());
	map<uint32_t, uint32_t>::iterator itr = m_defend.begin();
	for (; itr != m_defend.end(); ++itr) {
		PACKET_ENCODE(UInt32, itr->second);
		PACKET_ENCODE(UInt32, itr->first);
	}
	return true;
}

bool TroopsManager::packAttack(IBuffer *buff) {
	if (buff == NULL) {
		return false;
	}
	PACKET_ENCODE_BEGIN(buff);
	PACKET_ENCODE(UInt32, m_attack.size());
	vector<TroopsInfo>::iterator itr = m_attack.begin();
	for (; itr != m_attack.end(); ++itr) {
		PACKET_ENCODE(UInt32, itr->id);
		PACKET_ENCODE(UInt32, itr->value);
	}
	return true;
}

bool TroopsManager::setData(uint32_t uid, const Json::Value &data) {
	if (data.isNull() || !data.isObject()) {
		error_log("data error");
		return false;
	}
	CDataTroops dbc;

	//def
	const Json::Value &def = data.get(CTrans::ITOS(e_TROOPS_TYPE_DEFEND), Json::Value(Json::nullValue));
	if (!def.isNull() && def.isArray()) {
		for (size_t i = 0; i < def.size(); ++i) {
			TroopsInfo item;
			item.FromJson(def.get(i, Json::Value(Json::nullValue)));
			m_defend.insert(make_pair(item.value, item.id));
		}
	}
	CDataGuard dbGuard;
	map<uint32_t, uint32_t>::iterator itr = m_defend.begin();
	for (; itr != m_defend.end(); ++itr) {
		DataGuard data;
		data.uid = uid;
		data.id = itr->first;
		data.soldier = itr->second;
		dbGuard.Add(data);
	}

	//attack
	const Json::Value &att = data.get(CTrans::ITOS(e_TROOPS_TYPE_ATTACK), Json::Value(Json::nullValue));
	if (!att.isNull() && att.isArray()) {
		for (size_t i = 0; i < att.size(); ++i) {
			TroopsInfo item;
			item.FromJson(att.get(i, Json::Value(Json::nullValue)));
			m_attack.push_back(item);
		}
	}
	Json::Value attv = Json::Value(Json::arrayValue);
	vector<TroopsInfo>::iterator it = m_attack.begin();
	for (; it != m_attack.end(); ++it) {
		attv.append(it->ToJson());
	}
	DataTroops attd;
	attd.uid = uid;
	attd.id = e_TROOPS_TYPE_ATTACK;
	attd.data = Json::ToString(attv);
	dbc.AddTroops(attd);

	return true;
}

bool TroopsManager::subAttack(const vector<pair<uint32_t, uint32_t> > &data) {
	if (data.empty()) {
		return true;
	}

	bool chg = false;
	vector<pair<uint32_t, uint32_t> >::const_iterator it = data.begin();
	for (; it != data.end(); ++it) {
		unsigned id = it->first;
		unsigned count = it->second;

		vector<TroopsInfo>::iterator itr = m_attack.begin();
		for (; itr != m_attack.end(); ++itr) {
			if (itr->id == id) {
				if (count >= itr->value) {
					m_attack.erase(itr);
				} else {
					itr->value -= count;
				}
				debug_log("uid=%u,id=%u,count=%u", m_player->getUid(), id, count);
				chg = true;
				break;
			}
		}
	}
	if (chg) {
		updateAttack(false);
		sendAttack();
	}

	return true;
}

bool TroopsManager::delAttack(uint32_t id) {
	bool chg = false;
	vector<TroopsInfo>::iterator itr = m_attack.begin();
	for (; itr != m_attack.end(); ++itr) {
		if (itr->id == id) {
			debug_log("uid=%u,id=%u", m_player->getUid(), id);
			m_attack.erase(itr);
			chg = true;
			break;
		}
	}
	if (chg) {
		updateAttack(false);
		sendAttack();
	}
	debug_log("uid=%u,id=%u", m_player->getUid(), id);
	return true;
}

bool TroopsManager::setSkill(uint32_t id, uint32_t count) {
	const SkillConfig *cfg = CSkillConfig::getInstance()->getConfig(id);
	if (cfg == NULL || count == 0) {
		return false;
	}

	set<uint32_t> skills;
	vector<TroopsInfo>::iterator itr = m_attack.begin();
	for (; itr != m_attack.end(); ++itr) {
		const SkillConfig *cfg = CSkillConfig::getInstance()->getConfig(itr->id);
		if (cfg != NULL) {
			skills.insert(itr->id);
		}
	}
	if (skills.size() == 3 || skills.count(id)) {
		return true;
	}

	TroopsInfo item;
	item.id = id;
	item.value = count;
	m_attack.push_back(item);

	updateAttack(false);

	sendAttack();

	return true;
}

uint32_t TroopsManager::getAttackCount(uint32_t type) {
	uint32_t count = 0;
	vector<TroopsInfo>::iterator itr = m_attack.begin();
	for (; itr != m_attack.end(); ++itr) {
		if ((type != 0 && itr->id == type) || (type == 0 && itr->id != 0)) {
			count += itr->value;
		}
	}
	return count;
}

uint32_t TroopsManager::getDefendCount(uint32_t type) {
	uint32_t count = 0;
	map<uint32_t, uint32_t>::iterator itr = m_defend.begin();
	for (; itr != m_defend.end(); ++itr) {
		if ((type != 0 && itr->second == type) || (type == 0 && itr->second != 0)) {
			count++;
		}
	}
	return count;
}

uint32_t TroopsManager::getDefendScore() {
	return m_defend_score;
}

bool TroopsManager::doSetAttack(CNetPacket* packet) {
	uint32_t uid = packet->uid;
	CSoldierTroopsProtocol protocol;
	if (!protocol.Decode(&(packet->body))) {
		error_log("CSoldierTroopsProtocol decode error uid=%u", uid);
		onSetAttackResp(R_ERROR);
		return false;
	}
	m_attack.clear();
	vector<pair<uint32_t, uint32_t> >::iterator itr = protocol.troops.begin();
	for (; itr != protocol.troops.end(); ++itr) {
		TroopsInfo item;
		item.id = itr->first;
		item.value = itr->second;
		m_attack.push_back(item);
	}
	updateAttack(false);
	onSetAttackResp(R_SUCCESS);
	m_player->getTaskManager()->onTroops();
	return true;
}

bool TroopsManager::doSetDefend(CNetPacket* packet) {
	uint32_t uid = packet->uid;
	CSoldierTroopsProtocol protocol;
	if (!protocol.Decode(&(packet->body))) {
		error_log("CSoldierTroopsProtocol decode error uid=%u", uid);
		onSetDefendResp(R_ERROR);
		return false;
	}

	set<uint32_t> ids;
	vector<pair<uint32_t, uint32_t> >::iterator itr = protocol.troops.begin();
	for (; itr != protocol.troops.end(); ++itr) {
		uint32_t id = itr->second;
		uint32_t soldier = itr->first;
		if (m_defend.count(id)) {
			if (m_defend[id] != soldier) {
				m_defend[id] = soldier;
				updateDefend(id, soldier, e_DBAsyncTypeSet);
			}
		} else {
			m_defend.insert(make_pair(id, soldier));
			updateDefend(id, soldier, e_DBAsyncTypeAdd);
		}
		ids.insert(id);
	}

	CDataGuard dbc;
	map<uint32_t, uint32_t>::iterator it = m_defend.begin();
	for (; it != m_defend.end();) {
		if (ids.count(it->first)) {
			++it;
			continue;
		}
		updateDefend(it->first, it->second, e_DBAsyncTypeDel);
		m_defend.erase(it++);
	}

	calcDefendScore();

	m_player->calcAutoRewardRes();

	onSetDefendResp(R_SUCCESS);

	m_player->getTaskManager()->onTroops();

	m_player->getActivenessManager()->onZhen();

	debug_log("uid=%u,num=%u", uid, protocol.troops.size());

	return true;
}

bool TroopsManager::onSetAttackResp(byte ret) {
	CNetPacket sp;
	sp.uid = m_player->getUid();
	CBufferWriter writer(&(sp.body));
	writer.AppendByte(PROTOCOL_CMD_TROOPS);
	writer.AppendByte(PROTOCOL_SUNCMD_TROOPS_SET_ATTACK);
	writer.AppendByte(ret);

	return PlayerManager::getInstance()->sendToAccess(&sp);
}

bool TroopsManager::onSetDefendResp(byte ret) {
	CNetPacket sp;
	sp.uid = m_player->getUid();
	CBufferWriter writer(&(sp.body));
	writer.AppendByte(PROTOCOL_CMD_TROOPS);
	writer.AppendByte(PROTOCOL_SUNCMD_TROOPS_SET_DEFEND);
	writer.AppendByte(ret);

	return PlayerManager::getInstance()->sendToAccess(&sp);
}

bool TroopsManager::initAttack() {
	uint32_t uid = m_player->getUid();
	CDataTroops dbc;
	string data;
	int ret = dbc.GetTroops(uid, e_TROOPS_TYPE_ATTACK, data);
	if (R_SUCCESS == ret) {
		Json::Reader reader;
		Json::Value v;
		if (reader.parse(data, v) && v.isArray()) {
			for (size_t i = 0; i < v.size(); ++i) {
				TroopsInfo item;
				item.FromJson(v[i]);
				m_attack.push_back(item);
			}
		}
	} else if (R_ERR_NO_DATA == ret) {
		updateAttack(true);
	}

	return true;
}

bool TroopsManager::initDefend() {
	uint32_t uid = m_player->getUid();
	CDataGuard dbc;
	vector<DataGuard> datas;
	dbc.Get(uid, datas);
	vector<DataGuard>::iterator itr = datas.begin();
	for (; itr != datas.end(); ++itr) {
		m_defend.insert(make_pair(itr->id, itr->soldier));
	}
	checkDefend();
	return true;
}

bool TroopsManager::updateAttack(bool isNew) {
	Json::Value v = Json::Value(Json::arrayValue);
	vector<TroopsInfo>::iterator itr = m_attack.begin();
	for (; itr != m_attack.end(); ++itr) {
		v.append(itr->ToJson());
	}
	uint32_t uid = m_player->getUid();
	CDataTroops dbc;
	DataTroops data;
	data.uid = uid;
	data.id = e_TROOPS_TYPE_ATTACK;
	data.data = Json::ToString(v);
	int ret = isNew ? dbc.AddTroops(data) : dbc.SetTroops(data);
	if (ret != 0) {
		error_log("add or set troop error ret=%d uid=%u", ret, uid);
		return false;
	}
	return true;
}

bool TroopsManager::updateDefend(uint32_t id, uint32_t soldier, uint32_t type) {
	int ret = 0;
	CDataGuard dbc;
	DataGuard data;
	data.uid = m_player->getUid();
	data.id = id;
	data.soldier = soldier;
	switch (type) {
	case e_DBAsyncTypeAdd:
		ret = dbc.Add(data);
		break;
	case e_DBAsyncTypeSet:
		ret = dbc.Set(data);
		break;
	case e_DBAsyncTypeDel:
		ret = dbc.Del(data.uid, data.id);
		break;
	}
	if (0 != ret) {
		error_log("set guard error uid=%u ret=%d", data.uid, ret);
		return false;
	}
	return true;
}

bool TroopsManager::sendAttack() {
	CNetPacket sp;
	sp.uid = m_player->getUid();
	CBufferWriter writer(&(sp.body));
	writer.AppendByte(PROTOCOL_CMD_TROOPS);
	writer.AppendByte(PROTOCOL_SUNCMD_TROOPS_GET_ATTACK);
	writer.AppendUInt32(m_attack.size());
	vector<TroopsInfo>::iterator itr = m_attack.begin();
	for (; itr != m_attack.end(); ++itr) {
		writer.AppendUInt32(itr->id);
		writer.AppendUInt32(itr->value);
	}
	PlayerManager::getInstance()->sendToAccess(&sp);

	return true;
}

bool TroopsManager::sendDefend() {
	CNetPacket sp;
	sp.uid = m_player->getUid();
	CBufferWriter writer(&(sp.body));
	writer.AppendByte(PROTOCOL_CMD_TROOPS);
	writer.AppendByte(PROTOCOL_SUNCMD_TROOPS_GET_DEFEND);
	writer.AppendUInt32(m_defend.size());
	map<uint32_t, uint32_t>::iterator itr = m_defend.begin();
	for (; itr != m_defend.end(); ++itr) {
		writer.AppendUInt32(itr->second);
		writer.AppendUInt32(itr->first);
	}
	PlayerManager::getInstance()->sendToAccess(&sp);

	return true;
}

bool TroopsManager::checkDefend() {
	map<uint32_t, uint32_t>::iterator itr = m_defend.begin();
	for (; itr != m_defend.end(); ++itr) {
		const SoldierItemConfig *cfg = SoldierConfig::getInstance()->getItemConfig(itr->second);
		if (cfg == NULL) {
			continue;
		}
		if (cfg->type == SOLDIER_TYPE_VEHICLE) {
			return true;
		}
	}
	const Soldier *default_vehicle = m_player->getSoldierManager()->getSoldierByType(TROOPS_DEFAULT_VEHICLE);
	if (default_vehicle == NULL) {
		return false;
	}
	for (uint32_t y = TROOPS_DEFAULT_VEHICLE_MIN_Y; y <= TROOPS_DEFAULT_VEHICLE_MAX_Y; ++y) {
		for (uint32_t x = TROOPS_DEFAULT_VEHICLE_MIN_X; x <= TROOPS_DEFAULT_VEHICLE_MAX_X; ++x) {
			uint32_t id = y * 100 + x;
			if (m_defend.count(id)) {
				updateDefend(id, 0, e_DBAsyncTypeDel);
				m_defend.erase(id);
			}
		}
	}
	uint32_t id = TROOPS_DEFAULT_VEHICLE_MIN_Y * 100 + TROOPS_DEFAULT_VEHICLE_MIN_X;
	m_defend.insert(make_pair(id, TROOPS_DEFAULT_VEHICLE));
	updateDefend(id, TROOPS_DEFAULT_VEHICLE, e_DBAsyncTypeAdd);
	return true;
}

bool TroopsManager::calcDefendScore() {
	uint32_t power = 0;
	uint32_t uid = m_player->getUid();
	const SoldierItemConfig *cfg = NULL;
	map<uint32_t, uint32_t>::iterator itr = m_defend.begin();
	for (; itr != m_defend.end(); ++itr) {
		uint32_t sid = itr->second % 10000;
		cfg = SoldierConfig::getInstance()->getItemConfig(sid);
		if (cfg == NULL) {
			error_log("id not exists uid=%u id=%u", uid, sid);
			continue;
		}
		if (cfg->q == 1) {
			power += cfg->space2;
		} else if (cfg->q == 2) {
			power += cfg->space2 * 2;
		} else if (cfg->q == 3) {
			power += cfg->space2 * 3;
		} else if (cfg->q == 4) {
			power += cfg->space2 * 4;
		}
		if (itr->second > 10000) {
			uint32_t wid = itr->second % 10000000 / 10000;
			cfg = SoldierConfig::getInstance()->getItemConfig(wid);
			if (cfg != NULL) {
				power += cfg->q * 2;
			}
		}
		if (itr->second >= 10000000) {
			uint32_t wid = itr->second / 10000000;
			cfg = SoldierConfig::getInstance()->getItemConfig(wid);
			if (cfg != NULL) {
				power += cfg->q * 2;
			}
		}
	}
	m_defend_score = power;
	m_player->getActManager()->addSoldierScore(power);
	return true;
}
