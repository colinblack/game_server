#ifndef __SERVER_ASYNC_H__
#define __SERVER_ASYNC_H__

#include "Kernel.h"

#define DB_OUT_BUFF_LEN 512000
#define DB_IN_BUFF_LEN 512000

class CServerAsync: public CPollerObject {
public:
	enum SERVER_ASYNC_TYPE {
		SERVER_ASYNC_DB_WRITE = 1,
		SERVER_ASYNC_ALL_SERVER = 2,
		SERVER_ASYNC_TRANSIT = 3,
		SERVER_ASYNC_LOGIN = 4
	};
	CServerAsync(CPollThread *o, uint32_t type, uint32_t sid);
	virtual ~CServerAsync();
	int Attach();
	virtual void InputNotify(void);
	virtual void OutputNotify(void);
	virtual void HangupNotify(void);
	bool sendData(IBuffer* pData);
	bool clientClose(uint32_t fd, uint32_t time, uint32_t microTime, uint32_t ip);
	bool init();
	bool connectServer();
private:
	int connectingProcess(int src);
	int errorProcess(int src);
	void recvProcess();
	void packetProcess(IBuffer* pBuff);
	void onConnected();
	void onClientClose();
private:
	char m_addr[20];
	uint16_t m_port;
	int32_t m_stat;
	uint32_t m_sid;
	uint32_t m_type;
	bool m_init;
	CDynamicBuffer<DB_OUT_BUFF_LEN> m_outBuf;
	CStaticBuffer<DB_IN_BUFF_LEN> m_inBuf;
	enum STAT {
		IDLE, CONNECTING, CONNECTED
	};
	enum SRC {
		SRC_INPUT, SRC_OUTPUT, SRC_HANGUP
	};

};

#endif

