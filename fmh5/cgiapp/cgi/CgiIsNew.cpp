/*
 * CgiIsNew.cpp
 *
 *  Created on: 2017-12-22
 *      Author: Ralf
 */

#include "LogicInc.h"

class CCgiIsNew : public CCgiBase
{
public:

	CCgiIsNew() : CCgiBase("isNew")
	{
		SetFeature(CF_PRINT_JSON);
		SetFeature(CF_GET_REMOTE_IP);
		SetFeature(CF_CHECK_PLATFORM);
	}

	CGI_DIRECT_PROCESS(IsNew)

	int IsNew()
	{
		string openid = CCGIIn::GetCGIStr("openid");
		int serverid = CCGIIn::GetCGIInt("serverid", 0, 100000, 0, 0);
		ConfigManager::Instance()->SetServer(serverid);
		if(openid.empty())
			return R_ERR_PARAM;

		unsigned uid;
		int ret = CDataUserMapping().GetMapping(openid, PT_TEST, uid);
		if (R_ERR_NO_DATA == ret)
			m_jsonResult["isNew"] = 1;
		else if(ret == 0)
			m_jsonResult["isNew"] = 0;
		else
			return ret;

		CGI_SEND_LOG("operator=%s", openid.c_str());

		return R_SUCCESS;
	}

};

CGI_MAIN(CCgiIsNew)


