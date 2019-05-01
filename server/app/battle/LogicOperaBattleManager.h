#ifndef LOGIC_OPERA_BATTLE_MANAGER_
#define LOGIC_OPERA_BATTLE_MANAGER_

#include "ServerInc.h"

class LogicOperaBattleManager : public BattleSingleton, public CSingleton<LogicOperaBattleManager>
{
private:
	friend class CSingleton<LogicOperaBattleManager>;
	LogicOperaBattleManager(){};
	virtual ~LogicOperaBattleManager(){}

public:
	virtual void CallDestroy() {Destroy();}

	int LoginCheck(unsigned uid);

	//打开窗口
	int Process(unsigned uid, ProtoOperaBattle::OpenOperaBattleWindowReq* reqmsg, ProtoOperaBattle::OpenOperaBattleWindowResp * respmsg);

	//开启剧本战
	int Process(unsigned uid, ProtoOperaBattle::StartOperaBattleReq* reqmsg, ProtoOperaBattle::StartOperaBattleResp * respmsg);

	//结束剧本战
	int Process(unsigned uid, ProtoOperaBattle::EndOperaBattleReq* reqmsg, ProtoOperaBattle::EndOperaBattleResp * respmsg);

	//领取剧本奖励
	int Process(unsigned uid, ProtoOperaBattle::ReceiveStarRewardReq* reqmsg, ProtoOperaBattle::ReceiveStarRewardResp * respmsg);

	int FullMessage(unsigned uid, ProtoOperaBattle::MemoryOperaBattleRecordCPPAll * msg);

	int FullMessage(unsigned uid, ProtoOperaBattle::OperaBattleCPPAll * msg);
private:
	//打开窗口
	int OpenOperaBattleWindow(unsigned uid, ProtoOperaBattle::OpenOperaBattleWindowResp * respmsg);

	//开启剧本战
	int StartOperaBattle(unsigned uid, unsigned gateid, unsigned diff, ProtoOperaBattle::StartOperaBattleResp * respmsg);

	//结束据本战
	int EndOperaBattle(unsigned uid, unsigned gateid, unsigned diff, unsigned used_time, ProtoOperaBattle::EndOperaBattleResp * respmsg);

	//领取剧本奖励
	int ReceiveBattleReward(unsigned uid, unsigned gateid, unsigned diff, unsigned star, unsigned battle_star, ProtoOperaBattle::ReceiveStarRewardResp * respmsg);

};


#endif //LOGIC_OPERA_BATTLE_MANAGER_
