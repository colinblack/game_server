/*
 * FireChannel.cpp
 *
 * Created on: 2013-01-31
 * Author: rein
 */

#include "FireChannel.h"
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include "FireServer.h"
#include <math.h>

#define TCP_SERVER_LISTEN_CONNCETIONS 100
#define TCP_CHANNEL_ACTIVE_TIMEOUT	60

static unsigned CRCBitReflect(unsigned arg1, unsigned arg2)
{
	const unsigned P6110[] = {0xFFFFFFFF,0xFFFFFFFE,0xFFFFFFFC,0xFFFFFFF8,
		0xFFFFFFF0,0xFFFFFFE0,0xFFFFFFC0,0xFFFFFF80,0xFFFFFF00,0xFFFFFE00,
	    0xFFFFFC00,0xFFFFF800,0xFFFFF000,0xFFFFE000,0xFFFFC000,0xFFFF8000
	};

	unsigned local6 = 0;
	unsigned local5 = 0;
	unsigned local3 = 0;
	arg2--;
	local6 = 0;
	while (local6 <= arg2)
	{
		local5 = (arg2 - local6);
		if ((arg1 & 1))
		{
			local3 = (local3 | ((1 << local5) & P6110[local5]));
		};
		arg1 = ((arg1 >> 1) & 2147483647);
		local6++;
	}
	return (local3);
}

static unsigned* MakeCrcTable()
{
	unsigned local4 = 0;
	unsigned local3 = 0;
	unsigned* local2 = NULL;
	unsigned local1 = 0;
	const unsigned P6109 = 4129;
	local2 = new unsigned[0x0100];
	if (NULL == local2)
	{
		return NULL;
	}
	local3 = 0;
	while (local3 < 0x0100)
	{
		local1 = ((local3 << 8) & 0xFFFFFF00);
		local4 = 0;
		while (local4 < 8)
		{
			local1 = (((local1 & 0x8000)) ? (((local1 << 1) & 0xFFFFFFFE) ^ P6109) : ((local1 << 1) & 0xFFFFFFFE));
			local4++;
		};
		local2[local3] = local1;
		local3++;
	};
	return local2;
}

CInternetFireAddress::CInternetFireAddress() :
	Port(0)
{
}

CInternetFireAddress::CInternetFireAddress(const char *ip, uint16_t port) :
	IP(ip),
	Port(port)
{
}

CInternetFireAddress &CInternetFireAddress::operator=(const CInternetFireAddress &address)
{
	IP = address.IP;
	Port = address.Port;
	return *this;
}

void CInternetFireAddress::Clear()
{
	IP.clear();
	Port = 0;
}

bool CInternetFireAddress::FromString(const string &sAddress)
{
	vector<string> vecAddress;
	CBasic::StringSplitTrim(sAddress, ":", vecAddress);
	if(vecAddress.size() != 2)
	{
		return false;
	}
	unsigned port;
	if(!Convert::StringToUInt(port, vecAddress[1]))
	{
		return false;
	}
	if(port > UINT16_MAX)
	{
		return false;
	}
	IP = vecAddress[0];
	Port = port;
	return true;
}

bool CInternetFireAddress::FromSockAddr(const void *pSockAddr)
{
	if(pSockAddr == NULL)
	{
		return false;
	}
	const sockaddr_in *pSockAddrIn = (sockaddr_in *)pSockAddr;
	Port = ntohs(pSockAddrIn->sin_port);
	char acIp[40];
	if(inet_ntop(pSockAddrIn->sin_family, &pSockAddrIn->sin_addr, acIp, sizeof(acIp)) == NULL)
	{
		return false;
	}
	acIp[sizeof(acIp) - 1] = '\0';
	IP = acIp;
	return true;
}

string CInternetFireAddress::ToString() const
{
	string s;
	String::Format(s, "%s:%hu", IP.c_str(), Port);
	return s;
}

#define ASSERT_CALL_SOCKET(call)	\
	if(!m_socket.call)	\
	{	\
		m_socket.Close();	\
		return false;	\
	}	\

CFireServer* CFireChannel::m_pServer=NULL;
	
CFireChannel::CFireChannel() :
	m_channelId(-1),
	m_lastActiveTime(0),
	m_verification(0)
{
	memset(m_keyBuff, 0, 4);
}

CFireChannel::~CFireChannel()
{
}

int CFireChannel::GetChannelId()
{
	return m_channelId;
}

void CFireChannel::SetServer(CFireServer * pServer){
	m_pServer = pServer;
}

bool CFireChannel::CreateServer(int channelId, const CInternetFireAddress &listenAddress)
{
	Close();
	ASSERT_CALL_SOCKET(Socket(SOCK_STREAM))
	ASSERT_CALL_SOCKET(SetReuseAddr(true))
	ASSERT_CALL_SOCKET(Bind(listenAddress.Port, listenAddress.IP.c_str()))
	ASSERT_CALL_SOCKET(SetBlock(false))
	ASSERT_CALL_SOCKET(Listen(TCP_SERVER_LISTEN_CONNCETIONS))
	m_channelId = channelId;
	m_localAddress = listenAddress;
	m_lastActiveTime = Time::GetGlobalTime();
	return true;
}

bool CFireChannel::CreateClient(int channelId, const CInternetFireAddress &serverAddress, const CInternetFireAddress *bindAddress)
{
	Close();
	ASSERT_CALL_SOCKET(Socket(SOCK_STREAM))
	ASSERT_CALL_SOCKET(SetReuseAddr(true))
	if(bindAddress != NULL)
	{
		ASSERT_CALL_SOCKET(Bind(bindAddress->Port, bindAddress->IP.c_str()))
		m_localAddress = *bindAddress;
	}
	ASSERT_CALL_SOCKET(SetBufferSize(TCP_CHANNEL_BUFFER_SIZE))
	ASSERT_CALL_SOCKET(Connect(serverAddress.Port, serverAddress.IP.c_str()))
	ASSERT_CALL_SOCKET(SetBlock(false))
	m_channelId = channelId;
	m_remoteAddress = serverAddress;
	m_lastActiveTime = Time::GetGlobalTime();
	return true;
}

bool CFireChannel::Accept(int channelId, CFireChannel &listenChannel)
{
	Close();
	sockaddr_in sockAddr;
	int sockAddrLength = sizeof(sockaddr_in);
	if(!listenChannel.m_socket.Accept(&m_socket, (sockaddr *)&sockAddr, &sockAddrLength))
	{
		m_socket.Close();
		return false;
	}
	ASSERT_CALL_SOCKET(SetBlock(false))
	int iNoDelay = 1;
	ASSERT_CALL_SOCKET(SetSockOpt(IPPROTO_TCP, TCP_NODELAY, &iNoDelay, sizeof(iNoDelay)))
	ASSERT_CALL_SOCKET(SetBufferSize(TCP_CHANNEL_BUFFER_SIZE))
	m_channelId = channelId;
	m_localAddress = listenChannel.m_localAddress;
	m_remoteAddress.FromSockAddr(&sockAddr);
	m_lastActiveTime = Time::GetGlobalTime();
	return true;
}

bool CFireChannel::RealSend(){
	if(m_socket.IsClosed())
	{
		return false;
	}

	int byteLeft = m_sendBuffer.GetSize();
	if(byteLeft == 0){
		m_pServer->EnableOutput(this,false);
		return true;
	}

	m_lastActiveTime = Time::GetGlobalTime();
	int byteSent = m_socket.Send(m_sendBuffer.GetConstBuffer() , byteLeft);
	if(byteSent > 0){
		m_sendBuffer.Remove(0, byteSent);
	}
	return true;
}

bool CFireChannel::SendData(const IBuffer *pBuffer)
{
	if(m_socket.IsClosed())
	{
		return false;
	}

	if(pBuffer == NULL)
	{
		return true;
	}
	bool ret = m_sendBuffer.AppendBuffer(pBuffer);
	if(ret)
	{
		ret = m_pServer->EnableOutput(this);
	}
	else
	{
		debug_log("send buffer append failed");
	}
	return ret;
}

bool CFireChannel::ReceiveData()
{
	if(m_socket.IsClosed())
	{
		return false;
	}

	int byteRecv = 0;
	do
	{
		byteRecv = m_recvBuffer.GetFreeCapacity();
		if(byteRecv <= 0)
		{
			return true;
		}
		byteRecv = m_socket.Receive(m_recvBuffer.GetNativeBuffer() + m_recvBuffer.GetSize(), byteRecv);
		if(byteRecv > 0)
		{
			m_recvBuffer.SetSize(m_recvBuffer.GetSize() + byteRecv);
			m_lastActiveTime = Time::GetGlobalTime();
		}
		else if(byteRecv == 0)
		{
			error_log("[Receive error][m_channelId=%d,buffer=%s]",m_channelId, m_recvBuffer.ToString().c_str());
			return false;
		}
		else
		{
			int lastError = m_socket.GetLastError();
			if(lastError == EINTR)
			{
				error_log("[Receive error][error=EINTR,channel=%d,fd=%d]", m_channelId, m_socket.GetSocket());
			}
			else if(lastError == EAGAIN)
			{
				return true;
			}
			else
			{
				if(lastError != ECONNRESET)
				{
					error_log("[Receive error][error=%d,channel=%d,fd=%d]", lastError, m_channelId, m_socket.GetSocket());
				}
				error_log("[Receive error][error=%d,channel=%d,fd=%d]", lastError, m_channelId, m_socket.GetSocket());

				return false;
			}
		}
	}while(byteRecv > 0);

	return true;
}

IBuffer *CFireChannel::GetReceiveData()
{
	return &m_recvBuffer;
}

bool CFireChannel::SetDataRead(uint32_t byteRead)
{
	return m_recvBuffer.Remove(0, byteRead);
}

bool CFireChannel::Close()
{
	m_socket.Close();
	m_channelId = -1;
	m_lastActiveTime = 0;
	m_localAddress.Clear();
	m_remoteAddress.Clear();
	m_sendBuffer.Clear();
	m_recvBuffer.Clear();
	return true;
}

bool CFireChannel::IsClosed() const
{
	return m_socket.IsClosed();
}

bool CFireChannel::IsActive() const
{
	return m_lastActiveTime + TCP_CHANNEL_ACTIVE_TIMEOUT > Time::GetGlobalTime();
}

int CFireChannel::GetSocket() const
{
	return m_socket.GetSocket();
}

int CFireChannel::GetLastError() const
{
	return m_socket.GetLastError();
}

string CFireChannel::ToString() const
{
	string s;
	String::Format(s, "ChannelId=%d&Local=%s&Remote=%s", m_channelId,
			m_localAddress.ToString().c_str(), m_remoteAddress.ToString().c_str());
	return s;
}

const CInternetFireAddress *CFireChannel::GetRemoteAddress() const
{
	return &m_remoteAddress;
}

int CFireChannel::Verification()
{
	if (m_verification == 0)
	{
		CBufferReader reader(&m_recvBuffer);
		if(!reader.GetUInt32(m_SelfSalt))
		{
			return m_verification;
		}
		if(!SetDataRead(sizeof(uint32_t)))
		{
			info_log("SetDataRead m_SelfSalt fail!");
		}
		m_TargetSalt = (unsigned)rand();

		MakeKey();

		info_log("m_SelfSalt = %u, m_TargetSalt = %u", m_SelfSalt, m_TargetSalt);
		CStaticBuffer<4> sendBuffer;
		CBufferWriter writer(&sendBuffer);

		if (!writer.AppendUInt32(m_TargetSalt))
		{
			info_log("AppendUInt32 m_TargetSalt fail!");
			return m_verification;
		}

		if (SendData(&sendBuffer))
		{
			m_verification = 1;
		}
	}
	else if(m_verification == 1)
	{
		CBufferReader reader(&m_recvBuffer);
		unsigned short crcRecv = 0;
		if(!reader.GetUInt16(crcRecv))
		{
			info_log("reader crcRecv fail!");
			return m_verification;
		}
		if(!SetDataRead(sizeof(uint16_t)))
		{
			info_log("SetDataRead crcRecv fail!");
		}
		CStaticBuffer<4> sendBuffer;
		CBufferWriter writer(&sendBuffer);
		unsigned key = (m_SelfSalt ^ m_TargetSalt) + 3397;
		info_log("key=%u", key);

		if (!writer.AppendUInt32(key))
		{
			info_log("AppendUInt32 key fail!");
			return m_verification;
		}
		unsigned localCrcRet = Update(sendBuffer.GetConstBuffer(), sendBuffer.GetSize());
		info_log("crcRecv=%u,localCrcRet=%u", crcRecv, localCrcRet);
		if (crcRecv == localCrcRet)
		{
			m_verification = 2;
		}
	}

	return m_verification;
}


unsigned CFireChannel::Update(const byte* buffer, unsigned bufferLen, unsigned arg2, unsigned arg3)
{
	unsigned local7 = 0;
	unsigned local6 = 0;
	unsigned local5 = 0;
	unsigned local4 = 0;
	unsigned* CRCTable = MakeCrcTable();
	if (NULL == CRCTable)
	{
		return -1;
	}
	arg3 = ((arg3) ? arg3 : bufferLen);
	local6 = arg2;
	while (local6 < arg3)
	{
		local5 = ((CRCBitReflect(buffer[local6], 8) & 0xFF) ^ ((local4 >> 8) & 0xFFFFFF));
		local5 = (local5 & 0xFF);
		local4 = (CRCTable[local5] ^ ((local4 << 8) & 0xFFFFFF00));
		local6++;
	};
	local7 = ((CRCBitReflect(local4, 16) ^ 0) & 0xFFFF);
	return local7;
}

void CFireChannel::MakeKey()
{
	unsigned index = 0;
	unsigned Key = ((m_SelfSalt ^ m_TargetSalt) + 3397);
	while (index < 4)
	{
		m_keyBuff[index] = ((Key & (0xFF << (index << 3))) >> (index << 3));
		index++;
	};
}

unsigned CFireChannel::Encode(byte* buffer, int length, unsigned para2, unsigned para3)
{
	unsigned local5 = 0;
	unsigned local4 = 0;
	if (para2 >= length)
	{
		return (0);
	}
	local4 = ((para3) ? (para2 + para3) : length);
	if (local4 > length)
	{
		local4 = length;
	}
	local5 = para2;
	while (local5 < local4)
	{
		buffer[local5] = (buffer[local5] ^ m_keyBuff[(local5 % 4)]);
		local5++;
	}
	return ((local4 - para2));
}

bool CFireChannel::SetChannelUid(unsigned uid)
{
	m_uid = uid;
	return true;
}

unsigned CFireChannel::GetChannelUid(void)
{
	return m_uid;
}
