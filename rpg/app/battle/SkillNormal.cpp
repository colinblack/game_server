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
	SkillCfgWrap cfg_wrap;
	uint32_t skillId = sinfo.hurtSkillId == 0 ? sinfo.skillId : sinfo.hurtSkillId;
	const CfgSkill::Skill &cfg = cfg_wrap.GetById(skillId);

	PropertySets a_props, b_props;
	PropertyManager::Instance()->calcFightProps(caster, a_props);
	PropertyManager::Instance()->calcFightProps(target, b_props);

	if (cfg_wrap.IsZhanLing(cfg)) {
		float pre = 0.0f;
		if (target->getRace() != RACE_HUMAN) {
			if (cfg.has_zhanlinghurt() && cfg.zhanlinghurt() > 0) {
				pre = static_cast<float>(cfg.zhanlinghurt() % 10000) / 100.0f;
			} else {
				pre = static_cast<float>(cfg.hurt() % 1000) / 100.0f;
			}
		} else {
			pre = static_cast<float>(cfg.hurt() % 1000) / 100.0f;
		}
		ainfo.addHurt = pre * a_props[AP_ATTACK].pui + pre * (1 + a_props[AP_XPDMGADD].pui - b_props[AP_XPDMGDEC].pui);
		ainfo.hurtType = HURT_TYPE_HEJIE;
	} else {
		int hurt_add = cfg.has_hurtadd() ? cfg.hurtadd() : 0;

		//xxx hurt percent can not less then 15%
		float hurt_percent = std::max(0.15f, static_cast<float>(cfg.hurt() % 1000) / 100.0f);

		if (cfg_wrap.IsSummon(cfg)) {
			hurt_percent = 0.15f;
		}

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

		//火盾免伤
		int fix_hurt = hurt * (static_cast<float>(b_props[AP_FIXDMGPERCENT].pi) / 100.0f);
		int fix_hurt_max = b_props[AP_ATTACK].pi * static_cast<float>(b_props[AP_FIXDMGMAX].pi) / 100.0f;
		if (fix_hurt > fix_hurt_max) {
			fix_hurt = fix_hurt_max;
		}

		int finalHurt = std::max(static_cast<int>(0.25 * a_props[AP_ATTACK].pi), hurt + hurt_add + a_props[AP_FIXDMG].pi - (a_props[AP_FIXDMGDEC].pi + fix_hurt) + holyHurt);

		if (b_props[AP_MAX_HURTPERCENT].pi > 0) {
			int finalHurt1 = static_cast<double>(b_props[AP_MAXLIFE].pl) * static_cast<double>(b_props[AP_MAX_HURTPERCENT].pi) / 100.0;
			if (finalHurt > finalHurt1) {
				finalHurt = finalHurt1;
			}
		}
		ainfo.addHurt = finalHurt < 0 ? 0 : finalHurt;
		ainfo.hurtType = HURT_TYPE_NORMAL;
	}
	return true;
}
