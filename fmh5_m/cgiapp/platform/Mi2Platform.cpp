#include "Mi2Platform.h"
#include <iostream>

Mi2Platform::Mi2Platform()
{
}

int Mi2Platform::Initialize(const string &appid, const string &appkey, map<string, string> &params)
{
	IOpenPlatform::Initialize(appid, appkey, params);
	m_AppSecret = m_config["sigkey"];
	return 0;
}

void Mi2Platform::SetParameter(const map<string, string> &params)
{

}

int Mi2Platform::GetUserInfo(OPUserInfo &userInfo, const string &openid, const string &openkey)
{
	const string api = "/api/biz/service/loginvalidate";
	map<string,string> params;		//参数名按字典序排序
	params["appId"] = m_appId;
	params["uid"] = openid;			//此处uid是小米平台sdk获取的账号唯一标识,作用相当于openid
	params["session"] = openkey;	//此处session用于校验登录验证的有效性,作用相当于session
	string qstr;
	GetSig(params, m_AppSecret, api, qstr);		//获取post内容以及签名
	string url = m_config["v3domain"] + api;
	string response;
	if (!Network::HttpPostRequest(response, url, qstr) || response.empty())
	{
		error_log("[http request fail][openid=%s,openkey=%s,errmsg=%s,url=%s,post=%s]",
				openid.c_str(), openkey.c_str(), response.c_str(), url.c_str(), qstr.c_str());
		return -1;
	}

	info_log("Mi2_platform_login_verify_response:%s",response.c_str());

	Json::Value value;
	if (!Json::Reader().parse(response, value))
	{
		error_log("[json parse fail][openid=%s,openkey=%s,response=%s,url=%s,post=%s]",
				openid.c_str(), openkey.c_str(), response.c_str(), url.c_str(), qstr.c_str());
		return -1;
	}
	int errcode = 0;
	if (!Json::GetInt(value, "errcode", errcode))
	{
		error_log("[get_info fail][openid=%s,openkey=%s,msg=%s,url=%s,post=%s]",
				openid.c_str(), openkey.c_str(), response.c_str(), url.c_str(), qstr.c_str());
		return -1;
	}

	if(errcode != verify_success)
	{
		error_log("[Mi2_login_verify_fail][errcode=%d,openid=%s,openkey=%s,msg=%s,url=%s,post=%s]",
				errcode,openid.c_str(), openkey.c_str(), response.c_str(), url.c_str(), qstr.c_str());
		return -1;
	}

	userInfo.OpenId = openid;
	return 0;
}

string Mi2Platform::GetErrorMessage()
{
	return "no error message";
}

string Mi2Platform::GetSig(const map<string, string> &params, const string &secret_key, const string &uri, string &qstr)
{
	string signature;
	string qsig;
	qstr.clear();
	map<string, string>::const_iterator it = params.begin();
	for (; it != params.end(); it++)
	{
		if (!qsig.empty())
		{
			qsig += "&";
		}
		qsig += it->first + "=" + it->second;
	}
	string raw_sig = Crypt::HmacSha1(qsig, secret_key);
	transfer(raw_sig, signature);

	qstr = qsig + "&signature=" + signature;
	debug_log("raw_sig=%s,signature=%s",raw_sig.c_str(),signature.c_str());

	return signature;
}

string Mi2Platform::GetSig(const map<string, string> &params, const string &secretKey)
{
	string qsig;
	string signature;
	map<string, string>::const_iterator it = params.begin();
	for (; it != params.end(); it++)
	{
		if (!qsig.empty())
		{
			qsig += "&";
		}
		qsig += it->first + "=" + it->second;
	}
	string raw_sig = Crypt::HmacSha1(qsig, secretKey);
	transfer(raw_sig, signature);

	debug_log("qsig=%s,signature=%s",qsig.c_str(),signature.c_str());
	return signature;

}

void Mi2Platform::transfer(string & input, string & output)
{
	output.clear();
	int len = input.size();
	if(!len)
		return;
	for(int i = 0; i < len; ++i)
	{
		char buffer[3] = {0};   	//此处应该数组长度必须大于1
		sprintf(buffer,"%02x",(unsigned char) input[i]);	//十六进制转换时,需将0xe转换成0x0e
		output.append(buffer);
	}
	return;
}

int Mi2Platform::GetAppFriendList(OPFriendList &friendList, const string &openid, const string &openkey)
{

	return 0;
}

