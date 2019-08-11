/*RoleSuitManager.cpp
 *
 * Date :2019.07.09
 *
 * Author: next
 *
 * */

#include "RoleSuitManager.h"
#include "BattleInc.h"

enum SlotIndex {
	SLOT_1 = 0,
	SLOT_2 = 1,
	SLOT_3 = 2,
	SLOT_4 = 3,
	SLOT_5 = 4,
	SLOT_6 = 5,
	SLOT_7 = 6,
	SLOT_8 = 7,

	SLOT_MAX_CNT = 8,
};

enum ShowType {
	ROLE_TITLE_TYPE = 0,
	ROLE_SUIT_TYPE	= 1
};

RoleSuitManager::RoleSuitManager() {

}
RoleSuitManager::~RoleSuitManager() {
}

bool RoleSuitManager::AddRoleSuit(uint32_t uid, uint32_t roleId, uint32_t suitId) {
	UserCache& cache = CacheManager::Instance()->GetUser(uid);
	DataRoleSuit suit;
	suit.init(uid, roleId, TYPE_ROLE_SUIT, suitId);

	DataRoleAttr attr;
	memcpy((void*)&attr, (const void*)&suit, sizeof(suit));
	DataRoleAttrManager::Instance()->Add(attr);

	if(0 == cache.role_suit_.count(roleId)) {
		map<uint32_t, DataRoleSuit> suitMap;
		suitMap.insert(make_pair(suitId, suit));
		cache.role_suit_.insert(make_pair(roleId, suitMap));
	} else {
		map<uint32_t, DataRoleSuit> &suitMap =cache.role_suit_[roleId];
		suitMap.insert(make_pair(suitId, suit));
	}

	return true;
}

bool RoleSuitManager::GetactiveSuit(const map<uint32_t, DataRoleSuit> &source, map<int32_t, map<int32_t, int32_t> > &target) {
	map<uint32_t, DataRoleSuit>::const_iterator it = source.begin();
	for(; it != source.end(); ++it) {
		map<int32_t, int32_t> data;
		for(uint32_t i = 0; i < SLOT_MAX_CNT; ++i) {
			const uint32_t& slot = GetSloteByPart(it->second, i);
			info_log("slot:%u", slot);
			if(0 != slot) {
				data.insert(make_pair(i, 1));
			}
		}
		if(data.size() > 0) {
			target.insert(make_pair(it->first, data));
		}
	}
	return true;
}

bool RoleSuitManager::GetUnlockSuit(const map<uint32_t, DataRoleSuit> &source, map<int32_t, int32_t> &target) {
	map<uint32_t, DataRoleSuit>::const_iterator it = source.begin();
	for(; it != source.end(); ++it) {
		if(IsSuitUnlock(it->second)) {
			target.insert(make_pair(it->first, 1));
		}
	}
	return true;
}

bool RoleSuitManager::IsSuitUnlock(const DataRoleSuit& data) {
	for(int i = 0; i < SLOT_MAX_CNT; ++i) {
		const uint32_t& slot = GetSloteByPart(data, i);
		if(0 == slot) {
			return false;
		}
	}
	return true;
}

bool RoleSuitManager::CalcProperty(const UserCache &cache, byte rid, PropertySets &props){
	map<uint32_t, map<uint32_t, DataRoleSuit> >::const_iterator itr = cache.role_suit_.begin();
	for (; itr != cache.role_suit_.end(); ++itr) {
		if (itr->first != rid) {
			continue;
		}
		map<uint32_t, DataRoleSuit>::const_iterator item = itr->second.begin();
		for(; item != itr->second.end(); ++item) {
			const CfgSuit::Suit &cfg = RoleSuitWrap().GetSuit(item->first);
				PropertyCfg::setProps(cfg.attr(), 1.0, props);
				for (int index = 0; index < cfg.skills_size(); ++index) {
					const CfgSkill::Skill& skill = SkillCfgWrap().GetById(cfg.skills(index));
					PropertyCfg::setProps(skill.attr(), 1.0, props);
				}
		}

	}
	PropertyCfg::showProps(cache.uid_, rid, props, "RoleSuit");
	return true;
}

uint32_t RoleSuitManager::GetStarFromEquip(const DataEquip& equip) {
	Json::Value value = Json::Value(Json::objectValue);
	Json::Reader reader;
	if (!equip.ext.empty() && !reader.parse(equip.ext, value)) {
		error_log("parse equip extend error uid=%u ud=%u ext=%s", equip.uid, equip.ud, equip.ext.c_str());
		return false;
	}
	if(value.isMember("star")) {
		return value["star"].asUInt();

	} else {
		error_log("equip:%d star not exist", equip.id);
		throw std::runtime_error("get equip star error");
	}
}

uint32_t& RoleSuitManager::GetSloteByPart(DataRoleSuit& data, uint32_t index) {
	switch(index) {
	case SLOT_1:
		return (data.slot_1);
	case SLOT_2:
		return  (data.slot_2);
	case SLOT_3:
		return  (data.slot_3);
	case SLOT_4:
		return  (data.slot_4);
	case SLOT_5:
		return  (data.slot_5);
	case SLOT_6:
		return  (data.slot_6);
	case SLOT_7:
		return  (data.slot_7);
	case SLOT_8:
		return  (data.slot_8);
	default:
		throw std::runtime_error("slot index not exist");
	}
}

const uint32_t& RoleSuitManager::GetSloteByPart(const DataRoleSuit& data, uint32_t index) {
	switch(index) {
	case SLOT_1:
		return (data.slot_1);
	case SLOT_2:
		return  (data.slot_2);
	case SLOT_3:
		return  (data.slot_3);
	case SLOT_4:
		return  (data.slot_4);
	case SLOT_5:
		return  (data.slot_5);
	case SLOT_6:
		return  (data.slot_6);
	case SLOT_7:
		return  (data.slot_7);
	case SLOT_8:
		return  (data.slot_8);
	default:
		throw std::runtime_error("slot index not exist");
	}
}

uint16_t RoleSuitManager::GetShowId(uint32_t type) {
	static uint16_t show_ids[] = {53, 1001};
	if (type >= sizeof(show_ids) / sizeof(uint16_t)) {
		error_log("showId type:%u is error", type);
		return 0;
	}
	return show_ids[type];
}

int RoleSuitManager::Process(uint32_t uid, logins::SActiveSuitReq *req) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if(0 == cache.role_.count(req->roleId_)) {
		error_log("role_id:%d not exist", req->roleId_);
		return R_ERROR;
	}
	if(!RoleSuitWrap().isSuitExist(req->suitId_)) {
		error_log("suit_id:%d not exist", req->suitId_);
		return R_ERROR;
	}
	if(0 == cache.role_suit_.count(req->roleId_) || 0 == cache.role_suit_[req->roleId_].count(req->suitId_)) {
		AddRoleSuit(uid, req->roleId_, req->suitId_);
	}

	vector<uint32_t> slots;
	DataRoleSuit& suit = cache.role_suit_[req->roleId_][req->suitId_];

	vector<int64_t>::const_iterator it = req->uids_.begin();
	for(; it != req->uids_.end(); ++it) {
		const CfgSuit::Suit& suit_cfg = RoleSuitWrap().GetSuit(req->suitId_);
		const CfgItem::Equip& cfg = ItemCfgWrap().GetEquip(cache.equip_[*it].id);
		const DataEquip& data = cache.equip_[*it];
		uint32_t star = GetStarFromEquip(data);
		//点亮标志位
		uint32_t& slot = GetSloteByPart(suit, cfg.part());
		if(false == slot && cfg.color() >= suit_cfg.color() && cfg.changelevel() >= suit_cfg.level() && star >= suit_cfg.star()) {
			slots.push_back(cfg.part());
			slot = data.id;
		}
	}
	DataRoleAttr attr;
	memcpy((void*)&attr, (const void*)&suit, sizeof(suit));
	DataRoleAttrManager::Instance()->Set(attr);
	UpdateManager::Instance()->ActiveSuit(uid, req->roleId_, req->suitId_, slots);
	return 0;
}

int RoleSuitManager::Process(uint32_t uid, logins::SUnlockSuitReq *req) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if(0 == cache.role_.count(req->roleId_)) {
		error_log("role_id:%d not exist", req->roleId_);
		return R_ERROR;
	}
	if(0 == cache.role_suit_[req->roleId_].count(req->suitId_)) {
		error_log("Suit_:%d not exist", req->suitId_);
		return R_ERROR;
	}
	DataRoleSuit& suit = cache.role_suit_[req->roleId_][req->suitId_];
	if(true == suit.flag) {
		error_log("Suit_:%d already active", req->suitId_);
		return R_ERROR;
	}

	suit.flag = true;
	DataRoleAttr attr;
	vector<DataSkill> skills;
	memcpy((void*)&attr, (const void*)&suit, sizeof(suit));
	DataRoleAttrManager::Instance()->Set(attr);
	const CfgSuit::Suit& suit_cfg = RoleSuitWrap().GetSuit(req->suitId_);
	for(int i = 0; i < suit_cfg.skills_size(); ++i) {
		const CfgSkill::Skill& skill_cfg = SkillCfgWrap().GetById(suit_cfg.skills(i));
		DataSkill data;
		data.uid = uid;
		data.rid = 0;
		data.lv = 1;
		data.id = skill_cfg.serial();
		data.skill_id = skill_cfg.id();
		DataSkillManager::Instance()->Add(data);
		cache.skill_.push_back(data);
		skills.push_back(data);
	}

	UpdateManager::Instance()->roleUnlock(uid, req->roleId_, req->suitId_);
	UpdateManager::Instance()->roleDress(uid, req->roleId_, req->suitId_);
	UpdateManager::Instance()->skills(uid, req->suitId_ -1, skills);

	return 0;
}
int RoleSuitManager::Process(uint32_t uid, logins::SDressSuitReq *req) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if(0 == cache.role_.count(req->roleId_)) {
		error_log("role_id:%d not exist", req->roleId_);
		return R_ERROR;
	}
	if(0 == cache.role_suit_[req->roleId_].count(req->suitId_)) {
		error_log("Suit_:%d not exist", req->suitId_);
		return R_ERROR;
	}
	uint32_t suitId = req->isDress_ ? req->suitId_ : 0;
	UpdateManager::Instance()->roleDress(uid, req->roleId_, suitId);
	uint32_t showId = GetShowId(ROLE_SUIT_TYPE);
	const CfgSuit::Suit& cfg = RoleSuitWrap().GetSuit(suitId);
	UpdateManager::Instance()->roleShows(uid, cfg.mode(), req->isDress_, showId);
	return 0;
}

int RoleSuitManager::Sync(const UserCache &cache, uint32_t cmd, msgs::SPlayerSuitCollects *resp) {
	map<byte, DataRole>::const_iterator it = cache.role_.begin();
	for(; it != cache.role_.end(); ++it) {
		resp->roleId_ = it->second.id;
		map<uint32_t, map<uint32_t, DataRoleSuit> >::const_iterator item = cache.role_suit_.find(resp->roleId_);
		info_log("role_suit size:%u", cache.role_suit_.size());
		uint32_t suit_id = 0;
		if(item != cache.role_suit_.end()) {
			GetactiveSuit(item->second, resp->activeSuitCollect_);
			GetUnlockSuit(item->second, resp->unlockSuitCollect_);
			if(resp->unlockSuitCollect_.size() > 0) {
				suit_id = resp->unlockSuitCollect_.rbegin()->first;
			}
		}
		if(!LogicManager::Instance()->SendMsg(cache.uid_, cmd, resp)) {
			error_log("sync Role:%d suit Info error",resp->roleId_);
			return R_ERROR;
		}

		UpdateManager::Instance()->roleDress(cache.uid_, it->first, suit_id);
 	}
	return 0;
}
