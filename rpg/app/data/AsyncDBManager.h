#ifndef _ASYNC_DB_MANAGER_H_
#define _ASYNC_DB_MANAGER_H_

#include "Kernel.h"

class AsyncDBInterfaceBase;
class AsyncDBManager: public CSingleton<AsyncDBManager> {
private:
	friend class CSingleton<AsyncDBManager>;
	AsyncDBManager();

public:
	bool init(CTcpServer* pServer);
	bool initThread();
	bool send(DataPacket& packet);
	bool push(const DataPacket& packet);
	bool pop();
	bool onExit();
	bool onSecondTimer();
	AsyncDBInterfaceBase* getProcessor(uint32_t tableId);

protected:
	bool startAsynThread();

private:
	list<DataPacket> m_packets;
	ThreadMutex m_mutex;
	ThreadCond m_recvCond;
	map<uint32_t, AsyncDBInterfaceBase*> m_tables;
	CTcpChannel* m_channel;
	CTcpServer* m_server;
};

#endif
