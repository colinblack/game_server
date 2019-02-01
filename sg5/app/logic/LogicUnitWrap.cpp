/*
 * LogicUnitWrap.cpp
 *
 *  Created on: 2016-6-1
 *      Author: dawx62fac
 */

#include <stdexcept>

#include "LogicUnitWrap.h"
#include "LogicCMD.h"


UserWrap::UserWrap(unsigned uid, bool isBase)
	: m_nUid(uid)
	, m_bBase(isBase)
{
	if (! IsValidUid(uid))
	{
		throw std::runtime_error("invalid_uid");
	}

	CLogicUser logicuser;
	int ret;
	if (isBase)
	{
		if ((ret = logicuser.GetUserLimit(m_nUid, m_dataUser)) != 0)
		{
			error_log("get_user_info_failed, uid=%u,ret=%d", uid, ret);
			throw std::runtime_error("get_user_info_limit_failed");
		}
	}
	else
	{
		if ((ret = logicuser.GetUser(m_nUid, m_dataUser)) != 0)
		{
			error_log("get_user_info_failed, uid=%u,ret=%d", uid, ret);
			throw std::runtime_error("get_user_info_failed");
		}
	}
}

int UserWrap::SetUserFlag(Json::Value & user_flag)
{
	if (m_bBase)
	{
		return R_ERROR;
	}

	Json::FastWriter writer;
	m_dataUser.user_flag = writer.write(user_flag);
	
	return R_SUCCESS;
}

int UserWrap::GetUserFlag(Json::Value &user_flag)
{
	if (m_bBase)
	{
		return R_ERROR;
	}

	Json::Reader reader;
	
	reader.parse(m_dataUser.user_flag, user_flag);
	
	return R_SUCCESS;
}

int UserWrap::SetUserTrainQ(Json::Value & trainq)
{
	if (m_bBase)
	{
		return R_ERROR;
	}

	Json::FastWriter writer;
	m_dataUser.trainQ = writer.write(trainq);

	return R_SUCCESS;
}

int UserWrap::GetUserTrainQ(Json::Value &trainq)
{
	if (m_bBase)
	{
		return R_ERROR;
	}

	Json::Reader reader;

	reader.parse(m_dataUser.trainQ, trainq);

	return R_SUCCESS;
}

unsigned UserWrap::GetBattleSpirits()
{
	return m_dataUser.battle_spirits;
}

void UserWrap::ChangeBattle(int battle, string reason)
{
	if ((battle < 0 && (unsigned)(-battle) > m_dataUser.battle_spirits))
	{
		error_log("[ChangeBattle][uid=%u,battle=%d,battle_all=%u,]", m_nUid, battle, m_dataUser.battle_spirits);
		throw std::runtime_error("battle_not_enough");
	}

	m_dataUser.battle_spirits += battle;

	RESOURCE_LOG("[%s][uid=%u,chgbs=%d,bs=%u]", reason.c_str(), m_nUid, battle, m_dataUser.battle_spirits);
}

void UserWrap::GetResource(Json::Value & result)
{
	result["r1"] = m_dataUser.r1;
	result["r2"] = m_dataUser.r2;
	result["r3"] = m_dataUser.r3;
	result["r4"] = m_dataUser.r4;
}

void UserWrap::ChangeResource(int r1, int r2, int r3, int r4, string reason, Json::Value & result)
{
	if ((r1 < 0 && (unsigned)(-r1) > m_dataUser.r1))
	{
		error_log("[ChangeResource][uid=%u,r1=%d,r1_all=%u,]", m_nUid, r1, m_dataUser.r1);
		throw std::runtime_error("resource_not_enough");
	}

	if ((r2 < 0 && (unsigned)(-r2) > m_dataUser.r2))
	{
		error_log("[ChangeResource][uid=%u,r2=%d,r2_all=%u,]", m_nUid, r2, m_dataUser.r2);
		throw std::runtime_error("resource_not_enough");
	}

	if ((r3 < 0 && (unsigned)(-r3) > m_dataUser.r3))
	{
		error_log("[ChangeResource][uid=%u,r3=%d,r3_all=%u,]", m_nUid, r3, m_dataUser.r3);
		throw std::runtime_error("resource_not_enough");
	}

	if ((r4 < 0 && (unsigned)(-r4) > m_dataUser.r4))
	{
		error_log("[ChangeResource][uid=%u,r4=%d,r4_all=%u,]", m_nUid, r4, m_dataUser.r4);
		throw std::runtime_error("resource_not_enough");
	}

	if (r1 > 0 || r2 > 0 || r3 > 0 || r4 > 0)
	{
		AddResource(r1, r2, r3, r4, reason, result);   //资源的增加
	}
	else
	{
		m_dataUser.r1 += r1;
		m_dataUser.r2 += r2;
		m_dataUser.r3 += r3;
		m_dataUser.r4 += r4;

		RESOURCE_LOG("[%s][uid=%u,chgr1=%d,r1=%u,chgr2=%d,r2=%u,chgr3=%d,r3=%u,chgr4=%d,r4=%u]",
					reason.c_str(), m_nUid, r1, m_dataUser.r1, r2, m_dataUser.r2, r3, m_dataUser.r3, r4, m_dataUser.r4);

		result["r1"] = m_dataUser.r1;
		result["r2"] = m_dataUser.r2;
		result["r3"] = m_dataUser.r3;
		result["r4"] = m_dataUser.r4;
	}
}

unsigned UserWrap::GetProsper()
{
	return m_dataUser.prosper;
}

void UserWrap::ChangeProsper(int prosper, string reason, Json::Value & result)
{
	if ((prosper < 0 && (unsigned)(-prosper) > m_dataUser.prosper))
	{
		error_log("[ChangeProsper][uid=%u,prosper=%d,prosper_all=%u,]", m_nUid, prosper, m_dataUser.prosper);
		throw std::runtime_error("prosper_not_enough");
	}

	if (prosper > 0)
	{
		AddProsper(prosper, reason, result);
	}
	else
	{
		m_dataUser.prosper += prosper;
		RESOURCE_LOG("[%s][uid=%u,chgprosper=%d,prosper=%u]", reason.c_str(), m_nUid, prosper, m_dataUser.prosper);

		result["prosper"] = m_dataUser.prosper;
	}
}

unsigned UserWrap::GetEnergyBase()
{
	return m_dataUser.gcbase;
}

void UserWrap::AddEnergyBase(int gcbase, string reason, Json::Value & result)
{
	if (gcbase <= 0)
	{
		error_log("param error. uid=%u,gcbase=%d", m_nUid, gcbase);
		throw runtime_error("param error.");
	}

	m_dataUser.gcbase += gcbase;

	RESOURCE_LOG("[%s][uid=%u,chggcbase=%d,gcbase=%u]", reason.c_str(), m_nUid, gcbase, m_dataUser.gcbase);

	result["gcbase"] = m_dataUser.gcbase;
}

unsigned UserWrap::GetEnergyBuy()
{
	return m_dataUser.gcbuy;
}

void UserWrap::AddEnergyBuy(int gcbuy, string reason, Json::Value & result)
{
	if (gcbuy <= 0)
	{
		error_log("param error. uid=%u,gcbuy=%d", m_nUid, gcbuy);
		throw runtime_error("param error.");
	}

	m_dataUser.gcbuy += gcbuy;

	RESOURCE_LOG("[%s][uid=%u,chggcbuy=%d,gcbuy=%u]", reason.c_str(), m_nUid, gcbuy, m_dataUser.gcbuy);

	result["gcbuy"] = m_dataUser.gcbuy;
}


int UserWrap::GetUserLevel()
{
	return m_dataUser.level;
}
unsigned UserWrap::GetUserExp()
{
	return m_dataUser.point;
}

void UserWrap::GetUserSoldierLevel(Json::Value & soldierlevel)
{
	if (m_bBase)
	{
		throw std::runtime_error("get_user_soldierlevel_error");
	}

	Json::Reader reader;

	reader.parse(m_dataUser.soldierlevel, soldierlevel);
}

void UserWrap::SetUserSoldierLevel(Json::Value & soldierlevel)
{
	if (m_bBase)
	{
		throw std::runtime_error("set_user_soldierlevel_error");
	}

	//只要存档，都需要更新upts
	soldierlevel["upts"] = Time::GetGlobalTime();

	Json::FastWriter writer;
	m_dataUser.soldierlevel = writer.write(soldierlevel);
}


void UserWrap::GetUserBarrackQ(Json::Value & barrackq)
{
	if (m_bBase)
	{
		throw std::runtime_error("get_user_barrackq_error");
	}

	Json::Reader reader;

	reader.parse(m_dataUser.barrackQ, barrackq);
}

void UserWrap::SetUserBarrackQ(Json::Value & barrackq)
{
	if (m_bBase)
	{
		throw std::runtime_error("set_user_barrackq_error");
	}

	//只要存档，就要更新upts
	barrackq["upts"] = Time::GetGlobalTime();

	Json::FastWriter writer;
	m_dataUser.barrackQ = writer.write(barrackq);
}

void UserWrap::GetUserSoldier(Json::Value & soldier)
{
	if (m_bBase)
	{
		throw std::runtime_error("get_user_soldier_error");
	}

	Json::Reader reader;

	reader.parse(m_dataUser.soldier, soldier);
}

void UserWrap::SetUserSoldier(Json::Value & soldier)
{
	if (m_bBase)
	{
		throw std::runtime_error("set_user_soldier_error");
	}

	Json::FastWriter writer;
	m_dataUser.soldier = writer.write(soldier);
}

void UserWrap::GetUserSkillQ(Json::Value & skillq)
{
	if (m_bBase)
	{
		throw std::runtime_error("get_user_skillq_error");
	}

	Json::Reader reader;

	reader.parse(m_dataUser.skillQ, skillq);
}

void UserWrap::SetUserSkillQ(Json::Value & skillq)
{
	if (m_bBase)
	{
		throw std::runtime_error("set_user_skillq_error");
	}

	Json::FastWriter writer;
	m_dataUser.skillQ = writer.write(skillq);
}

void UserWrap::GetUserTech(Json::Value& tech) const
{
	tech.clear();

	if (m_bBase)
	{
		if (CLogicUser().GetUserTech(m_nUid, tech) != R_SUCCESS)
		{
			throw std::runtime_error("get_user_tech_error");
		}
	}
	else
	{
		if ( ! m_dataUser.user_tech.empty()
			&& ! Json::FromString(tech, m_dataUser.user_tech) )
		{
			error_log("[paser user_tech fail][uid=%u]", m_nUid);
			throw std::runtime_error("parse_user_tech_error");
		}
	}
}

void UserWrap::SetUserTech(const Json::Value& tech)
{
	if (m_bBase)
	{
		if (CLogicUser().SetUserTech(m_nUid, tech) != R_SUCCESS)
		{
			throw std::runtime_error("save_user_tech_error");
		}
	}
	else
	{
		m_dataUser.user_tech = Json::ToString(tech);
	}
}


void UserWrap::AddWareSoul(int cnt, const std::string& op, Json::Value& result)
{
	if (cnt <= 0)
	{
		throw std::runtime_error("add_qh_cnt_error");
	}

	Json::Value tech;
	GetUserTech(tech);
	int old_val = tech["godE"]["qlE"][0u].asInt();
	int new_val = old_val + cnt;

	tech["godE"]["qlE"][0u] = new_val;
	SetUserTech(tech);

	RESOURCE_LOG("[%s]uid=%u, qhchg=%d,qh=%u", op.c_str(), m_nUid, cnt, new_val);
	result["qh"] = new_val;
}


void UserWrap::SetUserStats(const Json::Value& stats)
{
	if (m_bBase)
	{
		if (CLogicUser().SetUserStat(m_nUid, stats) != R_SUCCESS)
		{
			throw std::runtime_error("save_user_stats_error");
		}
	}
	else
	{
		m_dataUser.user_stat = Json::ToString(stats);
	}
}

void UserWrap::GetUserStats(Json::Value& stats) const
{
	stats.clear();

	if (m_bBase)
	{
		if (CLogicUser().GetUserStat(m_nUid, stats) != R_SUCCESS)
		{
			throw std::runtime_error("get_user_stats_error");
		}
	}
	else
	{
		if ( ! m_dataUser.user_stat.empty()
			&& ! Json::FromString(stats, m_dataUser.user_stat) )
		{
			error_log("[paser user_stat fail][uid=%u]", m_nUid);
			throw std::runtime_error("parse_user_stats_error");
		}
	}
}

void UserWrap::GetUserGift()
{

}

void UserWrap::SetKingdom(unsigned kingdom, Json::Value& result)
{
	if (kingdom < 1 || kingdom > 3)
	{
		throw std::runtime_error("kingdom_params_error");
	}

	if (m_dataUser.kingdom >= 1 && m_dataUser.kingdom <= 3)
	{
		throw std::runtime_error("already_in_kingdom");
	}

	m_dataUser.kingdom = kingdom;

	result["kingdom"] = kingdom;
}

void UserWrap::Save()
{
	int ret = 0;
	CLogicUser logicuser;
	if (m_bBase)
	{
		if ((ret = logicuser.SetUserLimit(m_nUid, m_dataUser)) != R_SUCCESS)
		{
			error_log("update user failed. uid=%d, ret=%d", m_nUid, ret);
			throw std::runtime_error("save_user_data_error");
		}
	}
	else
	{
		if ((ret = logicuser.SetUser(m_nUid, m_dataUser)) != R_SUCCESS)
		{
			error_log("update user failed. uid=%d, ret=%d", m_nUid, ret);
			throw std::runtime_error("save_user_data_error");
		}
	}
}

unsigned UserWrap::Id() const //Uid;
{
	return m_dataUser.uid;
}

unsigned UserWrap::VipLevel() const
{
	return m_dataUser.viplevel;
}

unsigned UserWrap::TotalRecharge() const
{
	return m_dataUser.accCharge;
}

unsigned UserWrap::RegisterTime() const
{
	return m_dataUser.register_time;
}

int UserWrap::CheckSession(unsigned lasttime, unsigned seqid, Json::Value& result)
{
	int ret = R_SUCCESS;
	CLogicCMD logicCmd;
	//校验uid以及seqid
	if ((ret = logicCmd.checkLastSaveUID(m_dataUser)) != R_SUCCESS)
	{
		return ret;
	}

	if ((ret = logicCmd.checkLastSaveTime(m_dataUser, lasttime, seqid)) != R_SUCCESS)
	{
		return ret;
	}

	result["lasttime"] = m_dataUser.last_save_time;
	result["lastseq"] = m_dataUser.lastseq;
	result["saveuserid"] = m_nUid;

	return ret;
}

std::pair<unsigned, unsigned> UserWrap::GetCost(unsigned nStartTime, unsigned nEndTime) const
{
	if (m_bBase)
	{
		throw std::runtime_error("UserWrap::GetCostDiamond_Need_user_full_data");
	}

	if (nStartTime > nEndTime)
	{
		throw std::runtime_error("UserWrap::GetCostDiamond_invalid_time_period");
	}

	Json::Reader reader;
	Json::FastWriter write;
	Json::Value user_flag;
	reader.parse(m_dataUser.user_flag, user_flag);

	if (!user_flag.isMember("user_pay"))
	{
		return std::make_pair(0, 0);
	}

	unsigned size = user_flag["user_pay"].size();
	unsigned nTotalCash = 0;
	unsigned nTotalCoins = 0;
	for(int i = 0; i < size; ++i)
	{
		unsigned ts  = user_flag["user_pay"][i][0u].asUInt();
		if (ts >= nStartTime && ts <= nEndTime)
		{
			nTotalCash += user_flag["user_pay"][i][1u].asUInt();
			nTotalCoins += user_flag["user_pay"][i][2u].asUInt();
		}
	}

	return std::make_pair(nTotalCash, nTotalCoins);
}

int UserWrap::GetRechargePoint(const ActInfoConfig& config) const
{
	return GetRechargePoint(config.StartTS(), config.EndTS());
}

unsigned UserWrap::GetRechargePoint(unsigned nStartTime, unsigned nEndTime) const
{
	if (m_bBase)
	{
		throw std::runtime_error("UserWrap::GetRechargePoint_Need_user_full_data");
	}

	if (nStartTime >= nEndTime)
	{
		throw std::runtime_error("UserWrap::GetRechargePoint_invalid_time_period");
	}

	Json::Reader reader;
	Json::FastWriter write;
	Json::Value user_flag;
	reader.parse(m_dataUser.user_flag, user_flag);

	if (!user_flag.isMember("chgs"))
	{
		return 0;
	}

	if (!user_flag["chgs"].isArray())
	{
		error_log("chgs error");
		throw std::runtime_error("chgs_error");
	}

	unsigned size = user_flag["chgs"].size();
	unsigned chargeTotal = 0;
	for (unsigned i = 0; i < size; ++i)
	{
		unsigned ts  = user_flag["chgs"][i][0u].asUInt();
		if(ts >= nStartTime && ts <= nEndTime)
		{
			chargeTotal += user_flag["chgs"][i][1u].asUInt();
		}
	}

	return chargeTotal;
}

bool UserWrap::IsHaveRechargeGoal(unsigned nStartTime, unsigned nEndTime, unsigned goal)
{
	if (m_bBase)
	{
		throw std::runtime_error("Need_user_full_data");
	}

	if (nStartTime >= nEndTime)
	{
		throw std::runtime_error("invalid_time_period");
	}

	Json::Reader reader;
	Json::FastWriter write;
	Json::Value user_flag;
	reader.parse(m_dataUser.user_flag, user_flag);

	if (!user_flag.isMember("chgs"))
	{
		return false;
	}

	if (!user_flag["chgs"].isArray())
	{
		error_log("chgs error");
		throw std::runtime_error("chgs_error");
	}

	unsigned size = user_flag["chgs"].size();

	for (unsigned i = 0; i < size; ++i)
	{
		unsigned ts  = user_flag["chgs"][i][0u].asUInt();

		if(ts >= nStartTime && ts <= nEndTime && user_flag["chgs"][i][1u].asUInt() >= goal)
		{
			return true;
		}
	}

	return false;
}

unsigned UserWrap::GetRechargeGoalDays(unsigned nStartTime, unsigned nEndTime, unsigned goal)
{
	if (m_bBase)
	{
		throw std::runtime_error("Need_user_full_data");
	}

	if (nStartTime >= nEndTime)
	{
		throw std::runtime_error("invalid_time_period");
	}

	Json::Reader reader;
	Json::FastWriter write;
	Json::Value user_flag;
	reader.parse(m_dataUser.user_flag, user_flag);

	if (!user_flag.isMember("chgs"))
	{
		return 0;
	}

	if (!user_flag["chgs"].isArray())
	{
		error_log("chgs error");
		throw std::runtime_error("chgs_error");
	}

	unsigned size = user_flag["chgs"].size();
	unsigned days = 0;

	for (unsigned i = 0; i < size; ++i)
	{
		unsigned ts  = user_flag["chgs"][i][0u].asUInt();

		if(ts >= nStartTime && ts <= nEndTime && user_flag["chgs"][i][1u].asUInt() >= goal)
		{
			days++;
		}
	}

	return days;
}

unsigned UserWrap::GetSingleDayRecharge(unsigned day) const
{
	if (m_bBase)
	{
		throw std::runtime_error("get_user_charge_error");
	}

	Json::Reader reader;
	Json::Value user_flag;

	reader.parse(m_dataUser.user_flag, user_flag);

	if (!user_flag.isMember("chgs"))
	{
		return 0;
	}

	if (!user_flag["chgs"].isArray())
	{
		error_log("chgs error");
		throw std::runtime_error("chgs_error");
	}

	unsigned chagval = 0;

	for(unsigned i = user_flag["chgs"].size(); i > 0; --i)   //倒序遍历
	{
		if (!CTime::IsDiffDay(user_flag["chgs"][i-1][0u].asUInt(), day))  //同天
		{
			chagval = user_flag["chgs"][i-1][1u].asUInt();
			break;
		}
	}

	return chagval;
}

unsigned UserWrap::GetSingleDayConsume(unsigned day) const
{
	if (m_bBase)
	{
		throw std::runtime_error("UserWrap::GetCostDiamond_Need_user_full_data");
	}

	Json::Reader reader;
	Json::FastWriter write;
	Json::Value user_flag;
	reader.parse(m_dataUser.user_flag, user_flag);

	if (!user_flag.isMember("user_pay"))
	{
		return 0;
	}

	unsigned size = user_flag["user_pay"].size();
	unsigned costval = 0;  //消耗的钻石

	for(int i = 0; i < size; ++i)
	{
		unsigned ts  = user_flag["user_pay"][i][0u].asUInt();

		if (!CTime::IsDiffDay(ts, day))  //同天
		{
			costval = user_flag["user_pay"][i][1u].asUInt();
			break;
		}
	}

	return costval;
}

void UserWrap::AddProsper(int prosper, const std::string& reason, Json::Value& result)
{
	if (prosper < 0)
	{
		throw std::runtime_error("prosper_error");
	}

	if (prosper == 0)
	{
		return ;
	}

	m_dataUser.prosper += prosper;
	result["prosper"] = m_dataUser.prosper;

	RESOURCE_LOG("[AddProsper][uid=%u,chgprosper=%u,prosper=%u,code=%s]"
										,m_nUid, prosper, m_dataUser.prosper, reason.c_str());

}

void UserWrap::AddExp(int exp, const std::string& reason, Json::Value& result)
{
	int tempexp = exp + m_dataUser.point;
	if (tempexp < 0)
	{
		error_log("%u add %d exp error", m_nUid, exp);
		throw std::runtime_error("add_exp_params_error");
	}

	m_dataUser.point += exp;

	int leveltemp = 1;
	//更新用户level数据
	int levelSize = (int)(sizeof(user_lvl_exp) / sizeof(user_lvl_exp[0]));
	if (m_dataUser.point >=  user_lvl_exp[levelSize - 1])
	{
		leveltemp = levelSize;
	}
	else
	{
		for (int i = m_dataUser.level; i < levelSize; i++)
		{
			if (m_dataUser.point < (uint64_t)user_lvl_exp[i])
			{
				leveltemp = i;
				break;
			}
		}
	}
	if(m_dataUser.level != leveltemp)
	{
		USER_LEVEL_LOG("uid=%u,l=%u",m_dataUser.uid,leveltemp);
		m_dataUser.level = leveltemp;
	}

	result["exp"] = Convert::Int64ToString(m_dataUser.point);
	result["level"] = m_dataUser.level;

	RESOURCE_LOG("[AddExp][uid=%u,expchg=%d,exp=%u,code=%s]"
										,m_nUid, exp, m_dataUser.point, reason.c_str());
}

int UserWrap::CostAsset(int diamond, int coins, const std::string& reason, Json::Value& result)
{
	if (diamond < 0 || coins < 0 || (diamond == 0 && coins == 0))
	{
		error_log("[CostAsset] param error,uid=%u. cash=%d, coin=%d", m_nUid, diamond, coins);
		throw std::runtime_error("UserWrap::CostAsset_params_error");
	}

	int ret = 0;
	Json::Value user_flag;
	if (m_bBase)
	{
		//throw std::runtime_error("UserWrap::CostAsset_Need_user_full_data");
		CLogicUser logicUser;
		if (R_SUCCESS  != logicUser.GetUserFlag(m_nUid, user_flag))
		{
			throw std::runtime_error("UserWrap::CostAsset_get_user_flag_error");
		}
	}
	else
	{
		if (m_dataUser.user_flag.empty())
		{
			m_dataUser.user_flag = "{}";
		}

		if (! Json::FromString(user_flag, m_dataUser.user_flag))
		{
			error_log("[get_user_flag_error,uid=%u]", m_nUid);
			throw std::runtime_error("get_user_flag_error");
		}
	}

	bool bsave = false;
	CLogicPay logicPay;
	DataPay payData;
	ret = logicPay.ProcessOrderForBackend(
			m_nUid, -diamond, -coins, payData,
			reason,
			user_flag, bsave);
	if(ret != R_SUCCESS)
	{
		throw std::runtime_error("UserWrap::CostAsset_failed");
	}

	if(bsave)
	{
		result["pointpay"].resize(0);
		result["pointpay"] = user_flag["user_pay"];

		if (m_bBase)
		{
			CLogicUser logicUser;
			if (R_SUCCESS  != logicUser.SetUserFlag(m_nUid, user_flag))
			{
				throw std::runtime_error("UserWrap::CostAsset_save_user_flag_error");
			}
		}
		else
		{
			m_dataUser.user_flag = Json::ToString(user_flag);
		}
	}

	result["coins"] = payData.coins;
	result["coins2"] = payData.cash;

	return R_SUCCESS;
}

void UserWrap::AddCashCoin(int cashs, int coins, const std::string& reason, Json::Value& result)
{
	if (cashs < 0 || coins < 0 || (cashs == 0 && coins == 0))
	{
		error_log("[AddCashCoin] param error,uid=%u. cash=%d, coin=%d", m_nUid, cashs, coins);
		throw std::runtime_error("cash_coin_param_error");
	}

	int ret = 0;

	CLogicPay logicPay;
	DataPay   dataPay;
	ret = logicPay.ChangePay(m_nUid, cashs, coins, reason, dataPay);

	if (ret)
	{
		throw std::runtime_error("add_cashcoin_failed");
	}

	result["coins"] = dataPay.coins;
	result["coins2"] = dataPay.cash;
}

void UserWrap::AddGCBase(unsigned cnt, const std::string& reason, Json::Value& result)
{
	m_dataUser.gcbase += cnt;
	if (m_dataUser.gcbase > 1000)
	{
		m_dataUser.gcbase = 1000;
	}

	result["gcbase"] =  m_dataUser.gcbase;

	RESOURCE_LOG("[AddGCBase][uid=%u,gcbasechg=%u,gcbase=%u,code=%s]"
										,m_nUid, cnt, m_dataUser.gcbase, reason.c_str());
}

void UserWrap::AddResourceUniform(unsigned resource, const std::string& reason, Json::Value& result)
{
	AddResource(resource, resource, resource, resource, reason, result);
}

void UserWrap::AddResource(unsigned r1, unsigned r2, unsigned r3, unsigned r4
		, const std::string& reason, Json::Value& result)
{
	if ((r1 + r2 + r3 + r4) == 0)
	{
		return ;
	}

	m_dataUser.r1 +=  r1;
	if(m_dataUser.r1 > m_dataUser.r1_max)
	{
		m_dataUser.r1 = m_dataUser.r1_max;
	}

	m_dataUser.r2 +=  r2;
	if(m_dataUser.r2 > m_dataUser.r2_max)
	{
		m_dataUser.r2 = m_dataUser.r2_max;
	}

	m_dataUser.r3 +=  r3;
	if(m_dataUser.r3 > m_dataUser.r3_max)
	{
		m_dataUser.r3 = m_dataUser.r3_max;
	}

	m_dataUser.r4 +=  r4;
	if(m_dataUser.r4 > m_dataUser.r4_max)
	{
		m_dataUser.r4 = m_dataUser.r4_max;
	}

	RESOURCE_LOG("[%s][uid=%u, chgr1=%u,r1=%u,chgr2=%u,r2=%u,chgr3=%u,r3=%u,chgr4=%u,r4=%u]"
					, reason.c_str(), m_nUid
					, r1, m_dataUser.r1
					, r2, m_dataUser.r2
					, r3, m_dataUser.r3
					, r4, m_dataUser.r4);

	result["r1"] = m_dataUser.r1;
	result["r2"] = m_dataUser.r2;
	result["r3"] = m_dataUser.r3;
	result["r4"] = m_dataUser.r4;
}

void UserWrap::GetResource(map<unsigned, unsigned> & resource)
{
	resource.clear();

	resource[resource_rice] = m_dataUser.r1;
	resource[resource_stone] = m_dataUser.r2;
	resource[resource_wood] = m_dataUser.r3;
	resource[resource_iron] = m_dataUser.r4;
}

void UserWrap::GetResourceMax(map<unsigned, unsigned> & resourcemax)
{
	resourcemax.clear();

	resourcemax[resource_rice] = m_dataUser.r1_max;
	resourcemax[resource_stone] = m_dataUser.r2_max;
	resourcemax[resource_wood] = m_dataUser.r3_max;
	resourcemax[resource_iron] = m_dataUser.r4_max;
}

void UserWrap::GetUserBuildQ(Json::Value & buildq)
{
	if (m_bBase)
	{
		throw std::runtime_error("get_user_buildq_error");
	}
	Json::Reader().parse(m_dataUser.buildQ, buildq);
}

void UserWrap::SetUserBuildQ(Json::Value & buildq)
{
	if (m_bBase)
	{
		throw std::runtime_error("set_user_buildq_error");
	}
	m_dataUser.buildQ = Json::FastWriter().write(buildq);
}
