/*
 * TransitAsync.h
 *
 *  Created on: 2016-3-15
 *      Author: Administrator
 */

#ifndef TRANSITASYNC_H_
#define TRANSITASYNC_H_

#include "poller.h"
#include "poll_thread.h"
#include "Kernel.h"

#define CLIENT_BUFF_LEN 102400
#define OUT_BUFF_LEN 	512000


class TransitAsync : public CPollerObject
{
public:
	TransitAsync(CPollThread *o, int fd);
	virtual ~TransitAsync ();

	int Attach();

	virtual void InputNotify (void);
	virtual void OutputNotify (void);
	virtual void HangupNotify(void);
public:
	uint32_t getIp(){return m_peerIp;}
	uint32_t getFd(){ return netfd;}
private:
	int errorProcess(int src);
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

	enum SRC {SRC_INPUT,SRC_OUTPUT,SRC_HANGUP};
};


#endif /* TRANSITASYNC_H_ */
