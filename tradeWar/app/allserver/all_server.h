/*
 * AsrvServer.h
 *
 *  Created on: 2018年9月26日
 *      Author: Administrator
 */

#ifndef _RANK_SERVER_H_
#define _RANK_SERVER_H_

#include "Kernel.h"
#include "poll_thread.h"
#include "listener.h"
#include "ServerAsync.h"
#include "TimerThread.h"

class CNetPacket;
class AsrvClientAsync;

class AsrvServer: public CPollThread {
public:
	static bool IsClosed;
	static AsrvServer* getInstance() {
		static AsrvServer _ins;
		return &_ins;
	}
	virtual ~AsrvServer();
	virtual void onIdle();
	virtual bool addPacket(IBuffer* pBuff);
	bool onExit();
	bool doInit();
	bool doInitTimer();
	bool doPacket(CNetPacket *p);
	bool addRecvPacket(CNetPacket *p);
	bool getRecvPacket();
	bool addSendPacket(CNetPacket *p);
	CNetPacket* getSendPacket();
	bool sendToLogin(CNetPacket *p);
protected:
	AsrvServer();
	bool doTimer(CNetPacket *p);
	bool doTransfer(CNetPacket *p);
private:
	ThreadCond m_recvCond;
	ThreadMutex m_recvMutex;
	list<CNetPacket*> m_recvQueue;

	ThreadMutex m_sendMutex;
	list<CNetPacket*> m_sendQueue;

	CListener<AsrvClientAsync> *m_pListener;

	map<uint32_t, CServerAsync*> m_battles;

	CTimerThread *m_timer;
};

#endif /* _RANK_SERVER_H_ */
