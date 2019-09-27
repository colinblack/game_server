/*
 * 小米4部
 */

#ifndef _XMFOUR_PLATFORM_H_
#define _XMFOUR_PLATFORM_H_

#include "IOpenPlatform.h"
#include "Common.h"

class XMFourPlatform : public IOpenPlatform
{
public:
	XMFourPlatform();
	virtual int Initialize(const string &appid, const string &appkey, map<string, string> &params);
	virtual void SetParameter(const map<string, string> &params);
	virtual int GetUserInfo(OPUserInfo &userInfo, const string &openid, const string &openkey);
	virtual int GetAppFriendList(OPFriendList &friendList, const string &openid, const string &openkey);
	virtual string GetErrorMessage();

	static void GetPostData(const map<string, string> &params, const string &sig, string &qstr);
	static int formatUrl(const map<string, string> &param, const string &appkey, const string &api, string &url);
	//获得签名
	static string GetSigStr(map<string,string> param,const string key);

private:
	string m_token;
	string m_gameid;
};

#endif
