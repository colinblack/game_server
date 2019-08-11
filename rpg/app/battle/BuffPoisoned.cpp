/*
 * BuffPoisoned.cpp
 *
 *  Created on: 2019年8月3日
 *      Author: Administrator
 */

#include "BuffPoisoned.h"
#include "BattleInc.h"

bool BuffPoisoned::init(const CfgSkill::Skill& cfg, const CfgSkill::Buff& bcfg, MapMoveObject* caster, MapMoveObject* target) {
	if (!BuffBase::init(cfg, bcfg, caster, target)) {
		return false;
	}
	if (caster_ == target_) {
		error_log("can not poisoned to myself");
		return false;
	}
	return true;
}

bool BuffPoisoned::doEffect() {
	MapMoveObject *target = dynamic_cast<MapMoveObject*>(MapManager::Instance()->getMoveObject(target_));
	if (target == NULL) {
		return false;
	}
	MapMoveObject *caster = dynamic_cast<MapMoveObject*>(MapManager::Instance()->getMoveObject(caster_));
	if (target == NULL) {
		return false;
	}
	msgs::SFightUpdate hurt_update;
	PropertySets hurtProps;
	uint32_t attack = caster->getProps()[AP_ATTACK].pui;
	AttackInfo attackInfo;
	attackInfo.hurtType = HURT_TYPE_NORMAL;
	attackInfo.addHurt = static_cast<float>(attack) * 0.4f;
	SkillControler::Instance()->doBuffHurt(caster, target, attackInfo);
	if (target->isDie()) {
		endTs_ = 0;
	}
	return true;
}
