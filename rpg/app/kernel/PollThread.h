#ifndef __POLLTHREAD_H__
#define __POLLTHREAD_H__

#include <stdint.h>
#include <pthread.h>
#include <signal.h>
#include <sys/types.h>
#include <linux/unistd.h>

#include "Poller.h"

class CPollThread: public CPollerUnit {
public:
	CPollThread(const char *name, int mp);
	virtual ~CPollThread();
	int InitializeThread(int inSubThread);
	void RunningThread();
	const char *Name(void) {
		return taskname;
	}
	void SetStackSize(int);
	void interrupt(void);
	virtual void onIdle();

protected:
	char *taskname;
	pthread_t tid;
	pthread_mutex_t runlock;
	int stopped;
	volatile int *stopPtr;
	int subThread;
	int timeout;
	int stacksize;

private:
	int ThreadLoop(void);
	virtual void Cleanup(void);
	static void *PollThreadEntry(void *thread);
};

#endif
