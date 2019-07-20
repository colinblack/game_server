/*
 * SkillBase.cpp
 *
 *  Created on: 2013-4-10
 *      Author: Administrator
 */

#include "SkillBase.h"
#include "BattleInc.h"

SkillBase::SkillBase() {
	m_effectFlag = 0;
	m_notAutoUse = 0;
	m_magicLock = 0;
	m_canUseOnFD = 0;
	m_canUseOnDizzy = 0;
	m_canbeDefault = 0;
	m_isDelete = 0;
	m_gainFlag = 0;
	m_maxLevel = 0;
	m_type = 0;
}

SkillBase::~SkillBase() {
}


bool SkillBase::doSkillHit(const SkillUseInfo &sinfo, MapMoveObject *caster, MapMoveObject *target, AttackInfo &ainfo) {
	return true;
}

bool SkillBase::caculateHurt(const SkillUseInfo &sinfo, MapMoveObject *caster, MapMoveObject *target, AttackInfo &ainfo) {
	return true;
}

void SkillBase::doSceneEffect(const SkillUseInfo &sinfo, MapMoveObject *caster, const vector<uint32_t> &vecTargets) {
}

void SkillBase::doActorEffect(const SkillUseInfo &sinfo, MapMoveObject *caster, const vector<uint32_t> &vecTargets) {
}

void SkillBase::doEffect(const SkillUseInfo &sinfo, MapMoveObject *caster, const vector<uint32_t> &vecTargets) {
	doSceneEffect(sinfo, caster, vecTargets);
	doActorEffect(sinfo, caster, vecTargets);
}

void SkillBase::getTargets(const SkillUseInfo &sinfo, MapMoveObject *caster, vector<uint32_t> &targets) {
}

int SkillBase::getType() const {
	return m_type;
}

int SkillBase::getMaxLevel() const {
	return m_maxLevel;
}
