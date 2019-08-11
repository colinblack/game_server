/*
 * ReinCarnShengManager.h
 *
 *  Created on: 2019年7月29日
 *      Author: next
 */

#include "BattleBaseInc.h"

class ReinCarnShengManager: public CSingleton<ReinCarnShengManager> {
private:
	friend class CSingleton<ReinCarnShengManager>;
	ReinCarnShengManager();
public:
	bool CalcProperty(const UserCache &cache, byte rid, PropertySets &props);
	bool getShengMissionProps(const UserCache &cache, map<byte, uint32_t> role_equip, PropertySets &props);
	bool addShengMission(UserCache& cache, uint32_t reinCarnLevel);
	bool addShengCount(UserCache& cache, uint32_t reinCarnLevel);
	int32_t getIndexByPart(int32_t part);
	bool onShengMission(uint32_t uid, uint32_t type,uint32_t num);
	bool onShengSubMission(uint32_t uid, uint32_t type, uint32_t subType, uint32_t num);
public:
	int Process(uint32_t uid, logins::SCommitShengMissionReq *req);
	int Process(uint32_t uid, logins::SRequestShengMissionReq *req);

public:
	int Sync(const UserCache& cache, uint32_t cmd, msgs::SShengInfo *resp);
};
