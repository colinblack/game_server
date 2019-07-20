/*
 * ShenQiManager.h
 *
 *  Created on: 2019年6月27日
 *      Author: Administrator
 */

#ifndef SHENQI_MANAGER_H_
#define SHENQI_MANAGER_H_

#include "BattleBaseInc.h"


class ShenQiManager: public CSingleton<ShenQiManager> {
private:
	friend class CSingleton<ShenQiManager>;
	ShenQiManager();
	~ShenQiManager();
public:
	bool CalcProperty(const UserCache &cache, byte rid, PropertySets &props);

public:
	int Process(uint32_t uid, logins::SShenQiPiece *req);
	int Process(uint32_t uid, logins::SShenQi *req);

public:
	int Sync(const UserCache &cache, uint32_t cmd, msgs::SShenqiInfo *resp);

};

#endif /* SHENQI_MANAGER_H_ */
