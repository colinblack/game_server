/*
 *LogicHequActivity.h
 *
 *  Created on: 2014-07-14
 *      Author: Administrator
 */

#ifndef LOGICHEQUACTIVITY_H_
#define LOGICHEQUACTIVITY_H_
#include "LogicInc.h"

class CLogicHequActivity {
public:
	CLogicHequActivity();
	virtual ~CLogicHequActivity();
	static CDataAlliancePoint* GetHequAlliancePoing();
	static CDataWorldAttack* GetHequWorldAttack();

	int GetHequAlliancePointRank(unsigned uid,vector <AlliancePoint> &vecPoints);
	int GetHequAlliancePointRankJson(unsigned uid, Json::Value &result);
	int UpdateHequAlliancePointRank(unsigned uid, const AlliancePoint &points);

	int GetHequWorldAttackRank(unsigned uid,vector <HequWorldAttack> &vecAttacks);
	int GetHequWorldAttackRankJson(unsigned uid, Json::Value &result);
	int UpdateHequWorldAttackRank(unsigned uid, const HequWorldAttack &Attack);
	int UpdateNewWorldAttackRank(multimap<unsigned, unsigned> herokill, map<unsigned, string> heroname);
};
#endif /* LOGICHEQUACTIVITY_H_ */
