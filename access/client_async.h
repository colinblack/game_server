#ifndef __WX_CLIENT__ASYNC_H__
#define __WX_CLIENT__ASYNC_H__

#include "poller.h"
#include "poll_thread.h"
#include "uvlog.h"
#include "comm.h"
#include <string>

using namespace std;


class CClientAsync : public CPollerObject
{
public:
	CClientAsync(CPollThread *o, int fd);
	virtual ~CClientAsync ();
	
	int Attach();
	
	virtual void InputNotify (void);
	virtual void OutputNotify (void);
	virtual void HangupNotify(void);
public:
	bool sendData(const string& data, bool en = true);
	bool battleClose();
	uint32_t getFd(){ return netfd;}
	uint32_t getsrvId(){ return m_srvId;}
	uint32_t getTime(){return m_time;}
	uint32_t getMicrotime(){return m_microTime;}
	const char* getRemoteIp(){return m_peerAddr;}
	void setSrvId(uint32_t srvId){m_srvId = srvId;}
	uint32_t getIp(){return m_peerIp;}
private:
	void judgeProcess();
	int parseWebSocket(char* buf, int len);
	void startProcess();
	void keyProcess(char *buf);
	void verifyProcess();
	bool firstProcess();
	int errorProcess(int src);
	void recvProcess();
	void recvProcessRaw();
	void recvProcessWebSocket();
	bool packetProcess();
	void onClientClose();
	bool packetFormat(const string& in,string& out);
private:	
	char m_peerAddr[20];
	uint16_t m_peerPort;
	uint32_t m_peerIp;
	uint32_t m_time;
	uint32_t m_microTime;
	int m_stat;
	uint32_t m_clientKey;
	uint32_t m_selfKey;
	uint32_t m_bodyLen;
	uint32_t m_spanId;
	uint32_t m_srvId;
	uint32_t m_lastSeq;

	string m_outBuf;
	string m_inBuf;

	bool m_bWebSocket;
	char m_mask[4];
	int m_skip, m_l;

	enum STAT {CONN_JUDGE,CONN_START,CONN_VERFY,CONN_FIRST,CONN_TRANS};
	enum SRC {SRC_INPUT,SRC_OUTPUT,SRC_HANGUP};
};


#endif

