/*
 * LogicMVP.h
 *
 *  Created on: 2017-08-03
 *      Author: Ralf
 */

#ifndef LOGICMVP_H_
#define LOGICMVP_H_


#include "LogicInc.h"
#include "LogicBase.h"

class CLogicMVP : public LogicBase<CDataMVP>
{
public:
	CLogicMVP(){}
	~CLogicMVP(){}
//攻城
	int GetAllServerMVP(Json::Value &result);
	int StartAllServerMVP(unsigned rank, unsigned uid);
	int EndAllServerMVP(unsigned rank, unsigned uid, bool win, Json::Value &data);
	int SetAllServerMVP(unsigned uid, string &sign);

//斗将
	int StartAllServerBattleMVP(unsigned rank, unsigned uid);
	int EndAllServerBattleMVP(unsigned rank, unsigned uid, bool win, Json::Value &data);

//争霸
	int EndAllServerNewWorldFightMVP(unsigned rank, unsigned uid, bool win, Json::Value &data);
};

#endif /* LOGICMVP_H_ */
