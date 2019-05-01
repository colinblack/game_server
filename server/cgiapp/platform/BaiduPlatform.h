/*
 * BaiduPlatform.h
 *
 *  Created on: 2015-12-12
 *      Author: zkw
 */

#ifndef BAIDUPLATFORM_H_
#define BAIDUPLATFORM_H_

#include "IOpenPlatform.h"
#include "Common.h"

class BaiduPlatform : public IOpenPlatform
{
public:
	BaiduPlatform();
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
	string m_pf;
	string m_userip;
	string m_time;
	string m_reply;
	unsigned m_cm;
};

#endif //BAIDUPLATFORM_H_
