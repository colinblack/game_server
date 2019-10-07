#include "LiMiPlatform.h"
#include <iostream>

LiMiPlatform::LiMiPlatform()
{
}

int LiMiPlatform::Initialize(const string &appid, const string &appkey, map<string, string> &params)
{
	IOpenPlatform::Initialize(appid, appkey, params);
	m_gameid = m_config["gameid"];
	return 0;
}

void LiMiPlatform::SetParameter(const map<string, string> &params)
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

int LiMiPlatform::GetUserInfo(OPUserInfo &userInfo, const string &openid, const string &openkey)
{
	/*const string api = "/openapi/apollo_verify_openid_openkey";
	map<string,string> params;
	params["appid"] = m_appId;
	params["gameid"] = m_gameid;
	params["openid"] = openid;
	params["openkey"] = openkey;
	params["ts"] = CTrans::UTOS(Time::GetGlobalTime());
	params["rnd"] = CTrans::UTOS(Math::GetRandomInt());
	string qstr;
	GetSig(params, m_appKey, false, api, qstr);
	string url = m_config["v3domain"] + api;
	string response;
	if (!Network::HttpPostRequest(response, url, qstr) || response.empty())
	{
		error_log("[http request fail][openid=%s,openkey=%s,errmsg=%s,url=%s,post=%s]",
				openid.c_str(), openkey.c_str(), response.c_str(), url.c_str(), qstr.c_str());
		return -1;
	}
	Json::Value value;
	if (!Json::Reader().parse(response, value))
	{
		error_log("[json parse fail][openid=%s,openkey=%s,response=%s,url=%s,post=%s]",
				openid.c_str(), openkey.c_str(), response.c_str(), url.c_str(), qstr.c_str());
		return -1;
	}
	int ret = 0;
	if (!Json::GetInt(value, "ret", ret) || ret != 0)
	{
		error_log("[get_info fail][openid=%s,openkey=%s,msg=%s,url=%s,post=%s]",
				openid.c_str(), openkey.c_str(), response.c_str(), url.c_str(), qstr.c_str());
		return -1;
	}*/

	if(openid.length() != 32)
	{
		error_log("[openid len][openid=%s]", openid.c_str());
		return -1;
	}
	userInfo.OpenId = openid;
	return 0;
}

int LiMiPlatform::formatUrl(const map<string, string> &param,
		const string &appkey,
		const string &api,
		string &url)
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
	string osig = "POST&" + Crypt::UrlEncodeForTX(api) + "&" + Crypt::UrlEncodeForTX(qsig);
	string key = appkey + "&";
	string bsig = Crypt::HmacSha1(osig, key);
	string sig;
	Crypt::Base64Encode(sig, bsig);
	url = qstr + "&sig=" + Crypt::UrlEncodeForTX(sig);
	return 0;
}

string LiMiPlatform::GetErrorMessage()
{
	return "no error message";
}

string LiMiPlatform::GetSig(const map<string, string> &params, const string &appkey, bool get, const string &uri, string &qstr)
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

int LiMiPlatform::GetAppFriendList(OPFriendList &friendList, const string &openid, const string &openkey)
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
	string url = m_config["v3domain"] + api + "?" + qstr;

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

string LiMiPlatform::GetSigStr(map<string,string> param,const string key)
{
	string sig = "";

	//签名按照请求参数名ASCII码从小到大排序（字典序），使用URL键值对的格式进行拼接
	map<string,string>::iterator it = param.begin();
	for(; it != param.end(); it++)
	{
		if(it->second != "")
		{
			sig += it->first + "=" + it->second + "&";
		}
	}

	//拼接sigkey
	sig += "key=" + key;

	//进行md5运算
	sig = Crypt::Md5Encode(sig);

	//将签名中小写转大写
	transform(sig.begin(), sig.end(), sig.begin(), ::toupper);
	return sig;
}

string  LiMiPlatform::GenerateXMLStr(map<string,string> param)
{
	string data = "";

	//使用param拼接xml格式的字符串
	CMarkupSTL xml;
	xml.AddElem("xml");
	xml.IntoElem();
	map<string,string>::iterator it = param.begin();
	for(; it != param.end(); it++)
	{
		xml.AddElem( it->first.c_str(), it->second.c_str() );
	}
	data = xml.GetDoc();

	return data;
}
