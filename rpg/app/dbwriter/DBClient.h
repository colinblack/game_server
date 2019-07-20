#ifndef DB_CLIENT_H_
#define DB_CLIENT_H_

#include "Poller.h"
#include "PollThread.h"
#include "Kernel.h"
#include <string>

using namespace std;

#define CLIENT_BUFF_LEN 102400

class CDBClientAsync: public CPollerObject {
public:
	CDBClientAsync(CPollThread *o, int fd);
	virtual ~CDBClientAsync();
	int Attach();
	virtual void InputNotify(void);
	virtual void OutputNotify(void);
	virtual void HangupNotify(void);
	bool sendData(IBuffer* pData);
	uint32_t getFd() {
		return netfd;
	}
private:
	int errorProcess(int src);
	void recvProcess();
private:
	char m_peerAddr[20];
	uint16_t m_peerPort;
	uint32_t m_peerIp;
	CStaticBuffer<CLIENT_BUFF_LEN> m_inBuf;
	enum SRC {
		SRC_INPUT, SRC_OUTPUT, SRC_HANGUP
	};
};

#endif /* DB_CLIENT_H_ */

