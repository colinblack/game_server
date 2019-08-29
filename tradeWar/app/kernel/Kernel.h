//Kernel.h
//20110506 dada create

#ifndef __KERNEL_H__
#define __KERNEL_H__

#include "Common.h"

//#include "str4i.h"

#include "AppDefine.h"
#include "KernelUtil.h"
#include "ErrorUtil.h"
#include "DataLog.h"
#include "WhiteList.h"
#include "DataBaseDBC.h"
#include "Session.h"
#include "BusinessLog.h"
#include "Compress.h"
#include "FirePacket.h"
#include "poll_thread.h"
#include "TcpChannel.h"
#include "ServerConfig.h"
#include "NetPacket.h"

static inline uint64_t GET_MSEC(void) { struct timeval tv; gettimeofday(&tv, NULL); return tv.tv_sec * 1000 + tv.tv_usec/1000; }
static inline uint64_t GET_USEC(void) {struct timeval tv; gettimeofday(&tv, NULL); return tv.tv_sec * 1000000 + tv.tv_usec;}

#define SINGLETON_CLASS(name) private : name(); public : static name* getInstance() {static name _ins; return &_ins;} virtual ~name()

#endif //__KERNEL_H__
