#ifndef _CPP_SOCKET_THREAD_H_
#define _CPP_SOCKET_THREAD_H_

#include <pthread.h>
#include "non_copyable.h"

  class Thread : public NonCopyable
  {
  public:
  	Thread();
  	virtual ~Thread();
  	int Start();
  	void Stop();
  	void Join();

  	inline bool IsAlive() const { return alive; }
  	inline pthread_t GetThreadID() const { return hdl; }

  private:
  	virtual void Run() = 0;	

  private:
  	pthread_t hdl;
  	bool alive;

  	friend void* __THREAD_FUNC(void* p);
  };


#endif // AC_UTIL_THREAD_H_


