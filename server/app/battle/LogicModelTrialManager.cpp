#include "LogicModelTrialManager.h"

int LogicModelTrialManager::Process(unsigned uid, ProtoModelTrial::OpenModelWindowReq *reqmsg, ProtoModelTrial::OpenModelWindowResp * respmsg)
{
	OpenWindow(uid, respmsg);

	return 0;
}

int LogicModelTrialManager::OpenWindow(unsigned uid, ProtoModelTrial::OpenModelWindowResp * respmsg)
{
	DataModelTrial&  modeltrial = DataModelTrialManager::Instance()->GetModelTrial(uid);

	unsigned now = Time::GetGlobalTime();

	if (CTime::GetDayInterval(modeltrial.resetts, now))  //跨天重置次数
	{
		modeltrial.fight_times = 0;
		modeltrial.buy_times = 0;

		modeltrial.resetts = now;

		DataModelTrialManager::Instance()->UpdateModelTrial(modeltrial);
	}

	modeltrial.SetMessage(respmsg->mutable_modeltrial());

	return 0;
}

int LogicModelTrialManager::Process(unsigned uid, ProtoModelTrial::BuyFightTimesReq *reqmsg, ProtoModelTrial::BuyFightTimesResp * respmsg)
{
	BuyFightTimes(uid, respmsg);

	return 0;
}

int LogicModelTrialManager::BuyFightTimes(unsigned uid, ProtoModelTrial::BuyFightTimesResp * respmsg)
{
	ModelTrialConfigWrap trialconfig;

	int maxtimes = trialconfig.GetMaxBuytimes();

	//判断购买次数是否达到最大
	DataModelTrial&  modeltrial = DataModelTrialManager::Instance()->GetModelTrial(uid);

	if (modeltrial.buy_times >= maxtimes)
	{
		error_log("buy already max times. uid=%u.maxtime=%d", uid, maxtimes);
		throw runtime_error("already_maxtimes");
	}

	//只有免费次数用完之后才可以进行购买
	if (modeltrial.fight_times < max_free_times)
	{
		error_log("still have free times. uid=%u.fighttimes=%u", uid, modeltrial.fight_times);
		throw runtime_error("free_times_left");
	}

	int buytimes = modeltrial.buy_times + 1;
	int price = trialconfig.GetPrice(buytimes);

	DBCUserBaseWrap userwrap(uid);
	userwrap.CostCash(price, "BuyTrialTimes");

	modeltrial.buy_times += 1;
	DataModelTrialManager::Instance()->UpdateModelTrial(modeltrial);

	respmsg->set_cash(userwrap.Obj().cash);
	modeltrial.SetMessage(respmsg->mutable_modeltrial());

	return 0;
}

int LogicModelTrialManager::Process(unsigned uid, ProtoModelTrial::StartTrialGateReq *reqmsg, ProtoModelTrial::StartTrialGateResp * respmsg)
{
	unsigned pos = reqmsg->pos();
	unsigned gateid = reqmsg->gateid();
	vector<unsigned> heros;

	for(int i = 0; i < reqmsg->heros_size(); ++i)
	{
		heros.push_back(reqmsg->heros(i));
	}

	return StartTrialGate(uid, pos, gateid, heros, respmsg);
}

int LogicModelTrialManager::StartTrialGate(unsigned uid, unsigned pos, unsigned gateid, vector<unsigned> & heros, ProtoModelTrial::StartTrialGateResp * respmsg)
{
	//先判断是否是机型试验的闯关
	if (!IsTrialGate(gateid))
	{
		error_log("gate not model trial gate. uid=%u,gateid=%u", uid, gateid);
		return 0;
	}

	DataModelTrial&  modeltrial = DataModelTrialManager::Instance()->GetModelTrial(uid);

	ModelTrialConfigWrap trialconfig;
	int maxtimes = modeltrial.buy_times + max_free_times;

	//判断是否可以挑战当前关卡.curpos表示已闯过的最大关卡位置，因此，下一个位置是可以挑战的，但是再下一个不行.
	if ((modeltrial.curpos + 1) < pos)
	{
		error_log("can't gate in curpos's next's next. uid=%u", uid);
		throw runtime_error("can_not_start_gate");
	}

	if (modeltrial.fight_times >= maxtimes)
	{
		error_log("gate already max times. uid=%u.maxtime=%d", uid, maxtimes);
		throw runtime_error("have_no_times");
	}

	const ModelTrialConfig::TrialGate & trialgatecfg = trialconfig.GetTrialGateConfig(gateid);

	unsigned gid = trialgatecfg.terrain();
	//我方参战英雄
	vector<HeroPropertyItemIndex> heroPropertys;
	for (int i = 0;i < heros.size(); ++i)
	{
		heroPropertys.push_back(HeroPropertyItemIndex(uid, heros[i]));
	}

	vector<unsigned> npcs;

	for(int  i = 0;i < trialgatecfg.npcs_size(); i++)
	{
		npcs.push_back(trialgatecfg.npcs(i));
	}

	double diff = 1;

	int ret = WMI->CreateGateFight(uid, gateid, gid, heroPropertys, npcs, diff);

	if (ret)
	{
		return ret;
	}

	modeltrial.fight_times += 1;
	DataModelTrialManager::Instance()->UpdateModelTrial(modeltrial);

	modeltrial.SetMessage(respmsg->mutable_modeltrial());

	return 0;
}

int LogicModelTrialManager::EndTrialGate(unsigned uid, unsigned gateid)
{
	//判断是否有该关卡的配置
	if (!ConfigManager::Instance()->trialIndex.count(gateid))
	{
		error_log("config have no gateid. uid=%u.gateid=%u", uid, gateid);
		return R_ERROR;
	}

	//根据gateid获取位置
	int pos = ConfigManager::Instance()->trialIndex[gateid] + 1;

	try
	{
		ProtoModelTrial::PushTrialRewardReq *pushmsg = new ProtoModelTrial::PushTrialRewardReq;

		//判断是否是首次通关，如何判断?根据pos判断即可，只要比当前最大关卡位置大，则首次通关
		bool isfirst = false;
		DataModelTrial&  modeltrial = DataModelTrialManager::Instance()->GetModelTrial(uid);

		if (modeltrial.curpos < pos)  //首次通关
		{
			isfirst = true;
			modeltrial.curpos = pos;
			DataModelTrialManager::Instance()->UpdateModelTrial(modeltrial);

			modeltrial.SetMessage(pushmsg->mutable_modeltrial());
		}

		pushmsg->set_isfirst(isfirst);

		ModelTrialConfigWrap trialconfig;
		//发放奖励
		DBCUserBaseWrap userwrap(uid);
		const ModelTrialConfig::TrialGate & trialgatecfg = trialconfig.GetTrialGateConfig(gateid);

		if (isfirst)  //首次通关奖励
		{
			char szreason[100] = {0};
			sprintf(szreason, "TrialGateFirst_%d", pos);

			for(int i = 0; i < trialgatecfg.first_reward_size(); ++i)
			{
				LogicUserManager::Instance()->OpReward(userwrap, trialgatecfg.first_reward(i), szreason, pushmsg->mutable_reward());
			}
		}

		//首通奖励之后，闯关奖励也要发
		for(int i = 0; i < trialgatecfg.reward_size(); ++i)
		{
			LogicUserManager::Instance()->OpReward(userwrap, trialgatecfg.reward(i), "TrialGate", pushmsg->mutable_reward());
		}

		LogicManager::Instance()->sendMsg(uid, pushmsg);
	}
	catch(runtime_error &e)
	{
		error_log("exception. uid=%u,reason=%s", uid, e.what());
		return R_ERROR;
	}

	return 0;
}

bool LogicModelTrialManager::IsTrialGate(unsigned gateid)
{
	if (gateid >= e_gt_trial_min && gateid <= e_gt_trial_max)  //试验战的关卡范围
	{
		return true;
	}

	return false;
}
