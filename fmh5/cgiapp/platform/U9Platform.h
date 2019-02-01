/*
 * U9Platform.h
 *
 *  Created on: 2018年8月24日
 *      Author: Ralf
 */

#ifndef CGIAPP_PLATFORM_U9PLATFORM_H_
#define CGIAPP_PLATFORM_U9PLATFORM_H_

#include "IOpenPlatform.h"
#include "Common.h"

class U9Platform : public IOpenPlatform
{
public:
	U9Platform();
	virtual int Initialize(const string &appid, const string &appkey, map<string, string> &params);
	virtual void SetParameter(const map<string, string> &params);
	virtual int GetUserInfo(OPUserInfo &userInfo, const string &openid, const string &openkey);
	virtual int GetAppFriendList(OPFriendList &friendList, const string &openid, const string &openkey);
	virtual string GetErrorMessage();
	virtual int Is_Login(const string &openid, const string &openkey,const string &pf);
	virtual void ReplyCharge();
	virtual void SetReply(string& reply);
private:
	string m_errorMessage;
	string m_reply;
	string m_pf;
};






#endif /* CGIAPP_PLATFORM_U9PLATFORM_H_ */
