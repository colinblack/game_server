/*
 * LogicRechargeRank.h
 *
 *  Created on: 2015-7-28
 *      Author: eddard
 */

#ifndef LOGICRECHARGERANK_H_
#define LOGICRECHARGERANK_H_

#include "LogicInc.h"

class CLogicRechargeRank {
public:
	CLogicRechargeRank();
	static CDataRechargeRank* GetDataRechargeRank(void);
	int GetList(unsigned uid, Json::Value &result);
	int SetUser(unsigned uid, unsigned cashDay, unsigned cashAll, string& name, unsigned& need);
	int ReplyList(unsigned uid, Json::Value &result);
	int ReplyUser(unsigned uid, unsigned cashDay, unsigned cashAll, string& name, Json::Value &result);
};


#endif /* LOGICRECHARGERANK_H_ */
