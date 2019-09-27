#include <stdlib.h>
#include <sys/time.h>
#include "Kernel.h"
#include "Path.h"
namespace APath {

map<uint64_t, AStarInstance> AStar::m_astarMap;
CSpinLock AStar::m_lock;
int getHG(pos start, pos end) {
	int dx = fabs(start.x - end.x);
	int dy = fabs(start.y - end.y);
	//vert
	if (dx == 0)
		return dy * 10;
	//horz
	if (dy == 0)
		return dx * 10;
	//45
	if (dx == dy)
		return dx * 14;
	//45+vert/horz
	int dmin = std::min(dx, dy);
	int dmax = std::max(dx, dy);
	int res = dmin * 14 + (dmax - dmin) * 10;
	return res;
}

bool OpenList::HasPoint(int id) {
	return m_map.count(id);
}

bool OpenList::GetPoint(int id, point &pt) {
	if (m_map.count(id)) {
		pt = m_map[id];
		return true;
	}
	return false;
}

bool OpenList::Pop(point &pt) {
	if (m_length) {
		pt = m_map[m_heap[0]];
		Remove(pt.me.id);
		return true;
	}
	return false;
}

bool OpenList::Push(point &pt) {
	if (m_map.count(pt.me.id)) {
		if (pt.g < m_map[pt.me.id].g) {
			Remove(pt.me.id);
			return Push(pt);
		} else
			return true;
	} else {
		++m_length;
		if (m_length == HEAP_MAX) {
			debug_log("length == HEAP_MAX");
			return false;
		}

		if (m_length == 1) {
			m_heap[0] = pt.me.id;
			m_map[m_heap[0]] = pt;
			m_map[m_heap[0]].index = 0;
			return true;
		}

		int i;
		for (i = m_length - 1; i > 0; i = (i - 1) >> 1) {
			if (pt.f < m_map[m_heap[(i - 1) >> 1]].f) {
				m_heap[i] = m_heap[(i - 1) >> 1];
				m_map[m_heap[i]].index = i;
			} else
				break;
		}

		m_heap[i] = pt.me.id;
		m_map[m_heap[i]] = pt;
		m_map[m_heap[i]].index = i;

		return true;
	}
	return true;
}

bool OpenList::Remove(int id) {
	if (!m_map.count(id))
		return false;

	int index = m_map[id].index;
	--m_length;
	int i, tmp;

	for (i = index; ((i << 1) + 1) < m_length; i = tmp) {
		tmp = ((i << 1) + 2 < m_length && m_map[m_heap[(i << 1) + 2]].f < m_map[m_heap[(i << 1) + 1]].f) ? (i << 1) + 2 : (i << 1) + 1;
		if (m_map[m_heap[tmp]].f < m_map[m_heap[m_length]].f) {
			m_heap[i] = m_heap[tmp];
			m_map[m_heap[i]].index = i;
		} else
			break;
	}

	m_heap[i] = m_heap[m_length];
	m_map[m_heap[i]].index = i;
	m_map.erase(id);

	return true;
}

AStarInstance * AStar::getInstance(uint64_t battleId) {
	AStarInstance * pAStarInstance = NULL;
	map<uint64_t, AStarInstance>::iterator it = m_astarMap.find(battleId);
	if (it != m_astarMap.end()) {
		pAStarInstance = &(it->second);
	}
	return pAStarInstance;
}

bool AStar::createInstance(uint64_t battleId, uint32_t mapId, list<mpoint> & wmap, list<mpoint> & lmap) {
	return false;
}

bool AStar::removeInstance(uint64_t battleId) {
	map<uint64_t, AStarInstance>::iterator it = m_astarMap.find(battleId);
	if (it != m_astarMap.end()) {
		AStar * pASTar = it->second.pASTar;
		if (pASTar) {
			delete pASTar;
			pASTar = NULL;
		}
		m_astarMap.erase(it);
		debug_log("astar count:%d", m_astarMap.size());
		return true;
	} else {
		return false;
	}
}

bool AStar::Init(uint32_t width, uint32_t height, vector<byte> & vCells) {
	m_width = width;
	m_height = height;
	m_land_map.resize(vCells.size());
	m_water_map.resize(vCells.size());
	for (uint32_t i = 0; i < vCells.size(); i++) {
		if (vCells[i] == MAP_LAND) {
			m_land_map[i] = true;
			m_water_map[i] = false;
		} else if (vCells[i] == MAP_WATER) {
			m_land_map[i] = false;
			m_water_map[i] = true;
		} else {
			m_land_map[i] = false;
			m_water_map[i] = false;
		}
	}
	debug_log("init map point count:%d", vCells.size());
	return true;
}

bool AStar::UpdatePath(list<mpoint> & wmap, list<mpoint> & lmap) {
	list<mpoint>::iterator wit;
	for (wit = wmap.begin(); wit != wmap.end(); wit++) {
		if (wit->x < m_width && wit->y < m_height) {
			m_water_map[wit->y * m_width + wit->x] = wit->isMoveable;

		}
	}
	list<mpoint>::iterator lit;
	for (lit = lmap.begin(); lit != lmap.end(); lit++) {
		if (lit->x < m_width && lit->y < m_height) {
			m_land_map[lit->y * m_width + lit->x] = lit->isMoveable;
		}
	}
	debug_log("path update map point lpoint count:%d wpoint count:%d", lmap.size(), wmap.size());

	return true;
}

bool AStar::FindPath(pos startPos, pos endPos, uint32_t type, list<pos>& path) {
	OpenList openList;
	CloseList closeList;
	startPos.id = startPos.x + startPos.y * m_width;
	endPos.id = endPos.x + endPos.y * m_width;
	vector<bool> & m_map = (type == PROF_ARMY ? m_land_map : m_water_map);
	//起点或者目标点不可达
	if (startPos.id < 0 || endPos.id < 0) {
		debug_log("path startPos.id or endPos.id < 0");
		return false;
	}
	if (!m_map[startPos.id] || !m_map[endPos.id] || startPos.id >= (int) m_map.size() || endPos.id >= (int) m_map.size()) {
		debug_log("error!start point x:%d y:%d end point x:%d y:%d startPos.id:%d endPos.id:%d m_map size:%d", startPos.x, startPos.y, endPos.x, endPos.y, startPos.id, endPos.id, m_map.size());
		if (!m_map[startPos.id]) {
			debug_log("start pos is false id:%d", startPos.id);
		}
		if (!m_map[endPos.id]) {
			debug_log("end pos is false id:%d", endPos.id);
		}
		if (startPos.id >= (int) m_map.size()) {
			debug_log("start id is too large id:%d map size:%d", startPos.id, m_map.size());
		}
		if (endPos.id >= (int) m_map.size()) {
			debug_log("end id is too large id:%d map size:%d", endPos.id, m_map.size());
		}
		return false;
	}

	point curPoint(startPos, startPos, 0, endPos);

	/*******first**********/
	if (!openList.Push(curPoint)) {
		return false;
	}
	/*******then**********/
	while (1) {
		/**********1**************/
		if (!openList.Pop(curPoint)) {

			return false;
		}
		/**********2**************/
		closeList[curPoint.me.id] = curPoint;
		/**********3:1************/
		int tx, ty, L, R, U, D, LU, RU, LD, RD;
		tx = curPoint.me.x - 1;
		ty = curPoint.me.y;
		if (tx >= 0 && tx < m_width && ty >= 0 && ty < m_height) {
			L = curPoint.me.id - 1;
			if (L == endPos.id) {
				curPoint = point(pos(L % m_width, L / m_width, L), curPoint.me, curPoint.g, endPos);
				break;
			}
			if (m_map[L] && !closeList.count(L)) {
				point LPoint = point(pos(L % m_width, L / m_width, L), curPoint.me, curPoint.g, endPos);
				if (!openList.Push(LPoint)) {
					return false;
				}

			}
		}
		/**********3:2************/
		tx = curPoint.me.x + 1;
		ty = curPoint.me.y;
		if (tx >= 0 && tx < m_width && ty >= 0 && ty < m_height) {
			R = curPoint.me.id + 1;
			if (R == endPos.id) {
				curPoint = point(pos(R % m_width, R / m_width, R), curPoint.me, curPoint.g, endPos);
				break;
			}
			if (m_map[R] && !closeList.count(R)) {
				point RPoint = point(pos(R % m_width, R / m_width, R), curPoint.me, curPoint.g, endPos);
				if (!openList.Push(RPoint)) {
					return false;
				}
			}
		}
		/**********3:3************/
		tx = curPoint.me.x;
		ty = curPoint.me.y - 1;
		if (tx >= 0 && tx < m_width && ty >= 0 && ty < m_height) {
			U = curPoint.me.id - m_width;
			if (U == endPos.id) {
				curPoint = point(pos(U % m_width, U / m_width, U), curPoint.me, curPoint.g, endPos);
				break;
			}
			if (m_map[U] && !closeList.count(U)) {
				point UPoint = point(pos(U % m_width, U / m_width, U), curPoint.me, curPoint.g, endPos);
				if (!openList.Push(UPoint)) {
					return false;
				}
			}
		}
		/**********3:4************/
		tx = curPoint.me.x;
		ty = curPoint.me.y + 1;
		if (tx >= 0 && tx < m_width && ty >= 0 && ty < m_height) {
			D = curPoint.me.id + m_width;
			if (D == endPos.id) {
				curPoint = point(pos(D % m_width, D / m_width, D), curPoint.me, curPoint.g, endPos);
				break;
			}
			if (m_map[D] && !closeList.count(D)) {
				point DPoint = point(pos(D % m_width, D / m_width, D), curPoint.me, curPoint.g, endPos);
				if (!openList.Push(DPoint)) {
					return false;
				}
			}
		}
		/**********3:5************/
		tx = curPoint.me.x - 1;
		ty = curPoint.me.y - 1;
		if (tx >= 0 && tx < m_width && ty >= 0 && ty < m_height) {
			LU = curPoint.me.id - m_width - 1;
			if (LU == endPos.id) {
				curPoint = point(pos(LU % m_width, LU / m_width, LU), curPoint.me, curPoint.g, endPos);
				break;
			}
			if (m_map[LU] && m_map[L] && m_map[U] && !closeList.count(LU)) {
				point LUPoint = point(pos(LU % m_width, LU / m_width, LU), curPoint.me, curPoint.g, endPos);
				if (!openList.Push(LUPoint)) {
					return false;
				}
			}
		}
		/**********3:6************/
		tx = curPoint.me.x + 1;
		ty = curPoint.me.y - 1;
		if (tx >= 0 && tx < m_width && ty >= 0 && ty < m_height) {
			RU = curPoint.me.id - m_width + 1;
			if (RU == endPos.id) {
				curPoint = point(pos(RU % m_width, RU / m_width, RU), curPoint.me, curPoint.g, endPos);
				break;
			}
			if (m_map[RU] && m_map[R] && m_map[U] && !closeList.count(RU)) {
				point RUPoint = point(pos(RU % m_width, RU / m_width, RU), curPoint.me, curPoint.g, endPos);
				if (!openList.Push(RUPoint)) {
					return false;
				}
			}
		}
		/**********3:7************/
		tx = curPoint.me.x - 1;
		ty = curPoint.me.y + 1;
		if (tx >= 0 && tx < m_width && ty >= 0 && ty < m_height) {
			LD = curPoint.me.id + m_width - 1;
			if (LD == endPos.id) {
				curPoint = point(pos(LD % m_width, LD / m_width, LD), curPoint.me, curPoint.g, endPos);
				break;
			}
			if (m_map[LD] && m_map[L] && m_map[D] && !closeList.count(LD)) {
				point LDPoint = point(pos(LD % m_width, LD / m_width, LD), curPoint.me, curPoint.g, endPos);
				if (!openList.Push(LDPoint)) {
					return false;
				}
			}
		}
		/**********3:8************/
		tx = curPoint.me.x + 1;
		ty = curPoint.me.y + 1;
		if (tx >= 0 && tx < m_width && ty >= 0 && ty < m_height) {
			RD = curPoint.me.id + m_width + 1;
			if (RD == endPos.id) {
				curPoint = point(pos(RD % m_width, RD / m_width, RD), curPoint.me, curPoint.g, endPos);
				break;
			}
			if (m_map[RD] && m_map[R] && m_map[D] && !closeList.count(RD)) {
				point RDPoint = point(pos(RD % m_width, RD / m_width, RD), curPoint.me, curPoint.g, endPos);
				if (!openList.Push(RDPoint)) {
					return false;
				}
			}
		}
	}
	/*******last**********/
	vector<pos> temp;
	while (1) {
		temp.push_back(curPoint.me);
		if (curPoint.me.id == startPos.id)
			break;

		if (!closeList.count(curPoint.father.id)) {
			return false;
		}
		curPoint = closeList[curPoint.father.id];
	}
	for (vector<pos>::reverse_iterator it = temp.rbegin(); it != temp.rend(); ++it)
		path.push_back(*it);
	return true;
}

}
;

