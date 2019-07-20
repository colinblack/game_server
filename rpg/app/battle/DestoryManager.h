#ifndef DESTORY_MANAGER_H_
#define DESTORY_MANAGER_H_

#include "BattleBaseInc.h"
#include "MapMoveObject.h"

class DestoryManager: public CSingleton<DestoryManager> {
private:
	friend class CSingleton<DestoryManager>;
	DestoryManager();
	list<MapMoveObject*> m_objects;
	map<uint32_t, MapMoveObject*> m_alives;
public:
	void addObject(MapMoveObject *pMo);
	void addAlive(MapMoveObject *pMo);
	void onSecondTimer();
};

#endif /* DESTORY_MANAGER_H_ */
