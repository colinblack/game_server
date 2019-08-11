/*
 * SkillSummon.cpp
 *
 *  Created on: 2019年6月17日
 *      Author: Administrator
 */

#include "SkillSummon.h"
#include "BattleInc.h"

SkillSummon::SkillSummon() {
	m_type = SKILL_SUMMON;
}

SkillSummon::~SkillSummon() {
}

bool SkillSummon::doSkillHit(const SkillUseInfo &sinfo, MapMoveObject *caster, MapMoveObject *target, AttackInfo &ainfo) {
	const CfgSkill::Skill &skill = SkillCfgWrap().GetById(sinfo.skillId);
	StdMonster *dog = new StdMonster();

	Point p;
	caster->getPos(p.x, p.y);
	dog->init(skill.hurt(), caster->getFbId(), caster->getMapId(), p);

	dog->setOwner(caster->getId());

	dog->setNeedRecove(false);
	dog->setCanMove(true);
	dog->setActively(true);
	dog->setForce(FORCE_FRIEND);

	if (!dog->recove()) {
		return false;
	}

	PropertySets &marster_props = caster->getProps();

	dog->setActive(true);
	PropertySets &props = dog->getProps();
	props[AP_ATTACK].pi = marster_props[AP_ATTACK].pi;
	dog->setHurtSkill(sinfo.skillId);

	return true;
}
