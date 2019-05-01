#ifndef LOGIC_LITTLE_CHARGE_ACTIVITY_H_
#define LOGIC_LITTLE_CHARGE_ACTIVITY_H_

#include "ServerInc.h"

class LogicLittleChargeActivity : public ActivitySingleton<e_Activity_LittleCharge>, public CSingleton<LogicLittleChargeActivity>
{
private:
	friend class CSingleton<LogicLittleChargeActivity>;
	LogicLittleChargeActivity(){};
	virtual ~LogicLittleChargeActivity(){}

public:
	virtual void CallDestroy() {Destroy();}

	//打开活动窗口
	int Process(unsigned uid, ProtoActivity::OpenLittleChargeWindowReq *reqmsg, ProtoActivity::OpenLittleChargeWindowResp * respmsg);

	//领取充点小钱奖励
	int Process(unsigned uid, ProtoActivity::LittleChargeRewardReq *reqmsg, ProtoActivity::LittleChargeRewardResp * respmsg);

private:
	//打开窗口
	int OpenWindow(unsigned uid, ProtoActivity::OpenLittleChargeWindowResp * respmsg);

	int GetChargeReward(unsigned uid, ProtoActivity::LittleChargeRewardResp * respmsg);

	//检查版本
	int CheckActivity();
};

#endif /* LOGIC_LITTLE_CHARGE_ACTIVITY_H_ */
