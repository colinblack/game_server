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
	FightNum = user.FightNum;
	vip = user.vip;
	lvl = user.lvl;
	name = user.name;
	openid = user.openid;
	return *this;
}

bool CUserManager::AddUser(const UserData &user)
{
	m_users[user.UserId] = user;
	Json::Value data;
	Json::Reader reader;
	if(reader.parse(user.Name, data))
	{
		Json::GetString(data,"viplv",m_users[user.UserId].vip);
		Json::GetString(data,"lvl",m_users[user.UserId].lvl);
		Json::GetString(data,"name",m_users[user.UserId].name);
		Json::GetString(data,"openid",m_users[user.UserId].openid);
	}
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
void CUserManager::UpdateUser(unsigned uid,int fightnum){
	map<unsigned, UserData>::const_iterator itrFind = m_users.find(uid);
	if(itrFind != m_users.end())
	{
		m_users[uid].FightNum = fightnum;
	}
}
