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

#include "utils.h"
#include "client_async.h"
#include "ProtocolInc.h"
#include "all_server.h"

#define CLOSE(fd) {if(fd != 0) close(fd);fd=0;}

#define MAX_BUFF_SIZE 2048000

AsrvClientAsync::AsrvClientAsync(CPollThread *o, int fd) {
	ownerUnit = o;
	netfd = fd;
	memset(m_peerAddr, 0, sizeof(m_peerAddr));
	Utils::fdinfo(netfd, m_peerAddr, m_peerIp, m_peerPort);
	uint32_t now = GET_MSEC();
	m_time = now / 1000;
}

int AsrvClientAsync::Attach() {
	EnableInput();
	if (AttachPoller()) {
		return -1;
	}
	return 0;
}

AsrvClientAsync::~AsrvClientAsync() {
}

void AsrvClientAsync::InputNotify(void) {
	recvProcess();
}

void AsrvClientAsync::HangupNotify(void) {
	errorProcess(SRC_HANGUP);
}

void AsrvClientAsync::OutputNotify(void) {
	int sendLen = send(netfd, m_outBuf.GetNativeBuffer(), m_outBuf.GetSize(), 0);
	if (0 > sendLen) {
		error_log("errno=%u EAGIN addr [%s:%d],buflen=%u %m", errno, m_peerAddr, m_peerPort, m_outBuf.GetSize());
		errorProcess(SRC_OUTPUT);
		return;
	}
	m_outBuf.Remove(0, sendLen);
	if (m_outBuf.GetSize() == 0) {
		DisableOutput();
		ApplyEvents();
	}
	debug_log("kkk");
}

void AsrvClientAsync::errorProcess(int src) {
	info_log("err fd=%d, src=%d", netfd, src);
	delete this;
}

bool AsrvClientAsync::sendData(IBuffer* pData) {
	if (!m_outBuf.AppendBuffer(pData)) {
		error_log("send data failed, maybe buff too long");
		return false;
	}

	EnableOutput();
	ApplyEvents();

	return true;
}

void AsrvClientAsync::recvProcess() {
	int len = recv(netfd, m_inBuf.GetNativeBuffer() + m_inBuf.GetSize(), m_inBuf.GetFreeCapacity(), 0);
	if (len == 0) {
		error_log("peer close [%s:%d] fd=%d", m_peerAddr, m_peerPort, netfd);
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

bool AsrvClientAsync::packetProcess(IBuffer* pBuff) {
	CNetPacket *p = new CNetPacket;
	if (p == NULL) {
		error_log("why");
		return false;
	}
	if (!p->Decode(pBuff)) {
		error_log("decode failed");
		delete p;
		return false;
	}
	p->uid = p->fd;
	AsrvServer::getInstance()->addRecvPacket(p);
	return true;
}

void AsrvClientAsync::onClientClose() {

}
