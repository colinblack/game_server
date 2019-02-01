/*
 * TcpChannel.h
 *
 *  Created on: 2012-2-10
 *      Author: dada
 */

#ifndef TCPCHANNEL_H_
#define TCPCHANNEL_H_

#include "Common.h"

class CTcpServer;
class CInternetAddress
{
public:
	string IP;
	uint16_t Port;
	CInternetAddress();
	CInternetAddress(const char *ip, uint16_t port);
	CInternetAddress &operator =(const CInternetAddress &address);
	void Clear();
	bool FromString(const string &sAddress);
	bool FromSockAddr(const void *pSockAddr);
	string ToString() const;
};

#define TCP_CHANNEL_BUFFER_SIZE 0x80000

class CTcpChannel
{
public:
	CTcpChannel();
	~CTcpChannel();
	int GetChannelId();
	bool CreateServer(int channelId, const CInternetAddress &listenAddress);
	bool CreateClient(int channelId, const CInternetAddress &serverAddress, const CInternetAddress *bindAddress = NULL);
	bool Accept(int channelId, CTcpChannel &listenChannel);
	bool SendData(const IBuffer *pBuffer = NULL);
	bool RealSend();
	bool ReceiveData();
	IBuffer *GetReceiveData();
	bool SetDataRead(uint32_t byteRead);	//设置接收数据已读字节数
	bool Close();
	bool IsClosed() const;
	bool IsActive() const;
	int GetSocket() const;
	int GetLastError() const;
	string ToString() const;
	const CInternetAddress *GetRemoteAddress() const;
	static void SetServer(CTcpServer* pServer);
	bool IsWebSocket(){return m_bWebSocket;}
private:
	int m_channelId;
	CSocket m_socket;
	unsigned m_lastActiveTime;
	bool m_isFirst;
	bool m_bWebSocket;
	CInternetAddress m_localAddress;
	CInternetAddress m_remoteAddress;
	//CStaticBuffer<TCP_CHANNEL_BUFFER_SIZE> m_sendBuffer;
	//CStaticBuffer<TCP_CHANNEL_BUFFER_SIZE> m_recvBuffer;
	CDanymicBuffer<TCP_CHANNEL_BUFFER_SIZE> m_sendBuffer;
	CDanymicBuffer<TCP_CHANNEL_BUFFER_SIZE> m_recvBuffer;
	static byte m_Sbuffer[TCP_CHANNEL_BUFFER_SIZE];
	static CTcpServer* m_pServer;
};

#endif /* TCPCHANNEL_H_ */
