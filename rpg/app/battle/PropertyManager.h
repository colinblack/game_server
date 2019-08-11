/*
 * PropertyManager.h
 *
 *  Created on: 2019年7月2日
 *      Author: Administrator
 */

#ifndef PROPERTY_MANAGER_H_
#define PROPERTY_MANAGER_H_

#include "BattleBaseInc.h"
#include "MapMoveObject.h"

class PropertyManager: public CSingleton<PropertyManager> {
private:
	friend class CSingleton<PropertyManager>;
	PropertyManager();
	~PropertyManager();
	set<uint32_t> m_uids;

public:
	bool AddUser(uint32_t uid);
	void onSecondTimer();
	void calcFightProps(MapMoveObject *pMo, PropertySets &props);
	void addProps(const PropertySets &item, PropertySets &total);
};

#endif /* PROPERTY_MANAGER_H_ */
