/* : set sw=8 ai fdm=marker fmr={,} :*/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <sys/mman.h>
#include <time.h>
#include <sys/time.h>

#include <poll_thread.h>
#include <poller.h>
#include <myepoll.h>
#include <memcheck.h>
#include "commlog.h"

volatile extern int stop;

static inline int64_t GET_TIMESTAMP(void) {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (int64_t) tv.tv_sec * 1000000 + tv.tv_usec;
}

void *CPollThread::PollThreadEntry(void *thread) {
	return (void*) ((CPollThread*) thread)->ThreadLoop();
}

CPollThread::CPollThread(const char *name, int mp) : CPollerUnit(mp) {
	taskname = STRDUP(name);
	timeout = 2000;
	stacksize = 0;
	stopped = 0;
	stopPtr = &stopped;
	subThread = 0;
	pthread_mutex_init(&runlock, NULL);
}

CPollThread::~CPollThread() {
	pthread_mutex_destroy(&runlock);
	FREE_IF(taskname);
}

void CPollThread::SetStackSize(int size) {
	if (size < 0) {	// default size
		size = 0;
	} else if (size > 64 << 20) { // max 64M
		size = 64 << 20;
	}
	if ((size & 0xFFFF) != 0) { // round to 64K
		size = (size & ~0xFFFF) + 0x10000;
	}
	stacksize = size;
}

int CPollThread::InitializeThread(int inSubThread) {
	if (InitializePollerUnit() < 0) {
		return -1;
	}

	if (inSubThread) {
		subThread = 1;
		pthread_mutex_lock(&runlock);
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		if (stacksize) {
			pthread_attr_setstacksize(&attr, stacksize);
		}
		pthread_create(&tid, &attr, PollThreadEntry, this);
	} else {
		subThread = 0;
		tid = pthread_self();
	}

	return 0;
}

void CPollThread::RunningThread() {
	if (subThread) {
		pthread_mutex_unlock(&runlock);
	} else {
		stopPtr = &stop;
		ThreadLoop();
	}
}

int CPollThread::ThreadLoop(void) {
	sigset_t sset;
	sigemptyset(&sset);
	sigaddset(&sset, SIGTERM);
	pthread_sigmask(SIG_BLOCK, &sset, &sset);
	pthread_mutex_lock(&runlock);
	while (!*stopPtr) {
		WaitPollerEvents(1);
		if (*stopPtr) {
			break;
		}
		ProcessPollerEvents();
		onIdle();
	}
	Cleanup();
	return 0;
}

void CPollThread::interrupt(void) {
	if (this == NULL) {
		return;
	}
	int ret = 0;
	stopped = 1;
	if (subThread) {
		pthread_kill(tid, SIGINT);
		pthread_mutex_unlock(&runlock);
		if ((ret = pthread_join(tid, 0)) != 0) {
			warn_log("Thread [%s] join failed %d.", Name(), ret);
		} else {
			info_log("Thread [%s] stopped.", Name());
		}
	}
}

void CPollThread::Cleanup(void) {
}

void CPollThread::onIdle() {
}
