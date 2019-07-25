/*
 * 	ZhuLingManager.h
 *
 * 	2019.07.19
 *
 *  auto: next
 *
 * */

#ifndef _ZHULING_MANAGER_H_
#define _ZHULING_MANAGER_H_

#include "BattleBaseInc.h"

enum FormatType {
	FORMAT_LEVEL = 1,
	FORMAT_ADVANCE = 2,
};

class ZhuLingManager:public CSingleton<ZhuLingManager> {
private:
	friend class CSingleton<ZhuLingManager>;
	ZhuLingManager();
public:

	const DataEquip& GetRoleEquip(const UserCache& cache, uint32_t rid, uint32_t part);
	bool isPartExist(uint32_t part);
	bool addZhuLingInfo(UserCache& cache, uint32_t roleId);
	bool CalcProperty(const UserCache &cache, byte rid, PropertySets &props);
	bool format(UserCache& cache, uint32_t rid, uint32_t part, dbs::TPlayerEquip& data, uint32_t type);
	uint32_t getPart(uint32_t index);
public:

	int Process(uint32_t uid, logins::SopenZhulingReq* req);
	int Process(uint32_t uid, logins::SzhulingUpLevelReq *req, logins::SzhulingUpLevelResp *resp);
	int Process(uint32_t uid, logins::SzhulingUpAdvanceReq *req, logins::SzhulingUpAdvanceResp *resp);
public:
	int Sync(const UserCache& cache, uint32_t cmd, msgs::SInts * msg);
};

#endif /*_ZHULING_MANAGER_H_*/
