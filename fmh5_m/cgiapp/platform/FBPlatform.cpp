#include "FBPlatform.h"
#include <iostream>

FBPlatform::FBPlatform()
{
}

int FBPlatform::Initialize(const string &appid, const string &appkey, map<string, string> &params)
{
	IOpenPlatform::Initialize(appid, appkey, params);
	return 0;
}

void FBPlatform::SetParameter(const map<string, string> &params)
{

}

int FBPlatform::GetUserInfo(OPUserInfo &userInfo, const string &openid, const string &openkey)
{
	//1.按'.' 将字符串分割成两份,存储在vector中
	vector<string>part;
	part.clear();
	unsigned pos = 0;
	string flag = ".";
	string var_openkey = openkey;
	pos = var_openkey.find(flag);
	if(string::npos != pos)
	{
		part.push_back(var_openkey.substr(0, pos));
		part.push_back(var_openkey.substr(pos + 1,var_openkey.length()));
	}
	else
	{
		error_log("openkey_param_error.openkey=%s",openkey.c_str());
		return -1;
	}
	//2.使用BASE64解码第一部分 得到签名
	string sig;
	string strsrc = part[0];
	ReplaceStr(strsrc);
	Crypt::Base64Decode(sig,strsrc);
	//debug_log("strsrc=%s",strsrc.c_str());

	//3.使用BASE64解码第二部分得到一个JSON字符串,并校验
	string jsonStr;
	strsrc = part[1];
	ReplaceStr(strsrc);
	Crypt::Base64Decode(jsonStr,strsrc);
	Json::Value value;
	Json::Reader reader;
	if( !reader.parse( jsonStr, value ) )
	{
		error_log("[json_param_error].%s",jsonStr.c_str());
		return -1;
	}
	string player_id;
	string issued_at;
	Json::GetString(value,"player_id",player_id);
	Json::GetString(value,"issued_at",issued_at);
	if(player_id.empty() && issued_at.empty())
	{
		error_log("[openid_or_ts_param_error].%s,%s",player_id.c_str(),issued_at.c_str());
		return -1;
	}
	if(player_id != openid)
	{
		error_log("[openid_param_error].%s,%s",player_id.c_str(),openid.c_str());
		return -1;
	}

	unsigned cur_ts = Time::GetGlobalTime();
	unsigned openkey_ts = CTrans::STOI(issued_at);
	int diff_ts = cur_ts - openkey_ts;
	if(diff_ts >= 300)
	{
		error_log("[ts_time_out]%u,%u,%d",cur_ts,openkey_ts,diff_ts);
		return -1;
	}

	//4.使用 HMAC SHA-256 根据 secret key 加密第二部分，检验是否等于签名
	string sig2;
	sig2 = Crypt::HmacSha256(part[1],m_appKey);

	if(sig != sig2)
	{
		error_log("[sig_check_error],sig=%s,sig2=%s",sig.c_str(),sig2.c_str());
		return -1;
	}
	userInfo.OpenId = openid;
	return 0;
}

int FBPlatform::formatUrl(const map<string, string> &param,
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
			qstr.append("&").append(itr->first).append("=").append(Crypt::UrlEncodeForTX(itr->second));
		}
		else
		{
			qstr.append(itr->first).append("=").append(Crypt::UrlEncodeForTX(itr->second));
		}
	}
	url = api + qstr;
	return 0;
}

void FBPlatform::ReplaceStr(string & strsrc)
{
	int n_pos = 0;
	while( (n_pos=strsrc.find("-",n_pos)) != std::string::npos )
	{
		strsrc.replace( n_pos,1, "+" );
		n_pos += 1;
	}
	n_pos = 0;
	while( (n_pos=strsrc.find("_",n_pos)) != std::string::npos )
	{
		strsrc.replace( n_pos,1, "/" );
		n_pos += 1;
	}
}

string FBPlatform::GetErrorMessage()
{
	return "no error message";
}

string FBPlatform::GetSig(const map<string, string> &params, const string &appkey, bool get, const string &uri, string &qstr)
{
	string sig;
	return sig;
}

int FBPlatform::GetAppFriendList(OPFriendList &friendList, const string &openid, const string &openkey)
{
	return 0;
}

