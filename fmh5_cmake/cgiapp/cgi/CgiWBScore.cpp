#include "LogicInc.h"
#include "WanBaPlatform.h"

class CCgiWBScore : public CCgiBase
{
public:
	CCgiWBScore() : CCgiBase("wbscore")
	{
		SetFeature(CF_PRINT_JSON);
		SetFeature(CF_GET_REMOTE_IP);
		SetFeature(CF_CHECK_PLATFORM);
	}

	CGI_DIRECT_PROCESS(score)

	int score()
	{
		if(OpenPlatform::GetType() != PT_WB)
		{
			PARAM_ERROR_RETURN_MSG("param_error");
		}

		const string openid = CCGIIn::GetCGIStr("openid");
		const string openkey = CCGIIn::GetCGIStr("openkey");
		const string pf = CCGIIn::GetCGIStr("pf");
		if (openid.empty() || openkey.empty() || pf.empty())
		{
			PARAM_ERROR_RETURN_MSG("param_error");
		}

		const string api_name = "/v3/user/get_playzone_userinfo";
		const string &appid = OpenPlatform::GetPlatform()->GetAppId();
		const string &appkey = OpenPlatform::GetPlatform()->GetAppKey();
		map<string, string> param_map;
		param_map["appid"] = appid;
		param_map["openid"] = openid;
		param_map["openkey"] = openkey;
		param_map["pf"] = pf;
		param_map["format"] = "json";
		param_map["userip"] = m_ipstr;
		param_map["zoneid"] = Config::GetIntValue(CONFIG_ZONE_ID);
		string url;
		WanBaPlatform::formatUrl(param_map, appkey, api_name, url, OpenPlatform::GetPlatform()->GetConfig("v3domain"));
		string response;
		if (!Network::HttpGetRequest(response, url) || response.empty())
		{
			error_log("[http request fail][url=%s,openid=%s,response=%s]", url.c_str(), openid.c_str(), response.c_str());
			ERROR_RETURN_MSG(R_ERR_NO_DATA, "http_request_fail");
		}

		Json::Value result;
		Json::Reader reader;
		int responsetRet = 0;
		if (response.empty()
		|| !reader.parse(response, result)
		|| !Json::GetInt(result, "code", responsetRet)
		|| responsetRet != 0
		|| !result.isMember("data")
		|| !result["data"].isArray()
		|| result["data"].size() == 0)
		{
			error_log("[response error][openid=%s,response=%s,url=%s]",
					openid.c_str(), response.c_str(), url.c_str());
			ERROR_RETURN_MSG(R_ERR_NO_DATA, "response_error");
		}

		int score = 0;
		Json::GetInt(result["data"][0u], "score", score);
		m_jsonResult["score"] = score;
		CGI_SEND_LOG("openid=%s&score=%d", openid.c_str(), score);
		return R_SUCCESS;
	}
};

CGI_MAIN(CCgiWBScore)
