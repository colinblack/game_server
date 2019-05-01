#ifndef LOGIC_FOGGATE_MANAGER_H
#define LOGIC_FOGGATE_MANAGER_H

#include "ServerInc.h"

class LogicFogGateManager : public BattleSingleton, public CSingleton<LogicFogGateManager>
{
private:
	friend class CSingleton<LogicFogGateManager>;
	LogicFogGateManager(){};
	virtual ~LogicFogGateManager(){}

public:
	virtual void CallDestroy() {Destroy();}

	int LoginCheck(unsigned uid);

	//开始迷雾战
	int Process(unsigned uid, ProtoFogGate::StartFogGateReq* req);

	//开始迷雾战
	int StartFogGate(unsigned uid, unsigned gateid, vector<unsigned> & heros);

	//迷雾战结束结算
	int EndFogGate(unsigned uid, unsigned gateid, unsigned leftnpc);

	//是否有通过任意一个迷雾战
	bool IsHaveFogGateSuccess(unsigned uid);

	//获取闯过的迷雾数目
	unsigned GetFogGateSuccessNum(unsigned uid);

	int FullMessage(unsigned uid, ProtoFogGate::FogGateCPPAll* msg);

	//是否迷雾战
	bool IsFogGate(unsigned gateid);
};

#endif //LOGIC_FOGGATE_MANAGER_H
