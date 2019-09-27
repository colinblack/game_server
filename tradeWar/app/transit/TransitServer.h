/*
 * TransitServer.h
 *
 *  Created on: 2016-3-15
 *      Author: Administrator
 */

#ifndef TRANSITSERVER_H_
#define TRANSITSERVER_H_

#include "Kernel.h"
#include "listener.h"
#include "ProtocolInc.h"
#include "ServerAsync.h"

class TencentPacket;
class TransitAsync;
class TencentAsync;

class TransitServer: public CPollThread {
public:
	static TransitServer * getInstance() {
		static TransitServer transitServer;
		return &transitServer;
	}
	~TransitServer();
	static bool IsClosed;
private:
	TransitServer();
public:
	bool init();
	bool onExist();
	virtual void onIdle();
	static bool initDaemon();
	bool addLoginPacket(CNetPacket* packet);
	bool addSendLoginPacket(CNetPacket* packet);
	bool addTencentPacket(TencentPacket* packet);
	void getLoginPacket();
	void getTencentPacket();
	CNetPacket* getSendLoginPacket();
private:
	bool listenInit();
	bool threadInit();
	static void* processLoginFunc(void* arg);
	static void* processTencentFunc(void* arg);
	static void* processC6Func(void* arg);
private:
	CListener<TransitAsync> *m_pListener;	//本地端口监听
	CListener<TencentAsync> *m_pTencenter;  //腾讯端口监听

	ThreadMutex m_recvLoginMutex;
	ThreadCond m_recvLoginCond;
	list<CNetPacket*> m_recvLoginQueue;	// login包

	ThreadMutex m_sendLoginMutex;
	list<CNetPacket*> m_sendLoginQueue;	// login包

	ThreadMutex m_recvTencentMutex;
	ThreadCond m_recvTencentCond;
	list<TencentPacket*> m_recvTencentQueue;	// tencent包, 改为接入C6平台


	map<uint32_t, CServerAsync*> m_battles;
};

#endif /* TRANSITSERVER_H_ */
