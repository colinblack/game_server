/*
 * CgiNewMatch.cpp
 *
 *  Created on: 2015-10-23
 *      Author: Ralf
 */


#include "LogicInc.h"

class CCgiNewMatch: public CCgiBase {
public:
	CCgiNewMatch() : CCgiBase("newmatch")
	{
		SetFeature(CF_PRINT_JSON);
		SetFeature(CF_GET_REMOTE_IP);
		SetFeature(CF_GET_UID);
		SetFeature(CF_CHECK_SESSION);
		SetFeature(CF_CHECK_TIME);
		SetFeature(CF_CHECK_PLATFORM);
		SetFeature(CF_CHECK_HASH);
		SetFeature(CF_CHECK_VERSION);
		SetFeature(CF_APPEND_HASH);
		SetFeature(CF_PARSE_DATA);
		SetFeature(CF_CRYPT_DATA);
		SetFeature(CF_DECRYPT_DATA);
		SetFeature(CF_COMPRESS_OUT);

		int ret = CLogicNewMatch::Init(CONFIG_NEW_MATCH_DATA, false);
		if(ret)
			exit(ret);
	}

	CGI_ACTION_MAP_BEGIN
	CGI_SET_ACTION_MAP("Get", Get)
	CGI_SET_ACTION_MAP("Apply", Apply)
	CGI_SET_ACTION_MAP("ChangeIndex", ChangeIndex)
	CGI_SET_ACTION_MAP("Fight", Fight)
	CGI_SET_ACTION_MAP("Guess", Guess)
	CGI_ACTION_MAP_END

	~CCgiNewMatch()
	{
		CLogicNewMatch::Exit();
	}

	void ProcessSig(int sig)
	{
		CLogicNewMatch::Sig(sig);
	}

	int Get()
	{
		int ret = 0;

		CLogicNewMatch logicNewMatch;
		ret = logicNewMatch.Get(m_uid, m_jsonResult);

		CGI_SEND_LOG("action=Get&uid=%u", m_uid);
		return ret;
	}

	int Apply()
	{
		int ret = 0;

		CLogicNewMatch logicNewMatch;
		ret = logicNewMatch.Apply(m_uid, m_data);

		CGI_SEND_LOG("action=Apply&uid=%u", m_uid);
		return ret;
	}

	int ChangeIndex()
	{
		int ret = 0;

		CLogicNewMatch logicNewMatch;
		ret = logicNewMatch.ChangeIndex(m_uid, m_data);

		CGI_SEND_LOG("action=ChangeIndex&uid=%u", m_uid);
		return ret;
	}

	int Fight()
	{
		int ret = 0;

		CLogicNewMatch logicNewMatch;
		ret = logicNewMatch.Fight(m_uid, m_jsonResult);

		CGI_SEND_LOG("action=Fight&uid=%u", m_uid);
		return ret;
	}

	int Guess()
	{
		int ret = 0;

		unsigned guess = 0;
		if(!Json::GetUInt(m_data, "guess", guess))
			return R_ERR_PARAM;
		unsigned bet = 0;
		if(!Json::GetUInt(m_data, "bet", bet))
			return R_ERR_PARAM;

		CLogicNewMatch logicNewMatch;
		ret = logicNewMatch.Guess(m_uid, guess, bet);

		CGI_SEND_LOG("action=Guess&uid=%u", m_uid);
		return ret;
	}

};

CGI_MAIN(CCgiNewMatch)
