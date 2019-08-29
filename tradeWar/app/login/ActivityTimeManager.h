/*
 * ActivityTimeManager.h
 *
 *  Created on: 2018年12月3日
 *      Author: Administrator
 */

#ifndef ACTIVITY_TIME_MANAGER_H_
#define ACTIVITY_TIME_MANAGER_H_

#include "Kernel.h"

struct ActivityTime {
	uint32_t id;
	uint32_t bts;
	uint32_t ets;
	uint32_t ver;
	uint32_t type;

	ActivityTime() {
		id = 0;
		bts = 0;
		ets = 0;
		ver = 0;
		type = 0;
	}

	inline bool IsOpen() const {
		return Time::GetGlobalTime() >= bts && ets >= Time::GetGlobalTime();
	}

	inline int OpenDay() const {
		return CTime::GetDayInterval(bts, Time::GetGlobalTime()) + 1;
	}
};

class ActivityTimeManager {
public:
	static ActivityTimeManager* getInstance() {
		static ActivityTimeManager _inc;
		return &_inc;
	}
	virtual ~ActivityTimeManager();
	bool init();
	bool reload();
	bool sendInfo(uint32_t uid);
	bool isOpen(uint32_t id) const;
	bool isEnd(uint32_t id) const;
	bool getValidId(vector<uint32_t> &ids) const;
	uint32_t getVer(uint32_t id) const;
	uint32_t getBts(uint32_t id) const;
	uint32_t getOpenDay(uint32_t id) const;
	const ActivityTime* getActTime(uint32_t id) const;
protected:
	ActivityTimeManager();
private:
	map<uint32_t, ActivityTime> m_data;
};

#endif /* ACTIVITY_TIME_MANAGER_H_ */
