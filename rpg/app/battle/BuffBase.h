/*
 * BuffBase.h
 *
 *  Created on: 2019年7月30日
 *      Author: Administrator
 */

#ifndef BUFF_BASE_H_
#define BUFF_BASE_H_

#include "Kernel.h"
#include "MapMoveObject.h"

class BuffBase {
public:
	BuffBase();
	virtual ~BuffBase();
	virtual bool init(const CfgSkill::Skill& cfg, const CfgSkill::Buff& bcfg, MapMoveObject* caster, MapMoveObject* target);
	virtual bool doEffect();
	virtual bool isEnd();
	virtual bool doEnd();
	virtual bool getMsg(msgs::SBuffInfo *msg);
	virtual bool calcProperty(const PropertySets &role_props, PropertySets &buff_props);
	virtual bool getControl(uint32_t &state);
	virtual uint32_t getType();
	virtual uint32_t getTargetId();
	virtual uint32_t getCasterId();
protected:
	uint32_t id_;
	uint32_t type_;
	uint32_t endTs_;
	uint32_t count_;
	uint32_t value_;
	uint32_t caster_;
	uint32_t target_;
	uint32_t roleId_;
	float percent_;
};

#endif /* BUFF_BASE_H_ */
