/*
 * PurifyManager.h
 *
 *  Created on: 2019年7月3日
 *      Author: Administrator
 */

#ifndef PURIFY_MANAGER_H_
#define PURIFY_MANAGER_H_

#include "BattleBaseInc.h"

class PurifyManager: public CSingleton<PurifyManager> {
private:
	friend class CSingleton<PurifyManager>;
	PurifyManager();
	~PurifyManager();

public:
	bool FormatMsg(const DataForge &data, dbs::TPlayerEquip &msg);
	bool CalcProperty(const UserCache &cache, byte rid, PropertySets &props);

public:
	int Process(uint32_t uid, logins::SPurifyReq *req, logins::SPurifyResp *resp);

};

#endif /* PURIFY_MANAGER_H_ */
