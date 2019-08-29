/*
 * SoldierRecoverTrain.cpp
 *
 *  Created on: 2018年7月28日
 *      Author: Administrator
 */

#include "SoldierRecoverTrain.h"
#include "PlayerManager.h"
#include "SoldierConfig.h"

bool SoldierRecoverTrain::doPacket(CNetPacket *packet) {
	switch (packet->subCmd) {
	case PROTOCOL_SUBCMD_SOLDIER_RECOVER_TRAIN_INFO:
		doSend();
		break;
	case PROTOCOL_SUBCMD_SOLDIER_RECOVER_TRAIN_DEL:
		doDelTrain(packet);
		break;
	case PROTOCOL_SUBCMD_SOLDIER_RECOVER_TRAIN_ADD:
		doAddTrain(packet);
		break;
	}
	return true;
}
bool SoldierRecoverTrain::load(uint32_t uid) {
	int ret = 0;
	CDataState dbState;
	DataState data;
	data.uid = m_player->getUid();
	data.id = PLAYER_DATA_STATE_SOLDIER_RECOVER_TRAIN;
	ret = dbState.GetState(data.uid, data.id, data.data);
	if (R_SUCCESS == ret) {
		Json::Reader reader;
		Json::Value value;
		if (reader.parse(data.data, value) && value.isArray()) {
			for (size_t i = 0; i < value.size(); ++i) {
				SoldierRecoverTrainItem item;
				item.FromJson(value[i]);
				m_data.insert(make_pair(item.id, item));
			}
		}
	} else if (R_ERR_NO_DATA == ret) {
		dbState.AddState(data.uid, data.id, "");
	} else {
		error_log("GetState error uid=%u id=%u ret=%d", data.uid, data.id, ret);
	}

	return true;
}
bool SoldierRecoverTrain::doSave() {
	Json::Value value = Json::Value(Json::arrayValue);
	map<uint32_t, SoldierRecoverTrainItem>::iterator itr = m_data.begin();
	for (; itr != m_data.end(); ++itr) {
		value.append(itr->second.ToJson());
	}
	CDataState dbState;
	DataState data;
	data.uid = m_player->getUid();
	data.id = PLAYER_DATA_STATE_SOLDIER_RECOVER_TRAIN;
	data.data = Json::ToString(value);
	int ret = dbState.SetState(data);
	if (ret != 0) {
		error_log("SetState error uid=%u id=%u ret=%d", data.uid, data.id, ret);
		return false;
	}
	return true;
}
bool SoldierRecoverTrain::doSend() {
	CNetPacket packet;
	packet.uid = m_player->getUid();
	CBufferWriter writer(&(packet.body));
	writer.AppendByte(PROTOCOL_CMD_SOLDIER);
	writer.AppendByte(PROTOCOL_SUBCMD_SOLDIER_RECOVER_TRAIN_INFO);
	writer.AppendUInt32(m_data.size());
	map<uint32_t, SoldierRecoverTrainItem>::iterator itr = m_data.begin();
	for (; itr != m_data.end(); ++itr) {
		SoldierRecoverTrainItem &item = itr->second;
		writer.AppendUInt32(item.id);
		writer.AppendUInt32(item.ts);
		writer.AppendUInt32(item.count);
	}

	PlayerManager::getInstance()->sendToAccess(&packet);

	return true;
}
void SoldierRecoverTrain::onTimer() {
	bool chg = false;
	set<uint32_t> del;
	map<uint32_t, SoldierRecoverTrainItem>::iterator itr = m_data.begin();
	for (; itr != m_data.end(); ++itr) {
		SoldierRecoverTrainItem &item = itr->second;
		if (item.ts <= LogicManager::GlobalTime) {
			chg = true;
			del.insert(itr->first);
		} else {
			if (item.speed == 0) {
				continue;
			}
			uint32_t count = ::ceil(static_cast<float>(item.ts - LogicManager::GlobalTime) / static_cast<float>(item.speed));
			if (count > 0 && count < item.count) {
				item.count = count;
				chg = true;
			}
		}
	}

	set<uint32_t>::iterator it = del.begin();
	for (; it != del.end(); ++it) {
		m_data.erase(*it);
	}

	if (chg) {
		doSave();
		doSend();
	}
}
uint32_t SoldierRecoverTrain::getDelCount(uint32_t type) {
	map<uint32_t, SoldierRecoverTrainItem>::iterator itr = m_data.begin();
	for (; itr != m_data.end(); ++itr) {
		SoldierRecoverTrainItem &item = itr->second;
		if (item.ts <= LogicManager::GlobalTime) {
			continue;
		}
		if (type != item.id) {
			continue;
		}
		return item.count;
	}
	return 0;
}
bool SoldierRecoverTrain::doDelTrain(CNetPacket *packet) {
	uint32_t uid = packet->uid;
	CSoldierDelRecoverTrainProtocol protocol;
	if (!protocol.Decode(&(packet->body))) {
		error_log("CSoldierDelRecoverTrainProtocol Decode error uid=%u", uid);
		onDelTrainResp(uid, 1);
		return false;
	}
	set<uint32_t> del;
	MoneyCost cost;
	for (vector<uint32_t>::iterator itr = protocol.data.begin(); itr != protocol.data.end(); ++itr) {
		if (!m_data.count(*itr)) {
			continue;
		}
		SoldierRecoverTrainItem &item = m_data[*itr];
		if (item.ts > LogicManager::GlobalTime) {
			cost.cash += ::ceil(static_cast<float>(item.ts - LogicManager::GlobalTime) / 150.0f);
			del.insert(*itr);
		}
	}
	if (del.empty()) {
		doSend();
		onDelTrainResp(uid, 0);
		return true;
	}
	string code = "recover_soldier";
	do {
		if (cost.cash > 0) {
			if (protocol.type == 1 && m_player->getEm()->useBagItemByType(601, 1, code)) {
				break;
			}
			if (!m_player->getRm()->useMoney(cost, code)) {
				error_log("useMoney error uid=%u", uid);
				onDelTrainResp(uid, 1);
				return false;
			}
		}
	} while(false);

	string log_str;
	for (set<uint32_t>::iterator it = del.begin(); it != del.end(); ++it) {
		m_data.erase(*it);
		log_str += CTrans::ITOS(*it) + ",";
	}

	doSave();

	doSend();

	onDelTrainResp(uid, 0);

	debug_log("uid=%u,ids=%s", uid, log_str.c_str());

	return true;
}
bool SoldierRecoverTrain::doAddTrain(CNetPacket *packet) {
	uint32_t uid = packet->uid;
	CSoldierAddRecoverTrainProtocol protocol;
	if (!protocol.Decode(&(packet->body))) {
		error_log("CSoldierAddRecoverTrainProtocol Decode error uid=%u", uid);
		return false;
	}

	vector<pair<uint32_t, uint32_t> > dieSoldier;

	vector<pair<uint32_t, uint32_t> >::iterator itr = protocol.data.begin();
	for (; itr != protocol.data.end(); ++itr) {
		uint32_t id = itr->first;
		uint32_t count = itr->second;
		Soldier *ps = m_player->getSoldierManager()->getSoldierByType(id);
		if (ps == NULL) {
			error_log("getSoldierByType error uid=%u id=%u", uid, id);
			continue;
		}
		uint32_t speed = SoldierConfig::getInstance()->GetSoldierRepairTime(id, ps->getLevel());
		uint32_t lv = m_player->getBm()->getBuildingLevel(BUILDING_ID_PUB);
		PropertySets sPropSets;
		BuildingConfig::getInstance()->getBaseProp(BUILDING_ID_PUB, lv, sPropSets);

		float capacity = (float)sPropSets[AP_MAX_CAPACITY].pui / 10000;
		uint32_t ts = (int)(speed * count * (1 - capacity));
		if (ts == 0) {
			error_log("GetSoldierRepairTime error uid=%u id=%u lv=%u", uid, id, ps->getLevel());
			continue;
		}
		if (m_data.count(id)) {
			m_data[id].count += count;
			m_data[id].ts += ts;
			m_data[id].speed = speed;
		} else {
			m_data.insert(make_pair(id, SoldierRecoverTrainItem(id, LogicManager::GlobalTime + ts, speed, count)));
		}
		dieSoldier.push_back(*itr);
		debug_log("uid=%u,id=%u,count=%u,ts=%u", uid, id, count, ts);
	}

	m_player->getTroopsManager()->subAttack(dieSoldier);

	doSave();

	doSend();

	debug_log("uid=%u", uid);

	return true;
}
void SoldierRecoverTrain::onDelTrainResp(uint32_t uid, byte ret) {
	CNetPacket packet;
	packet.uid = uid;
	CBufferWriter writer(&(packet.body));
	writer.AppendByte(PROTOCOL_CMD_SOLDIER);
	writer.AppendByte(PROTOCOL_SUBCMD_SOLDIER_RECOVER_TRAIN_DEL);
	writer.AppendByte(ret);

	PlayerManager::getInstance()->sendToAccess(&packet);
}

void SoldierRecoverTrain::onAddTrainResp(uint32_t uid, byte ret) {
}
