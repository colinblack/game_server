/*
 * CgiLogin.cpp
 *
 *  Created on: 2011-5-27
 *      Author: dada
 */

#include "LogicInc.h"

class CCgiLogin : public CCgiBase
{

public:

	CCgiLogin() : CCgiBase("login")
	{
		SetFeature(CF_PRINT_JSON);
		SetFeature(CF_GET_REMOTE_IP);
		SetFeature(CF_CHECK_PLATFORM);
		SetFeature(CF_CHECK_HASH);
		SetFeature(CF_APPEND_HASH);
		SetFeature(CF_PARSE_DATA);
		SetFeature(CF_CRYPT_DATA);
		SetFeature(CF_DECRYPT_DATA);
		SetFeature(CF_COMPRESS_OUT);
	}

//	BEGIN_ACTION_MAP
//	SET_ACTION_MAP("login", Login)
//	END_ACTION_MAP

	CGI_DIRECT_PROCESS(Login)

	int Login()
	{
		//解析参数
		int ret;
		string openid;
		if(!Json::GetString(m_data, "openid", openid))
		{
			return R_ERR_PARAM;
		}
		string openkey;
		Json::GetString(m_data, "openkey", openkey);
		string iopenid;
		Json::GetString(m_data, "iopenid", iopenid);
		int isWhite = 0;
		Json::GetInt(m_data, "white", isWhite);
		if(openid.empty() && openkey.empty())
		{
			error_log("[openid or openkey empty][platform=%d,openid=%s,openkey=%s]",
					OpenPlatform::GetType(), openid.c_str(),openkey.c_str());
			return R_ERR_PARAM;
		}
		int verify = 0;
		Json::GetInt(m_data, "verify", verify);
		string pf;
		Json::GetString(m_data, "pf", pf);
		unsigned uid;
		string skey;
		ret = LogicSso::Login(openid, openkey, isWhite == 1, iopenid, pf, m_ipstr, verify == 1, true, uid, skey);
		if(ret != 0)
		{
			return ret;
		}

		//读档
		m_uid = uid;
		Json::Value archive;
		CLogicArchive logicArchive;
		int result = logicArchive.Load(uid, MAIN_BASE_ID, uid, LT_BUILD, m_jsonResult);
		if(result != 0)
		{
			return result;
		}

		m_jsonResult["uid"] = uid;
		m_jsonResult["skey"] = skey;

		CGI_SEND_LOG("uid=%u&platform=%d&openid=%s&openkey=%s&skey=%s&pf=%s",
				uid, OpenPlatform::GetType(), openid.c_str(), openkey.c_str(), skey.c_str(), pf.c_str());
		return R_SUCCESS;
	}

};

CGI_MAIN(CCgiLogin)
