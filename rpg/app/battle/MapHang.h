/*
 * MapHang.h
 *
 *  Created on: 2019年6月14日
 *      Author: Administrator
 */

#ifndef _MAP_HANG_H_
#define _MAP_HANG_H_

#include "Map.h"

class MapHang: public Map {
public:
	MapHang();
	virtual ~MapHang();
	virtual int addMainActor(Human *human);
	virtual int objectDie(MapMoveObject *pMo);
	virtual int objectMove(MapMoveObject *pMo);
	virtual int delObject(MapDisplayObject *obj);
	virtual int addObject(MapDisplayObject *obj);
	virtual int updateField(MapMoveObject *pMo, bool enter);
	virtual int syncFieldMsg(MapMoveObject *pMo, uint32_t cmd, Msg *msg, bool self);
	virtual void GetAroundObjects(MapMoveObject *pMo, vector<MapMoveObject *> &objs);
	virtual int destoryField(uint32_t id);
	uint32_t getFileId(MapMoveObject *pMo);
};

#endif /* _MAP_HANG_H_ */
