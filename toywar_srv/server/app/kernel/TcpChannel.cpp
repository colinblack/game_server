/*
 * TcpChannel.cpp
 *
 *  Created on: 2012-2-10
 *      Author: dada
 */

#include "TcpChannel.h"
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include "TcpServer.h"

#define TCP_SERVER_LISTEN_CONNCETIONS 100
#define TCP_CHANNEL_ACTIVE_TIMEOUT	60

#define htonll(x) ((1==htonl(1)) ? (x) : (((uint64_t)htonl((x) & 0xFFFFFFFFUL)) << 32) | htonl((uint32_t)((x) >> 32)))
#define ntohll(x) ((1==ntohl(1)) ? (x) : (((uint64_t)ntohl((x) & 0xFFFFFFFFUL)) << 32) | ntohl((uint32_t)((x) >> 32)))

byte CTcpChannel::m_Sbuffer[TCP_CHANNEL_BUFFER_SIZE];

CInternetAddress::CInternetAddress() :
	Port(0) {
}

CInternetAddress::CInternetAddress(const char *ip, uint16_t port) :
	IP(ip), Port(port) {
}

CInternetAddress &CInternetAddress::operator=(const CInternetAddress &address) {
	IP = address.IP;
	Port = address.Port;
	return *this;
}

void CInternetAddress::Clear() {
	IP.clear();
	Port = 0;
}

bool CInternetAddress::FromString(const string &sAddress) {
	vector < string > vecAddress;
	CBasic::StringSplitTrim(sAddress, ":", vecAddress);
	if (vecAddress.size() != 2) {
		return false;
	}
	unsigned port;
	if (!Convert::StringToUInt(port, vecAddress[1])) {
		return false;
	}
	if (port > UINT16_MAX) {
		return false;
	}
	IP = vecAddress[0];
	Port = port;
	return true;
}

bool CInternetAddress::FromSockAddr(const void *pSockAddr) {
	if (pSockAddr == NULL) {
		return false;
	}
	const sockaddr_in *pSockAddrIn = (sockaddr_in *) pSockAddr;
	Port = ntohs(pSockAddrIn->sin_port);
	char acIp[40];
	if (inet_ntop(pSockAddrIn->sin_family, &pSockAddrIn->sin_addr, acIp,
			sizeof(acIp)) == NULL) {
		return false;
	}
	acIp[sizeof(acIp) - 1] = '\0';
	IP = acIp;
	return true;
}

string CInternetAddress::ToString() const {
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

CTcpServer* CTcpChannel::m_pServer = NULL;

CTcpChannel::CTcpChannel() :
	m_channelId(-1), m_isFirst(true),m_bWebSocket(false), m_lastActiveTime(0) {
}

CTcpChannel::~CTcpChannel() {
}

int CTcpChannel::GetChannelId() {
	return m_channelId;
}

void CTcpChannel::SetServer(CTcpServer * pServer) {
	m_pServer = pServer;
}

bool CTcpChannel::CreateServer(int channelId,
		const CInternetAddress &listenAddress) {
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

bool CTcpChannel::CreateClient(int channelId,
		const CInternetAddress &serverAddress,
		const CInternetAddress *bindAddress) {
	Close();
	ASSERT_CALL_SOCKET(Socket(SOCK_STREAM))
	ASSERT_CALL_SOCKET(SetReuseAddr(true))
	if (bindAddress != NULL) {
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

bool CTcpChannel::Accept(int channelId, CTcpChannel &listenChannel) {
	Close();
	sockaddr_in sockAddr;
	int sockAddrLength = sizeof(sockaddr_in);
	if (!listenChannel.m_socket.Accept(&m_socket, (sockaddr *) &sockAddr,
			&sockAddrLength)) {
		m_socket.Close();
		return false;
	}
	ASSERT_CALL_SOCKET(SetBlock(false));
	int iNoDelay = 1;
	ASSERT_CALL_SOCKET(SetSockOpt(IPPROTO_TCP, TCP_NODELAY, &iNoDelay, sizeof(iNoDelay)))
	ASSERT_CALL_SOCKET(SetBufferSize(TCP_CHANNEL_BUFFER_SIZE))
	m_channelId = channelId;
	m_isFirst = true;
	m_bWebSocket = false;
	m_localAddress = listenChannel.m_localAddress;
	m_remoteAddress.FromSockAddr(&sockAddr);
	m_lastActiveTime = Time::GetGlobalTime();
	return true;
}

bool CTcpChannel::RealSend() {
	if (m_socket.IsClosed()) {
		return false;
	}
	int byteLeft = m_sendBuffer.GetSize();
	if (byteLeft == 0) {
		m_pServer->EnableOutput(this, false);
		return true;
	}

	m_lastActiveTime = Time::GetGlobalTime();

	int byteSent = m_socket.Send(m_sendBuffer.GetConstBuffer(), byteLeft);

	if (byteSent > 0) {
		//debug_log("[%s:%d,%d]",m_remoteAddress.ToString().c_str(),byteLeft,byteSent);
		m_sendBuffer.Remove(0, byteSent);
	}

	return true;
}

bool CTcpChannel::SendData(const IBuffer *pBuffer) {
	if (m_socket.IsClosed()) {
		return false;
	}

	if (pBuffer == NULL) {
		return true;
	}

	bool ret = m_sendBuffer.AppendBuffer(pBuffer);
	if (ret) {
		ret = m_pServer->EnableOutput(this);
	} else {
		debug_log("send buffer append failed");
	}
	return ret;

	//发送滞留缓冲区数据
	int byteLeft = m_sendBuffer.GetSize();
	int sendPos = 0;
	while (byteLeft > 0) {
		int byteSent = m_socket.Send(m_sendBuffer.GetConstBuffer() + sendPos,
				byteLeft);
		if (byteSent > 0) {
			byteLeft -= byteSent;
			sendPos += byteSent;
			m_lastActiveTime = Time::GetGlobalTime();
		} else if (byteSent < 0) {
			int lastError = m_socket.GetLastError();
			if (lastError == EINTR) {
				error_log("[Send error][error=EINTR,channel=%d,fd=%d]", m_channelId, m_socket.GetSocket());
			} else if (lastError == EAGAIN) {
				if (sendPos > 0) {
					m_sendBuffer.Remove(0, sendPos);
				}
				if (pBuffer == NULL) {
					return true;
				}
				return m_sendBuffer.AppendBuffer(pBuffer);
			} else {
				error_log("[Send error][error=%d,channel=%d,fd=%d]", lastError, m_channelId, m_socket.GetSocket());
				return false;
			}
		} else {
			error_log("[Send error][socket=%d,bytesent=0]",m_socket.GetSocket());
		}
	}
	if (sendPos > 0) {
		m_sendBuffer.Clear();
	}

	if (pBuffer == NULL) {
		return true;
	}
	byteLeft = pBuffer->GetSize();
	sendPos = 0;
	while (byteLeft > 0) {
		int byteSent = m_socket.Send(pBuffer->GetConstBuffer() + sendPos,
				byteLeft);
		if (byteSent > 0) {
			byteLeft -= byteSent;
			sendPos += byteSent;
			m_lastActiveTime = Time::GetGlobalTime();
		} else if (byteSent < 0) {
			int lastError = m_socket.GetLastError();
			if (lastError == EINTR) {
				error_log("[Send error][error=EINTR,channel=%d,fd=%d]", m_channelId, m_socket.GetSocket());
			} else if (lastError == EAGAIN) {
				//系统发送缓冲区已满，放进滞留缓冲区
				return m_sendBuffer.Append(pBuffer->GetConstBuffer() + sendPos,
						pBuffer->GetSize() - sendPos);
			} else {
				if (lastError != ECONNRESET) {
					error_log("[Send error][error=%d,channel=%d,fd=%d]", lastError, m_channelId, m_socket.GetSocket());
				}
				return false;
			}
		}
	}
	return true;
}

bool CTcpChannel::ReceiveData() {
	if (m_socket.IsClosed()) {
		return false;
	}

	int byteRecv = 0;
	do {
		byteRecv = m_recvBuffer.GetFreeCapacity();
		if (byteRecv <= 0) {
			return true;
		}
		byteRecv = m_socket.Receive(m_Sbuffer, byteRecv);

		if (byteRecv > 0) {
			m_recvBuffer.Append(m_Sbuffer, byteRecv);
			m_lastActiveTime = Time::GetGlobalTime();

			if (m_isFirst) {
				//error_log("buff = %s,|||size =%d",m_recvBuffer.ToString().c_str(),byteRecv);
				byte buf[1024] = {0};
				int len = byteRecv > sizeof(buf) ? sizeof(buf) : byteRecv;
				m_recvBuffer.GetData(buf,len,0);

				if(m_bWebSocket){//websocket first
					m_isFirst = false;

					if((buf[0] & 0x80) != 0x80)
					{
						error_log("[websocket fin error][channel=%d,fd=%d]", m_channelId, m_socket.GetSocket());
						return false;
					}
					if((buf[0] & 0x0F) != 0x02)
					{
						error_log("[websocket opcode error][channel=%d,fd=%d]", m_channelId, m_socket.GetSocket());
						return false;
					}
					if((buf[1] & 0x80) != 0x80)
					{
						error_log("[websocket mask error][channel=%d,fd=%d]", m_channelId, m_socket.GetSocket());
						return false;
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

					if(l + skip <= len){
						for(int i=0;i<l;++i)
							buf[i + skip] = buf[i + skip] ^ mask[i % 4];
					}

					//debug_log("websocket first %s", (char*)(buf+skip));
				}
				else{
					if(strstr((char*)buf, "GET ") == (char*)buf){//websocket shake hand
						m_bWebSocket = true;

				        string k((char*)buf), b("Sec-WebSocket-Key:"), e("\r");
				        if(k.find(b) == string::npos){
							error_log("[websocket key error][channel=%d,fd=%d]", m_channelId, m_socket.GetSocket());
							return false;
				        }
				        k = k.substr(k.find(b) + b.length());
				        if(k.find(e) == string::npos){
							error_log("[websocket value error][channel=%d,fd=%d]", m_channelId, m_socket.GetSocket());
							return false;
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

						CDanymicBuffer<1000> buffer;
						CBufferWriter writer(&buffer);
						writer.AppendBytes((byte*)res.c_str(), res.size());
						SendData(&buffer);

						//debug_log("websocket shake hand skey=%s,rkey=%s",skey.c_str(),rkey.c_str());
					}
					else if(strstr((char*)buf, "websocket\r\n\r\n") == (char*)buf){//websocket from transfer first
						m_isFirst = false;
						m_bWebSocket = true;

						//debug_log("websocket transfer %s", (char*)buf);
					}
					else//normal tcp
						m_isFirst = false;
				}

				char* pos = strstr((char*)buf,"\r\n\r\n");
				if(pos !=NULL)
				{
					m_recvBuffer.Remove(0, (byte*)pos - &buf[0] + 4);
					byteRecv -= ((byte*)pos - &buf[0] + 4);
					//error_log("buff = %s,|||size =%d",m_recvBuffer.ToString().c_str(),byteRecv);
				}
			}

		} else if (byteRecv == 0) {
			//error_log("[Receive error] 0,%s",m_recvBuffer.ToString().c_str());
			return false;
		} else {
			int lastError = m_socket.GetLastError();
			if (lastError == EINTR) {
				error_log("[Receive error][error=EINTR,channel=%d,fd=%d]", m_channelId, m_socket.GetSocket());
			} else if (lastError == EAGAIN) {
				return true;
			} else {
				if (lastError != ECONNRESET) {
					error_log("[Receive error][error=%d,channel=%d,fd=%d]", lastError, m_channelId, m_socket.GetSocket());
				}
				error_log("[Receive error][error=%d,channel=%d,fd=%d]", lastError, m_channelId, m_socket.GetSocket());

				return false;
			}
		}
	} while (byteRecv > 0);

	return true;
}

IBuffer *CTcpChannel::GetReceiveData() {
	return &m_recvBuffer;
}

bool CTcpChannel::SetDataRead(uint32_t byteRead) {
	return m_recvBuffer.Remove(0, byteRead);
}

bool CTcpChannel::Close() {
	m_socket.Close();
	m_channelId = -1;
	m_lastActiveTime = 0;
	m_localAddress.Clear();
	m_remoteAddress.Clear();
	m_sendBuffer.Clear();
	m_recvBuffer.Clear();
	return true;
}

bool CTcpChannel::IsClosed() const {
	return m_socket.IsClosed();
}

bool CTcpChannel::IsActive() const {
	return m_lastActiveTime + TCP_CHANNEL_ACTIVE_TIMEOUT
			> Time::GetGlobalTime();
}

int CTcpChannel::GetSocket() const {
	return m_socket.GetSocket();
}

int CTcpChannel::GetLastError() const {
	return m_socket.GetLastError();
}

string CTcpChannel::ToString() const {
	string s;
	String::Format(s, "ChannelId=%d&Local=%s&Remote=%s", m_channelId,
			m_localAddress.ToString().c_str(),
			m_remoteAddress.ToString().c_str());
	return s;
}

const CInternetAddress *CTcpChannel::GetRemoteAddress() const {
	return &m_remoteAddress;
}

