/*
 * DataMap.cpp
 *
 *  Created on: 2011-6-21
 *      Author: dada
 */

#include "DataMap.h"

#define MAX_USER_GROUP 100
#define MAX_USER_LIMIT 200
#define MAP_USER_COUNT 10000000

struct MapDataItem
{
	int32_t MaxCount;	//当前组最大可添加数
	int32_t Reserve1;
	int32_t Reserve2;
	int32_t Reserve3;
	uint32_t UserListHead[MAX_USER_LIMIT];	//以可添加关系数作为索引
};

struct MapUserData
{
	uint16_t Valid;	//是否有效
	uint16_t Group;	//所属组
	uint16_t Count;	//当前关系数
	uint16_t Limit;	//最大关系数
	uint32_t LastUid;
	uint32_t NextUid;
};

struct MapTable
{
	MapDataItem MapData[MAX_USER_GROUP];	//分组列表
	MapUserData UserData[MAP_USER_COUNT];	//用户数据表
};

CDataMap::CDataMap()
{
	m_init = false;
}

int CDataMap::Init(const string &path)
{
	if(m_init)
	{
		return 0;
	}
	if(!m_sh.CreateOrOpen(path.c_str(), sizeof(MapTable)))
	{
		fatal_log("[init_map_data_fail][path=%s]", path.c_str());
		return R_ERROR;
	}
	CAutoLock lock(&m_sh, true);
	if(!m_sh.HasInit())
	{
		MapTable *pTable = (MapTable *)m_sh.GetAddress();
		memset(pTable, 0, sizeof(MapTable));
		m_sh.SetInitDone();
	}
	m_init = true;
	return 0;
}

int CDataMap::SetUser(unsigned uid, int group, int count, int limit)
{
	if(uid < USER_UID_START || uid > (USER_UID_START + MAP_USER_COUNT))
	{
		error_log("[uid overflow][uid=%u]", uid);
		return R_ERR_DATA_LIMIT;
	}
	uid -= USER_UID_START;
	MapTable *pTable = (MapTable *)m_sh.GetAddress();
	if(pTable == NULL)
	{
		error_log("[map_set_user_fail][uid=%u,group=%d,count=%d,limit=%d]", uid, group, count, limit);
		return R_ERR_DB;
	}

	CAutoLock lock(&m_sh, true);
	int currCount = limit - count;
	if(currCount < 0)
	{
		currCount = 0;
	}
	MapUserData *pUserData = &(pTable->UserData[uid]);
	if(pUserData->Valid == 0)	//新用户
	{
		pUserData->Group = group;
		pUserData->Count = count;
		pUserData->Limit = limit;
		MapDataItem *pDataItem = &(pTable->MapData[group]);
		if(pDataItem->MaxCount < currCount)
		{
			pDataItem->MaxCount = currCount;
		}
		unsigned nextUid = pDataItem->UserListHead[currCount];
		pUserData->NextUid = nextUid;
		if(nextUid != 0)
		{
			pTable->UserData[nextUid].LastUid = uid;
		}
		pUserData->LastUid = 0;
		pDataItem->UserListHead[currCount] = uid;
		pUserData->Valid = 1;
	}
	else	//已有用户
	{
		int lastCount = pUserData->Limit - pUserData->Count;
		if(lastCount < 0)
		{
			lastCount = 0;
		}
		pUserData->Count = count;
		pUserData->Limit = limit;

		if(pUserData->Group == group && lastCount == currCount)
		{
			return 0;
		}

		MapDataItem *pDataItem = &(pTable->MapData[pUserData->Group]);
		if(pUserData->LastUid != 0)
		{
			pTable->UserData[pUserData->LastUid].NextUid = pUserData->NextUid;
		}
		else
		{
			pDataItem->UserListHead[lastCount] = pUserData->NextUid;
		}
		if(pUserData->NextUid != 0)
		{
			pTable->UserData[pUserData->NextUid].LastUid = pUserData->LastUid;
		}

		pDataItem = &(pTable->MapData[group]);
		if(currCount > pDataItem->MaxCount)
		{
			pDataItem->MaxCount = currCount;
		}
		pUserData->LastUid = 0;
		unsigned headUid = pDataItem->UserListHead[currCount];
		pUserData->NextUid = headUid;
		if(headUid != 0)
		{
			pTable->UserData[headUid].LastUid = uid;
		}
		pDataItem->UserListHead[currCount] = uid;
		pUserData->Group = group;
	}
	return 0;
}

int CDataMap::SetCount(unsigned uid, int count)
{
	if(uid < USER_UID_START || uid > (USER_UID_START + MAP_USER_COUNT))
	{
		error_log("[uid overflow][uid=%u]", uid);
		return R_ERR_DATA_LIMIT;
	}
	uid -= USER_UID_START;
	MapTable *pTable = (MapTable *)m_sh.GetAddress();
	if(pTable == NULL)
	{
		error_log("[map_set_count_fail][uid=%u,count=%d]", uid, count);
		return R_ERR_DB;
	}

	CAutoLock lock(&m_sh, true);
	MapUserData *pUserData = &(pTable->UserData[uid]);
	if(count == pUserData->Count)
	{
		return 0;
	}

	MapDataItem *pDataItem = &(pTable->MapData[pUserData->Group]);
	if(pUserData->LastUid != 0)
	{
		pTable->UserData[pUserData->LastUid].NextUid = pUserData->NextUid;
	}
	else
	{
		int lastCount = pUserData->Limit - pUserData->Count;
		if(lastCount < 0)
		{
			lastCount = 0;
		}
		pDataItem->UserListHead[lastCount] = pUserData->NextUid;
	}
	if(pUserData->NextUid != 0)
	{
		pTable->UserData[pUserData->NextUid].LastUid = pUserData->LastUid;
	}

	int currCount = pUserData->Limit - count;
	if(currCount < 0)
	{
		currCount = 0;
	}
	if(currCount > pDataItem->MaxCount)
	{
		pDataItem->MaxCount = currCount;
	}
	pUserData->LastUid = 0;
	unsigned headUid = pDataItem->UserListHead[currCount];
	pUserData->NextUid = headUid;
	if(headUid != 0)
	{
		pTable->UserData[headUid].LastUid = uid;
	}
	pDataItem->UserListHead[currCount] = uid;
	pUserData->Count = count;
	return 0;
}

int CDataMap::GetUser(int group, unsigned &uid, int &count)
{
	MapTable *pTable = (MapTable *)m_sh.GetAddress();
	if(pTable == NULL)
	{
		error_log("[map_get_user_fail][group=%d]", group);
		return R_ERR_DB;
	}

	CAutoLock lock(&m_sh, true);
	MapDataItem *pDataItem = &(pTable->MapData[group]);
	while(pDataItem->MaxCount > 0)
	{
		unsigned nextUid = pDataItem->UserListHead[pDataItem->MaxCount];
		if(nextUid != 0)
		{
			int randomEnd = Math::GetRandomInt(10) + 1;
			for(int n = 0; n < randomEnd && nextUid != 0; n++)
			{
				uid = nextUid;
				nextUid = pTable->UserData[uid].NextUid;
			}
			if(nextUid != 0)
			{
				uid = nextUid;
			}
			count = pTable->UserData[uid].Count;
			uid += USER_UID_START;
			return 0;
		}
		pDataItem->MaxCount--;
	}
	return R_ERR_DATA;
}

int CDataMap::RemoveUser(unsigned uid)
{
	if(uid < USER_UID_START || uid > (USER_UID_START + MAP_USER_COUNT))
	{
		error_log("[uid overflow][uid=%u]", uid);
		return R_ERR_DATA_LIMIT;
	}
	uid -= USER_UID_START;
	MapTable *pTable = (MapTable *)m_sh.GetAddress();
	if(pTable == NULL)
	{
		error_log("[map_remove_user_fail][uid=%u]", uid);
		return R_ERR_DB;
	}

	CAutoLock lock(&m_sh, true);
	MapUserData *pUserData = &(pTable->UserData[uid]);
	if(pUserData->Valid == 0)
	{
		return 0;
	}
	MapDataItem *pDataItem = &(pTable->MapData[pUserData->Group]);
	if(pUserData->LastUid != 0)
	{
		pTable->UserData[pUserData->LastUid].NextUid = pUserData->NextUid;
	}
	else
	{
		int lastCount = pUserData->Limit - pUserData->Count;
		if(lastCount < 0)
		{
			lastCount = 0;
		}
		pDataItem->UserListHead[lastCount] = pUserData->NextUid;
	}
	if(pUserData->NextUid != 0)
	{
		pTable->UserData[pUserData->NextUid].LastUid = pUserData->LastUid;
	}
	pUserData->Valid = 0;
	pUserData->Group = 0;
	pUserData->Count = 0;
	pUserData->Limit = 0;
	pUserData->LastUid = 0;
	pUserData->NextUid = 0;
	return 0;
}
