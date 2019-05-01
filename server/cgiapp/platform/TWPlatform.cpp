#include "TWPlatform.h"
#include "Common.h"

//获取平台信息
#define URL_TW_GET_PF_USER_INFO "https://www.goodogames.com/Change/TGIDToUID/%s" 
//获取用户在台湾乐谷平台上创建的角色信息
#define URL_TW_GET_CHARACTER_INFO "https://www.goodogames.com/Change/CharacterInfo/%s/BSG/%u"
//将FB openid转为TGID
#define URL_TW_GET_TGID "https://www.goodogames.com/Change/UIDToTGID/%s"

#define URL_FB_FIGURE "http://graph.facebook.com/%s/picture"
#define URL_FB_GET_OTHER_USER_INFO "https://graph.facebook.com/%s?access_token=%s"
#define URL_FB_FQL_QUERY "https://graph.facebook.com/fql?q=%s&access_token=%s&format=json"
#define FQL_GET_APP_FRIENDS "SELECT%%20uid%%20FROM%%20user%%20WHERE%%20uid%%20IN%%20(SELECT%%20uid2%%20FROM%%20friend%%20WHERE%%20uid1=me())%%20AND%%20is_app_user"

CTWPlatform::CTWPlatform()
{
}

CTWPlatform::~CTWPlatform()
{
}

int CTWPlatform::Initialize(const string &appid, const string &appkey, map<string, string> &params)
{
	IOpenPlatform::Initialize(appid, appkey, params);
	return 0;
}

int CTWPlatform::GetUserInfo(OPUserInfo &userInfo, const string &openid, const string &openkey)
{
    //openid为TGID
    //如果为FB账号登入, 则openkey为serverid&fbtoken; 否则openkey为serverid

	string url;
	string response;
	String::Format(url, URL_TW_GET_CHARACTER_INFO, openid.c_str(), atoi(openkey.c_str()));
	if(!Network::HttpGetRequest(response, url))
	{
		m_errorMessage = response;
		error_log("[http request fail][reason=HttpGetRequest,openid=%s,errmsg=%s]",
				openid.c_str(), m_errorMessage.c_str());
		return -1;
	}

	Json::Value jsonUserInfo;
	Json::Reader reader;
	if(!reader.parse(response, jsonUserInfo))
	{
		m_errorMessage = "json_parse_fail";
		error_log("[response parse fail][reason=JsonParse,openid=%s,errmsg=%s,response=%s]",
				openid.c_str(), m_errorMessage.c_str(), response.c_str());
		return -1;
	}
	if(!jsonUserInfo.isMember("charactername"))
	{
		m_errorMessage = "query_fail";
		error_log("[data error][reason=QueryFail,openid=%s,errmsg=%s,response=%s]",
				openid.c_str(), m_errorMessage.c_str(), response.c_str());
		return -1;
	}

	userInfo.Clear();
	userInfo.OpenId = openid;
	userInfo.Name = jsonUserInfo["charactername"].asString();
	userInfo.Name = jsonUserInfo["charactername"].asString();
	userInfo.FigureUrl = jsonUserInfo["head_pic"].asString();

    userInfo.Gender = GD_UNKNOW;
	string sGender = jsonUserInfo["gender"].asString();
	if(sGender == "Male")
		userInfo.Gender = GD_MALE;
	if(sGender == "Female")
		userInfo.Gender = GD_FEMALE;


	return 0;
}

/*
int CTWPlatform::GetOtherUserInfo(OPUserInfo userInfo, const string &queryOpenId, const string &openid, const string &openkey)
{
	string url;
	string response;
	String::Format(url, URL_FB_GET_OTHER_USER_INFO, queryOpenId.c_str(), openkey.c_str());
	if(!Network::HttpGetRequest(response, url))
	{
		m_errorMessage = response;
		error_log("[http request fail][reason=HttpGetRequest,openid=%s,errmsg=%s]",
				queryOpenId.c_str(), m_errorMessage.c_str());
		return -1;
	}
	Json::Value jsonUserInfo;
	Json::Reader reader;
	if(!reader.parse(response, jsonUserInfo))
	{
		m_errorMessage = "json_parse_fail";
		error_log("[json parse fail][reason=JsonParse,openid=%s,errmsg=%s,response=%s]",
				queryOpenId.c_str(), m_errorMessage.c_str(), response.c_str());
		return -1;
	}
	if(!jsonUserInfo.isMember("id"))
	{
		m_errorMessage = "query_fail";
		error_log("[data error][reason=QueryFail,openid=%s,errmsg=%s,response=%s]",
				queryOpenId.c_str(), m_errorMessage.c_str(), response.c_str());
		return -1;
	}

	userInfo.Clear();
	userInfo.OpenId = jsonUserInfo["id"].asString();
	userInfo.Name = jsonUserInfo["name"].asString();
	string sGender = jsonUserInfo["gender"].asString();
	if(sGender == "male")
	{
		userInfo.Gender = GD_MALE;
	}
	else if(sGender == "female")
	{
		userInfo.Gender = GD_FEMALE;
	}
	else
	{
		userInfo.Gender = GD_UNKNOW;
	}
	String::Format(userInfo.FigureUrl, URL_FB_FIGURE, userInfo.OpenId.c_str());
	string locale = jsonUserInfo["locale"].asString();
	userInfo.Nation = locale;
	if(locale.size() == 5)
	{
		if(locale[2] == '_')
		{
			userInfo.Nation = locale.substr(3, 2);
		}
	}

	return 0;
}
*/

int CTWPlatform::GetAppFriendList(OPFriendList &friendList, const string &openid, const string &_openkey)
{
    //openid为TGID
    //如果为FB账号登入, 则openkey为serverid&fbtoken; 否则openkey为serverid
    
    if (_openkey.find("&") == string::npos) //不是FB的账号
        return 0;

    string openkey = _openkey;
    openkey.erase(0, _openkey.find("&") + strlen("&"));

	//获取FB好友
	string url;
	String::Format(url, URL_FB_FQL_QUERY, FQL_GET_APP_FRIENDS, openkey.c_str());
	string response;
	if(!Network::HttpGetRequest(response, url))
	{
		m_errorMessage = response;
		error_log("[http request fail][reason=HttpGetRequest,openid=%s,errmsg=%s]",
				openid.c_str(), m_errorMessage.c_str());
		return -1;
	}

	Json::Value friends;
	Json::Reader reader;
	if(!reader.parse(response, friends))
	{
		m_errorMessage = "json_parse_fail";
		error_log("[json parse fail][reason=JsonParse,openid=%s,errmsg=%s,response=%s,url=%s]",
				openid.c_str(), m_errorMessage.c_str(), response.c_str(), url.c_str());
		return -1;
	}

	friendList.clear();
	size_t size = friends["data"].size();
	for (size_t i = 0; i < size; i++)
	{
		//friendList.push_back(friends["data"][i]["uid"].asString());
		
		//根据FB好友openid获得TGID
        string url;
        string response;
        String::Format(url, URL_TW_GET_TGID, friends["data"][i]["uid"].asString().c_str());
        if(!Network::HttpGetRequest(response, url))
        {
            m_errorMessage = "get tgid failed";
            error_log("[http request fail][reason=HttpGetRequest,openid=%s,errmsg=%s]",
                    friends["data"][i]["uid"].asString().c_str(), m_errorMessage.c_str());
            return -1;
        }

        Json::Value jsonUserInfo;
        Json::Reader reader;
        if(!reader.parse(response, jsonUserInfo))
        {
            m_errorMessage = "json_parse_fail";
            error_log("[response parse fail][reason=JsonParse,openid=%s,errmsg=%s,response=%s]",
                    friends["data"][i]["uid"].asString().c_str(), m_errorMessage.c_str(), response.c_str());
            return -1;
        }
        if(!jsonUserInfo.isMember("tgid"))
        {
            m_errorMessage = "query_fail";
            error_log("[data error][reason=QueryFail,openid=%s,errmsg=%s,response=%s]",
                    friends["data"][i]["uid"].asString().c_str(), m_errorMessage.c_str(), response.c_str());
            return -1;
        }

		friendList.push_back(jsonUserInfo["tgid"].asString());
	}

	return 0;
}

string CTWPlatform::GetErrorMessage()
{
	return m_errorMessage;
}

void CTWPlatform::ReplyCharge()
{
	CgiUtil::PrintText("{\"ret\":0,\"msg\":\"OK\"}");
}
