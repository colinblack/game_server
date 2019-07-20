/*
 * DestoryObjectManager.cpp
 *
 *  Created on: 2019年6月18日
 *      Author: Administrator
 */

#include "DestoryManager.h"
#include "BattleInc.h"

DestoryManager::DestoryManager() {
	m_objects.clear();
	m_alives.clear();
}

void DestoryManager::addObject(MapMoveObject *pMo) {
	if (pMo == NULL) {
		return;
	}
	map<uint32_t, MapMoveObject*>::iterator itr = m_alives.find(pMo->getId());
	if (itr != m_alives.end()) {
		m_alives.erase(itr);
	}
	m_objects.push_back(pMo);
	MapMoveManager::Instance()->DelObj(pMo);
}

void DestoryManager::addAlive(MapMoveObject *pMo) {
	if (pMo == NULL) {
		return;
	}
	m_alives[pMo->getId()] = pMo;
}

void DestoryManager::onSecondTimer() {
	short count = 0;
	MapMoveObject *pMo = NULL;
	while (++count < 1000 && !m_objects.empty()) {
		pMo = m_objects.front();
		m_objects.pop_front();
		if (pMo != NULL) {
			delete pMo;
		}
	}

	map<uint32_t, MapMoveObject*>::iterator itr = m_alives.begin();
	while (itr != m_alives.end()) {
		pMo = itr->second;
		if (pMo == NULL) {
			m_alives.erase(itr++);
		} else if (!pMo->isAlive()) {
			MapManager::Instance()->mapRemoveObject(pMo->getId());
			m_objects.push_back(pMo);
			MapMoveManager::Instance()->DelObj(pMo);
			m_alives.erase(itr++);
		} else {
			++itr;
		}
	}
}
