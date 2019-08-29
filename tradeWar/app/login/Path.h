#ifndef _MAPOBJ_PATH_H_
#define _MAPOBJ_PATH_H_

#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include <map>
#include <vector>
#include <stdio.h>
#include <sys/time.h>
#include "Common.h"

using namespace std;

namespace APath {
class AStar;

struct AStarInstance {
	AStarInstance() :
			count(0), state(0), pASTar(NULL) {
	}
	uint32_t count;   //计数器
	uint32_t state;	  //当前状态
	AStar * pASTar;
};

struct pos {
	pos() :
			x(0), y(0), id(0) {
	}
	pos(int x0, int y0, int id0 = 0) :
			x(x0), y(y0), id(id0) {
	}
	int x;
	int y;
	int id;
};

struct mpoint {
	mpoint() :
			x(0), y(0), isMoveable(true) {
	}
	mpoint(int x0, int y0, bool id0 = true) :
			x(x0), y(y0), isMoveable(id0) {
	}
	int x;
	int y;
	bool isMoveable;
};

int getHG(pos start, pos end);

struct point {
	point() :
			h(100000), g(100000), f(200000), index(0) {
	}
	point(pos me0, pos father0, int fatherG, pos end) :
			me(me0), father(father0), index(0) {
		g = getHG(me0, father0) + fatherG;
		h = getHG(me0, end) * 10;
		f = g + h;
	}
	pos me;
	pos father;
	int h;
	int g;
	int f;
	int index;
};

typedef map<int, point> CloseList;

#define HEAP_MAX 10000
class OpenList {
public:
	OpenList() :
			m_length(0) {
	}
	~OpenList() {
	}
	bool Pop(point &pt);
	bool Push(point &pt);
	bool Remove(int id);
	bool GetPoint(int id, point &pt);
	bool HasPoint(int id);
private:
	map<int, point> m_map;
	int m_heap[HEAP_MAX];
	int m_length;
};

class AStar {
public:
	AStar() :
			m_width(0), m_height(0) {
	}
	static bool createInstance(uint64_t battleId, uint32_t mapId, list<mpoint> & wmap, list<mpoint> & lmap);
	static AStarInstance * getInstance(uint64_t battleId);
	static bool removeInstance(uint64_t battleId);
	bool FindPath(pos startPos, pos endPos, uint32_t type, list<pos>& path);
	bool UpdatePath(list<mpoint> & wmap, list<mpoint> & lmap);
private:
	~AStar() {
	}
	;
	bool Init(uint32_t width, uint32_t height, vector<byte> & vCells);
public:
	static CSpinLock m_lock;
private:
	static map<uint64_t, AStarInstance> m_astarMap;
private:
	vector<bool> m_water_map;
	vector<bool> m_land_map;
	int m_width;
	int m_height;
};

}
;
#endif
