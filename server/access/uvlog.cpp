#include "uvlog.h"
#include <stdio.h>
#include <time.h>
#include <libgen.h>
#include <iostream>
#include <unistd.h>
#include <stdarg.h>
#include <sys/time.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/cdefs.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <stdlib.h>

#define LOGSIZE 4096

UVLog* g_pLog = NULL;
UVLog* g_pOnlineLog = NULL;

map<string,UVLog*>	UVLog::logsMap;

UVLog* UVLog::createInstance(const char* name,LogFile* logFile)
{	
	if(name == NULL) return NULL;
	
	UVLog *pLog = UVLog::getInstance(name);
	if(pLog)
	{
	    return pLog;
	}
	
	pLog = new UVLog();
	memcpy(&pLog->logFile,logFile,sizeof(LogFile));
	
	
	if(access(dirname(logFile->sLogFileName), W_OK|X_OK) < 0)
	{
	    delete pLog;
	    
	    fprintf(stderr,"log dir not accessiable:dirname = [%s],LogFileName = [%s]\n",dirname(logFile->sLogFileName),logFile->sLogFileName);

	    exit(1);
	    
	    return NULL;
	}

	UVLog::logsMap[name] = pLog;
	return pLog;
}

UVLog* UVLog::getInstance(const char* name)
{
	if(name == NULL) return NULL;
	
    	map<string,UVLog*>::iterator it;
	it = UVLog::logsMap.find(name);
	if(it != UVLog::logsMap.end())
	{
        return it->second;
	}
	
	return NULL;
}

void UVLog::setLogLevel(int level)
{
    logLevel = level;
}

bool UVLog::write_log(int level, const char *filename, const char *funcname,int lineno,const char *format, ...)
{
    if(level > logLevel)
    {
        return false;
    }
    
    int off = 0;
	char buf[LOGSIZE] = {0};
	struct tm tm;
	time_t now = time (NULL);
	localtime_r(&now, &tm);
	
	off = snprintf (buf, LOGSIZE,
			"<%d>[%02d:%02d:%02d] pid[%d:%u]: %s(%d)[%s]: ",
			level,
			tm.tm_hour, tm.tm_min, tm.tm_sec,
			getpid(),
			(unsigned int)pthread_self(),
			filename, lineno, funcname
		       );
	if(off >= LOGSIZE)
	off = LOGSIZE - 1;
    
    
	{
		// formatted message
		va_list ap;
		va_start(ap, format);
		// restore errno
		off += vsnprintf(buf+off, LOGSIZE-off, format, ap);
		va_end(ap);
	}

	if(off >= LOGSIZE)
		off = LOGSIZE - 1;
	if(buf[off-1]!='\n'){
		if(off < LOGSIZE - 1)
			buf[off++] = '\n';
		else
			buf[LOGSIZE-1] = '\n';
	}
	
	if(logFd < 0)
	{
	    logFd = open(logFile.sLogFileName, O_CREAT | O_LARGEFILE | O_APPEND |O_WRONLY, 0644);
	    fcntl(logFd, F_SETFD, FD_CLOEXEC);
	}

	if(logFd >= 0)
	{
		write(logFd, buf, off);   
    }
	
	shiftFiles();
	return true;
}


bool UVLog::shiftFiles()
{
    struct stat stStat;
    //struct tm stLogTm, stShiftTm;
    char sLogFileName[300];
	char sNewLogFileName[300];
	bool flag = true;
    
    if(stat(logFile.sLogFileName, &stStat) < 0) return false;
    
    if (stStat.st_size < logFile.lMaxSize) return true;
    close(logFd);  
    
    for(int i = logFile.iMaxLogNum-2; i >= 0; i--)
    {
        if (i == 0)
			sprintf(sLogFileName,"%s",logFile.sLogFileName);
		else
			sprintf(sLogFileName,"%s.%d",logFile.sLogFileName, i);
			
		if (access(sLogFileName, F_OK) == 0)
		{
			sprintf(sNewLogFileName, "%s.%d" , logFile.sLogFileName, i+1);
			if (rename(sLogFileName,sNewLogFileName) < 0 )
			{
			    flag = false;
				break;
			}
		}
    }
    
    logFd = open(logFile.sLogFileName, O_CREAT | O_LARGEFILE | O_APPEND |O_WRONLY, 0644);
	fcntl(logFd, F_SETFD, FD_CLOEXEC);
    
    
    return flag;    
}

bool UVLog::busiLog(const char* format , ...)
{
    int off = 0;
    char buf[LOGSIZE] = {0};
    char logfile[256];
	struct tm tm;
	time_t now = time (NULL);
	localtime_r(&now, &tm);
	
	off = snprintf (buf, LOGSIZE,
			"%04d-%02d-%02d %02d:%02d:%02d|",
			tm.tm_year+1900,
			tm.tm_mon+1,
			tm.tm_mday,
			tm.tm_hour, tm.tm_min, tm.tm_sec);
	if(off >= LOGSIZE)
	off = LOGSIZE - 1;
	
    va_list ap;
    va_start(ap, format);    
    off += vsnprintf(buf+off, LOGSIZE-off, format, ap);
    va_end(ap);
    
    if(off >= LOGSIZE)
		off = LOGSIZE - 1;
	if(buf[off-1]!='\n'){
		if(off < LOGSIZE - 1)
			buf[off++] = '\n';
		else
			buf[LOGSIZE-1] = '\n';
	}
    
    int today = tm.tm_year*1000 + tm.tm_yday;
	if(logFd < 0 || today != logFile.iLogDay)
	{
		if(logFd > 0)
		{
		    close(logFd);
		    logFd = -1;
		}

		logFile.iLogDay = today;
		snprintf (logfile, sizeof(logfile),
				"%s.%04d%02d%02d", logFile.sLogFileName,
				tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
		logFd = open (logfile, O_CREAT | O_LARGEFILE | O_APPEND |O_WRONLY, 0644);
		fcntl(logFd, F_SETFD, FD_CLOEXEC);
	}
	
	if(logFd >= 0)
	{
		write(logFd, buf, off);   
    }
    
    return true;
}
