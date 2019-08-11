/*
 * BuffControler.h
 *
 *  Created on: 2019年7月31日
 *      Author: Administrator
 */

#ifndef BUFF_CONTROLER_H_
#define BUFF_CONTROLER_H_

#include "BuffBase.h"

enum BUFF_OP {
	BUFF_ADD = 1,	//
	BUFF_REP = 2,	//
	BUFF_DEL = 3	//
};

enum BUFF_TYPE {
	BUFF_POISONED = 1,
	BUFF_DIZZY = 4,
	BUFF_ADD_HP = 17,
	BUFF_BLESS = 18,
	BUFF_FIRE_SHIELD = 32,
};

class BuffControler: public CSingleton<BuffControler> {
private:
	friend class CSingleton<BuffControler> ;
	BuffControler();
	~BuffControler();
	map<uint32_t, map<uint32_t, BuffBase*> > m_buffs;

public:
	bool addBuff(const CfgSkill::Skill& cfg, MapMoveObject* caster, MapMoveObject* target);
	bool onSecondTimer();
	BuffBase* createBuff(uint32_t type);
	bool sendMsg(uint32_t op, BuffBase* buff);
	bool sendSelf(uint32_t op, BuffBase* buff);
	bool sendAll(uint32_t op, BuffBase* buff);
	bool calcProperty(MapMoveObject *pMo, PropertySets &buff_props);
	bool getControl(MapMoveObject *pMo, uint32_t &state);
};

#endif /* BUFF_CONTROLER_H_ */
