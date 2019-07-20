/*
 * MapHang.cpp
 *
 *  Created on: 2019年6月14日
 *      Author: Administrator
 */

#include "MapHang.h"
#include "BattleInc.h"

MapHang::MapHang() {
}

MapHang::~MapHang() {
}

int MapHang::addMainActor(Human *human) {
	int blockId = 0;

	m_mapObject[blockId][human->getId()] = human;
	m_humans[human->getId()] = human;
	map<unsigned, MapDisplayObject*> &field = m_curField[human->getId()];
	field.clear();

	MapManager::savePos(human);

	return R_SUCCESS;
}

int MapHang::objectDie(MapMoveObject *pMo) {
	msgs::SMapEntityLeaves msg;
	msg.clear();
	if (pMo->getRace() != RACE_HUMAN) {
		delObject(pMo);
		if (!pMo->isNeedRecove()) {
			DestoryManager::Instance()->addObject(pMo);
			msg.entityIds_.push_back(pMo->getEntityMsg());
			syncFieldMsg(pMo, CMD_MAP_LEAVES, &msg, false);
		}
		return 0;
	}

	//挂机地图，人死后，清理怪物，然人恢复。
	vector<MapDisplayObject*> dels;
	MapDisplayObject *pDo = NULL;
	map<unsigned, MapDisplayObject*> &field = m_curField[pMo->getId()];
	map<unsigned, MapDisplayObject*>::iterator itr = field.begin();
	for (; itr != field.end(); ++itr) {
		pDo = itr->second;
		if (pDo == NULL || pDo->getRace() != RACE_HUMAN) {
			dels.push_back(pDo);
		}
	}

	vector<MapDisplayObject*>::iterator dItr = dels.begin();
	for (; dItr != dels.end(); ++dItr) {
		pDo = *dItr;
		delObject(pDo);
		if (pDo != NULL) {
			DestoryManager::Instance()->addObject((MapMoveObject*)pDo);
			msg.entityIds_.push_back(pDo->getEntityMsg());
		}
	}

	if (!msg.entityIds_.empty()) {
		syncFieldMsg(pMo, CMD_MAP_LEAVES, &msg, true);
	}

	HangManager::Instance()->OnHumanDie(pMo->getId());
	CopyManager::Instance()->OnHumanDie(pMo->getId());
	pMo->doRecover();

	return 0;
}

int MapHang::objectMove(MapMoveObject *pMo) {
	return R_SUCCESS;
}

int MapHang::delObject(MapDisplayObject *obj) {
	int race = obj->getRace();
	uint32_t id = obj->getId();

	if (race == RACE_HUMAN) {
		destoryField(id);
		m_humans.erase(id);
		return R_SUCCESS;
	}

	if (race == RACE_MONSTER) {
		m_mapMonster.erase(id);
	}

	uint32_t field_id = getFileId(dynamic_cast<MapMoveObject*>(obj));
	if (field_id != 0) {
		map<unsigned, MapDisplayObject*> &field = m_curField[field_id];
		field.erase(id);
	}

	return R_SUCCESS;
}

int MapHang::addObject(MapDisplayObject *obj) {
	int blockId = 0;
	Point point;

	obj->getPos(point.x, point.y);
	int race = obj->getRace();
	if (!m_pWWMParser || !m_pWWMParser->isMoveable(point.x, point.y)) {
		error_log("can not add object at race=%d mapid=%d point[%d,%d]", race, m_mapId, point.x, point.y);
		return R_ERROR;
	}

	uint32_t field_id = getFileId(dynamic_cast<MapMoveObject*>(obj));

	map<unsigned, MapDisplayObject*> &field = m_curField[field_id];
	field[obj->getId()] = obj;

	m_mapObject[blockId][obj->getId()] = obj;

	info_log("add obj mid=%d bid=%d id=%d race=%d pos[%d,%d]", m_mapId, blockId, obj->getId(), obj->getRace(), point.x, point.y);

	if (IS_MONSTER_RACE(race)) {
		m_mapMonster[obj->getId()] = dynamic_cast<StdMonster*>(obj);
	}

	msgs::SMapEntityEnters *sel_appear = MsgPool::Instance()->GetMsg<msgs::SMapEntityEnters>();
	if (sel_appear == NULL) {
		return R_ERROR;
	}

	sel_appear->entities_.push_back(obj->doAppear());

	syncFieldMsg(dynamic_cast<MapMoveObject*>(obj), CMD_MAP_ENTERS, sel_appear, false);

	return R_SUCCESS;
}

int MapHang::updateField(MapMoveObject *pMo, bool enter) {
	return 0;
}

int MapHang::syncFieldMsg(MapMoveObject *pMo, uint32_t cmd, Msg *msg, bool self) {
	if (pMo == NULL || msg == NULL) {
		return R_ERROR;
	}

	if (pMo->getRace() == RACE_HUMAN) {
		if (self) {
			LogicManager::Instance()->SendMsg(pMo->getId(), cmd, msg);
		}
	} else {
		uint32_t uid = getFileId(pMo);
		if (uid != 0) {
			LogicManager::Instance()->SendMsg(uid, cmd, msg);
		}
	}

	return 0;
}

void MapHang::GetAroundObjects(MapMoveObject *pMo, vector<MapMoveObject *> &objs) {
	uint32_t field_id = getFileId(pMo);
	if (field_id == 0) {
		return;
	}
	map<unsigned, MapDisplayObject*> &field = m_curField[field_id];
	map<unsigned, MapDisplayObject*>::iterator itr = field.begin();
	MapMoveObject *obj = NULL;
	for (; itr != field.end(); ++itr) {
		obj = dynamic_cast<MapMoveObject*>(itr->second);
		if (obj != NULL && pMo->getForce() != obj->getForce() && pMo->getId() != obj->getId()) {
			objs.push_back(obj);
		}
	}
}

int MapHang::destoryField(uint32_t id) {
	uint32_t blockId = 0;
	map<unsigned, MapDisplayObject*> &field = m_curField[id];
	map<unsigned, MapDisplayObject*>::iterator itr = field.begin();
	for (; itr != field.end(); ++itr) {
		MapDisplayObject *pDo = itr->second;
		if (pDo != NULL) {
			MapManager::Instance()->eraseObject(pDo);
			m_mapObject[blockId].erase(pDo->getId());
			DestoryManager::Instance()->addObject(dynamic_cast<MapMoveObject*>(pDo));
		}
	}
	field.clear();
	m_curField.erase(id);
	return 0;
}

uint32_t MapHang::getFileId(MapMoveObject *pMo) {
	if (pMo->getBelong() > 0) {
		return pMo->getBelong();
	}
	if (pMo->getOwner() > 0) {
		return pMo->getOwner();
	}
	return 0;
}
