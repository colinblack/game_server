#include "VIVOPlatform.h"
#include <iostream>

VIVOPlatform::VIVOPlatform()
{
}

int VIVOPlatform::Initialize(const string &appid, const string &appkey, map<string, string> &params)
{
	IOpenPlatform::Initialize(appid, appkey, params);
	return 0;
}

void VIVOPlatform::SetParameter(const map<string, string> &params)
{
}

int VIVOPlatform::GetUserInfo(OPUserInfo &userInfo, const string &openid, const string &openkey)
{
	userInfo.OpenId = openid;
	return 0;
}

int VIVOPlatform::formatUrl(const map<string, string> &param,
		const string &appkey,
		const string &api,
		string &url)
{
	string qstr;
	map<string, string>::const_iterator itr = param.begin();
	for (; itr != param.end(); ++itr)
	{
		if (!qstr.empty())
		{
			qstr.append("&").append(itr->first).append("=").append(itr->second);
		}
		else
		{
			qstr.append(itr->first).append("=").append(itr->second);
		}
	}
	url = qstr + "&signature=" + appkey;
	return 0;
}

string VIVOPlatform::GetErrorMessage()
{
	return "no error message";
}

string VIVOPlatform::GetSig(const map<string, string> &params, const string &appkey, bool get, const string &uri, string &qstr)
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

int VIVOPlatform::GetAppFriendList(OPFriendList &friendList, const string &openid, const string &openkey)
{
	return 0;
}

string VIVOPlatform::GetSigStr(map<string,string> param,const string key)
{
	string sig = "";

	//1.to_lower(md5_hex(key))
	string crypt_key= Crypt::Md5Encode(key);

	//2.签名按照请求参数名ASCII码从小到大排序（字典序）
	map<string,string>::iterator it = param.begin();
	for(; it != param.end(); it++)
	{
		sig += it->first + "=" + it->second + "&";
	}
	//拼接crypt_key
	sig += crypt_key;

	//进行md5运算
	sig = Crypt::Md5Encode(sig);
	return sig;
}

string  VIVOPlatform::GenerateXMLStr(map<string,string> param)
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
