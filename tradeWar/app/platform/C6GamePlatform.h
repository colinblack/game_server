/*
 * C6GamePlatform.h
 *
 *  Created on: 2019年3月1日
 *      Author: colin
 */

#ifndef APP_PLATFORM_C6GAMEPLATFORM_H_
#define APP_PLATFORM_C6GAMEPLATFORM_H_

#include "IOpenPlatform.h"
#include "Common.h"

class CC6GamePlatform : public IOpenPlatform{
public:
	CC6GamePlatform();
	virtual ~CC6GamePlatform();
 	virtual PlatformType GetPlatformType() {
		return m_type;
	}
	virtual int Initialize(const string &appid, const string &appkey, map<string, string> &params);
	virtual int GetUserInfo(OPUserInfo &userInfo, const string &openid, const string &openkey, const string &pf, const string &userip);
	virtual string GetErrorMessage();
private:
	void GetQueryData(const map<string, string>& params, string& data);

private:
	PlatformType m_type;
};

#endif /* APP_PLATFORM_C6GAMEPLATFORM_H_ */
