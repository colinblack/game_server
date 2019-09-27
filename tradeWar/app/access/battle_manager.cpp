#include "battle_manager.h"
#include "config.h"
#include "utils.h"

bool BattleManager::init() {
	return true;
}

bool BattleManager::sendData(uint32_t serverId, const string& data) {
	map<uint32_t, CBattleAsync*>::iterator it = m_battles.find(serverId);
	CBattleAsync* pBattle;
	if (it == m_battles.end()) {
		pBattle = connectBattle(serverId);
		if (pBattle == NULL) {
			error_log("pBattle is NULL serverId=%u", serverId);
			return false;
		}
		m_battles[serverId] = pBattle;
	} else {
		pBattle = it->second;
	}

	return pBattle->sendData(data);
}

CBattleAsync* BattleManager::connectBattle(uint32_t serverId) {
	ServerItem addr;
	if (!ServerConfig::getInstance()->GetLogin(serverId, addr)) {
		error_log("get server info error sid=%u", serverId);
		return NULL;
	}
	CBattleAsync* pBattle = new CBattleAsync(m_pollThread, serverId);
	LOG_DEBUG("connect %u", serverId);
	return pBattle;
}

bool BattleManager::clientClose(uint32_t serverId, uint32_t fd, uint32_t time, uint32_t microTime, uint32_t ip) {
	LOG_INFO("detect client close serverId:%d fd:%d time:%d microTime:%d", serverId, fd, time, microTime);
	map<uint32_t, CBattleAsync*>::iterator it = m_battles.find(serverId);
	if (it == m_battles.end()) {
		LOG_ERROR("invalid span,srv [%u]", serverId);
		return false;
	}

	it->second->clientClose(fd, time, microTime, ip);

	return true;
}
