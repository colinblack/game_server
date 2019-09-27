/*
 * 支持腾讯v3版api
 */

#ifndef _WANBA_PLATFORM_H_
#define _WANBA_PLATFORM_H_

#include "IOpenPlatform.h"
#include "Common.h"

class WanBaPlatform : public IOpenPlatform
{
public:
	WanBaPlatform();
	virtual int Initialize(const string &appid, const string &appkey, map<string, string> &params);
	virtual void SetParameter(const map<string, string> &params);
	virtual int GetUserInfo(OPUserInfo &userInfo, const string &openid, const string &openkey);
	virtual int GetBlueVipInfo(OPUserInfo &userInfo, const string &openid, const string &openkey);
	virtual int WordFilter(uint32_t uid, const string &name, const string &openid, const string &openkey);
	virtual int GetAppFriendList(OPFriendList &friendList, const string &openid, const string &openkey);
	virtual string GetErrorMessage();

	static string GetSig(const map<string, string> &params, const string &appkey, bool get, const string &uri, string &qstr);
	static int formatUrl(const map<string, string> &param, const string &appkey, const string &api, string &url, string domain);

	virtual int Is_Login(const string &openid, const string &openkey,const string &pf);
private:
	string m_pf;
	string m_userip;
};

#endif
