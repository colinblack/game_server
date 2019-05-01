/*
 * LogicSmeltActivity.cpp
 *
 *  Created on: 2016-12-6
 *      Author: dawx62fac
 */

#include "LogicSmeltActivity.h"

DBCSmeltActivityWrap::DBCSmeltActivityWrap(unsigned uid)
	: container_(DataSmeltActivityMgr::Instance())
	, index_(_Index(uid))
	, data_(container_->m_data->data[index_])
{
	unsigned nVersion = LogicSmeltActivity::Instance()->GetVersion();
	if (data_.version != nVersion)
	{
		data_.Reset(nVersion);

		Save();
	}
}

unsigned DBCSmeltActivityWrap::_Index(unsigned uid) const
{
	if (! LogicSmeltActivity::Instance()->IsOn())
	{
		throw std::runtime_error("smelt_activity_not_open");
	}

	return container_->GetIndex(uid);
}

void DBCSmeltActivityWrap::AccumulateSmeltCnt(int cnt)
{
	data_.total += cnt;

	Save();

	const ActivityConfig::SmeltActivity&  cfg = SmeltActivityCfgWrap().Cfg();
	for (int i = cfg.smelt_activity_size() - 1; i >= 0; i--)
	{
		int total_cfg_cnt = cfg.smelt_activity(i).smelt_total_cnt();
		int limit_cfg_cnt = total_cfg_cnt * cfg.smelt_activity(i).limit_reward_cnt();
		if ((data_.total >= total_cfg_cnt)
			&& (data_.total % total_cfg_cnt == 0)
			&& (data_.total <= limit_cfg_cnt))
		{
			ProtoPush::SmeltActivityHint* msg = new ProtoPush::SmeltActivityHint();
			msg->set_type(cfg.smelt_activity(i).id());

			LogicManager::Instance()->sendMsg(data_.uid, msg);
			return ;
		}
	}
}

unsigned DBCSmeltActivityWrap::GetTotalRewardCnt(int id) const
{
	const ActivityConfig::SmeltActivityItem& itemCfg = SmeltActivityCfgWrap().GetItem(id);
	return std::min(data_.total / itemCfg.smelt_total_cnt(), itemCfg.limit_reward_cnt());
}

unsigned DBCSmeltActivityWrap::GetAvailableRewardCnt(int id) const
{
	return GetTotalRewardCnt(id) - data_.GetRewardCnt(id);
}

//已经领取次数
unsigned DBCSmeltActivityWrap::GetAlreadyRewardCnt(int id) const
{
	return data_.GetRewardCnt(id);
}

void DBCSmeltActivityWrap::AccumulateRewardCnt(int id, int cnt)
{
	uint16_t* reward_cnt = data_.RewardCnt(id);
	*reward_cnt += cnt;

	Save();
}

void DBCSmeltActivityWrap::FullMessage(::google::protobuf::RepeatedPtrField< ::ProtoActivity::SmeltItem >* obj) const
{
	for (int i = 1; i <= 3; i++)
	{
		FullMessage(i, obj->Add());
	}
}

void DBCSmeltActivityWrap::FullMessage(unsigned id, ::ProtoActivity::SmeltItem* obj) const
{
	obj->set_id(id);
	obj->set_reward_cnt(GetAvailableRewardCnt(id));
	obj->set_yet_cnt(GetAlreadyRewardCnt(id));
}

/////////////////////////////////////////////////////////////////////////////
void LogicSmeltActivity::Online(unsigned uid)
{
	if (IsOn() && ! DataSmeltActivityMgr::Instance()->IsExist(uid))
	{
		DataSmeltActivityMgr::Instance()->LoadBuffer(uid);
	}
}

void LogicSmeltActivity::AccumulateSmeltCnt(unsigned uid, int cnt)
{
	if (IsOn())
	{
		DBCSmeltActivityWrap(uid).AccumulateSmeltCnt(cnt);
	}
}

int LogicSmeltActivity::Process(unsigned uid, ProtoActivity::SmeltInfoReq* req, ProtoActivity::SmeltInfoResp* resp)
{
	DBCSmeltActivityWrap smelt(uid);

	resp->set_total_smelt_cnt(smelt.Obj().total);
	smelt.FullMessage(resp->mutable_items());

	return 0;
}

int LogicSmeltActivity::Process(unsigned uid, ProtoActivity::SmeltRewardReq* req, ProtoActivity::SmeltRewardResp* resp)
{
	DBCSmeltActivityWrap smelt(uid);
	unsigned id = req->id();

	unsigned  newCnt = smelt.GetAvailableRewardCnt(id);
	if (newCnt == 0)
	{
		throw std::runtime_error("not_reward_cnt");
	}

	std::string reason = "smelt_activity_reward_op";
	const ActivityConfig::SmeltActivityItem& itemCfg = SmeltActivityCfgWrap().GetItem(id);
	LogicEquipmentManager::Instance()->AddEquipment(uid, itemCfg.reward(), 1, reason, resp->mutable_equip());

	smelt.AccumulateRewardCnt(id, 1);

	smelt.FullMessage(id, resp->mutable_item());

	return 0;
}
