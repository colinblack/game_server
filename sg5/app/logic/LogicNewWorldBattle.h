/*
 * LogicNewWorldBattle.h
 *
 *  Created on: 2015-2-12
 *      Author: Ralf
 */

#ifndef LOGICNEWWORLDBATTLE_H_
#define LOGICNEWWORLDBATTLE_H_


#define NEW_WORLD_BATTLE_RECOVER_COST 4065
#define NEW_WORLD_BATTLE_RUSH_COST 4066
#define NEW_WORLD_BATTLE_CLONE_COST 4067
#define NEW_WORLD_BATTLE_COLLECTOTHER_COST	4068
#define NEW_WORLD_BATTLE_DOUBLE_COST 4069
#define NEW_WORLD_BATTLE_BLINK_COST		4074
#define NEW_WORLD_BATTLE_KILL_REWARD_NEW 4055

#include "LogicInc.h"
class CLogicNewWorldBattle {
public:
	CLogicNewWorldBattle();
	virtual ~CLogicNewWorldBattle();
	CDataNewWorldBattle *GetDataNewWorldBattle();

	int GetWorld(Json::Value &allresult);

	int GetCity(unsigned cid, Json::Value &allresult);
	int GetBattle(unsigned cid, Json::Value &allresult);
	int GetBattleList(unsigned cid, unsigned camp, Json::Value &allresult);
	int GetHero(unsigned uid, unsigned index, Json::Value &allresult);
	int GetAllHero(unsigned uid, Json::Value &allresult);
	int SetHero(unsigned uid, unsigned index, const Json::Value &para, Json::Value &allresult);

	int Move(unsigned uid, unsigned index, unsigned cid, bool leave, unsigned fly, Json::Value &allresult);
	int Change(unsigned uid, unsigned index, unsigned type, Json::Value &allresult);
	int Clone(unsigned uid, unsigned index, unsigned equd, Json::Value &allresult);
	int Rush(unsigned uid, unsigned index, unsigned equd, bool fly, Json::Value &allresult);
	int Recover(unsigned uid, unsigned index, unsigned equd, unsigned num, Json::Value &allresult);
	int Double(unsigned uid, unsigned kingdom, unsigned cid, unsigned equd, Json::Value &allresult);
	int CollectOther(unsigned uid, unsigned cid, unsigned equd, Json::Value &allresultk);
	int Blink(unsigned uid, unsigned cid, unsigned equd, const Json::Value &freeHeroIndex, Json::Value &allresult);

	int Buildyjt(unsigned uid, unsigned index, Json::Value &allresult);

	int KillRank(string path = "../webroot/data/newworldbattlekill");
	int KillReward();

	int Restart();

	int Watch();
	int Fix();
	int Reset();
	int Back();
	int Test(NewWorldBattleHero &attacker, unsigned hpa, NewWorldBattleHero &defender, unsigned hpd);
	int Test(NewWorldBattleHero &attacker, NewWorldBattleHero &defender, unsigned &times);
};


#endif /* LOGICNewWorldBattle_H_ */
