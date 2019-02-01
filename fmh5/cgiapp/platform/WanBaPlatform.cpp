#include "WanBaPlatform.h"
#include <iostream>

WanBaPlatform::WanBaPlatform()
{
}

int WanBaPlatform::Initialize(const string &appid, const string &appkey, map<string, string> &params)
{
	IOpenPlatform::Initialize(appid, appkey, params);
	SetPlatformType(PT_WB);
	return 0;
}

void WanBaPlatform::SetParameter(const map<string, string> &params)
{
	m_pf.clear();
	m_userip.clear();
	map<string, string>::const_iterator it = params.find("pf");
	if (it != params.end())
		m_pf = it->second;
	it = params.find("userip");
	if (it != params.end())
		m_userip = it->second;
}

int WanBaPlatform::GetUserInfo(OPUserInfo &userInfo, const string &openid, const string &openkey)
{
	const string api = "/v3/user/get_info";
	map<string,string> params;
	params["appid"] = m_appId;
	params["format"] = "json";
	params["openid"] = openid;
	params["openkey"] = openkey;
	params["pf"] = m_pf;
	params["userip"] = m_userip;
	string qstr;
	GetSig(params, m_appKey, true, api, qstr);
	string url = "http://" + m_config["v3domain"] + api + "?" + qstr;

	string response;
	if (!Network::HttpGetRequest(response, url) || response.empty())
	{
		error_log("[http request fail][openid=%s,openkey=%s,errmsg=%s,url=%s]",
				openid.c_str(), openkey.c_str(), response.c_str(), url.c_str());
		return -1;
	}
	Json::Value value;
	if (!Json::Reader().parse(response, value))
	{
		error_log("[json parse fail][openid=%s,openkey=%s,response=%s,url=%s]",
				openid.c_str(), openkey.c_str(), response.c_str(), url.c_str());
		return -1;
	}
	int ret = 0;
	if (!Json::GetInt(value, "ret", ret) || ret != 0)
	{
		error_log("[get_info fail][openid=%s,openkey=%s,msg=%s,url=%s]",
				openid.c_str(), openkey.c_str(), response.c_str(), url.c_str());
		return -1;
	}
	userInfo.Clear();
	userInfo.OpenId = openid;
	Json::GetString(value, "nickname", userInfo.Name);
	Json::GetString(value, "figureurl", userInfo.FigureUrl);
	size_t httppos = userInfo.FigureUrl.find("http://");
	if (httppos != 0)
	{
		userInfo.FigureUrl = "https://" + userInfo.FigureUrl;
	}
	else
	{
		userInfo.FigureUrl = "https://" + userInfo.FigureUrl.substr(httppos + strlen("http://"));
	}
	string temp;
	Json::GetString(value, "gender", temp);
	if (temp == "男")
	{
		userInfo.Gender = GD_MALE;
	}
	else if (temp == "女")
	{
		userInfo.Gender = GD_FEMALE;
	}
	else
	{
		userInfo.Gender = GD_UNKNOW;
	}
	Json::GetString(value, "country", userInfo.Nation);
	Json::GetString(value, "province", userInfo.Province);
	Json::GetString(value, "city", userInfo.City);
	int is_yellow_vip = 0;
	int is_yellow_year_vip = 0;
	int yellow_vip_level = 0;
	Json::GetInt(value, "is_yellow_vip", is_yellow_vip);
	Json::GetInt(value, "is_yellow_year_vip", is_yellow_year_vip);
	Json::GetInt(value, "yellow_vip_level", yellow_vip_level);
	userInfo.ExtraIntInfo["bIsVip"] = is_yellow_vip == 1 ? 1 : 0;
	userInfo.ExtraIntInfo["bIsYearVip"] = is_yellow_year_vip == 1 ? 1 : 0;
	userInfo.ExtraIntInfo["nVipLevel"] = yellow_vip_level;

	debug_log("openid=%s,response=%s", openid.c_str(), Json::ToString(value).c_str());

	return 0;
}

int WanBaPlatform::GetBlueVipInfo(OPUserInfo &userInfo, const string &openid, const string &openkey)
{
	const string api = "/v3/user/blue_vip_info";
	map<string,string> params;
	params["appid"] = m_appId;
	params["format"] = "json";
	params["openid"] = openid;
	params["openkey"] = openkey;
	params["pf"] = m_pf;
	params["userip"] = m_userip;
	string qstr;
	GetSig(params, m_appKey, true, api, qstr);
	string url = "http://" + m_config["v3domain"] + api + "?" + qstr;

	string response;
	if (!Network::HttpGetRequest(response, url) || response.empty())
	{
		error_log("[http request fail][openid=%s,openkey=%s,errmsg=%s,url=%s]",
				openid.c_str(), openkey.c_str(), response.c_str(), url.c_str());
		return -1;
	}
	Json::Value value;
	if (!Json::Reader().parse(response, value))
	{
		error_log("[json parse fail][openid=%s,openkey=%s,response=%s,url=%s]",
				openid.c_str(), openkey.c_str(), response.c_str(), url.c_str());
		return -1;
	}
	int ret;
	if (!Json::GetInt(value, "ret", ret) || ret != 0)
	{
		error_log("[get_info fail][openid=%s,openkey=%s,msg=%s,url=%s]",
				openid.c_str(), openkey.c_str(), response.c_str(), url.c_str());
		return -1;
	}
	userInfo.Clear();
	userInfo.OpenId = openid;
	vector<string> needField;
	needField.push_back("is_blue_vip");
	needField.push_back("is_blue_year_vip");
	needField.push_back("is_super_blue_vip");
	needField.push_back("blue_vip_level");
	needField.push_back("vip_valid_time");
	needField.push_back("year_vip_valid_time");
	needField.push_back("super_vip_valid_time");
	for (vector<string>::iterator iter = needField.begin(); iter != needField.end(); ++iter)
	{
		const string& field = *iter;
		Json::GetInt(value, field.c_str(), userInfo.ExtraIntInfo[field]);
	}

	return 0;
}
int WanBaPlatform::WordFilter(uint32_t uid, const string &name, const string &openid, const string &openkey)
{
	string errorMessage;

	uint32_t timer = time(NULL);
	static uint32_t temp = 0;
	string msgid = CTrans::UTOS(timer) + CTrans::UTOS(temp++);

	string url = "http://" + m_config["v3domain"] + "/v3/csec/word_filter?";
	string osig = "GET&" + Crypt::UrlEncodeForTX("/v3/csec/word_filter") + "&";
	string qsig = "appid=" + m_appId + "&content=" + name + "&format=json&msgid=" + msgid + "&openid=" + openid + "&openkey=" + openkey + "&pf=" + m_pf;
	string qstr = "appid=" + Crypt::UrlEncodeForTX(m_appId) + "&content=" + Crypt::UrlEncodeForTX(name) + "&format=json&msgid=" + Crypt::UrlEncodeForTX(msgid) + "&openid=" + Crypt::UrlEncodeForTX(openid) + "&openkey=" + Crypt::UrlEncodeForTX(openkey) + "&pf=" + Crypt::UrlEncodeForTX(m_pf);
	osig += Crypt::UrlEncodeForTX(qsig);
	string key = m_appKey + "&";
	string bsig = Crypt::HmacSha1(osig, key);
	string sig;
	Crypt::Base64Encode(sig, bsig);
	url += qstr + "&sig=" + Crypt::UrlEncodeForTX(sig);
//	url += qsig + "&sig=" + sig;

	string response;
	if (!Network::HttpGetRequest(response, url) || response.empty())
	{
		errorMessage = response;
		error_log("[http request fail][openid=%s,openkey=%s,errmsg=%s,url=%s]", openid.c_str(), openkey.c_str(), errorMessage.c_str(), url.c_str());
		return -1;
	}
	Json::Value value;
	if (!Json::Reader().parse(response, value))
	{
		errorMessage = "json_parse_fail";
		error_log("[json parse fail][openid=%s,openkey=%s,response=%s,url=%s]", openid.c_str(), openkey.c_str(), response.c_str(), url.c_str());
		return -1;
	}

	int ret = -1;
	if (!Json::GetInt(value, "ret", ret) || ret != 0)
	{
		Json::GetString(value, "msg", errorMessage);
		error_log("[get_info fail][openid=%s,openkey=%s,msg=%s,url=%s]", openid.c_str(), openkey.c_str(), errorMessage.c_str(), url.c_str());
		return -1;
	}
	if (!Json::GetInt(value, "is_dirty", ret) || ret != 0)
	{
		Json::GetString(value, "msg", errorMessage);
		error_log("[get_info fail][openid=%s,openkey=%s,msg=%s,url=%s]", openid.c_str(), openkey.c_str(), errorMessage.c_str(), url.c_str());
		return -1;
	}

	return ret;
}

int WanBaPlatform::GetAppFriendList(OPFriendList &friendList, const string &openid, const string &openkey)
{
	const string api = "/v3/relation/get_app_friends";
	map<string,string> params;
	params["appid"] = m_appId;
	params["format"] = "json";
	params["openid"] = openid;
	params["openkey"] = openkey;
	params["pf"] = m_pf;
	params["userip"] = m_userip;
	string qstr;
	GetSig(params, m_appKey, true, api, qstr);
	string url = "http://" + m_config["v3domain"] + api + "?" + qstr;

	string response;
	if (!Network::HttpGetRequest(response, url) || response.empty())
	{
		error_log("[http request fail][openid=%s,openkey=%s,errmsg=%s]",
				openid.c_str(), openkey.c_str(), response.c_str());
		return -1;
	}
	Json::Value value;
	if (!Json::Reader().parse(response, value))
	{
		error_log("[json parse fail][openid=%s,openkey=%s,response=%s]",
				openid.c_str(), openkey.c_str(), response.c_str());
		return -1;
	}
	int ret;
	if (!Json::GetInt(value, "ret", ret) || ret != 0)
	{
		error_log("[get_info fail][openid=%s,openkey=%s,msg=%s]",
				openid.c_str(), openkey.c_str(), response.c_str());
		return -1;
	}
	if (Json::IsArray(value, "items"))
	{
		for (unsigned i = 0; i < value["items"].size(); i++)
		{
			string temp;
			if (Json::GetString(value["items"][i], "openid", temp))
			{
				friendList.push_back(temp);
			}
		}
	}
	info_log("response=%s", Json::ToString(value).c_str());
	return 0;
}
string WanBaPlatform::GetErrorMessage()
{
	return "no error message";
}

string WanBaPlatform::GetSig(const map<string, string> &params, const string &appkey, bool get, const string &uri, string &qstr)
{
	string sig;
	string qsig;
	qstr.clear();
	map<string, string>::const_iterator it = params.begin();
	for (; it != params.end(); it++)
	{
		if (!qsig.empty())
		{
			qsig += "&";
		}
		if (!qstr.empty())
		{
			qstr += "&";
		}
		qsig += it->first + "=" + it->second;
		qstr += it->first + "=" + Crypt::UrlEncodeForTX(it->second);
	}
	string osig = (get ? "GET&" : "POST&") + Crypt::UrlEncodeForTX(uri) + "&" + Crypt::UrlEncodeForTX(qsig);
	string key = appkey + "&";
	string bsig = Crypt::HmacSha1(osig, key);
	Crypt::Base64Encode(sig, bsig);
	qstr += "&sig=" + Crypt::UrlEncodeForTX(sig);

	return sig;
}
int WanBaPlatform::formatUrl(const map<string, string> &param,
		const string &appkey,
		const string &api,
		string &url,
		string domain)
{
	string qsig;
	string qstr;
	map<string, string>::const_iterator itr = param.begin();
	for (; itr != param.end(); ++itr)
	{
		if (!qsig.empty())
		{
			qsig.append("&").append(itr->first).append("=").append(itr->second);
			qstr.append("&").append(itr->first).append("=").append(Crypt::UrlEncodeForTX(itr->second));
		}
		else
		{
			qsig.append(itr->first).append("=").append(itr->second);
			qstr.append(itr->first).append("=").append(Crypt::UrlEncodeForTX(itr->second));
		}
	}
	url = "https://" + domain + api + "?";
	string osig = "GET&" + Crypt::UrlEncodeForTX(api) + "&" + Crypt::UrlEncodeForTX(qsig);
	string key = appkey + "&";
	string bsig = Crypt::HmacSha1(osig, key);
	string sig;
	Crypt::Base64Encode(sig, bsig);
	url += qstr + "&sig=" + Crypt::UrlEncodeForTX(sig);
	return 0;
}

int WanBaPlatform::Is_Login(const string &openid, const string &openkey, const string &pf)
{
	const string api = "/v3/user/is_login";
	map<string,string> param;
	param["appid"] = m_appId;
	param["format"] = "json";
	param["openid"] = openid;
	param["openkey"] = openkey;
	param["pf"] = m_pf;
	param["userip"] = m_userip;
	string qstr;
	GetSig(param, m_appKey, true, api, qstr);
	string url = "http://" + m_config["v3domain"] + api + "?" + qstr;

	string response;
	if (!Network::HttpGetRequest(response, url) || response.empty())
	{
		error_log("[http request fail][openid=%s,openkey=%s,errmsg=%s]",
				openid.c_str(), openkey.c_str(), response.c_str());
		return -1;
	}
	Json::Value value;
	if (!Json::Reader().parse(response, value))
	{
		error_log("[json parse fail][openid=%s,openkey=%s,response=%s]",
				openid.c_str(), openkey.c_str(), response.c_str());
		return -1;
	}
	int ret;
	if (!Json::GetInt(value, "ret", ret) || ret != 0)
	{
		error_log("[get_info fail][openid=%s,openkey=%s,response=%s]",
				openid.c_str(), openkey.c_str(), response.c_str());
		return -1;
	}
	return 0;
}
