/*
 * 支持腾讯v3版api
 */

#ifndef _OPPO_PLATFORM_H_
#define _OPPO_PLATFORM_H_

#include "IOpenPlatform.h"
#include "Common.h"

class OPPOPlatform : public IOpenPlatform
{
public:
	OPPOPlatform();
	virtual int Initialize(const string &appid, const string &appkey, map<string, string> &params);
	virtual void SetParameter(const map<string, string> &params);
	virtual int GetUserInfo(OPUserInfo &userInfo, const string &openid, const string &openkey);
	virtual int GetAppFriendList(OPFriendList &friendList, const string &openid, const string &openkey);
	virtual string GetErrorMessage();

	static string GetSig(const map<string, string> &params, const string &appkey, bool get, const string &uri, string &qstr);
	static int formatUrl(const map<string, string> &param, const string &appkey, const string &api, string &url);
	//获得签名
	static string GetSigStr(map<string,string> param,const string key);

	//校验签名
	static bool CheckSign(const string &text,const string publicKey,const string sign);
	//生产xml格式字符串
	static string GenerateXMLStr(map<string,string> param);
};

#endif
