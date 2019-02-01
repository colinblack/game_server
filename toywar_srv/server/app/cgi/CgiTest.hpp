/*
 * CgiTest.cpp
 *
 *  Created on: 2011-7-7
 *      Author: dada
 */

#include "LogicInc.h"
#include "WeiyouxiPlatform.h"

class CCgiTest : public CCgiBase
{

public:

	CCgiTest() : CCgiBase("test")
	{
		SetFeature(CF_GET_REMOTE_IP);
		SetFeature(CF_PRINT_JSON);
		SetFeature(CF_CHECK_PLATFORM);
	}

	CGI_SIMPLE_ACTION_MAP_BEGIN
	CGI_SET_ACTION_MAP("setachievement", SetAchievement)
	CGI_SET_ACTION_MAP("setleaderboard", SetLeaderboard)
	CGI_ACTION_MAP_END

	int SetAchievement()
	{
		if(OpenPlatform::GetType() != PT_WEIYOUXI)
		{
			return R_ERR_PLATFORM;
		}
		string openid = CCGIIn::GetCGIStr("openid");
		string openkey = CCGIIn::GetCGIStr("openkey");
		int id = CCGIIn::GetCGIInt("id");
		int ret = ((CWeiyouxiPlatform *)OpenPlatform::GetPlatform())->SetAchievement(openid, openkey, id);
		if(ret != 0)
		{
			return R_ERR_PLATFORM;
		}
		return R_SUCCESS;
	}

	int SetLeaderboard()
	{
		if(OpenPlatform::GetType() != PT_WEIYOUXI)
		{
			return R_ERR_PLATFORM;
		}
		string openid = CCGIIn::GetCGIStr("openid");
		string openkey = CCGIIn::GetCGIStr("openkey");
		int id = CCGIIn::GetCGIInt("id");
		int value = CCGIIn::GetCGIInt("value");
		int ret = ((CWeiyouxiPlatform *)OpenPlatform::GetPlatform())->SetLeaderboard(openid, openkey, id, value);
		if(ret != 0)
		{
			return R_ERR_PLATFORM;
		}
		return R_SUCCESS;
	}
};

CGI_MAIN(CCgiTest)

