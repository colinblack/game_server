#include "LogicDailyMissionManager.h"

int LogicDailyMissionManager::NewUserInit(unsigned uid)
{
	for(int i = 0; i < max_daily_mission; ++i)
	{
		//初始化空的数据
		DataDailyMission dailymission;
		dailymission.uid = uid;
		dailymission.id = i+1;

		DataDailyMissionManager::Instance()->AddBuff(dailymission);
	}

	ProtoDailyMission::DailyMissionAllCPP msg;

	try
	{
		//刷新每日任务
		RefreshMission(uid, &msg);
	}
	catch(runtime_error &e)
	{
		return R_ERROR;
	}

	return 0;
}

int LogicDailyMissionManager::LoginCheck(unsigned uid)
{
	//检查累积登录数据是否加载进内存
	int ret = DataDailyMissionManager::Instance()->CheckBuff(uid);

	if (ret)   //内存中没有数据，可能是没有从dbc中取出来
	{
		ret = DataDailyMissionManager::Instance()->LoadBuff(uid);

		if (R_ERR_NO_DATA == ret)
		{
			return NewUserInit(uid);
		}
	}

	return ret;
}

int LogicDailyMissionManager::Process(unsigned uid, ProtoDailyMission::RefreshDailyMissionReq* reqmsg, ProtoDailyMission::RefreshDailyMissionResp* respmsg)
{
	//普通刷新
	CommonRefreshMission(uid, respmsg);

	return 0;
}

int LogicDailyMissionManager::CommonRefreshMission(unsigned uid, ProtoDailyMission::RefreshDailyMissionResp * msg)
{
	DBCUserBaseWrap userwrap(uid);

	//判断是否有免费次数
	if (0 == userwrap.Obj().daily_free_times)
	{
		userwrap.Obj().daily_free_times += 1;
	}
	else
	{
		unsigned now = Time::GetGlobalTime();

		//获取当前每日任务中的第一个任务,序号为1的任务
		DataDailyMission& first_mission = DataDailyMissionManager::Instance()->GetDailyMission(uid, first_seq_mission);

		bool iscdtime = false;  //是否处于cd中
		unsigned nextts = userwrap.Obj().daily_refresh_ts + 3600;

		//判断是否处于cd时间内
		if (now < nextts)
		{
			iscdtime = true;
		}

		if (iscdtime)
		{
			error_log("[CommonRefreshMission] refresh is in cd. uid=%u,now=%u,next_ts=%u", uid, now, nextts);
			throw runtime_error("refresh_in_cd");
		}

		//更新cd时间
		userwrap.Obj().daily_refresh_ts = now;
	}

	userwrap.Save();

	//不在cd中，可以刷新
	RefreshMission(uid, msg->mutable_missionall());
	msg->set_refreshtime(userwrap.Obj().daily_refresh_ts);
	msg->set_freetimes(userwrap.Obj().daily_free_times);

	return 0;
}

int LogicDailyMissionManager::Process(unsigned uid, ProtoDailyMission::CashRefreshMissionReq* reqmsg, ProtoDailyMission::CashRefreshMissionResp* respmsg)
{
	//钻石刷新
	CashRefreshMission(uid, respmsg);

	return 0;
}

int LogicDailyMissionManager::CashRefreshMission(unsigned uid, ProtoDailyMission::CashRefreshMissionResp * msg)
{
	//花钻刷新，无视cd
	//扣钻
	DBCUserBaseWrap  userwrap(uid);
	userwrap.CostCash(pay_refresh_cash, "DailyMission_Refresh");

	msg->set_cash(userwrap.Obj().cash);

	//刷新，且不改变原来的cd时间
	RefreshMission(uid, msg->mutable_missionall());

	return 0;
}

int LogicDailyMissionManager::Process(unsigned uid, ProtoDailyMission::OpenDailyMissionWindowReq* reqmsg, ProtoDailyMission::OpenDailyMissionWindowResp* respmsg)
{
	//打开每日任务窗口
	OpenDailyMissionWindow(uid, respmsg->mutable_missionall());

	return 0;
}

int LogicDailyMissionManager::OpenDailyMissionWindow(unsigned uid, ProtoDailyMission::DailyMissionAllCPP * msg)
{
	//遍历所有的每日任务
	vector<unsigned> mission_indexs;
	DataDailyMissionManager::Instance()->GetDailyMissions(uid, mission_indexs);

	for(int i = 0; i < mission_indexs.size(); ++i)
	{
		DataDailyMission& dailymission = DataDailyMissionManager::Instance()->GetDailyMission(mission_indexs[i]);

		//排除已完成的任务
		if (0 != dailymission.status)
		{
			dailymission.SetMessage(msg->add_missions());
			continue;
		}

		//根据任务id，获取任务配置
		const DailyMissionConfig::DailyMission & missioncfg = DailyMissionConfigWrap().GetDailyMissionCfg(dailymission.missid);
		int type = missioncfg.type();

		//只处理杀敌和功勋等不能实时更新的任务，但是其他任务都需要返回给前端
		switch(type)
		{
			case daily_mission_type_exploit:
			case daily_mission_type_kill:
			{
				DailyMissionParam param;
				param.type = type;
				VerifyDailyMission(dailymission, param);
				dailymission.SetMessage(msg->add_missions());
				break;
			}
			default: dailymission.SetMessage(msg->add_missions()); break;
		}
	}

	return 0;
}

int LogicDailyMissionManager::Process(unsigned uid, ProtoDailyMission::GetDailyMissionRewardReq* reqmsg, ProtoDailyMission::GetDailyMissionRewardResp* respmsg)
{
	//领取奖励
	unsigned missid = reqmsg->missid();

	GetDailyMissionReward(uid, missid, respmsg);

	return 0;
}

int LogicDailyMissionManager::GetDailyMissionReward(unsigned uid, unsigned missid, ProtoDailyMission::GetDailyMissionRewardResp * respmsg)
{
	//判断每日任务的领取次数是否足够
	DBCUserBaseWrap  userwrap(uid);

	if (userwrap.Obj().daily_reward_times >= max_reward_times)
	{
		error_log("[GetDailyMissionReward] get mission reward times is used out. uid=%u,missid=%u", uid, missid);
		throw runtime_error("mission_times_used_out");
	}

	//获取每日任务的数据
	DataDailyMission& dailymission = DataDailyMissionManager::Instance()->GetDailyMissionByMissid(uid, missid);

	//判断是否满足领取的条件
	if (0 == dailymission.status)
	{
		error_log("[GetDailyMissionReward] mission not complete. uid=%u,missid=%u", uid, missid);
		throw runtime_error("mission_not_complete");
	}
	else if (2 == dailymission.status)
	{
		error_log("[GetDailyMissionReward] mission reward already got. uid=%u,missid=%u", uid, missid);
		throw runtime_error("reward_already_get");
	}

	//根据任务id，获取任务配置
	const DailyMissionConfig::DailyMission & missioncfg = DailyMissionConfigWrap().GetDailyMissionCfg(dailymission.missid);

	//计算经验奖励
	//根据星级，获取星级系数
	double coefficient = missioncfg.starcoefficient(dailymission.star - 1);
	int addexp = missioncfg.exp() * coefficient;

	userwrap.AddExp(addexp);   //内部已处理了升级的推送

	dailymission.status = 2;
	DataDailyMissionManager::Instance()->UpdateDailyMission(dailymission);

	dailymission.SetMessage(respmsg->mutable_mission());

	//更新次数
	userwrap.Obj().daily_reward_times += 1;
	userwrap.Save();

	respmsg->set_reward_times(userwrap.Obj().daily_reward_times);
	respmsg->set_exp(userwrap.Obj().exp);

	//todo 接入每日任务领取奖励成就
	if (dailymission.star >= 3)
	{
	    LogicAchievementManager::AchievementParam achievementparam;
		achievementparam.type = achievement_type_dailymission;

		LogicAchievementManager::Instance()->VerifyAchievementComplete(uid, achievementparam);
	}

	return 0;
}

int LogicDailyMissionManager::RefreshMission(unsigned uid, ProtoDailyMission::DailyMissionAllCPP * msg)
{
	unsigned now = Time::GetGlobalTime();

	//获取用户当前的所有每日任务
	vector<unsigned> mission_indexs;
	DataDailyMissionManager::Instance()->GetDailyMissions(uid, mission_indexs);

	if (0 == mission_indexs.size())
	{
		return R_ERROR;
	}

	//todo 从科技系统中获取当前的每日任务科技
	int tech = 1;

	try
	{
		tech = LogicScienceMgr::Instance()->GetDayTaskLevel(uid);
	}
	catch(const std::exception& e)
	{
		;
	}

	//根据科技读取配置
	const DailyMissionConfig::DailyMissionsItem & dailymissons = DailyMissionConfigWrap().GetDailyMissionItem(tech -1 );
	set<int> refresh_mission;   //任务下标集合
	vector<unsigned> rates;

	for(int i = 0; i < dailymissons.missions_size(); ++i)
	{
		unsigned rate = dailymissons.missions(i).rate();
		rates.push_back(rate);
	}

	//清除每日任务的映射
	DataDailyMissionManager::Instance()->ClearMissidIndex(uid);

	//随机每日任务，附带上概率数组的条件，以免while中死循环
	for(int j = 0; j < mission_indexs.size() && j < rates.size(); ++j)
	{
		//先随机选取任务下标
		int target = 0;

		while(true)
		{
			LogicCommonUtil::TurnLuckTable(rates, rates.size(), target);

			if (!refresh_mission.count(target))   //对应下标第一次出现
			{
				refresh_mission.insert(target);
				break;
			}
		}

		//随机星级
		vector<unsigned> starrates;

		for(int k = 0; k < dailymissons.missions(target).starrate_size(); ++k)
		{
			unsigned rate = dailymissons.missions(target).starrate(k);
			starrates.push_back(rate);
		}

		int star_target = 0;
		LogicCommonUtil::TurnLuckTable(starrates, starrates.size(), star_target);

		DataDailyMission& dailymission = DataDailyMissionManager::Instance()->GetDailyMission(mission_indexs[j]);

		//每日任务数据清理
		dailymission.Clear();

		//修改missid,gettime.base -稍后处理
		dailymission.missid = dailymissons.missions(target).id();
		dailymission.star = star_target + 1;
		dailymission.gettime = now;

		//任务刷新后，进行前期的特殊处理，记录下那些递增的数据的初始值
		PrepareMission(dailymission);

		//更新
		DataDailyMissionManager::Instance()->UpdateDailyMission(dailymission);

		//协议设置
		dailymission.SetMessage(msg->add_missions());
	}

	return 0;
}

int LogicDailyMissionManager::PrepareMission(DataDailyMission & dailymission)
{
	//根据任务id，获取任务配置，根据type判断是否需要初期处理
	const DailyMissionConfig::DailyMission & missioncfg = DailyMissionConfigWrap().GetDailyMissionCfg(dailymission.missid);

	int type = missioncfg.type();

	switch(type)
	{
		case daily_mission_type_productivity: PrepareProductivity(dailymission, missioncfg.subtype()); break;
		case daily_mission_type_exploit: PrepareExploit(dailymission); break;
		case daily_mission_type_kill: PrepareKill(dailymission); break;
		default: break;
	}

	return 0;
}

int LogicDailyMissionManager::PrepareProductivity(DataDailyMission & dailymission, unsigned subtype)
{
	unsigned uid = dailymission.uid;

	//根据资源类型，获取当前产量
	int productivity = LogicBuildManager::Instance()->Yields(uid, subtype);
	dailymission.base = productivity;

	return 0;
}

int LogicDailyMissionManager::PrepareExploit(DataDailyMission & dailymission)
{
	unsigned uid = dailymission.uid;

	dailymission.base = GET_RMI(uid).reward;

	return 0;
}

int LogicDailyMissionManager::PrepareKill(DataDailyMission & dailymission)
{
	unsigned uid = dailymission.uid;

	dailymission.base = GET_RMI(uid).kill;

	return 0;
}

int LogicDailyMissionManager::VerifyDailyMissionComplete(unsigned uid, DailyMissionParam & param)
{
	//增加用户等级限制
	if (BaseManager::Instance()->Get(uid).level < 40)
	{
		return 0;
	}

	//遍历所有的每日任务
	vector<unsigned> mission_indexs;
	DataDailyMissionManager::Instance()->GetDailyMissions(uid, mission_indexs);

	//推送
	ProtoDailyMission::PushDailyMissionReq * msg = new ProtoDailyMission::PushDailyMissionReq;

	try
	{
		for(int i = 0; i < mission_indexs.size(); ++i)
		{
			DataDailyMission& dailymission = DataDailyMissionManager::Instance()->GetDailyMission(mission_indexs[i]);

			//排除已完成的任务
			if (0 != dailymission.status)
			{
				continue;
			}

			//根据任务id，获取任务配置
			const DailyMissionConfig::DailyMission & missioncfg = DailyMissionConfigWrap().GetDailyMissionCfg(dailymission.missid);
			int type = missioncfg.type();

			//排除非此类型的任务
			//对type=0的做特殊处理，意味着可以匹配任意类型
			if (param.type && param.type != type)
			{
				continue;
			}

			if (param.subparam.size() > 0 && type == daily_mission_type_productivity)   //这个只用于验证资源相关的成就
			{
				if (missioncfg.subtype() != param.subparam[0])  //子类型不一致，比如产量，配置的资源类型和发来的类型不一致
				{
					continue;
				}
			}

			VerifyDailyMission(dailymission, param);
			dailymission.SetMessage(msg->mutable_missionall()->add_missions());
		}
	}
	catch(runtime_error & e)
	{
		error_log("[VerifyDailyMissionComplete] exception:%s. uid=%u", e.what(), uid);
		delete msg;  //释放内存空间

		return R_ERROR;
	}

	if (0 == msg->missionall().missions_size())  //没有任务推送时，释放内存
	{
		delete msg;
	}
	else
	{
		LogicManager::Instance()->sendMsg(uid, msg);
	}

	return 0;
}

int LogicDailyMissionManager::VerifyDailyMission(DataDailyMission & dailymission, DailyMissionParam & param)
{
	if (0 == param.type)  //任务类型未知，则从配置文件中提取
	{
		//根据任务id，获取任务配置
		const DailyMissionConfig::DailyMission & missioncfg = DailyMissionConfigWrap().GetDailyMissionCfg(dailymission.missid);
		param.type = missioncfg.type();
	}

	int subvalue = 0;

	if (param.subparam.size() > 0)
	{
		subvalue = param.subparam[0];
	}

	switch(param.type)
	{
		case daily_mission_type_productivity: VerifyProductivity(dailymission); break;
		case daily_mission_type_affair: VerifyAffair(dailymission); break;
		case daily_mission_type_smelt: VerifyEquipSmelt(dailymission); break;
		case daily_mission_type_blackmarket: VerifyBlackMarket(dailymission);  break;
		case daily_mission_type_pkfield: VerifyPKField(dailymission); break;
		case daily_mission_type_upgrade_weapon: VerifyUpgradeWeapon(dailymission, subvalue); break;
		case daily_mission_type_minesupport: VerifyMineSupport(dailymission); break;
		case daily_mission_type_gate: VerifyGate(dailymission); break;
		case daily_mission_type_exploit: VerifyExploit(dailymission); break;
		case daily_mission_type_kill: VerifyKill(dailymission); break;
		case daily_mission_type_refresheqshop: VerifyEquipShopReresh(dailymission); break;
		case daily_mission_type_parade: VerifyParade(dailymission); break;
		case daily_mission_type_official: VerifyOfficial(dailymission); break;
		default : break;
	}

	DataDailyMissionManager::Instance()->UpdateDailyMission(dailymission);

	return 0;
}

int LogicDailyMissionManager::VerifyProductivity(DataDailyMission & dailymission)
{
	//根据任务id，获取任务配置
	const DailyMissionConfig::DailyMission & missioncfg = DailyMissionConfigWrap().GetDailyMissionCfg(dailymission.missid);

	unsigned uid = dailymission.uid;
	int subtype = missioncfg.subtype();

	//根据资源类型，获取当前产量
	int productivity = LogicBuildManager::Instance()->Yields(uid, subtype);
	int increment = productivity - dailymission.base;

	dailymission.current = increment;

	if (dailymission.current >= missioncfg.count())
	{
		dailymission.status = 1;
	}

	return 0;
}

int LogicDailyMissionManager::VerifyAffair(DataDailyMission & dailymission)
{
	//处理政务，调用一次，次数+1
	dailymission.current += 1;

	CheckMission(dailymission);

	return 0;
}

int LogicDailyMissionManager::VerifyEquipSmelt(DataDailyMission & dailymission)
{
	//调用一次，次数+1
	dailymission.current += 1;

	CheckMission(dailymission);
}

int LogicDailyMissionManager::VerifyBlackMarket(DataDailyMission & dailymission)
{
	//调用一次，次数+1
	dailymission.current += 1;

	CheckMission(dailymission);
}

int LogicDailyMissionManager::VerifyPKField(DataDailyMission & dailymission)
{
	//调用一次，次数+1
	dailymission.current += 1;

	CheckMission(dailymission);
}

int LogicDailyMissionManager::VerifyUpgradeWeapon(DataDailyMission & dailymission, unsigned gold)
{
	//调用一次，增加黄金使用量
	dailymission.current += gold;

	CheckMission(dailymission);
}

int LogicDailyMissionManager::VerifyMineSupport(DataDailyMission & dailymission)
{
	//调用一次，次数+1
	dailymission.current += 1;

	CheckMission(dailymission);
}

int LogicDailyMissionManager::VerifyGate(DataDailyMission & dailymission)
{
	//调用一次，次数+1
	dailymission.current += 1;

	CheckMission(dailymission);
}

int LogicDailyMissionManager::VerifyExploit(DataDailyMission & dailymission)
{
	//判断是否跨天
	unsigned now = Time::GetGlobalTime();
	unsigned uid = dailymission.uid;

	//判断接取任务到现在，是否跨天
	if (CTime::GetDayInterval(dailymission.gettime, now))  //跨天
	{
		dailymission.current += GET_RMI(uid).reward;   //已清过功勋
	}
	else  //未跨天
	{
		unsigned reward = GET_RMI(uid).reward;

		//二次校验是否重置
		//判断base大还是当前值大
		if (reward < dailymission.base)  //经历了功勋的重置
		{
			dailymission.current += reward;
		}
		else
		{
			int increment = reward - dailymission.base;
			dailymission.current += increment;
		}
	}

	CheckMission(dailymission);

	return 0;
}

int LogicDailyMissionManager::VerifyKill(DataDailyMission & dailymission)
{
	unsigned now = Time::GetGlobalTime();
	unsigned uid = dailymission.uid;

	bool isReset = LogicCommonUtil::IsCrossTime(dailymission.gettime, now, KILL_RANK_REWARD);  //是否重置

	if (isReset)
	{
		dailymission.current += GET_RMI(uid).reward;   //已清过杀敌量
	}
	else
	{
		unsigned kill = GET_RMI(uid).kill;

		//二次校验是否重置
		//判断base大还是当前值大
		if (kill < dailymission.base)  //经历了杀敌的重置
		{
			dailymission.current += kill;
		}
		else
		{
			int increment = kill - dailymission.base;
			dailymission.current += increment;
		}
	}

	CheckMission(dailymission);

	return 0;
}

int LogicDailyMissionManager::VerifyEquipShopReresh(DataDailyMission & dailymission)
{
	//调用一次，次数+1
	dailymission.current += 1;

	CheckMission(dailymission);
}

int LogicDailyMissionManager::VerifyParade(DataDailyMission & dailymission)
{
	//调用一次，次数+1
	dailymission.current += 1;

	CheckMission(dailymission);
}

int LogicDailyMissionManager::VerifyOfficial(DataDailyMission & dailymission)
{
	//调用一次，次数+1
	dailymission.current += 1;

	CheckMission(dailymission);
}

int LogicDailyMissionManager::CheckMission(DataDailyMission & dailymission)
{
	//根据任务id，获取任务配置
	const DailyMissionConfig::DailyMission & missioncfg = DailyMissionConfigWrap().GetDailyMissionCfg(dailymission.missid);

	if (dailymission.current >= missioncfg.count())
	{
		dailymission.status = 1;
	}

	return 0;
}

int LogicDailyMissionManager::FullMessage(unsigned uid, ProtoDailyMission::DailyMissionAllCPP *msg)
{
	vector<unsigned> mission_indexs;

	DataDailyMissionManager::Instance()->GetDailyMissions(uid, mission_indexs);

	for(int i = 0; i < mission_indexs.size(); ++i)
	{
		DataDailyMission& dailymission = DataDailyMissionManager::Instance()->GetDailyMission(mission_indexs[i]);
		dailymission.SetMessage(msg->add_missions());
	}

	return 0;
}
