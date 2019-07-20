/*
 * RoleManager.cpp
 *
 *  Created on: 2019年4月23日
 *      Author: Administrator
 */

#include "RoleManager.h"
#include "BattleInc.h"

RoleManager::RoleManager() {
}

RoleManager::~RoleManager() {
}

bool RoleManager::AddRole(uint32_t uid, uint32_t rid, int16_t sex, int16_t c, const string &n) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return false;
	}

	map<byte, DataRole>::iterator itr = cache.role_.find(rid);
	if (itr != cache.role_.end()) {
		return true;
	}

	DataRole data;
	data.uid = uid;
	data.id = rid;
	data.sex = sex;
	data.name = n;
	data.career = c;

	int ret = DataRoleManager::Instance()->Add(data);
	if (0 != ret) {
		error_log("add role error ret=%u uid=%u rid=%u", ret, uid, rid);
		return false;
	}

	cache.role_[data.id] = data;
	cache.base_.role_num += 1;
	if (cache.base_.role_num == 1) {
		cache.base_.main_role = 1;
	}

	SkillManager::Instance()->AutoUnlock(cache, false);

	return true;
}

bool RoleManager::CalcProperty(const UserCache &cache, byte rid, PropertySets &props) {
	const CfgLevel::Attr &cfg = LevelCfgWrap().GetAttr(cache.base_.level);
	PropertyCfg::setProps(cfg.attr(), 1, props);
//	props[1000 + AP_MAXLIFE].pl = 37720;
//	props[1000 + AP_ATTACK].pui = 500;
//	props[1000 + AP_HIT].pui = 32;
//	props[1000 + AP_DODGE].pui = 32;
//	props[1000 + AP_CRIT].pui = 15000;
	return true;
}

int RoleManager::Sync(const UserCache &cache, uint32_t cmd, msgs::SPlayerRoleList *resp) {
	if (!cache.init_) {
		return false;
	}
	map<byte, DataRole>::const_iterator itr = cache.role_.begin();
	for (; itr != cache.role_.end(); ++itr) {
		const DataRole &role = itr->second;
		dbs::TPlayerRole *item = MsgPool::Instance()->GetMsg<dbs::TPlayerRole>();
		if (item == NULL) {
			continue;
		}
		item->clear();
		item->playerId_ = cache.uid_;
		item->roleId_ = itr->first;
		item->career_ = role.career;
		item->combat_ = role.combat;
		item->maxCombat_ = role.combat;
		item->curLife_ = 999999999999999;
		item->inPower_ = 999999999999999;
		item->avaLife_ = 2147483647;
		item->curMagic_ = 2147483647;
		item->entityShows_ = "{\"53\":11010,\"1001\":0,\"1002\":0,\"1004\":310001,\"1005\":300001}";
		item->entityAttrs_ = "{\"0\":49673,\"1\":4576,\"2\":816,\"9\":15000}";

		resp->roleList_.push_back(item);
	}

	if (!LogicManager::Instance()->SendMsg(cache.uid_, cmd, resp)) {
		return R_ERROR;
	}

	return R_SUCCESS;
}
