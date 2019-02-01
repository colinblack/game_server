/*
 * LogicConsumeRank.h
 *
 *  Created on: 2015-2-2
 *      Author: Ralf
 */

#ifndef LOGICCONSUMERANK_H_
#define LOGICCONSUMERANK_H_

#include "LogicInc.h"

class CLogicConsumeRank {
public:
	CLogicConsumeRank();
	static CDataConsumeRank* GetDataConsumeRank(void);
	int GetList(unsigned uid, Json::Value &result);
	int SetUser(unsigned uid, unsigned cashDay, unsigned cashAll, string& name, unsigned& need);
	int ReplyList(Json::Value &result);
	int ReplyUser(unsigned uid, unsigned cashDay, unsigned cashAll, string& name, Json::Value &result);
};


#endif /* LOGICCONSUMERANK_H_ */
