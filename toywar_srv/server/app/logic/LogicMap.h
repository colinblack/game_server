/*
 * LogicMap.h
 *
 *  Created on: 2011-6-9
 *      Author: dada
 */

#ifndef LOGICMAP_H_
#define LOGICMAP_H_

#include "LogicInc.h"

struct MapUserData
{
	unsigned uid;
	PlatformType platform;
	string open_id;
	string name;
	int gender;
	string figure_url;
	bool is_friend;
	int vip_type;
	int vip_level;
	uint64_t point;
	int level;
	unsigned last_active_time;
	unsigned baseid;
	int baseseed;
	string basename;
	unsigned alliance_id;
	string alliance_name;
	int alliance_flag;
	unsigned savetime;
	int attacksfrom;
	int attacksto;
	int helpsfrom;
	int helpsto;
	int attack_permit;
	int attackable_in;
	int retaliate_count;
};

enum AttackPermitType
{
	APT_ALLOW = 1,	//可以进攻，客户端判断自己保护期提醒和好友攻打提醒
	APT_ALLOW_LEVEL_HIGH = 2,	//可以进攻，对方等级高
	APT_BAN_LEVEL_LOW = 3,	//对方等级低
	APT_ALLOW_REVENGE = 4,	//可以进攻，复仇
	APT_BAN_DAMAGE_PROTECT = 5,	//破坏保护
	APT_BAN_NEW_PROTECT = 6,	//新手保护
	APT_BAN_BEING_ATTACK = 7,	//对方被攻击
	APT_BAN_TRUCE = 9, //讲和
	APT_ALLOW_ALLIANCE_REVENGE = 10,	//可以进攻，联盟复仇
	APT_BAN_ALLIANCE = 11	//同联盟
};

class CLogicMap
{

public:

	int GetMapUsersJson(unsigned uid, PlatformType platform, Json::Value &data);
	int GetMapUsers(unsigned uid, PlatformType platform, vector<MapUserData> &userList);
	int GetUserData(unsigned uid, PlatformType platform, const DataUser& userQuery, bool isFriend, MapUserData & userData);

	//返回attack permit
	int GetAttackPermit(const DataUser &user, const DataBase &base, const DataUser& userQuery);

	int UpdateUserInteract(vector<MapUserData> &userList, const DataUser& userQuery);

	int RemoveMapUser(unsigned uid);

protected:

	int PointToGroup(uint64_t point);

	CDataMap *GetDataMap(PlatformType platform);

};

#endif /* LOGICMAP_H_ */
