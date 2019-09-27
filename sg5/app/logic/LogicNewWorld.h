/*
 * LogicNewWorld.h
 *
 *  Created on: 2014-9-18
 *      Author: Ralf
 */

#ifndef LOGICNEWWORLD_H_
#define LOGICNEWWORLD_H_

#define NEW_WORLD_RECOVER_COST 4065
#define NEW_WORLD_RUSH_COST 4066
#define NEW_WORLD_CLONE_COST 4067
#define NEW_WORLD_SUPER_CLONE_COST 4115
#define NEW_WORLD_COLLECTOTHER_COST		(4068)
#define NEW_WORLD_DOUBLE_COST			(4069)
#define NEW_WORLD_RUSHTS_COST			(4088)
#define NEW_WORLD_BLINK_COST			(4074)
#define NEW_WORLD_EXPLODE_COST 2010
#define NEW_WORLD_KILL_REWARD_1 50053
#define NEW_WORLD_KILL_REWARD_2 4031
#define NEW_WORLD_KILL_REWARD_NEW 4055

#include "LogicInc.h"
#include "LogicSyncLords.h"
class CLogicNewWorld {
public:
	CLogicNewWorld();
	virtual ~CLogicNewWorld();
	CDataNewWorld *GetDataNewWorld();

	int GetWorld(Json::Value &allresult);
	int GetHistory(unsigned index, Json::Value &allresult);
	int GetMission(Json::Value &allresult);

	int GetCity(unsigned cid, Json::Value &allresult);
	int GetBattle(unsigned cid, Json::Value &allresult);
	int GetBattleList(unsigned cid, unsigned camp, Json::Value &allresult);
	int GetHero(unsigned uid, unsigned index, Json::Value &allresult);
	int GetAllHero(unsigned uid, Json::Value &allresult);
	int SetHero(unsigned uid, unsigned index, const Json::Value &para, Json::Value &allresult);

	int Move(unsigned uid, unsigned index, unsigned cid, bool leave, unsigned fly, Json::Value &allresult);
	int Change(unsigned uid, unsigned index, unsigned type, Json::Value &allresult);
	int Clone(unsigned uid, unsigned index, unsigned equd, Json::Value &allresult, bool issuper = false);
	int Rush(unsigned uid, unsigned index, unsigned equd, bool fly, Json::Value &allresult);
	int Recover(unsigned uid, unsigned index, unsigned equd, unsigned num, Json::Value &allresult);
	int Explode(unsigned uid, unsigned index, unsigned equd, Json::Value &allresult);

	int Challenge(unsigned uid, unsigned &olduid, unsigned cid, string &name, unsigned k);
	int SetChallengeTS(unsigned cid, int set, unsigned k);
	int Collect(unsigned uid, unsigned cid, Json::Value &allresult);
	int Double(unsigned uid, unsigned kingdom, unsigned cid, unsigned equd, Json::Value &allresult);
	int rushTS(unsigned uid, unsigned kingdom, unsigned cid, unsigned equd, Json::Value &allresult);
	int CollectOther(unsigned uid, unsigned cid, unsigned equd, Json::Value &allresultk);
	int Blink(unsigned uid, unsigned cid, unsigned equd, const Json::Value &freeHeroIndex, Json::Value &allresult);

	int Buildyjt(unsigned uid, unsigned index, Json::Value &allresult);

	int UseJM(unsigned uid, unsigned jm, unsigned cid, unsigned kingdom, Json::Value &allresult);
	int BuyNPC(unsigned uid, unsigned cid, unsigned kingdom, Json::Value &allresult);

	int WorldReward();
	int CityReward();
	int StartMission();
	int EndMission();
	int KillRank(string path = "../webroot/data/newworldkill");
	int KillReward();

	int Watch();
	int Fix();
	int Reset();
	int Back();
	int Test(NewWorldHero &attacker, unsigned hpa, NewWorldHero &defender, unsigned hpd);
	int Test(NewWorldHero &attacker, NewWorldHero &defender, unsigned &times);
	int FixOld();
};


#endif /* LOGICNEWWORLD_H_ */
