/*
 * TimeUtil.h
 *
 *  Created on: 2011-5-27
 *      Author: dada
 */

#ifndef TIMEUTIL_H_
#define TIMEUTIL_H_

#include <string>
using std::string;

namespace Time {
	bool Init();
	bool UpdateGlobalTime();
	unsigned GetGlobalTime();
	bool IsToday(unsigned ts);
	bool IsThisWeek(unsigned ts);
	int ThroughDay(unsigned beg, unsigned end);
	unsigned GetWeekBeginTs(unsigned ts);
	unsigned GetTodayBeginTs();
	unsigned GetTodaySecond();
	unsigned GetDayBeginTs(unsigned ts);
	unsigned GetDaySecond(unsigned ts);
	const string getTimeStr(unsigned ts);
	const string getTimeStrNew(unsigned ts);
	const string getDayStr(unsigned ts);
	const unsigned int SECOND_OF_HOUR = 3600u;
	const unsigned int SECOND_OF_DAY = 86400u;
	const unsigned int SECOND_OF_WEEK = 604800u;
}
#endif /* TIMEUTIL_H_ */
