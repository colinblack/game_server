/*
 *	Log.cpp   log日志类
 *	功能: 完成基本日志功能已经启动时打印启动信息
 *	作者: geminiguan     2006.8.3
 *	日志分5层，更具定义对象时的lvl区分
 *	modify :
 *		billyli 2006.11.28
 *		增加日志文件写满时回绕功能
 */

#include "commlog.h"
#include "logserver.h"
#include <strings.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "tsc.h"
#include <string>
#include <map>

volatile time_t 	now ;

#define LOG_RECORD_MAX_SIZE 8000

std::map<std::string,CLog*> CLog::_logMap;
std::string CLog::SRV_ID;
std::string CLog::PRO_ID;
std::string CLog::LOGGER_SERVER_IP;
short CLog::LOGGER_SERVER_PORT;

std::map<int, CLog*> CLog::_logMapF;
int CLog::_domain = 0;

/* func		: CLog
 * desc		: 初始化对象中的变量和内存
 */
CLog::CLog()
{
    rewind = 1; //默认日志需要回绕
    log_valid = 0;
}

//CLog * CLog::_pInstance = 0;
CLog::~CLog()
{
    log_valid = 0;
    //munmap(log_buffer, 1024);
    for (int i=0; i<APP_DEBUG+1; i++)
    {
        if(log_fd[i].opfd != -1)    // 这里应该是!=, 不是==
        {
            close(log_fd[i].opfd);
            log_fd[i].opfd = -1;
        }
        log_fd[i].seq = -1;
    }
}
/* func		: initalize
 * desc		: 初始化log对象
 * input   	: lvl -输出错误日志的最高层数
 *			: logdir -存放目录，目录必须有写和执行的权限
 * 		    : pre_name -配置文件名前缀
 *          : size - 文件大小
 *			: record_size 日志记录大小
 * return	: 成功返回 0,失败返回-1
 */
int CLog::initalize(int lvl,const char *logdir, const char* pre_name,
					int rewind,uint32_t size,uint32_t record_size)
{
	tsc_init ();
	log_level = lvl;
	this->rewind = rewind;
	//this->record_size = record_size;
    for(int i = 0; i<APP_DEBUG+1; i++)
    {
        log_fd[i].seq = -1;
        log_fd[i].opfd = -1;
    }
    memset(log_prefix, 0, sizeof(log_prefix));
    memset(log_dir, 0, sizeof(log_dir));

    if(logdir != NULL)
    {
        strncpy(log_dir, logdir, sizeof(log_dir)-1);
        if(log_dir[strlen(log_dir) -1] == '/')
        {
            log_dir[strlen(log_dir) -1] = '\0';
        }
        if(access(log_dir, F_OK | X_OK | W_OK) != 0)
        {
            fprintf (stderr, "the logdir do not exist or do not have wx. dir: %s\n", logdir);
            return -1;
        }

    }
    else
    {
        memset(log_dir, 0, sizeof(log_dir));
    }

    if(pre_name != NULL)
    {
        strncpy(log_prefix, pre_name, sizeof(log_prefix)-1);
    }
    else
    {
        memset(log_prefix, 0, sizeof(log_prefix));
    }
     //分配内存
//    log_buffer =  (char *)mmap (0, record_size, PROT_WRITE | PROT_READ, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
//    if(log_buffer == MAP_FAILED)
//    {
//        fprintf (stderr, "mmap log buffer failed, %m\n");
//        return -1;
//    }
    assert(size >0 && size < (unsigned int)(1<<31));
    log_size = size;

    for (int i=0; i<APP_DEBUG+1; i++)
    {
        log_fd[i].seq = request_log_seq(i);
    }

    log_valid = 1;

    return 0;
}
/*
获得文件名，包括目录 根据时间和序号
*/
/* func		: get_log_name
 * desc		: 获得文件名
 * input	: lvl -层数
 *			: seq -序号
 *			: now - 时间
 * output	: file_name 生成文件名
 */
inline void CLog::get_log_name(int lvl, int seq, char* file_name, time_t now)
{
    struct tm tm;

    localtime_r(&now, &tm);

    if(lvl == APP_BUSI){
    	snprintf(file_name,FILENAME_MAX -1,"%s/%s.log.%04d%02d%02d",
    			log_dir,
    			log_prefix,
    			tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);

    	return;
    }

    if(seq == 0)
    {
        snprintf (file_name,FILENAME_MAX -1, "%s/%s.%s.%04d%02d%02d.log",
					log_dir,
					log_prefix,
					((char*[]){"fatal", "error", "warn","info", "debug"})[lvl],
					tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday
				);
    }
    else
    {
        snprintf (file_name,FILENAME_MAX-1, "%s/%s.%s.%04d%02d%02d.%03d.log",
					log_dir,
					log_prefix,
					((char*[]){"fatal", "error", "warn","info", "debug"})[lvl],
			        tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, seq
				);
    }
}

/* func		: request_log_seq
 * desc		: 获得可用序号
 * input	: lvl -层
 * return	: 序号
 */
int CLog::request_log_seq(int lvl)
{
    char file_name[FILENAME_MAX];
	int seq;
	//unixtime(now);
	now = time(NULL);
	struct stat buf;
    //寻找当前日期的日志文件最大序号
    for (seq = 0; seq < MAX_LOG_CNT; seq ++)
    {
        get_log_name (lvl, seq, file_name, now);

        if (access (file_name, F_OK))
        {
            if (seq == 0)
                return 0;
            else
                break;
        }
    }

    if (seq == MAX_LOG_CNT)
    {
        fprintf (stderr, "too many log files\n");
        return -1;
    }

    get_log_name (lvl, --seq, file_name, now);
    if (stat (file_name, &buf))
    {
         fprintf (stderr, "stat %s error, %m\n", file_name);
         return -1;
    }
    return seq;
}
/* func		: openfd
 * desc		: 打开文件，填写fd相关信息
 * input	: lvl - 层
 *			: now -当前时间
 * return	: 文件fd
 */
int CLog::openfd(int lvl, time_t now)
{
    char file_name[FILENAME_MAX];
    struct tm tm;
    int val;

    get_log_name (lvl, log_fd[lvl].seq, file_name, now);
    //打开文件
    if(__sync_bool_compare_and_swap(&log_fd[lvl].opfd, -1, -2))
    {
    	log_fd[lvl].opfd = open (file_name, O_WRONLY|O_CREAT|O_APPEND, 0644);
    }
    if (log_fd[lvl].opfd >= 0)
	{//设置相关信息
        localtime_r (&now, &tm);
        log_fd[lvl].day = tm.tm_yday;

        val = fcntl(log_fd[lvl].opfd, F_GETFD, 0);
        val |= FD_CLOEXEC;
        fcntl(log_fd[lvl].opfd, F_SETFD, val);
    }
    return log_fd[lvl].opfd;
}

/* func		: shiftfd
 * desc		: 根据当前时间，确定是否要打开新的log文件
 * input	: lvl - 层
 *			: now -当前时间
 *			: len -本条日志长度
 * return	: 成功返回 0或文件fd 失败返回-1
 */
int CLog::shiftfd (int lvl, time_t now,int len)
{
#ifdef DEBUG
	log_fd[lvl].opfd = 1;
	return 0;
#endif
	off_t length;
	struct tm tm;
	//没有打开，也打不开log文件
	if (log_fd[lvl].opfd < 0 && openfd (lvl, now) < 0)
		return -1;

	length = lseek (log_fd[lvl].opfd, 0, SEEK_END);
	localtime_r (&now, &tm);

	if (log_fd[lvl].day != tm.tm_yday) //如果日期不是当前日期
	{
		close (log_fd[lvl].opfd);
		log_fd[lvl].opfd  = -1;
		log_fd[lvl].seq = 0;
		return openfd (lvl, now);
	}
	if ( (unsigned int)(length + len) >= log_size ) //如果文件已超过设置的长度
	{
		if(rewind == 0)	//不回绕
		{
			close (log_fd[lvl].opfd);
			log_fd[lvl].opfd  = -1;
			log_fd[lvl].seq ++;
			return openfd (lvl, now);
		}
		else
		{
			return ftruncate(log_fd[lvl].opfd,0); //需要回绕则截断为0长
		}
	}
	return 0;
}
/* func		: boot_log
 * desc		: 打印启动信息
 * input	: result - 成功或失败
 *			: dummy -空白
 *			: fmt- 参数
 */
void CLog::write_boot_log(int result, int dummy, const char *fmt, ...)
{
	#define SCREEN_COLS    80
	#define BOOT_OK        "\e[1m\e[32m[ ok ]\e[m"
	#define BOOT_FAIL    "\e[1m\e[31m[ failed ]\e[m"
    int end, i, pos;
    va_list ap;
    char logBuf[512];

    va_start(ap, fmt);
    end = vsnprintf (logBuf, sizeof(logBuf),fmt, ap);
    va_end (ap);
    //ok或failed到启动信息结尾的长度
    pos = SCREEN_COLS - 10 - (end - dummy) % SCREEN_COLS;
    for (i = 0; i < pos; i++)
        logBuf[end + i] = ' ';
     logBuf[end + i] = '\0';
    strncat (logBuf, result == LOG_OK ? BOOT_OK : BOOT_FAIL,sizeof(logBuf)-strlen(logBuf)-1);
    fprintf (stderr,"\r%s\n", logBuf);
}
/*
写log文件
*/
/* func		: write_log
 * desc		: 写log文件
 * input	: lvl - 层
 *			: fmt- 参数
 *return	: 返回0
 */
int CLog::write_log (int lvl, const char* fmt, ...)
{
	if(!log_valid) return 0;

	if(lvl > log_level) return 0;
    struct tm tm;
	int pos, end;
	va_list ap;
    //unixtime(now);
	now = time(NULL);
    char log_buffer[LOG_RECORD_MAX_SIZE];
	localtime_r((const time_t *)&now, &tm);
    //时间信息
	//pos = snprintf (log_buffer,record_size, "[%02d:%02d:%02d][%05d]",
	pos = snprintf (log_buffer,sizeof(log_buffer), "[%02d:%02d:%02d][%05d]",
					tm.tm_hour, tm.tm_min, tm.tm_sec, getpid());
	va_start(ap, fmt);
	//end = vsnprintf (log_buffer + pos,record_size-pos, fmt, ap);
	end = vsnprintf (log_buffer + pos,sizeof(log_buffer)-pos, fmt, ap);
	va_end(ap);
	if(end < 0)
		end = 0;
	//else if((unsigned int)end >= (record_size-pos))
	//	end = record_size-pos-1;
	else if((unsigned int)end >= (sizeof(log_buffer)-pos))
		end = sizeof(log_buffer)-pos-1;

    //如果没有分配对应的配置文件，从stderr输出
    if(shiftfd(lvl, now,end+pos) == -1)
    {
		va_start(ap,fmt);
		vfprintf(stderr, fmt, ap);
		va_end(ap);
		return 0;
    }

	write (log_fd[lvl].opfd, log_buffer, end + pos);//写日志

    return 0;
}

int CLog::busi_write(const char* fmt,...){
	if(!log_valid) return 0;
	int lvl = APP_BUSI;
	struct tm tm;
	int pos, end;
	va_list ap;
	//unixtime(now);
	time_t now;
	time(&now);
	char log_buffer[LOG_RECORD_MAX_SIZE];
	localtime_r((const time_t *)&now, &tm);

	pos = snprintf (log_buffer,sizeof(log_buffer), "%04d-%02d-%02d %02d:%02d:%02d|",
					tm.tm_year+1900,tm.tm_mon+1,tm.tm_mday,tm.tm_hour, tm.tm_min, tm.tm_sec);
	va_start(ap, fmt);
	//end = vsnprintf (log_buffer + pos,record_size-pos, fmt, ap);
	end = vsnprintf (log_buffer + pos,sizeof(log_buffer)-pos, fmt, ap);
	va_end(ap);
	if(end < 0)
		end = 0;
	//else if((unsigned int)end >= (record_size-pos))
	//	end = record_size-pos-1;
	else if((unsigned int)end >= (sizeof(log_buffer)-pos))
		end = sizeof(log_buffer)-pos-1;

	//如果没有分配对应的配置文件，从stderr输出
	if(shiftfd(lvl, now,end+pos) == -1)
	{
		va_start(ap,fmt);
		vfprintf(stderr, fmt, ap);
		va_end(ap);
		return 0;
	}

	write (log_fd[lvl].opfd, log_buffer, end + pos);//写日志

	LogMsg logMsg;
	logMsg.srvId       = SRV_ID;
	logMsg.proId	   = PRO_ID;
	logMsg.logFileName = std::string(log_prefix);
	logMsg.logStr      = std::string(log_buffer);
	Logger::getInstance()->sendData(logMsg, LOGGER_SERVER_IP, LOGGER_SERVER_PORT);
	return 0;
}

CLog * CLog::GetInstance()
{
	if(_domain)
	{
		if (_logMapF.find(_domain) == _logMapF.end())
		{
			_logMapF[_domain] = new CLog();
		}
		return _logMapF[_domain];
	}
	else
	{
		static CLog s_pLog;
		return &s_pLog;
	}
};

CLog* CLog::GetInstance(const std::string& name)
{
	std::map<std::string,CLog*>::iterator it = _logMap.find(name);
	if(it != _logMap.end())
	{
		CLog* p = it->second;
		return it->second;
	}

	return NULL;
}

int CLog::create_inst(const char* logtype,const char *logdir){
	int rewind = 1;
	uint32_t size = 2000000000;

	CLog* pLog = new CLog();
	if(0 != pLog->initalize(APP_BUSI,logdir,logtype,rewind,size,LOG_RECORD_MAX_SIZE)){
		return -1;
	}

	std::string logType(logtype);
	_logMap[logType] = pLog;

	return 0;
}

int CLog::initLoggerServer(const std::string& srvId, const std::string& proId, const std::string& ip, const short port){
	SRV_ID = srvId;
	PRO_ID = proId;
	LOGGER_SERVER_IP = ip;
	LOGGER_SERVER_PORT = port;
	return 0;
}

void CLog::SetDomain(int domain)
{
	_domain = domain;
	return;
}
