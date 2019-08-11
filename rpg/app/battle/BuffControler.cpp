/*
 * BuffControler.cpp
 *
 *  Created on: 2019年7月31日
 *      Author: Administrator
 */

#include "BuffControler.h"
#include "BattleInc.h"
#include "BuffAddHp.h"
#include "BuffPoisoned.h"
#include "BuffBless.h"
#include "BuffFireShield.h"
#include "BuffDizzy.h"

BuffControler::BuffControler() {
}

BuffControler::~BuffControler() {
}

bool BuffControler::addBuff(const CfgSkill::Skill& cfg, MapMoveObject* caster, MapMoveObject* target) {
	SkillCfgWrap cfg_warp;
	uint32_t buff_id = 0;
	BuffBase *buff = NULL;
	try {
		cfg_warp.GetBuffId(cfg, buff_id);
		const CfgSkill::Buff &bcfg = cfg_warp.GetBuff(buff_id);

		map<uint32_t, BuffBase*> &buff_info = m_buffs[target->getId()];
		map<uint32_t, BuffBase*>::iterator itr = buff_info.find(buff_id);
		if (itr != buff_info.end()) {
			return false;
		}

		buff = createBuff(bcfg.type());
		if (buff == NULL) {
			error_log("create buff error id=%u", buff_id);
			return false;
		}

		if (!buff->init(cfg, bcfg, caster, target)) {
			error_log("init buff error id=%u", buff_id);
			throw std::runtime_error("buff init error!");
		}

		buff_info[buff_id] = buff;

		sendMsg(BUFF_ADD, buff);

	} catch (const std::exception& e) {
		error_log("add buff error msg=%s", e.what());
		if (buff != NULL) {
			delete buff;
		}
		return false;
	}
	return true;
}

bool BuffControler::onSecondTimer() {
	static map<uint32_t, map<uint32_t, BuffBase*> >::iterator itr;
	static map<uint32_t, BuffBase*>::iterator it;

	for (itr = m_buffs.begin(); itr != m_buffs.end();) {
		map<uint32_t, BuffBase*> &buff_info = itr->second;
		for (it = buff_info.begin(); it != buff_info.end();) {
			BuffBase *buff = it->second;
			if (buff == NULL) {
				buff_info.erase(it++);
				continue;
			}
			buff->doEffect();
			if (buff->isEnd()) {
				buff->doEnd();
				sendMsg(BUFF_DEL, buff);
				delete buff;
				buff_info.erase(it++);
				continue;
			}
			++it;
		}
		if (buff_info.empty()) {
			m_buffs.erase(itr++);
		} else {
			++itr;
		}
	}
	return true;
}

BuffBase* BuffControler::createBuff(uint32_t type) {
	BuffBase *buff = NULL;
	switch (type) {
	case BUFF_POISONED:
		buff = new BuffPoisoned();
		break;
	case BUFF_DIZZY:
		buff = new BuffDizzy();
		break;
	case BUFF_ADD_HP:
		buff = new BuffAddHp();
		break;
	case BUFF_BLESS:
		buff = new BuffBless();
		break;
	case BUFF_FIRE_SHIELD:
		buff = new BuffFireShield();
		break;
	default:
		buff = new BuffBase();
		break;
	}
	return buff;
}

bool BuffControler::sendMsg(uint32_t op, BuffBase* buff) {
	uint32_t type = buff->getType();
	switch (type) {
	case BUFF_ADD_HP:
	case BUFF_BLESS:
	case BUFF_FIRE_SHIELD:
		sendSelf(op, buff);
		break;
	case BUFF_DIZZY:
	case BUFF_POISONED:
		sendAll(op, buff);
		break;
	}
	return true;
}

bool BuffControler::sendSelf(uint32_t op, BuffBase* buff) {
	msgs::SUpdateBuff info;
	msgs::SBuffInfo msg;
	buff->getMsg(&msg);
	info.op_ = op;
	info.buffs_.push_back(msg);
	LogicManager::Instance()->SendMsg(buff->getTargetId(), CMD_PLAYER_BUFF_UPDATE, &info);
	return true;
}

bool BuffControler::sendAll(uint32_t op, BuffBase* buff) {
	msgs::SBroadBuffInfo info;
	MapMoveObject *target = MapManager::Instance()->getMoveObject(buff->getTargetId());
	if (target == NULL) {
		error_log("target error %u", buff->getTargetId());
		return false;
	}
	MapMoveObject *caster = dynamic_cast<MapMoveObject*>(MapManager::Instance()->getMoveObject(buff->getCasterId()));
	if (caster == NULL) {
		error_log("caster error %u", buff->getCasterId());
		return false;
	}
	info.fromEntityId_ = caster->getEntityMsg();
	info.toEntityId_ = target->getEntityMsg();
	info.buffs_.op_ = op;
	msgs::SBuffInfo msg;
	buff->getMsg(&msg);
	info.buffs_.buffs_.push_back(msg);
	Map *pMap = MapManager::Instance()->getMapInstance(caster->getFbId(), caster->getMapId());
	if (pMap != NULL) {
		pMap->syncFieldMsg(caster, CMD_BROAD_BUFF_INFO, &info, true);
	} else {
		error_log("map error %u %u", caster->getFbId(), caster->getMapId());
	}
	return true;
}

bool BuffControler::calcProperty(MapMoveObject *pMo, PropertySets &buff_props) {
	if (pMo == NULL) {
		return false;
	}
	map<uint32_t, map<uint32_t, BuffBase*> >::iterator itr = m_buffs.find(pMo->getId());
	if (itr == m_buffs.end()) {
		return false;
	}
	map<uint32_t, BuffBase*> &buffs = itr->second;
	map<uint32_t, BuffBase*>::iterator it = buffs.begin();
	for (; it != buffs.end(); ++it) {
		BuffBase *buff = it->second;
		if (buff == NULL) {
			continue;
		}
		buff->calcProperty(pMo->getProps(), buff_props);
	}
	return true;
}

bool BuffControler::getControl(MapMoveObject *pMo, uint32_t &state) {
	if (pMo == NULL) {
		return false;
	}
	map<uint32_t, map<uint32_t, BuffBase*> >::iterator itr = m_buffs.find(pMo->getId());
	if (itr == m_buffs.end()) {
		return false;
	}
	map<uint32_t, BuffBase*> &buffs = itr->second;
	map<uint32_t, BuffBase*>::iterator it = buffs.begin();
	for (; it != buffs.end(); ++it) {
		BuffBase *buff = it->second;
		if (buff == NULL) {
			continue;
		}
		buff->getControl(state);
	}
	return true;
}
