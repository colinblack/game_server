#include "LogicInc.h"

class CCgiSelectQQGameServer : public CCgiBase
{
	string notice;
	map<unsigned, string> servers;

public:

	CCgiSelectQQGameServer() : CCgiBase("selectserver")
	{
		SetFeature(CF_PRINT_JSON);
		SetFeature(CF_GET_REMOTE_IP);
		SetFeature(CF_CHECK_PLATFORM);
		SetFeature(CF_CHECK_VERSION);
	}

	CGI_DIRECT_PROCESS(SelectServer)

	int SelectServer()
	{
		string openid = CCGIIn::GetCGIStr("openid");
		string pf = CCGIIn::GetCGIStr("pf");
		if(pf != "qqgame")
		{
			PARAM_ERROR_RETURN_MSG("only_qqgame_platform");
		}


		CLogicUserMapping LogicUserMapping;
		unsigned uid = 0;
		unsigned ret = LogicUserMapping.GetUid(openid,PT_qqgame,uid);
		//unsigned ret = LogicUserMapping.GetUid(openid,PT_TEST,uid);
		if(ret == R_ERR_NO_DATA)
		{
			m_jsonResult["server"] = "newqqgame.gzopen.1251017117.clb.myqcloud.com";
			m_jsonResult["zoneid"] = "1";
			//m_jsonResult["server"] = "192.168.100.237";
		}
		else if(ret == 0 && IsValidUid(uid))
		{
			m_jsonResult["server"] = "tygame.gzopen.1251017117.clb.myqcloud.com";
			m_jsonResult["zoneid"] = "0";
			//m_jsonResult["server"] = "192.168.100.237";
		}
		else
		{
			error_log("openid=%s,pf=%s,uid=%u",openid.c_str(),pf.c_str(),uid);
			PARAM_ERROR_RETURN_MSG("db_query_error");
		}

		CGI_SEND_LOG("openid=%s", openid.c_str());
		return R_SUCCESS;
	}

};

CGI_MAIN(CCgiSelectQQGameServer)
