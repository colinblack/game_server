/*
 * LogicPay.cpp
 *
 *  Created on: 2011-7-11
 *      Author: dada
 */

#include "LogicPay.h"

int CLogicPay::AddUser(unsigned uid, unsigned cash)
{
	CDataPay dbPay;
	int ret = dbPay.AddPay(uid, cash);
	if(ret != 0)
	{
		fatal_log("[AddPay fail][ret=%d,uid=%u,cash=%u]", ret, uid, cash);
		DB_ERROR_RETURN_MSG("add_pay_fail");
	}
	return 0;
}

int CLogicPay::GetCash(unsigned uid, unsigned &cash)
{
	CDataPay dbPay;
	int ret = dbPay.GetPay(uid, cash);
	if(ret != 0)
	{
		if(ret != R_ERR_NO_DATA || !IsAllianceId(uid))
		{
			error_log("[GetPay fail][ret=%d,uid=%u]", ret, uid);
		}
		if(ret == R_ERR_NO_DATA)
		{
			ERROR_RETURN_MSG(R_ERR_NO_DATA, "no_pay_data");
		}
		DB_ERROR_RETURN_MSG("get_pay_fail");
	}
	return 0;
}

int CLogicPay::ChangeCash(unsigned uid, const string &type, int cash, int count, unsigned data, unsigned &balance)
{
	int ret;
	ret = GetCash(uid, balance);
	if(ret != 0)
	{
		return ret;
	}
	if(cash < 0 && (unsigned)(-cash) > balance)
	{
		error_log("[pay overspend][uid=%u,type=%s,cash=%u,delta=%d]", uid, type.c_str(), balance, cash);
		ERROR_RETURN_MSG(R_ERR_DATA_LIMIT, "pay_overspend");
	}
	balance += cash;
	CDataPay dbPay;
	ret = dbPay.SetPay(uid, balance);
	if(ret != 0)
	{
		error_log("[SetPay fail][ret=%d,uid=%u,type=%s,cash=%u]", ret, uid, type.c_str(), balance);
		DB_ERROR_RETURN_MSG("set_pay_fail");
	}
	if(count < 0)
	{
		count = -count;
	}
	DATA_INFO_LOG("purchase", "uid=%u&item=%s&count=%d&cash=%d&data=%u&balance=%u",
			uid, type.c_str(), count, cash, data, balance);
	DataCashFlow cashFlow;
	cashFlow.uid = uid;
	cashFlow.type = type;
	cashFlow.count = count;
	cashFlow.cash = cash;
	cashFlow.balance = balance;
	cashFlow.data = data;
	ret = AddCashFlow(cashFlow);
	return 0;
}

int CLogicPay::BuyCash(unsigned uid, int cash, int credit)
{
	int ret;
	unsigned balance;
	ret = ChangeCash(uid, "PAY", cash, credit, 0, balance);
	if(ret != 0)
	{
		return ret;
	}
	OnPay(uid, cash, credit);
	return 0;
}

int CLogicPay::ChangeCash(unsigned uid, const string &type, int cash, int count)
{
	unsigned balance;
	return ChangeCash(uid, type, cash, count, 0, balance);
}

int CLogicPay::AddPayHistory(DataPayHistory &payHistory)
{
	int ret;
	payHistory.time = Time::GetGlobalTime();
	//payHistory.pay_id = (uint64_t)payHistory.uid * 10000000000ULL + payHistory.time;
	CLogicIdCtrl logicIdCtrl;
	CDataPayHistory dbPayHistory;
	for(int i = 0; i < 3; i++)
	{
		uint64_t payId;
		ret = logicIdCtrl.GetNextId(KEY_PAY_ID_CTRL, payId);
		if(ret != 0)
		{
			error_log("[GetNextId fail][ret=%d,uid=%u,channel=%d,channel_pay_id=%s]",
					ret, payHistory.uid, payHistory.channel, payHistory.channel_pay_id.c_str());
			return ret;
		}
		payHistory.pay_id = payId;
		ret = dbPayHistory.AddPayHistory(payHistory);
		if(ret == 0)
		{
			return 0;
		}
		else if(ret != -DBCache::ER_DUP_ENTRY)
		{
			error_log("[AddPayHistory fail][ret=%d,uid=%u,payid=%llu,channel=%d,channel_pay_id=%s,type=%d,count=%d,credit=%d]",
					ret, payHistory.uid, payHistory.pay_id, payHistory.channel, payHistory.channel_pay_id.c_str(),
					payHistory.type, payHistory.count, payHistory.credit);
			DB_ERROR_RETURN_MSG("add_pay_history_fail");
		}
	}
	error_log("[AddPayHistory fail][ret=%d,uid=%u,payid=%llu,channel=%d,channel_pay_id=%s,type=%d,count=%d,credit=%d]",
			ret, payHistory.uid, payHistory.pay_id, payHistory.channel, payHistory.channel_pay_id.c_str(),
			payHistory.type, payHistory.count, payHistory.credit);
	DB_ERROR_RETURN_MSG("add_pay_history_fail");
}

int CLogicPay::GetPayHistory(unsigned uid, uint64_t payId, DataPayHistory &payHistory)
{
	CDataPayHistory dbPayHistory;
	int ret = dbPayHistory.GetPayHistory(uid, payId, payHistory);
	if(ret != 0)
	{
		error_log("[GetPayHistory fail][ret=%d,uid=%u,payid=%llu]", ret, uid, payId);
		DB_ERROR_RETURN_MSG("get_pay_history_fail");
	}
	return ret;
}

int CLogicPay::GetPayHistory(unsigned uid, PayChannelType channel, const string &channelPayId, DataPayHistory &payHistory)
{
	CDataPayHistory dbPayHistory;
	int ret = dbPayHistory.GetPayHistory(uid, channel, channelPayId, payHistory);
	if(ret != 0)
	{
		error_log("[GetPayHistory fail][ret=%d,uid=%u,channel=%d,channel_pay_id=%s]",
				ret, uid, channel, channelPayId.c_str());
		DB_ERROR_RETURN_MSG("get_pay_history_fail");
	}
	return ret;
}

int CLogicPay::SetPayHistory(unsigned uid, uint64_t payId, const DataPayHistory &payHistory)
{
	CDataPayHistory dbPayHistory;
	int ret = dbPayHistory.SetPayHistory(uid, payId, payHistory);
	if(ret != 0)
	{
		error_log("[SetPayHistory fail][ret=%d,uid=%u,payid=%llu]", ret, uid, payId);
		DB_ERROR_RETURN_MSG("set_pay_history_fail");
	}
	return ret;
}

int CLogicPay::SetPayHistoryStatus(unsigned uid, uint64_t payId, PayStatusType status)
{
	CDataPayHistory dbPayHistory;
	int ret = dbPayHistory.SetPayHistoryStatus(uid, payId, status);
	if(ret != 0)
	{
		error_log("[SetPayHistoryStatus fail][ret=%d,uid=%u,payId=%llu,status=%d]",
				ret, uid, payId, status);
		DB_ERROR_RETURN_MSG("set_pay_status_fail");
	}
	return ret;
}

int CLogicPay::SetPayHistoryStatus(unsigned uid, PayChannelType channel, const string &channelPayId, PayStatusType status)
{
	CDataPayHistory dbPayHistory;
	int ret = dbPayHistory.SetPayHistoryStatus(uid, channel, channelPayId, status);
	if(ret != 0)
	{
		error_log("[SetPayHistoryStatus fail][ret=%d,uid=%u,channel=%d,channelPayId=%s,,status=%d]",
				ret, uid, channel, channelPayId.c_str(), status);
		DB_ERROR_RETURN_MSG("set_pay_status_fail");
	}
	return ret;
}

int CLogicPay::AddCashFlow(DataCashFlow &flow)
{
	int ret;
	CLogicIdCtrl logicIdCtrl;
	CDataCashFlow dbCashFlow;
	flow.time = Time::GetGlobalTime();
	for(int i = 0; i < 3; i++)
	{
		ret = logicIdCtrl.GetNextId(KEY_CASH_FLOW_ID_CTRL, flow.flow_id);
		if(ret != 0)
		{
			error_log("[GetNextId fail][ret=%d,uid=%u,type=%s,cash=%d]",
					ret, flow.uid, flow.type.c_str(), flow.cash);
			return ret;
		}
		ret = dbCashFlow.AddCashFlow(flow);
		if(ret == 0)
		{
			return 0;
		}
		else if(ret != -DBCache::ER_DUP_ENTRY)
		{
			error_log("[AddCashFlow fail][ret=%d,uid=%u,flowid=%llu,type=%s,cash=%d]",
					ret, flow.uid, flow.flow_id, flow.type.c_str(), flow.cash);
			DB_ERROR_RETURN_MSG("add_cash_flow_fail");
		}
	}
	error_log("[AddCashFlow fail][ret=%d,uid=%u,flowid=%llu,type=%s,cash=%d]",
			ret, flow.uid, flow.flow_id, flow.type.c_str(), flow.cash);
	DB_ERROR_RETURN_MSG("add_cash_flow_fail");
	return ret;
}

int CLogicPay::GetCashFlows(unsigned uid, unsigned startTime, unsigned endTime, vector<DataCashFlow> &flows)
{
	int ret;
	CDataCashFlow dbCashFlow;
	ret = dbCashFlow.GetCashFlows(uid, startTime, endTime, flows);
	if(ret != 0)
	{
		error_log("[GetCashFlows fail][ret=%d,uid=%d,start=%u,end=%u]", ret, uid, startTime, endTime);
		DB_ERROR_RETURN_MSG("get_cash_flow_fail");
	}
	return 0;
}

int CLogicPay::OnPay(unsigned uid, int cash, int credit)
{
	int ret;
	if(cash == 0)
	{
		return 0;
	}
	DataBase base;
	ret = LogicBase::GetBase(uid, MAIN_BASE_ID, base);
	if(ret != 0)
	{
		return ret;
	}
	unsigned baseid = base.baseid;
	string sConsume;
	CDataBaseExtra dbBaseExtra;
	ret = dbBaseExtra.GetConsume(baseid, sConsume);
	if(ret != 0)
	{
		error_log("[GetConsume fail][ret=%d,baseid=%u]", ret, baseid);
		DB_ERROR_RETURN_MSG("get_base_extra_fail");
	}
	Json::Value storedata;
	if(!Json::FromString(storedata, sConsume))
	{
		error_log("[base_data_error][uid=%u,baseid=%u]", uid, baseid);
		DATA_ERROR_RETURN_MSG("base_data_error");
	}
	int lastCount = 0;
	if(storedata.type() != Json::objectValue)
	{
		storedata = Json::Value(Json::objectValue);
	}
	if(Json::IsObject(storedata, "PAY"))
	{
		Json::GetInt(storedata["PAY"], "q", lastCount);
	}
	storedata["PAY"]["q"] = lastCount + cash;
	ret = dbBaseExtra.SetConsume(baseid, Json::ToString(storedata));
	if(ret != 0)
	{
		error_log("[SetConsume fail][ret=%d,baseid=%u]", ret, baseid);
		DB_ERROR_RETURN_MSG("set_base_extra_fail");
	}
	return 0;
}
