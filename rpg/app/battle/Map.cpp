/*
 * Map.cpp
 *
 *  Created on: 2013-3-11
 *      Author: aaron
 */

#include "Map.h"
#include "BattleInc.h"

#define MAP_BLOCK_SIZE 15

Map::Map() {
	m_mapWidth = 0;
	m_mapHeight = 0;
	m_gridWidth = 0;
	m_gridHeight = 0;
	m_mapType = 0;
	m_mapId = 0;
	m_fbId = 0;
	m_pAreaState = NULL;
	m_pWWMParser = NULL;
}

Map::~Map() {
}

bool Map::isInField(const Point &centerPoint, const Point &point) {
	return (abs(point.x - centerPoint.x) <= MAX_FIELD_WIDTH * m_gridWidth && abs(point.y - centerPoint.y) <= MAX_FIELD_HEIGHT * m_gridHeight);
}

bool Map::posToBlockId(const Point &point, int &blockId) {
	if (point.x >= 0 && point.x < m_mapWidth * m_gridWidth && point.y >= 0 && point.y < m_mapHeight * m_gridHeight) {
		blockId = (point.y / m_gridHeight / MAP_BLOCK_SIZE) * ((m_mapWidth + (MAP_BLOCK_SIZE - 1)) / MAP_BLOCK_SIZE) + (point.x / m_gridWidth) / MAP_BLOCK_SIZE;
		return true;
	}
	return false;
}

bool Map::getBlocks(int blockId, vector<int> &vBlocks) {
	int widethBlockCount = ((m_mapWidth + (MAP_BLOCK_SIZE - 1)) / MAP_BLOCK_SIZE);
	int heightBlockCount = ((m_mapHeight + (MAP_BLOCK_SIZE - 1)) / MAP_BLOCK_SIZE);
	int blocks = widethBlockCount * heightBlockCount;
	if (blockId < 0 || blockId >= blocks) {
		error_log("blockId out of range,blockId = %d", blockId);
		return false;
	}
	vBlocks.push_back(blockId);

	if (blockId % widethBlockCount > 0 && blockId % widethBlockCount < widethBlockCount - 1 && blockId > widethBlockCount && blockId < widethBlockCount * (heightBlockCount - 1)) {
		vBlocks.push_back(blockId - 1);
		vBlocks.push_back(blockId + 1);
		vBlocks.push_back(blockId - widethBlockCount);
		vBlocks.push_back(blockId - widethBlockCount - 1);
		vBlocks.push_back(blockId - widethBlockCount + 1);
		vBlocks.push_back(blockId + widethBlockCount);
		vBlocks.push_back(blockId + widethBlockCount - 1);
		vBlocks.push_back(blockId + widethBlockCount + 1);
		return true;
	}
	// 上方
	if (blockId - widethBlockCount >= 0) {
		vBlocks.push_back(blockId - widethBlockCount);
	}
	// 下方
	if (blockId + widethBlockCount < blocks) {
		vBlocks.push_back(blockId + widethBlockCount);
	}
	// 左边
	if (blockId % widethBlockCount > 0) {
		vBlocks.push_back(blockId - 1);
	}
	// 右边
	if (blockId % widethBlockCount < widethBlockCount - 1) {
		vBlocks.push_back(blockId + 1);
	}
	// 左上
	if (blockId % widethBlockCount > 0 && blockId - widethBlockCount > 0) {
		vBlocks.push_back(blockId - widethBlockCount - 1);
	}
	// 右上
	if (blockId % widethBlockCount < widethBlockCount - 1 && blockId - widethBlockCount >= 0) {
		vBlocks.push_back(blockId - widethBlockCount + 1);
	}
	// 左下
	if (blockId % widethBlockCount > 0 && blockId + widethBlockCount < blocks) {
		vBlocks.push_back(blockId + widethBlockCount - 1);
	}
	// 右下
	if (blockId % widethBlockCount < widethBlockCount - 1 && blockId + widethBlockCount < blocks - 1) {
		vBlocks.push_back(blockId + widethBlockCount + 1);
	}

	return true;
}

void Map::setFbId(uint32_t fbId) {
	m_fbId = fbId;
}

uint32_t Map::getMapHeight() {
	return m_mapHeight;
}

uint32_t Map::getMapWidth() {
	return m_mapWidth;
}

int32_t Map::getGridWidth() {
	return m_gridWidth;
}

int32_t Map::getGridHeight() {
	return m_gridHeight;
}

bool Map::init(const string &wwm, const string &name, int mapId, int type) {
	m_mapType = type;
	m_wwmFile = wwm;
	m_mapId = mapId;
	m_mapName = name;

	m_pWWMParser = WWMParser::getInstance(m_wwmFile);
	if (m_pWWMParser == NULL) {
		error_log("get wwmInstance failed,mapfile=%s", m_wwmFile.c_str());
		return false;
	}

	m_mapWidth = m_pWWMParser->getWidth();
	m_mapHeight = m_pWWMParser->getHeight();
	m_gridWidth = m_pWWMParser->getGridWidth();
	m_gridHeight = m_pWWMParser->getGridHeight();

	if (!initMonster()) {
		error_log("init monster failed mapId = %d", m_mapId);
		return false;
	}

//	if (!initNpc(cfg.npcdata())) {
//		error_log("init npc failed mapId = %d", m_mapId);
//		return false;
//	}

//	if (!initTransfer(sceneValue["teleport"])) {
//		error_log("init transfer failed mapId = %d", m_mapId);
//		return false;
//	}

//	if (!initBirthPoint(cfg.birthpointdata())) {
//		error_log("init birth point failed mapId = %d", m_mapId);
//		return false;
//	}

	initAreaInfo();

	return true;
}

bool Map::initAreaInfo() {
	m_pAreaState = MapAreaManager::getInstance()->getMapAreaInfo(m_mapId);
	return true;
}

int Map::addMainActor(Human *pHuman) {
	int blockId = -1;
	Point point;

	pHuman->getPos(point.x, point.y);

	if (!posToBlockId(point, blockId)) {
		error_log("pos to block failed");
		return R_ERROR;
	}

	m_mapObject[blockId][pHuman->getId()] = pHuman;
	m_humans[pHuman->getId()] = pHuman;

	updateField(pHuman, true);

	//保存位置
	MapManager::savePos(pHuman);

	return R_SUCCESS;
}

bool Map::isMoveAble(const Point &point) {
	return m_pWWMParser->isMoveable(point.x, point.y);
}

bool Map::initMoveAbleArena(const string &born) {
	list<vector<float> > data;
	list<Point> points;
	Utils::Parse2DFloat(born, "},{", ",", data);
	list<vector<float> >::iterator itr = data.begin();
	for (; itr != data.end(); ++itr) {
		vector<float> &item = *itr;
		if (item.size() != 2) {
			continue;
		}
		Point pos(item[0], item[1]);
		points.push_back(pos);
	}
	debug_log("mid %u points size %u data size %u born %s", m_mapId, points.size(), data.size(), born.c_str());
	m_mapMonsterAvailable.insert(make_pair(0, points));
	return true;
}

bool Map::initTransfer(const Json::Value &teleportValue) {
	return true;
}

bool Map::initMonster() {
	return true;
}

int Map::objectMove(MapMoveObject *pMO) {
	Point srcPoint; //原来位置
	Point desPoint; // 目的位置
	Point point;
	int srcBlockId = 0;
	int desBlockId = 0;

	pMO->getPos(desPoint.x, desPoint.y);
	posToBlockId(desPoint, desBlockId);

	pMO->getLastPos(srcPoint.x, srcPoint.y);
	posToBlockId(srcPoint, srcBlockId);

	if (desBlockId != srcBlockId) {
		m_mapObject[desBlockId][pMO->getId()] = pMO;
		if (m_mapObject.find(srcBlockId) == m_mapObject.end() || m_mapObject[srcBlockId].find(pMO->getId()) == m_mapObject[srcBlockId].end()) {
			error_log("move find target failed id=%u race=%d srcPos[%d,%d,%d] desPos[%d,%d,%d]", pMO->getId(), pMO->getRace(), srcPoint.x, srcPoint.y, srcBlockId, desPoint.x, desPoint.y, desBlockId);
		} else {
			m_mapObject[srcBlockId].erase(pMO->getId());
		}
	}

	updateField(pMO, false);

	return 0;
}

int Map::updateField(MapMoveObject *pMo, bool enter) {
	if (pMo == NULL) {
		return R_ERR_PARAM;
	}
	Point currPoint;
	Point lastPoint;
	Point pointCenter;

	vector<int> vCurrBlocks;
	vector<int> vLastBlocks;
	int currBlockId = 0;
	int lastBlockId = 0;

	// 当前坐标
	pMo->getPos(currPoint.x, currPoint.y);
	posToBlockId(currPoint, currBlockId);
	getBlocks(currBlockId, vCurrBlocks);

	// 上次坐标
	pMo->getLastPos(lastPoint.x, lastPoint.y);
	posToBlockId(lastPoint, lastBlockId);
	getBlocks(lastBlockId, vLastBlocks);

	uint32_t sel_uid = pMo->getId();

	vector<uint32_t> sel_dis_appear;
	sel_dis_appear.push_back(sel_uid);

	map<unsigned, MapDisplayObject*> &sel_field = m_curField[sel_uid];

	uint32_t oth_uid = 0;

	msgs::SMapEntityEnters *oth_appear = MsgPool::Instance()->GetMsg<msgs::SMapEntityEnters>();
	if (oth_appear == NULL) {
		return R_ERROR;
	}
	msgs::SMapEntityLeaves *oth_disappear = MsgPool::Instance()->GetMsg<msgs::SMapEntityLeaves>();
	if (oth_disappear == NULL) {
		return R_ERROR;
	}

	msgs::SMapEntityEnters *sel_appear = MsgPool::Instance()->GetMsg<msgs::SMapEntityEnters>();
	if (sel_appear == NULL) {
		return R_ERROR;
	}
	sel_appear->entities_.push_back(pMo->doAppear());

	msgs::SMapEntityLeaves *sel_disappear = MsgPool::Instance()->GetMsg<msgs::SMapEntityLeaves>();
	if (sel_disappear == NULL) {
		return R_ERROR;
	}
	sel_disappear->entityIds_.push_back(pMo->getEntityMsg());

	map<uint32_t, map<uint32_t, MapDisplayObject*> >::iterator allObjsItr;
	map<uint32_t, map<uint32_t, MapDisplayObject*> >::iterator nextFieldItr;
	map<uint32_t, map<uint32_t, MapDisplayObject*> >::iterator curFieldItr;
	map<uint32_t, MapDisplayObject*>::iterator objItr;
	vector<int>::iterator blockItr;
	vector<int>::iterator lastItr;

	MapDisplayObject *pDo = NULL;
	MapMoveObject *ptrMo = NULL;

	for (blockItr = vCurrBlocks.begin(); blockItr != vCurrBlocks.end(); ++blockItr) {
		if ((lastItr = find(vLastBlocks.begin(), vLastBlocks.end(), *blockItr)) != vLastBlocks.end()) {
			vLastBlocks.erase(lastItr);
		}

		if ((allObjsItr = m_mapObject.find(*blockItr)) == m_mapObject.end()) {
			continue;
		}

		for (objItr = allObjsItr->second.begin(); objItr != allObjsItr->second.end(); ++objItr) {
			pDo = objItr->second;
			if (pDo == NULL) {
				continue;
			}

			oth_uid = pDo->getId();
			if (oth_uid == sel_uid) {
				continue;
			}

			map<unsigned, MapDisplayObject*> &oth_field = m_curField[oth_uid];

			pDo->getPos(pointCenter.x, pointCenter.y);
			if (isInField(pointCenter, currPoint)) {
				if (oth_field.find(sel_uid) == oth_field.end()) {
					oth_field[sel_uid] = pMo;
					sel_field[oth_uid] = pDo;
					if (pDo->getRace() == RACE_HUMAN) {
						// TODO ADD ME
						LogicManager::Instance()->SendMsg(pDo->getId(), CMD_MAP_ENTERS, sel_appear);
					}
					ptrMo = dynamic_cast<MapMoveObject*>(pDo);
					if (ptrMo != NULL) {
						oth_appear->entities_.push_back(ptrMo->doAppear());
					}
				}
			} else {
				debug_log("s=%u,o=%u,[%d,%d],[%d,%d]", sel_uid, oth_uid, currPoint.x, currPoint.y, pointCenter.x, pointCenter.y);
				if (oth_field.find(sel_uid) != oth_field.end()) {
					oth_field.erase(sel_uid);
					if (pDo->getRace() == RACE_HUMAN) {
						// TODO DEL ME
						LogicManager::Instance()->SendMsg(pDo->getId(), CMD_MAP_LEAVES, sel_disappear);
					}
					oth_disappear->entityIds_.push_back(pDo->getEntityMsg());
				}
				if (sel_field.find(oth_uid) != sel_field.end()) {
					sel_field.erase(oth_uid);
				}
			}
		}
	}

	for (lastItr = vLastBlocks.begin(); lastItr != vLastBlocks.end(); lastItr++) {
		if ((allObjsItr = m_mapObject.find(*lastItr)) == m_mapObject.end()) {
			continue;
		}

		for (objItr = allObjsItr->second.begin(); objItr != allObjsItr->second.end(); ++objItr) {
			pDo = objItr->second;
			if (pDo == NULL) {
				continue;
			}
			oth_uid = pDo->getId();
			if ((curFieldItr = m_curField.find(oth_uid)) == m_curField.end()) {
				continue;
			}

			if (curFieldItr->second.find(oth_uid) != curFieldItr->second.end()) {
				if (pDo->getRace() == RACE_HUMAN) {
					// TODO DEL ME
					LogicManager::Instance()->SendMsg(pDo->getId(), CMD_MAP_LEAVES, sel_disappear);
				}
				curFieldItr->second.erase(oth_uid);
				oth_disappear->entityIds_.push_back(pDo->getEntityMsg());
			}
		}
	}

	if (!enter && pMo->getRace() == RACE_HUMAN) {
		// TODO SYNC ME
		if (!oth_appear->entities_.empty()) {
			LogicManager::Instance()->SendMsg(sel_uid, CMD_MAP_ENTERS, oth_appear);
		}
		if (!oth_disappear->entityIds_.empty()) {
			LogicManager::Instance()->SendMsg(sel_uid, CMD_MAP_LEAVES, oth_disappear);
		}
	}

	return 0;
}

int Map::syncFieldMsg(MapMoveObject *pMo, uint32_t cmd, Msg *msg, bool self) {
	if (pMo == NULL || msg == NULL) {
		return R_ERROR;
	}
	map<unsigned, map<unsigned, MapDisplayObject*> >::iterator itr = m_curField.find(pMo->getId());
	if (itr == m_curField.end()) {
		return R_ERROR;
	}
	map<unsigned, MapDisplayObject*>::iterator objItr = itr->second.begin();
	MapDisplayObject *pDo = NULL;
	for (; objItr != itr->second.end(); ++objItr) {
		pDo = objItr->second;
		if (pDo != NULL && pDo->getRace() == RACE_HUMAN) {
			if (pDo->getId() == pMo->getId()) {
				continue;
			}
			LogicManager::Instance()->SendMsg(dynamic_cast<Human*>(pDo)->getUid(), cmd, msg);
		}
	}
	if (self && pMo->getRace() == RACE_HUMAN) {
		LogicManager::Instance()->SendMsg(dynamic_cast<Human*>(pMo)->getUid(), cmd, msg);
	}
	return 0;
}

void Map::getAroundHuman(MapDisplayObject *obj, vector<Human*> &vHuman) {
	Point point(0, 0);
	obj->getPos(point.x, point.y);
	int blockId = 0;
	vector<int> vBlocks;
	posToBlockId(point, blockId);
	getBlocks(blockId, vBlocks);
	vector<int>::iterator itr;
	map<uint32_t, MapDisplayObject*>::iterator mapItr;
	map<uint32_t, map<uint32_t, MapDisplayObject*> >::iterator allObjsItr;
	Point humanPos;
	for (itr = vBlocks.begin(); itr != vBlocks.end(); itr++) {
		if ((allObjsItr = m_mapObject.find(*itr)) == m_mapObject.end()) {
			continue;
		}

		for (mapItr = allObjsItr->second.begin(); mapItr != allObjsItr->second.end(); mapItr++) {
			mapItr->second->getPos(humanPos.x, humanPos.y);
			if (isInField(point, humanPos) && mapItr->second->getRace() == RACE_HUMAN) {
				vHuman.push_back(static_cast<Human *>(mapItr->second));
			}
		}
	}
}

void Map::getAroundHuman(const Point &point, map<uint32_t, Human*> &mapHumans) {
	int blockId = 0;
	vector<int> vBlocks;
	posToBlockId(point, blockId);
	getBlocks(blockId, vBlocks);
	vector<int>::iterator itr;
	map<uint32_t, MapDisplayObject*>::iterator mapItr;
	map<uint32_t, map<uint32_t, MapDisplayObject*> >::iterator allObjsItr;

	for (itr = vBlocks.begin(); itr != vBlocks.end(); itr++) {
		if ((allObjsItr = m_mapObject.find(*itr)) == m_mapObject.end()) {
			continue;
		}

		for (mapItr = allObjsItr->second.begin(); mapItr != allObjsItr->second.end(); mapItr++) {
			if ((mapItr->second->getRace() == RACE_HUMAN)) {
				mapHumans[mapItr->first] = static_cast<Human *>(mapItr->second);
			}
		}
	}
}

void Map::getAroundMonsters(MapMoveObject *pMo, vector<MapMoveObject*> &vecMonsters) {
	Point point;
	pMo->getPos(point.x, point.y);
	int blockId = 0;
	vector<int> vBlocks;
	posToBlockId(point, blockId);
	getBlocks(blockId, vBlocks);
	vector<int>::iterator itr;
	map<uint32_t, MapDisplayObject*>::iterator mapItr;
	map<uint32_t, map<uint32_t, MapDisplayObject*> >::iterator allObjsItr;

	for (itr = vBlocks.begin(); itr != vBlocks.end(); itr++) {
		if ((allObjsItr = m_mapObject.find(*itr)) == m_mapObject.end()) {
			continue;
		}

		for (mapItr = allObjsItr->second.begin(); mapItr != allObjsItr->second.end(); mapItr++) {
			int race = mapItr->second->getRace();
			if (race == RACE_MONSTER) {
				vecMonsters.push_back(static_cast<MapMoveObject *>(mapItr->second));
			}
		}
	}
}

void Map::getAroundObjects(MapMoveObject *pMo, vector<MapMoveObject*> &objs) {
}

int Map::delObject(MapDisplayObject *obj) {
	int blockId;
	vector<int> vBlocks;
	Point point;
	obj->getPos(point.x, point.y);
	int race = obj->getRace();
	uint32_t my_id = obj->getId();
	if (!posToBlockId(point, blockId)) {
		error_log("pos to block id failed x=%d y=%d", point.x, point.y);
		return R_ERR_DATA;
	}

	static map<uint32_t, map<uint32_t, MapDisplayObject*> >::iterator allObjsItr;
	static map<uint32_t, MapDisplayObject *>::iterator mapItr;

	if ((allObjsItr = m_mapObject.find(blockId)) == m_mapObject.end()
	|| (mapItr = allObjsItr->second.find(my_id)) == allObjsItr->second.end()) {
		error_log("object not exist id=%u race=%d", my_id, obj->getRace());
		return R_ERR_DATA;
	}

	allObjsItr->second.erase(my_id);
	if (race == RACE_HUMAN) {
		m_curField.erase(my_id);
		m_humans.erase(my_id);
	} else if (race == RACE_MONSTER) {
		m_mapMonster.erase(my_id);
	}

	// 更新周围玩家视野
	if (!getBlocks(blockId, vBlocks)) {
		error_log("get blocks id failed x=%d y=%d blockId=%d", point.x, point.y, blockId);
		return R_ERR_DATA;
	}

	msgs::SMapEntityLeaves *sel_disappear = MsgPool::Instance()->GetMsg<msgs::SMapEntityLeaves>();
	if (sel_disappear == NULL) {
		return R_ERROR;
	}
	sel_disappear->entityIds_.push_back(obj->getEntityMsg());

	msgs::SMapEntityLeaves *oth_disappear = MsgPool::Instance()->GetMsg<msgs::SMapEntityLeaves>();
	if (oth_disappear == NULL) {
		return R_ERROR;
	}

	MapDisplayObject *pDo = NULL;
	map<uint32_t, map<uint32_t, MapDisplayObject*> >::iterator curFieldItr;
	for (vector<int>::iterator itr = vBlocks.begin(); itr != vBlocks.end(); itr++) {
		if ((allObjsItr = m_mapObject.find(*itr)) == m_mapObject.end()) {
			continue;
		}

		for (mapItr = allObjsItr->second.begin(); mapItr != allObjsItr->second.end(); mapItr++) {
			pDo = mapItr->second;
			if (pDo == NULL) {
				continue;
			}
			m_curField[pDo->getId()].erase(my_id);
			if (pDo->getRace() == RACE_HUMAN) {
				//TODO del me
				LogicManager::Instance()->SendMsg(pDo->getId(), CMD_MAP_LEAVES, sel_disappear);
			}
			oth_disappear->entityIds_.push_back(pDo->getEntityMsg());
		}
	}
	if (obj->getRace() == RACE_HUMAN) {
		//TODO del oth
		if (!oth_disappear->entityIds_.empty()) {
			LogicManager::Instance()->SendMsg(obj->getId(), CMD_MAP_LEAVES, oth_disappear);
		}
		msgs::SRoleLeaveMap *my_msg = MsgPool::Instance()->GetMsg<msgs::SRoleLeaveMap>();
		my_msg->entityId_ = obj->getEntityMsg();
		LogicManager::Instance()->SendMsg(obj->getId(), CMD_ROLE_LEAVE_MAP, my_msg);
	}
	return 0;
}

int Map::objectDie(MapMoveObject *pMo) {
	if (pMo->getRace() != RACE_HUMAN) {
		delObject(pMo);
		if (!pMo->isNeedRecove()) {
			DestoryManager::Instance()->addObject(pMo);
		}
		return 0;
	}
	info_log("object die id=%u mapid=%u race=%d", pMo->getId(), pMo->getMapId(), pMo->getRace());
	return 0;
}

int Map::addObject(MapDisplayObject *obj) {
	int blockId = -1;
	Point point;

	obj->getPos(point.x, point.y);
	int race = obj->getRace();
	if (!m_pWWMParser || !m_pWWMParser->isMoveable(point.x, point.y)) {
		error_log("can not add object at race=%d mapid=%d point[%d,%d]", race, m_mapId, point.x, point.y);
		return R_ERROR;
	}

	if (!posToBlockId(point, blockId)) {
		error_log("pos to block id failed x=%d y=%d mapId=%d", point.x, point.y, m_mapId);
		return R_ERROR;
	}

	m_mapObject[blockId][obj->getId()] = obj;

	info_log("add obj mid=%d bid=%d id=%d race=%d pos[%d,%d]", m_mapId, blockId, obj->getId(), obj->getRace(), point.x, point.y);

	if (IS_MONSTER_RACE(race)) {
		m_mapMonster[obj->getId()] = dynamic_cast<StdMonster*>(obj);
	}

	MapMoveObject *pMo = dynamic_cast<MapMoveObject*>(obj);
	if (pMo != NULL) {
		updateField(pMo, true);
	}

	return R_SUCCESS;
}

void Map::getFieldAppear(Human *human, msgs::SMapEntityEnters *msg) {
	map<unsigned, map<unsigned, MapDisplayObject*> >::iterator curFieldItr;
	if ((curFieldItr = m_curField.find(human->getId())) != m_curField.end()) {
		map<unsigned, MapDisplayObject*>::iterator mapItr = curFieldItr->second.begin();
		for (; mapItr != curFieldItr->second.end(); ++mapItr) {
			MapDisplayObject *pDo = mapItr->second;
			if (pDo == NULL) {
				continue;
			}
			if (pDo->getRace() == RACE_HUMAN && dynamic_cast<Human*>(pDo)->getUid() == human->getUid()) {
				continue;
			}
			msg->entities_.push_back(pDo->doAppear());
		}
	}
}

void Map::getHumans(vector<Human*> &vecHumans) {
	for (map<uint32_t, Human*>::iterator itr = m_humans.begin(); itr != m_humans.end(); ++itr) {
		vecHumans.push_back(itr->second);
	}
}

bool Map::isPointEmpty(const Point &point) {
	vector<int> vecBlocks;
	int blockId;
	if (!posToBlockId(point, blockId)) {
		return false;
	}

	Point targetPoint;
	map<uint32_t, map<uint32_t, MapDisplayObject*> >::iterator allObjsItr;

	if ((allObjsItr = m_mapObject.find(blockId)) == m_mapObject.end()) {
		return false;
	}

	for (map<uint32_t, MapDisplayObject*>::iterator mapItr = allObjsItr->second.begin(); mapItr != allObjsItr->second.end(); mapItr++) {
		mapItr->second->getPos(targetPoint.x, targetPoint.y);
		if (targetPoint == point) {
			return false;
		}
	}

	return true;
}

bool Map::isInMap(const Point &point) {
	return ((point.x >= 0) && (point.x <= m_mapWidth * m_gridWidth) && (point.y >= 0) && (point.y <= m_mapHeight * m_gridHeight));
}

bool Map::isInSafeArea(const Point &point) {
	return (m_pAreaState && m_pAreaState->isInSafeArea(point));
}

bool Map::isInMineArea(const Point &point) {
	return (m_pAreaState && m_pAreaState->isInMineArea(point));
}

bool Map::getForbidFlag() {
	return (m_pAreaState && m_pAreaState->getForbidFlag());
}

bool Map::isInFireWallForbidArea(const Point &point) {
	return (m_pAreaState && m_pAreaState->isInFireWallForbidArea(point));

}

bool Map::isInCrossMonsterFbArea(const Point &point) {
	return (m_pAreaState && m_pAreaState->isInCrossMonsterForbidArea(point));
}

bool Map::isInCrossHumanFbArea(const Point &point) {
	return (m_pAreaState && m_pAreaState->isInCrossHumanForbidArea(point));
}

void Map::getAroundPoints(const Point &point, vector<Point> &vecPoints, int32_t distance) {
	if (distance < 0 || !isInMap(point)) {
		return;
	}
	if (!m_pWWMParser) {
		error_log("get wwmInstance failed,mapfile=%s", m_wwmFile.c_str());
		return;
	}

	Point tmpPoint;
	for (int dis = 1; dis <= distance; dis++) {
		for (tmpPoint.x = point.x - dis; tmpPoint.x <= point.x + dis; ++tmpPoint.x) {
			if (tmpPoint.x == point.x - dis || tmpPoint.x == point.x + dis) {
				for (tmpPoint.y = point.y - dis; tmpPoint.y <= point.y + dis; ++tmpPoint.y) {

					if (m_pWWMParser->isMoveable(tmpPoint.x, tmpPoint.y)) {
						vecPoints.push_back(tmpPoint);
					}
				}
			} else {
				tmpPoint.y = point.y - dis;
				if (m_pWWMParser->isMoveable(tmpPoint.x, tmpPoint.y)) {
					vecPoints.push_back(tmpPoint);
				}

				tmpPoint.y = point.y + dis;
				if (m_pWWMParser->isMoveable(tmpPoint.x, tmpPoint.y)) {
					vecPoints.push_back(tmpPoint);
				}
			}
		}
	}

	return;
}

uint32_t Map::getAliveHumanCount() {
	uint32_t alive = 0;
	map<uint32_t, Human*>::iterator itr = m_humans.begin();
	for (; itr != m_humans.end(); ++itr) {
		Human *ptr = itr->second;
		if (ptr != NULL && !ptr->isDie()) {
			++alive;
		}
	}
	return alive;
}

uint32_t Map::getAliveMonsterCount() {
	uint32_t alive = 0;
	map<unsigned, StdMonster*>::iterator itr = m_mapMonster.begin();
	for (; itr != m_mapMonster.end(); ++itr) {
		StdMonster *ptr = itr->second;
		if (ptr != NULL && !ptr->isDie()) {
			++alive;
		}
	}
	return alive;
}

bool Map::getMonterBirthPoint(int zoneId, Point &point) {
	map<unsigned, list<Point> >::iterator itr = m_mapMonsterAvailable.find(zoneId);
	if (itr != m_mapMonsterAvailable.end() && itr->second.size() >= 1) {
		point = *(itr->second.begin());
		itr->second.pop_front();
		return true;
	}

	return false;
}

void Map::onDestory() {
	static vector<Human*> vecHumans;
	vecHumans.clear();
	map<uint32_t, map<uint32_t, MapDisplayObject*> >::iterator allItr;
	map<uint32_t, MapDisplayObject*>::iterator objItr;
	static MapDisplayObject *pDo = NULL;

	for (allItr = m_mapObject.begin(); allItr != m_mapObject.end(); ++allItr) {
		for (objItr = allItr->second.begin(); objItr != allItr->second.end(); ++objItr) {
			pDo = objItr->second;
			if (pDo == NULL) {
				continue;
			}
			int race = pDo->getRace();
			if (race == RACE_HUMAN) {
				vecHumans.push_back(dynamic_cast<Human*>(pDo));
				continue;
			} else if (race == RACE_PET) {
				//vecPets.push_back(static_cast<StdPet *>(objItr->second));
				//error_log("logic error,pet shouldn't not be here mapId = %d id=%u,ownerId=%u", m_mapId, objItr->second->getId(), static_cast<StdPet *>(objItr->second)->getOwner()->getRid());
				continue;
			}
			MapManager::Instance()->eraseObject(pDo);
			pDo->onDestory();
			delete pDo;
		}
	}

	// 地图中有人，传到安全区
	if (!vecHumans.empty()) {
		for (vector<Human*>::iterator it = vecHumans.begin(); it != vecHumans.end(); ++it) {
			DataLastSafeArea safeArea;
			MapChangeInfo mapChangeInfo;
			MapManager::Instance()->getLastSafeArea((*it)->getUid(), safeArea);
			mapChangeInfo.desFbInstanceId = safeArea.fbInstanceId;
			mapChangeInfo.desMapId = safeArea.mapId;
			mapChangeInfo.desPoint.x = safeArea.x;
			mapChangeInfo.desPoint.y = safeArea.y;
		}
	}

	// 宠物 ，传到人身边
//	if (!vecPets.empty()) {
//		for (vector<StdPet *>::iterator it = vecPets.begin(); it != vecPets.end(); ++it) {
//			(*it)->trans2Owner();
//		}
//	}
}

void Map::reclaimBirthPoint(int zoneId, const Point &point) {
	map<unsigned, list<Point> >::iterator itr = m_mapMonsterAvailable.find(zoneId);
	if (itr != m_mapMonsterAvailable.end()) {
		itr->second.push_back(point);
	}
}

