/*
 * U9Platform.cpp
 *
 *  Created on: 2018年8月24日
 *      Author: Ralf
 */





#include "U9Platform.h"
#include <iostream>

U9Platform::U9Platform()
{
}

int U9Platform::Initialize(const string &appid, const string &appkey, map<string, string> &params)
{
	IOpenPlatform::Initialize(appid, appkey, params);
	//info_log("[init ok][appid=%s,appkey=%s,v3domain=%s]",	appid.c_str(), appkey.c_str(), params["v3domain"].c_str());
	return 0;
}

void U9Platform::SetParameter(const map<string, string> &params)
{
	m_pf.clear();
	map<string, string>::const_iterator it = params.find("pf");
	if (it != params.end())
		m_pf = it->second;
}

int U9Platform::GetUserInfo(OPUserInfo &userInfo, const string &openid, const string &openkey)
{
	userInfo.Clear();
	m_errorMessage.clear();

	if(m_pf == "u9-android")
	{
		string url = m_config["v3domaina"] + "?UserId=" + openid + "&Token=" + openkey;
		string response;
		if (!Network::HttpGetRequest(response, url) || response.empty())
		{
			m_errorMessage = response;
			error_log("[http fail][url=%s,response=%s]", url.c_str(), response.c_str());
			return -1;
		}
		Json::Value value;
		if(!Json::Reader().parse(response, value))
		{
			m_errorMessage = response;
			error_log("[json parse fail][url=%s,response=%s]", url.c_str(), response.c_str());
			return -1;
		}
		int Code;
		if (!Json::GetInt(value, "Code", Code) || Code != 0)
		{
			Json::GetString(value, "Message", m_errorMessage);
			error_log("[get_info fail][url=%s,response=%s]", url.c_str(), response.c_str());
			return -1;
		}
	}
	else if(m_pf == "u9-ios")
	{
		string url = m_config["v3domaini"];
		string data = "guid=" + openid + "&token=" + openkey;
		string response;
		if (!Network::HttpPostRequest(response, url, data) || response.empty())
		{
			m_errorMessage = response;
			error_log("[http fail][data=%s,response=%s]", data.c_str(), response.c_str());
			return -1;
		}
		Json::Value value;
		if(!Json::Reader().parse(response, value))
		{
			m_errorMessage = response;
			error_log("[json parse fail][data=%s,response=%s]", data.c_str(), response.c_str());
			return -1;
		}
		int status;
		if (!Json::GetInt(value, "status", status) || status != 0)
		{
			Json::GetString(value, "message", m_errorMessage);
			error_log("[get_info fail][data=%s,response=%s]", data.c_str(), response.c_str());
			return -1;
		}
	}
	else
	{
		m_errorMessage = "pf_err";
		error_log("[pf fail][pf=%s]", m_pf.c_str());
		return -1;
	}

	userInfo.OpenId = openid;

	return 0;
}

int U9Platform::GetAppFriendList(OPFriendList &friendList, const string &openid, const string &openkey)
{
	return 0;
}
int U9Platform::Is_Login(const string &openid, const string &openkey,const string &pf)
{
	return 0;
}

string U9Platform::GetErrorMessage()
{
	return m_errorMessage;
}

void U9Platform::ReplyCharge()
{
	CgiUtil::PrintText(m_reply.c_str());
	m_reply.clear();
}
void U9Platform::SetReply(string& reply)
{
	m_reply = reply;
}



