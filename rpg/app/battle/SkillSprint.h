/*
 * SkillSprint.h
 *
 *  Created on: 2019年6月13日
 *      Author: Administrator
 */

#ifndef _SKILL_SPRINT_H_
#define _SKILL_SPRINT_H_

#include "SkillBase.h"

class SkillSprint: public SkillBase {
public:
	SkillSprint();
	virtual ~SkillSprint();
	virtual bool doSkillHit(const SkillUseInfo &sinfo, MapMoveObject *caster, MapMoveObject *target, AttackInfo &ainfo);
};

#endif /* _SKILL_SPRINT_H_ */
