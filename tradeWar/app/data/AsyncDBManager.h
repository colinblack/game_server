#ifndef _ASYNC_DB_MANAGER_H_
#define _ASYNC_DB_MANAGER_H_

#include "Kernel.h"

#define MAX_DB_PACKET_SIZE 0x8000

/**
 *	CNetPacket.fd 代表操作哪张表
 *	CNetPacket.stime 代表操作类型
 */
#include "NetPacket.h"
class AsyncDBInterface;
class AsyncDBManager {
public:
	static AsyncDBManager* getInstance() {
		static AsyncDBManager adm;
		return &adm;
	}
private:
	AsyncDBManager();
public:
	bool initThread();
	bool doPacket(CNetPacket* packet);
	bool doWrite(CNetPacket* packet);
	bool doProbe(CNetPacket* packet);
	bool send(CNetPacket* packet);
	bool push(const CNetPacket& packet);
	bool getPacket();
	bool sendData(CNetPacket& packet);
	bool getSendPacket(CNetPacket& packet);
	bool addEncodedPacket(CNetPacket* packet);
	bool getEncodedPacket(list<CNetPacket*>& epList);
	AsyncDBInterface* getProcessor(uint32_t tableId) {
		map<uint32_t, AsyncDBInterface*>::iterator it = m_tables.find(tableId);
		return it == m_tables.end() ? NULL : it->second;
	}
	bool printStat();
private:
	bool startAsynThread();
private:
	list<CNetPacket> m_packets;
	ThreadMutex m_mutex; // 接收队列锁
	ThreadCond m_cond;
	list<CNetPacket> m_sendQueue;
	ThreadMutex m_sendMutex; // 发送队列锁
	map<uint32_t, AsyncDBInterface*> m_tables;
	ThreadMutex m_eplMutex;	// 已经编码完成待发送的包队列锁
	list<CNetPacket*> m_encodedPacketList; // 已经编码完成待发送的包队列
	map<uint32_t, uint32_t> m_stat;	// 统计包的收发量
};

#endif
