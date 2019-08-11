/*	ActivityManager.h
 *
 * 	2019.07.15
 *
 *  auto: next
 */
#ifndef _ACTIVITY_MANAGER_H_
#define _ACTIVITY_MANAGER_H_

#include "BattleBaseInc.h"
//副本对应活动ID
enum ActivityType {
	EXPER_ACTIVITY_TYPE = 1,
	MATER_ACTIVITY_TYPE = 2,
	WEAPON_ACTIVITY_TYPE = 4,
	GUARD_ACTIVITY_TYPE = 5,
	WORLD_BOSS_ACTIVITY_TYPE = 6,
	VIP_BOSS_ACTIVITY_TYPE = 7,
	FORGE_ACTIVITY_TYPE = 10,
	PURIFY_ACTIVITY_TYPE = 11
};

class ActivityManager:public CSingleton<ActivityManager> {
private:
	friend class CSingleton<ActivityManager>;
	ActivityManager();
public:
	bool addActInfo(uint32_t uid, uint32_t id);
	bool addActCnt(uint32_t uid, uint32_t id);
	bool ReflashActive(uint32_t uid);
	bool SyncActivity(UserCache& cache, uint32_t actId, uint32_t num);
	bool ActorLogin(uint32_t uid);
	bool onHour(uint32_t lastHour);
public:
	int Process(uint32_t uid, logins::SGetActivityReq *req);
	int Process(uint32_t uid, logins::SGetActivityRewardReq *req);
public:
	int Sync(const UserCache &cache, uint32_t cmd, msgs::SDailyActivityInfo *resp);
};

#endif /*_ACTIVITY_MANAGER_H_*/
