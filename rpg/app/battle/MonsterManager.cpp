/*
 * MonsterManager.cpp
 *
 *  Created on: 2013-5-5
 *      Author: lucky
 */

#include "BattleInc.h"
#include "MonsterManager.h"

MonsterManager::MonsterManager() {
	memset((void*) m_objs, 0, sizeof(m_objs));
	m_lastIdx = 0;
}

void MonsterManager::onSecondTimer() {
}

void MonsterManager::onTimer() {
	uint32_t last = m_lastIdx;
	uint32_t counter = 0; //处理怪物计数器
	uint32_t maxId = MapDisplayObject::maxMonsterId > ID_MONSTER_MAX ? ID_MONSTER_MAX : MapDisplayObject::maxMonsterId;
	uint32_t cur_mits = 0;
	struct timeval tv;

	do {
		MapMoveObject *pMo = m_objs[m_lastIdx];
		if (pMo != NULL && pMo->isActive()) {
			if (counter++ >= MONSTER_AI_SCAN_MONSTERS) {
				break;
			}

			pMo->doAi();

			//检测是否超时，及时让出cpu
			if (counter % 10 != 0) {
				continue;
			}

			gettimeofday(&tv, NULL);
			cur_mits = tv.tv_sec * 1000 + tv.tv_usec / 1000;
			if (cur_mits - LogicManager::GlobalMilliTime - LogicManager::StartMilliTime > MONSTER_AI_SCAN_MAX_TIME) {
				m_lastIdx = m_lastIdx + 1 > maxId ? 0 : m_lastIdx + 1;
				break;
			}
		}
		m_lastIdx = m_lastIdx + 1 > maxId ? 0 : m_lastIdx + 1;
	} while (m_lastIdx != last);
}

void MonsterManager::addObj(MapDisplayObject *pDo) {
	MapMoveObject *pMo = (MapMoveObject*)pDo;
	if (pMo == NULL || pMo->getId() >= ID_MONSTER_MAX) {
		return;
	}
	m_objs[pMo->getId()] = pMo;
}

void MonsterManager::delObj(MapDisplayObject *pDo) {
	MapMoveObject *pMo = (MapMoveObject*)pDo;
	if (pMo == NULL || pMo->getId() >= ID_MONSTER_MAX) {
		error_log("%p,%p", pMo, pDo);
		return;
	}
	m_objs[pMo->getId()] = NULL;
}

