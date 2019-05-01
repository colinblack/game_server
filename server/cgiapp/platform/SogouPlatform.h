/*
 * SogouPlatform.h
 *
 *  Created on: 2015-9-01
 *      Author: Eddard
 */

#ifndef SOGOUPLATFORM_H_
#define SOGOUPLATFORM_H_

#include "IOpenPlatform.h"
#include "Common.h"

class SogouPlatform : public IOpenPlatform
{
public:
	SogouPlatform();
	virtual int Initialize(const string &appid, const string &appkey, map<string, string> &params);
	virtual void SetParameter(const map<string, string> &params);
	virtual int GetUserInfo(OPUserInfo &userInfo, const string &openid, const string &openkey);
	virtual int GetAppFriendList(OPFriendList &friendList, const string &openid, const string &openkey);
	virtual string GetErrorMessage();
	virtual int Is_Login(const string &openid, const string &openkey,const string &pf);
	virtual void ReplyCharge();

private:
	string m_errorMessage;
	string m_pf;
	string m_userip;
	string m_time;
	unsigned m_cm;
};

#endif //SOGOUPLATFORM_H_
