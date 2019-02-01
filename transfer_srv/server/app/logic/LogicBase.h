/*
 * LogicBase.h
 *
 *  Created on: 2011-6-10
 *      Author: dada
 */

#ifndef LOGICBASEX_H_
#define LOGICBASEX_H_

#include "LogicInc.h"

enum BaseType
{
	BT_MAIN_BASE = 0,
	BT_SUB_BASE = 1,
	BT_WILD_FORCE = 2,
	BT_GATE = 3,
	BT_WORLD_WILD_FORCE = 4
};

enum BaseStatus
{
	BS_NEW = 0,
	BS_BUILD = 1,
	BS_FIGHT = 2
};

//#define ANTI_PROTECT_TIME	(24 * 60 * 60)
//#define UpdateProtectTime(t)	if(Time::GetGlobalTime() > ((t) & 0x7fffffff)) t = 0
//#define IsInProtect(t)	(((t) & 0x80000000) == 0 && Time::GetGlobalTime() <= (t))
//#define IsInAntiProtect(t)	((Time::GetGlobalTime() | 0x80000000) <= (t))
//#define GetProtectTime(t)	((t) & 0x80000000) ? 0 : (t)
//#define SetAntiProtect(t)	t = (Time::GetGlobalTime() + ANTI_PROTECT_TIME) | 0x80000000

#define UpdateProtectTime(t)	if(Time::GetGlobalTime() > ((t) & 0x7fffffff)) t = 0
#define IsInProtect(t)	(((t) & 0x80000000) == 0 && Time::GetGlobalTime() <= (t))
#define IsInAntiProtect(t)	false
#define GetProtectTime(t)	(((t) & 0x80000000) ? 0 : (t))
#define SetAntiProtect(t)	t = 0

namespace LogicBase
{
	int AddBase(DataBase &base, DataBaseExtra &baseExtra);	//自动生成baseid，保存在base.baseid中
	int AddMainBase(unsigned uid, unsigned &baseid);
	int RemoveBase(unsigned uid, unsigned baseid);

	int SetBase(const DataBase &base);
	int GetBase(unsigned uid, unsigned baseid, DataBase &base);

	int SetBaseExtra(const DataBaseExtra &baseExtra);
	int GetBaseExtra(unsigned baseid, DataBaseExtra &baseExtra);

	int AddUserBase(unsigned uid, int index, unsigned baseid);
	int GetUserBases(unsigned uid, map<int, unsigned> &bases);
	int RemoveUserBase(unsigned uid, int index);
	int GetSubBasesJson(unsigned uid, Json::Value &data);

	int SetExtraData(unsigned baseid, const Json::Value &extraData);
	int GetExtraData(unsigned baseid, Json::Value &extraData);
	int SetPosition(unsigned baseid, unsigned position);
	int GetPosition(unsigned baseid, unsigned &position);

	int UpdateActiveTime(unsigned baseid);

	int AddUpdate(unsigned uid, unsigned baseid, unsigned uidBy, const Json::Value &data, Json::Value *pResult = NULL);
	int GetUpdates(unsigned baseid, Json::Value &data);
	int ClearUpdates(unsigned lastUpdateId, Json::Value &updates);

	int SetMilitary(unsigned baseid, const Json::Value &data);
	int GetMilitary(unsigned baseid, Json::Value &data);
	int UpdateMilitary(unsigned uid, const Json::Value &data);
	int ChangeArmy(unsigned uid, unsigned baseid, const map<string, int> &change);
	int SetHero(unsigned baseid, const Json::Value &hero);

	int ChangeOwner(unsigned uid, DataBase &base);
	int AddSubBase(unsigned uid, DataBase &base);

};

#endif /* LOGICBASEX_H_ */
