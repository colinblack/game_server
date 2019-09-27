#ifndef __WX_CLIENT__ASYNC_H__
#define __WX_CLIENT__ASYNC_H__

#include "poller.h"
#include "poll_thread.h"
#include "uvlog.h"
#include "Kernel.h"
#include <string>

using namespace std;

#define CLIENT_BUFF_LEN 102400
#define OUT_BUFF_LEN 	512000

class CDBClientAsync: public CPollerObject
{
public:
	CDBClientAsync(CPollThread *o, int fd);
	virtual ~CDBClientAsync();

	int Attach();

	virtual void InputNotify(void);
	virtual void OutputNotify(void);
	virtual void HangupNotify(void);
public:
	bool sendData(IBuffer* pData);
	uint32_t getFd()
	{
		return netfd;
	}
	const char* getRemoteIp()
	{
		return m_peerAddr;
	}
private:
	int errorProcess(int src);
	void recvProcess();
	bool packetProcess(IBuffer* pBuff);
	void onClientClose();
	bool packetFormat(const string& in, string& out);
private:
	char m_peerAddr[20];
	uint16_t m_peerPort;
	uint32_t m_peerIp;
	uint16_t m_bodyLen;

	CDynamicBuffer<OUT_BUFF_LEN> m_outBuf;
	CStaticBuffer<CLIENT_BUFF_LEN> m_inBuf;

	enum SRC
	{
		SRC_INPUT,
		SRC_OUTPUT,
		SRC_HANGUP
	};
};

#endif

