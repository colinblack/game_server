/*
 * CPengyouPlatform.h
 *
 *  Created on: 2011-5-16
 *      Author: dada
 */

#ifndef PENGYOUPLATFORM_H_
#define PENGYOUPLATFORM_H_

#include "IOpenPlatform.h"
#include "pengyou.h"

class CPengyouPlatform : public IOpenPlatform
{
public:
	CPengyouPlatform();
	virtual ~CPengyouPlatform();
	virtual PlatformType GetPlatformType() { return m_type; }
	virtual int Initialize(const string &appid, const string &appkey, map<string, string> &params);
	virtual int GetUserInfo(OPUserInfo &userInfo, const string &openid, const string &openkey);
	virtual int GetAppFriendList(OPFriendList &friendList, const string &openid, const string &openkey);
	virtual string GetErrorMessage();

private:
	CPengyou *m_pengyou;
	PlatformType m_type;
};

#endif /* PENGYOUPLATFORM_H_ */
