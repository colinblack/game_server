/*
 * BuffAddHp.cpp
 *
 *  Created on: 2019年7月31日
 *      Author: Administrator
 */

#include "BuffAddHp.h"
#include "BattleInc.h"

bool BuffAddHp::init(const CfgSkill::Skill& cfg, const CfgSkill::Buff& bcfg, MapMoveObject* caster, MapMoveObject* target) {
	if (!BuffBase::init(cfg, bcfg, caster, target)) {
		return false;
	}
	id_ = cfg.id();
	value_ = static_cast<float>(caster->getProps()[AP_ATTACK].pui) * 0.27f + (cfg.has_hurtadd() ? cfg.hurtadd() : 0);
	return true;
}

bool BuffAddHp::doEffect() {
	MapMoveObject *target = MapManager::Instance()->getMoveObject(target_);
	if (target == NULL) {
		return false;
	}
	target->addHp(value_);
	return true;
}
