/*
 * LogicCumulationLoginManager.h
 *
 *  Created on: 2016-10-12
 *      Author: city
 */

#ifndef LOGIC_CUMULATION_LOGIN_MANAGER_H_
#define LOGIC_CUMULATION_LOGIN_MANAGER_H_

#include "ServerInc.h"
#include "DataCumulationLogin.h"

class LogicCumulationLogicManager : public BattleSingleton, public CSingleton<LogicCumulationLogicManager>
{
private:
	friend class CSingleton<LogicCumulationLogicManager>;
	LogicCumulationLogicManager();
	virtual ~LogicCumulationLogicManager(){}

public:
	virtual void CallDestroy() {Destroy();}

	int NewUserInit(unsigned uid);

	int LoginCheck(unsigned uid);

	int FullMessage(unsigned uid, ProtoCumulation::CumulationCPP * msg);

	//累积登录奖励领取
	int Process(unsigned uid, ProtoCumulation::CumulationRewardReq *reqmsg, ProtoCumulation::CumulationRewardResp * respmsg);

private:
	int GetCumulationLoginReward(unsigned uid, unsigned index, ProtoCumulation::CumulationRewardResp * respmsg);
};

#endif //LOGIC_CUMULATION_LOGIN_MANAGER_H_
