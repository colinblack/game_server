#include "BattleInc.h"
#include "StdMonster.h"

StdMonster::StdMonster() {
	race_ = RACE_MONSTER;
	need_recove_ = true;
	idInit();
	entity_msg_.id_ = id_;
	entity_msg_.type_ = 2;

	m_attackRadius = 250;
	m_viewRadius = 250;
	m_holdRadius = 15;
	m_guardRadius = 250;
	m_maxRadius = 20;
	m_lastLoopMilliTime = 0;
	m_canMove = false;
	m_isActively = false;
	m_isReturn = false;
	m_type = 1;
	m_pathFlag = false;
}

StdMonster::~StdMonster() {
}

bool StdMonster::init(uint32_t id, uint32_t fbId, uint32_t mapId, const Point &p) {
	entity_id_ = id;
	fb_id_ = fbId;
	const CfgMonster::Monster &cfg = MonsterCfgWrap().Get(id);

	props_[AP_HP].pl = cfg.hp();
	props_[AP_MAXLIFE].pl = cfg.hp();
	speed_ = cfg.speed();
	level_ = cfg.level();
	move_id_ = MapMoveManager::Instance()->GetMoveId();
	props_[AP_ATTACK].pui = cfg.attack();
	props_[AP_DEFENCE].pui = cfg.defence();
	props_[AP_WUXINGDEFENSE].pui = cfg.wuxing();
	props_[AP_FIXDMGDEC].pui = cfg.fixdmgdec();
	props_[AP_DMGDEC].pui = cfg.dmgdec();
	props_[AP_CRITBREAKRATE].pui = cfg.critbreakrate();
	props_[AP_CRITBREAK].pui = cfg.critbreak();
	props_[AP_MAX_HURTPERCENT].pui = cfg.hppercent();

	map_id_ = mapId;
	x_ = p.x;
	y_ = p.y;
	bx_ = p.x;
	by_ = p.y;
	if (cfg.alive() > 0) {
		alive_time_ = LogicManager::GlobalTime + cfg.alive();
		DestoryManager::Instance()->addAlive(this);
	} else {
		alive_time_ = 0;
	}
	body_width_ = cfg.width();

	initSkill();

	return true;
}

bool StdMonster::initSkill() {
	map_skill_info_.clear();
	const CfgMonster::Monster &cfg = MonsterCfgWrap().Get(entity_id_);
	const CfgSkill::Skill &skill = SkillCfgWrap().GetById(cfg.skill());
	SkillUseInfo item;
	item.skillId = cfg.skill();
	item.skillLevel = 1;
	item.entityId = SkillControler::getSkillType(skill);
	item.cdTime = skill.cd();
	map_skill_info_[item.skillId] = item;
	return true;
}

bool StdMonster::getSceneMsg() {
	return true;
}

bool StdMonster::getMoveMsg() {
	return true;
}

bool StdMonster::onFightInfo() {
	return true;
}

bool StdMonster::recove() {
	Point birthPoint;
	if (!MapManager::Instance()->getMonsterBirthPoint(fb_id_, map_id_, zone_id_, birthPoint)) {
		return false;
	}

	ltx_ = 0;
	lty_ = 0;
//	x_ = birthPoint.x;
//	y_ = birthPoint.y;
//	bx_ = birthPoint.x;
//	by_ = birthPoint.y;
	props_[AP_HP].pl = props_[AP_MAXLIFE].pl;
	first_attacker_.Clear();
	is_active_ = false;
	hurt_map_.clear();
	m_isReturn = false;
	move_path_.clear();

	if (!MapManager::Instance()->addObject(this)) {
		MapManager::Instance()->reclaimBirthPoint(fb_id_, map_id_, zone_id_, birthPoint);
		return false;
	}

	return true;
}

void StdMonster::doMove(IBuffer* buf) {

}

/**
 * 主动攻击性怪物寻找视野范围内距离最近的目标作为第一攻击目标
 */

bool StdMonster::findTarget() {
	static MapManager* pMapManager = MapManager::Instance();
	vector<MapMoveObject*> objs;
	pMapManager->getAroundObjects(this, objs);
	if (objs.size() == 0) {
		return false;
	}

	uint32_t minDistance = 10000;
	MapMoveObject* nearestHuman = NULL;
	for (vector<MapMoveObject*>::iterator it = objs.begin(); it != objs.end(); ++it) {
		uint32_t d = getDistance(this, *it);
		MapMoveObject *pTarget = *it;
		if (d < minDistance && !pTarget->isDie() && !pTarget->getHideFlag()) {
			minDistance = d;
			nearestHuman = pTarget;
		}
	}

	if (nearestHuman != NULL && minDistance <= m_guardRadius) {
		first_attacker_.race = nearestHuman->getRace();
		first_attacker_.id = nearestHuman->getId();
		first_attacker_.lastTime = LogicManager::GlobalTime;
		first_attacker_.hurt = 0;
		return true;
	}

	return false;
}

void StdMonster::doAi() {
	static MapManager* pMapManager = MapManager::Instance();
	static PathManager* pPathManager = PathManager::Instance();

	if (isDie()) {
		is_active_ = false;
		return;
	}

	if (!m_canMove) {
		if (m_isActively) {
			if ((first_attacker_.id == 0 || LogicManager::GlobalTime - first_attacker_.lastTime > FIRST_ATTACKER_INTERVAL) && !findTarget()) {
				is_active_ = false;
				return;
			}
		}

		if (first_attacker_.id == 0) {
			is_active_ = false;
			return;
		}

		MapMoveObject *pMo = pMapManager->getObject(first_attacker_.id, first_attacker_.race);
		if (pMo == NULL || pMo->isDie()) {
			first_attacker_.id = 0;
			is_active_ = false;
			return;
		}

		if (getDistance(this, pMo) > m_attackRadius) {
			is_active_ = false;
			return;
		}

		doAttack(pMo);

	} else {
		//能移动怪物处理

		if (!m_isReturn) {
			Point targetPoint;
			if (first_attacker_.id == 0 && m_isActively == false) {
				is_active_ = false;
				return;
			}

			if (first_attacker_.id == 0) {
				if (!findTarget()) {
					//is_active_ = false;
					return;
				}
			}

			MapMoveObject *pMo = pMapManager->getObject(first_attacker_.id, first_attacker_.race);
			if (pMo == NULL) {
				m_isReturn = true;
				m_pathFlag = false;
				first_attacker_.id = 0;
				targetPoint.x = bx_;
				targetPoint.y = by_;
			} else if (pMo->isDie() || pMo->getHideFlag()) {
				m_isReturn = true;
				m_pathFlag = false;

				first_attacker_.id = 0;
				targetPoint.x = bx_;
				targetPoint.y = by_;

				Point p;
				if (move_path_.empty()) {
					p.x = x_;
					p.y = y_;
				} else {
					p.x = move_path_.rbegin()->x;
					p.y = move_path_.rbegin()->y;
				}
				pMo->addTargetPoint(p.x, p.y);
			} else {
				// 向目标靠近或者发起攻击
				if (move_path_.empty() && getDistance(this, pMo) <= m_attackRadius) {
					doAttack(pMo);
					return;
				}

				if (getDistance(this, pMo) > m_viewRadius
				|| getDistance(Point(x_, y_), Point(bx_, by_)) > m_maxRadius
				|| pMo->isDie()) {
					m_isReturn = true;
					m_pathFlag = false;
					first_attacker_.id = 0;
					targetPoint.x = bx_;
					targetPoint.y = by_;
				} else {
					pMo->getPos(targetPoint.x, targetPoint.y);
				}
			}

			if (move_path_.empty() || m_dest != targetPoint) {
				if (pathing_flag_) {
					return;
				}

				m_dest = targetPoint;
				APath::pos startPos(x_, y_);
				APath::pos endPos;
				if (m_isReturn) {
					endPos.x = bx_;
					endPos.y = by_;
				} else {
					if (!pMo->getTargetPoint(endPos.x, endPos.y)) {
						is_active_ = false;
						return;
					}

					//判断新的目标点是否比当前位置更靠近目标，如果更靠近才向这个更优的点移动
					if (move_path_.empty()) {
						Point target;
						pMo->getPos(target.x, target.y);
						if (getDistance(this, pMo) <= getDistance(target, Point(endPos.x, endPos.y))) {
							pMo->addTargetPoint(endPos.x, endPos.y);
							//is_active_ = false;
							return;
						}
					}
				}

				PathTask pathTask;
				pathTask.id = id_;
				pathTask.mapId = map_id_;
				pathTask.time = LogicManager::GlobalTime;
				pathTask.address = (void*) this;
				pathTask.start.x = x_;
				pathTask.start.y = y_;
				pathTask.end = endPos;

				pPathManager->addTask(pathTask);
				pathing_flag_ = true;
				move_path_.clear();
				debug_log("find path x=%d y=%d s=%u x=%f y=%f", endPos.x, endPos.y, move_path_.size(), x_, y_);
			}
		}

		if (m_isReturn && move_path_.empty() && !pathing_flag_) {
			m_isReturn = false;
			if (!m_isActively) {
				is_active_ = false;
			}
		}
	}
}

Msg* StdMonster::doAppear() {
	msgs::SMapMonster *ptr = MsgPool::Instance()->GetMsg<msgs::SMapMonster>();
	if (ptr == NULL) {
		return NULL;
	}
	ptr->clear();
	ptr->entityId_ = entity_msg_;
	ptr->spacePos_.x = x_;
	ptr->spacePos_.y = y_;
	ptr->name_ = "monster";
	ptr->level_ = level_;
	ptr->direction_ = 135;
	ptr->maxLife_ = props_[AP_MAXLIFE].pl;
	ptr->curLife_ = props_[AP_HP].pl;
	ptr->monsterId_ = entity_id_;
	ptr->force_ = force_;
	if (belong_id_ > 0) {
		MapDisplayObject *pDo = MapManager::Instance()->getObject(belong_id_);
		if (pDo != NULL) {
			ptr->belongId_ = pDo->getEntityMsg();
		}
	}
	if (owner_id_ > 0) {
		MapDisplayObject *pDo = MapManager::Instance()->getObject(owner_id_);
		if (pDo != NULL) {
			ptr->ownerId_ = pDo->getEntityMsg();
		}
	}
	return ptr;
}

bool StdMonster::doAttack(MapMoveObject* other) {
	if (other->getMapId() != map_id_) {
		first_attacker_.id = 0;
		return false;
	}

	doUseSKill(other);

	return true;
}

bool StdMonster::doUseSKill(MapMoveObject *target) {
	map<int32_t, SkillUseInfo>::iterator itr = map_skill_info_.begin();
	for (; itr != map_skill_info_.end(); ++itr) {
		SkillUseInfo &info = itr->second;
		if (info.nextUseTime > LogicManager::GlobalMilliTime) {
			continue;
		}
		Point cen;
		cen.x = x_;
		cen.y = y_;
		vector<uint32_t> tars;
		tars.push_back(target->getId());
		if (!SkillControler::Instance()->doUseSkill(this, tars, info, cen)) {
			continue;
		}
		info.nextUseTime = LogicManager::GlobalMilliTime + info.cdTime;
		debug_log("skillid=%u", info.skillId);
	}
	return false;
}

void StdMonster::onDie() {
	if (fb_id_ != 0) {
		CarbonManager::Instance()->onMapMoveObjectDie(this);
	}
	map<uint64_t, HurtInfo>::iterator itr = hurt_map_.begin();
	for (; itr != hurt_map_.end(); ++itr) {
		if (itr->first >> 32 == RACE_HUMAN){
			HangManager::Instance()->OnMonsterDie(itr->first & 0xFFFFFFFF, entity_id_, Point(x_, y_));
			CopyManager::Instance()->OnMonsterDie(itr->first & 0xFFFFFFFF, entity_id_, Point(x_, y_));
		}
	}
}

void StdMonster::onFirstAttackerChange() {
	MapMoveObject* pMo = MapManager::Instance()->getObject(first_attacker_.id, first_attacker_.race);
	if (pMo != NULL && m_pathFlag) {
		Point p;
		if (move_path_.empty()) {
			p.x = x_;
			p.y = y_;
		} else {
			p.x = move_path_.rbegin()->x;
			p.y = move_path_.rbegin()->y;
		}
		pMo->addTargetPoint(p.x, p.y);
	}

	m_pathFlag = false;
}

void StdMonster::onSetPath() {
	m_pathFlag = true;
	move_type_ = MOVE_TYPE_WALK | MOVE_TYPE_AI;
	if (!move_path_.empty()) {
		MapMoveManager::Instance()->AddObj(this);
	}
	string log;
	char item[24];
	list<APath::pos>::iterator itr = move_path_.begin();
	for (; itr != move_path_.end(); ++itr) {
		sprintf(item, "[%d,%d],", itr->x, itr->y);
		log.append(item);
	}

	debug_log("%s", log.c_str());


}

void StdMonster::setCanMove(bool flag) {
	m_canMove = flag;
}

void StdMonster::setActively(bool flag) {
	m_isActively = flag;
}

void StdMonster::onDestory() {
}

void StdMonster::onSetPos() {
}

bool StdMonster::canAttack(MapMoveObject *target) {
	return true;
}
