/*
 * LogicOnhookManager.cpp
 *
 *  Created on: 2018年8月28日
 *      Author: colin
 */
#include "LogicOnhookManager.h"

void LogicOnhookManager::FullMessage(unsigned uid, User::OnhookReward* msg)
{
	try
	{
		CommonGiftConfig::CommonModifyItem cfg;
		cfg.mutable_based()->set_coin(0);
		cfg.mutable_based()->set_exp(0);
		DataBase& user  = BaseManager::Instance()->Get(uid);
		OnhookOfflineProp(user.last_off_time, Time::GetGlobalTime(), user.pass, cfg);
		LogicUserManager::Instance()->CommonProcess(uid, cfg, "onhook_offline_rewards", msg->mutable_commons(), 0);
	}
	catch(const exception& e)
	{
		error_log("onhook: %s", e.what());
		throw runtime_error("onhook_error");
	}

}

int LogicOnhookManager::OnhookExpOrCoin(OnhookType type, unsigned startTs, unsigned endTs, unsigned stageId)
{
	int res = 0;
	if(startTs > endTs)
		return 0;

	if(startTs == 0)
		startTs = Time::GetGlobalTime();
	unsigned ts = endTs - startTs;

	auto& onhookCfg = OnhookCfgWarp().GetRewardByStageId(stageId);
	unsigned add = 0;
	if(type == e_onhook_exp)
		add = onhookCfg.exp();
	if(type == e_onhook_coin)
		add = onhookCfg.coin();

	if(ts > ONHOOK_OFLINE_REWARD_TS)
		add *= (ONHOOK_OFLINE_REWARD_TS / 60);
	else
		add *= (ts / 60);

	res += (int)add;

	return res;
}

void LogicOnhookManager::OnhookOnlineProp()
{
	vector<unsigned> onlineUser;
	UserManager::Instance()->GetOnlineUsers(onlineUser);

	for(auto& uid: onlineUser)
	{
		DBCUserBaseWrap user(uid);
		auto& onhookCfg = OnhookCfgWarp().GetRewardByStageId(user.Obj().pass);
		int size = onhookCfg.propsid_size();
		int idx = Math::GetRandomInt(size);
		unsigned propId = onhookCfg.propsid(idx);


		User::OnhookOnlinePropReward *msg = new User::OnhookOnlinePropReward;
		LogicPropsManager::Instance()->AddProps(uid, propId, 1, "onhook_online_prop", msg->mutable_commons()->mutable_props());
		LMI->sendMsg(uid, msg);
	}

}

bool LogicOnhookManager::OnhookOfflineProp(unsigned startTs, unsigned endTs, unsigned stageId, CommonGiftConfig::CommonModifyItem& cfg)
{
	if(endTs < startTs)
		return false;

	if(startTs == 0)
		startTs = Time::GetGlobalTime();

	auto& onhookCfg = OnhookCfgWarp().GetRewardByStageId(stageId);
	int size = onhookCfg.propsid_size();

	if(size == 0)
		return false;

	unsigned ts = endTs - startTs;

	unsigned times = 0;
	//超过两天按两天算
	if(ts > ONHOOK_OFLINE_REWARD_TS)
		times = ONHOOK_OFLINE_REWARD_TS / 3600;
	else
		times = ts /3600;

	map<unsigned, unsigned> propsMap;
	int idx = 0;
	while(times--)
	{
		idx = Math::GetRandomInt(size);
		propsMap[idx]++;
	}
	for(auto &e : propsMap)
	{
		auto prop = cfg.add_props();
		prop->set_id(onhookCfg.propsid(e.first));
		prop->set_count(e.second);
	}

	return true;
}

