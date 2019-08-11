/*
 * SkillRush.cpp
 *
 *  Created on: 2019年8月6日
 *      Author: Administrator
 */

#include "SkillRush.h"
#include "BattleInc.h"

SkillRush::SkillRush() {
	m_type = SKILL_RUSH;
}

SkillRush::~SkillRush() {
}

bool SkillRush::doSkillHit(const SkillUseInfo &sinfo, MapMoveObject *caster, MapMoveObject *target, AttackInfo &ainfo) {
	return caculateHurt(sinfo, caster, target, ainfo);
}
