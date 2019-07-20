/*
 * SpecialEntity.h
 *
 *  Created on: 2013-5-13
 *      Author: Administrator
 */

#ifndef SPECIAL_ENTITY_H_
#define SPECIAL_ENTITY_H_

#include "BattleBaseInc.h"
#include "MapDisplayObject.h"

#define SPECIAL_ENTITY_FIRE_WALL 1

class SpecialEntity: public MapDisplayObject {

public:
	SpecialEntity(unsigned short effectid,const string &name);
	virtual ~SpecialEntity();

public:
	unsigned short getEffectId();
	virtual Msg* doAppear();

protected:
	unsigned short effectid;
	string name;
};

#endif /* SPECIAL_ENTITY_H_ */
