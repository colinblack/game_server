/*
 * LogicUserManager.cpp
 *
 *  Created on: 2016-9-12
 *      Author: dawx62fac
 */

#include "LogicUserManager.h"

DBCUserBaseWrap::DBCUserBaseWrap(unsigned uid)
	: container_(BaseManager::Instance())
	, index_(_Index(uid))
	, data_(container_->m_data->data[index_])
{
}

DBCUserBaseWrap::DBCUserBaseWrap(unsigned index, DataBase& data)
	: container_(BaseManager::Instance())
	, index_(index)
	, data_(data)
{

}

int DBCUserBaseWrap::_Index(unsigned uid)
{
	int index = container_->GetIndex(uid);
	if (index < 0)
	{
		int ret = container_->LoadBuff(uid);
		if (0 != ret) {
			error_log("get_user_data_error.uid=%u,ret=%d", uid, ret);
			throw std::runtime_error("get_user_data_error");
		}

		return container_->GetIndex(uid);
	}

	return index;
}

void DBCUserBaseWrap::AddCash(int cash, const std::string& reason)
{
	if (cash <= 0)
	{
		error_log("[AddCash] wrong param. uid=%u, cash=%d", data_.uid, cash);
		throw std::runtime_error("invalid_cash_param");
	}

	COINS_LOG("[%s][uid=%u,ocash=%u,ncash=%u,chgcash=%d]"
			, reason.c_str(), data_.uid, data_.cash, data_.cash+cash, cash);

	data_.cash += cash;

	Save();
}

void DBCUserBaseWrap::CostCash(int cash, const std::string& reason)
{
	if (cash <= 0)
	{
		error_log("wrong param. uid=%u, cash=%d", data_.uid, cash);
		throw std::runtime_error("invalid_cash_param");
	}

	if (cash > (int)data_.cash)
	{
		error_log("cash not enough uid=%u,chgcash=%d,cash=%u", data_.uid, cash, data_.cash);
		throw std::runtime_error("cash_not_enough");
	}

	unsigned old_cash = data_.cash;
	data_.cash -= cash;

	COINS_LOG("[%s][uid=%u,ocash=%u,ncash=%u,chgcash=%d]", reason.c_str(), data_.uid, old_cash, data_.cash, -cash);
	Save();
}

void DBCUserBaseWrap::FullMessage(User::Base* obj) const
{
	data_.SetMessage(obj);
}


void DBCUserBaseWrap::AccRecharge(int count,  bool isPush)
{
	data_.acccharge += count;

	RefreshVIPLevel(isPush);

	Save();
}

bool DBCUserBaseWrap::IsGetFirstRechargeReward() const
{
	//检测第1位是否为0
	return data_.acccharge >= 100 && (0 == (data_.first_recharge & 1));
}

void DBCUserBaseWrap::SetFirstRechargeRewardStatus()
{
	//设置第1位为1
	data_.first_recharge |= 1;

	Save();
}

bool DBCUserBaseWrap::IsGetSecondRechargeReward() const
{
	//是否能够领取
	return data_.acccharge >= 888 && (0 == (data_.first_recharge & 2));
}

void DBCUserBaseWrap::SetSecondRechargeRewardStatus()
{
	data_.first_recharge |= 2;

	Save();
}

int DBCUserBaseWrap::AsynType2ResourceType(ASYN_TYPE type)
{
	switch(type)
	{
		case e_asyn_coin: return 0;
		default:
		{
			error_log("unknow_asyn_type: ", type);
			throw std::runtime_error("unknow_asyn_type");
		}
	}
}

void DBCUserBaseWrap::AddAsynItem(unsigned id, unsigned count, const std::string& op)
{
	if ((ASYN_TYPE)id == e_asyn_cash)
	{
		this->AddCash(count, op);
	}
	else if ((ASYN_TYPE)id == e_asyn_accrecharge)
	{
		data_.acccharge += count;
		LogicUserManager::Instance()->NotifyRecharge(data_.uid, count);

		Common::NoticePay* m = new Common::NoticePay;
		m->set_cash(data_.cash);
		m->set_vip_level(data_.viplevel);
		m->set_acc_recharge(data_.acccharge);
	}
	else if (id == e_asyn_coin)
	{
	}
	else if(id == e_asyn_exp)
	{
	}
	else if (id >= e_asyn_max)
	{
	}

}

void DBCUserBaseWrap::FinalAsynData()
{
	unsigned uid = data_.uid;
	const AsynMap& map_data = AsynManager::Instance()->GetMap();
	if (map_data.count(uid) <= 0)
	{
		return ;
	}

	const AsynMap::const_iterator asyn_it = map_data.find(uid);
	if (asyn_it == map_data.end())
	{
		return ;
	}

	const std::map<unsigned, unsigned>& user_map = asyn_it->second;
	for (std::map<unsigned, unsigned>::const_iterator it = user_map.begin();
			it != user_map.end();
			++it)
	{
		try
		{
			const AsynItem& as_item = AsynManager::Instance()->m_data->item[it->second];
			AddAsynItem(as_item.id, as_item.count);
		}
		catch(const std::exception& e)
		{
			error_log("%s", e.what());
		}

	}

	AsynManager::Instance()->Del(uid);
}

unsigned DBCUserBaseWrap::GetRegisterHours() const
{
	unsigned now = Time::GetGlobalTime();
	if (now > data_.register_time)
	{
		return (now - data_.register_time) / (60*60);
	}
	else
	{
		return 0;
	}
}


void DBCUserBaseWrap::EveryDayAction(int di)
{
	//day interval
	if(di == 1)
	{
		++data_.login_times;
	}
	else
	{
		data_.login_times = 0;
	}

	data_.login_days ++;

	Save();
}


void DBCUserBaseWrap::RefreshVIPLevel(bool isPush)
{
	uint8_t level = data_.viplevel;
	data_.viplevel = 0;//todo
	if (data_.viplevel > level)
	{
		Save();

		unsigned uid = data_.uid;

		if (isPush)
		{
		}
		OfflineResourceItem& resItem = LogicResourceManager::Instance()->Get(uid);
		resItem.viplevel = data_.viplevel;
	}
}
///////////////////////////////////////////////////////////////////////////////////
LogicUserManager::LogicUserManager()
	: baseData_(BaseManager::Instance())
{
	if (baseData_ == NULL)
	{
		error_log("base_data_manager_instance_error");
		throw std::runtime_error("base_data_manager_instance_error");
	}

	start_time = Time::GetGlobalTime();
}

void LogicUserManager::OnTimer1()
{
	unsigned now = Time::GetGlobalTime();

	while(! recharge_records_.empty())
	{
		const _RechargeRecord& record = recharge_records_.front();
		try
		{
			DBCUserBaseWrap user(record.uid);

			unsigned oldvip = user.Obj().viplevel;

			//添加充值记录到玩家的档里
			DataChargeHistoryManager::Instance()->AddChargeHistory(record.uid, record.cash);

			user.RefreshVIPLevel();

			Common::NoticePay* m = new Common::NoticePay;
			m->set_cash(user.Obj().cash);
			m->set_vip_level(user.Obj().viplevel);
			m->set_acc_recharge(user.Obj().acccharge);

			LogicManager::Instance()->sendMsg(record.uid, m);

			//推送最新的累积充值数据
			User::PushAccumulateChangeReq * pushmsg = new User::PushAccumulateChangeReq;
			//GET_RMI(record.uid).SetMessage(pushmsg->mutable_change_acccharge());
			//改为使用玩家档中的充值数据
			DataChargeHistoryManager::Instance()->FullMessage(record.uid, pushmsg->mutable_change_acccharge());

			LogicManager::Instance()->sendMsg(record.uid, pushmsg);
		}
		catch (const std::exception& e)
		{
			error_log("uid: %u, %s", record.uid, e.what());
		}

		recharge_records_.pop_front();
	}
}

void LogicUserManager::NotifyRecharge(unsigned uid, unsigned cash)
{
	recharge_records_.push_back(_RechargeRecord(uid, cash));
}

void LogicUserManager::CostCash(unsigned uid, int cash, string reason, unsigned & newcash)
{
	DBCUserBaseWrap userWrap(uid);
	userWrap.CostCash(cash, reason);

	newcash = userWrap.Obj().cash;
}

int LogicUserManager::EveryDayAction()
{
	std::vector<unsigned> vUsers;
	UserManager::Instance()->GetOnlineUsers(vUsers);

	for (size_t i = 0; i < vUsers.size(); ++i)
	{
		try
		{
			DBCUserBaseWrap user(vUsers[i]);
			user.EveryDayAction();
		}
		catch(const std::exception& e)
		{
			error_log("uid: %u, %s", vUsers[i], e.what());
		}
	}

	return R_SUCCESS;
}

int LogicUserManager::Process(unsigned uid, User::CostCashReq* req, User::CostCashResp* resp)
{
	DBCUserBaseWrap user(uid);
	if (req->cash() > user.Obj().cash)
	{
		throw std::runtime_error("cash_not_enough");
	}

	if (req->op_code().empty())
	{
		throw std::runtime_error("need_op_code");
	}

	user.CostCash(req->cash(), req->op_code());

	if (resp)
	{
		resp->set_cash(user.Obj().cash);
		resp->set_operation(req->operation());
	}

	return R_SUCCESS;
}

