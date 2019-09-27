/*
 * UserStateManager.cpp
 *
 *  Created on: 2017年11月17日
 *      Author: Administrator
 */

#include "UserStateManager.h"
#include "PlayerManager.h"
#include "LogicIdCtrl.h"
#include "SoldierConfig.h"

UserStateManager::UserStateManager() {
	m_mapState.clear();
	m_clientState.clear();
}

UserStateManager::~UserStateManager() {
}

bool UserStateManager::load(uint32_t uid) {
	loadClientState(uid);
	loadLevelReward(uid);
	loadOnlineTs(uid);
	return true;
}

void UserStateManager::onTimer() {
}

DataState* UserStateManager::getState(uint32_t id) {
	map<uint32_t, DataState>::iterator iter = m_mapState.find(id);
	return iter != m_mapState.end() ? &(iter->second) : NULL;
}

bool UserStateManager::addState(uint32_t uid, uint32_t id, const string& data) {
	DataState* ds = getState(id);
	if (ds == NULL) {
		CDataState dbState;
		DataState dataState;
		dataState.uid = uid;
		dataState.id = id;
		dataState.data = data;
		m_mapState[id] = dataState;
		int ret = dbState.AddState(dataState);
		if (ret != 0) {
			error_log("add new state failed uid=%u id=%u ret=%d", uid, id, ret);
			return false;
		}
		return true;
	}
	return false;
}

bool UserStateManager::setState(uint32_t uid, uint32_t id, const string& data) {
	DataState* ds = getState(id);
	if (ds != NULL) {
		CDataState dbState;
		ds->data = data;
		int ret = 0;
		if ((ret = dbState.SetState(*ds)) != 0) {
			error_log("add new state failed uid=%u id=%u ret=%d", uid, id, ret);
			return false;
		}
		return true;
	} else {
		error_log("not find state uid=%u id=%u", uid, id);
		return false;
	}
}

bool UserStateManager::setStateData(uint32_t uid, uint32_t id, const string& data) {
	DataState* ds = getState(id);
	if (ds == NULL) {
		if (!addState(uid, id, data)) {
			error_log("add new state failed uid=%u id=%u", uid, id);
			return false;
		}
	} else {
		if (!setState(uid, id, data)) {
			error_log("setState fail uid=%u id=%u", uid, id);
			return false;
		}
	}
	return true;
}

bool UserStateManager::getStateData(uint32_t uid, uint32_t id, Json::Value& res) {
	DataState* ds = getState(id);
	if (ds == NULL) {
		CDataState dbState;
		DataState dataState;
		dataState.uid = uid;
		dataState.id = id;
		int ret = 0;
		ret = dbState.GetState(uid, id, dataState.data);
		if (ret != 0 && ret != R_ERR_NO_DATA) {
			error_log("load %u's state failed uid=%u id=%u ret=%d", uid, id, ret);
			return false;
		}
		if (ret == R_ERR_NO_DATA) {
			return true;
		}
		m_mapState[id] = dataState;

		if (!Json::FromString(res, dataState.data)) {
			error_log("FromString fail uid=%u id=%u", uid, id);
			return false;
		}
	} else {
		if (!Json::FromString(res, ds->data)) {
			error_log("FromString fail uid=%u id=%u", uid, id);
			return false;
		}
	}
	return true;
}

bool UserStateManager::loadClientState(uint32_t uid) {
	CDataState dbState;
	DataState data;
	data.uid = uid;
	data.id = PLAYER_DATA_STATE_CLIENT_STATE;
	int ret = 0;
	ret = dbState.GetState(uid, data.id, data.data);
	if (ret == 0) {
		Json::Value value;
		Json::Reader reader;
		reader.parse(data.data, value);
		if (value.isArray()) {
			for (size_t i = 0; i < value.size(); ++i) {
				if (value[i].isIntegral()) {
					m_clientState.push_back(value[i].asUInt());
				} else {
					m_clientState.push_back(0);
				}
			}
		}
	} else if (ret == R_ERR_NO_DATA) {
		dbState.AddState(uid, data.id, "");
	} else {
		error_log("GetState error ret=%d uid=%u", ret, uid);
	}

	return true;
}

bool UserStateManager::setClientState(const vector<pair<byte, byte> > &data) {
	for (size_t i = 0; i < data.size(); ++i) {
		size_t id = data[i].first;
		byte value = data[i].second;
		if (m_clientState.size() <= id) {
			m_clientState.resize(id + 1, 0);
		}
		m_clientState[id] = value;
	}

	saveClientState();

	sendClientState();

	return true;
}

bool UserStateManager::sendClientState() {
	CNetPacket sPacket;
	sPacket.uid = m_player->getUid();

	CBufferWriter bWriter(&(sPacket.body));
	bWriter.AppendByte(PROTOCOL_CMD_USER);
	bWriter.AppendByte(PROTOCOL_SUBCMD_USER_CLIENT_STATE);
	bWriter.AppendUInt32(m_clientState.size());
	for (size_t i = 0; i < m_clientState.size(); ++i) {
		bWriter.AppendByte(m_clientState[i]);
	}

	PlayerManager::getInstance()->sendToAccess(&sPacket);

	return true;
}

bool UserStateManager::saveClientState() {
	Json::Value value(Json::arrayValue);
	value.resize(m_clientState.size());
	for (size_t i = 0; i < m_clientState.size(); ++i) {
		value[i] = m_clientState[i];
	}

	CDataState dbState;
	DataState data;
	data.uid = m_player->getUid();
	data.id = PLAYER_DATA_STATE_CLIENT_STATE;
	data.data = Json::ToString(value);

	if (data.data.size() > 1024) {
		error_log("data too large!uid=%u,id=%u", data.uid, data.id);
		return false;
	}

	int ret = dbState.SetState(data);
	if (0 != ret) {
		error_log("SetState error,ret=%d,uid=%u,id=%u", ret, data.uid, data.id);
		return false;
	}

	return true;
}

bool UserStateManager::loadLevelReward(uint32_t uid) {
	CDataState dbState;
	DataState data;
	data.uid = uid;
	data.id = PLAYER_DATA_STATE_LEVEL_REWARD;
	int ret = dbState.GetState(data.uid, data.id, data.data);
	if (R_SUCCESS == ret) {
		Json::Reader reader;
		Json::Value v;
		if (reader.parse(data.data, v) && v.isArray()) {
			for (size_t i = 0; i < v.size(); ++i) {
				m_levelReward.push_back(v[i].asUInt());
			}
		}
	} else if (R_ERR_NO_DATA == ret) {
		dbState.AddState(data.uid, data.id, "");
	}
	uint32_t m = ExpConfig::getInstance()->getExpLevelSize();
	if (m_levelReward.size() < m) {
		m_levelReward.resize(m, 0);
	}
	return true;
}

bool UserStateManager::setLevelReward(uint32_t id) {
	if (id >= m_levelReward.size()) {
		return false;
	}
	m_levelReward[id] = 1;
	return true;
}

bool UserStateManager::getLevelReward(uint32_t id) {
	if (id >= m_levelReward.size()) {
		return false;
	}
	return m_levelReward[id] == 1;
}

bool UserStateManager::saveLevelReward() {
	Json::Value v = Json::Value(Json::arrayValue);
	vector<byte>::iterator itr = m_levelReward.begin();
	for (; itr != m_levelReward.end(); ++itr) {
		v.append(static_cast<uint32_t>(*itr));
	}
	CDataState dbState;
	DataState data;
	data.uid = m_player->getUid();
	data.id = PLAYER_DATA_STATE_LEVEL_REWARD;
	data.data = Json::ToString(v);
	dbState.SetState(data);
	return true;
}

bool UserStateManager::sendLevelReward() {
	CNetPacket sp;
	sp.uid = m_player->getUid();
	CBufferWriter writer(sp.GetBody());
	writer.AppendByte(PROTOCOL_CMD_USER);
	writer.AppendByte(PROTOCOL_SUBCMD_USER_LEVEL_REWARD_INFO);
	writer.AppendUInt32(m_levelReward.size());
	vector<byte>::iterator itr = m_levelReward.begin();
	for (; itr != m_levelReward.end(); ++itr) {
		writer.AppendByte(*itr);
	}

	PlayerManager::getInstance()->sendToAccess(&sp);

	return true;
}

bool UserStateManager::loadOnlineTs(uint32_t uid) {
	CDataState dbState;
	DataState data;
	data.uid = uid;
	data.id = PLAYER_DATA_STATE_ONLINE_TS;
	int ret = dbState.GetState(data.uid, data.id, data.data);
	if (R_SUCCESS == ret) {
		Json::Reader reader;
		Json::Value v;
		if (reader.parse(data.data, v) && v.isArray()) {
			for (size_t i = 0; i < v.size(); ++i) {
				m_onlineTs.push_back(v[i].asUInt());
			}
		}
	} else if (R_ERR_NO_DATA == ret) {
		dbState.AddState(data.uid, data.id, "");
	}
	return true;
}

bool UserStateManager::setOnlineTs(uint32_t id, uint32_t ts) {
	if (id > 7) {
		return true;
	}
	if (m_onlineTs.size() <= id) {
		m_onlineTs.resize(id + 1, 0);
	}
	m_onlineTs[id] += ts;
	saveOnlineTs();
	return true;
}

bool UserStateManager::saveOnlineTs() {
	Json::Value v = Json::Value(Json::arrayValue);
	vector<uint32_t>::iterator itr = m_onlineTs.begin();
	for (; itr != m_onlineTs.end(); ++itr) {
		v.append(*itr);
	}
	CDataState dbState;
	DataState data;
	data.uid = m_player->getUid();
	data.id = PLAYER_DATA_STATE_ONLINE_TS;
	data.data = Json::ToString(v);
	dbState.SetState(data);
	return true;
}
