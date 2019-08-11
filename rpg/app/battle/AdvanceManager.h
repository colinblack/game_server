/*
 * AdvanceManager.h
 *
 *  Created on: 2019年6月22日
 *      Author: Administrator
 */

#ifndef ADVANCE_MANAGER_H_
#define ADVANCE_MANAGER_H_

#include "BattleBaseInc.h"
#define IS_BAG_ADVANCE(bag) ((bag)>(BAG_ADVANCE_HORSE)&&(bag)<=(BAG_ADVANCE_WING)+MAX_ROLE_COUNT)


class AdvanceManager: public CSingleton<AdvanceManager> {
private:
	friend class CSingleton<AdvanceManager>;
	AdvanceManager();
	~AdvanceManager();

public:
	int Process(uint32_t uid, logins::SActiveAdvance *req);
	int Process(uint32_t uid, logins::SAdvanceReq *req, logins::SAdvanceResp *resp);
	int Process(uint32_t uid, logins::SAdvanceEatDan *req);
	int Process(uint32_t uid, logins::SOneKeyDressReq *req);
	int Process(uint32_t uid, logins::SDressReq *req);
	int Process(uint32_t uid, logins::SStrengthEquipReq *req);
	int Process(uint32_t uid, logins::SRecycleReq *req);
	int Process(uint32_t uid, logins::SLearnSkillReq *req);
	int Process(uint32_t uid, logins::SAdvanceAwakenReq *req);
	int Process(uint32_t uid, logins::SActiveAdvanceTargetReq *req);
public:
	int Sync(const UserCache &cache, uint32_t cmd, msgs::SPlayerAdvanceInfo *resp);
	int Sync(const UserCache &cache, uint32_t cmd, msgs::SPlayerAdvanceAwakenInfo *resp);
	int Sync(const UserCache &cache, uint32_t cmd, msgs::SIntIntMap *resp);
public:
	bool CalcProperty(const UserCache &cache, byte rid, PropertySets &props);
	bool GetEntityShows(const UserCache &cache, byte rid, map<int16_t, int32_t> &show);
	uint16_t GetShowId(byte type);
	void OnLevelUp(const DataAdvance &data);
	bool setStrengthExt(DataEquip& data, uint32_t level);
	uint32_t getStrengthExt(DataEquip& data);
	bool dress(UserCache& cache, uint32_t rid, uint32_t ud);
	bool addDataTarget(UserCache& cache, uint32_t type);
};

#endif /* ADVANCE_MANAGER_H_ */
