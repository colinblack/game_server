/*
 * MapAreaState.h
 *
 *  Created on: 2013-6-5
 *      Author: Administrator
 */

#ifndef MAPAREASTATE_H_
#define MAPAREASTATE_H_

#include "Kernel.h"
#include "MsgDef.h"

#define MAX_MAP_SIZE 500

#define HUMAN_CROSS_FORBID 0X80000
#define MONSTER_CROSS_FORBID 0X100000
#define FIRE_WALL_FORBID 0X40000
#define MINE_ARENA 0X10000
#define DIE_WITHOUT_DROP 0X8000
#define SITU_RECOVE_FORBID 0X800
#define KILL_WITHOUT_PUNISH 0X20000
#define TRANSFER_FORBID 0X40000

//struct Point {
//	int x;
//	int y;
//	union {
//		int sceneId;
//		int entityId;
//		int npcID;
//	};
//
//	Point(int x, int y) {
//		this->x = x;
//		this->y = y;
//		sceneId = 0;
//	}
//
//	Point() : x(0), y(0), sceneId(0) {
//	}
//
//	bool operator ==(const Point &other) {
//		return ((this->x == other.x) && (this->y == other.y));
//	}
//
//	bool operator !=(const Point& other) {
//		return (this->x != other.x) || (this->y != other.y);
//	}
//};

struct Rect {
	Point beginPoint;
	Point endPoint;
};

struct MapCellState {
	int flag1;
	int flag2;
	int flag3;
	MapCellState() :
			flag1(0), flag2(0), flag3(0) {
	}

	friend bool operator ==(const MapCellState &left, const MapCellState &right);
	friend bool operator !=(const MapCellState &left, const MapCellState &right);

};

class Map;
class MapAreaState {
public:
	MapAreaState();
	MapAreaState(int width, int height);
	virtual ~MapAreaState();
	bool init(const Json::Value &value);
	const MapCellState *getPointFlag(const Point &point);

public:
	bool isInSafeArea(const Point &point);
	bool isInMineArea(const Point &pos);
	bool isInFireWallForbidArea(const Point &point);
	bool isInCrossMonsterForbidArea(const Point &point);
	bool isInCrossHumanForbidArea(const Point &point);
	bool isInSituRecoveForbidArea(const Point &point);
	bool isInKillWithoutPunishArea(const Point &point);
	bool isInTransferForbidArea(const Point &point);
	bool isInDieWithoutDrop(const Point &point);
	bool getSafeArea(Rect &safeArea);
	bool haveSafeArea() {
		return m_haveSafeArea;
	}
	const vector<Rect> &getFireWallForbidArea() {
		return m_vecFireWallForbid;
	}
	bool isInMap(const Point &point);
	void setDieWithoutPunish(const Rect &rect);
	void setDieWithPunish(const Rect &rect);

	void setKillWithoutPunish(const Rect &rect);
	void setKillPunish(const Rect &rect);
	bool getForbidFlag() {
		return m_forbidFlag;
	}
private:
	int m_mapWidth;
	int m_mapHeight;
	Rect m_safeArea;
	bool m_haveSafeArea;
	vector<Rect> m_vecFireWallForbid;
	bool m_forbidFlag;
	MapCellState m_mapCellState[MAX_MAP_SIZE][MAX_MAP_SIZE];

};

#endif /* MAPAREASTATE_H_ */
