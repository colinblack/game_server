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
//#include <cache_process.h>
#include "uvlog.h"
#include "utils.h"


//#define STRDUP(x)	strdup(x)
//#define FREE_IF(x)	do { if((x) != 0) free((void *)(x)); } while(0)

volatile extern int stop;

static inline int64_t GET_TIMESTAMP(void) {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (int64_t)tv.tv_sec * 1000000 + tv.tv_usec;
}

void *CPollThread::PollThreadEntry (void *thread)
{
	return (void*)((CPollThread*)thread)->ThreadLoop ();
}

CPollThread::CPollThread (const char *name, int mp) :
	CPollerUnit(mp)
{
	taskname = STRDUP(name);
	timeout = 2000;
	stacksize = 0;

	stopped = 0;
	stopPtr = &stopped;

	pthread_mutex_init (&runlock, NULL);
}

CPollThread::~CPollThread ()
{
	pthread_mutex_destroy (&runlock);
	FREE_IF(taskname);
}

void CPollThread::SetStackSize(int size)
{
	if(size < 0)	// default size
		size = 0;
	else if(size > 64<<20) // max 64M
		size = 64<<20;

	// round to 64K
	if((size & 0xFFFF) != 0)
		size = (size & ~0xFFFF) + 0x10000;
	stacksize = size;
}

int CPollThread::InitializeThread (int inSubThread)
{
	if(InitializePollerUnit() < 0)
		return -1;

	if (inSubThread)
	{
		subThread = 1;
		pthread_mutex_lock (&runlock);
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		if(stacksize)
			pthread_attr_setstacksize(&attr, stacksize);
		pthread_create (&tid, &attr, PollThreadEntry, this);
	}
	else
	{
		subThread = 0;
		tid = pthread_self ();
	}	

	return 0;
}

void CPollThread::RunningThread ()
{
	if (subThread)
	{
		pthread_mutex_unlock (&runlock);
	}
	else
	{
		stopPtr = &stop;
		ThreadLoop();
	}
}

int CPollThread::ThreadLoop (void)
{
	//char name[32];
	//snprintf(name, sizeof(name), "%s[%d]", taskname, gettid());
	//set_log_thread_name(name);

	sigset_t sset;
	sigemptyset(&sset);
	sigaddset(&sset, SIGTERM);
	pthread_sigmask(SIG_BLOCK, &sset, &sset);

	pthread_mutex_lock (&runlock);

	while (!*stopPtr)
	{
		WaitPollerEvents(1);
		//uint64_t now = GET_TIMESTAMP();

		if (*stopPtr)
			break;

		ProcessPollerEvents();
		//CheckExpired(now);
		//CheckReady();
	}
	Cleanup();

	return 0;
}

void CPollThread::interrupt (void)
{
    if(this==NULL)
			return;

    int ret;
    stopped = 1;
    
    if (subThread)
    {
        pthread_kill (tid, SIGINT);
        pthread_mutex_unlock (&runlock);

        if ((ret=pthread_join(tid, 0)) != 0)
        {
            LOG_WARNING("Thread [%s] join failed %d.", Name(), ret);
        } else {
            LOG_INFO("Thread [%s] stopped.", Name());
        }
    }
}

void CPollThread::Cleanup (void)
{
}
