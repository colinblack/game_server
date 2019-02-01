/*
 * Platform360.cpp
 *
 *  Created on: 2017-4-11
 *      Author: Ralf
 */

#include "Platform360.h"
#include <iostream>

Platform360::Platform360()
{
	m_time = 0;
}

int Platform360::Initialize(const string &appid, const string &appkey, map<string, string> &params)
{
	IOpenPlatform::Initialize(appid, appkey, params);
	//info_log("[init ok][appid=%s,appkey=%s,v3domain=%s]",	appid.c_str(), appkey.c_str(), params["v3domain"].c_str());
	return 0;
}

void Platform360::SetParameter(const map<string, string> &params)
{
	m_pf.clear();
	m_userip.clear();
	m_cm.clear();
	m_time = 0;
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
        m_cm = it->second;
}

int Platform360::GetUserInfo(OPUserInfo &userInfo, const string &openid, const string &openkey)
{
	userInfo.Clear();
	m_errorMessage.clear();

	if (Math::Abs(Time::GetGlobalTime() - m_time) > 7200)
	{
		m_errorMessage = "time_out";
		error_log("[time_out][openid=%s,openkey=%s,cm=%s,m_time=%u,errmsg=%s]",
				openid.c_str(), openkey.c_str(), m_cm.c_str(), m_time, m_errorMessage.c_str());
		return -1;
	}

	string platForm = "wan", sss = "#";
	int server = 0;
	Config::GetDB(server);
	string osig = openid + platForm + GetAppId() + CTrans::ITOS(server) + CTrans::ITOS(m_time) + m_cm + sss + m_appKey;
	string sig = Crypt::Md5Encode(osig);
	if(sig != openkey)
	{
		m_errorMessage = "openkey_error";
		error_log("[openkey_error][openid=%s,openkey=%s,osig=%s,sig=%s]",
				openid.c_str(), openkey.c_str(), osig.c_str(), sig.c_str());
		return -1;
	}
	userInfo.OpenId = openid;

	return 0;
}

int Platform360::GetAppFriendList(OPFriendList &friendList, const string &openid, const string &openkey)
{
	return 0;
}
int Platform360::Is_Login(const string &openid, const string &openkey,const string &pf)
{
	return 0;
}

string Platform360::GetErrorMessage()
{
	return m_errorMessage;
}

void Platform360::ReplyCharge()
{
	CgiUtil::PrintText(m_reply.c_str());
	m_reply.clear();
}
void Platform360::SetReply(string& reply)
{
	m_reply = reply;
}


