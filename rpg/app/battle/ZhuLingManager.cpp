/*
 * 	ZhuLingManager.cpp
 *
 * 	2019.07.19
 *
 *  auto: next
 *
 * */

#include "ZhuLingManager.h"
#include "BattleInc.h"

#define CONSUM_ITEM_ID 		110170001

enum SlotType {
	ZHULING_SLOT_0 = 0,
	ZHULING_SLOT_1 = 1,
	ZHULING_SLOT_2 = 2,
	ZHULING_SLOT_3 = 3,
	ZHULING_SLOT_4 = 4,
	ZHULING_SLOT_5 = 5,
	ZHULING_SLOT_6 = 6,
	ZHULING_SLOT_7 = 7,
	ZHULING_SLOT_8 = 20,
	ZHULING_SLOT_9 = 21,
	SLOT_TYPE_SIZE = 10,
};

ZhuLingManager::ZhuLingManager() {
}

bool ZhuLingManager::isPartExist(uint32_t part) {
	switch(part) {
	case ZHULING_SLOT_0:
	case ZHULING_SLOT_1:
	case ZHULING_SLOT_2:
	case ZHULING_SLOT_3:
	case ZHULING_SLOT_4:
	case ZHULING_SLOT_5:
	case ZHULING_SLOT_6:
	case ZHULING_SLOT_7:
	case ZHULING_SLOT_8:
	case ZHULING_SLOT_9:
		return true;
	default:
		return false;
	}
}

uint32_t ZhuLingManager::getPart(uint32_t index) {
	switch(index) {
	case 0:
	return ZHULING_SLOT_0;
	case 1:
	return ZHULING_SLOT_1;
	case 2:
	return ZHULING_SLOT_2;
	case 3:
	return ZHULING_SLOT_3;
	case 4:
	return ZHULING_SLOT_4;
	case 5:
	return ZHULING_SLOT_5;
	case 6:
	return ZHULING_SLOT_6;
	case 7:
	return ZHULING_SLOT_7;
	case 8:
	return ZHULING_SLOT_8;
	case 9:
	return ZHULING_SLOT_9;
	default:
		error_log("get zhuling part error");
		throw std::runtime_error("get zhuling part error");
	}
}

const DataEquip& ZhuLingManager::GetRoleEquip(const UserCache& cache, uint32_t rid, uint32_t part) {
	map<byte, map<byte, uint32_t> >::const_iterator it =cache.role_bag_.find(rid);
	if(it != cache.role_bag_.end()) {
		map<byte, uint32_t>::const_iterator item = it->second.begin();
		if(item != it->second.end()) {
			return cache.equip_.at(item->second);
		}
	}
	error_log("ZhuLingequip not exist");
	throw std::runtime_error("ZhuLingequip not exist");
}

bool ZhuLingManager::addZhuLingInfo(UserCache& cache, uint32_t roleId) {
	map<uint32_t, DataZhuLing> part_map;
	DataZhuLing zhuLing;
	for(int i = 0; i < SLOT_TYPE_SIZE; ++i) {
		uint32_t part = getPart(i);
		zhuLing.init(cache.uid_, roleId, TYPE_ROLE_ZHULING, part);
		part_map.insert(make_pair(part, zhuLing));
		ROLE_ATTR_DB_ADD(zhuLing);
	}
	cache.role_zhuLing.insert(make_pair(roleId, part_map));
	return true;
}

bool ZhuLingManager::CalcProperty(const UserCache &cache, byte rid, PropertySets &props) {
	map<uint32_t, map<uint32_t, DataZhuLing> >::const_iterator itr = cache.role_zhuLing.begin();
	for (; itr != cache.role_zhuLing.end(); ++itr) {
		if (itr->first != rid) {
			continue;
		}
		map<uint32_t, DataZhuLing>::const_iterator item = itr->second.begin();
		for(; item != itr->second.end(); ++item) {
			const DataEquip& equip = GetRoleEquip(cache, itr->first, item->first);
			const CfgItem::Equip& equip_cfg = ItemCfgWrap().GetEquip(equip.id);
			if(item->second.advance > 0 && item->second.level > 0) {
				const CfgZhuLing::zhuLing& zhuling_cfg = ZhuLingCfgWrap().GetZhuLing(item->second.advance, item->second.level);
				PropertyCfg::setProps(equip_cfg.attr(), zhuling_cfg.rate()/10000.0, props);

				const CfgZhuLing::Spet& spet_cfg = ZhuLingCfgWrap().GetSpet(item->second.advance, item->first);
				if(100 > spet_cfg.limit()) {
					if(0 == spet_cfg.attr_size()) {
						PropertyCfg::setProps(equip_cfg.attr(), spet_cfg.rate()/10000.0, props);
					} else {
						PropertyCfg::setProps(spet_cfg.attr(), 1.0, props);
					}
				}
			}
		}
	}
	PropertyCfg::showProps(cache.uid_, rid, props, "zhuLing");
	return true;
}

bool ZhuLingManager::format(UserCache& cache, uint32_t rid, uint32_t part, dbs::TPlayerEquip& data, uint32_t type) {
	DataForge forge_data;
	forge_data.uid = cache.uid_;
	forge_data.rid = rid;
	forge_data.type = part;
	list<DataForge>::iterator item =  find(cache.forge_.begin(), cache.forge_.end(), forge_data);
	if (item == cache.forge_.end()) {
		forge_data.strength = 0;
		forge_data.purify = 0;
		forge_data.zhulingLevel = (type == FORMAT_LEVEL) ? 1 : 0;
		forge_data.zhulingAdvance = (type == FORMAT_ADVANCE) ? 1 : 0;
		DataForgeManager::Instance()->Add(forge_data);
		cache.forge_.push_back(forge_data);
		ForgeManager::Instance()->FormatMsg(forge_data, data);
	} else {
		forge_data.zhulingLevel += ((type == FORMAT_LEVEL) ? 1 : 0);
		forge_data.zhulingAdvance += ((type == FORMAT_ADVANCE) ? 1 : 0);
		DataForgeManager::Instance()->Set(forge_data);
		ForgeManager::Instance()->FormatMsg(forge_data, data);
	}
	return true;
}

int ZhuLingManager::Process(uint32_t uid, logins::SopenZhulingReq* req) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return false;
	}
	if(0 == cache.role_.count(req->roleId_)) {
		error_log("role_id:%d not exist", req->roleId_);
		return R_ERROR;
	}
	if(cache.role_zhuLing.count(req->roleId_) != 0) {
		error_log("role:%d zhuLing already open", req->roleId_);
		return R_ERROR;
	}
	addZhuLingInfo(cache, req->roleId_);
	LogicManager::Instance()->AddSync(CMD_PLAYER_ZHULING_OPEN_IFNO);
	return R_SUCCESS;
}

int ZhuLingManager::Process(uint32_t uid, logins::SzhulingUpLevelReq *req, logins::SzhulingUpLevelResp *resp) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return false;
	}
	if(0 == cache.role_.count(req->roleId_)) {
		error_log("role_id:%d not exist", req->roleId_);
		return R_ERROR;
	}
	if(!isPartExist(req->equipType_)) {
		error_log("equipType:%u error", req->equipType_);
		return R_ERROR;
	}
	if(0 == cache.role_zhuLing.count(req->roleId_) ||
			0 == cache.role_zhuLing[req->roleId_].count(req->equipType_)) {
		error_log("role:%d zhuLing not open", req->roleId_);
		return R_ERROR;
	}

	DataZhuLing& data = cache.role_zhuLing[req->roleId_][req->equipType_];
	if(data.level == ZhuLingCfgWrap().GetMaxZhuLinglevel()) {
		error_log("role:%d part:%d, zhuLing level:%d is already Max", req->roleId_, req->equipType_, data.level);
		return R_ERROR;
	}
	//铸灵关卡限制
	const CfgZhuLing::Spet& spet_cfg = ZhuLingCfgWrap().GetSpet(data.advance, req->equipType_);
	if(100/*铸灵关卡*/ < spet_cfg.limit()) {
		error_log("zhuling copy level:%d limited", spet_cfg.limit());
		return R_ERROR;
	}
	uint32_t cost = 0;
	if(req->isAuto_) {
		while(data.level < ZhuLingCfgWrap().GetMaxZhuLinglevel()) {
			data.level++;
			const CfgZhuLing::zhuLing& zhuling_cfg = ZhuLingCfgWrap().GetZhuLing(data.advance, data.level);
			cost += zhuling_cfg.consum();
		}
	} else {
		data.level++;
		const CfgZhuLing::zhuLing& zhuling_cfg = ZhuLingCfgWrap().GetZhuLing(data.advance, data.level);
		cost = zhuling_cfg.consum();
	}
	UpdateManager::Instance()->SetCode(UC_EquipZhuling);
	if(!UserManager::Instance()->UseMoney(uid, CONSUM_ITEM_ID, cost, "zhuLing upLevel use")) {
		return R_ERROR;
	}
	ROLE_ATTR_DB_ADD(data);

	PropertyManager::Instance()->AddUser(cache.uid_);
	format(cache, req->roleId_, req->equipType_, resp->plyerEquip, FORMAT_LEVEL);
	return true;
}

int ZhuLingManager::Process(uint32_t uid, logins::SzhulingUpAdvanceReq *req, logins::SzhulingUpAdvanceResp *resp) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return false;
	}
	if(0 == cache.role_.count(req->roleId_)) {
		error_log("role_id:%d not exist", req->roleId_);
		return R_ERROR;
	}
	if(!isPartExist(req->equipType_)) {
		error_log("equipType:%u error", req->equipType_);
		return R_ERROR;
	}
	if(0 == cache.role_zhuLing.count(req->roleId_) ||
			0 == cache.role_zhuLing[req->roleId_].count(req->equipType_)) {
		error_log("role:%d zhuLing not open", req->roleId_);
		return R_ERROR;
	}

	DataZhuLing& data = cache.role_zhuLing[req->roleId_][req->equipType_];
	if(data.advance == ZhuLingCfgWrap().GetMaxZhuLingAdvance()) {
		error_log("role:%d part:%d, zhuLing advance:%d is already Max", req->roleId_, req->equipType_, data.advance);
		return R_ERROR;
	}
	//铸灵关卡限制
	const CfgZhuLing::Spet& spet_cfg = ZhuLingCfgWrap().GetSpet(data.advance, req->equipType_);
	if(100/*铸灵关卡*/ < spet_cfg.limit()) {
		error_log("zhuling copy level:%d limited", spet_cfg.limit());
		return R_ERROR;
	}

	uint32_t cost = 0;
	data.advance++;
	const CfgZhuLing::zhuLing& zhuling_cfg = ZhuLingCfgWrap().GetZhuLing(data.advance, data.level);
	cost = zhuling_cfg.consum();

	UpdateManager::Instance()->SetCode(UC_EquipZhuling);
	if(!UserManager::Instance()->UseMoney(uid, CONSUM_ITEM_ID, cost, "zhuLing upLevel use")) {
		return R_ERROR;
	}
	ROLE_ATTR_DB_ADD(data);

	PropertyManager::Instance()->AddUser(cache.uid_);
	format(cache, req->roleId_, req->equipType_, resp->PlayerEquip, FORMAT_ADVANCE);
	return true;
}

int ZhuLingManager::Sync(const UserCache& cache, uint32_t cmd, msgs::SInts * msg) {
	map<uint32_t, map<uint32_t, DataZhuLing> >::const_iterator it = cache.role_zhuLing.begin();
	for(; it != cache.role_zhuLing.end(); ++it) {
		msg->values_.push_back(it->first);
	}
	if(!LogicManager::Instance()->SendMsg(cache.uid_, cmd, msg)) {
		return R_ERROR;
	}
	return R_SUCCESS;
}
