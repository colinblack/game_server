/*
 * MapAreaManager.h
 *
 *  Created on: 2013-6-5
 *      Author: Administrator
 */

#ifndef MAP_AREA_MANAGER_H_
#define MAP_AREA_MANAGER_H_

#include "BattleBaseInc.h"
#include "MapAreaState.h"

class MapAreaManager {
public:
	virtual ~MapAreaManager();
	static MapAreaManager *getInstance();
	bool init(const string &path);
	MapAreaState *getMapAreaInfo(uint32_t mapId);
private:
	MapAreaManager();
	map<uint32_t, MapAreaState *> m_mapAreaInfo;
};

#endif /* MAP_AREA_MANAGER_H_ */
