#include "BattleServer.h"
#include "FdManager.h"
#include "BattleInc.h"
#include "LoginServer.h"

void* LoginThread(void*) {
	if (!LoginServer::Instance()->Init()) {
		return NULL;
	}
	LoginServer::Instance()->RunningThread();
	return NULL;
}

static void OnExit() {
	BattleServer::Instance()->onExit();
	LogicManager::Instance()->onExit();
	PathManager::Instance()->onExit();
}

static bool ParseAddress(vector<CInternetAddress> &vecAddress, const string &sAddress) {
	if (sAddress.empty()) {
		return false;
	}
	vector<string> vecStrAddress;
	CBasic::StringSplitTrim(sAddress, ",", vecStrAddress);
	for (vector<string>::iterator itr = vecStrAddress.begin(); itr != vecStrAddress.end(); itr++) {
		CInternetAddress address;
		if (address.FromString(*itr)) {
			vecAddress.push_back(address);
		}
	}
	return vecAddress.size() != 0;
}

BattleServer::BattleServer() {

}

BattleServer::~BattleServer() {

}

bool BattleServer::Initialize() {
	if (!Kernel::Init()) {
		fatal_log("[Kernel::Init fail][server=Toywar]");
		return false;
	}
	vector<CInternetAddress> listenAddress;
	if (!ParseAddress(listenAddress, Config::GetValue("server_listen"))) {
		fatal_log("[ParseAddress fail]");
		return false;
	}
	int maxConn = TCP_SERVER_MAX_CONNECTIONS;
	Config::GetIntValue(maxConn, "server_max_conn");
	if (!CTcpServer::Initialize(listenAddress, maxConn)) {
		fatal_log("[TcpServer::Initialize fail]");
		return false;
	}
	if (!System::InitDaemon()) {
		fatal_log("[System::InitDaemon fail][error=%d]", errno);
		return false;
	}
	System::InitSig(NULL, OnExit);

	pthread_t pid;
	pthread_create(&pid, NULL, LoginThread, NULL);

	return true;
}

void BattleServer::OnReceive(CFirePacket *pPacket) {
	static LogicManager *logicManager = LogicManager::Instance();
	logicManager->Process(pPacket);
}

void BattleServer::OnChannelClose(CTcpChannel *pChannel) {

}

void BattleServer::OnIdle() {
	CFirePacket *pPacket = NULL;
	if (m_recvMutex.acquire() == 0) {
		if (!recvQueue.empty()) {
			pPacket = recvQueue.front();
			recvQueue.pop_front();
		} else {
			pPacket = NULL;
		}
		m_recvMutex.release();
	}
	if (pPacket != NULL) {
		OnReceive(pPacket);
		delete pPacket;
		pPacket = NULL;
	}
}

void BattleServer::onExit() {
	vector<FDINFO> vecFd;
	FdManager::Instance()->getAllFd(vecFd);
	info_log("now online user %u", vecFd.size());

	for (vector<FDINFO>::iterator it = vecFd.begin(); it != vecFd.end(); ++it) {
		CFirePacket firePacket;
		firePacket.cmd = PROTOCOL_ACCESS_COFFLINE;
		firePacket.fd = it->fd;
		firePacket.time = it->time;
		firePacket.microTime = it->microTime;

		LogicManager::Instance()->OfflineProcess(&firePacket, "battle_exit");
	}
}

void BattleServer::OnConnect(CTcpChannel *pChannel) {
	debug_log("%s", pChannel->ToString().c_str());
}

bool BattleServer::AddRecv(CFirePacket *pPacket) {
	if (m_recvMutex.acquire() == 0) {
		recvQueue.push_back(pPacket);
		m_recvMutex.release();
		return true;
	}
	return false;
}

bool BattleServer::AddSend(CFirePacket *pPacket) {
	CFirePacket *sp = new CFirePacket(pPacket);
	if (sp == NULL) {
		return false;
	}
	if (m_sendMutex.acquire() == 0) {
		sendQueue.push_back(sp);
		m_sendMutex.release();
		return true;
	}
	delete sp;
	return false;
}

CFirePacket* BattleServer::GetSend() {
	CFirePacket *pPacket = NULL;
	if (m_sendMutex.acquire() == 0) {
		if (!sendQueue.empty()) {
			pPacket = sendQueue.front();
			sendQueue.pop_front();
		}
		m_sendMutex.release();
	}
	return pPacket;
}

