/*
 * LogicConsumeRank.cpp
 *
 *  Created on: 2015-2-2
 *      Author: Ralf
 */


#include "LogicConsumeRank.h"

CLogicConsumeRank::CLogicConsumeRank(){
}

CDataConsumeRank* CLogicConsumeRank::GetDataConsumeRank(void)
{
	GET_MEM_DATA_SEM(CDataConsumeRank, CONFIG_CONSUME_RANK_PATH, sem_consume_rank, true)
}

int CLogicConsumeRank::GetList(unsigned uid, Json::Value &result)
{
	unsigned now = Time::GetGlobalTime();
	if(now >= Config::GetIntValue(CONFIG_ACTIVITY_CONSUME_RANK_B_TS)
	&& now <= Config::GetIntValue(CONFIG_ACTIVITY_CONSUME_RANK_E_TS))
	{
		string url = "action=getconsumeranklist";
		CLogicAllServerBaseMatch logicBaseMatch;
		int ret = logicBaseMatch.RequestBaseMatch(url,result);
		if(ret)
			return ret;

		CLogicUser logicUser;
		Json::Value userFlag;
		ret = logicUser.GetUserFlag(uid, userFlag);
		if(ret)
			return ret;

		unsigned dayTotal = 0;
		unsigned allTotal = 0;
		if(userFlag.isMember("user_pay"))
		{
			unsigned size = userFlag["user_pay"].size();
			for(int i = 0; i < size; ++i)
			{
				unsigned ts  = userFlag["user_pay"][i][0u].asUInt();
				if(!CTime::IsDiffDay(ts, now))
				{
					dayTotal = userFlag["user_pay"][i][1u].asUInt();
				}

				if(ts >= Config::GetIntValue(CONFIG_ACTIVITY_CONSUME_RANK_B_TS)
				&& ts <= Config::GetIntValue(CONFIG_ACTIVITY_CONSUME_RANK_E_TS))
				{
					allTotal += userFlag["user_pay"][i][1u].asUInt();
				}
			}
		}
		result["dayTotal"] = dayTotal;
		result["allTotal"] = allTotal;

		return 0;
	}

	return R_ERR_LOGIC;
}

int CLogicConsumeRank::SetUser(unsigned uid, unsigned cashDay, unsigned cashAll, string& name, unsigned& need)
{
	Json::Value data;
	data["uid"] = uid;
	data["cashDay"] = cashDay;
	data["cashAll"] = cashAll;
	data["name"] = name;
	string url = "action=setconsumeuser";
	string datastr = Json::ToString(data);
	url.append("&data=").append(Crypt::UrlEncode(datastr));

	CLogicAllServerBaseMatch logicBaseMatch;
	Json::Value result;
	int ret = logicBaseMatch.RequestBaseMatch(url,result);
	if(ret)
		return ret;
	Json::GetUInt(result["setconsumeuser"],"need",need);
	return 0;
}


int CLogicConsumeRank::ReplyList(Json::Value &result)
{
	int ret = 0;
	if(Time::GetGlobalTime() < Config::GetIntValue(CONFIG_ACTIVITY_CONSUME_RANK_B_TS)
	|| Time::GetGlobalTime() > Config::GetIntValue(CONFIG_ACTIVITY_CONSUME_RANK_E_TS))
		return R_ERR_LOGIC;

	CDataConsumeRank *pData = GetDataConsumeRank();
	if (NULL == pData)
	{
		error_log("GetDataConsumeRank fail");
		return R_ERR_DATA;
	}

	vector<CRUser> day, all;
	ret = pData->GetList(day, all);
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

int CLogicConsumeRank::ReplyUser(unsigned uid, unsigned cashDay, unsigned cashAll, string& name, Json::Value &result)
{
	int ret = 0;
	if(Time::GetGlobalTime() < Config::GetIntValue(CONFIG_ACTIVITY_CONSUME_RANK_B_TS)
	|| Time::GetGlobalTime() > Config::GetIntValue(CONFIG_ACTIVITY_CONSUME_RANK_E_TS))
		return R_ERR_LOGIC;

	CDataConsumeRank *pData = GetDataConsumeRank();
	if (NULL == pData)
	{
		error_log("GetDataConsumeRank fail");
		return R_ERR_DATA;
	}

	unsigned need = 0;
	ret = pData->SetUser(uid, cashDay, cashAll, name, need);
	if(ret)
		return ret;

	result["need"] = need;
	return 0;
}

