/*
 * SkillNormal.cpp
 *
 *  Created on: 2019年6月13日
 *      Author: Administrator
 */

#include "SkillNormal.h"
#include "BattleInc.h"

SkillNormal::SkillNormal() {
	m_type = SKILL_NORMAL;
}

SkillNormal::~SkillNormal() {
}

bool SkillNormal::doSkillHit(const SkillUseInfo &sinfo, MapMoveObject *caster, MapMoveObject *target, AttackInfo &ainfo) {
	return caculateHurt(sinfo, caster, target, ainfo);
}

bool SkillNormal::caculateHurt(const SkillUseInfo &sinfo, MapMoveObject *caster, MapMoveObject *target, AttackInfo &ainfo) {
	const CfgSkill::Skill &cfg = SkillCfgWrap().GetById(sinfo.skillId);

	int hurt_add = cfg.hurt() / 1000;
	float hurt_percent = static_cast<float>(cfg.hurt() % 1000) / 100.0f;

	PropertySets& a_props = caster->getProps();
	PropertySets& b_props = target->getProps();

	float attack = static_cast<float>(Math::GetRandomInt(5) + 8) / 10.0f * static_cast<float>(a_props[AP_ATTACK].pui);

	int physicsHurt = std::max(0, static_cast<int>(attack) - b_props[AP_DEFENCE].pi);
	int holyHurt = std::max(0, a_props[AP_WUXINGHURT].pi - b_props[AP_WUXINGDEFENSE].pi);
	float dmg_add = static_cast<float>(a_props[AP_DMGADD].pi) / 10000;
	float dmg_dec = static_cast<float>(b_props[AP_DMGDEC].pi) / 10000;

	int hurt = (std::max(0.0f, 1 + dmg_add - dmg_dec) * hurt_percent) * static_cast<float>(physicsHurt);

	int criteRate = std::max(0, a_props[AP_CRITRATE].pi - b_props[AP_CRITBREAKRATE].pi);

	if (Math::GetRandomInt(10000) < criteRate) {
		hurt = static_cast<float>(hurt) * (static_cast<float>(a_props[AP_CRIT].pi - b_props[AP_CRITBREAK].pi) / 10000) + a_props[AP_CRITDMG].pi;
	}

	int finalHurt = std::max(static_cast<int>(0.25 * a_props[AP_ATTACK].pi), hurt + hurt_add + a_props[AP_FIXDMG].pi - a_props[AP_FIXDMGDEC].pi + holyHurt);

	if (b_props[AP_MAX_HURTPERCENT].pi > 0) {
		int finalHurt1 = static_cast<double>(b_props[AP_MAXLIFE].pl) * static_cast<double>(b_props[AP_MAX_HURTPERCENT].pi) / 100.0;
		if (finalHurt > finalHurt1) {
			finalHurt = finalHurt1;
		}
	}

	ainfo.addHurt = finalHurt;

	return true;
}
