/*
 * ChatAsync.cpp
 *
 *  Created on: 2016年4月28日
 *      Author: aaron
 */

#include "ChatAsync.h"
#include "ChatPacket.h"
#include "ProtocolDefine.h"
#include "ChatManager.h"
#define CLOSE(fd) {if(fd != 0) close(fd);fd=0;}

CChatAsync::CChatAsync(CPollThread *o)
{
	ownerUnit = o;
	m_stat = IDLE;
	m_port = 0;
}

CChatAsync::~CChatAsync()
{
}

bool CChatAsync::init()
{

	if (m_stat != IDLE)
	{
		return true;
	}

	if (!parseAddress())
	{
		error_log("parse address failed");
		return false;
	}

	struct sockaddr_in inaddr;
	int fd, flags, n;

	if ((fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		error_log("make tcp socket error, %m");
		return false;
	}

	netfd = fd;
	debug_log("get socket %d", netfd);

	bzero(&inaddr, sizeof(struct sockaddr_in));
	inaddr.sin_family = AF_INET;
	inaddr.sin_port = htons(m_port);

	if (inet_pton(AF_INET, m_addr, &inaddr.sin_addr) <= 0)
	{
		error_log("invalid address:[%s %d]", m_addr, m_port);
		return false;
	}

	//set the socket to nonblock
	flags = fcntl(fd, F_GETFL, 0);
	fcntl(fd, F_SETFL, flags | O_NONBLOCK);

	//int sockRcvBufLen = SIZE_RECV_BUFF;
	//setsockopt(netfd,SOL_SOCKET,SO_RCVBUF,&sockRcvBufLen,sizeof(sockRcvBufLen));

	if ((n = connect(fd, (const struct sockaddr *) &inaddr, sizeof(inaddr))) < 0)
	{
		if (errno != EINPROGRESS)
		{
			error_log("connect failed,errno:%d %s", errno, strerror(errno));
			return false;
		}

		info_log("wait to connected");

		m_stat = CONNECTING;

		EnableInput();
		EnableOutput();

		if (AttachPoller() != 0)
		{
			error_log("AttachPoller failed");
		}
	}

	if (n == 0)
	{
		info_log("connect to [%s:%d] success immediately", m_addr, m_port);
		m_stat = CONNECTED;
		if (Attach() != 0)
		{
			error_log("AttachPoller failed");
		}
		onConnected();
	}

	return true;
}

int CChatAsync::Attach()
{
	EnableInput();

	if (AttachPoller())
	{
		return -1;
	}

	return 0;
}

int CChatAsync::connectingProcess(int src)
{
	if (src == SRC_INPUT || src == SRC_OUTPUT)
	{
		int error;
		socklen_t len = sizeof(error);

		if (getsockopt(netfd, SOL_SOCKET, SO_ERROR, &error, &len) < 0)
		{
			error_log("connected to [%s:%d] failed, %s", m_addr, m_port, strerror(errno));

			m_stat = IDLE;
			DetachPoller();
			CLOSE(netfd);
			return -1;
		}

		if (error)
		{
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
	}
	else if (src == SRC_HANGUP) //some error occured
	{
		int error;
		socklen_t len = sizeof(error);

		if (getsockopt(netfd, SOL_SOCKET, SO_ERROR, &error, &len) < 0)
		{
			error_log("connected to [%s:%d] failed", m_addr, m_port);
		}
		else if (error)
		{
			error_log("connected to [%s:%d] failed", m_addr, m_port);
		}

		m_stat = IDLE;
		DetachPoller();
		CLOSE(netfd);
	}

	return 0;
}

bool CChatAsync::sendData(IBuffer* pData)
{

	if (!m_outBuf.AppendBuffer(pData))
	{
		error_log("buff too long [%s:%d]", m_addr, m_port);
		return false;
	}

	if (m_stat == CONNECTED)
	{
		EnableOutput();
		ApplyEvents();

		return true;
	}

	if (m_stat == IDLE)
	{
		init();
	}

	return false;
}

void CChatAsync::OutputNotify(void)
{
	if (m_stat == CONNECTING)
	{
		connectingProcess(SRC_OUTPUT);
		return;
	}

	int sendLen = send(netfd, m_outBuf.GetNativeBuffer(), m_outBuf.GetSize(), 0);
	if (0 > sendLen)
	{
		errorProcess(SRC_OUTPUT);
		return;
	}

	m_outBuf.Remove(0, sendLen);
	if (m_outBuf.GetSize() == 0)
	{
		DisableOutput();
		ApplyEvents();
	}
}

void CChatAsync::InputNotify(void)
{
	if (m_stat == CONNECTING)
	{
		connectingProcess(SRC_INPUT);
		return;
	}

	recvProcess();
}

void CChatAsync::HangupNotify(void)
{
	errorProcess(SRC_HANGUP);
}

int CChatAsync::errorProcess(int src)
{
//	error_log("error occured [%s:%d],src=%d,reason=%m",m_addr,m_port,src);
	m_stat = IDLE;
	DetachPoller();
	CLOSE(netfd);
	CChatManager::getInstance()->clearKey();
	return 0;
}

void CChatAsync::recvProcess()
{

	typedef struct ChatServerHead
	{
		byte magic;
		uint16_t bodyLen;
		uint16_t ptype;			//对应PROTOCOL_TYPE_系列
		uint32_t fd;
		uint32_t time;
		uint32_t microTime;
		uint32_t clientIp;
	} ChatServerHead;

	int len = recv(netfd, m_inBuf.GetNativeBuffer() + m_inBuf.GetSize(), m_inBuf.GetFreeCapacity(), 0);
	if (len == 0)
	{
//		error_log("peer close [%s:%d] fd=%d",m_addr,m_port,netfd);
		onClientClose();
		errorProcess(SRC_INPUT);
		return;
	}
	else if (len < 0)
	{
		errorProcess(SRC_INPUT);
		return;
	}
	m_inBuf.SetSize(m_inBuf.GetSize() + len);

	uint32_t decodeSize = 0;
	do
	{
//		if(m_inBuf.GetSize() - start < sizeof(ServerHead)){
//			break;
//		}
//
//		ServerHead* pHead = (ServerHead*)(m_inBuf.GetNativeBuffer() + start);
//		if(pHead->magic != PACKET_HEAD_MAGIC_NUMBER){
//			error_log("invalid magic head,%u",pHead->magic);
//			errorProcess(SRC_INPUT);
//			return;
//		}
//
//		if(m_inBuf.GetSize() - start < sizeof(ServerHead) + pHead->bodyLen){
//			break;
//		}
//
//		CStaticBuffer<MAX_PACKET_SIZE> packet;
//		packet.Append(m_inBuf.GetNativeBuffer()+start,pHead->bodyLen+sizeof(ServerHead));
//		packetProcess(&packet);
//
//		start += pHead->bodyLen+sizeof(ServerHead);

		CChatPacket packet;
		CStaticBuffer<MAX_PACKET_SIZE> buffer;
		buffer.Append(m_inBuf.GetNativeBuffer(), m_inBuf.GetSize());
		bool decodeSuccess = packet.Decode(&buffer);
		///TODO: decode size error auto close
		decodeSize = packet.GetDecodeSize();
		if (decodeSize > 0)
		{
			if (!decodeSuccess)
			{
//				error_log("[Decode fail][channelId=%d,size=%u,packet=%s]",
//						pChannel->GetChannelId(), pChannel->GetReceiveData()->GetSize(),
//						pChannel->GetReceiveData()->ToString().c_str());
			}
			m_inBuf.Remove(0, decodeSize);
		}
		if (decodeSuccess)
		{
			packetProcess(&buffer);
		}

	} while (decodeSize > 0);

//	uint32_t decodeSize = 0;
//	if(start > 0){
//		m_inBuf.Remove(0,start);
//	}
}

void CChatAsync::onConnected()
{
	info_log("connect [%s:%d] ok", m_addr, m_port);

	// 通知transfer 属于哪一个服务器
//	CStaticBuffer<MAX_PACKET_SIZE> buffer;
//	buffer.Clear();
//	CBufferWriter writer(&buffer);
	string firstPacket;
	string serverid = Config::GetValue("server_id");
	firstPacket.append("tgw_17_forward\r\nHost: ").append(m_addr).append(":").append(String::i2s(m_port)).append(" serverid:").append(serverid).append("\r\n\r\n");
	send(netfd, firstPacket.c_str(), firstPacket.size(), 0);
//	sendData(&buffer);

	CChatManager::getInstance()->onLogin();
}

bool CChatAsync::parseAddress()
{
	ServerItem addr;
	if (!ServerConfig::getInstance()->GetChat(addr)) {
		error_log("get chat server error!");
		return false;
	}
	strncpy(m_addr, addr.host.c_str(), sizeof(m_addr) - 1);
	m_port = addr.port;
	return true;
}

void CChatAsync::packetProcess(IBuffer* pBuff)
{
	CChatPacket* packet = new CChatPacket();
	if (!packet->Decode(pBuff))
	{
		error_log("packet decode failed");
		delete packet;
		return;
	}
	CChatManager::getInstance()->onReceive(packet);
}

void CChatAsync::onClientClose()
{

}
