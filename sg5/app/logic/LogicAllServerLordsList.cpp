/*
 * LogicAllServerLordsList.cpp
 *
 *  Created on: 2016-7-6
 *      Author: dawx62fac
 */

#include "LogicAllServerLordsList.h"
#include <stdexcept>

CDataAllServerLordsList* CLogicAllServerLordsList::DataWrap()
{
	CDataAllServerLordsList* p = GetData();
	if (NULL == p)
	{
		throw std::runtime_error("Get_AllServer_lord_list_data_error");
	}

	return p;
}


int CLogicAllServerLordsList::Sync(int type, const Json::Value& jsonList)
{

	if (! jsonList.isArray())
	{
		error_log("list data params error.");
		return R_ERR_PARAM;
	}

	try
	{
		DataWrap()->Sync(type, jsonList);
	}
	catch (const std::exception& e)
	{
		::SetError(R_ERROR, e.what());
		error_log("%s", e.what());
		return R_ERROR;
	}

	return R_SUCCESS;
}

int CLogicAllServerLordsList::Worship(unsigned uid, int id, int type, Json::Value& result)
{
	try
	{
		int cnt = DataWrap()->Worship(uid, id, type);
		result["cnt"] = cnt;
	}
	catch (const std::exception& e)
	{
		::SetError(R_ERROR, e.what());
		error_log("%s", e.what());
		return R_ERROR;
	}

	return R_SUCCESS;
}

int CLogicAllServerLordsList::CloseWorship()
{
	try
	{
		DataWrap()->CloseWorship();
	}
	catch (const std::exception& e)
	{
		::SetError(R_ERROR, e.what());
		error_log("%s", e.what());
		return R_ERROR;
	}

	return R_SUCCESS;
}

int CLogicAllServerLordsList::GetRankList(unsigned uid, int type, Json::Value& result)
{
	try
	{
		DataWrap()->GetRankList(uid, type, result["list"]);
	}
	catch (const std::exception& e)
	{
		::SetError(R_ERROR, e.what());
		error_log("%s", e.what());
		return R_ERROR;
	}

	return R_SUCCESS;
}

int CLogicAllServerLordsList::GetAllLords(unsigned uid, Json::Value& result)
{
	try
	{
		DataWrap()->GetAllLords(uid, result);
	}
	catch (const std::exception& e)
	{
		::SetError(R_ERROR, e.what());
		error_log("%s", e.what());
		return R_ERROR;
	}

	return R_SUCCESS;
}
