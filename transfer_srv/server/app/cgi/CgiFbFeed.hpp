/*
 * CgiLoad.cpp
 *
 *  Created on: 2011-10-18
 *      Author: dada
 */

#include "LogicInc.h"
#include "FacebookPlatform.h"

class CCgiFbFeed : public CCgiBase
{

public:

	CCgiFbFeed() : CCgiBase("fbfeed")
	{
		SetFeature(CF_PRINT_JSON);
		SetFeature(CF_GET_REMOTE_IP);
		SetFeature(CF_GET_UID);
		SetFeature(CF_CHECK_SESSION);
		SetFeature(CF_CHECK_PLATFORM);
		SetFeature(CF_CHECK_HASH);
		SetFeature(CF_APPEND_HASH);
		SetFeature(CF_PARSE_DATA);
		SetFeature(CF_CRYPT_DATA);
		SetFeature(CF_DECRYPT_DATA);
		SetFeature(CF_COMPRESS_OUT);
	}

	CGI_DIRECT_PROCESS(SendFeed)

	int SendFeed()
	{
		//check platform
		if(OpenPlatform::GetType() != PT_FACEBOOK)
		{
			error_log("[platform_error][cgi=FbFeed,platform=%d]", OpenPlatform::GetType());
			SetError(R_ERR_REFUSE, "server_error");
			return R_ERR_REFUSE;
		}
		int ret;
		string openid;
		string openkey;
		ret = LogicSso::GetOpenKey(m_uid, openid, openkey);
		if(ret != 0)
		{
			return ret;
		}
		FacebookFeed feed;
		if( !Json::GetString(m_data, "name", feed.name) ||
			!Json::GetString(m_data, "description", feed.description) )
		{
			return R_ERR_PARAM;
		}
		Json::GetString(m_data, "caption", feed.caption);
		Json::GetString(m_data, "message", feed.message);
		Json::GetString(m_data, "picture", feed.picture);
		Json::GetString(m_data, "link", feed.link);
		Json::GetString(m_data, "source", feed.source);
		Json::GetString(m_data, "to", feed.to);
		if(Json::IsArray(m_data, "actions"))
		{
			if(m_data["actions"].size() > 0)
			{
				feed.actions = Json::ToString(m_data["actions"]);
			}
		}
		String::Trim(feed.message);
		ret = ((CFacebookPlatform *)(OpenPlatform::GetPlatform()))->SendFeed(openid, openkey, feed);
		if(ret != 0)
		{
			return R_ERR_PLATFORM;
		}
		CGI_SEND_LOG("send=ok&uid=%u&openid=%s", m_uid, openid.c_str());
		return R_SUCCESS;
	}

};

CGI_MAIN(CCgiFbFeed)
