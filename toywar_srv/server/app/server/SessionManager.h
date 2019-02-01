/*
 * SessionManager.h
 *
 *  Created on: 2012-2-14
 *      Author: dada
 */

#ifndef SESSIONMANAGER_H_
#define SESSIONMANAGER_H_

#include "Kernel.h"

#define SESSION_SECRET_KEY_SIZE 16
//typedef CStaticBuffer<SESSION_SECRET_KEY_SIZE> SessionSecretKeyType;
typedef CDanymicBuffer<SESSION_SECRET_KEY_SIZE> SessionSecretKeyType;

struct SessionData
{
	int SessionId;
	uint32_t SessionKey;
	SessionSecretKeyType SecretKey;
	unsigned UserId;
	unsigned LastActiveTime;

	SessionData& operator=(const SessionData &session);
};

class CSessionManager
{
public:
	bool AddSession(SessionData &sessionData);
	void RemoveSession(int sessionId);
	bool GetSession(int sessionId, SessionData &sessionData);
	bool ActiveSession(int sessionId);
	void GetExpiredSessions(vector<int> &expiredSessions, unsigned timeBefore);
	int GetSessionCount() const;
private:
	map<int, SessionData> m_sessions;
};

#endif /* SESSIONMANAGER_H_ */
