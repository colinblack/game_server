/*
 * LogicPassActivityMgr.cpp
 *
 *  Created on: 2016-11-23
 *      Author: dawx62fac
 */


#include "LogicPassActivityMgr.h"

LogicPassActivityMgr::LogicPassActivityMgr()
{

}

void LogicPassActivityMgr::AddRecord(const PassActivityRecord& record)
{
	if (record_.size() >= 50)
	{
		record_.pop_front();
	}

	record_.push_back(record);
}

bool LogicPassActivityMgr::IsValidPeroid(const DBCUserBaseWrap& user)
{
	return user.GetRegisterHours() < 48;
}

int LogicPassActivityMgr::Process(unsigned uid, ProtoActivity::PassActivityInfoReq* req, ProtoActivity::PassActivityInfoResp* resp)
{
	DBCUserBaseWrap user(uid);

	if (! IsValidPeroid(user))
	{
		throw std::runtime_error("out_valid_peroid");
	}

	const ActivityConfig::PassActivity& cfg = PassActivityCfgWrap().Cfg();
	for (int i = 0; i < cfg.pass_activity_size(); i++)
	{
		bool flag = user.IsSetPassActivityRewardFlag(i);
		::ProtoActivity::PassActivityItem* item = resp->add_items();
		item->set_id(cfg.pass_activity(i).id());
		item->set_is_get_reward(flag);
	}

	for (size_t i = 0; i < record_.size(); i++)
	{
		::ProtoActivity::PassActivityRecord*  record = resp->add_records();
		record->set_name(record_[i].Name());
		record->set_pass_id(record_[i].PassId());
		record->set_cash(record_[i].Cash());
	}

	return 0;
}

int LogicPassActivityMgr::Process(unsigned uid, ProtoActivity::PassActivityRewardReq* req, ProtoActivity::PassActivityRewardResp* resp)
{
	DBCUserBaseWrap user(uid);

	if (! IsValidPeroid(user))
	{
		throw std::runtime_error("out_valid_peroid");
	}

	const ActivityConfig::PassActivityItem& itemCfg = PassActivityCfgWrap().Item(req->id());
	if (itemCfg.pass_id() > user.Obj().npc_pass)
	{
		throw std::runtime_error("not_get_assign_pass");
	}

	int idx = PassActivityCfgWrap().Index(req->id());
	user.SetPassActivityRewardFlag(idx);

	//
	int cash = itemCfg.reward();
	user.AddCash(cash, "pass_activity_reward_op");

	AddRecord(PassActivityRecord(user.Obj().name, itemCfg.pass_id(), cash));

	resp->mutable_items()->set_id(itemCfg.id());
	resp->mutable_items()->set_is_get_reward(user.IsSetPassActivityRewardFlag(idx));

	resp->mutable_reward()->mutable_cash()->set_value(cash);
	resp->mutable_reward()->mutable_cash()->set_total_value(user.Obj().cash);

	return 0;
}
