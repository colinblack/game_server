/*
 * BuffBless.cpp
 *
 *  Created on: 2019年8月5日
 *      Author: Administrator
 */

#include "BuffBless.h"
#include "BattleInc.h"

bool BuffBless::calcValue(const CfgSkill::Skill& cfg, const CfgSkill::Buff& bcfg) {
	id_ = cfg.id();
	value_ = cfg.has_hurtadd() ? cfg.hurtadd() : 0;
	percent_ = 0.35f;
	propType_ = AP_DEFENCE;
	return true;
}

