#ifndef LOGIC_DAILY_MISSION_MANAGER_H
#define LOGIC_DAILY_MISSION_MANAGER_H

#include "ServerInc.h"

class LogicDailyMissionManager : public BattleSingleton, public CSingleton<LogicDailyMissionManager>
{
private:
	friend class CSingleton<LogicDailyMissionManager>;
	LogicDailyMissionManager(){};
	virtual ~LogicDailyMissionManager(){}

	enum
	{
		first_seq_mission = 1,  //第一个任务的序列号
		max_daily_mission = 5,  //每日任务刷新产生的任务数
		pay_refresh_cash = 5, //花钻刷新价格
		max_reward_times = 10, //最大的每日任务领取次数
	};

public:
	struct DailyMissionParam
	{
		int type;  //任务类型
		vector<int> subparam;

		DailyMissionParam():
			type(0)
		{

		}
	};

	virtual void CallDestroy() {Destroy();}

	//新手初始化
	int NewUserInit(unsigned uid);

	//登录检查
	int LoginCheck(unsigned uid);

	//普通刷新
	int Process(unsigned uid, ProtoDailyMission::RefreshDailyMissionReq* reqmsg, ProtoDailyMission::RefreshDailyMissionResp* respmsg);

	//花钻刷新
	int Process(unsigned uid, ProtoDailyMission::CashRefreshMissionReq* reqmsg, ProtoDailyMission::CashRefreshMissionResp* respmsg);

	//打开每日任务窗口
	int Process(unsigned uid, ProtoDailyMission::OpenDailyMissionWindowReq* reqmsg, ProtoDailyMission::OpenDailyMissionWindowResp* respmsg);

	//领取每日任务奖励
	int Process(unsigned uid, ProtoDailyMission::GetDailyMissionRewardReq* reqmsg, ProtoDailyMission::GetDailyMissionRewardResp* respmsg);

	/*
	 * 验证任务是否完成 -不带输出,将内容推送给客户端
	 * param  uid(in),param(in)
	 * return 0-成功
	 */
	int VerifyDailyMissionComplete(unsigned uid, DailyMissionParam & param);

	//打开每日任务窗口
	int OpenDailyMissionWindow(unsigned uid, ProtoDailyMission::DailyMissionAllCPP * msg);

	int VerifyDailyMission(DataDailyMission & dailymission, DailyMissionParam & param);

	int FullMessage(unsigned uid, ProtoDailyMission::DailyMissionAllCPP *msg);

private:
	//普通刷新
	int CommonRefreshMission(unsigned uid, ProtoDailyMission::RefreshDailyMissionResp * msg);

	//花钻刷新
	int CashRefreshMission(unsigned uid, ProtoDailyMission::CashRefreshMissionResp * msg);

	//刷新每日任务
	int RefreshMission(unsigned uid, ProtoDailyMission::DailyMissionAllCPP * msg);

	//领取每日任务奖励
	int GetDailyMissionReward(unsigned uid, unsigned missid, ProtoDailyMission::GetDailyMissionRewardResp * respmsg);

	//任务前期处理
	int PrepareMission(DataDailyMission & dailymission);

	//资源前期处理
	int PrepareProductivity(DataDailyMission & dailymission, unsigned subtype);

	//功勋前期处理
	int PrepareExploit(DataDailyMission & dailymission);

	//杀敌前期处理
	int PrepareKill(DataDailyMission & dailymission);

	//验证资源产量
	int VerifyProductivity(DataDailyMission & dailymission);

	//政务事件验证
	int VerifyAffair(DataDailyMission & dailymission);

	//洗练验证
	int VerifyEquipSmelt(DataDailyMission & dailymission);

	//黑市兑换
	int VerifyBlackMarket(DataDailyMission & dailymission);

	//竞技场挑战
	int VerifyPKField(DataDailyMission & dailymission);

	//升级军工，消耗黄金
	int VerifyUpgradeWeapon(DataDailyMission & dailymission, unsigned gold);

	//矿藏援建
	int VerifyMineSupport(DataDailyMission & dailymission);

	//闯关挑战
	int VerifyGate(DataDailyMission & dailymission);

	//世界功勋
	int VerifyExploit(DataDailyMission & dailymission);

	//世界杀敌
	int VerifyKill(DataDailyMission & dailymission);

	//装备商店刷新
	int VerifyEquipShopReresh(DataDailyMission & dailymission);

	//阅兵
	int VerifyParade(DataDailyMission & dailymission);

	//军职挑战
	int VerifyOfficial(DataDailyMission & dailymission);

	int CheckMission(DataDailyMission & dailymission);
};

#endif //LOGIC_DAILY_MISSION_MANAGER_H
