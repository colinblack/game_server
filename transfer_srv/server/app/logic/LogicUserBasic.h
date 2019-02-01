/*
 * LogicUserBasic.h
 *
 *  Created on: 2011-7-11
 *      Author: dada
 */

#ifndef LOGICUSERBASIC_H_
#define LOGICUSERBASIC_H_

#include "LogicInc.h"

enum VipType
{
	VT_NORMAL = 0,
	VT_QQ_YELLOW = 1,
	VT_QQ_YELLOW_YEAR = 2,
	VT_SINAWB = 3,
};

namespace LogicUserBasic
{

	int LoginPlatformUser(PlatformType platform, OPUserInfo &userInfo, const OPFriendList &friendList,
		const string &openkey, const string &inviteId, unsigned &uid);

	//autoAlt: 是否自动从互通平台查找用户
	int GetUid(unsigned &uid, PlatformType platform, const string &openid, bool autoAlt = true);

	int GetUser(unsigned uid, PlatformType platform, DataUserBasic &user);

	//自动切换互通平台
	int GetUserSmart(unsigned uid, PlatformType platform, DataUserBasic &user);

	int RemoveUser(unsigned uid);

	int AfterLogin(unsigned uid, const string &openid, const string &openkey);

};

#endif /* LOGICUSERBASIC_H_ */
