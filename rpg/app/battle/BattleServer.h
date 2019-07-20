#ifndef _BATTLE_SERVER_H_
#define _BATTLE_SERVER_H_

#include "BattleBaseInc.h"

class BattleServer: public CTcpServer, public CSingleton<BattleServer> {
private:
	friend class CSingleton<BattleServer> ;
	BattleServer();
	virtual ~BattleServer();

	list<CFirePacket*> sendQueue;
	list<CFirePacket*> recvQueue;
	ThreadMutex m_recvMutex;		//接收队列锁
	ThreadMutex m_sendMutex;		//发送队列锁

public:
	bool Initialize();
	virtual void OnReceive(CFirePacket *pPacket);
	virtual void OnChannelClose(CTcpChannel *pChannel);
	virtual void OnIdle();
	virtual void onExit();
	virtual void OnConnect(CTcpChannel *pChannel);
	bool AddRecv(CFirePacket *pPacket);
	bool AddSend(CFirePacket *pPacket);
	CFirePacket* GetSend();
};

#endif
