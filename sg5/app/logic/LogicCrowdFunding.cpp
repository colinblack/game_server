/*
 * LogicCrowdFunding.cpp
 *
 *  Created on: 2016-1-25
 *      Author: Ralf
 */

#include "LogicCrowdFunding.h"


int CLogicCrowdFunding::Get(unsigned uid, Json::Value &result)
{
	string url = "action=Get";
	url += "&uid=";
	url += CTrans::UTOS(uid);
	CLogicAllServerBaseMatch logicBaseMatch;
	return logicBaseMatch.RequestBaseMatch(url,result, CONFIG_CROWD_FUNDING_PATH, true);
}
int CLogicCrowdFunding::Buy(unsigned uid, unsigned id, unsigned need, Json::Value &result)
{
	int ret = 0;

	CLogicPay logicPay;
	ret = logicPay.Try(uid, -need * CROWD_FUNDING_NEED_CASH, 0);
	if(ret)
		return ret;

	string url = "action=Buy";
	url += "&uid=";
	url += CTrans::UTOS(uid);
	url += "&id=";
	url += CTrans::UTOS(id);
	url += "&need=";
	url += CTrans::UTOS(need);
	CLogicAllServerBaseMatch logicBaseMatch;
	ret = logicBaseMatch.RequestBaseMatch(url,result, CONFIG_CROWD_FUNDING_PATH, true);
	if(ret)
		return ret;

	if(result.isMember("need"))
	{
		bool bsave;
		Json::Value user_flag;
		CLogicUser logicUser;
		ret = logicUser.GetUserFlag(uid, user_flag);
		if(ret)
			return ret;
		DataPay payData;
		ret = logicPay.ProcessOrderForBackend(uid, -result["need"].asInt() * CROWD_FUNDING_NEED_CASH, 0, payData, "CrowdFunding",user_flag,bsave);
		if(ret)
			return ret;
		if(bsave)
		{
			ret = logicUser.SetUserFlag(uid, user_flag);
			if(ret)
				return ret;
		}
	}

	return 0;
}

int CLogicCrowdFunding::_Get(unsigned uid, Json::Value &result)
{
	CDataCrowdFunding *pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}

	int ret = pData->Get(uid, result);
	if(ret)
		return ret;

	return 0;
}

int CLogicCrowdFunding::_Buy(unsigned uid, unsigned id, unsigned need, Json::Value &result)
{
	CDataCrowdFunding *pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}

	int ret = pData->Buy(uid, id, need, result);
	if(ret)
		return ret;

	return 0;
}
