#ifndef MEMORYMANGER_H
#define MEMORYMANGER_H

//#include "Common.h"
//#include "Kernel.h"
#include "mem_core.h"
#include "singleton.h"
#include "AppDefine.h"

class MemoryManager : public CHSingleton<MemoryManager>
{
private:
    friend class CHSingleton<MemoryManager>;
    MemoryManager()
    {
        mempool_ = ngx_create_pool(MEM_POOL_SIZE);
    }
    ~MemoryManager()
    {
        ngx_destroy_pool(mempool_);
    }

public:
    ngx_pool_t *Pool()
    {
        return mempool_;
    }

private:
    ngx_pool_t *mempool_;
};

/* template <class Type, class... Args>
void Construct(Type *p, int num, Args... args)
{
    for (int i = 0; i < num; ++i)
    {
        new ((void *)(p + i)) Type(args...);
    }
} */

/* template <class Type>
Type *CreateObj(int num = 1)
{
    Type *p = (Type *)ngx_palloc(MemoryManager::Instance()->Pool(), sizeof(Type) * num);
    Construct(p, num);

    return p;
} */

template <class Type, class... Args>
Type *CreateObj(int num = 1, Args... args)
{
    Type *p = (Type *)ngx_palloc(MemoryManager::Instance()->Pool(), sizeof(Type) * num);
    for (int i = 0; i < num; ++i)
    {
        new ((void *)(p + i)) Type(args...);
    }
    return p;
}

template <class Type>
void DestoryObj(Type *p, int num = 1)
{
    Type *tmp = p;
    for (int i = 0; i < num; ++i, ++tmp)
    {
        tmp->~Type();
    }
    ngx_pfree(MemoryManager::Instance()->Pool(), (void *)p);
}

#endif