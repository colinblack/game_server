
#include "ThreadMutex.h"


// class Thread_Mutex
ThreadMutex::ThreadMutex()
{
	pthread_mutex_init(&m_thread_mutex, NULL);
}

ThreadMutex::~ThreadMutex()
{
	pthread_mutex_destroy(&m_thread_mutex);

}

int ThreadMutex::acquire()
{
	int rc = pthread_mutex_lock(&m_thread_mutex);
	if (0 != rc) {
		return -1;
	}
	return 0;
}

int ThreadMutex::release()
{
	int rc = pthread_mutex_unlock(&m_thread_mutex);
	if (0 != rc) {
		return -1;
	}
	return 0;
}

pthread_mutex_t* ThreadMutex::getMutex() {
	return &m_thread_mutex;
}


// class Thread_Mutex_Guard
ThreadMutexGuard::ThreadMutexGuard(ThreadMutex* mutex) : m_mutex(mutex)
{
	m_mutex->acquire();
}

ThreadMutexGuard::~ThreadMutexGuard()
{
	m_mutex->release();
}


ThreadCond::ThreadCond() {
	pthread_cond_init(&m_thread_cond, NULL);
}

ThreadCond::~ThreadCond() {
	pthread_cond_destroy(&m_thread_cond);
}

int ThreadCond::Signal() {
	return pthread_cond_signal(&m_thread_cond);
}

int ThreadCond::Broadcast() {
	return pthread_cond_broadcast(&m_thread_cond);
}

int ThreadCond::Wait(pthread_mutex_t* mut) {
	if (mut == NULL) {
		return 1;
	}
	return pthread_cond_wait(&m_thread_cond, mut);
}

