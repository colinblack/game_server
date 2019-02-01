/*
 * LogicSso.cpp
 *
 *  Created on: 2011-12-22
 *      Author: dada
 */

#include "LogicSso.h"

#define MAX_OPEN_KEY_LENGTH 200

static int GetSession(unsigned uid, const string &openid, const string &openkey, string &skey)
{
	string sessionData = Session::GetValue(uid, SESSION_DATA);
	if(sessionData.empty())
	{
		ERROR_RETURN(R_ERR_SESSION);
	}
	Json::Value value;
	if(!Json::FromString(value, sessionData))
	{
		error_log("[session_data_error][uid=%d,session_data=%s]", uid, sessionData.c_str());
		Session::RemoveSession(uid);
		ERROR_RETURN(R_ERR_SESSION);
	}
	unsigned lastVisitTime = 0;
	Json::GetUInt(value, "lvt", lastVisitTime);
	if(lastVisitTime + SESSION_TIME_OUT < Time::GetGlobalTime())
	{
		Session::RemoveSession(uid);
		ERROR_RETURN(R_ERR_SESSION);
	}
	string realOpenId;
	string realOpenKey;
	string realKey;
	if(!Json::GetString(value, "oid", realOpenId) ||
		!Json::GetString(value, "okey", realOpenKey) ||
		!Json::GetString(value, "skey", realKey))
	{
		error_log("[session_data_error][uid=%d,session_data=%s]", uid, sessionData.c_str());
		ERROR_RETURN(R_ERR_SESSION);
	}
	if(openid != realOpenId)
	{
		ERROR_RETURN(R_ERR_SESSION);
	}
	if(openkey.size() > MAX_OPEN_KEY_LENGTH)
	{
		if(openkey.substr(0, MAX_OPEN_KEY_LENGTH) != realOpenKey)
		{
			ERROR_RETURN(R_ERR_SESSION);
		}
	}
	else
	{
		if(realOpenKey != openkey)
		{
			ERROR_RETURN(R_ERR_SESSION);
		}
	}
	int platformType = -1;
	Json::GetInt(value, "pt", platformType);
	if(platformType != OpenPlatform::GetType())
	{
		ERROR_RETURN(R_ERR_SESSION);
	}
	//unsigned remoteip = value.get("rip", 0).asUInt();

	value["lvt"] = Time::GetGlobalTime();
	sessionData = Json::ToString(value);
	Session::SetValue(uid, SESSION_DATA, sessionData);
	skey = realKey;
	return 0;
}

int LogicSso::Login(string &openid, const string &openkey, bool white, const string &iopenid,
		const string &pf, const string &userip, bool verified, bool ingame, unsigned &uid, string &skey)
{
	//非新用户检查Session
	int ret;
	if(openid.empty() && openkey.empty())
	{
		PARAM_ERROR_RETURN();
	}
	uid = 0;
//	ret = LogicUserBasic::GetUid(uid, OpenPlatform::GetType(), openid);
//	if(ret == 0)
//	{
//		if(GetSession(uid, openid, openkey, skey) == 0)
//		{
//			if(ingame)
//			{
//				ret = LogicUser::OnLogin(uid, OpenPlatform::GetType(), openid, openkey);
//				if(ret != 0)
//				{
//					return ret;
//				}
//				return Verify(uid, ingame, verified);
//			}
//			return 0;
//		}
//	}
//	else if(ret != R_ERR_NO_DATA)
//	{
//		return ret;
//	}
//	else if(!ingame)
//	{
//		ERROR_RETURN_MSG(R_ERR_LOGIC, "user_not_exist");
//	}

	//登录
	if(white)
	{
		//白名单
		if(!WhiteList::Check(openid, openkey))
		{
			error_log("[invalid white user][openid=%s,openkey=%s]", openid.c_str(), openkey.c_str());
			ERROR_RETURN(R_ERR_AUTH);
		}
		uid = Convert::StringToUInt(openid, 0);
		if(!IsValidUid(uid))
		{
			error_log("[invalid white user][openid=%s,openkey=%s]", openid.c_str(), openkey.c_str());
			ERROR_RETURN(R_ERR_AUTH);
		}
		info_log("[white user login][uId=%d,openid=%s,openkey=%s]", uid, openid.c_str(), openkey.c_str());
	}
	else
	{
		//非白名单
		int ret;

		map<string, string> params;
		params["pf"] = pf;
		params["userip"] = userip;
		OpenPlatform::GetPlatform()->SetParameter(params);

		OPUserInfo userinfo;
		ret = OpenPlatform::GetPlatform()->GetUserInfo(userinfo, openid, openkey);
		if (ret != 0)
		{
			error_log("[GetUserInfo fail][ret=%d,openid=%s,openkey=%s]", ret,openid.c_str(),openkey.c_str());
			ERROR_RETURN(R_ERR_AUTH);
		}
		if (userinfo.Name.empty())
		{
			error_log("[GetUserInfo name empty][openid=%s,openkey=%s,name=%s,pic=%s]",
					openid.c_str(), openkey.c_str(), userinfo.Name.c_str(), userinfo.FigureUrl.c_str());
			//ERROR_RETURN(R_ERR_AUTH);
		}
		openid = userinfo.OpenId;

		if(IsValidUid(uid) && ingame)
		{
			ret = Verify(uid, ingame, verified);
			if(ret != 0)
			{
				return ret;
			}
		}

		OPFriendList friendList;
		ret = OpenPlatform::GetPlatform()->GetAppFriendList(friendList, openid, openkey);
		if(ret != 0)
		{
			error_log("[GetAppFriendList fail][ret=%d,openid=%s,openkey=%s]",
					ret,openid.c_str(),openkey.c_str());
			//ERROR_RETURN(R_ERR_AUTH);
		}

		//平台登录时间耗时较长，所以登录后再次确认有没有重复登录
		if(IsValidUid(uid))
		{
			if(GetSession(uid, openid, openkey, skey) == 0)
			{
				info_log("[concurrent_login][openid=%s,openkey=%s,uid=%u,skey=%s]",
						openid.c_str(), openkey.c_str(), uid, skey.c_str());
				if(ingame)
				{
					return LogicUser::OnLogin(uid, OpenPlatform::GetType(), openid, openkey);
				}
				return 0;
			}
		}
		ret = LogicUserBasic::LoginPlatformUser(OpenPlatform::GetType(), userinfo, friendList, openkey, iopenid, uid);
		if(ret != 0)
		{
			return ret;
		}
		if(ingame)
		{
			ret = LogicUser::OnLogin(uid, OpenPlatform::GetType(), openid, openkey);
			if(ret != 0)
			{
				return ret;
			}
		}
	}

	//保存Session
	skey = Session::CreateSessionKey(uid);
	Json::Value sessionData;
	sessionData["skey"] = skey;;
	sessionData["lvt"] = Time::GetGlobalTime();;
	sessionData["oid"] = openid;
	if(openkey.size() > MAX_OPEN_KEY_LENGTH)
	{
		sessionData["okey"] = openkey.substr(0, MAX_OPEN_KEY_LENGTH);
	}
	else
	{
		sessionData["okey"] = openkey;
	}
	sessionData["pt"] = (int)OpenPlatform::GetType();
	Session::SetValue(uid, SESSION_DATA, Json::ToString(sessionData));
	return 0;
}

bool LogicSso::IsLogin(unsigned uid, const string &skey)
{
	if(!IsValidUid(uid) || skey.empty())
	{
		return false;
	}
	string sessionData = Session::GetValue(uid, SESSION_DATA);
	if(sessionData.empty())
	{
		error_log("[skey_empty][uid=%d,skey=%s]", uid, skey.c_str());
		return false;
	}
	Json::Value value;
	if(!Json::FromString(value, sessionData))
	{
		error_log("[session_data_error][uid=%u,session_data=%s]", uid, sessionData.c_str());
		Session::RemoveSession(uid);
		return false;
	}
	unsigned lastVisitTime = 0;
	Json::GetUInt(value, "lvt", lastVisitTime);
	if(lastVisitTime + SESSION_TIME_OUT < Time::GetGlobalTime())
	{
		Session::RemoveSession(uid);
		error_log("[session_overtime][uid=%u,time=%u,last_visit_time=%u]", uid, Time::GetGlobalTime(), lastVisitTime);
		return false;
	}
	string realKey;
	if(!Json::GetString(value, "skey", realKey))
	{
		error_log("[session_key_empty][uid=%u,skey=%s,session_data=%s]", uid, skey.c_str(), sessionData.c_str());
		return false;
	}
	if(realKey != skey)
	{
		error_log("[session_key_error][uid=%u,skey=%s,real_skey=%s]", uid, skey.c_str(), realKey.c_str());
		return false;
	}
	int platformType = -1;
	Json::GetInt(value, "pt", platformType);
	if(OpenPlatform::GetType() != platformType)
	{
		error_log("[session_platform_error][uid=%u,platform=%s,real_platfrom=%s]", uid, OpenPlatform::GetType(), platformType);
		return false;
	}
	//unsigned remoteip = value.get("rip", 0).asUInt();

	value["lvt"] = Time::GetGlobalTime();
	Session::SetValue(uid, SESSION_DATA, Json::ToString(value));
	return true;
}

int LogicSso::GetOpenKey(unsigned uid, string &openid, string &openkey)
{
	string sData = Session::GetValue(uid, SESSION_DATA);
	if(sData.empty())
	{
		error_log("[get_session_data_fail][uid=%u,data=%s]", uid, sData.c_str());
		ERROR_RETURN(R_ERR_NO_DATA);
	}
	Json::Value data;
	if(!Json::FromString(data, sData))
	{
		error_log("[get_session_data_fail][uid=%u,data=%s]", uid, sData.c_str());
		DATA_ERROR_RETURN_MSG("get_session_data_fail");
	}
	if(!Json::GetString(data, "oid", openid) || !Json::GetString(data, "okey", openkey))
	{
		error_log("[parse_session_data_fail][uid=%u,data=%s]", uid, sData.c_str());
		DATA_ERROR_RETURN_MSG("get_session_data_fail");
	}
	return 0;
}

int LogicSso::GetLoginUid(unsigned &uid, const string &openid, const string &openkey)
{
	int ret;
	if(openid.empty() || openkey.empty())
	{
		PARAM_ERROR_RETURN();
	}
	ret = LogicUserBasic::GetUid(uid, OpenPlatform::GetType(), openid);
	if(ret != 0)
	{
		return ret;
	}
	string skey;
	ret = GetSession(uid, openid, openkey, skey);
	if(ret != 0)
	{
		string sessionData = Session::GetValue(uid, SESSION_DATA);
		error_log("[get_session_fail][ret=%d,uid=%u,openid=%s,openkey=%s]",
				ret, uid, openid.c_str(), openkey.c_str());
		return ret;
	}
	return 0;
}

#define VERIFY_LOGIN_TIMES	30
#define VERIFY_LOGIN_REDUCE	10
#define VERIFY_ONLINE_TIME	(12*3600)
#define VERIFY_ONLINE_REDUCE	(2*3600)
#define FCM_ONLINE_TIME_LIMIT	(16*3600)

#define ERROR_NEED_VERIFY	1
#define ERROR_FCM_TIMEOUT	2

int LogicSso::Verify(unsigned uid, bool login, bool verified)
{
	Json::Value userExtraData;
	int ret = LogicUser::GetExtraData(uid, userExtraData);
	if(ret != 0)
	{
		return ret;
	}
	unsigned lvt = 0;
	Json::GetUInt(userExtraData, "lvt", lvt);
	if(!Time::IsToday(lvt))
	{
		userExtraData["lgs"] = 1u;
		userExtraData["otm"] = 0u;
		userExtraData["totm"] = 0u;
		userExtraData["lvt"] = Time::GetGlobalTime();
		ret = LogicUser::SetExtraData(uid, userExtraData);
		if (ret != 0)
		{
			return ret;
		}
		return 0;
	}
	bool modify = true;
	unsigned otm = 0;
	unsigned lgs = 0;
	unsigned totm = 0;
	Json::GetUInt(userExtraData, "otm", otm);
	Json::GetUInt(userExtraData, "lgs", lgs);
	Json::GetUInt(userExtraData, "totm", totm);
	int onlineTime = Time::GetGlobalTime() - lvt;
	if(onlineTime < 10 && !login && !verified)
	{
		modify = false;
	}
	if(onlineTime < 0 || onlineTime > ONLINE_TIMEOUT)
	{
		onlineTime = 0;
	}
	otm += onlineTime;
	totm += onlineTime;
	if(login)
	{
		lgs++;
	}
	if(verified)
	{
		if(otm > VERIFY_ONLINE_TIME - VERIFY_ONLINE_REDUCE)
		{
			otm = VERIFY_ONLINE_TIME - VERIFY_ONLINE_REDUCE;
		}
		if(lgs > VERIFY_LOGIN_TIMES - VERIFY_LOGIN_REDUCE)
		{
			lgs = VERIFY_LOGIN_TIMES - VERIFY_LOGIN_REDUCE;
		}
	}
	userExtraData["lgs"] = lgs;
	userExtraData["otm"] = otm;
	userExtraData["totm"] = totm;
	userExtraData["lvt"] = Time::GetGlobalTime();
	if(modify)
	{
		ret = LogicUser::SetExtraData(uid, userExtraData);
		if (ret != 0)
		{
			return ret;
		}
	}
	if(totm > FCM_ONLINE_TIME_LIMIT)
	{
		ERROR_RETURN_MSG(ERROR_FCM_TIMEOUT, "fcm_timeout");
	}
	if(lgs > VERIFY_LOGIN_TIMES || otm > VERIFY_ONLINE_TIME)
	{
		ERROR_RETURN_MSG(ERROR_NEED_VERIFY, "needverify");
	}
	return 0;
}

