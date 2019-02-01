/*
 * GroupManager.h
 *
 *  Created on: 2012-3-7
 *      Author: dada
 */

#ifndef GROUPMANAGER_H_
#define GROUPMANAGER_H_

#include "Kernel.h"

enum GroupType
{
	GT_NONE = 0,
	GT_ALL = 1,
	GT_USER = 2,
	GT_SESSION = 3,
	GT_CHAT_CHANNEL = 4,
	GT_CHAT_ALLIANCE = 5,
	GT_BATTLE = 6,
	GT_COMBAT = 7,
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
	""
};

enum GroupEvent
{
	GE_JOIN = 1,
	GE_EXIT = 2,
	GE_DISBAND = 3,
	GE_START = 4
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

class IGroupCallback
{
public:
	virtual void OnGroupEvent(GroupEvent event, unsigned uid, const GroupData &group) = 0;
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
	int SetGroupStat(GroupType type,uint32_t id,byte stat);
protected:
	int CreateEmptyGroup(GroupType type, uint32_t id, const string &name);
	int RemoveGroupUser(unsigned uid, GroupType type, uint32_t id);
private:
	IGroupCallback *m_pGroupCallback;
	GroupTable m_groupTables[GT_MAX];
	UserGroupTable m_userGroups;
	queue<uint32_t> m_freeChatChannelId;
};

#endif /* GROUPMANAGER_H_ */
