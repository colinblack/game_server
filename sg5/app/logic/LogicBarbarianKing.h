/*
 * LogicBarbarianKing.h
 *
 *  Created on: 2014-4-3
 *      Author: dawx123
 */

#ifndef LOGICBARBARIANKING_H_
#define LOGICBARBARIANKING_H_
#include "LogicInc.h"

class CLogicBarbarianKing
{
public:
	CLogicBarbarianKing(){}
	~CLogicBarbarianKing(){}
	static CDataBarbarianKing* GetCDataBarbarianKing();

	int GetBKList(unsigned group, Json::Value &result);
	int ReplyBKList(unsigned group, Json::Value &result);
	int SetBKChallenger(unsigned level, unsigned uid, unsigned point, string &name);
	int ReplyBKChallenger(Json::Value &data);
	int GetGroupByLevel(unsigned level);
	int Reward();
};


#endif /* LOGICBARBARIANKING_H_ */
