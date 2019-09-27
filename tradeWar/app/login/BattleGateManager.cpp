/*
 * BattleGateManager.cpp
 *
 *  Created on: 2018年10月30日
 *      Author: Administrator
 */

#include "BattleGateManager.h"
#include "PlayerManager.h"
#include "ProtocolInc.h"
#include "SystemMessage.h"

enum BattleGateManagerResult {
	BATTLE_GATE_MANAGER_RESULT_SUCCESS = 0, //成功
	BATTLE_GATE_MANAGER_RESULT_FAIL = 1     //失败
};

BattleGateManager::BattleGateManager() {
	m_data.clear();
}

BattleGateManager::~BattleGateManager() {
}

bool BattleGateManager::doPacket(CNetPacket *packet) {
	switch (packet->subCmd) {
	case PROTOCOL_SUBCMD_BATTLE_LIST:
		doGetInfo(packet);
		break;
	case PROTOCOL_SUBCMD_BATTLE_RET:
		doOver(packet);
		break;
	case PROTOCOL_SUBCMD_SET_SPEED_UP_FLAG:{
			doSetSpeedUp(packet);
			break;
		}
	}
	return true;
}

bool BattleGateManager::load(uint32_t uid) {
	int ret = 0;
	CDataBattleGate dbc;
	vector<DataBattleGate> datas;
	ret = dbc.Get(uid, datas);
	if (ret != R_SUCCESS && ret != R_ERR_NO_DATA) {
		error_log("get data error uid=%u ret=%d", uid, ret);
		return false;
	}
	uint32_t m_id = 0;
	vector<DataBattleGate>::const_iterator itr = datas.begin();
	for (; itr != datas.end(); ++itr) {
		m_data.insert(make_pair(itr->level, *itr));
		if (itr->star > 0 && itr->level > m_id) {
			m_id = itr->level;
		}
	}

	onAddNewGate();

	m_player->getBm()->unlockTower(getCurr());

	m_player->getActManager()->addBattleGate(m_id);

	debug_log("m_data uid=%u size=%u", uid, m_data.size());

	return true;
}

bool BattleGateManager::doGetInfo(CNetPacket *packet) {
	return sendInfo();
}

bool BattleGateManager::doOver(CNetPacket *packet) {
	uint32_t uid = packet->uid;
	CGateBattleOverProtocol protocol;
	if (!protocol.Decode(&(packet->body))) {
		error_log("CGateBattleOverProtocol decode error uid=%u", uid);
		onOverResp(protocol.level, BATTLE_GATE_MANAGER_RESULT_FAIL);
		return false;
	}
	uint32_t level = protocol.level;
	byte star = protocol.star;
	map<uint32_t, DataBattleGate>::iterator itr = m_data.find(level);
	if (itr == m_data.end()) {
		onOverResp(protocol.level, BATTLE_GATE_MANAGER_RESULT_FAIL);
		return false;
	}
	itr->second.score = protocol.score;
	itr->second.res += protocol.res;
	if (star > 0) {
		if (star > itr->second.star) {
			m_player->getTaskManager()->onStarNum(star - itr->second.star);
			itr->second.star = star;
			saveData(itr->second);
			m_player->getStarBoxManager()->infoReFlash(protocol.level);
			m_player->getStarBoxManager()->save();
		}
		onAddNewGate();
		SystemMessage::getInstance()->addGate(uid, level);
		m_player->getBm()->unlockTower(level);
		m_player->getTaskManager()->onBattleGateOver();
		m_player->getActManager()->addBattleGate(level);
	}
	onOverResp(protocol.level, BATTLE_GATE_MANAGER_RESULT_SUCCESS);
	sendInfo();
	m_player->getActivenessManager()->onGate();
	BUSI_MISC("play|battlegate|%u|%u|%u|%u", uid, protocol.level, star, Time::GetGlobalTime());
	return true;
}

bool BattleGateManager::onOverResp(uint32_t level, byte ret) {
	CNetPacket sRspPacket;
	sRspPacket.uid = m_player->getUid();
	CBufferWriter selfWriter(&sRspPacket.body);
	selfWriter.AppendByte(PROTOCOL_CMD_GATE);
	selfWriter.AppendByte(PROTOCOL_SUBCMD_BATTLE_RET);
	selfWriter.AppendUInt32(level);
	selfWriter.AppendByte(ret);
	if (!PlayerManager::getInstance()->sendToAccess(&sRspPacket)) {
		error_log("sendAccess_fail&uid=%u", m_player->getUid());
		return false;
	}
	return true;
}

bool BattleGateManager::doSetSpeedUp(CNetPacket *packet) {
	uint32_t uid = packet->uid;
	CGateSpeedUpProtocol protocol;
	if (!protocol.Decode(&(packet->body))) {
		error_log("CGateSpeedUpProtocol decode error uid=%u", uid);
		onSpeedUpResp(0);
		return false;
	}
	m_player->setSpeedUpFlag(protocol.flag);
	onSpeedUpResp(m_player->getSpeedUp());
	return true;
}

bool BattleGateManager::onSpeedUpResp(byte flag) {
	CNetPacket sRspPacket;
	sRspPacket.uid = m_player->getUid();
	CBufferWriter selfWriter(&sRspPacket.body);
	selfWriter.AppendByte(PROTOCOL_CMD_GATE);
	selfWriter.AppendByte(PROTOCOL_SUBCMD_SET_SPEED_UP_FLAG);
	selfWriter.AppendUInt32(flag);
	if (!PlayerManager::getInstance()->sendToAccess(&sRspPacket)) {
		error_log("sendAccess_fail&uid=%u", m_player->getUid());
		return false;
	}
	return true;
}


bool BattleGateManager::sendInfo() {
	CNetPacket sRspPacket;
	sRspPacket.uid = m_player->getUid();
	CBufferWriter selfWriter(&sRspPacket.body);
	selfWriter.AppendByte(PROTOCOL_CMD_GATE);
	selfWriter.AppendByte(PROTOCOL_SUBCMD_BATTLE_LIST);
	selfWriter.AppendUInt32(m_data.size());
	map<uint32_t, DataBattleGate>::const_iterator itr = m_data.begin();
	for (; itr != m_data.end(); ++itr) {
		selfWriter.AppendUInt32(itr->second.level);
		selfWriter.AppendUInt32(itr->second.score);
		selfWriter.AppendByte(itr->second.star);
		selfWriter.AppendUInt32(itr->second.res);
	}
	if (!PlayerManager::getInstance()->sendToAccess(&sRspPacket)) {
		error_log("sendAccess_fail&uid=%u", m_player->getUid());
		return false;
	}
	return true;
}

bool BattleGateManager::saveData(const DataBattleGate &data) {
	int ret = 0;
	CDataBattleGate dbc;
	DataBattleGate old;
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

uint32_t BattleGateManager::getCurr() const {
	map<uint32_t, DataBattleGate>::const_reverse_iterator itr = m_data.rbegin();
	for (; itr != m_data.rend(); ++itr) {
		if (itr->second.star > 0) {
			return itr->first;
		}
	}
	return 0;
}

bool BattleGateManager::onAddNewGate() {
	uint32_t level = getCurr() + 1;
	map<uint32_t, DataBattleGate>::iterator itr = m_data.find(level);
	if (itr == m_data.end()) {
		DataBattleGate data;
		data.uid = m_player->getUid();
		data.level = level;
		data.score = 0;
		data.star = 0;
		m_data[level] = data;
		CDataBattleGate dbc;
		int ret = dbc.Add(data);
		if (ret != R_SUCCESS) {
			return false;
		}
	}
	return true;
}

uint32_t BattleGateManager::getLevelStarCnt(uint32_t level) {
	if(m_data.count(level) == 0) {
		return 0;
	} else {
		return m_data[level].star;
	}
}
