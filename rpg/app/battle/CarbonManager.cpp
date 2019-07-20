/*
 * CarbonManager.cpp
 *
 *  Created on: 2013-5-13
 *      Author: lucky
 */

#include "CarbonManager.h"
#include "BattleInc.h"

CarbonBase *CarbonManager::getCarbon(uint32_t entityId) {
	map<uint32_t, CarbonBase*>::iterator itr = m_mapCarbon.find(entityId);
	return (itr != m_mapCarbon.end() ? itr->second : NULL);
}

bool CarbonManager::init() {
	return true;
}

bool CarbonManager::addCarbon(uint32_t fbid, Human *pHuman) {
	if (pHuman == NULL) {
		return false;
	}

	if (!canAddCarbon(fbid, pHuman)) {
		error_log("can not add carbon fbid=%u uid=%u", fbid, pHuman->getUid());
		return false;
	}

	CarbonBase *pCarbon = createCarbon(fbid);
	if (!pCarbon) {
		error_log("create carbon error fbid=%u uid=%u", fbid, pHuman->getUid());
		return false;
	}

	// 副本初始化
	if (!pCarbon->init(fbid)) {
		error_log("init carbon error fbid=%u uid=%u", fbid, pHuman->getUid());
		return false;
	}

	pCarbon->enterCarbon(pHuman);

	m_mapCarbon[pCarbon->getCarbonId()] = pCarbon;

	return true;
}

/*
 id|86|name|妖月恶魔|type|0|target_id|63|target_type|19
 id|166|name|赤月魔域|type|0|target_id|77|target_type|19
 id|180|name|宝矿洞窟|type|0|target_id|74|target_type|19
 id|206|name|天地宝窟|type|0|target_id|64|target_type|19
 id|248|name|神灯传奇|type|0|target_id|79|target_type|19
 id|340|name|古墓凶影|type|0|target_id|62|target_type|19
 id|349|name|攻城记忆|type|0|target_id|113|target_type|19
 id|355|name|屠龙传说|type|0|target_id|109|target_type|19
 id|359|name|水域显威|type|0|target_id|80|target_type|19
 id|360|name|勇斗魔龙|type|0|target_id|65|target_type|19
 id|367|name|魔剑封印|type|0|target_id|81|target_type|19
 */

bool CarbonManager::canAddCarbon(uint32_t fbId, Human *pHuman) {
	if (!pHuman) {
		error_log("human not exist");
		return false;
	}

	if (!canEnterCarbon(fbId, pHuman)) {
		return false;
	}

	return true;
}

bool CarbonManager::canEnterCarbon(uint32_t fbId, Human *pHuman) {
	return true;
}

bool CarbonManager::canHumanEnterCarbon(uint32_t fbId, Human *pHuman) {
	if (!pHuman) {
		return false;
	}
	return true;
}

CarbonBase* CarbonManager::createCarbon(uint32_t type) {
	CarbonBase *ptr = NULL;
	switch (type) {
	default:
		ptr = new CarbonBase();
	}

	return ptr;
}

bool CarbonManager::delCarbon(uint32_t entityId) {
	map<uint32_t, CarbonBase*>::iterator itr = m_mapCarbon.find(entityId);
	if (itr == m_mapCarbon.end()) {
		return false;
	}
	CarbonBase *pCarbon = itr->second;
	if (pCarbon == NULL) {
		return false;
	}

	MapManager::Instance()->destoryCarbon(entityId);

	delete pCarbon;
	m_mapCarbon.erase(entityId);

	return true;
}

bool CarbonManager::enterCarbon(Human *pHuman, uint32_t fbId) {
	if (pHuman == NULL) {
		return false;
	}

	CarbonBase* pCarbon = getCarbon(fbId);
	if (pCarbon == NULL) {
		if (!addCarbon(fbId, pHuman)) {
			return false;
		}
	} else {
		if (!pCarbon->isEverInCarbon(pHuman->getUid()) && !canHumanEnterCarbon(fbId, pHuman)) {
			error_log("can not enter fbid=%u uid=%u", fbId, pHuman->getUid());
			return false;
		}
		if (!pCarbon->enterCarbon(pHuman)) {
			return false;
		}
	}
	return true;
}

bool CarbonManager::leaveCarbon(uint32_t teamId, Human *pHuman) {
	if (!pHuman) {
		return false;
	}

	map<uint32_t, CarbonBase*>::iterator itr = m_mapCarbon.find(pHuman->getFbId());
	if (itr == m_mapCarbon.end()) {
		return false;
	}

	CarbonBase *pCarbon = itr->second;
	if (pCarbon == NULL) {
		return false;
	}

	pCarbon->doExit(pHuman);

	if (pCarbon->canRemove()) {
		delCarbon(pCarbon->getCarbonId());
	}

	pHuman->setActive(false);

	return true;
}

bool CarbonManager::actorOffLine(Human *pHuman) {
	if (!pHuman) {
		return false;
	}

	map<uint32_t, CarbonBase*>::iterator itr = m_mapCarbon.find(pHuman->getFbId());
	if (itr == m_mapCarbon.end()) {
		return false;
	}

	CarbonBase *pCarbon = itr->second;
	if (pCarbon == NULL) {
		return false;
	}

	if (!pCarbon->actorOffLine(pHuman)) {
		return false;
	}

	return true;
}

bool CarbonManager::actorLogin(uint32_t uid) {
//	onLogin(uid);
//	Human *pHuman = MapManager::Instance()->getHuman(uid);
//	if (!pHuman) {
//		error_log("human null, rid = %u", uid);
//		return false;
//	}
//	map<uint32_t, CarbonBase*>::iterator itr = m_mapCarbon.find(pHuman->getFbId());
//	if (itr == m_mapCarbon.end()) {
//		return false;
//	}
//
//	CarbonBase *pCarbon = itr->second;
//	if (pCarbon == NULL) {
//		return false;
//	}
//
//	if (!pCarbon->actorLogin(pHuman)) {
//		return false;
//	}

	return true;
}

bool CarbonManager::actorQuitTeam(uint32_t teamId, Human *pHuman) {
	return true;
}

bool CarbonManager::actorJoinTeam(Human *pHuman) {
	return true;
}

bool CarbonManager::onSecondTimer() {
	map<uint32_t, CarbonBase*>::iterator itr;
	for (itr = m_mapCarbon.begin(); itr != m_mapCarbon.end(); ++itr) {
		CarbonBase *pCarbon = itr->second;
		if (pCarbon != NULL) {
			pCarbon->onSecondTimer();
		}
	}
	return true;
}

bool CarbonManager::onCarbonResult(uint32_t fbId, uint32_t mapId, bool win) {
	Map *pMap = MapManager::Instance()->getMapInstance(fbId, mapId);
	if (pMap == NULL) {
		return false;
	}
	vector<Human*> humans;
	pMap->getHumans(humans);
	vector<Human*>::iterator itr = humans.begin();
	for (; itr != humans.end(); ++itr) {
		Human *ptr = *itr;
		if (ptr == NULL) {
			continue;
		}
	}
	return true;
}

bool CarbonManager::onMapMoveObjectDie(MapMoveObject *pMo) {
	if (pMo == NULL) {
		return false;
	}
	uint32_t fbId = pMo->getFbId();
	map<uint32_t, CarbonBase*>::iterator itr = m_mapCarbon.find(fbId);
	if (itr == m_mapCarbon.end()) {
		return false;
	}
	CarbonBase *pCarbon = itr->second;
	if (pCarbon == NULL) {
		return false;
	}
	uint32_t mapId = pCarbon->getMapId();
	Map *pMap = MapManager::Instance()->getMapInstance(fbId, mapId);
	if (pMap == NULL) {
		return false;
	}
	uint32_t leftHumanCount = pMap->getAliveHumanCount();
	uint32_t leftMonsterCount = pMap->getAliveMonsterCount();
	int race = pMo->getRace();

	if (race == RACE_HUMAN) {
		if (leftMonsterCount == 0) {
			onCarbonResult(fbId, mapId, true);
		} else if (leftHumanCount == 0) {
			onCarbonResult(fbId, mapId, false);
		}
	} else if (IS_MONSTER_RACE(race)) {
		if (leftMonsterCount == 0) {
			onCarbonResult(fbId, mapId, true);
		}
	}
	return true;
}

bool CarbonManager::isEnterTimesEnough(int32_t fbId, Human *pHuman) {
	if (pHuman) {
		return getCarbonTimes(pHuman->getUid(), fbId) > 0;
	}
	return false;
}

bool CarbonManager::doBuyEnterTimes(Human *pHuman, int32_t fubenId) {
	return false;
}

bool CarbonManager::onLogin(unsigned uid) {
	return true;
}

uint32_t CarbonManager::getCarbonTimes(uint32_t uid, byte fbId) {
	return 0;
}
