
#ifndef _MAP_COPY_H_
#define _MAP_COPY_H_

#include "Map.h"

class MapCopy: public Map {
public:
	MapCopy();
	virtual ~MapCopy();
	virtual int addMainActor(Human *human);
	virtual int objectDie(MapMoveObject *pMo);
	virtual int objectMove(MapMoveObject *pMo);
	virtual int delObject(MapDisplayObject *obj);
	virtual int addObject(MapDisplayObject *obj);
	virtual int updateField(MapMoveObject *pMo, bool enter);
	virtual void getFieldAppear(Human *human, msgs::SMapEntityEnters *msg);
	virtual int syncFieldMsg(MapMoveObject *pMo, uint32_t cmd, Msg *msg, bool self);
	virtual void GetAroundObjects(MapMoveObject *pMo, vector<MapMoveObject *> &objs);
	virtual int destoryField(uint32_t id);
	uint32_t getFileId(MapMoveObject *pMo);
};

#endif /* _MAP_COPY_H_ */
