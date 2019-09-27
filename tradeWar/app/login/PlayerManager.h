/*
 * PlayerManager.h
 *
 *  Created on: 2015-8-31
 *      Author: Administrator
 */

#ifndef PLAYERMANAGER_H_
#define PLAYERMANAGER_H_

#include "Player.h"
#include "FdManager.h"
#include "LogicManager.h"

#define CACHE_STATE_IDLE 0
#define CACHE_STATE_BUSY 1
#define CACHE_MAX_COUNT 1500
#define CACHE_CHECK_INTER 10
#define CACHE_STAT_INTER 300
#define CACHE_FRESH_INTER 30

struct LruCache {
	uint32_t uid;
	uint32_t stamp;
	LruCache() {
		uid = 0;
		stamp = 0;
	}
	void set_stamp() {
		stamp = LogicManager::GlobalTime;
	}
	bool operator ==(const LruCache & another) {
		return uid == another.uid;
	}
};

class PlayerManager {
public:
	static PlayerManager* getInstance() {
		static PlayerManager pm;
		return &pm;
	}
	~PlayerManager();
private:
	PlayerManager();
public:
	bool doPacket(CNetPacket * packet);
	bool doLogin(CNetPacket * packet);
	bool doTencentUserInfo(CNetPacket * packet);
	bool doTencentFriendInfo(CNetPacket * packet);
	bool doTransitLogin(CNetPacket * packet);
	bool doGetBlueInfoAnswer(CNetPacket * packet);
	bool doPayGetTokenAnswer(CNetPacket *packet);
	bool sendToAccess(CNetPacket* packet);
	bool sendToBattle(CNetPacket* packet);
	bool onSecondTimer();
	void getCountryPlayer(byte country, vector<Player *> &vecPlayers);
	bool addPlayer(Player * player);
	bool PrintStat();
	bool onHeroLevelUp(uint32_t uid);
	bool sendToTransit(CNetPacket *packet);
	bool setPlayerPropChange(uint32_t uid);
	bool IsOnline(uint32_t uid);
	bool isLoadComplete(uint32_t uid);
	bool GetOnlineUsers(vector<uint32_t> & vUids);
	bool getUserInfo(uint32_t uid, DataUser& dataUser);
	bool forceKick(uint32_t uid, const string & reason);
	bool offlineProcess(uint32_t uid, const string & reason);
	bool InformTransit(uint32_t uid);
	bool IsNewUser(uint32_t uid, bool &isNew);
	Player* CreatePlayer(uint32_t uid, uint32_t platform = 0);
	Player* LoadForcePlayer(uint32_t uid);
	Player* LoadExistPlayer(uint32_t uid);
	void FreshLru(uint32_t uid);
	bool delLruPlayerCache(uint32_t uid);
	bool AddiactionNotify(uint32_t uid, uint32_t hour);
	bool sendActTime();
private:
	bool IsInternal();
	bool IsIdle(uint32_t uid);
	bool GetUid(uint32_t serverId, uint32_t platform, string & openId, uint32_t & uid);
	bool LoginConfirm(uint32_t uid, byte ret);
private:
	map<uint32_t, Player*> m_players;
	map<uint32_t, Player*> m_onlines;
	list<LruCache> m_lru_player_cache;
	list<LruCache> m_lru_npc_cache;
	uint32_t m_last_lru_time;
	uint32_t m_last_stat_time;
	uint32_t m_load_times;
	uint32_t m_hit_times;
};

#endif /* PLAYERMANAGER_H_ */
