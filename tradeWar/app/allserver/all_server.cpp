/*
 * AsrvServer.cpp
 *
 *  Created on: 2018年9月26日
 *      Author: Administrator
 */

#include <pthread.h>
#include "all_server.h"
#include "NetPacket.h"
#include "ProtocolDefine.h"
#include "client_async.h"
#include "ProtocolLogin.h"
#include "TransportManager.h"
#include "BoatConfig.h"
#include "ExpConfig.h"

#define MAX_EPOLL_WATH_COUNT 1024
#define LISTEN_BACKLOG 500

bool AsrvServer::IsClosed = false;

void* LogicThread(void *para) {
	AsrvServer::getInstance()->getRecvPacket();
	return NULL;
}

AsrvServer::AsrvServer(): CPollThread("AsrvServer", MAX_EPOLL_WATH_COUNT) {
	m_pListener = NULL;
	m_timer = NULL;
}

AsrvServer::~AsrvServer() {
}

void AsrvServer::onIdle() {
	CNetPacket *sp = NULL;;
	while ((sp = getSendPacket()) != NULL) {
		do {
			uint32_t sid = Config::GetZoneByUID(sp->uid);
			if (!m_battles.count(sid)) {
				CServerAsync *pp = new CServerAsync(this, CServerAsync::SERVER_ASYNC_LOGIN, sid);
				if (pp == NULL) {
					break;
				}
				if (!pp->init()) {
					delete pp;
					break;
				}
				m_battles[sid] = pp;
			}
			if (m_battles[sid] == NULL) {
				break;
			}
			CStaticBuffer<MAX_PACKET_SIZE> buff;
			sp->Encode(&buff);
			m_battles[sid]->sendData(&buff);
			debug_log("send to login sid=%u", sid);
		} while (false);
		delete sp;
	}
}

bool AsrvServer::addPacket(IBuffer* pBuff) {
	CNetPacket* packet = new CNetPacket();
	if (!packet->Decode(pBuff)) {
		error_log("packet decode failed");
		delete packet;
		return false;
	}
	packet->uid = packet->fd;
	AsrvServer::getInstance()->addRecvPacket(packet);
	return true;
}

bool AsrvServer::onExit() {
	TransportManager::getInstance()->doSave();
	if (m_timer != NULL) {
		m_timer->Stop();
	}
	m_recvCond.Broadcast();
	return true;
}

bool AsrvServer::doInit() {
	if (m_pListener != NULL) {
		return true;
	}

	if (!ExpConfig::getInstance()->init(Config::GetValue(CONFIG_EXP))) {
		error_log("exp config init fail");
		return false;
	}

	if (!CBoatConfig::getInstance()->init(Config::GetValue(CONFIG_RESOURCE_TRANSPORT))) {
		error_log("init transport config fail");
		return false;
	}

	uint32_t maxClient = Config::GetIntValue("maxclient");
	maxClient = maxClient ? maxClient : MAX_EPOLL_WATH_COUNT;
	SetMaxPollers(maxClient);
	if (InitializeThread(0) != 0) {
		error_log("AsrvServer run failed %m");
		return false;
	}

	int port = Config::GetIntValue("port");
	const char *addr = Config::GetValue("ip").c_str();

	m_pListener = new CListener<AsrvClientAsync>(addr, port);
	if (m_pListener->Attach(this, LISTEN_BACKLOG)) {
		error_log("bind [%s:%d] failed\n", addr, port);
		exit(-1);
	}

	pthread_t pid;
	pthread_create(&pid, NULL, LogicThread, this);

	doInitTimer();

	TransportManager::getInstance()->doLoad();

	return true;
}

bool AsrvServer::doInitTimer() {
	if (!m_pListener) {
		error_log("must init listener first");
		return false;
	}
	m_timer = new CTimerThread(Config::GetValue("ip").c_str(), Config::GetIntValue("port"), 0, 1);
	if (!m_timer->Start()) {
		error_log("timer start error");
	}
	return true;
}

bool AsrvServer::doPacket(CNetPacket *p) {
	switch(p->ptype)
	{
	case PROTOCOL_TYPE_SECOND_TIMER:
		doTimer(p);
		break;
	case PROTOCOL_TYPE_ALL_SERVER_TRANSFER:
		doTransfer(p);
		break;
	}
	if (p->ptype != PROTOCOL_TYPE_SECOND_TIMER) {
		debug_log("type=%u,cmd=%u,sub=%u", p->ptype, static_cast<uint32_t>(p->cmd), static_cast<uint32_t>(p->subCmd));
	}
	return true;
}

bool AsrvServer::doTimer(CNetPacket *p) {
	Time::UpdateGlobalTime();
	TransportManager::getInstance()->onSecondTimer();
	return true;
}

bool AsrvServer::doTransfer(CNetPacket *p) {
	p->uid = p->fd;
	switch(p->cmd) {
	case PROTOCOL_CMD_TRANSPORT:
		TransportManager::getInstance()->doPacket(p);
		break;
	}
	return true;
}

bool AsrvServer::addRecvPacket(CNetPacket *p) {
	if (p == NULL) {
		return false;
	}
	if (m_recvMutex.acquire() == 0) {
		m_recvQueue.push_back(p);
		m_recvCond.Signal();
		m_recvMutex.release();
	}
	return true;
}

bool AsrvServer::getRecvPacket() {
	CNetPacket *p = NULL;
	while (!IsClosed) {
		if (m_recvMutex.acquire() == 0) {
			if (!m_recvQueue.empty()) {
				p = m_recvQueue.front();
				m_recvQueue.pop_front();
			} else {
				p = NULL;
				m_recvCond.Wait(m_recvMutex.getMutex());
			}
			m_recvMutex.release();
		}
		if (p != NULL) {
			doPacket(p);
			delete p;
		}
	}
	return true;
}

bool AsrvServer::addSendPacket(CNetPacket *p) {
	if (p == NULL) {
		return false;
	}
	if (m_sendMutex.acquire() == 0) {
		CNetPacket *np = new CNetPacket(*p);
		if (np == NULL) {
			m_sendMutex.release();
			return false;
		}
		m_sendQueue.push_back(np);
		m_sendMutex.release();
	}
	return true;
}

CNetPacket* AsrvServer::getSendPacket() {
	CNetPacket *p = NULL;
	if (m_sendMutex.acquire() == 0) {
		if (!m_sendQueue.empty()) {
			p = m_sendQueue.front();
			m_sendQueue.pop_front();
		}
		m_sendMutex.release();
	}
	return p;
}

bool AsrvServer::sendToLogin(CNetPacket *p) {
	p->ptype = PROTOCOL_TYPE_ALL_SERVER_ANSWER;
	p->fd = p->uid;
	addSendPacket(p);
	return true;
}
