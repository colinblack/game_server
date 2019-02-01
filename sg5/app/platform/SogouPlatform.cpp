/*
 * SogouPlatform.cpp
 *
 *  Created on: 2015-9-01
 *      Author: Eddard
 */

#include "SogouPlatform.h"
#include <iostream>

SogouPlatform::SogouPlatform()
{
	m_cm = 0;
}

int SogouPlatform::Initialize(const string &appid, const string &appkey, map<string, string> &params)
{
	IOpenPlatform::Initialize(appid, appkey, params);
	//info_log("[init ok][appid=%s,appkey=%s,v3domain=%s]",	appid.c_str(), appkey.c_str(), params["v3domain"].c_str());
	return 0;
}

void SogouPlatform::SetParameter(const map<string, string> &params)
{
	m_pf.clear();
	m_userip.clear();
	m_time.clear();
	m_cm = 0;
	map<string, string>::const_iterator it = params.find("pf");
	if (it != params.end())
		m_pf = it->second;
	it = params.find("userip");
	if (it != params.end())
		m_userip = it->second;
	it = params.find("time");
	if (it != params.end())
		m_time = it->second;
    it = params.find("cm");
    if (it != params.end())
        m_cm = CTrans::STOI(it->second);

}

int SogouPlatform::GetUserInfo(OPUserInfo &userInfo, const string &openid, const string &openkey)
{
	userInfo.Clear();
	m_errorMessage.clear();

	unsigned time = 0;
	struct tm t;
	if (strptime(m_time.c_str(), "%Y%m%d%H%M%S", &t) != NULL)
		time = CTime::MakeTime(t);

	if (Math::Abs(Time::GetGlobalTime() - time) > 7200)
	{
		m_errorMessage = "time_out";
		error_log("[time_out][openid=%s,openkey=%s,errmsg=%s]",
				openid.c_str(), openkey.c_str(), m_errorMessage.c_str());
		return -1;
	}

	int server = 0;
	Config::GetDB(server);
	map<string, string> params;
	params["gid"] = m_appId;
	params["sid"] = CTrans::ITOS(server);
	params["uid"] = openid;
	params["cm"] = CTrans::ITOS(m_cm);
	params["time"] = m_time;
	map<string, string>::iterator iter = params.begin();
	string osig = "";
	for (; iter != params.end(); ++iter)
	{
		osig += iter->first + "=" + iter->second + "&";
	}
	osig += m_appKey;

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

int SogouPlatform::GetAppFriendList(OPFriendList &friendList, const string &openid, const string &openkey)
{
	return 0;
}
int SogouPlatform::Is_Login(const string &openid, const string &openkey,const string &pf)
{
	return 0;
}

string SogouPlatform::GetErrorMessage()
{
	return m_errorMessage;
}

void SogouPlatform::ReplyCharge()
{
}
