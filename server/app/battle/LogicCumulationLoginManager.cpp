#include "LogicCumulationLoginManager.h"

LogicCumulationLogicManager::LogicCumulationLogicManager()
{

}

int LogicCumulationLogicManager::NewUserInit(unsigned uid)
{
	DataCumulationLoginManager::Instance()->New(uid);

	return 0;
}

int LogicCumulationLogicManager::LoginCheck(unsigned uid)
{
	//检查累积登录数据是否加载进内存
	int ret = DataCumulationLoginManager::Instance()->CheckBuff(uid);

	if (ret)   //内存中没有数据，可能是没有从dbc中取出来
	{
		ret = DataCumulationLoginManager::Instance()->LoadBuff(uid);

		if (R_ERR_NO_DATA == ret)
		{
			return NewUserInit(uid);
		}
	}

	return ret;
}

int LogicCumulationLogicManager::Process(unsigned uid, ProtoCumulation::CumulationRewardReq *reqmsg, ProtoCumulation::CumulationRewardResp * respmsg)
{
	unsigned index = reqmsg->rindex();

	GetCumulationLoginReward(uid, index, respmsg);

	return 0;
}

int LogicCumulationLogicManager::GetCumulationLoginReward(unsigned uid, unsigned index, ProtoCumulation::CumulationRewardResp * respmsg)
{
	//对参数进行校验
	const RewardConfig::CumulationLogin & comulation_condition = ConfigManager::Instance()->cumulationlogin.m_config.cumulation_login();

	if (index < 1 || index > comulation_condition.dayrewards_size())
	{
		error_log("[GetCumulationLoginReward] index param error. uid=%u,index=%u", uid, index);
		throw std::runtime_error("param_error");
	}

	int pos = index - 1;
	int condition_day = comulation_condition.dayrewards(pos).day();
	DBCUserBaseWrap userwrap(uid);

	if (userwrap.Obj().login_days < condition_day)
	{
		error_log("[GetCumulationLoginReward] condition not match. uid=%u,index=%u, day=%u", uid, index, userwrap.Obj().login_days);
		throw std::runtime_error("condition_not_match");
	}

	//判断是否已经领取过该奖励
	DataCumulationLogin & datacumulation = DataCumulationLoginManager::Instance()->Get(uid);

	//是否领取校验
	bool iszero = LogicCommonUtil::CheckPosIsZero(datacumulation.status, pos);

	if (!iszero)   //非0，表示已领取
	{
		error_log("[GetCumulationLoginReward] cumulation already get. uid=%u, index=%u", uid, index);
		throw std::runtime_error("already_get_reward");
	}

	//领取奖励
	for(int i = 0; i < comulation_condition.dayrewards(pos).reward_size(); ++i)
	{
		const RewardConfig::Reward & rewardconfig = comulation_condition.dayrewards(pos).reward(i);

		//装备
		if (rewardconfig.has_equips())
		{
			unsigned eqid = rewardconfig.equips().eqid();
			unsigned count = rewardconfig.equips().count();

			LogicEquipmentManager::Instance()->AddEquipment(uid, eqid, count, "CumulationLogin", respmsg->mutable_equips());
		}

		//英雄
		if (rewardconfig.has_hero())
		{
			unsigned heroid = rewardconfig.hero();
			int ret = LogicHeroManager::Instance()->UnlockHero(uid, heroid, "CumulationLogin", respmsg->mutable_hero());

			if (ret)
			{
				error_log("[GetCumulationLoginReward] unlock hero error. uid=%u", uid);
				throw std::runtime_error("unlock_hero_error");
			}
		}

		//资源+钻石+次数
		if (rewardconfig.has_base())
		{
			const CommonGiftConfig::BaseReward& base = rewardconfig.base();
			userwrap.Reward(base, respmsg->mutable_base(), "CumulationLogin");
		}
	}

	//设置已领取标志
	LogicCommonUtil::SetBitCurrent(datacumulation.status, pos);
	DataCumulationLoginManager::Instance()->UpdateDataCumulation(datacumulation);
	respmsg->set_status(datacumulation.status);

	return 0;
}


int LogicCumulationLogicManager::FullMessage(unsigned uid, ProtoCumulation::CumulationCPP * msg)
{
	try
	{
		DataCumulationLogin & cumulation = DataCumulationLoginManager::Instance()->Get(uid);
		cumulation.SetMessage(msg);
	}
	catch (std::runtime_error & e)
	{
		error_log("[FullMessage] can't get cumulation data. uid=%u", uid);
		return R_ERROR;
	}

	return 0;
}

