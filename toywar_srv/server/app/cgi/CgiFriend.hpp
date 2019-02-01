/*
 * CgiFriend.cpp
 *
 *  Created on: 2011-6-16
 *      Author: dada
 */

#include "LogicInc.h"

class CCgiFriend : public CCgiBase
{

public:

	CCgiFriend() : CCgiBase("friend")
	{
		SetFeature(CF_PRINT_JSON);
		SetFeature(CF_GET_REMOTE_IP);
		SetFeature(CF_GET_UID);
		SetFeature(CF_CHECK_SESSION);
		SetFeature(CF_CHECK_PLATFORM);
		//SetFeature(CF_CHECK_HASH);
		SetFeature(CF_APPEND_HASH);
		//SetFeature(CF_PARSE_DATA);
		SetFeature(CF_COMPRESS_OUT);
	}

	CGI_DIRECT_PROCESS(GetFriend)

	int GetFriend()
	{
		Json::Value friends;
		int result = LogicFriend::GetFriendsJson(m_uid, OpenPlatform::GetType(), friends);
		if(result != 0)
		{
			return result;
		}

		m_jsonResult["pt"] = OpenPlatform::GetType();
		m_jsonResult["friends"] = friends;
		m_jsonResult["error"] = 0;
		m_jsonResult["currenttime"] = Time::GetGlobalTime();

		CGI_SEND_LOG("uid=%u&platform=%d&friends=%d", m_uid, OpenPlatform::GetType(), friends.size());
		return R_SUCCESS;
	}

};

CGI_MAIN(CCgiFriend)
