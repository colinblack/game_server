#ifndef __LOGIC_UPDATES_H__
#define __LOGIC_UPDATES_H__

#include "LogicInc.h"

#define ID_SUIJI_CAILIAO_BAO 50053	// 随机材料包
#define ID_WUXINGZHU 4031	//五行珠
#define ID_ZHAO_MU_LING 42015 //招募令
#define ACTIVITY_XIUQIU_MAX 5400

class CLogicUpdates
{
public:
	int AddUpdates(unsigned uid, Json::Value &data,bool email = false, bool isother = false);
	int AddUpdate(unsigned uid, Json::Value &data,bool email = false, bool isother = false);
	int GetUpdates(unsigned uid, Json::Value &data, bool onlyother = false);
	int RemoveUpdatesBeforeTs(unsigned uid, unsigned ts);

	int sendReward(unsigned uid, const Json::Value &data);

	/** 以下函数为后台发放各种update的奖励 */
	int sendAllianceBossAward(unsigned uid, const Json::Value &data);			    // 联盟屠魔
	int sendEndofShipReward(unsigned uid, const Json::Value &data);					// 草船借箭
	int sendWorldBossAward(unsigned uid, const Json::Value &data);					// 世界屠魔奖励
	int sendBarbarianKingReward(unsigned uid, const Json::Value &data);				// 蛮王发排名奖励
	int sendQixiRankReward(unsigned uid, const Json::Value &data);					// 幸运大转盘奖励
	int sendHundredDaysReward(unsigned uid, const Json::Value &data);				// 乐不思蜀奖励
	int sendAllServerPMatchAward(unsigned uid, const Json::Value &data);			// 周五的跨服武林大会奖励
	int sendPointRankReward(unsigned uid, const Json::Value &data);					// 砸罐子奖励
	int sendSnatchDragonballAward(unsigned uid, const Json::Value &data);			// 绣球易主
	int resetDragonBall(unsigned uid, const Json::Value &data);						// 绣球结束
	int sendPowerRankReward(unsigned uid, const Json::Value &data);					// 开区活动战力排名奖励
	int sendAttackRankReward(unsigned uid, const Json::Value &data);				// 开区活动掠夺排名奖励
public:
	int sendProsperAndCoins(unsigned uid, const Json::Value &update, const string &reason);
};

#endif
