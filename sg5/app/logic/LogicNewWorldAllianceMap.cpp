/*
 * LogicNewWorldAllianceMap.cpp
 *
 *  Created on: 2015-12-22
 *      Author: Ralf
 */

#include "LogicNewWorldAllianceMap.h"

int CLogicNewWorldAllianceMap::GetRoom(unsigned aid, Json::Value &result)
{
	CDataNewWorldAllianceMap *pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}

	unsigned rid = 0, level = 0, reward = 0;
	int ret = pData->GetRoom(aid, rid, level, reward);
	if(ret)
		return ret;

	result["rid"] = rid;
	result["level"] = level;
	result["reward"] = reward;

	return 0;
}
