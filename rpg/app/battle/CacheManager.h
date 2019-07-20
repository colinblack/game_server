/*
 * CacheManager.h
 *
 *  Created on: 2019年6月21日
 *      Author: Administrator
 */

#ifndef CACHE_MANAGER_H_
#define CACHE_MANAGER_H_

#include "BattleBaseInc.h"

#define USER_CACHE_TS 36000

class CacheManager: public CSingleton<CacheManager> {
private:
	friend class CSingleton<CacheManager> ;
	CacheManager();
	~CacheManager();
	map<uint32_t, UserCache> m_mapUser;
	map<uint32_t, uint32_t> m_offline;

public:
	bool ActorLogin(uint32_t uid);
	bool ActorOffline(uint32_t uid);
	void OnSecondTimer();
	UserCache& GetUser(uint32_t uid);

private:
	bool LoadBase(UserCache &cache);
	bool LoadPay(UserCache &cache);
	bool LoadPos(UserCache &cache);
	bool LoadRole(UserCache &cache);
	bool LoadSkill(UserCache &cache);
	bool LoadMission(UserCache &cache);
	bool LoadAdvance(UserCache &cache);
	bool LoadEquip(UserCache &cache);
	bool LoadShenQi(UserCache &cache);
	bool LoadBagExtend(UserCache &cache);
	bool LoadForge(UserCache &cache);
	bool LoadAttr(UserCache &cache);
	bool LoadTreasure(UserCache &cache);
	bool LoadRoleSuit(UserCache &cache);
	bool LoadActive(UserCache &cache);
};

#endif /* CACHE_MANAGER_H_ */
