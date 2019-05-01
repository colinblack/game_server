#ifndef __WX_BATTLE__ASYNC_H__
#define __WX_BATTLE__ASYNC_H__

#include "poller.h"
#include "poll_thread.h"
#include "uvlog.h"
#include "comm.h"
#include <string>

using namespace std;

class CBattleAsync : public CPollerObject
{
public:
	CBattleAsync(CPollThread *o, uint32_t spanId, uint32_t srvId);
	virtual ~CBattleAsync ();

	int Attach();

	virtual void InputNotify (void);
	virtual void OutputNotify (void);
	virtual void HangupNotify(void);

	bool sendData(const string& data);
	bool clientClose(uint32_t fd,uint32_t time,uint32_t microTime,uint32_t ip);
private:
	int init();
	int connectingProcess(int src);
	int errorProcess(int src);
	bool parseAddress();
	void recvProcess();
	void packetProcess();
	void onConnected();
private:
	char m_addr[20];
	uint16_t m_port;
	bool m_isConnected;
	int m_stat;
	uint32_t m_bodyLen;
	uint32_t m_spanId;
	uint32_t m_srvId;
	string m_outBuf;
	string m_inBuf;

	enum STAT {IDLE,CONNECTING,CONNECTED};
	enum SRC {SRC_INPUT,SRC_OUTPUT,SRC_HANGUP};
};


#endif

