/*
 * LogicCashBack.cpp
 *
 *  Created on: 2016-11-22
 *      Author: dawx62fac
 */

#include "LogicCashBack.h"

DBCCashBackWrap::DBCCashBackWrap(unsigned uid)
	: container_(DataCashBackMgr::Instance())
	, index_(_Index(uid))
	, data_(container_->m_data->data[index_])
{
	unsigned nVersion = LogicCashBack::Instance()->GetVersion();
	if (nVersion != data_.version || ! Time::IsToday(data_.ts_op))
	{
		data_.Reset(nVersion);

		Save();
	}

	//充值计算从resourcemanager里面读取
	data_.total = LogicResourceManager::Instance()->GetRechargePays(uid, data_.ts_op);
}

unsigned DBCCashBackWrap::_Index(unsigned uid)
{
	if (! LogicCashBack::Instance()->IsOpen())
	{
		throw std::runtime_error("cash_back_activity_not_open");
	}

	return container_->GetIndex(uid);
}


void DBCCashBackWrap::SetRewardFlag(int id)
{
	if (id < 1 || id > 32)
	{
		throw std::runtime_error("cash_back_id_params_error");
	}

	data_.reward_flag |= 1 << (id - 1);

	Save();
}

bool DBCCashBackWrap::IsRewardFlag(int id) const
{
	if (id < 1 || id > 32)
	{
		throw std::runtime_error("cash_back_id_params_error");
	}

	unsigned flag = 1 << (id - 1);

	return (data_.reward_flag & flag) > 0;
}

//////////////////////////////////////////////////////////////////////
bool LogicCashBack::IsOpen()
{
	return this->IsOn();
}

void LogicCashBack::Online(unsigned uid)
{
	if (IsOpen())
	{
		try
		{
			if (! DataCashBackMgr::Instance()->IsExist(uid))
			{
				DataCashBackMgr::Instance()->LoadBuffer(uid);
			}
		}
		catch(const std::exception& e)
		{
			error_log("%s", e.what());
		}

	}

}


int LogicCashBack::Process(unsigned uid, ProtoActivity::CashBackInfoReq* req, ProtoActivity::CashBackInfoResp* resp)
{
	DBCCashBackWrap cashBack(uid);

	CashBackCfgWrap cfg;
	for (int i = 1; i <= cfg.MaxId(); i++)
	{
		try
		{
			if (! cashBack.IsRewardFlag(i)
					&& cashBack.Obj().total >= cfg.GetItem(i).total())
			{
				::ProtoActivity::CashBackItem* obj = resp->add_items();
				obj->set_id(i);
				obj->set_is_get_reward(true);
			}
			else
			{
				::ProtoActivity::CashBackItem* obj = resp->add_items();
				obj->set_id(i);
				obj->set_is_get_reward(false);
			}
		}
		catch(const std::exception& e)
		{
			(void)e;
			break;
		}
	}

	resp->set_total_recharge(cashBack.Obj().total);

	return 0;
}

int LogicCashBack::Process(unsigned uid, ProtoActivity::CashBackRewardReq* req, ProtoActivity::CashBackRewardResp* resp)
{
	DBCUserBaseWrap user(uid);
	DBCCashBackWrap cashBack(uid);
	unsigned id = req->id();

	if (cashBack.Obj().total < CashBackCfgWrap().GetItem(id).total())
	{
		throw std::runtime_error("accumulated_recharge_not_enough");
	}

	if (cashBack.IsRewardFlag(id))
	{
		throw std::runtime_error("already_get_cash_back_reward");
	}

	cashBack.SetRewardFlag(id);

	int cash = CashBackCfgWrap().GetItem(id).back();
	user.AddCash(cash, "cash_back_activity_op");

	resp->mutable_item()->set_id(id);
	resp->mutable_item()->set_is_get_reward(false);
	resp->mutable_reward()->mutable_cash()->set_total_value(user.Obj().cash);
	resp->mutable_reward()->mutable_cash()->set_value(cash);

	return 0;
}
