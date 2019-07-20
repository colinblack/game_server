/*
 * CopyManager.h
 *
 *  Created on: 2019年6月27日
 *      Author: Administrator
 */
#ifndef COPY_MANAGER_H_
#define COPY_MANAGER_H_
#include "BattleBaseInc.h"
#include "MapManager.h"

#define DEFAULT_COPY_X 588
#define DEFAULT_COPY_Y 876

#define MAGIC_TOWER_BASE 200001000
#define MAGIC_TOWER_COPY 220

class CopyManager: public CSingleton<CopyManager> {
private:
	friend class CSingleton<CopyManager>;
	CopyManager();
	~CopyManager();

public:
	int Process(uint32_t uid, boss::CSEnterReincarnCopy *req);
	int Process(uint32_t uid, boss::CSEnterMagicTowerCopy *req);
	int Process(uint32_t uid, boss::CSEnterMaterialCopy *req);
	int Process(uint32_t uid, boss::CSLeaveCopy *req);
	int Process(uint32_t uid, boss::CSQuickFinish *req);
	int Process(uint32_t uid, boss::CSGotReward *req);

public:
	void onHour(uint32_t hour);
	bool OnMonsterDie(uint32_t uid, uint32_t monster_id, const Point &diePos);
	bool OnHumanDie(uint32_t uid);

private:
	map<uint32_t,vector<uint32_t> > m_saveInfo;
	bool MonsterDrop(uint32_t uid,uint32_t monster_id, const Point &diePos);
	bool checkReset(CopyInfo& copyInfo);

public:
	int Sync(const UserCache &cache, uint32_t cmd, msgs::SPlayerCopyDataList *resp);
	bool sendUpdate(const UserCache &cache, uint32_t copyId);
};

#endif /* COPY_MANAGER_H_ */
