#include "BattleInc.h"

MapMoveObject::MapMoveObject() {
	recog_ = id_ * ID_COEFFICIENT;
	dir_ = 0;
	move_type_ = MOVE_TYPE_NONE;
	zone_id_ = 0;
	dx_ = 0;
	dy_ = 0;
	bx_ = 0;
	by_ = 0;
	ltx_ = 0;
	lty_ = 0;
	protect_flag_ = false;
	hide_flag_ = false;
	need_recove_ = false;
	is_active_ = false;
	pathing_flag_ = false;
	ride_ = false;
	dis_ = 0;
	dis_left_ = 0;
	dis_move_ = 0;
	dis_x_ = 0;
	dis_y_ = 0;
	next_skill_time_ = 0;
	entity_id_ = 0;
	pos_idx_ = 0;
	state_ = MO_STATE_NORMAL;
	last_move_time_ = 0;
	alive_time_ = 0;
	combat_ = 0;
	body_width_ = 0;
	level_ = 0;
	speed_ = 0;
	move_id_ = 0;
	sex_ = 0;
	career_ = 0;
	for (uint32_t i = 0; i < AP_VALUE_MAX; ++i) {
		props_[i].pi = 0;
	}
}

MapMoveObject::~MapMoveObject() {

}

void MapMoveObject::doHurt(const PropertySets &changProps) {
	static msgs::SFightUpdate update;
	for (PropertySets::const_iterator it = changProps.begin(); it != changProps.end(); ++it) {
		int type = PropertyCfg::getDataType(it->first);
		switch (type) {
		case DT_INT:
			props_[it->first].pi += it->second.pi;
			break;
		case DT_FLOAT:
			props_[it->first].pf += it->second.pf;
			break;
		case DT_LONG:
			props_[it->first].pl += it->second.pl;
			break;
		case DT_ULONG:
			props_[it->first].pul += it->second.pul;
			break;
		default: {
			if (it->second.pi < 0 && ((unsigned) (-it->second.pi) > props_[it->first].pui)) {
				props_[it->first].pui = 0;
				break;
			}
			props_[it->first].pui += it->second.pi;
		}
			break;
		}
		if (it->first == AP_HP) {
			update.clear();
			update.updateType_ = ATTR_UPDATE_HURT;
			update.updateData_.push_back(1);
			update.updateData_.push_back(0 - it->second.pl);
			fight_update_.push_back(update);
		}
	}

	props_[AP_HP].pl = props_[AP_HP].pl > props_[AP_MAXLIFE].pl ? props_[AP_MAXLIFE].pl : props_[AP_HP].pl;

	if (props_[AP_HP].pl < 0) {
		props_[AP_HP].pl = 0;
	}

	update.clear();
	update.updateType_ = ATTR_UPDATE_HP;
	update.updateData_.push_back(props_[AP_HP].pl);
	update.updateData_.push_back(1);
	fight_update_.push_back(update);

}

uint32_t MapMoveObject::getDistance(const MapMoveObject *pMoA, const MapMoveObject *pMoB) {
	if (pMoA == NULL || pMoB == NULL) {
		return 9999999;
	}
	if (pMoA->map_id_ != pMoB->map_id_) {
		return 9999999;
	}
	return std::max(abs(static_cast<int>(pMoA->x_) - static_cast<int>(pMoB->x_)), abs(static_cast<int>(pMoA->y_) - static_cast<int>(pMoB->y_)));
}

uint32_t MapMoveObject::getDistance(Point p1, Point p2) {
	return std::max(abs(p1.x - p2.x), abs(p1.y - p2.y));
}

uint32_t MapMoveObject::getDistance(int sx, int sy, int ex, int ey) {
	return sqrt(static_cast<double>((sx - ex) * (sx - ex) + (sy - ey) * (sy - ey)));
}

void MapMoveObject::setProps(const PropertySets &props) {
	for (PropertySets::const_iterator it = props.begin(); it != props.end(); ++it) {
		int key = it->first;
		int type = PropertyCfg::getDataType(key);
		switch (type) {
		case DT_INT:
			if (props_[key].pi != it->second.pi) {
				diff_fix_attr[key] = props_[key].pi;
				diff_attr[key] = it->second.pi;
				props_[key].pi = it->second.pi;
			}
			break;
		case DT_UINT:
			if (props_[key].pui != it->second.pui) {
				diff_fix_attr[key] = props_[key].pui;
				diff_attr[key] = it->second.pui;
				props_[key].pi = it->second.pui;
			}
			break;
		case DT_FLOAT:
			if (props_[key].pf != it->second.pf) {
				diff_fix_attr[key] = props_[key].pf;
				diff_attr[key] = it->second.pf;
				props_[key].pf = it->second.pf;
			}
			break;
		case DT_LONG:
			if (props_[key].pl != it->second.pl) {
				diff_fix_attr[key] = props_[key].pl;
				diff_attr[key] = it->second.pl;
				props_[key].pl = it->second.pl;
			}
			break;
		case DT_ULONG:
			if (props_[key].pul != it->second.pul) {
				diff_fix_attr[key] = props_[key].pul;
				diff_attr[key] = it->second.pul;
				props_[key].pul = it->second.pul;
			}
			break;
		}
	}
}

void MapMoveObject::getDiffProps(map<int16_t, int64_t> &diff, map<int16_t, int64_t> &fix) {
	if (!diff_attr.empty()) {
		diff = diff_attr;
		diff_attr.clear();
	}
	if (!diff_fix_attr.empty()) {
		fix = diff_fix_attr;
		diff_fix_attr.clear();
	}
}

bool MapMoveObject::isAttackAble(MapMoveObject *destObj) {
	if ((destObj->race_ == RACE_HUMAN || destObj->race_ == RACE_MONSTER) && !destObj->isDie()) {
		return true;
	}
	return false;
}

void MapMoveObject::setLastAttacker(uint32_t race, uint32_t id) {
	last_attacker_.race = race;
	last_attacker_.id = id;
	last_attacker_.hurt = 0;
	last_attacker_.lastTime = LogicManager::GlobalTime;
}

void MapMoveObject::setLastAttacker(MapMoveObject *pAttacker) {
	last_attacker_.race = pAttacker->getRace();
	if (last_attacker_.race == RACE_HUMAN) {
		last_attacker_.id = dynamic_cast<Human*>(pAttacker)->getUid();
	} else {
		last_attacker_.id = pAttacker->getId();
	}
	last_attacker_.recog = pAttacker->getRecog();
	last_attacker_.hurt = 0;
	last_attacker_.lastTime = LogicManager::GlobalTime;
}

/**
 * 伤害列表计算
 */

void MapMoveObject::onHurt(MapMoveObject *caster, const PropertySets &hurtProps) {
	if (caster == NULL) {
		return;
	}

	if (isDie()) {
		return;
	}

	HurtInfo hurtInfo;
	PropertySets::const_iterator hurtIt = hurtProps.find(AP_HP);
	if (hurtIt != hurtProps.end()) {
		hurtInfo.race = caster->getRace();
		hurtInfo.id = (hurtInfo.race == RACE_HUMAN ? (static_cast<Human *>(caster)->getUid()) : caster->getId());
		hurtInfo.hurt = hurtIt->second.pi * -1;
	}

	if (hurtInfo.hurt <= 0) {
		return;
	}

	if (IS_MONSTER_RACE(race_)) {
		is_active_ = true;
	}

	uint64_t key = ((uint64_t) hurtInfo.race << 32) | hurtInfo.id;
	HurtInfo& attackerHurt = hurt_map_[key];
	attackerHurt.race = hurtInfo.race;
	attackerHurt.id = hurtInfo.id;
	if (LogicManager::GlobalTime - attackerHurt.lastTime > FIRST_ATTACKER_INTERVAL) {
		attackerHurt.hurt = 0;
	}
	attackerHurt.hurt += hurtInfo.hurt;
	attackerHurt.lastTime = LogicManager::GlobalTime;
	if (first_attacker_.id == attackerHurt.id
	|| first_attacker_.id == 0
	|| LogicManager::GlobalTime - first_attacker_.lastTime > FIRST_ATTACKER_INTERVAL
	|| attackerHurt.hurt > first_attacker_.hurt * 1.2) {
		if (first_attacker_.id != attackerHurt.id && first_attacker_.id != 0) {
			onFirstAttackerChange();
		}
		first_attacker_ = attackerHurt;
	}

	setLastAttacker(hurtInfo.race, hurtInfo.id);
}

void MapMoveObject::onAttack(int attackType) {

}

void MapMoveObject::doAi() {

}

void MapMoveObject::onFirstAttackerChange() {

}

void MapMoveObject::onSetPath() {

}

void MapMoveObject::onSetState() {

}

void MapMoveObject::onUpdate(short type) {
	msgs::SEntityUpdate msg;
	msg.clear();
	msg.entityId_ = getEntityMsg();
	msg.updateType_ = type;
	switch(type) {
	case ATTR_UPDATE_RIDE:
		msg.updateData_.push_back(ride_ ? 1 : 0);
		break;
	case ATTR_UPDATE_HP:
		msg.updateData_.push_back(props_[AP_HP].pl);
		break;
	case ATTR_UPDATE_POINT:
		msg.updateData_.push_back(x_);
		msg.updateData_.push_back(y_);
		break;
	default:
		return;
	}
	MapManager::Instance()->mapFieldMsg(this, CMD_PLAYER_UPDATE, &msg);
}

bool MapMoveObject::doAttack(MapMoveObject *other) {
	return false;
}

bool MapMoveObject::doRecover() {
	if (props_[AP_HP].pl == props_[AP_MAXLIFE].pl) {
		return true;
	}
	props_[AP_HP].pl = props_[AP_MAXLIFE].pl;
	onUpdate(ATTR_UPDATE_HP);
	return true;
}

void MapMoveObject::onDie() {

}

bool MapMoveObject::updateSkillProficient(int32_t skillId) {
	return true;
}

void MapMoveObject::syncMoveInfo(bool self) {
}

bool MapMoveObject::moveTick() {
	if (move_type_ == MOVE_TYPE_NONE) {
		return false;
	}
	if (!checkNextWayPoint(false)) {
		return false;
	}
	uint32_t ts = LogicManager::GlobalMilliTime - last_move_time_;
	float dis = getMoveSpeed() * ts + dis_left_;
	dis_left_ = 0.0f;
	debug_log("%u,%f,%f,%f", id_, dis_move_, dis, dis_);
	if (dis <= dis_) {
		dis_ -= dis;
		setPos(x_ + dis * dis_x_, y_ + dis * dis_y_);
	} else {
		dis_left_ = dis - dis_;
		dis_ = 0;
		setPos(dx_, dy_);
	}

	dis_move_ += dis;

	Map *pMap = MapManager::Instance()->getMapInstance(getFbId(), getMapId());
	if (pMap) {
		pMap->objectMove(this);
		if (dis_move_ > 24 || move_path_.empty()) {
			dis_move_ = 0;
		}
	}

	last_move_time_ = LogicManager::GlobalMilliTime;

	if (dis_ <= MIN_MOVE_DISTANCE) {
		checkNextWayPoint(true);
	}

	return true;
}

bool MapMoveObject::moveStop() {
	move_type_ = MOVE_TYPE_NONE;
	move_path_.clear();
	return true;
}

bool MapMoveObject::checkNextWayPoint(bool pop) {
	if (move_path_.empty()) {
		move_type_ = MOVE_TYPE_NONE;
		return false;
	}
	if (pop) {
		move_path_.erase(move_path_.begin());
		if (move_path_.empty()) {
			move_type_ = MOVE_TYPE_NONE;
			return false;
		}
	}

	float x = move_path_.front().x;
	float y = move_path_.front().y;
	float dis = getDistance(x_, y_, x, y);
	if (dis < MIN_MOVE_DISTANCE) {
		return checkNextWayPoint(true);
	}
	dx_ = x;
	dy_ = y;
	dis_ = dis;
	dis_x_ = (x - x_) / dis_;
	dis_y_ = (y - y_) / dis_;
	return true;
}

const SkillUseInfo* MapMoveObject::getSkill(uint32_t skillId) {
	map<int32_t, SkillUseInfo>::const_iterator itr = map_skill_info_.find(skillId);
	if (itr != map_skill_info_.end()) {
		return &itr->second;
	}
	return NULL;
}

void MapMoveObject::getFightUpdate(vector<msgs::SFightUpdate> &data) {
	data = fight_update_;
	fight_update_.clear();
}

void MapMoveObject::addFightUpdate(msgs::SFightUpdate &data) {
	fight_update_.push_back(data);
}

bool MapMoveObject::isAlive() {
	return alive_time_ == 0 || alive_time_ > LogicManager::GlobalTime;
}

uint32_t MapMoveObject::getBodyWidth() {
	return body_width_;
}

void MapMoveObject::getShow(map<int16_t, int32_t> &data) {
	data = shows_;
}

void MapMoveObject::setShow(uint16_t id, uint32_t value) {
	shows_[id] = value;
}

void MapMoveObject::sendShow() {
	msgs::SEntityUpdateEntityShows msg;
	msg.entityId_ = getEntityMsg();
	getShow(msg.shows_);
	MapManager::Instance()->mapFieldMsg(this, CMD_ENTITY_UPDATE_ENTITY_SHOWS, &msg);
}

uint32_t MapMoveObject::calcCombat() {
	combat_ = PropertyCfg::getCombat(props_);
	return combat_;
}

bool MapMoveObject::doLearnSKill(int32_t skillId) {
	return true;
}

bool MapMoveObject::skillUp(int32_t skillId) {
	return true;
}

bool MapMoveObject::initSkill() {
	return true;
}

/**
 * 目标周边的点放入list,从list提取最近的点返回
 */
bool MapMoveObject::getTargetPoint(int &dx, int &dy) {
	static MapManager* pMapManager = MapManager::Instance();
	if (ltx_ != x_ || lty_ != y_) {
		ltx_ = x_;
		lty_ = y_;

		target_points_.clear();
		pMapManager->getAroundPoints(this, target_points_, 3);
	}

	if (target_points_.size() == 0) {
		return false;
	}

	dx = target_points_.begin()->x;
	dy = target_points_.begin()->y;

	target_points_.erase(target_points_.begin());
	return true;
}

//计算目标周边的点用，目标点回收操作
bool MapMoveObject::addTargetPoint(int &dx, int &dy) {
	if (ltx_ != x_ || lty_ != y_) {
		return false;
	}

	if (getDistance(Point(dx, dy), Point(x_, y_)) > 10) {
		return false;
	}

	target_points_.insert(target_points_.begin(), Point(dx, dy));
	return true;
}

Msg* MapMoveObject::doAppear() {
	return NULL;
}

bool MapMoveObject::propsCalc() {
	return true;
}

void MapMoveObject::getRateProps(PropertySets &changeProps) {

}

void MapMoveObject::getAddProps(PropertySets &changeProps) {

}

void MapMoveObject::setPath(const PathRlt &rlt) {
	if (rlt.address != (void*) this) {
		return;
	}
	pathing_flag_ = false;
	if (!rlt.flag) {
		return;
	}

	move_path_ = rlt.path;
	move_path_.erase(move_path_.begin());
	last_move_time_ = LogicManager::GlobalMilliTime;

	onSetPath();
}

void MapMoveObject::setPath(const vector<Point> &path) {
	if (path.empty()) {
		return;
	}
	pathing_flag_ = false;
	vector<Point>::const_iterator itr = path.begin();
	for (; itr != path.end(); ++itr) {
		move_path_.push_back(APath::pos(itr->x, itr->y));
	}
	move_path_.erase(move_path_.begin());
	last_move_time_ = LogicManager::GlobalMilliTime;
	onSetPath();
}
