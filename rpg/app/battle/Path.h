#ifndef _A_PATH_H_
#define _A_PAHT_H_

#include <math.h>
#include <stdlib.h>
#include <map>
#include <vector>
#include <stdio.h>
#include <sys/time.h>

using namespace std;

namespace APath {

struct pos {
	pos() : x(0), y(0), id(0) {
	}
	pos(int x0, int y0, int id0 = 0) : x(x0), y(y0), id(id0) {
	}
	int x;
	int y;
	int id;
};

int getHG(pos start, pos end);

struct point {
	point() : h(100000), g(100000), f(200000), index(0) {
	}
	point(pos me0, pos father0, int fatherG, pos end) : me(me0), father(father0), index(0) {
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
	OpenList() : m_length(0) {
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
	static AStar* getInstance(int mapId);
	AStar() : m_width(0), m_height(0), m_gWidth(0), m_gHeight(0) {
	}
	//the id of startPos and endPos is not nessary
	bool FindPath(pos startPos, pos endPos, list<pos>& path);

	bool CanThrough(const pos &startPos, const pos &endPos);

	bool FixPos(pos &p);
private:
	~AStar() {
	}

	//in map false means blocked
	bool Init(int width, int height, int gwidth, int gheight, vector<bool>& map);
	bool isMoveable(const pos &thePos);
	bool isMoveable(int x, int y);
private:
	static map<int, AStar*> m_astarMap;
private:
	vector<bool> m_map;
	int m_width;
	int m_height;
	int m_gWidth;
	int m_gHeight;
};

}

#endif
