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

void PropertyManager::calcFightProps(MapMoveObject *pMo, PropertySets &props) {
	props = pMo->getProps();
	PropertySets buff_props;
	BuffControler::Instance()->calcProperty(pMo, buff_props);
	PropertyCfg::showProps(pMo->getId(), 0, buff_props, "buff");
	addProps(buff_props, props);
}

void PropertyManager::addProps(const PropertySets &item, PropertySets &total) {
	for (PropertySets::const_iterator itr = item.begin(); itr != item.end(); ++itr) {
		int key = itr->first;
		const Property &prop = itr->second;
		int type = PropertyCfg::getDataType(key);
		switch (type) {
		case DT_INT:
			total[key].pi += prop.pi;
			break;
		case DT_FLOAT:
			total[key].pf += prop.pf;
			break;
		case DT_UINT:
			total[key].pui += prop.pui;
			break;
		case DT_LONG:
			total[key].pl += prop.pl;
			break;
		case DT_ULONG:
			total[key].pui += prop.pui;
			break;
		}
	}
}
