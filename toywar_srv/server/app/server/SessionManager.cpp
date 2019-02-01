/*
 * SessionManager.cpp
 *
 *  Created on: 2012-2-14
 *      Author: dada
 */

#include "SessionManager.h"

SessionData& SessionData::operator=(const SessionData &session)
{
	SessionId = session.SessionId;
	SessionKey = session.SessionKey;
	SecretKey = session.SecretKey;
	UserId = session.UserId;
	LastActiveTime = session.LastActiveTime;
	return *this;
}

bool CSessionManager::AddSession(SessionData &sessionData)
{
	sessionData.LastActiveTime = Time::GetGlobalTime();
	sessionData.SessionKey = Math::GetRandomUInt();
	sessionData.SecretKey.Clear();
	for(size_t i = 0; i < SESSION_SECRET_KEY_SIZE / sizeof(uint32_t); i++)
	{
		uint32_t randomKey = Math::GetRandomUInt();
		sessionData.SecretKey.Append((byte *)&randomKey, sizeof(uint32_t));
	}
	m_sessions[sessionData.SessionId] = sessionData;
	return true;
}

void CSessionManager::RemoveSession(int sessionId)
{
	map<int, SessionData>::iterator itrFind = m_sessions.find(sessionId);
	if(itrFind == m_sessions.end())
	{
		return;
	}
	m_sessions.erase(itrFind);
}

bool CSessionManager::GetSession(int sessionId, SessionData &sessionData)
{
	map<int, SessionData>::iterator itrFind = m_sessions.find(sessionId);
	if(itrFind == m_sessions.end())
	{
		return false;
	}
	sessionData = itrFind->second;
	return true;
}

bool CSessionManager::ActiveSession(int sessionId)
{
	map<int, SessionData>::iterator itrFind = m_sessions.find(sessionId);
	if(itrFind == m_sessions.end())
	{
		return false;
	}
	itrFind->second.LastActiveTime = Time::GetGlobalTime();
	return true;
}

void CSessionManager::GetExpiredSessions(vector<int> &expiredSessions, unsigned timeBefore)
{
	for(map<int, SessionData>::iterator itr = m_sessions.begin(); itr != m_sessions.end(); itr++)
	{
		if(itr->second.LastActiveTime < timeBefore)
		{
			expiredSessions.push_back(itr->second.SessionId);
		}
	}
}

int CSessionManager::GetSessionCount() const
{
	return m_sessions.size();
}
