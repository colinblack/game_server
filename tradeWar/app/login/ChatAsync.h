/*
 * ChatAsync.h
 *
 *  Created on: 2016年4月28日
 *      Author: aaron
 *        Desc:聊天
 */

#ifndef CHATASYNC_H_
#define CHATASYNC_H_
#include "Kernel.h"

#define DB_OUT_BUFF_LEN 	512000
#define DB_IN_BUFF_LEN 	512000

class CChatAsync: public CPollerObject
{
public:
	CChatAsync(CPollThread *o);
	virtual ~CChatAsync ();

	int Attach();

	virtual void InputNotify (void);
	virtual void OutputNotify (void);
	virtual void HangupNotify(void);

	bool sendData(IBuffer* pData);
	bool clientClose(uint32_t fd,uint32_t time,uint32_t microTime,uint32_t ip);
	bool init();
private:
	int connectingProcess(int src);
	int errorProcess(int src);
	bool parseAddress();
	void recvProcess();
	void packetProcess(IBuffer* pBuff);
	void onConnected();
	void onClientClose();
private:
	char m_addr[20];
	uint16_t m_port;
	int m_stat;
	CDynamicBuffer<DB_OUT_BUFF_LEN> m_outBuf;
	CStaticBuffer<DB_IN_BUFF_LEN> m_inBuf;
	enum STAT {IDLE,CONNECTING,CONNECTED};
	enum SRC {SRC_INPUT,SRC_OUTPUT,SRC_HANGUP};
};

#endif /* CHATASYNC_H_ */
