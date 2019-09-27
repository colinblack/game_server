/*
 * New4399Platform.cpp
 *
 *  Created on: 2017-3-28
 *      Author: Ralf
 */


#include "New4399Platform.h"
#include <iostream>

CNew4399Platform::CNew4399Platform()
{
	m_time = m_cm = 0;
}

int CNew4399Platform::Initialize(const string &appid, const string &appkey, map<string, string> &params)
{
	IOpenPlatform::Initialize(appid, appkey, params);
	//info_log("[init ok][appid=%s,appkey=%s,v3domain=%s]",	appid.c_str(), appkey.c_str(), params["v3domain"].c_str());
	return 0;
}

void CNew4399Platform::SetParameter(const map<string, string> &params)
{
	m_time = m_cm = 0;
	m_site.clear();
	map<string, string>::const_iterator it;
	it = params.find("time");
	if (it != params.end())
		m_time = CTrans::STOI(it->second);
	it = params.find("cm");
	if (it != params.end())
		m_cm = CTrans::STOI(it->second);
	it = params.find("site");
	if (it != params.end())
		m_site = it->second;
}

int CNew4399Platform::GetUserInfo(OPUserInfo &userInfo, const string &openid, const string &openkey)
{
	userInfo.Clear();
	m_errorMessage.clear();

	if (Math::Abs(Time::GetGlobalTime() - m_time) > 300)
	{
		m_errorMessage = "time_out";
		error_log("[time_out][openid=%s,openkey=%s,errmsg=%s]",
				openid.c_str(), openkey.c_str(), m_errorMessage.c_str());
		return -1;
	}

	int server = 1;
	string osig  = openid
			+ CTrans::ITOS(m_time)
			+ GetConfig(CONFIG_4399_LOGIN_KEY)
			+ CTrans::ITOS(m_cm)
			+ m_site
			+ CTrans::ITOS(server);
	string sig = Crypt::Md5Encode(osig);
	if(sig != openkey)
	{
		m_errorMessage = "openkey_error";
		error_log("[openkey_error][openid=%s,openkey=%s,errmsg=%s]",
				openid.c_str(), openkey.c_str(), m_errorMessage.c_str());
		return -1;
	}
	userInfo.OpenId = openid;

	return 0;
}

int CNew4399Platform::GetAppFriendList(OPFriendList &friendList, const string &openid, const string &openkey)
{
	return 0;
}
int CNew4399Platform::Is_Login(const string &openid, const string &openkey,const string &pf)
{
	return 0;
}

string CNew4399Platform::GetErrorMessage()
{
	return m_errorMessage;
}

void CNew4399Platform::ReplyCharge()
{
	CgiUtil::PrintText("1");
}




