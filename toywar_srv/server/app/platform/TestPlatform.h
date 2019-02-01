/*
 * TestPlatform.h
 *
 *  Created on: 2011-5-16
 *      Author: dada
 */

#ifndef TESTPLATFORM_H_
#define TESTPLATFORM_H_

#include "IOpenPlatform.h"

class CTestPlatform: public IOpenPlatform
{
public:
	CTestPlatform() {}
	virtual ~CTestPlatform() {}
	virtual PlatformType GetPlatformType() { return PT_TEST; }
	virtual int Initialize(const string &appid, const string &appkey, map<string, string> &params);
	virtual int GetUserInfo(OPUserInfo &userInfo, const string &openid, const string &openkey);
	virtual int GetAppFriendList(OPFriendList &friendList, const string &openid, const string &openkey);
	virtual string GetErrorMessage() { return m_errMsg; };
private:
	string m_userData;
	string m_errMsg;
};

#endif /* TESTPLATFORM_H_ */
