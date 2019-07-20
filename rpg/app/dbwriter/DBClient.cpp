#include <stdio.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <fcntl.h>
#include <assert.h>
#include <errno.h>
#include <libgen.h>
#include <stddef.h>

#include "AsyncDBManager.h"
#include "DBClientManager.h"
#include "DBClient.h"
#include "PollThread.h"
#include "Utils.h"

#define CLOSE(fd) {if(fd != 0) close(fd);fd=0;}

CDBClientAsync::CDBClientAsync(CPollThread *o, int fd) {
	ownerUnit = o;
	netfd = fd;
	memset(m_peerAddr, 0, sizeof(m_peerAddr));
	Utils::fdinfo(netfd, m_peerAddr, m_peerIp, m_peerPort);
	DBClientManager::Instance()->addClient(this);
}

int CDBClientAsync::Attach() {
	EnableInput();

	if (AttachPoller()) {
		return -1;
	}

	return 0;

}

CDBClientAsync::~CDBClientAsync() {

}

void CDBClientAsync::InputNotify(void) {
	recvProcess();
}

void CDBClientAsync::HangupNotify(void) {
	errorProcess(SRC_HANGUP);
}

void CDBClientAsync::OutputNotify(void) {
}

int CDBClientAsync::errorProcess(int src) {
	DetachPoller();
	delete this;
	return 0;
}

bool CDBClientAsync::sendData(IBuffer* pData) {
	return false;
}

void CDBClientAsync::recvProcess() {
	int len = recv(netfd, m_inBuf.GetNativeBuffer() + m_inBuf.GetSize(), m_inBuf.GetFreeCapacity(), 0);
	if (len == 0) {
		error_log("peer close [%s:%d] fd=%d", m_peerAddr, m_peerPort, netfd);
		errorProcess(SRC_INPUT);
		return;
	} else if (len < 0) {
		errorProcess(SRC_INPUT);
		return;
	}
	uint32_t decodeSize = 0;
	m_inBuf.SetSize(m_inBuf.GetSize() + len);
	DataPacket packet;
	do {
		packet.Clean();
		bool ret = packet.Decode(&m_inBuf);
		decodeSize = packet.GetDecodeSize();
		if (decodeSize > 0) {
			if (!ret) {
				error_log("decode error");
				decodeSize = 0;
				break;
			}
			m_inBuf.Remove(0, decodeSize);
		}
		if (ret) {
			AsyncDBManager::getInstance()->push(packet);
			debug_log("%u", packet.body.GetSize());
		}
	} while (decodeSize > 0);
}
