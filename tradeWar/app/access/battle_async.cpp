#include <sys/un.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include "battle_async.h"
#include "config.h"
#include "client_manager.h"
#include "battle_manager.h"

#define CLOSE(fd) {if(fd != 0) close(fd);fd=0;}
#define MAX_BUFF_LEN 10240000

CBattleAsync::CBattleAsync(CPollThread *o, uint32_t serverId) {
	m_packetOutCount = 0;
	ownerUnit = o;
	m_serverId = serverId;
	m_isConnected = false;
	m_stat = IDLE;
	m_bodyLen = 0;
	m_recvBufLen = 0;
	init();
}

CBattleAsync::~CBattleAsync() {

}

int CBattleAsync::init() {

	if (!parseAddress()) {
		LOG_ERROR("parse address failed");
		return -1;
	}

	struct sockaddr_in inaddr;
	int fd, flags, n;

	if ((fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		LOG_ERROR("make tcp socket error, %m");
		return -1;
	}

	netfd = fd;
	LOG_DEBUG("get socket %d", netfd);

	bzero(&inaddr, sizeof(struct sockaddr_in));
	inaddr.sin_family = AF_INET;
	inaddr.sin_port = htons(m_port);

	if (inet_pton(AF_INET, m_addr, &inaddr.sin_addr) <= 0) {
		LOG_EMERG("invalid address:[%s %d]", m_addr, m_port);
		return -1;
	}

	//set the socket to nonblock
	flags = fcntl(fd, F_GETFL, 0);
	fcntl(fd, F_SETFL, flags | O_NONBLOCK);

	int sockRcvBufLen = SIZE_RECV_BUFF;
	setsockopt(netfd, SOL_SOCKET, SO_RCVBUF, &sockRcvBufLen, sizeof(sockRcvBufLen));

	if ((n = connect(fd, (const struct sockaddr *) &inaddr, sizeof(inaddr))) < 0) {
		if (errno != EINPROGRESS) {
			LOG_ERROR("connect failed,errno:%d %s", errno, strerror(errno));
			return -1;
		}

		LOG_INFO("wait to connected");

		m_stat = CONNECTING;

		EnableInput();
		EnableOutput();

		if (AttachPoller() != 0) {
			LOG_ERROR("AttachPoller failed");
		}
	}

	if (n == 0) {
		LOG_INFO("connect to [%s:%d] success immediately", m_addr, m_port);
		m_stat = CONNECTED;
		EnableInput();
		EnableOutput();
		if (Attach() != 0) {
			LOG_ERROR("AttachPoller failed");
		}
		onConnected();
	}

	return 0;
}

int CBattleAsync::Attach() {
	EnableInput();

	if (AttachPoller()) {
		return -1;
	}

	return 0;
}

int CBattleAsync::connectingProcess(int src) {
	if (src == SRC_INPUT || src == SRC_OUTPUT) {
		int error;
		socklen_t len = sizeof(error);

		if (getsockopt(netfd, SOL_SOCKET, SO_ERROR, &error, &len) < 0) {
			LOG_ERROR("connected to [%s:%d] failed, %s", m_addr, m_port, strerror(errno));

			m_stat = IDLE;
			DetachPoller();
			CLOSE(netfd);
			return -1;
		}

		if (error) {
			LOG_ERROR("connected to [%s:%d] failed,%s", m_addr, m_port, strerror(error));

			m_stat = IDLE;

			DetachPoller();
			CLOSE(netfd);
			return -1;
		}

		m_stat = CONNECTED;

		LOG_INFO("connect to [%s:%d] success", m_addr, m_port);

		EnableOutput();
		EnableInput();
		ApplyEvents();
		onConnected();
	} else if (src == SRC_HANGUP) //some error occured
			{
		int error;
		socklen_t len = sizeof(error);

		if (getsockopt(netfd, SOL_SOCKET, SO_ERROR, &error, &len) < 0) {
			LOG_ERROR("connected to [%s:%d] failed", m_addr, m_port);
		} else if (error) {
			LOG_ERROR("connected to [%s:%d] failed", m_addr, m_port);
		}

		m_stat = IDLE;
		DetachPoller();
		CLOSE(netfd);
	}

	return 0;
}

bool CBattleAsync::sendData(const string& data) {

	if (m_outBuf.length() > MAX_BUFF_LEN) {
		LOG_ERROR("buff too long [%s:%d]", m_addr, m_port);
		return false;
	}
	m_outBuf.append(data);

	if (m_stat == CONNECTED) {
		EnableOutput();
		ApplyEvents();
		return true;
	}

	if (m_stat == IDLE) {
		init();
	}

	return false;
}

void CBattleAsync::OutputNotify(void) {
	if (m_stat == CONNECTING) {
		connectingProcess(SRC_OUTPUT);
		return;
	}
	if (m_outBuf.empty()) {
		return;
	}
	int sendLen = send(netfd, m_outBuf.c_str(), m_outBuf.length(), 0);
	if (0 > sendLen) {
		errorProcess(SRC_OUTPUT);
		return;
	}
	m_outBuf.erase(0, sendLen);
	if (m_outBuf.length() == 0) {
		DisableOutput();
		ApplyEvents();
	}
}

void CBattleAsync::InputNotify(void) {
	if (m_stat == CONNECTING) {
		connectingProcess(SRC_INPUT);
		return;
	}

	recvProcess();
}

void CBattleAsync::HangupNotify(void) {
	errorProcess(SRC_HANGUP);
}

int CBattleAsync::errorProcess(int src) {
	LOG_ERROR("error occured [%s:%d],src=%d", m_addr, m_port, src);

	m_stat = IDLE;
	m_outBuf.clear();
	DetachPoller();
	CLOSE(netfd);

	return 0;
}

void CBattleAsync::recvProcess() {

	int len = recv(netfd, m_recvBuf + m_recvBufLen, sizeof(m_recvBuf) - m_recvBufLen, 0);
	if (len == 0) {
		LOG_ERROR("peer close [%s:%d]", m_addr, m_port);
		errorProcess(SRC_INPUT);
		return;
	} else if (len < 0) {
		errorProcess(SRC_INPUT);
		return;
	}
	m_recvBufLen += len;

	if (m_recvBufLen < sizeof(BattleHead)) {
		return;
	}

	do {
		if (((BattleHead*) m_recvBuf)->head != MAGIC_HEADER) {
			LOG_ERROR("invalid magic head");
			errorProcess(SRC_INPUT);
			return;
		}
		m_bodyLen = ((BattleHead*) m_recvBuf)->bodyLen;

		uint32_t packLen = m_bodyLen + sizeof(BattleHead);

		if (packLen > m_recvBufLen) {
			break;
		}

//		LOG_DEBUG("CBattleAsync_recvProcess_packLen=%u", packLen);

		m_inBuf.append(m_recvBuf, packLen);
		packetProcess();
		m_inBuf.clear();
		m_bodyLen = 0;

		memmove(m_recvBuf, m_recvBuf + packLen, m_recvBufLen - packLen);
		m_recvBufLen -= packLen;

		if (m_recvBufLen < sizeof(BattleHead)) {
			break;
		}

	} while (true);

	return;

	char buf[4096];

	if (m_inBuf.length() < sizeof(BattleHead)) {
		int len = recv(netfd, buf, sizeof(BattleHead) - m_inBuf.length(), 0);
		if (len == 0) {
			LOG_ERROR("peer close [%s:%d]", m_addr, m_port);
			errorProcess(SRC_INPUT);
			return;
		} else if (len < 0) {
			errorProcess(SRC_INPUT);
			return;
		}

		m_inBuf.append(buf, len);

		if (m_inBuf.length() != sizeof(BattleHead)) {
			//LOG_ERROR("expect recv %u but only recv %u",sizeof(BattleHead),len);
			return;
		}

		if (((BattleHead*) m_inBuf.c_str())->head != MAGIC_HEADER) {
			LOG_ERROR("invalid magic head");
			errorProcess(SRC_INPUT);
		}
		m_bodyLen = ((BattleHead*) m_inBuf.c_str())->bodyLen;
		if (m_bodyLen == 0) {
			packetProcess();
			m_inBuf.clear();
			m_bodyLen = 0;
		}
	} else {
		int leftLen = m_bodyLen + sizeof(BattleHead) - m_inBuf.length();
		int expectLen = leftLen > sizeof(buf) ? sizeof(buf) : leftLen;
		int len = recv(netfd, buf, expectLen, 0);
		if (len == 0) {
			LOG_ERROR("peer close [%s:%d]", m_addr, m_port);
			errorProcess(SRC_INPUT);
			return;
		} else if (len < 0) {
			errorProcess(SRC_INPUT);
			return;
		}

		m_inBuf.append(buf, len);

		if (m_inBuf.length() == m_bodyLen + sizeof(BattleHead)) {
			packetProcess();
			m_inBuf.clear();
			m_bodyLen = 0;
			return;
		}

		if (m_inBuf.length() > m_bodyLen + sizeof(BattleHead)) {
			LOG_ERROR("invalid packet,len=%u", m_inBuf.length());
			errorProcess(SRC_INPUT);
			return;
		}
	}
}

void CBattleAsync::packetProcess() {

	doStat();

	//修改
	static ClientManager* pClient = ClientManager::getInstance();

	BattleHead* pHead = (BattleHead*) m_inBuf.c_str();
	uint32_t fd = pHead->fd;
	uint32_t time = pHead->time;
	uint32_t microTime = pHead->microTime;

	//服务端踢下线
	if (pHead->cmd == PROTOCOL_ACCESS_LOFFLINE) {
		pClient->battleClose(fd, time, microTime);
		return;
	}

	// 修改登录服务器
	if (pHead->cmd == PROTOCOL_ACCESS_CHANGE_LOGIN || pHead->cmd == PROTOCOL_ACCESS_KICK_CROSS) {
		uint16_t cmd = pHead->cmd;
		pHead->cmd = PROTOCOL_ACCESS_CHANGE_LOGIN;
		uint32_t srvId = pHead->clientIp;
		pHead->clientIp = pClient->getIp(fd, time, microTime);
		if (!BattleManager::getInstance()->sendData(m_serverId, m_inBuf)) {
			LOG_ERROR("may be srv [%u] disconnect", m_serverId);
			errorProcess(SRC_OUTPUT);
			return;
		}

		if (PROTOCOL_ACCESS_CHANGE_LOGIN == cmd) {
			pClient->updateClientSrvId(fd, time, microTime, srvId);
		}

		return;
	}

	if (pHead->cmd == PROTOCOL_ACCESS_LOGIN_TRANSFER) {
		pHead->cmd = PROTOCOL_ACCESS_LOGIN_TRANSFER;
		pHead->clientIp = pClient->getIp(fd, time, microTime);
		if (!BattleManager::getInstance()->sendData(m_serverId, m_inBuf)) {
			LOG_ERROR("may be srv [%u] disconnect", m_serverId);
			errorProcess(SRC_OUTPUT);
			return;
		}

		return;
	}

	ClientHead clientHead;
	clientHead.head = MAGIC_HEADER;
	clientHead.bodyLen = m_bodyLen;
	clientHead.crc1 = 0;
	clientHead.crc2 = 0;
	clientHead.padding1 = 0;
	clientHead.padding2 = 0;

	string packet;
	packet.append((char*) &clientHead, sizeof(ClientHead));
	packet.append(m_inBuf.begin() + sizeof(BattleHead), m_inBuf.end());

	LOG_INFO("packet_size=%u inbuf_size=%u fd=%u", packet.size(), m_inBuf.size(), fd);

	if (!pClient->sendData(fd, time, microTime, packet)) {
		LOG_ERROR("[%u-%u-%u] has gone away", fd, time, microTime);
		clientClose(fd, time, microTime, 0);
		return;
	}
}

bool CBattleAsync::clientClose(uint32_t fd, uint32_t time, uint32_t microTime, uint32_t ip) {
	BattleHead battleHead;
	battleHead.head = MAGIC_HEADER;
	battleHead.bodyLen = 0;
	battleHead.cmd = PROTOCOL_ACCESS_COFFLINE;
	battleHead.fd = fd;
	battleHead.time = time;
	battleHead.microTime = microTime;
	battleHead.clientIp = ip;

	string packet;
	packet.append((char*) &battleHead, sizeof(BattleHead));
	sendData(packet);

	return true;
}

void CBattleAsync::onConnected() {
	LOG_INFO("connect [%s:%d] ok", m_addr, m_port);
	m_inBuf.clear();
	m_recvBufLen = 0;
	m_bodyLen = 0;
}

void CBattleAsync::doStat() {
	++m_packetOutCount;
	if (m_packetOutCount % 1000000 == 0) {
		info_log("access_packet_info m_packetOutCount=%llu", m_packetOutCount);
	}
}

bool CBattleAsync::parseAddress() {
	ServerItem addr;
	if (!ServerConfig::getInstance()->GetLogin(m_serverId, addr)) {
		error_log("get server info error sid=%u", m_serverId);
		return false;
	}
	memcpy(m_addr, addr.host.c_str(), sizeof(m_addr) - 1);
	m_port = addr.port;
	return true;
}

