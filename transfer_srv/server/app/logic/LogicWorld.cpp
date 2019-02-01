/*
 * LogicWorld.cpp
 *
 *  Created on: 2012-2-23
 *      Author: dada
 */

#include "LogicWorld.h"

#define WILD_FORCE_FREE_TIMEOUT (60 * 60)

CWorldPoint::CWorldPoint() :
	World(0),
	X(0),
	Y(0)
{
}

CWorldPoint::CWorldPoint(unsigned position)
{
	FromUInt(position);
}

CWorldPoint::CWorldPoint(unsigned world, int x, int y) :
	World(world),
	X(x),
	Y(y)
{
}

int CWorldPoint::GetDistance(const CWorldPoint &to) const
{
	//int dx = Math::Abs(((X - to.X) * 2) + ((Y - to.Y) % 2));
	int dx = Math::Abs(((X<<1) + (Y&1)) - ((to.X<<1) + (to.Y&1)));
	int dy = Math::Abs(Y - to.Y);
	return (dx + dy) >> 1;
}

void CWorldPoint::FromUInt(unsigned position)
{
	World = (position >> 24) & 0xff;
	X = (position >> 12) & 0xfff;
	Y = position & 0xfff;
}

unsigned CWorldPoint::ToUInt() const
{
	return (((unsigned)World) << 24) | (((unsigned)X & 0xfff) << 12) | (((unsigned)Y) & 0xfff);
}

unsigned LogicWorld::GetWorldSize()
{
	bool s_bInitWorldSize = false;
	static unsigned s_worldSize = 0;
	if(!s_bInitWorldSize)
	{
		s_bInitWorldSize = true;
		s_worldSize = Config::GetIntValue(CONFIG_WORLD_SIZE);
		if(s_worldSize <= 0)
		{
			fatal_log("[config_world_size_error][worldsize=%u]", s_worldSize);
			s_worldSize = 800;
		}
	}
	return s_worldSize;
}

static int GetRandomNpc(DataBaseExtra &baseExtra)
{
	int ret;
	static bool s_bInitNpcList = false;
	static vector<DataBaseExtra> s_npcList;
	if(!s_bInitNpcList)
	{
		s_bInitNpcList = true;
		string sNpcIds = Config::GetValue(CONFIG_WORLD_NPC);
		vector<string> npcIds;
		CBasic::StringSplitTrim(sNpcIds, ",", npcIds);
		s_npcList.resize(npcIds.size());
		size_t count = 0;
		for(vector<string>::iterator itr = npcIds.begin(); itr != npcIds.end(); itr++)
		{
			unsigned npcId;
			if(Convert::StringToUInt(npcId, *itr))
			{
				DataBaseExtra &npcBase = s_npcList[count];
				ret = LogicNpc::GetInitBase(npcId, npcBase);
				if(ret != 0)
				{
					error_log("[invalid_npc_id][npcid=%u]", npcId);
				}
				npcBase.baseid = npcId;
				count++;
			}
		}
		s_npcList.resize(count);
		if(s_npcList.size() == 0)
		{
			fatal_log("[config_world_npc_error][worldnpc=%s]", sNpcIds.c_str());
		}
	}
	if(s_npcList.size() == 0)
	{
		ERROR_RETURN_MSG(R_ERR_DATA, "server_error");
	}
	baseExtra = s_npcList[Math::GetRandomInt(s_npcList.size())];
	return 0;
}

int LogicWorld::CreateNpc(unsigned position)
{
	int ret;
	DataBaseExtra baseExtra;
	ret = GetRandomNpc(baseExtra);
	if(ret != 0)
	{
		return ret;
	}
	DataBase base;
	base.baseid = 0;
	base.uid = 0;
	base.base_index = baseExtra.baseid;
	base.type = BT_WORLD_WILD_FORCE;
	base.base_name = "";
	base.seed = Math::GetRandomInt(10000);
	base.position = position;
	base.create_time = Time::GetGlobalTime();
	base.save_time = Time::GetGlobalTime();
	base.saveby_uid = 0;
	base.protected_time = 0;
	base.last_active_time = Time::GetGlobalTime();
	base.status = BS_NEW;
	base.damage = 0;
	base.destroyed = 0;
	base.value = 0;
	base.attack_level = 0;
	base.bomb_level = 0;
	ret = LogicBase::AddBase(base, baseExtra);
	if(ret != 0)
	{
		fatal_log("[AddBase fail][ret=%d,position=%u]", ret, position);
		return ret;
	}
	CDataWorld dbWorld;
	ret = dbWorld.Replace(position, base.baseid);
	if(ret != 0)
	{
		fatal_log("[World.Add fail][ret=%d,position=%u,baseid=%u]", ret, position, base.baseid);
		DB_ERROR_RETURN_MSG("add_world_fail");
	}
	return 0;
}

int LogicWorld::RefreshNpc(DataBase &base)
{
	int ret;
	if(base.type != BT_WORLD_WILD_FORCE || base.saveby_uid == 0 ||
		base.save_time + WORLD_WF_REFRESH_TIME > Time::GetGlobalTime())
	{
		return 0;
	}
	DataBaseExtra baseExtra;
	CHECK_CALL(GetRandomNpc(baseExtra));
	base.uid = 0;
	base.base_index = baseExtra.baseid;
	base.type = BT_WORLD_WILD_FORCE;
	base.base_name = "";
	base.seed = Math::GetRandomInt(10000);
	base.create_time = Time::GetGlobalTime();
	base.save_time = Time::GetGlobalTime();
	base.saveby_uid = 0;
	base.protected_time = 0;
	base.last_active_time = Time::GetGlobalTime();
	base.status = BS_NEW;
	base.damage = 0;
	base.destroyed = 0;
	base.value = 0;
	base.attack_level = 0;
	base.bomb_level = 0;
	baseExtra.baseid = base.baseid;
	CHECK_CALL(LogicBase::SetBase(base));
	CHECK_CALL(LogicBase::SetBaseExtra(baseExtra));
	return 0;
}

static int ReplaceNpc(unsigned position)
{
	int ret;
	DataBase base;
	CHECK_CALL(LogicWorld::GetBase(position, base));
	if(IsValidUid(base.uid))
	{
		if(!IsSubBase(base.base_index))
		{
			error_log("[not_sub_base][uid=%u,position=%u,baseid=%u,baseindex=%d]",
					base.uid, position, base.baseid, base.base_index);
			ERROR_RETURN_MSG(R_ERR_LOGIC, "not_sub_base");
		}
		CHECK_CALL(LogicBase::RemoveUserBase(base.uid, base.base_index));
	}
	DataBaseExtra baseExtra;
	CHECK_CALL(GetRandomNpc(baseExtra));
	base.uid = 0;
	base.base_index = baseExtra.baseid;
	base.type = BT_WORLD_WILD_FORCE;
	base.base_name = "";
	base.seed = Math::GetRandomInt(10000);
	base.position = position;
	base.create_time = Time::GetGlobalTime();
	base.save_time = Time::GetGlobalTime();
	base.saveby_uid = 0;
	base.protected_time = 0;
	base.last_active_time = Time::GetGlobalTime();
	base.status = BS_NEW;
	base.damage = 0;
	base.destroyed = 0;
	base.value = 0;
	base.attack_level = 0;
	base.bomb_level = 0;
	baseExtra.baseid = base.baseid;
	CHECK_CALL(LogicBase::SetBase(base));
	CHECK_CALL(LogicBase::SetBaseExtra(baseExtra));
	return 0;
}

int LogicWorld::CreateWorld(unsigned world)
{
	int ret;
	unsigned worldSize = LogicWorld::GetWorldSize();
	CWorldPoint point;
	point.World = world;
	CDataWorld dbWorld;
	for(point.X = 0; (unsigned)point.X < worldSize; point.X++)
	{
		for(point.Y = 0; (unsigned)point.Y < worldSize; point.Y++)
		{
			unsigned position = point.ToUInt();
			unsigned baseid;
			ret = dbWorld.Get(position, baseid);
			if(ret == R_ERR_NO_DATA)
			{
				ret = CreateNpc(point.ToUInt());
				if(ret != 0)
				{
					fatal_log("[create_world_error][ret=%d,world=%u,x=%u,y=%u]", ret, point.World, point.X, point.Y);
				}
			}
			else
			{
				if(ret == 0)
				{
					error_log("[add_base_exist][ret=%d,position=%u,baseid=%u]", ret, position, baseid);
				}
				else
				{
					fatal_log("[World.Get fail][ret=%d,position=%u]", ret, position);
				}
			}
		}
	}
	return 0;
}

static int IdToPosition(unsigned id, CWorldPoint &position)
{
	static unsigned s_worldSize = 0;
	static unsigned s_userPerWorld = 0;
	if(s_worldSize <= 0)
	{
		s_worldSize = LogicWorld::GetWorldSize();
		s_userPerWorld = s_worldSize / 3;
		s_userPerWorld *= s_userPerWorld;
		if(s_userPerWorld <= 0)
		{
			fatal_log("[config_world_size_error][worldsize=%u,userperworld=%u]", s_worldSize, s_userPerWorld);
			ERROR_RETURN_MSG(R_ERR_DATA, "server_error");
		}
	}
	position.World = id / s_userPerWorld + 1;
	int pos = id % s_userPerWorld;
	int mid = sqrt(pos);
	int low = mid * mid;
	int high = (mid + 1) * (mid + 1);
	int space = high - low;
	int diff = pos - low;
	if(diff < space / 2)
	{
		position.X = mid;
		position.Y = diff;
	}
	else
	{
		position.X = diff - (space / 2);
		position.Y = mid;
	}
	position.X = position.X * 3 + 1;
	position.Y = position.Y * 3 + 1;
	return 0;
}

static int GetFreePosition(unsigned &position, unsigned &baseid)
{
	int ret;
	int dx[] = {0, 0, 1, 1, 1, 0, -1, -1, -1};
	int dy[] = {0, 1, 1, 0, -1, -1, -1, 0, 1};
	CWorldPoint point(position);
	DataBase base;
	for(int i = 0; i < 9; i++)
	{
		CWorldPoint newPoint(point.World, point.X + dx[i], point.Y + dy[i]);
		unsigned newPosition = newPoint.ToUInt();
		if(LogicWorld::GetTerrain(newPosition) >= WORLD_TERRAIN_HORIZON)
		{
			ret = LogicWorld::GetBase(newPosition, base);
			if(ret == 0)
			{
				if(base.uid == 0 && base.type == BT_WORLD_WILD_FORCE &&
					(base.saveby_uid == 0 || base.last_active_time + WILD_FORCE_FREE_TIMEOUT < Time::GetGlobalTime()))
				{
					position = newPosition;
					baseid = base.baseid;
					return 0;
				}
			}
		}
	}
	error_log("[free_position_not_found][world=%u,x=%u,y=%u]", point.World, point.X, point.Y);
	ERROR_RETURN_MSG(R_ERR_NO_DATA, "free_position_not_found");
}

int LogicWorld::GetMaxWorld(int &world)
{
	int ret;
	uint64_t u64Id;
	CLogicIdCtrl logicIdCtrl;
	ret = logicIdCtrl.GetCurrentId(KEY_POSITION_CTRL, u64Id);
	if(ret != 0)
	{
		return ret;
	}
	CWorldPoint point;
	ret = IdToPosition(u64Id, point);
	if(ret != 0)
	{
		return ret;
	}
	world = point.World;
	return 0;
}

int LogicWorld::GetTerrain(unsigned position)
{
	//0 < 80 10 > 175
	//70-189
	static unsigned s_worldSize = 0;
	static string s_terrain;
	if(s_terrain.empty())
	{
		s_worldSize = GetWorldSize();
		string path = Config::GetValue(CONFIG_WORLD_TERRAIN);
		if(File::Read(path, s_terrain))
		{
			fatal_log("[get_terrain_fail][path=%s]", path.c_str());
			return WORLD_TERRAIN_HORIZON - 1;
		}
	}
	CWorldPoint point(position);
	size_t index = point.X + point.Y * s_worldSize;
	if(index > s_terrain.size())
	{
		error_log("[position_overflow][position=%u,x=%d,y=%d,size=%u]",
				position, point.X, point.Y, (unsigned)s_terrain.size());
		return WORLD_TERRAIN_HORIZON - 1;
	}
	return (int)(unsigned char)s_terrain[index];
}

int LogicWorld::AddUser(unsigned uid, CWorldPoint &point)
{
	int ret;
	DataUser user;
	ret = LogicUser::GetUser(uid, user);
	if(ret != 0)
	{
		return ret;
	}
	if(user.world != 0)
	{
		error_log("[user_already_in_world][uid=%u,world=%u]", uid, user.world);
		ERROR_RETURN_MSG(R_ERR_LOGIC, "already_in_world");
	}
	uint64_t u64Id;
	CLogicIdCtrl logicIdCtrl;
	ret = logicIdCtrl.GetNextId(KEY_POSITION_CTRL, u64Id);
	if(ret != 0)
	{
		return ret;
	}
	ret = IdToPosition(u64Id, point);
	if(ret != 0)
	{
		return ret;
	}
	unsigned position = point.ToUInt();
	unsigned baseid;
	ret = GetFreePosition(position, baseid);
	if(ret != 0)
	{
		return ret;
	}
	ret = LogicBase::SetPosition(user.main_base_id, position);
	if(ret != 0)
	{
		return ret;
	}
	int world = CWorldPoint(position).World;
	ret = LogicUser::SetWorld(uid, world);
	if(ret != 0)
	{
		return ret;
	}
	CDataWorld dbWorld;
	ret = dbWorld.Set(position, user.main_base_id);
	if(ret != 0)
	{
		error_log("[World.Set fail][ret=%d,position=%u,baseid=%u]", ret, position, baseid);
		user.world = 0;
		ret = LogicUser::SetUser(user);
		if(ret != 0)
		{
			fatal_log("[recover_user_error][ret=%d,uid=%u]", ret, uid);
		}
		DB_ERROR_RETURN_MSG("set_world_fail");
	}
	ret = LogicBase::RemoveBase(0, baseid);
	CLogicMap logicMap;
	ret = logicMap.RemoveMapUser(uid);
	return 0;
}

int LogicWorld::RemoveUser(unsigned uid)
{
	int ret;
	int world;
	if(IsMercenary())
	{
		DataUser user;
		CHECK_CALL(LogicUser::GetUser(uid, user));
		if(IsAllianceId(user.alliance_id))
		{
			error_log("[in_alliance][uid=%u,aid=%ud]", uid, user.alliance_id);
			ERROR_RETURN_MSG(R_ERR_LOGIC, "in_alliance");
		}
		world = user.world;
	}
	else
	{
		ret = LogicUser::GetWorld(uid, world);
		if(ret != 0)
		{
			return ret;
		}
	}
	if(world == 0)
	{
		error_log("[not_in_world][uid=%u]", uid);
		ERROR_RETURN_MSG(R_ERR_LOGIC, "not_in_world");
	}
	map<int, unsigned> bases;
	ret = LogicBase::GetUserBases(uid, bases);
	if(ret != 0)
	{
		return ret;
	}
	DataBase base;
	unsigned position;
	map<int, unsigned>::iterator itrFind = bases.find(MAIN_BASE_ID);
	if(itrFind == bases.end())
	{
		error_log("[not_main_base][uid=%u]", uid);
		ERROR_RETURN_MSG(R_ERR_DATA, "not_main_base");
	}
	unsigned mainBaseId = itrFind->second;
	bases.erase(itrFind);
	for(map<int, unsigned>::iterator itr = bases.begin(); itr != bases.end(); itr++)
	{
		if(IsUserBaseIndex(itr->first))
		{
			unsigned baseid = itr->second;
			ret = LogicBase::GetPosition(baseid, position);
			if(ret != 0)
			{
				return ret;
			}
			if(position == 0)
			{
				error_log("[position_unexpect][uid=%u,baseid=%u,position=%u]", uid, baseid, position);
				ret = LogicBase::RemoveBase(uid, baseid);
				if(ret != 0)
				{
					error_log("[remove_base_fail][uid=%u,baseindex=%d,baseid=%u]", uid, itr->first, baseid);
					return ret;
				}
			}
			else
			{
				ret = ReplaceNpc(position);
				if(ret != 0)
				{
					error_log("[replace_npc_fail][uid=%u,baseid=%u,position=%u]", uid, baseid, position);
					return ret;
				}
			}
		}
	}
	//最后处理主基地
	ret = LogicBase::GetPosition(mainBaseId, position);
	if(ret != 0)
	{
		return ret;
	}
	if(position == 0)
	{
		error_log("[position_unexpect][uid=%u,baseid=%u,position=%u]", uid, mainBaseId, position);
	}
	else
	{
		ret = CreateNpc(position);
		if(ret != 0)
		{
			error_log("[create_npc_fail][uid=%u,baseid=%u,position=%u]", uid, mainBaseId, position);
			return ret;
		}
	}
	ret = LogicUser::SetWorld(uid, 0);
	if(ret != 0)
	{
		return ret;
	}
	if(position != 0)
	{
		ret = LogicBase::SetPosition(mainBaseId, 0);
		if(ret != 0)
		{
			error_log("[set_position_fail][uid=%u,baseindex=0,baseid=%u]", uid, mainBaseId);
			int tempRet = LogicUser::SetWorld(uid, world);
			if(tempRet != 0)
			{
				fatal_log("[recover_user_error][ret=%d,uid=%u]", tempRet, uid);
				return ret;
			}
			return ret;
		}
	}
	return 0;
}

int LogicWorld::SetWorld(unsigned position, unsigned baseid)
{
	int ret;
	CDataWorld dbWorld;
	ret = dbWorld.Set(position, baseid);
	if(ret != 0)
	{
		error_log("[World.Set fail][ret=%d,position=%u,baseid=%u]", ret, position, baseid);
		DB_ERROR_RETURN_MSG("set_world_fail");
	}
	return 0;
}

int LogicWorld::SetBasePosition(unsigned baseid, unsigned position)
{
	int ret;
	CHECK_CALL(LogicBase::SetPosition(baseid, position));
	CHECK_CALL(SetWorld(position, baseid));
	return 0;
}

int LogicWorld::GetBase(unsigned position, DataBase &base)
{
	int ret;
	CDataWorld dbWorld;
	ret = dbWorld.Get(position, base.baseid);
	if(ret != 0)
	{
		error_log("[World.Get fail][ret=%d,position=%u]", ret, position);
		DB_ERROR_RETURN_MSG("get_world_fail");
	}
	CDataBase dbBase;
	ret = dbBase.GetBase(base.baseid, base);
	if(ret != 0)
	{
		if(ret == R_ERR_NO_DATA)
		{
			fatal_log("[world_base_not_exist][ret=%d,position=%u,baseid=%u]", ret, position, base.baseid);
		}
		else
		{
			error_log("[GetBase fail][ret=%d,baseid=%u]", ret, base.baseid);
		}
		DB_ERROR_RETURN_MSG("get_base_fail");
	}
	return 0;
}

static int GetBaseJson(unsigned uid, unsigned position, Json::Value &baseData)
{
//	b : base type Y
//	bid : base id Y
//	i : height	Y
//	f : flinger level	U
//	c : catapult level	U
//	uid : .	U
//	fbid : facebookid	U
//	t : truce	U
//	n : name	U
//	fr : friend	X
//	on : is online	U
//	p : _protected	U
//	mine : is self	X
//	r : resource	X
//	m : monsterdata	U
//	l : level	U
//	d : destroyed	Y
//	dm : damage	Y
//	lo : locked	X
//	bi : baseindex	+

	///TODO: cache

	int ret;
	int terrain = LogicWorld::GetTerrain(position);
	baseData["i"] = terrain;
	if(terrain < WORLD_TERRAIN_HORIZON)
	{
		return 0;
	}
	DataBase base;
	ret = LogicWorld::GetBase(position, base);
	if(ret != 0)
	{
		return ret;
	}
	if(base.type == BT_WORLD_WILD_FORCE)
	{
		LogicWorld::RefreshNpc(base);
	}
	baseData["bid"] = base.baseid;
	baseData["b"] = base.type;
	baseData["bi"] = base.base_index;
	baseData["d"] = base.destroyed;
	baseData["dm"] = base.damage;
	if(IsUserBaseIndex(base.base_index))
	{
		if(!IsValidUid(base.uid))
		{
			error_log("[invalid_base_owner][position=%u,uid=%u,baseid=%u,baseindex=%d]",
					position,base.uid, base.baseid, base.base_index);
			ERROR_RETURN_MSG(R_ERR_DATA, "invalid_base_data");
		}
		baseData["f"] = base.attack_level;
		baseData["c"] = base.bomb_level;
		baseData["p"] = base.protected_time;
		baseData["uid"] = base.uid;
		ret = LogicBase::GetMilitary(base.baseid, baseData["m"]);
		if(ret != 0)
		{
			return ret;
		}
		DataUser user;
		ret = LogicUser::GetUser(base.uid, user);
		if(ret != 0)
		{
			return ret;
		}
		baseData["l"] = user.level;
		if(IsOnline(user.last_active_time))
		{
			baseData["on"] = 1;
		}
		DataUserBasic userBasic;
		ret = LogicUserBasic::GetUserSmart(base.uid, OpenPlatform::GetType(), userBasic);
		if(ret != 0)
		{
			return ret;
		}
		baseData["fbid"] = userBasic.open_id;
		baseData["n"] = userBasic.name;
		if(uid == base.uid && IsSubBase(base.base_index))
		{
			Json::Value extraData;
			CHECK_CALL(LogicBase::GetExtraData(base.baseid, extraData));
			if(extraData.isMember("inviteid"))
			{
				baseData["rid"] = extraData["inviteid"];
			}
		}
		if(uid != base.uid)
		{
			CLogicUserInteract logicInteract;
			DataUserInteract userInteract;
			ret = logicInteract.GetInteract(uid, base.uid, userInteract);
			if(ret == 0)
			{
				if(Time::GetGlobalTime() < userInteract.truce_time)
				{
					baseData["t"] = userInteract.truce_time;
				}
			}
		}
		if(IsAllianceId(user.alliance_id))
		{
			baseData["aid"] = user.alliance_id;
			DataAlliance alliance;
			CLogicAlliance logicAlliance;
			ret = logicAlliance.GetAllianceLimit(user.alliance_id, alliance);
			if(ret == 0)
			{
				baseData["aname"] = alliance.name;
				baseData["aflag"] = alliance.flag;
			}
		}
	}
	return 0;
}

int LogicWorld::GetBasesJson(unsigned uid, const Json::Value &positions, Json::Value &data)
{
	int ret;
	DataUser user;
	ret = LogicUser::GetUser(uid, user);
	if(ret != 0)
	{
		return ret;
	}
	if(user.world == 0)
	{
		error_log("[not_in_world][uid=%u]", uid);
		ERROR_RETURN_MSG(R_ERR_LOGIC, "not_in_world");
	}
	LogicUser::GetResourcesJson(user, data["resources"]);
	unsigned cash;
	CLogicPay logicPay;
	ret = logicPay.GetCash(uid, cash);
	if(ret != 0)
	{
		return ret;
	}
	data["credits"] = cash;
	Json::Value &bases = data["bases"];
	unsigned count = positions.size();
	for(unsigned i = 0; i < count; i++)
	{
		int x;
		int y;
		const Json::Value &position = positions[i];
		if(position.isArray() &&
			Json::GetInt(position, 0u, x) &&
			Json::GetInt(position, 1u, y))
		{
			CWorldPoint point(user.world, x, y);
			ret = GetBaseJson(uid, point.ToUInt(), bases[Convert::IntToString(point.X)][Convert::IntToString(point.Y)]);
			if(ret != 0)
			{
				error_log("[get_world_base_fail][ret=%d,uid=%u,position=%u]", ret, uid, point.ToUInt());
			}
		}
		else
		{
			error_log("[unknow_position][uid=%u,position=%s]", uid, Json::ToString(positions[i]).c_str());
		}
	}
	return 0;
}

int LogicWorld::OccupyBase(unsigned uid, unsigned baseid, unsigned r1, unsigned r2, unsigned r3, unsigned r4, unsigned cash)
{
	int ret;
	DataUserBasic userBasic;
	CLogicAlliance logicAlliance;
	DataUser user;
	CHECK_CALL(LogicUser::GetUser(uid, user));
	if(user.world == 0)
	{
		error_log("[not_in_world][uid=%u,world=%u]", uid, user.world);
		ERROR_RETURN_MSG(R_ERR_LOGIC, "not_in_world");
	}
	if(user.r1 < r1 || user.r2 < r2 || user.r3 < r3 || user.r4 < r4)
	{
		error_log("[occupy_not_enough_resource][uid=%u,r1=%d,r2=%d,r3=%d,r4=%d,rr1=%u,rr2=%u,rr3=%u,rr4=%u]",
				uid, r1, r2, r3, r4, user.r1, user.r2, user.r3, user.r4);
		ERROR_RETURN_MSG(R_ERR_LOGIC, "not_enough_resource");
	}
	CLogicPay logicPay;
	unsigned userCash;
	if(cash > 0)
	{
		CHECK_CALL(logicPay.GetCash(uid, userCash));
		if(userCash < cash)
		{
			error_log("[occupy_not_enough_cash][uid=%u,cash=%d,userCash=%u]", uid, cash, userCash);
			ERROR_RETURN_MSG(R_ERR_LOGIC, "pay_overspend");
		}
	}

	DataBase base;
	CHECK_CALL(LogicBase::GetBase(0, baseid, base));
	if(base.uid == uid)
	{
		error_log("[self_occupy][uid=%u,baseid=%u,baseindex=%d]", uid, base.baseid, base.base_index);
		ERROR_RETURN_MSG(R_ERR_LOGIC, "self_occupy");
	}
	if(base.type == BT_WORLD_WILD_FORCE)
	{
		CHECK_CALL(RefreshNpc(base));
		if(base.damage < WORLD_OCCUPY_DAMAGE_LIMIT)
		{
			error_log("[not_enough_damage][uid=%u,baseid=%u,damage=%d]", uid, base.baseid, base.damage);
			ERROR_RETURN_MSG(R_ERR_LOGIC, "not_enough_damage");
		}
		CHECK_CALL(LogicBase::AddSubBase(uid, base));
	}
	else if(base.type == BT_SUB_BASE)
	{
		if(!IsSubBase(base.base_index))
		{
			error_log("[not_sub_base][uid=%u,baseid=%u,baseindex=%u]", uid, baseid, base.base_index);
			ERROR_RETURN_MSG(R_ERR_LOGIC, "not_sub_base");
		}
		if(base.saveby_uid == base.uid || base.damage < WORLD_OCCUPY_DAMAGE_LIMIT)
		{
			error_log("[not_enough_damage][uid=%u,baseid=%u,baseuid=%u,saveuid=%u,damage=%d]",
					uid, base.baseid, base.uid, base.saveby_uid, base.damage);
			ERROR_RETURN_MSG(R_ERR_LOGIC, "not_enough_damage");
		}
		CHECK_CALL(LogicBase::ChangeOwner(uid, base));
		unsigned allianceId;
		ret = LogicUser::GetAllianceId(base.uid, allianceId);
		if(ret == 0 && IsAllianceId(allianceId))
		{
			ret = LogicUserBasic::GetUserSmart(base.uid, OpenPlatform::GetType(), userBasic);
			if(ret == 0)
			{
				Json::Value activity;
				activity["type"] = "lose_base";
				activity["uid"] = uid;
				activity["name"] = userBasic.name;
				logicAlliance.AddActivity(allianceId, activity);
			}
		}
	}
	else
	{
		error_log("[unexpect_base_type][uid=%u,baseid=%u,baseindex=%d,type=%d]",
				uid, base.baseid, base.base_index, base.type);
		ERROR_RETURN_MSG(R_ERR_LOGIC, "unexpect_base_type");
	}

	CHECK_CALL(LogicUser::ChangeResource(uid, -r1, -r2, -r3, -r4));
	if(cash > 0)
	{
		CHECK_CALL(logicPay.ChangeCash(uid, "OCCUPY", -cash, 1, baseid, userCash));
	}
	if(IsAllianceId(user.alliance_id))
	{
		ret = LogicUserBasic::GetUserSmart(uid, OpenPlatform::GetType(), userBasic);
		if(ret == 0)
		{
			Json::Value activity;
			activity["type"] = "occupy_base";
			activity["uid"] = uid;
			activity["name"] = userBasic.name;
			logicAlliance.AddActivity(user.alliance_id, activity);
		}
	}
	return 0;
}

int LogicWorld::MoveBase(unsigned uid, unsigned baseid, unsigned r1, unsigned r2, unsigned r3, unsigned r4, unsigned cash)
{
	int ret;
	DataUser user;
	CHECK_CALL(LogicUser::GetUser(uid, user));
	if(user.world == 0)
	{
		error_log("[not_in_world][uid=%u,world=%u]", uid, user.world);
		ERROR_RETURN_MSG(R_ERR_LOGIC, "not_in_world");
	}
	if(user.main_base_id == baseid)
	{
		error_log("[move_to_main_base][uid=%u,baseid=%u,mainbaseid=%u]", uid, baseid, user.main_base_id);
		ERROR_RETURN_MSG(R_ERR_LOGIC, "not_in_world");
	}
	if(user.r1 < r1 || user.r2 < r2 || user.r3 < r3 || user.r4 < r4)
	{
		error_log("[occupy_not_enough_resource][uid=%u,r1=%d,r2=%d,r3=%d,r4=%d,rr1=%u,rr2=%u,rr3=%u,rr4=%u]",
				uid, r1, r2, r3, r4, user.r1, user.r2, user.r3, user.r4);
		ERROR_RETURN_MSG(R_ERR_LOGIC, "not_enough_resource");
	}
	CLogicPay logicPay;
	unsigned userCash;
	if(cash > 0)
	{
		CHECK_CALL(logicPay.GetCash(uid, userCash));
		if(userCash < cash)
		{
			error_log("[occupy_not_enough_cash][uid=%u,cash=%d,userCash=%u]", uid, cash, userCash);
			ERROR_RETURN_MSG(R_ERR_LOGIC, "pay_overspend");
		}
	}

	DataBase base;
	CHECK_CALL(LogicBase::GetBase(uid, baseid, base));
	if(base.uid != uid || !IsSubBase(base.base_index))
	{
		error_log("[not_user_base][uid=%i,baseid=%u,baseuid=%u,baseindex=%d]",
				uid, baseid, base.uid, base.base_index);
		ERROR_RETURN_MSG(R_ERR_LOGIC, "not_user_base");
	}
	unsigned fromPosition;
	CHECK_CALL(LogicBase::GetPosition(user.main_base_id, fromPosition));
	ret = SetBasePosition(user.main_base_id, base.position);
	if(ret != 0)
	{
		error_log("[SetBasePosition fail][ret=%d,position=%u,baseid=%u]", ret, base.position, user.main_base_id);
		return ret;
	}
	ret = SetWorld(fromPosition, baseid);
	if(ret != 0)
	{
		error_log("[SetWorld fail][ret=%d,uid=%u,baseid=%u,position=%u]", ret, uid, baseid, fromPosition);
		return ret;
	}
	ret = LogicBase::RemoveUserBase(uid, base.base_index);
	if(ret != 0)
	{
		error_log("[RemoveUserBase fail][ret=%d,uid=%u,baseid=%u,baseindex=%d]", ret, uid, baseid, base.base_index);
		return ret;
	}
	ret = ReplaceNpc(fromPosition);
	if(ret != 0)
	{
		error_log("[ReplaceNpc fail][ret=%d,uid=%u,baseid=%u,baseindex=%d]", ret, uid, baseid, base.base_index);
		return ret;
	}

	CHECK_CALL(LogicUser::ChangeResource(uid, -r1, -r2, -r3, -r4));
	if(cash > 0)
	{
		CHECK_CALL(logicPay.ChangeCash(uid, "MOVEBASE", -cash, 1, baseid, userCash));
	}
	return 0;
}

int LogicWorld::InviteMove(uint64_t &inviteId, unsigned fromUid, unsigned toUid, unsigned baseid)
{
	int ret;
	if(fromUid == toUid)
	{
		error_log("[self_invite][fromuid=%u,touid=%u,baseid=%u]", fromUid, toUid, baseid);
		ERROR_RETURN_MSG(R_ERR_LOGIC, "self_invite");
	}
	int fromWorld;
	CHECK_CALL(LogicUser::GetWorld(fromUid, fromWorld));
	if(fromWorld == 0)
	{
		error_log("[from_not_in_world][uid=%u,world=%d]", fromUid, fromWorld);
		ERROR_RETURN_MSG(R_ERR_LOGIC, "not_in_world");
	}
	int toWorld;
	CHECK_CALL(LogicUser::GetWorld(toUid, toWorld));
	if(toWorld == 0)
	{
		error_log("[to_not_in_world][uid=%u,world=%d]", toUid, toWorld);
		ERROR_RETURN_MSG(R_ERR_LOGIC, "not_in_world");
	}
	DataBase base;
	CHECK_CALL(LogicBase::GetBase(fromUid, baseid, base));
	if(base.uid != fromUid || !IsSubBase(base.base_index))
	{
		error_log("[not_sub_base][uid=%u,baseid=%u,baseuid=%u,baseindex=%d]",
				fromUid, baseid, base.uid, base.base_index);
		ERROR_RETURN_MSG(R_ERR_LOGIC, "not_sub_base");
	}
	Json::Value extraData;
	CHECK_CALL(LogicBase::GetExtraData(baseid, extraData));
	if(Json::GetUInt64(extraData, "inviteid", inviteId))
	{
		error_log("[had_invite_move][uid=%u,baseid=%u,inviteid=%llu]", fromUid, baseid, inviteId);
		ERROR_RETURN_MSG(R_ERR_LOGIC, "had_invite_move");
	}
	Json::Value request;
	request["type"] = "invite_move";
	request["baseid"] = base.baseid;
	CWorldPoint point(base.position);
	request["world"] = point.World;
	request["x"] = point.X;
	request["y"] = point.Y;
	CLogicMessage logicMessage;
	CHECK_CALL(logicMessage.AddRequest(inviteId, fromUid, toUid, request));
	extraData["inviteid"] = Convert::UInt64ToString(inviteId);
	CHECK_CALL(LogicBase::SetExtraData(baseid, extraData));
	return 0;
}

int LogicWorld::ProcessRequest(const DataMessage &request, unsigned from, unsigned to, const string &type, int action, const Json::Value &data)
{
	if(type == "invite_move")
	{
		int ret;
		if(action != MS_REJECT && action != MS_CANCEL)
		{
			return 0;
		}
		unsigned baseid;
		if(!Json::GetUInt(data, "baseid", baseid))
		{
			error_log("[error_request][id=%llu,type=%s,action=%d,data=%s]",
					request.message_id, type.c_str(), action, Json::ToString(data).c_str());
			PARAM_ERROR_RETURN();
		}
		Json::Value extraData;
		CHECK_CALL(LogicBase::GetExtraData(baseid, extraData));
		uint64_t inviteId;
		if(!Json::GetUInt64(extraData, "inviteid", inviteId))
		{
			error_log("[no_invite_move][uid=%u,baseid=%u,inviteid=%llu]", from, baseid, request.message_id);
			ERROR_RETURN_MSG(R_ERR_LOGIC, "no_invite_move");
		}
		if(inviteId != request.message_id)
		{
			error_log("[invite_id_mismatch][uid=%u,baseid=%u,inviteid=%llu,requestid=%llu]",
					from, baseid, inviteId, request.message_id);
			ERROR_RETURN_MSG(R_ERR_LOGIC, "no_invite_move");
		}
		extraData.removeMember("inviteid");
		CHECK_CALL(LogicBase::SetExtraData(baseid, extraData));
	}
	return 0;
}

int LogicWorld::AcceptMove(unsigned uid, uint64_t inviteId, unsigned r1, unsigned r2, unsigned r3, unsigned r4, unsigned cash)
{
	//check cond
	int ret;
	CLogicMessage logicMessage;
	DataMessage invite;
	CHECK_CALL(logicMessage.GetMessage(inviteId, invite));
	if(invite.to_uid != uid)
	{
		error_log("[invite_uid_mismatch][uid=%u,inviteid=%llu,touid=%u]", uid, inviteId, invite.to_uid);
		PARAM_ERROR_RETURN();
	}
	Json::Value inviteData;
	string requestType;
	unsigned toBaseId;
	if(!Json::FromString(inviteData, invite.content) ||
		!Json::GetString(inviteData, "type", requestType) ||
		!Json::GetUInt(inviteData, "baseid", toBaseId) ||
		requestType != "invite_move")
	{
		error_log("[invite_data_error][uid=%u,inviteid=%llu,data=%s]", uid, inviteId, invite.content.c_str());
		DATA_ERROR_RETURN();
	}
	int fromWorld;
	CHECK_CALL(LogicUser::GetWorld(invite.from_uid, fromWorld));
	if(fromWorld == 0)
	{
		error_log("[from_not_in_world][uid=%u,world=%d]", invite.from_uid, fromWorld);
		ERROR_RETURN_MSG(R_ERR_LOGIC, "not_in_world");
	}
	DataUser user;
	CHECK_CALL(LogicUser::GetUser(uid, user));
	if(user.world == 0)
	{
		error_log("[to_not_in_world][uid=%u,world=%d]", uid, user.world);
		ERROR_RETURN_MSG(R_ERR_LOGIC, "not_in_world");
	}
	if(user.r1 < r1 || user.r2 < r2 || user.r3 < r3 || user.r4 < r4)
	{
		error_log("[occupy_not_enough_resource][uid=%u,r1=%d,r2=%d,r3=%d,r4=%d,rr1=%u,rr2=%u,rr3=%u,rr4=%u]",
				uid, r1, r2, r3, r4, user.r1, user.r2, user.r3, user.r4);
		ERROR_RETURN_MSG(R_ERR_LOGIC, "not_enough_resource");
	}
	CLogicPay logicPay;
	unsigned userCash;
	if(cash > 0)
	{
		CHECK_CALL(logicPay.GetCash(uid, userCash));
		if(userCash < cash)
		{
			error_log("[occupy_not_enough_cash][uid=%u,cash=%d,userCash=%u]", uid, cash, userCash);
			ERROR_RETURN_MSG(R_ERR_LOGIC, "pay_overspend");
		}
	}
	DataBase toBase;
	CHECK_CALL(LogicBase::GetBase(invite.from_uid, toBaseId, toBase));
	int toWorld = CWorldPoint(toBase.position).World;
	if(toBase.uid != invite.from_uid || !IsSubBase(toBase.base_index) || toWorld == 0)
	{
		error_log("[not_sub_base][uid=%u,baseid=%u,baseuid=%u,baseindex=%d,position=%u]",
				invite.from_uid, toBaseId, toBase.uid, toBase.base_index, toBase.position);
		ERROR_RETURN_MSG(R_ERR_LOGIC, "not_sub_base");
	}
	if(IsMercenary() && IsAllianceId(user.alliance_id) && user.world != toWorld)
	{
		error_log("[in_alliance][uid=%u,aid=%u,world=%d,toworld=%d]", uid, user.alliance_id, user.world, toWorld);
		ERROR_RETURN_MSG(R_ERR_LOGIC, "in_alliance");
	}

	//move
	Json::Value reply;
	reply["type"] = "accept_move";
	CHECK_CALL(logicMessage.ReplyRequest(uid, invite.from_uid, inviteId, MS_ACCEPT, reply));
	ret = RemoveSubBases(uid);
	if(ret != 0)
	{
		error_log("[RemoveSubBases fail][ret=%d,uid=%u,inviteid=%llu]", ret, uid, inviteId);
		return ret;
	}
	if(toWorld != user.world)
	{
		CHECK_CALL(LogicUser::SetWorld(uid, toWorld));
		if(ret != 0)
		{
			error_log("[SetWorld fail][ret=%d,uid=%u,world=%d,inviteid=%llu]", ret, uid, toWorld, inviteId);
			return ret;
		}
	}
	unsigned fromPosition;
	ret = LogicBase::GetPosition(user.main_base_id, fromPosition);
	if(ret != 0)
	{
		error_log("[GetPosition fail][ret=%d,uid=%u,baseid=%u,inviteid=%llu]", ret, uid, user.main_base_id, inviteId);
		return ret;
	}
	ret = SetBasePosition(user.main_base_id, toBase.position);
	if(ret != 0)
	{
		error_log("[SetBasePosition fail][ret=%d,position=%u,baseid=%u,inviteid=%llu]",
				ret, toBase.position, user.main_base_id, inviteId);
		return ret;
	}
	ret = SetWorld(fromPosition, toBase.baseid);
	if(ret != 0)
	{
		error_log("[SetWorld fail][ret=%d,uid=%u,baseid=%u,position=%u]", ret, uid, toBase.baseid, fromPosition);
		return ret;
	}
	ret = LogicBase::RemoveUserBase(toBase.uid, toBase.base_index);
	if(ret != 0)
	{
		error_log("[RemoveUserBase fail][ret=%d,uid=%u,baseid=%u,inviteid=%llu]", ret, uid, toBase.baseid, inviteId);
		return ret;
	}
	ret = ReplaceNpc(fromPosition);
	if(ret != 0)
	{
		error_log("[ReplaceNpc fail][ret=%d,uid=%u,baseid=%u,inviteid=%llu]", ret, uid, toBase.baseid,  inviteId);
		return ret;
	}
	CHECK_CALL(LogicUser::ChangeResource(uid, -r1, -r2, -r3, -r4));
	if(cash > 0)
	{
		CHECK_CALL(logicPay.ChangeCash(uid, "MOVEBASE", -cash, 1, user.main_base_id, userCash));
	}
	return 0;
}

int LogicWorld::RemoveSubBases(unsigned uid)
{
	int ret;
	map<int, unsigned> bases;
	CHECK_CALL(LogicBase::GetUserBases(uid, bases));
	for(map<int, unsigned>::iterator itr = bases.begin(); itr != bases.end(); itr++)
	{
		if(IsSubBase(itr->first))
		{
			unsigned baseid = itr->second;
			CHECK_CALL(LogicBase::RemoveUserBase(uid, itr->first));
			unsigned position = 0;
			ret = LogicBase::GetPosition(baseid, position);
			if(ret == 0)
			{
				ret = ReplaceNpc(position);
				if(ret != 0 && ret != R_ERR_NO_DATA)
				{
					return ret;
				}
			}
			else if(ret != R_ERR_NO_DATA)
			{
				return ret;
			}
		}
	}
	return 0;
}

CDataWorldUser *LogicWorld::GetDataWorldUser()
{
	if(!IsMercenary())
	{
		return NULL;
	}
	static CDataWorldUser s_dbWorldUser;
	static bool s_initWorldUser = false;
	if(!s_initWorldUser)
	{
		int ret = s_dbWorldUser.Init(Config::GetValue(CONFIG_WORLD_USER_DATA));
		if(ret != 0)
		{
			return NULL;
		}
		s_initWorldUser = true;
	}
	return &s_dbWorldUser;
}

int LogicWorld::RefreshUserWorld(unsigned uid, int world)
{
	CDataWorldUser *pDbWorldUser = LogicWorld::GetDataWorldUser();
	if(pDbWorldUser == NULL)
	{
		return R_ERR_DB;
	}
	if(world == 0)
	{
		return pDbWorldUser->RemoveUser(uid);
	}
	else
	{
		return pDbWorldUser->SetUser(uid, world);
	}
}
