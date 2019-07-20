/*
 * IMap.h
 *
 *  Created on: 2013-3-11
 *      Author: Administrator
 */

#ifndef _LIP_IMAP_H_
#define _LIP_IMAP_H_

#define MAX_FIELD_HEIGHT 12
#define MAX_FIELD_WIDTH  24

#include "BattleBaseInc.h"
#include "LogicManager.h"
#include "MapAreaState.h"
#include "WWMParser.h"
#include "MapMoveObject.h"
#include "Human.h"
#include "StdMonster.h"

class Map {
public:
	Map();
	virtual ~Map();

public:
	void setFbId(uint32_t fbId);
	uint32_t getMapHeight();
	uint32_t getMapWidth();
	int32_t getGridWidth();
	int32_t getGridHeight();

public:
	virtual int addMainActor(Human *human);
	virtual int objectMove(MapMoveObject *pMo);
	virtual int objectDie(MapMoveObject *pMo);
	virtual int delObject(MapDisplayObject *obj);
	virtual int addObject(MapDisplayObject *obj);

public:
	virtual int updateField(MapMoveObject *pMo, bool enter);
	virtual int syncFieldMsg(MapMoveObject *pMo, uint32_t cmd, Msg *msg, bool self);

public:
	bool init(const string &wwm, const string &name, int mapId, int type);
	bool initAreaInfo();
	bool initMonster();
	bool initMoveAbleArena(const string &born);
	bool initTransfer(const Json::Value &value);

public:
	virtual bool isPointEmpty(const Point &point);
	virtual void getAroundHuman(MapDisplayObject *obj, vector<Human*> &vHuman);
	virtual void getAroundHuman(const Point &point, map<uint32_t, Human*> &mapHumans);
	virtual void getAroundMonsters(MapMoveObject *pMo, vector<MapMoveObject*> &vecMonsters);
	virtual void getAroundObjects(MapMoveObject *pMo, vector<MapMoveObject*> &objs);
	virtual void getHumans(vector<Human*> &vecHumans);
	virtual void getFieldAppear(Human *human, msgs::SMapEntityEnters *msg);
	virtual uint32_t getAliveHumanCount();
	virtual uint32_t getAliveMonsterCount();

public:
	bool posToBlockId(const Point &point, int &blockId);
	bool getBlocks(int blockId, vector<int> &vBlocks);
	void getAroundPoints(const Point &point, vector<Point> &vecPoints, int32_t distance = 1);
	bool getMonterBirthPoint(int zoneId, Point &point);
	bool isInMap(const Point &point);
	bool isInField(const Point &centerPoint, const Point &point);
	bool isInSafeArea(const Point &point);
	bool getForbidFlag();
	bool isInMineArea(const Point &point);
	bool isInCrossMonsterFbArea(const Point &point);
	bool isInCrossHumanFbArea(const Point &point);
	bool isInFireWallForbidArea(const Point &point);
	bool isMoveAble(const Point &point);
	void reclaimBirthPoint(int zoneId, const Point &point);

public:
	void onDestory();

protected:
	uint32_t m_mapId;
	uint32_t m_fbId;
	int32_t m_mapWidth;
	int32_t m_mapHeight;
	int32_t m_gridWidth;
	int32_t m_gridHeight;
	int32_t m_mapType;
	map<uint32_t, Human*> m_humans;
	map<uint32_t, map<uint32_t, MapDisplayObject*> > m_mapObject;   // map<blockid,map<id,MapDisplayObject>
	map<uint32_t, map<uint32_t, MapDisplayObject*> > m_curField;    // map<selfid,map<id,MapDisplayObject>
	map<uint32_t, list<Point> > m_mapMonsterAvailable;   			// map<zoneId,vector<point> >
	list<Point> m_mapBirthPoint;
	map<uint32_t, StdMonster*> m_mapMonster;  				        // map<id,StdMonster >

	string m_wwmFile;
	string m_mapName;
	MapAreaState *m_pAreaState;
	WWMParser *m_pWWMParser;
};

#endif /* IMAP_H_ */
