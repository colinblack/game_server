/*
 * ShareConfig.h
 *
 *  Created on: 2017年10月14日
 *      Author: Administrator
 */

#ifndef SHARE_CONFIG_H_
#define SHARE_CONFIG_H_

#include "Kernel.h"
#include "Award.h"

struct DailyShare {
	uint32_t interval;
	uint32_t max;
	Award reward;
};

class CShareConfig {
public:
	virtual ~CShareConfig();
	static CShareConfig *getInstance() {
		static CShareConfig instance;
		return &instance;
	}
	bool init(const string &path);
	const DailyShare* getDaily() const {
		return &m_daily;
	}
	Award getInvite() const {
		return m_invite;
	}
protected:
	CShareConfig();

private:
	Award m_invite;
	DailyShare m_daily;
};

#endif /* SHARE_CONFIG_H_ */
