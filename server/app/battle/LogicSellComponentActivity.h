#ifndef LOGIC_SELL_COMPONENT_ACTIVITY_H_
#define LOGIC_SELL_COMPONENT_ACTIVITY_H_

#include "ServerInc.h"

class LogicSellComponentActivity : public ActivitySingleton<e_Activity_SellComponent>, public CSingleton<LogicSellComponentActivity>
{
private:
	friend class CSingleton<LogicSellComponentActivity>;
	LogicSellComponentActivity(){};
	virtual ~LogicSellComponentActivity(){}

public:
	virtual void CallDestroy() {Destroy();}

	//打开活动窗口
	int Process(unsigned uid, ProtoActivity::OpenSellComponentWindowReq *reqmsg, ProtoActivity::OpenSellComponentWindowResp * respmsg);

	//购买部件
	int Process(unsigned uid, ProtoActivity::BuyComponentReq *reqmsg, ProtoActivity::BuyComponentResp * respmsg);

private:
	//打开窗口
	int OpenWindow(unsigned uid, ProtoActivity::OpenSellComponentWindowResp * respmsg);

	//领取杀敌活跃奖励
	int BuyComponent(unsigned uid, unsigned index, ProtoActivity::BuyComponentResp * respmsg);

	//重置活动数据
	int ResetActivity(DataSellComponent& sellcomponent, unsigned ts);

	//检查版本
	int CheckActivity();
};

#endif /* LOGIC_SELL_COMPONENT_ACTIVITY_H_ */
