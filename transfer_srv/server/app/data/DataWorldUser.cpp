/*
 * DataWorldUser.cpp
 *
 *  Created on: 2012-5-15
 *      Author: dada
 */

#include "DataWorldUser.h"

#define MAX_WORLD_COUNT	100
#define WORLD_GROUP_COUNT	10
#define WORLD_USER_COUNT	10000000

struct WorldData
{
	uint32_t Reserve1;
	uint32_t Reserve2;
	uint32_t UserListHead[WORLD_GROUP_COUNT];
	uint32_t UserListTail[WORLD_GROUP_COUNT];
};

struct WorldUserData
{
	uint16_t World;
	uint16_t Group;
	uint32_t Reserve;
	uint32_t LastUid;
	uint32_t NextUid;
};

struct WorldTable
{
	WorldData World[MAX_WORLD_COUNT];	//以可添加关系数作为索引
	WorldUserData UserData[WORLD_USER_COUNT];	//用户数据表
};

CDataWorldUser::CDataWorldUser()
{
	m_init = false;
}

int CDataWorldUser::Init(const string &path)
{
	if(m_init)
	{
		return 0;
	}
	if(!m_sh.CreateOrOpen(path.c_str(), sizeof(WorldTable)))
	{
		fatal_log("[init_world_user_data_fail][path=%s]", path.c_str());
		return R_ERROR;
	}
	CAutoLock lock(&m_sh, true);
	if(!m_sh.HasInit())
	{
		WorldTable *pTable = (WorldTable *)m_sh.GetAddress();
		memset(pTable, 0, sizeof(WorldTable));
		m_sh.SetInitDone();
	}
	m_init = true;
	return 0;
}

static void RemoveFromList(WorldTable *pTable, WorldUserData *pUser, WorldData *pWorld)
{
	if(pUser->LastUid == 0)
	{
		pWorld->UserListHead[pUser->Group] = pUser->NextUid;
	}
	else
	{
		pTable->UserData[pUser->LastUid].NextUid = pUser->NextUid;
		pUser->LastUid = 0;
	}
	if(pUser->NextUid == 0)
	{
		pWorld->UserListTail[pUser->Group] = pUser->LastUid;
	}
	else
	{
		pTable->UserData[pUser->NextUid].LastUid = pUser->LastUid;
		pUser->NextUid = 0;
	}
	pUser->World = 0;
	pUser->Group = 0;
}

int CDataWorldUser::SetUser(unsigned uid, int world)
{
	if(uid < USER_UID_START || uid > (USER_UID_START + WORLD_USER_COUNT))
	{
		error_log("[uid overflow][uid=%u]", uid);
		return R_ERR_DATA_LIMIT;
	}
	uid -= USER_UID_START;
	WorldTable *pTable = (WorldTable *)m_sh.GetAddress();
	if(pTable == NULL)
	{
		error_log("[world_set_user_fail][uid=%u,world=%d]", uid, world);
		return R_ERR_DB;
	}
	CAutoLock lock(&m_sh, true);
	WorldUserData *pUser = &(pTable->UserData[uid]);
	WorldData *pWorld;
	if(pUser->World > 0)
	{
		pWorld = &(pTable->World[pUser->World]);
		RemoveFromList(pTable, pUser, pWorld);
	}
	pUser->World = world;
	pUser->Group = Math::GetRandomInt(WORLD_GROUP_COUNT);
	pWorld = &(pTable->World[world]);
	pUser->NextUid = pWorld->UserListHead[pUser->Group];
	pWorld->UserListHead[pUser->Group] = uid;
	pUser->LastUid = 0;
	if(pUser->NextUid == 0)
	{
		pWorld->UserListTail[pUser->Group] = uid;
	}
	else
	{
		pTable->UserData[pUser->NextUid].LastUid = uid;
	}
	return 0;
}

int CDataWorldUser::GetUser(unsigned &uid, int world)
{
	WorldTable *pTable = (WorldTable *)m_sh.GetAddress();
	if(pTable == NULL)
	{
		error_log("[world_get_user_fail][world=%d]", world);
		return R_ERR_DB;
	}
	CAutoLock lock(&m_sh, true);
	WorldData *pWorld = &(pTable->World[world]);
	uint16_t group = Math::GetRandomInt(WORLD_GROUP_COUNT);
	for(uint16_t i = 0; i < WORLD_GROUP_COUNT; i++)
	{
		uid = pWorld->UserListHead[group];
		if(uid != 0)
		{
			WorldUserData *pUser = &(pTable->UserData[uid]);
			RemoveFromList(pTable, pUser, pWorld);
			pUser->Group = Math::GetRandomInt(WORLD_GROUP_COUNT);
			pWorld = &(pTable->World[world]);
			pUser->LastUid = pWorld->UserListTail[pUser->Group];
			pWorld->UserListTail[pUser->Group] = uid;
			pUser->NextUid = 0;
			if(pUser->LastUid == 0)
			{
				pWorld->UserListHead[pUser->Group] = uid;
			}
			else
			{
				pTable->UserData[pUser->LastUid].NextUid = uid;
			}
			uid += USER_UID_START;
			return 0;
		}
		group++;
		if(group >= WORLD_GROUP_COUNT)
		{
			group = 0;
		}
	}
	return R_ERR_NO_DATA;
}

int CDataWorldUser::RemoveUser(unsigned uid)
{
	if(uid < USER_UID_START || uid > (USER_UID_START + WORLD_USER_COUNT))
	{
		error_log("[uid overflow][uid=%u]", uid);
		return R_ERR_DATA_LIMIT;
	}
	uid -= USER_UID_START;
	WorldTable *pTable = (WorldTable *)m_sh.GetAddress();
	if(pTable == NULL)
	{
		error_log("[world_remove_user_fail][uid=%u]", uid);
		return R_ERR_DB;
	}
	CAutoLock lock(&m_sh, true);
	WorldUserData *pUser = &(pTable->UserData[uid]);
	if(pUser->World > 0)
	{
		WorldData *pWorld = &(pTable->World[pUser->World]);
		RemoveFromList(pTable, pUser, pWorld);
	}
	return 0;
}
