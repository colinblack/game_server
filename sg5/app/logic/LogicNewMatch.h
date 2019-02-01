/*
 * LogicNewMatch.h
 *
 *  Created on: 2015-10-23
 *      Author: Ralf
 */

#ifndef LOGICNEWMATCH_H_
#define LOGICNEWMATCH_H_

#include "LogicInc.h"
#include "LogicBase.h"

class CLogicNewMatch : public LogicBase<CDataNewMatch>
{
public:
	CLogicNewMatch(){}
	~CLogicNewMatch(){}
	int Get(unsigned uid, Json::Value &result);
	int Apply(unsigned uid, Json::Value &data);
	int ChangeIndex(unsigned uid, Json::Value &data);
	int Fight(unsigned uid, Json::Value &result);
	int Guess(unsigned uid, unsigned guess, unsigned bet);
	int Reward();
};

#endif /* LOGICNEWMATCH_H_ */
