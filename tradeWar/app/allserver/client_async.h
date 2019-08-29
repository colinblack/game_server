#ifndef _RANK_CLIENT_ASYNC_H_
#define _RANK_CLIENT_ASYNC_H_

#include <string>
#include "poller.h"
#include "poll_thread.h"
#include "Kernel.h"
using namespace std;

#define CLIENT_BUFF_LEN 102400
#define OUT_BUFF_LEN 	512000

class AsrvClientAsync: public CPollerObject {
public:
	AsrvClientAsync(CPollThread *o, int fd);
	virtual ~AsrvClientAsync();
	int Attach();
	virtual void InputNotify(void);
	virtual void OutputNotify(void);
	virtual void HangupNotify(void);
public:
	bool sendData(IBuffer* pData);
	uint32_t getIp() {
		return m_peerIp;
	}
private:
	void errorProcess(int src);
	void recvProcess();
	bool packetProcess(IBuffer* pBuff);
	void onClientClose();
private:
	char m_peerAddr[20];
	uint16_t m_peerPort;
	uint32_t m_peerIp;
	uint32_t m_time;
	CDynamicBuffer<OUT_BUFF_LEN> m_outBuf;
	CStaticBuffer<CLIENT_BUFF_LEN> m_inBuf;
	enum SRC {
		SRC_INPUT, SRC_OUTPUT, SRC_HANGUP
	};
};

#endif

