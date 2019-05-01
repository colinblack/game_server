/*
 * BaiduPlatform.cpp
 *
 *  Created on: 2015-12-12
 *      Author: zkw
 */

#include "BaiduPlatform.h"
#include <iostream>

BaiduPlatform::BaiduPlatform()
{
	m_cm = 0;
}

int BaiduPlatform::Initialize(const string &appid, const string &appkey, map<string, string> &params)
{
	IOpenPlatform::Initialize(appid, appkey, params);
	//info_log("[init ok][appid=%s,appkey=%s,v3domain=%s]",	appid.c_str(), appkey.c_str(), params["v3domain"].c_str());
	return 0;
}

void BaiduPlatform::SetParameter(const map<string, string> &params)
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
	it = params.find("time4399");
	if (it != params.end())
		m_time = it->second;
    it = params.find("cm4399");
    if (it != params.end())
        m_cm = CTrans::STOI(it->second);
}

int BaiduPlatform::GetUserInfo(OPUserInfo &userInfo, const string &openid, const string &openkey)
{
	userInfo.Clear();
	m_errorMessage.clear();

	//sign=md5(secret_key+“api_key”+api_key+“cm_flag”+cm_flag+“server_id”+server_id+“timestamp”+timestamp+“user_id”+user_id)
	string osig = "";
	osig += m_appKey;

	osig += "api_key";
	osig += m_appId;

	osig += "cm_flag";
	osig +=  (m_cm?"y":"n");

	osig += "server_id";
	int server = 0;
	Config::GetDB(server);
	osig += CTrans::ITOS(server);

	osig += "timestamp";
	osig += m_time;

	osig += "user_id";
	osig += openid;

	string sig = Crypt::Md5Encode(osig);    //要确定加密后为大写
	String::ToUpper(sig);
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

int BaiduPlatform::GetAppFriendList(OPFriendList &friendList, const string &openid, const string &openkey)
{
	return 0;
}
int BaiduPlatform::Is_Login(const string &openid, const string &openkey,const string &pf)
{
	return 0;
}

string BaiduPlatform::GetErrorMessage()
{
	return m_errorMessage;
}

void BaiduPlatform::ReplyCharge()
{
	CgiUtil::PrintText(m_reply);
	m_reply.clear();
}

void BaiduPlatform::SetReply(string& reply)
{
	m_reply = reply;
}
