/*
 * New4399Platform.h
 *
 *  Created on: 2017-3-28
 *      Author: Ralf
 */

#ifndef NEW4399PLATFORM_H_
#define NEW4399PLATFORM_H_



#include "IOpenPlatform.h"
#include "Common.h"

class CNew4399Platform : public IOpenPlatform
{
public:
	CNew4399Platform();
	virtual int Initialize(const string &appid, const string &appkey, map<string, string> &params);
	virtual void SetParameter(const map<string, string> &params);
	virtual int GetUserInfo(OPUserInfo &userInfo, const string &openid, const string &openkey);
	virtual int GetAppFriendList(OPFriendList &friendList, const string &openid, const string &openkey);
	virtual string GetErrorMessage();
	virtual int Is_Login(const string &openid, const string &openkey,const string &pf);
	virtual void ReplyCharge();
private:
	string m_errorMessage, m_site;
	unsigned m_time, m_cm;
};


#endif /* NEW4399PLATFORM_H_ */
