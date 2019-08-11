#include "BattleInc.h"
#include "SkillControler.h"
#include "SkillNormal.h"
#include "SkillSprint.h"
#include "SkillSummon.h"
#include "SkillRush.h"

SkillControler::SkillControler() {
	m_attackId = 0;
}

SkillControler::~SkillControler() {
}

bool SkillControler::init() {
	const CfgSkill::Skills &cfg = ConfigManager::Instance()->skill_cfg_.m_config;
	for (int i = 0; i < cfg.skills_size(); ++i) {
		initSkill(cfg.skills(i));
	}

	const CfgSkill::Skills &cfg_m = ConfigManager::Instance()->skill_monster_cfg_.m_config;
	for (int i = 0; i < cfg_m.skills_size(); ++i) {
		initSkill(cfg_m.skills(i));
	}

	return true;
}

bool SkillControler::initSkill(const CfgSkill::Skill &cfg) {
	int skill_type = getSkillType(cfg);
	if (m_mapSkillEntities.count(skill_type)) {
		return true;
	}

	SkillBase *ptr = NULL;
	switch (skill_type) {
	case SKILL_UNKNOW:
		ptr = new SkillBase();
		break;
	case SKILL_NORMAL:
		ptr = new SkillNormal();
		break;
	case SKILL_SPRINT:
		ptr = new SkillSprint();
		break;
	case SKILL_SUMMON:
		ptr = new SkillSummon();
		break;
	case SKILL_RUSH:
		ptr = new SkillRush();
		break;
	}

	if (ptr == NULL) {
		error_log("skill type is %d", skill_type);
		return false;
	}

	m_mapSkillEntities[ptr->getType()] = ptr;

	debug_log("%d", ptr->getType());

	return true;
}

bool SkillControler::doUseSkill(MapMoveObject *caster, const vector<uint32_t> &targets, const SkillUseInfo &info, const Point &cen) {
	bool ret = true;
	if (caster == NULL) {
		return false;
	}

	map<int32_t, SkillBase*>::const_iterator itr = m_mapSkillEntities.find(info.entityId);
	if (itr == m_mapSkillEntities.end()) {
		error_log("skill id error %d", info.skillId);
		return false;
	}

	SkillBase *skill_entity = itr->second;
	if (skill_entity == NULL) {
		error_log("skill id error %d", info.skillId);
		return false;
	}

	static msgs::SBeginFight skill_msg;
	skill_msg.clear();
	skill_msg.fromEntity_ = caster->getEntityMsg();
	skill_msg.skillId_ = info.skillId;
	skill_msg.centerPoint_ = cen;
	skill_msg.attackId_ = m_attackId;

	msgs::SFightUpdate hurt_update;
	static msgs::SDoFights fights_msg;
	static msgs::SDoFight fight_msg;
	fights_msg.clear();

	PropertySets hurtProps;
	MapMoveObject *pTarget = NULL;
	vector<MapMoveObject*> die_obj;
	vector<MapMoveObject*> alive_obj;
	for (vector<uint32_t>::const_iterator it = targets.begin(); it != targets.end(); ++it) {
		pTarget = MapManager::Instance()->getMoveObject(*it);
		if (!pTarget) {
			error_log("target error %u %u", *it, caster->getId());
			continue;
		}

		AttackInfo attackInfo;
		hurtProps.clear();
		hurtProps[AP_HP].pl = 0;

		skill_entity->doSkillHit(info, caster, pTarget, attackInfo);

		caculateHurt(caster, pTarget, attackInfo, hurtProps);

		if (hurtProps[AP_HP].pl != 0) {
			hurt_update.clear();
			hurt_update.updateType_ = ATTR_UPDATE_HURT;
			hurt_update.updateData_.push_back(attackInfo.hurtType);
			hurt_update.updateData_.push_back(attackInfo.addHurt);
			pTarget->addFightUpdate(hurt_update);

			ret = objectHurt(caster, pTarget, hurtProps);
			if (ret) {
				caster->setFirstAttacker(pTarget);
			}

			if (pTarget->isDie()) {
				die_obj.push_back(pTarget);
			} else {
				alive_obj.push_back(pTarget);
			}
		} else {
			alive_obj.push_back(pTarget);
		}

		skill_msg.toEntitys_.push_back(pTarget->getEntityMsg());
		caster->getFightUpdate(skill_msg.propertyUpdates_);

		fight_msg.clear();
		fight_msg.attackId_ = m_attackId;
		fight_msg.entity_ = pTarget->getEntityMsg();
		fight_msg.fromEntity_ = caster->getEntityMsg();
		fight_msg.skillId_ = info.skillId;
		pTarget->getFightUpdate(fight_msg.propertyUpdates_);
		fights_msg.doFights_.push_back(fight_msg);
	}

	++m_attackId;

	Map *pMap = MapManager::Instance()->getMapInstance(caster->getFbId(), caster->getMapId());
	if (pMap) {
		pMap->syncFieldMsg(caster, CMD_ENTITY_BEGIN_DOFIGHT, &skill_msg, true);
	}

	for (vector<MapMoveObject*>::iterator it = alive_obj.begin(); it != alive_obj.end(); ++it) {
		skill_entity->doEffect(info, caster, pTarget);
	}

	if (pMap) {
		pMap->syncFieldMsg(caster, CMD_ENTITY_DO_FIGHTS, &fights_msg, true);
	}

	for (vector<MapMoveObject*>::iterator it = die_obj.begin(); it != die_obj.end(); ++it) {
		MapMoveObject *obj = *it;
		obj->onDie();
		MapManager::Instance()->mapMoveObjectDie(caster, obj);
	}
	return true;
}

bool SkillControler::doBuffHurt(MapMoveObject *caster, MapMoveObject *target, const AttackInfo &hurt) {
	msgs::SFightUpdate hurt_update;
	PropertySets hurtProps;
	hurtProps[AP_HP].pl = 0 - hurt.addHurt;
	if (hurtProps[AP_HP].pl != 0) {
		hurt_update.clear();
		hurt_update.updateType_ = ATTR_UPDATE_HURT;
		hurt_update.updateData_.push_back(HURT_TYPE_NORMAL);
		hurt_update.updateData_.push_back(hurt.addHurt);
		target->addFightUpdate(hurt_update);
		objectHurt(caster, target, hurtProps);
	}
	msgs::SDoFights fights_msg;
	msgs::SDoFight fight_msg;

	fight_msg.clear();
	fight_msg.attackId_ = m_attackId;
	fight_msg.entity_ = target->getEntityMsg();
	fight_msg.fromEntity_ = caster->getEntityMsg();
	fight_msg.skillId_ = 0;
	target->getFightUpdate(fight_msg.propertyUpdates_);
	fights_msg.doFights_.push_back(fight_msg);

	Map *pMap = MapManager::Instance()->getMapInstance(caster->getFbId(), caster->getMapId());
	if (pMap) {
		pMap->syncFieldMsg(caster, CMD_ENTITY_DO_FIGHTS, &fights_msg, true);
	}

	if (target->isDie()) {
		target->onDie();
		MapManager::Instance()->mapMoveObjectDie(caster, target);
	}

	return true;
}

bool SkillControler::objectHurt(MapMoveObject *caster, MapMoveObject *target, const PropertySets &hurt) {
	if (!target || target->isDie()) {
		return false;
	}
	if (hurt.empty()) {
		return false;
	}
	target->onHurt(caster, hurt);
	target->doHurt(hurt);
	target->onUpdate(ATTR_UPDATE_HP);

	return true;
}

void SkillControler::caculateHurt(MapMoveObject *caster, MapMoveObject *target, AttackInfo &attackInfo, PropertySets &hurtProps) {
	if (!caster || !target) {
		return;
	}
	int hpHurt = attackInfo.addHurt;
	hurtProps[AP_HP].pl = -hpHurt;
}

const SkillBase* SkillControler::getEntity(int id) {
	map<int32_t, SkillBase*>::const_iterator itr = m_mapSkillEntities.find(id);
	if (itr == m_mapSkillEntities.end()) {
		return NULL;
	}
	return itr->second;
}

int SkillControler::getSkillType(const CfgSkill::Skill &cfg) {
	SkillCfgWrap cfgWrap;
	int skill_type = SKILL_UNKNOW;
	if (cfgWrap.IsNormal(cfg)) {
		skill_type = SKILL_NORMAL;
	} else if (cfgWrap.IsSprint(cfg)) {
		skill_type = SKILL_SPRINT;
	} else if (cfgWrap.IsSummon(cfg)) {
		skill_type = SKILL_SUMMON;
	} else if (cfgWrap.IsRush(cfg)) {
		skill_type = SKILL_RUSH;
	}
	return skill_type;
}
