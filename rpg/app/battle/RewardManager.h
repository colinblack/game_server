/*
 * RewardManager.h
 *
 *  Created on: 2019年7月18日
 *      Author: colin
 */

#ifndef APP_BATTLE_REWARDMANAGER_H_
#define APP_BATTLE_REWARDMANAGER_H_

#include "BattleBaseInc.h"


#define RETROACTION_GOLD_COUNT 100 //补签消耗100元宝
#define GET_TARGET_REWARD_GAP  7


enum PlayerDaliyType{
 	ePlayerDaliyCommon = 0,  //免费签到
	ePlayerDaliyRetroaction = 2 //补签
};

enum LevelRewardStatus{
	eStatusEmpty	= 0,   //不能领取
	eStatusOwn		= 1,   //可以领取
	eStatusGot		= 3    //已经领取
};


class RewardManager: public CSingleton<RewardManager>{
private:
	friend class CSingleton<RewardManager>;
	RewardManager();


public:
	int Process(uint32_t uid, logins::SPlayerSignEveryDayReq* req);
	int Process(uint32_t uid, logins::SGetSignEverydayRwardReq* req);
	int Process(uint32_t uid, logins::SGetLevelRwardReq* req);
	int Sync(const UserCache &cache, uint32_t cmd, msgs::SPlayerSignEveryDay *resp);
	int Sync(const UserCache &cache, uint32_t cmd, msgs::SPlayerLevelReward *resp);

};



#endif /* APP_BATTLE_REWARDMANAGER_H_ */
