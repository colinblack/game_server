/*
 * SkillSummon.h
 *
 *  Created on: 2019年6月17日
 *      Author: Administrator
 */

#ifndef SKILL_SUMMON_H_
#define SKILL_SUMMON_H_

#include "SkillBase.h"
#include "StdMonster.h"

class SkillSummon: public SkillBase {
public:
	SkillSummon();
	virtual ~SkillSummon();
	virtual bool doSkillHit(const SkillUseInfo &sinfo, MapMoveObject *caster, MapMoveObject *target, AttackInfo &ainfo);
};

#endif /* SKILL_SUMMON_H_ */
