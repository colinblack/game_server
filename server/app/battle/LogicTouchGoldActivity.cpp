/*
 * LogicTouchGoldActivity.cpp
 *
 *  Created on: 2016-12-9
 *      Author: dawx62fac
 */


#include "LogicTouchGoldActivity.h"

DBCTouchGoldWrap::DBCTouchGoldWrap(unsigned uid)
	: container_(DataTouchGoldMgr::Instance())
	, index_(_Index(uid))
	, data_(container_->m_data->data[index_])
{
	unsigned nVersion = LogicTouchGold::Instance()->GetVersion();
	if (data_.version != nVersion)
	{
		data_.ResetVersion(nVersion);

	}
	else if (! Time::IsToday(data_.ts_op))
	{
		data_.total_touchs = 0;
	}

	data_.ts_op = Time::GetGlobalTime();

	Save();
}

unsigned DBCTouchGoldWrap::_Index(unsigned uid)
{
	if (! LogicTouchGold::Instance()->IsOn())
	{
		throw std::runtime_error("touch_gold_activity_not_open");
	}

	return container_->GetIndex(uid);
}

void DBCTouchGoldWrap::CheckTombId(int id) const
{
	if (id <= 0 || id > data_.MaxId())
	{
		throw std::runtime_error("tomb_id_params_error");
	}
}

void DBCTouchGoldWrap::OpenTomb(int id)
{
	data_.UnlockTomb(id);

	Save();
}

bool DBCTouchGoldWrap::IsOpenNextTomb(int id) const
{
	int next_id = id + 1;
	next_id = next_id > data_.MaxId() ? data_.MaxId() : next_id;

	if (IsTombOpened(next_id)) return false;

	//
	const  ActivityConfig::TouchGoldItem& cfg = TouchGoldCfgWrap().GetItem(id);
	unsigned val = Math::GetRandomInt(100);
	if (val < cfg.open_next_prob())
	{
		return true;
	}
	//
	return false;
}

void DBCTouchGoldWrap::OpenNextTomb(int cur_id)
{
	//CheckTombId(cur_id);
	int next_id = cur_id + 1;
	next_id = next_id > data_.MaxId() ? data_.MaxId() : next_id;

	data_.UnlockTomb(next_id);

	Save();
}

bool DBCTouchGoldWrap::IsTombOpened(int id) const
{
	//CheckTombId(cur_id);
	return data_.IsUnlocked(id);
}

unsigned DBCTouchGoldWrap::TouchGold(int index)
{
	if (data_.total_touchs >= TOUCH_TOTAL_MAX_CNT)
	{
		throw std::runtime_error("reach_total_touch_cnt");
	}

	if (data_.surpluses <= 0)
	{
		throw std::runtime_error("have_not_touch_cnt");
	}

	unsigned out = TouchGoldCfgWrap().Output(data_.tomb_id);
	data_.TouchGold(index, out);

	if (IsOpenNextTomb(data_.tomb_id))
	{
		OpenNextTomb(data_.tomb_id);
	}

	data_.total_touchs ++;
	data_.surpluses --;

	Save();

	return out;
}

unsigned DBCTouchGoldWrap::TouchGold()
{
	if (data_.total_touchs + data_.MaxTouches() > TOUCH_TOTAL_MAX_CNT)
	{
		throw std::runtime_error("reach_total_touch_cnt");
	}

	if (data_.touch_bit > 0)
	{
		throw std::runtime_error("already_touch_gold");
	}

	TouchGoldCfgWrap cfg;
	std::vector<int> result;
	unsigned total_out = 0;
	LogicCommonUtil::GetRandoms(0, data_.MaxTouchPosition(), data_.MaxTouches(), result);
	for (size_t i = 0; i < result.size(); i++)
	{
		unsigned out = cfg.Output(data_.tomb_id);
		data_.TouchGold(result[i], out);
		total_out += out;

		if (IsOpenNextTomb(data_.tomb_id))
		{
			OpenNextTomb(data_.tomb_id);
		}
	}

	data_.total_touchs += data_.MaxTouches();
	data_.surpluses = 0;

	Save();

	return total_out;
}

void DBCTouchGoldWrap::SwitchTomb(int id)
{
	if (! data_.IsUnlocked(id))
	{
		throw std::runtime_error("the_tomb_not_unlock");
	}

	data_.ResetTomb(id);

	Save();
}

void DBCTouchGoldWrap::Reset()
{
	data_.ResetTomb(data_.tomb_id);

	Save();
}

void DBCTouchGoldWrap::FullMessage(const DataBase& base, ProtoActivity::TouchGoldInfo* obj)
{
	obj->Clear();

	for (int i = 1; i <= data_.MaxId(); i++)
	{
		::ProtoActivity::TouchGoldTombItem* tomb = obj->add_tombs();
		tomb->set_id(i);
		tomb->set_is_locked(data_.IsUnlocked(i));
	}
	obj->set_total_touch(data_.total_touchs);
	obj->set_total_limit(TOUCH_TOTAL_MAX_CNT);
	obj->set_surplus(data_.surpluses);
	obj->set_cur_tomb_id(data_.tomb_id);

	int touch_index = 0;
	for (int i = 0; i <= data_.MaxTouchPosition(); i++)
	{
		if (data_.IsTouched(i))
		{
			obj->add_out(data_.GetOutput(touch_index ++));
		}
		else
		{
			obj->add_out(0);
		}
	}

	obj->set_component(base.market);
}
//////////////////////////////////////////////////////////////////////////////////////
void LogicTouchGold::Online(unsigned uid)
{
	if (IsOn())
	{
		try
		{
			if (! DataTouchGoldMgr::Instance()->IsExist(uid))
			{
				DataTouchGoldMgr::Instance()->LoadBuffer(uid);
			}
		}
		catch(const std::exception& e)
		{
			error_log("%s", e.what());
		}
	}
}

int LogicTouchGold::Process(unsigned uid, ProtoActivity::TouchGoldInfoReq* req, ProtoActivity::TouchGoldInfo* resp)
{
	DBCUserBaseWrap user(uid);
	DBCTouchGoldWrap touch(uid);
	touch.FullMessage(user.Obj(), resp);

	return 0;
}

int LogicTouchGold::Process(unsigned uid, ProtoActivity::TouchGoldOnceReq* req, ProtoActivity::TouchGoldResp* resp)
{
	DBCUserBaseWrap user(uid);
	DBCTouchGoldWrap touch(uid);

	unsigned tombId = touch.Obj().tomb_id;
	TouchGoldCfgWrap touchCfg;

	unsigned cost = 0;
	if (touch.Obj().total_touchs >= TOUCH_FREE_CNT)
	{
		cost = touchCfg.GetItem(tombId).cost();
	}

	if (cost > 0)
	{
		user.CostCash(cost, "touch_gold_once_op");
	}

	unsigned out = touch.TouchGold(req->index());

	user.AddMarket(out, "touch_gold_once_op");

	touch.FullMessage(user.Obj(), resp->mutable_info());
	resp->set_cash(user.Obj().cash);

	return 0;
}

int LogicTouchGold::Process(unsigned uid, ProtoActivity::TouchGoldAllReq* req, ProtoActivity::TouchGoldResp* resp)
{
	DBCUserBaseWrap user(uid);
	DBCTouchGoldWrap touch(uid);

	unsigned tombId = touch.Obj().tomb_id;

	//免费可用次数
	unsigned free_cnt = touch.Obj().total_touchs >= TOUCH_FREE_CNT ?
			0 : TOUCH_FREE_CNT - touch.Obj().total_touchs;

	//
	unsigned max_cnt = touch.Obj().MaxTouches();
	unsigned cost_cnt = max_cnt > free_cnt ? max_cnt - free_cnt : 0;
	unsigned cost = TouchGoldCfgWrap().GetItem(tombId).cost() * cost_cnt;
	if (cost > 0)
	{
		user.CostCash(cost, "touch_gold_one_key_op");
	}

	unsigned out = touch.TouchGold();

	user.AddMarket(out, "touch_gold_one_key_op");

	touch.FullMessage(user.Obj(), resp->mutable_info());
	resp->set_cash(user.Obj().cash);

	return 0;
}

int LogicTouchGold::Process(unsigned uid, ProtoActivity::TouchGoldResetReq* req, ProtoActivity::TouchGoldInfo* resp)
{
	DBCUserBaseWrap user(uid);
	DBCTouchGoldWrap touch(uid);

	touch.Reset();

	touch.FullMessage(user.Obj(), resp);

	return 0;
}

int LogicTouchGold::Process(unsigned uid, ProtoActivity::TouchGoldSwitchReq* req, ProtoActivity::TouchGoldInfo* resp)
{
	DBCUserBaseWrap user(uid);
	DBCTouchGoldWrap touch(uid);

	unsigned id = req->id();
	if (id != touch.Obj().tomb_id)
	{
		touch.SwitchTomb(req->id());
	}

	touch.FullMessage(user.Obj(), resp);

	return 0;
}

int LogicTouchGold::Process(unsigned uid, ProtoActivity::TouchGoldUnlockReq* req, ProtoActivity::TouchGoldResp* resp)
{
	DBCUserBaseWrap user(uid);
	DBCTouchGoldWrap touch(uid);

	unsigned tombId = req->id();
	if (! touch.IsTombOpened(tombId))
	{
		unsigned cost = TouchGoldCfgWrap().GetUnlockCost(tombId);
		user.CostCash(cost, "touch_gold_unlock_tomb");

		touch.OpenTomb(tombId);
	}


	touch.FullMessage(user.Obj(), resp->mutable_info());
	resp->set_cash(user.Obj().cash);

	return 0;
}
