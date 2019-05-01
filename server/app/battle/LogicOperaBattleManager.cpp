#include "LogicOperaBattleManager.h"

int LogicOperaBattleManager::LoginCheck(unsigned uid)
{
	//检查累积登录数据是否加载进内存
	int ret = DataOperaBattleManager::Instance()->CheckBuff(uid);

	if (ret)   //内存中没有数据，可能是没有从dbc中取出来
	{
		DataOperaBattleManager::Instance()->LoadBuff(uid);
	}

	return 0;
}

int LogicOperaBattleManager::Process(unsigned uid, ProtoOperaBattle::OpenOperaBattleWindowReq* reqmsg, ProtoOperaBattle::OpenOperaBattleWindowResp * respmsg)
{
	OpenOperaBattleWindow(uid, respmsg);

	return 0;
}

int LogicOperaBattleManager::OpenOperaBattleWindow(unsigned uid, ProtoOperaBattle::OpenOperaBattleWindowResp * respmsg)
{
	//发送所有剧本奖励记录信息
	FullMessage(uid, respmsg->mutable_operabattles());

	//发送所有剧本记录信息
	FullMessage(uid, respmsg->mutable_records());

	return 0;
}

int LogicOperaBattleManager::Process(unsigned uid, ProtoOperaBattle::StartOperaBattleReq* reqmsg, ProtoOperaBattle::StartOperaBattleResp * respmsg)
{
	unsigned gateid = reqmsg->gateid();
	unsigned diff = reqmsg->difficulty();

	StartOperaBattle(uid, gateid, diff, respmsg);

	return 0;
}

int LogicOperaBattleManager::StartOperaBattle(unsigned uid, unsigned gateid, unsigned diff, ProtoOperaBattle::StartOperaBattleResp * respmsg)
{
	//校验参数
	if (diff < 1 || diff > MAX_DIFFICULTY)
	{
		error_log("wrong diff param. uid=%u,diff=%u", uid, diff);
		throw runtime_error("wrong_param");
	}

	//读取配置，获取资源消耗
	const OperaBattleConfig::DifficultyReward & diff_reward_cfg = OperaBattleConfigWrap().GetDifficultyRewardConfig(gateid, diff);
	int food_cost = diff_reward_cfg.cost_food();

	DBCUserBaseWrap userwrap(uid);
	userwrap.CostUserResource(0, 0, food_cost, 0, "OperaBattle");

	respmsg->set_food(userwrap.Obj().food);

	return 0;
}

int LogicOperaBattleManager::Process(unsigned uid, ProtoOperaBattle::EndOperaBattleReq* reqmsg, ProtoOperaBattle::EndOperaBattleResp * respmsg)
{
	unsigned gateid = reqmsg->gateid();
	unsigned diff = reqmsg->difficulty();
	unsigned usedtime = reqmsg->left_time();

	EndOperaBattle(uid, gateid, diff, usedtime, respmsg);

	return 0;
}

int LogicOperaBattleManager::EndOperaBattle(unsigned uid, unsigned gateid, unsigned diff, unsigned left_time,
		ProtoOperaBattle::EndOperaBattleResp * respmsg)
{
	//校验参数
	if (diff < 1 || diff > MAX_DIFFICULTY)
	{
		error_log("wrong param, diff or star. uid=%u, diff=%u", uid, diff);
		throw runtime_error("wrong_param");
	}

	MemoryRecord record;
	record.left_time = left_time;

	int user_index = ResourceManager::Instance()->GetIndex(uid);

	if (-1 == user_index)
	{
		error_log("get index from ResourceManager errror. uid=%u", uid);
		throw runtime_error("get_user_data_error");
	}

	sprintf(record.name, "%s", ResourceManager::Instance()->m_data->item[user_index].name);
	record.kingdom = ResourceManager::Instance()->m_data->item[user_index].kingdom;

	bool isexist = MemoryOperaBattleManager::Instance()->IsGateExist(gateid);

	if(!isexist)  //没有这个剧本的记录，则添加
	{
		MemoryOperaBattleManager::Instance()->Add(gateid);
	}

	unsigned index = MemoryOperaBattleManager::Instance()->GetIndex(gateid);

	//判断该难度的记录是否存在
	MemoryRecord & oldrecord = MemoryOperaBattleManager::Instance()->GetRecord(gateid, diff);

	if (oldrecord.kingdom == 0)  //之前未有记录
	{
		oldrecord.Replace(record);
	}
	else if (oldrecord < record)  //已有记录剩余用时小于现有记录
	{
		//旧记录剩余时间更少，用新记录替换
		oldrecord.Replace(record);
	}
	else
	{
		return 0;
	}

	//将新记录发送给前端
	oldrecord.SetMessage(respmsg->mutable_record());
	respmsg->set_gateid(gateid);
	respmsg->set_difficulty(diff);

	return 0;
}

int LogicOperaBattleManager::Process(unsigned uid, ProtoOperaBattle::ReceiveStarRewardReq* reqmsg, ProtoOperaBattle::ReceiveStarRewardResp * respmsg)
{
	unsigned gateid = reqmsg->gateid();
	unsigned diff = reqmsg->difficulty();
	unsigned star = reqmsg->star();
	unsigned battle_star = reqmsg->battle_star();

	ReceiveBattleReward(uid, gateid, diff, star, battle_star, respmsg);

	return 0;
}

int LogicOperaBattleManager::ReceiveBattleReward(unsigned uid, unsigned gateid, unsigned diff, unsigned star, unsigned battle_star,
		ProtoOperaBattle::ReceiveStarRewardResp * respmsg)
{
	//校验参数
	if (diff < 1 || diff > MAX_DIFFICULTY || star < 1 || star > MAX_STAR_VALUE)
	{
		error_log("wrong param, diff or star. uid=%u, diff=%u, star=%u", uid, diff, star);
		throw runtime_error("wrong_param");
	}

	//加载奖励领取记录
	bool isexist = DataOperaBattleManager::Instance()->IsDiffBattleExist(uid, gateid, diff);

	if (!isexist)  //不存在，则增加记录
	{
		DataOperaBattle  addbattle;
		addbattle.uid = uid;
		addbattle.gateid = gateid;
		addbattle.difficulty = diff;

		DataOperaBattleManager::Instance()->AddBuff(addbattle);
	}

	DataOperaBattle & operabattle = DataOperaBattleManager::Instance()->GetDiffBattle(uid, gateid, diff);

	//判断星级奖励是否可以领取
	if (operabattle.star >= star)
	{
		error_log("star reward alread have gotten. uid=%u,gateid=%u,diff=%u,star=%u", uid, gateid, diff, star);
		throw runtime_error("reward_already_gotten");
	}

	DBCUserBaseWrap userwrap(uid);
	const OperaBattleConfig::DifficultyReward & diff_reward_cfg = OperaBattleConfigWrap().GetDifficultyRewardConfig(gateid, diff);

	if (star > battle_star)  //花钻购买奖励
	{
		int need_cash = 0;

		for(int i = operabattle.star; i < star; ++i)
		{
			need_cash += diff_reward_cfg.star_reward(i).cash_cost();
		}

		userwrap.CostCash(need_cash, "OperaBattleReward");
	}

	respmsg->set_cash(userwrap.Obj().cash);

	//发放奖励
	for(int i = operabattle.star; i < star; ++i)
	{
		const OperaBattleConfig::StarReward& star_reward_cfg = diff_reward_cfg.star_reward(i);

		for(int j = 0; j < star_reward_cfg.reward_size(); ++j)
		{
			LogicUserManager::Instance()->OpReward(userwrap, star_reward_cfg.reward(j), "OperaBattleReward", respmsg->mutable_reward());
		}
	}

	operabattle.star = star;
	DataOperaBattleManager::Instance()->UpdateDiffBattle(operabattle);

	operabattle.SetMessage(respmsg->mutable_operabattle());

	return 0;
}

int LogicOperaBattleManager::FullMessage(unsigned uid, ProtoOperaBattle::MemoryOperaBattleRecordCPPAll * msg)
{
	vector<unsigned> indexs;
	MemoryOperaBattleManager::Instance()->GetIndexs(indexs);

	for(int i = 0; i < indexs.size(); ++i)
	{
		unsigned bindex = indexs[i];

		MemoryBattleInfo & battleinfo = MemoryOperaBattleManager::Instance()->m_data->data[bindex];

		if (battleinfo.gateid > 0)
		{
			battleinfo.SetMessage(msg->add_battle_record());
		}
	}

	return 0;
}

int LogicOperaBattleManager::FullMessage(unsigned uid, ProtoOperaBattle::OperaBattleCPPAll * msg)
{
	vector<unsigned> indexs;

	DataOperaBattleManager::Instance()->GetBattles(uid, indexs);

	for(int i = 0; i < indexs.size(); ++i)
	{
		unsigned bindex = indexs[i];

		DataOperaBattle & operabattle  = DataOperaBattleManager::Instance()->GetDiffBattle(bindex);
		operabattle.SetMessage(msg->add_operabattles());
	}

	return 0;
}
