#include "XMFourPlatform.h"
#include <iostream>

XMFourPlatform::XMFourPlatform()
{
}

int XMFourPlatform::Initialize(const string &appid, const string &appkey, map<string, string> &params)
{
	IOpenPlatform::Initialize(appid, appkey, params);
	m_gameid = m_config["gameid"];
	return 0;
}

void XMFourPlatform::SetParameter(const map<string, string> &params)
{
	m_token.clear();
	map<string, string>::const_iterator it = params.find("token");
	if (it != params.end())
		m_token = it->second;
}

int XMFourPlatform::GetUserInfo(OPUserInfo &userInfo, const string &openid, const string &openkey)
{
	const string api = "/v2/platform/checkToken";
	map<string,string> params;
	params["token"] = m_token;
	params["timestamp"] = CTrans::UTOS(Time::GetGlobalTime()) + "000";
	params["appId"] = m_appId;
	params["gameId"] = m_gameid;
	string sign;
	sign = GetSigStr(params,m_appKey);
	string url = m_config["v3domain"] + api;

	string qstr;
	GetPostData(params, sign, qstr);

	debug_log("token=%s,timestamp=%s,appId=%s,gameId=%s,sign=%s,url=%s,qstr=%s",
			  m_token.c_str(),
			  params["timestamp"].c_str(),
			  params["appId"].c_str(),
			  params["gameId"].c_str(),
			  sign.c_str(),
			  url.c_str(),
			  qstr.c_str());
	string response;
	if (!Network::HttpPostRequest(response, url, qstr) || response.empty())
	{
		error_log("[http request fail][token=%s]",m_token.c_str());
		return -1;
	}
	Json::Value value;
	if (!Json::Reader().parse(response, value))
	{
		error_log("[data_parse_failed][token=%s]",m_token.c_str());
		return -1;
	}

	//是否成功返回
	int code = 0;
	if (!Json::GetInt(value, "code", code) || code != 200)
	{
		error_log("[data_request_fail][token=%s,code=%d]",m_token.c_str(),code);
		return -1;
	}

	//获取对应信息
	if (!Json::IsObject(value, "data"))
	{
		error_log("[http request fail][userdata_str=%s]");
		return -1;
	}

	Json::Value userdata;
	if (!Json::GetObject(value, "data",userdata))
	{
		error_log("[user_data_parse_fail][token=%s]",m_token.c_str());
		return -1;
	}

	if (!Json::GetString(userdata, "uid", userInfo.OpenId))
	{
		error_log("[get_openid_failed][token=%s,code=%d]",m_token.c_str());
		return -1;
	}
	if (!Json::GetString(userdata, "nickname", userInfo.Name))
	{
		error_log("[get_name_failed][token=%s]",m_token.c_str());
	}
	if (!Json::GetString(userdata, "avatar", userInfo.FigureUrl))
	{
		error_log("[get_fig_failed][token=%s]",m_token.c_str());
	}
	return 0;
}

int XMFourPlatform::formatUrl(const map<string, string> &param,
		const string &appkey,
		const string &api,
		string &url)
{

	return 0;
}

string XMFourPlatform::GetErrorMessage()
{
	return "no error message";
}

void XMFourPlatform::GetPostData(const map<string, string> &params, const string &sig, string &qstr)
{
	map<string, string>::const_iterator it = params.begin();
	for (; it != params.end(); it++)
	{
		if (!qstr.empty())
		{
			qstr += "&";
		}
		qstr += it->first + "=" + Crypt::UrlEncodeForTX(it->second);
	}
	qstr += "&sign=" + Crypt::UrlEncodeForTX(sig);
}

int XMFourPlatform::GetAppFriendList(OPFriendList &friendList, const string &openid, const string &openkey)
{

	return 0;
}

string XMFourPlatform::GetSigStr(map<string,string> param,const string key)
{
	string sig = "";

	//签名按照请求参数名ASCII码从小到大排序（字典序），使用URL键值对的格式进行拼接
	map<string,string>::iterator it = param.begin();
	for(; it != param.end(); it++)
	{
		if(it->second != "")
		{
			sig += it->first + "=" + it->second + "&";
		}
	}

	//拼接sigkey
	sig += key;

	//进行md5运算
	sig = Crypt::Md5Encode(sig);

	return sig;
}
