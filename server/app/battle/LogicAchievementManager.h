#ifndef LOGIC_ACHIEVEMENT_MANAGER_H
#define LOGIC_ACHIEVEMENT_MANAGER_H

#include "ServerInc.h"

class LogicAchievementManager : public BattleSingleton, public CSingleton<LogicAchievementManager>
{
private:
	friend class CSingleton<LogicAchievementManager>;
	LogicAchievementManager(){};
	virtual ~LogicAchievementManager(){}

public:
	struct AchievementParam
	{
		int type;  //成就类型
		vector<int> subparam;

		AchievementParam():
			type(0)
		{

		}
	};

	enum
	{
		status_uncomplete = 0,  //未完成
		status_waiting_reward,  //等待领取
		status_get_reward, 	//已领取
	};

	virtual void CallDestroy() {Destroy();}

	int NewUserInit(unsigned uid);

	int LoginCheck(unsigned uid);

	//前端触发，验证成就
	int Process(unsigned uid, ProtoAchievement::VerifyAchievementReq *reqmsg);

	//领取成就奖励
	int Process(unsigned uid, ProtoAchievement::GetAchievementRewardReq* reqmsg, ProtoAchievement::GetAchievementRewardResp * respmsg);

	int VerifyAchievementComplete(unsigned uid, AchievementParam & param);

	int FullMessage(unsigned uid, ProtoAchievement::AchievementAllCPP * msg);

private:
	int VerifyAchievement(DataAchievement & achievement, AchievementParam & param);

	//领取成就奖励
	int GetAchievementReward(unsigned uid, unsigned id, ProtoAchievement::GetAchievementRewardResp * respmsg);

	//验证资源产量
	int VerifyProductivity(DataAchievement & achievement);

	//开矿
	int VerifyOpenMine(DataAchievement & achievement);

	//矿藏援建
	int VerifyMineSupport(DataAchievement & achievement);

	//解锁英雄
	int VerifyUnlockHero(DataAchievement & achievement);

	//地勤令使用
	int VerifyUseOrder(DataAchievement & achievement, unsigned count);

	//加入非军校部门
	int VerifyJoinDepartment(DataAchievement & achievement);

	//获得非成员职位
	int VerifyOfficial(DataAchievement & achievement);

	//政务事件验证
	int VerifyAffair(DataAchievement & achievement);

	//民忠兑换
	int VerifyLoyalExchange(DataAchievement & achievement);

	//阅兵
	int VerifyParade(DataAchievement & achievement);

	//三星每日任务领取奖励
	int VerifyDailyMission(DataAchievement & achievement);

	//军工等级
	int VerifyWeaponLevel(DataAchievement & achievement);

	//指定品质装备
	int VerifyCharacterEquip(DataAchievement & achievement);

	//星级装备
	int VerifyStarEquip(DataAchievement & achievement);

	//额外属性
	int VerifyExtraProperty(DataAchievement & achievement);

	//指定品质部件
	int VerifyCharacterComponent(DataAchievement & achievement);

	//科技研究
	int VerifyTechResearch(DataAchievement & achievement);

	//套装合成
	int VerifyComposeSuit(DataAchievement & achievement);

	//单挑
	int VerifyRush(DataAchievement & achievement);

	//世界杀敌
	int VerifyKill(DataAchievement & achievement);

	//突进
	int VerifyMarch(DataAchievement & achievement);

	//撤退
	int VerifyRetreat(DataAchievement & achievement);

	//占领城市
	int VerifyOccupy(DataAchievement & achievement);

	//迷雾闯关
	int VerifyFoggate(DataAchievement & achievement);
};

#endif //LOGIC_ACHIEVEMENT_MANAGER_H
