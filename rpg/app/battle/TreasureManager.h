/*
 * Treasure.h
 *
 *  Created on: 2019年7月2日
 *      Author: next
 */

#ifndef _TREASURE_H_
#define _TREASURE_H_

#include "BattleBaseInc.h"

enum TREASURE_DRAW_TYPE {
	TREASURE_HUNT_EQUIP = 0,
	TREASURE_HUNT_DIANFENG = 2,
	TREASURE_HUNT_SANJIE = 3,
	TREASURE_HUNT_LIUDAO = 4,
	TREASURE_HUNT_MAX
};

class TreasureManager: public CSingleton<TreasureManager> {
private:
	friend class CSingleton<TreasureManager> ;
	TreasureManager();
	~TreasureManager();

public:
	//激活宝物
	int Process(uint32_t uid, logins::SActiveTreasure *req);
	//消耗道具升级
	int Process(uint32_t uid, logins::STreasureAdvance *req);
	//消耗丹药
	int Process(uint32_t uid, logins::STreasureEatDan *req);
	int Process(uint32_t uid, logins::STreasureDrawReq *req, logins::STreasureDrawResp *resp);
	int Process(uint32_t uid, logins::STreasureGetRewardHisReq *req, logins::STreasureGetRewardHisResp *resp);

public:
	//返回所有宝物信息
	int Sync(const UserCache &cache, uint32_t cmd, msgs::STreasureAdvanceInfo *resp);
	int Sync(const UserCache &cache, uint32_t cmd, msgs::SPlayerTreasureInfo *resp);

public:
	bool ActorLogin(uint32_t uid);
	bool InitHunt(UserCache &cache);
	bool FormatHuntMsg(msgs::SPlayerTreasure &msg, const TreasureHunt &data);
	bool DailyReset(TreasureHunt &data);
	bool DoHunt(UserCache &cache, uint32_t type, uint32_t num, vector<int32_t> &ids, vector<int32_t> &items);
	bool DoRandom(const list<int32_t> &pool, Award &award, uint32_t &reward_id, uint32_t &reward_item, uint32_t &xiyou);
	bool SendHunt(const TreasureHunt &data);
	bool CalcProperty(const UserCache &cache, PropertySets &props);
};

#endif /*_TREASURE_H_*/
