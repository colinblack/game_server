/*
 * BuffAddProps.cpp
 *
 *  Created on: 2019年8月6日
 *      Author: Administrator
 */

#include "BuffAddProps.h"

bool BuffAddProps::init(const CfgSkill::Skill& cfg, const CfgSkill::Buff& bcfg, MapMoveObject* caster, MapMoveObject* target) {
	if (!BuffBase::init(cfg, bcfg, caster, target)) {
		return false;
	}
	if (!calcValue(cfg, bcfg)) {
		return false;
	}
	return true;
}

bool BuffAddProps::calcValue(const CfgSkill::Skill& cfg, const CfgSkill::Buff& bcfg) {
	return true;
}

bool BuffAddProps::doEffect() {
	return true;
}

bool BuffAddProps::calcProperty(const PropertySets &role_props, PropertySets &buff_props) {
	PropertySets::const_iterator itr = role_props.find(propType_);
	if (itr == role_props.end()) {
		return false;
	}
	const Property &prop = itr->second;
	buff_props[propType_].pui += static_cast<float>(prop.pui) * percent_ + value_;
	return true;
}
