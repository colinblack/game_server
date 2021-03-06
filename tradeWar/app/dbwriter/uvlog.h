#ifndef _WANGXUAN_UVLOG_H_
#define _WANGXUAN_UVLOG_H_

#include <sys/time.h>
#include "commlog.h"

#define LOG_EMERG(fmt, args...)	fatal_log(fmt, ##args)
#define LOG_ALERT(fmt, args...)	fatal_log(fmt, ##args)
#define LOG_CRIT(fmt, args...)		fatal_log(fmt, ##args)
#define LOG_ERROR(fmt, args...)		error_log(fmt, ##args)
#define LOG_WARNING(fmt, args...)	warn_log(fmt, ##args)
#define LOG_NOTICE(fmt, args...)	warn_log(fmt, ##args)
#define LOG_INFO(fmt, args...)		info_log(fmt, ##args)
#define LOG_DEBUG(fmt, args...)		debug_log(fmt, ##args)
#define LOG_PACKET(fmt, args...)		debug_log(fmt, ##args)


//static inline unsigned int GET_MSEC(void) { struct timeval tv; gettimeofday(&tv, NULL); return tv.tv_sec * 1000 + tv.tv_usec/1000; }
//static inline uint64_t GET_USEC(void) {struct timeval tv; gettimeofday(&tv, NULL); return tv.tv_sec * 1000000 + tv.tv_usec;}

#endif
