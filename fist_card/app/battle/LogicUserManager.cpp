/*
 * LogicUserManager.cpp
 *
 *  Created on: 2016-9-12
 *      Author: dawx62fac
 */

#include "LogicUserManager.h"

OffUserSaveControl::OffUserSaveControl(unsigned uid):
		uid_(uid)
{
	//加载用户的玩家档
	int ret = UserManager::Instance()->LoadArchives(uid_);

	if (ret)
	{
		throw runtime_error("load_other_data_error");
	}
}

OffUserSaveControl::~OffUserSaveControl()
{
	//析构的时候，进行离线用户保存
	UserManager::Instance()->SyncSave(uid_);
}


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

unsigned DBCUserBaseWrap::GetCash()
{
	return data_.cash;
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

void DBCUserBaseWrap::AddCoin(int coin, const std::string& reason)
{
	if (coin <= 0)
	{
		error_log("[AddCoin] wrong param. uid=%u, coin=%d", data_.uid, coin);
		throw std::runtime_error("invalid_coin_param");
	}

	RESOURCE_LOG("[%s][uid=%u,ocoin=%u,ncoin=%u,chgcoin=%d]"
			, reason.c_str(), data_.uid, data_.coin, data_.coin+coin, coin);

	data_.coin += coin;

	Save();
}

unsigned DBCUserBaseWrap::GetCoin()
{
	return data_.coin;
}

void DBCUserBaseWrap::CostCoin(int coin, const std::string& reason)
{
	if (coin <= 0)
	{
		error_log("wrong param. uid=%u, coin=%d", data_.uid, coin);
		throw std::runtime_error("invalid_coin_param");
	}

	if (coin > (int)data_.coin)
	{
		error_log("coin not enough uid=%u,chgcoin=%d,coin=%u", data_.uid, coin, data_.coin);
		throw std::runtime_error("coin_not_enough");
	}

	unsigned old_coin = data_.coin;
	data_.coin -= coin;

	RESOURCE_LOG("[%s][uid=%u,ocoin=%u,ncoin=%u,chgcoin=%d]", reason.c_str(), data_.uid, old_coin, data_.coin, -coin);

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
		m->set_viplevel(data_.viplevel);
		m->set_accrecharge(data_.acccharge);
	}
	else if((ASYN_TYPE)id == e_asyn_power)
	{
		//恢复体力
		RecoverPower(Time::GetGlobalTime(), data_.recover_time);
		CommonGiftConfig::CommonModifyItem cfg;
		cfg.mutable_based()->set_power(count);
		ProtoPush::PushDonationPower* msg = new ProtoPush::PushDonationPower;
		LogicUserManager::Instance()->CommonProcess(data_.uid, cfg, "systime_friend_donate_power", msg->mutable_commons());
		LMI->sendMsg(data_.uid, msg);
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

bool DBCUserBaseWrap::AddExp(int exp)
{
	unsigned old_lvl = data_.level;

	if (exp > 0)
	{
		data_.AddExp(exp);
		data_.onhook_exp_ts = Time::GetGlobalTime();
		Save();

		if (data_.level > old_lvl)
		{
			//用户升级推送
			OnUserUpgradeReward(old_lvl);

			std::string open_id = UserManager::Instance()->GetOpenId(data_.uid);
			USER_LOG("[upgrade]uid=%u,open_id=%s,name:%s,old_level=%d,new_level:%d"
					, data_.uid, open_id.c_str(),data_.name, old_lvl, data_.level);
		}

		return true;
	}

	return false;
}

void DBCUserBaseWrap::AddPower(int power, int limit, const std::string& reason)
{
	if (power <0)
	{
		error_log("[AddPower] wrong param. uid=%u, power=%d", data_.uid, power);
		throw std::runtime_error("invalid_power_param");
	}
	if(0 == power)
		return;
	unsigned old_power = data_.power;
	//0： 没有上限限制, 1：有上限限制
	if(0 == limit)
	{
		data_.power += power;
	}
	else if(1 == limit)
	{
		if(data_.power >= POWER_MAX)
			return;
		if(data_.power + power >= POWER_MAX)
			data_.power = POWER_MAX;
		else
			data_.power += power;
	}


	POWER_LOG("[%s][uid=%u,opower=%u,npowerh%u,chgpower=%d]"
			, reason.c_str(), data_.uid, old_power, data_.power, power);
	Save();
}

void DBCUserBaseWrap::CostPower(int power, const string &reason)
{
	if (power <= 0)
	{
		error_log("wrong param. uid=%u, power=%d", data_.uid, power);
		throw std::runtime_error("invalid_power_param");
	}

	if (power> (int)data_.power)
	{
		error_log("power not enough uid=%u,chgpower=%d,power=%u", data_.uid, power, data_.power);
		throw std::runtime_error("power_not_enough");
	}

	unsigned old_power = data_.power;
	data_.power -= power;

	POWER_LOG("[%s][uid=%u,opower=%u,npower=%u,chgpower=%d]", reason.c_str(), data_.uid, old_power, data_.power, -power);
	Save();
}

void DBCUserBaseWrap::RecoverPower(unsigned now, unsigned last)
{
	if(now < last)
	{
		error_log("power recover error uid: %u, now: %u, last: %u", data_.uid, now, last);
		throw runtime_error("recover_power_error");
	}
	debug_log(" ---------  recover power, uid: %u, now: %u, last: %u --------- ", data_.uid, now, last);
	unsigned inc = INC_POW(now, last);
	AddPower(inc, 1, "recover_power");
	data_.recover_time = now;
	Save();
}


void DBCUserBaseWrap::AddHonor(int honor, const string &reason)
{
	if(honor < 0)
	{
		error_log("[AddHonor] wrong param. uid=%u, honor =%d", data_.uid, honor);
		throw runtime_error("param_error");
	}

	unsigned old_honor = data_.honor;
	data_.honor += honor;
	USER_LOG("[%s][uid=%u,ohonor=%u,nhonor%u,chghonor=%d]"
				, reason.c_str(), data_.uid, old_honor, data_.honor, honor);
	Save();
}

void DBCUserBaseWrap::CostHonor(int honor, const std::string& reason)
{
	if(honor < 0)
	{
		error_log("[CostHonor] wrong param. uid=%u, honor =%d", data_.uid, honor);
		throw runtime_error("param_error");
	}
	if(honor > (int)data_.honor)
	{
		error_log("honor not enough uid=%u,chghonor=%d,honor=%u", data_.uid, honor, data_.honor);
		throw std::runtime_error("honor_not_enough");
	}

	unsigned old_honor = data_.honor;
	data_.honor -= honor;
	USER_LOG("[%s][uid=%u,ohonor=%u,nhonor%u,chghonor=%d]"
				, reason.c_str(), data_.uid, old_honor, data_.honor, honor);
	Save();
}


unsigned DBCUserBaseWrap::GetStages()
{
	return data_.pass;
}

void DBCUserBaseWrap::UpdateStages(unsigned idx)
{
	data_.pass = idx;
	Save();
}


unsigned DBCUserBaseWrap::GetLevel()
{
	return data_.level;
}

bool DBCUserBaseWrap::GetArchive(unsigned id)
{
	if(id < 1 || id > MAX_HERO_NUM)
		return false;
	int idx = id-1;
	data_.archive_level[idx] = 1;
	Save();

	return true;
}

bool DBCUserBaseWrap::ActArchiveChip(unsigned id, int idx)
{
	if(idx < 0 || idx >= ARCHIVE_CHIP_NUM)
	{
		return false;
	}

	uint16_t& chips = data_.archive_chip[id-1];

	if((chips & (uint16_t)(1 << idx)) != 0)
	{
		return false;
	}

	chips |= (uint16_t)(1 << idx);

	Save();
	return true;
}

bool DBCUserBaseWrap::UnActArchiveChip(unsigned id, int idx)
{
	if(idx < 0 || idx >= ARCHIVE_CHIP_NUM)
		return false;
	uint16_t& chips = data_.archive_chip[id-1];
	if((chips & (uint16_t)(1 << idx)) == 0)
		return false;
	chips &= ~(uint16_t)(1 << idx);

	Save();
	return true;
}

bool DBCUserBaseWrap::ArchiveUpLevel(unsigned id)
{
	if(id < 1 || id > ARCHIVE_CHIP_LENGTH)
		return false;

	uint16_t& chips = data_.archive_chip[id-1];
	if(0 != (chips ^ 0x01FF))
		return false;

	data_.archive_level[id-1] += 1;

	memset(&chips, 0, sizeof(chips));
	Save();

	return true;
}

bool DBCUserBaseWrap::UpateArchiveRewardCount(unsigned id)
{
	if(id < 1 || id > ARCHIVE_LENGTH)
		return false;
	if(data_.archive_reward[id-1] + 1 >= data_.archive_level[id-1])
		return false;

	data_.archive_reward[id-1]++;
	Save();
	return true;
}


void DBCUserBaseWrap::RestPowerPropTimes()
{

	bool isToday = Time::IsToday(data_.use_props_ts);
	if(isToday)
		return;

	for(int i = 0; i < LIMIT_TIMES_PROPS_LEN; ++i)
	{
		data_.limit_times_props[i] = 0;
	}
	Save();
}

bool DBCUserBaseWrap::UpdatePowerPropTimes(int idx)
{
	if(idx >= LIMIT_TIMES_PROPS_LEN)
		return false;
	if(data_.limit_times_props[idx] >= POWER_PROP_TIMES)
		return false;
	data_.limit_times_props[idx] += 1;
	Save();

	return true;
}


void DBCUserBaseWrap::UpdatePowerPropTs(unsigned ts)
{
	data_.use_props_ts = ts;
	Save();
}

void DBCUserBaseWrap::ResetDonatePower()
{
	data_.daily_power = 0;
	Save();
}

void DBCUserBaseWrap::UpdateDonatePowerTs(unsigned ts)
{
	data_.daily_power_ts = ts;
	Save();
}

void DBCUserBaseWrap::OnUserUpgradeReward(unsigned old_level)
{
	LogicResourceManager::Instance()->SyncUserLevel(data_.uid, data_.level);

	ProtoPush::PushUserUpLevel* msg = new ProtoPush::PushUserUpLevel;
	DataCommon::BaseItemCPP* basemsg = msg->mutable_commons()->mutable_userbase()->add_baseitem();

	basemsg->set_type(type_level);
	basemsg->set_change(data_.level - old_level);
	basemsg->set_totalvalue(data_.level);

	LogicManager::Instance()->sendMsg(data_.uid, msg);
}

void DBCUserBaseWrap::SetHero(unsigned heroid)
{
	data_.heroId = heroid;
	Save();
}

void DBCUserBaseWrap::IncDailyBattleCount()
{
	data_.daily_battle_count +=1;
	Save();
}

void DBCUserBaseWrap::BaseProcess(const CommonGiftConfig::BaseItem & base, DataCommon::UserBaseChangeCPP* obj,
		  const std::string& reason, double nMul)
{
	CheckBaseBeforeCost(data_.uid, reason, base);

	string strlog;

	char szchgtemp[1000] = {0};
	sprintf(szchgtemp, "[%s] uid=%u,", reason.c_str(), data_.uid);
	strlog += szchgtemp;

	if (base.has_coin())
	{
		int coin = base.coin() * nMul;
		if(coin < 0 && data_.coin < -coin)
		{
			error_log("coin not enough uid=%u,chgcoin=%d,coin=%u", data_.uid, coin, data_.coin);
			throw std::runtime_error("coin_not_enough");
		}

		int add = LOI->OnhookExpOrCoin(e_onhook_coin, data_.onhook_coin_ts, Time::GetGlobalTime(), data_.pass);
		if(add > 0)
			coin += add;
		data_.coin += coin;
		sprintf(szchgtemp, "chgcoin=%d,coin=%u,", coin, data_.coin);
		strlog += szchgtemp;

		DataCommon::BaseItemCPP * item = obj->add_baseitem();

		item->set_type(type_coin);
		//item->set_id(id);
		item->set_change(coin);
		item->set_totalvalue(data_.coin);
		if(add > 0)
		{
			data_.onhook_coin_ts = Time::GetGlobalTime();
			item->set_onhookcoints(data_.onhook_coin_ts);
		}

	}

	//只支持加经验
	if (base.has_exp() && base.exp() >= 0)
	{
		//经验没有扣除这一说法，所以AddExp方法内，排除了经验小于0的情况
		int exp = nMul * base.exp();
		int add = LOI->OnhookExpOrCoin(e_onhook_exp, data_.onhook_exp_ts, Time::GetGlobalTime(), data_.pass);
		if(add > 0)
			exp += add;
		bool success = AddExp(exp);

		if (success)
		{
			sprintf(szchgtemp, "chgexp=%d,exp=%llu,", exp, data_.exp);
			strlog += szchgtemp;

			DataCommon::BaseItemCPP * item = obj->add_baseitem();

			item->set_type(type_exp);
			//item->set_id(id);
			item->set_change(exp);
			item->set_totalvalue(data_.exp);
			if(add > 0)
			{
				data_.onhook_exp_ts = Time::GetGlobalTime();
				item->set_onhookexpts(data_.onhook_exp_ts);
			}

		}
	}

	if (base.has_cash())
	{
		//调用加钻石的接口
		int cash = base.cash() * nMul;

		if (cash > 0)
		{
			AddCash(cash, reason);
		}
		else if (cash < 0)
		{
			CostCash(-cash, reason);
		}

		DataCommon::BaseItemCPP * item = obj->add_baseitem();

		item->set_type(type_cash);
		//item->set_id(id);
		item->set_change(cash);
		item->set_totalvalue(data_.cash);
	}
	if (base.has_power())
	{
		int power = base.power() * nMul;

		if(power > 0)
		{
			AddPower(power, 0, reason);
		}
		else if(power < 0)
		{
			CostPower(-power, reason);
		}
		DataCommon::BaseItemCPP * item = obj->add_baseitem();

		item->set_type(type_power);
		item->set_change(power);
		item->set_totalvalue(data_.power);
		item->set_powerts(data_.recover_time);
	}

	Save();

	RESOURCE_LOG(strlog.c_str());
}

int DBCUserBaseWrap::CheckBaseBeforeCost(unsigned uid, const string & reason, const CommonGiftConfig::BaseItem & base)
{
	if (base.has_coin() && base.coin() < 0 && static_cast<unsigned>(-base.coin()) > data_.coin)
	{
		error_log("coin not enough. uid=%u,need=%d,code=%s", uid, base.coin(), reason.c_str());
		throw runtime_error("coin_not_enough");
	}

	if (base.has_cash() && base.cash() < 0 && static_cast<unsigned>(-base.cash()) > data_.cash)
	{
		error_log("cash not enough. uid=%u,need=%d,code=%s", uid, base.cash(), reason.c_str());
		throw runtime_error("cash_not_enough");
	}

	return 0;
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
	//unsigned now = Time::GetGlobalTime();

	while(! recharge_records_.empty())
	{
		const _RechargeRecord& record = recharge_records_.front();
		try
		{
			DBCUserBaseWrap user(record.uid);

			//unsigned oldvip = user.Obj().viplevel;

			//添加充值记录到玩家的档里
			DataChargeHistoryManager::Instance()->AddChargeHistory(record.uid, record.cash);

			user.RefreshVIPLevel();

			Common::NoticePay* m = new Common::NoticePay;
			m->set_cash(user.Obj().cash);
			m->set_viplevel(user.Obj().viplevel);
			m->set_accrecharge(user.Obj().acccharge);

			LogicManager::Instance()->sendMsg(record.uid, m);

			//推送最新的累积充值数据
			User::PushAccumulateChangeReq * pushmsg = new User::PushAccumulateChangeReq;
			//GET_RMI(record.uid).SetMessage(pushmsg->mutable_change_acccharge());
			//改为使用玩家档中的充值数据
			DataChargeHistoryManager::Instance()->FullMessage(record.uid, pushmsg->mutable_changeacccharge());

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


int LogicUserManager::DonatePower(unsigned uid, unsigned power, const string& reason)
{
	DBCUserBaseWrap userWrap(uid);

	unsigned ts = userWrap.Obj().daily_power_ts;
	CommonGiftConfig::CommonModifyItem cfg;
	cfg.mutable_based()->set_power(power);
	if(!Time::IsToday(ts))
	{
		userWrap.UpdateDonatePowerTs(Time::GetGlobalTime());
		ProtoPush::PushDonationPower* msg = new ProtoPush::PushDonationPower;
		LogicUserManager::Instance()->CommonProcess(uid, cfg, reason, msg->mutable_commons());
		userWrap.ResetDonatePower();
		return LMI->sendMsg(uid, msg)? 0 : R_ERROR;
	}

	return R_ERROR;
}



int LogicUserManager::Process(unsigned uid, User::CostCashReq* req, User::CostCashResp* resp)
{
	DBCUserBaseWrap user(uid);
	if (req->cash() > user.Obj().cash)
	{
		throw std::runtime_error("cash_not_enough");
	}

	if (req->opcode().empty())
	{
		throw std::runtime_error("need_op_code");
	}

	user.CostCash(req->cash(), req->opcode());

	if (resp)
	{
		resp->set_cash(user.Obj().cash);
		resp->set_operation(req->operation());
	}

	return R_SUCCESS;
}

int LogicUserManager::Process(unsigned uid, User::BuyPowerReq* req, User::BuyPowerResp* resp)
{
	unsigned ts = req->ts();
	DBCUserBaseWrap user(uid);

	//体力恢复
	user.RecoverPower(ts, user.Obj().recover_time);
	unsigned power = user.Obj().power;
	//体力必须小于上限
	if(power >= POWER_MAX)
	{
		error_log("power reached limit: %u, power: %u", uid, power);
		throw runtime_error("power_reached_limit");
	}
	unsigned propId = req->propid();


	const ConfigItem::PropItem& prop = ItemCfgWrap().GetPropsItem(propId);
	if(prop.type() != item_type_strength)
	{
		error_log("propId is wrong uid:%u, type: %u", uid, prop.type());
		throw runtime_error("param_error");
	}

	user.RestPowerPropTimes();
	int propIdx =  ConfigManager::Instance()->GetPowerPropIndex(propId);
	if(-1 == propIdx)
	{
		error_log("propId is wrong uid:%u, type: %u", uid, prop.type());
		throw runtime_error("param_error");
	}
	if(!user.UpdatePowerPropTimes(propIdx))
	{
		error_log("buy power fail uid:%u, type: %u", uid);
		throw runtime_error("buy_power_fail");
	}

	user.UpdatePowerPropTs(Time::GetGlobalTime());
	CommonGiftConfig::CommonModifyItem cfg;
	cfg.mutable_based()->set_power(prop.dimond_cost().based().power());
	CommonGiftConfig::PropsItem * propsbase = cfg.add_props();
	propsbase->set_count(-1);
	propsbase->set_id(propId);

	LogicUserManager::Instance()->CommonProcess(uid, cfg, "buy_power", resp->mutable_commons());

	return 0;
}

int LogicUserManager::Process(unsigned uid, User::InviteActivityUrlReq* req)
{
	DataBase& user = BaseManager::Instance()->Get(uid);
	if(user.last_login_time - Time::GetGlobalTime() > 30)
		return 0;
	unsigned uuid = req->uuid();

	if(CMI->IsNeedConnectByUID(uuid))
	{
		User::CSInviteActivityUrlReq* msg = new User::CSInviteActivityUrlReq;
		msg->set_uuid(uuid);
		msg->set_uid(uid);
		return ProtoManager::BattleConnectNoReplyByUID(uuid, msg);
	}

	//加载离线数据
	OffUserSaveControl  offuserCtl(uuid);
	DBCUserBaseWrap uuser(uuid);
	uuser.Obj().invite_friend_count++;
	uuser.Save();

	//保存被邀请玩家信息
	if(uuser.Obj().invite_friend_count <= MAX_INVITE_REWARD_NUM)
	{
		int index = DataInviteManager::Instance()->GetIndex(uuid, uid);
		DataInvite& data = DataInviteManager::Instance()->m_data->data[index];

		memcpy(data.name, user.name, sizeof(data.name));
		memcpy(data.fig, user.fig, sizeof(data.fig));
		DataInviteManager::Instance()->m_data->MarkChange(index);
	}

	return 0;
}

int LogicUserManager::Process(User::CSInviteActivityUrlReq* req)
{
	unsigned uuid = req->uuid();
	unsigned uid  = req->uid();

	DataBase& user = BaseManager::Instance()->Get(uid);
	//加载离线数据
	OffUserSaveControl  offuserCtl(uuid);
	DBCUserBaseWrap uuser(uuid);
	uuser.Obj().invite_friend_count++;
	uuser.Save();


	//保存被邀请玩家信息
	if(uuser.Obj().invite_friend_count <= MAX_INVITE_REWARD_NUM)
	{
		int index = DataInviteManager::Instance()->GetIndex(uuid, uid);
		DataInvite& data = DataInviteManager::Instance()->m_data->data[index];

		memcpy(data.name, user.name, sizeof(data.name));
		memcpy(data.fig, user.fig, sizeof(data.fig));
		DataInviteManager::Instance()->m_data->MarkChange(index);
	}

	return 0;
}

int LogicUserManager::Process(unsigned uid, User::GetInviteRewardReq* req, User::GetInviteRewardResp* resp)
{
	unsigned seq = req->seq();
	DBCUserBaseWrap user(uid);

	if(user.Obj().invite_friend_count < seq || seq < 1)
	{
		error_log("param error");
		throw runtime_error("param_error");
	}
	uint64_t& mark = user.Obj().invite_reward_mark;
	if(0 != (mark & (1 << (seq-1))))
	{
		error_log("get fail");
		throw runtime_error("get_fail");
	}
	auto& cfg = ActiveCfgWrap().GetInviteRewardBySeq(seq);

	CommonProcess(uid, cfg.rewards(), "get_invite_reward", resp->mutable_commons());
	mark |= (1 << (seq-1));
	user.Save();
	resp->set_mark(mark);

	return 0;
}

int LogicUserManager::Process(unsigned uid, User::GetAddInviteRewardReq* req, User::GetAddInviteRewardResp* resp)
{
	unsigned num = req->num();
	DBCUserBaseWrap user(uid);

	if(user.Obj().invite_friend_count < num)
	{
		error_log("param error");
		throw runtime_error("param_error");
	}

	auto& cfg = ActiveCfgWrap().GetInviteRewardByNum(num);
	int pos = ConfigManager::Instance()->invite_addreward_index[num];
	unsigned& mark = user.Obj().invite_add_reward_mark;
	if(0 != (mark & (1<< pos)))
	{
		error_log("get fail");
		throw runtime_error("get_fail");
	}
	CommonProcess(uid, cfg.rewards(), "get_addinvite_reward", resp->mutable_commons());
	mark |= (1 << pos);
	user.Save();
	resp->set_mark(mark);
	return 0;
}


int LogicUserManager::Process(unsigned uid, User::GetDrawRewardReq* req, User::GetDrawRewardResp* resp)
{
	bool isFree  = req->free() == 0 ? true : false;
	//免费领取
	DBCUserBaseWrap user(uid);

	if(isFree &&Time::IsToday(user.Obj().free_draw_reward_ts))
	{
		error_log("time_invalid uid:%u", uid);
		throw runtime_error("time_invalid");
	}

	unsigned rewardId = draw_reward_id_[uid];
	ActiveCfgWrap cfgWrap;
	auto& cfg = cfgWrap.GetLuckyDrawRewardById(rewardId);
	int cost = (int)cfgWrap.Activity().luckyrewardcost();

	vector<unsigned> weight;
	if(isFree)
	{
		for(int i = 0; i < cfg.items_size(); ++i)
		{
			weight.push_back(cfg.items(i).weight());
		}
	}
	else
	{
		for(int i = 0; i < cfg.items_size(); ++i)
		{
			weight.push_back(cfg.items(i).freeweight());
		}
	}

	int idx = 0;
	LogicCommonUtil::TurnLuckTable(weight,weight.size(),idx);
	auto rewardCfg = cfg.items(idx);
	if(rewardCfg.rewards().based().has_cash())
	{
		int cash = rewardCfg.rewards().based().cash();
		rewardCfg.mutable_rewards()->mutable_based()->set_cash(-cost+cash); //set_cash(-cost+cash);
		draw_reward_cost_cash_[uid] += (cost - cash) ;
	}
	else
	{
		rewardCfg.mutable_rewards()->mutable_based()->set_cash(-cost);
		draw_reward_cost_cash_[uid] += cost;
	}

	CommonProcess(uid, rewardCfg.rewards(), "get_draw_rewards", resp->mutable_commons());

	if(isFree)
		user.Obj().free_draw_reward_ts = Time::GetGlobalTime();
	user.Save();

	//下次抽检奖励
	auto& mapIndex = CMI->luck_reward_range_index;
	unsigned range = 0;
	for(auto& e : CMI->luck_reward_range_index)
	{
		if(draw_reward_cost_cash_[uid] <= (int)e.first)
		{
			range = e.first;
			break;
		}
	}
	if(range == 0)
		range = mapIndex.rbegin()->first;

	auto iter = CMI->luck_reward_range_index[range].begin();
	unsigned offest = Math::GetRandomInt(CMI->luck_reward_range_index[range].size());
	advance(iter, offest);
	draw_reward_id_[uid] = iter->first;
	resp->set_index(idx);
	resp->set_nextid(draw_reward_id_[uid]);

	return 0;
}


int LogicUserManager::Process(unsigned uid, User::NewUserAddExpReq* req, User::NewUserAddExpResp* resp)
{
	DBCUserBaseWrap user(uid);
	if(user.Obj().tutorial_stage > TUTORIAL_MAX_STAGE)
	{
		error_log("tutorial stage is max");
		throw runtime_error("tutorial_stage_is_max");
	}

	CommonGiftConfig::CommonModifyItem cfg;
	cfg.mutable_based()->set_exp(req->exp());
	LogicUserManager::Instance()->CommonProcess(uid, cfg, "tutorial_stage", resp->mutable_commons());

	return R_SUCCESS;
}

unsigned LogicUserManager::GetDrawRewardId(unsigned uid)
{
	if(draw_reward_id_.count(uid) == 0)
	{
		auto mapIndex = ConfigManager::Instance()->luck_reward_range_index;
		unsigned range = mapIndex.begin()->first;
		auto iter = mapIndex[range].begin();

		unsigned offest = Math::GetRandomInt(mapIndex[range].size());
		advance(iter, offest);
		unsigned id = iter->first;
		draw_reward_id_[uid] = id;
		draw_reward_cost_cash_[uid] = 0;
	}

	return draw_reward_id_[uid];
}

void LogicUserManager::ResetInviteRwards(unsigned uid, unsigned lastOfftimeTs)
{
	int maxSize = ActiveCfgWrap().Activity().inviterewards_size();

	DBCUserBaseWrap user(uid);
	if(Time::IsToday(lastOfftimeTs))
		return;
	uint64_t& mark1 = user.Obj().invite_reward_mark;
	if(0 != (mark1 ^ ((1 << maxSize) -1)))
		return ;

	unsigned& mark2 = user.Obj().invite_add_reward_mark;
	maxSize = ActiveCfgWrap().Activity().accrewards_size();
	if(0 !=  (mark2 ^ ((1 << maxSize) -1)))
		return ;

	mark1= 0;
	mark2 = 0;
	user.Obj().invite_friend_count = 0;

	user.Save();
}

int LogicUserManager::CommonProcess(unsigned uid, const CommonGiftConfig::CommonModifyItem& cfg, const std::string& reason,
		DataCommon::CommonItemsCPP * obj, double multiple)
{
	DBCUserBaseWrap userwrap(uid);

	//调用底层的通用操作
	CommonUnderlaying(userwrap, cfg, reason, obj, multiple);

	return 0;
}

void LogicUserManager::CommonUnderlaying(DBCUserBaseWrap& user, const CommonGiftConfig::CommonModifyItem& cfg, const std::string& reason,
			DataCommon::CommonItemsCPP* obj, double multiple)
{
	unsigned uid = user.Obj().uid;

	//装备消耗的检查
	CheckPropsBeforeCost(uid, reason, cfg);

	//进行资源的结算
	if (cfg.has_based())
	{
		//处理用户属性的扣除和增加
		user.BaseProcess(cfg.based(), obj->mutable_userbase(), reason, multiple);
	}

	//道具的结算
	for(int i = 0; i < cfg.props_size(); ++i)
	{
		unsigned int propsid = cfg.props(i).id();
		int cnt = cfg.props(i).count();

		if (cnt > 0)
		{
			LogicPropsManager::Instance()->AddProps(uid, propsid, cnt, reason, obj->mutable_props());
		}
		else if (cnt < 0)
		{
			//获取该propid对应的ud
			unsigned ud = DataItemManager::Instance()->GetPropsUd(uid, propsid);

			if (-1 == ud)
			{
				error_log("props not exist. uid=%u,propsid=%u", uid, propsid);
				throw runtime_error("props_not_exist");
			}

			LogicPropsManager::Instance()->CostProps(uid, ud, propsid, -cnt, reason, obj->mutable_props());
		}
	}
}

void LogicUserManager::CheckPropsBeforeCost(unsigned uid, const string & reason, const CommonGiftConfig::CommonModifyItem& cfg)
{
	if (cfg.props_size() > 0)
	{
		for(int i = 0; i < cfg.props_size(); ++i)
		{
			if (cfg.props(i).count() < 0)
			{
				unsigned int propsid = cfg.props(i).id();

				//只支持可叠加装备
				bool isOverlay = LogicPropsManager::Instance()->IsAllowOverlay(propsid);

				if (!isOverlay)
				{
					error_log("props can not overlay. uid=%u,propsid=%u,code=%s", uid, propsid, reason.c_str());
					throw runtime_error("props_cfg_error");
				}

				unsigned ud = DataItemManager::Instance()->GetPropsUd(uid, propsid);

				if (-1 == ud)
				{
					error_log("props not exist. uid=%u,propsid=%u", uid, propsid);
					throw runtime_error("props_not_exist");
				}

				if ( static_cast<unsigned>(-cfg.props(i).count()) > DataItemManager::Instance()->GetData(uid, ud).item_cnt)
				{
					error_log("props not enough. uid=%u,propsid=%u,need=%d,code=%s", uid, propsid, cfg.props(i).count(), reason.c_str());
					throw runtime_error("props_not_enough");
				}
			}
		}
	}
}

