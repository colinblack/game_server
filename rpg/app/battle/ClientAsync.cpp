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

#include "Kernel.h"
#include "ClientAsync.h"
#include "Utils.h"
#include "ClientManager.h"
#include "BattleServer.h"
#include "LogicManager.h"

static inline uint32_t GET_MSEC(void) {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

#define CLOSE(fd) {if(fd != 0) close(fd);fd=0;}

#define MAX_BUFF_SIZE 2048000

ClientAsync::ClientAsync(CPollThread *o, int fd) {
	ownerUnit = o;
	netfd = fd;
	memset(m_peerAddr, 0, sizeof(m_peerAddr));
	Utils::fdinfo(netfd, m_peerAddr, m_peerIp, m_peerPort);
	uint32_t now = GET_MSEC();
	m_time = now / 1000;
	m_microTime = now % 1000;
	m_cSeq = 0;
	m_sSeq = 0;
	m_stat = CONN_START;
	m_wsHeadLen = 0;
	m_wsBodyLen = 0;
	m_wsDataLen = 0;

	m_sendBuf.clear();
	m_recvBuf.clear();
	m_wsInBuf.clear();
	m_isHttp = false;
	m_bWebSocket = false;

	ClientManager::Instance()->AddClient(this);
}

int ClientAsync::Attach() {
	EnableInput();

	if (AttachPoller()) {
		return -1;
	}

	return 0;
}

ClientAsync::~ClientAsync() {
	ClientManager::Instance()->DelClient(this);
}

void ClientAsync::InputNotify(void) {
	switch (m_stat) {
	case CONN_START:
		startProcess();
		break;
	default:
		recvProcess();
		break;
	}
}

void ClientAsync::HangupNotify(void) {
	errorProcess(SRC_HANGUP);
}

void ClientAsync::OutputNotify(void) {
	int byteLeft = m_sendBuf.length();
	if (byteLeft == 0) {
		DisableOutput();
		ApplyEvents();
		return;
	}

	int byteSent = send(netfd, m_sendBuf.c_str(), byteLeft, 0);
	if (0 > byteSent) {
		error_log("errno=%u EAGIN addr [%s:%d],buflen=%u %m", errno, m_peerAddr, m_peerPort, m_sendBuf.c_str());
		errorProcess(SRC_OUTPUT);
		return;
	}

	m_sendBuf.erase(0, byteSent);
}

void ClientAsync::errorProcess(int src) {
	if (!m_isHttp) {
		error_log("error occured [%s:%d],seq=%u,src=%d,errno=%u", m_peerAddr, m_peerPort, m_cSeq, src, errno);
	}

	DetachPoller();

	delete this;

	return;
}

bool ClientAsync::sendData(const string& data) {
	if (m_sendBuf.length() > MAX_BUFF_SIZE) {
		error_log("buf too long,[%s:%d],close it netfd=%u", m_peerAddr, m_peerPort, netfd);
		errorProcess(101);
		return false;
	}

	if (m_stat == CONN_START) {
		EnableOutput();
		ApplyEvents();
		m_sendBuf.append(data.c_str(), data.length());
		return true;
	}

	EnableOutput();
	ApplyEvents();

	onWsEncode(data, m_sendBuf);

	return true;
}

bool ClientAsync::onBattleMsg(CFirePacket *pPacket) {
	if (pPacket == NULL) {
		return false;
	}

	static string packet;
	packet.clear();

	byte head = 0;
	byte seq = (++m_sSeq) % 256;

	if (pPacket->callback != 0) {
		head = 32;
		packet.append((char*) &head, sizeof(head));
		packet.append((char*) &seq, sizeof(seq));
		packet.append((char*) &(pPacket->callback), sizeof(uint32_t));
		packet.append((char*) &(pPacket->errorCode), sizeof(uint32_t));
		packet.append((char*) &(pPacket->msgId), sizeof(int32_t));
	} else {
		head = 48;
		packet.append((char*) &head, sizeof(head));
		packet.append((char*) &seq, sizeof(seq));
		packet.append((char*) &(pPacket->subCmd), sizeof(uint32_t));
		packet.append((char*) &(pPacket->msgId), sizeof(int32_t));
	}
	IBuffer *body = pPacket->GetBody();
	packet.append((char*) body->GetNativeBuffer(), body->GetSize());

	return sendData(packet);
}

void ClientAsync::recvProcess() {
	if (m_bWebSocket) {
		if (!getWsHeadLen()) {
			onWsError(WS_ERR_HEADLEN);
			return;
		}
		if (!getWsBodyLen()) {
			onWsError(WS_ERR_BODYLEN);
			return;
		}
		if (!getWsBodyData()) {
			onWsError(WS_ERR_BODYDATA);
			return;
		}
	} else {
		char buf[0xFFFF];
		int len = recv(netfd, buf, 0xFFFF, 0);
		if (len > 0) {
			m_recvBuf.append(buf, len);
		} else if (len == 0) {
			onWsError(SRC_INPUT);
			return;
		} else if (len < 0) {
			if (errno != EAGAIN) {
				onWsError(SRC_INPUT);
			}
		}
	}

	while (m_recvBuf.length() != 0) {
		if (!decodeProcess()) {
			return;
		}
	}
}

bool ClientAsync::decodeProcess() {
	if (m_recvBuf.length() < sizeof(ClientHead)) {
		error_log("%u", m_recvBuf.length());
		return false;
	}
	ClientHead *pHead = (ClientHead*) (m_recvBuf.c_str());
	if (pHead->head != FP_CHEAD) {
		error_log("invalid magic head,head=%d", pHead->head);
		errorProcess(SRC_INPUT);
		return false;
	}
	if (pHead->seq != (m_cSeq + 1) % 256) {
		error_log("invalid seq s=%d c=%d", pHead->seq, m_cSeq);
		errorProcess(SRC_INPUT);
		return false;
	}

	m_cSeq = pHead->seq;

	unsigned end_pos = m_recvBuf.length();
	const char* pos = m_recvBuf.c_str();
	for (unsigned i = 0; i < m_recvBuf.length(); ++i) {
		//next packet
		if (i > 0 && *(pos + i) == FP_CHEAD && (i + 1) < m_recvBuf.length() && *(pos + i + 1) == (m_cSeq + 1) % 256) {
			end_pos = i - 1;
			break;
		}
	}

	if (end_pos < sizeof(ClientHead)) {
		error_log("end pos error %u", end_pos);
		errorProcess(SRC_INPUT);
		return false;
	}

	if (end_pos > m_recvBuf.size()) {
		error_log("end pos error %u %u", end_pos, m_recvBuf.size());
		errorProcess(SRC_INPUT);
		return false;
	}

	CFirePacket *packet = new CFirePacket();
	if (packet == NULL) {
		return false;
	}
	packet->head = FP_SHEAD;
	packet->bodyLen = end_pos - sizeof(ClientHead);
	packet->cmd = PROTOCOL_ACCESS_TRANSFER;
	packet->fd = netfd;
	packet->time = m_time;
	packet->microTime = m_microTime;
	packet->clientIp = m_peerIp;
	packet->subCmd = pHead->command;
	packet->callback = pHead->callback;
	packet->msgId = pHead->msgId;
	packet->body.Append((byte*)m_recvBuf.c_str() + sizeof(ClientHead), end_pos - sizeof(ClientHead));

	m_recvBuf.erase(0, end_pos);

	if (!BattleServer::Instance()->AddRecv(packet)) {
		delete packet;
		packet = NULL;
	}

	return true;
}

void ClientAsync::startProcess() {
	char buf[1024] = { 0 };
	int len = recv(netfd, buf, sizeof(buf) - 1, 0);
	if (len <= 0) {
		errorProcess(SRC_INPUT);
		return;
	}
	if (strstr(buf, "GET ") != buf) {
		m_recvBuf.append(buf, len);
		m_stat = CONN_COMPLETE;
	} else {
		char *str = strstr(buf, "Sec-WebSocket-Key");
		if (str == NULL) {
			onHttpHead();
			return;
		}
		char *str1 = strstr(str, ":");
		if (str1 == NULL) {
			error_log("key not exists [%s:%d] fd=%d buf=%s", m_peerAddr, m_peerPort, netfd, buf);
			errorProcess(SRC_INPUT);
			return;
		}
		char *str2 = strstr(str1, "\r\n");
		if (str2 == NULL) {
			error_log("key not exists [%s:%d] fd=%d buf=%s", m_peerAddr, m_peerPort, netfd, buf);
			errorProcess(SRC_INPUT);
			return;
		}
		string key;
		key.append(str1 + 2, str2);
		string acceptKey;
		if (!Crypt::Base64Encode(acceptKey, Crypt::Sha1Raw(key + "258EAFA5-E914-47DA-95CA-C5AB0DC85B11"))) {
			error_log("Base64Encode error [%s:%d] fd=%d acceptKey=%s", m_peerAddr, m_peerPort, netfd, acceptKey.c_str());
			errorProcess(SRC_INPUT);
			return;
		}

		string upgrade = "HTTP/1.1 101 Switching Protocols\r\n";
		upgrade += "Upgrade: websocket\r\n";
		upgrade += "Connection: Upgrade\r\n";
		upgrade += "Sec-WebSocket-Accept: " + acceptKey + "\r\n";
		upgrade += "\r\n";

		sendData(upgrade);

		m_stat = CONN_COMPLETE;
		m_bWebSocket = true;

		info_log("key=%s,acceptKey=%s,fd=%d", key.c_str(), acceptKey.c_str(), netfd);
	}
}

void ClientAsync::onWsEncode(const string &data, string &result) {
	if (!m_bWebSocket) {
		result.append(data.c_str(), data.length());
		return;
	}

	uint64_t data_len = data.length();
	if (data_len == 0) {
		return;
	}

	/*
	 * 0x81 for text   10000001
	 * 0x82 for binary 10000010
	 */
	char flag = 0x82;
	char payload_len = 0;
	result.append(&flag, 1);
	if (data_len < 0x7E) {
		char len = data_len;
		result.append(&len, 1);
	} else if (data_len < 0xFFFF) {
		payload_len = 0x7E;
		result.append(&payload_len, 1);
		uint16_t len = data_len;
		len = htons(len);
		result.append((char*)&len, 2);
	} else {
		payload_len = 0x7F;
		result.append(&payload_len, 1);
		uint64_t len = data_len;
		len = hton64(len);
		result.append((char*)&len, 8);
	}
	result.append(data.c_str(), data.length());
	return;
}

bool ClientAsync::battleClose() {
	info_log("battle kick [%s:%u]", m_peerAddr, m_peerPort);

	errorProcess(100);

	return true;
}

bool ClientAsync::getWsHeadLen() {
	if (m_wsHeadLen != 0) {
		return true;
	}
	if (m_wsInBuf.length() < WS_HEAD_FLAG && !recvWsBuffer(WS_HEAD_FLAG - m_wsInBuf.length())) {
		error_log("recvWsBuffer error len=%u", m_wsInBuf.length());
		return false;
	}
	if (m_wsInBuf.length() < WS_HEAD_FLAG) {
		return true;
	}

	const char* pBuf = m_wsInBuf.data();
	uint8_t fin = pBuf[0] & 0x80;
	if (fin != 0x80) {
		error_log("fin error [%s:%d] fd=%d fin=%d", m_peerAddr, m_peerPort, netfd, (int )fin);
	}
	uint8_t opcode = pBuf[0] & 0xF;
	if (opcode != 0x2) {
		error_log("opcode error [%s:%d] fd=%d opcode=%d", m_peerAddr, m_peerPort, netfd, (int )opcode);
		return false;
	}
	uint8_t mask = pBuf[1] & 0x80;
	if (mask != 0x80) {
		error_log("mask error [%s:%d] fd=%d mask=%d", m_peerAddr, m_peerPort, netfd, (int )mask);
		return false;
	}

	m_wsDataLen = pBuf[1] & 0x7F;
	switch (m_wsDataLen) {
	case 0x7E:
		m_wsHeadLen = WS_MIDDLE_HEAD;
		break;
	case 0x7F:
		m_wsHeadLen = WS_LARGE_HEAD;
		break;
	default:
		m_wsHeadLen = WS_LITTLE_HEAD;
		break;
	}

	return true;
}

bool ClientAsync::getWsBodyLen() {
	if (m_wsBodyLen > 0) {
		return true;
	}

	if (m_wsInBuf.length() < m_wsHeadLen && !recvWsBuffer(m_wsHeadLen - m_wsInBuf.length())) {
		return false;
	}

	if (m_wsInBuf.length() < m_wsHeadLen) {
		return true;
	}

	const char* pBuf = m_wsInBuf.data();
	if (m_wsDataLen == 0x7E) {
		uint16_t dataLen = *((uint16_t*) (pBuf + 2));
		m_wsBodyLen = ntohs(dataLen);
	} else if (m_wsDataLen == 0x7F) {
		uint64_t dataLen = *((uint64_t*) (pBuf + 2));
		m_wsBodyLen = ntoh64(dataLen);
	} else {
		m_wsBodyLen = m_wsDataLen;
	}

	if (m_wsBodyLen == 0) {
		error_log("body len error [%s:%d] fd=%d", m_peerAddr, m_peerPort, netfd);
		return false;
	}
	return true;
}

bool ClientAsync::getWsBodyData() {
	if (m_wsBodyLen == 0) {
		return true;
	}
	uint64_t packetLen = m_wsHeadLen + m_wsBodyLen;
	if (m_wsInBuf.length() < packetLen && !recvWsBuffer(packetLen - m_wsInBuf.length())) {
		return false;
	}

	if (m_wsInBuf.length() < packetLen) {
		return true;
	}

	const char *pBuf = m_wsInBuf.data();
	const char *pMasks = pBuf + (m_wsHeadLen - 4);
	const char *pData = pBuf + m_wsHeadLen;
	for (uint64_t i = 0; i < m_wsBodyLen; ++i) {
		char c = pData[i] ^ pMasks[i % 4];
		m_recvBuf.append(&c, 1);
	}
	m_wsInBuf.erase(0, m_wsHeadLen + m_wsBodyLen);
	m_wsDataLen = 0;
	m_wsHeadLen = 0;
	m_wsBodyLen = 0;
	return true;
}

bool ClientAsync::recvWsBuffer(int len) {
	if (len < 0 || len > 0xFFFF) {
		len = 0xFFFF;
	}
	char * buf = (char*) malloc(len);
	if (buf == NULL) {
		error_log("malloc error [%s:%d] fd=%d needLen=%d", m_peerAddr, m_peerPort, netfd, len);
		return false;
	}
	int recvLen = recv(netfd, buf, len, 0);
	if (recvLen > 0) {
		m_wsInBuf.append(buf, recvLen);
	}
	free(buf);

	if (recvLen == 0) {
		error_log("peer disconnect fd=%d", netfd);
		return false;
	} else if (recvLen < 0) {
		if (errno == EAGAIN) {
			return true;
		}
		error_log("errno=%d", errno);
		return false;
	}
	return true;
}

void ClientAsync::onWsError(int ret) {
	errorProcess(ret);
}

void ClientAsync::onHttpHead() {
	m_isHttp = true;
	const char *str = "HTTP/1.1 200 OK\r\nConnection: close\r\nContent-Length: 0\r\nContent-Type:text/html\r\n\r\n";
	sendData(str);
}
