/*
 * ZhanLingManager.cpp
 *
 *  Created on: 2019年7月20日
 *      Author: Administrator
 */

#include "ZhanLingManager.h"
#include "BattleInc.h"
#include "MapDisplayObject.h"

ZhanLingManager::ZhanLingManager() {
	m_recover.clear();
}

ZhanLingManager::~ZhanLingManager() {
	m_recover.clear();
}

bool ZhanLingManager::ActorLogin(uint32_t uid) {
	return checkUnlock(uid);
}

bool ZhanLingManager::checkUnlock(uint32_t uid) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	map<uint32_t, DataMission>::iterator itr = cache.mission_.find(ZHAN_LING_UNLOCK_MISSION);
	if (itr == cache.mission_.end()) {
		return false;
	}
	const DataMission &mission = itr->second;
	if (mission.status != MISSION_COMMIT) {
		return false;
	}
	if (cache.zhanling_.uid != 0) {
		return false;
	}
	cache.zhanling_.uid = uid;
	cache.zhanling_.nuqi = ZHAN_LING_MAX_NUQI;
	DataAttr attr;
	cache.zhanling_.ToAttr(attr);
	DataAttrManager::Instance()->Add(attr);
	SkillManager::Instance()->UnlockZhanLing(cache);
	m_recover[uid] = cache.zhanling_.nuqi;
	LogicManager::Instance()->AddSync(CMD_ZHANLING_INFO);
	return true;
}

bool ZhanLingManager::onChangeMap(uint32_t uid) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	uint32_t sub = ZHAN_LING_MAX_NUQI > cache.zhanling_.nuqi ? ZHAN_LING_MAX_NUQI - cache.zhanling_.nuqi : 0;
	if (sub < ZHAN_LING_MAX_NUQI_SUB) {
		cache.zhanling_.nuqi = ZHAN_LING_MAX_NUQI - ZHAN_LING_MAX_NUQI_SUB;
	}
	if (cache.zhanling_.nuqi < ZHAN_LING_MAX_NUQI) {
		m_recover[uid] = cache.zhanling_.nuqi;
	}
	return true;
}

bool ZhanLingManager::onSecondTimer() {
	static map<uint32_t, uint16_t>::iterator itr;
	for (itr = m_recover.begin(); itr != m_recover.end();) {
		uint16_t &nuqi = itr->second;
		if (nuqi + ZHAN_LING_MAX_NUQI_SPEED >= ZHAN_LING_MAX_NUQI) {
			nuqi = ZHAN_LING_MAX_NUQI;
			setNuQi(itr->first, nuqi);
			m_recover.erase(itr++);
			continue;
		}
		nuqi += ZHAN_LING_MAX_NUQI_SPEED;
		updateNuQi(itr->first, nuqi);
		++itr;
	}
	return true;
}

bool ZhanLingManager::setNuQi(uint32_t uid, uint32_t nuqi) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (cache.zhanling_.uid == 0) {
		return false;
	}
	cache.zhanling_.nuqi = nuqi;
	DataAttr attr;
	cache.zhanling_.ToAttr(attr);
	DataAttrManager::Instance()->Set(attr);
	updateNuQi(uid, nuqi);
	return true;
}

bool ZhanLingManager::updateNuQi(uint32_t uid, uint32_t nuqi) {
	Human *pHuman = MapManager::Instance()->getHuman(uid);
	if (pHuman == NULL) {
		return false;
	}
	msgs::SEntityUpdate msg;
	msg.clear();
	msg.entityId_ = pHuman->getEntityMsg();
	msg.updateType_ = ATTR_UPDATE_NUQI;
	msg.updateData_.push_back(nuqi);
	msg.updateData_.push_back(ZHAN_LING_MAX_NUQI_SPEED);
	LogicManager::Instance()->SendMsg(uid, CMD_PLAYER_UPDATE, &msg);
	return true;
}

bool ZhanLingManager::useNuQi(uint32_t uid) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (cache.zhanling_.uid == 0) {
		return false;
	}
	if (cache.zhanling_.nuqi < ZHAN_LING_MAX_NUQI) {
		return false;
	}
	cache.zhanling_.nuqi = 0;
	DataAttr attr;
	cache.zhanling_.ToAttr(attr);
	DataAttrManager::Instance()->Set(attr);
	m_recover[uid] = 0;
	return true;
}

int ZhanLingManager::Process(uint32_t uid, logins::SSkillCleanNuQi *req) {
	if (!useNuQi(uid)) {
		return R_ERROR;
	}
	return 0;
}

int ZhanLingManager::Sync(const UserCache &cache, uint32_t cmd, msgs::SZhanlingInfo *resp) {
	if (cache.zhanling_.uid == 0) {
		return 0;
	}
	resp->dai_ = cache.zhanling_.dai;
	resp->mission_ = cache.zhanling_.mission;
	resp->deadline_ = cache.zhanling_.deadline;
	resp->adv_ = cache.zhanling_.adv;
	LogicManager::Instance()->SendMsg(cache.uid_, cmd, resp);
	return 0;
}
