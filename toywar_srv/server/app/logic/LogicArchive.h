/*
 * LogicArchive.h
 *
 *  Created on: 2011-6-1
 *      Author: dada
 */

#ifndef LOGICARCHIVE_H_
#define LOGICARCHIVE_H_

#include "LogicInc.h"

enum LoadType
{
	LT_UNKNOW = 0,	//未知
	LT_BUILD,	//建造
	LT_VIEW, 	//查看
	LT_HELP,	//帮助
	LT_ATTACK,	//攻击
};

enum SaveType
{
	ST_UNKNOW = 0,	//未知
	ST_BUILD,	//建造
	ST_VIEW,	//查看
	ST_HELP,	//帮助
	ST_ATTACK,	//攻击
};

struct DataArchive
{
	DataUserBasic UserBasic;
	DataUser User;
	DataUserExtra UserExtra;
	DataBase Base;
	DataBaseExtra BaseExtra;
	DataAlliance Alliance;
	DataAllianceMember Member;
	unsigned Cash;
};

class CLogicArchive
{
public:
	int GetArchive(PlatformType platform, unsigned uid, unsigned baseid, Json::Value &archive);
	int SetArchive(PlatformType platform, unsigned uid, unsigned baseid, const Json::Value &archive);

	int Load(unsigned uid, unsigned baseid, unsigned uidLoadBy, LoadType type, Json::Value &archive);
	int Save(unsigned uid, unsigned baseid, unsigned uidSaveBy, const Json::Value &data, Json::Value &result);
	int SaveUpdate(unsigned uid, unsigned baseid, unsigned uidSaveBy, const Json::Value &data, Json::Value &result);
	int UpdateSave(unsigned uid, unsigned baseid, unsigned uidSaveBy, SaveType type, Json::Value &result);

protected:
	int UpdateAttack(unsigned uid, unsigned uidDefence, const DataBase &baseDefence, const Json::Value &data);
	int ProcessPurchase(DataUser &user, DataUserExtra &userExtra, DataBase &base, const Json::Value &purchase, unsigned &cash, Json::Value &consume);

	int ArchiveToJson(const DataArchive &dataArchive, Json::Value &data, bool isOwner = true);
};

#endif /* LOGICARCHIVE_H_ */
