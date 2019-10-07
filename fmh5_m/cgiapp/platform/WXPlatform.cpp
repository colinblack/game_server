#include "WXPlatform.h"
#include <iostream>

WXPlatform::WXPlatform()
{
}

int WXPlatform::Initialize(const string &appid, const string &appkey, map<string, string> &params)
{
	IOpenPlatform::Initialize(appid, appkey, params);
	return 0;
}

void WXPlatform::SetParameter(const map<string, string> &params)
{
	m_code.clear();
	map<string, string>::const_iterator it = params.find("code");
	if (it != params.end())
		m_code = it->second;
}

int WXPlatform::GetUserInfo(OPUserInfo &userInfo, const string &openid, const string &openkey)
{
	const string api = "/sns/jscode2session?";
	map<string,string> params;
	params["appid"] = m_appId;
	params["secret"] = m_appKey;
	params["js_code"] = m_code;
	params["grant_type"] = m_config["grant_type"];
	string qstr;
	formatUrl(params,"",api,qstr);
	string url = m_config["v3domain"] + qstr;
	string response;
	if (!Network::HttpGetRequest(response, url) || response.empty())
	{
		error_log("[http request fail].openid=%s",openid.c_str());
		return -1;
	}
	Json::Value value;
	if (!Json::Reader().parse(response, value))
	{
		error_log("[json parse fail].openid=%s",openid.c_str());
		return -1;
	}
	int ret = 0;
	//1.只有接口返回失败,才会有errcode字段,所以只要有errorcode,就返回错误
	if(Json::GetInt(value, "errcode", ret))
	{
		error_log("[get_info fail].response=%s,errcode=%d",response.c_str(),ret);
		return -1;
	}

	string openid_new;
	string session_key;
	if(!Json::GetString(value,"openid",openid_new) || !Json::GetString(value,"session_key",session_key))
	{
		error_log("[get_info fail].response=%s,openid_new=%s,session_key=%s",response.c_str(),openid_new.c_str(),session_key.c_str());
		return -1;
	}
	userInfo.OpenId = openid_new;
	return 0;
}

int WXPlatform::formatUrl(const map<string, string> &param,
		const string &appkey,
		const string &api,
		string &url)
{
	string qstr;
	map<string, string>::const_iterator itr = param.begin();
	for (; itr != param.end(); ++itr)
	{
		if (!qstr.empty())
		{
			qstr.append("&").append(itr->first).append("=").append(Crypt::UrlEncodeForTX(itr->second));
		}
		else
		{
			qstr.append(itr->first).append("=").append(Crypt::UrlEncodeForTX(itr->second));
		}
	}
	url = api + qstr;
	return 0;
}

string WXPlatform::GetErrorMessage()
{
	return "no error message";
}

string WXPlatform::GetSig(const map<string, string> &params, const string &appkey, bool get, const string &uri, string &qstr)
{
	string sig;
	return sig;
}

int WXPlatform::GetAppFriendList(OPFriendList &friendList, const string &openid, const string &openkey)
{

	return 0;
}

