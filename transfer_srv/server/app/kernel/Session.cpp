/*
 * Session.cpp
 *
 *  Created on: 2011-1-10
 *      Author: LARRY
 */

#include "Session.h"

class CDataSession : public CDataBaseDBC
{
public:
	CDataSession(int table = MEM_SESSION) : CDataBaseDBC(table) {}
	virtual ~CDataSession() {}

public:
	const string CreateNewSessionID(unsigned uid);
	int GetSessionAttribute(unsigned uid,const string &key,string & value);
	int SetSessionAttribute(unsigned uid,const string &key,const string &value);
	int RemoveSessionAttribute(unsigned uid,const string &key);
	int RemoveSession(unsigned uid);
	int RemoveSessionExpired(unsigned uid, unsigned timeBefore);
	int RemoveSessionAttributeExpired(unsigned uid, const string &key, unsigned timeBefore);
};

const string CDataSession::CreateNewSessionID(unsigned uid)
{
	string skey = "";
	//srand(time(NULL) + uid);	//not need
	int range = 36;
	for (int i = 0; i < 8 ; i++ )
	{
		int c = rand() % range;
		if(c >= 26)
		{
			c -= 26;
			//skey += CTrans::ITOS(c) ;
			skey += (char)('0' + c);
		}
		else
		{
			skey += (char)('a' + c);
		}
	}
	fatal_log("pid = %d, skey = %s",getpid(), skey.c_str());
	return skey;
}

int CDataSession::GetSessionAttribute(unsigned uid,const string &key,string &value)
{
	DBCREQ_DECLARE( DBC::GetRequest, uid );

	req.SetKey( uid);
	req.Need( "svalue", 1 );
	req.Need( "lastcmod", 2 );
	req.EQ("skey",key.c_str());

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;
	DBCREQ_IFFETCHROW;

	value = m_dbcret.StringValue( 1 );
	m_dbcret.IntValue( 2 );

	return 0;
}

int CDataSession::SetSessionAttribute(unsigned uid,const string &key,const string &value)
{
	DBCREQ_DECLARE( DBC::ReplaceRequest,uid );

	req.SetKey( uid );
	req.Set("skey",key.c_str() );
	req.Set( "svalue", value.c_str() );
	req.Set( "lastcmod", Time::GetGlobalTime() );

	//req.EQ("skey",key.c_str());

	DBCREQ_EXEC;

	return 0;
}

int CDataSession::RemoveSessionAttribute(unsigned uid,const string &key)
{
	DBCREQ_DECLARE( DBC::DeleteRequest, uid );
	req.SetKey( uid  );
	req.EQ("skey",key.c_str() );
	DBCREQ_EXEC;

	return 0;
}

int CDataSession::RemoveSession(unsigned uid)
{
	DBCREQ_DECLARE( DBC::DeleteRequest, uid );
	req.SetKey( uid  );
	DBCREQ_EXEC;
	return 0;
}

int CDataSession::RemoveSessionAttributeExpired(unsigned uid, const string &key, unsigned timeBefore)
{
	DBCREQ_DECLARE( DBC::DeleteRequest, uid );
	req.SetKey( uid  );
	req.EQ("skey",key.c_str() );
	req.LT("lastcmod", timeBefore);
	DBCREQ_EXEC;

	return 0;
}

int CDataSession::RemoveSessionExpired(unsigned uid, unsigned timeBefore)
{
	DBCREQ_DECLARE( DBC::DeleteRequest, uid );
	req.SetKey( uid  );
	req.LT("lastcmod", timeBefore);
	DBCREQ_EXEC;

	return 0;
}

namespace Session
{
	static CDataSession g_session;
	string CreateSessionKey(unsigned uid)
	{
		return g_session.CreateNewSessionID(uid);
	}
	string GetValue(unsigned uid,const string &key)
	{
		string value;
		g_session.GetSessionAttribute(uid, key, value);
		return value;
	}
	int GetValue(unsigned uid,const string &key,string &value)
	{
		return g_session.GetSessionAttribute(uid, key, value);
	}
	int SetValue(unsigned uid,const string &key,const string &value)
	{
		return g_session.SetSessionAttribute(uid, key, value);
	}
	int RemoveValue(unsigned uid,const string &key)
	{
		return g_session.RemoveSessionAttribute(uid, key);
	}
	int RemoveSession(unsigned uid)
	{
		return g_session.RemoveSession(uid);
	}
	int RemoveValueExpired(unsigned uid, const string &key, unsigned timeBefore)
	{
		return g_session.RemoveSessionAttributeExpired(uid, key, timeBefore);
	}
	int RemoveSessionExpired(unsigned uid, unsigned timeBefore)
	{
		return g_session.RemoveSessionExpired(uid, timeBefore);
	}
}
