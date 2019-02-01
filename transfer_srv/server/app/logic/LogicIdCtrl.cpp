/*
 * LogicIdCtrl.cpp
 *
 *  Created on: 2011-7-14
 *      Author: dada
 */

#include "LogicIdCtrl.h"

int CLogicIdCtrl::GetNextId(int key, uint64_t &nextId)
{
	int ret;
	CDataIdCtrl dbIdCtrl;
	ret = dbIdCtrl.GetId(key, nextId);
	if(ret != 0)
	{
		fatal_log("[GetId fail][key=%d]", key);
		DB_ERROR_RETURN_MSG("get_id_fail");
	}
	nextId++;
	ret = dbIdCtrl.SetId(key, nextId);
	if(ret != 0)
	{
		fatal_log("[SetId fail][key=%d,nextId=%llu]", key, nextId);
		DB_ERROR_RETURN_MSG("set_id_fail");
	}
	return 0;
}

int CLogicIdCtrl::GetCurrentId(int key, uint64_t &currId)
{
	int ret;
	CDataIdCtrl dbIdCtrl;
	ret = dbIdCtrl.GetId(key, currId);
	if(ret != 0)
	{
		fatal_log("[GetId fail][key=%d]", key);
		DB_ERROR_RETURN_MSG("get_id_fail");
	}
	return 0;
}
