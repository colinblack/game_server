/*
 * BuffAddHp.h
 *
 *  Created on: 2019年7月31日
 *      Author: Administrator
 */

#ifndef APP_BATTLE_BUFFADDHP_H_
#define APP_BATTLE_BUFFADDHP_H_

#include "BuffBase.h"

class BuffAddHp: public BuffBase {
public:
	virtual bool init(const CfgSkill::Skill& cfg, const CfgSkill::Buff& bcfg, MapMoveObject* caster, MapMoveObject* target);
	virtual bool doEffect();
};

#endif /* APP_BATTLE_BUFFADDHP_H_ */
