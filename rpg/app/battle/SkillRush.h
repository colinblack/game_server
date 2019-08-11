/*
 * SkillRush.h
 *
 *  Created on: 2019年8月6日
 *      Author: Administrator
 */

#ifndef SKILL_RUSH_H_
#define SKILL_RUSH_H_

#include "SkillNormal.h"

class SkillRush: public SkillNormal {
public:
	SkillRush();
	virtual ~SkillRush();
	virtual bool doSkillHit(const SkillUseInfo &sinfo, MapMoveObject *caster, MapMoveObject *target, AttackInfo &ainfo);
};

#endif /* SKILL_RUSH_H_ */
