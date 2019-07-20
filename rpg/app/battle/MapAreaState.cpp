/*
 * MapAreaState.cpp
 *
 *  Created on: 2013-6-5
 *      Author: Administrator
 */

#include "MapAreaState.h"
#include "BattleInc.h"

MapAreaState::MapAreaState() {
	m_mapWidth = MAX_MAP_SIZE; // width < MAX_MAP_SIZE ? width : MAX_MAP_SIZE ;
	m_mapHeight = MAX_MAP_SIZE; //height < MAX_MAP_SIZE ? height : MAX_MAP_SIZE ;
	m_haveSafeArea = false;
	m_forbidFlag = false;
}

MapAreaState::MapAreaState(int width, int height) {
	m_mapWidth = MAX_MAP_SIZE; // width < MAX_MAP_SIZE ? width : MAX_MAP_SIZE ;
	m_mapHeight = MAX_MAP_SIZE; //height < MAX_MAP_SIZE ? height : MAX_MAP_SIZE ;
	m_haveSafeArea = false;
	m_forbidFlag = false;
}

MapAreaState::~MapAreaState() {
}

bool operator ==(const MapCellState &left, const MapCellState &right) {
	return ((left.flag1 == right.flag1) && (left.flag2 == right.flag2) && (left.flag3 == right.flag3));
}

bool operator !=(const MapCellState &left, const MapCellState &right) {
	return !(left == right);
}

bool MapAreaState::init(const Json::Value &mapAreaStateConfig) {
	int iCount = mapAreaStateConfig.size();
	for (int i = 0; i < iCount; i++) {
		int beginX = mapAreaStateConfig[i]["beginX"].asInt();
		int beginY = mapAreaStateConfig[i]["beginY"].asInt();
		int endX = mapAreaStateConfig[i]["endX"].asInt() == 0 ? MAX_MAP_SIZE - 1 : mapAreaStateConfig[i]["endX"].asInt();
		int endY = mapAreaStateConfig[i]["endY"].asInt() == 0 ? MAX_MAP_SIZE - 1 : mapAreaStateConfig[i]["endY"].asInt();

		if (beginX < 0 || endX > m_mapWidth || beginY < 0 || endY > m_mapHeight) {
			return false;
		}

		int flag1 = mapAreaStateConfig[i]["flag1"].asInt();
		int flag2 = mapAreaStateConfig[i]["flag2"].asInt();
		int flag3 = mapAreaStateConfig[i]["flag3"].asInt();

		bool safeFlag = mapAreaStateConfig[i]["safeFlag"].asBool();
		// 安全复活区
		if (safeFlag) {
			m_haveSafeArea = true;
			m_safeArea.beginPoint.x = mapAreaStateConfig[i]["safeX1"].asInt();
			m_safeArea.beginPoint.y = mapAreaStateConfig[i]["safeY1"].asInt();
			m_safeArea.endPoint.x = mapAreaStateConfig[i]["safeX2"].asInt();
			m_safeArea.endPoint.y = mapAreaStateConfig[i]["safeY2"].asInt();
		}

		//  禁止使用火墙区
		if (flag3 & (1 << 18)) {
			Rect rect;
			rect.beginPoint.x = beginX;
			rect.beginPoint.y = beginY;
			rect.endPoint.x = endX;
			rect.endPoint.y = endY;
			m_vecFireWallForbid.push_back(rect);
		}

		for (int m = beginX; m <= endX; m++) {
			for (int n = beginY; n <= endY; n++) {
				m_mapCellState[m][n].flag1 |= flag1;
				m_mapCellState[m][n].flag2 |= flag2;
				m_mapCellState[m][n].flag3 |= flag3;

				if (isInCrossMonsterForbidArea(Point(m, n)) || isInCrossHumanForbidArea(Point(m, n))) {
					m_forbidFlag = true;
				}
			}
		}
	}

	return true;
}

const MapCellState *MapAreaState::getPointFlag(const Point &point) {
	if (point.x < 0 || point.x >= m_mapWidth || point.y < 0 || point.y >= m_mapHeight) {
		return NULL;
	}

	return &m_mapCellState[point.x][point.y];
}

bool MapAreaState::getSafeArea(Rect &safeArea) {
	if (m_haveSafeArea) {
		safeArea = m_safeArea;
		return true;
	}

	return false;
}

bool MapAreaState::isInMap(const Point &point) {
	return (point.x >= 0 && point.x < m_mapWidth && point.y >= 0 && point.y < m_mapHeight);

}
bool MapAreaState::isInSafeArea(const Point &point) {
	return isInMap(point) && (m_mapCellState[point.x][point.y].flag1 & 0x01);
}

bool MapAreaState::isInCrossMonsterForbidArea(const Point &point) {
	return isInMap(point) && (m_mapCellState[point.x][point.y].flag1 & MONSTER_CROSS_FORBID); //(1 << 20);
}

bool MapAreaState::isInCrossHumanForbidArea(const Point &point) {
	return isInMap(point) && (m_mapCellState[point.x][point.y].flag1 & HUMAN_CROSS_FORBID); //(1 << 19);
}

bool MapAreaState::isInSituRecoveForbidArea(const Point &point) {
	return isInMap(point) && (m_mapCellState[point.x][point.y].flag2 & SITU_RECOVE_FORBID); //(1 << 11);
}

bool MapAreaState::isInKillWithoutPunishArea(const Point &point) {
	return isInMap(point) && (m_mapCellState[point.x][point.y].flag1 & KILL_WITHOUT_PUNISH); //(1 << 17);
}

bool MapAreaState::isInTransferForbidArea(const Point &point) {
	return isInMap(point) && (m_mapCellState[point.x][point.y].flag1 & TRANSFER_FORBID); //(1 << 18);
}

bool MapAreaState::isInMineArea(const Point &point) {
	return isInMap(point) && (m_mapCellState[point.x][point.y].flag3 & MINE_ARENA);
}

bool MapAreaState::isInDieWithoutDrop(const Point &point) {
	return isInMap(point) && (m_mapCellState[point.x][point.y].flag3 & DIE_WITHOUT_DROP);
}

bool MapAreaState::isInFireWallForbidArea(const Point &point) {
	return isInMap(point) && (m_mapCellState[point.x][point.y].flag3 & FIRE_WALL_FORBID); // (1 << 18);
}

void MapAreaState::setDieWithoutPunish(const Rect &rect) {
	if (rect.beginPoint.x < 0 || rect.beginPoint.x >= m_mapWidth || rect.beginPoint.y < 0 || rect.beginPoint.y >= m_mapHeight || rect.endPoint.x < 0 || rect.endPoint.x >= m_mapWidth || rect.endPoint.y < 0 || rect.endPoint.y >= m_mapHeight) {
		return;
	}

	for (int x = rect.beginPoint.x; x <= rect.endPoint.x; ++x) {
		for (int y = rect.beginPoint.y; y <= rect.endPoint.y; ++y) {
			m_mapCellState[x][y].flag3 |= DIE_WITHOUT_DROP;
		}
	}
}

void MapAreaState::setDieWithPunish(const Rect &rect) {
	if (rect.beginPoint.x < 0 || rect.beginPoint.x >= m_mapWidth || rect.beginPoint.y < 0 || rect.beginPoint.y >= m_mapHeight || rect.endPoint.x < 0 || rect.endPoint.x >= m_mapWidth || rect.endPoint.y < 0 || rect.endPoint.y >= m_mapHeight) {
		return;
	}

	for (int x = rect.beginPoint.x; x <= rect.endPoint.x; ++x) {
		for (int y = rect.beginPoint.y; y <= rect.endPoint.y; ++y) {
			m_mapCellState[x][y].flag3 &= ~DIE_WITHOUT_DROP;
		}
	}
}

void MapAreaState::setKillWithoutPunish(const Rect &rect) {
	if (rect.beginPoint.x < 0 || rect.beginPoint.x >= m_mapWidth || rect.beginPoint.y < 0 || rect.beginPoint.y >= m_mapHeight || rect.endPoint.x < 0 || rect.endPoint.x >= m_mapWidth || rect.endPoint.y < 0 || rect.endPoint.y >= m_mapHeight) {
		return;
	}

	for (int x = rect.beginPoint.x; x <= rect.endPoint.x; ++x) {
		for (int y = rect.beginPoint.y; y <= rect.endPoint.y; ++y) {
			m_mapCellState[x][y].flag1 |= KILL_WITHOUT_PUNISH;
		}
	}
}

void MapAreaState::setKillPunish(const Rect &rect) {
	if (rect.beginPoint.x < 0 || rect.beginPoint.x >= m_mapWidth || rect.beginPoint.y < 0 || rect.beginPoint.y >= m_mapHeight || rect.endPoint.x < 0 || rect.endPoint.x >= m_mapWidth || rect.endPoint.y < 0 || rect.endPoint.y >= m_mapHeight) {
		return;
	}

	for (int x = rect.beginPoint.x; x <= rect.endPoint.x; ++x) {
		for (int y = rect.beginPoint.y; y <= rect.endPoint.y; ++y) {
			m_mapCellState[x][y].flag1 &= ~KILL_WITHOUT_PUNISH;
		}
	}
}
