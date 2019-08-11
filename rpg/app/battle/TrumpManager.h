/*
 * TrumpManager.h
 *
 *  Created on: 2019年7月24日
 *      Author: colin
 */

#ifndef APP_BATTLE_TRUMPMANAGER_H_
#define APP_BATTLE_TRUMPMANAGER_H_

#include "BattleBaseInc.h"



#define IS_LAST_FOUR_TRUMP(id)  (id >= 310010006 && id <= 310010009)

struct ActiveTrump{
	uint32_t id;
	uint32_t money;
};



class TrumpManager: public CSingleton<TrumpManager> {
private:
	friend class CSingleton<TrumpManager> ;
	TrumpManager();
	uint32_t GetTrumpLevel(const DataEquip& data);
	uint32_t GetTrumpStage(const DataEquip& data);


public:
	static const ActiveTrump cost_[3];

public:
	int Process(uint32_t uid, logins::STrumpActiveReq* req);
	int Process(uint32_t uid, logins::STrumpUpgradeReq* req);
	int Process(uint32_t uid, logins::SActiveTrumpSkillReq* req);
	int Process(uint32_t uid, logins::STrumpRequestMissionReq* req);
	int Process(uint32_t uid, logins::SUnlockTrumpReq* req);



	int Sync(const UserCache &cache, uint32_t cmd, msgs::STrumpInfo *resp);


	bool CalcProperty(const UserCache &cache, byte rid, PropertySets &props);
};



#endif /* APP_BATTLE_TRUMPMANAGER_H_ */
