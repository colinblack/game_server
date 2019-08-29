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

#include "client_async.h"
#include "poll_thread.h"
#include "utils.h"
#include "battle_manager.h"
#include "client_manager.h"
#include "crc_16.h"
#include "BufferReader.h"
#include "comm.h"

#define CLOSE(fd) {if(fd != 0) close(fd);fd=0;}

#define MAX_BUFF_SIZE 2048000
#define TGW_STR "tgw_l7_forward"

CClientAsync::CClientAsync(CPollThread *o, int fd) {
	ownerUnit = o;
	netfd = fd;
	m_packetInCount = 0;
	memset(m_peerAddr, 0, sizeof(m_peerAddr));
	Utils::fdinfo(netfd, m_peerAddr, m_peerIp, m_peerPort);
	uint32_t now = GET_MSEC();
	m_time = now / 1000;
	m_microTime = now % 1000;
	m_clientKey = 0;
	m_selfKey = 0;
	m_serverId = 0;
	m_lastSeq = 0;
	m_bodyLen = 0;
	m_stat = CONN_START;
	m_wsHeadLen = 0;
	m_wsBodyLen = 0;
	m_wsDataLen = 0;

	m_inBuf.clear();
	m_outBuf.clear();
	m_recvBuf.clear();
	m_openid.clear();
	m_wsInBuf.clear();
	m_isHttp = false;
	m_bWebSocket = false;

	ClientManager::getInstance()->addClient(this);
}

int CClientAsync::Attach() {
	EnableInput();

	if (AttachPoller()) {
		return -1;
	}

	return 0;
}

CClientAsync::~CClientAsync() {
	ClientManager::getInstance()->removeClient(this);
}

void CClientAsync::InputNotify(void) {
	switch (m_stat) {
	case CONN_START:
		startProcess();
		break;
	default:
		recvProcess();
		break;
	}
}

void CClientAsync::HangupNotify(void) {
	errorProcess(SRC_HANGUP);
}

void CClientAsync::OutputNotify(void) {
	int sendLen = send(netfd, m_outBuf.c_str(), m_outBuf.length(), 0);
	if (0 > sendLen) {
		{
			LOG_ERROR("errno=%u EAGIN addr [%s:%d],buflen=%u %m", errno, m_peerAddr, m_peerPort, m_outBuf.length());
			return;
		}
		errorProcess(SRC_OUTPUT);
		return;
	}
	m_outBuf.erase(0, sendLen);
	if (m_outBuf.length() == 0) {
		DisableOutput();
		ApplyEvents();
	}
}

void CClientAsync::errorProcess(int src) {
	if (!m_isHttp) {
		LOG_ERROR("error occured [%s:%d],seq=%u,src=%d,errno=%u", m_peerAddr, m_peerPort, m_lastSeq, src, errno);
	}

	DetachPoller();

	delete this;

	return;
}

bool CClientAsync::sendData(const string& data) {
	if (m_outBuf.length() > MAX_BUFF_SIZE) {
		LOG_ERROR("buf too long,[%s:%d],close it netfd=%u", m_peerAddr, m_peerPort, netfd);
		onClientClose();
		errorProcess(101);
		return false;
	}

	if (m_stat != CONN_TRANS) {
		EnableOutput();
		ApplyEvents();
		if (m_stat != CONN_CREATE_KEY) {
			onWsEncode(data, m_outBuf);
		} else {
			m_outBuf.append(data);
		}
		return true;
	}

	static CrcUtil* pUtil = CrcUtil::getInstance();

	//加密处理
	ClientHead* pHead = (ClientHead*) (data.c_str());
	if (data.length() != pHead->bodyLen + sizeof(ClientHead)) {
		LOG_ERROR("invalid length,impossible!");
		return false;
	}

	byte cmd = *((byte*) (data.c_str() + sizeof(ClientHead)));
	byte subCmd = *((byte*) (data.c_str() + sizeof(ClientHead) + 1));
	PACKET_LOG("%d_%d|%s|send|%s|%u", (int )cmd, (int )subCmd, m_peerAddr, m_openid.c_str(), m_serverId);

	pHead->crc2 = pUtil->update(data.c_str() + sizeof(ClientHead), static_cast<int>(pHead->bodyLen));
	pUtil->enCrypt(const_cast<char*>(data.c_str() + sizeof(ClientHead)), static_cast<int>(pHead->bodyLen), m_selfKey);
	pHead->crc1 = pUtil->update(data.c_str() + sizeof(ClientHead), static_cast<int>(pHead->bodyLen));

	EnableOutput();
	ApplyEvents();

	onWsEncode(data, m_outBuf);

	return true;
}

bool CClientAsync::createKeyProcess() {
	if (m_recvBuf.empty()) {
		LOG_ERROR("invalid start [%s:%d]", m_peerAddr, m_peerPort);
		return false;
	}
	if (m_recvBuf.find(TGW_STR) == string::npos) {
		m_clientKey = *((uint32_t*) m_recvBuf.c_str());
	} else {
		size_t pos = m_recvBuf.find("\r\n\r\n");
		if (pos == string::npos) {
			LOG_ERROR("invalid start [%s:%d]", m_peerAddr, m_peerPort);
			errorProcess(SRC_INPUT);
			return false;
		}
		m_clientKey = *((uint32_t*) (m_recvBuf.c_str() + pos + 4));
	}
	m_selfKey = rand();
	m_stat = CONN_VERFY_KEY;
	m_recvBuf.clear();
	string sendBuf;
	sendBuf.append((char*) &m_selfKey, 4);
	sendData(sendBuf);
	LOG_INFO("[%s:%d] fd=%d,ck=%u,sk=%u", m_peerAddr, m_peerPort, netfd, m_clientKey, m_selfKey);
	return true;
}

bool CClientAsync::verifyKeyProcess() {
	if (m_recvBuf.empty() || m_recvBuf.length() < 2) {
		LOG_ERROR("invalid check [%s:%d] fd=%d", m_peerAddr, m_peerPort, netfd);
		return false;
	}
	uint16_t checkKey = *((uint16_t*) m_recvBuf.c_str());
	uint32_t rltVal = (m_clientKey ^ m_selfKey) + MAGIC_ADDER;
	if (checkKey != CrcUtil::getInstance()->update((char*) &rltVal, 4)) {
		LOG_ERROR("invalid check key [%u %u] fd=%d", checkKey, CrcUtil::getInstance()->update((char* )&rltVal, 4), netfd);
		errorProcess(SRC_INPUT);
		return false;
	}
	m_stat = CONN_FIRST;
	m_recvBuf.erase(0, 2);
	LOG_INFO("[%s:%d] connect ok,fd=%d", m_peerAddr, m_peerPort, netfd);
	return true;
}

bool CClientAsync::statProcess() {
	bool ret = false;
	switch (m_stat) {
	case CONN_CREATE_KEY:
		ret = createKeyProcess();
		break;
	case CONN_VERFY_KEY:
		ret = verifyKeyProcess();
		break;
	case CONN_FIRST:
		ret = decodeProcess() ? firstProcess() : false;
		break;
	case CONN_TRANS:
		ret = decodeProcess() ? packetProcess() : false;
		break;
	}

	return ret;
}

void CClientAsync::recvProcess() {
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

	while (!m_recvBuf.empty()) {
		if (!statProcess()) {
			return;
		}
	}
}

bool CClientAsync::decodeProcess() {
	if (m_recvBuf.length() < sizeof(ClientHead)) {
		return false;
	}
	ClientHead *pHead = (ClientHead*) (m_recvBuf.c_str());
	if (pHead->head != MAGIC_HEADER) {
		LOG_ERROR("invalid magic head,head=%d", pHead->head);
		errorProcess(SRC_INPUT);
		return false;
	}
	m_bodyLen = pHead->bodyLen;
	if (m_bodyLen < 4) {
		LOG_ERROR("invalid body len [%s:%u] len=%u", m_peerAddr, m_peerPort, m_bodyLen);
		errorProcess(SRC_INPUT);
		return false;
	}
	uint32_t packetLen = m_bodyLen + sizeof(ClientHead);
	if (m_recvBuf.length() < packetLen) {
		return false;
	}

	m_inBuf.clear();
	m_inBuf.append(m_recvBuf.c_str(), packetLen);
	m_recvBuf.erase(0, packetLen);

	static CrcUtil* pUtils = CrcUtil::getInstance();
	pHead = (ClientHead*) (m_inBuf.c_str());
	uint16_t crc = pUtils->update(m_inBuf.c_str() + sizeof(ClientHead), m_bodyLen);
	if (pHead->crc2 != crc) {
		LOG_ERROR("[%s:%u] raw crc check failed,crc2=%u,crc=%u", m_peerAddr, m_peerPort, pHead->crc2, crc);
		errorProcess(SRC_INPUT);
		return false;
	}
	pUtils->deCrypt(const_cast<char*>(m_inBuf.c_str() + sizeof(ClientHead)), m_bodyLen, m_clientKey);
	crc = pUtils->update(m_inBuf.c_str() + sizeof(ClientHead), m_bodyLen);
	if (pHead->crc1 != crc) {
		LOG_ERROR("[%s:%u] decrypt crc check failed crc1=%u,crc=%u", m_peerAddr, m_peerPort, pHead->crc1, crc);
		errorProcess(SRC_INPUT);
		return false;
	}
	return true;
}

bool CClientAsync::firstProcess() {
	doStat();

	uint16_t strlen = *(uint16_t*) ((m_inBuf.c_str() + sizeof(ClientHead)) + 6);
	const char * pOpenId = m_inBuf.c_str() + sizeof(ClientHead) + 8;
	m_openid.append(pOpenId, strlen);
	m_serverId = *((int*) (m_inBuf.c_str() + m_inBuf.length() - 8)); //当前服
	uint32_t register_server_id = *((int*) (m_inBuf.c_str() + m_inBuf.length() - 12)); //注册服

	m_lastSeq = *((uint32_t*) (m_inBuf.c_str() + sizeof(ClientHead)));

	string packet;
	string body(m_inBuf.begin() + sizeof(ClientHead) + 4, m_inBuf.end());
	packetFormat(body, packet);

	BattleManager::getInstance()->sendData(m_serverId, packet);

	char cmd = 0;
	char subCmd = 0;
	if (body.size() >= 2) {
		cmd = *(body.data());
		subCmd = *(body.data() + 1);
	}

	m_stat = CONN_TRANS;

	PACKET_LOG("%d_%d|%s|first|%s|%u|%u|%u", (int )cmd, (int )subCmd, m_peerAddr, m_openid.c_str(), m_serverId, register_server_id, netfd);
	return true;
}

bool CClientAsync::packetProcess() {
	doStat();

	uint32_t curSeq = *((uint32_t*) (m_inBuf.c_str() + sizeof(ClientHead)));
	if (curSeq <= m_lastSeq) {
		char cmd = 0;
		char subCmd = 0;
		if (m_inBuf.size() >= sizeof(ClientHead) + 6) {
			cmd = *(m_inBuf.c_str() + sizeof(ClientHead) + 4);
			subCmd = *(m_inBuf.c_str() + sizeof(ClientHead) + 5);
		}
		LOG_ERROR("[%s:%d] seq error [%u:%u] %d_%d", m_peerAddr, m_peerPort, curSeq, m_lastSeq, (int )cmd, (int )subCmd);
		errorProcess(SRC_INPUT);
		return false;
	}

	m_lastSeq = curSeq;

	string packet;
	string body(m_inBuf.begin() + sizeof(ClientHead) + 4, m_inBuf.end());
	packetFormat(body, packet);

	if (!BattleManager::getInstance()->sendData(m_serverId, packet)) {
		LOG_ERROR("may be srv [%u] disconnect", m_serverId);
		errorProcess(SRC_OUTPUT);
		return false;
	}

	char cmd = 0;
	char subCmd = 0;
	if (body.size() >= 2) {
		cmd = *(body.data());
		subCmd = *(body.data() + 1);
	}

	PACKET_LOG("%d_%d|%s|recv|%s|%u", (int )((byte )cmd), (int )((byte )subCmd), m_peerAddr, m_openid.c_str(), m_serverId);
	return true;
}

void CClientAsync::startProcess() {
	char buf[1024] = { 0 };
	int len = recv(netfd, buf, sizeof(buf) - 1, 0);
	if (len <= 0) {
		errorProcess(SRC_INPUT);
		return;
	}
	if (strstr(buf, "GET ") != buf) {
		m_recvBuf.append(buf, len);
		createKeyProcess();
	} else {
		char *str = strstr(buf, "Sec-WebSocket-Key");
		if (str == NULL) {
			onHttpHead();
			return;
		}
		char *str1 = strstr(str, ":");
		if (str1 == NULL) {
			LOG_ERROR("key not exists [%s:%d] fd=%d buf=%s", m_peerAddr, m_peerPort, netfd, buf);
			errorProcess(SRC_INPUT);
			return;
		}
		char *str2 = strstr(str1, "\r\n");
		if (str2 == NULL) {
			LOG_ERROR("key not exists [%s:%d] fd=%d buf=%s", m_peerAddr, m_peerPort, netfd, buf);
			errorProcess(SRC_INPUT);
			return;
		}
		string key;
		key.append(str1 + 2, str2);
		string acceptKey;
		if (!Crypt::Base64Encode(acceptKey, Crypt::Sha1Raw(key + "258EAFA5-E914-47DA-95CA-C5AB0DC85B11"))) {
			LOG_ERROR("Base64Encode error [%s:%d] fd=%d acceptKey=%s", m_peerAddr, m_peerPort, netfd, acceptKey.c_str());
			errorProcess(SRC_INPUT);
			return;
		}

		string upgrade = "HTTP/1.1 101 Switching Protocols\r\n";
		upgrade += "Upgrade: websocket\r\n";
		upgrade += "Connection: Upgrade\r\n";
		upgrade += "Sec-WebSocket-Accept: " + acceptKey + "\r\n";
		upgrade += "\r\n";

		m_stat = CONN_CREATE_KEY;
		m_bWebSocket = true;
		sendData(upgrade);

		LOG_INFO("key=%s,acceptKey=%s,fd=%d", key.c_str(), acceptKey.c_str(), netfd);
	}
	LOG_DEBUG("fd=%d,ws=%d", netfd, m_bWebSocket);
	return;
}

void CClientAsync::onWsEncode(const string &data, string &result) {
	if (!m_bWebSocket) {
		result.append(data);
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
		result.append((char*) &len, 2);
	} else {
		payload_len = 0x7F;
		result.append(&payload_len, 1);
		uint64_t len = data_len;
		len = hton64(len);
		result.append((char*) &len, 8);
	}
	result.append(data);
	return;
}

bool CClientAsync::packetFormat(const string& in, string& out) {
	char cmd = 0;
	if (in.size() > 0) {
		cmd = *(in.c_str());
	}

	BattleHead battleHead;

	battleHead.head = MAGIC_HEADER;
	battleHead.bodyLen = m_bodyLen - 4;
	if (cmd == PROTOCOL_CMD_ADMIN) {
		battleHead.cmd = PROTOCOL_TYPE_ACCESS_ADMIN;
	} else {
		battleHead.cmd = PROTOCOL_ACCESS_TRANSFER;
	}
	battleHead.fd = netfd;
	battleHead.time = m_time;
	battleHead.microTime = m_microTime;
	battleHead.clientIp = m_peerIp;

	out.append((char*) &battleHead, sizeof(BattleHead));
	out.append(in);

	return true;
}

void CClientAsync::doStat() {
	++m_packetInCount;
	if (m_packetInCount % 1000000 == 0) {
		info_log("access_packet_info m_packetInCount=%llu", m_packetInCount);
	}
}
bool CClientAsync::battleClose() {
	LOG_INFO("battle kick [%s:%u]", m_peerAddr, m_peerPort);

	errorProcess(100);

	return true;
}

void CClientAsync::onClientClose() {
	if (m_stat != CONN_TRANS) {
		return;
	}
	BattleManager::getInstance()->clientClose(m_serverId, netfd, m_time, m_microTime, m_peerIp);
}

bool CClientAsync::getWsHeadLen() {
	if (m_wsHeadLen != 0) {
		return true;
	}
	if (m_wsInBuf.length() < WS_HEAD_FLAG && !recvWsBuffer(WS_HEAD_FLAG - m_wsInBuf.length())) {
		LOG_ERROR("recvWsBuffer error len=%u", m_wsInBuf.length());
		return false;
	}
	if (m_wsInBuf.length() < WS_HEAD_FLAG) {
		return true;
	}

	const char* pBuf = m_wsInBuf.data();
	uint8_t fin = pBuf[0] & 0x80;
	if (fin != 0x80) {
		LOG_ERROR("fin error [%s:%d] fd=%d fin=%d", m_peerAddr, m_peerPort, netfd, (int )fin);
	}
	uint8_t opcode = pBuf[0] & 0xF;
	if (opcode != 0x2) {
		LOG_ERROR("opcode error [%s:%d] fd=%d opcode=%d", m_peerAddr, m_peerPort, netfd, (int )opcode);
		return false;
	}
	uint8_t mask = pBuf[1] & 0x80;
	if (mask != 0x80) {
		LOG_ERROR("mask error [%s:%d] fd=%d mask=%d", m_peerAddr, m_peerPort, netfd, (int )mask);
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

bool CClientAsync::getWsBodyLen() {
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
		LOG_ERROR("body len error [%s:%d] fd=%d", m_peerAddr, m_peerPort, netfd);
		return false;
	}
	return true;
}

bool CClientAsync::getWsBodyData() {
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
	LOG_INFO("fd=%d m_wsHeadLen=%u,m_wsBodyLen=%u", netfd, m_wsHeadLen, m_wsBodyLen);
	m_wsInBuf.erase(0, m_wsHeadLen + m_wsBodyLen);
	m_wsDataLen = 0;
	m_wsHeadLen = 0;
	m_wsBodyLen = 0;
	return true;
}

bool CClientAsync::recvWsBuffer(int len) {
	if (len < 0 || len > 0xFFFF) {
		len = 0xFFFF;
	}
	char * buf = (char*) malloc(len);
	if (buf == NULL) {
		LOG_ERROR("malloc error [%s:%d] fd=%d needLen=%d", m_peerAddr, m_peerPort, netfd, len);
		return false;
	}
	int recvLen = recv(netfd, buf, len, 0);
	if (recvLen > 0) {
		m_wsInBuf.append(buf, recvLen);
	}
	free(buf);

	if (recvLen == 0) {
		LOG_ERROR("peer disconnect fd=%d", netfd);
		return false;
	} else if (recvLen < 0) {
		if (errno == EAGAIN) {
			return true;
		}
		return false;
	}
	return true;
}

void CClientAsync::onWsError(int ret) {
	onClientClose();
	errorProcess(ret);
}

void CClientAsync::onHttpHead() {
	m_isHttp = true;
	const char *str = "HTTP/1.1 200 OK\r\nConnection: close\r\nContent-Length: 0\r\nContent-Type:text/html\r\n\r\n";
	sendData(str);
}

