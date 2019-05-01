/*
 * LogicMineMgr.cpp
 *
 *  Created on: 2016-11-15
 *      Author: dawx62fac
 */


#include "LogicMineMgr.h"


void LogicMineMgr::CheckUserParams(const DBCUserBaseWrap& user) const
{
	if (user.Obj().level < MINE_OPEN_LEVEL)
	{
		throw std::runtime_error("user_level_not_enough");
	}
}

void LogicMineMgr::OnDay()
{
	for (int kingdom = 1; kingdom <= 3; kingdom++)
	{
		MineKingdom& mineObj = DataPtr()->GetMine(kingdom);
		mineObj.MineKingdomHole().Reset();
	}
}

void LogicMineMgr::FullMessage(unsigned uid, const MineHole& mineHole, ProtoMine::MineItem* obj)
{
	obj->set_uid(mineHole.Uid());
	obj->set_level(mineHole.Level());
	obj->set_donate_cnt(mineHole.DonateCnt());
	obj->set_is_donate(mineHole.IsDonated(uid));
	obj->set_name(mineHole.Name());
}

void LogicMineMgr::FullMessage(unsigned uid, const MineKingdom& mineObj, ::google::protobuf::RepeatedPtrField< ::ProtoMine::MineItem >* obj)
{
	for (int i = 0; i < mineObj.MineNoramlHoleSize(); i++)
	{
		FullMessage(uid, mineObj.MineNoramlHoleIndex(i), obj->Add());
	}
}

void LogicMineMgr::FullMessage(const DBCUserBaseWrap& user, User::MineItem* obj)
{
	obj->set_mine_reward_ts(user.Obj().mine_reward_ts);

	int kingdom = user.Obj().kingdom;
	MineKingdom& mineObj = DataPtr()->GetMine(kingdom);

	obj->set_mine_kingdom_status(mineObj.MineKingdomHole().IsDonateFull());
}

int LogicMineMgr::Process(unsigned uid, ProtoMine::MineInfoReq* req, ProtoMine::MineInfoResp* resp)
{
	DBCUserBaseWrap user(uid);
	CheckUserParams(user);

	int kingdom = user.Obj().kingdom;
	MineKingdom& mineObj = DataPtr()->GetMine(kingdom);

	resp->set_mine_exp(user.Obj().mine_exp);
	resp->set_mine_level(MineCfgWrap().Exp2Level(user.Obj().mine_exp));
	FullMessage(uid, mineObj.MineKingdomHole(), resp->mutable_kingdom_mine());
	FullMessage(uid, mineObj, resp->mutable_normal_mine());
	resp->set_mine_normal_ts(user.Obj().mine_normal_ts);
	resp->set_mine_reward_ts(user.Obj().mine_reward_ts);

	return 0;
}

int LogicMineMgr::Process(unsigned uid, ProtoMine::MineNormalOpenReq* req, ProtoMine::MineOpenResp* resp)
{
	DBCUserBaseWrap user(uid);
	CheckUserParams(user);

	int kingdom = user.Obj().kingdom;
	MineKingdom& mineObj = DataPtr()->GetMine(kingdom);

	MineHole& hole = mineObj.MineNoramlHoleIndex(req->index() - 1);
	if (hole.IsOpen())
	{
		throw std::runtime_error("the_hole_is_open");
	}

	//
	if (Time::IsToday(user.Obj().mine_normal_ts))
	{
		throw std::runtime_error("already_open_mine_today");
	}

	if (mineObj.IsMineMaster(uid))
	{
		throw std::runtime_error("already_have_mine");
	}

	//
	MineCfgWrap cfg;
	int cost = cfg.GetNormalOpenCost(user.Obj().mine_exp);
	if ((int)user.Obj().coin < cost)
	{
		throw std::runtime_error("coin_not_enough");
	}
	//
	std::string reason = "mine_open_normal_hole";
	user.CostUserResource(cost, 0, 0, 0, reason);

	hole.Open(uid, user.Obj().name, user.Obj().mine_exp);
	user.OpenNormalHole(cfg.GetOpenExp());

	mineObj.AddOpenNoramlMineRecord(uid, user.Obj().name, hole);

	//
	FullMessage(uid, hole, resp->mutable_mine());
	user.FullMessage(resp->mutable_assets());
	resp->set_mine_exp(user.Obj().mine_exp);
	resp->set_mine_level(cfg.Exp2Level(user.Obj().mine_exp));
	resp->set_mine_normal_ts(user.Obj().mine_normal_ts);

	//todo 开矿的外部接口
	OpenMineExternalInterface(uid);

	return 0;
}

int LogicMineMgr::Process(unsigned uid, ProtoMine::MineKingdomOpenReq* rep, ProtoMine::MineOpenResp* resp)
{
	DBCUserBaseWrap user(uid);
	CheckUserParams(user);

	int kingdom = user.Obj().kingdom;
	MineKingdom& mineObj = DataPtr()->GetMine(kingdom);

	MineHole& hole = mineObj.MineKingdomHole();
	if (hole.IsOpen())
	{
		throw std::runtime_error("the_hole_is_open");
	}
	//
//	if (Time::IsToday(user.Obj().mine_kingdom_ts))
//	{
//		throw std::runtime_error("already_open_mine_today");
//	}

	MineCfgWrap cfg;
	int cost = cfg.GetKingdomOpenCost();
	std::string reason = "mine_open_kingdom_hole";
	if ((int)user.Obj().cash < cost)
	{
		throw std::runtime_error("cash_not_enough");
	}

	user.CostCash(cost, reason);

	hole.Open(uid, user.Obj().name);
	user.OpenKingdomHole(cfg.GetOpenExp());

	mineObj.AddOpenKingdomMineRecord(uid, user.Obj().name);

	FullMessage(uid, hole, resp->mutable_mine());
	user.FullMessage(resp->mutable_assets());
	resp->set_mine_exp(user.Obj().mine_exp);
	resp->set_mine_level(cfg.Exp2Level(user.Obj().mine_exp));

	//todo 开矿的外部接口
	OpenMineExternalInterface(uid);

	return 0;
}

int LogicMineMgr::OpenMineExternalInterface(unsigned uid)
{
	//接入开矿成就
    LogicAchievementManager::AchievementParam achievementparam;
	achievementparam.type = achievement_type_openmine;

	LogicAchievementManager::Instance()->VerifyAchievementComplete(uid, achievementparam);

	return 0;
}

void LogicMineMgr::OnMineNormalHoleFull(MineKingdom& mineObj, const MineHole& hole)
{
	int harvest = MineCfgWrap().HarvestNormalMine(hole.Level());
	try
	{
		mineObj.AddNormalHarvestRecord(hole, harvest);

		DBCUserBaseWrap mineMaster(hole.Uid());
		mineMaster.AddCash(harvest, "mine_donate_full_harvest");
		//
		ProtoMine::SyncUserBaseInfo* msg = new  ProtoMine::SyncUserBaseInfo;
		msg->mutable_info()->mutable_cash()->set_total_value(mineMaster.Obj().cash);
		msg->mutable_info()->mutable_cash()->set_value(harvest);
		msg->set_level(hole.Level());
		LogicManager::Instance()->sendMsg(hole.Uid(), msg);

		//给矿主发送通知
		SendNotify(hole.Uid(), harvest);
	}
	catch(const std::exception& e)
	{
		error_log("%u, %s", hole.Uid(), e.what());
		//
	}
}

int LogicMineMgr::SendNotify(unsigned uid, unsigned cash)
{
	Json::Value notifyval;
	notifyval["cash"] = cash;

	Json::FastWriter writer;
	string content  = writer.write(notifyval);

	NotifyItem notifyitem;

	notifyitem.uid = uid;
	notifyitem.id = e_Notify_Mine;
	notifyitem.ts = Time::GetGlobalTime();
	snprintf(notifyitem.content, NOTIFY_CONTENT_LEN, "%s", content.c_str());

	LogicNotifyManager::Instance()->AddNotify(notifyitem);

	return 0;
}

int LogicMineMgr::Process(unsigned uid, ProtoMine::DonateNormalReq* req, ProtoMine::DonateResp* resp)
{
	//
	DBCUserBaseWrap user(uid);
	CheckUserParams(user);

	int kingdom = user.Obj().kingdom;
	MineKingdom& mineObj = DataPtr()->GetMine(kingdom);
	MineHole& hole = mineObj.MineNoramlHoleIndex(req->index() - 1);
//	if (! hole.IsOpen())
//	{
//		throw std::runtime_error("the_mine_hole_not_open");
//	}

	MineCfgWrap cfg;
	int cost = cfg.GetNormalDonateCost();
	if ((int)user.Obj().coin < cost)
	{
		throw std::runtime_error("cash_not_enough");
	}

	hole.Donate(uid);
	std::string reason = "mine_donate_normal_hole";
	user.CostUserResource(cost, 0, 0, 0, reason);

	user.DonateHole(cfg.GetDonateExp());
	mineObj.AddNormalDonateRecord(uid, user.Obj().name, hole);

	if (hole.IsDonateFull())
	{
		OnMineNormalHoleFull(mineObj, hole);

		hole.Reset();
	}

	FullMessage(uid, hole, resp->mutable_mine());
	user.FullMessage(resp->mutable_assets());
	resp->set_mine_exp(user.Obj().mine_exp);
	resp->set_mine_level(cfg.Exp2Level(user.Obj().mine_exp));

	//矿藏援建外部接口
	DonateExternalInterface(uid);

	return 0;
}

void LogicMineMgr::OnMineKingdomHoleFull(int kingdom, MineKingdom& mineObj, const MineHole& hole)
{
	try
	{
		vector<unsigned> uids;
		UMI->GetOnlineUsers(uids);

		ProtoPush::MineKingdomRewardStatus* pStatusMsg = new ProtoPush::MineKingdomRewardStatus;
		pStatusMsg->set_kingdom(kingdom);
		LogicManager::Instance()->broadcastMsg(pStatusMsg);

	}
	catch(const std::exception& e)
	{
		error_log("%u, %s", hole.Uid(), e.what());
	}
}

int LogicMineMgr::Process(unsigned uid, ProtoMine::DonateKingdomReq* req, ProtoMine::DonateResp* resp)
{
	DBCUserBaseWrap user(uid);
	CheckUserParams(user);

	int kingdom = user.Obj().kingdom;
	MineKingdom& mineObj = DataPtr()->GetMine(kingdom);
	MineHole& hole = mineObj.MineKingdomHole();
	//
	if (hole.IsDonateFull())
	{
		throw std::runtime_error("donate_is_full");
	}

	MineCfgWrap cfg;
	int cost = cfg.GetKingdomDonateCost();
	if ((int)user.Obj().coin < cost)
	{
		throw std::runtime_error("cash_not_enough");
	}

	hole.Donate(uid);
	std::string reason = "mine_donate_kingdom_hole";
	user.CostUserResource(cost, 0, 0, 0, reason);

	user.DonateHole(cfg.GetDonateExp());

	mineObj.AddKingdomDonateRecord(uid, user.Obj().name);

	if (hole.IsDonateFull())
	{
		OnMineKingdomHoleFull(kingdom, mineObj, hole);
	}

	//
	FullMessage(uid, hole, resp->mutable_mine());
	user.FullMessage(resp->mutable_assets());
	resp->set_mine_exp(user.Obj().mine_exp);
	resp->set_mine_level(cfg.Exp2Level(user.Obj().mine_exp));

	//矿藏援建外部接口
	DonateExternalInterface(uid);

	return 0;
}

int LogicMineMgr::Process(unsigned uid, ProtoMine::MineKingdomRewardReq* req, ProtoMine::MineKingdomRewardResp* resp)
{
	DBCUserBaseWrap user(uid);
	CheckUserParams(user);

	int kingdom = user.Obj().kingdom;
	MineKingdom& mineObj = DataPtr()->GetMine(kingdom);
	MineHole& hole = mineObj.MineKingdomHole();

	if (uid == hole.Uid())
	{
		throw std::runtime_error("you_are_mine_master");
	}

	if (! hole.IsDonateFull())
	{
		throw std::runtime_error("donate_not_full");
	}

	if (Time::IsToday(user.Obj().mine_reward_ts))
	{
		throw std::runtime_error("already_get_kingdom_reward");
	}

	int reward = MineCfgWrap().GetKingdomReward();
	user.AddCash(reward, "mine_kingdom_reward_op");

	user.GetKingdomMineReward();

	mineObj.AddKingdomRewardRecord(uid, user.Obj().name, reward);

	resp->set_op_ts(user.Obj().mine_reward_ts);
	user.FullMessage(resp->mutable_assets());

	return 0;
}

int LogicMineMgr::Process(unsigned uid, ProtoMine::MineKingdomMinerRewardReq* req,ProtoMine::MineKingdomMinerRewardResp* resp)
{
	DBCUserBaseWrap user(uid);
	CheckUserParams(user);

	int kingdom = user.Obj().kingdom;
	MineKingdom& mineObj = DataPtr()->GetMine(kingdom);
	MineHole& hole = mineObj.MineKingdomHole();

	if (uid != hole.Uid())
	{
		throw std::runtime_error("you_not_mine_master");
	}

	if (! hole.IsDonateFull())
	{
		throw std::runtime_error("donate_not_full");
	}

	if (Time::IsToday(user.Obj().mine_reward_ts))
	{
		throw std::runtime_error("already_get_kingdom_reward");
	}

	int exp = MineCfgWrap().HarvestKingdomMine(user.Obj().level);
	mineObj.AddKingdomHarvestRecord(hole, exp);

	user.GetKingdomMineReward();

	user.AddExp(exp);
	resp->mutable_exp()->set_total_value(user.Obj().exp);
	resp->mutable_exp()->set_value(exp);
	resp->set_op_ts(user.Obj().mine_reward_ts);

	return 0;
}

int LogicMineMgr::Process(unsigned uid, ProtoMine::MineRecordReq* req, ProtoMine::MineRecordResp* resp)
{
	DBCUserBaseWrap user(uid);
	CheckUserParams(user);

	DataPtr()->GetMine(user.Obj().kingdom).FullMessage(resp->mutable_records());

	return  0;
}

int LogicMineMgr::DonateExternalInterface(unsigned uid)
{
	//todo 接入矿藏援建每日任务
	LogicDailyMissionManager::DailyMissionParam dailymissionparam;
	dailymissionparam.type = daily_mission_type_minesupport;

	LogicDailyMissionManager::Instance()->VerifyDailyMissionComplete(uid, dailymissionparam);

	//todo 接入援建成就
    LogicAchievementManager::AchievementParam achievementparam;
	achievementparam.type = achievement_type_minesupport;

	LogicAchievementManager::Instance()->VerifyAchievementComplete(uid, achievementparam);

	return 0;
}
