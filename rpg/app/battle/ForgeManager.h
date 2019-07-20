/*
 * ForgeManager.h
 *
 *  Created on: 2019年7月3日
 *      Author: Administrator
 */

#ifndef FORGE_MANAGER_H_
#define FORGE_MANAGER_H_

#include "BattleBaseInc.h"

class ForgeManager: public CSingleton<ForgeManager> {
private:
	friend class CSingleton<ForgeManager>;
	ForgeManager();
	~ForgeManager();

public:
	bool FormatMsg(const DataForge &data, dbs::TPlayerEquip &msg);
	bool CalcProperty(const UserCache &cache, byte rid, PropertySets &props);

public:
	int Process(uint32_t uid, logins::SStrengthenReq *req, logins::SStrengthenResp *resp);

public:
	int Sync(const UserCache &cache, uint32_t cmd, msgs::SPlayerEquipList *resp);

};

#endif /* FORGE_MANAGER_H_ */
