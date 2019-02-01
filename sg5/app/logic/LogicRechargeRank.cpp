/*
 * LogicRechargeRank.cpp
 *
 *  Created on: 2015-7-28
 *      Author: eddard
 */


#include "LogicRechargeRank.h"

CLogicRechargeRank::CLogicRechargeRank(){
}

CDataRechargeRank* CLogicRechargeRank::GetDataRechargeRank(void)
{
	GET_MEM_DATA_SEM(CDataRechargeRank, CONFIG_RECHARGE_RANK_DIR, sem_recharge_rank, true)
}

int CLogicRechargeRank::GetList(unsigned uid, Json::Value &result)
{
	unsigned now = Time::GetGlobalTime();
	if(now >= Config::GetIntValue(CONFIG_ACTIVITY_RECHARGE_RANK_B_TS)
	&& now <= Config::GetIntValue(CONFIG_ACTIVITY_RECHARGE_RANK_E_TS))
	{
		string url = "action=getRechargeRanklist&uid=";
		url.append(Convert::UIntToString(uid));
		CLogicAllServerBaseMatch logicBaseMatch;
		int ret = logicBaseMatch.RequestBaseMatch(url,result,CONFIG_ALLS_MATCH_SERVER_PATH,true);
		if(ret)
			return ret;

		CLogicUser logicUser;
		Json::Value userFlag;
		ret = logicUser.GetUserFlag(uid, userFlag);
		if(ret)
			return ret;

		unsigned dayTotal = 0;
		unsigned allTotal = 0;
		if(userFlag.isMember("chgs"))
		{
			unsigned size = userFlag["chgs"].size();
			for(int i = 0; i < size; ++i)
			{
				unsigned ts  = userFlag["chgs"][i][0u].asUInt();
				if(!CTime::IsDiffDay(ts, now))
				{
					dayTotal = userFlag["chgs"][i][1u].asUInt();
				}

				if(ts >= Config::GetIntValue(CONFIG_ACTIVITY_RECHARGE_RANK_B_TS)
				&& ts <= Config::GetIntValue(CONFIG_ACTIVITY_RECHARGE_RANK_E_TS))
				{
					allTotal += userFlag["chgs"][i][1u].asUInt();
				}
			}
		}
		result["dayTotal"] = dayTotal;
		result["allTotal"] = allTotal;

		return 0;
	}

	return R_ERR_LOGIC;
}

int CLogicRechargeRank::SetUser(unsigned uid, unsigned cashDay, unsigned cashAll, string& name, unsigned& need)
{
	Json::Value data;
	data["uid"] = uid;
	data["cashDay"] = cashDay;
	data["cashAll"] = cashAll;
	data["name"] = name;
	string url = "action=setRechargeUser";
	string datastr = Json::ToString(data);
	url.append("&data=").append(Crypt::UrlEncode(datastr));

	CLogicAllServerBaseMatch logicBaseMatch;
	Json::Value result;
	int ret = logicBaseMatch.RequestBaseMatch(url,result,CONFIG_ALLS_MATCH_SERVER_PATH,true);
	if(ret)
		return ret;
	Json::GetUInt(result["setRechargeUser"],"need",need);
	return 0;
}


int CLogicRechargeRank::ReplyList(unsigned uid, Json::Value &result)
{
	int ret = 0;
	if(Time::GetGlobalTime() < Config::GetIntValue(CONFIG_ACTIVITY_RECHARGE_RANK_B_TS)
	|| Time::GetGlobalTime() > Config::GetIntValue(CONFIG_ACTIVITY_RECHARGE_RANK_E_TS))
		return R_ERR_LOGIC;

	CDataRechargeRank *pData = GetDataRechargeRank();
	if (NULL == pData)
	{
		error_log("GetDataRechargeRank fail");
		return R_ERR_DATA;
	}

	vector<RRUser> day, all;
	ret = pData->GetList(uid, day, all);
	if(ret)
		return ret;

	result["day"].resize(day.size());
	result["all"].resize(all.size());
	for(unsigned i=0;i<day.size();++i)
	{
		result["day"][i]["uid"] = day[i].uid;
		result["day"][i]["cash"] = day[i].cash;
		result["day"][i]["name"] = string(day[i].name);
	}
	for(unsigned i=0;i<all.size();++i)
	{
		result["all"][i]["uid"] = all[i].uid;
		result["all"][i]["cash"] = all[i].cash;
		result["all"][i]["name"] = string(all[i].name);
	}

	return 0;
}

int CLogicRechargeRank::ReplyUser(unsigned uid, unsigned cashDay, unsigned cashAll, string& name, Json::Value &result)
{
	int ret = 0;
	if(Time::GetGlobalTime() < Config::GetIntValue(CONFIG_ACTIVITY_RECHARGE_RANK_B_TS)
	|| Time::GetGlobalTime() > Config::GetIntValue(CONFIG_ACTIVITY_RECHARGE_RANK_E_TS))
		return R_ERR_LOGIC;

	CDataRechargeRank *pData = GetDataRechargeRank();
	if (NULL == pData)
	{
		error_log("GetDataRechargeRank fail");
		return R_ERR_DATA;
	}

	unsigned need = 0;
	ret = pData->SetUser(uid, cashDay, cashAll, name, need);
	if(ret)
		return ret;

	result["need"] = need;
	return 0;
}

