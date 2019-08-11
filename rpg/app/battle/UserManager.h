/*
 * UserManager.h
 *
 *  Created on: 2019年6月20日
 *      Author: Administrator
 */

#ifndef USER_MANAGER_H_
#define USER_MANAGER_H_

#include "BattleBaseInc.h"

class UserManager: public CSingleton<UserManager> {
private:
	friend class CSingleton<UserManager>;
	UserManager();
	~UserManager();

public:
	int Process(uint32_t uid, logins::SQuery *req, logins::SQueryResult *resp);
	int Process(uint32_t uid, logins::SLogin *req, logins::SLoginResult *resp);
	int Process(uint32_t uid, copy::CSSavePlayerConfig *resp);

public:
	int Sync(const UserCache &cache, uint32_t cmd, msgs::SPlayerLoginData *resp);
	int Sync(const UserCache &cache, uint32_t cmd, dbs::TPlayer *resp);
	int Sync(const UserCache &cache, uint32_t cmd, msgs::SPlayerMoneyList *resp);
	int Sync(const UserCache &cache, uint32_t cmd, dbs::TPlayerConfig *resp);

public:
	bool onLogin(uint32_t uid);
	bool ActorOffline(uint32_t uid);
	bool ActorOnline(uint32_t uid);
	bool AddBase(UserCache &cache, const string &open_id);
	bool GetUid(const string &open_id, uint32_t &uid, bool &is_new);
	bool GetNextUid(uint32_t &uid);
	bool AddExp(uint32_t uid, uint32_t exp);
	bool AddMoney(uint32_t uid, uint32_t id, uint32_t num, const string &code);
	bool UseMoney(uint32_t uid, uint32_t id, uint32_t num, const string &code);
	uint32_t GetMoney(uint32_t uid, uint32_t id);
	bool AddItem(uint32_t uid, uint32_t id, uint32_t num, const string &code, uint32_t bag=1);
	bool UseItem(uint32_t uid, uint32_t id, uint32_t num, const string &code);
	bool doTestLevel(uint32_t uid, uint32_t level);
	uint32_t TryUseItem(uint32_t uid, uint32_t id, uint32_t num, const string &code);
	uint32_t TryUseItemMulti(uint32_t uid, uint32_t id, uint32_t num, uint32_t multi, const string &code);
	bool Reward(uint32_t uid, const Award &v, const string &code, uint32_t bag=1);
	bool AddHangPower(UserCache &cache, uint32_t power);
	bool UseHangPower(UserCache &cache, uint32_t power);
	bool CalcProperty(const UserCache &cache, byte rid, PropertySets &props);
	uint32_t GetGoldDiscount(uint32_t gold);

public:
	static void GetPlayerMsg(const UserCache &data, dbs::TPlayer *msg);
	static const char* m_player_config_key[];
};

#endif /* APP_BATTLE_USERMANAGER_H_ */
