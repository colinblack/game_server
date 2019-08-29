/*
 * Common.h
 *
 *  Created on: 2011-5-20
 *      Author: dada
 */


#ifndef __COMMON_H__
#define __COMMON_H__

#include "SysCommon.h"

#include "basic.h"
#include "trans.h"
#include "json.h"
#include "markupstl.h"
#include "commlog.h"
#include "ctime.h"
#include "tsc.h"
#include "crc.h"

#include "CommonUtil.h"
#include "StringUtil.h"
#include "Math.h"
#include "Convert.h"
#include "TimeUtil.h"
#include "FileUtil.h"
#include "JsonUtil.h"
#include "Crypt.h"
#include "HttpUtil.h"
#include "Compress.h"
#include "Config.h"
#include "IBase.h"

#define LogError(fmt, ...)	error_log("[" fmt "]",   __VA_ARGS__)

#include "SystemUtil.h"
#include "Thread.h"
#include "ILock.h"
#include "ISemaphore.h"
#include "IMemory.h"
#include "IShareMemory.h"
#include "HeapMemory.h"
#include "AutoLock.h"
#include "Mutex.h"
#include "SpinLock.h"
#include "Semaphore.h"
#include "SemaphoreLock.h"
#include "ThreadSemaphore.h"
#include "Event.h"
#include "ShareMemory.h"
#include "ReadOnlyShareMemory.h"
#include "IBuffer.h"
#include "IMessageQueue.h"
#include "Buffer.h"
#include "StaticBuffer.h"
#include "DynamicBuffer.h"
#include "BufferReader.h"
#include "BufferWriter.h"
#include "MessageQueue.h"
#include "Socket.h"
#include "FileToJson.h"
#include "ThreadMutex.h"

#include "StringFilter.h"

typedef   unsigned   char   byte;

#endif //__COMMON_H__
