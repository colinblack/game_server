#ifndef __SHAREMEMORY_H__
#define __SHAREMEMORY_H__

#include "ILock.h"
#include "IShareMemory.h"
#include "Semaphore.h"
#include "Vsem.h"

class CShareMemory : public IShareMemory, public ILock
{
public:
	CShareMemory();
	~CShareMemory();

	bool Create(const char *name, int size);
	bool Open(const char *name, int size);
	bool CreateOrOpen(const char *name, int size);
	bool Close();
	bool Flush();

	void *GetAddress() const;
	int GetSize() const;

	bool HasInit();
	void SetInitDone();

	bool Lock();
	bool Unlock();

private:
	void *m_pAddress;

//#if SEM_TYPE == 1
//	CSemaphoreLock m_lock;
//#else
//	CVsem m_lock;
//#endif
	CSemaphoreLock m_lock;
};

#endif //__SHAREMEMORY_H__
