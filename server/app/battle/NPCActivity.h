/*
 * NPCActivity.h
 *
 *  Created on: 2016-10-20
 *      Author: Ralf
 */

#ifndef NPCACTIVITY_H_
#define NPCACTIVITY_H_


#include "ServerInc.h"

class NPCActivity : public ActivitySingleton<e_Activity_NPC>, public CSingleton<NPCActivity>
{
private:
	friend class CSingleton<NPCActivity>;
	NPCActivity(){};
	virtual ~NPCActivity(){}

	map<uint8_t, pair<pair<uint16_t, unsigned>, unsigned> > m_cts;

	enum
	{
		complete_affair_by_props = 1,  //道具完成
		complete_affair_by_cash	 =2,  //钻石完成
	};

public:
	void CallDestroy() {Destroy();}
	void OnStart();
	void OnMin();
	void OnDay();

	int NewUserInit(unsigned uid);

	//初始化空白活动数据
	int NPCActivityInit(unsigned uid);

	//离线用户，登录结算-刷新活动事件
	int LoginCheck(unsigned uid);

	//NPC掉落材料增加
	int AddNPCActivityMaterial(unsigned uid, unsigned id, unsigned count);

	//打开窗口
	int Process(unsigned uid, ProtoNPCActivity::OpenNPCActivityWindowReq *reqmsg, ProtoNPCActivity::OpenNPCActivityWindowResp * respmsg);

	//领取事件奖励
	int Process(unsigned uid, ProtoNPCActivity::GetActiveAffairRewardReq *reqmsg, ProtoNPCActivity::GetActiveAffairRewardResp * respmsg);

	//领取活力值奖励
	int Process(unsigned uid, ProtoNPCActivity::GetActiveValueRewardReq *reqmsg, ProtoNPCActivity::GetActiveValueRewardResp * respmsg);

private:
	//刷新在线玩家的跨天活动事件
	int RefreshNewDayAffair(unsigned uid);

	//打开活动窗口
	int OpenNPCActivity(unsigned uid, ProtoNPCActivity::OpenNPCActivityWindowResp * respmsg);

	//活动事件奖励
	int GetAffairReward(unsigned uid, unsigned type, ProtoNPCActivity::GetActiveAffairRewardResp * respmsg);

	//活力值奖励
	int GetActiveValueReward(unsigned uid, unsigned index, ProtoNPCActivity::GetActiveValueRewardResp * respmsg);

	//检查活动,包括是否开启，版本号
	int CheckNPCActivity(unsigned uid);

	//重置活动内容
	int ResetNPCActivity(DataNPCActivity & npcactivity, unsigned version);

	//道具检查，检查通过则消耗
	int CheckAndCostMaterial(DataNPCActivity & npcactivity, const ProtoNPCActivity::AffairConfigCPP & affairconfig);

	//道具到后台定义的类型转换
	int Props2Type(unsigned props);

	//获取倍数
	int GetMultiple();

	//获取活动开启天数
	int GetBeginDays();

	//发放奖励
	int ProvideReward(unsigned uid, const DataConfig::RewardConfigCPP & rewardconf, unsigned multiple, string reason, ProtoNPCActivity::FinalRewardCPP * reward);

	//适配DataConfig::BaseRewardConfigCPP 到CommonGiftConfig::BaseReward base;
	int AdaptCommonGiftBase(const DataConfig::BaseRewardConfigCPP & from_base, CommonGiftConfig::BaseReward & dest_base);

	//获得新一天的事件id
	int GetNewDayAffair();

	int RefreshNextAffair(unsigned uid);
};

#endif /* NPCACTIVITY_H_ */
