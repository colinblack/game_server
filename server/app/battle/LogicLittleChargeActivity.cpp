#include "LogicLittleChargeActivity.h"

int LogicLittleChargeActivity::Process(unsigned uid, ProtoActivity::OpenLittleChargeWindowReq *reqmsg, ProtoActivity::OpenLittleChargeWindowResp * respmsg)
{
	OpenWindow(uid, respmsg);

	return 0;
}

int LogicLittleChargeActivity::OpenWindow(unsigned uid, ProtoActivity::OpenLittleChargeWindowResp * respmsg)
{
	//获取当日充值
	unsigned now = Time::GetGlobalTime();
	int cash_charge =LogicResourceManager::Instance()->GetRechargePays(uid, now);

	respmsg->set_cash(cash_charge);

	return 0;
}

int LogicLittleChargeActivity::Process(unsigned uid, ProtoActivity::LittleChargeRewardReq *reqmsg, ProtoActivity::LittleChargeRewardResp * respmsg)
{
	GetChargeReward(uid, respmsg);

	return 0;
}

int LogicLittleChargeActivity::GetChargeReward(unsigned uid, ProtoActivity::LittleChargeRewardResp * respmsg)
{
	int ret = CheckActivity();

	if (ret)
	{
		error_log("activity_not_open. uid=%u", uid);
		throw runtime_error("activity_not_open");
	}

	unsigned now = Time::GetGlobalTime();
	//获取今日充值数
	int cash_charge =LogicResourceManager::Instance()->GetRechargePays(uid, now);

	//获取配置
	LittleChargeConfigWrap chargecfgwrap;

	int cash_condition = chargecfgwrap.GetCashCondition();

	if (0 == cash_condition)
	{
		error_log("condition config error. uid=%u", uid);
		throw runtime_error("config_error");
	}

	if (cash_charge  < cash_condition)
	{
		error_log("little charge not enough. uid=%u, charge=%u,need=%u", uid, cash_charge, cash_condition);
		throw runtime_error("little_charge_not_enough");
	}

	DBCUserBaseWrap userwrap(uid);

	if (! LogicCommonUtil::CheckPosIsZero(userwrap.Obj().shadow, 0) )  //第1位非0，则表示已领取
	{
		error_log("little charge reward already been gotten. uid=%u", uid);
		throw runtime_error("chargereward_already_gotten");
	}

	//发放奖励
	unsigned diff = LogicManager::Instance()->GetOpenDays();
	const LittleChargeConfig::OpenPlatFormReward & reward_cfg = chargecfgwrap.GetRewardConfigByDiff(diff);

	//只支持发放道具
	for(int i = 0; i < reward_cfg.reward_size(); ++i)
	{
		if (reward_cfg.reward(i).has_equips())
		{
			unsigned eqid = reward_cfg.reward(i).equips().eqid();
			unsigned cnt = reward_cfg.reward(i).equips().count();

			LogicEquipmentManager::Instance()->AddEquipment(uid, eqid, cnt, "LittleChargeReward", respmsg->mutable_equip());
		}
	}

	LogicCommonUtil::SetBitCurrent(userwrap.Obj().shadow , 0);  //设置第一位已领取
	userwrap.Save();

	respmsg->set_shadow(userwrap.Obj().shadow);

	return 0;
}

int LogicLittleChargeActivity::CheckActivity()
{
	//默认开服30天之内活动开启
	if (!IsOn())
	{
		return R_ERROR;
	}

	return 0;
}
