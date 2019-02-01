/*
 * LogicMVP.cpp
 *
 *  Created on: 2017-08-03
 *      Author: Ralf
 */

#include "LogicMVP.h"

int CLogicMVP::GetAllServerMVP(Json::Value &result)
{
	CDataMVP *pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}

	int ret = pData->GetAllServerMVP(result);
	if(ret)
		return ret;

	return 0;
}
int CLogicMVP::StartAllServerMVP(unsigned rank, unsigned uid)
{
	CDataMVP *pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}

	int ret = pData->StartAllServerMVP(rank, uid);
	if(ret)
		return ret;

	return 0;
}
int CLogicMVP::EndAllServerMVP(unsigned rank, unsigned uid, bool win, Json::Value &data)
{
	CDataMVP *pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}

	int ret = pData->EndAllServerMVP(rank, uid, win, data);
	if(ret)
		return ret;

	return 0;
}
int CLogicMVP::SetAllServerMVP(unsigned uid, string &sign)
{
	CDataMVP *pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}

	int ret = pData->SetAllServerMVP(uid, sign);
	if(ret)
		return ret;

	return 0;
}

int CLogicMVP::StartAllServerBattleMVP(unsigned rank, unsigned uid)
{
	CDataMVP *pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}

	int ret = pData->StartAllServerBattleMVP(rank, uid);
	if(ret)
		return ret;

	return 0;
}
int CLogicMVP::EndAllServerBattleMVP(unsigned rank, unsigned uid, bool win, Json::Value &data)
{
	CDataMVP *pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}

	int ret = pData->EndAllServerBattleMVP(rank, uid, win, data);
	if(ret)
		return ret;

	return 0;
}

int CLogicMVP::EndAllServerNewWorldFightMVP(unsigned rank, unsigned uid, bool win, Json::Value &data)
{
	CDataMVP*pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}

	int ret = pData->EndAllServerNewWorldFightMVP(rank, uid, win, data);
	if(ret)
		return ret;

	return 0;
}

