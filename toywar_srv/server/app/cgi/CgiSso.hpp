/*
 * CgiSso.cpp
 *
 *  Created on: 2011-12-22
 *      Author: dada
 */


#include "LogicInc.h"

class CCgiSso : public CCgiBase
{

public:

	CCgiSso() : CCgiBase("sso")
	{
		SetFeature(CF_PRINT_JSON);
		SetFeature(CF_GET_REMOTE_IP);
		SetFeature(CF_CHECK_PLATFORM);
	}

	CGI_SIMPLE_ACTION_MAP_BEGIN
	CGI_SET_ACTION_MAP("login", Login)
	CGI_ACTION_MAP_END

	int Login()
	{
		int ret;
		string openid = CCGIIn::GetCGIStr("openid");
		string openkey = CCGIIn::GetCGIStr("openkey");
		string pf = CCGIIn::GetCGIStr("pf");
		if(openid.empty() && openkey.empty())
		{
			error_log("[openid or openkey empty][platform=%d,openid=%s,openkey=%s]",
					OpenPlatform::GetType(), openid.c_str(),openkey.c_str());
			PARAM_ERROR_RETURN();
		}
		string iopenid = CCGIIn::GetCGIStr("iopenid");
		unsigned uid;
		string skey;
		ret = LogicSso::Login(openid, openkey, false, iopenid, pf, m_ipstr, false, false, uid, skey);
		if(ret != 0)
		{
			return ret;
		}
		m_jsonResult["uid"] = uid;
		m_jsonResult["skey"] = skey;
		CGI_SEND_LOG("action=login&uid=%u&platform=%d&openid=%s&openkey=%s&skey=%s&pf=%s",
				uid, OpenPlatform::GetType(), openid.c_str(), openkey.c_str(), skey.c_str(), pf.c_str());
		return 0;
	}

};

CGI_MAIN(CCgiSso)


