#include "LogicInc.h"

#define CONFIG_GAME_HOME	"game_home"
#define CONFIG_GAME_ENTRY	"game_entry"
#define CONFIG_AUTH_SCOPE   "auth_scope"
#define FB_AUTH_PAGE	"http://www.facebook.com/dialog/oauth?client_id=%s&scope=%s&redirect_uri=%s"
#define FB_GRAPH_URL	"https://graph.facebook.com/%s/?access_token=%s"

class CCgiFbEntry : public CCgiBase
{
public:

	CCgiFbEntry() : CCgiBase("fb/")
	{
		SetFeature(CF_GET_REMOTE_IP);
		SetFeature(CF_CHECK_PLATFORM);
	}

	CGI_DIRECT_PROCESS(FbEntry)

	int FbEntry()
	{
		//init
		static bool s_init = false;
		static string s_gameHome;
		static string s_authUrl;
		if(!s_init)
		{
			IOpenPlatform *pPlatform = OpenPlatform::GetPlatform();
			s_gameHome = pPlatform->GetConfig(CONFIG_GAME_HOME);
			String::Format(s_authUrl, FB_AUTH_PAGE, pPlatform->GetAppId().c_str(),
					Crypt::UrlEncode(pPlatform->GetConfig(CONFIG_AUTH_SCOPE)).c_str(),
					Crypt::UrlEncode(pPlatform->GetConfig(CONFIG_GAME_ENTRY)).c_str());
			s_init = true;
		}

		string redirectUrl;
		if(OpenPlatform::GetType() != PT_FACEBOOK)
		{
			error_log("[platform_error][cgi=FbEntry,platform=%d]", OpenPlatform::GetType());
			String::Format(redirectUrl, "%s?error=%d&ts=%u", s_gameHome.c_str(), R_ERR_REFUSE, Time::GetGlobalTime());
			CgiUtil::ScriptRedirect(redirectUrl);
			return R_ERR_REFUSE;
		}

		//get user data
		string error = CCGIIn::GetCGIStr("error");
		if(!error.empty())
		{
			error_log("[platform_auth_error][error=%s,error_reason=%s,error_desc=%s]",
					error.c_str(), CCGIIn::GetCGIStr("error_reason").c_str(), CCGIIn::GetCGIStr("error_description").c_str());
			String::Format(redirectUrl, "%s?error=%d&ts=%u", s_gameHome.c_str(), R_ERR_AUTH, Time::GetGlobalTime());
			CgiUtil::ScriptRedirect(redirectUrl);
			return R_ERR_AUTH;
		}

		string iopenid = CCGIIn::GetCGIStr("iopenid");
		string requestIds = CCGIIn::GetCGIStr("request_ids");
		string signedRequest = CCGIIn::GetCGIStr("signed_request");
		if(signedRequest.empty())
		{
			//check error
			String::Format(redirectUrl, "%s?error=%d&ts=%u", s_gameHome.c_str(), R_ERR_AUTH, Time::GetGlobalTime());
			CgiUtil::ScriptRedirect(redirectUrl);
			return R_ERR_AUTH;
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
					parseSuccess = true;
				}
			}
		}
		if(!parseSuccess)
		{
			error_log("[request_parse_error][request=%s]", signedRequest.c_str());
			String::Format(redirectUrl, "%s?error=%d&ts=%u", s_gameHome.c_str(), R_ERR_AUTH, Time::GetGlobalTime());
			CgiUtil::ScriptRedirect(redirectUrl);
			return R_ERR_AUTH;
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
			else if(!requestIds.empty())
			{
				authUrl.append(Crypt::UrlEncode(string("?request_ids=") + requestIds));
			}
			CgiUtil::ScriptTopRedirect(authUrl);
			CGI_SEND_LOG("userid=%s&do=redirect_oauth", userId.c_str());
			return R_SUCCESS;
		}
		oauthToken = Crypt::UrlEncode(oauthToken);
		string locale;
		if(Json::IsObject(jsonUserData, "user"))
		{
			Json::GetString(jsonUserData["user"], "locale", locale);
		}

		//get iopenid
		if(iopenid.empty())
		{
			if(!requestIds.empty())
			{
				vector<string> vecRequestIds;
				CBasic::StringSplitTrim(requestIds, ",", vecRequestIds);
				if(vecRequestIds.size() > 0)
				{
					string requestId = vecRequestIds[0];
					iopenid = GetIOpenIdFromRequest(requestId, userId, oauthToken);
				}
			}
		}

		//get extra request params
		map<string, string> requestParams;
		CgiUtil::GetRequestParams(requestParams);
		if(!iopenid.empty())
		{
			requestParams["iopenid"] = iopenid;
		}
		string extraParams;
		for(map<string, string>::iterator itr = requestParams.begin(); itr != requestParams.end(); itr++)
		{
			extraParams.append("&");
			extraParams.append(itr->first);
			extraParams.append("=");
			extraParams.append(itr->second);
		}

		//redirect
		String::Format(redirectUrl, "%s?openid=%s&openkey=%s&locale=%s&ts=%u%s",
				s_gameHome.c_str(), userId.c_str(), oauthToken.c_str(),
				locale.c_str(), Time::GetGlobalTime(), extraParams.c_str());
		CgiUtil::ScriptRedirect(redirectUrl.c_str());
		SEND_LOG("FbEntry", CCGIIn::GetStrRemoteIP(), "oauth=ok&openid=%s&iopenid=%s&locale=%s",
				userId.c_str(), iopenid.c_str(), locale.c_str());
		return R_SUCCESS;
	}

protected:

	string GetIOpenIdFromRequest(const string &requestId, const string &openid, const string &openkey)
	{
		string url;
		string response;
		String::Format(url, FB_GRAPH_URL, requestId.c_str(), openkey.c_str());
		if(!Network::HttpGetRequest(response, url))
		{
			error_log("[get request fail][reason=HttpGetRequest,request_id=%s,openid=%s,openkey=%s,errmsg=%s]",
					requestId.c_str(), openid.c_str(), openkey.c_str(), response.c_str());
			return "";
		}
		Json::Value jsonRequest;
		if(!Json::FromString(jsonRequest, response))
		{
			error_log("[json parse fail][reason=JsonParse,request_id=%s,openid=%s,openkey=%s,response=%s]",
					requestId.c_str(), openid.c_str(), openkey.c_str(), response.c_str());
			return "";
		}
		if(!jsonRequest.isObject())
		{
			error_log("[json data error][reason=JsonParse,request_id=%s,openid=%s,openkey=%s,response=%s]",
					requestId.c_str(), openid.c_str(), openkey.c_str(), response.c_str());
			return "";
		}
		string iopenid;
		if(Json::IsObject(jsonRequest, "from"))
		{
			Json::GetString(jsonRequest["from"], "id", iopenid);
		}
		if(iopenid.empty())
		{
			error_log("[request data error][reason=DataParse,request_id=%s,openid=%s,openkey=%s,response=%s]",
				requestId.c_str(), openid.c_str(), openkey.c_str(), response.c_str());
		}
		return iopenid;
	}

};

CGI_MAIN(CCgiFbEntry)

