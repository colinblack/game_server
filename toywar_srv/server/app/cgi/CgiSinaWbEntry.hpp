#include "LogicInc.h"

#define CONFIG_GAME_HOME	"game_home"
#define CONFIG_GAME_ENTRY	"game_entry"
#define SINAWB_AUTH_PAGE	"https://api.weibo.com/oauth2/authorize?response_type=token&client_id=%s&redirect_uri=%s"

class CCgiSinaWbEntry : public CCgiBase
{
public:

	CCgiSinaWbEntry() : CCgiBase("sinawb")
	{
		SetFeature(CF_GET_REMOTE_IP);
		SetFeature(CF_CHECK_PLATFORM);
	}

	CGI_DIRECT_PROCESS(SinaWbEntry)

	int SinaWbEntry()
	{
		//init
		static bool s_init = false;
		static string s_gameHome;
		static string s_authUrl;
		if(!s_init)
		{
			IOpenPlatform *pPlatform = OpenPlatform::GetPlatform();
			s_gameHome = pPlatform->GetConfig(CONFIG_GAME_HOME);
			String::Format(s_authUrl, SINAWB_AUTH_PAGE, pPlatform->GetAppId().c_str(),
					Crypt::UrlEncode(pPlatform->GetConfig(CONFIG_GAME_ENTRY)).c_str());
			s_init = true;
		}

#define SINAWB_ENTRY_ERROR_RETURN(ErrorCode)	\
		String::Format(redirectUrl, "%s?error=%d&ts=%u", s_gameHome.c_str(), ErrorCode, Time::GetGlobalTime());	\
		CgiUtil::HttpRedirect(redirectUrl);	\
		return ErrorCode;	\

		string redirectUrl;
		if(OpenPlatform::GetType() != PT_SINAWB)
		{
			error_log("[platform_error][cgi=SinaWbEntry,platform=%d]", OpenPlatform::GetType());
			SINAWB_ENTRY_ERROR_RETURN(R_ERR_REFUSE);
		}

		//get user data
		string error = CCGIIn::GetCGIStr("error");
		if(!error.empty())
		{
			error_log("[platform_auth_error][error=%s,error_reason=%s,error_desc=%s]",
					error.c_str(), CCGIIn::GetCGIStr("error_reason").c_str(), CCGIIn::GetCGIStr("error_description").c_str());
			SINAWB_ENTRY_ERROR_RETURN(R_ERR_AUTH);
		}

		string iopenid = CCGIIn::GetCGIStr("iopenid");
		string signedRequest = CCGIIn::GetCGIStr("signed_request");
		if(signedRequest.empty())
		{
			error_log("[empty_signed_request][request=]");
			SINAWB_ENTRY_ERROR_RETURN(R_ERR_AUTH);
		}
		bool parseSuccess = false;
		Json::Value jsonUserData;
		vector<string> datas;
		CBasic::StringSplit(signedRequest, ".", datas);
		if(datas.size() == 2)
		{
			string userData;
			if(Crypt::Base64UrlDecode(userData, datas[1]))
			{
				Json::Reader reader;
				if(reader.parse(userData, jsonUserData))
				{
					if(jsonUserData.isObject())
					{
						parseSuccess = true;
					}
				}
			}
		}
		if(!parseSuccess)
		{
			error_log("[request_parse_error][request=%s]", signedRequest.c_str());
			SINAWB_ENTRY_ERROR_RETURN(R_ERR_AUTH);
		}

		//process request
		string userId;
		string oauthToken;
		Json::GetString(jsonUserData, "user_id", userId);
		if(!Json::GetString(jsonUserData, "oauth_token", oauthToken))
		{
			string authUrl = s_authUrl;
			if(!iopenid.empty())
			{
				authUrl.append(Crypt::UrlEncode(string("?iopenid=") + iopenid));
			}
			CgiUtil::ScriptTopRedirect(authUrl);
			CGI_SEND_LOG("userid=%s&do=redirect_oauth", userId.c_str());
			return R_SUCCESS;
		}
		oauthToken = Crypt::UrlEncode(oauthToken);

		//check sig
		string hashAlgorithm;
		if(!Json::GetString(jsonUserData, "algorithm", hashAlgorithm))
		{
			error_log("[no_hash_algorithm][request=%s,openid=%s]", signedRequest.c_str(), userId.c_str());
			SINAWB_ENTRY_ERROR_RETURN(R_ERR_AUTH);
		}
		if(hashAlgorithm != "HMAC-SHA256")
		{
			error_log("[unknow_hash_algorithm][request=%s,algorithm=%s,openid=%s]",
					signedRequest.c_str(), hashAlgorithm.c_str(), userId.c_str());
			SINAWB_ENTRY_ERROR_RETURN(R_ERR_AUTH);
		}
		string hash = Crypt::HmacSha256(datas[1], OpenPlatform::GetPlatform()->GetAppKey());
		string encodeHash;
		Crypt::Base64UrlEncodeTrim(encodeHash, hash);
		if(encodeHash != datas[0])
		{
			error_log("[check_sig_error][request=%s,sig=%s,openid=%s]",
					signedRequest.c_str(), encodeHash.c_str(), userId.c_str());
			SINAWB_ENTRY_ERROR_RETURN(R_ERR_AUTH);
		}

		//redirect
		String::Format(redirectUrl, "%s?openid=%s&openkey=%s&iopenid=%s&ts=%u",
				s_gameHome.c_str(), userId.c_str(), oauthToken.c_str(), iopenid.c_str(), Time::GetGlobalTime());
		CgiUtil::HttpRedirect(redirectUrl.c_str());
		CGI_SEND_LOG("oauth=ok&openid=%s&iopenid=%s", userId.c_str(), iopenid.c_str());
		return R_SUCCESS;
	}

};

CGI_MAIN(CCgiSinaWbEntry)

