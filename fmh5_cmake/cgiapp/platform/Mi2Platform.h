/*
 * 小米2 平台接入
 */

#ifndef _MI2_PLATFORM_H_
#define _MI2_PLATFORM_H_

#include "IOpenPlatform.h"
#include "Common.h"

class Mi2Platform : public IOpenPlatform
{
public:
	Mi2Platform();
	virtual int Initialize(const string &appid, const string &appkey, map<string, string> &params);
	virtual void SetParameter(const map<string, string> &params);
	virtual int GetUserInfo(OPUserInfo &userInfo, const string &openid, const string &openkey);
	virtual int GetAppFriendList(OPFriendList &friendList, const string &openid, const string &openkey);
	virtual string GetErrorMessage();

	static string GetSig(const map<string, string> &params, const string &secret_key, const string &uri, string &qstr);
	static string GetSig(const map<string, string> &params, const string &secretKey);
	enum Mi2ErrCode{
		verify_success 	= 200,	//验证正确
		wrong_appId 	= 1515,	//appId 错误
		wrong_uid 		= 1516,	//uid 错误
		wrong_session	= 1520,	//session 错误
		wrong_signature = 1525,	//signature 错误
		info_mismatch	= 4002	//appid, uid, session 不匹配(常见为session过期)
	};
	static void transfer(string & input, string & output);	//将字节数组转换成16进制字符串
private:
	string m_AppSecret;

};

#endif
