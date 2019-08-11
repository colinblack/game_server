/*
 * OnlineReward.h
 *
 *  Created on: 2019年7月25日
 *      Author: memory
 */

#ifndef ONLINEREWARD_H_
#define ONLINEREWARD_H_

#include "BattleBaseInc.h"

class OnlineRewardManager: public CSingleton<OnlineRewardManager> {
private:
	friend class CSingleton<OnlineRewardManager>;
	OnlineRewardManager();
	~OnlineRewardManager();

public:
	bool DailyReset(UserCache &cache);

public:
	int Process(uint32_t uid, logins::COnlineRewardReq *req);

public:
	int Sync(const UserCache &cache, uint32_t cmd, msgs::SPlayerOnlineReward *resp);// 4072 - 1568

};

#endif /* ONLINEREWARD_H_ */
