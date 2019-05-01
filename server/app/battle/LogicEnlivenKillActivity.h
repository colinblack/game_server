#ifndef LOGIC_ENLIVEN_KILL_ACTIVITY_H_
#define LOGIC_ENLIVEN_KILL_ACTIVITY_H_

#include "ServerInc.h"

class LogicEnlivenKillActivity : public ActivitySingleton<e_Activity_EnlivenKill>, public CSingleton<LogicEnlivenKillActivity>
{
private:
	friend class CSingleton<LogicEnlivenKillActivity>;
	LogicEnlivenKillActivity(){};
	virtual ~LogicEnlivenKillActivity(){}

public:
	enum{
		max_daily_kill_items = 4, //每日杀敌最大项
	};

	struct Record
	{
		unsigned rank;
		unsigned kill;
		unsigned reward;

		Record():
			rank(0),
			kill(0),
			reward(0)
		{

		}
	};

	virtual void CallDestroy() {Destroy();}

	//离线用户的上线重置
	int LoginCheck(unsigned uid);

	//打开活动窗口
	int Process(unsigned uid, ProtoActivity::OpenEnlivenKillWindowReq *reqmsg, ProtoActivity::OpenEnlivenKillWindowResp * respmsg);

	//领取杀敌活跃奖励
	int Process(unsigned uid, ProtoActivity::ReceiveDailyKillRewardReq *reqmsg, ProtoActivity::ReceiveDailyKillRewardResp * respmsg);

	//刷新全服排行榜
	int RefreshFullServerKillRank(string path);

	//重置奖励领取状态
	int ResetRewardStatus(unsigned uid);

	//发放杀敌活跃排行榜奖励
	int ProvideRankReward(string path);
private:
	virtual void OnEnd();

	//打开窗口
	int OpenWindow(unsigned uid, ProtoActivity::OpenEnlivenKillWindowResp * respmsg);

	//领取杀敌活跃奖励
	int GetDailyKillReward(unsigned uid, unsigned index, ProtoActivity::ReceiveDailyKillRewardResp * respmsg);

	//检查版本
	int CheckActivity();

	//发送全部杀敌人员的通知
	int SendRankNotify();

	//当活动结束后，删除该活动的通知
	int ClearRankNotify();
private:
	static const string fullrankname;
	map<unsigned, Record> m_kill_rank;  //杀敌排行榜，uid->记录内容
};

#endif /* LOGIC_ENLIVEN_KILL_ACTIVITY_H_ */
