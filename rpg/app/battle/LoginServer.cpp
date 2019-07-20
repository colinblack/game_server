/*
 * LoginServer.cpp
 *
 *  Created on: 2019年6月29日
 *      Author: Administrator
 */

#include "LoginServer.h"
#include "ClientAsync.h"
#include "BattleServer.h"
#include "ClientManager.h"

#define MAX_EPOLL_WATH_COUNT 10
#define LISTEN_BACKLOG 80

LoginServer::LoginServer() :
		CPollThread("login", MAX_EPOLL_WATH_COUNT) {
}

LoginServer::~LoginServer() {
}

bool LoginServer::Init() {
	uint32_t maxClient = Config::GetIntValue("client_max_conn");
	maxClient = maxClient ? maxClient : MAX_EPOLL_WATH_COUNT;
	SetMaxPollers(maxClient);
	if (InitializeThread(0) != 0) {
		error_log("LoginServer run failed %m");
		return false;
	}

	CInternetAddress addr;
	addr.FromString(Config::GetValue("client_listen"));
	CListener<ClientAsync> *client = new CListener<ClientAsync>(addr.IP.c_str(), addr.Port);
	if (client->Attach(this, LISTEN_BACKLOG) != 0) {
		fatal_log("client attach fatal %s:%u", addr.IP.c_str(), addr.Port);
		return false;
	}
	return true;
}

void LoginServer::onIdle() {
	CFirePacket *packet = NULL;
	while ((packet = BattleServer::Instance()->GetSend()) != NULL) {
		ClientManager::Instance()->SendData(packet);
		delete packet;
		packet = NULL;
	}
}

void LoginServer::onExit() {
}
