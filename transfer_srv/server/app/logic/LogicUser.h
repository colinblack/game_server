/*
 * LogicUser.h
 *
 *  Created on: 2011-5-27
 *      Author: dada
 */

#ifndef LOGICUSER_H_
#define LOGICUSER_H_

#include "LogicInc.h"

enum UserStatus
{
	US_ACTIVE = 0,
	US_REMOVE = 1,
	US_BAN = 2
};

namespace LogicUser
{

	int AddUser(unsigned &uid, PlatformType platform, unsigned inviteUid = 0);	//返回uid
	int RemoveUser(unsigned uid);

	int SetUser(DataUser &user);
	int GetUser(unsigned uid, DataUser &user);

	int SetUserExtra(const DataUserExtra &userExtra);
	int GetUserExtra(unsigned uid, DataUserExtra &userExtra);

	int UpdateActiveTime(unsigned uid, unsigned activeTime = 0);
	int GetMainBaseId(unsigned uid, unsigned &baseid);
	int GetActiveTime(unsigned uid, unsigned activeTime);
	int GetExtraData(unsigned uid, Json::Value &extraData);
	int SetExtraData(unsigned uid, const Json::Value &extraData);
	int GetStat(unsigned uid, Json::Value &userStat);
	int SetStat(unsigned uid, const Json::Value &userStat);
	int SetGateTimes(const DataUserExtra &userExtra);
	int GetGateTimes(unsigned uid, DataUserExtra &userExtra);
	int SetWorld(unsigned uid, int world);
	int GetWorld(unsigned uid, int &world);
	int SetAllianceId(unsigned uid, unsigned allianceId);
	int GetAllianceId(unsigned uid, unsigned &allianceId);
	int SetBookmark(unsigned uid, const Json::Value &bookmark);
	int ChangeResource(unsigned uid, int r1, int r2, int r3, int r4);
	int GetResourcesJson(const DataUser &user, Json::Value &data);
	int UpdateLevel(DataUser &user);

	int OnLogin(unsigned uid, PlatformType platform, const string &openid, const string &openkey);
	int OnInvite(unsigned uid, const string &name, PlatformType platform, unsigned inviteUid);

	int GetUserInfo(unsigned uid, Json::Value &data);
};

#endif /* LOGICUSER_H_ */
