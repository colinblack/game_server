/*
 * BuffPoisoned.h
 *
 *  Created on: 2019年8月3日
 *      Author: Administrator
 */

#ifndef BUFF_POISONED_H_
#define BUFF_POISONED_H_

#include "BuffBase.h"

class BuffPoisoned: public BuffBase {
public:
	virtual bool init(const CfgSkill::Skill& cfg, const CfgSkill::Buff& bcfg, MapMoveObject* caster, MapMoveObject* target);
	virtual bool doEffect();
};

#endif /* BUFF_POISONED_H_ */
