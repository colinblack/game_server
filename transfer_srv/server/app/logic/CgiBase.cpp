/*
 * CgiBase.cpp
 *
 *  Created on: 2011-5-26
 *      Author: dada
 */

#include "CgiBase.h"
#include "fcgi_stdio.h"

#define CLIENT_KEY "z1hcdgiV4e5BwUKa9IT3EM8CpqnPufob"
#define SERVER_KEY "QDneu1n5z2f491o4kiClIT35EgQDneuX"

CCgiBase::CCgiBase(const string &cgiName)
{
	m_cgiName = cgiName;
	memset(m_features, 0, sizeof(m_features));
}

CCgiBase::~CCgiBase()
{
}

int CCgiBase::Run()
{
	unsigned lastLogTime = 0;
	while(FCGI_Accept() >= 0)
	{
		unsigned startMTime;
		mtime(startMTime);

		RECV_LOG(m_cgiName.c_str(), CCGIIn::GetStrRemoteIP(), "%s", getenv("QUERY_STRING"));
		int result = Initialize();
		if(0 != result)
		{
			error_log("[cgi initialize fail][cgi=%s,uid=%u,ret=%d]", m_cgiName.c_str(), m_uid, result);
			if(result != GetError())
			{
				SetError(result);
			}
			PrintResult(result);
			CGI_SEND_LOG("action=%s&uid=%d&error=%d&errmsg=%s&reason=Initialize",
					m_actionName.c_str(), m_uid, result, GetErrorMessage());
		}
		else
		{
			result = Process();
			if(result != 0)
			{
				if(result != GetError())
				{
					SetError(result);
				}
				CGI_SEND_LOG("action=%s&uid=%u&error=%d&errmsg=%s",
						m_actionName.c_str(), m_uid, result, GetErrorMessage());
			}
			PrintResult(result);

			//每10分钟记录一次指令的执行时间
			if(startMTime - lastLogTime >= 600000)
			{
				unsigned endMTime;
				mtime(endMTime);
				lastLogTime = startMTime;
				info_log("[exec time][cgi=%s,action=%s,retcode=%d,time=%u]",
						m_cgiName.c_str(), m_actionName.c_str(), result, endMTime - startMTime);
			}
		}
	}
	return 0;
}

int CCgiBase::RunOnce()
{
	static unsigned s_lastLogTime = 0;
	unsigned startMTime;
	mtime(startMTime);
	RECV_LOG(m_cgiName.c_str(), CCGIIn::GetStrRemoteIP(), "%s", getenv("QUERY_STRING"));
	int result = Initialize();
	if(0 != result)
	{
		error_log("[cgi initialize fail][cgi=%s,uid=%u,ret=%d]", m_cgiName.c_str(), m_uid, result);
		if(result != GetError())
		{
			SetError(result);
		}
		PrintResult(result);
		CGI_SEND_LOG("action=%s&uid=%d&error=%d&errmsg=%s&reason=Initialize",
				m_actionName.c_str(), m_uid, result, GetErrorMessage());
	}
	else
	{
		result = Process();
		if(result != 0)
		{
			if(result != GetError())
			{
				SetError(result);
			}
			CGI_SEND_LOG("action=%s&uid=%u&error=%d&errmsg=%s",
					m_actionName.c_str(), m_uid, result, GetErrorMessage());
		}
		PrintResult(result);

		//每10分钟记录一次指令的执行时间
		if(startMTime - s_lastLogTime >= 600000)
		{
			unsigned endMTime;
			mtime(endMTime);
			s_lastLogTime = startMTime;
			info_log("[exec time][cgi=%s,action=%s,retcode=%d,time=%u]",
					m_cgiName.c_str(), m_actionName.c_str(), result, endMTime - startMTime);
		}
	}
	return result;
}

string CCgiBase::GetCgiName()
{
	return m_cgiName;
}

void CCgiBase::SetFeature(int feature)
{
	m_features[feature] = 1;
}

int CCgiBase::Initialize()
{
	//Reset
	int ret;
	STATICDATA::m_iCGIValueState = 0;
	STATICDATA::m_iCookieState = 0;
	Time::UpdateGlobalTime();
	m_uid = 0;
	m_skey.clear();
	m_remoteip = 0;
	m_ipstr.clear();
	m_actionName.clear();
	m_strData.clear();
	m_data = Json::Value();
	m_jsonResult = Json::Value();
	ResetError();

	if(m_features[CF_CHECK_PLATFORM])
	{
		if(!OpenPlatform::Reset())
		{
			return R_ERR_PLATFORM;
		}
	}

//	//设置语言类型
//	std::string sLang = CCookie::GetCookie("lang");
//	if (!sLang.empty())
//	{
//		CStr4I::SetLang(atoi(sLang.c_str()));
//	}
//	else
//	{
//		CStr4I::SetLang(CStr4I::LANG_CN_SIMPLE);
//	}

	//checks
#define CGI_CHECK(feature, function)	\
	if(m_features[feature])	\
	{	\
		ret = function();	\
		if(ret != 0)	\
		{	\
			return ret;	\
		}	\
	}	\

	CGI_CHECK(CF_GET_REMOTE_IP, GetRemoteIp);
	CGI_CHECK(CF_GET_UID, GetUid);
	CGI_CHECK(CF_CHECK_SESSION, CheckSession);
	CGI_CHECK(CF_CHECK_TIME, CheckTime);
	CGI_CHECK(CF_DECRYPT_DATA, DecryptData);
	CGI_CHECK(CF_CHECK_HASH, CheckHash);
	CGI_CHECK(CF_PARSE_DATA, ParseData);

	return 0;
}

int CCgiBase::GetRemoteIp()
{
	m_remoteip = CCGIIn::GetRemoteIP();
	struct in_addr addr;
	addr.s_addr = htonl(m_remoteip);
	m_ipstr = inet_ntoa(addr);
	return 0;
}

int CCgiBase::GetUid()
{
	int uid = CCGIIn::GetCGIInt("uid");
	if( uid == CCGIIn::CGI_INT_ERR )
	{
		error_log("[get uid fail][uid=%d]",uid);
		return R_ERR_PARAM;
	}
	m_uid = uid;

	if(!IsValidUid(m_uid))
	{
		error_log("[invalid uid][uid=%d]", m_uid);
		return R_ERR_PARAM;
	}

	return 0;
}

int CCgiBase::CheckSession()
{
	if(!IsValidUid(m_uid))
	{
		PARAM_ERROR_RETURN();
	}
	string skey = CCGIIn::GetCGIStr("skey");
	if(!LogicSso::IsLogin(m_uid, skey))
	{
		ERROR_RETURN(R_ERR_SESSION);
	}

//	if(!IsValidUid(m_uid))
//	{
//		return R_ERR_PARAM;
//	}
//	string skey = CCGIIn::GetCGIStr("skey");
//	string sessionData = Session::GetValue(m_uid, SESSION_DATA);
//	if( skey.empty() || sessionData.empty() )
//	{
//		error_log("[key is empty][uid=%d,skey=%s,session_data=%s]", m_uid,skey.c_str(),sessionData.c_str());
//		return R_ERR_SESSION;
//	}
//
//	Json::Value value;
//	Json::Reader reader;
//	if( !reader.parse( sessionData, value ) )
//	{
//		error_log("[session data parse error][uid=%d,session_data=%s]",m_uid,sessionData.c_str());
//		Session::RemoveSession(m_uid);
//		return R_ERR_SESSION;
//	}
//
//	unsigned lastVisitTime = value.get("lvt", 0).asUInt();
//	if( (Time::GetGlobalTime() - lastVisitTime) > SESSION_TIME_OUT )
//	{
//		Session::RemoveSession(m_uid);
//		error_log("[session overtime][uid=%d,time=%u,last_visit_time=%d]", m_uid, Time::GetGlobalTime(), lastVisitTime);
//		return R_ERR_SESSION;
//	}
//	string realKey = value["skey"].asString();
//	if( realKey != skey )
//	{
//		error_log("[session key error][uid=%d,skey=%s,real_skey=%s]", m_uid,skey.c_str(),realKey.c_str());
//		return R_ERR_SESSION;
//	}
//	int platformType = value["pt"].asInt();
//	if(platformType != OpenPlatform::GetType())
//	{
//		error_log("[session platform error][uid=%d,platform=%s,real_platfrom=%s]", m_uid, OpenPlatform::GetType(), platformType);
//		return R_ERR_SESSION;
//	}
//	//unsigned remoteip = value.get("rip", 0).asUInt();
//
//	value["lvt"] = Time::GetGlobalTime();
//	Json::FastWriter writer;
//	sessionData = writer.write(value);
//	Session::SetValue(m_uid, SESSION_DATA, sessionData);
	m_skey = skey;
	return 0;
}

int CCgiBase::CheckTime()
{
	int ts = CCGIIn::GetCGIInt("ts");
	if( ts == CCGIIn::CGI_INT_ERR )
	{
		return R_ERR_PARAM;
	}
	int delta = ts - Time::GetGlobalTime();
	if(delta > 20)	//暂不处理时间落后
	{
		error_log("[check_time_error][cgi=%s,uid=%u,ts=%u,st=%u,delta=%d]", m_cgiName.c_str(), m_uid, ts, Time::GetGlobalTime(), delta);
		return R_ERR_PARAM;
	}
	if(delta < -30)
	{
		info_log("[check_time_error][cgi=%s,uid=%u,ts=%u,st=%u,delta=%d]", m_cgiName.c_str(), m_uid, ts, Time::GetGlobalTime(), delta);
	}
	return 0;
}

int CCgiBase::DecryptData()
{
	string data = CCGIIn::GetCGIStr("data");
	if(data.empty())
	{
		error_log("[decrypt_data_param_error][cgi=%s,uid=%u,data=empty]", m_cgiName.c_str(), m_uid);
		return R_ERR_PARAM;
	}
	if(Config::GetIntValue("unsafe") == 1)
	{
		m_strData = data;
		return 0;
	}
	string hn = CCGIIn::GetCGIStr("hn");
	if(hn.empty())
	{
		error_log("[decrypt_data_param_error][cgi=%s,uid=%u,hn=%s]", m_cgiName.c_str(), m_uid, hn.c_str());
		return R_ERR_PARAM;
	}
	string key = hn + m_skey + OpenPlatform::GetPlatform()->GetConfig(CONFIG_CLIENT_DOMAIN) + CLIENT_KEY;
	if(!Crypt::DawxDecode(m_strData, data, key))
	{
		error_log("[decrypt_data_error][cgi=%s,uid=%u,skey=%s,hn=%s,datasize=%u]",
				m_cgiName.c_str(), m_uid, m_skey.c_str(), hn.c_str(), (unsigned)data.size());
		return R_ERR_PARAM;
	}
	return 0;
}

int CCgiBase::CheckHash()
{
	if(!m_features[CF_DECRYPT_DATA])
	{
		m_strData = CCGIIn::GetCGIStr("data");
	}
	if(Config::GetIntValue("unsafe") == 1)
	{
		return 0;
	}
	string hn = CCGIIn::GetCGIStr("hn");
	string h = CCGIIn::GetCGIStr("h");
	if(h.empty() || hn.empty())
	{
		error_log("[check_key_param_error][cgi=%s,uid=%u,hn=%s,h=%s]", m_cgiName.c_str(), m_uid, hn.c_str(), h.c_str());
		return R_ERR_PARAM;
	}
	if(m_strData.empty())
	{
		error_log("[check_key_param_error][cgi=%s,uid=%u,data=empty]", m_cgiName.c_str(), m_uid);
		return R_ERR_PARAM;
	}
	string key = GetHash(m_strData, hn);
	if(!String::EqualNoCase(key, h))
	{
		error_log("[check_key_error][cgi=%s,uid=%u,skey=%s,hn=%s,h=%s,key=%s,textsize=%u]",
				m_cgiName.c_str(), m_uid, m_skey.c_str(), hn.c_str(), h.c_str(), key.c_str(), (unsigned)m_strData.size());
		return R_ERR_PARAM;
	}
	return 0;
}

int CCgiBase::ParseData()
{
	if(!m_features[CF_DECRYPT_DATA] && !m_features[CF_CHECK_HASH])
	{
		m_strData = CCGIIn::GetCGIStr("data");
	}
	if(!Json::Reader().parse(m_strData, m_data))
	{
		error_log("[param_parse_error][cgi=%s,uid=%u,param=data]", m_cgiName.c_str(), m_uid);
		return R_ERR_PARAM;
	}
	if(m_data.type() != Json::objectValue)
	{
		error_log("[param_type_error][cgi=%s,uid=%u,param=data]", m_cgiName.c_str(), m_uid);
		return R_ERR_PARAM;
	}
	if(m_features[CF_CHECK_TIME])
	{
		unsigned ts = CCGIIn::GetCGIInt("ts");
		unsigned dataTs;
		if(!Json::GetUInt(m_data, "ts", dataTs))
		{
			error_log("[data_miss_ts][cgi=%s,uid=%u,param=data.ts]", m_cgiName.c_str(), m_uid);
			return R_ERR_PARAM;
		}
		if(ts != dataTs)
		{
			error_log("[ts_not_equal][cgi=%s,uid=%u,ts=%u,data_ts=%u]", m_cgiName.c_str(), m_uid, ts, dataTs);
			return R_ERR_PARAM;
		}
	}
	if(m_features[CF_GET_UID])
	{
		unsigned uid;
		if(!Json::GetUInt(m_data, "uid", uid))
		{
			error_log("[data_miss_uid][cgi=%s,uid=%u,param=data.uid]", m_cgiName.c_str(), m_uid);
			return R_ERR_PARAM;
		}
		if(uid != m_uid)
		{
			error_log("[uid_not_equal][cgi=%s,uid=%u,data_uid=%u]", m_cgiName.c_str(), m_uid, uid);
			return R_ERR_PARAM;
		}
	}
	return 0;
}

void CCgiBase::PrintResult(int result)
{
	if(m_features[CF_PRINT_JSON])
	{
		//错误处理
		if(result == R_SUCCESS)
		{
			m_jsonResult[KEY_RESULT] = R_SUCCESS;
		}
		else
		{
			m_jsonResult[KEY_RESULT] = GetErrorMessage();
		}

		//清理h,hn
		if(m_jsonResult.isObject())
		{
			if(m_jsonResult.isMember("hn"))
			{
				m_jsonResult.removeMember("hn");
			}
			if(m_jsonResult.isMember("h"))
			{
				m_jsonResult.removeMember("h");
			}
		}
		string result = Json::FastWriter().write(m_jsonResult);
		if(m_features[CF_APPEND_HASH])
		{
			string hn = Convert::UInt64ToString(Math::GetRandomInt());
			string h = GetHash(result, hn);
			result.resize(result.size() - 1);
			string appendKey;
			String::Format(appendKey, ",\"hn\":\"%s\",\"h\":\"%s\"}", hn.c_str(), h.c_str());
			result.append(appendKey);
			if(m_features[CF_CRYPT_DATA] && Config::GetIntValue("unsafe") != 1)
			{
				string key = hn + m_skey + OpenPlatform::GetPlatform()->GetConfig(CONFIG_CLIENT_DOMAIN) + SERVER_KEY;
				string encodeResult;
				Crypt::DawxEncode(encodeResult, result, key);
				result = hn + "|" + encodeResult.c_str();
			}
		}
		if(m_features[CF_COMPRESS_OUT])
		{
			CgiUtil::CompressPrint(result);
		}
		else
		{
			CgiUtil::PrintText(result);
		}
	}
}

string CCgiBase::GetHash(const string &data, const string &hn)
{
	string h = Crypt::Md5Encode(data);
	string domain = OpenPlatform::GetPlatform()->GetConfig(CONFIG_CLIENT_DOMAIN);
	h.append(domain);
	h.append(m_skey);
	h.append(hn);
	h = Crypt::Md5Encode(h);
	return h;
}

int CCgiManager::Run()
{
	CCgiBase *pCgi = NULL;
	while(FCGI_Accept() >= 0)
	{
		const char *pRequestUri = getenv("REQUEST_URI");
		if(pRequestUri == NULL)
		{
			fatal_log("[REQUEST_URI is null][ip=%s]", CCGIIn::GetStrRemoteIP());
			RECV_LOG("<NULL>", CCGIIn::GetStrRemoteIP(), "%s", getenv("QUERY_STRING"));
			continue;
		}
		string requestUri = pRequestUri;
		size_t sItr = requestUri.find('?');
		if(sItr != string::npos)
		{
			requestUri = requestUri.substr(0, sItr);
		}

		bool find = false;
		if(pCgi != NULL)
		{
			if(requestUri.find(pCgi->GetCgiName()) != string::npos)
			{
				find = true;
			}
		}
		if(!find)
		{
			for(vector<CCgiBase *>::iterator itr = m_cgiList.begin(); itr != m_cgiList.end() && !find; itr++)
			{
				pCgi = *itr;
				if(pCgi != NULL)
				{
					if(requestUri.find(pCgi->GetCgiName()) != string::npos)
					{
						find = true;
					}
				}
			}
		}
		if(find)
		{
			pCgi->RunOnce();
		}
		else
		{
			pCgi = NULL;
			fatal_log("[unknow_cgi_name][request_uri=%s,ip=%s]", requestUri.c_str(), CCGIIn::GetStrRemoteIP());
			RECV_LOG(requestUri.c_str(), CCGIIn::GetStrRemoteIP(), "%s", getenv("QUERY_STRING"));
		}
	}
	return 0;
}

int CCgiManager::RegisterCgi(CCgiBase *pCgi)
{
	if(pCgi == NULL)
	{
		return R_ERR_PARAM;
	}
	m_cgiList.push_back(pCgi);
	return 0;
}
