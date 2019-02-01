
#include <ctime>
#include <string>
#include <vector>
#include <stdint.h>

#include "basic.h"
#include "trans.h"
#include "ctime.h"

int CTime::GetDayInterval(time_t tFrom, time_t tTo)
{
	return ((int)CTime::GetDayBeginTime(tTo)-(int)CTime::GetDayBeginTime(tFrom))/CTime::SECONDS_OF_DAY;
}



time_t CTime::GetDayBeginTime(time_t tTime)
{
	tm tTm = *localtime(&tTime);
	tTm.tm_hour	= 0;
	tTm.tm_min	= 0;
	tTm.tm_sec	= 0;	
	return CTime::MakeTime(tTm);
}

time_t CTime::GetMonthBeginTime(time_t tTime) 
{
	tm tTm = *localtime(&tTime);
	tTm.tm_hour	= 0;
	tTm.tm_min	= 0;
	tTm.tm_sec	= 0;
	tTm.tm_mday = 1 ;
	return CTime::MakeTime(tTm);
}

const std::string CTime::FormatTime(const std::string& sFmt, const tm& stTime)
{
	char buf[255]={};
	strftime(buf, sizeof(buf)-1, sFmt.c_str(), &stTime);
	return buf;
}

const std::string CTime::FormatTime(const std::string& sFmt, time_t tTime)
{
	char buf[255]={};
	strftime(buf, sizeof(buf)-1, sFmt.c_str(), localtime(&tTime));
	return buf;
}

time_t CTime::MakeTime(tm& stTime)
{
	return mktime(&stTime);
}

time_t CTime::MakeTime(int iYear, int iMon, int iDay, int iHour, int iMin, int iSec)
{
	tm stTime;
	stTime.tm_year	= iYear-1900;
	stTime.tm_mon	= iMon-1;
	stTime.tm_mday	= iDay;
	stTime.tm_hour	= iHour;
	stTime.tm_min	= iMin;
	stTime.tm_sec	= iSec;

	return mktime(&stTime);
}


int CTime::ParseDate(const std::string& sDate, int& iYear, int& iMon, int& iDay, const std::string& sDelim)
{
	std::vector<std::string> vItems;
	CBasic::StringSplit(sDate, sDelim, vItems);

	if (vItems.size() < 3)
	{
		return -1;
	}

	iYear	= CTrans::STOI(vItems[0]);
	iMon	= CTrans::STOI(vItems[1]);
	iDay	= CTrans::STOI(vItems[2]);

	return 0;
}

int CTime::GetDate(int& iYear, int& iMon, int& iDay, int iTime)
{
	if (iTime < 0)
	{
		iTime = time(NULL);
	}

	tm* ptm = localtime((time_t*)&iTime);

	iYear	= ptm->tm_year+1900;
	iMon	= ptm->tm_mon+1;
	iDay	= ptm->tm_mday;

	return iTime;
}

int CTime::GetCurrentYear( void )
{
	int iYear = 0;
	int iTime = time(NULL);	
	tm* ptm = localtime((time_t*)&iTime);
	iYear	= ptm->tm_year+1900;
	
	return iYear;
}

int CTime::CheckDate(int& iYear, int& iMonth, int& iDay)
{
	static int s_nDays[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int iRetCode = 0;
	if (iMonth < 1)
	{
		iMonth = 1;
		iRetCode = 0x02;
	}
	else if (iMonth > 12)
	{
		iMonth = 12;
		iRetCode = 0x02;
	}
	else if (iMonth == 2)
	{
		if (iDay < 1)
		{
			iDay = 1;
			iRetCode |= 0x01;
			return iRetCode;
		}
		int nDays = ((iYear%400==0) || (iYear%100!=0 && iYear%4==0)) ? 29 : 28;
		if (iDay > nDays)
		{
			iDay = nDays;
			iRetCode |= 0x01;
			return iRetCode;
		}
		return iRetCode;
	}
	if (iDay < 1)
	{
		iDay = 1;
		iRetCode |= 0x01;
	}
	else if (iDay > s_nDays[iMonth-1])
	{
		iDay = s_nDays[iMonth-1];
		iRetCode |= 0x01;
	}

	return iRetCode;
}

std::string CTime::UTCTime(time_t tTime)
{
	char buf[255]={};
	strftime(buf, sizeof(buf)-1, "%a, %d %b %Y %H:%M:%S UTC", gmtime(&tTime));
	return buf;
}

timeval CTime::GetTimeOfDay()
{
	timeval tv;
	gettimeofday(&tv, 0);
	return tv;
}

time_t CTime::GetUSInterval(const timeval& tvfrom, const timeval& tvto)
{
	return (tvto.tv_sec-tvfrom.tv_sec)*1000000+(tvto.tv_usec-tvfrom.tv_usec);
}

time_t CTime::GetMSInterval(const timeval& tvfrom, const timeval& tvto)
{
	return (tvto.tv_sec-tvfrom.tv_sec)*1000+(tvto.tv_usec-tvfrom.tv_usec)/1000;
}

int CTime::GetCurrentuTime()
{
	uint64_t time=0;
	struct timeval now;
	gettimeofday( &now , NULL );
	time = now.tv_sec;
	time = time*1000000;
	time += now.tv_usec;
	return time;
}

int CTime::GetCurrentMSTime()
{
	return GetCurrentuTime()/1000;
}

time_t CTime::ParseDate(const std::string& data)
{
	struct tm t;
	if (strptime(data.c_str(), "%F %T", &t)==NULL)
	{
		return 0;
	}
	return MakeTime(t);
}

bool IsDiffDay( time_t t1, time_t t2 )
{
	// 中国是东八区，比格林威治时间早8小时
	t1 = ( t1 + 8*3600 ) / 86400;
	t2 = ( t2 + 8*3600 ) / 86400;
	return t1 != t2;
}

bool IsDiffHour( time_t t1, time_t t2 )
{
	if (IsDiffDay(t1, t2))
	{
		return true;
	}

	t1 = (t1%86400)/3600;
	t2 = (t2%86400)/3600;

	return t1 != t2;
}

