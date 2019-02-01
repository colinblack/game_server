#ifndef CPPSOCKET_THREADPOOL_H_
#define CPPSOCKET_THREADPOOL_H_

#include "non_copyable.h"
#include "thread.h"
#include <pthread.h>
#include <list>

  class JobThread;

  // NOTICE: ThreadPool 对象不能在多个线程中被同时操控
  class ThreadPool  : public NonCopyable
  {
  protected:
  	typedef std::list<Thread*>	ThreadPtrContainer;
  	
  	ThreadPtrContainer	livethreads;
  	ThreadPtrContainer	deadthreads;
  	
  	pthread_mutex_t		mutex;

  	volatile size_t			stopcount;
  	
  public:

  	ThreadPool();

  	virtual ~ThreadPool();

  	int Start(size_t count);

  	void Stop(size_t count);

  	void StopAll();

  	size_t GetThreadNum();

  protected:

  	virtual bool RunOnce();
  	
  	virtual void StopThreads(size_t stopcount);


  protected:
  		
  	Thread* CreateThread();

  	void DestroyThread(Thread* thread);

  	friend class JobThread;
  };
#endif // AC_UTIL_THREADPOOL_H_

