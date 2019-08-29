/*
 * TencentAsync.h
 *
 *  Created on: 2016-3-15
 *      Author: Administrator
 */

#ifndef TENCENTASYNC_H_
#define TENCENTASYNC_H_

#include "poller.h"
#include "poll_thread.h"
#include "Kernel.h"

#define CLIENT_BUFF_LEN 102400
#define OUT_BUFF_LEN 	512000


class TencentAsync : public CPollerObject
{
public:
	TencentAsync(CPollThread *o, int fd);
	virtual ~TencentAsync ();

	int Attach();

	virtual void InputNotify (void);
	virtual void OutputNotify (void);
	virtual void HangupNotify(void);
public:
	uint32_t getIp(){return m_peerIp;}
	uint32_t getFd(){ return netfd;}
	bool sendData(IBuffer* pData);
private:
	int errorProcess(int src);
	void recvProcess();
	bool packetProcess();
	void onClientClose();
private:
	char m_peerAddr[20];
	uint16_t m_peerPort;
	uint32_t m_peerIp;
	uint32_t m_time;

	CDynamicBuffer<OUT_BUFF_LEN> m_outBuf;
	CStaticBuffer<CLIENT_BUFF_LEN> m_inBuf;

	enum SRC {SRC_INPUT,SRC_OUTPUT,SRC_HANGUP};
};


#endif /* TENCENTASYNC_H_ */
