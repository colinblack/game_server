/*
 * LogicTopTenUser.h
 *
 *  Created on: 2013-3-6
 *      Author: Administrator
 */

#ifndef LOGICTOPTENUSER_H_
#define LOGICTOPTENUSER_H_

#include "LogicInc.h"

class CLogicTopTenUser {
public:
	CLogicTopTenUser();
	virtual ~CLogicTopTenUser();

	int GetInfo(DataTopTenUser &data);
	int SetUserLevel(unsigned uid, int level,int leveltemp);
	int SetHeroPower(unsigned uid, unsigned power, bool &error);
	int SetUserPlunder(unsigned uid, unsigned uidLock);
	bool CheckTime(unsigned uid, int type);
	int Reward(unsigned uid, int type);
protected :
	CDataTopTenUser* GetCDataTopTenUser();
};

#endif /* LOGICTOPTENUSER_H_ */
