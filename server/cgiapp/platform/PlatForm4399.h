/*
 * PlatForm4399.h
 *
 *  Created on: 2015-4-30
 *      Author: Ralf
 */

#ifndef PLATFORM4399_H_
#define PLATFORM4399_H_

#include "IOpenPlatform.h"
#include "Common.h"

class CPlatform4399 : public IOpenPlatform
{
public:
	CPlatform4399();
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
	unsigned m_time, m_cm;
};



#endif /* PLATFORM4399_H_ */
