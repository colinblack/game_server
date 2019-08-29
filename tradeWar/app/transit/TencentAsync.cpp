/*
 * TencentAsync.cpp
 *
 *  Created on: 2016-3-15
 *      Author: Administrator
 */

#include "utils.h"
#include "TencentAsync.h"
#include "ProtocolDefine.h"
#include "TransitManager.h"
#include "OpenPlatform.h"
#include "TencentAsyncManager.h"
#include "TransitServer.h"

#define CLOSE(fd) {if(fd != 0) close(fd);fd=0;}
#define MAX_BUFF_SIZE 2048000

TencentAsync::TencentAsync(CPollThread *o, int fd)
{
	ownerUnit = o;
	netfd = fd;

	memset(m_peerAddr,0,sizeof(m_peerAddr));
	Utils::fdinfo(netfd, m_peerAddr,m_peerIp, m_peerPort);

	uint32_t now = GET_MSEC();
	m_time = now / 1000;
	TencentAsyncManager::getInstance()->addClient(this);
}

int TencentAsync::Attach()
{
	EnableInput();

	if(AttachPoller())
	{
		return -1;
	}

	return 0;

}

TencentAsync::~TencentAsync()
{
	TencentAsyncManager::getInstance()->removeClient(this);
}

void TencentAsync::InputNotify(void)
{
	recvProcess();
}

void TencentAsync::HangupNotify(void)
{
	errorProcess(SRC_HANGUP);
}

void TencentAsync::OutputNotify (void)
{
	int sendLen = send(netfd,m_outBuf.GetNativeBuffer(),m_outBuf.GetSize(),0);
	if(sendLen < 0)
	{
		{
			error_log("errno=%u EAGIN addr [%s:%d],buflen=%u %m",errno,m_peerAddr,m_peerPort,m_outBuf.GetSize());
			return;
		}
		errorProcess(SRC_OUTPUT);
		return;
	}
	m_outBuf.Remove(0,sendLen);
	if(m_outBuf.GetSize() == 0)
	{
		onClientClose();
	}
}

int TencentAsync::errorProcess(int src){

	error_log("error occured [%s:%d],src=%d,errno=%u,%m",m_peerAddr,m_peerPort,src,errno);
	DetachPoller();
	delete this;
	return 0;
}

void TencentAsync::recvProcess()
{
	do{
		int len = recv(netfd,m_inBuf.GetNativeBuffer() + m_inBuf.GetSize(),m_inBuf.GetFreeCapacity(),0);
		if(len == 0)
		{
			errorProcess(SRC_INPUT);
			return;
		}
		else if(len > 0)
		{
			m_inBuf.SetSize(m_inBuf.GetSize()+len);
		}
		else
		{
			if(errno == EAGAIN)//接收完成
			{
				m_inBuf.SetSize(m_inBuf.GetSize()+len);
				packetProcess();
				break;
			}
			else if(errno == EINTR)
			{
				error_log("receive error error:%d",errno);
			}
			else
			{
				errorProcess(SRC_INPUT);
				return;
			}
		}
	}while(true);
	//m_inBuf.Remove(0,len);
}

bool TencentAsync::packetProcess()
{
	TencentPacket* packet = new TencentPacket();
	if(packet == NULL)
	{
		error_log("new packet fail");
		return false;
	}
	packet->netfd = netfd;
	packet->msg = (char*)(m_inBuf.GetNativeBuffer());
	TransitServer::getInstance()->addTencentPacket(packet);
	return true;
}

void TencentAsync::onClientClose()
{
	DetachPoller();
	delete this;
	return;
}

bool TencentAsync::sendData(IBuffer* pData)
{
	if(!m_outBuf.AppendBuffer(pData))
	{
		error_log("send data failed, maybe buff too long");
		return false;
	}
	EnableOutput();
	ApplyEvents();
	return true;
}
