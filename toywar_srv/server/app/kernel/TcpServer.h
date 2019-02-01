/*
 * TcpServer.h
 *
 *  Created on: 2012-2-9
 *      Author: dada
 */

#ifndef TCPSERVER_H_
#define TCPSERVER_H_

#include "Kernel.h"

#define TCP_SERVER_MAX_CONNECTIONS 4000

class IServer : public IBase
{
public:
	virtual bool Run() = 0;
	virtual bool Close() = 0;
	virtual bool CloseChannel(int channelId) = 0;
	virtual bool SendData(CPacket *pHead, IPacketSend *pBody) = 0;
	virtual void OnChannelReceive(CTcpChannel *pChannel) = 0;
	virtual void OnReceive(CPacket *pPacket) {}
	virtual void OnConnect(CTcpChannel *pChannel) {}
	virtual void OnChannelClose(CTcpChannel *pChannel) {}
	virtual void OnIdle() {}
};

class CTcpServer : public IServer
{
public:
	CTcpServer();
	~CTcpServer();
	bool Initialize(const vector<CInternetAddress> &listenList, int maxConn = TCP_SERVER_MAX_CONNECTIONS);
	virtual bool Run();
	virtual bool Close();
	virtual bool CloseChannel(int channelId);
	virtual bool SendData(CPacket *pHead, IPacketSend *pBody);
	virtual void OnChannelReceive(CTcpChannel *pChannel);
	const CTcpChannel *GetChannel(int channelId) ;
	bool EnableOutput(CTcpChannel *pChannel,bool flag=true);
	CTcpChannel* GetSelfClientChannel();
protected:
	int GetFreeChannelId();
private:
	bool m_bRunning;
	vector<CInternetAddress> m_listenList;
	int m_listenCount;
	int m_maxConn;
	map<int,CTcpChannel*> m_pChannels;
	set<int> m_pFreeChannels;
	int m_lastNew;
	int m_lastFreeChannelId;
	int m_fdEpoll;
};

#endif /* TCPSERVER_H_ */
