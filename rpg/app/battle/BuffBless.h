/*
 * BuffBless.h
 *
 *  Created on: 2019年8月5日
 *      Author: Administrator
 */

#ifndef BUFF_BLESS_H_
#define BUFF_BLESS_H_

#include "BuffAddProps.h"

class BuffBless: public BuffAddProps {
public:
	virtual bool calcValue(const CfgSkill::Skill& cfg, const CfgSkill::Buff& bcfg);
};

#endif /* BUFF_BLESS_H_ */
