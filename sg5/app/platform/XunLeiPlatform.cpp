/*
 * XunLeiPlatform.cpp
 *
 *  Created on: 2017-3-21
 *      Author: Ralf
 */




#include "XunLeiPlatform.h"
#include <iostream>

XunLeiPlatform::XunLeiPlatform()
{
	m_time = m_cm = m_clienttype = 0;
}

int XunLeiPlatform::Initialize(const string &appid, const string &appkey, map<string, string> &params)
{
	IOpenPlatform::Initialize(appid, appkey, params);
	//info_log("[init ok][appid=%s,appkey=%s,v3domain=%s]",	appid.c_str(), appkey.c_str(), params["v3domain"].c_str());
	return 0;
}

void XunLeiPlatform::SetParameter(const map<string, string> &params)
{
	m_pf.clear();
	m_userip.clear();
	m_time = m_cm = m_clienttype = 0;
	map<string, string>::const_iterator it = params.find("pf");
	if (it != params.end())
		m_pf = it->second;
	it = params.find("userip");
	if (it != params.end())
		m_userip = it->second;
	it = params.find("time");
	if (it != params.end())
		m_time = CTrans::STOI(it->second);
    it = params.find("cm");
    if (it != params.end())
        m_cm = CTrans::STOI(it->second);
    it = params.find("clienttype");
    if (it != params.end())
    	m_clienttype = CTrans::STOI(it->second);
}

int XunLeiPlatform::GetUserInfo(OPUserInfo &userInfo, const string &openid, const string &openkey)
{
	userInfo.Clear();
	m_errorMessage.clear();

	if (Math::Abs(Time::GetGlobalTime() - m_time) > 7200)
	{
		m_errorMessage = "time_out";
		error_log("[time_out][openid=%s,openkey=%s,cm=%u,m_time=%u,errmsg=%s]",
				openid.c_str(), openkey.c_str(), m_cm, m_time, m_errorMessage.c_str());
		return -1;
	}

	string agent = "xunlei", clienttype = CTrans::ITOS(m_clienttype), goldlevel = "0", isvip = "0", isgoldvip = "0", paytype = "0", viplevel = "0", viptype = "0";
	int server = 0;
	Config::GetDB(server);
	string osig = agent + clienttype + CTrans::ITOS(m_cm) + goldlevel + isvip + isgoldvip + paytype
				+ m_appKey + CTrans::ITOS(server) + CTrans::ITOS(m_time) + openid + viplevel + viptype;
	string sig = Crypt::Md5Encode(osig);
	if(sig != openkey)
	{
		m_errorMessage = "openkey_error";
		error_log("[openkey_error][openid=%s,openkey=%s,osig=%s,sig=%s]",
				openid.c_str(), openkey.c_str(), osig.c_str(), sig.c_str());
		return -1;
	}
	userInfo.OpenId = openid;

	userInfo.ExtraIntInfo["xunlei_clienttype"] = m_clienttype;
	string ts = CTrans::UTOS(Time::GetGlobalTime());
	string url = "http://websvr.niu.xunlei.com/queryGameJinzuanVip.gameUserInfo?gameid=" + GetAppId()
			+ "&customerid=" + openid
			+ "&time=" + ts
			+ "&sign=" + Crypt::Md5Encode(GetAppId() + openid + ts + "hyidn87d678p0dj7");
	string response;
	Json::Value value;
	try
	{
		if (Network::HttpGetRequest(response, url) && !response.empty() && Json::Reader().parse(response, value)
		&& value.isMember("code") && value["code"].asInt() == 0 && value.isMember("jinzuanLevel"))
			userInfo.ExtraIntInfo["xunlei_vip_level"] = value["jinzuanLevel"].asInt();
		else
			userInfo.ExtraIntInfo["xunlei_vip_level"] = 0;
	}
	catch(const std::exception& e)
	{
		error_log("vip: %s, %s", url.c_str(), response.c_str());
	}

	return 0;
}

int XunLeiPlatform::GetAppFriendList(OPFriendList &friendList, const string &openid, const string &openkey)
{
	return 0;
}
int XunLeiPlatform::Is_Login(const string &openid, const string &openkey,const string &pf)
{
	return 0;
}

string XunLeiPlatform::GetErrorMessage()
{
	return m_errorMessage;
}

void XunLeiPlatform::ReplyCharge()
{
	CgiUtil::PrintText(m_reply.c_str());
	m_reply.clear();
}
void XunLeiPlatform::SetReply(string& reply)
{
	m_reply = reply;
}

