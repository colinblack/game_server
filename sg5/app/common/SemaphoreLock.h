#ifndef __SEMAPHORELOCK_H__
#define __SEMAPHORELOCK_H__

#include "ILock.h"

class CSemaphoreLock : public ILock
{
public:
	CSemaphoreLock();
	~CSemaphoreLock();

	bool Create(const char *name, int semid = 0);
	bool Open(const char *name, int semid = 0);
	bool CreateOrOpen(const char *name, int semid = 0);
	bool Close();

	bool Lock();
	bool Unlock();

private:
	void *m_sem;
};

#endif //__SEMAPHORELOCK_H__
