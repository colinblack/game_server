/*
 * MonsterManager.h
 *
 *  Created on: 2013-5-5
 *      Author: lucky
 */

#ifndef MONSTER_MANAGER_H_
#define MONSTER_MANAGER_H_

#include "BattleBaseInc.h"
#include "StdMonster.h"

class MonsterManager: public CSingleton<MonsterManager> {
private:
	friend class CSingleton<MonsterManager> ;
	MonsterManager();
	~MonsterManager();

public:
	void onSecondTimer();
	void onTimer();
	void addObj(MapDisplayObject *pDo);
	void delObj(MapDisplayObject *pDo);

private:
	MapMoveObject* m_objs[ID_MONSTER_MAX];
	uint32_t m_lastIdx;
};

#endif /* MONSTER_MANAGER_H_ */
