#include "kfc_log.h"
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <iostream>
#include <fstream>

using namespace std;

kfc::log_open_fail::log_open_fail(const string & s) : runtime_error(s)
{
}

kfc::CRollLog::CRollLog()
{
	_setlevel = DEBUG_LOG;
	_level = NORMAL_LOG;
	_buf_count = 0;
	_pid = getpid();

	_flags[0] = true;
	_flags[1] = false;
	_flags[2] = false;
	_flags[3] = true;

	_fd = -1;

	_lock = false;

	time_format();
}

kfc::CRollLog::~CRollLog()
{
	if(_fd > 0)
	{
		close(_fd);
		_fd = -1;
	}
}

void kfc::CRollLog::Init(const string & sPreFix, const string & module, size_t maxsize, size_t maxnum)
throw(log_open_fail)
{
	if(_fd > 0)
	{
		close(_fd);
		_fd = -1;
	}
	_module = module;
	_filename = sPreFix;
	_max_log_size = maxsize;
	_max_log_num = maxnum;
	_buf_count = 0;
	_pid = getpid();

	_flags[0] = true;
	_flags[1] = false;
	_flags[2] = false;
	_flags[3] = true;

	_lock = false;

#ifdef O_LARGEFILE
	_fd = open((_filename + ".log").c_str(), O_WRONLY | O_CREAT | O_APPEND | O_LARGEFILE, 0644);
#else
	_fd = open((_filename + ".log").c_str(), O_WRONLY | O_CREAT | O_APPEND, 0644);
#endif
	if(_fd < 0)
	{
		throw log_open_fail(string("can not open file:") + _filename + ".log");
	}
}

void kfc::CRollLog::set_titleflag(title_flag f)
{
	_flags[f] = true;
	_pid = getpid();
	switch(_level)
	{
	case NO_LOG:
		_debugtip = "";
		break;
	case ERROR_LOG:
		_debugtip = "ERROR:";
		break;
	case NORMAL_LOG:
		_debugtip = "";
		break;
	case DEBUG_LOG:
		_debugtip = "DEBUG:";
		break;
	default:
		break;
	}
}

inline string kfc::CRollLog::cur_time()
{
	time_t tNow = time(0);
	struct tm curr;
	curr = *localtime(&tNow);
	char sTmp[1024];
	strftime(sTmp, sizeof(sTmp), _time_format.c_str(), &curr);
	return string(sTmp);
}

bool kfc::CRollLog::check_level()
{
	if(_fd < 0)
	{
#ifdef O_LARGEFILE
		_fd = open((_filename + ".log").c_str(), O_WRONLY | O_CREAT | O_APPEND | O_LARGEFILE, 0644);
#else
		_fd = open((_filename + ".log").c_str(), O_WRONLY | O_CREAT | O_APPEND, 0644);
#endif
	}
	if(_fd < 0)
	{
		return false;
	}

	_buf_count++;
	if(_buf_count % FLUSH_COUNT == 0)
	{
		_buf_count = 0;

		// close and roll file
		if(lseek(_fd, 0, SEEK_CUR) > (int) _max_log_size)
		{
			// 2005-06-06, 多线程(进程)时会写乱,需要重新open之后判断
			if(_fd < 0)
			{
#ifdef O_LARGEFILE
				_fd = open((_filename + ".log").c_str(), O_WRONLY | O_CREAT | O_APPEND | O_LARGEFILE, 0644);
#else
				_fd = open((_filename + ".log").c_str(), O_WRONLY | O_CREAT | O_APPEND, 0644);
#endif
			}
			if(_fd < 0)
			{
				return false;
			}
			if(lseek(_fd, 0, SEEK_CUR) > (int) _max_log_size)
			{
				char sTmp[16];
				close(_fd);
				_fd = -1;
				string from, to;
				// remove the last one
				sprintf(sTmp, "%d", _max_log_num - 1);
				from = _filename + sTmp + ".log";
				if(access(from.c_str(), F_OK) == 0)
				{
					if(remove(from.c_str()) < 0)
					{
						cerr << "remove " << from << " fail!!!" << std::endl;
						// return _level<=_setlevel;
					}
				}
				// rename the others
				for(int i = _max_log_num - 2; i >= 0; i--)
				{
					sprintf(sTmp, "%d", i);
					if(i == 0) from = _filename + ".log";
					else from = _filename + sTmp + ".log";
					sprintf(sTmp, "%d", i + 1);
					to = _filename + sTmp + ".log";
					if(access(from.c_str(), F_OK) == 0)
					{
						if(rename(from.c_str(), to.c_str()) < 0)
						{
							cerr << "rename " << from << " --> " << to << " fail!!!" << std::endl;
						}
					}
				}
				if(_fd < 0)
				{
#ifdef O_LARGEFILE
					_fd = open((_filename + ".log").c_str(), O_WRONLY | O_CREAT | O_APPEND | O_LARGEFILE, 0644);
#else
					_fd = open((_filename + ".log").c_str(), O_WRONLY | O_CREAT | O_APPEND, 0644);
#endif
				}
				if(_fd < 0)
				{
					return false;
				}
			}
		}
	}

	if(_level <= _setlevel)
	{
		if(!_lock)
		{
			char spacebuf[2];
			spacebuf[0] = ' ';
			spacebuf[1] = '\0';
			if(_flags[F_Time])
			{
				_log_buffer += cur_time() + spacebuf;
				//string s = cur_time();
				//write(_fd,s.c_str(),s.length());
				//write(_fd,spacebuf,1);
			}
			if(_flags[F_Module])
			{
				_log_buffer += _module + spacebuf;
				//write(_fd,_module.c_str(),_module.length());
				//write(_fd,spacebuf,1);
			}
			if(_flags[F_PID])
			{
				char sPid[16];
				sprintf(sPid, "%d", _pid);
				_log_buffer += sPid;
				_log_buffer += spacebuf;
				//write(_fd,sPid,strlen(sPid));
				//write(_fd,spacebuf,1);
			}
			if(_flags[F_DEBUGTIP])
			{
				_log_buffer += _debugtip + spacebuf;
				//write(_fd,_debugtip.c_str(),_debugtip.length());
				//write(_fd,spacebuf,1);
			}
			_lock = true;
		}
		return true;
	}
	return false;
}

kfc::CRollLog& kfc::CRollLog::operator<<(char n)
{
	if(check_level())
	{
		char tmpbuf[16];
		tmpbuf[0] = n;
		tmpbuf[1] = '\0';
		_log_buffer += tmpbuf;
		//write(_fd,tmpbuf,1);
	}
	return *this;
}

kfc::CRollLog& kfc::CRollLog::operator<<(unsigned char n)
{
	if(check_level())
	{
		char tmpbuf[16];
		tmpbuf[0] = n;
		tmpbuf[1] = '\0';
		_log_buffer += tmpbuf;
		//write(_fd,tmpbuf,1);
	}
	return *this;
}

kfc::CRollLog& kfc::CRollLog::operator<<(short n)
{
	if(check_level())
	{
		char tmpbuf[16] = {0};
		snprintf(tmpbuf, sizeof(tmpbuf) - 1, "%d", n);
		_log_buffer += tmpbuf;
		//write(_fd,tmpbuf,strlen(tmpbuf));
	}
	return *this;
}

kfc::CRollLog& kfc::CRollLog::operator<<(unsigned short n)
{
	if(check_level())
	{
		char tmpbuf[16] = {0};
		snprintf(tmpbuf, sizeof(tmpbuf) - 1, "%u", n);
		_log_buffer += tmpbuf;
		//write(_fd,tmpbuf,strlen(tmpbuf));
	}
	return *this;
}

kfc::CRollLog& kfc::CRollLog::operator<<(int n)
{
	if(check_level())
	{
		char tmpbuf[16] = {0};
		snprintf(tmpbuf, sizeof(tmpbuf) - 1, "%d", n);
		_log_buffer += tmpbuf;
		//write(_fd,tmpbuf,strlen(tmpbuf));
	}
	return *this;
}

kfc::CRollLog& kfc::CRollLog::operator<<(unsigned int n)
{
	if(check_level())
	{
		char tmpbuf[16] = {0};
		snprintf(tmpbuf, sizeof(tmpbuf) - 1, "%d", n);
		_log_buffer += tmpbuf;
		//write(_fd,tmpbuf,strlen(tmpbuf));
	}
	return *this;
}

kfc::CRollLog& kfc::CRollLog::operator<<(long n)
{
	if(check_level())
	{
		char tmpbuf[16] = {0};
		snprintf(tmpbuf, sizeof(tmpbuf) - 1, "%ld", n);
		_log_buffer += tmpbuf;
		//write(_fd,tmpbuf,strlen(tmpbuf));
	}
	return *this;
}

kfc::CRollLog& kfc::CRollLog::operator<<(unsigned long n)
{
	if(check_level())
	{
		char tmpbuf[16] = {0};
		snprintf(tmpbuf, sizeof(tmpbuf) - 1, "%lu", n);
		_log_buffer += tmpbuf;
		//write(_fd,tmpbuf,strlen(tmpbuf));
	}
	return *this;
}

kfc::CRollLog& kfc::CRollLog::operator<<(long long n)
{
	if(check_level())
	{
		char tmpbuf[64] = {0};
		snprintf(tmpbuf, sizeof(tmpbuf) - 1, "%lld", n);
		_log_buffer += tmpbuf;
		//write(_fd,tmpbuf,strlen(tmpbuf));
	}
	return *this;
}

kfc::CRollLog& kfc::CRollLog::operator<<(unsigned long long n)
{
	if(check_level())
	{
		char tmpbuf[64] = {0};
		snprintf(tmpbuf, sizeof(tmpbuf) - 1, "%llu", n);
		_log_buffer += tmpbuf;
		//write(_fd,tmpbuf,strlen(tmpbuf));
	}
	return *this;
}

kfc::CRollLog& kfc::CRollLog::operator<<(double n)
{
	if(check_level())
	{
		char tmpbuf[16] = {0};
		snprintf(tmpbuf, sizeof(tmpbuf) - 1, "%f", n);
		_log_buffer += tmpbuf;
		//write(_fd,tmpbuf,strlen(tmpbuf));
	}
	return *this;
}

kfc::CRollLog& kfc::CRollLog::operator<<(float n)
{
	if(check_level())
	{
		char tmpbuf[16] = {0};
		snprintf(tmpbuf, sizeof(tmpbuf) - 1, "%f", n);
		_log_buffer += tmpbuf;
		//write(_fd,tmpbuf,strlen(tmpbuf));
	}
	return *this;
}

kfc::CRollLog& kfc::CRollLog::operator<<(const string& s)
{
	if(check_level())
	{
		_log_buffer += s;
		//write(_fd,s.c_str(),s.length());
	}
	return *this;
}

///////////////////////////////////////////////////////////////////////////////

kfc::CDayLog::CDayLog()
{
	_flags[0] = true;
	_flags[1] = false;
	_flags[2] = false;

	_fd = -1;

	_lock = false;
	_last = 0;
	_pid = getpid();

	time_format();
}

kfc::CDayLog::~CDayLog()
{
	UnLock();
	if(_fd > 0)
	{
		close(_fd);
		_fd = -1;
	}
}

void kfc::CDayLog::Init(const string& sPreFix, const string& module) throw(log_open_fail)
{
	_module = module;
	_filename = sPreFix;
	_pid = getpid();

#ifdef O_LARGEFILE
	_fd = open((_filename  + ".log." + s_day(time(0))).c_str(), O_WRONLY | O_CREAT | O_APPEND | O_LARGEFILE, 0644);
#else
	_fd = open((_filename  + ".log." + s_day(time(0))).c_str(), O_WRONLY | O_CREAT | O_APPEND, 0644);
#endif
	if(_fd < 0)
	{
		throw log_open_fail(string("can not open file:") + _filename + "_" + s_day(time(0)) + ".log");
	}
}

void kfc::CDayLog::set_titleflag(title_flag f)
{
	_flags[f] = true;
	_pid = getpid();
}

inline string kfc::CDayLog::s_time(time_t t)
{
	struct tm curr;
	curr = *localtime(&t);
	char sTmp[1024];
	strftime(sTmp, sizeof(sTmp), _time_format.c_str(), &curr);
	return string(sTmp);
}

inline string kfc::CDayLog::s_day(time_t t)
{
	struct tm curr;
	curr = *localtime(&t);
	char sTmp[1024];
	strftime(sTmp, sizeof(sTmp), "%Y%m%d", &curr);
	return string(sTmp);
}

inline time_t kfc::CDayLog::t_day(time_t t)
{
	struct tm curr;
	curr = *localtime(&t);
	curr.tm_hour = 0;
	curr.tm_min = 0;
	curr.tm_sec = 0;

	return mktime(&curr);
}

bool kfc::CDayLog::Lock()
{
	if(_fd < 0)
	{
#ifdef O_LARGEFILE
		_fd = open((_filename + "_" + s_day(time(0)) + ".log").c_str(), O_WRONLY | O_CREAT | O_APPEND | O_LARGEFILE, 0644);
#else
		_fd = open((_filename + "_" + s_day(time(0)) + ".log").c_str(), O_WRONLY | O_CREAT | O_APPEND, 0644);
#endif
	}

	if(_fd < 0)
	{
		return false;
	}

	if(!_lock)
	{
		time_t tnow = time(0);
		if((tnow - _last) / 86400 > 0)
		{
			//			if(_lock) {_os<<unlock;_lock = false;}
			if(_fd > 0) close(_fd);
#ifdef O_LARGEFILE
			_fd = open((_filename + "_" + s_day(time(0)) + ".log").c_str(), O_WRONLY | O_CREAT | O_APPEND | O_LARGEFILE, 0644);
#else
			_fd = open((_filename + "_" + s_day(time(0)) + ".log").c_str(), O_WRONLY | O_CREAT | O_APPEND, 0644);
#endif
			if(_fd < 0) return false;
			_last = t_day(tnow);
		}

		//2005-05-09,在gcc3下<< lock编译不过,临时屏蔽
		//_os << lock;
		char spacebuf[2];
		spacebuf[0] = ' ';
		spacebuf[1] = '\0';
		if(_flags[F_Time])
		{
			_log_buffer += s_time(tnow) + spacebuf;
			//write(_fd,s_time(tnow).c_str(),s_time(tnow).length());
			//write(_fd,spacebuf,1);
		}
		if(_flags[F_Module])
		{
			_log_buffer += _module + spacebuf;
			//write(_fd,spacebuf,1);
		}
		if(_flags[F_PID])
		{
			_log_buffer += _pid + spacebuf;
			//write(_fd,spacebuf,1);
		}
		_lock = true;
	}

	return true;
}

void kfc::CDayLog::UnLock()
{
	if(_lock)
	{
		//if(_os.is_open())
		//_os<<unlock;
		_lock = false;
	}
}

kfc::CDayLog& kfc::CDayLog::operator<<(char n)
{
	if(Lock())
	{
		char tmpbuf[16];
		tmpbuf[0] = n;
		tmpbuf[1] = '\0';
		_log_buffer += tmpbuf;
		//write(_fd,tmpbuf,1);
	}
	return *this;
}

kfc::CDayLog& kfc::CDayLog::operator<<(unsigned char n)
{
	if(Lock())
	{
		char tmpbuf[16];
		tmpbuf[0] = n;
		tmpbuf[1] = '\0';
		_log_buffer += tmpbuf;
		//write(_fd,tmpbuf,1);
	}
	return *this;
}

kfc::CDayLog& kfc::CDayLog::operator<<(short n)
{
	if(Lock())
	{
		char tmpbuf[16];
		snprintf(tmpbuf, sizeof(tmpbuf), "%d", n);
		_log_buffer += tmpbuf;
		//write(_fd,tmpbuf,strlen(tmpbuf));
	}
	return *this;
}

kfc::CDayLog& kfc::CDayLog::operator<<(unsigned short n)
{
	if(Lock())
	{
		char tmpbuf[16];
		snprintf(tmpbuf, sizeof(tmpbuf), "%u", n);
		_log_buffer += tmpbuf;
		//write(_fd,tmpbuf,strlen(tmpbuf));
	}
	return *this;
}

kfc::CDayLog& kfc::CDayLog::operator<<(int n)
{
	if(Lock())
	{
		char tmpbuf[16];
		snprintf(tmpbuf, sizeof(tmpbuf), "%d", n);
		_log_buffer += tmpbuf;
		//write(_fd,tmpbuf,strlen(tmpbuf));
	}
	return *this;
}

kfc::CDayLog& kfc::CDayLog::operator<<(unsigned int n)
{
	if(Lock())
	{
		char tmpbuf[16];
		snprintf(tmpbuf, sizeof(tmpbuf), "%d", n);
		_log_buffer += tmpbuf;
		//write(_fd,tmpbuf,strlen(tmpbuf));
	}
	return *this;
}

kfc::CDayLog& kfc::CDayLog::operator<<(long n)
{
	if(Lock())
	{
		char tmpbuf[16];
		snprintf(tmpbuf, sizeof(tmpbuf), "%ld", n);
		_log_buffer += tmpbuf;
		//write(_fd,tmpbuf,strlen(tmpbuf));
	}
	return *this;
}

kfc::CDayLog& kfc::CDayLog::operator<<(unsigned long n)
{
	if(Lock())
	{
		char tmpbuf[16];
		snprintf(tmpbuf, sizeof(tmpbuf), "%lu", n);
		_log_buffer += tmpbuf;
		//write(_fd,tmpbuf,strlen(tmpbuf));
	}
	return *this;
}

kfc::CDayLog& kfc::CDayLog::operator<<(long long n)
{
	if(Lock())
	{
		char tmpbuf[32];
		snprintf(tmpbuf, sizeof(tmpbuf), "%lld", n);
		_log_buffer += tmpbuf;
		//write(_fd,tmpbuf,strlen(tmpbuf));
	}
	return *this;
}

kfc::CDayLog& kfc::CDayLog::operator<<(unsigned long long n)
{
	if(Lock())
	{
		char tmpbuf[32];
		snprintf(tmpbuf, sizeof(tmpbuf), "%llu", n);
		_log_buffer += tmpbuf;
		//write(_fd,tmpbuf,strlen(tmpbuf));
	}
	return *this;
}

kfc::CDayLog& kfc::CDayLog::operator<<(double n)
{
	if(Lock())
	{
		char tmpbuf[16] = {0};
		snprintf(tmpbuf, sizeof(tmpbuf) - 1, "%f", n);
		_log_buffer += tmpbuf;
		//write(_fd,tmpbuf,strlen(tmpbuf));
	}
	return *this;
}

kfc::CDayLog& kfc::CDayLog::operator<<(float n)
{
	if(Lock())
	{
		char tmpbuf[16] = {0};
		snprintf(tmpbuf, sizeof(tmpbuf) - 1, "%f", n);
		_log_buffer += tmpbuf;
		//write(_fd,tmpbuf,strlen(tmpbuf));
	}
	return *this;
}

kfc::CDayLog& kfc::CDayLog::operator<<(const string& s)
{
	if(Lock())
	{
		_log_buffer += s;
		//write(_fd,s.c_str(),s.length());
	}
	return *this;
}
