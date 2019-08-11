/*
 * BuffBase.cpp
 *
 *  Created on: 2019年7月30日
 *      Author: Administrator
 */

#include "BuffBase.h"
#include "BattleInc.h"

BuffBase::BuffBase() {
	id_ = 0;
	type_ = 0;
	endTs_ = 0;
	count_ = 0;
	value_ = 0;
	caster_ = 0;
	target_ = 0;
	roleId_ = 0;
	percent_ = 0;
}

BuffBase::~BuffBase() {
}

bool BuffBase::init(const CfgSkill::Skill& cfg, const CfgSkill::Buff& bcfg, MapMoveObject* caster, MapMoveObject* target) {
	id_ = bcfg.id();
	caster_ = caster->getId();
	target_ = target->getId();
	roleId_ = target->getRid();
	type_ = bcfg.type();
	if (bcfg.ts() > 0) {
		endTs_ = Time::GetGlobalTime() + bcfg.ts() / 1000;
	}
	return true;
}

bool BuffBase::doEffect() {
	return true;
}

bool BuffBase::isEnd() {
	if (endTs_ < Time::GetGlobalTime()) {
		return true;
	}
	return false;
}

bool BuffBase::doEnd() {
	return true;
}

bool BuffBase::getMsg(msgs::SBuffInfo *msg) {
	msg->clear();
	msg->buffId_ = id_;
	msg->roleId_ = roleId_;
	msg->overlay_ = 1;
	msg->count_ = 0;
	msg->endDt_ = endTs_ * 1000LL;
	msg->value_ = 0;
	return true;
}

bool BuffBase::calcProperty(const PropertySets &role_props, PropertySets &buff_props) {
	return true;
}

bool BuffBase::getControl(uint32_t &state) {
	return true;
}

uint32_t BuffBase::getType() {
	return type_;
}

uint32_t BuffBase::getTargetId() {
	return target_;
}

uint32_t BuffBase::getCasterId() {
	return caster_;
}
