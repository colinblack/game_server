/*
 * NearEnemy.cpp
 *
 *  Created on: 2019年8月2日
 *      Author: colin
 */


#include "BattleInc.h"

NearEnemy::NearEnemy(){
	uid_ = 0;
}

NearEnemy::~NearEnemy(){
}

bool NearEnemy::init(const UserCache &cache, byte rid, uint32_t fbId, uint32_t mapId, const Point &p){
	map<byte, DataRole>::const_iterator itr = cache.role_.find(rid);
	if (itr == cache.role_.end()) {
		return false;
	}

	const DataRole &role = itr->second;
	x_ = p.x;
	y_ = p.y;
	bx_ = p.x;
	by_ = p.y;

	entity_id_ = cache.base_.uid;
	fb_id_ = fbId;
	map_id_ = mapId;

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

	AdvanceManager::Instance()->GetEntityShows(cache, rid, shows_);
	uid_ = cache.uid_;
	role_id_ = rid;

	entity_msg_.id_ = id_;
	entity_msg_.type_ = Identity::ROLE_TYPE_BEGIN + rid;
	entity_msg_.proxy_ = LogicManager::ProxyId;
	entity_msg_.server_ = LogicManager::ServerId;

	list<DataSkill>::const_iterator skItr = cache.skill_.begin();
	SkillCfgWrap cfgWrap;
	for (int i = 0; skItr != cache.skill_.end() &&  i < 1; ++skItr, ++i) {
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


bool NearEnemy::recove() {
	if (!MapManager::Instance()->addObject(this)) {
		return false;
	}

	return true;
}

Msg* NearEnemy::doAppear(){
	msgs::SMapRole *ptr = MsgPool::Instance()->GetMsg<msgs::SMapRole>();
	if (ptr == NULL) {
		return NULL;
	}
	const UserCache &cache = CacheManager::Instance()->GetUser(uid_);
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
