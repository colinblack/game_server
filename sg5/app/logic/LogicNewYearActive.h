/*
 * LogicNewYearActive.h
 *
 *  Created on: 2018年1月26日
 *      Author: Administrator
 */

#ifndef LOGIC_NEWYEARACTIVE_H_
#define LOGIC_NEWYEARACTIVE_H_

#include "LogicInc.h"
#include "DataNewYearActive.h"
#include "LogicCmdUnits.h"

class CLogicNewYearActive : public LogicBase<CDataNewYearActive>
{
public:
	CLogicNewYearActive();
	virtual ~CLogicNewYearActive();

	int Visit(unsigned uid, unsigned userid, Json::Value &result);
	int BirdBridgeReward(unsigned uid, unsigned type, Json::Value &equip, unsigned ats);
	int GetInfo(unsigned uid, unsigned userid, Json::Value &result);
	int Refresh(unsigned uid, Json::Value &result);
private:
	int getNewAct(unsigned uid, Json::Value & newAct);
	int randomType(bool buy);
	int getEquipReward(unsigned type, unsigned &equid, unsigned &count);
};

//助力大行动
class CLogicGiveHelpActive: public LogicBase<CDataGiveHelpActive> {
public:
	CLogicGiveHelpActive() {
	}
	virtual ~CLogicGiveHelpActive() {
	}
	int GetStartGiveHelpList(unsigned uid, Json::Value &result);
	int ClickGiveHelpList(unsigned tuid, unsigned fuid, Json::Value &result);
	int GiveHelpRetail(unsigned uid, Json::Value &result);
	int DelHelper(unsigned uid, unsigned userid, Json::Value &result);
	unsigned GetTotalChargeByUid(unsigned uid);
};

#endif /* LOGIC_NEWYEARACTIVE_H_ */
