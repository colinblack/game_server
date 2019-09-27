/*
 * LoginServer.h
 *
 *  Created on: 2015-8-28
 *      Author: Administrator
 */

#ifndef LOGINSERVER_H_
#define LOGINSERVER_H_

#include "Kernel.h"
#include "listener.h"
#include "LoginClientAsync.h"
#include "ProtocolInc.h"
#include "BattleManager.h"
#include "TimerThread.h"

struct LogPacketItem {
	uint32_t uid;
	uint32_t fd;
	uint32_t mts;
	uint32_t span;
	uint16_t ptype;
	byte cmd;
	byte subCmd;

	LogPacketItem() : uid(0), fd(0), mts(0), span(0), ptype(0), cmd(0), subCmd(0) {
	}
};

class CServerAsync;
class LoginServer: public CPollThread {
public:
	static LoginServer* getInstance() {
		static LoginServer loginServer;
		return &loginServer;
	}
	~LoginServer();
	static bool IsClosed;
	static bool IsReLoad;
private:
	LoginServer();
public:
	bool init();
	void setAccessChannel(CLoginClientAsync* pChannel) {
		m_accessChannel = pChannel;
	}
	CLoginClientAsync *getAccessChannel() {
		return m_accessChannel;
	}
	bool sendData(CNetPacket *packet);
	bool addPacket(IBuffer *pBuff);
	CNetPacket* getPacket();
	virtual void onIdle();
	virtual void onExit();
	bool addRecvPacket(CNetPacket *packet);
	CNetPacket* getSendPacket();
	uint64_t getBattleId(CNetPacket *packet);
	static bool initDaemon();
	void setLogTs(uint32_t ts) {
		m_logTs = ts;
	}
	uint32_t getLogTs() const {
		return m_logTs;
	}
	bool removeLogPacketItem(LogPacketItem& item);
	bool printStat();
	void doLogic();
	void logStat(CNetPacket *packet);
	void addAdmin(int fd, CLoginClientAsync *c) {
		m_admins[fd] = c;
	}
	void delAdmin(int fd) {
		if (m_admins.count(fd)) {
			m_admins.erase(fd);
		}
	}
private:
	bool listenInit();
	bool timerInit();
	bool asyncDBInit();
	bool asyncAllServerInit();
	bool asyncTransitInit();
private:
	CListener<CLoginClientAsync>* m_pListener;
	CLoginClientAsync* m_accessChannel;
	CServerAsync* m_dbChannel;
	CServerAsync* m_allServerChannel;
	CServerAsync* m_transitChannel;

	list<CNetPacket*> m_recvHighQueue;
	list<CNetPacket*> m_recvLowQueue;	//接受低优先级队列，登录请求放在这个队列里处理
	list<CNetPacket*> m_sendQueue;

	ThreadMutex m_recvMutex;		//接收队列锁
	ThreadCond  m_recvCond;
	ThreadMutex m_sendMutex;		//发送队列锁

	uint32_t m_logTs;				//日志时间戳
	uint32_t m_recvCount;
	uint32_t m_hSize;
	uint32_t m_lSize;
	uint32_t m_sendSize;

	LogPacketItem logItem;
	list<LogPacketItem> logItemList;

	map<uint32_t, CServerAsync*> m_battles;

	map<uint32_t, CLoginClientAsync*> m_admins;

	CTimerThread *m_timer;

	string m_addr;

	uint16_t m_port;
};

#endif /* LOGINSERVER_H_ */
