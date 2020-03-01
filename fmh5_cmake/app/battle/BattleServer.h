#ifndef _BATTLE_SERVER_H_
#define _BATTLE_SERVER_H_

#include "ServerInc.h"
#include "TcpServer1.h"
#include <memory>

class BattleServer : public CTcpServer, public CSingleton<BattleServer>
{
private:
	friend class CSingleton<BattleServer>;
	BattleServer(){};
	virtual ~BattleServer()
	{
		pthread_cancel(m_thread);
		pthread_cond_destroy(&m_cond);
	}
public:
	bool Initialize();
	bool InitThread()
	{
		pthread_cond_init(&m_cond, NULL);
		return pthread_create(&m_thread, NULL, BattleServer::_run, NULL) == 0;
	}
	virtual void OnReceive(CFirePacket *pPacket);
	virtual void OnChannelClose(int channelId);
	virtual void OnIdle();
	virtual void onExit(){}
	bool AddSend(CFirePacket* packet);
	bool IsChannelClosed(int channel);
private:
	static void* _run(void* args);
	static CBaseMutex   m_mutex;
	static pthread_t m_thread;
	static pthread_cond_t m_cond;
	static list<CFirePacket*> m_recv, m_send;
	static set<int> m_closed;
};

class BattleServer1 : public CSingleton<BattleServer1> {
public:
    bool Run();
    bool Initialize();

    BattleServer1();
    virtual  ~BattleServer1();

private:
    std::unique_ptr<TcpServer1> pTcpSvr_;
    std::unique_ptr<int> pInt_;
    EventLoop* loop_;
};


#endif
