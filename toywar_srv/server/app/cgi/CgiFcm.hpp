/*
 * CgiFcm.cpp
 *
 *  Created on: 2011-10-27
 *      Author: dada
 */

#include "LogicInc.h"

class CCgiFcm : public CCgiBase
{

public:

	CCgiFcm() : CCgiBase("fcm")
	{
		SetFeature(CF_PRINT_JSON);
		SetFeature(CF_GET_REMOTE_IP);
		SetFeature(CF_CHECK_PLATFORM);
	}

	CGI_SIMPLE_ACTION_MAP_BEGIN
	CGI_SET_ACTION_MAP("get", GetUser)
	CGI_SET_ACTION_MAP("add", AddUser)
	CGI_ACTION_MAP_END

	int GetUser()
	{
		int ret;
		unsigned uid;
		string openid = CCGIIn::GetCGIStr("openid");
		string openkey = CCGIIn::GetCGIStr("openkey");
		ret = LogicSso::GetLoginUid(uid, openid, openkey);
		if(ret != 0)
		{
			return ret;
		}

		Json::Value userExtraData;
		ret = LogicUser::GetExtraData(uid, userExtraData);
		if(ret != 0)
		{
			return ret;
		}
		string realName;
		string identityCardId;
		if(!Json::GetString(userExtraData, "rname", realName) ||
			!Json::GetString(userExtraData, "icid", identityCardId))
		{
			ERROR_RETURN_MSG(R_ERR_NO_DATA, "no_fcm_data");
		}

		m_jsonResult["rname"] = realName;
		m_jsonResult["icid"] = identityCardId;
		CGI_SEND_LOG("action=get&uid=%u&rname=%s&idid=%s", uid, realName.c_str(), identityCardId.c_str());
		return 0;
	}

	int AddUser()
	{
		int ret;
		string realName = CCGIIn::GetCGIStr("rname");
		string identityCardId = CCGIIn::GetCGIStr("icid");
		int nameLength = String::Utf8GetLength(realName);
		int idicLength = identityCardId.length();
		if(nameLength < 2 || nameLength > 10 || idicLength < 15 || idicLength > 20)
		{
			return R_ERR_PARAM;
		}

		unsigned uid;
		string openid = CCGIIn::GetCGIStr("openid");
		string openkey = CCGIIn::GetCGIStr("openkey");
		ret = LogicSso::GetLoginUid(uid, openid, openkey);
		if(ret != 0)
		{
			return ret;
		}

		Json::Value userExtraData;
		ret  = LogicUser::GetExtraData(uid, userExtraData);
		if(ret != 0)
		{
			return ret;
		}
		if(userExtraData.isMember("rname") || userExtraData.isMember("icid"))
		{
			ERROR_RETURN_MSG(R_ERR_NO_DATA, "had_fcm_data");
		}
		userExtraData["rname"] = realName;
		userExtraData["icid"] = identityCardId;
		ret = LogicUser::SetExtraData(uid, userExtraData);
		if(ret != 0)
		{
			return ret;
		}

		CGI_SEND_LOG("action=add&uid=%u&rname=%s&idid=%s", uid, realName.c_str(), identityCardId.c_str());
		return 0;
	}

};

CGI_MAIN(CCgiFcm)

