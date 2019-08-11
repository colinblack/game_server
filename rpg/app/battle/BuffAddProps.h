/*
 * BuffAddProps.h
 *
 *  Created on: 2019年8月6日
 *      Author: Administrator
 */

#ifndef BUFF_ADD_PROPS_H_
#define BUFF_ADD_PROPS_H_

#include "BuffBase.h"

class BuffAddProps: public BuffBase {
public:
	virtual bool init(const CfgSkill::Skill& cfg, const CfgSkill::Buff& bcfg, MapMoveObject* caster, MapMoveObject* target);
	virtual bool calcValue(const CfgSkill::Skill& cfg, const CfgSkill::Buff& bcfg);
	virtual bool doEffect();
	virtual bool calcProperty(const PropertySets &role_props, PropertySets &buff_props);

protected:
	int propType_;
};

#endif /* BUFF_ADD_PROPS_H_ */
