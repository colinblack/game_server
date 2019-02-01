/*
 * LogicAllianceConsume.cpp
 *
 *  Created on: 2017-3-15
 *      Author: Ralf
 */

#include "LogicAllianceConsume.h"

int CLogicAllianceConsume::AllianceShopInfo(unsigned aid, Json::Value &result)
{
	CDataAllianceConsume *pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}

	int ret = pData->AllianceShopInfo( aid, result);
	if(ret)
		return ret;

	return 0;
}
int CLogicAllianceConsume::AllianceShopBuy(unsigned uid, unsigned aid, unsigned index, unsigned count, Json::Value &result)
{
	CDataAllianceConsume *pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}

	int ret = pData->AllianceShopBuy(uid, aid, index, count, result);
	if(ret)
		return ret;

	return 0;
}
int CLogicAllianceConsume::AllianceShopLimit(unsigned uid, unsigned aid, unsigned type, unsigned index, unsigned count, Json::Value &result)
{
	CDataAllianceConsume *pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}

	int ret = pData->AllianceShopLimit(uid, aid, type, index, count, result);
	if(ret)
		return ret;

	return 0;
}
int CLogicAllianceConsume::AllianceShopGift(unsigned uid, unsigned aid, unsigned index, Json::Value &result)
{
	CDataAllianceConsume *pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}

	int ret = pData->AllianceShopGift(uid, aid, index, result);
	if(ret)
		return ret;

	return 0;
}

