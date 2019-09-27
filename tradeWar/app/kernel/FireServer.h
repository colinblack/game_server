/*
 * FireServer.h
 *
 * Created on: 2013-01-31
 * Author: rein
 */

#ifndef FIRESERVER_H_
#define FIRESERVER_H_

#include "Kernel.h"

class IFireServer : public IBase
{
public:
	virtual bool Run() = 0;
	virtual bool Close() = 0;
	virtual bool CloseChannel(int channelId) = 0;
	virtual bool SendData(CFirePacket *pHead, IPacketSend *pBody) = 0;
	virtual void OnChannelReceive(CFireChannel *pChannel) = 0;
	virtual void OnReceive(CFirePacket *pPacket) {}
	virtual void OnConnect(CFireChannel *pChannel) {}
	virtual void OnChannelClose(CFireChannel *pChannel) {}
	virtual void OnIdle() {}
};

#define TCP_SERVER_MAX_CONNECTIONS 4000

class CFireServer : public IFireServer
{
public:
	CFireServer();
	~CFireServer();
	bool Initialize(const vector<CInternetFireAddress> &listenList, int maxConn = TCP_SERVER_MAX_CONNECTIONS);
	virtual bool Run();
	virtual bool Close();
	virtual bool CloseChannel(int channelId);
	virtual bool SendData(CFirePacket *pHead, IPacketSend *pBody);
	virtual void OnChannelReceive(CFireChannel *pChannel);
	const CFireChannel *GetChannel(int channelId) const;
	bool EnableOutput(CFireChannel *pChannel,bool flag=true);
protected:
	int GetFreeChannelId();
private:
	bool m_bRunning;
	vector<CInternetFireAddress> m_listenList;
	int m_listenCount;
	int m_maxConn;
	CFireChannel *m_pChannels;
	int m_lastFreeChannelId;
	int m_fdEpoll;
};

#endif /* FIRESERVER_H_ */
