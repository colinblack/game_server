/*
 * BuffFireShield.h
 *
 *  Created on: 2019年8月6日
 *      Author: Administrator
 *  烈焰神盾
 */

#ifndef BUFF_FIRE_SHIELD_H_
#define BUFF_FIRE_SHIELD_H_

#include "BuffAddProps.h"

class BuffFireShield: public BuffAddProps {
public:
	virtual bool calcValue(const CfgSkill::Skill& cfg, const CfgSkill::Buff& bcfg);
	virtual bool calcProperty(const PropertySets &role_props, PropertySets &buff_props);
};

#endif /* BUFF_FIRE_SHIELD_H_ */
