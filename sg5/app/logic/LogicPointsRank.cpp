/*
 * LogicPointRank.cpp
 *
 *  Created on: 2012-10-17
 *      Author: Administrator
 */

#include "LogicPointsRank.h"

/*************砸罐活动********************************/
CLogicPointsRank::CLogicPointsRank() {
	// TODO Auto-generated constructor stub

}

CLogicPointsRank::~CLogicPointsRank() {
	// TODO Auto-generated destructor stub
}

CDataPointsRank* CLogicPointsRank::GetPointsRankData()
{
	GET_MEM_DATA_SEM(CDataPointsRank, POINTS_RANK, sem_pointsrank,false)
	/*static CDataPointsRank *pdata = NULL;
	if(pdata == NULL)
	{
		pdata = new CDataPointsRank();
	}
	if(pdata->Init(Config::GetValue(POINTS_RANK)))
	{
		delete pdata;
		pdata = NULL;
	}
	return pdata;*/
}
int CLogicPointsRank::GetPointsRank(int unsigned uid, DataPoints vecPoints[])
{
	CDataPointsRank *pdata= GetPointsRankData();
	if(pdata == NULL)
	{
		DB_ERROR_RETURN_MSG("init_pointsrank_fail");
	}
	int ret = pdata->GetRankList(vecPoints);
	if(ret != 0)
	{
		return ret;
	}
	return 0;
}
int CLogicPointsRank::GetPointsRankJson(int unsigned uid, Json::Value &result)
{
	int ret = 0;
	// vector<DataPoints> vecPoints;
	DataPoints vecPoints[RANK_SIZE];
	ret = GetPointsRank(uid,vecPoints);
	if(ret != 0)
	{
			return ret;
	}
	int iCount = RANK_SIZE;
	//int iCount = vecPoints.size();
	for(int i = 0; i < iCount; i++)
	{
		result[i]["uid"] = vecPoints[i].uid;
		result[i]["points"] = vecPoints[i].points;
		result[i]["name"] = string(vecPoints[i].name);
	}
	RewardPointRank();
	return 0;
}

int CLogicPointsRank::UpdatePointsRank(int unsigned uid, const DataPoints &points)
{
	// 活动到期，不更新排行榜
	//info_log("points record uid=%u,points = %d",points.uid, points.points);
	if(!(  Time::GetGlobalTime() >=Config::GetIntValue(CONFIG_POINTS_BEGIN_TS)
		&& Time::GetGlobalTime() + 4*60*60 <= Config::GetIntValue(CONFIG_POINTS_END_TS)))
	{
		return R_ERR_REFUSE;
	}
	CDataPointsRank *pdata= GetPointsRankData();
	if(pdata == NULL)
	{
		DB_ERROR_RETURN_MSG("init_pointsrank_fail");
	}

	int ret = pdata->UpdateRankList(points);
	if(ret != 0)
	{
		return ret;
	}
	return 0;
}

int CLogicPointsRank::RewardPointRank(void)
{
	//活动未结束，不需发奖励
	if(    Time::GetGlobalTime() >=Config::GetIntValue(CONFIG_POINTS_BEGIN_TS)
		&& Time::GetGlobalTime()+4*60*60 <= Config::GetIntValue(CONFIG_POINTS_END_TS))
	{
		return R_ERR_REFUSE;
	}

	int ret = 0;
	DataPoints pointList[RANK_SIZE];
	CDataPointsRank *pdata= GetPointsRankData();
	if(pdata == NULL)
	{
		DB_ERROR_RETURN_MSG("init_pointsrank_fail");
	}

	ret = pdata->GetRankList(pointList);
	if(ret != 0)
	{
		return ret;
	}

	Json::Value updateJson = Json::Value(Json::arrayValue);
	updateJson.resize(1);
	CLogicUpdates logiceUpdates;
	for (int i=0; i<5; i++)
	{
		if (!IsValidUid(pointList[i].uid))
		{
			//error_log("[invalid uid][uid=%u]", pointList[i].uid);
			continue;
		}
		if (pointList[i].reward == 1)
		{
			//error_log("[allready had reward][uid=%u]", pointList[i].uid);
			continue;
		}
		ret = pdata->SetReward(pointList[i].uid, 1);
		if (0 != ret)
		{
			error_log("[set reward flag fail][ret=%d,uid=%u]", ret, pointList[i].uid);
			continue;
		}
		if (pointList[i].points < 500)
			continue;

		updateJson[(unsigned)0]["uid"] = pointList[i].uid;
		updateJson[(unsigned)0]["s"] = "activitypointrank";
		updateJson[(unsigned)0]["rank"] = i+1;
		updateJson[(unsigned)0]["ts"] = Time::GetGlobalTime();
		updateJson[(unsigned)0]["points"] = pointList[i].points;
		ret = logiceUpdates.AddUpdates(pointList[i].uid, updateJson,true);
		if (0 != ret)
		{
			//debug_log("[Add updates fail][ret=%d,uid=%u]", ret, pointList[i].uid);
			error_log("[Add updates fail][ret=%d,uid=%u]", ret, pointList[i].uid);
		}
		Json::FastWriter writer;
		info_log("pointrnak rewar,updates=%s", writer.write(updateJson).c_str());
	}
	return 0;
}

int CLogicPointsRank::CleanRankList(void)
{
	CDataPointsRank *pdata= GetPointsRankData();
	if(pdata == NULL)
	{
		DB_ERROR_RETURN_MSG("init_pointsrank_fail");
	}
	return pdata->CleanRankList();
}
/***********************************************/

/************跨服砸罐活动***************************/
CDataPointsRankAllServer* CLogicPointsRank::GetPointsRankAllServerData()
{
	GET_MEM_DATA_SEM(CDataPointsRankAllServer, POINTS_RANK_ALL_SERVER, sem_pointsrankallserver,true)
}

int CLogicPointsRank::SetUser(int unsigned uid, unsigned pointsDay, unsigned pointsAll, string& name, unsigned& need)
{
	Json::Value data;
	data["uid"] = uid;
	data["pointsDay"] = pointsDay;
	data["pointsAll"] = pointsAll;
	data["name"] = name;
	string url = "action=setPointsUser";
	string datastr = Json::ToString(data);
	url.append("&data=").append(Crypt::UrlEncode(datastr));

	CLogicAllServerBaseMatch logicBaseMatch;
	Json::Value result;
	int ret = logicBaseMatch.RequestBaseMatch(url,result,CONFIG_ALLS_MATCH_SERVER_PATH,true);
	if(ret)
		return ret;
	Json::GetUInt(result["setPointsUser"],"need",need);
	return 0;

	return R_SUCCESS;
}

int CLogicPointsRank::ReplyUser(unsigned uid, unsigned pointsDay, unsigned pointsAll, string& name, Json::Value &result)
{
	int ret = 0;
	if(Time::GetGlobalTime() < Config::GetIntValue(CONFIG_HAMMERHIT_ALLSERVER_BEGIN_TS)
	|| Time::GetGlobalTime() > Config::GetIntValue(CONFIG_HAMMERHIT_ALLSERVER_END_TS))
		return R_ERR_LOGIC;

	CDataPointsRankAllServer *pData = GetPointsRankAllServerData();
	if (NULL == pData)
	{
		error_log("GetDataPointsRankAllServer fail");
		return R_ERR_DATA;
	}

	unsigned need = 0;
	ret = pData->UpdateRankList(uid, pointsDay, pointsAll, name, need);
	if(ret)
		return ret;

	result["need"] = need;

	return R_SUCCESS;
}

int CLogicPointsRank::GetList(unsigned uid, Json::Value &result)
{
	unsigned now = Time::GetGlobalTime();
	if(now >= Config::GetIntValue(CONFIG_HAMMERHIT_ALLSERVER_BEGIN_TS)
	&& now <= Config::GetIntValue(CONFIG_HAMMERHIT_ALLSERVER_END_TS))
	{
		string url = "action=getPointsRanklist&uid=";
		url.append(Convert::UIntToString(uid));
		CLogicAllServerBaseMatch logicBaseMatch;
		int ret = logicBaseMatch.RequestBaseMatch(url,result,CONFIG_ALLS_MATCH_SERVER_PATH,true);
		if(ret)
			return ret;

		unsigned dayTotal = 0, allTotal = 0;
		CLogicSecinc logicSec;
		Json::Value newAct;
		ret = logicSec.GetSecinc(uid, NAT_HAMMERHIT_ALLSERVER, newAct);
		if (ret == R_ERR_NO_DATA)
		{
			dayTotal = 0;
			allTotal = 0;
		}
		else if (ret == 0)
		{
			if (newAct["v"].asUInt() != Config::GetIntValue(CONFIG_HAMMERHIT_ALLSERVER_VER))
			{
				dayTotal = 0;
				allTotal = 0;
			}
			else if (CTime::IsDiffDay(newAct["p"][0u].asUInt(), now))
			{
				dayTotal = 0;
				allTotal = newAct["pa"].asUInt();
			}
			else
			{
				dayTotal = newAct["p"][1u].asUInt();
				allTotal = newAct["pa"].asUInt();
			}
		}
		else if (ret)
		{
			return ret;
		}

		result["dayTotal"] = dayTotal;
		result["allTotal"] = allTotal;
		return 0;
	}

	return R_SUCCESS;
}

int CLogicPointsRank::ReplyList(unsigned uid, Json::Value &result)
{
	int ret = 0;
	if(Time::GetGlobalTime() < Config::GetIntValue(CONFIG_HAMMERHIT_ALLSERVER_BEGIN_TS)
	|| Time::GetGlobalTime() > Config::GetIntValue(CONFIG_HAMMERHIT_ALLSERVER_END_TS))
		return R_ERR_LOGIC;

	CDataPointsRankAllServer *pData = GetPointsRankAllServerData();
	if (NULL == pData)
	{
		error_log("GetDataPointsRankAllServer fail");
		return R_ERR_DATA;
	}

	vector<PRUser> day, all;
	ret = pData->GetRankList(uid, day, all);
	if(ret)
		return ret;

	result["day"].resize(day.size());
	result["all"].resize(all.size());
	for(unsigned i=0;i<day.size();++i)
	{
		result["day"][i]["uid"] = day[i].uid;
		result["day"][i]["points"] = day[i].points;
		result["day"][i]["name"] = string(day[i].name);
	}
	for(unsigned i=0;i<all.size();++i)
	{
		result["all"][i]["uid"] = all[i].uid;
		result["all"][i]["points"] = all[i].points;
		result["all"][i]["name"] = string(all[i].name);
	}

	return R_SUCCESS;
}
/*******************************************************/
