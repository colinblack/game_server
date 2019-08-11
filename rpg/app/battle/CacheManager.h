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
	map<uint32_t, uint32_t> m_online; // <uid ,onlineTime>
	map<uint32_t,string> m_playerConfig;

public:
	bool Init();
	bool ActorLogin(uint32_t uid);
	bool ActorOffline(uint32_t uid);
	bool ActorOnline(uint32_t uid);
	void OnSecondTimer();
	UserCache& GetUser(uint32_t uid);
	uint32_t GetUserOnlineTime(uint32_t uid);
	bool GetAllUser(vector<uint32_t>& uids);
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
	bool LoadSign(UserCache &cache);
	bool LoadTrump(UserCache &cache);

};

#endif /* CACHE_MANAGER_H_ */
