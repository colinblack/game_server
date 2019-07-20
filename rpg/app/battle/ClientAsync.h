#ifndef _CLIENT_ASYNC_H_
#define _CLIENT_ASYNC_H_

#include "Poller.h"
#include "PollThread.h"
#include <string>
#include "FirePacket.h"
#include "TcpChannel.h"

using namespace std;

#define WS_HEAD_FLAG   2
#define WS_LITTLE_HEAD 6
#define WS_MIDDLE_HEAD 8
#define WS_LARGE_HEAD  14

class ClientAsync: public CPollerObject {
public:
	ClientAsync(CPollThread *o, int fd);
	virtual ~ClientAsync();
	int Attach();
	virtual void InputNotify(void);
	virtual void OutputNotify(void);
	virtual void HangupNotify(void);
public:
	bool sendData(const string& data);
	bool onBattleMsg(CFirePacket *pPacket);
	bool battleClose();
	uint32_t getFd() {
		return netfd;
	}
	uint32_t getTime() {
		return m_time;
	}
	uint32_t getMicrotime() {
		return m_microTime;
	}
	const char* getRemoteIp() {
		return m_peerAddr;
	}
	uint32_t getIp() {
		return m_peerIp;
	}
private:
	void errorProcess(int src);
	void startProcess();
	void recvProcess();
	bool decodeProcess();
	void onWsEncode(const string &data, string &result);
	bool getWsHeadLen();
	bool getWsBodyLen();
	bool getWsBodyData();
	bool recvWsBuffer(int len);
	void onWsError(int ret);
	void onHttpHead();
private:
	char m_peerAddr[20];
	uint8_t m_cSeq;
	uint8_t m_sSeq;
	uint16_t m_peerPort;
	uint32_t m_peerIp;
	uint32_t m_time;
	uint32_t m_microTime;
	uint32_t m_stat;
	string m_sendBuf;
	string m_recvBuf;

	//ws
	uint16_t m_wsHeadLen;
	uint64_t m_wsBodyLen;
	uint8_t m_wsDataLen;
	string m_wsInBuf;
	bool m_isHttp;
	bool m_bWebSocket;

	enum STAT {
		CONN_START, CONN_COMPLETE
	};
	enum SRC {
		SRC_INPUT, SRC_OUTPUT, SRC_HANGUP
	};
	enum WS_ERR_CODE {
		WS_ERR_HEADLEN = 10, WS_ERR_BODYLEN = 11, WS_ERR_BODYDATA = 12
	};
};

#endif /* _CLIENT_ASYNC_H_ */

