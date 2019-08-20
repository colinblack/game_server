/*
 * LogicNewDouJiang.cpp
 *
 *  Created on: 2017-2-14
 *      Author: Ralf
 */


#include "LogicNewDouJiang.h"

void CLogicNewDouJiang::CheckVersion()
{
	CDataNewDouJiang *pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData fail");
		return;
	}

	pData->CheckVersion();

	return;
}

int CLogicNewDouJiang::SetZhenRong(unsigned uid, const vector<unsigned> & z, Json::Value & result)
{
	CDataNewDouJiang *pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}

	int ret = pData->SetZhenRong(uid, z, result);
	if(ret)
		return ret;

	return 0;
}

int CLogicNewDouJiang::GetZhenRong(unsigned uid, Json::Value & result)
{
	CDataNewDouJiang *pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}

	int ret = pData->GetZhenRong(uid, result);
	if(ret)
		return ret;

	return 0;
}

int CLogicNewDouJiang::GetMyList(unsigned uid, Json::Value & result)
{
	CDataNewDouJiang *pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}

	int ret = pData->GetMyList(uid, result);
	if(ret)
		return ret;

	return 0;
}

int CLogicNewDouJiang::PiPei(unsigned uid, unsigned seq,Json::Value & result)
{
	CDataNewDouJiang *pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}

	int ret = pData->PiPei(uid, seq, result);
	if(ret)
		return ret;

	return 0;
}

int CLogicNewDouJiang::StartAttack(unsigned uid, unsigned type, unsigned uid2, unsigned hud, unsigned seq, unsigned ud, Json::Value & result, unsigned fcts)
{
	CDataNewDouJiang *pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}

	int ret = pData->StartAttack(uid, type, uid2, hud, seq, ud, result,fcts);
	if(ret)
		return ret;

	return 0;
}

int CLogicNewDouJiang::SetResult(unsigned uid, unsigned type, unsigned uid2, unsigned win, unsigned hud, unsigned seq, unsigned ud, Json::Value & result)
{
	CDataNewDouJiang *pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}

	int ret = pData->SetResult(uid, type, uid2, win, hud, seq, ud, result);
	if(ret)
		return ret;

	return 0;
}

int CLogicNewDouJiang::GetRankList(unsigned uid, Json::Value & result)
{
	CDataNewDouJiang *pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}

	int ret = pData->GetRankList(uid, result);
	if(ret)
		return ret;

	return 0;
}

int CLogicNewDouJiang::GetZhanBao(unsigned uid, Json::Value &result)
{
	CDataNewDouJiang *pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}

	int ret = pData->GetZhanBao(uid, result);
	if(ret)
		return ret;

	return 0;
}
