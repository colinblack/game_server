/*
 * LogicBase.cpp
 *
 *  Created on: 2011-6-10
 *      Author: dada
 */

#include "LogicBase.h"

static int AddBaseSafe(DataBase &base)
{
	int ret;
	uint64_t nextId;
	CLogicIdCtrl logicIdCtrl;
	CDataBase dbBase;
	for(int i = 0; i < 3; i++)
	{
		ret = logicIdCtrl.GetNextId(KEY_BASEID_CTRL, nextId);
		if(ret != 0)
		{
			return ret;
		}
		base.baseid = (unsigned)nextId;
		ret = dbBase.AddBase(base);
		if(ret == 0)
		{
			return 0;
		}
		else if(ret != -DBCache::ER_DUP_ENTRY)
		{
			error_log("[AddBase fail][ret=%d,uid=%u,baseid=%u]", ret, base.uid, base.baseid);
			DB_ERROR_RETURN_MSG("add_base_fail");
		}
	}
	error_log("[AddBase fail][ret=%d,uid=%u,baseid=%u]", ret, base.uid, base.baseid);
	DB_ERROR_RETURN_MSG("add_base_fail");
}

int LogicBase::AddBase(DataBase &base, DataBaseExtra &baseExtra)
{
	int ret;
	ret = AddBaseSafe(base);
	if(ret != 0)
	{
		return ret;
	}
	baseExtra.baseid = base.baseid;
	CDataBaseExtra dbBaseExtra;
	ret = dbBaseExtra.AddBase(baseExtra);
	if(ret != 0)
	{
		error_log("[AddBaseExtra fail][ret=%d,uid=%u,baseid=%u]", ret, base.uid, base.baseid);
		DB_ERROR_RETURN_MSG("add_base_extra_fail");
	}
	if(IsValidUid(base.uid))
	{
		CDataUserBase dbUserBase;
		ret = dbUserBase.AddUserBase(base.uid, base.base_index, base.baseid);
		if(ret != 0)
		{
			error_log("[AddUserBase fail][ret=%d,uid=%u,baseid=%u,index=%d]", ret, base.uid, base.baseid, base.base_index);
			DB_ERROR_RETURN_MSG("add_user_base_fail");
		}
	}
	return 0;
}

int LogicBase::AddMainBase(unsigned uid, unsigned &baseid)
{
	int ret;

	DataBase base;
	base.baseid = 0;
	base.uid = uid;
	base.base_index = MAIN_BASE_ID;
	base.type = BT_MAIN_BASE;
	base.base_name = "";
	base.seed = Math::GetRandomInt(10000);
	base.position = 0;
	base.create_time = Time::GetGlobalTime();
	base.save_time = Time::GetGlobalTime();
	base.saveby_uid = uid;
	base.protected_time = Time::GetGlobalTime() + NEW_USER_PROTECT;
	base.last_active_time = Time::GetGlobalTime();
	base.status = BS_NEW;
	base.damage = 0;
	base.destroyed = 0;
	base.value = 0;
	base.attack_level = 0;
	base.bomb_level = 0;

	DataBaseExtra baseExtra;
	baseExtra.baseid = 0;
	baseExtra.updates = "{}";
	baseExtra.building = "{}";
	baseExtra.effect = "[]";
	baseExtra.aiattack = "{}";
	baseExtra.manoeuvre = "{}";
	baseExtra.grower = "{}";
	baseExtra.military = "{}";
	baseExtra.hero = "{}";
	baseExtra.recycle = "{}";
	baseExtra.consume = "{}";
	baseExtra.extra_data = "{}";

	ret = AddBase(base, baseExtra);
	if(ret != 0)
	{
		return ret;
	}
	baseid = base.baseid;
	return 0;
}

int LogicBase::RemoveBase(unsigned uid, unsigned baseid)
{
	int ret;
	int index = 0;
	CDataUserBase dbUserBase;
	CDataBase dbBase;
	CDataBaseExtra dbBaseExtra;
	if(IsBaseIndex(baseid))
	{
		index = baseid;
		ret = dbUserBase.GetUserBase(uid, index, baseid);
		if(ret == R_ERR_NO_DATA)
		{
			return 0;
		}
		if(ret != 0)
		{
			error_log("[GetUserBase fail][ret=%d,uid=%u,baseid=%u]", ret, uid, baseid);
			DB_ERROR_RETURN_MSG("get_user_base_fail");
		}
	}
	else
	{
		DataBase base;
		ret = dbBase.GetBase(baseid, base);
		if(ret == R_ERR_NO_DATA)
		{
			ERROR_RETURN_MSG(R_ERR_NO_DATA, "get_base_fail");
		}
		if(ret != 0)
		{
			error_log("[GetBaseLimit fail][ret=%d,uid=%u,baseid=%u]", ret, uid, baseid);
			DB_ERROR_RETURN_MSG("get_base_fail");
		}
		index = base.base_index;
	}
	if(IsValidUid(uid))
	{
		ret = dbUserBase.RemoveUserBase(uid, index);
		if(ret != 0)
		{
			error_log("[RemoveUserBase fail][ret=%d,uid=%u,index=%d,baseid=%u]", ret, uid, index, baseid);
			DB_ERROR_RETURN_MSG("remove_user_base_fail");
		}
	}
	ret = dbBase.RemoveBase(baseid);
	if(ret != 0)
	{
		error_log("[RemoveBase fail][ret=%d,uid=%u,index=%d,baseid=%u]", ret, uid, index, baseid);
		DB_ERROR_RETURN_MSG("remove_base_fail");
	}
	ret = dbBaseExtra.RemoveBase(baseid);
	if(ret != 0)
	{
		error_log("[RemoveBaseExtra fail][ret=%d,uid=%u,index=%d,baseid=%u]", ret, uid, index, baseid);
		DB_ERROR_RETURN_MSG("remove_base_extra_fail");
	}
	return 0;
}

int LogicBase::SetBase(const DataBase &base)
{
	int ret;
	CDataBase dbBase;
	ret = dbBase.SetBase(base);
	if(ret != 0)
	{
		error_log("[SetBase fail][ret=%d,uid=%u,baseid=%u]", ret, base.uid, base.baseid);
		DB_ERROR_RETURN_MSG("set_base_fail");
	}
	return 0;
}

int LogicBase::GetBase(unsigned uid, unsigned baseid, DataBase &base)
{
	int ret;
	if(IsBaseIndex(baseid))
	{
		int index = baseid;
		CDataUserBase dbUserBase;
		ret = dbUserBase.GetUserBase(uid, index, baseid);
		if(ret == R_ERR_NO_DATA)
		{
			ERROR_RETURN_MSG(R_ERR_NO_DATA, "get_user_base_fail");
		}
		if(ret != 0)
		{
			error_log("[GetUserBase fail][ret=%d,uid=%u,baseid=%u]", ret, uid, baseid);
			DB_ERROR_RETURN_MSG("get_user_base_fail");
		}
	}
	CDataBase dbBase;
	ret = dbBase.GetBase(baseid, base);
	if(ret == R_ERR_NO_DATA)
	{
		ERROR_RETURN_MSG(R_ERR_NO_DATA, "get_base_fail");
	}
	if(ret != 0)
	{
		error_log("[GetBase fail][ret=%d,uid=%u,baseid=%u]", ret, uid, baseid);
		DB_ERROR_RETURN_MSG("get_base_fail");
	}
	return 0;
}

int LogicBase::SetBaseExtra(const DataBaseExtra &baseExtra)
{
	int ret;
	CDataBaseExtra dbBaseExtra;
	ret = dbBaseExtra.SetBase(baseExtra);
	if(ret != 0)
	{
		error_log("[SetBaseExtra fail][ret=%d,baseid=%u]", ret, baseExtra.baseid);
		DB_ERROR_RETURN_MSG("set_base_extra_fail");
	}
	return 0;
}

int LogicBase::GetBaseExtra(unsigned baseid, DataBaseExtra &baseExtra)
{
	int ret;
	CDataBaseExtra dbBaseExtra;
	ret = dbBaseExtra.GetBase(baseid, baseExtra);
	if(ret != 0)
	{
		error_log("[GetBaseExtra fail][ret=%d,baseid=%u]", ret, baseid);
		DB_ERROR_RETURN_MSG("get_base_extra_fail");
	}
	return 0;
}

int LogicBase::AddUserBase(unsigned uid, int index, unsigned baseid)
{
	int ret;
	CDataUserBase dbUserBase;
	ret = dbUserBase.AddUserBase(uid, index, baseid);
	if(ret != 0)
	{
		error_log("[AddUserBase fail][ret=%d,uid=%u,index=%d]", ret, uid, index);
		DB_ERROR_RETURN_MSG("add_user_base_fail");
	}
	return 0;
}

int LogicBase::GetUserBases(unsigned uid, map<int, unsigned> &bases)
{
	int ret;
	CDataUserBase dbUserBase;
	ret = dbUserBase.GetUserBases(uid, bases);
	if(ret != 0)
	{
		error_log("[GetUserBases fail][ret=%d,uid=%u]", ret, uid);
		DB_ERROR_RETURN_MSG("get_user_bases_fail");
	}
	return 0;
}

int LogicBase::RemoveUserBase(unsigned uid, int index)
{
	int ret;
	CDataUserBase dbUserBase;
	ret = dbUserBase.RemoveUserBase(uid, index);
	if(ret != 0)
	{
		error_log("[RemoveUserBase fail][ret=%d,uid=%u,index=%d]", ret, uid, index);
		DB_ERROR_RETURN_MSG("remove_user_base_fail");
	}
	return 0;
}

int LogicBase::GetSubBasesJson(unsigned uid, Json::Value &data)
{
	int ret;
	map<int, unsigned> bases;
	ret = GetUserBases(uid, bases);
	if(ret != 0)
	{
		return ret;
	}
	data = Json::Value(Json::arrayValue);
	for(map<int, unsigned>::iterator itr = bases.begin(); itr != bases.end(); itr++)
	{
		if(IsSubBase(itr->first))
		{
			unsigned baseid = itr->second;
			unsigned position = 0;
			ret = GetPosition(baseid, position);
			if(ret == 0)
			{
				CWorldPoint point(position);
				Json::Value &baseData = data[data.size()];
				baseData[0u] = point.X;
				baseData[1u] = point.Y;
				baseData[2u] = baseid;
			}
			else
			{
				error_log("[sub_base_not_exist][ret=%d,uid=%u,baseindex=%d,baseid=%u]", ret, uid, itr->first, baseid);
			}
		}
	}
	return 0;
}

int LogicBase::UpdateActiveTime(unsigned baseid)
{
	int ret;
	CDataBase dbBase;
	ret = dbBase.SetActiveTime(baseid, Time::GetGlobalTime());
	if(ret != 0)
	{
		error_log("[SetActiveTime fail][ret=%d,baseid=%u]", ret, baseid);
		DB_ERROR_RETURN_MSG("set_base_fail");
	}
	return 0;
}

int LogicBase::SetExtraData(unsigned baseid, const Json::Value &extraData)
{
	string sExtraData = Json::ToString(extraData);
	if(sExtraData.size() > 500)
	{
		fatal_log("[ASSERT(base_extra_data_overflow)][baseid=%u,data=%s,size=%d]",
				baseid, sExtraData.c_str(), (int)sExtraData.size());
		ERROR_RETURN_MSG(R_ERR_DATA_LIMIT, "set_base_extra_fail");
	}
	CDataBaseExtra dbBaseExtra;
	int ret = dbBaseExtra.SetExtraData(baseid, sExtraData);
	if (ret != 0)
	{
		error_log("[SetExtraData fail][ret=%d,baseid=%u]", ret, baseid);
		DB_ERROR_RETURN_MSG("set_base_extra_fail");
	}
	return 0;
}

int LogicBase::GetExtraData(unsigned baseid, Json::Value &extraData)
{
	CDataBaseExtra dbBaseExtra;
	string sExtraData;
	int ret = dbBaseExtra.GetExtraData(baseid, sExtraData);
	if (ret != 0)
	{
		error_log("[GetExtraData fail][ret=%d,baseid=%u]", ret, baseid);
		DB_ERROR_RETURN_MSG("get_base_extra_fail");
	}
	if(!Json::FromString(extraData, sExtraData))
	{
		if(!sExtraData.empty())
		{
			error_log("[base_extra_data_parse_fail][baseid=%u,data=%s]", baseid, sExtraData.c_str());
		}
		extraData = Json::Value(Json::objectValue);
	}
	return 0;
}

int LogicBase::SetPosition(unsigned baseid, unsigned position)
{
	int ret;
	CDataBase dbBase;
	ret = dbBase.SetPosition(baseid, position);
	if(ret != 0)
	{
		error_log("[SetPosition fail][ret=%d,baseid=%u,position=%u]", ret, baseid, position);
		DB_ERROR_RETURN_MSG("set_base_fail");
	}
	return 0;
}

int LogicBase::GetPosition(unsigned baseid, unsigned &position)
{
	int ret;
	CDataBase dbBase;
	ret = dbBase.GetPosition(baseid, position);
	if(ret != 0)
	{
		error_log("[GetPosition fail][ret=%d,baseid=%u]", ret, baseid);
		DB_ERROR_RETURN_MSG("get_base_fail");
	}
	return 0;
}

int LogicBase::AddUpdate(unsigned uid, unsigned baseid, unsigned uidBy, const Json::Value &data, Json::Value *pResult)
{
	int ret;
	string sUpdates;
	CDataBaseExtra dbBaseExtra;
	ret = dbBaseExtra.GetUpdates(baseid, sUpdates);
	if(ret != 0)
	{
		error_log("[GetUpdates fail][ret=%d,uid=%u,baseid=%u]", ret, uid, baseid);
		DB_ERROR_RETURN_MSG("get_base_extra_fail");
	}
	Json::Value updates;
	if(!Json::FromString(updates, sUpdates))
	{
		error_log("[updates_parse_error][uid=%u,uidby=%u,baseid=%u,updates=%s]",
				uid, uidBy, baseid, Json::ToString(data).c_str());
		PARAM_ERROR_RETURN();
	}
	if(!updates.isObject())
	{
		updates = Json::Value(Json::objectValue);
	}
	DataUserBasic userBasicBy;
	ret = LogicUserBasic::GetUser(uidBy, OpenPlatform::GetType(), userBasicBy);
	if(ret != 0)
	{
		return ret;
	}
	unsigned nextUpdateId;
	if(!Json::GetUInt(updates, "nextid", nextUpdateId))
	{
		nextUpdateId = Time::GetGlobalTime();
	}
	if(!Json::IsArray(updates, "updates"))
	{
		updates["updates"] = Json::Value(Json::arrayValue);
	}
	Json::Value &update = updates["updates"][updates["updates"].size()];
	update["id"] = nextUpdateId;
	update["data"] = Json::ToString(data);
	update["pt"] = userBasicBy.platform;
	update["fbid"] = userBasicBy.open_id;
	update["name"] = userBasicBy.name;
	if(IsMercenary())
	{
		update["pic"] = userBasicBy.figure_url;
	}
	updates["nextid"] = nextUpdateId + 1;
	sUpdates = Json::ToString(updates);
	if(sUpdates.size() >= 5000)
	{
		fatal_log("[ASSERT(updates_size_overflow)][uid=%u,uidby=%u,baseid=%u,size=%u]",
				uid, uidBy, baseid, (unsigned)sUpdates.size());
		DB_ERROR_RETURN_MSG("updates_overflow");
	}
	ret = dbBaseExtra.SetUpdates(baseid, sUpdates);
	if(ret != 0)
	{
		error_log("[SetUpdates fail][ret=%d,uid=%u,baseid=%u]", ret, uid, baseid);
		DB_ERROR_RETURN_MSG("set_base_extra_fail");
	}
	if(pResult != NULL)
	{
		(*pResult) = updates;
	}
	return 0;
}

int LogicBase::GetUpdates(unsigned baseid, Json::Value &data)
{
	int ret;
	string sUpdates;
	CDataBaseExtra dbBaseExtra;
	ret = dbBaseExtra.GetUpdates(baseid, sUpdates);
	if(ret != 0)
	{
		error_log("[GetUpdates fail][ret=%d,baseid=%u]", ret, baseid);
		DB_ERROR_RETURN_MSG("get_base_extra_fail");
	}
	Json::Value updates;
	if(!Json::FromString(updates, sUpdates))
	{
		error_log("[updates_parse_error][baseid=%u]", baseid);
		ERROR_RETURN(R_ERR_DATA);
	}
	if(!updates.isObject())
	{
		data = Json::Value(Json::arrayValue);
		return 0;
	}
	data = updates["updates"];
	if(!data.type() != Json::arrayValue)
	{
		data = Json::Value(Json::arrayValue);
	}
	return 0;
}

int LogicBase::ClearUpdates(unsigned lastUpdateId, Json::Value &updates)
{
	if(!updates.isObject())
	{
		updates = Json::Value(Json::objectValue);
	}
	unsigned lastId = 0;
	Json::GetUInt(updates, "lastid", lastId);
	if(lastUpdateId <= lastId)
	{
		return 0;
	}
	updates["lastid"] = lastUpdateId;
	if(!Json::IsArray(updates, "updates"))
	{
		return 0;
	}
	Json::Value &updatesArray = updates["updates"];
	unsigned count = updatesArray.size();
	unsigned validCount = 0;
	for(unsigned i = 0; i < count; i++)
	{
		unsigned id = 0;
		Json::GetUInt(updatesArray[i], "id", id);
		if(id > lastUpdateId)
		{
			if(i !=  validCount)
			{
				updatesArray[validCount].swap(updatesArray[i]);
			}
			validCount++;
		}
	}
	if(validCount < count)
	{
		updatesArray.resize(validCount);
	}
	return 0;
}

int LogicBase::SetMilitary(unsigned baseid, const Json::Value &data)
{
	int ret;
	CDataBaseExtra dbBaseExtra;
	ret = dbBaseExtra.SetMilitary(baseid, Json::ToString(data));
	if(ret != 0)
	{
		error_log("[SetMilitary fail][ret=%d,baseid=%u]", ret, baseid);
		DB_ERROR_RETURN_MSG("set_base_extra_fail");
	}
	return 0;
}

int LogicBase::GetMilitary(unsigned baseid, Json::Value &data)
{
	int ret;
	string sMilitary;
	CDataBaseExtra dbBaseExtra;
	ret = dbBaseExtra.GetMilitary(baseid, sMilitary);
	if(ret != 0)
	{
		error_log("[GetMilitary fail][ret=%d,baseid=%u]", ret, baseid);
		DB_ERROR_RETURN_MSG("get_base_extra_fail");
	}
	if(!Json::FromString(data, sMilitary))
	{
		error_log("[military_parse_error][baseid=%u]", baseid);
		DATA_ERROR_RETURN_MSG("base_extra_data_error");
	}
	return 0;
}

int LogicBase::UpdateMilitary(unsigned uid, const Json::Value &data)
{
	int ret;
	unsigned baseCount = data.size();
	for(unsigned i = 0; i < baseCount; i++)
	{
		const Json::Value &dataMonster = data[i];
		unsigned baseid;
		if(Json::IsObject(dataMonster, "m") &&
			Json::GetUInt(dataMonster, "baseid", baseid))
		{
			DataBase base;
			CHECK_CALL(GetBase(uid, baseid, base));
			if(base.uid != uid || !IsUserBaseIndex(base.base_index))
			{
				error_log("[not_user_base][uid=%i,baseid=%u,baseuid=%u,baseindex=%d]",
						uid, baseid, base.uid, base.base_index);
				ERROR_RETURN_MSG(R_ERR_LOGIC, "not_user_base");
			}
			CHECK_CALL(SetMilitary(baseid, dataMonster["m"]));
		}
		else
		{
			error_log("[unknow_monsterupdate][uid=%u,baseid=%u,data=%s]",
				uid, baseid, Json::ToString(dataMonster).c_str());
		}
	}
	return 0;
}

int LogicBase::ChangeArmy(unsigned uid, unsigned baseid, const map<string, int> &change)
{
	int ret;
	if(IsBaseIndex(baseid))
	{
		DataBase base;
		ret = GetBase(uid, baseid, base);
		if(ret != 0)
		{
			return ret;
		}
		baseid = base.baseid;
	}
	Json::Value military;
	ret = LogicBase::GetMilitary(baseid, military);
	if(!military.isObject())
	{
		military = Json::Value(Json::objectValue);
	}
	Json::Value *pArmy;
	if(military.isMember("housed"))
	{
		pArmy = &military["housed"];
	}
	else
	{
		pArmy = &military;
	}
	Json::Value &army = *pArmy;
	if(!army.isObject())
	{
		army = Json::Value(Json::objectValue);
	}
	for(map<string, int>::const_iterator itr = change.begin(); itr != change.end(); itr++)
	{
		unsigned count = 0;
		Json::GetUInt(army, itr->first.c_str(), count);
		if(itr->second < 0 && (unsigned)(-(itr->second)) > count)
		{
			error_log("[not_enough_army][uid=%u,baseid=%u,type=%s,count=%u,change=%d]",
					uid, baseid, itr->first.c_str(), count, itr->second);
			ERROR_RETURN_MSG(R_ERR_LOGIC, "not_enough_army");
		}
		count += itr->second;
		if(count == 0)
		{
			if(army.isMember(itr->first))
			{
				army.removeMember(itr->first);
			}
		}
		else
		{
			army[itr->first] = count;
		}
	}
	CDataBaseExtra dbBaseExtra;
	ret = dbBaseExtra.SetMilitary(baseid, Json::ToString(military));
	if(ret != 0)
	{
		error_log("[SetMilitary fail][ret=%d,baseid=%u]", ret, baseid);
		DB_ERROR_RETURN_MSG("set_base_extra_fail");
	}
	return 0;
}

int LogicBase::SetHero(unsigned baseid, const Json::Value &hero)
{
	int ret;
	CDataBaseExtra dbBaseExtra;
	ret = dbBaseExtra.SetHero(baseid, Json::ToString(hero));
	if(ret != 0)
	{
		error_log("[SetHero fail][ret=%d,baseid=%u]", ret, baseid);
		DB_ERROR_RETURN_MSG("set_base_extra_fail");
	}
	return 0;
}

static int GetFreeUserBaseIndex(unsigned uid)
{
	int ret;
	map<int, unsigned> bases;
	CHECK_CALL(LogicBase::GetUserBases(uid, bases));
	map<int, unsigned>::iterator itr;
	for(int baseIndex = SUB_BASE_ID_START; baseIndex < MAX_SUB_BASE_ID; baseIndex++)
	{
		itr = bases.find(baseIndex);
		if(itr == bases.end())
		{
			return baseIndex;
		}
	}
	return -1;
}

int LogicBase::ChangeOwner(unsigned uid,  DataBase &base)
{
	int ret;
	int baseIndex = GetFreeUserBaseIndex(uid);
	if(!IsUserBaseIndex(baseIndex))
	{
		error_log("[base_count_limit][uid=%u,baseid=%u]", uid, base.baseid);
		ERROR_RETURN_MSG(R_ERR_DATA_LIMIT, "base_count_limit");
	}
	CHECK_CALL(RemoveUserBase(base.uid, base.base_index));
	base.uid = uid;
	base.base_index = baseIndex;
	base.save_time = Time::GetGlobalTime();
	base.saveby_uid = uid;
	base.protected_time = Time::GetGlobalTime() + NEW_SUB_BASE_PROTECT;
	base.last_active_time = Time::GetGlobalTime();
	CHECK_CALL(SetBase(base));
	CHECK_CALL(AddUserBase(uid, base.base_index, base.baseid));
	return 0;
}


int LogicBase::AddSubBase(unsigned uid, DataBase &base)
{
	int ret;
	int baseIndex = GetFreeUserBaseIndex(uid);
	if(!IsUserBaseIndex(baseIndex))
	{
		error_log("[base_count_limit][uid=%u,baseid=%u]", uid, base.baseid);
		ERROR_RETURN_MSG(R_ERR_DATA_LIMIT, "base_count_limit");
	}

	base.uid = uid;
	base.base_index = baseIndex;
	base.type = BT_SUB_BASE;
	base.base_name = "";
	base.seed = Math::GetRandomInt(10000);
	base.create_time = Time::GetGlobalTime();
	base.save_time = Time::GetGlobalTime();
	base.saveby_uid = uid;
	base.protected_time = Time::GetGlobalTime() + NEW_SUB_BASE_PROTECT;
	base.last_active_time = Time::GetGlobalTime();
	base.status = BS_NEW;
	base.damage = 0;
	base.destroyed = 0;
	base.value = 0;
	base.attack_level = 0;
	base.bomb_level = 0;

	DataBaseExtra baseExtra;
	baseExtra.baseid = base.baseid;
	baseExtra.updates = "{}";
	baseExtra.building = "{}";
	baseExtra.effect = "[]";
	baseExtra.aiattack = "{}";
	baseExtra.manoeuvre = "{}";
	baseExtra.grower = "{}";
	baseExtra.military = "{}";
	baseExtra.hero = "{}";
	baseExtra.recycle = "{}";
	baseExtra.consume = "{}";
	baseExtra.extra_data = "{}";

	CHECK_CALL(SetBaseExtra(baseExtra));
	CHECK_CALL(SetBase(base));
	CHECK_CALL(AddUserBase(uid, base.base_index, base.baseid));
	return 0;
}
