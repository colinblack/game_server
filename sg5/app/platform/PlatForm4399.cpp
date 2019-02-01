/*
 * PlatForm4399.cpp
 *
 *  Created on: 2015-4-30
 *      Author: Ralf
 */


#include "PlatForm4399.h"
#include <iostream>

CPlatform4399::CPlatform4399()
{
	m_time = m_cm = 0;
}

int CPlatform4399::Initialize(const string &appid, const string &appkey, map<string, string> &params)
{
	IOpenPlatform::Initialize(appid, appkey, params);
	//info_log("[init ok][appid=%s,appkey=%s,v3domain=%s]",	appid.c_str(), appkey.c_str(), params["v3domain"].c_str());
	return 0;
}

void CPlatform4399::SetParameter(const map<string, string> &params)
{
	m_pf.clear();
	m_userip.clear();
	m_time = m_cm = 0;
	map<string, string>::const_iterator it = params.find("pf");
	if (it != params.end())
		m_pf = it->second;
	it = params.find("userip");
	if (it != params.end())
		m_userip = it->second;
	it = params.find("time4399");
	if (it != params.end())
		m_time = CTrans::STOI(it->second);
	it = params.find("cm4399");
	if (it != params.end())
		m_cm = CTrans::STOI(it->second);

}

int CPlatform4399::GetUserInfo(OPUserInfo &userInfo, const string &openid, const string &openkey)
{
	userInfo.Clear();
	m_errorMessage.clear();

	if (Math::Abs(Time::GetGlobalTime() - m_time) > 7200)
	{
		m_errorMessage = "time_out";
		error_log("[time_out][openid=%s,openkey=%s,errmsg=%s]",
				openid.c_str(), openkey.c_str(), m_errorMessage.c_str());
		return -1;
	}

	int server = 0;
	Config::GetDB(server);
	string osig  = openid
			+ CTrans::ITOS(m_time)
			+ GetConfig(CONFIG_4399_LOGIN_KEY)
			+ CTrans::ITOS(m_cm)
			+ "S" + CTrans::ITOS(server);
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

int CPlatform4399::GetAppFriendList(OPFriendList &friendList, const string &openid, const string &openkey)
{
	return 0;
}
int CPlatform4399::Is_Login(const string &openid, const string &openkey,const string &pf)
{
	return 0;
}

string CPlatform4399::GetErrorMessage()
{
	return m_errorMessage;
}

void CPlatform4399::ReplyCharge()
{
	CgiUtil::PrintText("1");
}


