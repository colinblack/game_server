/*
 * Soldier.h
 *
 *  Created on: 2016-4-14
 *      Author: Administrator
 */

#ifndef SOLDIER_H_
#define SOLDIER_H_

#include "MapObject.h"
#include "Path.h"
#include "PropertyManager.h"

class Soldier: public MapObject {
public:
	Soldier();
	~Soldier();
public:
	virtual bool encode(IBuffer* buffer);
	bool init();
	bool setData(const string& jsonData);
	bool calcProps();
	bool saveData(bool isNew = false);
	bool onUpgradeOver();
	bool packetToBattle(CBufferWriter &bWriter);
	void setPropertyManager(PropertyManager* pm) {
		m_pm = pm;
	}
	static uint32_t calcCombat(uint32_t type, uint32_t cnt);
	static bool addOrSetSoldier(uint32_t uid, Json::Value& value, bool isNew);
public:
	PropertyManager* m_pm;
};

#endif /* SOLDIER_H_ */
