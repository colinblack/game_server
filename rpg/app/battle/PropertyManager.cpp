/*
 * PropertyManager.cpp
 *
 *  Created on: 2019年7月2日
 *      Author: Administrator
 */

#include "PropertyManager.h"
#include "BattleInc.h"

PropertyManager::PropertyManager() {
	m_uids.clear();
}

PropertyManager::~PropertyManager() {
	m_uids.clear();
}

bool PropertyManager::AddUser(uint32_t uid) {
	m_uids.insert(uid);
	return true;
}

void PropertyManager::onSecondTimer() {
	static set<uint32_t>::iterator itr;
	static MapManager *pMapManager = MapManager::Instance();
	uint32_t ctrl = 0;
	Human *pHuman = NULL;
	for (itr = m_uids.begin(); itr != m_uids.end() && ctrl < 1000; ++ctrl) {
		pHuman = pMapManager->getHuman(*itr);
		if (pHuman != NULL) {
			pHuman->propsCalc();
			pHuman->sendShow();
		}
		m_uids.erase(itr++);
	}
}
