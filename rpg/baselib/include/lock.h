#ifndef __DBC_LOCK_H__
#define __DBC_LOCK_H__

#include <pthread.h>

class CBaseMutex
{
    friend class condition;

public:
    inline CBaseMutex (void)
    {
        ::pthread_mutex_init (&_mutex, 0);
    }

    inline void lock (void) 
    {
        ::pthread_mutex_lock (&_mutex);
    }

    inline void unlock (void) 
    {
        ::pthread_mutex_unlock (&_mutex);
    }

    inline ~CBaseMutex (void)
    {
        ::pthread_mutex_destroy (&_mutex);
    }

private:
    CBaseMutex(const CBaseMutex& m);
    CBaseMutex& operator= (const CBaseMutex &m);

private:
    pthread_mutex_t _mutex;
};

/**
 * *    definition of ScopedLock;
 * **/
class CScopedLock 
{
    friend class condition;

public:
    inline CScopedLock (CBaseMutex& mutex) : _mutex (mutex)
    {
        _mutex.lock ();
    }

    inline ~CScopedLock (void) 
    {
        _mutex.unlock ();
    }

private:
    CBaseMutex& _mutex;
};

#endif //__DBC_LOCK_H__
