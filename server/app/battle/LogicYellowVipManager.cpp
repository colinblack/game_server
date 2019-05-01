#include "LogicYellowVipManager.h"
#include "DataYellowVip.h"

int LogicYellowVipManager::LoginCheck(unsigned uid)
{
	//判断英雄数据是否加载进内存
	bool isExists = DataYellowVipManager::Instance()->IsDataYellowVipExists(uid);

	if (isExists)
	{
		return 0;
	}

	//没有数据。重新加载一遍
	int ret = DataYellowVipManager::Instance()->LoadBuff(uid);

	if (R_ERR_NO_DATA == ret)   //表中没有数据，重新初始化
	{
		ret = NewUserInit(uid);
	}

	return ret;
}

int LogicYellowVipManager::NewUserInit(unsigned uid)
{
	//不管是否黄钻，都插入数据
	DataYellowVip datayellow;
	datayellow.uid = uid;

	int ret = DataYellowVipManager::Instance()->AddBuff(datayellow);

	if (ret)
	{
		error_log("[NewUserInit] add yellow vip data error. uid=%u", uid);
		return ret;
	}

	return 0;
}

int LogicYellowVipManager::Process(unsigned uid, ProtoYellowVip::GetNewerGiftReq *reqmsg, ProtoYellowVip::GetNewerGiftResp * respmsg)
{
	GetNewerReward(uid, respmsg);

	return 0;
}

int LogicYellowVipManager::GetNewerReward(unsigned uid, ProtoYellowVip::GetNewerGiftResp *respmsg)
{
	//黄钻判断
	CheckIsYellowVip(uid);

	try
	{
		DataYellowVip & datayellow = DataYellowVipManager::Instance()->Get(uid);

		if (datayellow.newerstatus)
		{
			error_log("[GetNewerReward] gift already get. uid=%u", uid);
			throw std::runtime_error("already_get_gift");
		}

		//从配置文件中获取奖励
		const VipGiftConfig::FinalReward & reward = VipGiftConfigWrap().GetNewerRewardCfg();
		ProvideReward(reward, uid, "YellowVIP_Newer_Gift", respmsg->mutable_reward());

		datayellow.newerstatus = 1;
		DataYellowVipManager::Instance()->UpdateDataYellowVip(datayellow);
		datayellow.SetMessage(respmsg->mutable_yellowvip());
	}
	catch (std::runtime_error & e)
	{
		error_log("[GetNewerReward] exception:%s", e.what());
		throw e;
	}

	return 0;
}

int LogicYellowVipManager::Process(unsigned uid, ProtoYellowVip::GetDailyGiftReq *reqmsg, ProtoYellowVip::GetDailyGiftResp * respmsg)
{
	GetDailyReward(uid, respmsg);

	return 0;
}

//领取黄钻每日礼包
int LogicYellowVipManager::GetDailyReward(unsigned uid, ProtoYellowVip::GetDailyGiftResp * respmsg)
{
	//黄钻判断
	CheckIsYellowVip(uid);

	try
	{
		DataYellowVip & datayellow = DataYellowVipManager::Instance()->Get(uid);

		CheckCrossDay(datayellow);

		//判断黄钻每日礼包是否已领取
		if (datayellow.dailystatus)
		{
			error_log("[GetDailyReward] gift already get. uid=%u", uid);
			throw std::runtime_error("already_get_gift");
		}

		//从配置文件中获取奖励
		Common::Login info;
		UserManager::Instance()->GetUserInfo(uid, info);
		int yellowvip_level = 0;
		switch(info.platform())
		{
		case PT_TEST:
		case PT_PENGYOU:
		case PT_QZONE:
			yellowvip_level = info.yellow_vip_level();
			break;
		case PT_qqgame:
			yellowvip_level = info.blue_vip_level();
			break;
		default:
			break;
		}
		const VipGiftConfig::FinalReward & reward = VipGiftConfigWrap().GetDailyRewardCfg(yellowvip_level);
		ProvideReward(reward, uid, "YellowVIP_Daily_Gift", respmsg->mutable_reward());

		datayellow.dailystatus = 1;
		DataYellowVipManager::Instance()->UpdateDataYellowVip(datayellow);
		datayellow.SetMessage(respmsg->mutable_yellowvip());
	}
	catch (std::runtime_error & e)
	{
		error_log("[GetDailyReward] exception:%s", e.what());
		throw e;
	}

	return 0;
}


int LogicYellowVipManager::Process(unsigned uid, ProtoYellowVip::GetYearDailyGiftReq *reqmsg, ProtoYellowVip::GetYearDailyGiftResp * respmsg)
{
	GetYearDailyReward(uid, respmsg);
	return 0;
}


int LogicYellowVipManager::GetYearDailyReward(unsigned uid, ProtoYellowVip::GetYearDailyGiftResp * respmsg)
{
	//年费黄钻判断
	CheckIsYellowYearVip(uid);

	DataYellowVip & datayellow = DataYellowVipManager::Instance()->Get(uid);

	CheckCrossDay(datayellow);

	//判断年费黄钻每日礼包是否已领取
	if (datayellow.year_daily_status)
	{
		error_log("[GetYearDailyReward] year gift already get. uid=%u", uid);
		throw std::runtime_error("already_get_year_gift");
	}

	try
	{
		const VipGiftConfig::FinalReward & reward = VipGiftConfigWrap().GetYearDailyRewardCfg();
		ProvideReward(reward, uid, "YellowVIP_Year_Daily_Gift", respmsg->mutable_reward());

		datayellow.year_daily_status = 1;
		DataYellowVipManager::Instance()->UpdateDataYellowVip(datayellow);
		datayellow.SetMessage(respmsg->mutable_yellowvip());
	}
	catch (std::runtime_error & e)
	{
		error_log("[GetYearDailyReward] exception:%s", e.what());
		throw e;
	}

	return 0;
}


int LogicYellowVipManager::Process(unsigned uid, ProtoYellowVip::GetLevelGiftReq *reqmsg, ProtoYellowVip::GetLevelGiftResp * respmsg)
{
	unsigned index = reqmsg->index();
	GetUpgradeReward(uid, index, respmsg);

	return 0;
}


int LogicYellowVipManager::GetUpgradeReward(unsigned uid, unsigned index, ProtoYellowVip::GetLevelGiftResp * respmsg)
{
	//黄钻判断
	CheckIsYellowVip(uid);

	//对发来的任务领取进行条件校验
	//判断参数是否有效
	VipGiftConfigWrap vipgiftconfig;
	unsigned max_condition_size = vipgiftconfig.VipGift().yellowvip().upgrade_size();

	if (index < 1 || index > max_condition_size)
	{
		error_log("[GetUpgradeReward] param error.uid=%u,index=%u.max-size=%u", uid, index, max_condition_size);
		throw std::runtime_error("invalid_param");
	}

	unsigned pos = index - 1; //下标

	const VipGiftConfig::UpgradeGift & upgadeconfig = vipgiftconfig.GetUpgradeCfg(pos);

	uint8_t minlevel = upgadeconfig.userlevel();
	DBCUserBaseWrap userbasewrap(uid);
	uint8_t userlevel = userbasewrap.Obj().level;

	//等级校验
	if (userlevel < minlevel)
	{
		error_log("[GetUpgradeReward] user level not match condion. ulevel=%hhu, condtion_level=%hhu", userlevel, minlevel);
		throw std::runtime_error("user_level_not_match");
	}

	DataYellowVip & datayellow = DataYellowVipManager::Instance()->Get(uid);
	//是否领取校验
	bool iszero = LogicCommonUtil::CheckPosIsZero(datayellow.levelstatus, pos);

	if (!iszero)   //非0，表示已领取
	{
		error_log("[GetUpgradeReward] level gift already get. uid=%u, index=%u", uid, index);
		throw std::runtime_error("already_get_level_gift");
	}

	try
	{
		char szReason[50] = {0};
		sprintf(szReason, "YellowVIP_Gift_Level_%u", index);
		ProvideReward(upgadeconfig.reward(), uid, szReason, respmsg->mutable_reward());

		LogicCommonUtil::SetBitCurrent(datayellow.levelstatus, pos);  //设置该位为1，表示已领取奖励
		DataYellowVipManager::Instance()->UpdateDataYellowVip(datayellow);
		datayellow.SetMessage(respmsg->mutable_yellowvip());
	}
	catch (std::runtime_error & e)
	{
		error_log("[GetYearDailyReward] exception:%s", e.what());
		throw e;
	}

	return 0;
}

int LogicYellowVipManager::Process(unsigned uid, ProtoYellowVip::QQZoneGetDailyGiftReq *reqmsg, ProtoYellowVip::QQZoneGetDailyGiftResp * respmsg)
{
	GetQQZoneDailyReward(uid, respmsg);

	return 0;
}

int LogicYellowVipManager::GetQQZoneDailyReward(unsigned uid, ProtoYellowVip::QQZoneGetDailyGiftResp * respmsg)
{
	//判断是否空间平台
	CheckIsFromQQZone(uid);

	DataYellowVip & datayellow = DataYellowVipManager::Instance()->Get(uid);

	CheckCrossDay(datayellow);

	//判断年费黄钻每日礼包是否已领取
	if (datayellow.qqzone_dailystatus)
	{
		error_log("[GetQQZoneDailyReward] qqzone daily already get. uid=%u", uid);
		throw std::runtime_error("already_get_dailygift");
	}

	try
	{
		const VipGiftConfig::FinalReward & reward = VipGiftConfigWrap().GetQQZoneDailyRewardCfg();
		ProvideReward(reward, uid, "QQZone_Daily_Gift", respmsg->mutable_reward());

		datayellow.qqzone_dailystatus = 1;
		DataYellowVipManager::Instance()->UpdateDataYellowVip(datayellow);
		datayellow.SetMessage(respmsg->mutable_yellowvip());
	}
	catch (std::runtime_error & e)
	{
		error_log("[GetQQZoneDailyReward] exception:%s", e.what());
		throw e;
	}

	return 0;
}


int LogicYellowVipManager::Process(unsigned uid, ProtoYellowVip::QQZoneGetLevelGiftReq *reqmsg, ProtoYellowVip::QQZoneGetLevelGiftResp * respmsg)
{
	unsigned index = reqmsg->index();

	GetQQZoneUpgradeReward(uid, index, respmsg);
}

int LogicYellowVipManager::GetQQZoneUpgradeReward(unsigned uid, unsigned index, ProtoYellowVip::QQZoneGetLevelGiftResp * respmsg)
{
	//判断是否空间平台
	CheckIsFromQQZone(uid);

	//对发来的任务领取进行条件校验
	//判断参数是否有效
	VipGiftConfigWrap vipgiftconfig;
	unsigned max_condition_size = vipgiftconfig.VipGift().qqzone().upgrade_size();

	if (index < 1 || index > max_condition_size)
	{
		error_log("[GetQQZoneUpgradeReward] param error.uid=%u,index=%u.max-size=%u", uid, index, max_condition_size);
		throw std::runtime_error("invalid_param");
	}

	unsigned pos = index - 1; //下标

	const VipGiftConfig::UpgradeGift & upgadeconfig = vipgiftconfig.GetQQZoneUpgradeCfg(pos);

	uint8_t minlevel = upgadeconfig.userlevel();
	DBCUserBaseWrap userbasewrap(uid);
	uint8_t userlevel = userbasewrap.Obj().level;

	//等级校验
	if (userlevel < minlevel)
	{
		error_log("[GetQQZoneUpgradeReward] user level not match condion. ulevel=%hhu, condtion_level=%hhu", userlevel, minlevel);
		throw std::runtime_error("user_level_not_match");
	}

	DataYellowVip & datayellow = DataYellowVipManager::Instance()->Get(uid);
	//是否领取校验
	bool iszero = LogicCommonUtil::CheckPosIsZero(datayellow.qqzone_levelstatus, pos);

	if (!iszero)   //非0，表示已领取
	{
		error_log("[GetQQZoneUpgradeReward] level gift already get. uid=%u, index=%u", uid, index);
		throw std::runtime_error("already_get_level_gift");
	}

	try
	{
		char szReason[50] = {0};
		sprintf(szReason, "QQZone_Gift_Level_%u", index);
		ProvideReward(upgadeconfig.reward(), uid, szReason, respmsg->mutable_reward());

		LogicCommonUtil::SetBitCurrent(datayellow.qqzone_levelstatus, pos);  //设置该位为1，表示已领取奖励
		DataYellowVipManager::Instance()->UpdateDataYellowVip(datayellow);
		datayellow.SetMessage(respmsg->mutable_yellowvip());
	}
	catch (std::runtime_error & e)
	{
		error_log("[GetQQZoneUpgradeReward] exception:%s", e.what());
		throw e;
	}

	return 0;
}

int LogicYellowVipManager::FullMessage(unsigned uid, ProtoYellowVip::YellowVipCPP * msg)
{
	bool isExists = DataYellowVipManager::Instance()->IsDataYellowVipExists(uid);

	if (!isExists)  //不存在
	{
		return 0;
	}

	//获取yellow vip的数据
	DataYellowVip & datayellow = DataYellowVipManager::Instance()->Get(uid);
	datayellow.SetMessage(msg);

	return 0;
}

int LogicYellowVipManager::CheckCrossDay(DataYellowVip & datayellow)
{
	//判断是否已跨天
	unsigned now = Time::GetGlobalTime();
	bool isDiff = CTime::IsDiffDay(now, datayellow.daily_reward_time);  //以每日领取时间为准

	if (isDiff)   //跨天，重置每日领取状态
	{
		datayellow.dailystatus = 0;   //黄钻每日
		datayellow.year_daily_status = 0;   //年费黄钻每日
		datayellow.qqzone_dailystatus = 0;   //qq空间每日

		datayellow.daily_reward_time = now;
		datayellow.year_reward_time = now;
		datayellow.qqzone_daily_time = now;

		DataYellowVipManager::Instance()->UpdateDataYellowVip(datayellow);
	}

	return 0;
}

int LogicYellowVipManager::ProvideReward(const VipGiftConfig::FinalReward & reward, unsigned uid,
		string reason, ProtoYellowVip::FinalRewardCPP * msg)
{
	//先处理道具奖励
	for(int i = 0; i < reward.equips_size(); ++i)
	{
		unsigned eqid = reward.equips(i).eqid();
		unsigned count = reward.equips(i).count();

		LogicEquipmentManager::Instance()->AddEquipment(uid, eqid, count, reason, msg->mutable_equips());
	}

	//处理资源类
	int coin = 0, food = 0, wood = 0, iron = 0;
	DBCUserBaseWrap userbasewrap(uid);

	if (reward.has_coin())
	{
		coin = reward.coin();
		map<unsigned, unsigned> resource;
		resource.insert(make_pair(resource_type_coin, coin));

		userbasewrap.AddResource(resource, reason);
		msg->set_coin(userbasewrap.Obj().coin);
	}

	if (reward.has_wood())
	{
		wood = reward.wood();
		map<unsigned, unsigned> resource;
		resource.insert(make_pair(resource_type_wood, wood));

		userbasewrap.AddResource(resource, reason);
		msg->set_wood(userbasewrap.Obj().wood);
	}

	if (reward.has_food())
	{
		food = reward.food();
		map<unsigned, unsigned> resource;
		resource.insert(make_pair(resource_type_food, food));

		userbasewrap.AddResource(resource, reason);
		msg->set_food(userbasewrap.Obj().food);
	}

	if (reward.has_iron())
	{
		iron = reward.iron();
		map<unsigned, unsigned> resource;
		resource.insert(make_pair(resource_type_iron, iron));

		userbasewrap.AddResource(resource, reason);
		msg->set_iron(userbasewrap.Obj().iron);
	}

	//募兵次数
	if(reward.has_order())
	{
		int count = reward.order();
		userbasewrap.AddRecruitProp(count, reason);
		msg->set_order(userbasewrap.Obj().order);
	}

	//锤子次数
	if (reward.has_hammer())
	{
		int count = reward.hammer();
		userbasewrap.AddGoldHammer(count, reason);
		msg->set_hammer(userbasewrap.Obj().harmmer);
	}

	//经验
	if (reward.has_exp())
	{
		int exp = reward.exp();
		userbasewrap.AddExp(exp);  //如果导致用户升级，会自动推送给前端，不需要额外的再发送经验和等级
	}

	userbasewrap.Save();

	return 0;
}

int LogicYellowVipManager::CheckIsYellowVip(unsigned uid)
{
	//判断是否黄钻会员
	Common::Login info;
	bool isHave = UserManager::Instance()->GetUserInfo(uid, info);

	if (!isHave)
	{
		error_log("[CheckIsYellowVip] get user info error. uid=%u", uid);
		throw std::runtime_error("get_user_info_error");
	}

	int is = 0;
	switch(info.platform())
	{
	case PT_TEST:
	case PT_PENGYOU:
	case PT_QZONE:
		is = info.is_yellow_vip();
		break;
	case PT_qqgame:
		is = info.is_blue_vip();
		break;
	default:
		break;
	}
	if (is < 1)
	{
		error_log("[CheckIsYellowVip] user not yellow vip. uid=%u", uid);
		throw std::runtime_error("not_yellow_vip");
	}

	return 0;
}

int LogicYellowVipManager::CheckIsYellowYearVip(unsigned uid)
{
	//判断是否是年费黄钻
	Common::Login info;
	bool isHave = UserManager::Instance()->GetUserInfo(uid, info);

	if (!isHave)
	{
		error_log("[CheckIsYellowYearVip] get user info error. uid=%u", uid);
		throw std::runtime_error("get_user_info_error");
	}

	int is = 0;
	switch(info.platform())
	{
	case PT_TEST:
	case PT_PENGYOU:
	case PT_QZONE:
		is = info.is_yellow_year_vip();
		break;
	case PT_qqgame:
		is = info.is_blue_year_vip();
		break;
	default:
		break;
	}
	if (is < 1)
	{
		error_log("[CheckIsYellowYearVip] user is not yellow year vip. uid=%u", uid);
		throw std::runtime_error("user_not_yellow_year_vip");
	}

	return 0;
}

int LogicYellowVipManager::CheckIsFromQQZone(unsigned uid)
{
	//判断是否是qq空间平台
	Common::Login info;
	bool isHave = UserManager::Instance()->GetUserInfo(uid, info);

	if (!isHave)
	{
		error_log("[CheckIsFromQQZone] get user info error. uid=%u", uid);
		throw std::runtime_error("get_user_info_error");
	}

	unsigned platform = info.platform();

	if(!Is_QQ_Platform(platform) && platform != PT_TEST)
	{
		error_log("[CheckIsFromQQZone] user platform is not qqzone. uid=%u,platform=%u", uid, platform);
		throw std::runtime_error("user_not_from_qqzone");
	}

	return 0;
}
