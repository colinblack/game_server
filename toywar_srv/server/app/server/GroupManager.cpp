/*
 * GroupManager.cpp
 *
 *  Created on: 2012-3-7
 *      Author: dada
 */

#include "GroupManager.h"
#include "ServerInc.h"

#define GROUP_MIN_CHAT_CHANNEL_COUNT	20
#define GROUP_CHAT_CHANNEL_MAX_USER	8000
#define GROUP_CHAT_ALLIANCE_MAX_USER	200
#define GROUP_BATTLE_MAX_USER	100
#define GROUP_MAX_CHAT_CHANNEL_COUNT	100
#define GROUP_COMBAT_MAX_USER 5
#define GROUP_FIGHT_MAX_USER 2
#define GROUP_CHAT_NATION_MAX_USER	8000
#define GROUP_CHAT_NATIONFIGHT_MAX_USER  1000
#define GROUP_ALLIANCE_FIGHT_MAX_USER  5
#define GROUP_CHIBI_WAR_MAX_USER 2000
#define GROUP_NEW_WORLD_MAX_USER 10000
#define GROUP_NEW_WORLD_BATTLE_MAX_USER 10000

GroupData& GroupData::operator=(const GroupData &gd)
{
	Type = gd.Type;
	Id = gd.Id;
	Name = gd.Name;
	MaxCount = gd.MaxCount;
	OwnerId = gd.OwnerId;
	Users = gd.Users;
	
	return *this;
}

CGroupManager::CGroupManager() :
	m_pGroupCallback(NULL)
{
	for(uint32_t i = 0; i < GROUP_MIN_CHAT_CHANNEL_COUNT; i++)
	{
		CreateEmptyGroup(GT_CHAT_CHANNEL, i, "");
	}
	for(uint32_t i = GROUP_MIN_CHAT_CHANNEL_COUNT; i < GROUP_MAX_CHAT_CHANNEL_COUNT; i++)
	{
		m_freeChatChannelId.push(i);
	}
}

void CGroupManager::SetGroupCallback(IGroupCallback *pGroupCallback)
{
	m_pGroupCallback = pGroupCallback;
}

int CGroupManager::GetGroupList(GroupType type, GroupList &groupList)
{
	if(type != GT_CHAT_CHANNEL && type != GT_BATTLE && type != GT_COMBAT&& type !=GT_FIGHT&& type != GT_NATIONFIGHT)
	{
		error_log("[unexpect_group_type][type=%d]", (int)type);
		PARAM_ERROR_RETURN();
	}
	GroupTable &groups = m_groupTables[type];
	groupList.resize(groups.size());
	size_t i = 0;
	for(GroupTable::const_iterator itr = groups.begin(); itr != groups.end(); itr++)
	{
		const GroupData &groupData = itr->second;
		GroupInfo &groupInfo = groupList[i];
		groupInfo.Type = groupData.Type;
		groupInfo.Id = groupData.Id;
		groupInfo.Name = groupData.Name;
		groupInfo.MaxCount = groupData.MaxCount;
		groupInfo.UserCount = groupData.Users.size();
		groupInfo.OwnerId = groupData.OwnerId;
		groupInfo.Stat = groupData.Stat;
		i++;
	}
	return 0;
}

int CGroupManager::GetGroupData(GroupType type,uint32_t gid,GroupData& data)
{
	GroupTable& groups = m_groupTables[type];
	if(groups.find(gid) == groups.end()){
		error_log("group [%d,%u] not exist",type,gid);
		ERROR_RETURN(PR_GROUP_NOT_EXIST);
	}

	data = groups[gid];
	
	return 0;
}

int CGroupManager::CreateGroup(unsigned uid, GroupType type, const string &name, GroupInfo &groupInfo)
{
	int ret;
	if(type != GT_CHAT_CHANNEL
		&& type != GT_BATTLE
		&& type != GT_COMBAT
		&& type !=GT_FIGHT
		&& type !=GT_NATIONFIGHT
		&& type !=GT_KO
		&& type !=GT_ALLIANCE_FIGHT
		&& type !=GT_ALLIANCE_NEW_BATTLE
		)
	{
		error_log("[unexpect_group_type][uid=%u,type=%d]", uid, (int)type);
		PARAM_ERROR_RETURN();
	}
	if (type == GT_ALLIANCE_FIGHT)
	{
		return CreateAllianceGroup(uid, type, name, groupInfo);
	}
	if (type == GT_ALLIANCE_NEW_BATTLE)
	{
		return CreateAllianceNewBattle(uid, type, name, groupInfo);
	}
	if(type == GT_CHAT_CHANNEL)
	{
		if(m_freeChatChannelId.size() <= 0)
		{
			error_log("[group_create_limit][uid=%u,type=%d]", uid, (int)type);
			ERROR_RETURN(PR_GROUP_LIMIT);
		}
		groupInfo.Id = m_freeChatChannelId.front();
	}
	ret = CreateEmptyGroup(type, groupInfo.Id, name);
	if(ret != 0)
	{
		return ret;
	}
	if(type == GT_CHAT_CHANNEL)
	{
		m_freeChatChannelId.pop();
	}
	ret = JoinGroup(uid, type, groupInfo.Id, &groupInfo);
	if(ret != 0)
	{
		error_log("[join_create_group_fail][uid=%u,type=%d,id=%u]", uid, (int)type, groupInfo.Id);
		return ret;
	}
	GroupTable &groupTable = m_groupTables[type];
	GroupTable::iterator itrGroup = groupTable.find(groupInfo.Id);
	if(itrGroup == groupTable.end())
	{
		error_log("[ASSERT(create_group_fail)][uid=%u,type=%d,id=%u]", uid, (int)type, groupInfo.Id);
		ERROR_RETURN(PR_GROUP_NOT_EXIST);
	}

	if(type == GT_COMBAT
	|| type == GT_BATTLE
	|| type == GT_FIGHT
	|| type == GT_NATIONFIGHT
	|| type == GT_KO
	|| type == GT_ALLIANCE_NEW_BATTLE){
		m_groupTables[type][groupInfo.Id].OwnerId = uid;
	}
	
	return 0;
}

int CGroupManager::CreateAllianceGroup(unsigned uid, GroupType type, const string &name, GroupInfo &groupInfo)
{
	int ret = 0;
	if (GT_ALLIANCE_FIGHT != type)
	{
		ERROR_RETURN(PR_ILLEGAL_PARAM);
	}
	ret = IsAllianceFightGroupExist(groupInfo.Id);
	if (0 == ret)
	{
		ret = JoinGroup(uid, type, groupInfo.Id, &groupInfo);
		if(ret != 0)
		{
			error_log("[join_create_group_fail][uid=%u,type=%d,id=%u]", uid, (int)type, groupInfo.Id);
			return ret;
		}
		debug_log("[Join alliance fight group][uid=%u,type=%d,gid=%u]",uid,type,groupInfo.Id);
	}
	else
	{
		ret = CreateEmptyGroup(type, groupInfo.Id, name);
		if(ret != 0)
		{
			return ret;
		}
		ResetAllianceHero(groupInfo.Id);
		ret = JoinGroup(uid, type, groupInfo.Id, &groupInfo);
		if(ret != 0)
		{
			error_log("[join_create_group_fail][uid=%u,type=%d,id=%u]", uid, (int)type, groupInfo.Id);
			return ret;
		}

		GroupTable &groupTable = m_groupTables[type];
		GroupTable::iterator itrGroup = groupTable.find(groupInfo.Id);
		if(itrGroup == groupTable.end())
		{
			error_log("[ASSERT(create_group_fail)][uid=%u,type=%d,id=%u]", uid, (int)type, groupInfo.Id);
			ERROR_RETURN(PR_GROUP_NOT_EXIST);
		}
		m_groupTables[type][groupInfo.Id].OwnerId = uid;

		debug_log("[Create alliance fight group][uid=%u,type=%d,gid=%u]",uid,type,groupInfo.Id);
	}
	return 0;
}

int CGroupManager::IsAllianceFightGroupExist(uint32_t id)
{
	GroupTable &groupTable = m_groupTables[GT_ALLIANCE_FIGHT];
	GroupTable::iterator itrGroup = groupTable.find(id);
	if(itrGroup == groupTable.end())
	{
		ERROR_RETURN(PR_GROUP_NOT_EXIST);
	}
	return 0;
}

int CGroupManager::RemoveUser(unsigned uid)
{
	UserGroupTable::iterator itrUser = m_userGroups.find(uid);
	if(itrUser == m_userGroups.end())
	{
		return 0;
	}
	for(map<GroupType, uint32_t>::iterator itrJoin = itrUser->second.begin(); itrJoin != itrUser->second.end(); itrJoin++)
	{
		RemoveGroupUser(uid, itrJoin->first, itrJoin->second);
	}
	m_userGroups.erase(itrUser);
	return 0;
}

int CGroupManager::JoinGroup(unsigned uid, GroupType type, uint32_t id, GroupInfo *pGroupInfo)
{
	if((type < GT_CHAT_CHANNEL || type >= GT_MAX) && type != GT_USER)
	{
		error_log("[unexpect_group_type][uid=%u,type=%d,id=%u]", uid, (int)type, id);
		PARAM_ERROR_RETURN();
	}
	if(type == GT_CHAT_ALLIANCE && (!IsAllianceId(id) && !IS_NWE_USER_ROOM_ID(id)))
	{
		error_log("[invalid_alliance_id][uid=%u,type=%d,id=%u]", uid, (int)type, id);
		PARAM_ERROR_RETURN();
	}
	uint32_t oldGroupId = id;
	UserGroupTable::iterator itrUser = m_userGroups.find(uid);
	if(itrUser == m_userGroups.end())
	{
		m_userGroups[uid].clear();
		if(type == GT_USER)
		{
			return 0;
		}
	}
	else
	{
		if(type == GT_USER)
		{
			return 0;
		}
		map<GroupType, uint32_t>::iterator itrJoin = itrUser->second.find(type);
		if(itrJoin != itrUser->second.end())
		{
			if(itrJoin->second == id)
			{
				return 0;
			}
			else
			{
				oldGroupId = itrJoin->second;
			}
		}
	}
	GroupTable &groupTable = m_groupTables[type];
	GroupTable::iterator itrGroup = groupTable.find(id);
	if(itrGroup == groupTable.end())
	{
		if(type  == GT_CHAT_ALLIANCE || type == GT_NATION
		|| type == GT_NATIONFIGHT || type == GT_CHIBI_WAR
		|| type == GT_NEW_WORLD || type == GT_NEW_WORLD_BATTLE
		|| type == GT_ALLIANCE_NEW_BATTLE)
		{
			CreateEmptyGroup(type, id, "");
			itrGroup = groupTable.find(id);
			if(itrGroup == groupTable.end())
			{
				error_log("[ASSERT(join_group_create_fail)][uid=%u,type=%d,id=%u]", uid, (int)type, id);
			}
		}
		else
		{
			error_log("[join_group_not_exist][uid=%u,type=%d,id=%u]", uid, (int)type, id);
			ERROR_RETURN(PR_GROUP_NOT_EXIST);
		}
	}
	GroupData &group = itrGroup->second;
	
	if(type == GT_COMBAT && group.Stat == 1){
		error_log("[join_group_incombat][uid=%u,type=%d,id=%u]", uid, (int)type, id);
		ERROR_RETURN(PR_GROUP_NOT_EXIST);
	}
	
	if(type == GT_ALLIANCE_FIGHT && group.Stat == 1){
		error_log("[join_group_incombat][uid=%u,type=%d,id=%u]", uid, (int)type, id);
		ERROR_RETURN(PR_GROUP_NOT_EXIST);
	}

	if(group.Users.size() >= group.MaxCount)
	{
		ERROR_RETURN(PR_GROUP_USER_FULL);
	}
	if(oldGroupId != id)
	{
		RemoveGroupUser(uid, type, oldGroupId);
	}
	group.Users.push_back(uid);
	m_userGroups[uid][type] = id;
	if(m_pGroupCallback != NULL)
	{
		m_pGroupCallback->OnGroupEvent(GE_JOIN, uid, itrGroup->second);
	}
	if(pGroupInfo != NULL)
	{
		pGroupInfo->Type = group.Type;
		pGroupInfo->Id = group.Id;
		pGroupInfo->Name = group.Name;
		pGroupInfo->MaxCount = group.MaxCount;
		pGroupInfo->UserCount = group.Users.size();
	}
	return 0;
}

int CGroupManager::ExitGroup(unsigned uid, GroupType type, uint32_t id)
{
	if(type < GT_CHAT_CHANNEL || type >= GT_MAX)
	{
		error_log("[unexpect_group_type][uid=%u,type=%d,id=%u]", uid, (int)type, id);
		PARAM_ERROR_RETURN();
	}
	UserGroupTable::iterator itrUser = m_userGroups.find(uid);
	if(itrUser == m_userGroups.end())
	{
		error_log("[get_group_user_not_exist][uid=%u,type=%d,id=%u]", uid, (int)type, id);
		ERROR_RETURN(PR_GROUP_NOT_IN);
	}
	map<GroupType, uint32_t>::iterator itrJoin = itrUser->second.find(type);
	if(itrJoin == itrUser->second.end())
	{
		error_log("[get_group_not_in][uid=%u,type=%d,id=%u]", uid, (int)type, id);
		ERROR_RETURN(PR_GROUP_NOT_IN);
	}
	if(itrJoin->second != id)
	{
		error_log("[get_group_not_in][uid=%u,type=%d,id=%d,realid=%u]", uid, (int)type, id, itrJoin->second);
		ERROR_RETURN(PR_GROUP_NOT_IN);
	}
	itrUser->second.erase(itrJoin);
	int ret = RemoveGroupUser(uid, type, id);
	if(ret != 0)
	{
		return ret;
	}
	//debug_log("[ExitGroup][uid=%u,type=%d,gid=%u]", uid, (int)type, id);
	return 0;
}

int  CGroupManager::ExitGroup2(unsigned uid,GroupType type,uint32_t id)
{
	if(type == GT_BATTLE
		|| type == GT_COMBAT
		|| type == GT_FIGHT
		|| type == GT_NATIONFIGHT
		|| type == GT_ALLIANCE_FIGHT
		|| type == GT_ALLIANCE_NEW_BATTLE
		){
		GroupTable &groupTable = m_groupTables[type];
		GroupTable::iterator itrGroup = groupTable.find(id);
		if(itrGroup == groupTable.end())
		{
			error_log("[ASSERT(get_group_not_exist)][uid=%u,type=%d,id=%u]", uid, (int)type, id);
			ERROR_RETURN(PR_GROUP_NOT_EXIST);
		}
		if(itrGroup->second.OwnerId == uid){
			vector<uint32_t> users = itrGroup->second.Users;
			for(vector<uint32_t>::iterator it = users.begin(); it != users.end();it++){
				ExitGroup(*it,type,id);
			}
			if (type == GT_ALLIANCE_FIGHT)
			{
				ResetAllianceHero(id);
			}
			return 0;
		}
	}

	return ExitGroup(uid, type, id);
}

int CGroupManager::GetGroupUsers(unsigned uid, GroupType type, uint32_t id, vector<uint32_t> &users)
{

	if(type < GT_NONE || type >= GT_MAX || type == GT_SESSION)
	{
		error_log("[unexpect_group_type][uid=%u,type=%d,id=%u]", uid, (int)type, id);
		PARAM_ERROR_RETURN();
	}
	size_t i = 0;
	UserGroupTable::iterator itrUser = m_userGroups.find(uid);
	if(itrUser == m_userGroups.end())
	{
		error_log("[get_group_user_not_exist][uid=%u,type=%d,id=%u]", uid, (int)type, id);
		ERROR_RETURN(PR_GROUP_NOT_IN);
	}
	if(type == GT_USER)
	{
		itrUser = m_userGroups.find(id);
		if(itrUser == m_userGroups.end())
		{
			ERROR_RETURN(PR_USER_NOT_ONLINE);
		}
		users.clear();
		users.push_back(id);
		return 0;
	}
	else if(type == GT_ALL)
	{
		users.resize(m_userGroups.size());
		for(itrUser = m_userGroups.begin(); itrUser != m_userGroups.end(); itrUser++)
		{
			users[i++] = itrUser->first;
		}
		return 0;
	}
	map<GroupType, uint32_t>::iterator itrJoin = itrUser->second.find(type);
	if(itrJoin == itrUser->second.end())
	{
		error_log("[get_group_not_in][uid=%u,type=%d,id=%u]", uid, (int)type, id);
		ERROR_RETURN(PR_GROUP_NOT_IN);
	}
	if(itrJoin->second != id)
	{
		error_log("[get_group_not_in][uid=%u,type=%d,id=%u,realid=%u]", uid, (int)type, id, itrJoin->second);
		ERROR_RETURN(PR_GROUP_NOT_IN);
	}
	GroupTable &groupTable = m_groupTables[type];
	GroupTable::const_iterator itrGroup = groupTable.find(id);
	if(itrGroup == groupTable.end())
	{
		error_log("[ASSERT(get_group_not_exist)][uid=%u,type=%d,id=%u]", uid, (int)type, id);
		itrUser->second.erase(itrJoin);
		ERROR_RETURN(PR_GROUP_NOT_EXIST);
	}
	
//	if(type == GT_COMBAT || type == GT_BATTLE){
//		if(itrGroup->second.OwnerId != uid){
//			users.clear();
//			users.push_back(itrGroup->second.OwnerId);
//			return 0;
//		}
//	}
	
	users = itrGroup->second.Users;
	vector<uint32_t>::iterator it = find(users.begin(),users.end(),uid);
	if(it != users.end()){
		users.erase(it);
	}
	return 0;
}
int CGroupManager::GetAllianceUsers(unsigned uid, uint32_t id, vector<uint32_t> &users)
{
	GroupTable &groupTable = m_groupTables[GT_CHAT_ALLIANCE];
	GroupTable::const_iterator itrGroup = groupTable.find(id);
	if(itrGroup == groupTable.end())
	{
		error_log("[ASSERT(get_group_not_exist)][uid=%u,type=%d,id=%u]", uid, id);
		ERROR_RETURN(PR_GROUP_NOT_EXIST);
	}
	users = itrGroup->second.Users;
	return 0;
}

int CGroupManager::CreateEmptyGroup(GroupType type, uint32_t id, const string &name)
{
	if(type < GT_CHAT_CHANNEL || type >= GT_MAX)
	{
		error_log("[unexpect_group_type][type=%d,id=%u]", (int)type, id);
		PARAM_ERROR_RETURN();
	}
	GroupTable &groupTable = m_groupTables[type];
	GroupTable::iterator itrGroup = groupTable.find(id);
	if(itrGroup != groupTable.end())
	{
		error_log("[ASSERT(create_group_exist)][type=%d,id=%u]", (int)type, id);
		ERROR_RETURN(PR_GROUP_EXIST);
	}
	GroupData &group = groupTable[id];
	group.Type = type;
	group.Id = id;
	group.Name = name;
	group.Stat = 0;
	if(type == GT_CHAT_CHANNEL)
	{
		group.MaxCount = GROUP_CHAT_CHANNEL_MAX_USER;
	}
	else if(type == GT_CHAT_ALLIANCE)
	{
		group.MaxCount = GROUP_CHAT_ALLIANCE_MAX_USER;
	}
	else if(type == GT_COMBAT){
		group.MaxCount = GROUP_COMBAT_MAX_USER;
	}
	else if(type == GT_FIGHT){
		group.MaxCount = GROUP_FIGHT_MAX_USER;
	}
	else if(type == GT_NATION)
	{
		group.MaxCount = GROUP_CHAT_NATION_MAX_USER;
	}
	else if(type == GT_NATIONFIGHT)
	{
		group.MaxCount = GROUP_CHAT_NATIONFIGHT_MAX_USER;
	}
	else if(type == GT_ALLIANCE_FIGHT)
	{
		group.MaxCount = GROUP_ALLIANCE_FIGHT_MAX_USER;
	}
	else if (type == GT_CHIBI_WAR)
	{
		group.MaxCount = GROUP_CHIBI_WAR_MAX_USER;
	}
	else if (type == GT_NEW_WORLD)
	{
		group.MaxCount = GROUP_NEW_WORLD_MAX_USER;
	}
	else if (type == GT_NEW_WORLD_BATTLE)
	{
		group.MaxCount = GROUP_NEW_WORLD_BATTLE_MAX_USER;
	}
	else if (type == GT_ALLIANCE_NEW_BATTLE)
	{
		group.MaxCount = GROUP_BATTLE_MAX_USER;
	}
	else
	{
		group.MaxCount = GROUP_BATTLE_MAX_USER;
	}
	group.Users.clear();
	return 0;
}

int CGroupManager::RemoveGroupUser(unsigned uid, GroupType type, uint32_t id)
{
	if(type < GT_CHAT_CHANNEL || type >= GT_MAX)
	{
		error_log("[ASSERT(unexpect_group_type)][uid=%u,type=%d,id=%u]", uid, (int)type, id);
		PARAM_ERROR_RETURN();
	}
	GroupTable &groupTable = m_groupTables[type];
	GroupTable::iterator itrGroup = groupTable.find(id);
	if(itrGroup == groupTable.end())
	{
		error_log("[ASSERT(get_group_not_exist)][uid=%u,type=%d,id=%u]", uid, (int)type, id);
		ERROR_RETURN(PR_GROUP_NOT_EXIST);
	}
	vector<uint32_t> &groupUsers = itrGroup->second.Users;
	vector<uint32_t>::iterator itrGroupUser = find(groupUsers.begin(), groupUsers.end(), uid);
	if(itrGroupUser == groupUsers.end())
	{
		error_log("[ASSERT(group_user_not_in)][uid=%u,type=%d,id=%u]", uid, (int)type, id);
		ERROR_RETURN(PR_GROUP_NOT_IN);
	}
	groupUsers.erase(itrGroupUser);
	if(m_pGroupCallback != NULL)
	{
		if(type==GT_FIGHT)
		{
			m_pGroupCallback-> OnGroupEvent(GE_EXIT, uid, itrGroup->second);

			unsigned matchgroupid = FindMatchGroupId(id);
			if(matchgroupid!=0)
			{
				GroupData dataMatch;
				int ret = GetGroupData(type,matchgroupid, dataMatch);
				if(ret==0)
				{
					m_pGroupCallback-> OnGroupEvent(GE_EXIT, uid, dataMatch);
				}
			}
		}
		else
		{
			m_pGroupCallback->OnGroupEvent(GE_EXIT, uid, itrGroup->second);
		}
	}
	if(groupUsers.size() == 0)
	{
		if(type != GT_CHAT_CHANNEL || id >= GROUP_MIN_CHAT_CHANNEL_COUNT)
		{
			groupTable.erase(itrGroup);
			if(type == GT_CHAT_CHANNEL)
			{
				m_freeChatChannelId.push(id);
			}
			if(type == GT_FIGHT)
			{
				DeleteMatch(id);
			}
		}
	}
	return 0;
}

int CGroupManager::SetGroupStat(GroupType type,uint32_t id,byte stat)
{
	GroupTable &groupTable = m_groupTables[type];
	GroupTable::iterator itrGroup = groupTable.find(id);
	if(itrGroup == groupTable.end())
	{
		error_log("[ASSERT(get_group_not_exist)][type=%d,id=%u]", (int)type, id);
		ERROR_RETURN(PR_GROUP_NOT_EXIST);
	}

	GroupData& gd = itrGroup->second;
	gd.Stat = stat;
	return 0;
}

int CGroupManager::DeleteMatch(unsigned groupId){
	map<unsigned ,unsigned >::iterator l_it1 = m_matchgroups1.find(groupId);
	map<unsigned ,unsigned >::iterator l_it2 = m_matchgroups2.find(groupId);
	if(l_it1!=m_matchgroups1.end())
	{
		unsigned groupid1 = l_it1->second ;
		m_matchgroups1.erase(l_it1);
		l_it2 = m_matchgroups2.find(groupid1);
		if(l_it2!=m_matchgroups2.end())
		{
			m_matchgroups2.erase(l_it2);
		}
	}
	else if(l_it2!=m_matchgroups2.end())
	{
		unsigned groupid1 = l_it2->second ;
		m_matchgroups2.erase(l_it2);
		l_it1 = m_matchgroups1.find(groupid1);
		if(l_it1!=m_matchgroups1.end())
		{
			m_matchgroups1.erase(l_it1);
		}
	}
	return 0;
}

int CGroupManager::AddGroupMatch(unsigned groupIdA,unsigned groupIdB){
	m_matchgroups1.insert(pair<unsigned,unsigned>(groupIdA,groupIdB));
	m_matchgroups2.insert(pair<unsigned,unsigned>(groupIdB,groupIdA));
	return 0;
}

unsigned CGroupManager::FindMatchGroupId(unsigned groupId){
	map<unsigned ,unsigned >::iterator l_it1 = m_matchgroups1.find(groupId);
	map<unsigned ,unsigned >::iterator l_it2 = m_matchgroups2.find(groupId);
	return l_it1!= m_matchgroups1.end()?l_it1->second :l_it2!= m_matchgroups2.end()?l_it2->second:0;
}
int CGroupManager::GetMatchGroupData(map<unsigned,unsigned> &matchgroups1,map<unsigned,unsigned> &matchgroups2){
	matchgroups1 = m_matchgroups1;
	matchgroups2 = m_matchgroups2;
	return 0;
}

int CGroupManager::SelectAllianceHero(unsigned uid, unsigned gid, int heroId, unsigned &ower, int &releaseHid)
{
	map<unsigned,unsigned> userMap;
	map<unsigned,map<unsigned,unsigned> >::iterator itr = m_AllianceHeroMap.find(gid);
	if (itr != m_AllianceHeroMap.end())
	{
		userMap = itr->second;
		map<unsigned,unsigned>::iterator hItr = userMap.begin();
		for (;hItr != userMap.end();hItr++)
		{
			if (hItr->second == uid && hItr->first != heroId)
			{
				debug_log("select another hero,old=%d,new=%d", hItr->first, heroId);
				releaseHid = hItr->first;
				userMap.erase(hItr);
			}
			if (hItr->first == heroId)
			{
				ower = hItr->second;
				debug_log("hero is select by %u", ower);
				return R_ERR_LOGIC;
			}
		}
	}
	ower = uid;
	userMap[heroId] = uid;
	m_AllianceHeroMap[gid] = userMap;
	return 0;
}

int CGroupManager::ResetAllianceHero(unsigned gid)
{
	map<unsigned,map<unsigned,unsigned> >::iterator itr = m_AllianceHeroMap.find(gid);
	if (itr != m_AllianceHeroMap.end())
	{
		m_AllianceHeroMap[gid].clear();
	}
	return 0;
}

int CGroupManager::GetAllianceHeroStat(unsigned gid, map<unsigned,unsigned> &data)
{
	map<unsigned,map<unsigned,unsigned> >::iterator itr = m_AllianceHeroMap.find(gid);
	if (itr != m_AllianceHeroMap.end())
	{
		data = itr->second;
	}
	else
	{
		data.clear();
	}
	return 0;
}

int CGroupManager::ReleaseAllianceHero(unsigned uid, unsigned gid, int &releaseHid)
{
	map<unsigned,unsigned> userMap;
	map<unsigned,map<unsigned,unsigned> >::iterator itr = m_AllianceHeroMap.find(gid);
	if (itr != m_AllianceHeroMap.end())
	{
		userMap = itr->second;
		map<unsigned,unsigned>::iterator hItr = userMap.begin();
		for (;hItr != userMap.end();hItr++)
		{
			if (hItr->second == uid)
			{
				releaseHid = (int)hItr->first;
				userMap.erase(hItr);
				m_AllianceHeroMap[gid] = userMap;
				return 0;
			}
		}
	}

	return 0;
}

int CGroupManager::CreateAllianceNewBattle(unsigned uid, GroupType type, const string &name, GroupInfo &groupInfo)
{
	int ret = 0;
	if (GT_ALLIANCE_NEW_BATTLE != type)
	{
		ERROR_RETURN(PR_ILLEGAL_PARAM);
	}
	GroupTable &groupTable = m_groupTables[GT_ALLIANCE_NEW_BATTLE];
	GroupTable::iterator itrGroup = groupTable.find(groupInfo.Id);
	if(itrGroup != groupTable.end())
	{
		ret = JoinGroup(uid, type, groupInfo.Id, &groupInfo);
		if(ret != 0)
		{
			error_log("[join_create_group_fail][uid=%u,type=%d,id=%u]", uid, (int)type, groupInfo.Id);
			return ret;
		}
	}
	else
	{
		ret = CreateEmptyGroup(type, groupInfo.Id, name);
		if(ret != 0)
		{
			return ret;
		}
		ret = JoinGroup(uid, type, groupInfo.Id, &groupInfo);
		if(ret != 0)
		{
			error_log("[join_create_group_fail][uid=%u,type=%d,id=%u]", uid, (int)type, groupInfo.Id);
			return ret;
		}

		GroupTable &groupTable = m_groupTables[type];
		GroupTable::iterator itrGroup = groupTable.find(groupInfo.Id);
		if(itrGroup == groupTable.end())
		{
			error_log("[ASSERT(create_group_fail)][uid=%u,type=%d,id=%u]", uid, (int)type, groupInfo.Id);
			ERROR_RETURN(PR_GROUP_NOT_EXIST);
		}
		m_groupTables[type][groupInfo.Id].OwnerId = uid;
	}
	return 0;
}
