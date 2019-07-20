/*
 * SkillNormal.h
 *
 *  Created on: 2019年6月13日
 *      Author: Administrator
 */

#ifndef _SKILL_NORMAL_H_
#define _SKILL_NORMAL_H_

#include "SkillBase.h"

class SkillNormal: public SkillBase {
public:
	SkillNormal();
	virtual ~SkillNormal();
	virtual bool doSkillHit(const SkillUseInfo &sinfo, MapMoveObject *caster, MapMoveObject *target, AttackInfo &ainfo);
	virtual bool caculateHurt(const SkillUseInfo &sinfo, MapMoveObject *caster, MapMoveObject *target, AttackInfo &ainfo);
};

#endif /* _SKILL_NORMAL_H_ */
