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

#include "ProtocolInc.h"
#include "AsyncDBManager.h"
#include "db_client_manager.h"
#include "db_client_async.h"
#include "poll_thread.h"
#include "utils.h"

#define CLOSE(fd) {if(fd != 0) close(fd);fd=0;}

CDBClientAsync::CDBClientAsync(CPollThread *o, int fd)
{
	ownerUnit = o;
	netfd = fd;
	m_bodyLen = 0;
	memset(m_peerAddr, 0, sizeof(m_peerAddr));
	Utils::fdinfo(netfd, m_peerAddr, m_peerIp, m_peerPort);
	LOG_INFO("[%s:%d] connected", m_peerAddr, m_peerPort);
	DBClientManager::getInstance()->addClient(this);
}

int CDBClientAsync::Attach()
{
	EnableInput();

	if (AttachPoller())
	{
		return -1;
	}

	return 0;

}

CDBClientAsync::~CDBClientAsync()
{

}

void CDBClientAsync::InputNotify(void)
{
	recvProcess();
}

void CDBClientAsync::HangupNotify(void)
{
	errorProcess(SRC_HANGUP);
}

void CDBClientAsync::OutputNotify(void)
{
	int sendLen = send(netfd, m_outBuf.GetNativeBuffer(), m_outBuf.GetSize(), 0);
	if (0 > sendLen)
	{
		{
			error_log("errno=%u EAGIN addr [%s:%d],buflen=%u %m", errno, m_peerAddr, m_peerPort, m_outBuf.GetSize());
			return;
		}
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

int CDBClientAsync::errorProcess(int src)
{
	LOG_ERROR("error occured [%s:%d],src=%d,errno=%u,%m", m_peerAddr, m_peerPort, src, errno);

	DetachPoller();

	delete this;
	return 0;
}

bool CDBClientAsync::sendData(IBuffer* pData)
{
	if (!m_outBuf.AppendBuffer(pData))
	{
		error_log("send data failed, maybe buff too long");
		return false;
	}

	EnableOutput();
	ApplyEvents();

	return true;
}

void CDBClientAsync::recvProcess()
{
	int len = recv(netfd, m_inBuf.GetNativeBuffer() + m_inBuf.GetSize(), m_inBuf.GetFreeCapacity(), 0);
	if (len == 0)
	{
		LOG_ERROR("peer close [%s:%d] fd=%d", m_peerAddr, m_peerPort, netfd);
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

	uint32_t start = 0;
	do
	{
		if (m_inBuf.GetSize() - start < sizeof(ServerHead))
		{
			break;
		}

		ServerHead* pHead = (ServerHead*) (m_inBuf.GetNativeBuffer() + start);
		if (pHead->magic != MAGIC_HEADER)
		{
			LOG_ERROR("invalid magic head,%u", pHead->magic);
			errorProcess(SRC_INPUT);
			return;
		}

		if (m_inBuf.GetSize() - start < sizeof(ServerHead) + pHead->bodyLen)
		{
			break;
		}

		CStaticBuffer<MAX_PACKET_SIZE> packet;
		packet.Append(m_inBuf.GetNativeBuffer() + start, pHead->bodyLen + sizeof(ServerHead));
		packetProcess(&packet);

		start += pHead->bodyLen + sizeof(ServerHead);

	} while (true);

	if (start > 0)
	{
		m_inBuf.Remove(0, start);
	}
}

bool CDBClientAsync::packetProcess(IBuffer* pBuff)
{
	CNetPacket packet;
	if (!packet.Decode(pBuff))
	{
		LOG_ERROR("decode failed");
		return false;
	}
	packet.clientIp = netfd; // 通道fd存到packet中,发包时会用到
	AsyncDBManager::getInstance()->push(packet);

	return true;
}

void CDBClientAsync::onClientClose()
{

}
