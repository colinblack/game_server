#ifndef __LOGIC_ALLIANCE_BATTLE_H__
#define __LOGIC_ALLIANCE_BATTLE_H__

#include "LogicInc.h"

#define PRICE_K 100
#define PRICE_NK 20

#define ALLIANCE_NPC 70002
#define ALLIANCE_NPC_BIG 70003

#define HUFU_M_C 25
#define HUFU_K_C 30
#define HUFU_NK_C 20

#define CITY_K_ID 40

#define KINGDOM_1_ID 10
#define KINGDOM_2_ID 20
#define KINGDOM_3_ID 30

#define HUFU_ID 	4030
#define HUFU_K 		500		//2
#define HUFU_NK 	200		//1
#define HUFU_A_1 	1000	//5
#define HUFU_A_2 	600		//3
#define HUFU_A_3 	200		//1

class CLogicAllianceBattle
{
public:
	static CDataAllianceBattle* GetCDataAllianceBattle();

	int GetAllCityLimit(Json::Value &result);
	int GetCityPrice(unsigned cid, Json::Value &result);
	int GetAllCityPrice(Json::Value &result);
	int PayCityPrice(unsigned cid, unsigned aid, string &name);
	int StartDefence();
	int GetAllBattlePointLimit(unsigned cid, Json::Value &result);
	int SetDefence(unsigned bid, unsigned uid, const string &name);
	int StartAttack();
	int SetArchive(unsigned bid, unsigned uid, char archiveStr[1048128]);
	int SetNPC(unsigned bid, unsigned npcid, char archiveStr[1048128]);
	int Load(unsigned bid, DataUser &userBy, LoadType loadType, Json::Value &result);
	int Save(unsigned bid, DataUser &userBy, Json::Value &data, Json::Value &result, LoadType loadtype);
	int StartOccupy();
	int ChooseOccupy(unsigned cid, unsigned aid, unsigned flag, unsigned kingdom);
	int RewardAndRestart();
	int BattleNum2Bid(unsigned cnum, unsigned bnum, bool defence);
	int SetHufu(unsigned aid, Json::Value &hufu);
	int GetHufu(unsigned uid, Json::Value &result);
	int HequChanganActivity(unsigned uid, Json::Value &result);
	int ProcessKingdom();

	int RepairAllianceID();
};

#endif
