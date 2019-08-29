/*
 * DailyLoginManager.h
 *
 *  Created on: 2018年9月6日
 *      Author: rein
 */

#ifndef _DAILY_LOGIN_MANAGER_H_
#define _DAILY_LOGIN_MANAGER_H_

#include "IManager.h"
#include "Award.h"

#define DAILY_SIGN_BEGIN_DAY 1
#define DAILY_SIGN_LOOP 30

class DailyLoginManager : public IManager {
public:
	DailyLoginManager();
	virtual ~DailyLoginManager();
	virtual bool doPacket(CNetPacket* packet);
	bool load(uint32_t uid);
	bool doReward(CNetPacket* packet);
	bool doSign(CNetPacket* packet);
	bool sendData();
	bool sendSign();
	bool saveData();
	void onReward(byte ret, uint32_t type, const Award &reward);
	void onSign(byte ret, uint32_t type, const Award &award);
	void resetSign();
private:
	vector<uint32_t> m_data;
	vector<byte> m_sign;
	uint32_t m_sign_ts;
};

#endif /* _DAILY_LOGIN_MANAGER_H_ */
