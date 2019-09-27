/*
 * TimerThread.h
 *
 *  Created on: 2018年11月1日
 *      Author: Administrator
 */

#ifndef _TIMER_THREAD_H_
#define _TIMER_THREAD_H_

#include "Thread.h"

class CTimerThread: public CThread {
public:
	CTimerThread(const char *addr, short port, long usec, long sec);
	virtual ~CTimerThread();
	virtual void Run();
	inline bool IsRun() {
		return GetStatus() == TS_RUNNING;
	}
private:
	char  m_addr[20];
	short m_port;
	long  m_usec;
	long  m_sec;
	int   m_fd;
};

#endif /* _TIMER_THREAD_H_ */
