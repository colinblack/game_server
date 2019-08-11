/*
 * BuffFireShield.cpp
 *
 *  Created on: 2019年8月6日
 *      Author: Administrator
 */

#include "BuffFireShield.h"

bool BuffFireShield::calcValue(const CfgSkill::Skill& cfg, const CfgSkill::Buff& bcfg) {
	id_ = cfg.id();
	value_ = cfg.has_hurtadd() ? cfg.hurtadd() : 0;
	return true;
}

bool BuffFireShield::calcProperty(const PropertySets &role_props, PropertySets &buff_props) {
	buff_props[AP_FIXDMGPERCENT].pi = value_;
	buff_props[AP_FIXDMGMAX].pi = 140;
	return true;
}
