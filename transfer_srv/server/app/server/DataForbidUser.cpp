/*
 * DataForbidUser.cpp
 *
 *  Created on: 2012-11-14
 *      Author: Administrator
 */

#include "DataForbidUser.h"

CDataForbidUser::CDataForbidUser() {
	// TODO Auto-generated constructor stub
	m_init = false;
}

CDataForbidUser::~CDataForbidUser() {
	// TODO Auto-generated destructor stub
}

bool CDataForbidUser::Init(const std::string &path)
{
	if(m_init)
	{
		return true;
	}
	if(!m_sh.CreateOrOpen(path.c_str(), sizeof(UserForbidList)))
	{
		error_log("[init_forbid_userlist_fail][path=%s]", path.c_str());
		return false;
	}
	CAutoLock lock(&m_sh, true);
	if(!m_sh.HasInit())
	{
		UserForbidList *pdata = (UserForbidList *)m_sh.GetAddress();
		memset(pdata,0x00,sizeof(UserForbidList));
		m_sh.SetInitDone();
	}
	m_init = true;
	return true;
}
int CDataForbidUser::update(unsigned uid,unsigned ts)
{
	UserForbidList *pdata = (UserForbidList *)m_sh.GetAddress();
	CAutoLock lock(&m_sh, true);
	int i = 0;
	if(pdata == NULL)
	{
		return -1;
	}
	for(i = 0; i < MAX_USER_COUNT;i++ )
	{
		if(pdata->uidList[i].uid == uid)
		{
			pdata->uidList[i].forbidTs = ts;
			return 0;
		}
	}
	if(pdata->iCount < MAX_USER_COUNT)
	{
		pdata->uidList[pdata->iCount].uid = uid;
		pdata->uidList[pdata->iCount].forbidTs = ts;
		pdata->iCount++;
	}else{
		pdata->iCount = 0;
		pdata->uidList[pdata->iCount].uid = uid;
		pdata->uidList[pdata->iCount].forbidTs = ts;
	}
	return 0;
}
bool CDataForbidUser::IsForbid(unsigned uid)
{
	UserForbidList *pdata = (UserForbidList *)m_sh.GetAddress();
	CAutoLock lock(&m_sh, true);
	int i = 0;

	//vector<UserItem> vUserList;
	map<unsigned,unsigned> usermap;
	for(i = 0; i < MAX_USER_COUNT; i++)
	{
		usermap[pdata->uidList[i].uid] = pdata->uidList[i].forbidTs;
	}
	map<unsigned,unsigned>::iterator itr = usermap.find(uid);
	if(itr == usermap.end())
	{
		return false;
	}else
	{
		if(itr->second > Time::GetGlobalTime())
		{
			return true;
		}
	}
	return false;
}
int CDataForbidUser::GetUserList(map<unsigned, unsigned> &userMap)
{
	UserForbidList *pdata = (UserForbidList *)m_sh.GetAddress();
	if(pdata == NULL)
	{
		return -1;
	}
	// 初始化标记
	if(userMap[10000000] == 1)
	{
		return 0;
	}
	CAutoLock lock(&m_sh, true);
	for(int i = 0; i < 200; i++)
	{
		userMap[pdata->uidList[i].uid] = pdata->uidList[i].forbidTs;
	}
	userMap[10000000] = 1;
	return 0;
}

