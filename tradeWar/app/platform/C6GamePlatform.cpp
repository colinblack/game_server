/*
 * C6GamePlatform.cpp
 *
 *  Created on: 2019年3月1日
 *      Author: colin
 */

#include "C6GamePlatform.h"
#include "Common.h"


CC6GamePlatform::CC6GamePlatform(): m_type(PT_UNKNOW)
{

}

CC6GamePlatform::~CC6GamePlatform()
{

}

int CC6GamePlatform::Initialize(const string &appid, const string &appkey, map<string, string> &params) {
	IOpenPlatform::Initialize(appid, appkey, params);
	m_type = PT_C6_IOS;
	return 0;
}


void CC6GamePlatform::GetQueryData(const map<string, string>& params, string& data)
{
	data.clear();
	map<string, string>::const_iterator itr = params.begin();
	for (; itr != params.end(); ++itr)
	{
		data.append(itr->first).append("=").append(itr->second).append("&");
	}
	if (!data.empty())
	{
		data.erase(data.length() - 1);
	}
}

int CC6GamePlatform::GetUserInfo(OPUserInfo &userInfo, const string &openid, const string &openkey, const string &pf, const string &userip)
{
	const string api = "/api/cp/user/check";
	map<string, string> params;
	params["app_id"] = m_config["c6_appid"];
	params["mem_id"] = openid;
	params["user_token"] = openkey;

	string queryData;
	GetQueryData(params, queryData);
	string sig = Crypt::Md5Encode(queryData + "&app_key=" + m_config["c6_appkey"]);
	params["sign"] = sig;
	GetQueryData(params, queryData);

	string url = "https://" + m_config["c6_v3domain"] + api;

	debug_log("url:%s, querydata:%s", url.c_str(), queryData.c_str());
	string resp;
	if (!Network::HttpPostRequest(resp, url, queryData) || resp.empty()) {
		error_log("[http request fail][query=%s,errmsg=%s]", queryData.c_str(), resp.c_str());
		return -1;
	}
	Json::Value result;
	Json::Reader reader;
	if (!reader.parse(resp, result))
	{
		error_log("[http request fail][query=%s,errmsg=%s]", queryData.c_str(), resp.c_str());
		return -1;
	}
	string status;
	Json::GetString(result, "status", status);
	if (status != "1")
	{
		error_log("[http request fail][query=%s,errmsg=%s]", queryData.c_str(), resp.c_str());
		return -1;
	}

	userInfo.Clear();
	userInfo.OpenId = openid;

	return 0;
}

string CC6GamePlatform::GetErrorMessage() {
	return "no error message";
}

