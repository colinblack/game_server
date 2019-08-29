/*
 * LogicIdCtrl.cpp
 *
 *  Created on: 2015-9-9
 *      Author: Administrator
 */

#include "LogicIdCtrl.h"

int CLogicIdCtrl::GetNextId(int key, uint32_t &nextId, uint32_t serverId) {
	int ret;
	CDataIdCtrl dbIdCtrl;
	ret = dbIdCtrl.GetId(key, nextId, serverId);
	if (ret != 0) {
		fatal_log("[GetId fail][key=%d]", key);
		DB_ERROR_RETURN_MSG("db_get_id_ctrl_fail");
	}
	nextId++;
	ret = dbIdCtrl.SetId(key, nextId, serverId);
	if (ret != 0) {
		fatal_log("[SetId fail][key=%d,nextId=%llu]", key, nextId);
		DB_ERROR_RETURN_MSG("db_set_id_ctrl_fail");
	}
	return 0;
}

int CLogicIdCtrl::GetNextId(int key, uint32_t &nextId, uint32_t getCount, uint32_t serverId) {
	int ret;
	CDataIdCtrl dbIdCtrl;
	ret = dbIdCtrl.GetId(key, nextId, serverId);
	if (ret != 0) {
		fatal_log("[GetId fail][key=%d]", key);
		DB_ERROR_RETURN_MSG("db_get_id_ctrl_fail");
	}
	nextId++;
	ret = dbIdCtrl.SetId(key, nextId + getCount - 1, serverId);
	if (ret != 0) {
		fatal_log("[SetId fail][key=%d,nextId=%llu]", key, nextId);
		DB_ERROR_RETURN_MSG("db_set_id_ctrl_fail");
	}
	return 0;
}

int CLogicIdCtrl::GetCurrentId(int key, uint32_t &currId, uint32_t serverId) {
	int ret;
	CDataIdCtrl dbIdCtrl;
	ret = dbIdCtrl.GetId(key, currId, serverId);
	if (ret != 0) {
		fatal_log("[GetId fail][key=%d]", key);
		DB_ERROR_RETURN_MSG("get_id_fail");
	}
	return 0;
}

