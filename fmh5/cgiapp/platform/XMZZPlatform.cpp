#include "XMZZPlatform.h"
#include <iostream>

XMZZPlatform::XMZZPlatform()
{
}

int XMZZPlatform::Initialize(const string &appid, const string &appkey, map<string, string> &params)
{
	IOpenPlatform::Initialize(appid, appkey, params);
	return 0;
}

void XMZZPlatform::SetParameter(const map<string, string> &params)
{
}

int XMZZPlatform::GetUserInfo(OPUserInfo &userInfo, const string &openid, const string &openkey)
{
	userInfo.OpenId = openid;
	return 0;
}

int XMZZPlatform::formatUrl(const map<string, string> &param,
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

string XMZZPlatform::GetErrorMessage()
{
	return "no error message";
}

string XMZZPlatform::GetSig(const map<string, string> &params, const string &appkey, bool get, const string &uri, string &qstr)
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

int XMZZPlatform::GetAppFriendList(OPFriendList &friendList, const string &openid, const string &openkey)
{
	return 0;
}

string XMZZPlatform::GetSigStr(map<string,string> param,const string key)
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

string  XMZZPlatform::GenerateXMLStr(map<string,string> param)
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
