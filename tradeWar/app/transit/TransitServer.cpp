/*
 * TransitServer.cpp
 *
 *  Created on: 2016-3-15
 *      Author: Administrator
 */

#include <sys/un.h>
#include <sys/socket.h>
#include <curl/curl.h>
#include "TransitServer.h"
#include "ProtocolInc.h"
#include "TransitManager.h"
#include "TransitAsync.h"
#include "TencentAsync.h"

#define MAX_EPOLL_WATH_COUNT 1024
#define LISTEN_BACKLOG 80

bool TransitServer::IsClosed = false;

static void OnExit() {
	stop = 1;
	TransitServer::IsClosed = true;
	TransitServer::getInstance()->onExist();
	debug_log("server exists!");
}

TransitServer::TransitServer() : CPollThread("transit_server", MAX_EPOLL_WATH_COUNT) {
	m_pListener = NULL;
	m_pTencenter = NULL;
}

TransitServer::~TransitServer() {
	if (m_pListener) {
		delete m_pListener;
		m_pListener = NULL;
	}

	if (m_pTencenter) {
		delete m_pTencenter;
		m_pTencenter = NULL;
	}
}

bool TransitServer::initDaemon() {
	if (!Kernel::Init()) {
		fatal_log("[Kernel::Init fail][server=tower login]");
		return false;
	}
	if (!System::InitDaemon(NULL, OnExit)) {
		fatal_log("[System::InitDaemon fail][error=%d]", errno);
		return false;
	}
	return true;
}

bool TransitServer::addLoginPacket(CNetPacket* packet) {
	if (m_recvLoginMutex.acquire() == 0) {
		m_recvLoginQueue.push_back(packet);
		m_recvLoginCond.Signal();
		m_recvLoginMutex.release();
	}
	return true;
}

bool TransitServer::addSendLoginPacket(CNetPacket* packet) {
	CNetPacket *sp = new CNetPacket(*packet);
	if (m_sendLoginMutex.acquire() == 0) {
		m_sendLoginQueue.push_back(sp);
		m_sendLoginMutex.release();
	}
	return true;
}

bool TransitServer::addTencentPacket(TencentPacket* packet) {
	if (m_recvTencentMutex.acquire() == 0) {
		m_recvTencentQueue.push_back(packet);
		m_recvTencentCond.Signal();
		m_recvTencentMutex.release();
	}
	return true;
}

void TransitServer::getLoginPacket() {
	CNetPacket* packet = NULL;
	while(!IsClosed) {
		if (m_recvLoginMutex.acquire() == 0) {
			if (m_recvLoginQueue.size() > 0) {
				packet = m_recvLoginQueue.front();
				m_recvLoginQueue.pop_front();
			} else {
				packet = NULL;
				m_recvLoginCond.Wait(m_recvLoginMutex.getMutex());
			}
			Time::UpdateGlobalTime();
			m_recvLoginMutex.release();
		}
		if (packet != NULL) {
			packet->uid = packet->fd;
			TransitManager::getInstance()->doLoginPacket(packet);
			delete(packet);
		}
	}
}

void TransitServer::getTencentPacket() {
	TencentPacket* packet = NULL;
	while (!IsClosed) {
		if (m_recvTencentMutex.acquire() == 0) {
			if (m_recvTencentQueue.size() > 0) {
				packet = m_recvTencentQueue.front();
				m_recvTencentQueue.pop_front();
			} else {
				packet = NULL;
				m_recvTencentCond.Wait(m_recvTencentMutex.getMutex());
			}
			m_recvTencentMutex.release();
		}
		if (packet != NULL) {
			TransitManager::getInstance()->doTencentPacket(packet);
			delete packet;
		}
	}
}

CNetPacket* TransitServer::getSendLoginPacket() {
	CNetPacket *p = NULL;
	if (m_sendLoginMutex.acquire() == 0) {
		if (!m_sendLoginQueue.empty()) {
			p = m_sendLoginQueue.front();
			m_sendLoginQueue.pop_front();
		}
		m_sendLoginMutex.release();
	}
	return p;
}

bool TransitServer::init() {
	CURLcode res = curl_global_init(CURL_GLOBAL_SSL);
	if (res != CURLE_OK) {
		error_log("curl_global_init fail. ErrorCode=%d, ErrorMessage=%s", res, curl_easy_strerror(res));
		return false;
	}
	if (!listenInit()) {
		fatal_log("listen init failed");
		return false;
	}
	if (!threadInit()) {
		fatal_log("thread init failed");
		return false;
	}
	return true;
}

bool TransitServer::onExist() {
	TransitManager::getInstance()->saveIds();
	m_recvTencentCond.Broadcast();
	m_recvLoginCond.Broadcast();
	return true;
}

void TransitServer::onIdle() {
	CNetPacket *sp = NULL;
	while ((sp = getSendLoginPacket()) != NULL) {
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
			debug_log("send to login uid=%u sid=%u", sp->uid, sid);
		} while (false);
		delete sp;
	}
}

bool TransitServer::listenInit() {
	if (m_pListener || m_pTencenter) {
		return true;
	}

	uint32_t maxClient = Config::GetIntValue("server_max_conn");
	maxClient = maxClient ? maxClient : MAX_EPOLL_WATH_COUNT;

	SetMaxPollers(maxClient);
	if (InitializeThread(0) != 0) {
		error_log("transit_server run failed %m");
		return false;
	}

	CInternetAddress address;
	if (!address.FromString(Config::GetValue("transit_server"))) {
		error_log("config server_listen format error:%s", Config::GetValue("transit_server").c_str());
		return false;
	}

	m_pListener = new CListener<TransitAsync>(address.IP.c_str(), address.Port);
	if (m_pListener->Attach(this, LISTEN_BACKLOG) != 0) {
		error_log("local listen attach failed");
		return false;
	}

	CInternetAddress tencent;
	if (!tencent.FromString(Config::GetValue("c6_server"))) {
		error_log("config tencent_server format error:%s", Config::GetValue("c6_server").c_str());
		return false;
	}

	m_pTencenter = new CListener<TencentAsync>(tencent.IP.c_str(), tencent.Port);
	if (m_pTencenter->Attach(this, LISTEN_BACKLOG) != 0) {
		error_log("tencent listen attach failed");
		return false;
	}

	return true;
}

bool TransitServer::threadInit() {
	int threadCount = 1;
	Config::GetIntValue(threadCount, "thread_count");
	pthread_t pid;
	for (int i = 0; i < threadCount; ++i) {
		if (pthread_create(&pid, NULL, processLoginFunc, (void*) NULL) != 0) {
			error_log("start path login thread failed");
			return false;
		}
		info_log("start path thread %u success", pid);
	}

	if (pthread_create(&pid, NULL, processC6Func, (void*) NULL) != 0) {
		error_log("start path tencent thread failed");
		return false;
	}

	return true;
}

void* TransitServer::processLoginFunc(void* arg) {
	TransitServer::getInstance()->getLoginPacket();
	return NULL;
}

void* TransitServer::processTencentFunc(void* arg) {
	TransitServer::getInstance()->getTencentPacket();
	return NULL;
}

void* TransitServer::processC6Func(void* arg){
	TransitServer::getInstance()->getTencentPacket();
	return NULL;
}
