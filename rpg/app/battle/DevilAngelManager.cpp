/*
 * DevilAngelManager.cpp
 *
 *  Created on: 2019年7月23日
 *      Author: next
 */

#include "BattleInc.h"
#include "DevilAngelManager.h"

DevilAngelManager::DevilAngelManager() {
}

bool DevilAngelManager::DevilAngelTimeEnd(UserCache &cache) {
	map<uint32_t, map<uint32_t, DataDevilAngel> >::iterator it = cache.devilAngelDate.begin();
	for(; it != cache.devilAngelDate.end(); ++it) {
		map<uint32_t, DataDevilAngel>::iterator item = it->second.begin();
		for(; item != it->second.end(); ++item) {
			if(item->second.ms < uint64_t(Time::GetGlobalTime()) * 1000) {
				item->second.ms = 0;
				ROLE_ATTR_DB_SET(item->second);
				PropertyManager::Instance()->AddUser(cache.uid_);
				LogicManager::Instance()->AddSync(CMD_PLAYER_DEVILANGEL_DATE);
			}
		}
	}
	return true;
}

int DevilAngelManager::Process(uint32_t uid, logins::SBuyReq *req) {
	if(!ItemCfgWrap().IsEquip(req->itemId)) {
		error_log("itemId:%u is not exist", req->itemId);
		return R_ERROR;
	}
	UserManager::Instance()->AddItem(uid, req->itemId, req->num, "admin");
	return R_SUCCESS;
}

bool DevilAngelManager::addDevilAngeleInfo(UserCache& cache, uint32_t equipId, uint32_t rid) {
	DataDevilAngel &data = cache.devilAngelDate[equipId][rid];
	data.init(cache.uid_, rid, TYPE_ROLE_ANGEL, equipId);
	ROLE_ATTR_DB_ADD(data);
	return true;
}

bool DevilAngelManager::onSecondTimer() {
	vector<uint32_t> uids;
	CacheManager::Instance()->GetAllUser(uids);
	for(uint32_t i=0;i<uids.size();i++){
		UserCache &cache = CacheManager::Instance()->GetUser(uids[i]);
		if(!cache.init_) {
			return false;
		}
		DevilAngelTimeEnd(cache);
	}
	return true;
}

int DevilAngelManager::Process(uint32_t uid, logins::SDevilAngelequipReq *req) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if(0 == cache.role_.count(req->roleId)) {
		error_log("role_id:%d not exist", req->roleId);
		return R_ERROR;
	}
	map<uint32_t, DataEquip>::iterator it = cache.equip_.find(req->uid);
	if(it == cache.equip_.end()) {
		error_log("equip uid:%u is not exist", req->uid);
		return R_ERROR;
	}

	DataEquip& equip = cache.equip_[req->uid];
	UpdateManager::Instance()->SetCode(UC_EquipDevilAngel);
	if(!UserManager::Instance()->UseItem(uid, equip.id, 1, "DavilAngel")) {
		return R_ERROR;
	}

	const CfgItem::Equip& equip_cfg = ItemCfgWrap().GetEquip(equip.id);
	if(0 == cache.devilAngelDate.count(equip.id) ||
			0 == cache.devilAngelDate[equip.id].count(req->roleId)) {
		addDevilAngeleInfo(cache, equip.id, req->roleId);
	}

	DataDevilAngel &data = cache.devilAngelDate[equip.id][req->roleId];
	if(0 == data.ms || data.ms < Time::GetGlobalTime() * 1000) {
		data.ms = uint64_t(Time::GetGlobalTime() + equip_cfg.active_min() * 60) * 1000;
		PropertyManager::Instance()->AddUser(cache.uid_);
	} else{
		data.ms += (equip_cfg.active_min() * 60 * 1000);
	}

	ROLE_ATTR_DB_SET(data);
	LogicManager::Instance()->AddSync(CMD_PLAYER_DEVILANGEL_DATE);
	return R_SUCCESS;
}

int DevilAngelManager::Sync(const UserCache & cache, uint32_t cmd, msgs::SDevilAngelDate *resp) {
	map<uint32_t, map<uint32_t, DataDevilAngel> >::const_iterator it = cache.devilAngelDate.begin();
	for(; it != cache.devilAngelDate.end(); ++it) {
		msgs::SDevilAngelRoleDate data;
		map<uint32_t, DataDevilAngel>::const_iterator item = it->second.begin();
		for(; item != it->second.end(); ++item) {
			data.roleDate_.insert(make_pair(item->first, item->second.ms));
		}
		resp->devilAngelDate_.insert(make_pair(it->first, data));
	}
	if (!LogicManager::Instance()->SendMsg(cache.uid_, cmd, resp)) {
		return R_ERROR;
	}
	return R_SUCCESS;
}

