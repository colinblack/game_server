#include "LogicShakeDiceActivity.h"

int LogicShakeDiceActivity::NewUserInit(unsigned uid)
{
	//初始化
	DataShakeDiceManager::Instance()->New(uid);

	return 0;
}


int LogicShakeDiceActivity::LoginCheck(unsigned uid)
{
	//检查摇骰子数据是否加载进内存
	int ret = DataShakeDiceManager::Instance()->CheckBuff(uid);

	if (ret)   //内存中没有数据，可能是没有从dbc中取出来
	{
		ret = DataShakeDiceManager::Instance()->LoadBuff(uid);

		if (R_ERR_NO_DATA == ret)  //没有数据，则需初始化
		{
			NewUserInit(uid);
		}
	}

	return 0;
}

int LogicShakeDiceActivity::Process(unsigned uid, ProtoShakeDice::OpenShakeDiceWindowReq *reqmsg, ProtoShakeDice::OpenShakeDiceWindowResp * respmsg)
{
	OpenWindow(uid, respmsg);

	return 0;
}

int LogicShakeDiceActivity::OpenWindow(unsigned uid, ProtoShakeDice::OpenShakeDiceWindowResp * respmsg)
{
	int ret = CheckActivity(uid);

	if (ret)
	{
		error_log("activity_not_on. uid=%u", uid);
		throw runtime_error("activity_not_open");
	}

	DataShakeDice & shakedice = DataShakeDiceManager::Instance()->GetShakeDice(uid);

	shakedice.SetMessage(respmsg->mutable_dice());

	return 0;
}

int LogicShakeDiceActivity::Process(unsigned uid, ProtoShakeDice::RollDiceReq *reqmsg, ProtoShakeDice::RollDiceResp * respmsg)
{
	RollDice(uid, respmsg);

	return 0;
}

int LogicShakeDiceActivity::RollDice(unsigned uid, ProtoShakeDice::RollDiceResp * respmsg)
{
	int ret = CheckActivity(uid);

	if (ret)
	{
		error_log("activity_not_on. uid=%u", uid);
		throw runtime_error("activity_not_open");
	}

	//判断是否跨天
	DataShakeDice & shakedice = DataShakeDiceManager::Instance()->GetShakeDice(uid);
	unsigned now = Time::GetGlobalTime();

	if (CTime::GetDayInterval(shakedice.operate_ts, now))  //跨天
	{
		DailyReset(shakedice, now);
	}

	//获取配置
	ShakeDiceConfigWrap::BaseConfig basecfg;
	ShakeDiceConfigWrap().GetShakeBaseConfig(basecfg);

	DBCUserBaseWrap userwrap(uid);

	//判断次数
	if (shakedice.dice_times >= basecfg.free_times)  //免费次数用完
	{
		//扣钻
		userwrap.CostCash(basecfg.dice_cash, "RollDice");
	}
	else
	{
		shakedice.operate_ts = now;
		shakedice.dice_times += 1;
	}

	//摇色子，取步数
	int addstep = Math::GetRandomInt(dice_max_point) + 1;
	shakedice.steps += addstep;

	DataShakeDiceManager::Instance()->UpdateDataShakeDice(shakedice);

	respmsg->set_cash(userwrap.Obj().cash);
	shakedice.SetMessage(respmsg->mutable_dice());

	return 0;
}

int LogicShakeDiceActivity::Process(unsigned uid, ProtoShakeDice::ResetMapReq *reqmsg, ProtoShakeDice::ResetMapResp *respmsg)
{
	ResetActivityMap(uid, respmsg);

	return 0;
}

int LogicShakeDiceActivity::ResetActivityMap(unsigned uid, ProtoShakeDice::ResetMapResp * respmsg)
{
	int ret = CheckActivity(uid);

	if (ret)
	{
		error_log("activity_not_on. uid=%u", uid);
		throw runtime_error("activity_not_open");
	}

	//判断是否跨天
	DataShakeDice & shakedice = DataShakeDiceManager::Instance()->GetShakeDice(uid);
	unsigned now = Time::GetGlobalTime();

	if (CTime::GetDayInterval(shakedice.operate_ts, now))  //跨天
	{
		DailyReset(shakedice, now);
	}

	//获取配置
	ShakeDiceConfigWrap::BaseConfig basecfg;
	ShakeDiceConfigWrap().GetShakeBaseConfig(basecfg);

	//判断次数
	if (shakedice.reset_times >= basecfg.reset_times)  //每日重置次数设置
	{
		error_log("reset time already used out. uid=%u,limit=%u", uid, basecfg.reset_times);
		throw runtime_error("reset_times_not_enough");
	}

	//扣钻
	DBCUserBaseWrap userwrap(uid);
	userwrap.CostCash(basecfg.reset_cash, "Dice_ResetMap");

	shakedice.operate_ts = now;
	shakedice.reset_times += 1;

	//重置地图
	ResetMap(shakedice);
	DataShakeDiceManager::Instance()->UpdateDataShakeDice(shakedice);

	//设置活动数据
	shakedice.SetMessage(respmsg->mutable_dice());
	respmsg->set_cash(userwrap.Obj().cash);

	return 0;
}

int LogicShakeDiceActivity::Process(unsigned uid, ProtoShakeDice::PositionRewardReq *reqmsg, ProtoShakeDice::PositionRewardResp *respmsg)
{
	vector<unsigned> positions;

	for(int i = 0; i < reqmsg->pids_size(); ++i)
	{
		positions.push_back(reqmsg->pids(i));
	}

	WalkRecieveReward(uid, positions, respmsg);

	return 0;
}

int LogicShakeDiceActivity::WalkRecieveReward(unsigned uid, vector<unsigned> & positions, ProtoShakeDice::PositionRewardResp * respmsg)
{
	int ret = CheckActivity(uid);

	if (ret)
	{
		error_log("activity_not_on. uid=%u", uid);
		throw runtime_error("activity_not_open");
	}

	if (positions.size() < 2)
	{
		error_log("wrong param pids. uid=%u", uid);
		throw runtime_error("wrong_param");
	}

	int steps = positions.size() - 1;
	DataShakeDice & shakedice = DataShakeDiceManager::Instance()->GetShakeDice(uid);

	//步数是否足够
	if (shakedice.steps < steps)
	{
		error_log("steps not enough. uid=%u,step=%u,need_step=%u", uid, shakedice.steps, steps);
		throw runtime_error("steps_not_enough");
	}

	shakedice.steps -= steps;

	//获取开服相关的奖励配置
	ShakeDiceConfigWrap shakeconfigwrap;

	unsigned diff = LogicManager::Instance()->GetOpenDays();
	const ShakeDiceConfig::MapInfo & map_reward = shakeconfigwrap.GetMapInfoConfig(diff, shakedice.curmap);
	DBCUserBaseWrap userwrap(uid);

	for(int i = 0 ; i < positions.size(); ++i)
	{
		//判断指定id是否已经领取奖励
		unsigned pid = positions[i];
		//是否领取校验
		bool iszero = false;
		int pos = pid - 1;
		unsigned value = GetMapRewardStatus(shakedice);
		iszero = LogicCommonUtil::CheckPosIsZero(value, pos);

		if (!iszero)   //非0，表示已领取
		{
			continue;
		}

		//发放奖励
		const ShakeDiceConfig::PointReward & point_reward_cfg = map_reward.points_reward(pos);

		if (point_reward_cfg.reward_size())
		{
			for(int j = 0; j < point_reward_cfg.reward_size(); ++j)
			{
				LogicUserManager::Instance()->OpReward(userwrap, point_reward_cfg.reward(j), "RollDice", respmsg->mutable_reward());
			}

			//设置奖励领取标志位
			SetMapRewardStatus(shakedice, pos);
		}
	}

	shakedice.curpos = positions[steps];
	DataShakeDiceManager::Instance()->UpdateDataShakeDice(shakedice);

	shakedice.SetMessage(respmsg->mutable_dice());

	return 0;
}


int LogicShakeDiceActivity::Process(unsigned uid, ProtoShakeDice::EnterMapReq *reqmsg, ProtoShakeDice::EnterMapResp * respmsg)
{
	unsigned mapid = reqmsg->mapid();

	EnterActivityMap(uid, mapid, respmsg);

	return 0;
}

int LogicShakeDiceActivity::EnterActivityMap(unsigned uid, unsigned mapid, ProtoShakeDice::EnterMapResp * respmsg)
{
	int ret = CheckActivity(uid);

	if (ret)
	{
		error_log("activity_not_on. uid=%u", uid);
		throw runtime_error("activity_not_open");
	}

	if (mapid < 1 || mapid > max_map_num)
	{
		error_log("mapid param error. uid=%u,mapid=%u", uid, mapid);
		throw runtime_error("param_error");
	}

	DataShakeDice & shakedice = DataShakeDiceManager::Instance()->GetShakeDice(uid);

	unsigned status = GetMapStatus(shakedice, mapid);

	if (status != map_status_process)
	{
		error_log("mapid can not allow to get in. uid=%u,mapid=%u", uid, mapid);
		throw runtime_error("can_not_get_in");
	}

	shakedice.curmap = mapid;

	DataShakeDiceManager::Instance()->UpdateDataShakeDice(shakedice);

	shakedice.SetMessage(respmsg->mutable_dice());

	return 0;
}

int LogicShakeDiceActivity::Process(unsigned uid, ProtoShakeDice::UnlockMapReq *reqmsg, ProtoShakeDice::UnlockMapResp *respmsg)
{
	unsigned mapid = reqmsg->mapid();

	UnlockMap(uid, mapid, respmsg);

	return 0;
}

int LogicShakeDiceActivity::UnlockMap(unsigned uid, unsigned mapid, ProtoShakeDice::UnlockMapResp * respmsg)
{
	int ret = CheckActivity(uid);

	if (ret)
	{
		error_log("activity_not_on. uid=%u", uid);
		throw runtime_error("activity_not_open");
	}
	//解锁地图
	//判断地图是否已解锁
	DataShakeDice & shakedice = DataShakeDiceManager::Instance()->GetShakeDice(uid);

	unsigned status = GetMapStatus(shakedice, mapid);

	if (status != map_status_lock)
	{
		error_log("mapid is unlock. uid=%u,mapid=%u", uid, mapid);
		throw runtime_error("already_unlock");
	}

	if (mapid != shakedice.curmap + 1)
	{
		error_log("param mapid value error. should be curmap's next. uid=%u,mapid=%u,curmap=%u", uid, mapid, shakedice.curmap);
		throw runtime_error("param_error");
	}

	//判断是否能解锁
	//判断飞机是否在终点上
	int finalpid = GetFinalPositionId(shakedice.curmap);

	if (shakedice.curpos != finalpid)
	{
		error_log("user not in final position. uid=%u", uid);
		throw runtime_error("not_in_final_position");
	}

	bool ishave = IsHaveExtraReward(shakedice);

	if (ishave && 0 == shakedice.extra_reward_status)
	{
		error_log("extra reward not get. uid=%u", uid);
		throw runtime_error("extra_reward_not_get");
	}

	//正式解锁
	SetMapStatus(shakedice, shakedice.curmap, map_status_complete);  //设置当前地图完成
	SetMapStatus(shakedice, mapid, map_status_process);

	shakedice.extra_reward_status = 0;  //重置额外奖励状态
	shakedice.curpos = 1; //重置当前位置

	DataShakeDiceManager::Instance()->UpdateDataShakeDice(shakedice);

	shakedice.SetMessage(respmsg->mutable_dice());

	return 0;
}

int LogicShakeDiceActivity::Process(unsigned uid, ProtoShakeDice::ReceiveExtraRewardReq *reqmsg, ProtoShakeDice::ReceiveExtraRewardResp *respmsg)
{
	GetExtraReward(uid, respmsg);

	return 0;
}

int LogicShakeDiceActivity::GetExtraReward(unsigned uid, ProtoShakeDice::ReceiveExtraRewardResp * respmsg)
{
	int ret = CheckActivity(uid);

	if (ret)
	{
		error_log("activity_not_on. uid=%u", uid);
		throw runtime_error("activity_not_open");
	}

	//判断是否可以领取当前奖励
	DataShakeDice & shakedice = DataShakeDiceManager::Instance()->GetShakeDice(uid);

	unsigned status = GetMapStatus(shakedice, shakedice.curmap);

	if (map_status_process != status)
	{
		error_log("map is not process. uid=%u,mapid=%u", uid, shakedice.curmap);
		throw runtime_error("map_not_processing");
	}

	//获取开服相关的奖励配置
	ShakeDiceConfigWrap shakeconfigwrap;
	unsigned diff = LogicManager::Instance()->GetOpenDays();
	const ShakeDiceConfig::MapInfo & map_reward = shakeconfigwrap.GetMapInfoConfig(diff, shakedice.curmap);

	bool isHave = IsHaveExtraReward(shakedice);

	//判断是否有额外奖励，且未领取
	if (!isHave)
	{
		error_log("condition not match. uid=%u", uid);
		throw runtime_error("condition_not_match");
	}

	if (shakedice.extra_reward_status)
	{
		error_log("extra reward already been gotten. uid=%u", uid);
		throw runtime_error("condition_not_match");
	}

	DBCUserBaseWrap userwrap(uid);

	//领取额外奖励
	for(int i = 0; i < map_reward.extra_reward_size(); ++i)
	{
		LogicUserManager::Instance()->OpReward(userwrap, map_reward.extra_reward(i), "ShakeDiceFinial", respmsg->mutable_reward());
	}

	//设置额外奖励领取状态
	shakedice.extra_reward_status = 1;
	DataShakeDiceManager::Instance()->UpdateDataShakeDice(shakedice);

	shakedice.SetMessage(respmsg->mutable_dice());

	return 0;
}

bool LogicShakeDiceActivity::IsHaveExtraReward(DataShakeDice & shakedice)
{
	unsigned diff = LogicManager::Instance()->GetOpenDays();
	const ShakeDiceConfig::MapInfo & map_reward = ShakeDiceConfigWrap().GetMapInfoConfig(diff, shakedice.curmap);

	unsigned target = 0;
	unsigned value = GetMapRewardStatus(shakedice);

	//比较值中1的个数和配置的奖励个数是否匹配
	int count = 0;

	while(value)
	{
		++count;
		value &= value - 1;
	}

	//统计奖励中的点个数
	int reward_point = 0;

	for(int i = 0; i < map_reward.points_reward_size(); ++i)
	{
		if (map_reward.points_reward(i).reward_size() > 0 )
		{
			++reward_point;
		}
	}

	if (count >= reward_point)
	{
		return true;
	}

	return false;
}

int LogicShakeDiceActivity::GetFinalPositionId(unsigned mapid)
{
	unsigned diff = LogicManager::Instance()->GetOpenDays();
	const ShakeDiceConfig::MapInfo & map_reward = ShakeDiceConfigWrap().GetMapInfoConfig(diff, mapid);

	int max_points = map_reward.points();  //当前地图的点数

	return map_reward.points_reward(max_points - 1).pid();
}

unsigned LogicShakeDiceActivity::GetMapRewardStatus(DataShakeDice & shakedice)
{
	switch(shakedice.curmap)
	{
		case 1: return shakedice.map1_rewards;
		case 2: return shakedice.map2_rewards;
		case 3: return shakedice.map3_rewards;
		default: break;
	}

	return 0;
}

int LogicShakeDiceActivity::SetMapRewardStatus(DataShakeDice & shakedice, unsigned pos)
{
	switch(shakedice.curmap)
	{
		case 1: LogicCommonUtil::SetBitCurrent(shakedice.map1_rewards, pos); break;
		case 2: LogicCommonUtil::SetBitCurrent(shakedice.map2_rewards, pos); break;
		case 3: LogicCommonUtil::SetBitCurrent(shakedice.map3_rewards, pos); break;
		default: break;
	}

	return 0;
}

unsigned LogicShakeDiceActivity::GetMapStatus(DataShakeDice & shakedice, unsigned curmap)
{
	switch(curmap)
	{
		case 1: return shakedice.map1_status;
		case 2: return shakedice.map2_status;
		case 3: return shakedice.map3_status;

		default: break;
	}

	return 0;
}

int LogicShakeDiceActivity::SetMapStatus(DataShakeDice & shakedice, unsigned curmap, unsigned status)
{
	switch(curmap)
	{
		case 1: shakedice.map1_status = status; break;
		case 2: shakedice.map2_status = status; break;
		case 3: shakedice.map3_status = status; break;
		default: break;
	}

	return 0;
}

int LogicShakeDiceActivity::CheckActivity(unsigned uid)
{
	if (!IsOn())
	{
		return R_ERROR;
	}

	DataShakeDice & shakedice = DataShakeDiceManager::Instance()->GetShakeDice(uid);

	User::ActivityItem act;

	ConfigManager::Instance()->GetActivity(e_Activity_ShakeDice, act);

	//判断是否新版本
	if (act.ver() != shakedice.version)
	{
		//重置活动数据
		ResetActivity(shakedice, act.ver());

		DataShakeDiceManager::Instance()->UpdateDataShakeDice(shakedice);
	}

	return 0;
}

int LogicShakeDiceActivity::ResetMap(DataShakeDice & shakedice)
{
	//重置3张地图
	shakedice.curmap = 1;
	shakedice.curpos = 1;

	shakedice.map1_status = 1;
	shakedice.map2_status = 0;
	shakedice.map3_status = 0;

	shakedice.extra_reward_status = 0;

	shakedice.map1_rewards = 0;
	shakedice.map2_rewards = 0;
	shakedice.map3_rewards = 0;

	return 0;
}

int LogicShakeDiceActivity::DailyReset(DataShakeDice & shakedice, unsigned now)
{
	shakedice.dice_times = 0;
	shakedice.reset_times= 0;

	shakedice.operate_ts = now;

	return 0;
}

int LogicShakeDiceActivity::ResetActivity(DataShakeDice & shakedice, unsigned version)
{
	shakedice.Clear();
	shakedice.version = version;
	shakedice.curmap = 1;
	shakedice.map1_status = 1;
	shakedice.curpos = 1;

	return 0;
}

