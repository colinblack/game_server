
/*
 * LogicHundredDaysActivity.h
 *
 *  Created on: 2013-07-17
 *      Author: Administrator
 */

#include "LogicHundredDaysActivity.h"


CLogicHundredDaysActivityRank::CLogicHundredDaysActivityRank() {
	// TODO Auto-generated constructor stub

}

CLogicHundredDaysActivityRank::~CLogicHundredDaysActivityRank() {
	// TODO Auto-generated destructor stub
}

CDataHDaysAcvitityRank* CLogicHundredDaysActivityRank::GetHundredDaysActivityRankData()
{
	GET_MEM_DATA_SEM(CDataHDaysAcvitityRank, HUNDREDDAYSACTIVITY_RANK, sem_hundreddaysactivity,false)
}

int CLogicHundredDaysActivityRank::GetHundredDaysActivityRank(int unsigned uid, DataHDaysAcvitityPay vecPoints[])
{
	CDataHDaysAcvitityRank *pdata= GetHundredDaysActivityRankData();
	if(pdata == NULL)
	{
		DB_ERROR_RETURN_MSG("init_hundreddaysactivityrank_fail");
	}
	int ret = pdata->GetRankList(vecPoints);
	if(ret != 0)
	{
		return ret;
	}
	return 0;
}
int CLogicHundredDaysActivityRank::GetHundredDaysActivityRankJson(unsigned uid, Json::Value &result)
{
	time_t now;
	time(&now);

	CDataHDaysAcvitityRank *pdata= GetHundredDaysActivityRankData();
	if(pdata == NULL)
	{
		DB_ERROR_RETURN_MSG("init_hundreddaysactivityrank_fail");
	}

	DataHDaysAcvitityPay vecPoints[RANK_SIZE];
	int ret = GetHundredDaysActivityRank(uid,vecPoints);
	if(ret != 0)
	{
		return ret;
	}
	int iCount = RANK_SIZE;
	//int iCount = vecPoints.size();
	//前十名积分
	for(int i = 0; i < iCount; i++)
	{

		result[i]["uid"] = vecPoints[i].uid;
		result[i]["pay"] = vecPoints[i].pay;
		result[i]["name"] = string(vecPoints[i].name);
	}

	//自己积分
	Json::Value userFlag;
	CLogicUser logicUser;
	ret = logicUser.GetUserFlag(uid,userFlag);
	if(ret)
		return ret;

	result[10]["uid"] = uid;
	unsigned payTotal = 0;
	if(userFlag.isMember("user_pay"))
	{
		unsigned size = userFlag["user_pay"].size();
		for(int i = 0; i < size; ++i)
		{
			unsigned ts  = userFlag["user_pay"][i][0u].asUInt();
			if(!CTime::IsDiffDay(ts, now))
			{
				payTotal = userFlag["user_pay"][i][1u].asUInt();
				break;
			}
		}
	}
	result[10]["pay"] = payTotal;


    //发奖
	vector <UpdatesHundDays> data;
	Json::Value updateJson;
	updateJson.resize(1);
	ret = pdata->RewardHundredDaysActivityRank(data);
	if(ret != 0)
	{
		return ret;
	}

	if(data.size() > 0)
	{
		for(int i = 0; i < 5; i++)
		{
			CLogicUpdates logiceUpdates;
			updateJson[(unsigned)0]["uid"] = data[i].uid;
			updateJson[(unsigned)0]["s"] = "IntegralRank";
			updateJson[(unsigned)0]["rank"] = i+1;
			updateJson[(unsigned)0]["ts"] = Time::GetGlobalTime();
			updateJson[(unsigned)0]["pay"] = data[i].pay;

			if(data[i].uid != 0)
			{
				ret = logiceUpdates.AddUpdates(data[i].uid, updateJson,true);
				if (0 != ret)
				{
					error_log("[Add updates fail][ret=%d,uid=%u]", ret, data[i].uid);
				}
				Json::FastWriter writer;
				info_log("hundreddays reward,updates=%s", writer.write(updateJson).c_str());

				/*
				string texT = "感谢您参加乐不思蜀活动，您共获得";
				unsigned int rrr = i +1;
				texT.append(CTrans::ITOS(data[i].pay)).append("积分，排名第");
				texT.append(CTrans::ITOS(rrr)).append(",本次乐不思蜀活动奖励已发放，请查收！");

				DataEmail email;
				CLogicEmail logicEmail;
				vector<uint64_t> toUidList;
				toUidList.push_back(data[i].uid);
				email.attach_flag = 0;
				email.attachments = "";
				email.uid = ADMIN_UID;
				email.post_ts = Time::GetGlobalTime();
				email.title = "乐不思蜀";
				email.text = texT;
				logicEmail.AddEmail(email,toUidList);
				*/
			}
		}
	}


	return 0;
}

int CLogicHundredDaysActivityRank::UpdateHundredDaysActivityRank(int unsigned uid, const DataHDaysAcvitityPay &points)
{
	CDataHDaysAcvitityRank *pdata= GetHundredDaysActivityRankData();
	time_t now;
	time(&now);
	struct tm *pTm = localtime(&now);
	int tempSec = pTm->tm_sec;
	int tempMin = pTm->tm_min;
	int tempHour = pTm->tm_hour;
	unsigned tempNow = tempSec + tempMin * 60 + tempHour *3600;
	//更新排行榜
	if((unsigned)now >=Config::GetIntValue(CONFIG_PAY_OF_HUNDRED_DAYS_BEGIN_TS)
	&& (unsigned)now <= Config::GetIntValue(CONFIG_PAY_OF_HUNDRED_DAYS_END_TS)
	&& tempNow < 79200)					//每天的0点至22点
	{
		if(pdata == NULL)
		{
			DB_ERROR_RETURN_MSG("init_hundreddaysactivityrank_fail");
		}
		int ret = pdata->UpdateRankList(points);
		if(ret != 0)
		{
			return ret;
		}
	}
	return 0;
}



