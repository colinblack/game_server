/*
 * TransitAsync.cpp
 *
 *  Created on: 2016-3-15
 *      Author: Administrator
 */

#include "utils.h"
#include "TransitAsync.h"
#include "ProtocolDefine.h"
#include "TransitManager.h"
#include "OpenPlatform.h"
#include "TransitServer.h"


#define CLOSE(fd) {if(fd != 0) close(fd);fd=0;}
#define MAX_BUFF_SIZE 2048000

TransitAsync::TransitAsync(CPollThread *o, int fd)
{
	ownerUnit = o;
	netfd = fd;

	memset(m_peerAddr,0,sizeof(m_peerAddr));
	Utils::fdinfo(netfd, m_peerAddr,m_peerIp, m_peerPort);

	uint32_t now = GET_MSEC();
	m_time = now / 1000;
}

int TransitAsync::Attach()
{
	EnableInput();

	if(AttachPoller())
	{
		return -1;
	}

	return 0;

}

TransitAsync::~TransitAsync ()
{

}


void TransitAsync::InputNotify (void)
{
	recvProcess();
}

void TransitAsync::HangupNotify(void)
{
	errorProcess(SRC_HANGUP);
}

void TransitAsync::OutputNotify (void)
{
	int sendLen = send(netfd,m_outBuf.GetNativeBuffer(),m_outBuf.GetSize(),0);
	if(0 > sendLen){
		{
			error_log("errno=%u EAGIN addr [%s:%d],buflen=%u %m",errno,m_peerAddr,m_peerPort,m_outBuf.GetSize());
			return;
		}
		errorProcess(SRC_OUTPUT);
		return;
	}
	m_outBuf.Remove(0,sendLen);
	if(m_outBuf.GetSize() == 0){
		DisableOutput();
		ApplyEvents();
	}
}

int TransitAsync::errorProcess(int src){

	error_log("error occured [%s:%d],src=%d,errno=%u,%m",m_peerAddr,m_peerPort,src,errno);
	DetachPoller();
	delete this;
	return 0;
}

void TransitAsync::recvProcess(){

	int len = recv(netfd,m_inBuf.GetNativeBuffer() + m_inBuf.GetSize(),m_inBuf.GetFreeCapacity(),0);
	if(len == 0){
		error_log("peer close [%s:%d] fd=%d",m_peerAddr,m_peerPort,netfd);
		onClientClose();
		//errorProcess(SRC_INPUT);
		return;
	}
	else if(len < 0){
		errorProcess(SRC_INPUT);
		return;
	}
	m_inBuf.SetSize(m_inBuf.GetSize()+len);

	uint32_t start = 0;
	do{
		if(m_inBuf.GetSize() - start < sizeof(ServerHead)){
			break;
		}

		ServerHead* pHead = (ServerHead*)(m_inBuf.GetNativeBuffer() + start);
		if(pHead->magic != MAGIC_HEADER){
			error_log("invalid magic head,%u",pHead->magic);
			errorProcess(SRC_INPUT);
			return;
		}

		if(pHead->bodyLen < 2){
			error_log("invalid bodyLen:%d",pHead->bodyLen);
			errorProcess(SRC_INPUT);
			return;
		}

		if(m_inBuf.GetSize() - start < sizeof(ServerHead) + pHead->bodyLen){
			break;
		}

		CStaticBuffer<MAX_PACKET_SIZE> packet;
		packet.Append(m_inBuf.GetNativeBuffer()+start,pHead->bodyLen+sizeof(ServerHead));
		if(!packetProcess(&packet))
		{
			error_log("packetProcess fail");
		}

		start += pHead->bodyLen+sizeof(ServerHead);

	}while(true);

	if(start > 0){
		m_inBuf.Remove(0,start);
	}
}


bool TransitAsync::packetProcess(IBuffer* pBuff){

	CNetPacket* packet = new CNetPacket();
	if(packet == NULL)
	{
		error_log("new packet fail");
		return false;
	}
	if(!packet->Decode(pBuff)){
		error_log("packet decode failed");
		delete packet;
		return false;
	}
	TransitServer::getInstance()->addLoginPacket(packet);
	return true;
}

void TransitAsync::onClientClose()
{
	DetachPoller();
	delete this;
	return;
}
