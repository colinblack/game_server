#ifndef LOGIC_MODEL_TRIAL_MANAGER_H
#define LOGIC_MODEL_TRIAL_MANAGER_H

#include "ServerInc.h"

class LogicModelTrialManager : public BattleSingleton, public CSingleton<LogicModelTrialManager>
{
private:
	friend class CSingleton<LogicModelTrialManager>;
	LogicModelTrialManager(){};
	virtual ~LogicModelTrialManager(){}

public:
	enum
	{
		max_free_times = 5, //免费挑战次数
	};

	virtual void CallDestroy() {Destroy();}

	//打开窗口
	int Process(unsigned uid, ProtoModelTrial::OpenModelWindowReq *reqmsg, ProtoModelTrial::OpenModelWindowResp * respmsg);

	//购买次数
	int Process(unsigned uid, ProtoModelTrial::BuyFightTimesReq *reqmsg, ProtoModelTrial::BuyFightTimesResp * respmsg);

	//开始试验战斗
	int Process(unsigned uid, ProtoModelTrial::StartTrialGateReq *reqmsg, ProtoModelTrial::StartTrialGateResp * respmsg);

	//是否试炼副本
	bool IsTrialGate(unsigned gateid);

	//结束试验战斗
	int EndTrialGate(unsigned uid, unsigned gateid);
private:
	//打开窗口
	int OpenWindow(unsigned uid, ProtoModelTrial::OpenModelWindowResp * respmsg);

	//购买次数
	int BuyFightTimes(unsigned uid, ProtoModelTrial::BuyFightTimesResp * respmsg);

	//开始试验战
	int StartTrialGate(unsigned uid, unsigned pos, unsigned gateid, vector<unsigned> & heros, ProtoModelTrial::StartTrialGateResp * respmsg);


};

#endif //LOGIC_MODEL_TRIAL_MANAGER_H
