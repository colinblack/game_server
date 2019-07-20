/*
 * MapMoveManager.h
 *
 *  Created on: 2019年6月19日
 *      Author: Administrator
 */

#ifndef MAP_MOVE_MANAGER_H_
#define MAP_MOVE_MANAGER_H_

#include "BattleBaseInc.h"
#include "MapMoveObject.h"

class MapMoveManager: public CSingleton<MapMoveManager> {
private:
	friend class CSingleton<MapMoveManager>;
	MapMoveManager();
	map<uint32_t, MapMoveObject*> m_objs;
	uint16_t m_move_id;

public:
	void AddObj(MapMoveObject *pMo);
	void DelObj(MapMoveObject *pMo);
	void onTimer();
	uint16_t GetMoveId();

};

#endif /* MAP_MOVE_MANAGER_H_ */
