/*
 * SpecialEntity.cpp
 *
 *  Created on: 2013-5-13
 *      Author: Administrator
 */

#include "SpecialEntity.h"
#include "BattleInc.h"

SpecialEntity::SpecialEntity(unsigned short effectid, const string &name) : effectid(effectid), name(name) {
	race_ = RACE_EFFECTS;
	idInit();
}

SpecialEntity::~SpecialEntity() {
}

unsigned short SpecialEntity::getEffectId() {
	return effectid;
}

Msg* SpecialEntity::doAppear() {
	return NULL;
}
