/*
 * LogicMap.cpp
 *
 *  Created on: 2011-6-9
 *      Author: dada
 */

#include "LogicMap.h"

#define MAP_GROUP_RANGE 3

static uint64_t s_p2g[] = {
	500, 625, 781, 976, 1220,
	1525, 1906, 2382, 2977, 3721,
	4651, 5813, 7266, 9082, 11352,
	14190, 17737, 22171, 27713, 34641,
	43301, 54126, 67657, 84571, 105713,
	132141, 165176, 206470, 258087, 322608,
	403260, 504075, 630093, 787616, 984520,
	1230650, 1538312, 1922890, 2403612, 3004515,
	3755643, 4694553, 5868191, 7335238, 9169047,
	11461308, 14326635, 17908293, 22385366, 27981707,
	34977133, 43721416, 54651770, 68314712, 85393390,
	106741737, 133427171, 166783963, 208479953, 260599941,
	325749926, 407187407, 508984258, 636230322, 795287902,
	994109877ULL, 1242637346ULL, 1553296682ULL, 1941620852ULL, 2427026065ULL,
	3033782581ULL, 3792228226ULL, 4740285282ULL, 5925356602ULL, 7406695752ULL,
	9258369690ULL, 11572962112ULL, 14466202640ULL, 18082753300ULL, 22603441625ULL,
	28254302031ULL, 35317877538ULL, 44147346922ULL, 55184183652ULL, 68980229565ULL,
	86225286956ULL, 107781608695ULL, 134727010868ULL, 168408763585ULL, 210510954481ULL,
	263138693101ULL, 328923366376ULL, 411154207970ULL, 513942759962ULL, 642428449952ULL,
	803035562440ULL, 1003794453050ULL, 1254743066312ULL, 1568428832890ULL, 1960536041112ULL
};

int CLogicMap::GetMapUsersJson(unsigned uid, PlatformType platform, Json::Value &data)
{
	int ret;
	vector<MapUserData> userList;
	ret = GetMapUsers(uid, platform, userList);
	if(ret != 0)
	{
		return ret;
	}

	data.clear();
	for(vector<MapUserData>::iterator itr = userList.begin(); itr != userList.end(); itr++)
	{
		Json::Value &userData = data[data.size()];
		userData["userid"] = itr->uid;
		userData["openid"] = itr->open_id;
		userData["pt"] = itr->platform;
		userData["name"] = itr->name;
		userData["pic"] = itr->figure_url;
		userData["friend"] = itr->is_friend ? 1 : 0;
		userData["vt"] = itr->vip_type;
		userData["vl"] = itr->vip_level;
		userData["baseid"] = itr->baseid;
		userData["basename"] = itr->basename;
		userData["baseseed"] = itr->baseseed;
		if(IsAllianceId(itr->alliance_id))
		{
			userData["aid"] = itr->alliance_id;
			userData["aname"] = itr->alliance_name;
			userData["aflag"] = itr->alliance_flag;
		}
		userData["level"] = itr->level;
		userData["saved"] = itr->last_active_time;
		userData["attacksfrom"] = itr->attacksfrom;
		userData["attacksto"] = itr->attacksto;
		userData["helpsfrom"] = itr->helpsfrom;
		userData["helpsto"] = itr->helpsto;
		userData["attackpermitted"] = itr->attack_permit;
		if(itr->attackable_in >= 0)
		{
			userData["attackablein"] = itr->attackable_in;
		}
		if(itr->retaliate_count > 0)
		{
			userData["retaliatecount"] = itr->retaliate_count;
		}
	}
	return 0;
}

int CLogicMap::GetMapUsers(unsigned uid, PlatformType platform, vector<MapUserData> &userList)
{
	//check
	int ret;
	DataUser user;
	ret = LogicUser::GetUser(uid, user);
	if(ret != 0)
	{
		return ret;
	}
	if(user.world != 0)
	{
		error_log("[world_user_get_map][uid=%u,world=%d]", uid, user.world);
		PARAM_ERROR_RETURN_MSG("not_in_map");
	}

	//get friend and neighbour
	UidList friends;
	ret = LogicFriend::GetFriends(uid, platform, friends);
	if(ret != 0)
	{
		return ret;
	}

	UidList neighbours;
	CLogicNeighbour logicNeighbour;
	ret = logicNeighbour.GetNeighbours(uid, neighbours);
	if(ret != 0)
	{
		return ret;
	}

	//remove friend from neighbour
	for(UidList::iterator itr = friends.begin(); itr != friends.end(); itr++)
	{
		UidList::iterator itrFind = find(neighbours.begin(), neighbours.end(), *itr);
		if(itrFind != neighbours.end())
		{
			neighbours.erase(itrFind);
		}
	}

	//calc count
	int playTime = Time::GetGlobalTime() - user.register_time;
	int timeCount = playTime / (3 * 24 * 60 * 60);
	if(timeCount > 15)
	{
		timeCount = 15;
	}
	int count = 5 + user.level + timeCount;
	if(count > 60)
	{
		count = 60;
	}
	if(count / 2 < (int)friends.size())
	{
		count = count / 2;
	}
	else
	{
		count = count - friends.size();
	}
	int group = PointToGroup(user.point + user.value);

	//refresh neighbour
	userList.clear();
	int groupCount[MAP_GROUP_RANGE * 2 + 1];
	memset(groupCount, 0, sizeof(groupCount));
	for(UidList::iterator itr = neighbours.begin(); itr != neighbours.end();)
	{
		MapUserData userData;
		ret = GetUserData(*itr, platform, user, false, userData);
		if(ret == 0)
		{
			int neighbourGroup = PointToGroup(userData.point);
			if(neighbourGroup < group - MAP_GROUP_RANGE || neighbourGroup > group + MAP_GROUP_RANGE)
			{
				itr = neighbours.erase(itr);
			}
			else
			{
				userList.push_back(userData);
				groupCount[neighbourGroup + MAP_GROUP_RANGE - group]++;
				itr++;
			}
		}
		else
		{
			itr++;
		}
	}

	//get map db
	CDataMap *pDbMap = GetDataMap(platform);
	if(pDbMap == NULL)
	{
		DB_ERROR_RETURN_MSG("map_init_fail");
	}

	//set map user data
	ret = pDbMap->SetUser(uid, group, (int)neighbours.size(), count);
	if(ret != 0)
	{
		DB_ERROR_RETURN_MSG("map_set_user_fail");
		return ret;
	}

	//add neighbour
	int countAdd = count - (int)neighbours.size() - 1;
	if(countAdd > 0)
	{
		int groupStart = 0;
		if(group < MAP_GROUP_RANGE)
		{
			groupStart = MAP_GROUP_RANGE - group;
		}
		int groupEnd = COUNT_OF(groupCount);
		if(group + MAP_GROUP_RANGE >= (int)COUNT_OF(s_p2g))
		{
			groupEnd = COUNT_OF(s_p2g) + MAP_GROUP_RANGE - group - 1;
		}
		while(countAdd > 0)
		{
			//get new user
			int groupAdd = group;
			int minCount = 0x7fffffff;
			for(int i = groupStart; i < groupEnd; i++)
			{
				if(groupCount[i] < minCount)
				{
					minCount = groupCount[i];
					groupAdd = i + group - MAP_GROUP_RANGE;
				}
			}

			unsigned uidNew;
			int countNew;
			ret = pDbMap->GetUser(groupAdd, uidNew, countNew);
			if(ret == 0)
			{
				if(uid != uidNew &&
						find(friends.begin(), friends.end(), uidNew) == friends.end() &&
						find(neighbours.begin(), neighbours.end(), uidNew) == neighbours.end()
						)
				{
					MapUserData userData;
					ret = GetUserData(uidNew, platform, user, false, userData);
					if(ret == 0)
					{
						userList.push_back(userData);
					}
					neighbours.push_back(uidNew);
					pDbMap->SetCount(uid, (int)neighbours.size());
					pDbMap->SetCount(uidNew, countNew + 1);
				}
			}

			groupCount[groupAdd + MAP_GROUP_RANGE - group]++;
			countAdd--;
		}
	}

	//add friend data
	for(UidList::iterator itr = friends.begin(); itr != friends.end(); itr++)
	{
		MapUserData userData;
		ret = GetUserData(*itr, platform, user, true, userData);
		if(ret == 0)
		{
			userList.push_back(userData);
		}
	}

	//update neighbour
	ret = logicNeighbour.SetNeighbours(uid, neighbours);
	if(ret != 0)
	{
		return ret;
	}

	ret = UpdateUserInteract(userList, user);

	return ret;
}

int CLogicMap::GetUserData(unsigned uid, PlatformType platform, const DataUser& userQuery, bool isFriend, MapUserData &userData)
{
	int ret;
	DataUserBasic userBasic;
	ret = LogicUserBasic::GetUserSmart(uid, platform, userBasic);
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

	DataBase base;
	ret = LogicBase::GetBase(uid, user.main_base_id, base);
	if(ret != 0)
	{
		return ret;
	}

	DataAlliance alliance;
	alliance.alliance_id = user.alliance_id;
	alliance.flag = 0;
	if(IsAllianceId(user.alliance_id))
	{
		CLogicAlliance logicAlliance;
		logicAlliance.GetAllianceLimit(user.alliance_id, alliance);
	}

	userData.uid = uid;
	userData.platform = (PlatformType)userBasic.platform;
	userData.open_id = userBasic.open_id;
	userData.name = userBasic.name;
	userData.gender = userBasic.gender;
	userData.figure_url = userBasic.figure_url;
	userData.is_friend = isFriend;
	userData.vip_type = userBasic.vip_type;
	userData.vip_level = userBasic.vip_level;
	userData.point = user.value + user.point;
	userData.level = user.level;
	userData.last_active_time = user.last_active_time;
	userData.baseid = user.main_base_id;
	userData.baseseed = base.seed;
	userData.basename = base.base_name;
	userData.alliance_id = alliance.alliance_id;
	userData.alliance_name = alliance.name;
	userData.alliance_flag = alliance.flag;
	userData.savetime = user.last_active_time;
	userData.attacksfrom = 0;
	userData.attacksto = 0;
	userData.helpsfrom = 0;
	userData.helpsto = 0;
	userData.attack_permit = GetAttackPermit(user, base, userQuery);
	userData.attackable_in = 0;
	userData.retaliate_count = 0;
	if(userData.attack_permit == APT_BAN_DAMAGE_PROTECT || userData.attack_permit == APT_BAN_NEW_PROTECT)
	{
		userData.attackable_in = base.protected_time - Time::GetGlobalTime();
	}

	return 0;
}

int CLogicMap::GetAttackPermit(const DataUser &user, const DataBase &base, const DataUser& userQuery)
{
	if(IsAllianceId(user.alliance_id) &&
			user.alliance_id == userQuery.alliance_id)
	{
		return APT_BAN_ALLIANCE;
	}
	if(IsInProtect(base.protected_time))
	{
		if(base.status != BS_NEW)
		{
			return APT_BAN_DAMAGE_PROTECT;
		}
		else
		{
			return APT_BAN_NEW_PROTECT;
		}
	}
	if(userQuery.level - user.level > ATTACK_LEVEL_LIMIT)
	{
		return APT_BAN_LEVEL_LOW;
	}
	if(base.status == BS_FIGHT && base.saveby_uid != userQuery.uid &&
			Time::GetGlobalTime() - base.last_active_time < ATTACK_TIMEOUT)
	{
		return APT_BAN_BEING_ATTACK;
	}
	if(user.level - userQuery.level > ATTACK_LEVEL_LIMIT)
	{
		return APT_ALLOW_LEVEL_HIGH;
	}
	return APT_ALLOW;
}

int CLogicMap::UpdateUserInteract(vector<MapUserData> &userList, const DataUser& userQuery)
{
	int ret;
	map<unsigned, DataUserInteract> interacts;
	map<unsigned, DataUserInteract>::iterator itrInteract;
	CLogicUserInteract logicInteract;
	ret = logicInteract.GetInteracts(userQuery.uid, interacts);
	if(ret != 0)
	{
		return ret;
	}
	for(vector<MapUserData>::iterator itrUser = userList.begin(); itrUser != userList.end(); itrUser++)
	{
		itrInteract = interacts.find(itrUser->uid);
		if(itrInteract != interacts.end())
		{
			itrUser->attacksfrom = itrInteract->second.attack_from;
			itrUser->attacksto = itrInteract->second.attack_to;
			itrUser->helpsfrom = itrInteract->second.help_from;
			itrUser->helpsto = itrInteract->second.help_to;
			if(itrUser->attack_permit == APT_BAN_LEVEL_LOW && itrInteract->second.retaliate_count > 0)
			{
				itrUser->attack_permit = APT_ALLOW_REVENGE;
				itrUser->retaliate_count = itrInteract->second.retaliate_count;
			}
			if(Time::GetGlobalTime() < itrInteract->second.truce_time)
			{
				itrUser->attack_permit = APT_BAN_TRUCE;
				itrUser->attackable_in = itrInteract->second.truce_time - Time::GetGlobalTime();
			}
		}
	}

//	//联盟复仇
//	if(IsAllianceId(userQuery.alliance_id))
//	{
//		interacts.clear();
//		ret = logicInteract.GetInteracts(userQuery.allaince_id, interacts);
//		if(ret == 0)
//		{
//			for(vector<MapUserData>::iterator itrUser = userList.begin(); itrUser != userList.end(); itrUser++)
//			{
//				if(itrUser->attack_permit == APT_BAN_LEVEL_LOW)
//				{
//					itrInteract = interacts.find(itrUser->uid);
//					if(itrInteract != interacts.end())
//					{
//						if(itrInteract->second.retaliate_count > 0)
//						{
//							itrUser->attack_permit = APT_ALLOW_ALLIANCE_REVENGE;
//							itrUser->retaliate_count = itrInteract->second.retaliate_count;
//						}
//					}
//				}
//			}
//		}
//	}

	return 0;
}

int CLogicMap::RemoveMapUser(unsigned uid)
{
	int ret;
	CDataMap *pDbMap = GetDataMap(OpenPlatform::GetType());
	if(pDbMap == NULL)
	{
		DB_ERROR_RETURN_MSG("map_init_fail");
	}
	ret = pDbMap->RemoveUser(uid);
	if(ret != 0)
	{
		error_log("[RemoveUser fail][uid=%u]", uid);
		DB_ERROR_RETURN_MSG("remove_map_user_fail");
	}
	UidList neighbours;
	CLogicNeighbour logicNeighbour;
	ret = logicNeighbour.SetNeighbours(uid, neighbours);
	if(ret != 0)
	{
		return ret;
	}
	return 0;
}

int CLogicMap::PointToGroup(uint64_t point)
{
	for(unsigned i = 0; i < COUNT_OF(s_p2g); i++)
	{
		if(point < s_p2g[i])
		{
			return (int)i;
		}
	}
	return (int)COUNT_OF(s_p2g) - 1;
}

CDataMap *CLogicMap::GetDataMap(PlatformType platform)
{
	int ret;
	CDataMap *pDbMap = NULL;
	static map<int, CDataMap*> s_mapTable;
	map<int, CDataMap*>::iterator itrMapTable;
	itrMapTable = s_mapTable.find(platform);
	if(itrMapTable != s_mapTable.end())
	{
		pDbMap = itrMapTable->second;
	}
	else
	{
		if(OpenPlatform::GetPlatform()->GetConfig(CONFIG_INDEPEND) == "1")
		{
			string mapDataFile;
			String::Format(mapDataFile, "%s.%d", Config::GetValue(CONFIG_MAP_DATA).c_str(), platform);
			pDbMap = new CDataMap;
			ret = pDbMap->Init(mapDataFile);
			if(ret != 0)
			{
				delete pDbMap;
				return NULL;
			}
			s_mapTable[platform] = pDbMap;
		}
		else
		{
			itrMapTable = s_mapTable.find(0);
			if(itrMapTable != s_mapTable.end())
			{
				pDbMap = itrMapTable->second;
				s_mapTable[platform] = pDbMap;
			}
			else
			{
				pDbMap = new CDataMap;
				ret = pDbMap->Init(Config::GetValue(CONFIG_MAP_DATA));
				if(ret != 0)
				{
					delete pDbMap;
					return NULL;
				}
				s_mapTable[0] = pDbMap;
				s_mapTable[platform] = pDbMap;
			}
		}
	}
	return pDbMap;
}
