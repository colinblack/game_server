/*
 * LogicAlliance.cpp
 *
 *  Created on: 2011-9-19
 *      Author: dada
 */

#include "LogicAlliance.h"

int CLogicAlliance::AddAlliance(unsigned uid, string &name, int flag, const string &description,
		int cash, bool useResource, DataAlliance &alliance)
{
	int ret;

	//名字检查
	String::Trim(name);
	if(OpenPlatform::GetType() != PT_MOBAGE)
	{
		if(name.size() < 3 || name.size() > 30)
		{
			error_log("[alliance_name_length_error][uid=%u,name=%s,size=%u]", uid, name.c_str(), (unsigned)name.size());
			ERROR_RETURN_MSG(R_ERR_DATA_LIMIT, "alliance_name_length_error");
		}
	}
	if(OpenPlatform::GetType() != PT_FACEBOOK)
	{
		if(!StringFilter::Check(name))
		{
			error_log("[forbidden_alliance_name][uid=%u,name=%s]", uid, name.c_str());
			ERROR_RETURN_MSG(R_ERR_DATA_LIMIT, "forbidden_alliance_name");
		}
	}
	CDataAllianceMapping dbMapping;
	unsigned allianceId;
	ret = dbMapping.GetMapping(name, allianceId);
	if(ret == 0)
	{
		error_log("[duplicate_alliance_name][uid=%u,allianceId=%u,name=%s]", uid, alliance.alliance_id, name.c_str());
		ERROR_RETURN_MSG(R_ERR_DATA_LIMIT, "duplicate_alliance_name");
	}
	else if(ret != R_ERR_NO_DATA)
	{
		error_log("[GetMapping fail][ret=%d,uid=%u,allianceId=%u,name=%s]", ret, uid, alliance.alliance_id, name.c_str());
		DB_ERROR_RETURN_MSG("get_alliance_mapping_fail");
	}

	//原联盟检查
	DataUser user;
	ret = LogicUser::GetUser(uid, user);
	if(ret != 0)
	{
		return ret;
	}
	if(IsAllianceId(user.alliance_id))
	{
		error_log("[user_in_alliance][uid=%u,allianceId=%u]", uid, user.alliance_id);
		ERROR_RETURN_MSG(R_ERR_LOGIC, "in_alliance");
	}

	unsigned oldCash;
	CLogicPay logicPay;
	if(!IsMercenary() && cash != 0)
	{
		ret = logicPay.GetCash(uid, oldCash);
		if(ret != 0)
		{
			return ret;
		}
		if((unsigned)cash > oldCash)
		{
			error_log("[not_enough_cash][uid=%u,cash=%d,oldCash=%u]", uid, cash, oldCash);
			ERROR_RETURN_MSG(R_ERR_LOGIC, "not_enough_cash");
		}
	}

	//添加联盟
	CLogicIdCtrl logicIdCtrl;
	uint64_t u64AllianceId;
	ret = logicIdCtrl.GetNextId(KEY_ALLIANCE_ID_CTRL, u64AllianceId);
	if(ret != 0)
	{
		return ret;
	}
	alliance.alliance_id = (unsigned)u64AllianceId;
	if(IsMercenary())
	{
		alliance.world = user.world;
	}
	else
	{
		alliance.world = 0;
	}
	alliance.name = name;
	alliance.flag = flag;
	alliance.leader_uid = uid;
	alliance.create_time = Time::GetGlobalTime();
	alliance.status = AS_ACTIVE;
	alliance.level = 1;
	alliance.point = 0;
	alliance.rank = alliance.alliance_id - ALLIANCE_ID_START;
	alliance.member_count = 1;
	alliance.enemy_alliance_id = 0;
	alliance.description = description;
	alliance.activity = "[]";
	alliance.extra_data = "{}";
	CDataAlliance dbAlliance;
	ret = dbAlliance.AddAlliance(alliance);
	if(ret != 0)
	{
		fatal_log("[AddAlliance fail][ret=%d,uid=%u,allianceId=%u,name=%s]", ret, uid, alliance.alliance_id, name.c_str());
		DB_ERROR_RETURN_MSG("add_alliance_fail");
	}

	//添加成员
	DataAllianceMember member;
	member.alliance_id = alliance.alliance_id;
	member.uid = uid;
	member.type = AMT_LEADER;
	member.point = 0;
	member.join_time = Time::GetGlobalTime();
	String::Format(member.extra_data, "{\"initpoint\":\"%s\"}", Convert::UInt64ToString(user.point + user.value).c_str());
	CDataAllianceMember dbMember;
	ret = dbMember.AddMember(member);
	if(ret != 0)
	{
		fatal_log("[AddMember fail][ret=%d,uid=%u,allianceId=%u]", ret, uid, alliance.alliance_id);
		dbAlliance.RemoveAlliance(alliance.alliance_id);
		DB_ERROR_RETURN_MSG("add_alliance_member_fail");
	}

	//添加映射
	ret = dbMapping.AddMapping(alliance.name, alliance.alliance_id);
	if(ret != 0)
	{
		fatal_log("[AddMapping fail][ret=%d,uid=%u,allianceId=%u,name=%s]", ret, uid, alliance.alliance_id, name.c_str());
		dbMember.RemoveMember(alliance.alliance_id, uid);
		dbAlliance.RemoveAlliance(alliance.alliance_id);
		DB_ERROR_RETURN_MSG("add_alliance_mapping_fail");
	}

	//设置用户联盟，扣除资源
	if(IsMercenary())
	{
		ret = LogicUser::SetAllianceId(uid, alliance.alliance_id);
	}
	else
	{
		if(useResource)
		{
			if(user.r1 < 2000000)
			{
				user.r1 = 0;
			}
			else
			{
				user.r1 -= 2000000;
			}
			if(user.r2 < 2000000)
			{
				user.r2 = 0;
			}
			else
			{
				user.r2 -= 2000000;
			}
			if(user.r3 < 2000000)
			{
				user.r3 = 0;
			}
			else
			{
				user.r3 -= 2000000;
			}
		}
		user.alliance_id = alliance.alliance_id;
		ret = LogicUser::SetUser(user);
	}
	if(ret != 0)
	{
		error_log("[SetUser fail][ret=%d,uid=%u,allianceId=%u]", ret, uid, alliance.alliance_id);
		dbMapping.RemoveMapping(alliance.name);
		dbMember.RemoveMember(alliance.alliance_id, uid);
		dbAlliance.RemoveAlliance(alliance.alliance_id);
		DB_ERROR_RETURN_MSG("set_user_alliance_fail");
	}
	if(!IsMercenary() && cash != 0)
	{
		ret = logicPay.ChangeCash(uid, "ALCR", -cash);
		if(ret != 0)
		{
			error_log("[ChangeCash fail][ret=%d,uid=%u,allianceId=%u,cash=%d]", ret, uid, alliance.alliance_id, cash);
		}
	}

	return 0;
}

int CLogicAlliance::SetAlliance(const DataAlliance &alliance)
{
	int ret;
	CDataAlliance dbAlliance;
	ret = dbAlliance.SetAlliance(alliance);
	if(ret != 0)
	{
		error_log("[SetAlliance fail][ret=%d,allianceId=%u]", ret, alliance.alliance_id);
		DB_ERROR_RETURN_MSG("set_alliance_fail");
	}
	return 0;
}

int CLogicAlliance::SetAllianceLimit(const DataAlliance &alliance)
{
	int ret;
	CDataAlliance dbAlliance;
	ret = dbAlliance.SetAllianceLimit(alliance);
	if(ret != 0)
	{
		error_log("[SetAllianceLimit fail][ret=%d,allianceId=%u]", ret, alliance.alliance_id);
		DB_ERROR_RETURN_MSG("set_alliance_fail");
	}
	return 0;
}

int CLogicAlliance::GetAlliance(unsigned allianceId, DataAlliance &alliance)
{
	int ret;
	CDataAlliance dbAlliance;
	ret = dbAlliance.GetAlliance(allianceId, alliance);
	if(ret != 0)
	{
		if(ret == R_ERR_NO_DATA)
		{
			ERROR_RETURN_MSG(R_ERR_NO_DATA, "alliance_not_exist");
		}
		error_log("[GetAlliance fail][ret=%d,allianceId=%u]", ret, allianceId);
		DB_ERROR_RETURN_MSG("get_alliance_fail");
	}
	if(alliance.status != AS_ACTIVE)
	{
		ERROR_RETURN_MSG(R_ERR_NO_DATA, "alliance_removed");
	}
	return 0;
}

int CLogicAlliance::GetAllianceLimit(unsigned allianceId, DataAlliance &alliance)
{
	int ret;
	CDataAlliance dbAlliance;
	ret = dbAlliance.GetAllianceLimit(allianceId, alliance);
	if(ret != 0)
	{
		if(ret == R_ERR_NO_DATA)
		{
			ERROR_RETURN_MSG(R_ERR_NO_DATA, "alliance_not_exist");
		}
		error_log("[GetAllianceLimit fail][ret=%d,allianceId=%u]", ret, allianceId);
		DB_ERROR_RETURN_MSG("get_alliance_fail");
	}
	if(alliance.status != AS_ACTIVE)
	{
		ERROR_RETURN_MSG(R_ERR_NO_DATA, "alliance_removed");
	}
	return 0;
}

int CLogicAlliance::RemoveAlliance(unsigned allianceId)
{
	//删除联盟
	int ret;
	DataAlliance alliance;
	ret = GetAllianceLimit(allianceId, alliance);
	if(ret != 0)
	{
		return ret;
	}
	alliance.status = AS_REMOVE;
	ret = SetAllianceLimit(alliance);
	if(ret != 0)
	{
		return ret;
	}
	CDataAllianceMapping dbMapping;
	ret = dbMapping.RemoveMapping(alliance.name);

	//删除联盟成员
	vector<DataAllianceMember> members;
	ret = GetMembers(allianceId, members);
	if(ret != 0)
	{
		return ret;
	}
	CDataAllianceMember dbMember;
	CLogicMessage logicMessage;
	Json::Value message;
	message["id"] = "remove_alliance";
	message["name"] = alliance.name;
	string sMessage = Json::ToString(message);
	for(vector<DataAllianceMember>::iterator itr = members.begin(); itr != members.end(); itr++)
	{
		ret = LogicUser::SetAllianceId(itr->uid, ALLIANCE_ID_NULL);
		if(ret != 0)
		{
			error_log("[SetAllianceId fail][ret=%d,uid=%u,allianceId=%u]", ret, itr->uid, ALLIANCE_ID_NULL);
		}
		ret = dbMember.RemoveMember(allianceId, itr->uid);
		if(ret != 0)
		{
			error_log("[RemoveMember fail][ret=%d,uid=%u,allianceId=%u]", ret, itr->uid, allianceId);
		}
		ret = logicMessage.AddSysMessage(itr->uid, Json::ToString(sMessage));
	}

	//删除消息
	ret = logicMessage.CancelRequest(allianceId);

	return 0;
}

int CLogicAlliance::AddMember(unsigned allianceId, unsigned uid)
{
	int ret;

	//原联盟检查
	DataUser user;
	CHECK_CALL(LogicUser::GetUser(uid, user));
	if(IsAllianceId(user.alliance_id))
	{
		error_log("[user_in_alliance][uid=%u,allianceId=%u,oldAllianceId=%u]", uid, allianceId, user.alliance_id);
		ERROR_RETURN_MSG(R_ERR_LOGIC, "in_alliance");
	}

	//检查人数上限
	DataAlliance alliance;
	ret = GetAllianceLimit(allianceId, alliance);
	if(ret != 0)
	{
		return ret;
	}
	if(IsMercenary())
	{
		if(user.world != alliance.world)
		{
			error_log("[not_in_same_world][uid=%u,allianceid=%u,world=%d,aworld=%d]",
					uid, allianceId, user.world, alliance.world);
			ERROR_RETURN_MSG(R_ERR_LOGIC, "not_in_same_world");
		}
	}
	int limitCount = GetMemberMaxCount(alliance.level);
	if(alliance.member_count >= limitCount)
	{
		error_log("[alliance_member_count_limit][uid=%u,allianceId=%u,count=%d,level=%d]",
				uid, allianceId, alliance.member_count, alliance.level);
		ERROR_RETURN_MSG(R_ERR_DATA_LIMIT, "alliance_member_count_limit");
	}

	//添加成员
	DataAllianceMember member;
	member.alliance_id = allianceId;
	member.uid = uid;
	member.type = AMT_NORMAL;
	member.point = 0;
	member.join_time = Time::GetGlobalTime();
	String::Format(member.extra_data, "{\"initpoint\":\"%s\"}", Convert::UInt64ToString(user.point + user.value).c_str());
	CDataAllianceMember dbMember;
	ret = dbMember.AddMember(member);
	if(ret != 0)
	{
		error_log("[AddMember fail][ret=%d,uid=%u,allianceId=%u]", ret, uid, allianceId);
		DB_ERROR_RETURN_MSG("add_alliance_member_fail");
	}

	//设置用户联盟
	ret = LogicUser::SetAllianceId(uid, allianceId);
	if(ret != 0)
	{
		error_log("[SetAllianceId fail][ret=%d,uid=%u,allianceId=%u]", ret, uid, allianceId);
		dbMember.RemoveMember(allianceId, uid);
		DB_ERROR_RETURN_MSG("set_user_alliance_fail");
	}

	//设置联盟成员数
	alliance.member_count++;
	ret = SetAllianceLimit(alliance);
	if(ret != 0)
	{
		error_log("[set_member_count_fail][ret=%d,uid=%u,allianceId=%u,count=%d]", ret, uid, allianceId, alliance.member_count);
	}

	DataUserBasic userBasic;
	ret = LogicUserBasic::GetUserSmart(uid, OpenPlatform::GetType(), userBasic);
	if(ret == 0)
	{
		Json::Value activity;
		activity["type"] = "add";
		activity["uid"] = uid;
		activity["name"] = userBasic.name;
		activity["photo"] = userBasic.figure_url;
		AddActivity(allianceId, activity);
	}
	return 0;
}

int CLogicAlliance::SetMember(const DataAllianceMember &member)
{
	int ret;
	CDataAllianceMember dbMember;
	ret = dbMember.SetMember(member);
	if(ret != 0)
	{
		error_log("[SetMember fail][ret=%d,allianceId=%u,uid=%u]", ret, member.alliance_id, member.uid);
		DB_ERROR_RETURN_MSG("set_alliance_member_fail");
	}
	return 0;
}

int CLogicAlliance::GetMember(unsigned allianceId, unsigned uid, DataAllianceMember &member)
{
	int ret;
	CDataAllianceMember dbMember;
	ret = dbMember.GetMember(allianceId, uid, member);
	if(ret != 0)
	{
		error_log("[GetMember fail][ret=%d,allianceId=%u,uid=%u]", ret, allianceId, uid);
		DB_ERROR_RETURN_MSG("get_alliance_member_fail");
	}
	return 0;
}

int CLogicAlliance::GetMembers(unsigned allianceId, vector<DataAllianceMember> &members)
{
	int ret;
	CDataAllianceMember dbMember;
	ret = dbMember.GetMembers(allianceId, members);
	if(ret != 0)
	{
		error_log("[GetMembers fail][ret=%d,allianceId=%u]", ret, allianceId);
		DB_ERROR_RETURN_MSG("get_alliance_member_fail");
	}
	return 0;
}

int CLogicAlliance::RemoveMember(unsigned allianceId, unsigned uid)
{
	int ret;

	//检查是否盟主
	DataAlliance alliance;
	ret = GetAllianceLimit(allianceId, alliance);
	if(ret != 0)
	{
		return ret;
	}
	if(alliance.leader_uid == uid)
	{
		ERROR_RETURN_MSG(R_ERR_LOGIC, "is_leader");
	}

	//删除成员
	DataAllianceMember member;
	ret = GetMember(allianceId, uid, member);
	if(ret != 0)
	{
		return ret;
	}
	CDataAllianceMember dbMember;
	ret = dbMember.RemoveMember(allianceId, uid);
	if(ret != 0)
	{
		error_log("[RemoveMember fail][ret=%d,uid=%u,allianceId=%u]", ret, uid, allianceId);
		DB_ERROR_RETURN_MSG("remove_alliance_member_fail");
	}

	//设置用户联盟
	ret = LogicUser::SetAllianceId(uid, ALLIANCE_ID_NULL);
	if(ret != 0)
	{
		error_log("[SetAllianceId fail][ret=%d,uid=%u,allianceId=%u]", ret, uid, ALLIANCE_ID_NULL);
	}

	//设置联盟成员数
	alliance.member_count--;
	if(IsMercenary())
	{
		uint64_t reducePoint = member.point / 2;
		if(alliance.point > reducePoint)
		{
			alliance.point -= reducePoint;
		}
		else
		{
			alliance.point = 0;
		}
	}
	ret = SetAllianceLimit(alliance);
	if(ret != 0)
	{
		error_log("[set_member_count_fail][ret=%d,uid=%u,allianceId=%u,count=%d]", ret, uid, allianceId, alliance.member_count);
	}

	return 0;
}

int CLogicAlliance::ChangeLeader(unsigned allianceId, unsigned newLeaderUid)
{
	int ret;
	if(IsToywar())
	{
		DataUser user;
		ret = LogicUser::GetUser(newLeaderUid, user);
		if(ret != 0)
		{
			return ret;
		}
		if(user.level < 40)
		{
			error_log("[leader_level_dissatisfy][allianceId=%u,newLeaderUid=%u,level=%d]", allianceId, newLeaderUid, user.level);
			ERROR_RETURN_MSG(R_ERR_LOGIC, "leader_level_dissatisfy");
		}
	}
	DataAlliance alliance;
	ret = GetAllianceLimit(allianceId, alliance);
	if(ret != 0)
	{
		return ret;
	}
	if(alliance.leader_uid == newLeaderUid)
	{
		error_log("[is_leader][allianceId=%u,leaderUid=%u,newLeaderUid=%u]", allianceId, alliance.leader_uid, newLeaderUid);
		ERROR_RETURN_MSG(R_ERR_LOGIC, "is_leader");
	}
	DataAllianceMember oldLeader;
	ret = GetMember(allianceId, alliance.leader_uid, oldLeader);
	if(ret != 0)
	{
		return ret;
	}
	DataAllianceMember newLeader;
	ret = GetMember(allianceId, newLeaderUid, newLeader);
	if(ret != 0)
	{
		return ret;
	}

	alliance.leader_uid = newLeaderUid;
	oldLeader.type = AMT_NORMAL;
	newLeader.type = AMT_LEADER;

	ret = SetMember(newLeader);
	if(ret != 0)
	{
		return ret;
	}
	ret = SetMember(oldLeader);
	if(ret != 0)
	{
		return ret;
	}
	ret = SetAllianceLimit(alliance);
	if(ret != 0)
	{
		return ret;
	}

	DataUserBasic userBasicNewLeader;
	ret = LogicUserBasic::GetUserSmart(newLeaderUid, OpenPlatform::GetType(), userBasicNewLeader);
	if(ret == 0)
	{
		Json::Value activity;
		activity["type"] = "change_leader";
		activity["uid"] = newLeaderUid;
		activity["name"] = userBasicNewLeader.name;
		activity["photo"] = userBasicNewLeader.figure_url;
		AddActivity(allianceId, activity);
		Json::Value message;
		message["id"] = "alliance_change_leader";
		message["name"] = userBasicNewLeader.name;
		message["aname"] = alliance.name;
		CLogicMessage logicMessage;
		logicMessage.AddSysMessage(newLeaderUid, Json::ToString(message));
	}

	return 0;
}

int CLogicAlliance::AddPoint(unsigned allianceId, unsigned uid, int point)
{
	int ret;
	CDataAlliance dbAlliance;
	ret = dbAlliance.AddPoint(allianceId, point);
	if(ret != 0)
	{
		error_log("[AddPoint fail][ret=%d,target=alliance,allianceId=%u,uid=%u,point=%d]", ret, allianceId, uid, point);
		DB_ERROR_RETURN_MSG("set_alliance_fail");
	}
	if(IsValidUid(uid))
	{
		CDataAllianceMember dbMember;
		ret = dbMember.AddPoint(allianceId, uid, point);
		if(ret != 0)
		{
			error_log("[AddPoint fail][ret=%d,target=member,allianceId=%u,uid=%u,point=%d]", ret, allianceId, uid, point);
			DB_ERROR_RETURN_MSG("set_member_fail");
		}
	}
	return 0;
}

int CLogicAlliance::AddAttackPoint(unsigned allianceId, unsigned uid, int damage, int attackLevel, int defenceLevel, bool isMainBase)
{
	if(damage <= 0)
	{
		return 0;
	}
	float point;
	point = (float)damage * (float)defenceLevel / 10.0;
	float deltaLevel = defenceLevel - attackLevel;
	if(deltaLevel > 0)
	{
		deltaLevel *= 2;
	}
	deltaLevel = (deltaLevel + 100) / 100.0;
	point *= deltaLevel;
	if (!isMainBase) point /= 3;
	int nPoint = (int)point;
	if(nPoint <= 0)
	{
		nPoint = 1;
	}
	return AddPoint(allianceId, uid, nPoint);
}

int CLogicAlliance::UpdateMemberPoint(unsigned allianceId, unsigned uid, uint64_t point)
{
	int ret;
	DataAllianceMember member;
	ret = GetMember(allianceId, uid, member);
	if(ret != 0)
	{
		return ret;
	}
	Json::Value data;
	Json::FromString(data, member.extra_data);
	int donate = 0;
	Json::GetInt(data, "donate", donate);
	uint64_t initPoint = 0;
	Json::GetUInt64(data, "initpoint", initPoint);
	uint64_t newPoint = (point - initPoint) / 100000 + donate;
	if(newPoint <= member.point)
	{
		return 0;
	}
	return AddPoint(allianceId, uid, newPoint - member.point);
}

int CLogicAlliance::GetRandomAlliances(int count, vector<DataAlliance> &alliances)
{
	int ret;
	if(count <= 0)
	{
		return 0;
	}
	CLogicIdCtrl logicIdCtrl;
	uint64_t u64Id;
	ret = logicIdCtrl.GetCurrentId(KEY_ALLIANCE_ID_CTRL, u64Id);
	if(ret != 0)
	{
		return ret;
	}
	unsigned maxId = (unsigned)u64Id;
	unsigned total = maxId - ALLIANCE_ID_START;
	if(total <= 0)
	{
		return 0;
	}
	int maxTime = count * 3;
	int currTime = 0;
	while(currTime < maxTime && (int)alliances.size() < count)
	{
		currTime++;
		unsigned allianceId = (unsigned)Math::GetRandomInt(total) + ALLIANCE_ID_START + 1;
		bool unique = true;
		for(vector<DataAlliance>::const_iterator itr = alliances.begin(); itr != alliances.end(); itr++)
		{
			if(allianceId == itr->alliance_id)
			{
				unique = false;
				break;
			}
		}
		if(unique)
		{
			DataAlliance alliance;
			ret = GetAlliance(allianceId, alliance);
			if(ret == 0)
			{
				alliances.push_back(alliance);
			}
			else if(ret != R_ERR_NO_DATA)
			{
				return ret;
			}
		}
	}
	return 0;
}

int CLogicAlliance::AddActivity(DataAlliance &alliance, Json::Value activity)
{
	activity["time"] = Time::GetGlobalTime();
	Json::Value data;
	Json::FromString(data, alliance.activity);
	if(!data.isArray())
	{
		data = Json::Value(Json::arrayValue);
	}
	unsigned count = data.size();
	if(count >= ALLIANCE_ACTIVE_COUNT)
	{
		for(unsigned i = 1; i < ALLIANCE_ACTIVE_COUNT; i++)
		{
			data[i - 1] = data[i];
		}
		data[ALLIANCE_ACTIVE_COUNT - 1] = activity;
		data.resize(ALLIANCE_ACTIVE_COUNT);
	}
	else
	{
		data[data.size()] = activity;
	}
	alliance.activity = Json::ToString(data);
	return SetAlliance(alliance);
}

int CLogicAlliance::AddActivity(unsigned &allianceId, Json::Value activity)
{
	int ret;
	DataAlliance alliance;
	ret = GetAlliance(allianceId, alliance);
	if(ret != 0)
	{
		return ret;
	}
	return AddActivity(alliance, activity);
}

int CLogicAlliance::AddLastAttack(unsigned allianceId, unsigned uid, const Json::Value &attackData)
{
	int ret;
	unsigned attackUid;
	if(!Json::GetUInt(attackData, "a_uid", attackUid))
	{
		return R_ERR_PARAM;
	}
	DataAllianceMember member;
	ret = GetMember(allianceId, uid, member);
	if(ret != 0)
	{
		return ret;
	}
	Json::Value data;
	Json::FromString(data, member.extra_data);
	Json::Value &attacks = data["attacks"];
	if(!attacks.isArray())
	{
		attacks = Json::Value(Json::arrayValue);
	}
	for(unsigned i = 0; i < attacks.size();)
	{
		unsigned currAttackUid;
		if(Json::GetUInt(attacks[i], "a_uid", currAttackUid))
		{
			if(currAttackUid == attackUid)
			{
				for(unsigned j = i + 1; j < attacks.size(); j++)
				{
					attacks[j - 1] = attacks[j];
				}
				attacks.resize(attacks.size() - 1);
			}
			else
			{
				i++;
			}
		}
		else
		{
			i++;
		}
	}
	if(attacks.size() >= ALLIANCE_MEMBER_ATTACK_COUNT)
	{
		for(unsigned i = 1; i < ALLIANCE_MEMBER_ATTACK_COUNT; i++)
		{
			attacks[i - 1] = attacks[i];
		}
		attacks.resize(ALLIANCE_MEMBER_ATTACK_COUNT - 1);
	}
	attacks[attacks.size()] = attackData;
	member.extra_data = Json::ToString(data);
	return SetMember(member);
}

bool CLogicAlliance::IsInSameAlliance(unsigned uid, unsigned targetUid)
{
	int ret;
	unsigned allianceId;
	ret = LogicUser::GetAllianceId(uid, allianceId);
	if(ret != 0)
	{
		return false;
	}
	if(!IsAllianceId(allianceId))
	{
		return false;
	}
	unsigned targetAllianceId;
	ret = LogicUser::GetAllianceId(targetUid, targetAllianceId);
	if(ret != 0)
	{
		return false;
	}
	return allianceId == targetAllianceId;
}

int CLogicAlliance::Donate(unsigned uid, unsigned allianceId, int r1, int r2, int r3, int r4, int cash)
{
	if(r1 < 0 || r2 < 0 || r3 < 0 || r4 < 0 || cash < 0)
	{
		error_log("[donate_param_error][uid=%u,r1=%d,r2=%d,r3=%d,r4=%d,cash=%d]", uid, r1, r2, r3, r4, cash);
		PARAM_ERROR_RETURN();
	}
	int ret;

	DataAllianceMember member;
	ret = GetMember(allianceId, uid, member);
	if(ret != 0)
	{
		return ret;
	}

	DataUser user;
	ret = LogicUser::GetUser(uid, user);
	if(ret != 0)
	{
		return ret;
	}

	if(cash != 0 && member.type != AMT_LEADER && member.type != AMT_MANAGER && user.level < 40)
	{
		error_log("[can_not_donate_cash][uid=%u,aid=%u,type=%d,level=%d,cash=%d]",
				uid, allianceId, member.type, user.level, cash);
		ERROR_RETURN_MSG(R_ERR_LOGIC, "can_not_donate_cash");
	}

	if(user.alliance_id != allianceId)
	{
		error_log("[user_not_in_alliance][uid=%u,allianceId=%u,realAllianceId=%u]", uid, allianceId, user.alliance_id);
		PARAM_ERROR_RETURN_MSG("no_in_alliance");
	}

	if( (unsigned)r1 > user.r1 || (unsigned)r2 > user.r2 ||
		(unsigned)r3 > user.r3 || (unsigned)r4 > user.r4 )
	{
		error_log("[donate_not_enough_resource][uid=%u,r1=%d,r2=%d,r3=%d,r4=%d,rr1=%u,rr2=%u,rr3=%u,rr4=%u]",
				uid, r1, r2, r3, r4, user.r1, user.r2, user.r3, user.r4);
		ERROR_RETURN_MSG(R_ERR_LOGIC, "not_enough_resource");
	}
	unsigned userCash;
	CLogicPay logicPay;
	if(cash > 0)
	{
		ret = logicPay.GetCash(uid, userCash);
		if(ret != 0)
		{
			return ret;
		}
		if((unsigned)cash > userCash)
		{
			error_log("[donate_not_enough_cash][uid=%u,cash=%d,userCash=%u]", uid, cash, userCash);
			ERROR_RETURN_MSG(R_ERR_LOGIC, "pay_overspend");
		}
	}

	Json::Value data;
	Json::FromString(data, member.extra_data);
	int donate = 0;
	Json::GetInt(data, "donate", donate);
	int donateAdd = 0;
	if(IsMercenary())
	{
		donateAdd = (r1 + r2 + r3 + r4) / 100000 + cash;
		if(donateAdd > 0)
		{
			member.point += donateAdd;
			CDataAlliance dbAlliance;
			ret = dbAlliance.AddPoint(allianceId, donateAdd);
			if(ret != 0)
			{
				error_log("[AddPoint fail][ret=%d,allianceId=%u,uid=%u,point=%d]",  ret, allianceId, uid, donateAdd);
				DB_ERROR_RETURN_MSG("set_alliance_fail");
			}
		}
	}
	else
	{
		donateAdd = (r1 + r2 + r3 + r4) / 10000 + cash;
	}
	if(donateAdd > 0)
	{
		donate += donateAdd;
		data["donate"] = donate;
		member.extra_data = Json::ToString(data);
		ret = SetMember(member);
		if(ret != 0)
		{
			return ret;
		}
	}

	ret = ChangeResource(allianceId, r1, r2, r3, r4, cash, "ALRECV");
	if(ret != 0)
	{
		return ret;
	}

	if(r1 > 0 || r2 > 0 || r3 > 0 || r4 > 0)
	{
		ret = LogicUser::ChangeResource(uid, -r1, -r2, -r3, -r4);
		if(ret != 0)
		{
			error_log("[change_user_resource_fail][uid=%u,r1=%d,r2=%d,r3=%d,r4=%d]", uid, r1, r2, r3, r4);
		}
	}
	if(cash > 0)
	{
		ret = logicPay.ChangeCash(uid, "ADNT", -cash);
		if(ret != 0)
		{
			error_log("[change_user_cash_fail][uid=%u,cash=%d]", uid, cash);
		}
	}
	DataUserBasic userBasic;
	ret = LogicUserBasic::GetUserSmart(uid, OpenPlatform::GetType(), userBasic);
	if(ret == 0)
	{
		Json::Value activity;
		activity["type"] = "donate";
		activity["uid"] = uid;
		activity["name"] = userBasic.name;
		activity["photo"] = userBasic.figure_url;
		activity["r1"] = r1;
		activity["r2"] = r2;
		activity["r3"] = r3;
		activity["r4"] = r4;
		activity["cash"] = cash;
		AddActivity(allianceId, activity);
	}
	return 0;
}

int CLogicAlliance::ChangeResource(unsigned allianceId, int r1, int r2, int r3, int r4, int cash, const string &reason)
{
	int ret;
	DataAlliance alliance;
	if(r1 != 0 || r2 != 0 || r3 != 0 || r4 != 0)
	{
		ret = GetAlliance(allianceId, alliance);
		if(ret != 0)
		{
			return ret;
		}
		Json::Value data;
		Json::FromString(data, alliance.extra_data);
		Json::Value &resource = data["resource"];

#define CHANGE_ALLIANCE_RESOURCE(res)	\
		if(res != 0)	\
		{	\
			uint64_t old##res = 0;	\
			Json::GetUInt64(resource, #res, old##res);	\
			if(res < 0 && (unsigned)-res > old##res)	\
			{	\
				error_log("[not_enough_resource][allianceId=%u," #res "=%d,old" #res "=%llu]", allianceId, res, old##res);	\
				ERROR_RETURN_MSG(R_ERR_DATA_LIMIT, "not_enough_resource");	\
			}	\
			old##res += res;	\
			resource[#res] = Convert::UInt64ToString(old##res);	\
		}	\

		CHANGE_ALLIANCE_RESOURCE(r1);
		CHANGE_ALLIANCE_RESOURCE(r2);
		CHANGE_ALLIANCE_RESOURCE(r3);
		CHANGE_ALLIANCE_RESOURCE(r4);

		alliance.extra_data = Json::ToString(data);
	}

	bool hasCashData = true;
	unsigned allianceCash = 0;
	CLogicPay logicPay;
	if(cash != 0)
	{
		ret = logicPay.GetCash(allianceId, allianceCash);
		if(ret != 0)
		{
			if(ret != R_ERR_NO_DATA)
			{
				return ret;
			}
			hasCashData = false;
		}
		if(cash < 0 && (unsigned)-cash > allianceCash)
		{
			error_log("[pay overspend][allianceId=%u,cash=%u,delta=%d]", allianceId, allianceCash, cash);
			ERROR_RETURN_MSG(R_ERR_DATA_LIMIT, "pay_overspend");
		}
	}

	if(r1 != 0 || r2 != 0 || r3 != 0 || r4 != 0)
	{
		ret = SetAlliance(alliance);
		if(ret != 0)
		{
			return ret;
		}
	}
	if(cash != 0)
	{
		if(hasCashData)
		{
			ret = logicPay.ChangeCash(allianceId, reason, cash);
		}
		else
		{
			ret = logicPay.AddUser(allianceId, cash);
		}
		if(ret != 0)
		{
			return ret;
		}
	}
	return 0;
}

int CLogicAlliance::SetAllianceData(unsigned uid, unsigned allianceId, const Json::Value &data)
{
	int ret;
	DataAlliance alliance;
	ret = GetAlliance(allianceId, alliance);
	if(ret != 0)
	{
		return ret;
	}
//	if(alliance.leader_uid != uid)
//	{
//		error_log("[is_not_leader][aid=%u,uid=%u,luid=%u]", allianceId, uid, alliance.leader_uid);
//		ERROR_RETURN_MSG(R_ERR_LOGIC, "is_not_leader");
//	}
	Json::Value extraData;
	Json::FromString(extraData, alliance.extra_data);
	extraData["cdata"] = data;
	alliance.extra_data = Json::ToString(extraData);
	ret = SetAlliance(alliance);
	if(ret != 0)
	{
		return ret;
	}
	return 0;
}

int CLogicAlliance::SetMemberData(unsigned uid, unsigned allianceId, const Json::Value &data)
{
	int ret;
	DataAllianceMember member;
	ret = GetMember(allianceId, uid, member);
	if(ret != 0)
	{
		return ret;
	}
	Json::Value extraData;
	Json::FromString(extraData, member.extra_data);
	extraData["cdata"] = data;
	member.extra_data = Json::ToString(extraData);
	ret = SetMember(member);
	if(ret != 0)
	{
		return ret;
	}
	return 0;
}

bool CLogicAlliance::IsLeader(unsigned uid, unsigned allianceId)
{
	int ret;
	DataAlliance alliance;
	ret = GetAllianceLimit(allianceId, alliance);
	if(ret != 0)
	{
		return false;
	}
	return alliance.leader_uid == uid;
}

bool CLogicAlliance::IsManager(unsigned uid, unsigned allianceId)
{
	int ret;
	int type;
	CDataAllianceMember dbMember;
	ret = dbMember.GetMemberType(allianceId, uid, type);
	if(ret != 0)
	{
		error_log("[GetMemberType fail][ret=%d,allianceId=%u,uid=%u]", ret, allianceId, uid);
		return false;
	}
	return type == AMT_LEADER || type == AMT_MANAGER;
}

int CLogicAlliance::Upgrade(unsigned uid, unsigned allianceId, int r1, int r2, int r3, int r4, int cash, int &level)
{
	int ret;
	if(r1 < 0 || r2 < 0 || r3 < 0 || r4 < 0 || cash < 0)
	{
		error_log("[upgrade_param_error][uid=%u,r1=%d,r2=%d,r3=%d,r4=%d,cash=%d]", uid, r1, r2, r3, r4, cash);
		return R_ERR_PARAM;
	}

	if(!IsManager(uid, allianceId))
	{
		error_log("[is_not_leader][aid=%u,uid=%u]", allianceId, uid);
		ERROR_RETURN_MSG(R_ERR_LOGIC, "is_not_leader");
	}

	DataAlliance alliance;
	ret = GetAllianceLimit(allianceId, alliance);
	if(ret != 0)
	{
		return ret;
	}
//	if(alliance.leader_uid != uid)
//	{
//		error_log("[is_not_leader][aid=%u,uid=%u,luid=%u]", allianceId, uid, alliance.leader_uid);
//		ERROR_RETURN_MSG(R_ERR_LOGIC, "is_not_leader");
//	}
	if(alliance.level != level)
	{
		error_log("[level_mismatch][uid=%u,aid=%u,level=%d,rlevel=%d]", uid, allianceId, level, alliance.level);
		PARAM_ERROR_RETURN();
	}
	if(level <= 0 || level >= 10)
	{
		error_log("[level_out_range][uid=%u,aid=%u,level=%d]", uid, allianceId, level);
		PARAM_ERROR_RETURN();
	}
	static uint64_t pointRequire[] = {
			0, 180000, 300000, 480000, 720000,
			1020000, 1380000, 1800000, 2280000, 2820000
	};
	if(alliance.point < pointRequire[level])
	{
		error_log("[point_require][uid=%u,aid=%u,level=%d,point=%llu]", uid, allianceId, level, alliance.point);
		ERROR_RETURN_MSG(R_ERR_DATA_LIMIT, "point_require");
	}
	if(alliance.member_count < GetMemberMaxCount(level))
	{
		error_log("[member_count_require][uid=%u,aid=%u,level=%d,mc=%d]", uid, allianceId, level, alliance.member_count);
		ERROR_RETURN_MSG(R_ERR_DATA_LIMIT, "member_count_require");
	}
	ret = ChangeResource(allianceId, -r1, -r2, -r3, -r4, -cash, "ALUP");
	if(ret != 0)
	{
		return ret;
	}
	level++;
	alliance.level = level;
	ret = SetAllianceLimit(alliance);
	if(ret != 0)
	{
		fatal_log("[set_level_fail][uid=%u,aid=%u,level=%d,r1=%d,r2=%d,r3=%d,r4=%d,cash=%d]",
				uid, allianceId, level, r1, r2, r3, r4, cash);
		return ret;
	}
	return 0;
}

int CLogicAlliance::RemoveMember(unsigned uid, unsigned allianceId, unsigned uidRemove)
{
	int ret;
	DataUser userRemove;
	ret = LogicUser::GetUser(uidRemove, userRemove);
	if(ret != 0)
	{
		return ret;
	}
	if(userRemove.alliance_id != allianceId)
	{
		PARAM_ERROR_RETURN();
	}
	DataAlliance alliance;
	ret = GetAllianceLimit(allianceId, alliance);
	if(ret != 0)
	{
		return ret;
	}
	if(uidRemove != uid)
	{
		if(alliance.leader_uid != uid && !IsManager(uid, allianceId))
		{
			error_log("[is_not_leader][aid=%u,uid=%u]", allianceId, uid);
			ERROR_RETURN_MSG(R_ERR_LOGIC, "is_not_leader");
		}
	}
	ret = RemoveMember(allianceId, uidRemove);
	if(ret != 0)
	{
		return ret;
	}

	//消息通知
	DataUserBasic userBasicRemove;
	ret = LogicUserBasic::GetUserSmart(uidRemove, OpenPlatform::GetType(), userBasicRemove);
	if(ret == 0)
	{
		Json::Value activity;
		if(uidRemove == uid)
		{
			activity["type"] = "exit";
		}
		else
		{
			activity["type"] = "remove";
		}
		activity["uid"] = uid;
		activity["name"] = userBasicRemove.name;
		activity["photo"] = userBasicRemove.figure_url;
		AddActivity(allianceId, activity);

		if(uidRemove != uid)
		{
			Json::Value message;
			message["id"] = "alliance_remove_member";
			message["name"] = alliance.name;
			CLogicMessage logicMessage;
			logicMessage.AddSysMessage(uidRemove, Json::ToString(message));
		}
	}
	return 0;
}

int CLogicAlliance::SetMemberType(unsigned uid, unsigned allianceId, unsigned memberUid, int type)
{
	if(type != AMT_NORMAL && type != AMT_MANAGER)
	{
		PARAM_ERROR_RETURN();
	}
	int ret;
	DataAlliance alliance;
	ret = GetAllianceLimit(allianceId, alliance);
	if(ret != 0)
	{
		return ret;
	}
	if(memberUid == alliance.leader_uid)
	{
		ERROR_RETURN_MSG(R_ERR_LOGIC, "is_leader");
	}
	if(alliance.leader_uid != uid)
	{
		error_log("[is_not_leader][aid=%u,uid=%u]", allianceId, uid);
		ERROR_RETURN_MSG(R_ERR_LOGIC, "is_not_leader");
	}
	int oldType;
	CDataAllianceMember dbMember;
	ret = dbMember.GetMemberType(allianceId, memberUid, oldType);
	if(ret != 0)
	{
		error_log("[GetMemberType fail][ret=%d,allianceId=%u,uid=%u]", ret, allianceId, uid);
		return ret;
	}
	if(oldType == type)
	{
		return 0;
	}
	ret = dbMember.SetMemberType(allianceId, memberUid, type);
	if(ret != 0)
	{
		error_log("[SetMemberType fail][ret=%d,allianceId=%u,uid=%u,type=%d]", ret, allianceId, uid, type);
		return ret;
	}

	//消息通知
	DataUserBasic userBasic;
	ret = LogicUserBasic::GetUserSmart(memberUid, OpenPlatform::GetType(), userBasic);
	if(ret == 0)
	{
		Json::Value activity;
		activity["type"] = "settype";
		activity["name"] = userBasic.name;
		AddActivity(allianceId, activity);

		if(memberUid != uid)
		{
			Json::Value message;
			message["id"] = "allience_set_member_type";
			message["name"] = alliance.name;
			message["type"] = type;
			CLogicMessage logicMessage;
			logicMessage.AddSysMessage(memberUid, Json::ToString(message));
		}
	}
	return 0;
}

int CLogicAlliance::ProcessRequest(const DataMessage &request, unsigned from, unsigned to, const string &type, int action, const Json::Value &data)
{
	int ret;
	if(type == "alliance_join")
	{
		if(action != MS_ACCEPT)
		{
			return 0;
		}
		if(!IsValidUid(request.from_uid) || !IsAllianceId(request.to_uid))
		{
			error_log("[error_request][from=%u,to=%u,type=%s,action=%d]", request.from_uid, request.to_uid, type.c_str(), action);
			return R_ERR_PARAM;
		}
		return AddMember(request.to_uid, request.from_uid);
	}
	else if(type == "alliance_invite")
	{
		if(action != MS_ACCEPT)
		{
			return 0;
		}
		if(!IsValidUid(request.from_uid) || !IsValidUid(request.to_uid))
		{
			error_log("[error_request][from=%u,to=%u,type=%s,action=%d]",
					request.from_uid, request.to_uid, type.c_str(), action);
			return R_ERR_PARAM;
		}
		unsigned allianceId;
		if(!Json::GetUInt(data, "aid", allianceId) || !IsAllianceId(allianceId))
		{
			error_log("[error_request][from=%u,to=%u,type=%s,action=%d]",
					request.from_uid, request.to_uid, type.c_str(), action);
			return R_ERR_PARAM;
		}
		unsigned fromAllianceId;
		ASSERT_CALL(LogicUser::GetAllianceId(request.from_uid, fromAllianceId));
		if(fromAllianceId != allianceId)
		{
			error_log("[error_request][from=%u,to=%u,type=%s,action=%d,aid=%u,fromaid=%u]",
					request.from_uid, request.to_uid, type.c_str(), action, allianceId, fromAllianceId);
			PARAM_ERROR_RETURN_MSG("alliance_id_mismatch");
		}
		return AddMember(allianceId, request.to_uid);
	}
	return 0;
}

int CLogicAlliance::GetAllianceJson(unsigned uid, unsigned allianceId, Json::Value &value)
{
	int ret;
	DataAlliance alliance;
	ret = GetAlliance(allianceId, alliance);
	if(ret != 0)
	{
		return ret;
	}
	value["aid"] = alliance.alliance_id;
	if(IsMercenary())
	{
		value["world"] = alliance.world;
	}
	value["name"] = alliance.name;
	value["flag"] = alliance.flag;
	value["leader"] = alliance.leader_uid;
	value["level"] = alliance.level;
	value["point"] = Convert::UInt64ToString(alliance.point);
	value["rank"] = alliance.rank;
	value["mc"] = alliance.member_count;
	value["enemyid"] = alliance.enemy_alliance_id;
	value["enemyname"] = alliance.enemy_alliance_name;
	value["createtime"] = alliance.create_time;
	value["desc"] = alliance.description;
	value["notice"] = alliance.notice;
	Json::FromString(value["activity"], alliance.activity);
	Json::FromString(value["data"], alliance.extra_data);
	DataUserBasic userBasic;
	ret = LogicUserBasic::GetUserSmart(alliance.leader_uid, OpenPlatform::GetType(), userBasic);
	if(ret == 0)
	{
		value["leadername"] = userBasic.name;
	}
	DataUser user;
	ret = LogicUser::GetUser(alliance.leader_uid, user);
	if(ret == 0)
	{
		value["leaderlevel"] = user.level;
	}

	CLogicPay logicPay;
	unsigned cash = 0;
	ret = logicPay.GetCash(allianceId, cash);
	value["cash"] =cash;

	map<unsigned, int> interacts;
	if(IsMercenary())
	{
		CLogicUserInteract logicInteract;
		ret = logicInteract.GetFriendInteracts(uid, interacts);
	}

	Json::Value &membersData = value["members"];
	membersData = Json::Value(Json::arrayValue);
	vector<DataAllianceMember> members;
	ret = GetMembers(allianceId, members);
	for(vector<DataAllianceMember>::const_iterator itr = members.begin(); itr != members.end(); itr++)
	{
		Json::Value &member = membersData[membersData.size()];
		member["uid"] = itr->uid;
		member["type"] = itr->type;
		member["point"] = Convert::UInt64ToString(itr->point);
		member["jt"] = itr->join_time;
		Json::FromString(member["data"], itr->extra_data);

		ret = LogicUserBasic::GetUserSmart(itr->uid, OpenPlatform::GetType(), userBasic);
		if(ret == 0)
		{
			member["name"] = userBasic.name;
		}

		ret = LogicUser::GetUser(itr->uid, user);
		if(ret == 0)
		{
			member["level"] = user.level;
			member["online"] = (Time::GetGlobalTime() - ONLINE_TIMEOUT < user.last_active_time) ? 1 : 0;
			member["lat"] = user.last_active_time;
			if(!IsMercenary())
			{
				member["world"] = user.world;
			}
		}

		if(IsMercenary())
		{
			map<unsigned, int>::iterator itrInteract = interacts.find(itr->uid);
			if(itrInteract != interacts.end())
			{
				member["ic"] = itrInteract->second;
			}
		}
	}

	//sync member count
	if((int)members.size() != alliance.member_count)
	{
		info_log("[member_count_mismatch][allianceId=%u,mc=%d,rmc=%d]",
				allianceId, alliance.member_count, (int)members.size());
		alliance.member_count = members.size();
		ret = SetAllianceLimit(alliance);
	}

	return 0;
}

int CLogicAlliance::SearchAllianceJson(const string &name, Json::Value &value)
{
	int ret;
	CDataAllianceMapping dbMapping;
	unsigned allianceId;
	ret = dbMapping.GetMapping(name, allianceId);
	if(ret != 0)
	{
		if(ret == R_ERR_NO_DATA)
		{
			ERROR_RETURN_MSG(R_ERR_NO_DATA, "alliance_not_exist");
		}
		error_log("[GetMapping fail][ret=%d,name=%s]", ret, name.c_str());
		DB_ERROR_RETURN_MSG("get_alliance_mapping_fail");
	}

	DataAlliance alliance;
	ret = GetAllianceLimit(allianceId, alliance);
	if(ret != 0)
	{
		return ret;
	}
	value["aid"] = alliance.alliance_id;
	if(IsMercenary())
	{
		value["world"] = alliance.world;
	}
	value["name"] = alliance.name;
	value["flag"] = alliance.flag;
	value["leader"] = alliance.leader_uid;
	value["level"] = alliance.level;
	value["point"] = Convert::UInt64ToString(alliance.point);
	value["rank"] = alliance.rank;
	value["mc"] = alliance.member_count;
	value["enemyid"] = alliance.enemy_alliance_id;
	value["enemyname"] = alliance.enemy_alliance_name;
	value["createtime"] = alliance.create_time;
	value["desc"] = alliance.description;
	value["notice"] = alliance.notice;

	DataUserBasic userBasic;
	ret = LogicUserBasic::GetUserSmart(alliance.leader_uid, OpenPlatform::GetType(), userBasic);
	if(ret == 0)
	{
		value["leadername"] = userBasic.name;
	}

	DataUser user;
	ret = LogicUser::GetUser(alliance.leader_uid, user);
	if(ret == 0)
	{
		value["leaderlevel"] = user.level;
	}

	return 0;
}

int CLogicAlliance::GetRandomAlliancesJson(Json::Value &value)
{
	int ret;
	vector<DataAlliance> alliances;
	ret = GetRandomAlliances(GET_ALLIANCE_COUNT, alliances);
	if(ret != 0)
	{
		return ret;
	}
	for(vector<DataAlliance>::const_iterator itr = alliances.begin(); itr != alliances.end(); itr++)
	{
		Json::Value &alliance = value[value.size()];
		alliance["aid"] = itr->alliance_id;
		if(IsMercenary())
		{
			alliance["world"] = itr->world;
		}
		alliance["name"] = itr->name;
		alliance["flag"] = itr->flag;
		alliance["leader"] = itr->leader_uid;
		alliance["level"] = itr->level;
		alliance["point"] = Convert::UInt64ToString(itr->point);
		alliance["rank"] = itr->rank;
		alliance["mc"] = itr->member_count;
		alliance["enemyid"] = itr->enemy_alliance_id;
		alliance["enemyname"] = itr->enemy_alliance_name;
		alliance["createtime"] = itr->create_time;
		alliance["desc"] = itr->description;

		DataUserBasic userBasic;
		ret = LogicUserBasic::GetUserSmart(itr->leader_uid, OpenPlatform::GetType(), userBasic);
		if(ret == 0)
		{
			alliance["leadername"] = userBasic.name;
		}

		DataUser user;
		ret = LogicUser::GetUser(itr->leader_uid, user);
		if(ret == 0)
		{
			alliance["leaderlevel"] = user.level;
		}
	}
	return 0;
}

static bool InteractAttackTimeCompare(const DataUserInteract &left, const DataUserInteract &right)
{
	return left.last_attack_time > right.last_attack_time;
}

int CLogicAlliance::GetAllianceEnemys(unsigned allianceId, unsigned startIndex, unsigned count, Json::Value &value)
{
	int ret;
	if(!IsAllianceId(allianceId))
	{
		return R_ERR_PARAM;
	}
	vector<DataUserInteract> interacts;
	CDataUserInteract dbInteract;
	ret = dbInteract.GetInteractsAttackAfter(allianceId, Time::GetGlobalTime() - ALLIANCE_ENEMY_TIME, interacts);
	if(ret != 0)
	{
		error_log("[GetInteractsAttackAfter fail][ret=%d,allianceId=%u,time=%u]",
				ret, allianceId, Time::GetGlobalTime() - ALLIANCE_ENEMY_TIME);
		DB_ERROR_RETURN_MSG("get_user_interact_fail");
	}
	vector<DataUserInteract>::iterator itr;
	itr = interacts.begin();
	while(itr != interacts.end())
	{
		if(!IsValidUid(itr->opposite_uid) || itr->attack_from <= 0)
		{
			itr = interacts.erase(itr);
		}
		else
		{
			itr++;
		}
	}
	value["total"] = (unsigned)interacts.size();
	if(interacts.size() <= startIndex)
	{
		ERROR_RETURN_MSG(R_ERR_NO_DATA, "no_more_enemys");
	}
	sort(interacts.begin(), interacts.end(), InteractAttackTimeCompare);

	Json::Value &enemys = value["enemys"];
	enemys = Json::Value(Json::arrayValue);
	for(size_t i = startIndex; i < interacts.size() && enemys.size() < count; i++)
	{
		Json::Value &enemy = enemys[enemys.size()];
		const DataUserInteract &interact = interacts[i];
		enemy["uid"] = interact.opposite_uid;
		enemy["attackfrom"] = interact.attack_from;
		enemy["attackto"] = interact.attack_to;
		enemy["retaliatecount"] = interact.retaliate_count;
		enemy["lastattacktime"] = interact.last_attack_time;

		DataUserBasic userBasic;
		ret = LogicUserBasic::GetUserSmart(interact.opposite_uid, OpenPlatform::GetType(), userBasic);
		if(ret == 0)
		{
			enemy["name"] = userBasic.name;
		}

		DataUser user;
		ret = LogicUser::GetUser(interact.opposite_uid, user);
		if(ret == 0)
		{
			enemy["level"] = user.level;
			enemy["online"] = (Time::GetGlobalTime() - ONLINE_TIMEOUT < user.last_active_time) ? 1 : 0;
			enemy["lat"] = user.last_active_time;
			enemy["world"] = user.world;
		}

		if(IsAllianceId(user.alliance_id))
		{
			DataAlliance alliance;
			ret = GetAllianceLimit(user.alliance_id, alliance);
			if(ret == 0)
			{
				enemy["aid"] = alliance.alliance_id;
				enemy["aname"] = alliance.name;
				enemy["aflag"] = alliance.flag;
			}
		}
	}
	return 0;
}

static int GetSuggestedUserJson(unsigned allianceId, int world, unsigned uid, bool isFriend, Json::Value &data)
{
	int ret;
	DataUser user;
	CHECK_CALL(LogicUser::GetUser(uid, user));
	if(IsAllianceId(user.alliance_id) || user.world == 0)
	{
		return R_ERR_LOGIC;
	}
	if(!isFriend && user.world != world)
	{
		return R_ERR_LOGIC;
	}
	DataUserBasic userBasic;
	CHECK_CALL(LogicUserBasic::GetUserSmart(uid, OpenPlatform::GetType(), userBasic));
	Json::Value &userData = data[data.size()];
	userData["uid"] = user.uid;
	userData["world"] = user.world;
	userData["online"] = IsOnline(user.last_active_time) ? 1 : 0;
	userData["level"] = user.level;
	userData["point"] = Convert::UInt64ToString(user.point + user.value);
	userData["name"] = userBasic.name;
	userData["pt"] = userBasic.platform;
	userData["photo"] = userBasic.figure_url;
	userData["friend"] = isFriend ? 1 : 0;
	return 0;
}

int CLogicAlliance::GetSuggestedUsers(unsigned uid, unsigned allianceId, int count, Json::Value &data)
{
	int ret;
	if(!IsManager(uid, allianceId))
	{
		error_log("[is_not_leader][aid=%u,uid=%u]", allianceId, uid);
		ERROR_RETURN_MSG(R_ERR_LOGIC, "is_not_leader");
	}
	CDataAlliance dbAlliance;
	int world;
	ret = dbAlliance.GetWorld(allianceId, world);
	if(ret != 0)
	{
		error_log("[GetWorld fail][ret=%d,allianceId=%u]", ret, allianceId);
		DB_ERROR_RETURN_MSG("get_alliance_fail");
	}
	if(world <= 0)
	{
		error_log("[not_in_world][aid=%u,uid=%u,world=%d]", allianceId, uid, world);
		ERROR_RETURN_MSG(R_ERR_LOGIC, "not_in_world");
	}
	UidList users;
	CHECK_CALL(LogicFriend::GetFriends(uid, OpenPlatform::GetType(), users));
	int currCount = 0;
	for(UidList::iterator itr = users.begin(); itr != users.end(); itr++)
	{
		if(*itr != uid)
		{
			ret = GetSuggestedUserJson(allianceId, world, *itr, true, data);
			if(ret == 0)
			{
				currCount++;
				if(currCount >= count)
				{
					return 0;
				}
			}
		}
	}
	CDataWorldUser *pDbWorldUser = LogicWorld::GetDataWorldUser();
	if(pDbWorldUser == NULL)
	{
		return 0;
	}
	int maxTime = (count - currCount) * 4 / 3 + 1;
	for(int i = 0; i < maxTime; i++)
	{
		unsigned suggestedUid;
		ret = pDbWorldUser->GetUser(suggestedUid, world);
		if(ret != 0)
		{
			return 0;
		}
		if(find(users.begin(), users.end(), suggestedUid) == users.end() && uid != suggestedUid)
		{
			users.push_back(suggestedUid);
			ret = GetSuggestedUserJson(allianceId, world, suggestedUid, false, data);
			if(ret == 0)
			{
				currCount++;
				if(currCount >= count)
				{
					return 0;
				}
			}
			else if(ret == R_ERR_LOGIC)
			{
				pDbWorldUser->RemoveUser(suggestedUid);
			}
		}
	}
	return 0;
}

int CLogicAlliance::GetMemberMaxCount(int level)
{
	if(IsMercenary())
	{
		return 50;
	}
	int count = 0;
	count = level * 5 + 25;
	if(count > 60)
	{
		count = 60;
	}
	return count;
}

