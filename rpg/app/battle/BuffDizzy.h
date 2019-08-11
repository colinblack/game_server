/*
 * BuffDizzy.h
 *
 *  Created on: 2019年8月6日
 *      Author: Administrator
 */

#ifndef BUFF_DIZZY_H_
#define BUFF_DIZZY_H_

#include "BuffBase.h"

class BuffDizzy: public BuffBase {
public:
	virtual bool init(const CfgSkill::Skill& cfg, const CfgSkill::Buff& bcfg, MapMoveObject* caster, MapMoveObject* target);
	virtual bool getControl(uint32_t &state);
};

#endif /* BUFF_DIZZY_H_ */
