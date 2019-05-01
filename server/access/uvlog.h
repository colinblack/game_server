#ifndef _WANGXUAN_UVLOG_H_
#define _WANGXUAN_UVLOG_H_

#include <sys/time.h>
#include <map>
#include <string>
#include <stdint.h>
using namespace std;

typedef struct {
char	sLogFileName[80];
int		iShiftType;		// 0 -> shift by size,  1 ->shift by day
int		iMaxLogNum;
int	    lMaxSize;
int	    iLogDay;
} LogFile;


#define DISPATH_ERROR_BUSI_FNAME "error_busi_fname"
#define DISPATH_INPUT_BUSI_FNAME "input_busi_fname"
#define DISPATH_OUTPUT_BUSI_FNAME "output_busi_fname"


class UVLog
{
public:
	static UVLog* getInstance(const char* name);
	static UVLog* createInstance(const char* name,LogFile* logFile);
	
public:
	bool write_log(int level, const char *filename, const char *funcname,int lineno,const char *format, ...);
	bool busiLog(const char* fmt , ...);
    void setLogLevel(int level);
    int getLogLevel(){return logLevel;};
private:
    UVLog(){logFd = -1;logLevel=6;};   
    bool shiftFiles();

public:
    
private:	
    static map<string,UVLog*>	logsMap;
	LogFile logFile;
	int logFd;
	int logLevel;
};

extern UVLog* g_pLog;
extern UVLog* g_pOnlineLog;
#define INIT_LOG(fname,persize,maxc)  \
do{\
	LogFile logFile;\
	memset(&logFile,0,sizeof(LogFile));\
	strncpy(logFile.sLogFileName,fname,sizeof(logFile.sLogFileName) - 1);\
	logFile.iShiftType = 0;\
	logFile.iMaxLogNum = maxc;\
	logFile.lMaxSize = persize;\
	g_pLog  = UVLog::createInstance("COMMON_LOG",&logFile);\
}while(0)

#define INIT_ONLINE_LOG(fname,persize,maxc)  \
do{\
	LogFile logFile;\
	memset(&logFile,0,sizeof(LogFile));\
	strncpy(logFile.sLogFileName,fname,sizeof(logFile.sLogFileName) - 1);\
	logFile.iShiftType = 0;\
	logFile.iMaxLogNum = maxc;\
	logFile.lMaxSize = persize;\
	g_pOnlineLog  = UVLog::createInstance("ONLINE_LOG",&logFile);\
}while(0)



#define LOG_GENERIC(lvl, fmt, args...)	 if(g_pLog->getLogLevel() > lvl) g_pLog->write_log(lvl, __FILE__, __FUNCTION__, __LINE__ , fmt, ##args)
#define LOG_EMERG(fmt, args...)	LOG_GENERIC(0, fmt, ##args)
#define LOG_ALERT(fmt, args...)	LOG_GENERIC(1, fmt, ##args)
#define LOG_CRIT(fmt, args...)		LOG_GENERIC(2, fmt, ##args)
#define LOG_ERROR(fmt, args...)		LOG_GENERIC(3, fmt, ##args)
#define LOG_WARNING(fmt, args...)	LOG_GENERIC(4, fmt, ##args)
#define LOG_NOTICE(fmt, args...)	LOG_GENERIC(5, fmt, ##args)
#define LOG_INFO(fmt, args...)		LOG_GENERIC(6, fmt, ##args)
#define LOG_DEBUG(fmt, args...)		LOG_GENERIC(7, fmt, ##args)
#define LOG_PACKET(fmt, args...)		LOG_GENERIC(8, fmt, ##args)
#define ONLINE_LOG(fmt,args...) g_pOnlineLog->busiLog(fmt,##args)


static inline unsigned int GET_MSEC(void) { struct timeval tv; gettimeofday(&tv, NULL); return tv.tv_sec * 1000 + tv.tv_usec/1000; }
static inline uint64_t GET_USEC(void) {struct timeval tv; gettimeofday(&tv, NULL); return tv.tv_sec * 1000000 + tv.tv_usec;}

#endif
