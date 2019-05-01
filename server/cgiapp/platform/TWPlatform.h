#ifndef  BSGPLATFORM_INC
#define  BSGPLATFORM_INC

#include "IOpenPlatform.h"
#include "Common.h"

class CTWPlatform : public IOpenPlatform
{
public:
	CTWPlatform();
	virtual ~CTWPlatform();
	virtual int Initialize(const string &appid, const string &appkey, map<string, string> &params);

	virtual int GetUserInfo(OPUserInfo &userInfo, const string &openid, const string &openkey);
	//int GetOtherUserInfo(OPUserInfo userInfo, const string &queryOpenId, const string &openid, const string &openkey);
	virtual int GetAppFriendList(OPFriendList &friendList, const string &openid, const string &openkey);

	virtual string GetErrorMessage();

	virtual void ReplyCharge();
private:
	string m_errorMessage;
};

#endif

