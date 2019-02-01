/*
 * LogicFriend.h
 *
 *  Created on: 2012-3-5
 *      Author: dada
 */

#ifndef LOGICFRIEND_H_
#define LOGICFRIEND_H_

#include "LogicInc.h"

namespace LogicFriend
{
	int AddFriends(unsigned uid, PlatformType platform, const string &openId, const OPFriendList &friendList);
	int UpdateFriends(unsigned uid, PlatformType platform, const string &openId, const OPFriendList &friendList);
	int GetFriends(unsigned uid, PlatformType platform, UidList &friends);
	int GetFriendsJson(unsigned uid, PlatformType platform, Json::Value &friends);
	bool IsFriend(unsigned uid, PlatformType platform, unsigned friendId);
}

#endif /* LOGICFRIEND_H_ */
