/*
 * CgiPromote.cpp
 *
 *  Created on: 2011-11-2
 *      Author: dada
 */

#include "LogicInc.h"

#define MAX_PROMOTE_TARGET 10

class CCgiPromote : public CCgiBase
{

public:

	CCgiPromote() : CCgiBase("promote")
	{
		SetFeature(CF_PRINT_JSON);
		SetFeature(CF_GET_REMOTE_IP);
		SetFeature(CF_GET_UID);
		SetFeature(CF_CHECK_SESSION);
		SetFeature(CF_CHECK_PLATFORM);
	}

	CGI_SIMPLE_ACTION_MAP_BEGIN
	CGI_SET_ACTION_MAP("GetPromoteTarget", GetPromoteTarget)
	CGI_ACTION_MAP_END

	int GetPromoteTarget()
	{
		int ret;
		int count = CCGIIn::GetCGIInt("count");
		if(count <= 0 || count > MAX_PROMOTE_TARGET)
		{
			return R_ERR_PARAM;
		}
		CLogicUserData logicUserData;
		vector<string> friends;
		ret = logicUserData.GetPromoteFriends(m_uid, count, friends);
		Json::Value &target = m_jsonResult["target"];
		target = Json::Value(Json::arrayValue);
		for(vector<string>::iterator itr = friends.begin(); itr != friends.end(); itr++)
		{
			target[target.size()] = *itr;
		}
		CGI_SEND_LOG("action=gettaget&uid=%u&count=%u", m_uid, target.size());
		return 0;
	}

};

CGI_MAIN(CCgiPromote)
