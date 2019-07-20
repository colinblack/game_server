/*
 * MapMoveManager.cpp
 *
 *  Created on: 2019年6月19日
 *      Author: Administrator
 */

#include "MapMoveManager.h"

MapMoveManager::MapMoveManager() {
	m_move_id = 0;
}

void MapMoveManager::AddObj(MapMoveObject *pMo) {
	if (pMo == NULL) {
		return;
	}
	m_objs[pMo->getId()] = pMo;
}

void MapMoveManager::DelObj(MapMoveObject *pMo) {
	if (pMo == NULL) {
		return;
	}
	map<uint32_t, MapMoveObject*>::iterator itr = m_objs.find(pMo->getId());
	if (itr != m_objs.end()) {
		m_objs.erase(itr);
	}
}

void MapMoveManager::onTimer() {
	static map<uint32_t, MapMoveObject*>::iterator itr;
	for (itr = m_objs.begin(); itr != m_objs.end();) {
		MapMoveObject *pMo = itr->second;
		if (pMo == NULL || !pMo->moveTick()) {
			m_objs.erase(itr++);
		} else {
			++itr;
		}
	}
}

uint16_t MapMoveManager::GetMoveId() {
	return ++m_move_id;
}
