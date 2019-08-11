/*
 * BuffDizzy.cpp
 *
 *  Created on: 2019年8月6日
 *      Author: Administrator
 */

#include "BuffDizzy.h"
#include "BattleInc.h"

bool BuffDizzy::init(const CfgSkill::Skill& cfg, const CfgSkill::Buff& bcfg, MapMoveObject* caster, MapMoveObject* target) {
	if (!BuffBase::init(cfg, bcfg, caster, target)) {
		return false;
	}
	endTs_ = Time::GetGlobalTime() + 10;
	return true;
}

bool BuffDizzy::getControl(uint32_t &state) {
	state |= AP_STAT_DIZZY;
	return true;
}
