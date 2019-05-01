#ifndef LOGIC_YELLOWVIP_MANAGER_H
#define LOGIC_YELLOWVIP_MANAGER_H

#include "ServerInc.h"

class LogicYellowVipManager : public BattleSingleton, public CSingleton<LogicYellowVipManager>
{
private:
	friend class CSingleton<LogicYellowVipManager>;
	LogicYellowVipManager(){};
	virtual ~LogicYellowVipManager(){}

public:
	virtual void CallDestroy() {Destroy();}

	int NewUserInit(unsigned uid);

	int LoginCheck(unsigned uid);

	//领取新手礼包接口
	int Process(unsigned uid, ProtoYellowVip::GetNewerGiftReq *reqmsg, ProtoYellowVip::GetNewerGiftResp * respmsg);

	//领取黄钻每日礼包接口
	int Process(unsigned uid, ProtoYellowVip::GetDailyGiftReq *reqmsg, ProtoYellowVip::GetDailyGiftResp * respmsg);

	//领取年费黄钻每日礼包接口
	int Process(unsigned uid, ProtoYellowVip::GetYearDailyGiftReq *reqmsg, ProtoYellowVip::GetYearDailyGiftResp * respmsg);

	//领取升级礼包接口
	int Process(unsigned uid, ProtoYellowVip::GetLevelGiftReq *reqmsg, ProtoYellowVip::GetLevelGiftResp * respmsg);

	//领取空间每日礼包接口
	int Process(unsigned uid, ProtoYellowVip::QQZoneGetDailyGiftReq *reqmsg, ProtoYellowVip::QQZoneGetDailyGiftResp * respmsg);

	//领取空间升级礼包接口
	int Process(unsigned uid, ProtoYellowVip::QQZoneGetLevelGiftReq *reqmsg, ProtoYellowVip::QQZoneGetLevelGiftResp * respmsg);

	int FullMessage(unsigned uid, ProtoYellowVip::YellowVipCPP * msg);

private:
	//领取新手礼包
	int GetNewerReward(unsigned uid, ProtoYellowVip::GetNewerGiftResp *respmsg);

	//领取黄钻每日礼包
	int GetDailyReward(unsigned uid, ProtoYellowVip::GetDailyGiftResp * respmsg);

	//领取年费黄钻每日礼包
	int GetYearDailyReward(unsigned uid, ProtoYellowVip::GetYearDailyGiftResp * respmsg);

	//领取升级礼包
	int GetUpgradeReward(unsigned uid, unsigned index, ProtoYellowVip::GetLevelGiftResp * respmsg);

	//领取空间每日礼包
	int GetQQZoneDailyReward(unsigned uid, ProtoYellowVip::QQZoneGetDailyGiftResp * respmsg);

	//领取空间升级礼包
	int GetQQZoneUpgradeReward(unsigned uid, unsigned index, ProtoYellowVip::QQZoneGetLevelGiftResp * respmsg);

	//发放奖励
	int ProvideReward(const VipGiftConfig::FinalReward & reward, unsigned uid, string reason, ProtoYellowVip::FinalRewardCPP * msg);

	//是否跨天领取的检查以及重置
	int CheckCrossDay(DataYellowVip & datayellow);

	//校验是否是黄钻会员
	int CheckIsYellowVip(unsigned uid);

	//校验是否是年费黄钻
	int CheckIsYellowYearVip(unsigned uid);

	//校验是否qq空间平台
	int CheckIsFromQQZone(unsigned uid);
};

#endif //LOGIC_YELLOWVIP_MANAGER_H
