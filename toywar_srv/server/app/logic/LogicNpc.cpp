/*
 * LogicNpc.cpp
 *
 *  Created on: 2011-7-19
 *      Author: dada
 */

#include "LogicNpc.h"

bool LogicNpc::IsNpc(unsigned id)
{
	return IsWildForce(id) || IsGate(id) || id == NPC_ADMIN_ID;
}

bool LogicNpc::IsWildForce(unsigned id)
{
	static unsigned s_maxWildForceId = 0;
	if(s_maxWildForceId <= 0)
	{
		s_maxWildForceId = Config::GetIntValue(CONFIG_WF_COUNT);
		s_maxWildForceId += WF_BASE_ID_START;
	}
	return id >= WF_BASE_ID_START && id < s_maxWildForceId;
}

bool LogicNpc::IsGate(unsigned id)
{
	static unsigned s_maxGateId = 0;
	if(s_maxGateId <= 0)
	{
		s_maxGateId = Config::GetIntValue(CONFIG_GATE_COUNT);
		s_maxGateId += GATE_BASE_ID_START;
	}
	return id > GATE_BASE_ID_START && id <= s_maxGateId;
}

int LogicNpc::GetInitBase(unsigned id, DataBaseExtra &baseExtra)
{
	if(!IsNpc(id))
	{
		error_log("[invalid_npc_id][baseid=%u]", id);
		ERROR_RETURN(R_ERR_DATA_LIMIT);
	}
	static map<unsigned, DataBaseExtra> s_mapArchive;
	map<unsigned, DataBaseExtra>::iterator itrArchive = s_mapArchive.find(id);
	if(itrArchive == s_mapArchive.end())
	{
		string path;
		String::Format(path, "%s/%u.dat", Config::GetValue(CONFIG_NPC_DATA).c_str(), id);
		string data;
		int ret = File::Read(path, data);
		if(ret != 0 || data.empty())
		{
			fatal_log("[archive_file_not_exist][ret=%d,path=%s]", ret, path.c_str());
			DB_ERROR_RETURN_MSG("get_archive_fail");
		}
		Json::Value initArchive;
		if(!Json::FromString(initArchive, data))
		{
			fatal_log("[archive_parse_fail][path=%s,data_size=%u]", path.c_str(), (unsigned)data.size());
			DATA_ERROR_RETURN_MSG("archive_data_error");
		}
		DataBaseExtra &initBase = s_mapArchive[id];
		initBase.baseid = id;
		initBase.updates = "[]";
		initBase.building = Json::ToString(initArchive["buildingdata"]);
		initBase.effect = Json::ToString(initArchive["effects"]);
		initBase.aiattack = "{}";
		initBase.manoeuvre = "{}";
		initBase.grower = Json::ToString(initArchive["mushrooms"]);
		initBase.military = Json::ToString(initArchive["monsters"]);
		if(initArchive.isMember("champion"))
		{
			initBase.hero = Json::ToString(initArchive["champion"]);
		}
		else
		{
			initBase.hero = "{}";
		}
		initBase.recycle = "{}";
		initBase.consume = "{}";
		Json::Value extraData;
		extraData["resources"] = initArchive["resources"];
		initBase.extra_data = Json::ToString(extraData);
		baseExtra = initBase;
	}
	else
	{
		baseExtra = itrArchive->second;
	}
	return 0;
}

int LogicNpc::GetArchive(unsigned uid, unsigned id, bool attack, Json::Value &archive)
{
	int ret;
	DataBase base;
	DataBaseExtra baseExtra;
	if(IsBaseIndex(id) && !IsNpc(id))
	{
		error_log("[invalid_npc_id][uid=%u,baseid=%u]", uid, id);
		PARAM_ERROR_RETURN();
	}
	if(id == NPC_ADMIN_ID)
	{
		if(attack)
		{
			error_log("[attack_admin][uid=%u,baseid=%u]", uid, id);
			PARAM_ERROR_RETURN();
		}
		ret = R_ERR_NO_DATA;
	}
	else
	{
		ret = LogicBase::GetBase(uid, id, base);
	}
	if(ret == 0)
	{
		if(base.type == BT_MAIN_BASE || base.type == BT_SUB_BASE || base.uid != uid)
		{
			error_log("[invalid_npc_base][uid=%u,baseid=%u,type=%d,baseuid=%u]", uid, id, base.type, base.uid);
			PARAM_ERROR_RETURN();
		}

		if(Time::GetGlobalTime() - base.save_time > WF_REFRESH_TIME)
		{
			//每隔一定时间刷新一次
			ret = GetInitBase(id, baseExtra);
			if(ret != 0)
			{
				return ret;
			}
			base.create_time = Time::GetGlobalTime();
			base.save_time = Time::GetGlobalTime();
			base.last_active_time = Time::GetGlobalTime();
			base.status = attack ? BS_FIGHT : BS_BUILD;
			base.damage = 0;
			base.destroyed = 0;
			baseExtra.baseid = base.baseid;
			ret = LogicBase::SetBase(base);
			if(ret != 0)
			{
				return ret;
			}
			ret = LogicBase::SetBaseExtra(baseExtra);
			if(ret != 0)
			{
				return ret;
			}
		}
		else
		{
			//已有数据
			ret = LogicBase::GetBaseExtra(base.baseid, baseExtra);
			if(ret != 0)
			{
				return ret;
			}
			if(attack)
			{
				base.status = BS_FIGHT;
				base.saveby_uid = uid;
			}
			else
			{
				base.status = BS_BUILD;
			}
			base.last_active_time = Time::GetGlobalTime();
			ret = LogicBase::SetBase(base);
			if(ret != 0)
			{
				return ret;
			}
		}

		archive["savedby"] = uid;
		archive["lastupdate"] = 0;
		archive["savetime"] = base.save_time;
	}
	else if(ret == R_ERR_NO_DATA)
	{
		ret = GetInitBase(id, baseExtra);
		if(ret != 0)
		{
			return ret;
		}

		if(attack)
		{
			base.baseid = 0;
			base.uid = uid;
			base.base_index = id;
			if(IsWildForce(id))
			{
				base.type = BT_WILD_FORCE;
			}
			else
			{
				base.type = BT_GATE;
			}
			base.base_name = "";
			base.seed = Math::GetRandomInt(10000);
			base.position = 0;
			base.create_time = Time::GetGlobalTime();
			base.save_time = Time::GetGlobalTime();
			base.saveby_uid = uid;
			base.protected_time = 0;
			base.last_active_time = Time::GetGlobalTime();
			base.status = BS_FIGHT;
			base.damage = 0;
			base.destroyed = 0;
			base.value = 0;
			base.attack_level = 0;
			base.bomb_level = 0;
			baseExtra.baseid = base.baseid;
			ret = LogicBase::AddBase(base, baseExtra);
			if(ret != 0)
			{
				return ret;
			}
		}
		else
		{
			base.baseid = id;
			base.base_index = id;
			base.save_time = 0;
			base.saveby_uid = 0;
		}
	}
	else
	{
		return ret;
	}

	archive = Json::Value(Json::objectValue);
	archive["baseid"] = base.baseid;
	archive["npcid"] = base.base_index;
	archive["savetime"] = base.save_time;
	archive["saveby"] = base.saveby_uid;
	Json::FromString(archive["buildingdata"], baseExtra.building);
	Json::FromString(archive["effects"], baseExtra.effect);
	Json::FromString(archive["mushrooms"], baseExtra.grower);
	archive["mushrooms"]["s"] = Time::GetGlobalTime();
	Json::FromString(archive["monsters"], baseExtra.military);
	Json::FromString(archive["champion"], baseExtra.hero);
	Json::Value extraData;
	if(Json::FromString(extraData, baseExtra.extra_data))
	{
		archive["resources"] = extraData["resources"];
	}

	return 0;
}

int LogicNpc::UpdateBase(unsigned uid, unsigned id, const Json::Value &data, DataBase &base)
{
	int ret;
	if(IsBaseIndex(id) && !IsNpc(id))
	{
		error_log("[invalid_npc_id][uid=%u,baseid=%u]", uid, id);
		PARAM_ERROR_RETURN();
	}

	DataBaseExtra baseExtra;
	ret = LogicBase::GetBase(uid, id, base);
	if(ret != 0)
	{
		return ret;
	}
	if(base.type == BT_MAIN_BASE || base.type == BT_SUB_BASE || base.uid != uid)
	{
		error_log("[invalid_npc_base][uid=%u,baseid=%u,type=%d,baseuid=%u]", uid, id, base.type, base.uid);
		PARAM_ERROR_RETURN();
	}
	unsigned saveid;
	if(!Json::GetUInt(data, "basesaveid", saveid))
	{
		error_log("[not save id][uid=%u,baseid=%u]", uid, base.baseid);
		PARAM_ERROR_RETURN();
	}
	if(saveid != base.save_time)
	{
		error_log("[save id unequal][uid=%u,baseid=%u,saveid=%u,real_saveid=%u]",
				uid, base.baseid, saveid, base.save_time);
		PARAM_ERROR_RETURN();
	}

	ret = LogicBase::GetBaseExtra(base.baseid, baseExtra);
	if(ret != 0)
	{
		return ret;
	}

	if(data.isMember("buildingdata"))
	{
		baseExtra.building = Json::ToString(data["buildingdata"]);
	}
	if(data.isMember("effects"))
	{
		baseExtra.effect = Json::ToString(data["effects"]);
	}
	if(data.isMember("mushrooms"))
	{
		baseExtra.grower = Json::ToString(data["mushrooms"]);
	}
	if(data.isMember("monsters"))
	{
		baseExtra.military = Json::ToString(data["monsters"]);
	}
	if(data.isMember("champion"))
	{
		baseExtra.hero = Json::ToString(data["champion"]);
	}
	Json::GetInt(data, "damage", base.damage);
	Json::GetInt(data, "destroyed", base.destroyed);

	if(Json::IsObject(data, "resources"))
	{
		ret = ChangeResource(uid, baseExtra, data["resources"]);
		if(ret != 0)
		{
			return ret;
		}
	}

	base.saveby_uid = uid;
	base.last_active_time = Time::GetGlobalTime();
	if(base.save_time < Time::GetGlobalTime())	//防重放
	{
		base.save_time = Time::GetGlobalTime();
	}
	else
	{
		base.save_time++;
	}

	ret = LogicBase::SetBase(base);
	if(ret != 0)
	{
		return ret;
	}
	ret = LogicBase::SetBaseExtra(baseExtra);
	if(ret != 0)
	{
		return ret;
	}

	return 0;
}

int LogicNpc::ChangeResource(unsigned uid, DataBaseExtra &baseExtra, const Json::Value &resources)
{
	static char s_resField[][20] = { "r1", "r2", "r3", "r4" };
	Json::Value extraData;
	Json::FromString(extraData, baseExtra.extra_data);
	Json::Value &baseResources = extraData["resources"];
	for(unsigned i = 0; i < COUNT_OF(s_resField); i++)
	{
		unsigned currResource = 0;
		Json::GetUInt(baseResources, s_resField[i], currResource);
		int resourceDelta = 0;
		if(Json::GetInt(resources, s_resField[i], resourceDelta))
		{
			if(resourceDelta < 0 && currResource < (unsigned)(-resourceDelta))
			{
				error_log("[not_enough_resource][uid=%u,baseid=%u,type=%d,resource=%u,delta=%d]",
						uid, baseExtra.baseid, i, currResource, resourceDelta);
				DATA_ERROR_RETURN_MSG("not_enough_resource");
			}
			else
			{
				currResource += resourceDelta;
			}
			baseResources[s_resField[i]] = currResource;
		}
	}
	baseExtra.extra_data = Json::ToString(extraData);
	return 0;
}

int LogicNpc::SetNpcStatus(unsigned uid, unsigned id, NpcStatus status)
{
	int ret;
	CDataUserExtra dbUserExtra;
	string wfstatus;
	ret = dbUserExtra.GetWfStatus(uid, wfstatus);
	if(ret != 0)
	{
		error_log("[GetWfStatus fail][ret=%,uid=%u]", ret, uid);
		DB_ERROR_RETURN_MSG("get_user_extra_fail");
	}
	if(wfstatus.size() <= id)
	{
		if(status == NS_UNPASS)
		{
			return 0;
		}
		wfstatus.resize(id, (char)NS_UNPASS);
	}
	if(wfstatus[id] != (char)status)
	{
		wfstatus[id] = (char)status;
		ret = dbUserExtra.SetWfStatus(uid, wfstatus);
		if(ret != 0)
		{
			error_log("[SetWfStatus fail][ret=%,uid=%u]", ret, uid);
			DB_ERROR_RETURN_MSG("set_user_extra_fail");
		}
	}
	return 0;
}
