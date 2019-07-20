#include "Kernel.h"
#include "WWMParser.h"
#include "MapManager.h"
#include <stdlib.h>
#include <sys/time.h>

namespace APath {

map<int, AStar*> AStar::m_astarMap;

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
		if (m_length == HEAP_MAX)
			return false;

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

AStar* AStar::getInstance(int mapId) {
	map<int, AStar*>::iterator it = m_astarMap.find(mapId);
	if (it != m_astarMap.end()) {
		return it->second;
	}

	AStar* pAStar = new AStar();
	WWMParser* pWwm = WWMParser::getInstance(MapManager::Instance()->getwwmFile(mapId));
	if (pWwm == NULL) {
		error_log("may be invalid mapid:%d", mapId);
		delete pAStar;
		return NULL;
	}

	vector<bool> vecBool;
	for (uint32_t j = 0; j < pWwm->getHeight(); ++j) {
		for (uint32_t i = 0; i < pWwm->getWidth(); ++i) {
			vecBool.push_back(pWwm->isMoveable(i, j));
		}
	}

	pAStar->Init(pWwm->getWidth(), pWwm->getHeight(), pWwm->getGridWidth(), pWwm->getGridHeight(), vecBool);

	m_astarMap[mapId] = pAStar;

	return pAStar;
}

//in map false means blocked
bool AStar::Init(int width, int height, int gwidth, int gheight, vector<bool>& map) {
	if ((unsigned) (width * height) != map.size() || gwidth == 0 || gheight == 0)
		return false;

	m_width = width;
	m_height = height;
	m_gWidth = gwidth;
	m_gHeight = gheight;
	m_map.resize(map.size());
	std::copy(map.begin(), map.end(), m_map.begin());

	return true;
}

bool AStar::isMoveable(const pos &thePos) {
	return m_map[thePos.y * m_width + thePos.x];
}

bool AStar::isMoveable(int x, int y) {
	int id = x + y * m_width;
	if (id >= 0 && static_cast<size_t>(id) < m_map.size() && m_map[id]) {
		return true;
	}
	return false;
}

//the id of startPos and endPos is not nessary
bool AStar::FindPath(pos startPos, pos endPos, list<pos>& path) {
	startPos.x /= m_gWidth;
	startPos.y /= m_gHeight;
	endPos.x /= m_gWidth;
	endPos.y /= m_gHeight;

	OpenList openList;
	CloseList closeList;
	if (!FixPos(startPos)) {
		error_log("start pos error %d %d", startPos.x, startPos.y);
		return false;
	}
	if(!FixPos(endPos)) {
		error_log("end pos error %d %d", endPos.x, endPos.y);
		return false;
	}

	startPos.id = startPos.x + startPos.y * m_width;
	endPos.id = endPos.x + endPos.y * m_width;

	//起点或者目标点不可达
//	if (!m_map[startPos.id]) {
//		error_log("start pos error %d %d", startPos.x, startPos.y);
//		return false;
//	}
//	if (!m_map[endPos.id]) {
//		error_log("end pos error %d %d", endPos.x, endPos.y);
//		return false;
//	}

	path.push_back(pos(startPos.x * m_gWidth, startPos.y * m_gHeight));

	if (CanThrough(startPos, endPos)) {
		path.push_back(pos(endPos.x * m_gWidth, endPos.y * m_gHeight));
		return true;
	}

	point curPoint(startPos, startPos, 0, endPos);

	/*******first**********/
	if (!openList.Push(curPoint))
		return false;
	/*******then**********/
	while (1) {
		/**********1**************/
		if (!openList.Pop(curPoint))
			return false;
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
				if (!openList.Push(LPoint))
					return false;
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
				if (!openList.Push(RPoint))
					return false;
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
				if (!openList.Push(UPoint))
					return false;
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
				if (!openList.Push(DPoint))
					return false;
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
				if (!openList.Push(LUPoint))
					return false;
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
				if (!openList.Push(RUPoint))
					return false;
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
				if (!openList.Push(LDPoint))
					return false;
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
				if (!openList.Push(RDPoint))
					return false;
			}
		}
	}
	/*******last**********/
	vector<pos> temp;
	while (1) {
		//temp.push_back(curPoint.me);
		temp.insert(temp.begin(), curPoint.me);
		if (curPoint.me.id == startPos.id)
			break;

		if (!closeList.count(curPoint.father.id))
			return false;
		curPoint = closeList[curPoint.father.id];
	}

	size_t idx1 = 0;
	size_t idx2 = 0;
	int ctrl = 0;
	pos p1, p2;
	while(++ctrl < 1000 && idx1 < temp.size()) {
		idx2 = idx1 + 2;
		p1 = temp[idx1];
		while(idx2 < temp.size()) {
			p2 = temp[idx2];
			if (CanThrough(p1, p2)) {
				++idx2;
				continue;
			}
			idx1 = idx2 - 1;
			path.push_back(pos(temp[idx1].x * m_gWidth, temp[idx1].y * m_gHeight));
			break;
		}
		if (idx2 == temp.size()) {
			path.push_back(pos(endPos.x * m_gWidth, endPos.y * m_gHeight));
			break;
		}
	}
	if (ctrl == 1000) {
		pos last_pos;
		if (!path.empty()) {
			last_pos.x = path.rbegin()->x;
			last_pos.y = path.rbegin()->y;
		}
		string ddlog;
		char dditem[125];
		vector<pos>::iterator log_itr = temp.begin();
		for (; log_itr != temp.end(); ++log_itr) {
			sprintf(dditem, "[%d,%d],", log_itr->x, log_itr->y);
			ddlog.append(dditem);
		}
		error_log("last pos=[%d,%d],path=%s", last_pos.x, last_pos.y, ddlog.c_str());
		return false;
	}

	//for (vector<pos>::reverse_iterator it = temp.rbegin(); it != temp.rend(); ++it)
	//	path.push_back(*it);
	return true;
}

bool AStar::CanThrough(const pos &startPos, const pos &endPos) {
	const float LIMIT = 2.938736E-39f;
	float max_value = 0xFFFFFFFF;
	float dx = endPos.x - startPos.x;
	float dy = endPos.y - startPos.y;
	if (dx * dx >= LIMIT) {
		max_value = dy / dx;
	}
	if (max_value * max_value < LIMIT) {
		max_value = LIMIT;
	}
	int nx = Math::Abs(dx) + 1;
	int step = dx < 0 ? -1 : 1;
	float x = startPos.x;
	float y = startPos.y;
	int ix = 0;
	for (ix = 0; ix < nx; ++ix) {
		x += step;
		if (dx * (endPos.x - x) > 0) {
			y = max_value * (x - startPos.x) + startPos.y;
		} else {
			x = endPos.x;
			y = endPos.y;
		}
		if (!isMoveable(pos(x, y))) {
			break;
		}
		if (!isMoveable(pos(x - 1, y))) {
			break;
		}
	}

	if (ix < nx) {
		return false;
	}

	int ny = Math::Abs(dy) + 1;
	int iy = 0;
	x = startPos.x;
	y = startPos.y;
	step = dy < 0 ? -1 : 1;
	for (iy = 0; iy < ny; ++iy) {
		y += step;
		if (dy * (endPos.y - y) > 0) {
			x = ((y - startPos.y) / max_value) + startPos.x;
		} else {
			x = endPos.x;
			y = endPos.y;
		}
		if (!isMoveable(pos(x, y))) {
			break;
		}
		if (!isMoveable(pos(x, y - 1))) {
			break;
		}
	}

	if (iy < ny) {
		return false;
	}

	return true;
}

bool AStar::FixPos(pos &p) {
	int x = p.x;
	int y = p.y;
	if (isMoveable(x, y)) {
		return true;
	}
	if (isMoveable(x - 1, y)) {
		p.x = x - 1;
		return true;
	}
	if (isMoveable(x + 1, y)) {
		p.x = x + 1;
		return true;
	}
	if (isMoveable(x, y - 1)) {
		p.y = y - 1;
		return true;
	}
	if (isMoveable(x, y + 1)) {
		p.y = y + 1;
		return true;
	}
	return false;
}

}
;

