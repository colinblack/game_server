/*
 * AdvanceManager.h
 *
 *  Created on: 2019年6月22日
 *      Author: Administrator
 */

#ifndef ADVANCE_MANAGER_H_
#define ADVANCE_MANAGER_H_

#include "BattleBaseInc.h"

class AdvanceManager: public CSingleton<AdvanceManager> {
private:
	friend class CSingleton<AdvanceManager>;
	AdvanceManager();
	~AdvanceManager();

public:
	int Process(uint32_t uid, logins::SActiveAdvance *req);
	int Process(uint32_t uid, logins::SAdvanceReq *req, logins::SAdvanceResp *resp);
	int Process(uint32_t uid, logins::SAdvanceEatDan *req);

public:
	int Sync(const UserCache &cache, uint32_t cmd, msgs::SPlayerAdvanceInfo *resp);

public:
	bool CalcProperty(const UserCache &cache, byte rid, PropertySets &props);
	bool GetEntityShows(const UserCache &cache, byte rid, map<int16_t, int32_t> &show);
	uint16_t GetShowId(byte type);
	void OnLevelUp(const DataAdvance &data);

};

#endif /* ADVANCE_MANAGER_H_ */
