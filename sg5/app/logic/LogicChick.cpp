/*
 * LogicChick.cpp
 *
 *  Created on: 2018年7月26日
 *      Author: Ralf
 */


#include "LogicChick.h"

int CLogicChick::GetChickReg(unsigned uid, Json::Value &res)
{
	CDataChick *pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}

	int ret = pData->GetChickReg(uid, res);
	if(ret)
		return ret;

	return 0;
}
int CLogicChick::ChickReg(unsigned uid, Json::Value &data, Json::Value &res)
{
	CDataChick *pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}

	int ret = pData->ChickReg(uid, data, res);
	if(ret)
		return ret;

	return 0;
}
