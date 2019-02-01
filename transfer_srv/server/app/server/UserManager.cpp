/*
 * UserManager.cpp
 *
 *  Created on: 2012-3-8
 *      Author: dada
 */

#include "UserManager.h"

UserData& UserData::operator=(const UserData &user)
{
	UserId = user.UserId;
	SessionId = user.SessionId;
	Delay = user.Delay;
	Platform = user.Platform;
	Name = user.Name;
	return *this;
}

bool CUserManager::AddUser(const UserData &user)
{
	m_users[user.UserId] = user;
	return true;
}

void CUserManager::RemoveUser(unsigned uid)
{
	m_users.erase(uid);
}

bool CUserManager::GetUser(unsigned uid, UserData &user)
{
	map<unsigned, UserData>::const_iterator itrFind = m_users.find(uid);
	if(itrFind == m_users.end())
	{
		return false;
	}
	user = itrFind->second;
	return true;
}

int CUserManager::GetSessionId(unsigned uid)
{
	map<unsigned, UserData>::const_iterator itrFind = m_users.find(uid);
	if(itrFind == m_users.end())
	{
		return -1;
	}
	return itrFind->second.SessionId;
}
