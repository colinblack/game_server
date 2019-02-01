#ifndef _WX_PLATFORM_H_
#define _WX_PLATFORM_H_

#include "IOpenPlatform.h"
#include "Common.h"

class WXPlatform : public IOpenPlatform
{
public:
	WXPlatform();
	virtual int Initialize(const string &appid, const string &appkey, map<string, string> &params);
	virtual void SetParameter(const map<string, string> &params);
	virtual int GetUserInfo(OPUserInfo &userInfo, const string &openid, const string &openkey);
	virtual int GetAppFriendList(OPFriendList &friendList, const string &openid, const string &openkey);
	virtual string GetErrorMessage();
	static string GetSig(const map<string, string> &params, const string &appkey, bool get, const string &uri, string &qstr);
	static int formatUrl(const map<string, string> &param, const string &appkey, const string &api, string &url);
private:
	string m_code;
};

#endif
