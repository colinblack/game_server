/*
 * CarbonBase.cpp
 *
 *  Created on: 2013-5-14
 *      Author: lucky
 */

#include "CarbonBase.h"
#include "BattleInc.h"

CarbonBase::CarbonBase() {
	m_carbonId = 0;
	m_mapId = 0;
	m_offlineActorCount = 0;
	m_createTime = 0;
	m_monsterIndex = 0;
}

CarbonBase::~CarbonBase() {

}

bool CarbonBase::init(uint32_t fbId) {
	const CfgDungeon::DungeonItem &cfg = DungeonCfgWrap().Get(fbId);
	m_carbonId = MapManager::Instance()->createCarbon(fbId);
	m_mapId = cfg.mapid();
	if (m_carbonId == 0) {
		error_log("init carbon map failed");
		return false;
	}
	m_createTime = LogicManager::GlobalTime;
	m_offlineActorCount = 0;
	return true;
}

bool CarbonBase::canEnterCarbon(Human *pHuman) {
	return true;
}

bool CarbonBase::canAddCarbon(Human *pHuman) {
	return true;
}

bool CarbonBase::doExit(Human *pHuman) {
	if (!pHuman) {
		return false;
	}

	leaveCarbon(pHuman);
	vector<uint32_t>::iterator it = find(m_vecHumans.begin(), m_vecHumans.end(), pHuman->getUid());
	if (it == m_vecHumans.end()) {
		return false;
	}

	m_vecHumans.erase(it);
	m_mapFromPos.erase(pHuman->getUid());

	return true;
}

bool CarbonBase::onExit(Human* pHuman) {
	return leaveCarbon(pHuman);
}

bool CarbonBase::leaveCarbon(Human *pHuman) {
	if (!pHuman) {
		return false;
	}

	MapChangeInfo mapChangeInfo;
	mapChangeInfo.desFbInstanceId = 0;

	map<uint32_t, Point>::iterator posItr = m_mapFromPos.find(pHuman->getUid());
	if (posItr == m_mapFromPos.end()) {
		error_log("from pos not exist rid= %d", pHuman->getUid());

		DataLastSafeArea lastSafeArea;
		MapManager::Instance()->getLastSafeArea(pHuman->getUid(), lastSafeArea);
		mapChangeInfo.desMapId = lastSafeArea.mapId;
		mapChangeInfo.desPoint.x = lastSafeArea.x;
		mapChangeInfo.desPoint.y = lastSafeArea.y;
	} else {
		mapChangeInfo.desMapId = posItr->second.sceneId;
		mapChangeInfo.desPoint.x = posItr->second.x;
		mapChangeInfo.desPoint.y = posItr->second.y;
	}
	pHuman->doRecover();
//	MapManager::Instance()->actorChangeMap(pHuman, mapChangeInfo);

	// pet 离开副本
//	vector<StdPet *> vecStdPets;
//	if (PetManager::getInstance()->getPets(pHuman->getUid(), vecStdPets)) {
//		for (vector<StdPet *>::iterator itr = vecStdPets.begin(); itr != vecStdPets.end(); ++itr) {
//			MapManager::Instance()->actorChangeMap(*itr, mapChangeInfo);
//		}
//	}

// 通知任务系统
//	CQuestCC::getInstance()->onEnterFB(pHuman, m_carbonConfInfo.mapId);
//	pHuman->clearFlag(DIE_WITHOUT_PUNISH_FLAG | CAN_TRANSFER_FORBID_FLAG);

	return true;
}

bool CarbonBase::doDestory() {
	MapManager::Instance()->destoryCarbon(m_carbonId);
	return true;
}

bool CarbonBase::isEmpty() {
	return m_vecHumans.empty();
}

bool CarbonBase::getFromPos(uint32_t uid, Point &fromPoint) {
	map<uint32_t, Point>::iterator posItr = m_mapFromPos.find(uid);
	if (posItr == m_mapFromPos.end()) {
		return false;
	}
	fromPoint = posItr->second;
	return true;
}

bool CarbonBase::actorOffLine(Human *pHuman) {
	vector<uint32_t>::iterator it;
	if (!pHuman || (it = find(m_vecHumans.begin(), m_vecHumans.end(), pHuman->getUid())) == m_vecHumans.end()) {
		return false;
	}

	m_vecHumans.erase(it);

	++m_offlineActorCount;

	return true;
}

bool CarbonBase::actorLogin(Human *pHuman) {
	if (!pHuman) {
		return false;
	}

	if (find(m_vecHumans.begin(), m_vecHumans.end(), pHuman->getUid()) == m_vecHumans.end()) {
		m_vecHumans.push_back(pHuman->getUid());
	}

	--m_offlineActorCount;

	return true;
}

bool CarbonBase::enterCarbon(Human *pHuman) {
	uint32_t uid = pHuman->getUid();
	Point fromPos;
	pHuman->getPos(fromPos.x, fromPos.y);
	fromPos.sceneId = pHuman->getMapId();
	m_mapFromPos[uid] = fromPos;
	if (find(m_vecHumans.begin(), m_vecHumans.end(), uid) == m_vecHumans.end()) {
		m_vecHumans.push_back(uid);
	}

	MapChangeInfo mapChangeInfo;
	mapChangeInfo.desFbInstanceId = m_carbonId;
	mapChangeInfo.desMapId = m_mapId;
	mapChangeInfo.desPoint.x = fromPos.x;
	mapChangeInfo.desPoint.y = fromPos.y;
//	if (!MapManager::Instance()->actorChangeMap(pHuman, mapChangeInfo)) {
//		error_log("actorChangeMap error");
//		return false;
//	}
	pHuman->setActive(true);
	addNewMonster();
	return true;
}

bool CarbonBase::actorQuitTeam(uint32_t teamId, Human *pHuman) {
	return true;
}

bool CarbonBase::actorJoinTeam(Human *pHuman) {
	return true;
}

bool CarbonBase::isTeamEmpty(uint32_t teamId) {
//	for (vector<uint32_t>::iterator it = m_vecHumans.begin(); it != m_vecHumans.end(); ++it) {
//		Human *pHuman = MapManager::Instance()->getHuman(*it);
//		if (pHuman) {
//			if (pHuman->getTeamId() == teamId) {
//				return false;
//			}
//		}
//	}

	return true;
}

bool CarbonBase::onDestory() {
//	for (vector<uint32_t>::iterator it = m_vecHumans.begin(); it != m_vecHumans.end(); ++it) {
//		Human *pHuman = MapManager::Instance()->getHuman(*it);
//		leaveCarbon(pHuman);
//	}
	return true;
}

bool CarbonBase::onSecondTimer() {
	return true;
}

bool CarbonBase::addNewMonster() {
	return true;
}

