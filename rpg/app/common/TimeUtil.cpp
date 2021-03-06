/*
 * TimeUtil.cpp
 *
 *  Created on: 2011-5-27
 *      Author: dada
 */

#include "TimeUtil.h"
#include "Common.h"

extern long timezone;

namespace Time
{
	unsigned g_nGlobalTime = 0;
}

bool Time::Init()
{
	tsc_init();
	UpdateGlobalTime();
	return true;
}

bool Time::UpdateGlobalTime()
{
	g_nGlobalTime = time(NULL);
	return true;
}

unsigned Time::GetGlobalTime()
{
	return g_nGlobalTime;
}

bool Time::IsToday(unsigned ts)
{
	return ((g_nGlobalTime - timezone) / 86400) == ((ts - timezone) / 86400);
}

bool Time::IsYestoday(unsigned ts)
{
	return ((g_nGlobalTime - 86400 - timezone) / 86400) == ((ts - timezone) / 86400);
}

bool Time::IsThisWeek(unsigned ts)
{
	uint32_t weekBeginTs = GetWeekBeginTs(g_nGlobalTime);
	if(weekBeginTs > 0)
	{
		return ts >= weekBeginTs && ts < weekBeginTs + 7 * 86400;
	}
	return false;
}
int Time::ThroughDay(unsigned beg, unsigned end)
{
	return ((end - timezone) / 86400 - (beg - timezone) / 86400);
}
uint32_t Time::GetWeekBeginTs(unsigned ts)
{
	time_t nts = ts;
    struct tm* ptm = localtime(&nts);
    if(ptm != NULL)
    {
		unsigned int wday = ptm->tm_wday;
		unsigned int frontDays = (wday == 0) ? 6 : (wday - 1);
		unsigned int todaySecond = ptm->tm_hour * 3600 + ptm->tm_min * 60 + ptm->tm_sec;
		return ts - frontDays * 86400 - todaySecond;
    }
    else
    {
    	return 0;
    }
}

unsigned Time::GetTodayBeginTs()
{
	return g_nGlobalTime - GetTodaySecond();
}

unsigned Time::GetTodaySecond()
{
	return GetDaySecond(g_nGlobalTime);
}
unsigned Time::GetDayBeginTs(unsigned ts)
{
	return ts - GetDaySecond(ts);
}

unsigned Time::GetDaySecond(unsigned ts)
{
	time_t nts = ts;
	struct tm* ptm = localtime(&nts);
	return (ptm != NULL) ? (ptm->tm_hour * 3600 + ptm->tm_min * 60 + ptm->tm_sec) : 0;
}

unsigned Time::GetHour(unsigned ts){
	time_t nts = ts;
	struct tm* ptm = localtime(&nts);
	return ptm->tm_hour;
}

const string Time::getTimeStr(unsigned ts)
{
	time_t nts = ts;
	struct tm* ptm = localtime(&nts);
	char str[128];
	snprintf(str, sizeof(str), "%u-%u-%u %u:%u:%u", ptm->tm_year + 1900, ptm->tm_mon + 1, ptm->tm_mday, ptm->tm_hour, ptm->tm_min, ptm->tm_sec);
	return str;
}

const string Time::getTimeStrNew(unsigned ts)
{
	time_t nts = ts;
	struct tm* ptm = localtime(&nts);
	char str[128];
	snprintf(str, sizeof(str), "%u_%u_%u_%u_%u_%u", ptm->tm_year + 1900, ptm->tm_mon + 1, ptm->tm_mday, ptm->tm_hour, ptm->tm_min, ptm->tm_sec);
	return str;
}
const string Time::getDayStr(unsigned ts)
{
	time_t nts = ts;
	struct tm* ptm = localtime(&nts);
	char str[128];
	snprintf(str, sizeof(str), "%u_%u_%u", ptm->tm_year + 1900, ptm->tm_mon + 1, ptm->tm_mday);
	return str;
}
