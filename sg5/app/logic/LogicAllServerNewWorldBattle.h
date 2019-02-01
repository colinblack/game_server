/*
 * LogicAllServerNewWorldBattle.h
 *
 *  Created on: 2015-2-12
 *      Author: Ralf
 */

#ifndef LOGICALLSERVERNEWWORLDBATTLE_H_
#define LOGICALLSERVERNEWWORLDBATTLE_H_

#include "LogicInc.h"

class CLogicAllServerNewWorldBattle {
public:
	CLogicAllServerNewWorldBattle();
	static CDataAllServerNewWorldBattle* GetDataAllServerNewWorldBattle(void);
	int GetList(Json::Value &result);
	int ReplyList(Json::Value &result);
	int SetAttack(unsigned uid, unsigned attack, unsigned kingdom, unsigned defend, Json::Value &result);
	int ReplyAttack(unsigned attack, unsigned kingdom, unsigned defend, Json::Value &result);
	int SetArmy(unsigned serverid, unsigned domain, unsigned army[3], string& host);
	int ReplyArmy(unsigned serverid, unsigned domain, unsigned army[3], string& host);
	int SetResult(unsigned defend, unsigned result);
	int ReplyResult(unsigned defend, unsigned result);
};



#endif /* LOGICALLSERVERNEWWORLDBATTLE_H_ */
