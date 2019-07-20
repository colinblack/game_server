#include "ClientManager.h"
#include "BattleServer.h"

bool ClientManager::AddClient(ClientAsync* pClient) {
	if (m_clients.find(pClient->getFd()) != m_clients.end()) {
	}
	m_clients[pClient->getFd()] = pClient;
	onlineLog();
	return true;
}

bool ClientManager::DelClient(ClientAsync* pClient) {
	map<uint32_t, ClientAsync*>::iterator it = m_clients.find(pClient->getFd());
	if (it == m_clients.end()) {
		return false;
	}
	if (it->second->getTime() != pClient->getTime() || it->second->getMicrotime() != pClient->getMicrotime()) {
		return false;
	}

	CFirePacket *packet = new CFirePacket();
	packet->cmd = PROTOCOL_EVENT_OFFLINE;
	packet->fd = pClient->getFd();
	packet->time = pClient->getTime();
	packet->microTime = pClient->getMicrotime();

	if (!BattleServer::Instance()->AddRecv(packet)) {
		delete packet;
		packet = NULL;
	}

	m_clients.erase(it);
	onlineLog();
	return true;
}

bool ClientManager::SendData(CFirePacket *packet) {
	if (packet == NULL) {
		return false;
	}
	map<uint32_t, ClientAsync*>::iterator it = m_clients.find(packet->fd);
	if (it == m_clients.end()) {
		return false;
	}
	if (it->second->getTime() != packet->time || it->second->getMicrotime() != packet->microTime) {
		return false;
	}
	it->second->onBattleMsg(packet);
	return true;
}

void ClientManager::onlineLog() {

}

