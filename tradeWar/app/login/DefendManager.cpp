/*
 * DefendManager.cpp
 *
 *  Created on: 2017年11月14日
 *      Author: Administrator
 */

#include "DefendManager.h"
#include "PlayerManager.h"
#include "ProtocolInc.h"
#include "SystemMessage.h"
#include "GateConfig.h"

enum DefendManagerResult {
	DEFEND_MANAGER_RESULT_SUCCESS = 0, // 成功
	DEFEND_MANAGER_RESULT_FAIL = 1     // 失败
};

DefendManager::DefendManager() {
	m_defends.clear();
}

DefendManager::~DefendManager() {
}

bool DefendManager::doPacket(CNetPacket *packet) {
	switch (packet->subCmd) {
	case PROTOCOL_SUBCMD_DEFEND_LIST:
		doGetInfo(packet);
		break;
	case PROTOCOL_SUBCMD_DEFEND_RET:
		doDefendOver(packet);
		break;
	}
	return true;
}

bool DefendManager::load(uint32_t uid) {
	int ret = 0;
	CDataDefend dbc;
	vector<DataDefend> datas;
	ret = dbc.Get(uid, datas);
	if (ret != R_SUCCESS && ret != R_ERR_NO_DATA) {
		error_log("getDefends error uid=%u ret=%d", uid, ret);
		return false;
	}
	uint32_t m_id = 0;
	vector<DataDefend>::const_iterator itr = datas.begin();
	for (; itr != datas.end(); ++itr) {
		m_defends.insert(make_pair(itr->level, *itr));
		if (itr->star > 0 && itr->level > m_id) {
			m_id = itr->level;
		}
	}

	onAddNewGate();

	m_player->getBm()->unlockTower(getCurr());

	m_player->getActManager()->addDefendGate(m_id);

	debug_log("m_defends uid=%u size=%u", uid, m_defends.size());

	return true;
}

bool DefendManager::doGetInfo(CNetPacket *packet) {
	return sendInfo();
}

bool DefendManager::doDefendOver(CNetPacket *packet) {
	uint32_t uid = packet->uid;
	CGateDefendOverProtocol protocol;
	if (!protocol.Decode(&(packet->body))) {
		error_log("CGateDefendOverProtocol decode error uid=%u", uid);
		onDefendOverResp(protocol.level, DEFEND_MANAGER_RESULT_FAIL);
		return false;
	}

	uint32_t level = protocol.level;
	byte star = protocol.star;
	map<uint32_t, DataDefend>::iterator itr = m_defends.find(level);
	if (itr == m_defends.end()) {
		error_log("front gate is lock uid=%u lv=%u", uid, level);
		onDefendOverResp(protocol.level, DEFEND_MANAGER_RESULT_FAIL);
		return false;
	}
	const DefendGateItem *cfg = GateConfig::getInstance()->getDefend(level);
	if (cfg == NULL) {
		error_log("get config error uid=%u lv=%u", uid, level);
		onDefendOverResp(protocol.level, DEFEND_MANAGER_RESULT_FAIL);
		return false;
	}

	if (m_player->getLevel() < cfg->lv) {
		error_log("gate is lock uid=%u lv=%u", uid, level);
		onDefendOverResp(protocol.level, DEFEND_MANAGER_RESULT_FAIL);
		return false;
	}

	m_player->resetUserDaily();
	if (m_player->getUserInfo().defend_num == 0) {
		error_log("attack num is limit uid=%u lv=%u", uid, level);
		onDefendOverResp(protocol.level, DEFEND_MANAGER_RESULT_FAIL);
		return false;
	}
	m_player->getUserInfo().defend_num -= 1;
	m_player->savePlayerUserInfo();

	if (star > 0) {
		if (star > itr->second.star) {
			itr->second.star = star;
			saveData(itr->second);
		}
		m_player->doReward(&(cfg->award), "defend_" + CTrans::ITOS(level));
		m_player->getActManager()->addDefendGate(level);
		onAddNewGate();
	}

	onDefendOverResp(protocol.level, DEFEND_MANAGER_RESULT_SUCCESS);
	sendInfo();
	BUSI_MISC("play|defendgate|%u|%u|%u|%u", uid, protocol.level, star, Time::GetGlobalTime());
	return true;
}

bool DefendManager::onDefendOverResp(uint32_t level, byte ret) {
	CNetPacket sRspPacket;
	sRspPacket.uid = m_player->getUid();
	CBufferWriter selfWriter(&sRspPacket.body);
	selfWriter.AppendByte(PROTOCOL_CMD_GATE);
	selfWriter.AppendByte(PROTOCOL_SUBCMD_DEFEND_RET);
	selfWriter.AppendUInt32(level);
	selfWriter.AppendByte(ret);
	if (!PlayerManager::getInstance()->sendToAccess(&sRspPacket)) {
		error_log("sendAccess_fail&uid=%u", m_player->getUid());
		return false;
	}
	return true;
}

bool DefendManager::sendInfo() {
	m_player->resetUserDaily();

	CNetPacket sRspPacket;
	sRspPacket.uid = m_player->getUid();
	CBufferWriter selfWriter(&sRspPacket.body);
	selfWriter.AppendByte(PROTOCOL_CMD_GATE);
	selfWriter.AppendByte(PROTOCOL_SUBCMD_DEFEND_LIST);
	selfWriter.AppendByte(m_player->getUserInfo().defend_num);
	selfWriter.AppendUInt32(m_defends.size());
	map<uint32_t, DataDefend>::const_iterator itr = m_defends.begin();
	for (; itr != m_defends.end(); ++itr) {
		selfWriter.AppendUInt32(itr->second.level);
		selfWriter.AppendByte(itr->second.star);
	}
	if (!PlayerManager::getInstance()->sendToAccess(&sRspPacket)) {
		error_log("sendAccess_fail&uid=%u", m_player->getUid());
		return false;
	}
	return true;
}

bool DefendManager::saveData(const DataDefend &data) {
	int ret = 0;
	CDataDefend dbc;
	DataDefend old;
	ret = dbc.Get(data.uid, data.level, old);
	if (R_SUCCESS == ret) {
		debug_log("set uid=%u,id=%u", data.uid, data.level);
		ret = dbc.Set(data);
	} else if (R_ERR_NO_DATA == ret) {
		debug_log("add uid=%u,id=%u", data.uid, data.level);
		ret = dbc.Add(data);
	} else {
		return false;
	}
	if (ret != 0) {
		error_log("save data error ret=%d", ret);
		return false;
	}
	return true;
}

uint32_t DefendManager::getCurr() const {
	map<uint32_t, DataDefend>::const_reverse_iterator itr = m_defends.rbegin();
	for (; itr != m_defends.rend(); ++itr) {
		if (itr->second.star > 0) {
			return itr->first;
		}
	}
	return 0;
}

bool DefendManager::onAddNewGate() {
	uint32_t level = getCurr() + 1;
	map<uint32_t, DataDefend>::iterator itr = m_defends.find(level);
	if (itr == m_defends.end()) {
		DataDefend data;
		data.uid = m_player->getUid();
		data.level = level;
		data.star = 0;
		m_defends[level] = data;
		CDataDefend dbc;
		int ret = dbc.Add(data);
		if (ret != R_SUCCESS) {
			return false;
		}
	}
	return true;
}
