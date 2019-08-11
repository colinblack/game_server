#include "Human.h"
#include "BattleInc.h"

Human::Human() {
	race_ = RACE_HUMAN;
	m_attackRadius = 0;
	m_teamId = 0;
}

Human::~Human() {
}

bool Human::init(const UserCache &cache, byte rid) {
	map<byte, DataRole>::const_iterator itr = cache.role_.find(rid);
	if (itr == cache.role_.end()) {
		return false;
	}

	const DataRole &role = itr->second;
	const DataPos &pos = cache.pos_;

	MapCfgWrap cfg_warp;
	SceneCfgWrap scene_cfg_warp;
	const CfgMap::Map &map_cfg = cfg_warp.Get(pos.map_id);
	const CfgMap::Scene &scene_cfg = scene_cfg_warp.Get(map_cfg.mapscene());
	if (scene_cfg.instancetype() == SceneCfgWrap::SCENE_TYPE_HANG || cache.base_.hang == 1) {
		Point des_pos;
		HangManager::Instance()->GetHangMap(cache.base_.hang, map_id_, des_pos);
		x_ = des_pos.x;
		y_ = des_pos.y;
	} else {
		x_ = pos.x;
		y_ = pos.y;
		map_id_ = pos.map_id;
	}

	dir_ = pos.dir;
	fb_id_ = pos.fb_id;

	name_ = role.name;
	sex_ = role.sex;
	career_ = role.career;
	level_ = cache.base_.level;
	speed_ = 230;
	move_id_ = MapMoveManager::Instance()->GetMoveId();

	PropertySets props;
	UserManager::Instance()->CalcProperty(cache, rid, props);
	setProps(props);
	props_[AP_HP].pl = props_[AP_MAXLIFE].pl;

	uint32_t combat = PropertyCfg::getCombat(props_);
	if (combat_ != combat) {
		combat_ = combat;
	}

	diff_attr.clear();
	diff_fix_attr.clear();

	AdvanceManager::Instance()->GetEntityShows(cache, rid, shows_);

	id_ = cache.uid_;
	role_id_ = rid;

	entity_msg_.id_ = id_;
	entity_msg_.type_ = Identity::ROLE_TYPE_BEGIN + rid;
	entity_msg_.proxy_ = LogicManager::ProxyId;
	entity_msg_.server_ = LogicManager::ServerId;

	list<DataSkill>::const_iterator skItr = cache.skill_.begin();
	SkillCfgWrap cfgWrap;
	for (; skItr != cache.skill_.end(); ++skItr) {
		if (skItr->rid != rid && skItr->rid != 0) {
			continue;
		}
		const CfgSkill::Skill &cfg = cfgWrap.GetByLv(skItr->id, skItr->lv, skItr->skill_id);
		SkillUseInfo item;
		item.skillId = skItr->skill_id;
		item.skillLevel = skItr->lv;
		item.cdTime = cfg.cd();
		item.entityId = SkillControler::getSkillType(cfg);
		map_skill_info_[item.skillId] = item;
	}

	return true;
}

bool Human::propsCalc() {
	UserCache &cache = CacheManager::Instance()->GetUser(id_);
	if (!cache.init_) {
		return false;
	}

	PropertySets props;
	UserManager::Instance()->CalcProperty(cache, role_id_, props);
	setProps(props);
	props_[AP_HP].pl = props_[AP_MAXLIFE].pl;

	uint32_t combat = PropertyCfg::getCombat(props_);
	if (combat_ != combat) {
		combat_ = combat;
		cache.role_[role_id_].combat = combat;
		DataRoleManager::Instance()->Set(cache.role_[role_id_]);
	}

	msgs::SRoleCombatChange role_msg;
	role_msg.roleId_ = role_id_;
	role_msg.combat_ = combat_;
	getDiffProps(role_msg.diffAttr_, role_msg.diffFixAttr_);
	LogicManager::Instance()->SendMsg(id_, CMD_ROLE_COMBAT_CHANGE, &role_msg);

	msgs::SPlayerCombatChange player_msg;
	player_msg.combat_ = combat_;
	player_msg.avatarCombat_ = 0;
	LogicManager::Instance()->SendMsg(id_, CMD_PLAYER_COMBAT_CHANGE, &player_msg);

	return true;
}

bool Human::initSkill() {
	return true;
}

void Human::onDie() {
	if (fb_id_ != 0) {
		CarbonManager::Instance()->onMapMoveObjectDie(this);
	}
}

void Human::onSetPos() {
}

void Human::doAi() {
	if (!is_active_) {
		return;
	}
//	if (fb_id_ == 0) {
//		return;
//	}
	if (first_attacker_.id == 0) {
		if (!findTarget()) {
			return;
		}
	}
	MapMoveObject *pMo = MapManager::Instance()->getObject(first_attacker_.id, first_attacker_.race);
	if (pMo == NULL || pMo->isDie() || pMo->getHideFlag()) {
		first_attacker_.id = 0;
		return;
	}

	uint32_t dis = getDistance(this, pMo);
	if (m_attackRadius > dis) {
		if (!move_path_.empty()) {
			move_path_.clear();
			syncMoveInfo(true);
		}
		doAttack(pMo);
		return;
	}

	Point targetPos;
	pMo->getPos(targetPos.x, targetPos.y);
	uint16_t excursion = getDistance(m_dest, targetPos);
	if (move_path_.empty() || excursion > m_attackRadius) {
		if (pathing_flag_) {
			return;
		}
		m_dest = targetPos;
		APath::pos endPos;
		endPos.x = targetPos.x;
		endPos.y = targetPos.y;
		PathTask pathTask;
		pathTask.id = id_;
		pathTask.mapId = map_id_;
		pathTask.time = LogicManager::GlobalTime;
		pathTask.address = (void*) this;
		pathTask.start.x = x_;
		pathTask.start.y = y_;
		pathTask.end = endPos;
		pathing_flag_ = true;
		PathManager::Instance()->addTask(pathTask);
		debug_log("find path x=%d y=%d s=%u x=%f y=%f", endPos.x, endPos.y, move_path_.size(), x_, y_);
		move_path_.clear();
	}
}

bool Human::doAttack(MapMoveObject* other) {
	map<int32_t, SkillUseInfo>::iterator itr = map_skill_info_.begin();
	msgs::SBeginFight msg;
	for (; itr != map_skill_info_.end(); ++itr) {
		SkillUseInfo &info = itr->second;
		if (info.nextUseTime > LogicManager::GlobalMilliTime) {
			continue;
		}
		SkillBase *pSkill = const_cast<SkillBase*>(SkillControler::Instance()->getEntity(info.entityId));
		if (pSkill == NULL) {
			continue;
		}

		vector<uint64_t> targets;
		//pSkill->getTargets(info, this, targets);
		targets.push_back(other->getId());
		//pSkill->doSkillHit(info, this, targets);

		info.nextUseTime = LogicManager::GlobalMilliTime + info.cdTime;

		msg.clear();
		msg.fromEntity_ = getEntityMsg();
		msg.toEntitys_.push_back(other->getEntityMsg());
		msg.skillId_ = info.skillId;

		LogicManager::Instance()->SendMsg(id_, CMD_ENTITY_BEGIN_DOFIGHT, &msg);

	}
	return true;
}

bool Human::doUseSkill(int32_t skillId, vector<uint32_t> &tar, const Point &cen) {
	map<int32_t, SkillUseInfo>::iterator itr = map_skill_info_.find(skillId);
	if (itr == map_skill_info_.end()) {
		error_log("skill not exist id=%u skillid=%d", id_, skillId);
		return false;
	}
	SkillUseInfo &info = itr->second;
	if (info.nextUseTime > LogicManager::GlobalMilliTime) {
		error_log("skill is cool down id=%u skillid=%d", id_, skillId);
		return false;
	}
	if (!doSkillCost(info)) {
		error_log("skill cost error id=%u skillid=%d", id_, skillId);
		return false;
	}
	if (!SkillControler::Instance()->doUseSkill(this, tar, info, cen)) {
		error_log("skill hurt error id=%u skillid=%d", id_, skillId);
		return false;
	}
	setRide(false);
	info.nextUseTime = LogicManager::GlobalMilliTime + info.cdTime;
	return true;
}

bool Human::doAddSkill(const DataSkill &skill) {
	SkillCfgWrap cfgWrap;
	map<int32_t, SkillUseInfo>::iterator itr = map_skill_info_.begin();
	for (; itr != map_skill_info_.end(); ++itr) {
		const CfgSkill::Skill &cfg = cfgWrap.GetById(itr->second.skillId);
		if (cfg.serial() == skill.id) {
			const CfgSkill::Skill &new_cfg = cfgWrap.GetById(skill.skill_id);
			map_skill_info_.erase(itr);
			SkillUseInfo item;
			item.skillId = skill.skill_id;
			item.skillLevel = skill.lv;
			item.cdTime = new_cfg.cd();
			item.entityId = SkillControler::getSkillType(new_cfg);
			map_skill_info_[item.skillId] = item;
			debug_log("replace skill %u %u %u", skill.uid, skill.id, skill.lv);
			return true;
		}
	}

	const CfgSkill::Skill &cfg = cfgWrap.GetByLv(skill.id, skill.lv, skill.skill_id);
	SkillUseInfo item;
	item.skillId = skill.skill_id;
	item.skillLevel = skill.lv;
	item.cdTime = cfg.cd();
	item.entityId = SkillControler::getSkillType(cfg);
	map_skill_info_[item.skillId] = item;
	return true;
}

bool Human::doSkillCost(const SkillUseInfo &info) {
	SkillCfgWrap cfg_warp;
	const CfgSkill::Skill &cfg = cfg_warp.GetById(info.skillId);
	if (cfg_warp.IsZhanLing(cfg)) {
		return ZhanLingManager::Instance()->useNuQi(id_);
	}
	return true;
}

Msg* Human::doAppear() {
	msgs::SMapRole *ptr = MsgPool::Instance()->GetMsg<msgs::SMapRole>();
	if (ptr == NULL) {
		return NULL;
	}
	const UserCache &cache = CacheManager::Instance()->GetUser(id_);
	if (!cache.init_) {
		return NULL;
	}
	ptr->clear();
	ptr->entityId_ = entity_msg_;
	ptr->spacePos_.x = x_;
	ptr->spacePos_.y = y_;
	ptr->name_ = name_;
	ptr->sex_ = sex_;
	ptr->career_ = career_;
	ptr->force_ = force_;
	ptr->level_ = cache.base_.level;
	ptr->speed_ = speed_;
	ptr->maxLife_ = props_[AP_MAXLIFE].pl;
	ptr->curLife_ = props_[AP_HP].pl;;
	ptr->entityShows_ = shows_;
	ptr->isRide_ = getRide();
	ptr->careerLevel_ = cache.m_reinCarnInfo.reinCarnLevel;

	return ptr;
}

void Human::onSetPath() {
	move_type_ = MOVE_TYPE_WALK | MOVE_TYPE_AI;
	string log;
	char item[24];
	list<APath::pos>::iterator itr = move_path_.begin();
	for (; itr != move_path_.end(); ++itr) {
		sprintf(item, "[%d,%d],", itr->x, itr->y);
		log.append(item);
	}
	if (!move_path_.empty()) {
		MapMoveManager::Instance()->AddObj(this);
	}
	debug_log("%s", log.c_str());
}

void Human::onSetState() {
}

bool Human::findTarget() {
	vector<MapMoveObject*> vecMonsters;
	MapManager::Instance()->getAroundMonsters(this, vecMonsters);
	if (vecMonsters.empty()) {
		return false;
	}

	uint32_t minDistance = 10000;
	MapMoveObject* nearestMonster = NULL;
	vector<MapMoveObject*>::iterator itr = vecMonsters.begin();
	for (; itr != vecMonsters.end(); ++itr) {
		MapMoveObject *pTarget = *itr;
		uint32_t dis = getDistance(this, pTarget);
		if (dis < minDistance && !pTarget->isDie() && !pTarget->getHideFlag()) {
			minDistance = dis;
			nearestMonster = pTarget;
		}
	}

	if (nearestMonster != NULL) {
		first_attacker_.race = nearestMonster->getRace();
		first_attacker_.id = nearestMonster->getId();
		first_attacker_.lastTime = LogicManager::GlobalTime;
		first_attacker_.hurt = 0;
		return true;
	}

	return false;
}
