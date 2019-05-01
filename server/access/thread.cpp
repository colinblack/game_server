#include "thread.h"

#include <pthread.h>

  void* __THREAD_FUNC(void* p)
  {
  	Thread* thread = static_cast<Thread*>(p);
  	thread->Run();
  	thread->alive = false;
  	return NULL;
  }

  Thread::Thread()
  	: hdl(0), alive(false)
  {
  }

  Thread::~Thread()
  {
  	Stop();
  }

  int Thread::Start()
  {
  	
  	if ( alive ) {
  		return -1;
  	}

  	pthread_attr_t attr;
  	if ( pthread_attr_init(&attr) != 0 ) {
  		return -1;
  	}
  	
  	if ( pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE) != 0 ) {
  		return -1;
  	}
  	
  	if (pthread_create(&hdl, &attr, __THREAD_FUNC, this) == -1) {
  		return -1;
  	}

  	alive = true;
  	return 0;
  }

  void Thread::Stop()
  {
  	
  	if ( alive ) {
  		pthread_cancel(hdl);
  		alive = false;
  	}
  }

  void Thread::Join()
  {

  	if ( alive ) {
  		pthread_join(hdl, NULL);
  		alive = false;
  	}
  }
