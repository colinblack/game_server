/*
 * FireChannel.h
 *
 * Created on: 2013-01-31
 * Author: rein
 */

#ifndef FIRECHANNEL_H_
#define FIRECHANNEL_H_

#include "Common.h"

class CFireServer;
class CInternetFireAddress
{
public:
	string IP;
	uint16_t Port;
	CInternetFireAddress();
	CInternetFireAddress(const char *ip, uint16_t port);
	CInternetFireAddress &operator =(const CInternetFireAddress &address);
	void Clear();
	bool FromString(const string &sAddress);
	bool FromSockAddr(const void *pSockAddr);
	string ToString() const;
};

#define TCP_CHANNEL_BUFFER_SIZE 0x8000000

class CFireChannel
{
public:
	CFireChannel();
	~CFireChannel();
	int GetChannelId();
	bool CreateServer(int channelId, const CInternetFireAddress &listenAddress);
	bool CreateClient(int channelId, const CInternetFireAddress &serverAddress, const CInternetFireAddress *bindAddress = NULL);
	bool Accept(int channelId, CFireChannel &listenChannel);
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
	int Verification();
	unsigned Update(const byte* buffer, unsigned bufferLen, unsigned arg2=0, unsigned arg3=0);
	unsigned Encode(byte* buffer, int length, unsigned para2=0, unsigned para3=0);
	void MakeKey();
	bool SetChannelUid(unsigned uid);
	unsigned GetChannelUid(void);
	const CInternetFireAddress *GetRemoteAddress() const;
	static void SetServer(CFireServer* pServer);
private:
	int m_channelId;
	unsigned m_uid;
	CSocket m_socket;
	unsigned m_lastActiveTime;
	CInternetFireAddress m_localAddress;
	CInternetFireAddress m_remoteAddress;
	CStaticBuffer<TCP_CHANNEL_BUFFER_SIZE> m_sendBuffer;
	CStaticBuffer<TCP_CHANNEL_BUFFER_SIZE> m_recvBuffer;
	static CFireServer* m_pServer;
	int m_verification;
	unsigned m_SelfSalt;
	unsigned m_TargetSalt;
	unsigned m_keyBuff[4];
};

#endif /* FIRECHANNEL_H_ */
