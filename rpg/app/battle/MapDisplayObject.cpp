#include "MapDisplayObject.h"
#include "BattleInc.h"

list<uint32_t> MapDisplayObject::idList;
list<uint32_t> MapDisplayObject::otherIdList;
uint32_t MapDisplayObject::maxMonsterId;

MapDisplayObject::MapDisplayObject() {
	lx_ = 0;
	ly_ = 0;
	x_ = 0;
	y_ = 0;
	race_ = 0;
	id_ = 0;
	role_id_ = 0;
	map_id_ = 0;
	last_map_id_ = 0;
	fb_id_ = 0;
	last_fb_id_ = 0;
	belong_id_ = 0;
	owner_id_ = 0;
	force_ = 0;
	recog_ = 0;
}

MapDisplayObject::~MapDisplayObject() {
	if (race_ == RACE_MONSTER || race_ == RACE_PET) {
		idList.push_back(id_);
		static MonsterManager* pmm = MonsterManager::Instance();
		pmm->delObj(this);
	} else if (race_ != RACE_HUMAN) {
		otherIdList.push_back(id_);
	}
	info_log("delete object id=%d,race=%d,mapId=%d,pos[%d,%d],pointer=%p", id_, race_, map_id_, x_, y_, this);
}

void MapDisplayObject::getPos(int& x, int& y) {
	x = x_;
	y = y_;
}

uint32_t MapDisplayObject::getId() {
	return id_;
}

uint32_t MapDisplayObject::getRid() {
	return role_id_;
}
uint32_t MapDisplayObject::getRealFbId() {
	return real_fb_id;
}

uint32_t MapDisplayObject::getMapId() {
	return map_id_;
}

uint32_t MapDisplayObject::getFbId() {
	return fb_id_;
}

uint32_t MapDisplayObject::getLastFbId() {
	return last_fb_id_;
}

uint32_t MapDisplayObject::getBelong() {
	return belong_id_;
}

uint32_t MapDisplayObject::getOwner() {
	return owner_id_;
}

int16_t MapDisplayObject::getForce() {
	return force_;
}

int32_t MapDisplayObject::getRace() {
	return race_;
}

Identity MapDisplayObject::getEntityMsg() {
	return entity_msg_;
}

void MapDisplayObject::onDestory() {

}

void MapDisplayObject::setPos(int x, int y) {
	lx_ = x_;
	ly_ = y_;
	x_ = x;
	y_ = y;
	onSetPos();
}

void MapDisplayObject::setMapId(uint32_t id) {
	last_map_id_ = this->map_id_;
	map_id_ = id;
	onSetMapId();
}

void MapDisplayObject::setFbId(uint32_t id) {
	last_fb_id_ = this->fb_id_;
	fb_id_ = id;
	onSetFbId();
}
void MapDisplayObject::setRealFbId(uint32_t id) {
	real_fb_id = id;
}


void MapDisplayObject::setBelong(uint32_t id) {
	belong_id_ = id;
}

void MapDisplayObject::setOwner(uint32_t id) {
	owner_id_ = id;
}

void MapDisplayObject::setForce(int16_t v) {
	force_ = v;
}

void MapDisplayObject::onSetPos() {

}

void MapDisplayObject::onSetMapId() {

}

void MapDisplayObject::onSetFbId() {

}

void MapDisplayObject::idInit() {
	if (race_ == RACE_MONSTER || race_ == RACE_PET) {
		if (idList.size() > 1000) {
			id_ = idList.front();
			idList.pop_front();
		} else {
			static uint32_t ID_MONSTER = 0;
			id_ = ++ID_MONSTER;
			maxMonsterId = id_;
			if (ID_MONSTER >= ID_MONSTER_MAX) {
				error_log("id monster overflow");
			}
		}
		static MonsterManager* pmm = MonsterManager::Instance();
		pmm->addObj(this);
	} else {
		if (otherIdList.size() > 10000) {
			id_ = otherIdList.front();
			otherIdList.pop_front();
		} else {
			static uint32_t ID_OTHER = ID_START_OTHERS;
			if (++ID_OTHER > ID_END_OTHERS) {
				ID_OTHER = ID_START_OTHERS;
			}
			id_ = ID_OTHER;
		}
	}
	recog_ = id_ * ID_COEFFICIENT;
	info_log("new object addr=%p id=%u", this, id_);
}
