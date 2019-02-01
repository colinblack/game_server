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

#include <client_async.h>
#include <poll_thread.h>
#include "utils.h"
#include "BattleManager.h"
#include "ClientManager.h"
#include "crc_16.h"

#define CLOSE(fd) {if(fd != 0) close(fd);fd=0;}

#define MAX_BUFF_SIZE 2048000
#define TGW_STR "tgw_l7_forward"

#define htonll(x) ((1==htonl(1)) ? (x) : (((uint64_t)htonl((x) & 0xFFFFFFFFUL)) << 32) | htonl((uint32_t)((x) >> 32)))
#define ntohll(x) ((1==ntohl(1)) ? (x) : (((uint64_t)ntohl((x) & 0xFFFFFFFFUL)) << 32) | ntohl((uint32_t)((x) >> 32)))

CClientAsync::CClientAsync(CPollThread *o, int fd)
{
	ownerUnit = o;
	netfd = fd;

	memset(m_peerAddr,0,sizeof(m_peerAddr));
	Utils::fdinfo(netfd, m_peerAddr,m_peerIp, m_peerPort);

	uint32_t now = GET_MSEC();
	m_time = now / 1000;
	m_microTime = now % 1000;

	m_clientKey = 0;
	m_selfKey = 0;

	m_spanId = 0;
	m_srvId = 0;
	m_lastSeq = 0;

	m_stat = CONN_JUDGE;
	m_bodyLen = 0;
	m_bWebSocket = false;
	memset(m_mask,0,sizeof(m_mask));
	m_skip = 0;
	m_l = 0;

	ClientManager::getInstance()->addClient(this);
}

int CClientAsync::Attach()
{	
	EnableInput();
	
	if(AttachPoller())
	{
		return -1;
	}

	return 0;
	
}

CClientAsync::~CClientAsync ()
{    
	ClientManager::getInstance()->removeClient(this);
}


void CClientAsync::InputNotify (void)
{
	switch(m_stat){
	case CONN_JUDGE:
		judgeProcess();
		break;
	case CONN_START:
		startProcess();
		break;
	case CONN_VERFY:
		verifyProcess();
		break;
	case CONN_FIRST:
	case CONN_TRANS:
		recvProcess();
		break;
	}
}

void CClientAsync::HangupNotify(void)
{
	errorProcess(SRC_HANGUP);
}

void CClientAsync::OutputNotify (void)
{
	int sendLen = send(netfd,m_outBuf.c_str(),m_outBuf.length(),0);
	if(0 > sendLen){
		{
			LOG_ERROR("errno=%u EAGIN addr [%s:%d],buflen=%u %m",errno,m_peerAddr,m_peerPort,m_outBuf.length());
			return;
		}
		errorProcess(SRC_OUTPUT);
		return;
	}

	m_outBuf.erase(0,sendLen);
	if(m_outBuf.length() == 0){
		DisableOutput();
		ApplyEvents();
	}
}

int CClientAsync::errorProcess(int src){
	onClientClose();

	LOG_ERROR("error occured [%s:%d],seq=%u,src=%d,errno=%u,%m",m_peerAddr,m_peerPort,m_lastSeq,src,errno);

	DetachPoller();

	delete this;
	return 0;
}


bool CClientAsync::sendData(const string& data, bool en){

	if(m_outBuf.length() > MAX_BUFF_SIZE){
		LOG_ERROR("buf too long,[%s:%d],close it netfd=%u",m_peerAddr,m_peerPort,netfd);
		//LOG_ERROR("%s",Utils::b2s(data.c_str(),sizeof(ClientHead)).c_str());
		errorProcess(101);
		return false;
	}

	if(m_stat != CONN_TRANS){
		EnableOutput();
		ApplyEvents();
		m_outBuf.append(data);
		return true;
	}
	//加密处理
	if(en)
	{
		static CrcUtil* pUtil = CrcUtil::getInstance();
		ClientHead* pHead = (ClientHead*)(data.c_str());
		if(data.length() != pHead->bodyLen + sizeof(ClientHead)){
			LOG_ERROR("invalid length,impossible!");
			return false;
		}
		pHead->crc2 = pUtil->update(data.c_str()+sizeof(ClientHead),pHead->bodyLen);
		pUtil->enCrypt(const_cast<char*>(data.c_str()+sizeof(ClientHead)),pHead->bodyLen,m_selfKey);
		pHead->crc1 = pUtil->update(data.c_str()+sizeof(ClientHead),pHead->bodyLen);
	}
	EnableOutput();
	ApplyEvents();

	if(m_bWebSocket){
		m_outBuf.append(1, char(0x82));
		uint32_t len = data.length();
		if(len < 126)
			m_outBuf.append(1, char(len));
		else if(len <= 65535){
			m_outBuf.append(1, char(126));
			uint16_t l = len;
			l = htons(l);
			m_outBuf.append((char*)&l, 2);
		}else{
			m_outBuf.append(1, char(127));
			uint64_t l = len;
			l = htonll(l);
			m_outBuf.append((char*)&l, 8);
		}
	}
	m_outBuf.append(data);
	return true;
}

void CClientAsync::judgeProcess()
{
	char buf[1024] = {0};
	int len = recv(netfd,buf,sizeof(buf)-1,0);

	if(len <= 0){
		errorProcess(SRC_INPUT);
		return;
	}

	if(strstr(buf, "GET ") != buf)//normal tcp
		keyProcess(buf);
	else{//websocket shake hand
		string k(buf), b("Sec-WebSocket-Key:"), e("\r");
		if(k.find(b) == string::npos){
			LOG_ERROR("[%s:%d]WebSocket key error",m_peerAddr,m_peerPort);
			errorProcess(SRC_INPUT);
			return;
		}
		k = k.substr(k.find(b) + b.length());
		if(k.find(e) == string::npos){
			LOG_ERROR("[%s:%d]WebSocket value error",m_peerAddr,m_peerPort);
			errorProcess(SRC_INPUT);
			return;
		}
		k = k.substr(0, k.find(e));
		while(k.find(" ") != string::npos)
			k.erase(k.find(" "), 1);
		string magic = k + "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";
		string sha = Crypt::Sha1Raw(magic);
		string rkey;
		Crypt::Base64Encode(rkey, sha);

		string res = "HTTP/1.1 101 Switching Protocols\r\n";
		res.append("Upgrade: websocket\r\n");
		res.append("Connection: upgrade\r\n");
		res.append("Sec-WebSocket-Accept: ");
		res.append(rkey);
		res.append("\r\n\r\n");

		sendData(res);

		m_bWebSocket = true;
		m_stat = CONN_START;

		LOG_INFO("[%s:%d] in:%s, out:%s",m_peerAddr,m_peerPort,k.c_str(),rkey.c_str());
	}
}

int CClientAsync::parseWebSocket(char* buf, int len){
	if(!m_bWebSocket)
		return 0;

	if((buf[0] & 0x80) != 0x80)
	{
		LOG_ERROR("[%s:%d]WebSocket fin error, buf=%x, fd=%d", m_peerAddr, m_peerPort,(unsigned)buf[0],netfd);
		return -1;
	}
	if((buf[0] & 0x0F) != 0x02)
	{
		LOG_ERROR("[%s:%d]WebSocket opcode error, buf=%x, fd=%d", m_peerAddr, m_peerPort,(unsigned)buf[0],netfd);
		return -2;
	}
	if((buf[1] & 0x80) != 0x80)
	{
		LOG_ERROR("[%s:%d]WebSocket mask error, buf=%x, fd=%d",m_peerAddr,m_peerPort,(unsigned)buf[1],netfd);
		return -3;
	}

	int skip, l;
	char mask[4];
	char c = buf[1] & 0x7F;
	if(c == 126){
		skip = 8;
		l = ntohs(*(uint16_t*)(buf + 2));
		memcpy(mask, buf + 4, 4);
	}
	else if(c == 127){
		skip = 14;
		l = ntohll(*(uint64_t*)(buf + 2));
		memcpy(mask, buf + 10, 4);
	}
	else{
		skip = 6;
		l = c;
		memcpy(mask, buf + 2, 4);
	}
	if(l + skip != len)
	{
		LOG_ERROR("[%s:%d]WebSocket len=%d, l=%d error, fd=%d",m_peerAddr,m_peerPort,len,l,netfd);
		return -4;
	}

	for(int i=0;i<l;++i)
		buf[i + skip] = buf[i + skip] ^ mask[i % 4];

	return skip;
}

void CClientAsync::startProcess(){
	char buf[1024] = {0};
	int len = recv(netfd,buf,sizeof(buf)-1,0);

	if(len <= 0){
		errorProcess(SRC_INPUT);
		return;
	}

	int c = parseWebSocket(buf, len);
	if(c < 0){
		errorProcess(SRC_INPUT);
		return;
	}

	keyProcess(buf + c);
}

void CClientAsync::keyProcess(char *buf)
{
	if(strstr(buf,TGW_STR) != buf){
		m_clientKey = *((uint32_t*)buf);
	}
	else{
		char* p = strstr(buf,"\r\n\r\n");
		if(p == NULL){
			LOG_ERROR("invalid start [%s:%d]",m_peerAddr,m_peerPort);
			errorProcess(SRC_INPUT);
			return;
		}

		m_clientKey = *((uint32_t*)(p+4));
	}

	m_selfKey = rand();
	string sendBuf;
	if(m_bWebSocket){
		sendBuf.append(1, char(0x82));
		sendBuf.append(1, char(0x04));
	}
	sendBuf.append((char*)&m_selfKey,4);
	sendData(sendBuf);

	m_stat = CONN_VERFY;

	LOG_INFO("[%s:%d] ck=%u,sk=%u",m_peerAddr,m_peerPort,m_clientKey,m_selfKey);
}

void CClientAsync::verifyProcess(){
	char buf[1024] = {0};
	int len = recv(netfd,buf,sizeof(buf)-1,0);

	if(len <= 0){
		LOG_ERROR("verify failed %m");
		errorProcess(SRC_INPUT);
		return;
	}

	int c = parseWebSocket(buf, len);
	if(c < 0){
		errorProcess(SRC_INPUT);
		return;
	}

	uint16_t checkKey = *((uint16_t*)(buf + c));
	uint32_t rltVal = (m_clientKey ^ m_selfKey) + MAGIC_ADDER;

	if(checkKey != CrcUtil::getInstance()->update((char*)&rltVal,4)){
		LOG_ERROR("invalid check key [%u %u]",checkKey,CrcUtil::getInstance()->update((char*)&rltVal,4));
		errorProcess(SRC_INPUT);
		return;
	}

	m_stat = CONN_FIRST;

	LOG_INFO("[%s:%d] connect ok,fd=%d",m_peerAddr,m_peerPort,netfd);
}

void CClientAsync::recvProcess(){
	if(m_bWebSocket)
		recvProcessWebSocket();
	else
		recvProcessRaw();
}
void CClientAsync::recvProcessRaw(){
	char buf[4096];
	if(m_inBuf.length() < sizeof(ClientHead)){
		int len = recv(netfd,buf,sizeof(ClientHead)-m_inBuf.length(),0);
		if(len == 0){
			LOG_ERROR("peer close [%s:%d] fd=%d",m_peerAddr,m_peerPort,netfd);
			errorProcess(SRC_INPUT);
			return;
		}
		else if(len < 0){
			errorProcess(SRC_INPUT);
			return;
		}

		m_inBuf.append(buf,len);

		if(m_inBuf.length() != sizeof(ClientHead)){
			LOG_ERROR("expect recv %u but only recv %u",sizeof(ClientHead),len);
			return;
		}

		if(((ClientHead*)m_inBuf.c_str())->head != MAGIC_HEADER){
			LOG_ERROR("invalid magic head");
			errorProcess(SRC_INPUT);
			return;
		}
		m_bodyLen = ((ClientHead*)m_inBuf.c_str())->bodyLen;
		if(m_bodyLen < 4){
			LOG_ERROR("invalid body len [%s:%u] len=%u",m_peerAddr,m_peerPort);
			errorProcess(SRC_INPUT);
			return ;
		}
	}
	else{
		int leftLen = m_bodyLen + sizeof(ClientHead) - m_inBuf.length();
		int expectLen = leftLen > sizeof(buf) ? sizeof(buf) : leftLen;
		int len = recv(netfd,buf,expectLen,0);
		if(len == 0){
			LOG_ERROR("peer close [%s:%d]",m_peerAddr,m_peerPort);
			errorProcess(SRC_INPUT);
			return;
		}
		else if(len < 0){
			errorProcess(SRC_INPUT);
			return;
		}

		m_inBuf.append(buf,len);

		if(m_inBuf.length() == m_bodyLen + sizeof(ClientHead)){
			static CrcUtil* pUtils = CrcUtil::getInstance();

			//crc校验
			ClientHead* pHead = (ClientHead*)(m_inBuf.c_str());

			if(pHead->crc2 != pUtils->update(m_inBuf.c_str()+sizeof(ClientHead),m_bodyLen)){
				LOG_ERROR("[%s:%u] raw crc check failed",m_peerAddr,m_peerPort);
				errorProcess(SRC_INPUT);
				return;
			}
			pUtils->deCrypt(const_cast<char*>(m_inBuf.c_str()+sizeof(ClientHead)),m_bodyLen,m_clientKey);
			if(pHead->crc1 != pUtils->update(m_inBuf.c_str()+sizeof(ClientHead),m_bodyLen)){
				LOG_ERROR("[%s:%u] decrypt crc check failed",m_peerAddr,m_peerPort);
				errorProcess(SRC_INPUT);
				return;
			}

			if(m_stat == CONN_FIRST){
				firstProcess();
			}
			else{
				if(!packetProcess()){
					return;
				}
			}
			m_inBuf.clear();
			m_bodyLen = 0;
			return;
		}

		if(m_inBuf.length() > m_bodyLen + sizeof(ClientHead)){
			LOG_ERROR("invalid packet,len=%u",m_inBuf.length());
			errorProcess(SRC_INPUT);
			return;
		}
	}
}
void CClientAsync::recvProcessWebSocket(){
	char buf[4096];
	if(m_inBuf.length() < 14){
		int len = recv(netfd,buf,14-m_inBuf.length(),0);
		if(len == 0){
			LOG_ERROR("peer close [%s:%d] fd=%d",m_peerAddr,m_peerPort,netfd);
			errorProcess(SRC_INPUT);
			return;
		}
		else if(len < 0){
			errorProcess(SRC_INPUT);
			return;
		}

		m_inBuf.append(buf,len);

		if(m_inBuf.length() != 14){
			if((m_inBuf.c_str()[0] & 0x0F) == 0x08)
			{
				LOG_ERROR("WebSocket close [%s:%d] fd=%d",m_peerAddr,m_peerPort,netfd);
				errorProcess(SRC_INPUT);
				return;
			}
			LOG_ERROR("expect recv %u but only recv %u",14,len);
			return;
		}

		const char *b = m_inBuf.c_str();
		if((b[0] & 0x80) != 0x80)
		{
			LOG_ERROR("[%s:%d]WebSocket fin error, buf=%x, fd=%d", m_peerAddr, m_peerPort,(unsigned)b[0],netfd);
			errorProcess(SRC_INPUT);
			return;
		}
		if((b[0] & 0x0F) != 0x02)
		{
			LOG_ERROR("[%s:%d]WebSocket opcode error, buf=%x, fd=%d", m_peerAddr, m_peerPort,(unsigned)b[0],netfd);
			errorProcess(SRC_INPUT);
			return;
		}
		if((b[1] & 0x80) != 0x80)
		{
			LOG_ERROR("[%s:%d]WebSocket mask error, buf=%x, fd=%d",m_peerAddr,m_peerPort,(unsigned)b[1],netfd);
			errorProcess(SRC_INPUT);
			return;
		}

		char c = b[1] & 0x7F;
		if(c == 126){
			m_skip = 8;
			m_l = ntohs(*(uint16_t*)(b + 2));
			memcpy(m_mask, b + 4, 4);
		}
		else if(c == 127){
			m_skip = 14;
			m_l = ntohll(*(uint64_t*)(b + 2));
			memcpy(m_mask, b + 10, 4);
		}
		else{
			m_skip = 6;
			m_l = c;
			memcpy(m_mask, b + 2, 4);
		}
	}
	else{
		int leftLen = m_l + m_skip - m_inBuf.length();
		int expectLen = leftLen > sizeof(buf) ? sizeof(buf) : leftLen;
		int len = recv(netfd,buf,expectLen,0);
		if(len == 0){
			LOG_ERROR("peer close [%s:%d]",m_peerAddr,m_peerPort);
			errorProcess(SRC_INPUT);
			return;
		}
		else if(len < 0){
			errorProcess(SRC_INPUT);
			return;
		}

		m_inBuf.append(buf,len);

		if(m_inBuf.length() == m_l + m_skip){
			char *b = const_cast<char*>(m_inBuf.c_str());
			for(int i=0;i<m_l;++i)
				b[i + m_skip] = b[i + m_skip] ^ m_mask[i % 4];

			if(((ClientHead*)(m_inBuf.c_str()+m_skip))->head != MAGIC_HEADER){
				LOG_ERROR("invalid magic head");
				errorProcess(SRC_INPUT);
				return;
			}
			m_bodyLen = ((ClientHead*)(m_inBuf.c_str()+m_skip))->bodyLen;
			if(m_bodyLen < 4 || m_bodyLen + sizeof(ClientHead) != m_l){
				LOG_ERROR("invalid body len [%s:%u] len=%u",m_peerAddr,m_peerPort);
				errorProcess(SRC_INPUT);
				return ;
			}

			static CrcUtil* pUtils = CrcUtil::getInstance();

			//crc校验
			ClientHead* pHead = (ClientHead*)(m_inBuf.c_str()+m_skip);

			if(pHead->crc2 != pUtils->update(m_inBuf.c_str()+m_skip+sizeof(ClientHead),m_bodyLen)){
				LOG_ERROR("[%s:%u] raw crc check failed",m_peerAddr,m_peerPort);
				errorProcess(SRC_INPUT);
				return;
			}
			pUtils->deCrypt(const_cast<char*>(m_inBuf.c_str()+m_skip+sizeof(ClientHead)),m_bodyLen,m_clientKey);
			if(pHead->crc1 != pUtils->update(m_inBuf.c_str()+m_skip+sizeof(ClientHead),m_bodyLen)){
				LOG_ERROR("[%s:%u] decrypt crc check failed",m_peerAddr,m_peerPort);
				errorProcess(SRC_INPUT);
				return;
			}

			if(m_stat == CONN_FIRST){
				firstProcess();
			}
			else{
				if(!packetProcess()){
					return;
				}
			}
			m_inBuf.clear();
			m_bodyLen = 0;
			memset(m_mask,0,sizeof(m_mask));
			m_skip = 0;
			m_l = 0;
			return;
		}

		if(m_inBuf.length() > m_l + m_skip){
			LOG_ERROR("invalid packet,len=%u",m_inBuf.length());
			errorProcess(SRC_INPUT);
			return;
		}
	}
}

bool CClientAsync::firstProcess(){

	//LOG_DEBUG(Utils::b2s(m_inBuf.c_str(),m_inBuf.length()).c_str());

	m_spanId = *((int*)(m_inBuf.c_str()+m_inBuf.length()-8));
	m_srvId = *((int*)(m_inBuf.c_str()+m_inBuf.length()-4));
	m_lastSeq = *((uint32_t*)(m_inBuf.c_str()+m_skip+sizeof(ClientHead)));

	string packet;
	string body(m_inBuf.begin()+m_skip+sizeof(ClientHead)+4,m_inBuf.end());
	packetFormat(body,packet);

	BattleManager::getInstance()->sendData(m_spanId,m_srvId,packet);

	LOG_INFO("[%s:%d] login [%u:%u],start seq %u",m_peerAddr,m_peerPort,m_spanId,m_srvId,m_lastSeq);
	m_stat = CONN_TRANS;

	return true;
}

bool CClientAsync::packetProcess(){

	uint32_t curSeq = *((uint32_t*)(m_inBuf.c_str()+m_skip+sizeof(ClientHead)));
	if(curSeq <= m_lastSeq){
		LOG_ERROR("[%s:%d] seq error [%u:%u]",m_peerAddr,m_peerPort,curSeq,m_lastSeq);

		errorProcess(SRC_INPUT);
		return false;
	}

	m_lastSeq = curSeq;

	string packet;
	string body(m_inBuf.begin()+m_skip+sizeof(ClientHead)+4,m_inBuf.end());
	packetFormat(body,packet);

	if(!BattleManager::getInstance()->sendData(m_spanId,m_srvId,packet)){
		LOG_ERROR("may be srv [%u_%u] disconnect",m_spanId,m_srvId);
		errorProcess(SRC_OUTPUT);
		return false;
	}

	return true;
}

bool CClientAsync::packetFormat(const string& in,string& out){
	BattleHead battleHead;

	battleHead.head = MAGIC_HEADER;
	battleHead.bodyLen = m_bodyLen - 4;
	battleHead.cmd = PROTOCOL_ACCESS_TRANSFER;
	battleHead.fd = netfd;
	battleHead.time = m_time;
	battleHead.microTime = m_microTime;
	battleHead.clientIp = m_peerIp;

	out.append((char*)&battleHead,sizeof(BattleHead));
	out.append(in);


	return true;
}

bool CClientAsync::battleClose(){
	LOG_INFO("battle kick [%s:%u]",m_peerAddr,m_peerPort);
	DetachPoller();
	delete this;
	return true;
}

void CClientAsync::onClientClose(){
	BattleManager::getInstance()->clientClose(m_spanId,m_srvId,netfd,m_time,m_microTime,m_peerIp);
}
