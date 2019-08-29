#ifndef __WX_CLIENT__ASYNC_H__
#define __WX_CLIENT__ASYNC_H__

#include "poller.h"
#include "poll_thread.h"
#include "uvlog.h"
#include "comm.h"
#include <string>
#include "ProtocolInc.h"

using namespace std;

class CClientAsync: public CPollerObject {
public:
	CClientAsync(CPollThread *o, int fd);
	virtual ~CClientAsync();
	int Attach();
	virtual void InputNotify(void);
	virtual void OutputNotify(void);
	virtual void HangupNotify(void);
public:
	bool sendData(const string& data);
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
	void setSrvId(uint32_t srvId) {
		m_serverId = srvId;
	}
	uint32_t getIp() {
		return m_peerIp;
	}
private:
	void errorProcess(int src);
	void startProcess();
	void recvProcess();
	bool createKeyProcess();
	bool verifyKeyProcess();
	bool statProcess();
	bool decodeProcess();
	bool firstProcess();
	bool packetProcess();
	void onWsEncode(const string &data, string &result);
	void onClientClose();
	bool packetFormat(const string& in, string& out);
	void doStat();
	bool getWsHeadLen();
	bool getWsBodyLen();
	bool getWsBodyData();
	bool recvWsBuffer(int len);
	void onWsError(int ret);
	void onHttpHead();
private:
	char m_peerAddr[20];
	uint16_t m_peerPort;
	uint32_t m_peerIp;
	uint32_t m_time;
	uint32_t m_microTime;
	uint32_t m_stat;
	uint32_t m_clientKey;
	uint32_t m_selfKey;
	uint16_t m_bodyLen;
	uint32_t m_serverId;
	uint32_t m_lastSeq;
	uint64_t m_packetInCount;
	string m_inBuf;
	string m_outBuf;
	string m_recvBuf;
	string m_openid;

	//ws
	uint16_t m_wsHeadLen;
	uint64_t m_wsBodyLen;
	uint8_t m_wsDataLen;
	string m_wsInBuf;
	bool m_isHttp;
	bool m_bWebSocket;

	enum STAT {
		CONN_START, CONN_CREATE_KEY, CONN_VERFY_KEY, CONN_FIRST, CONN_TRANS
	};
	enum SRC {
		SRC_INPUT, SRC_OUTPUT, SRC_HANGUP
	};
	enum WS_ERR_CODE {
		WS_ERR_HEADLEN = 10, WS_ERR_BODYLEN = 11, WS_ERR_BODYDATA = 12
	};
};

#endif

