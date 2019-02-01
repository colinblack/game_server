/*
 * GroupManager.h
 *
 *  Created on: 2012-3-7
 *      Author: dada
 */

#ifndef GROUPMANAGER_H_
#define GROUPMANAGER_H_

#include "Kernel.h"

#define GET_ALLIANCE_FIGHT_GROUP_ID(gid,room) ((gid) + ((room) * 100000))
#define MIN_NEW_USER_ROOM_ID 10001
#define MAX_NEW_USER_ROOM_ID 10009
#define IS_NWE_USER_ROOM_ID(id)((id) >= MIN_NEW_USER_ROOM_ID && (id) <= MAX_NEW_USER_ROOM_ID)

enum GroupType
{
	GT_NONE = 0,
	GT_ALL = 1,				//系统
	GT_USER = 2,  			//私聊
	GT_SESSION = 3,			//？？
	GT_CHAT_CHANNEL = 4,	//世界
	GT_CHAT_ALLIANCE = 5,	//联盟
	GT_BATTLE = 6,			//战斗转播
	GT_COMBAT = 7,			//联合副本
	GT_FIGHT = 8,			//斗将
	GT_KO = 9,				//3款
	GT_NATION = 10,			//国家
	GT_NATIONFIGHT = 11,	//3款
	GT_ALLIANCE_FIGHT = 12,	//3款
	GT_CHIBI_WAR     = 13,	//3款
	GT_NEW_WORLD     = 14,	//国战
	GT_NEW_WORLD_BATTLE = 15,//跨服国战
	GT_ALLIANCE_NEW_BATTLE = 16,
	GT_MAX
};

static const char* GroupNames[] = {
	"",
	"",
	"",
	"",
	"chat",
	"aliance",
	"battle",
	"teamboss",
	"fightagainst",
	"fightgroup",
	"",
	"",
	"alliancefight",
	"chibiwar",
	"newworld",
	"newworldbattle",
	"alliancenewbattle"
};

enum GroupEvent
{
	GE_JOIN = 1,
	GE_EXIT = 2,
	GE_DISBAND = 3,
	GE_START = 4,
	GE_MATCHING = 5,
	GE_SELECT_ALLIANCE_HERO = 6,
};

struct GroupData
{
	GroupType Type;
	uint32_t Id;
	string Name;
	uint16_t MaxCount;
	uint32_t OwnerId;
	byte Stat;
	vector<uint32_t> Users;
	GroupData& operator=(const GroupData &session);
};

struct GroupInfo
{
	GroupType Type;
	uint32_t Id;
	string Name;
	uint16_t MaxCount;
	uint16_t UserCount;
	uint32_t OwnerId;
	byte Stat;
};

typedef map<uint32_t, GroupData> GroupTable;
typedef vector<GroupInfo> GroupList;
typedef map<unsigned, map<GroupType, uint32_t> > UserGroupTable;
typedef vector<GroupInfo> abc;
class IGroupCallback
{
public:
	virtual void OnGroupEvent(GroupEvent event, unsigned uid, const GroupData &group) = 0;
	virtual void OnGroupEvent(GroupEvent event, unsigned uid, const GroupData &group,unsigned groupidA,unsigned groupidB) = 0;
};

class CGroupManager
{
public:
	CGroupManager();
	void SetGroupCallback(IGroupCallback *pGroupCallback);
	int GetGroupList(GroupType type, GroupList &groupList);
	int GetGroupData(GroupType type,uint32_t gid,GroupData& data);
	int CreateGroup(unsigned uid, GroupType type, const string &name, GroupInfo &groupInfo);
	int RemoveUser(unsigned uid);
	int JoinGroup(unsigned uid, GroupType type, uint32_t id, GroupInfo *pGroupInfo = NULL);
	int ExitGroup(unsigned uid, GroupType type, uint32_t id);
	int ExitGroup2(unsigned uid,GroupType type,uint32_t id);
	int GetGroupUsers(unsigned uid, GroupType type, uint32_t id, vector<uint32_t> &users);
	int GetAllianceUsers(unsigned uid, uint32_t id, vector<uint32_t> &users);
	int SetGroupStat(GroupType type,uint32_t id,byte stat);
	int DeleteMatch(unsigned groupId);
	int AddGroupMatch(unsigned groupIdA,unsigned groupIdB);
	unsigned FindMatchGroupId(unsigned groupId);
	int GetMatchGroupData(map<unsigned,unsigned> &matchgroups1,map<unsigned,unsigned> &matchgroups2);
	int CreateAllianceGroup(unsigned uid, GroupType type, const string &name, GroupInfo &groupInfo);
	int IsAllianceFightGroupExist(uint32_t id);
	int SelectAllianceHero(unsigned uid, unsigned gid, int heroId, unsigned &ower, int &releaseHid);
	int ResetAllianceHero(unsigned gid);
	int GetAllianceHeroStat(unsigned gid, map<unsigned,unsigned> &data);
	int ReleaseAllianceHero(unsigned uid, unsigned gid, int &releaseHid);
	int CreateAllianceNewBattle(unsigned uid, GroupType type, const string &name, GroupInfo &groupInfo);
protected:
	int CreateEmptyGroup(GroupType type, uint32_t id, const string &name);
	int RemoveGroupUser(unsigned uid, GroupType type, uint32_t id);
private:
	IGroupCallback *m_pGroupCallback;
	GroupTable m_groupTables[GT_MAX];
	UserGroupTable m_userGroups;
	queue<uint32_t> m_freeChatChannelId;
	map<unsigned,unsigned> m_matchgroups1;
	map<unsigned,unsigned> m_matchgroups2;
	map<unsigned,map<unsigned,unsigned> > m_AllianceHeroMap;
};

#endif /* GROUPMANAGER_H_ */
