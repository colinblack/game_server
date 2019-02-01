/*
 * Data4399Log.cpp
 *
 *  Created on: 2015-5-12
 *      Author: Ralf
 */
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

int CData4399Log::fd = -1;
int CData4399Log::last_day = 0;
int CData4399Log::server = 0;
string CData4399Log::sid;

#define DATA_LOG_RECORD_MAX_SIZE 1000

bool CData4399Log::init( struct tm *p )
{
	if(server < 0)
	{
		return false;
	}

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
	if(!Config::GetValue(logDir, "data_4399_log_path"))
	{
		server = -1;
		return false;
	}
	string tcpserver;
	if(!Config::GetValue(tcpserver, "server_listen"))
	{
		server = -1;
		return false;
	}
	size_t pos = tcpserver.find(':');
	string port = tcpserver.substr(pos + 1, tcpserver.length() - pos - 1);
	server = atoi(port.c_str()) - 10000;
	if(server <= 0)
	{
		server = -1;
		return false;
	}
	sid = "S" + CTrans::ITOS(server);

	char buf[200];
	sprintf(buf, "%s/cfsg_%04d%02d%02d.log", logDir.c_str(),1900+p->tm_year, p->tm_mon + 1, p->tm_mday);
	if(Atomic::CompareAndSwap(&fd, -1, -2))
	{
		fd = open(buf, O_CREAT | O_WRONLY | O_APPEND, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
	}
	return fd >= 0;
}

void CData4399Log::DataLog(const char *openid, const char *name, const char *ip, const char *chat)
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

	sprintf( buf, "cfsg|%s|%s|%s|%s|%s\n", sid.c_str(), openid, name, realIp.c_str(), chat);
	write(fd,buf,strlen(buf));
}

std::string& CData4399Log::ParseIP( const std::string pyIp, std::string& realIp )
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
	std::vector<std::string> portvec;
	CBasic::StringSplit(realIp, std::string(":"), portvec);
	realIp = portvec[0];
	return realIp;
}


