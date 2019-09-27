/*
 * LogicNewDouJiang.h
 *
 *  Created on: 2017-2-14
 *      Author: Ralf
 */

#ifndef LOGICNEWDOUJIANG_H_
#define LOGICNEWDOUJIANG_H_


#include "LogicInc.h"
#include "LogicBase.h"

class CLogicNewDouJiang : public LogicBase<CDataNewDouJiang>
{
public:
	CLogicNewDouJiang(){}
	~CLogicNewDouJiang(){}

	void CheckVersion();
	int SetZhenRong(unsigned uid, const vector<unsigned> & z, Json::Value & result);
	int GetZhenRong(unsigned uid, Json::Value & result);
	int GetMyList(unsigned uid, Json::Value & result);
	int PiPei(unsigned uid, unsigned seq,Json::Value & result);
	int StartAttack(unsigned uid, unsigned type, unsigned uid2, unsigned hud, unsigned seq, unsigned ud, Json::Value & result, unsigned fcts=0);
	int SetResult(unsigned uid, unsigned type, unsigned uid2, unsigned win, unsigned hud, unsigned seq, unsigned ud, Json::Value & result);
	int GetRankList(unsigned uid, Json::Value & result);
	int GetZhanBao(unsigned uid, Json::Value &result);
};



#endif /* LOGICNEWDOUJIANG_H_ */
