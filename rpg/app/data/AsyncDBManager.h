#ifndef _ASYNC_DB_MANAGER_H_
#define _ASYNC_DB_MANAGER_H_

#include "Kernel.h"

class AsyncDBInterfaceBase;
class AsyncDBManager {
public:
	static AsyncDBManager* getInstance() {
		static AsyncDBManager adm;
		return &adm;
	}
private:
	AsyncDBManager();
public:
	bool init(CTcpServer* pServer);
	bool initThread();
	bool send(DataPacket& packet);
	bool push(const DataPacket& packet);
	bool get(DataPacket& packet);
	int onSecondTimer();
	AsyncDBInterfaceBase* getProcessor(uint32_t tableId) {
		map<uint32_t, AsyncDBInterfaceBase*>::iterator it = m_tables.find(tableId);
		return it == m_tables.end() ? NULL : it->second;
	}
private:
	bool startAsynThread();
private:
	list<DataPacket> m_packets;
	ThreadMutex m_mutex;
	map<uint32_t, AsyncDBInterfaceBase*> m_tables;
	CTcpChannel* m_channel;
	CTcpServer* m_server;
};

#endif
