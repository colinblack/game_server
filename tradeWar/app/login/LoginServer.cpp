/*
 * LoginServer.cpp
 *
 *  Created on: 2015-8-28
 *      Author: Administrator
 */

#include <sys/un.h>
#include <sys/socket.h>

#include "LoginServer.h"
#include "ProtocolInc.h"
#include "PlayerManager.h"
#include "ServerAsync.h"
#include "AsyncDBManager.h"
#include "ChatManager.h"

#define MAX_EPOLL_WATH_COUNT 1024
#define LISTEN_BACKLOG 80
#define PRIORITY_QUEUE_FACTOR 10

bool LoginServer::IsClosed = false;
bool LoginServer::IsReLoad = false;

static void OnExit() {
	stop = 1;
	LoginServer::IsClosed = true;
	LoginServer::getInstance()->onExit();
}

static void OnReLoad() {
	LoginServer::IsReLoad = true;
}

void *NetThread(void *) {
	LoginServer::getInstance()->RunningThread();
	return NULL;
}

LoginServer::LoginServer() : CPollThread("towerlogin", MAX_EPOLL_WATH_COUNT) {
	m_pListener = NULL;
	m_accessChannel = NULL;
	m_dbChannel = NULL;
	m_allServerChannel = NULL;
	m_transitChannel = NULL;
	m_logTs = 0;
	m_recvCount = 0;
	m_hSize = 0;
	m_lSize = 0;
	m_sendSize = 0;
	m_timer = NULL;
	m_port = 0;
}

LoginServer::~LoginServer() {
	if (m_pListener) {
		delete m_pListener;
		m_pListener = NULL;
	}
	if (m_dbChannel) {
		delete m_dbChannel;
		m_dbChannel = NULL;
	}
}

bool LoginServer::initDaemon() {
	if (!Kernel::Init()) {
		fatal_log("[Kernel::Init fail][server=tower login]");
		return false;
	}
	if (!System::InitDaemon(OnReLoad, OnExit)) {
		fatal_log("[System::InitDaemon fail][error=%d]", errno);
		return false;
	}
	return true;
}

bool LoginServer::init() {
	uint32_t server_id = Config::GetIntValue("server_id");
	ServerItem addr;
	if (!ServerConfig::getInstance()->GetLogin(server_id, addr)) {
		fatal_log("get server info failed");
		return false;
	}
	m_addr = addr.host;
	m_port = addr.port;
	if (!listenInit()) {
		fatal_log("listen init failed");
		return false;
	}
	if (!timerInit()) {
		fatal_log("timer init failed");
		return false;
	}
	if (!asyncDBInit()) {
		error_log("async dbwrite init failed");
	}
	if (!asyncAllServerInit()) {
		error_log("async all server init failed");
	}
	if (!asyncTransitInit()) {
		error_log("async transit init failed");
	}

	pthread_t pid;
	pthread_create(&pid, NULL, NetThread, this);

	return true;
}

bool LoginServer::listenInit() {
	if (m_pListener) {
		return true;
	}
	uint32_t maxClient = Config::GetIntValue("server_max_conn");
	maxClient = maxClient ? maxClient : MAX_EPOLL_WATH_COUNT;
	SetMaxPollers(maxClient);
	if (InitializeThread(0) != 0) {
		error_log("LoginServer run failed %m");
		return false;
	}
	m_pListener = new CListener<CLoginClientAsync>(m_addr.c_str(), m_port);
	if (m_pListener->Attach(this, LISTEN_BACKLOG) != 0) {
		error_log("listen attach failed");
		return false;
	}
	return true;
}

bool LoginServer::asyncDBInit() {
	m_dbChannel = new CServerAsync(this, CServerAsync::SERVER_ASYNC_DB_WRITE, 0);
	if (m_dbChannel == NULL) {
		return false;
	}
	return m_dbChannel->init();
}

bool LoginServer::asyncAllServerInit() {
	m_allServerChannel = new CServerAsync(this, CServerAsync::SERVER_ASYNC_ALL_SERVER, 0);
	if (m_allServerChannel == NULL) {
		return false;
	}
	return m_allServerChannel->init();
}

bool LoginServer::asyncTransitInit() {
	m_transitChannel = new CServerAsync(this, CServerAsync::SERVER_ASYNC_TRANSIT, 0);
	if (m_transitChannel == NULL) {
		return false;
	}
	return m_transitChannel->init();
}

void LoginServer::onIdle() {
	CNetPacket* packet = NULL;
	CStaticBuffer<MAX_PACKET_SIZE> buff;
	while ((packet = getSendPacket()) != NULL) {
		packet->Encode(&buff);
		if ((packet->ptype == PROTOCOL_TYPE_ACCESS_ANSWER || packet->ptype == PROTOCOL_TYPE_LOFFLINE || packet->ptype == PROTOCOL_TYPE_LOGIN_TRANSFER)
		&& m_accessChannel) {
			if (!m_accessChannel->sendData(&buff)) {
				error_log("send access failed");
			}
		}
		if (packet->ptype == PROTOCOL_TYPE_ASYNC_DB || packet->ptype == PROTOCOL_TYPE_ASYNC_DB_TRANSFER) {
			if (!m_dbChannel->sendData(&buff)) {
				error_log("send async db failed");
			}
		}
		if (packet->ptype == PROTOCOL_TYPE_ALL_SERVER_TRANSFER) {
			if (!m_allServerChannel->sendData(&buff)) {
				error_log("send async rank failed");
			}
		}
		if (packet->ptype == PROTOCOL_TYPE_SERVER_ASYNC) {
			do {
				uint32_t sid = Config::GetZoneByUID(packet->uid);
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
				if (!m_battles[sid]->sendData(&buff)) {
					error_log("send to other login error sid=%u", sid);
				}
			} while (false);
		}
		if (packet->ptype == PROTOCOL_TYPE_TRANSIT_TRANSFER && m_transitChannel != NULL) {
			if (!m_transitChannel->sendData(&buff)) {
				error_log("send to transit error");
			}
		}
		if (packet->ptype == PROTOCOL_TYPE_ADMIN && m_admins.count(packet->fd) && m_admins[packet->fd] != NULL) {
			m_admins[packet->fd]->sendData(&buff);
		}
		delete packet;
	}
}

bool LoginServer::addPacket(IBuffer* pBuff) {
	CNetPacket* packet = new CNetPacket();
	if (!packet->Decode(pBuff)) {
		error_log("packet decode failed");
		delete packet;
		return false;
	}

	addRecvPacket(packet);

	return true;
}

bool LoginServer::addRecvPacket(CNetPacket* packet) {
	if (m_recvMutex.acquire() == 0) {
		++m_recvCount;
		if ((packet->cmd == PROTOCOL_CMD_LOGIN && packet->subCmd == PROTOCOL_SUBCMD_LOGIN && packet->ptype == PROTOCOL_TYPE_ACCESS_TRANSFER)
		|| (packet->cmd == PROTOCOL_CMD_BATTLE && packet->subCmd == PROTOCOL_SUBCMD_BATTLE_CONFIRM && packet->ptype == PROTOCOL_TYPE_ACCESS_TRANSFER)) {
			m_recvLowQueue.push_back(packet);
		} else {
			m_recvHighQueue.push_back(packet);
		}
		m_recvCond.Signal();
		m_recvMutex.release();
	}
	return true;
}

CNetPacket* LoginServer::getSendPacket() {
	CNetPacket* packet = NULL;
	if (m_sendMutex.acquire() == 0) {
		AsyncDBManager::getInstance()->getEncodedPacket(m_sendQueue);
		if (!m_sendQueue.empty()) {
			packet = m_sendQueue.front();
			m_sendQueue.pop_front();
		}
		m_sendMutex.release();
	}
	return packet;
}

bool LoginServer::sendData(CNetPacket* packet) {
	if (m_sendMutex.acquire() == 0) {
		CNetPacket* pTmp = new CNetPacket(*packet);
		if (!pTmp) {
			error_log("maybe memory not enough! uid=%u", packet->uid);
			m_sendMutex.release();
			return false;
		}
		m_sendQueue.push_back(pTmp);
		m_sendMutex.release();
	}
	return true;
}

bool LoginServer::timerInit() {
	if (!m_pListener) {
		error_log("must init listener first");
		return false;
	}
	m_timer = new CTimerThread(m_addr.c_str(), m_port, 500000, 0);
	if (m_timer == NULL) {
		error_log("create timer error");
		return false;
	}
	if (!m_timer->Start()) {
		error_log("start timer error");
		return false;
	}
	return true;
}

uint64_t LoginServer::getBattleId(CNetPacket * packet) {
	double bid = 0;
	CBufferReader reader(&packet->body);
	reader.Skip(2);
	reader.GetDouble(bid);
	return (uint64_t) bid;
}

void LoginServer::onExit() {
	vector<FDINFO> vecFd;
	FdManager::getInstance()->getAllFd(vecFd);
	for (vector<FDINFO>::iterator it = vecFd.begin(); it != vecFd.end(); ++it) {
		uint32_t uid;
		uint32_t rid;
		if (FdManager::getInstance()->getRole(it->fd, it->time, it->microTime, uid, rid)) {
			info_log("kick user uid:%d", uid);
			PlayerManager::getInstance()->forceKick(uid, "login_exit");
		}
	}
	LogicManager::getInstance()->onExit();
	m_recvCond.Broadcast();
	if (m_timer != NULL) {
		m_timer->Stop();
	}
}

bool LoginServer::removeLogPacketItem(LogPacketItem& item) {
	for (list<LogPacketItem>::iterator iter = logItemList.begin(); iter != logItemList.end(); ++iter) {
		if (iter->ptype == item.ptype && iter->cmd == item.cmd && iter->subCmd == item.subCmd) {
			// 取最长耗时
			if (iter->span > item.span) {
				item = *iter;
			}
			logItemList.erase(iter);
			return true;
		}
	}
	return false;
}

bool LoginServer::printStat() {
	if (Time::GetGlobalTime() % 360 == 0) {
		for (list<LogPacketItem>::iterator iter = logItemList.begin(); iter != logItemList.end(); ++iter) {
			LogPacketItem& item = *iter;
			info_log("packet_span_time uid=%u fd=%u mts=%u span=%u ptype=%u cmd=%u subCmd=%u", item.uid, item.fd, item.mts, item.span, item.ptype, item.cmd, item.subCmd);
		}
	}

	if (Time::GetGlobalTime() % 300 == 0) {
		info_log("pack_info lowSize=%u highSize=%u sendSize=%u recvCount=%u", m_lSize, m_hSize, m_sendSize, m_recvCount);
	}

	return true;
}

void LoginServer::doLogic() {
	int i = 0;
	while (!IsClosed) {
		CNetPacket* packet = NULL;
		if (m_recvMutex.acquire() == 0) {
			if ((m_recvHighQueue.empty() || ++i % PRIORITY_QUEUE_FACTOR == 0) && !m_recvLowQueue.empty()) {
				i = 0;
				packet = m_recvLowQueue.front();
				m_recvLowQueue.pop_front();
			} else if (!m_recvHighQueue.empty()) {
				packet = m_recvHighQueue.front();
				m_recvHighQueue.pop_front();
			} else {
				packet = NULL;
				m_recvCond.Wait(m_recvMutex.getMutex());
			}
			m_recvMutex.release();
		}
		if (packet != NULL) {
			logStat(packet);
			LogicManager::getInstance()->doPacket(packet);
			delete (packet);
		}
	}
}

void LoginServer::logStat(CNetPacket *packet) {
	if (packet == NULL) {
		return;
	}
	struct timeval tv;
	gettimeofday(&tv, NULL);
	uint32_t mts = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	if (logItem.ptype != PROTOCOL_TYPE_TRANSIT_ANSWER
	&& logItem.cmd != PROTOCOL_CMD_LOGIC
	&& logItem.mts > 0
	&& (logItem.span = mts - logItem.mts) > 0) {
		removeLogPacketItem(logItem);
		list<LogPacketItem>::iterator iter = logItemList.begin();
		for (; iter != logItemList.end(); ++iter) {
			if (logItem.span > iter->span) {
				break;
			}
		}
		logItemList.insert(iter, logItem);
		while (logItemList.size() > 10) {
			logItemList.pop_back();
		}
	}

	logItem.uid = packet->uid;
	logItem.fd = packet->fd;
	logItem.ptype = packet->ptype;
	logItem.cmd = packet->cmd;
	logItem.subCmd = packet->subCmd;
	logItem.mts = mts;
}
