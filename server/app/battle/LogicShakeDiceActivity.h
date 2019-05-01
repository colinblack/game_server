#ifndef LOGIC_SHAKE_DICE_ACTIVITY_H_
#define LOGIC_SHAKE_DICE_ACTIVITY_H_

#include "ServerInc.h"

class LogicShakeDiceActivity : public ActivitySingleton<e_Activity_ShakeDice>, public CSingleton<LogicShakeDiceActivity>
{
private:
	friend class CSingleton<LogicShakeDiceActivity>;
	LogicShakeDiceActivity(){};
	virtual ~LogicShakeDiceActivity(){}

public:
	enum
	{
		map_status_lock	= 0,   //未解锁
		map_status_process = 1,  //进行中
		map_status_complete	= 2, //已完成

		max_map_num	= 3,  //最大的地图页数
		dice_max_point	= 6, //骰子最大点数
	};

	virtual void CallDestroy() {Destroy();}

	int NewUserInit(unsigned uid);

	int LoginCheck(unsigned uid);

	//打开窗口
	int Process(unsigned uid, ProtoShakeDice::OpenShakeDiceWindowReq *reqmsg, ProtoShakeDice::OpenShakeDiceWindowResp * respmsg);

	//进入地图
	int Process(unsigned uid, ProtoShakeDice::EnterMapReq *reqmsg, ProtoShakeDice::EnterMapResp * respmsg);

	//摇骰子
	int Process(unsigned uid, ProtoShakeDice::RollDiceReq *reqmsg, ProtoShakeDice::RollDiceResp * respmsg);

	//重置地图
	int Process(unsigned uid, ProtoShakeDice::ResetMapReq *reqmsg, ProtoShakeDice::ResetMapResp *respmsg);

	//地点奖励
	int Process(unsigned uid, ProtoShakeDice::PositionRewardReq *reqmsg, ProtoShakeDice::PositionRewardResp *respmsg);

	//解锁地图
	int Process(unsigned uid, ProtoShakeDice::UnlockMapReq *reqmsg, ProtoShakeDice::UnlockMapResp *respmsg);

	//额外奖励领取
	int Process(unsigned uid, ProtoShakeDice::ReceiveExtraRewardReq *reqmsg, ProtoShakeDice::ReceiveExtraRewardResp *respmsg);

private:
	//打开窗口
	int OpenWindow(unsigned uid, ProtoShakeDice::OpenShakeDiceWindowResp * respmsg);

	//进入地图
	int EnterActivityMap(unsigned uid, unsigned mapid, ProtoShakeDice::EnterMapResp * respmsg);

	//摇骰子
	int RollDice(unsigned uid, ProtoShakeDice::RollDiceResp * respmsg);

	//重置活动地图
	int ResetActivityMap(unsigned uid, ProtoShakeDice::ResetMapResp * respmsg);

	//行走，领取地点奖励
	int WalkRecieveReward(unsigned uid, vector<unsigned> & positions, ProtoShakeDice::PositionRewardResp * respmsg);

	//解锁地图
	int UnlockMap(unsigned uid, unsigned mapid, ProtoShakeDice::UnlockMapResp * respmsg);

	//领取额外奖励
	int GetExtraReward(unsigned uid, ProtoShakeDice::ReceiveExtraRewardResp * respmsg);

	//判断是否有额外奖励需要领取
	bool IsHaveExtraReward(DataShakeDice & shakedice);

	//获取地图的终点的据点id
	int GetFinalPositionId(unsigned mapid);

	//检查活动,包括是否开启，版本号
	int CheckActivity(unsigned uid);

	//重置地图
	int ResetMap(DataShakeDice & shakedice);

	//重置活动内容
	int ResetActivity(DataShakeDice & shakedice, unsigned version);

	//每日重置
	int DailyReset(DataShakeDice & shakedice, unsigned now);

	//获取地图奖励领取状态
	unsigned GetMapRewardStatus(DataShakeDice & shakedice);

	//设置地图奖励领取状态
	int SetMapRewardStatus(DataShakeDice & shakedice, unsigned pos);

	//获取地图状态
	unsigned GetMapStatus(DataShakeDice & shakedice, unsigned curmap);

	//设置地图状态
	int SetMapStatus(DataShakeDice & shakedice, unsigned curmap, unsigned status);
};


#endif /* LOGIC_SHAKE_DICE_ACTIVITY_H_ */
