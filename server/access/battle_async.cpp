#include "battle_async.h"
#include "ClientManager.h"
#include <sys/un.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "BattleManager.h"
#include "crc_16.h"

#define CLOSE(fd) {if(fd != 0) close(fd);fd=0;}
#define MAX_BUFF_LEN 10240000

CBattleAsync::CBattleAsync(CPollThread *o, uint32_t spanId, uint32_t srvId){
	ownerUnit = o;

	m_spanId = spanId;
	m_srvId = srvId;
	//strncpy(m_addr,addr,sizeof(m_addr)-1);
	//m_port = port;
	m_isConnected = false;
	m_stat = IDLE;
	m_bodyLen = 0;

	init();
}

CBattleAsync::~CBattleAsync ()
{

}

int CBattleAsync::init(){

	if(!parseAddress()){
		LOG_ERROR("parse address failed");
		return -1;
	}

	struct sockaddr_in inaddr;
	int fd,flags,n;

	if((fd = socket (AF_INET, SOCK_STREAM, 0)) == -1)
	{
		LOG_ERROR("make tcp socket error, %m");
		return -1;
	}

	netfd = fd;
	LOG_DEBUG("get socket %d",netfd);

	bzero (&inaddr, sizeof (struct sockaddr_in));
	inaddr.sin_family = AF_INET;
	inaddr.sin_port = htons (m_port);

	if(inet_pton(AF_INET, m_addr, &inaddr.sin_addr) <= 0){
		LOG_EMERG("invalid address:[%s %d]",m_addr,m_port);
		return -1;
	}

	//set the socket to nonblock
	flags = fcntl(fd,F_GETFL,0);
	fcntl(fd,F_SETFL,flags | O_NONBLOCK);

	if((n = connect(fd,(const struct sockaddr *)&inaddr,sizeof(inaddr)))  < 0){
		if(errno != EINPROGRESS){
			LOG_ERROR("connect failed,errno:%d %s",errno,strerror(errno));
			return -1;
		}

		LOG_INFO("wait to connected");

		m_stat = CONNECTING;

		EnableInput();
		EnableOutput();

		if(AttachPoller() != 0){
			LOG_ERROR("AttachPoller failed");
		}
	}

	if(n == 0){
		LOG_INFO("connect to [%s:%d] success immediately",m_addr,m_port);
		m_stat = CONNECTED;
		if(Attach() != 0){
			LOG_ERROR("AttachPoller failed");
		}
		onConnected();
	}

	return 0;
}

int CBattleAsync::Attach()
{
	EnableInput();

	if(AttachPoller())
	{
		return -1;
	}

	return 0;
}

int CBattleAsync::connectingProcess(int src){
	if(src == SRC_INPUT || src == SRC_OUTPUT)
	{
		int error;
		socklen_t len = sizeof(error);

		if(getsockopt(netfd,SOL_SOCKET,SO_ERROR,&error,&len) < 0){
			LOG_ERROR("connected to [%s:%d] failed, %s",m_addr,m_port,strerror(errno));

			m_stat = IDLE;
			DetachPoller();
			CLOSE(netfd);
			return -1;
		}

		if(error){
			LOG_ERROR("connected to [%s:%d] failed,%s",m_addr,m_port,strerror(error));

			m_stat = IDLE;

			DetachPoller();
			CLOSE(netfd);
			return - 1;
		}

		m_stat = CONNECTED;

		LOG_INFO("connect to [%s:%d] success",m_addr,m_port);

		EnableOutput();
		EnableInput();
		ApplyEvents();
		onConnected();
	}
	else if(src == SRC_HANGUP) //some error occured
	{
		int error;
		socklen_t len = sizeof(error);

		if(getsockopt(netfd,SOL_SOCKET,SO_ERROR,&error,&len) < 0){
			LOG_ERROR("connected to [%s:%d] failed",m_addr,m_port);
		}
		else if(error){
			LOG_ERROR("connected to [%s:%d] failed",m_addr,m_port);
		}

		m_stat = IDLE;
		DetachPoller();
		CLOSE(netfd);
	}

	return 0;
}

bool CBattleAsync::sendData(const string& data){

	if(m_outBuf.length() > MAX_BUFF_LEN){
		LOG_ERROR("buff too long [%s:%d]",m_addr,m_port);
		return false;
	}

	if(m_stat == CONNECTED){
		EnableOutput();
		ApplyEvents();

		m_outBuf.append(data);
		return true;
	}
	else if(m_stat == CONNECTING)
	{
		m_outBuf.append(data);
	}
	else if(m_stat == IDLE){
		init();
		m_outBuf = data;
	}

	return false;
}


void CBattleAsync::OutputNotify (void){
	if(m_stat == CONNECTING){
		if(connectingProcess(SRC_OUTPUT) != 0)
			return;
	}

	int sendLen = send(netfd,m_outBuf.c_str(),m_outBuf.length(),0);
	if(0 > sendLen){
		errorProcess(SRC_OUTPUT);
		return;
	}

	m_outBuf.erase(0,sendLen);
	if(m_outBuf.length() == 0){
		DisableOutput();
		ApplyEvents();
	}
}

void CBattleAsync::InputNotify (void){
	if(m_stat == CONNECTING){
		if(connectingProcess(SRC_INPUT) != 0)
			return;
	}

	recvProcess();
}

void CBattleAsync::HangupNotify (void){
	errorProcess(SRC_HANGUP);
}

int CBattleAsync::errorProcess(int src){
	LOG_ERROR("error occured [%s:%d],src=%d",m_addr,m_port,src);

	m_stat = IDLE;
	DetachPoller();
	CLOSE(netfd);

	return 0;
}

void CBattleAsync::recvProcess(){
	char buf[4096];

	if(m_inBuf.length() < sizeof(BattleHead)){
		int len = recv(netfd,buf,sizeof(BattleHead)-m_inBuf.length(),0);
		if(len == 0){
			LOG_ERROR("peer close [%s:%d]",m_addr,m_port);
			errorProcess(SRC_INPUT);
			return;
		}
		else if(len < 0){
			errorProcess(SRC_INPUT);
			return;
		}

		m_inBuf.append(buf,len);

		if(m_inBuf.length() != sizeof(BattleHead)){
			//LOG_ERROR("expect recv %u but only recv %u",sizeof(BattleHead),len);
			return;
		}


		if(((BattleHead*)m_inBuf.c_str())->head != MAGIC_HEADER){
			LOG_ERROR("invalid magic head");
			errorProcess(SRC_INPUT);
		}
		m_bodyLen = ((BattleHead*)m_inBuf.c_str())->bodyLen;
		if(m_bodyLen == 0){
			packetProcess();
			m_inBuf.clear();
			m_bodyLen = 0;
		}
	}
	else{
		int leftLen = m_bodyLen + sizeof(BattleHead) - m_inBuf.length();
		int expectLen = leftLen > sizeof(buf) ? sizeof(buf) : leftLen;
		int len = recv(netfd,buf,expectLen,0);
		if(len == 0){
			LOG_ERROR("peer close [%s:%d]",m_addr,m_port);
			errorProcess(SRC_INPUT);
			return;
		}
		else if(len < 0){
			errorProcess(SRC_INPUT);
			return;
		}

		m_inBuf.append(buf,len);

		if(m_inBuf.length() == m_bodyLen + sizeof(BattleHead)){
			packetProcess();
			m_inBuf.clear();
			m_bodyLen = 0;
			return;
		}

		if(m_inBuf.length() > m_bodyLen + sizeof(BattleHead)){
			LOG_ERROR("invalid packet,len=%u",m_inBuf.length());
			errorProcess(SRC_INPUT);
			return;
		}
	}
}

void CBattleAsync::packetProcess(){
	static ClientManager* pClient = ClientManager::getInstance();

	BattleHead* pHead = (BattleHead*)m_inBuf.c_str();
	uint32_t fd = pHead->fd;
	uint32_t time = pHead->time;
	uint32_t microTime = pHead->microTime;

	//服务端踢下线
	if(pHead->cmd == PROTOCOL_ACCESS_LOFFLINE){
		pClient->battleClose(fd);
		return;
	}

/*
	// 修改登录服务器
	if(pHead->cmd == PROTOCOL_ACCESS_CHANGE_LOGIN || pHead->cmd == PROTOCOL_ACCESS_KICK_CROSS)
	{
		uint16_t cmd = pHead->cmd;
		pHead->cmd = PROTOCOL_ACCESS_CHANGE_LOGIN;
		uint32_t srvId = pHead->clientIp;
		pHead->clientIp = pClient->getIp(fd,time,microTime);
		if(!BattleManager::getInstance()->sendData(m_spanId,srvId,m_inBuf)){
			LOG_ERROR("may be srv [%u_%u] disconnect",m_spanId,m_srvId);
			errorProcess(SRC_OUTPUT);
			return ;
		}

		if(PROTOCOL_ACCESS_CHANGE_LOGIN == cmd)
		{
			pClient->updateClientSrvId(fd,time,microTime,srvId);
		}

		return ;
	}
*/

	ClientHead clientHead;
	clientHead.head = MAGIC_HEADER;
	string packet, body;
	set<unsigned> fds;
	if(pHead->cmd == PROTOCOL_ACCESS_GROUP_SEND)
	{
		unsigned count = *((uint32_t*)(m_inBuf.c_str() + sizeof(BattleHead)));
		for(unsigned i=0;i<count;++i)
			fds.insert(*((uint32_t*)(m_inBuf.c_str() + sizeof(BattleHead) + sizeof(uint32_t)*(1+i))));

		clientHead.bodyLen = m_bodyLen - sizeof(uint32_t)*(1+count);
		body.append(m_inBuf.begin() + sizeof(BattleHead) + sizeof(uint32_t)*(1+count),m_inBuf.end());
	}
	else
	{
		clientHead.bodyLen = m_bodyLen;
		body.append(m_inBuf.begin()+sizeof(BattleHead),m_inBuf.end());
	}
	if(pHead->cmd == PROTOCOL_ACCESS_GROUP_SEND || pHead->cmd == PROTOCOL_ACCESS_BROAD_CAST || pHead->cmd == PROTOCOL_ACCESS_SEND)
	{
		clientHead.padding1 = max(1,rand());
		clientHead.padding2 = 0;
		static CrcUtil* pUtil = CrcUtil::getInstance();
		if(body.length() != clientHead.bodyLen){
			LOG_ERROR("invalid length,impossible!");
			return;
		}
		clientHead.crc2 = pUtil->update(body.c_str(), clientHead.bodyLen);
		pUtil->enCrypt(const_cast<char*>(body.c_str()), clientHead.bodyLen, clientHead.padding1);
		clientHead.crc1 = pUtil->update(body.c_str(), clientHead.bodyLen);
	}
	else
	{
		clientHead.crc1 = 0;
		clientHead.crc2 = 0;
		clientHead.padding1 = 0;
		clientHead.padding2 = 0;
	}
	packet.append((char*)&clientHead,sizeof(ClientHead));
	packet.append(body);

	if(pHead->cmd == PROTOCOL_ACCESS_GROUP_SEND)
	{
		for(set<unsigned>::iterator it=fds.begin();it!=fds.end();++it)
		{
			if(!pClient->sendData(*it,packet)){
				LOG_ERROR("[%u-%u-%u] has gone away",*it,time,microTime);
				clientClose(*it,time,microTime,0);
				continue;
			}
		}
	}
	else if(pHead->cmd == PROTOCOL_ACCESS_BROAD_CAST)
	{
		pClient->sendAll(m_srvId, packet);
		return;
	}
	else if(pHead->cmd == PROTOCOL_ACCESS_ANSWER)
	{
		if(!pClient->sendData(fd,time,microTime,packet)){
			LOG_ERROR("[%u-%u-%u] has gone away",fd,time,microTime);
			clientClose(fd,time,microTime,0);
			return;
		}
	}
	else if(pHead->cmd == PROTOCOL_ACCESS_SEND)
	{
		if(!pClient->sendData(fd,packet)){
			LOG_ERROR("[%u-%u-%u] has gone away",fd,time,microTime);
			clientClose(fd,time,microTime,0);
			return;
		}
	}
}

bool CBattleAsync::clientClose(uint32_t fd,uint32_t time,uint32_t microTime,uint32_t ip)
{
	BattleHead battleHead;
	battleHead.head = MAGIC_HEADER;
	battleHead.bodyLen = 0;
	battleHead.cmd = PROTOCOL_ACCESS_COFFLINE;
	battleHead.fd = fd;
	battleHead.time = time;
	battleHead.microTime = microTime;
	battleHead.clientIp = ip;

	string packet;
	packet.append((char*)&battleHead,sizeof(BattleHead));
	sendData(packet);

	return true;
}

void CBattleAsync::onConnected(){
	LOG_INFO("connect [%s:%d] ok",m_addr,m_port);
	m_inBuf.clear();
	m_bodyLen = 0;
}

bool CBattleAsync::parseAddress(){
	char key[64] = {0};
	sprintf(key,"%u",m_srvId);
	CConfig *cfg = CConfig::getInstance();
	const char *addr = cfg->GetStrVal("BATTLES", key);

	if(addr == NULL){
		LOG_ERROR("unknow battle server %u_%u",m_spanId,m_srvId);
		return false;
	}

	uint32_t port,ip0,ip1,ip2,ip3;
	if(sscanf(addr,"%u.%u.%u.%u:%u",&ip0,&ip1,&ip2,&ip3,&port) != 5){
		LOG_ERROR("may be conf illeagle %s",addr);
		return false;
	}

	sprintf(m_addr,"%u.%u.%u.%u",ip0,ip1,ip2,ip3);
	m_port = port;

	return true;
}


