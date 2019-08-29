#include <sys/un.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>

#include "ServerAsync.h"
#include "ServerConfig.h"

#define CLOSE(fd) {if(fd != 0) close(fd);fd=0;}
#define MAX_BUFF_LEN 10240000

CServerAsync::CServerAsync(CPollThread *o, uint32_t type, uint32_t sid) {
	ownerUnit = o;
	m_stat = IDLE;
	m_port = 0;
	m_init = false;
	m_sid = sid;
	m_type = type;
}

CServerAsync::~CServerAsync() {
}

bool CServerAsync::init() {
	if (m_stat != IDLE) {
		return true;
	}
	ServerItem cfg;
	bool ret = false;
	switch (m_type)
	{
	case SERVER_ASYNC_DB_WRITE:
		ret = ServerConfig::getInstance()->GetDbWrite(cfg);
		break;
	case SERVER_ASYNC_ALL_SERVER:
		ret = ServerConfig::getInstance()->GetAllServer(cfg);
		break;
	case SERVER_ASYNC_TRANSIT:
		ret = ServerConfig::getInstance()->GetTransit(cfg);
		break;
	case SERVER_ASYNC_LOGIN:
		ret = ServerConfig::getInstance()->GetLogin(m_sid, cfg);
		break;
	}
	if (!ret) {
		return false;
	}

	memcpy(m_addr, cfg.host.c_str(), sizeof(m_addr));
	m_port = cfg.port;

	m_init = true;

	if (!connectServer()) {
		error_log("connect server failed");
		return false;
	}
	return true;
}

bool CServerAsync::connectServer() {
	if (!m_init) {
		return false;
	}
	struct sockaddr_in inaddr;
	int fd, flags, n;
	if ((fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		error_log("make tcp socket error, %m");
		return false;
	}
	netfd = fd;
	bzero(&inaddr, sizeof(struct sockaddr_in));
	inaddr.sin_family = AF_INET;
	inaddr.sin_port = htons(m_port);
	if (inet_pton(AF_INET, m_addr, &inaddr.sin_addr) <= 0) {
		error_log("invalid address:[%s %d]", m_addr, m_port);
		return false;
	}
	flags = fcntl(fd, F_GETFL, 0);
	fcntl(fd, F_SETFL, flags | O_NONBLOCK);
	if ((n = connect(fd, (const struct sockaddr *) &inaddr, sizeof(inaddr))) < 0) {
		if (errno != EINPROGRESS) {
			error_log("connect failed,errno:%d %s", errno, strerror(errno));
			return false;
		}
		m_stat = CONNECTING;
		EnableInput();
		EnableOutput();
		if (AttachPoller() != 0) {
			error_log("AttachPoller failed");
		}
	}
	if (n == 0) {
		m_stat = CONNECTED;
		if (Attach() != 0) {
			error_log("AttachPoller failed");
		}
		onConnected();
	}
	return true;
}

int CServerAsync::Attach() {
	EnableInput();
	if (AttachPoller()) {
		return -1;
	}
	return 0;
}

int CServerAsync::connectingProcess(int src) {
	if (src == SRC_INPUT || src == SRC_OUTPUT) {
		int error;
		socklen_t len = sizeof(error);
		if (getsockopt(netfd, SOL_SOCKET, SO_ERROR, &error, &len) < 0) {
			error_log("connected to [%s:%d] failed, %s", m_addr, m_port, strerror(errno));
			m_stat = IDLE;
			DetachPoller();
			CLOSE(netfd);
			return -1;
		}
		if (error) {
			error_log("connected to [%s:%d] failed,%s", m_addr, m_port, strerror(error));
			m_stat = IDLE;
			DetachPoller();
			CLOSE(netfd);
			return -1;
		}
		m_stat = CONNECTED;
		info_log("connect to [%s:%d] success", m_addr, m_port);
		EnableOutput();
		EnableInput();
		ApplyEvents();
		onConnected();
	} else if (src == SRC_HANGUP) { //some error occured
		int error;
		socklen_t len = sizeof(error);
		if (getsockopt(netfd, SOL_SOCKET, SO_ERROR, &error, &len) < 0) {
			error_log("connected to [%s:%d] failed", m_addr, m_port);
		} else if (error) {
			error_log("connected to [%s:%d] failed", m_addr, m_port);
		}
		m_stat = IDLE;
		DetachPoller();
		CLOSE(netfd);
	}
	return 0;
}

bool CServerAsync::sendData(IBuffer* pData) {
	if (!m_outBuf.AppendBuffer(pData)) {
		error_log("buff too long [%s:%d]", m_addr, m_port);
		return false;
	}
	if (m_stat == CONNECTED) {
		EnableOutput();
		ApplyEvents();
		return true;
	}
	if (m_stat == IDLE) {
		connectServer();
	}
	return false;
}

void CServerAsync::OutputNotify(void) {
	if (m_stat == CONNECTING) {
		connectingProcess(SRC_OUTPUT);
		return;
	}
	int sendLen = send(netfd, m_outBuf.GetNativeBuffer(), m_outBuf.GetSize(), 0);
	if (0 > sendLen) {
		errorProcess(SRC_OUTPUT);
		return;
	}
	m_outBuf.Remove(0, sendLen);
	if (m_outBuf.GetSize() == 0) {
		DisableOutput();
		ApplyEvents();
	}
}

void CServerAsync::InputNotify(void) {
	if (m_stat == CONNECTING) {
		connectingProcess(SRC_INPUT);
		return;
	}
	recvProcess();
}

void CServerAsync::HangupNotify(void) {
	errorProcess(SRC_HANGUP);
}

int CServerAsync::errorProcess(int src) {
	error_log("error occured [%s:%d],src=%d,reason=%m", m_addr, m_port, src);
	m_stat = IDLE;
	DetachPoller();
	CLOSE(netfd);
	return 0;
}

void CServerAsync::recvProcess() {
	int len = recv(netfd, m_inBuf.GetNativeBuffer() + m_inBuf.GetSize(), m_inBuf.GetFreeCapacity(), 0);
	if (len == 0) {
		error_log("peer close [%s:%d] fd=%d", m_addr, m_port, netfd);
		onClientClose();
		errorProcess(SRC_INPUT);
		return;
	} else if (len < 0) {
		errorProcess(SRC_INPUT);
		return;
	}
	m_inBuf.SetSize(m_inBuf.GetSize() + len);
	uint32_t start = 0;
	do {
		if (m_inBuf.GetSize() - start < sizeof(ServerHead)) {
			break;
		}
		ServerHead* pHead = (ServerHead*) (m_inBuf.GetNativeBuffer() + start);
		if (pHead->magic != MAGIC_HEADER) {
			error_log("invalid magic head,%u", pHead->magic);
			errorProcess(SRC_INPUT);
			return;
		}
		if (m_inBuf.GetSize() - start < sizeof(ServerHead) + pHead->bodyLen) {
			break;
		}
		CStaticBuffer<MAX_PACKET_SIZE> packet;
		packet.Append(m_inBuf.GetNativeBuffer() + start, pHead->bodyLen + sizeof(ServerHead));
		packetProcess(&packet);
		start += pHead->bodyLen + sizeof(ServerHead);
	} while (true);
	if (start > 0) {
		m_inBuf.Remove(0, start);
	}
}

void CServerAsync::onConnected() {
	info_log("connect [%s:%d] ok", m_addr, m_port);
	if (m_outBuf.GetSize() != 0) {
		EnableOutput();
		ApplyEvents();
	}
}

void CServerAsync::packetProcess(IBuffer* pBuff) {
	if (ownerUnit == NULL) {
		return;
	}
	ownerUnit->addPacket(pBuff);
}

void CServerAsync::onClientClose() {

}
