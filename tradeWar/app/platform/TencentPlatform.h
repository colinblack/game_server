/*
 * 支持腾讯v3版api
 */

#ifndef _TENCENT_PLATFORM_H_
#define _TENCENT_PLATFORM_H_

#include "IOpenPlatform.h"
#include "Common.h"

class CTencentPlatform: public IOpenPlatform {
public:
	CTencentPlatform();
	virtual PlatformType GetPlatformType() {
		return m_type;
	}
	virtual int Initialize(const string &appid, const string &appkey, map<string, string> &params);
	virtual void SetParameter(const map<string, string> &params);
	virtual int GetUserInfo(OPUserInfo &userInfo, const string &openid, const string &openkey, const string &pf, const string &userip);
	virtual int GetVipInfo(const string &openid, const string &openkey, const string &pf, const string &userip, uint32_t &vip);
	virtual int GetAppFriendList(OPFriendList &friendList, const string &openid, const string &openkey, const string& pf, const string& userip);
	virtual int GiftExchange(const string &openid, const string &openkey, const string &pf, const string &userip, const string &giftid, int &code);
	virtual string GetErrorMessage();
	virtual int IsLogin(const string &openid, const string &openkey, const string &pf, const string &user_ip);
	virtual int SendGameBarMsg(const string &openid, const string &openkey, const string &pf, const string &userip, const string &frd, int type, const string &msg, const string &qua);
public:
	static string FormatGetUrl(const map<string, string> &params, const string &appkey, const string &uri);
private:
	PlatformType m_type;
};

#endif
