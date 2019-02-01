#include "DataLog.h"
#include "Kernel.h"
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include "basic.h"

int CDataLog::fd = -1;
int CDataLog::last_day = 0;

#define DATA_LOG_RECORD_MAX_SIZE 1000

bool CDataLog::init( struct tm *p )
{
	time_t now;
	time( &now );
	localtime_r(&now, p);
	if(last_day != p->tm_mday)
	{
		close(fd);
		fd = -1;
		last_day = p->tm_mday;
	}

	if( fd >= 0 )
	{
		return true;
	}

	string logDir;
	if(!Config::GetValue(logDir, CONFIG_DATA_LOG_PATH))
	{
		return false;
	}

	char buf[200];
	sprintf(buf, "%s/data_%04d%02d%02d.log", logDir.c_str(),1900+p->tm_year, p->tm_mon + 1, p->tm_mday);
	if(Atomic::CompareAndSwap(&fd, -1, -2))
	{
		fd = open(buf, O_CREAT | O_WRONLY | O_APPEND, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
	}
	return fd >= 0;
}

void CDataLog::DataLog(const char *action, const char *ip, const char *type, const char* format, ...)
{
	struct tm p;
	if( !init( &p ) )
	{
		return;
	}
	char buf[DATA_LOG_RECORD_MAX_SIZE];

	std::string realIp;
	if (ip != NULL)
	{
		std::string ipstr(ip);
		if (!ipstr.empty())
		{
			ParseIP( ipstr, realIp );
		}
	}

	sprintf( buf, "%04d%02d%02d %02d:%02d:%02d|%s|%s|%s|",
			1900+p.tm_year, p.tm_mon + 1, p.tm_mday, p.tm_hour,
			p.tm_min, p.tm_sec, action, realIp.c_str(), type );
	int len = strlen(buf);
	va_list args;
	va_start(args, format);
	vsnprintf(buf+len, sizeof(buf)-len-4, format, args);
	va_end(args);
	buf[sizeof(buf) - 4] = '\0';
	strcat(buf, "\r\n");

	write(fd,buf,strlen(buf));
}

std::string& CDataLog::ParseIP( const std::string pyIp, std::string& realIp )
{
	realIp.clear();
	int ip1,ip2,ip3,ip4;
	char buf[20];
	std::vector<std::string> ipvec;
	CBasic::StringSplit(pyIp, std::string(", "), ipvec);
	for( unsigned i = 0; i < ipvec.size(); i++ )
	{
		if( ipvec[i].length() == 40 )
		{
			sscanf(ipvec[i].c_str(), "%02x%02x%02x%02x", &ip1,&ip2,&ip3,&ip4);
			sprintf( buf, "%d.%d.%d.%d", ip1,ip2,ip3,ip4 );
			realIp.append(buf);
		}
		else
		{
			realIp.append(ipvec[i]);
		}
		if( ipvec.size() - 1 != i )
		{
			realIp.append(",");
		}
	}
	return realIp;
}
