/*
 * LogicAttack.h
 *
 *  Created on: 2011-6-29
 *      Author: Administrator
 */

#ifndef LOGICATTACK_H_
#define LOGICATTACK_H_

#include "LogicInc.h"

enum AttackType
{
	AT_ATTACK = 0,
	AT_DEFENCE = 1
};

enum AttackStatus
{
	AS_NO_READ = 0,
	AS_READ = 1
};

class CLogicAttack
{
public:
	int AddAttack(DataAttack &attack);
	int UpdateAttack(const DataAttack &attack);

	int GetAttack(uint64_t attackId, DataAttack &attack);
	int GetAttackLog(uint64_t attackId, unsigned uid, string &log);

	int SetAttackRead(unsigned uid, AttackType type, unsigned baseid = 0);
	int GetUnreadAttacks(vector<DataUserAttack> &attacks, unsigned uid, AttackType type, unsigned baseid = 0, unsigned time = 0);
	int GetAttackHistory(unsigned uid, vector<DataAttack> &attacks);

	int GetAttackCount(unsigned uid, unsigned startTime, AttackType type, unsigned baseid = 0, unsigned oppositeUid = 0);

	//获取连续进攻保护时间
	unsigned GetConAttackProtect(unsigned uid, unsigned baseid);

};

#endif /* LOGICATTACK_H_ */
