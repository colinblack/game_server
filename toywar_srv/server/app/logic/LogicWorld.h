/*
 * LogicWorld.h
 *
 *  Created on: 2012-2-23
 *      Author: dada
 */

#ifndef LOGICWORLD_H_
#define LOGICWORLD_H_

#include "LogicInc.h"

//postion field
//+-------+-----+-----+
//| World |  X  |  Y  |
//+-------+-----+-----+
//31     23     11    0

class CWorldPoint
{
public:
	unsigned World;
	int X;
	int Y;
	CWorldPoint();
	CWorldPoint(unsigned position);
	CWorldPoint(unsigned world, int x, int y);
	int GetDistance(const CWorldPoint &to) const;
	void FromUInt(unsigned position);
	unsigned ToUInt() const;
};

namespace LogicWorld
{
	unsigned GetWorldSize();
	int CreateNpc(unsigned position);
	int RefreshNpc(DataBase &base);
	int CreateWorld(unsigned world);
	int GetMaxWorld(int &world);
	int GetTerrain(unsigned position);
	int AddUser(unsigned uid, CWorldPoint &point);
	int RemoveUser(unsigned uid);
	int SetWorld(unsigned position, unsigned baseid);
	int SetBasePosition(unsigned baseid, unsigned position);	//LogicWorld::SetWorld + LogicBase::SetPosition
	int GetBase(unsigned position, DataBase &base);
	int GetBasesJson(unsigned uid, const Json::Value &positions, Json::Value &data);

	int OccupyBase(unsigned uid, unsigned baseid, unsigned r1, unsigned r2, unsigned r3, unsigned r4, unsigned cash);
	int MoveBase(unsigned uid, unsigned baseid, unsigned r1, unsigned r2, unsigned r3, unsigned r4, unsigned cash);
	int InviteMove(uint64_t &inviteId, unsigned fromUid, unsigned toUid, unsigned baseid);
	int ProcessRequest(const DataMessage &request, unsigned from, unsigned to, const string &type, int action, const Json::Value &data);
	int AcceptMove(unsigned uid, uint64_t inviteId, unsigned r1, unsigned r2, unsigned r3, unsigned r4, unsigned cash);
	int RemoveSubBases(unsigned uid);

	CDataWorldUser *GetDataWorldUser();
	int RefreshUserWorld(unsigned uid, int world);
}

#endif /* LOGICWORLD_H_ */
