/*
 * LogicVipRebates.h
 *
 *  Created on: 2014年7月15日
 *      Author: Administrator
 */

#ifndef LOGICVIPREBATES_H_
#define LOGICVIPREBATES_H_
#include "LogicInc.h"
class CLogicVipRebates {
public:
	static CDataVipRebates* GetCDataVipRebates();
	int getVips(uint32_t viplvl, vector<VipUser> &rlt);
	int setVip(uint32_t uid, const string &name, uint32_t fromLvl, uint32_t toLvl);
	uint32_t getTime();
	int clear();
};

#endif /* LOGICVIPREBATES_H_ */
